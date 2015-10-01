// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt_filter.h>

#include <sys/fcntl.h>
#include <sys/socket.h>

namespace isc {
namespace dhcp {

int
PktFilter::openFallbackSocket(const isc::asiolink::IOAddress& addr,
                              const uint16_t port) {
    // Create socket.
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        isc_throw(SocketConfigError, "failed to create fallback socket for"
                  " address " << addr << ", port " << port
                  << ", reason: " << strerror(errno));
    }
    // Set the close-on-exec flag.
    if (fcntl(sock, F_SETFD, FD_CLOEXEC) < 0) {
        close(sock);
        isc_throw(SocketConfigError, "Failed to set close-on-exec flag"
                  << " on fallback socket for address " << addr
                  << ", port " << port
                  << ", reason: " << strerror(errno));
    }
    // Bind the socket to a specified address and port.
    struct sockaddr_in addr4;
    memset(&addr4, 0, sizeof(addr4));
    addr4.sin_family = AF_INET;
    addr4.sin_addr.s_addr = htonl(addr);
    addr4.sin_port = htons(port);

    if (bind(sock, reinterpret_cast<struct sockaddr*>(&addr4),
             sizeof(addr4)) < 0) {
        // Get the error message immediately after the bind because the
        // invocation to close() below would override the errno.
        char* errmsg = strerror(errno);
        // Remember to close the socket if we failed to bind it.
        close(sock);
        isc_throw(SocketConfigError, "failed to bind fallback socket to"
                  " address " << addr << ", port " << port
                  << ", reason: " << errmsg
                  << " - is another DHCP server running?");
    }

    // Set socket to non-blocking mode. This is to prevent the read from the
    // fallback socket to block message processing on the primary socket.
    if (fcntl(sock, F_SETFL, O_NONBLOCK) != 0) {
        // Get the error message immediately after the bind because the
        // invocation to close() below would override the errno.
        char* errmsg = strerror(errno);
        close(sock);
        isc_throw(SocketConfigError, "failed to set SO_NONBLOCK option on the"
                  " fallback socket, bound to " << addr << ", port "
                  << port << ", reason: " << errmsg);
    }
    // Successfully created and bound a fallback socket. Return a descriptor.
    return (sock);
}


} // end of isc::dhcp namespace
} // end of isc namespace
