// Copyright (C) 2010  CZ NIC
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
#include <cstring>
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
    if (bind(sock, bind_addr, addr_len) == -1) {
        return -2;
    }
    return sock;
}

int
send_fd(const int, const int) {
    return 0;
}

int
run(const int input_fd, const int output_fd, const get_sock_t get_sock,
    const send_fd_t send_fd)
{
// These are macros so they can exit the function
#define READ(WHERE, HOW_MANY) do { \
        size_t how_many = (HOW_MANY); \
        if (read_data(input_fd, (WHERE), how_many) < how_many) { \
            return 1; \
        } \
    } while (0)
#define WRITE(WHAT, HOW_MANY) do { \
        if (!write_data(output_fd, (WHAT), (HOW_MANY))) { \
            return 2; \
        } \
    } while (0)
#define DEFAULT \
    default: /* Unrecognized part of protocol */ \
        WRITE("FI", 2); \
        return 3;
    for (;;) {
        // Read the command
        char command;
        READ(&command, 1);
        switch (command) {
            case 'T': // The "terminate" command
                return 0;
            case 'S': { // Create a socket
                // Read what type of socket they want
                char type[2];
                READ(type, 2);
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
                        READ(static_cast<char *>(static_cast<void *>(
                            &addr_in.sin_port)), 2);
                        READ(static_cast<char *>(static_cast<void *>(
                            &addr_in.sin_addr.s_addr)), 4);
                        break;
                    case '6':
                        addr = static_cast<struct sockaddr *>(
                            static_cast<void *>(&addr_in6));
                        addr_len = sizeof addr_in6;
                        memset(&addr_in6, 0, sizeof addr_in6);
                        addr_in6.sin6_family = AF_INET6;
                        READ(static_cast<char *>(static_cast<void *>(
                            &addr_in6.sin6_port)), 2);
                        READ(static_cast<char *>(static_cast<void *>(
                            &addr_in6.sin6_addr.s6_addr)), 16);
                        break;
                    DEFAULT
                }
                int sock_type;
                switch (type[0]) { // Translate the type
                    case 'T':
                        sock_type = SOCK_STREAM;
                        break;
                    case 'U':
                        sock_type = SOCK_DGRAM;
                        break;
                    DEFAULT
                }
                int result(get_sock(sock_type, addr, addr_len));
                if (result >= 0) { // We got the socket
                    WRITE("S", 1);
                    // FIXME: Check the output and write a test for it
                    send_fd(output_fd, result);
                } else {
                    WRITE("E", 1);
                    switch (result) {
                        case -1:
                            WRITE("S", 1);
                            break;
                        case -2:
                            WRITE("B", 1);
                            break;
                        default:
                            return 4;
                    }
                    int error(errno);
                    WRITE(static_cast<char *>(static_cast<void *>(&error)),
                        sizeof error);
                }
                break;
            }
            DEFAULT
        }
    }
}

} // End of the namespaces
}
