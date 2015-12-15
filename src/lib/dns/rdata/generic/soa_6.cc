// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/master_lexer.h>
#include <dns/master_loader.h>
#include <dns/master_loader_callbacks.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/rdata/generic/detail/lexer_util.h>

#include <boost/static_assert.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <sstream>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using isc::dns::rdata::generic::detail::createNameFromLexer;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

SOA::SOA(InputBuffer& buffer, size_t) :
    mname_(buffer), rname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
    buffer.readData(numdata_, sizeof(numdata_));
}

namespace {
void
fillParameters(MasterLexer& lexer, uint8_t numdata[20]) {
    // Copy serial, refresh, retry, expire, minimum.  We accept the extended
    // TTL-compatible style for the latter four.
    OutputBuffer buffer(20);
    buffer.writeUint32(lexer.getNextToken(MasterToken::NUMBER).getNumber());
    for (int i = 0; i < 4; ++i) {
        buffer.writeUint32(RRTTL(lexer.getNextToken(MasterToken::STRING).
                                 getString()).getValue());
    }
    memcpy(numdata,  buffer.getData(), buffer.getLength());
}
}

/// \brief Constructor from string.
///
/// The given string must represent a valid SOA RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The MNAME and RNAME must be absolute since there's no parameter that
/// specifies the origin name; if these are not absolute, \c MissingNameOrigin
/// exception will be thrown.  These must not be represented as a quoted
/// string.
///
/// See the construction that takes \c MasterLexer for other fields.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
SOA::SOA(const std::string& soastr) :
    // Fill in dummy name and replace them soon below.
    mname_(Name::ROOT_NAME()), rname_(Name::ROOT_NAME())
{
    try {
        std::istringstream ss(soastr);
        MasterLexer lexer;
        lexer.pushSource(ss);

        mname_ = createNameFromLexer(lexer, NULL);
        rname_ = createNameFromLexer(lexer, NULL);
        fillParameters(lexer, numdata_);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for SOA: "
                      << soastr);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct SOA from '" <<
                  soastr << "': " << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an SOA RDATA.  The MNAME and RNAME fields can be non absolute if
/// \c origin is non NULL, in which case \c origin is used to make them
/// absolute.  These must not be represented as a quoted string.
///
/// The REFRESH, RETRY, EXPIRE, and MINIMUM fields can be either a valid
/// decimal representation of an unsigned 32-bit integer or other
/// valid textual representation of \c RRTTL such as "1H" (which means 3600).
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and RRTTL constructors if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non NULL, specifies the origin of MNAME and RNAME when
/// they are non absolute.
SOA::SOA(MasterLexer& lexer, const Name* origin,
         MasterLoader::Options, MasterLoaderCallbacks&) :
    mname_(createNameFromLexer(lexer, origin)),
    rname_(createNameFromLexer(lexer, origin))
{
    fillParameters(lexer, numdata_);
}

SOA::SOA(const Name& mname, const Name& rname, uint32_t serial,
         uint32_t refresh, uint32_t retry, uint32_t expire, uint32_t minimum) :
    mname_(mname), rname_(rname)
{
    OutputBuffer b(20);
    b.writeUint32(serial);
    b.writeUint32(refresh);
    b.writeUint32(retry);
    b.writeUint32(expire);
    b.writeUint32(minimum);
    assert(b.getLength() == sizeof(numdata_));
    memcpy(numdata_, b.getData(), sizeof(numdata_));
}

SOA::SOA(const SOA& other) :
    Rdata(), mname_(other.mname_), rname_(other.rname_)
{
    memcpy(numdata_, other.numdata_, sizeof(numdata_));
}

void
SOA::toWire(OutputBuffer& buffer) const {
    mname_.toWire(buffer);
    rname_.toWire(buffer);
    buffer.writeData(numdata_, sizeof(numdata_));
}

void
SOA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(mname_);
    renderer.writeName(rname_);
    renderer.writeData(numdata_, sizeof(numdata_));
}

Serial
SOA::getSerial() const {
    InputBuffer b(numdata_, sizeof(numdata_));
    return (Serial(b.readUint32()));
}

uint32_t
SOA::getMinimum() const {
    // Make sure the buffer access is safe.
    BOOST_STATIC_ASSERT(sizeof(numdata_) ==
                        sizeof(uint32_t) * 4 + sizeof(uint32_t));

    InputBuffer b(&numdata_[sizeof(uint32_t) * 4], sizeof(uint32_t));
    return (b.readUint32());
}

string
SOA::toText() const {
    InputBuffer b(numdata_, sizeof(numdata_));
    uint32_t serial = b.readUint32();
    uint32_t refresh = b.readUint32();
    uint32_t retry = b.readUint32();
    uint32_t expire = b.readUint32();
    uint32_t minimum = b.readUint32();

    return (mname_.toText() + " " + rname_.toText() + " " +
            lexical_cast<string>(serial) + " " +
            lexical_cast<string>(refresh) + " " +
            lexical_cast<string>(retry) + " " +
            lexical_cast<string>(expire) + " " +
            lexical_cast<string>(minimum));
}

int
SOA::compare(const Rdata& other) const {
    const SOA& other_soa = dynamic_cast<const SOA&>(other);

    int order = compareNames(mname_, other_soa.mname_);
    if (order != 0) {
        return (order);
    }

    order = compareNames(rname_, other_soa.rname_);
    if (order != 0) {
        return (order);
    }

    return (memcmp(numdata_, other_soa.numdata_, sizeof(numdata_)));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
