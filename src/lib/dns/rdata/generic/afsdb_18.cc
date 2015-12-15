// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <sstream>

#include <util/buffer.h>
#include <util/strutil.h>

#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <boost/lexical_cast.hpp>

#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using isc::dns::rdata::generic::detail::createNameFromLexer;

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
    try {
        std::istringstream ss(afsdb_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        createFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for AFSDB: "
                      << afsdb_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct AFSDB from '" <<
                  afsdb_str << "': " << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an AFSDB RDATA.  The SERVER field can be non-absolute if \c origin
/// is non-NULL, in which case \c origin is used to make it absolute.
/// It must not be represented as a quoted string.
///
/// The SUBTYPE field must be a valid decimal representation of an
/// unsigned 16-bit integer.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and RRTTL constructors if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non NULL, specifies the origin of SERVER when it
/// is non-absolute.
AFSDB::AFSDB(MasterLexer& lexer, const Name* origin,
       MasterLoader::Options, MasterLoaderCallbacks&) :
    subtype_(0), server_(".")
{
    createFromLexer(lexer, origin);
}

void
AFSDB::createFromLexer(MasterLexer& lexer, const Name* origin)
{
    const uint32_t num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (num > 65535) {
        isc_throw(InvalidRdataText, "Invalid AFSDB subtype: " << num);
    }
    subtype_ = static_cast<uint16_t>(num);

    server_ = createNameFromLexer(lexer, origin);
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
    return (lexical_cast<string>(subtype_) + " " + server_.toText());
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
