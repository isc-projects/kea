// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PKTINFO_UTIL_H
#define PKTINFO_UTIL_H 1

#include <sys/socket.h>
#include <netinet/in.h>

// These definitions in this file are for the convenience of internal
// implementation and test code, and are not intended to be used publicly.
// The namespace "internal" indicates the intent.

namespace isc {
namespace util {
namespace io {
namespace internal {

// Lower level C-APIs require conversion between char* pointers
// (like structures returned by CMSG_DATA macro) and in6_pktinfo,
// which is not friendly with C++. The following templates
// are a shortcut of common workaround conversion in such cases.
inline struct in6_pktinfo*
convertPktInfo6(char* pktinfo) {
    return (static_cast<struct in6_pktinfo*>(static_cast<void*>(pktinfo)));
}

inline struct in6_pktinfo*
convertPktInfo6(unsigned char* pktinfo) {
    return (static_cast<struct in6_pktinfo*>(static_cast<void*>(pktinfo)));
}

/// @todo: Do we need const versions as well?

}
}
}
}

#endif  // PKTINFO_UTIL_H
