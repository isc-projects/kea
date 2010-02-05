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

// $Id: rdata.cc 545 2010-01-27 00:33:28Z jinmei $

#include <stdint.h>
#include <string.h>

#include <string>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards

#include "buffer.h"
#include <exceptions/exceptions.h>
#include "messagerenderer.h"
#include "rdata.h"
#include "rdataclass.h"

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

A::A(const string& addrstr)
{
    // RFC1035 states textual representation of IN/A RDATA is
    // "four decimal numbers separated by dots without any embedded spaces".
    // This is exactly what inet_pton() accepts for AF_INET.  In particular,
    // it rejects an abbreviated form such as "10.1" meaning "10.0.0.1".
    if (inet_pton(AF_INET, addrstr.c_str(), &addr_) != 1) {
        dns_throw(InvalidRdataText,
                  "failed to parse IPv4 address for IN/A RDATA");
    }
}

A::A(InputBuffer& buffer, size_t rdata_len)
{
    if (rdata_len != sizeof(addr_)) {
        dns_throw(InvalidRdataLength, "Length mismatch for IN/A RDATA");
    }
    buffer.readData(&addr_, sizeof(addr_));
}

A::A(const A& other) :
    addr_(other.addr_)
{}

void
A::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(&addr_, sizeof(addr_));
}

void
A::toWire(MessageRenderer& renderer) const
{
    renderer.writeData(&addr_, sizeof(addr_));
}

string
A::toText() const
{
    char addr_string[sizeof("255.255.255.255")];

    if (inet_ntop(AF_INET, &addr_, addr_string, sizeof(addr_string)) == NULL) {
        dns_throw(Unexpected, "inet_ntop failed for an IPv4 address");
    }

    return (string(addr_string));
}

int
A::compare(const Rdata& other) const
{
    const A& other_a = dynamic_cast<const A&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}
// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
