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

DNSKEY::DNSKEY(const std::string& dnskey_str) :
    impl_(NULL)
{
    try {
        std::istringstream ss(dnskey_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        constructFromLexer(lexer);

        // This elaborate check is done to allow trailing comments in
        // the string.
        for (MasterToken::Type token_type = lexer.getNextToken().getType();
             token_type != MasterToken::END_OF_FILE;
             token_type = lexer.getNextToken().getType())
        {
            if (token_type == MasterToken::END_OF_LINE) {
                continue;
            }

            isc_throw(InvalidRdataText,
                      "Extra input text for DNSKEY: " << dnskey_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct DNSKEY from '" << dnskey_str << "': "
                  << ex.what());
    }
}

DNSKEY::DNSKEY(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 4) {
        isc_throw(InvalidRdataLength, "DNSKEY too short: " << rdata_len);
    }

    uint16_t flags = buffer.readUint16();
    uint16_t protocol = buffer.readUint8();
    uint16_t algorithm = buffer.readUint8();

    rdata_len -= 4;
    vector<uint8_t> keydata(rdata_len);
    buffer.readData(&keydata[0], rdata_len);

    impl_ = new DNSKEYImpl(flags, protocol, algorithm, keydata);
}

DNSKEY::DNSKEY(MasterLexer& lexer, const Name*,
               MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(NULL)
{
    constructFromLexer(lexer);
}

void
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

    std::string keydatastr;
    while (true) {
        const MasterToken& token = lexer.getNextToken();
        if (token.getType() != MasterToken::STRING) {
            break;
        }
        keydatastr.append(token.getString());
    }

    lexer.ungetToken();

    if (keydatastr.size() == 0) {
        isc_throw(InvalidRdataText, "Missing DNSKEY digest");
    }

    vector<uint8_t> keydata;
    decodeBase64(keydatastr, keydata);

    if (algorithm == 1 && keydata.size() < 3) {
        isc_throw(InvalidRdataLength, "DNSKEY keydata too short");
    }

    impl_ = new DNSKEYImpl(flags, protocol, algorithm, keydata);
}

DNSKEY::DNSKEY(const DNSKEY& source) :
    Rdata(), impl_(new DNSKEYImpl(*source.impl_))
{}

DNSKEY&
DNSKEY::operator=(const DNSKEY& source) {
    if (impl_ == source.impl_) {
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

    size_t this_len = impl_->keydata_.size();
    size_t other_len = other_dnskey.impl_->keydata_.size();
    size_t cmplen = min(this_len, other_len);
    int cmp = memcmp(&impl_->keydata_[0], &other_dnskey.impl_->keydata_[0],
                     cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

uint16_t
DNSKEY::getTag() const {
    if (impl_->algorithm_ == 1) {
        int len = impl_->keydata_.size();
        return ((impl_->keydata_[len - 3] << 8) + impl_->keydata_[len - 2]);
    }

    uint32_t ac = impl_->flags_;
    ac += (impl_->protocol_ << 8);
    ac += impl_->algorithm_;

    size_t size = impl_->keydata_.size();
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
