// Copyright (C) 2011-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SOCKADDR_UTIL_H
#define SOCKADDR_UTIL_H 1

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <exceptions/isc_assert.h>

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
        isc_throw_assert(sa.sa_family == AF_INET6);
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
