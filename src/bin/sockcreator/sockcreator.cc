// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "sockcreator.h"

#include <util/io/fd.h>

#include <cerrno>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace isc::util::io;
using namespace isc::socket_creator;

namespace {

// Simple wrappers for read_data/write_data that throw an exception on error.
void
read_message(int fd, void* where, const size_t length) {
    if (read_data(fd, where, length) < length) {
        isc_throw(ReadError, "Error reading from socket creator client");
    }
}

void
write_message(int fd, const void* what, const size_t length) {
    if (!write_data(fd, what, length)) {
        isc_throw(WriteError, "Error writing to socket creator client");
    }
}

// Exit on a protocol error after informing the client of the problem.
void
protocol_error(int fd, const char reason = 'I') {

    // Tell client we have a problem
    char message[2];
    message[0] = 'F';
    message[1] = reason;
    write_message(fd, message, sizeof(message));

    // ... and exit
    isc_throw(ProtocolError, "Fatal error, reason: " << reason);
}

// Handle the request from the client.
//
// Reads the type and family of socket required, creates the socket, then
// returns it to the client.
//
// The arguments are the same as those passed to run().
void
handle_request(const int input_fd, const int output_fd,
               const get_sock_t get_sock, const send_fd_t send_fd_fun,
               const close_t close_fun)
{
    // Read the message from the client
    char type[2];
    read_message(input_fd, type, sizeof(type));

    // Decide what type of socket is being asked for
    int sock_type = 0;
    switch (type[0]) {
        case 'T':
            sock_type = SOCK_STREAM;
            break;

        case 'U':
            sock_type = SOCK_DGRAM;
            break;

        default:
            protocol_error(output_fd);
    }

    // Read the address they ask for depending on what address family was
    // specified.
    sockaddr* addr = NULL;
    size_t addr_len = 0;
    sockaddr_in addr_in;
    sockaddr_in6 addr_in6;
    switch (type[1]) { // The address family

        // The casting to apparently incompatible types by reinterpret_cast
        // is required by the C low-level interface. Unions are not used
        // because of the possibility of alignment issues.

        case '4':
            addr = reinterpret_cast<sockaddr*>(&addr_in);
            addr_len = sizeof(addr_in);
            memset(&addr_in, 0, sizeof addr_in);
            addr_in.sin_family = AF_INET;
            read_message(input_fd, static_cast<void *>(&addr_in.sin_port),
                         sizeof(addr_in.sin_port));
            read_message(input_fd, static_cast<void *>(&addr_in.sin_addr.s_addr),
                         sizeof(addr_in.sin_addr.s_addr));
            break;

        case '6':
            addr = reinterpret_cast<sockaddr*>(&addr_in6);
            addr_len = sizeof addr_in6;
            memset(&addr_in6, 0, sizeof addr_in6);
            addr_in6.sin6_family = AF_INET6;
            read_message(input_fd, static_cast<void *>(&addr_in6.sin6_port),
                         sizeof(addr_in6.sin6_port));
            read_message(input_fd, static_cast<void *>(&addr_in6.sin6_addr.s6_addr),
                         sizeof(addr_in6.sin6_addr.s6_addr));
            break;

        default:
            protocol_error(output_fd);
    }

    // Obtain the socket
    int result = get_sock(sock_type, addr, addr_len);
    if (result >= 0) {
        // Got the socket, send it to the client.
        write_message(output_fd, "S", 1);
        if (send_fd_fun(output_fd, result) != 0) {
            // We'll soon abort ourselves, but make sure we still
            // close the socket; don't bother if it fails as the
            // higher level result (abort) is the same.
            close_fun(result);
            isc_throw(InternalError, "Error sending descriptor");
        }

        // Don't leak the socket used to send the acquired socket back to the
        // client.
        if (close_fun(result) == -1) {
            isc_throw(InternalError, "Error closing socket");
        }
    } else {
        // Error.  Tell the client.
        write_message(output_fd, "E", 1);
        switch (result) {
            case -1:
                write_message(output_fd, "S", 1);
                break;

            case -2:
                write_message(output_fd, "B", 1);
                break;

            default:
                isc_throw(InternalError, "Error creating socket");
        }

        // Error reason code.
        int error = errno;
        write_message(output_fd, static_cast<void *>(&error), sizeof error);
    }
}

} // Anonymous namespace

namespace isc {
namespace socket_creator {

// Get the socket and bind to it.
int
get_sock(const int type, struct sockaddr *bind_addr, const socklen_t addr_len)
{
    int sock(socket(bind_addr->sa_family, type, 0));
    if (sock == -1) {
        return -1;
    }
    const int on(1);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        return -2; // This is part of the binding process, so it's a bind error
    }
    if (bind_addr->sa_family == AF_INET6 &&
        setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)) == -1) {
        return -2; // This is part of the binding process, so it's a bind error
    }
    if (bind(sock, bind_addr, addr_len) == -1) {
        return -2;
    }
    return sock;
}

// Main run loop.
void
run(const int input_fd, const int output_fd, const get_sock_t get_sock,
    const send_fd_t send_fd_fun, const close_t close_fun)
{
    for (;;) {
        char command;
        read_message(input_fd, &command, sizeof(command));
        switch (command) {
            case 'S':   // The "get socket" command
                handle_request(input_fd, output_fd, get_sock,
                               send_fd_fun, close_fun);
                break;

            case 'T':   // The "terminate" command
                return;

            default:    // Don't recognise anything else
                protocol_error(output_fd);
        }
    }
}

} // End of the namespaces
}
