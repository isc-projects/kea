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

#ifndef UTIL_IO_FD_H
#define UTIL_IO_FD_H 1

#include <unistd.h>

/**
 * @file fd.h
 * @short Wrappers around common unix fd manipulation functions.
 */

namespace isc {
namespace util {
namespace io {

/*
 * \short write() that writes everything.
 * Wrapper around write(). The difference is, it never writes less data
 * and looks successful (eg. it blocks until all data are written).
 * Retries on signals.
 *
 * \return True if successful, false otherwise. The errno variable is left
 *     intact.
 * \param fd Where to write.
 * \param data The buffer to write.
 * \param length How much data is there to write.
 */
bool
write_data(const int fd, const void *data, const size_t length);

/*
 * \short read() that reads everything.
 * Wrapper around read(). It does not do short reads, if it returns less,
 * it means there was EOF. It retries on signals.
 *
 * \return Number of bytes read or -1 on error.
 * \param fd Where to read data from.
 * \param data Where to put the data.
 * \param length How many of them.
 */
ssize_t
read_data(const int fd, void *buffer, const size_t length);

}
}
}

#endif // UTIL_IO_FD_H
