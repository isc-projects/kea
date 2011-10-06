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
/// \c minfo_str must be formatted as follows:
/// \code <rmailbox name> <emailbox name>
/// \endcode
/// where both fields must represent a valid domain name.
///
/// An example of valid string is:
/// \code "rmail.example.com. email.example.com." \endcode
///
/// <b>Exceptions</b>
///
/// \exception InvalidRdataText The number of RDATA fields (must be 2) is
/// incorrect.
/// \exception std::bad_alloc Memory allocation for names fails.
/// \exception Other The constructor of the \c Name class will throw if the
/// names in the string is invalid.
MINFO::MINFO(const std::string& minfo_str) :
    // We cannot construct both names in the initialization list due to the
    // necessary text processing, so we have to initialize them with a dummy
    // name and replace them later.
    rmailbox_(Name::ROOT_NAME()), emailbox_(Name::ROOT_NAME())
{
    istringstream iss(minfo_str);
    string rmailbox_str, emailbox_str;
    iss >> rmailbox_str >> emailbox_str;

    // Validation: A valid MINFO RR must have exactly two fields.
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid MINFO text: " << minfo_str);
    }
    if (!iss.eof()) {
        isc_throw(InvalidRdataText, "Invalid MINFO text (redundant field): "
                  << minfo_str);
    }

    rmailbox_ = Name(rmailbox_str);
    emailbox_ = Name(emailbox_str);
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
MINFO::MINFO(InputBuffer& buffer, size_t) :
    rmailbox_(buffer), emailbox_(buffer)
{}

/// \brief Copy constructor.
///
/// \exception std::bad_alloc Memory allocation fails in copying internal
/// member variables (this should be very rare).
MINFO::MINFO(const MINFO& other) :
    Rdata(), rmailbox_(other.rmailbox_), emailbox_(other.emailbox_)
{}

/// \brief Convert the \c MINFO to a string.
///
/// The output of this method is formatted as described in the "from string"
/// constructor (\c MINFO(const std::string&))).
///
/// \exception std::bad_alloc Internal resource allocation fails.
///
/// \return A \c string object that represents the \c MINFO object.
std::string
MINFO::toText() const {
    return (rmailbox_.toText() + " " + emailbox_.toText());
}

/// \brief Render the \c MINFO in the wire format without name compression.
///
/// \exception std::bad_alloc Internal resource allocation fails.
///
/// \param buffer An output buffer to store the wire data.
void
MINFO::toWire(OutputBuffer& buffer) const {
    rmailbox_.toWire(buffer);
    emailbox_.toWire(buffer);
}

MINFO&
MINFO::operator=(const MINFO& source) {
    rmailbox_ = source.rmailbox_;
    emailbox_ = source.emailbox_;

    return (*this);
}

/// \brief Render the \c MINFO in the wire format with taking into account
/// compression.
///
/// As specified in RFC3597, TYPE MINFO is "well-known", the rmailbox and
/// emailbox fields (domain names) will be compressed.
///
/// \exception std::bad_alloc Internal resource allocation fails.
///
/// \param renderer DNS message rendering context that encapsulates the
/// output buffer and name compression information.
void
MINFO::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(rmailbox_);
    renderer.writeName(emailbox_);
}

/// \brief Compare two instances of \c MINFO RDATA.
///
/// See documentation in \c Rdata.
int
MINFO::compare(const Rdata& other) const {
    const MINFO& other_minfo = dynamic_cast<const MINFO&>(other);

    const int cmp = compareNames(rmailbox_, other_minfo.rmailbox_);
    if (cmp != 0) {
        return (cmp);
    }
    return (compareNames(emailbox_, other_minfo.emailbox_));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
