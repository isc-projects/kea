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

#include <config.h>

#include <string>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

MX::MX(InputBuffer& buffer, size_t) :
    preference_(buffer.readUint16()), mxname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

MX::MX(const std::string& mx_str) :
    // Fill in dummy name and replace them soon below.
    preference_(0), mxname_(Name::ROOT_NAME())
{
    try {
        std::istringstream ss(mx_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        const uint32_t num =
            lexer.getNextToken(MasterToken::NUMBER).getNumber();
        if (num > 65535) {
            isc_throw(InvalidRdataText, "Invalid MX preference");
        }
        preference_ = static_cast<uint16_t>(num);

        mxname_ = createNameFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for MX: "
                      << mx_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct MX from '" <<
                  mx_str << "': " << ex.what());
    }
}

MX::MX(MasterLexer& lexer, const Name* origin,
       MasterLoader::Options, MasterLoaderCallbacks&) :
    preference_(0), mxname_(".")
{
    const uint32_t num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (num > 65535) {
        isc_throw(InvalidRdataText, "Invalid MX preference");
    }
    preference_ = static_cast<uint16_t>(num);

    mxname_ = createNameFromLexer(lexer, origin);
}

MX::MX(uint16_t preference, const Name& mxname) :
    preference_(preference), mxname_(mxname)
{}

MX::MX(const MX& other) :
    Rdata(), preference_(other.preference_), mxname_(other.mxname_)
{}

void
MX::toWire(OutputBuffer& buffer) const {
    buffer.writeUint16(preference_);
    mxname_.toWire(buffer);
}

void
MX::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint16(preference_);
    renderer.writeName(mxname_);
}

string
MX::toText() const {
    return (lexical_cast<string>(preference_) + " " + mxname_.toText());
}

int
MX::compare(const Rdata& other) const {
    const MX& other_mx = dynamic_cast<const MX&>(other);

    if (preference_ < other_mx.preference_) {
        return (-1);
    } else if (preference_ > other_mx.preference_) {
        return (1);
    }

    return (compareNames(mxname_, other_mx.mxname_));
}

const Name&
MX::getMXName() const {
    return (mxname_);
}

uint16_t
MX::getMXPref() const {
    return (preference_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
