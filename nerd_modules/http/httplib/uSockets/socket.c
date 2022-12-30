/*
 * Authored by Alex Hultman, 2018-2021.
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

/* Shared with SSL */

int us_socket_local_port(int ssl, struct us_socket_t *s) {
    struct bsd_addr_t addr;
    if (bsd_local_addr(us_poll_fd(&s->p), &addr)) {
        return -1;
    } else {
        return bsd_addr_get_port(&addr);
    }
}

void us_socket_shutdown_read(int ssl, struct us_socket_t *s) {
    /* This syscall is idempotent so no extra check is needed */
    bsd_shutdown_socket_read(us_poll_fd((struct us_poll_t *) s));
}

void us_socket_remote_address(int ssl, struct us_socket_t *s, char *buf, int *length) {
    struct bsd_addr_t addr;
    if (bsd_remote_addr(us_poll_fd(&s->p), &addr) || *length < bsd_addr_get_ip_length(&addr)) {
        *length = 0;
    } else {
        *length = bsd_addr_get_ip_length(&addr);
        memcpy(buf, bsd_addr_get_ip(&addr), *length);
    }
}

struct us_socket_context_t *us_socket_context(int ssl, struct us_socket_t *s) {
    return s->context;
}

void us_socket_timeout(int ssl, struct us_socket_t *s, unsigned int seconds) {
    if (seconds) {
        s->timeout = 0x8000 | (s->context->timestamp + (seconds >> 2));
    } else {
        s->timeout = 0;
    }
}

void us_socket_flush(int ssl, struct us_socket_t *s) {
    if (!us_socket_is_shut_down(0, s)) {
        bsd_socket_flush(us_poll_fd((struct us_poll_t *) s));
    }
}

int us_socket_is_closed(int ssl, struct us_socket_t *s) {
    return s->prev == (struct us_socket_t *) s->context;
}

int us_socket_is_established(int ssl, struct us_socket_t *s) {
    /* Everything that is not POLL_TYPE_SEMI_SOCKET is established */
    return us_internal_poll_type((struct us_poll_t *) s) != POLL_TYPE_SEMI_SOCKET;
}

/* Exactly the same as us_socket_close but does not emit on_close event */
struct us_socket_t *us_socket_close_connecting(int ssl, struct us_socket_t *s) {
    if (!us_socket_is_closed(0, s)) {
        us_internal_socket_context_unlink(s->context, s);
        us_poll_stop((struct us_poll_t *) s, s->context->loop);
        bsd_close_socket(us_poll_fd((struct us_poll_t *) s));

        /* Link this socket to the close-list and let it be deleted after this iteration */
        s->next = s->context->loop->data.closed_head;
        s->context->loop->data.closed_head = s;

        /* Any socket with prev = context is marked as closed */
        s->prev = (struct us_socket_t *) s->context;

        //return s->context->on_close(s, code, reason);
    }
    return s;
}

/* Same as above but emits on_close */
struct us_socket_t *us_socket_close(int ssl, struct us_socket_t *s, int code, void *reason) {
    if (!us_socket_is_closed(0, s)) {
        us_internal_socket_context_unlink(s->context, s);
        us_poll_stop((struct us_poll_t *) s, s->context->loop);
        bsd_close_socket(us_poll_fd((struct us_poll_t *) s));

        /* Link this socket to the close-list and let it be deleted after this iteration */
        s->next = s->context->loop->data.closed_head;
        s->context->loop->data.closed_head = s;

        /* Any socket with prev = context is marked as closed */
        s->prev = (struct us_socket_t *) s->context;

        return s->context->on_close(s, code, reason);
    }
    return s;
}

/* Not shared with SSL */

void *us_socket_get_native_handle(int ssl, struct us_socket_t *s) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return us_internal_ssl_socket_get_native_handle((struct us_internal_ssl_socket_t *) s);
    }
#endif

    return (void *) (uintptr_t) us_poll_fd((struct us_poll_t *) s);
}

int us_socket_write(int ssl, struct us_socket_t *s, const char *data, int length, int msg_more) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return us_internal_ssl_socket_write((struct us_internal_ssl_socket_t *) s, data, length, msg_more);
    }
#endif

    if (us_socket_is_closed(ssl, s) || us_socket_is_shut_down(ssl, s)) {
        return 0;
    }

    int written = bsd_send(us_poll_fd(&s->p), data, length, msg_more);
    if (written != length) {
        s->context->loop->data.last_write_failed = 1;
        us_poll_change(&s->p, s->context->loop, LIBUS_SOCKET_READABLE | LIBUS_SOCKET_WRITABLE);
    }

    return written < 0 ? 0 : written;
}

void *us_socket_ext(int ssl, struct us_socket_t *s) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return us_internal_ssl_socket_ext((struct us_internal_ssl_socket_t *) s);
    }
#endif

    return s + 1;
}

int us_socket_is_shut_down(int ssl, struct us_socket_t *s) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        return us_internal_ssl_socket_is_shut_down((struct us_internal_ssl_socket_t *) s);
    }
#endif

    return us_internal_poll_type(&s->p) == POLL_TYPE_SOCKET_SHUT_DOWN;
}

void us_socket_shutdown(int ssl, struct us_socket_t *s) {
#ifndef LIBUS_NO_SSL
    if (ssl) {
        us_internal_ssl_socket_shutdown((struct us_internal_ssl_socket_t *) s);
        return;
    }
#endif

    /* Todo: should we emit on_close if calling shutdown on an already half-closed socket?
     * We need more states in that case, we need to track RECEIVED_FIN
     * so far, the app has to track this and call close as needed */
    if (!us_socket_is_closed(ssl, s) && !us_socket_is_shut_down(ssl, s)) {
        us_internal_poll_set_type(&s->p, POLL_TYPE_SOCKET_SHUT_DOWN);
        us_poll_change(&s->p, s->context->loop, us_poll_events(&s->p) & LIBUS_SOCKET_READABLE);
        bsd_shutdown_socket(us_poll_fd((struct us_poll_t *) s));
    }
}
