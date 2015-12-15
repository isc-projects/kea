// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/hex.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata_pimpl_holder.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct TLSAImpl {
    // straightforward representation of TLSA RDATA fields
    TLSAImpl(uint8_t certificate_usage, uint8_t selector,
             uint8_t matching_type, const vector<uint8_t>& data) :
        certificate_usage_(certificate_usage),
        selector_(selector),
        matching_type_(matching_type),
        data_(data)
    {}

    uint8_t certificate_usage_;
    uint8_t selector_;
    uint8_t matching_type_;
    const vector<uint8_t> data_;
};

// helper function for string and lexer constructors
TLSAImpl*
TLSA::constructFromLexer(MasterLexer& lexer) {
    const uint32_t certificate_usage =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (certificate_usage > 255) {
        isc_throw(InvalidRdataText,
                  "TLSA certificate usage field out of range");
    }

    const uint32_t selector =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (selector > 255) {
        isc_throw(InvalidRdataText,
                  "TLSA selector field out of range");
    }

    const uint32_t matching_type =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (matching_type > 255) {
        isc_throw(InvalidRdataText,
                  "TLSA matching type field out of range");
    }

    std::string certificate_assoc_data;
    std::string data_substr;
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }

        token.getString(data_substr);
        certificate_assoc_data.append(data_substr);
    }
    lexer.ungetToken();

    if (certificate_assoc_data.empty()) {
        isc_throw(InvalidRdataText, "Empty TLSA certificate association data");
    }

    vector<uint8_t> data;
    try {
        decodeHex(certificate_assoc_data, data);
    } catch (const isc::BadValue& e) {
        isc_throw(InvalidRdataText,
                  "Bad TLSA certificate association data: " << e.what());
    }

    return (new TLSAImpl(certificate_usage, selector, matching_type, data));
}

/// \brief Constructor from string.
///
/// The given string must represent a valid TLSA RDATA.  There can be
/// extra space characters at the beginning or end of the text (which
/// are simply ignored), but other extra text, including a new line,
/// will make the construction fail with an exception.
///
/// The Certificate Usage, Selector and Matching Type fields must be
/// within their valid ranges, but are not constrained to the values
/// defined in RFC6698.
///
/// The Certificate Association Data Field field may be absent, but if
/// present it must contain a valid hex encoding of the data. Whitespace
/// is allowed in the hex text.
///
/// \throw InvalidRdataText if any fields are missing, out of their
/// valid ranges, or are incorrect, or Certificate Association Data is
/// not a valid hex string.
///
/// \param tlsa_str A string containing the RDATA to be created
TLSA::TLSA(const string& tlsa_str) :
    impl_(NULL)
{
    // We use a smart pointer here because if there is an exception in
    // this constructor, the destructor is not called and there could be
    // a leak of the TLSAImpl that constructFromLexer() returns.
    RdataPimplHolder<TLSAImpl> impl_ptr;

    try {
        std::istringstream ss(tlsa_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for TLSA: "
                      << tlsa_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct TLSA from '" <<
                  tlsa_str << "': " << ex.what());
    }

    impl_ = impl_ptr.release();
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an TLSA RDATA.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw InvalidRdataText Fields are out of their valid range, or are
/// incorrect, or Certificate Association Data is not a valid hex string.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
TLSA::TLSA(MasterLexer& lexer, const Name*,
             MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(constructFromLexer(lexer))
{
}

/// \brief Constructor from InputBuffer.
///
/// The passed buffer must contain a valid TLSA RDATA.
///
/// The Certificate Usage, Selector and Matching Type fields must be
/// within their valid ranges, but are not constrained to the values
/// defined in RFC6698. It is okay for the certificate association data
/// to be missing (see the description of the constructor from string).
TLSA::TLSA(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 3) {
        isc_throw(InvalidRdataLength, "TLSA record too short");
    }

    const uint8_t certificate_usage = buffer.readUint8();
    const uint8_t selector = buffer.readUint8();
    const uint8_t matching_type = buffer.readUint8();

    vector<uint8_t> data;
    rdata_len -= 3;

    if (rdata_len == 0) {
        isc_throw(InvalidRdataLength,
                  "Empty TLSA certificate association data");
    }

    data.resize(rdata_len);
    buffer.readData(&data[0], rdata_len);

    impl_ = new TLSAImpl(certificate_usage, selector, matching_type, data);
}

TLSA::TLSA(uint8_t certificate_usage, uint8_t selector,
           uint8_t matching_type, const std::string& certificate_assoc_data) :
    impl_(NULL)
{
    if (certificate_assoc_data.empty()) {
        isc_throw(InvalidRdataText, "Empty TLSA certificate association data");
    }

    vector<uint8_t> data;
    try {
        decodeHex(certificate_assoc_data, data);
    } catch (const isc::BadValue& e) {
        isc_throw(InvalidRdataText,
                  "Bad TLSA certificate association data: " << e.what());
    }

    impl_ = new TLSAImpl(certificate_usage, selector, matching_type, data);
}

TLSA::TLSA(const TLSA& other) :
        Rdata(), impl_(new TLSAImpl(*other.impl_))
{}

TLSA&
TLSA::operator=(const TLSA& source) {
    if (this == &source) {
        return (*this);
    }

    TLSAImpl* newimpl = new TLSAImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

TLSA::~TLSA() {
    delete impl_;
}

void
TLSA::toWire(OutputBuffer& buffer) const {
    buffer.writeUint8(impl_->certificate_usage_);
    buffer.writeUint8(impl_->selector_);
    buffer.writeUint8(impl_->matching_type_);

    // The constructors must ensure that the certificate association
    // data field is not empty.
    assert(!impl_->data_.empty());
    buffer.writeData(&impl_->data_[0], impl_->data_.size());
}

void
TLSA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint8(impl_->certificate_usage_);
    renderer.writeUint8(impl_->selector_);
    renderer.writeUint8(impl_->matching_type_);

    // The constructors must ensure that the certificate association
    // data field is not empty.
    assert(!impl_->data_.empty());
    renderer.writeData(&impl_->data_[0], impl_->data_.size());
}

string
TLSA::toText() const {
    // The constructors must ensure that the certificate association
    // data field is not empty.
    assert(!impl_->data_.empty());

    return (lexical_cast<string>(static_cast<int>(impl_->certificate_usage_)) + " " +
            lexical_cast<string>(static_cast<int>(impl_->selector_)) + " " +
            lexical_cast<string>(static_cast<int>(impl_->matching_type_)) + " " +
            encodeHex(impl_->data_));
}

int
TLSA::compare(const Rdata& other) const {
    const TLSA& other_tlsa = dynamic_cast<const TLSA&>(other);

    if (impl_->certificate_usage_ < other_tlsa.impl_->certificate_usage_) {
        return (-1);
    } else if (impl_->certificate_usage_ >
               other_tlsa.impl_->certificate_usage_) {
        return (1);
    }

    if (impl_->selector_ < other_tlsa.impl_->selector_) {
        return (-1);
    } else if (impl_->selector_ > other_tlsa.impl_->selector_) {
        return (1);
    }

    if (impl_->matching_type_ < other_tlsa.impl_->matching_type_) {
        return (-1);
    } else if (impl_->matching_type_ >
               other_tlsa.impl_->matching_type_) {
        return (1);
    }

    const size_t this_len = impl_->data_.size();
    const size_t other_len = other_tlsa.impl_->data_.size();
    const size_t cmplen = min(this_len, other_len);

    if (cmplen > 0) {
        const int cmp = memcmp(&impl_->data_[0],
                               &other_tlsa.impl_->data_[0],
                               cmplen);
        if (cmp != 0) {
            return (cmp);
        }
    }

    if (this_len == other_len) {
        return (0);
    } else if (this_len < other_len) {
        return (-1);
    } else {
        return (1);
    }
}

uint8_t
TLSA::getCertificateUsage() const {
    return (impl_->certificate_usage_);
}

uint8_t
TLSA::getSelector() const {
    return (impl_->selector_);
}

uint8_t
TLSA::getMatchingType() const {
    return (impl_->matching_type_);
}

const std::vector<uint8_t>&
TLSA::getData() const {
    return (impl_->data_);
}

size_t
TLSA::getDataLength() const {
    return (impl_->data_.size());
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
