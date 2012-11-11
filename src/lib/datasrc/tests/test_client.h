// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef TEST_DATA_SOURCE_CLIENT_H
#define TEST_DATA_SOURCE_CLIENT_H 1

#include <dns/name.h>
#include <dns/rrclass.h>

#include <boost/shared_ptr.hpp>

#include <istream>

namespace isc {
namespace datasrc {
namespace unittest {

// Here we define utility modules for the convenience of tests that create
// a data source client according to the specified conditions.

/// \brief Create an SQLite3 data source client from a zone file.
///
/// This function creates an SQLite3 client for the specified zone containing
/// RRs in the specified zone file.  The zone will be created in the given
/// SQLite3 database file.  The database file does not have to exist; this
/// function will automatically create a new file for the test; if the given
/// file already exists this function overrides the content (so basically the
/// file must be an ephemeral one only for that test case).
///
/// The zone file must be formatted so it's accepted by the dns::masterLoad()
/// function.
///
/// \param zclass The RR class of the zone
/// \param zname The origin name of the zone
/// \param db_file The SQLite3 data base file in which the zone data should be
/// installed.
/// \param zone_file The filename of the zone data in the textual format.
/// \return Newly created \c DataSourceClient using the SQLite3 data source
boost::shared_ptr<DataSourceClient>
createSQLite3Client(dns::RRClass zclass, const dns::Name& zname,
                    const char* const db_file, const char* const zone_file);

/// \brief Create an SQLite3 data source client from a stream.
///
/// This is similar to the other version of the function, but takes an input
/// stream for the zone data.  The stream produces strings as the corresponding
/// dns::masterLoad() function expects.
boost::shared_ptr<DataSourceClient>
createSQLite3Client(dns::RRClass zclass, const dns::Name& zname,
                    const char* const db_file, std::istream& rr_stream);

} // end of unittest
} // end of datasrc
} // end of isc

#endif  // TEST_DATA_SOURCE_CLIENT_H

// Local Variables:
// mode: c++
// End:
