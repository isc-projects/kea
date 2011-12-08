// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

using namespace std;
using namespace isc::dns;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

/// \brief Constructor from string.
///
/// \c rp_str must be formatted as follows:
/// \code <mailbox name> <text name>
/// \endcode
/// where both fields must represent a valid domain name.
///
/// \exception InvalidRdataText The number of RDATA fields (must be 2) is
/// incorrect.
/// \exception Other The constructor of the \c Name class will throw if the
/// given name is invalid.
/// \exception std::bad_alloc Memory allocation for names fails.
RP::RP(const std::string& rp_str) :
    // We cannot construct both names in the initialization list due to the
    // necessary text processing, so we have to initialize them with a dummy
    // name and replace them later.
    mailbox_(Name::ROOT_NAME()), text_(Name::ROOT_NAME())
{
    istringstream iss(rp_str);
    string mailbox_str, text_str;
    iss >> mailbox_str >> text_str;

    // Validation: A valid RP RR must have exactly two fields.
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid RP text: " << rp_str);
    }
    if (!iss.eof()) {
        isc_throw(InvalidRdataText, "Invalid RP text (redundant field): "
                  << rp_str);
    }

    mailbox_ = Name(mailbox_str);
    text_ = Name(text_str);
}

/// \brief Constructor from wire-format data.
///
/// This constructor doesn't check the validity of the second parameter (rdata
/// length) for parsing.
/// If necessary, the caller will check consistency.
///
/// \exception std::bad_alloc Memory allocation for names fails.
/// \exception Other The constructor of the \c Name class will throw if the
/// names in the wire is invalid.
RP::RP(InputBuffer& buffer, size_t) : mailbox_(buffer), text_(buffer) {
}

/// \brief Copy constructor.
///
/// \exception std::bad_alloc Memory allocation fails in copying internal
/// member variables (this should be very rare).
RP::RP(const RP& other) :
    Rdata(), mailbox_(other.mailbox_), text_(other.text_)
{}

/// \brief Convert the \c RP to a string.
///
/// The output of this method is formatted as described in the "from string"
/// constructor (\c RP(const std::string&))).
///
/// \exception std::bad_alloc Internal resource allocation fails.
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
