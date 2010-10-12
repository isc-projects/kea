// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef FD_SHARE_H_
#define FD_SHARE_H_

/**
 * \file fd_share.h
 * \short Support to transfer file descriptors between processes.
 */

namespace isc {
namespace util {
namespace io {

/**
 * \short Receives a file descriptor.
 * This receives a file descriptor sent over an unix domain socket. This
 * is the counterpart of send_fd().
 *
 * @return -1 on error, the socket descriptor on success.
 * @param sock The unix domain socket to read from. Tested and it does
 *     not work with a pipe.
 */
int recv_fd(const int sock);

/**
 * \short Sends a file descriptor.
 * This sends a file descriptor over an unix domain socket. This is the
 * counterpart of recv_fd().
 *
 * @return -1 on error, 0 otherwise.
 * @param sock The unix domain socket to send to. Tested and it does not
 *     work with a pipe.
 * @param fd The file descriptor to send. It should work with any valid
 *     file descriptor.
 */
int send_fd(const int sock, const int fd);

} // End for namespace io
} // End for namespace util
} // End for namespace isc

#endif

// Local Variables: 
// mode: c++
// End: 
