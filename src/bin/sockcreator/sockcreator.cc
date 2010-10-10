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

#include <unistd.h>
#include <cerrno>

namespace isc {
namespace socket_creator {

int
get_sock(const int type, struct sockaddr *bind_addr, const socklen_t addr_len)
{
    int sock(socket(bind_addr->sa_family, type, 0));
    if(sock == -1) {
        return -1;
    }
    if(bind(sock, bind_addr, addr_len) == -1) {
        return -2;
    }
    return sock;
}

int
send_fd(const int destination, const int payload) {
    // TODO Steal
}

int
run(const int input_fd, const int output_fd, const get_sock_t get_sock,
    const send_fd_t send_fd)
{
    // TODO Implement
}

bool
write_data(const int fd, const char *buffer, const size_t length) {
    size_t rest(length);
    // Just keep writing until all is written
    while(rest) {
        ssize_t written(write(fd, buffer, rest));
        if(rest == -1) {
            if(errno == EINTR) { // Just keep going
                continue;
            } else {
                return false;
            }
        } else { // Wrote something
            rest -= written;
            buffer += written;
        }
    }
    return true;
}

ssize_t
read_data(const int fd, char *buffer, const size_t length) {
    size_t rest(length), already(0);
    while(rest) { // Stil something to read
        ssize_t amount(read(fd, buffer, rest));
        if(rest == -1) {
            if(errno == EINTR) { // Continue on interrupted call
                continue;
            } else {
                return -1;
            }
        } else if(amount) {
            already += amount;
            rest -= amount;
            buffer += amount;
        } else { // EOF
            return already;
        }
    }
    return already;
}

} // End of the namespaces
}
