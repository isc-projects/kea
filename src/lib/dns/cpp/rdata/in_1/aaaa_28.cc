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

#include <stdint.h>
#include <string.h>

#include <string>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards

#include "buffer.h"
#include "exceptions.h"
#include "messagerenderer.h"
#include "rdata.h"
#include "rdataclass.h"

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

AAAA::AAAA(const string& addrstr)
{
    if (inet_pton(AF_INET6, addrstr.c_str(), &addr_) != 1) {
        dns_throw(InvalidRdataText,
                  "failed to parse IPv6 address for IN/AAAA RDATA");
    }
}

AAAA::AAAA(InputBuffer& buffer, size_t rdata_len)
{
    if (rdata_len != sizeof(addr_)) {
        dns_throw(InvalidRdataLength, "Length mismatch for IN/AAAA RDATA");
    }
    buffer.readData(&addr_, sizeof(addr_));
}

AAAA::AAAA(const AAAA& other)
{
    memcpy(addr_, other.addr_, sizeof(addr_));
}

void
AAAA::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(&addr_, sizeof(addr_));
}

void
AAAA::toWire(MessageRenderer& renderer) const
{
    renderer.writeData(&addr_, sizeof(addr_));
}

string
AAAA::toText() const
{
    char addr_string[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

    if (inet_ntop(AF_INET6, &addr_, addr_string, sizeof(addr_string)) == NULL) {
        dns_throw(Unexpected, "inet_ntop failed for an IPv6 address");
    }

    return (string(addr_string));
}

int
AAAA::compare(const Rdata& other) const
{
    const AAAA& other_a = dynamic_cast<const AAAA&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
