// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include <util/encode/base64.h>
#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <memory>

#include <stdio.h>
#include <time.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct DNSKEYImpl {
    // straightforward representation of DNSKEY RDATA fields
    DNSKEYImpl(uint16_t flags, uint8_t protocol, uint8_t algorithm,
               const vector<uint8_t>& keydata) :
        flags_(flags), protocol_(protocol), algorithm_(algorithm),
        keydata_(keydata)
    {}

    uint16_t flags_;
    uint8_t protocol_;
    uint8_t algorithm_;
    const vector<uint8_t> keydata_;
};

/// \brief Constructor from string.
///
/// The given string must represent a valid DNSKEY RDATA.  There can be
/// extra space characters at the beginning or end of the text (which
/// are simply ignored), but other extra text, including a new line,
/// will make the construction fail with an exception.
///
/// The Protocol and Algorithm fields must be within their valid
/// ranges. The Public Key field must be present and must contain a
/// Base64 encoding of the public key. Whitespace is allowed within the
/// Base64 text.
///
/// It is okay for the key data to be missing.  Note: BIND 9 also accepts
/// DNSKEY missing key data.  While the RFC is silent in this case, and it
/// may be debatable what an implementation should do, but since this field
/// is algorithm dependent and this implementations doesn't reject unknown
/// algorithms, it's lenient here.
///
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
///
/// \param dnskey_str A string containing the RDATA to be created
DNSKEY::DNSKEY(const std::string& dnskey_str) :
    impl_(NULL)
{
    // We use auto_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the DNSKEYImpl that constructFromLexer() returns.
    std::auto_ptr<DNSKEYImpl> impl_ptr(NULL);

    try {
        std::istringstream ss(dnskey_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText,
                      "Extra input text for DNSKEY: " << dnskey_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct DNSKEY from '" << dnskey_str << "': "
                  << ex.what());
    }

    impl_ = impl_ptr.release();
}

/// \brief Constructor from InputBuffer.
///
/// The passed buffer must contain a valid DNSKEY RDATA.
///
/// The Protocol and Algorithm fields are not checked for unknown
/// values.  It is okay for the key data to be missing (see the description
/// of the constructor from string).
DNSKEY::DNSKEY(InputBuffer& buffer, size_t rdata_len) :
    impl_(NULL)
{
    if (rdata_len < 4) {
        isc_throw(InvalidRdataLength, "DNSKEY too short: " << rdata_len);
    }

    const uint16_t flags = buffer.readUint16();
    const uint16_t protocol = buffer.readUint8();
    const uint16_t algorithm = buffer.readUint8();

    rdata_len -= 4;

    vector<uint8_t> keydata;
    // If key data is missing, it's OK. See the API documentation of the
    // constructor.
    if (rdata_len > 0) {
        keydata.resize(rdata_len);
        buffer.readData(&keydata[0], rdata_len);
    }

    impl_ = new DNSKEYImpl(flags, protocol, algorithm, keydata);
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an DNSKEY RDATA.
///
/// See \c DNSKEY::DNSKEY(const std::string&) for description of the
/// expected RDATA fields.
///
/// \throw MasterLexer::LexerError General parsing error such as
/// missing field.
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
DNSKEY::DNSKEY(MasterLexer& lexer, const Name*,
               MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(NULL)
{
    impl_ = constructFromLexer(lexer);
}

DNSKEYImpl*
DNSKEY::constructFromLexer(MasterLexer& lexer) {
    const uint32_t flags = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (flags > 0xffff) {
        isc_throw(InvalidRdataText,
                  "DNSKEY flags out of range: " << flags);
    }

    const uint32_t protocol =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (protocol > 0xff) {
        isc_throw(InvalidRdataText,
                  "DNSKEY protocol out of range: " << protocol);
    }

    const uint32_t algorithm =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (algorithm > 0xff) {
        isc_throw(InvalidRdataText,
                  "DNSKEY algorithm out of range: " << algorithm);
    }

    std::string keydata_str;
    std::string keydata_substr;
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }

        // token is now assured to be of type STRING.

        token.getString(keydata_substr);
        keydata_str.append(keydata_substr);
    }

    lexer.ungetToken();

    vector<uint8_t> keydata;
    // If key data is missing, it's OK. See the API documentation of the
    // constructor.
    if (keydata_str.size() > 0) {
        decodeBase64(keydata_str, keydata);
    }

    return (new DNSKEYImpl(flags, protocol, algorithm, keydata));
}

DNSKEY::DNSKEY(const DNSKEY& source) :
    Rdata(), impl_(new DNSKEYImpl(*source.impl_))
{}

DNSKEY&
DNSKEY::operator=(const DNSKEY& source) {
    if (this == &source) {
        return (*this);
    }

    DNSKEYImpl* newimpl = new DNSKEYImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

DNSKEY::~DNSKEY() {
    delete impl_;
}

string
DNSKEY::toText() const {
    return (boost::lexical_cast<string>(static_cast<int>(impl_->flags_)) +
        " " + boost::lexical_cast<string>(static_cast<int>(impl_->protocol_)) +
        " " + boost::lexical_cast<string>(static_cast<int>(impl_->algorithm_)) +
        " " + encodeBase64(impl_->keydata_));
}

void
DNSKEY::toWire(OutputBuffer& buffer) const {
    buffer.writeUint16(impl_->flags_);
    buffer.writeUint8(impl_->protocol_);
    buffer.writeUint8(impl_->algorithm_);
    buffer.writeData(&impl_->keydata_[0], impl_->keydata_.size());
}

void
DNSKEY::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint16(impl_->flags_);
    renderer.writeUint8(impl_->protocol_);
    renderer.writeUint8(impl_->algorithm_);
    renderer.writeData(&impl_->keydata_[0], impl_->keydata_.size());
}

int
DNSKEY::compare(const Rdata& other) const {
    const DNSKEY& other_dnskey = dynamic_cast<const DNSKEY&>(other);

    if (impl_->flags_ != other_dnskey.impl_->flags_) {
        return (impl_->flags_ < other_dnskey.impl_->flags_ ? -1 : 1);
    }
    if (impl_->protocol_ != other_dnskey.impl_->protocol_) {
        return (impl_->protocol_ < other_dnskey.impl_->protocol_ ? -1 : 1);
    }
    if (impl_->algorithm_ != other_dnskey.impl_->algorithm_) {
        return (impl_->algorithm_ < other_dnskey.impl_->algorithm_ ? -1 : 1);
    }

    const size_t this_len = impl_->keydata_.size();
    const size_t other_len = other_dnskey.impl_->keydata_.size();
    const size_t cmplen = min(this_len, other_len);
    if (cmplen == 0) {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
    const int cmp = memcmp(&impl_->keydata_[0],
                           &other_dnskey.impl_->keydata_[0], cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

uint16_t
DNSKEY::getTag() const {
    if (impl_->algorithm_ == 1) {
        // See RFC 4034 appendix B.1 for why the key data must contain
        // at least 4 bytes with RSA/MD5: 3 trailing bytes to extract
        // the tag from, and 1 byte of exponent length subfield before
        // modulus.
        const int len = impl_->keydata_.size();
        if (len < 4) {
            isc_throw(isc::OutOfRange,
                      "DNSKEY keydata too short for tag extraction");
        }

        return ((impl_->keydata_[len - 3] << 8) + impl_->keydata_[len - 2]);
    }

    uint32_t ac = impl_->flags_;
    ac += (impl_->protocol_ << 8);
    ac += impl_->algorithm_;

    const size_t size = impl_->keydata_.size();
    for (size_t i = 0; i < size; i ++) {
        ac += (i & 1) ? impl_->keydata_[i] : (impl_->keydata_[i] << 8);
    }
    ac += (ac >> 16) & 0xffff;
    return (ac & 0xffff);
}

uint16_t
DNSKEY::getFlags() const {
    return (impl_->flags_);
}

uint8_t
DNSKEY::getAlgorithm() const {
    return (impl_->algorithm_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
