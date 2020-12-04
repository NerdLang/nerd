/* Incomplete Swift version of http_server example */

import Foundation
import CoreFoundation
import uSockets

/* Keep track of connections, for fun */
var sockets = 0

/* Create loop */
let loop = us_create_loop(UnsafeMutableRawPointer(bitPattern: 0), { loop in }, { loop in }, { loop in }, 0)

/* Create socket context */
let options = us_socket_context_options_t()
let context = us_create_socket_context(0, loop, 0, options)

/* Register callbacks */
us_socket_context_on_open(0, context) { (s, b, ip, ipLength) -> OpaquePointer? in
    sockets += 1
    print("Welcome socket \(sockets)!")
    return s
}

us_socket_context_on_end(0, context) { (s) -> OpaquePointer? in
    return s
}

us_socket_context_on_close(0, context) { (s) -> OpaquePointer? in
    return s
}

us_socket_context_on_data(0, context) { (s, data, length) -> OpaquePointer? in
    us_socket_write(0, s, data, length, 0)
    return s
}

/* Listen on port 3000 */
"127.0.0.1".data(using: .utf8)?.withUnsafeBytes({ (unsafeRawBufferPointer) -> Void in
    let host = unsafeRawBufferPointer.bindMemory(to: Int8.self).baseAddress!
    if let _ = us_socket_context_listen(0, context, host, 3000, 0, 0) {
        print("Listening on port 3000 from Swift")
    }
})

/* Integrate with existing CoreFoundation/GCD event-loop */
us_loop_integrate(loop)
CFRunLoopRun()
