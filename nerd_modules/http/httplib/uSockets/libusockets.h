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

#ifndef LIBUSOCKETS_H
#define LIBUSOCKETS_H

/* 512kb shared receive buffer */
#define LIBUS_RECV_BUFFER_LENGTH 524288
/* A timeout granularity of 4 seconds means give or take 4 seconds from set timeout */
#define LIBUS_TIMEOUT_GRANULARITY 4
/* 32 byte padding of receive buffer ends */
#define LIBUS_RECV_BUFFER_PADDING 32
/* Guaranteed alignment of extension memory */
#define LIBUS_EXT_ALIGNMENT 16

/* Define what a socket descriptor is based on platform */
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <winsock2.h>
#define LIBUS_SOCKET_DESCRIPTOR SOCKET
#define WIN32_EXPORT __declspec(dllexport)
#else
#define LIBUS_SOCKET_DESCRIPTOR int
#define WIN32_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum {
    /* No meaning, default listen option */
    LIBUS_LISTEN_DEFAULT,
    /* We exclusively own this port, do not share it */
    LIBUS_LISTEN_EXCLUSIVE_PORT
};

/* Library types publicly available */
struct us_socket_t;
struct us_timer_t;
struct us_socket_context_t;
struct us_loop_t;
struct us_poll_t;

/* Public interfaces for timers */

/* Create a new high precision, low performance timer. May fail and return null */
WIN32_EXPORT struct us_timer_t *us_create_timer(struct us_loop_t *loop, int fallthrough, unsigned int ext_size);

/* Returns user data extension for this timer */
WIN32_EXPORT void *us_timer_ext(struct us_timer_t *timer);

/* */
WIN32_EXPORT void us_timer_close(struct us_timer_t *timer);

/* Arm a timer with a delay from now and eventually a repeat delay.
 * Specify 0 as repeat delay to disable repeating. Specify both 0 to disarm. */
WIN32_EXPORT void us_timer_set(struct us_timer_t *timer, void (*cb)(struct us_timer_t *t), int ms, int repeat_ms);

/* Returns the loop for this timer */
WIN32_EXPORT struct us_loop_t *us_timer_loop(struct us_timer_t *t);

/* Public interfaces for contexts */

struct us_socket_context_options_t {
    const char *key_file_name;
    const char *cert_file_name;
    const char *passphrase;
    const char *dh_params_file_name;
    const char *ca_file_name;
    int ssl_prefer_low_memory_usage; /* Todo: rename to prefer_low_memory_usage and apply for TCP as well */
};

/* Return 15-bit timestamp for this context */
WIN32_EXPORT unsigned short us_socket_context_timestamp(int ssl, struct us_socket_context_t *context);

/* Adds SNI domain and cert in asn1 format */
WIN32_EXPORT void us_socket_context_add_server_name(int ssl, struct us_socket_context_t *context, const char *hostname_pattern, struct us_socket_context_options_t options);
WIN32_EXPORT void us_socket_context_remove_server_name(int ssl, struct us_socket_context_t *context, const char *hostname_pattern);
WIN32_EXPORT void us_socket_context_on_server_name(int ssl, struct us_socket_context_t *context, void (*cb)(struct us_socket_context_t *, const char *hostname));

/* Returns the underlying SSL native handle, such as SSL_CTX or nullptr */
WIN32_EXPORT void *us_socket_context_get_native_handle(int ssl, struct us_socket_context_t *context);

/* A socket context holds shared callbacks and user data extension for associated sockets */
WIN32_EXPORT struct us_socket_context_t *us_create_socket_context(int ssl, struct us_loop_t *loop,
    int ext_size, struct us_socket_context_options_t options);

/* Delete resources allocated at creation time. */
WIN32_EXPORT void us_socket_context_free(int ssl, struct us_socket_context_t *context);

/* Setters of various async callbacks */
WIN32_EXPORT void us_socket_context_on_open(int ssl, struct us_socket_context_t *context,
    struct us_socket_t *(*on_open)(struct us_socket_t *s, int is_client, char *ip, int ip_length));
WIN32_EXPORT void us_socket_context_on_close(int ssl, struct us_socket_context_t *context,
    struct us_socket_t *(*on_close)(struct us_socket_t *s, int code, void *reason));
WIN32_EXPORT void us_socket_context_on_data(int ssl, struct us_socket_context_t *context,
    struct us_socket_t *(*on_data)(struct us_socket_t *s, char *data, int length));
WIN32_EXPORT void us_socket_context_on_writable(int ssl, struct us_socket_context_t *context,
    struct us_socket_t *(*on_writable)(struct us_socket_t *s));
WIN32_EXPORT void us_socket_context_on_timeout(int ssl, struct us_socket_context_t *context,
    struct us_socket_t *(*on_timeout)(struct us_socket_t *s));
/* This one is only used for when a connecting socket fails in a late stage. */
WIN32_EXPORT void us_socket_context_on_connect_error(int ssl, struct us_socket_context_t *context,
    struct us_socket_t *(*on_connect_error)(struct us_socket_t *s, int code));

/* Emitted when a socket has been half-closed */
WIN32_EXPORT void us_socket_context_on_end(int ssl, struct us_socket_context_t *context, struct us_socket_t *(*on_end)(struct us_socket_t *s));

/* Returns user data extension for this socket context */
WIN32_EXPORT void *us_socket_context_ext(int ssl, struct us_socket_context_t *context);

/* Listen for connections. Acts as the main driving cog in a server. Will call set async callbacks. */
WIN32_EXPORT struct us_listen_socket_t *us_socket_context_listen(int ssl, struct us_socket_context_t *context,
    const char *host, int port, int options, int socket_ext_size);

/* listen_socket.c/.h */
WIN32_EXPORT void us_listen_socket_close(int ssl, struct us_listen_socket_t *ls);

/* Land in on_open or on_connection_error or return null or return socket */
WIN32_EXPORT struct us_socket_t *us_socket_context_connect(int ssl, struct us_socket_context_t *context,
    const char *host, int port, const char *source_host, int options, int socket_ext_size);

/* Is this socket established? Can be used to check if a connecting socket has fired the on_open event yet.
 * Can also be used to determine if a socket is a listen_socket or not, but you probably know that already. */
WIN32_EXPORT int us_socket_is_established(int ssl, struct us_socket_t *s);

/* Cancel a connecting socket. Can be used together with us_socket_timeout to limit connection times.
 * Entirely destroys the socket - this function works like us_socket_close but does not trigger on_close event since
 * you never got the on_open event first. */
WIN32_EXPORT struct us_socket_t *us_socket_close_connecting(int ssl, struct us_socket_t *s);

/* Returns the loop for this socket context. */
WIN32_EXPORT struct us_loop_t *us_socket_context_loop(int ssl, struct us_socket_context_t *context);

/* Invalidates passed socket, returning a new resized socket which belongs to a different socket context.
 * Used mainly for "socket upgrades" such as when transitioning from HTTP to WebSocket. */
WIN32_EXPORT struct us_socket_t *us_socket_context_adopt_socket(int ssl, struct us_socket_context_t *context, struct us_socket_t *s, int ext_size);

/* Create a child socket context which acts much like its own socket context with its own callbacks yet still relies on the
 * parent socket context for some shared resources. Child socket contexts should be used together with socket adoptions and nothing else. */
WIN32_EXPORT struct us_socket_context_t *us_create_child_socket_context(int ssl, struct us_socket_context_t *context, int context_ext_size);

/* Public interfaces for loops */

/* Returns a new event loop with user data extension */
WIN32_EXPORT struct us_loop_t *us_create_loop(void *hint, void (*wakeup_cb)(struct us_loop_t *loop),
    void (*pre_cb)(struct us_loop_t *loop), void (*post_cb)(struct us_loop_t *loop), unsigned int ext_size);

/* Frees the loop immediately */
WIN32_EXPORT void us_loop_free(struct us_loop_t *loop);

/* Returns the loop user data extension */
WIN32_EXPORT void *us_loop_ext(struct us_loop_t *loop);

/* Blocks the calling thread and drives the event loop until no more non-fallthrough polls are scheduled */
WIN32_EXPORT void us_loop_run(struct us_loop_t *loop);

/* Signals the loop from any thread to wake up and execute its wakeup handler from the loop's own running thread.
 * This is the only fully thread-safe function and serves as the basis for thread safety */
WIN32_EXPORT void us_wakeup_loop(struct us_loop_t *loop);

/* Hook up timers in existing loop */
WIN32_EXPORT void us_loop_integrate(struct us_loop_t *loop);

/* Returns the loop iteration number */
WIN32_EXPORT long long us_loop_iteration_number(struct us_loop_t *loop);

/* Public interfaces for polls */

/* A fallthrough poll does not keep the loop running, it falls through */
WIN32_EXPORT struct us_poll_t *us_create_poll(struct us_loop_t *loop, int fallthrough, unsigned int ext_size);

/* After stopping a poll you must manually free the memory */
WIN32_EXPORT void us_poll_free(struct us_poll_t *p, struct us_loop_t *loop);

/* Associate this poll with a socket descriptor and poll type */
WIN32_EXPORT void us_poll_init(struct us_poll_t *p, LIBUS_SOCKET_DESCRIPTOR fd, int poll_type);

/* Start, change and stop polling for events */
WIN32_EXPORT void us_poll_start(struct us_poll_t *p, struct us_loop_t *loop, int events);
WIN32_EXPORT void us_poll_change(struct us_poll_t *p, struct us_loop_t *loop, int events);
WIN32_EXPORT void us_poll_stop(struct us_poll_t *p, struct us_loop_t *loop);

/* Return what events we are polling for */
WIN32_EXPORT int us_poll_events(struct us_poll_t *p);

/* Returns the user data extension of this poll */
WIN32_EXPORT void *us_poll_ext(struct us_poll_t *p);

/* Get associated socket descriptor from a poll */
WIN32_EXPORT LIBUS_SOCKET_DESCRIPTOR us_poll_fd(struct us_poll_t *p);

/* Resize an active poll */
WIN32_EXPORT struct us_poll_t *us_poll_resize(struct us_poll_t *p, struct us_loop_t *loop, unsigned int ext_size);

/* Public interfaces for sockets */

/* Returns the underlying native handle for a socket, such as SSL or file descriptor.
 * In the case of file descriptor, the value of pointer is fd. */
WIN32_EXPORT void *us_socket_get_native_handle(int ssl, struct us_socket_t *s);

/* Write up to length bytes of data. Returns actual bytes written.
 * Will call the on_writable callback of active socket context on failure to write everything off in one go.
 * Set hint msg_more if you have more immediate data to write. */
WIN32_EXPORT int us_socket_write(int ssl, struct us_socket_t *s, const char *data, int length, int msg_more);

/* Set a low precision, high performance timer on a socket. A socket can only have one single active timer
 * at any given point in time. Will remove any such pre set timer */
WIN32_EXPORT void us_socket_timeout(int ssl, struct us_socket_t *s, unsigned int seconds);

/* Return the user data extension of this socket */
WIN32_EXPORT void *us_socket_ext(int ssl, struct us_socket_t *s);

/* Return the socket context of this socket */
WIN32_EXPORT struct us_socket_context_t *us_socket_context(int ssl, struct us_socket_t *s);

/* Withdraw any msg_more status and flush any pending data */
WIN32_EXPORT void us_socket_flush(int ssl, struct us_socket_t *s);

/* Shuts down the connection by sending FIN and/or close_notify */
WIN32_EXPORT void us_socket_shutdown(int ssl, struct us_socket_t *s);

/* Shuts down the connection in terms of read, meaning next event loop
 * iteration will catch the socket being closed. Can be used to defer closing
 * to next event loop iteration. */
WIN32_EXPORT void us_socket_shutdown_read(int ssl, struct us_socket_t *s);

/* Returns whether the socket has been shut down or not */
WIN32_EXPORT int us_socket_is_shut_down(int ssl, struct us_socket_t *s);

/* Returns whether this socket has been closed. Only valid if memory has not yet been released. */
WIN32_EXPORT int us_socket_is_closed(int ssl, struct us_socket_t *s);

/* Immediately closes the socket */
WIN32_EXPORT struct us_socket_t *us_socket_close(int ssl, struct us_socket_t *s, int code, void *reason);

/* Returns local port or -1 on failure. */
WIN32_EXPORT int us_socket_local_port(int ssl, struct us_socket_t *s);

/* Copy remote (IP) address of socket, or fail with zero length. */
WIN32_EXPORT void us_socket_remote_address(int ssl, struct us_socket_t *s, char *buf, int *length);

#ifdef __cplusplus
}
#endif

/* Decide what eventing system to use by default */
#if !defined(LIBUS_USE_EPOLL) && !defined(LIBUS_USE_LIBUV) && !defined(LIBUS_USE_GCD) && !defined(LIBUS_USE_KQUEUE)
#if defined(_WIN32)
#define LIBUS_USE_LIBUV
#elif defined(__APPLE__) || defined(__FreeBSD__)
#define LIBUS_USE_KQUEUE
#else
#define LIBUS_USE_EPOLL
#endif
#endif

#endif // LIBUSOCKETS_H
