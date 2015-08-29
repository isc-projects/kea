// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/io/fd.h>

#include <unistd.h>
#include <cerrno>

namespace isc {
namespace util {
namespace io {

bool
write_data(const int fd, const void *buffer_v, const size_t length) {
    const unsigned char* buffer(static_cast<const unsigned char*>(buffer_v));
    size_t remaining = length;  // Amount remaining to be written

    // Just keep writing until all is written
    while (remaining > 0) {
        const int written = write(fd, buffer, remaining);
        if (written == -1) {
            if (errno == EINTR) { // Just keep going
                continue;
            } else {
                return (false);
            }

        } else if (written > 0) {
            // Wrote "written" bytes from the buffer
            remaining -= written;
            buffer += written;

        } else {
            // Wrote zero bytes from the buffer. We should not get here as any
            // error that causes zero bytes to be written should have returned
            // -1.  However, write(2) can return 0, and in this case we
            // interpret it as an error.
            return (false);
        }
    }
    return (true);
}

ssize_t
read_data(const int fd, void *buffer_v, const size_t length) {
    unsigned char* buffer(static_cast<unsigned char*>(buffer_v));
    size_t remaining = length;   // Amount remaining to be read

    while (remaining > 0) {
        const int amount = read(fd, buffer, remaining);
        if (amount == -1) {
            if (errno == EINTR) { // Continue on interrupted call
                continue;
            } else {
                return (-1);
            }
        } else if (amount > 0) {
            // Read "amount" bytes into the buffer
            remaining -= amount;
            buffer += amount;
        } else {
            // EOF - end the read
            break;
        }
    }

    // Return total number of bytes read
    return (static_cast<ssize_t>(length - remaining));
}

}
}
}
