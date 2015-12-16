// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
