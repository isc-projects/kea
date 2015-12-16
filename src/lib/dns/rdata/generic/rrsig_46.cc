// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <util/encode/base64.h>
#include <util/buffer.h>
#include <util/time_utilities.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/lexer_util.h>

#include <stdio.h>
#include <time.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;
using isc::dns::rdata::generic::detail::createNameFromLexer;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

namespace {
// This is the minimum necessary length of all wire-format RRSIG RDATA:
// - two 8-bit fields (algorithm and labels)
// - two 16-bit fields (covered and tag)
// - three 32-bit fields (original TTL, expire and inception)
const size_t RRSIG_MINIMUM_LEN = 2 * sizeof(uint8_t) + 2 * sizeof(uint16_t) +
    3 * sizeof(uint32_t);
}

struct RRSIGImpl {
    // straightforward representation of RRSIG RDATA fields
    RRSIGImpl(const RRType& covered, uint8_t algorithm, uint8_t labels,
              uint32_t originalttl, uint32_t timeexpire,
              uint32_t timeinception, uint16_t tag, const Name& signer,
              const vector<uint8_t>& signature) :
        covered_(covered), algorithm_(algorithm), labels_(labels),
        originalttl_(originalttl), timeexpire_(timeexpire),
        timeinception_(timeinception), tag_(tag), signer_(signer),
        signature_(signature)
    {}

    const RRType covered_;
    uint8_t algorithm_;
    uint8_t labels_;
    uint32_t originalttl_;
    uint32_t timeexpire_;
    uint32_t timeinception_;
    uint16_t tag_;
    const Name signer_;
    const vector<uint8_t> signature_;
};

// helper function for string and lexer constructors
RRSIGImpl*
RRSIG::constructFromLexer(MasterLexer& lexer, const Name* origin) {
    const RRType covered(lexer.getNextToken(MasterToken::STRING).getString());
    const uint32_t algorithm =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (algorithm > 0xff) {
        isc_throw(InvalidRdataText, "RRSIG algorithm out of range");
    }
    const uint32_t labels =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (labels > 0xff) {
        isc_throw(InvalidRdataText, "RRSIG labels out of range");
    }
    const uint32_t originalttl =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    const uint32_t timeexpire =
        timeFromText32(lexer.getNextToken(MasterToken::STRING).getString());
    const uint32_t timeinception =
        timeFromText32(lexer.getNextToken(MasterToken::STRING).getString());
    const uint32_t tag =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (tag > 0xffff) {
        isc_throw(InvalidRdataText, "RRSIG key tag out of range");
    }
    const Name& signer = createNameFromLexer(lexer, origin);

    string signature_txt;
    string signature_part;
    // Whitespace is allowed within base64 text, so read to the end of input.
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }
        token.getString(signature_part);
        signature_txt.append(signature_part);
    }
    lexer.ungetToken();

    vector<uint8_t> signature;
    // missing signature is okay
    if (signature_txt.size() > 0) {
        decodeBase64(signature_txt, signature);
    }

    return (new RRSIGImpl(covered, algorithm, labels,
                          originalttl, timeexpire, timeinception,
                          static_cast<uint16_t>(tag), signer, signature));
}

/// \brief Constructor from string.
///
/// The given string must represent a valid RRSIG RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The Signer's Name must be absolute since there's no parameter that
/// specifies the origin name; if this is not absolute, \c MissingNameOrigin
/// exception will be thrown.  This must not be represented as a quoted
/// string.
///
/// See the construction that takes \c MasterLexer for other fields.
///
/// \throw Others Exception from the Name constructor.
/// \throw InvalidRdataText Other general syntax errors.
RRSIG::RRSIG(const std::string& rrsig_str) :
    impl_(NULL)
{
    // We use auto_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the RRSIGImpl that constructFromLexer() returns.
    std::auto_ptr<RRSIGImpl> impl_ptr(NULL);

    try {
        std::istringstream iss(rrsig_str);
        MasterLexer lexer;
        lexer.pushSource(iss);

        impl_ptr.reset(constructFromLexer(lexer, NULL));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for RRSIG: "
                      << rrsig_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct RRSIG from '" <<
                  rrsig_str << "': " << ex.what());
    }

    impl_ = impl_ptr.release();
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an RRSIG RDATA.  The Signer's Name fields can be non absolute if \c
/// origin is non NULL, in which case \c origin is used to make it absolute.
/// This must not be represented as a quoted string.
///
/// The Original TTL field is a valid decimal representation of an unsigned
/// 32-bit integer. Note that alternate textual representations of \c RRTTL,
/// such as "1H" for 3600 seconds, are not allowed here.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name constructor if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non NULL, specifies the origin of Signer's Name when
/// it is non absolute.
RRSIG::RRSIG(MasterLexer& lexer, const Name* origin,
             MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(constructFromLexer(lexer, origin))
{
}

RRSIG::RRSIG(InputBuffer& buffer, size_t rdata_len) {
    size_t pos = buffer.getPosition();

    if (rdata_len < RRSIG_MINIMUM_LEN) {
        isc_throw(InvalidRdataLength, "RRSIG too short");
    }

    RRType covered(buffer);
    uint8_t algorithm = buffer.readUint8();
    uint8_t labels = buffer.readUint8();
    uint32_t originalttl = buffer.readUint32();
    uint32_t timeexpire = buffer.readUint32();
    uint32_t timeinception = buffer.readUint32();
    uint16_t tag = buffer.readUint16();
    Name signer(buffer);

    // rdata_len must be sufficiently large to hold non empty signature data.
    if (rdata_len <= buffer.getPosition() - pos) {
        isc_throw(InvalidRdataLength, "RRSIG too short");
    }
    rdata_len -= (buffer.getPosition() - pos);

    vector<uint8_t> signature(rdata_len);
    buffer.readData(&signature[0], rdata_len);

    impl_ = new RRSIGImpl(covered, algorithm, labels,
                          originalttl, timeexpire, timeinception, tag,
                          signer, signature);
}

RRSIG::RRSIG(const RRSIG& source) :
    Rdata(), impl_(new RRSIGImpl(*source.impl_))
{}

RRSIG&
RRSIG::operator=(const RRSIG& source) {
    if (this == &source) {
        return (*this);
    }

    RRSIGImpl* newimpl = new RRSIGImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

RRSIG::~RRSIG() {
    delete impl_;
}

string
RRSIG::toText() const {
    return (impl_->covered_.toText() +
            " " + boost::lexical_cast<string>(static_cast<int>(impl_->algorithm_))
            + " " + boost::lexical_cast<string>(static_cast<int>(impl_->labels_))
            + " " + boost::lexical_cast<string>(impl_->originalttl_)
            + " " + timeToText32(impl_->timeexpire_)
            + " " + timeToText32(impl_->timeinception_)
            + " " + boost::lexical_cast<string>(impl_->tag_)
            + " " + impl_->signer_.toText()
            + " " + encodeBase64(impl_->signature_));
}

void
RRSIG::toWire(OutputBuffer& buffer) const {
    impl_->covered_.toWire(buffer);
    buffer.writeUint8(impl_->algorithm_);
    buffer.writeUint8(impl_->labels_);
    buffer.writeUint32(impl_->originalttl_);
    buffer.writeUint32(impl_->timeexpire_);
    buffer.writeUint32(impl_->timeinception_);
    buffer.writeUint16(impl_->tag_);
    impl_->signer_.toWire(buffer);
    buffer.writeData(&impl_->signature_[0], impl_->signature_.size());
}

void
RRSIG::toWire(AbstractMessageRenderer& renderer) const {
    impl_->covered_.toWire(renderer);
    renderer.writeUint8(impl_->algorithm_);
    renderer.writeUint8(impl_->labels_);
    renderer.writeUint32(impl_->originalttl_);
    renderer.writeUint32(impl_->timeexpire_);
    renderer.writeUint32(impl_->timeinception_);
    renderer.writeUint16(impl_->tag_);
    renderer.writeName(impl_->signer_, false);
    renderer.writeData(&impl_->signature_[0], impl_->signature_.size());
}

int
RRSIG::compare(const Rdata& other) const {
    const RRSIG& other_rrsig = dynamic_cast<const RRSIG&>(other);

    if (impl_->covered_.getCode() != other_rrsig.impl_->covered_.getCode()) {
        return (impl_->covered_.getCode() <
                other_rrsig.impl_->covered_.getCode() ? -1 : 1);
    }
    if (impl_->algorithm_ != other_rrsig.impl_->algorithm_) {
        return (impl_->algorithm_ < other_rrsig.impl_->algorithm_ ? -1 : 1);
    }
    if (impl_->labels_ != other_rrsig.impl_->labels_) {
        return (impl_->labels_ < other_rrsig.impl_->labels_ ? -1 : 1);
    }
    if (impl_->originalttl_ != other_rrsig.impl_->originalttl_) {
        return (impl_->originalttl_ < other_rrsig.impl_->originalttl_ ?
                -1 : 1);
    }
    if (impl_->timeexpire_ != other_rrsig.impl_->timeexpire_) {
        return (impl_->timeexpire_ < other_rrsig.impl_->timeexpire_ ?
                -1 : 1);
    }
    if (impl_->timeinception_ != other_rrsig.impl_->timeinception_) {
        return (impl_->timeinception_ < other_rrsig.impl_->timeinception_ ?
                -1 : 1);
    }
    if (impl_->tag_ != other_rrsig.impl_->tag_) {
        return (impl_->tag_ < other_rrsig.impl_->tag_ ? -1 : 1);
    }

    int cmp = compareNames(impl_->signer_, other_rrsig.impl_->signer_);
    if (cmp != 0) {
        return (cmp);
    }

    size_t this_len = impl_->signature_.size();
    size_t other_len = other_rrsig.impl_->signature_.size();
    size_t cmplen = min(this_len, other_len);
    cmp = memcmp(&impl_->signature_[0], &other_rrsig.impl_->signature_[0],
                 cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

const RRType&
RRSIG::typeCovered() const {
    return (impl_->covered_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
