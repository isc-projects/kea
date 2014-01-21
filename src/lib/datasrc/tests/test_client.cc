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

#include <exceptions/exceptions.h>

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/client.h>
#include <datasrc/zone.h>
#include <datasrc/sqlite3_accessor.h>

#include "test_client.h"

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <cstdlib>
#include <istream>
#include <fstream>

using namespace std;

using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace unittest {

namespace {
// A helper subroutine for the SQLite3Client creator.
void
addRRset(ZoneUpdaterPtr updater, ConstRRsetPtr rrset) {
    updater->addRRset(*rrset);
}
}

boost::shared_ptr<DataSourceClient>
createSQLite3Client(RRClass zclass, const Name& zname,
                    const char* const db_file, const char* const zone_file)
{
    ifstream ifs(zone_file, ios_base::in);
    if (ifs.fail()) {
        isc_throw(isc::Unexpected, "Failed to open test zone file: "
                  << zone_file);
    }
    return (createSQLite3Client(zclass, zname, db_file, ifs));
}

boost::shared_ptr<DataSourceClient>
createSQLite3Client(RRClass zclass, const Name& zname,
                    const char* const db_file, istream& rr_stream)
{
    // We always begin with an empty template SQLite3 DB file and install
    // the zone data from the zone file to ensure both cases have the
    // same test data.
    const char* const install_cmd_prefix = INSTALL_PROG " -c " TEST_DATA_COMMONDIR
        "/rwtest.sqlite3 ";
    const string install_cmd = string(install_cmd_prefix) + db_file;
    if (system(install_cmd.c_str()) != 0) {
        isc_throw(isc::Unexpected,
                  "Error setting up; command failed: " << install_cmd);
    }

    boost::shared_ptr<SQLite3Accessor> accessor(
        new SQLite3Accessor(db_file, zclass.toText()));
    boost::shared_ptr<DatabaseClient> client(new DatabaseClient(zclass,
                                                                accessor));

    ZoneUpdaterPtr updater = client->getUpdater(zname, true);
    masterLoad(rr_stream, zname, zclass, boost::bind(addRRset, updater, _1));

    updater->commit();

    return (client);
}

}
}
}
