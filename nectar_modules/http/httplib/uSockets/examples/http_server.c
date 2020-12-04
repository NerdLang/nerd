/* This is a barebone keep-alive HTTP server */
#include <libusockets.h>
/* Compiling with LIBUS_NO_SSL will ignore SSL */
const int SSL = 1;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct http_socket {
	/* How far we have streamed our response */
	int offset;
};

struct http_context {
	/* The shared response */
	char *response;
	int length;
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
	struct http_context *http_context = (struct http_context *) us_socket_context_ext(SSL, us_socket_context(SSL, s));

	/* Stream whatever is remaining of the response */
	http_socket->offset += us_socket_write(SSL, s, http_context->response + http_socket->offset, http_context->length - http_socket->offset, 0);

	return s;
}

struct us_socket_t *on_http_socket_close(struct us_socket_t *s, int code, void *reason) {
	printf("Client disconnected\n");

	return s;
}

struct us_socket_t *on_http_socket_end(struct us_socket_t *s) {
	/* HTTP does not support half-closed sockets */
	us_socket_shutdown(SSL, s);
	return us_socket_close(SSL, s, 0, NULL);
}

struct us_socket_t *on_http_socket_data(struct us_socket_t *s, char *data, int length) {
	/* Get socket extension and the socket's context's extension */
	struct http_socket *http_socket = (struct http_socket *) us_socket_ext(SSL, s);
	struct http_context *http_context = (struct http_context *) us_socket_context_ext(SSL, us_socket_context(SSL, s));

	/* We treat all data events as a request */
	http_socket->offset = us_socket_write(SSL, s, http_context->response, http_context->length, 0);

	/* Reset idle timer */
	us_socket_timeout(SSL, s, 30);

	return s;
}

struct us_socket_t *on_http_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {
	struct http_socket *http_socket = (struct http_socket *) us_socket_ext(SSL, s);

	/* Reset offset */
	http_socket->offset = 0;

	/* Timeout idle HTTP connections */
	us_socket_timeout(SSL, s, 30);

	printf("Client connected\n");

	return s;
}

struct us_socket_t *on_http_socket_timeout(struct us_socket_t *s) {
	/* Close idle HTTP sockets */
	return us_socket_close(SSL, s, 0, NULL);
}

int main() {
	/* Create the event loop */
	struct us_loop_t *loop = us_create_loop(0, on_wakeup, on_pre, on_post, 0);

	/* Create a socket context for HTTP */
	struct us_socket_context_options_t options = {};
	options.key_file_name = "/home/alexhultman/uWebSockets.js/misc/key.pem";
	options.cert_file_name = "/home/alexhultman/uWebSockets.js/misc/cert.pem";
	options.passphrase = "1234";

	struct us_socket_context_t *http_context = us_create_socket_context(SSL, loop, sizeof(struct http_context), options);


	/* Generate the shared response */
	const char body[] = "<html><body><h1>Why hello there!</h1></body></html>";

	struct http_context *http_context_ext = (struct http_context *) us_socket_context_ext(SSL, http_context);
	http_context_ext->response = (char *) malloc(128 + sizeof(body) - 1);
	http_context_ext->length = snprintf(http_context_ext->response, 128 + sizeof(body) - 1, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n%s", sizeof(body) - 1, body);

	/* Set up event handlers */
	us_socket_context_on_open(SSL, http_context, on_http_socket_open);
	us_socket_context_on_data(SSL, http_context, on_http_socket_data);
	us_socket_context_on_writable(SSL, http_context, on_http_socket_writable);
	us_socket_context_on_close(SSL, http_context, on_http_socket_close);
	us_socket_context_on_timeout(SSL, http_context, on_http_socket_timeout);
	us_socket_context_on_end(SSL, http_context, on_http_socket_end);

	/* Start serving HTTP connections */
	struct us_listen_socket_t *listen_socket = us_socket_context_listen(SSL, http_context, 0, 3000, 0, sizeof(struct http_socket));

	if (listen_socket) {
		printf("Listening on port 3000...\n");
		us_loop_run(loop);
	} else {
		printf("Failed to listen!\n");
	}
}
