// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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
            const std::vector<uint8_t>& value) :
        flags_(flags),
        tag_(tag),
        value_(value)
    {}

    uint8_t flags_;
    const std::string tag_;

    // The first byte of this vector contains the length of the rest of
    // the vector. This byte is actually unused and is skipped when
    // reading the vector.
    const detail::CharString value_;
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
    std::vector<uint8_t> value;
    MasterToken token = lexer.getNextToken(MasterToken::QSTRING, true);
    if ((token.getType() != MasterToken::END_OF_FILE) &&
        (token.getType() != MasterToken::END_OF_LINE))
    {
        detail::stringToCharString(token.getStringRegion(), value);
    } else {
        // Convert it into a CharString.
        value.push_back(0);
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

    vector<uint8_t> tag_vec;
    tag_vec.resize(tag_length + 1);
    tag_vec[0] = tag_length;
    buffer.readData(&tag_vec[1], tag_length);
    rdata_len -= tag_length;

    const std::string tag = detail::charStringToString(tag_vec);

    if (rdata_len > 255) {
        isc_throw(InvalidRdataLength,
                  "CAA value field is too long: " << rdata_len);
    }

    vector<uint8_t> value;
    value.resize(rdata_len + 1);
    value[0] = rdata_len;
    if (rdata_len > 0) {
        buffer.readData(&value[1], rdata_len);
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

    if (value.size() > 255) {
        isc_throw(isc::InvalidParameter,
                  "CAA value field is too long: " << value.size());
    }

    std::vector<uint8_t> value_vec;
    value_vec.reserve(value.size() + 1);
    value_vec.push_back(value.size());
    value_vec.insert(value_vec.end(), value.begin(), value.end());

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
    buffer.writeUint8(impl_->tag_.size());
    if (!impl_->tag_.empty()) {
        buffer.writeData(&impl_->tag_[0],
                         impl_->tag_.size());
    }
    if (impl_->value_.size() > 1) {
        buffer.writeData(&impl_->value_[1],
                         impl_->value_.size() - 1);
    }
}

void
CAA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint8(impl_->flags_);
    renderer.writeUint8(impl_->tag_.size());
    if (!impl_->tag_.empty()) {
        renderer.writeData(&impl_->tag_[0],
                           impl_->tag_.size());
    }
    if (impl_->value_.size() > 1) {
        renderer.writeData(&impl_->value_[1],
                           impl_->value_.size() - 1);
    }
}

std::string
CAA::toText() const {
    std::string result;

    result = lexical_cast<std::string>(static_cast<int>(impl_->flags_));
    result += " " + impl_->tag_;
    result += " \"" + detail::charStringToString(impl_->value_) + "\"";

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

    return (detail::compareCharStrings(impl_->value_,
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

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
