/* This example, or test, is a moron test where the library is being hammered in all the possible ways randomly over time */

#include <libusockets.h>
const int SSL = 1;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int port;
int opened_connections, closed_connections, operations_done;
struct us_socket_context_t *server_context, *client_context;
struct us_listen_socket_t *listen_socket;

char client_msg[] = "Hello from client";
char server_msg[] = "Hello from server";

// also make sure to have socket ext data
// and context ext data
// and loop ext data

bool client_received_data;
bool server_received_data;

struct socket_context {
    char *backpressure;
    int length;
};

void on_wakeup(struct us_loop_t *loop) {
    // note: we expose internal functions to trigger a timeout sweep to find bugs
    extern void us_internal_timer_sweep(struct us_loop_t * loop);
    us_internal_timer_sweep(loop);
}

// maybe use thse to count spurious wakeups?
// that is, if we get tons of pre/post over and over without any events
// that would point towards 100% cpu usage kind of bugs
void on_pre(struct us_loop_t *loop) {
    // printf("PRE\n");
}

void on_post(struct us_loop_t *loop) {
    // check if we did perform_random_operation
}

int write_buffered(int SSL, struct us_socket_t *s, const char *data, int length) {

    struct socket_context *ctx = (struct socket_context *)us_socket_ext(SSL, s);

    int written = us_socket_write(SSL, s, data, length, 0);
    if (written != length) {
        char *new_buffer = (char *)malloc(ctx->length + length - written);
        memcpy(new_buffer, ctx->backpressure, ctx->length);
        memcpy(new_buffer + ctx->length, data + written, length - written);
        free(ctx->backpressure);
        ctx->backpressure = new_buffer;
        ctx->length += length - written;
    }
    return written;
}

void write_backpressure(int SSL, struct us_socket_t *s) {

    struct socket_context *ctx = (struct socket_context *)us_socket_ext(SSL, s);

    /* Continue writing out our backpressure */
    int written = us_socket_write(SSL, s, ctx->backpressure, ctx->length, 0);
    if (written != ctx->length) {
        char *new_buffer = (char *)malloc(ctx->length - written);
        memcpy(new_buffer, ctx->backpressure, ctx->length - written);
        free(ctx->backpressure);
        ctx->backpressure = new_buffer;
        ctx->length -= written;
    } else {
        free(ctx->backpressure);
        ctx->length = 0;
    }
}

struct us_socket_t *on_server_socket_writable(struct us_socket_t *s) {
    printf("on_server_socket_writable\n");

    write_backpressure(SSL, s);

    /* Peer is not boring */
    us_socket_timeout(SSL, s, 30);

    return s;
}

struct us_socket_t *on_client_socket_writable(struct us_socket_t *s) {
    printf("on_client_socket_writable\n");

    write_backpressure(SSL, s);

    /* Peer is not boring */
    us_socket_timeout(SSL, s, 30);

    return s;
}

struct us_socket_t *on_server_socket_close(struct us_socket_t *s, int code, void *reason) {
    printf("on_server_socket_close\n");

    us_listen_socket_close(SSL, listen_socket);

    return s;
}

struct us_socket_t *on_client_socket_close(struct us_socket_t *s, int code, void *reason) {

    printf("on_client_socket_close\n");

    return s;
}

struct us_socket_t *on_server_socket_end(struct us_socket_t *s) {

    return us_socket_close(SSL, s, 0, NULL);
}

struct us_socket_t *on_client_socket_end(struct us_socket_t *s) {

    return us_socket_close(SSL, s, 0, NULL);
}

struct us_socket_t *on_server_socket_data(struct us_socket_t *s, char *data, int length) {

    if (length == 0) {
        printf("ERROR: Got data event with no data\n");
        exit(-1);
    }
    /* Print the data we received */
    printf("on_server_socket_data: received '%.*s'\n", length, data);

    server_received_data = true;

    write_buffered(SSL, s, server_msg, sizeof(server_msg));

    return s;
}

struct us_socket_t *on_client_socket_data(struct us_socket_t *s, char *data, int length) {

    if (length == 0) {
        printf("ERROR: Got data event with no data\n");
        exit(-1);
    }
    /* Print the data we received */
    printf("on_client_socket_data: received '%.*s'\n", length, data);

    client_received_data = true;

    return us_socket_close(SSL, s, 0, NULL);
}

struct us_socket_t *on_server_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {

    printf("on_server_socket_open\n");
    struct socket_context *ctx = (struct socket_context *)us_socket_ext(SSL, s);

    ctx->backpressure = 0;
    ctx->length = 0;

    /* Start a timeout to close the socket if boring */
    us_socket_timeout(SSL, s, 30);

    printf("Client connected\n");

    return s;
}

struct us_socket_t *on_client_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {

    printf("on_client_socket_open\n");

    struct socket_context *ctx = (struct socket_context *)us_socket_ext(SSL, s);

    ctx->backpressure = 0;
    ctx->length = 0;

    write_buffered(SSL, s, client_msg, sizeof(client_msg));

    return s;
}

struct us_socket_t *on_client_socket_timeout(struct us_socket_t *s) {
    return s;
}

struct us_socket_t *on_server_socket_timeout(struct us_socket_t *s) {
    return s;
}

int expect_peer_verify(const char *test_name, bool expect_data_exchanged,
                     struct us_socket_context_options_t server_options,
                     struct us_socket_context_options_t client_options) {


    printf("----------------------------------------\n"
           "[[ %s ]]\n"
           "  server_key: %s\n"
           "  server_crt: %s\n"
           "  server_ca: %s\n"
           "  client_crt: %s\n"
           "  client_key: %s\n"
           "  client_ca: %s\n\n",
           test_name,
           server_options.key_file_name,
           server_options.cert_file_name,
           server_options.ca_file_name,
           client_options.key_file_name,
           client_options.cert_file_name,
           client_options.ca_file_name);

    srand(time(0));
    server_received_data = false;
    client_received_data = false;

    struct us_loop_t *loop = us_create_loop(0, on_wakeup, on_pre, on_post, 0);

    server_context = us_create_socket_context(SSL, loop, sizeof(struct socket_context), server_options);

    us_socket_context_on_open(SSL, server_context, on_server_socket_open);
    us_socket_context_on_data(SSL, server_context, on_server_socket_data);
    us_socket_context_on_writable(SSL, server_context, on_server_socket_writable);
    us_socket_context_on_close(SSL, server_context, on_server_socket_close);
    us_socket_context_on_timeout(SSL, server_context, on_server_socket_timeout);
    us_socket_context_on_end(SSL, server_context, on_server_socket_end);

    port = 3000;
    listen_socket = us_socket_context_listen(SSL, server_context, "127.0.0.1", port, 0, sizeof(struct socket_context));
    while (!listen_socket) {
        listen_socket = us_socket_context_listen(SSL, server_context, "127.0.0.1", ++port, 0, sizeof(struct socket_context));
    }
    printf("Server listening on 127.0.0.1:%d\n", port);

    client_context = us_create_socket_context(SSL, loop, sizeof(struct socket_context), client_options);
    us_socket_context_on_open(SSL, client_context, on_client_socket_open);
    us_socket_context_on_data(SSL, client_context, on_client_socket_data);
    us_socket_context_on_writable(SSL, client_context, on_client_socket_writable);
    us_socket_context_on_close(SSL, client_context, on_client_socket_close);
    us_socket_context_on_timeout(SSL, client_context, on_client_socket_timeout);
    us_socket_context_on_end(SSL, client_context, on_client_socket_end);

    us_socket_context_connect(SSL, client_context, "127.0.0.1", port, NULL, 0, sizeof(struct socket_context));
    us_loop_run(loop);

    us_socket_context_free(SSL, server_context);
    us_socket_context_free(SSL, client_context);
    us_loop_free(loop);

    bool data_exchanged = server_received_data && client_received_data;
    if (!!expect_data_exchanged != !!data_exchanged) {

        fprintf(stderr, "\n~ ERROR: expected data_echanged == %s, got %s\n\n",
                (expect_data_exchanged ? "true" : "false"),
                (data_exchanged ? "true" : "false"));
        exit(1);
    }

    printf("[[ OK ]]\n\n");
    return 0;
}

int main() {

    expect_peer_verify("trusted client ca", true,
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/valid_server_key.pem",
            .cert_file_name = ".certs/valid_server_crt.pem",
            .ca_file_name = ".certs/valid_ca_crt.pem"
        },
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/valid_client_key.pem",
            .cert_file_name = ".certs/valid_client_crt.pem",
            .ca_file_name = ".certs/valid_ca_crt.pem"
        });


    expect_peer_verify("untrusted client ca", false,
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/valid_server_key.pem",
            .cert_file_name = ".certs/valid_server_crt.pem",
            .ca_file_name = ".certs/valid_ca_crt.pem"
        },
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/invalid_client_key.pem",
            .cert_file_name = ".certs/invalid_client_crt.pem",
            .ca_file_name = ".certs/valid_ca_crt.pem"
        });

    expect_peer_verify("trusted selfsigned client", true,
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/valid_server_key.pem",
            .cert_file_name = ".certs/valid_server_crt.pem",
            .ca_file_name = ".certs/selfsigned_client_crt.pem"
        },
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/selfsigned_client_key.pem",
            .cert_file_name = ".certs/selfsigned_client_crt.pem",
            .ca_file_name = ".certs/valid_ca_crt.pem"
        });

    expect_peer_verify("untrusted selfsigned client", false,
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/valid_server_key.pem",
            .cert_file_name = ".certs/valid_server_crt.pem",
            .ca_file_name = ".certs/valid_ca_crt.pem"
        },
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/selfsigned_client_key.pem",
            .cert_file_name = ".certs/selfsigned_client_crt.pem",
            .ca_file_name = ".certs/valid_ca_crt.pem"
        });

    expect_peer_verify("peer verify disabled", true,
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/valid_server_key.pem",
            .cert_file_name = ".certs/valid_server_crt.pem"
        },
        (struct us_socket_context_options_t){
            .key_file_name = ".certs/valid_client_key.pem",
            .cert_file_name = ".certs/valid_client_crt.pem"
        });

}
