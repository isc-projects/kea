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

namespace isc {
namespace xfr {

// Receive socket descriptor on unix domain socket 'sock'.
// Returned value is the socket descriptor received.
// Errors are indicated by a return value of -1.
int recv_fd(int sock);

// Send socket descriptor "fd" to server over unix domain socket 'sock', 
// the connection from socket 'sock' to unix domain server should be established first.
// Errors are indicated by a return value of -1.
int send_fd(int sock, int fd);

} // End for namespace xfr
} // End for namespace isc

#endif

// Local Variables: 
// mode: c++
// End: 
