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

#include <unistd.h>
#include <cerrno>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace isc::util::io;

namespace isc {
namespace socket_creator {

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

// Simple wrappers for read_data/write_data that thr0w an exception on error.
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

// Exit on some protocol error after informing the client of the problem.
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


void
run(const int input_fd, const int output_fd, const get_sock_t get_sock,
    const send_fd_t send_fd_fun, const close_t close_fun)
{
    for (;;) {
        // Read the command
        char command;
        read_message(input_fd, &command, sizeof(command));
        switch (command) {
            case 'T': // The "terminate" command
                return;
            case 'S': { // Create a socket
                // Read what type of socket they want
                char type[2];
                read_message(input_fd, type, sizeof(type));
                // Read the address they ask for
                struct sockaddr *addr(NULL);
                size_t addr_len(0);
                struct sockaddr_in addr_in;
                struct sockaddr_in6 addr_in6;
                switch (type[1]) { // The address family
                    /*
                     * Here are some casts. They are required by C++ and
                     * the low-level interface (they are implicit in C).
                     */
                    case '4':
                        addr = static_cast<struct sockaddr *>(
                            static_cast<void *>(&addr_in));
                        addr_len = sizeof addr_in;
                        memset(&addr_in, 0, sizeof addr_in);
                        addr_in.sin_family = AF_INET;
                        read_message(input_fd,
                            static_cast<char *>(static_cast<void *>(
                            &addr_in.sin_port)), 2);
                        read_message(input_fd,
                            static_cast<char *>(static_cast<void *>(
                            &addr_in.sin_addr.s_addr)), 4);
                        break;
                    case '6':
                        addr = static_cast<struct sockaddr *>(
                            static_cast<void *>(&addr_in6));
                        addr_len = sizeof addr_in6;
                        memset(&addr_in6, 0, sizeof addr_in6);
                        addr_in6.sin6_family = AF_INET6;
                        read_message(input_fd,
                            static_cast<char *>(static_cast<void *>(
                            &addr_in6.sin6_port)), 2);
                        read_message(input_fd,
                            static_cast<char *>(static_cast<void *>(
                            &addr_in6.sin6_addr.s6_addr)), 16);
                        break;
                    default:
                        protocol_error(output_fd);
                }
                int sock_type = 0;
                switch (type[0]) { // Translate the type
                    case 'T':
                        sock_type = SOCK_STREAM;
                        break;
                    case 'U':
                        sock_type = SOCK_DGRAM;
                        break;
                    default:
                        protocol_error(output_fd);
                }
                int result(get_sock(sock_type, addr, addr_len));
                if (result >= 0) { // We got the socket
                    write_message(output_fd, "S", 1);
                    if (send_fd_fun(output_fd, result) != 0) {
                        // We'll soon abort ourselves, but make sure we still
                        // close the socket; don't bother if it fails as the
                        // higher level result (abort) is the same.
                        close_fun(result);
                        isc_throw(InternalError, "Error sending descriptor");
                    }
                    // Don't leak the socket
                    if (close_fun(result) == -1) {
                        isc_throw(InternalError, "Error closing socket");
                    }
                } else {
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
                    int error(errno);
                    write_message(output_fd,
                        static_cast<char *>(static_cast<void *>(&error)),
                        sizeof error);
                }
                break;
            }
            default:
                protocol_error(output_fd);
        }
    }
}

} // End of the namespaces
}
