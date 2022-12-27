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

#include "libusockets.h"
#include "internal/internal.h"
#include <stdlib.h>
#include <string.h>

int default_ignore_data_handler(struct us_socket_t *s) {
    return 0;
}

/* Shared with SSL */

unsigned short us_socket_context_timestamp(int ssl, struct us_socket_context_t *context) {
    return context->timestamp;
}

void us_listen_socket_close(int ssl, struct us_listen_socket_t *ls) {
    /* us_listen_socket_t extends us_socket_t so we close in similar ways */
    if (!us_socket_is_closed(0, &ls->s)) {
        us_internal_socket_context_unlink(ls->s.context, &ls->s);
        us_poll_stop((struct us_poll_t *) &ls->s, ls->s.context->loop);
        bsd_close_socket(us_poll_fd((struct us_poll_t *) &ls->s));

        /* Link this socket to the close-list and let it be deleted after this iteration */
        ls->s.next = ls->s.context->loop->data.closed_head;
        ls->s.context->loop->data.closed_head = &ls->s;

        /* Any socket with prev = context is marked as closed */
        ls->s.prev = (struct us_socket_t *) ls->s.context;
    }

    /* We cannot immediately free a listen socket as we can be inside an accept loop */
}

void us_internal_socket_context_unlink(struct us_socket_context_t *context, struct us_socket_t *s) {
    /* We have to properly update the iterator used to sweep sockets for timeouts */
    if (s == context->iterator) {
        context->iterator = s->next;
    }

    if (s->prev == s->next) {
        context->head = 0;
    } else {
        if (s->prev) {
            s->prev->next = s->next;
        } else {
            context->head = s->next;
        }
        if (s->next) {
            s->next->prev = s->prev;
        }
    }
}

/* We always add in the top, so we don't modify any s.next */
void us_internal_socket_context_link(struct us_socket_context_t *context, struct us_socket_t *s) {
    s->context = context;
    s->timeout = 0;
    s->next = context->head;
    s->prev = 0;
    if (context->head) {
        context->head->prev = s;
    }
    context->head = s;
}

struct us_loop_t *us_socket_context_loop(int ssl, struct us_socket_context_t *context) {
    return context->loop;
}

/* Not shared with SSL */

/* Add SNI context */
void us_socket_context_add_server_name(int ssl, struct us_socket_context_t *context, const char *hostname_pattern, struct us_socket_context_options_t options) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_add_server_name((struct us_internal_ssl_socket_context_t *) context, hostname_pattern, options);
    }
#endif
}

/* Remove SNI context */
void us_socket_context_remove_server_name(int ssl, struct us_socket_context_t *context, const char *hostname_pattern) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_remove_server_name((struct us_internal_ssl_socket_context_t *) context, hostname_pattern);
    }
#endif
}

/* I don't like this one - maybe rename it to on_missing_server_name? */

/* Called when SNI matching fails - not if a match could be made.
 * You may modify the context by adding/removing names in this callback.
 * If the correct name is added immediately in the callback, it will be used */
void us_socket_context_on_server_name(int ssl, struct us_socket_context_t *context, void (*cb)(struct us_socket_context_t *, const char *hostname)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_server_name((struct us_internal_ssl_socket_context_t *) context, (void (*)(struct us_internal_ssl_socket_context_t *, const char *hostname)) cb);
    }
#endif
}

/* Todo: get native context from SNI pattern */

void *us_socket_context_get_native_handle(int ssl, struct us_socket_context_t *context) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return us_internal_ssl_socket_context_get_native_handle((struct us_internal_ssl_socket_context_t *) context);
    }
#endif

    /* There is no native handle for a non-SSL socket context */
    return 0;
}

/* Options is currently only applicable for SSL - this will change with time (prefer_low_memory is one example) */
struct us_socket_context_t *us_create_socket_context(int ssl, struct us_loop_t *loop, int context_ext_size, struct us_socket_context_options_t options) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        /* This function will call us, again, with SSL = false and a bigger ext_size */
        return (struct us_socket_context_t *) us_internal_create_ssl_socket_context(loop, context_ext_size, options);
    }
#endif

    /* This path is taken once either way - always BEFORE whatever SSL may do LATER.
     * context_ext_size will however be modified larger in case of SSL, to hold SSL extensions */

    struct us_socket_context_t *context = malloc(sizeof(struct us_socket_context_t) + context_ext_size);
    context->loop = loop;
    context->head = 0;
    context->iterator = 0;
    context->next = 0;
    context->ignore_data = default_ignore_data_handler;

    /* Begin at 0 */
    context->timestamp = 0;

    us_internal_loop_link(loop, context);

    /* If we are called from within SSL code, SSL code will make further changes to us */
    return context;
}

void us_socket_context_free(int ssl, struct us_socket_context_t *context) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        /* This function will call us again with SSL=false */
        us_internal_ssl_socket_context_free((struct us_internal_ssl_socket_context_t *) context);
        return;
    }
#endif

    /* This path is taken once either way - always AFTER whatever SSL may do BEFORE.
     * This is the opposite order compared to when creating the context - SSL code is cleaning up before non-SSL */

    us_internal_loop_unlink(context->loop, context);
    free(context);
}

struct us_listen_socket_t *us_socket_context_listen(int ssl, struct us_socket_context_t *context, const char *host, int port, int options, int socket_ext_size) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return us_internal_ssl_socket_context_listen((struct us_internal_ssl_socket_context_t *) context, host, port, options, socket_ext_size);
    }
#endif

    LIBUS_SOCKET_DESCRIPTOR listen_socket_fd = bsd_create_listen_socket(host, port, options);

    if (listen_socket_fd == LIBUS_SOCKET_ERROR) {
        return 0;
    }

    struct us_poll_t *p = us_create_poll(context->loop, 0, sizeof(struct us_listen_socket_t));
    us_poll_init(p, listen_socket_fd, POLL_TYPE_SEMI_SOCKET);
    us_poll_start(p, context->loop, LIBUS_SOCKET_READABLE);

    struct us_listen_socket_t *ls = (struct us_listen_socket_t *) p;

    ls->s.context = context;
    ls->s.timeout = 0;
    ls->s.next = 0;
    us_internal_socket_context_link(context, &ls->s);

    ls->socket_ext_size = socket_ext_size;

    return ls;
}

struct us_socket_t *us_socket_context_connect(int ssl, struct us_socket_context_t *context, const char *host, int port, const char *source_host, int options, int socket_ext_size) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return (struct us_socket_t *) us_internal_ssl_socket_context_connect((struct us_internal_ssl_socket_context_t *) context, host, port, source_host, options, socket_ext_size);
    }
#endif

    LIBUS_SOCKET_DESCRIPTOR connect_socket_fd = bsd_create_connect_socket(host, port, source_host, options);
    if (connect_socket_fd == LIBUS_SOCKET_ERROR) {
        return 0;
    }

    /* Connect sockets are semi-sockets just like listen sockets */
    struct us_poll_t *p = us_create_poll(context->loop, 0, sizeof(struct us_socket_t) + socket_ext_size);
    us_poll_init(p, connect_socket_fd, POLL_TYPE_SEMI_SOCKET);
    us_poll_start(p, context->loop, LIBUS_SOCKET_WRITABLE);

    struct us_socket_t *connect_socket = (struct us_socket_t *) p;

    /* Link it into context so that timeout fires properly */
    connect_socket->context = context;
    us_internal_socket_context_link(context, connect_socket);

    return connect_socket;
}

struct us_socket_context_t *us_create_child_socket_context(int ssl, struct us_socket_context_t *context, int context_ext_size) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return (struct us_socket_context_t *) us_internal_create_child_ssl_socket_context((struct us_internal_ssl_socket_context_t *) context, context_ext_size);
    }
#endif

    /* For TCP we simply create a new context as nothing is shared */
    struct us_socket_context_options_t options = {0};
    return us_create_socket_context(ssl, context->loop, context_ext_size, options);
}

/* Note: This will set timeout to 0 */
struct us_socket_t *us_socket_context_adopt_socket(int ssl, struct us_socket_context_t *context, struct us_socket_t *s, int ext_size) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return (struct us_socket_t *) us_internal_ssl_socket_context_adopt_socket((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t *) s, ext_size);
    }
#endif

    /* Cannot adopt a closed socket */
    if (us_socket_is_closed(ssl, s)) {
        return s;
    }

    /* This properly updates the iterator if in on_timeout */
    us_internal_socket_context_unlink(s->context, s);

    struct us_socket_t *new_s = (struct us_socket_t *) us_poll_resize(&s->p, s->context->loop, sizeof(struct us_socket_t) + ext_size);

    us_internal_socket_context_link(context, new_s);

    return new_s;
}

void us_socket_context_on_open(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_open)(struct us_socket_t *s, int is_client, char *ip, int ip_length)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_open((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t * (*)(struct us_internal_ssl_socket_t *, int,  char *, int)) on_open);
        return;
    }
#endif

    context->on_open = on_open;
}

void us_socket_context_on_close(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_close)(struct us_socket_t *s, int code, void *reason)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_close((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t * (*)(struct us_internal_ssl_socket_t *, int code, void *reason)) on_close);
        return;
    }
#endif

    context->on_close = on_close;
}

void us_socket_context_on_data(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_data)(struct us_socket_t *s, char *data, int length)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_data((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t * (*)(struct us_internal_ssl_socket_t *, char *, int)) on_data);
        return;
    }
#endif

    context->on_data = on_data;
}

void us_socket_context_on_writable(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_writable)(struct us_socket_t *s)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_writable((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t * (*)(struct us_internal_ssl_socket_t *)) on_writable);
        return;
    }
#endif

    context->on_writable = on_writable;
}

void us_socket_context_on_timeout(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_timeout)(struct us_socket_t *)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_timeout((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t * (*)(struct us_internal_ssl_socket_t *)) on_timeout);
        return;
    }
#endif

    context->on_socket_timeout = on_timeout;
}

void us_socket_context_on_end(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_end)(struct us_socket_t *)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_end((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t * (*)(struct us_internal_ssl_socket_t *)) on_end);
        return;
    }
#endif

    context->on_end = on_end;
}

void us_socket_context_on_connect_error(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_connect_error)(struct us_socket_t *s, int code)) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_context_on_connect_error((struct us_internal_ssl_socket_context_t *) context, (struct us_internal_ssl_socket_t * (*)(struct us_internal_ssl_socket_t *, int)) on_connect_error);
        return;
    }
#endif
    
    context->on_connect_error = on_connect_error;
}

void *us_socket_context_ext(int ssl, struct us_socket_context_t *context) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return us_internal_ssl_socket_context_ext((struct us_internal_ssl_socket_context_t *) context);
    }
#endif

    return context + 1;
}
