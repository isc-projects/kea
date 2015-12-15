// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

#include <cerrno>
#include <cstring>
#include <string>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards
#include <sys/socket.h> // for AF_INET/AF_INET6

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

namespace {
void
convertToIPv6Addr(const char* src, size_t src_len, void* dst) {
    // See a_1.cc for this check.
    if (src_len != strlen(src)) {
        isc_throw(InvalidRdataText,
                  "Bad IN/AAAA RDATA text: unexpected nul in string: '"
                  << src << "'");
    }
    const int result = inet_pton(AF_INET6, src, dst);
    if (result == 0) {
        isc_throw(InvalidRdataText, "Bad IN/AAAA RDATA text: '" << src << "'");
    } else if (result < 0) {
        isc_throw(isc::Unexpected,
                  "Unexpected failure in parsing IN/AAAA RDATA text: '"
                  << src << "': " << std::strerror(errno));
    }
}
}

/// \brief Constructor from string.
///
/// The given string must be a valid textual representation of an IPv6
/// address as specified in RFC1886.
///
/// No extra character should be contained in \c addrstr other than the
/// textual address.  These include spaces and the nul character.
///
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv6 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param addrstr Textual representation of IPv6 address to be used as the
/// RDATA.
AAAA::AAAA(const std::string& addrstr) {
    convertToIPv6Addr(addrstr.c_str(), addrstr.size(), addr_);
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of a class IN AAAA RDATA.
///
/// The acceptable form of the textual address is generally the same as the
/// string version of the constructor, but this version is slightly more
/// flexible.  See the similar constructor of \c in::A class; the same
/// notes apply here.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv6 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
AAAA::AAAA(MasterLexer& lexer, const Name*,
           MasterLoader::Options, MasterLoaderCallbacks&)
{
    const MasterToken& token = lexer.getNextToken(MasterToken::STRING);
    convertToIPv6Addr(token.getStringRegion().beg, token.getStringRegion().len,
                      addr_);
}

/// \brief Copy constructor.
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

/// \brief Return a textual form of the underlying IPv6 address of the RDATA.
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

    if (inet_ntop(AF_INET6, &addr_, addr_string, sizeof(addr_string))
        == NULL) {
        isc_throw(Unexpected,
                  "Failed to convert IN/AAAA RDATA to textual IPv6 address");
    }

    return (string(addr_string));
}

/// \brief Compare two in::AAAA RDATAs.
///
/// In effect, it compares the two RDATA as an unsigned 128-bit integer.
int
AAAA::compare(const Rdata& other) const {
    const AAAA& other_a = dynamic_cast<const AAAA&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
