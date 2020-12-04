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

#ifndef GCD_H
#define GCD_H

#include "internal/loop_data.h"

#include <dispatch/dispatch.h>
#define LIBUS_SOCKET_READABLE 1
#define LIBUS_SOCKET_WRITABLE 2

struct us_loop_t {
    alignas(LIBUS_EXT_ALIGNMENT) struct us_internal_loop_data_t data;

    dispatch_queue_t gcd_queue;
};

struct us_poll_t {
    int events;
    dispatch_source_t gcd_read, gcd_write;
    LIBUS_SOCKET_DESCRIPTOR fd;
    unsigned char poll_type;
};

#endif // GCD_H
