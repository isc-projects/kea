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

#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/master_lexer.h>
#include <dns/master_loader.h>

#include <stdint.h>
#include <string.h>

#include <string>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards
#include <sys/socket.h> // for AF_INET/AF_INET6

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

AAAA::AAAA(const std::string& addrstr) {
    if (inet_pton(AF_INET6, addrstr.c_str(), &addr_) != 1) {
        isc_throw(InvalidRdataText,
                  "IN/AAAA RDATA construction from text failed: "
                  "Address cannot be converted: " << addrstr);
    }
}

AAAA::AAAA(MasterLexer& lexer, const Name*,
           MasterLoader::Options, MasterLoaderCallbacks&)
{
    const MasterToken& token = lexer.getNextToken(MasterToken::STRING);
    if (inet_pton(AF_INET6, token.getStringRegion().beg, &addr_) != 1) {
        isc_throw(InvalidRdataText, "Failed to convert '"
                  << token.getString() << "' to IN/AAAA RDATA");
    }
}

AAAA::AAAA(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len != sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/AAAA RDATA construction from wire failed: "
                  "Invalid length: " << rdata_len);
    }
    if (buffer.getLength() - buffer.getPosition() < sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/AAAA RDATA construction from wire failed: "
                  "insufficient buffer length: "
                  << buffer.getLength() - buffer.getPosition());
    }
    buffer.readData(&addr_, sizeof(addr_));
}

AAAA::AAAA(const AAAA& other) : Rdata() {
    memcpy(addr_, other.addr_, sizeof(addr_));
}

void
AAAA::toWire(OutputBuffer& buffer) const {
    buffer.writeData(&addr_, sizeof(addr_));
}

void
AAAA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeData(&addr_, sizeof(addr_));
}

string
AAAA::toText() const {
    char addr_string[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

    if (inet_ntop(AF_INET6, &addr_, addr_string, sizeof(addr_string)) == NULL) {
        isc_throw(Unexpected,
                  "Failed to convert IN/AAAA RDATA to textual IPv6 address");
    }

    return (string(addr_string));
}

int
AAAA::compare(const Rdata& other) const {
    const AAAA& other_a = dynamic_cast<const AAAA&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
