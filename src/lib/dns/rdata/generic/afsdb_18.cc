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
#include <util/strutil.h>

#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace isc::util;
using namespace isc::util::str;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

/// \brief Constructor from string.
///
/// \c afsdb_str must be formatted as follows:
/// \code <subtype> <server name>
/// \endcode
/// where server name field must represent a valid domain name.
///
/// An example of valid string is:
/// \code "1 server.example.com." \endcode
///
/// <b>Exceptions</b>
///
/// \exception InvalidRdataText The number of RDATA fields (must be 2) is
/// incorrect.
/// \exception std::bad_alloc Memory allocation fails.
/// \exception Other The constructor of the \c Name class will throw if the
/// names in the string is invalid.
AFSDB::AFSDB(const std::string& afsdb_str) :
    subtype_(0), server_(Name::ROOT_NAME())
{
    istringstream iss(afsdb_str);

    try {
        const uint32_t subtype = tokenToNum<int32_t, 16>(getToken(iss));
        const Name servername(getToken(iss));

        if (!iss.eof()) {
            isc_throw(InvalidRdataText, "Unexpected input for AFSDB"
                    "RDATA: " << afsdb_str);
        }

        subtype_ = subtype;
        server_ = servername;

    } catch (const StringTokenError& ste) {
        isc_throw(InvalidRdataText, "Invalid AFSDB text: " <<
                  ste.what() << ": " << afsdb_str);
    }
}

/// \brief Constructor from wire-format data.
///
/// This constructor doesn't check the validity of the second parameter (rdata
/// length) for parsing.
/// If necessary, the caller will check consistency.
///
/// \exception std::bad_alloc Memory allocation fails.
/// \exception Other The constructor of the \c Name class will throw if the
/// names in the wire is invalid.
AFSDB::AFSDB(InputBuffer& buffer, size_t) :
    subtype_(buffer.readUint16()), server_(buffer)
{}

/// \brief Copy constructor.
///
/// \exception std::bad_alloc Memory allocation fails in copying internal
/// member variables (this should be very rare).
AFSDB::AFSDB(const AFSDB& other) :
    Rdata(), subtype_(other.subtype_), server_(other.server_)
{}

AFSDB&
AFSDB::operator=(const AFSDB& source) {
    subtype_ = source.subtype_;
    server_ = source.server_;

    return (*this);
}

/// \brief Convert the \c AFSDB to a string.
///
/// The output of this method is formatted as described in the "from string"
/// constructor (\c AFSDB(const std::string&))).
///
/// \exception std::bad_alloc Internal resource allocation fails.
///
/// \return A \c string object that represents the \c AFSDB object.
string
AFSDB::toText() const {
    return (boost::lexical_cast<string>(subtype_) + " " + server_.toText());
}

/// \brief Render the \c AFSDB in the wire format without name compression.
///
/// \exception std::bad_alloc Internal resource allocation fails.
///
/// \param buffer An output buffer to store the wire data.
void
AFSDB::toWire(OutputBuffer& buffer) const {
    buffer.writeUint16(subtype_);
    server_.toWire(buffer);
}

/// \brief Render the \c AFSDB in the wire format with taking into account
/// compression.
///
/// As specified in RFC3597, TYPE AFSDB is not "well-known", the server
/// field (domain name) will not be compressed.
///
/// \exception std::bad_alloc Internal resource allocation fails.
///
/// \param renderer DNS message rendering context that encapsulates the
/// output buffer and name compression information.
void
AFSDB::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint16(subtype_);
    renderer.writeName(server_, false);
}

/// \brief Compare two instances of \c AFSDB RDATA.
///
/// See documentation in \c Rdata.
int
AFSDB::compare(const Rdata& other) const {
    const AFSDB& other_afsdb = dynamic_cast<const AFSDB&>(other);
    if (subtype_ < other_afsdb.subtype_) {
        return (-1);
    } else if (subtype_ > other_afsdb.subtype_) {
        return (1);
    }

    return (compareNames(server_, other_afsdb.server_));
}

const Name&
AFSDB::getServer() const {
    return (server_);
}

uint16_t
AFSDB::getSubtype() const {
    return (subtype_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
