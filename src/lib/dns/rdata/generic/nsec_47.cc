// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <util/encode/base64.h>
#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/nsec_bitmap.h>
#include <dns/rdata/generic/detail/lexer_util.h>

#include <stdio.h>
#include <time.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata::generic::detail::nsec;
using isc::dns::rdata::generic::detail::createNameFromLexer;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct NSECImpl {
    // straightforward representation of NSEC RDATA fields
    NSECImpl(const Name& next, vector<uint8_t> typebits) :
        nextname_(next), typebits_(typebits)
    {}

    Name nextname_;
    vector<uint8_t> typebits_;
};

/// \brief Constructor from string.
///
/// The given string must represent a valid NSEC RDATA.  There
/// can be extra space characters at the beginning or end of the
/// text (which are simply ignored), but other extra text, including
/// a new line, will make the construction fail with an exception.
///
/// The Next Domain Name field must be absolute since there's no
/// parameter that specifies the origin name; if it is not absolute,
/// \c MissingNameOrigin exception will be thrown.  This must not be
/// represented as a quoted string.
///
/// The type mnemonics must be valid, and separated by whitespace. If
/// any invalid mnemonics are found, InvalidRdataText exception is
/// thrown.
///
/// \throw MissingNameOrigin Thrown when the Next Domain Name is not absolute.
/// \throw InvalidRdataText if any fields are out of their valid range.
///
/// \param nsec_str A string containing the RDATA to be created
NSEC::NSEC(const std::string& nsec_str) :
    impl_(NULL)
{
    try {
        std::istringstream ss(nsec_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        const Name origin_name(createNameFromLexer(lexer, NULL));

        vector<uint8_t> typebits;
        buildBitmapsFromLexer("NSEC", lexer, typebits);

        impl_ = new NSECImpl(origin_name, typebits);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText,
                      "Extra input text for NSEC: " << nsec_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct NSEC from '" << nsec_str << "': "
                  << ex.what());
    }
}

NSEC::NSEC(InputBuffer& buffer, size_t rdata_len) {
    const size_t pos = buffer.getPosition();
    const Name nextname(buffer);

    // rdata_len must be sufficiently large to hold non empty bitmap.
    if (rdata_len <= buffer.getPosition() - pos) {
        isc_throw(DNSMessageFORMERR,
                  "NSEC RDATA from wire too short: " << rdata_len << "bytes");
    }
    rdata_len -= (buffer.getPosition() - pos);

    vector<uint8_t> typebits(rdata_len);
    buffer.readData(&typebits[0], rdata_len);
    checkRRTypeBitmaps("NSEC", typebits);

    impl_ = new NSECImpl(nextname, typebits);
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an NSEC RDATA.
///
/// The Next Domain Name field can be non-absolute if \c origin is
/// non-NULL, in which case \c origin is used to make it absolute.  It
/// must not be represented as a quoted string.
///
/// The type mnemonics must be valid, and separated by whitespace. If
/// any invalid mnemonics are found, InvalidRdataText exception is
/// thrown.
///
/// \throw MasterLexer::LexerError General parsing error such as
/// missing field.
/// \throw MissingNameOrigin Thrown when the Next Domain Name is not
/// absolute and \c origin is NULL.
/// \throw InvalidRdataText if any fields are out of their valid range.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin The origin to use with a relative Next Domain Name
/// field
NSEC::NSEC(MasterLexer& lexer, const Name* origin, MasterLoader::Options,
           MasterLoaderCallbacks&)
{
    const Name next_name(createNameFromLexer(lexer, origin));

    vector<uint8_t> typebits;
    buildBitmapsFromLexer("NSEC", lexer, typebits);

    impl_ = new NSECImpl(next_name, typebits);
}

NSEC::NSEC(const NSEC& source) :
    Rdata(), impl_(new NSECImpl(*source.impl_))
{}

NSEC&
NSEC::operator=(const NSEC& source) {
    if (this == &source) {
        return (*this);
    }

    NSECImpl* newimpl = new NSECImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

NSEC::~NSEC() {
    delete impl_;
}

string
NSEC::toText() const {
    ostringstream s;
    s << impl_->nextname_;
    bitmapsToText(impl_->typebits_, s);
    return (s.str());
}

void
NSEC::toWire(OutputBuffer& buffer) const {
    impl_->nextname_.toWire(buffer);
    buffer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

void
NSEC::toWire(AbstractMessageRenderer& renderer) const {
    // Type NSEC is not "well-known", and name compression must be disabled
    // per RFC3597.
    renderer.writeName(impl_->nextname_, false);
    renderer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

const Name&
NSEC::getNextName() const {
    return (impl_->nextname_);
}

int
NSEC::compare(const Rdata& other) const {
    const NSEC& other_nsec = dynamic_cast<const NSEC&>(other);

    int cmp = compareNames(impl_->nextname_, other_nsec.impl_->nextname_);
    if (cmp != 0) {
        return (cmp);
    }

    const size_t this_len = impl_->typebits_.size();
    const size_t other_len = other_nsec.impl_->typebits_.size();
    const size_t cmplen = min(this_len, other_len);
    cmp = memcmp(&impl_->typebits_[0], &other_nsec.impl_->typebits_[0],
                 cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
