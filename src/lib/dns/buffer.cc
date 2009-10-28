// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <sys/types.h>
#include <sys/socket.h>

#include <dns/buffer.h>

using isc::SingleBuffer;

// The interface should be revisited.
int
SingleBuffer::send_to(int s, const struct sockaddr& to, socklen_t to_len)
{
    int cc;

    cc = sendto(s, &buf_[0], buf_.size(), 0, &to, to_len);
    return (cc);
}

int
SingleBuffer::recv_from(int s, struct sockaddr* from, socklen_t* from_len)
{
    int cc;

    if (!buf_.empty())
        throw isc::ISCBufferInvalidPosition();

    buf_.resize(buf_.capacity());
    cc = recvfrom(s, &buf_[0], buf_.size(), 0, from, from_len);
    if (cc >= 0)
        buf_.resize(cc);
    else
        buf_.resize(0);          // XXX

    return (cc);
}
