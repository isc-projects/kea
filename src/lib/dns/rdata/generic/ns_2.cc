// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <string>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using namespace isc::util;
using isc::dns::rdata::generic::detail::createNameFromLexer;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

/// \brief Constructor from string.
///
/// The given string must represent a valid NS RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The NSDNAME must be absolute since there's no parameter that
/// specifies the origin name; if it is not absolute, \c
/// MissingNameOrigin exception will be thrown.  These must not be
/// represented as a quoted string.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
NS::NS(const std::string& namestr) :
    // Fill in dummy name and replace them soon below.
    nsname_(Name::ROOT_NAME())
{
    try {
        std::istringstream ss(namestr);
        MasterLexer lexer;
        lexer.pushSource(ss);

        nsname_ = createNameFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for NS: "
                      << namestr);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct NS from '" <<
                  namestr << "': " << ex.what());
    }
}

NS::NS(InputBuffer& buffer, size_t) :
    nsname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an NS RDATA.  The NSDNAME field can be
/// non-absolute if \c origin is non-NULL, in which case \c origin is
/// used to make it absolute.  It must not be represented as a quoted
/// string.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and RRTTL constructors if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non NULL, specifies the origin of NSDNAME when it
/// is non-absolute.
NS::NS(MasterLexer& lexer, const Name* origin,
       MasterLoader::Options, MasterLoaderCallbacks&) :
    nsname_(createNameFromLexer(lexer, origin))
{}

NS::NS(const NS& other) :
    Rdata(), nsname_(other.nsname_)
{}

void
NS::toWire(OutputBuffer& buffer) const {
    nsname_.toWire(buffer);
}

void
NS::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(nsname_);
}

string
NS::toText() const {
    return (nsname_.toText());
}

int
NS::compare(const Rdata& other) const {
    const NS& other_ns = dynamic_cast<const NS&>(other);

    return (compareNames(nsname_, other_ns.nsname_));
}

const Name&
NS::getNSName() const {
    return (nsname_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
