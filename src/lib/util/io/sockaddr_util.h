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

#ifndef SOCKADDR_UTIL_H
#define SOCKADDR_UTIL_H 1

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cassert>

// These definitions in this file are for the convenience of internal
// implementation and test code, and are not intended to be used publicly.
// The namespace "internal" indicates the intent.

namespace isc {
namespace util {
namespace io {
namespace internal {

inline socklen_t
getSALength(const struct sockaddr& sa) {
    if (sa.sa_family == AF_INET) {
        return (sizeof(struct sockaddr_in));
    } else {
        assert(sa.sa_family == AF_INET6);
        return (sizeof(struct sockaddr_in6));
    }
}

// Lower level C-APIs require conversion between various variants of
// sockaddr's, which is not friendly with C++.  The following templates
// are a shortcut of common workaround conversion in such cases.

template <typename SAType>
const struct sockaddr*
convertSockAddr(const SAType* sa) {
    const void* p = sa;
    return (static_cast<const struct sockaddr*>(p));
}

template <typename SAType>
const SAType*
convertSockAddr(const struct sockaddr* sa) {
    const void* p = sa;
    return (static_cast<const SAType*>(p));
}

template <typename SAType>
struct sockaddr*
convertSockAddr(SAType* sa) {
    void* p = sa;
    return (static_cast<struct sockaddr*>(p));
}

template <typename SAType>
SAType*
convertSockAddr(struct sockaddr* sa) {
    void* p = sa;
    return (static_cast<SAType*>(p));
}

}
}
}
}

#endif  // SOCKADDR_UTIL_H

// Local Variables:
// mode: c++
// End:
