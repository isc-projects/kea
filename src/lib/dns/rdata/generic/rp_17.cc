// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <sstream>

#include <util/buffer.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using isc::dns::rdata::generic::detail::createNameFromLexer;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

// helper function for string and lexer constructors
void RP::constructFromLexer(MasterLexer& lexer, const Name* origin) {
    mailbox_ = createNameFromLexer(lexer, origin);
    text_ = createNameFromLexer(lexer, origin);
}

/// \brief Constructor from string.
///
/// \c rp_str must be formatted as follows:
/// \code <mailbox name> <text name>
/// \endcode
/// where both fields must represent a valid domain name.
///
/// \throw InvalidRdataText The number of RDATA fields (must be 2) is
/// incorrect.
/// \throw Other The constructor of the \c Name class will throw if the
/// given name is invalid.
/// \throw std::bad_alloc Memory allocation for names fails.
RP::RP(const std::string& rp_str) :
    // We cannot construct both names in the initialization list due to the
    // necessary text processing, so we have to initialize them with a dummy
    // name and replace them later.
    mailbox_(Name::ROOT_NAME()), text_(Name::ROOT_NAME())
{
    try {
        std::istringstream ss(rp_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        constructFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for RP: "
                      << rp_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct RP from '" <<
                  rp_str << "': " << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an RP RDATA.  The MAILBOX and TEXT fields can be non-absolute if \c
/// origin is non-NULL, in which case \c origin is used to make them absolute.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and constructors if construction of
/// textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non NULL, specifies the origin of SERVER when it
/// is non-absolute.
RP::RP(MasterLexer& lexer, const Name* origin,
       MasterLoader::Options, MasterLoaderCallbacks&) :
    mailbox_(Name::ROOT_NAME()), text_(Name::ROOT_NAME())
{
    constructFromLexer(lexer, origin);
}

/// \brief Constructor from wire-format data.
///
/// This constructor doesn't check the validity of the second parameter (rdata
/// length) for parsing.
/// If necessary, the caller will check consistency.
///
/// \throw std::bad_alloc Memory allocation for names fails.
/// \throw Other The constructor of the \c Name class will throw if the
/// names in the wire is invalid.
RP::RP(InputBuffer& buffer, size_t) : mailbox_(buffer), text_(buffer) {
}

/// \brief Copy constructor.
///
/// \throw std::bad_alloc Memory allocation fails in copying internal
/// member variables (this should be very rare).
RP::RP(const RP& other) :
    Rdata(), mailbox_(other.mailbox_), text_(other.text_)
{}

/// \brief Convert the \c RP to a string.
///
/// The output of this method is formatted as described in the "from string"
/// constructor (\c RP(const std::string&))).
///
/// \throw std::bad_alloc Internal resource allocation fails.
///
/// \return A \c string object that represents the \c RP object.
std::string
RP::toText() const {
    return (mailbox_.toText() + " " + text_.toText());
}

void
RP::toWire(OutputBuffer& buffer) const {
    mailbox_.toWire(buffer);
    text_.toWire(buffer);
}

void
RP::toWire(AbstractMessageRenderer& renderer) const {
    // Type RP is not "well-known", and name compression must be disabled
    // per RFC3597.
    renderer.writeName(mailbox_, false);
    renderer.writeName(text_, false);
}

int
RP::compare(const Rdata& other) const {
    const RP& other_rp = dynamic_cast<const RP&>(other);

    const int cmp = compareNames(mailbox_, other_rp.mailbox_);
    if (cmp != 0) {
        return (cmp);
    }
    return (compareNames(text_, other_rp.text_));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
