/*
 * Authored by Alex Hultman, 2018-2019.
 * Intellectual property of third-party.

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef LIBUS_USE_OPENSSL

/* These are in sni_tree.cpp */
void *sni_new();
void sni_free(void *sni, void(*cb)(void *));
int sni_add(void *sni, const char *hostname, void *user);
void *sni_remove(void *sni, const char *hostname);
void *sni_find(void *sni, const char *hostname);

#include "libusockets.h"
#include "internal/internal.h"
#include <string.h>

/* This module contains the entire OpenSSL implementation
 * of the SSL socket and socket context interfaces. */

#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

/* We do not want to block the loop with tons and tons of CPU-intensive work.
 * Spread it out during many loop iterations, prioritizing already open connections,
 * they are far easier on CPU */
static const int MAX_HANDSHAKES_PER_LOOP_ITERATION = 5;

struct loop_ssl_data {
    char *ssl_read_input, *ssl_read_output;
    unsigned int ssl_read_input_length;
    unsigned int ssl_read_input_offset;
    struct us_socket_t *ssl_socket;

    int last_write_was_msg_more;
    int msg_more;

    // these are used to throttle SSL handshakes per loop iteration
    long long last_iteration_nr;
    int handshake_budget;

    BIO *shared_rbio;
    BIO *shared_wbio;
    BIO_METHOD *shared_biom;
};

struct us_internal_ssl_socket_context_t {
    struct us_socket_context_t sc;

    // this thing can be shared with other socket contexts via socket transfer!
    // maybe instead of holding once you hold many, a vector or set
    // when a socket that belongs to another socket context transfers to a new socket context
    SSL_CTX *ssl_context;
    int is_parent;

    /* These decorate the base implementation */
    struct us_internal_ssl_socket_t *(*on_open)(struct us_internal_ssl_socket_t *, int is_client, char *ip, int ip_length);
    struct us_internal_ssl_socket_t *(*on_data)(struct us_internal_ssl_socket_t *, char *data, int length);
    struct us_internal_ssl_socket_t *(*on_writable)(struct us_internal_ssl_socket_t *);
    struct us_internal_ssl_socket_t *(*on_close)(struct us_internal_ssl_socket_t *, int code, void *reason);

    /* Called for missing SNI hostnames, if not NULL */
    void (*on_server_name)(struct us_internal_ssl_socket_context_t *, const char *hostname);

    /* Pointer to sni tree, created when the context is created and freed likewise when freed */
    void *sni;
};

// same here, should or shouldn't it contain s?
struct us_internal_ssl_socket_t {
    struct us_socket_t s;
    SSL *ssl;
    int ssl_write_wants_read; // we use this for now
    int ssl_read_wants_write;
};

int passphrase_cb(char *buf, int size, int rwflag, void *u) {
    const char *passphrase = (const char *) u;
    size_t passphrase_length = strlen(passphrase);
    memcpy(buf, passphrase, passphrase_length);
    // put null at end? no?
    return (int) passphrase_length;
}

int BIO_s_custom_create(BIO *bio) {
    BIO_set_init(bio, 1);
    return 1;
}

long BIO_s_custom_ctrl(BIO *bio, int cmd, long num, void *user) {
    switch(cmd) {
    case BIO_CTRL_FLUSH:
        return 1;
    default:
        return 0;
    }
}

int BIO_s_custom_write(BIO *bio, const char *data, int length) {
    struct loop_ssl_data *loop_ssl_data = (struct loop_ssl_data *) BIO_get_data(bio);

    //printf("BIO_s_custom_write\n");

    loop_ssl_data->last_write_was_msg_more = loop_ssl_data->msg_more || length == 16413;
    int written = us_socket_write(0, loop_ssl_data->ssl_socket, data, length, loop_ssl_data->last_write_was_msg_more);

    if (!written) {
        BIO_set_flags(bio, BIO_FLAGS_SHOULD_RETRY | BIO_FLAGS_WRITE);
        return -1;
    }

    //printf("BIO_s_custom_write returns: %d\n", ret);

    return written;
}

int BIO_s_custom_read(BIO *bio, char *dst, int length) {
    struct loop_ssl_data *loop_ssl_data = (struct loop_ssl_data *) BIO_get_data(bio);

    //printf("BIO_s_custom_read\n");

    if (!loop_ssl_data->ssl_read_input_length) {
        BIO_set_flags(bio, BIO_FLAGS_SHOULD_RETRY | BIO_FLAGS_READ);
        return -1;
    }

    if ((unsigned int) length > loop_ssl_data->ssl_read_input_length) {
        length = loop_ssl_data->ssl_read_input_length;
    }

    memcpy(dst, loop_ssl_data->ssl_read_input + loop_ssl_data->ssl_read_input_offset, length);

    loop_ssl_data->ssl_read_input_offset += length;
    loop_ssl_data->ssl_read_input_length -= length;
    return length;
}

struct us_internal_ssl_socket_t *ssl_on_open(struct us_internal_ssl_socket_t *s, int is_client, char *ip, int ip_length) {
    struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

    struct us_loop_t *loop = us_socket_context_loop(0, &context->sc);
    struct loop_ssl_data *loop_ssl_data = (struct loop_ssl_data *) loop->data.ssl_data;

    s->ssl = SSL_new(context->ssl_context);
    s->ssl_write_wants_read = 0;
    s->ssl_read_wants_write = 0;
    SSL_set_bio(s->ssl, loop_ssl_data->shared_rbio, loop_ssl_data->shared_wbio);

    BIO_up_ref(loop_ssl_data->shared_rbio);
    BIO_up_ref(loop_ssl_data->shared_wbio);

    if (is_client) {
        SSL_set_connect_state(s->ssl);
    } else {
        SSL_set_accept_state(s->ssl);
    }

    return (struct us_internal_ssl_socket_t *) context->on_open(s, is_client, ip, ip_length);
}

/* This one is a helper; it is entirely shared with non-SSL so can be removed */
struct us_internal_ssl_socket_t *us_internal_ssl_socket_close(struct us_internal_ssl_socket_t *s, int code, void *reason) {
    return (struct us_internal_ssl_socket_t *) us_socket_close(0, (struct us_socket_t *) s, code, reason);
}

struct us_internal_ssl_socket_t *ssl_on_close(struct us_internal_ssl_socket_t *s, int code, void *reason) {
    struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

    SSL_free(s->ssl);

    return context->on_close(s, code, reason);
}

struct us_internal_ssl_socket_t *ssl_on_end(struct us_internal_ssl_socket_t *s) {
    // struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

    // whatever state we are in, a TCP FIN is always an answered shutdown

    /* Todo: this should report CLEANLY SHUTDOWN as reason */
    return us_internal_ssl_socket_close(s, 0, NULL);
}

// this whole function needs a complete clean-up
struct us_internal_ssl_socket_t *ssl_on_data(struct us_internal_ssl_socket_t *s, void *data, int length) {
    // note: this context can change when we adopt the socket!
    struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

    struct us_loop_t *loop = us_socket_context_loop(0, &context->sc);
    struct loop_ssl_data *loop_ssl_data = (struct loop_ssl_data *) loop->data.ssl_data;

    // note: if we put data here we should never really clear it (not in write either, it still should be available for SSL_write to read from!)
    loop_ssl_data->ssl_read_input = data;
    loop_ssl_data->ssl_read_input_length = length;
    loop_ssl_data->ssl_read_input_offset = 0;
    loop_ssl_data->ssl_socket = &s->s;
    loop_ssl_data->msg_more = 0;

    if (us_internal_ssl_socket_is_shut_down(s)) {

        int ret;
        if ((ret = SSL_shutdown(s->ssl)) == 1) {
            // two phase shutdown is complete here
            //printf("Two step SSL shutdown complete\n");

            /* Todo: this should also report some kind of clean shutdown */
            return us_internal_ssl_socket_close(s, 0, NULL);
        } else if (ret < 0) {

            int err = SSL_get_error(s->ssl, ret);

            if (err == SSL_ERROR_SSL || err == SSL_ERROR_SYSCALL) {
                // we need to clear the error queue in case these added to the thread local queue
                ERR_clear_error();
            }

        }

        // no further processing of data when in shutdown state
        return s;
    }

    // bug checking: this loop needs a lot of attention and clean-ups and check-ups
    int read = 0;
    restart:
    while (1) {
        int just_read = SSL_read(s->ssl, loop_ssl_data->ssl_read_output + LIBUS_RECV_BUFFER_PADDING + read, LIBUS_RECV_BUFFER_LENGTH - read);

        if (just_read <= 0) {
            int err = SSL_get_error(s->ssl, just_read);

            // as far as I know these are the only errors we want to handle
            if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) {

                // clear per thread error queue if it may contain something
                if (err == SSL_ERROR_SSL || err == SSL_ERROR_SYSCALL) {
                    ERR_clear_error();
                }

                // terminate connection here
                return us_internal_ssl_socket_close(s, 0, NULL);
            } else {
                // emit the data we have and exit

                if (err == SSL_ERROR_WANT_WRITE) {
                    // here we need to trigger writable event next ssl_read!
                    s->ssl_read_wants_write = 1;
                }

                // assume we emptied the input buffer fully or error here as well!
                if (loop_ssl_data->ssl_read_input_length) {
                    return us_internal_ssl_socket_close(s, 0, NULL);
                }

                // cannot emit zero length to app
                if (!read) {
                    break;
                }

                context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

                s = context->on_data(s, loop_ssl_data->ssl_read_output + LIBUS_RECV_BUFFER_PADDING, read);
                if (us_socket_is_closed(0, &s->s)) {
                    return s;
                }

                break;
            }

        }

        read += just_read;

        // at this point we might be full and need to emit the data to application and start over
        if (read == LIBUS_RECV_BUFFER_LENGTH) {

            context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

            // emit data and restart
            s = context->on_data(s, loop_ssl_data->ssl_read_output + LIBUS_RECV_BUFFER_PADDING, read);
            if (us_socket_is_closed(0, &s->s)) {
                return s;
            }

            read = 0;
            goto restart;
        }
    }

    // trigger writable if we failed last write with want read
    if (s->ssl_write_wants_read) {
        s->ssl_write_wants_read = 0;

        // make sure to update context before we call (context can change if the user adopts the socket!)
        context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

        s = (struct us_internal_ssl_socket_t *) context->sc.on_writable(&s->s); // cast here!
        // if we are closed here, then exit
        if (us_socket_is_closed(0, &s->s)) {
            return s;
        }
    }

    // check this then?
    if (SSL_get_shutdown(s->ssl) & SSL_RECEIVED_SHUTDOWN) {
        //printf("SSL_RECEIVED_SHUTDOWN\n");

        //exit(-2);

        // not correct anyways!
        s = us_internal_ssl_socket_close(s, 0, NULL);

        //us_
    }

    return s;
}

struct us_internal_ssl_socket_t *ssl_on_writable(struct us_internal_ssl_socket_t *s) {

    struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

    // todo: cork here so that we efficiently output both from reading and from writing?

    if (s->ssl_read_wants_write) {
        s->ssl_read_wants_write = 0;

        // make sure to update context before we call (context can change if the user adopts the socket!)
        context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

        // if this one fails to write data, it sets ssl_read_wants_write again
        s = (struct us_internal_ssl_socket_t *) context->sc.on_data(&s->s, 0, 0); // cast here!
    }

    // should this one come before we have read? should it come always? spurious on_writable is okay
    s = context->on_writable(s);

    return s;
}

/* Lazily inits loop ssl data first time */
void us_internal_init_loop_ssl_data(struct us_loop_t *loop) {
    if (!loop->data.ssl_data) {
        struct loop_ssl_data *loop_ssl_data = malloc(sizeof(struct loop_ssl_data));

        loop_ssl_data->ssl_read_output = malloc(LIBUS_RECV_BUFFER_LENGTH + LIBUS_RECV_BUFFER_PADDING * 2);

        OPENSSL_init_ssl(0, NULL);

        loop_ssl_data->shared_biom = BIO_meth_new(BIO_TYPE_MEM, "µS BIO");
        BIO_meth_set_create(loop_ssl_data->shared_biom, BIO_s_custom_create);
        BIO_meth_set_write(loop_ssl_data->shared_biom, BIO_s_custom_write);
        BIO_meth_set_read(loop_ssl_data->shared_biom, BIO_s_custom_read);
        BIO_meth_set_ctrl(loop_ssl_data->shared_biom, BIO_s_custom_ctrl);

        loop_ssl_data->shared_rbio = BIO_new(loop_ssl_data->shared_biom);
        loop_ssl_data->shared_wbio = BIO_new(loop_ssl_data->shared_biom);
        BIO_set_data(loop_ssl_data->shared_rbio, loop_ssl_data);
        BIO_set_data(loop_ssl_data->shared_wbio, loop_ssl_data);

        // reset handshake budget (doesn't matter what loop nr we start on)
        loop_ssl_data->last_iteration_nr = 0;
        loop_ssl_data->handshake_budget = MAX_HANDSHAKES_PER_LOOP_ITERATION;

        loop->data.ssl_data = loop_ssl_data;
    }
}

/* Called by loop free, clears any loop ssl data */
void us_internal_free_loop_ssl_data(struct us_loop_t *loop) {
    struct loop_ssl_data *loop_ssl_data = (struct loop_ssl_data *) loop->data.ssl_data;

    if (loop_ssl_data) {
        free(loop_ssl_data->ssl_read_output);

        BIO_free(loop_ssl_data->shared_rbio);
        BIO_free(loop_ssl_data->shared_wbio);

        BIO_meth_free(loop_ssl_data->shared_biom);

        free(loop_ssl_data);
    }
}

// we ignore reading data for ssl sockets that are
// in init state, if our so called budget for doing
// so won't allow it. here we actually use
// the kernel buffering to our advantage
int ssl_ignore_data(struct us_internal_ssl_socket_t *s) {

    // fast path just checks for init
    if (!SSL_in_init(s->ssl)) {
        return 0;
    }

    // this path is run for all ssl sockets that are in init and just got data event from polling

    struct us_loop_t *loop = s->s.context->loop;
    struct loop_ssl_data *loop_ssl_data = loop->data.ssl_data;

    // reset handshake budget if new iteration
    if (loop_ssl_data->last_iteration_nr != us_loop_iteration_number(loop)) {
        loop_ssl_data->last_iteration_nr = us_loop_iteration_number(loop);
        loop_ssl_data->handshake_budget = MAX_HANDSHAKES_PER_LOOP_ITERATION;
    }

    if (loop_ssl_data->handshake_budget) {
        loop_ssl_data->handshake_budget--;
        return 0;
    }

    // ignore this data event
    return 1;
}

/* Per-context functions */
void *us_internal_ssl_socket_context_get_native_handle(struct us_internal_ssl_socket_context_t *context) {
    return context->ssl_context;
}

struct us_internal_ssl_socket_context_t *us_internal_create_child_ssl_socket_context(struct us_internal_ssl_socket_context_t *context, int context_ext_size) {
    /* Create a new non-SSL context */
    struct us_socket_context_options_t options = {0};
    struct us_internal_ssl_socket_context_t *child_context = (struct us_internal_ssl_socket_context_t *) us_create_socket_context(0, context->sc.loop, sizeof(struct us_internal_ssl_socket_context_t) + context_ext_size, options);

    /* The only thing we share is SSL_CTX */
    child_context->ssl_context = context->ssl_context;
    child_context->is_parent = 0;

    return child_context;
}

/* Common function for creating a context from options.
 * We must NOT free a SSL_CTX with only SSL_CTX_free! Also free any password */
void free_ssl_context(SSL_CTX *ssl_context) {
    if (!ssl_context) {
        return;
    }

    /* If we have set a password string, free it here */
    void *password = SSL_CTX_get_default_passwd_cb_userdata(ssl_context);
    /* OpenSSL returns NULL if we have no set password */
    free(password);

    SSL_CTX_free(ssl_context);
}

/* This function should take any options and return SSL_CTX - which has to be free'd with
 * our destructor function - free_ssl_context() */
SSL_CTX *create_ssl_context_from_options(struct us_socket_context_options_t options) {
    /* Create the context */
    SSL_CTX *ssl_context = SSL_CTX_new(TLS_method());

    /* Default options we rely on - changing these will break our logic */
    SSL_CTX_set_read_ahead(ssl_context, 1);
    SSL_CTX_set_mode(ssl_context, SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);

    /* Anything below TLS 1.2 is disabled */
    SSL_CTX_set_min_proto_version(ssl_context, TLS1_2_VERSION);

    /* The following are helpers. You may easily implement whatever you want by using the native handle directly */

    /* Important option for lowering memory usage, but lowers performance slightly */
    if (options.ssl_prefer_low_memory_usage) {
       SSL_CTX_set_mode(ssl_context, SSL_MODE_RELEASE_BUFFERS);
    }

    if (options.passphrase) {
        /* When freeing the CTX we need to check SSL_CTX_get_default_passwd_cb_userdata and
         * free it if set */
        SSL_CTX_set_default_passwd_cb_userdata(ssl_context, (void *) strdup(options.passphrase));
        SSL_CTX_set_default_passwd_cb(ssl_context, passphrase_cb);
    }

    /* This one most probably do not need the cert_file_name string to be kept alive */
    if (options.cert_file_name) {
        if (SSL_CTX_use_certificate_chain_file(ssl_context, options.cert_file_name) != 1) {
            free_ssl_context(ssl_context);
            return NULL;
        }
    }

    /* Same as above - we can discard this string afterwards I suppose */
    if (options.key_file_name) {
        if (SSL_CTX_use_PrivateKey_file(ssl_context, options.key_file_name, SSL_FILETYPE_PEM) != 1) {
            free_ssl_context(ssl_context);
            return NULL;
        }
    }

    if (options.ca_file_name) {
        STACK_OF(X509_NAME) *ca_list;
        ca_list = SSL_load_client_CA_file(options.ca_file_name);
        if(ca_list == NULL) {
            free_ssl_context(ssl_context);
            return NULL;
        }
        SSL_CTX_set_client_CA_list(ssl_context, ca_list);
        if (SSL_CTX_load_verify_locations(ssl_context, options.ca_file_name, NULL) != 1) {
            free_ssl_context(ssl_context);
            return NULL;
        }
        SSL_CTX_set_verify(ssl_context, SSL_VERIFY_PEER, NULL);
    }

    if (options.dh_params_file_name) {
        /* Set up ephemeral DH parameters. */
        DH *dh_2048 = NULL;
        FILE *paramfile;
        paramfile = fopen(options.dh_params_file_name, "r");

        if (paramfile) {
            dh_2048 = PEM_read_DHparams(paramfile, NULL, NULL, NULL);
            fclose(paramfile);
        } else {
            free_ssl_context(ssl_context);
            return NULL;
        }

        if (dh_2048 == NULL) {
            free_ssl_context(ssl_context);
            return NULL;
        }

        const long set_tmp_dh = SSL_CTX_set_tmp_dh(ssl_context, dh_2048);
        DH_free(dh_2048);

        if (set_tmp_dh != 1) {
            free_ssl_context(ssl_context);
            return NULL;
        }

        /* OWASP Cipher String 'A+' (https://www.owasp.org/index.php/TLS_Cipher_String_Cheat_Sheet) */
        if (SSL_CTX_set_cipher_list(ssl_context, "DHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-RSA-AES128-GCM-SHA256") != 1) {
            free_ssl_context(ssl_context);
            return NULL;
        }
    }

    /* This must be free'd with free_ssl_context, not SSL_CTX_free */
    return ssl_context;
}

/* Todo: return error on failure? */
void us_internal_ssl_socket_context_add_server_name(struct us_internal_ssl_socket_context_t *context, const char *hostname_pattern, struct us_socket_context_options_t options) {

    /* Try and construct an SSL_CTX from options */
    SSL_CTX *ssl_context = create_ssl_context_from_options(options);

    /* We do not want to hold any nullptr's in our SNI tree */
    if (ssl_context) {
        if (sni_add(context->sni, hostname_pattern, ssl_context)) {
            /* If we already had that name, ignore */
            free_ssl_context(ssl_context);
        }
    }
}

void us_internal_ssl_socket_context_on_server_name(struct us_internal_ssl_socket_context_t *context, void (*cb)(struct us_internal_ssl_socket_context_t *, const char *hostname)) {
    context->on_server_name = cb;
}

void us_internal_ssl_socket_context_remove_server_name(struct us_internal_ssl_socket_context_t *context, const char *hostname_pattern) {

    /* The same thing must happen for sni_free, that's why we have a callback */
    SSL_CTX *sni_node_ssl_context = (SSL_CTX *) sni_remove(context->sni, hostname_pattern);
    free_ssl_context(sni_node_ssl_context);
}

/* Returns NULL or SSL_CTX. May call missing server name callback */
SSL_CTX *resolve_context(struct us_internal_ssl_socket_context_t *context, const char *hostname) {

    /* Try once first */
    void *user = sni_find(context->sni, hostname);
    if (!user) {
        /* Emit missing hostname then try again */
        if (!context->on_server_name) {
            /* We have no callback registered, so fail */
            return NULL;
        }

        context->on_server_name(context, hostname);

        /* Last try */
        user = sni_find(context->sni, hostname);
    }

    return user;
}

// arg is context
int sni_cb(SSL *ssl, int *al, void *arg) {

    if (ssl) {
        const char *hostname = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
        if (hostname && hostname[0]) {
            /* Try and resolve (match) required hostname with what we have registered */
            SSL_CTX *resolved_ssl_context = resolve_context((struct us_internal_ssl_socket_context_t *) arg, hostname);
            if (resolved_ssl_context) {
                //printf("Did find matching SNI context for hostname: <%s>!\n", hostname);
                SSL_set_SSL_CTX(ssl, resolved_ssl_context);
            } else {
                /* Call a blocking callback notifying of missing context */
            }

        }

        return SSL_TLSEXT_ERR_OK;
    }

    /* Can we even come here ever? */
    return SSL_TLSEXT_ERR_NOACK;
}

struct us_internal_ssl_socket_context_t *us_internal_create_ssl_socket_context(struct us_loop_t *loop, int context_ext_size, struct us_socket_context_options_t options) {
    /* If we haven't initialized the loop data yet, do so .
     * This is needed because loop data holds shared OpenSSL data and
     * the function is also responsible for initializing OpenSSL */
    us_internal_init_loop_ssl_data(loop);

    /* First of all we try and create the SSL context from options */
    SSL_CTX *ssl_context = create_ssl_context_from_options(options);
    if (!ssl_context) {
        /* We simply fail early if we cannot even create the OpenSSL context */
        return NULL;
    }

    /* Otherwise ee continue by creating a non-SSL context, but with larger ext to hold our SSL stuff */
    struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_create_socket_context(0, loop, sizeof(struct us_internal_ssl_socket_context_t) + context_ext_size, options);

    /* I guess this is the only optional callback */
    context->on_server_name = NULL;

    /* Then we extend its SSL parts */
    context->ssl_context = ssl_context;//create_ssl_context_from_options(options);
    context->is_parent = 1;

    /* We, as parent context, may ignore data */
    context->sc.ignore_data = (int (*)(struct us_socket_t *)) ssl_ignore_data;

    /* Parent contexts may use SNI */
    SSL_CTX_set_tlsext_servername_callback(context->ssl_context, sni_cb);
    SSL_CTX_set_tlsext_servername_arg(context->ssl_context, context);

    /* Also create the SNI tree */
    context->sni = sni_new();

    return context;
}

/* Our destructor for hostnames, used below */
void sni_hostname_destructor(void *user) {
    /* Some nodes hold null, so this one must ignore this case */
    free_ssl_context((SSL_CTX *) user);
}

void us_internal_ssl_socket_context_free(struct us_internal_ssl_socket_context_t *context) {
    /* If we are parent then we need to free our OpenSSL context */
    if (context->is_parent) {
        free_ssl_context(context->ssl_context);

        /* Here we need to register a temporary callback for all still-existing hostnames
         * and their contexts. Only parents have an SNI tree */
        sni_free(context->sni, sni_hostname_destructor);
    }

    us_socket_context_free(0, &context->sc);
}

struct us_listen_socket_t *us_internal_ssl_socket_context_listen(struct us_internal_ssl_socket_context_t *context, const char *host, int port, int options, int socket_ext_size) {
    return us_socket_context_listen(0, &context->sc, host, port, options, sizeof(struct us_internal_ssl_socket_t) - sizeof(struct us_socket_t) + socket_ext_size);
}

struct us_internal_ssl_socket_t *us_internal_ssl_socket_context_connect(struct us_internal_ssl_socket_context_t *context, const char *host, int port, const char *source_host, int options, int socket_ext_size) {
    return (struct us_internal_ssl_socket_t *) us_socket_context_connect(0, &context->sc, host, port, source_host, options, sizeof(struct us_internal_ssl_socket_t) - sizeof(struct us_socket_t) + socket_ext_size);
}

void us_internal_ssl_socket_context_on_open(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *(*on_open)(struct us_internal_ssl_socket_t *s, int is_client, char *ip, int ip_length)) {
    us_socket_context_on_open(0, &context->sc, (struct us_socket_t *(*)(struct us_socket_t *, int, char *, int)) ssl_on_open);
    context->on_open = on_open;
}

void us_internal_ssl_socket_context_on_close(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *(*on_close)(struct us_internal_ssl_socket_t *s, int code, void *reason)) {
    us_socket_context_on_close(0, (struct us_socket_context_t *) context, (struct us_socket_t *(*)(struct us_socket_t *, int, void *)) ssl_on_close);
    context->on_close = on_close;
}

void us_internal_ssl_socket_context_on_data(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *(*on_data)(struct us_internal_ssl_socket_t *s, char *data, int length)) {
    us_socket_context_on_data(0, (struct us_socket_context_t *) context, (struct us_socket_t *(*)(struct us_socket_t *, char *, int)) ssl_on_data);
    context->on_data = on_data;
}

void us_internal_ssl_socket_context_on_writable(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *(*on_writable)(struct us_internal_ssl_socket_t *s)) {
    us_socket_context_on_writable(0, (struct us_socket_context_t *) context, (struct us_socket_t *(*)(struct us_socket_t *)) ssl_on_writable);
    context->on_writable = on_writable;
}

void us_internal_ssl_socket_context_on_timeout(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *(*on_timeout)(struct us_internal_ssl_socket_t *s)) {
    us_socket_context_on_timeout(0, (struct us_socket_context_t *) context, (struct us_socket_t *(*)(struct us_socket_t *)) on_timeout);
}

/* We do not really listen to passed FIN-handler, we entirely override it with our handler since SSL doesn't really have support for half-closed sockets */
void us_internal_ssl_socket_context_on_end(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *(*on_end)(struct us_internal_ssl_socket_t *)) {
    us_socket_context_on_end(0, (struct us_socket_context_t *) context, (struct us_socket_t *(*)(struct us_socket_t *)) ssl_on_end);
}

void us_internal_ssl_socket_context_on_connect_error(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *(*on_connect_error)(struct us_internal_ssl_socket_t *, int code)) {
    us_socket_context_on_connect_error(0, (struct us_socket_context_t *) context, (struct us_socket_t *(*)(struct us_socket_t *, int)) on_connect_error);
}

void *us_internal_ssl_socket_context_ext(struct us_internal_ssl_socket_context_t *context) {
    return context + 1;
}

/* Per socket functions */
void *us_internal_ssl_socket_get_native_handle(struct us_internal_ssl_socket_t *s) {
    return s->ssl;
}

int us_internal_ssl_socket_write(struct us_internal_ssl_socket_t *s, const char *data, int length, int msg_more) {
    if (us_socket_is_closed(0, &s->s) || us_internal_ssl_socket_is_shut_down(s)) {
        return 0;
    }

    struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);

    struct us_loop_t *loop = us_socket_context_loop(0, &context->sc);
    struct loop_ssl_data *loop_ssl_data = (struct loop_ssl_data *) loop->data.ssl_data;

    // it makes literally no sense to touch this here! it should start at 0 and ONLY be set and reset by the on_data function!
    // the way is is now, triggering a write from a read will essentially delete all input data!
    // what we need to do is to check if this ever is non-zero and print a warning



    loop_ssl_data->ssl_read_input_length = 0;


    loop_ssl_data->ssl_socket = &s->s;
    loop_ssl_data->msg_more = msg_more;
    loop_ssl_data->last_write_was_msg_more = 0;
    //printf("Calling SSL_write\n");
    int written = SSL_write(s->ssl, data, length);
    //printf("Returning from SSL_write\n");
    loop_ssl_data->msg_more = 0;

    if (loop_ssl_data->last_write_was_msg_more && !msg_more) {
        us_socket_flush(0, &s->s);
    }

    if (written > 0) {
        return written;
    } else {
        int err = SSL_get_error(s->ssl, written);
        if (err == SSL_ERROR_WANT_READ) {
            // here we need to trigger writable event next ssl_read!
            s->ssl_write_wants_read = 1;
        } else if (err == SSL_ERROR_SSL || err == SSL_ERROR_SYSCALL) {
            // these two errors may add to the error queue, which is per thread and must be cleared
            ERR_clear_error();

            // all errors here except for want write are critical and should not happen
        }

        return 0;
    }
}

void *us_internal_ssl_socket_ext(struct us_internal_ssl_socket_t *s) {
    return s + 1;
}

int us_internal_ssl_socket_is_shut_down(struct us_internal_ssl_socket_t *s) {
    return us_socket_is_shut_down(0, &s->s) || SSL_get_shutdown(s->ssl) & SSL_SENT_SHUTDOWN;
}

void us_internal_ssl_socket_shutdown(struct us_internal_ssl_socket_t *s) {
    if (!us_socket_is_closed(0, &s->s) && !us_internal_ssl_socket_is_shut_down(s)) {
        struct us_internal_ssl_socket_context_t *context = (struct us_internal_ssl_socket_context_t *) us_socket_context(0, &s->s);
        struct us_loop_t *loop = us_socket_context_loop(0, &context->sc);
        struct loop_ssl_data *loop_ssl_data = (struct loop_ssl_data *) loop->data.ssl_data;

        // also makes no sense to touch this here!
        // however the idea is that if THIS socket is not the same as ssl_socket then this data is not for me
        // but this is not correct as it is currently anyways, any data available should be properly reset
        loop_ssl_data->ssl_read_input_length = 0;


        // essentially we need two of these: one for CURRENT CALL and one for CURRENT SOCKET WITH DATA
        // if those match in the BIO function then you may read, if not then you may not read
        // we need ssl_read_socket to be set in on_data and checked in the BIO
        loop_ssl_data->ssl_socket = &s->s;


        loop_ssl_data->msg_more = 0;

        // sets SSL_SENT_SHUTDOWN no matter what (not actually true if error!)
        int ret = SSL_shutdown(s->ssl);
        if (ret == 0) {
            ret = SSL_shutdown(s->ssl);
        }

        if (ret < 0) {

            int err = SSL_get_error(s->ssl, ret);
            if (err == SSL_ERROR_SSL || err == SSL_ERROR_SYSCALL) {
                // clear
                ERR_clear_error();
            }

            // we get here if we are shutting down while still in init
            us_socket_shutdown(0, &s->s);
        }
    }
}

struct us_internal_ssl_socket_t *us_internal_ssl_socket_context_adopt_socket(struct us_internal_ssl_socket_context_t *context, struct us_internal_ssl_socket_t *s, int ext_size) {
    // todo: this is completely untested
    return (struct us_internal_ssl_socket_t *) us_socket_context_adopt_socket(0, &context->sc, &s->s, sizeof(struct us_internal_ssl_socket_t) - sizeof(struct us_socket_t) + ext_size);
}

#endif
