// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>
#include <string.h>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/base64.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

void
DHCID::constructFromLexer(MasterLexer& lexer) {
    string digest_txt = lexer.getNextToken(MasterToken::STRING).getString();

    // Whitespace is allowed within base64 text, so read to the end of input.
    string digest_part;
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }
        token.getString(digest_part);
        digest_txt.append(digest_part);
    }
    lexer.ungetToken();

    decodeBase64(digest_txt, digest_);
}

/// \brief Constructor from string.
///
/// \param dhcid_str A base-64 representation of the DHCID binary data.
///
/// \throw InvalidRdataText if the string could not be parsed correctly.
DHCID::DHCID(const std::string& dhcid_str) {
    try {
        std::istringstream iss(dhcid_str);
        MasterLexer lexer;
        lexer.pushSource(iss);

        constructFromLexer(lexer);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for DHCID: "
                      << dhcid_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct DHCID from '" <<
                  dhcid_str << "': " << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of a DHCID RDATA.
///
/// \throw BadValue if the text is not valid base-64.
/// \throw MasterLexer::LexerError General parsing error such as missing field.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
DHCID::DHCID(MasterLexer& lexer, const Name*,
             MasterLoader::Options, MasterLoaderCallbacks&) {
    constructFromLexer(lexer);
}

/// \brief Constructor from wire-format data.
///
/// \param buffer A buffer storing the wire format data.
/// \param rdata_len The length of the RDATA in bytes
DHCID::DHCID(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len == 0) {
        isc_throw(InvalidRdataLength, "Missing DHCID rdata");
    }

    digest_.resize(rdata_len);
    buffer.readData(&digest_[0], rdata_len);
}

/// \brief The copy constructor.
///
/// This trivial copy constructor never throws an exception.
DHCID::DHCID(const DHCID& other) : Rdata(), digest_(other.digest_)
{}

/// \brief Render the \c DHCID in the wire format.
///
/// \param buffer An output buffer to store the wire data.
void
DHCID::toWire(OutputBuffer& buffer) const {
    buffer.writeData(&digest_[0], digest_.size());
}

/// \brief Render the \c DHCID in the wire format into a
/// \c MessageRenderer object.
///
/// \param renderer DNS message rendering context that encapsulates the
/// output buffer in which the \c DHCID is to be stored.
void
DHCID::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeData(&digest_[0], digest_.size());
}

/// \brief Convert the \c DHCID to a string.
///
/// This method returns a \c std::string object representing the \c DHCID.
///
/// \return A string representation of \c DHCID.
string
DHCID::toText() const {
    return (encodeBase64(digest_));
}

/// \brief Compare two instances of \c DHCID RDATA.
///
/// See documentation in \c Rdata.
int
DHCID::compare(const Rdata& other) const {
    const DHCID& other_dhcid = dynamic_cast<const DHCID&>(other);

    size_t this_len = digest_.size();
    size_t other_len = other_dhcid.digest_.size();
    size_t cmplen = min(this_len, other_len);
    int cmp = memcmp(&digest_[0], &other_dhcid.digest_[0], cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

/// \brief Accessor method to get the DHCID digest
///
/// \return A reference to the binary DHCID data
const std::vector<uint8_t>&
DHCID::getDigest() const {
    return (digest_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
