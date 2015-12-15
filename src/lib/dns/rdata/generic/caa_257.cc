// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/rdata/generic/detail/char_string.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct CAAImpl {
    // straightforward representation of CAA RDATA fields
    CAAImpl(uint8_t flags, const std::string& tag,
            const detail::CharStringData& value) :
        flags_(flags),
        tag_(tag),
        value_(value)
    {
        if ((sizeof(flags) + 1 + tag_.size() + value_.size()) > 65535) {
            isc_throw(InvalidRdataLength,
                      "CAA Value field is too large: " << value_.size());
        }
    }

    uint8_t flags_;
    const std::string tag_;
    const detail::CharStringData value_;
};

// helper function for string and lexer constructors
CAAImpl*
CAA::constructFromLexer(MasterLexer& lexer) {
    const uint32_t flags =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (flags > 255) {
        isc_throw(InvalidRdataText,
                  "CAA flags field out of range");
    }

    // Tag field must not be empty.
    const std::string tag =
        lexer.getNextToken(MasterToken::STRING).getString();
    if (tag.empty()) {
        isc_throw(InvalidRdataText, "CAA tag field is empty");
    } else if (tag.size() > 255) {
        isc_throw(InvalidRdataText,
                  "CAA tag field is too large: " << tag.size());
    }

    // Value field may be empty.
    detail::CharStringData value;
    MasterToken token = lexer.getNextToken(MasterToken::QSTRING, true);
    if ((token.getType() != MasterToken::END_OF_FILE) &&
        (token.getType() != MasterToken::END_OF_LINE))
    {
        detail::stringToCharStringData(token.getStringRegion(), value);
    }

    return (new CAAImpl(flags, tag, value));
}

/// \brief Constructor from string.
///
/// The given string must represent a valid CAA RDATA.  There can be
/// extra space characters at the beginning or end of the text (which
/// are simply ignored), but other extra text, including a new line,
/// will make the construction fail with an exception.
///
/// The Flags, Tag and Value fields must be within their valid ranges,
/// but are not constrained to the values defined in RFC6844. The Tag
/// field must not be empty.
///
/// \throw InvalidRdataText if any fields are missing, out of their
/// valid ranges, incorrect, or empty.
///
/// \param caa_str A string containing the RDATA to be created
CAA::CAA(const string& caa_str) :
    impl_(NULL)
{
    // We use auto_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the CAAImpl that constructFromLexer() returns.
    std::auto_ptr<CAAImpl> impl_ptr(NULL);

    try {
        std::istringstream ss(caa_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for CAA: "
                      << caa_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct CAA from '" <<
                  caa_str << "': " << ex.what());
    }

    impl_ = impl_ptr.release();
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an CAA RDATA.
///
/// \throw MasterLexer::LexerError General parsing error such as missing
/// field.
/// \throw InvalidRdataText Fields are out of their valid ranges,
/// incorrect, or empty.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
CAA::CAA(MasterLexer& lexer, const Name*,
         MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(constructFromLexer(lexer))
{
}

/// \brief Constructor from InputBuffer.
///
/// The passed buffer must contain a valid CAA RDATA.
///
/// The Flags, Tag and Value fields must be within their valid ranges,
/// but are not constrained to the values defined in RFC6844. The Tag
/// field must not be empty.
CAA::CAA(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 2) {
        isc_throw(InvalidRdataLength, "CAA record too short");
    }

    const uint8_t flags = buffer.readUint8();
    const uint8_t tag_length = buffer.readUint8();
    rdata_len -= 2;
    if (tag_length == 0) {
        isc_throw(InvalidRdataText, "CAA tag field is empty");
    }

    if (rdata_len < tag_length) {
        isc_throw(InvalidRdataLength,
                  "RDATA is too short for CAA tag field");
    }

    std::vector<uint8_t> tag_vec(tag_length);
    buffer.readData(&tag_vec[0], tag_length);
    std::string tag(tag_vec.begin(), tag_vec.end());
    rdata_len -= tag_length;

    detail::CharStringData value;
    value.resize(rdata_len);
    if (rdata_len > 0) {
        buffer.readData(&value[0], rdata_len);
    }

    impl_ = new CAAImpl(flags, tag, value);
}

CAA::CAA(uint8_t flags, const std::string& tag, const std::string& value) :
    impl_(NULL)
{
    if (tag.empty()) {
        isc_throw(isc::InvalidParameter,
                  "CAA tag field is empty");
    } else if (tag.size() > 255) {
        isc_throw(isc::InvalidParameter,
                  "CAA tag field is too large: " << tag.size());
    }

    MasterToken::StringRegion region;
    region.beg = &value[0]; // note std ensures this works even if str is empty
    region.len = value.size();

    detail::CharStringData value_vec;
    detail::stringToCharStringData(region, value_vec);

    impl_ = new CAAImpl(flags, tag, value_vec);
}

CAA::CAA(const CAA& other) :
        Rdata(), impl_(new CAAImpl(*other.impl_))
{}

CAA&
CAA::operator=(const CAA& source) {
    if (this == &source) {
        return (*this);
    }

    CAAImpl* newimpl = new CAAImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

CAA::~CAA() {
    delete impl_;
}

void
CAA::toWire(OutputBuffer& buffer) const {
    buffer.writeUint8(impl_->flags_);

    // The constructors must ensure that the tag field is not empty.
    assert(!impl_->tag_.empty());
    buffer.writeUint8(impl_->tag_.size());
    buffer.writeData(&impl_->tag_[0], impl_->tag_.size());

    if (!impl_->value_.empty()) {
        buffer.writeData(&impl_->value_[0],
                         impl_->value_.size());
    }
}

void
CAA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint8(impl_->flags_);

    // The constructors must ensure that the tag field is not empty.
    assert(!impl_->tag_.empty());
    renderer.writeUint8(impl_->tag_.size());
    renderer.writeData(&impl_->tag_[0], impl_->tag_.size());

    if (!impl_->value_.empty()) {
        renderer.writeData(&impl_->value_[0],
                           impl_->value_.size());
    }
}

std::string
CAA::toText() const {
    std::string result;

    result = lexical_cast<std::string>(static_cast<int>(impl_->flags_));
    result += " " + impl_->tag_;
    result += " \"" + detail::charStringDataToString(impl_->value_) + "\"";

    return (result);
}

int
CAA::compare(const Rdata& other) const {
    const CAA& other_caa = dynamic_cast<const CAA&>(other);

    if (impl_->flags_ < other_caa.impl_->flags_) {
        return (-1);
    } else if (impl_->flags_ > other_caa.impl_->flags_) {
        return (1);
    }

    // Do a case-insensitive compare of the tag strings.
    const int result = boost::ilexicographical_compare
        <std::string, std::string>(impl_->tag_, other_caa.impl_->tag_);
    if (result != 0) {
        return (result);
    }

    return (detail::compareCharStringDatas(impl_->value_,
                                           other_caa.impl_->value_));
}

uint8_t
CAA::getFlags() const {
    return (impl_->flags_);
}

const std::string&
CAA::getTag() const {
    return (impl_->tag_);
}

const std::vector<uint8_t>&
CAA::getValue() const {
    return (impl_->value_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
