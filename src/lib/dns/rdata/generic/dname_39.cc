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
/// The given string must represent a valid DNAME RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The TARGET must be absolute since there's no parameter that specifies
/// the origin name; if it is not absolute, \c MissingNameOrigin
/// exception will be thrown.  These must not be represented as a quoted
/// string.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
DNAME::DNAME(const std::string& namestr) :
    // Fill in dummy name and replace it soon below.
    dname_(Name::ROOT_NAME())
{
    try {
        std::istringstream ss(namestr);
        MasterLexer lexer;
        lexer.pushSource(ss);

        dname_ = createNameFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for DNAME: "
                      << namestr);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct DNAME from '" <<
                  namestr << "': " << ex.what());
    }
}

DNAME::DNAME(InputBuffer& buffer, size_t) :
    dname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of a DNAME RDATA.  The TARGET field can be
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
/// \param origin If non NULL, specifies the origin of TARGET when it
/// is non-absolute.
DNAME::DNAME(MasterLexer& lexer, const Name* origin,
             MasterLoader::Options, MasterLoaderCallbacks&) :
    dname_(createNameFromLexer(lexer, origin))
{}

DNAME::DNAME(const DNAME& other) :
    Rdata(), dname_(other.dname_)
{}

DNAME::DNAME(const Name& dname) :
    dname_(dname)
{}

void
DNAME::toWire(OutputBuffer& buffer) const {
    dname_.toWire(buffer);
}

void
DNAME::toWire(AbstractMessageRenderer& renderer) const {
    // Type DNAME is not "well-known", and name compression must be disabled
    // per RFC3597.
    renderer.writeName(dname_, false);
}

string
DNAME::toText() const {
    return (dname_.toText());
}

int
DNAME::compare(const Rdata& other) const {
    const DNAME& other_dname = dynamic_cast<const DNAME&>(other);

    return (compareNames(dname_, other_dname.dname_));
}

const Name&
DNAME::getDname() const {
    return (dname_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
