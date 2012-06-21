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

#include <stdint.h>
#include <string.h>

#include <string>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards
#include <sys/socket.h> // for AF_INET/AF_INET6

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

A::A(const std::string& addrstr) {
    // RFC1035 states textual representation of IN/A RDATA is
    // "four decimal numbers separated by dots without any embedded spaces".
    // This is exactly what inet_pton() accepts for AF_INET.  In particular,
    // it rejects an abbreviated form such as "10.1" meaning "10.0.0.1".
    if (inet_pton(AF_INET, addrstr.c_str(), &addr_) != 1) {
        isc_throw(InvalidRdataText,
                  "IN/A RDATA construction from text failed: Address cannot be "
                  "converted: " << addrstr);
    }
}

A::A(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len != sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/A RDATA construction from wire failed: Invalid length: "
                  << rdata_len);
    }
    if (buffer.getLength() - buffer.getPosition() < sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/A RDATA construction from wire failed: "
                  "insufficient buffer length: "
                  << buffer.getLength() - buffer.getPosition());
    }
    buffer.readData(&addr_, sizeof(addr_));
}

A::A(const A& other) : Rdata(), addr_(other.addr_)
{}

void
A::toWire(OutputBuffer& buffer) const {
    buffer.writeData(&addr_, sizeof(addr_));
}

void
A::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeData(&addr_, sizeof(addr_));
}

string
A::toText() const {
    char addr_string[sizeof("255.255.255.255")];

    if (inet_ntop(AF_INET, &addr_, addr_string, sizeof(addr_string)) == NULL) {
        isc_throw(Unexpected,
                  "Failed to convert IN/A RDATA to textual IPv4 address");
    }

    return (addr_string);
}

int
A::compare(const Rdata& other) const {
    const A& other_a = dynamic_cast<const A&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}
// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
