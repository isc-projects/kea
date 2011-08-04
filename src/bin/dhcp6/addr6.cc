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

#include <string.h>
#include <arpa/inet.h>

#include <ostream>

#include "dhcp6/addr6.h"

std::ostream&
isc::operator << (std::ostream & out, const isc::Addr6& addr) {
    out << addr.getPlain();
    return out;
}

using namespace std;
using namespace isc;

Addr6::Addr6(const char* addr, bool plain /*=false*/) {
    if (plain) {
        inet_pton(AF_INET6, addr, addr_);
    } else {
        memcpy(addr_, addr, 16);
    }
}

Addr6::Addr6() {
    memset(addr_, 0, 16);
}

Addr6::Addr6(in6_addr* addr) {
    memcpy(addr_, addr, 16);
}

Addr6::Addr6(sockaddr_in6* addr) {
    memcpy(addr_, &addr->sin6_addr, 16);
}

bool
Addr6::linkLocal() const {
    if ( ( (unsigned char)addr_[0]==0xfe) &&
         ( (unsigned char)addr_[1]==0x80) ) {
	return (true);
    } else {
        return (false);
    }
}

bool
Addr6::multicast() const {
    if ( (unsigned char)addr_[0]==0xff) {
        return (true);
    } else {
        return (false);
    }
}

std::string
Addr6::getPlain() const {
    char buf[MAX_ADDRESS_STRING_LEN];

    inet_ntop(AF_INET6, addr_, buf, MAX_ADDRESS_STRING_LEN);
    return (string(buf));
}

bool
Addr6::equals(const Addr6& other) const {
    if (!memcmp(addr_, other.addr_, 16)) {
        return (true);
    } else {
        return (false);
    }
    // return !memcmp() would be shorter, but less readable
}

bool
Addr6::operator==(const Addr6& other) const {
    return (equals(other));
}
