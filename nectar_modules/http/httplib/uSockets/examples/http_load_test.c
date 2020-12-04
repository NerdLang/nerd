/* This is a simple yet efficient HTTP server benchmark */
#include <libusockets.h>
/* If compiled with SSL support, enable it */
const int SSL = 1;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char request[] = "GET / HTTP/1.1\r\n\r\n";
char *host;
int port;
int connections;

int responses;

struct http_socket {
    /* How far we have streamed our request */
    int offset;
};

/* We don't need any of these */
void on_wakeup(struct us_loop_t *loop) {

}

void on_pre(struct us_loop_t *loop) {

}

/* This is not HTTP POST, it is merely an event emitted post loop iteration */
void on_post(struct us_loop_t *loop) {

}

struct us_socket_t *on_http_socket_writable(struct us_socket_t *s) {
    struct http_socket *http_socket = (struct http_socket *) us_socket_ext(SSL, s);

    /* Stream whatever is remaining of the request */
    http_socket->offset += us_socket_write(SSL, s, request + http_socket->offset, (sizeof(request) - 1) - http_socket->offset, 0);

    return s;
}

struct us_socket_t *on_http_socket_close(struct us_socket_t *s, int code, void *reason) {
	return s;
}

struct us_socket_t *on_http_socket_end(struct us_socket_t *s) {
    return us_socket_close(SSL, s, 0, NULL);
}

struct us_socket_t *on_http_socket_data(struct us_socket_t *s, char *data, int length) {
    /* Get socket extension and the socket's context's extension */
    struct http_socket *http_socket = (struct http_socket *) us_socket_ext(SSL, s);

    /* We treat all data events as a response */
    http_socket->offset = us_socket_write(SSL, s, request, sizeof(request) - 1, 0);

    /* */
    responses++;

    return s;
}

struct us_socket_t *on_http_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {
    struct http_socket *http_socket = (struct http_socket *) us_socket_ext(SSL, s);

    /* Reset offset */
    http_socket->offset = 0;

    /* Send a request */
    us_socket_write(SSL, s, request, sizeof(request) - 1, 0);

    if (--connections) {
        us_socket_context_connect(SSL, us_socket_context(SSL, s), host, port, NULL, 0, sizeof(struct http_socket));
    } else {
        printf("Running benchmark now...\n");

        us_socket_timeout(SSL, s, LIBUS_TIMEOUT_GRANULARITY);
    }

    return s;
}

struct us_socket_t *on_http_socket_timeout(struct us_socket_t *s) {
    /* Print current statistics */
    printf("Req/sec: %f\n", ((float)responses) / LIBUS_TIMEOUT_GRANULARITY);

    responses = 0;
    us_socket_timeout(SSL, s, LIBUS_TIMEOUT_GRANULARITY);

    return s;
}

int main(int argc, char **argv) {

    /* Parse host and port */
    if (argc != 4) {
        printf("Usage: connections host port\n");
        return 0;
    }

    port = atoi(argv[3]);
    host = malloc(strlen(argv[2]) + 1);
    memcpy(host, argv[2], strlen(argv[2]) + 1);
    connections = atoi(argv[1]);

    /* Create the event loop */
    struct us_loop_t *loop = us_create_loop(0, on_wakeup, on_pre, on_post, 0);

    /* Create a socket context for HTTP */
    struct us_socket_context_options_t options = {};
    options.key_file_name = "/home/alexhultman/uWebSockets.js/misc/key.pem";
    options.cert_file_name = "/home/alexhultman/uWebSockets.js/misc/cert.pem";
    options.passphrase = "1234";
    struct us_socket_context_t *http_context = us_create_socket_context(SSL, loop, 0, options);

    /* Set up event handlers */
    us_socket_context_on_open(SSL, http_context, on_http_socket_open);
    us_socket_context_on_data(SSL, http_context, on_http_socket_data);
    us_socket_context_on_writable(SSL, http_context, on_http_socket_writable);
    us_socket_context_on_close(SSL, http_context, on_http_socket_close);
    us_socket_context_on_timeout(SSL, http_context, on_http_socket_timeout);
    us_socket_context_on_end(SSL, http_context, on_http_socket_end);

    /* Start making HTTP connections */
    us_socket_context_connect(SSL, http_context, host, port, NULL, 0, sizeof(struct http_socket));

    us_loop_run(loop);
}
