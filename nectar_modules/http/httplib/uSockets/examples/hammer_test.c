/* This example, or test, is a moron test where the library is being hammered in all the possible ways randomly over time */

#include <libusockets.h>
const int SSL = 1;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// todo: properly put all of these in various ext data so to test them!
int opened_connections, closed_connections, operations_done;
struct us_socket_context_t *http_context, *websocket_context;
struct us_listen_socket_t *listen_socket;

// put in loop ext data
void *long_buffer;
unsigned int long_length = 5 * 1024 * 1024;

// also make sure to have socket ext data
// and context ext data
// and loop ext data

const double pad_should_always_be = 14.652752;

struct http_socket {
    double pad_invariant;
    int is_http;
    double post_pad_invariant;
    char content[1024];
};

struct web_socket {
    double pad_invariant;
    int is_http;
    double post_pad_invariant;
    char content[128];
};

/* This checks the ext data state according to callbacks */
void assume_state(struct us_socket_t *s, int is_http) {
    struct http_socket *hs = (struct http_socket *) us_socket_ext(SSL, s);

    if (hs->pad_invariant != pad_should_always_be || hs->post_pad_invariant != pad_should_always_be) {
        printf("ERROR: Pad invariant is not correct!\n");
        free((void *) 1);
    }

    if (hs->is_http != is_http) {
        printf("ERROR: State is: %d should be: %d. Terminating now!\n", hs->is_http, is_http);
        free((void *) 1);
    }

    // try and cause havoc (different size)
    if (hs->is_http) {
        memset(hs->content, 0, 1024);
    } else {
        memset(hs->content, 0, 128);
    }
}

struct http_context {
    // link to the other context here
    char content[1];
};

// todo: it would be nice to randomly select socket instead of
// using the one responsible for the event
struct us_socket_t *perform_random_operation(struct us_socket_t *s) {
    switch (rand() % 5) {
        case 0: {
            // close
            return us_socket_close(SSL, s, 0, NULL);
        }
        case 1: {
            // adoption cannot happen if closed!
            if (!us_socket_is_closed(SSL, s)) {
                if (rand() % 2) {
                    s = us_socket_context_adopt_socket(SSL, websocket_context, s, sizeof(struct web_socket));
                    struct http_socket *hs = (struct http_socket *) us_socket_ext(SSL, s);
                    hs->is_http = 0;
                } else {
                    s = us_socket_context_adopt_socket(SSL, http_context, s, sizeof(struct http_socket));
                    struct http_socket *hs = (struct http_socket *) us_socket_ext(SSL, s);
                    hs->is_http = 1;
                }
            }

            return perform_random_operation(s);
        }
        case 2: {
            // write
            us_socket_write(SSL, s, (char *) long_buffer, rand() % long_length, 0);
        }
        break;
        case 3: {
            // shutdown
            us_socket_shutdown(SSL, s);
        }
        break;
        case 4: {
            // loop wakeup and timeout sweep
            us_socket_timeout(SSL, s, 1);
            us_wakeup_loop(us_socket_context_loop(SSL, us_socket_context(SSL, s)));
        }
        break;
    }
    return s;
}

void on_wakeup(struct us_loop_t *loop) {
    // note: we expose internal functions to trigger a timeout sweep to find bugs
    extern void us_internal_timer_sweep(struct us_loop_t *loop);
    us_internal_timer_sweep(loop);
}

// maybe use thse to count spurious wakeups?
// that is, if we get tons of pre/post over and over without any events
// that would point towards 100% cpu usage kind of bugs
void on_pre(struct us_loop_t *loop) {
    printf("PRE\n");

    // reset a boolean here
}

void on_post(struct us_loop_t *loop) {
    // check if we did perform_random_operation
}

struct us_socket_t *on_web_socket_writable(struct us_socket_t *s) {
    printf("on_web_socket_writable\n");
    assume_state(s, 0);

    return perform_random_operation(s);
}

struct us_socket_t *on_http_socket_writable(struct us_socket_t *s) {
    printf("on_http_socket_writable\n");
    assume_state(s, 1);

    return perform_random_operation(s);
}

struct us_socket_t *on_web_socket_close(struct us_socket_t *s, int code, void *reason) {
    assume_state(s, 0);

    closed_connections++;
    printf("Opened: %d\nClosed: %d\n\n", opened_connections, closed_connections);

    if (closed_connections == 10000) {
        us_listen_socket_close(SSL, listen_socket);
    } else {
        return perform_random_operation(s);
    }
    return s;
}

struct us_socket_t *on_http_socket_close(struct us_socket_t *s, int code, void *reason) {
    assume_state(s, 1);

    closed_connections++;
    printf("Opened: %d\nClosed: %d\n\n", opened_connections, closed_connections);

    if (closed_connections == 10000) {
        us_listen_socket_close(SSL, listen_socket);
    } else {
        return perform_random_operation(s);
    }
    return s;
}

struct us_socket_t *on_web_socket_end(struct us_socket_t *s) {
    assume_state(s, 0);

    // we need to close on shutdown
    s = us_socket_close(SSL, s, 0, NULL);
    return perform_random_operation(s);
}

struct us_socket_t *on_http_socket_end(struct us_socket_t *s) {
    assume_state(s, 1);

    // we need to close on shutdown
    s = us_socket_close(SSL, s, 0, NULL);
    return perform_random_operation(s);
}

struct us_socket_t *on_web_socket_data(struct us_socket_t *s, char *data, int length) {
    assume_state(s, 0);

    if (length == 0) {
        printf("ERROR: Got data event with no data\n");
        exit(-1);
    }

    //printf("Fick data: <%.*s>\n", length, data);
    return perform_random_operation(s);
}

struct us_socket_t *on_http_socket_data(struct us_socket_t *s, char *data, int length) {
    assume_state(s, 1);

    if (length == 0) {
        printf("ERROR: Got data event with no data\n");
        exit(-1);
    }

    //printf("Fick data: <%.*s>\n", length, data);
    return perform_random_operation(s);
}

struct us_socket_t *on_web_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {
    // fail here, this can never happen!
    printf("ERROR: on_web_socket_open called!\n");
    exit(-2);
}

struct us_socket_t *on_http_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {
    struct http_socket *hs = (struct http_socket *) us_socket_ext(SSL, s);
    hs->is_http = 1;
    hs->pad_invariant = pad_should_always_be;
    hs->post_pad_invariant = pad_should_always_be;

    assume_state(s, 1);

    opened_connections++;
    printf("Opened: %d\nClosed: %d\n\n", opened_connections, closed_connections);

    if (is_client && opened_connections <= 10000 - 2) {
        us_socket_context_connect(SSL, http_context, "127.0.0.1", 3000, NULL, 0, sizeof(struct http_socket));
    }

    return perform_random_operation(s);
}

struct us_socket_t *on_web_socket_timeout(struct us_socket_t *s) {
    assume_state(s, 0);

    return perform_random_operation(s);
}

struct us_socket_t *on_http_socket_timeout(struct us_socket_t *s) {
    assume_state(s, 1);

    return perform_random_operation(s);
}

int main() {
    srand(time(0));
    long_buffer = calloc(long_length, 1);

    struct us_loop_t *loop = us_create_loop(0, on_wakeup, on_pre, on_post, 0);

    // us_loop_on_wakeup()
    // us_loop_on_pre()
    // us_loop_on_post()
    // us_loop_on_poll()
    // us_loop_on_timer()


    // these are ignored for non-SSL
    struct us_socket_context_options_t options = {};
    options.key_file_name = "/home/alexhultman/uWebSockets.js/misc/key.pem";
    options.cert_file_name = "/home/alexhultman/uWebSockets.js/misc/cert.pem";
    options.passphrase = "1234";

    http_context = us_create_socket_context(SSL, loop, sizeof(struct http_context), options);


    us_socket_context_on_open(SSL, http_context, on_http_socket_open);
    us_socket_context_on_data(SSL, http_context, on_http_socket_data);
    us_socket_context_on_writable(SSL, http_context, on_http_socket_writable);
    us_socket_context_on_close(SSL, http_context, on_http_socket_close);
    us_socket_context_on_timeout(SSL, http_context, on_http_socket_timeout);
    us_socket_context_on_end(SSL, http_context, on_http_socket_end);

    websocket_context = us_create_child_socket_context(SSL, http_context, sizeof(struct http_context));

    us_socket_context_on_open(SSL, websocket_context, on_web_socket_open);
    us_socket_context_on_data(SSL, websocket_context, on_web_socket_data);
    us_socket_context_on_writable(SSL, websocket_context, on_web_socket_writable);
    us_socket_context_on_close(SSL, websocket_context, on_web_socket_close);
    us_socket_context_on_timeout(SSL, websocket_context, on_web_socket_timeout);
    us_socket_context_on_end(SSL, websocket_context, on_web_socket_end);

    listen_socket = us_socket_context_listen(SSL, http_context, "127.0.0.1", 3000, 0, sizeof(struct http_socket));

    if (listen_socket) {
        printf("Running hammer test\n");
        us_socket_context_connect(SSL, http_context, "127.0.0.1", 3000, NULL, 0, sizeof(struct http_socket));
        us_loop_run(loop);
    } else {
        printf("Cannot listen to port 3000!\n");
    }

    us_socket_context_free(SSL, websocket_context);
    us_socket_context_free(SSL, http_context);
    us_loop_free(loop);
    free(long_buffer);
    printf("Done, shutting down now\n");
}
