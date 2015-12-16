// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
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
/// The given string must represent a valid PTR RDATA. There can be
/// extra space characters at the beginning or end of the text (which
/// are simply ignored), but other extra text, including a new line,
/// will make the construction fail with an exception.
///
/// The PTRDNAME must be absolute since there's no parameter that
/// specifies the origin name; if it is not absolute, \c
/// MissingNameOrigin exception will be thrown. These must not be
/// represented as a quoted string.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
PTR::PTR(const std::string& type_str) :
    // Fill in dummy name and replace them soon below.
    ptr_name_(Name::ROOT_NAME())
{
    try {
        std::istringstream ss(type_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        ptr_name_ = createNameFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for PTR: "
                      << type_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct PTR from '" <<
                  type_str << "': " << ex.what());
    }
}

PTR::PTR(InputBuffer& buffer, size_t) :
    ptr_name_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of a PTR RDATA.  The PTRDNAME field can be
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
/// \param origin If non NULL, specifies the origin of PTRDNAME when it
/// is non-absolute.
PTR::PTR(MasterLexer& lexer, const Name* origin,
         MasterLoader::Options, MasterLoaderCallbacks&) :
    ptr_name_(createNameFromLexer(lexer, origin))
{}

PTR::PTR(const PTR& source) :
    Rdata(), ptr_name_(source.ptr_name_)
{}

std::string
PTR::toText() const {
    return (ptr_name_.toText());
}

void
PTR::toWire(OutputBuffer& buffer) const {
    ptr_name_.toWire(buffer);
}

void
PTR::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(ptr_name_);
}

int
PTR::compare(const Rdata& other) const {
    // The compare method normally begins with this dynamic cast.
    const PTR& other_ptr = dynamic_cast<const PTR&>(other);

    return (compareNames(ptr_name_, other_ptr.ptr_name_));

}

const Name&
PTR::getPTRName() const {
    return (ptr_name_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
