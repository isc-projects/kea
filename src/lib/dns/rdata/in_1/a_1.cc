// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>
#include <string.h>

#include <cerrno>
#include <cstring>
#include <string>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards
#include <sys/socket.h> // for AF_INET/AF_INET6

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/master_lexer.h>
#include <dns/master_loader_callbacks.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

namespace {
void
convertToIPv4Addr(const char* src, size_t src_len, uint32_t* dst) {
    // This check specifically rejects invalid input that begins with valid
    // address text followed by a nul character (and possibly followed by
    // further garbage).  It cannot be detected by inet_pton().
    //
    // Note that this is private subroutine of the in::A constructors, which
    // pass std::string.size() or StringRegion::len as src_len, so it should
    // be equal to strlen() unless there's an intermediate nul character.
    if (src_len != strlen(src)) {
        isc_throw(InvalidRdataText,
                  "Bad IN/A RDATA text: unexpected nul in string: '"
                  << src << "'");
    }
    const int result = inet_pton(AF_INET, src, dst);
    if (result == 0) {
        isc_throw(InvalidRdataText, "Bad IN/A RDATA text: '" << src << "'");
    } else if (result < 0) {
        isc_throw(isc::Unexpected,
                  "Unexpected failure in parsing IN/A RDATA text: '"
                  << src << "': " << std::strerror(errno));
    }
}
}

/// \brief Constructor from string.
///
/// The given string must be a valid textual representation of an IPv4
/// address as specified in RFC1035, that is, four decimal numbers separated
/// by dots without any embedded spaces.  Note that it excludes abbreviated
/// forms such as "10.1" to mean "10.0.0.1".
///
/// Internally, this implementation uses the standard inet_pton() library
/// function for the AF_INET family to parse and convert the textual
/// representation.  While standard compliant implementations of this function
/// should accept exactly what this constructor expects, specific
/// implementation may behave differently, in which case this constructor
/// will simply accept the result of inet_pton().  In any case, the user of
/// the class shouldn't assume such specific implementation behavior of
/// inet_pton().
///
/// No extra character should be contained in \c addrstr other than the
/// textual address.  These include spaces and the nul character.
///
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv4 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param addrstr Textual representation of IPv4 address to be used as the
/// RDATA.
A::A(const std::string& addrstr) {
    convertToIPv4Addr(addrstr.c_str(), addrstr.size(), &addr_);
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of a class IN A RDATA.
///
/// The acceptable form of the textual address is generally the same as the
/// string version of the constructor, but this version accepts beginning
/// spaces and trailing spaces or other characters.  Trailing non space
/// characters would be considered an invalid form in an RR representation,
/// but handling such errors is not the responsibility of this constructor.
/// It also accepts other unusual syntax that would be considered valid
/// in the context of DNS master file; for example, it accepts an IPv4
/// address surrounded by parentheses, such as "(192.0.2.1)", although it's
/// very unlikely to be used for this type of RDATA.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv4 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
A::A(MasterLexer& lexer, const Name*,
     MasterLoader::Options, MasterLoaderCallbacks&)
{
    const MasterToken& token = lexer.getNextToken(MasterToken::STRING);
    convertToIPv4Addr(token.getStringRegion().beg, token.getStringRegion().len,
                      &addr_);
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

/// \brief Copy constructor.
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

/// \brief Return a textual form of the underlying IPv4 address of the RDATA.
string
A::toText() const {
    char addr_string[sizeof("255.255.255.255")];

    if (inet_ntop(AF_INET, &addr_, addr_string, sizeof(addr_string)) == NULL) {
        isc_throw(Unexpected,
                  "Failed to convert IN/A RDATA to textual IPv4 address");
    }

    return (addr_string);
}

/// \brief Compare two in::A RDATAs.
///
/// In effect, it compares the two RDATA as an unsigned 32-bit integer.
int
A::compare(const Rdata& other) const {
    const A& other_a = dynamic_cast<const A&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}
// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
