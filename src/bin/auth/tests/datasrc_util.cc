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

#include <cc/data.h>

#include <datasrc/client.h>
#include <datasrc/zone.h>
#include <datasrc/factory.h>

#include "datasrc_util.h"

#include <boost/bind.hpp>

#include <istream>

#include <cstdlib>

using namespace std;

using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;

namespace isc {
namespace auth {
namespace unittest {

namespace {
void
addRRset(ZoneUpdaterPtr updater, ConstRRsetPtr rrset) {
    updater->addRRset(*rrset);
}
}

void
createSQLite3DB(RRClass zclass, const Name& zname,
                const char* const db_file, istream& rr_stream)
{
    // We always begin with an empty template SQLite3 DB file and install
    // the zone data from the zone file.
    const char* const install_cmd_prefix = INSTALL_PROG " -c " TEST_DATA_DIR
        "/rwtest.sqlite3 ";
    const string install_cmd = string(install_cmd_prefix) + db_file;
    if (system(install_cmd.c_str()) != 0) {
        isc_throw(isc::Unexpected,
                  "Error setting up; command failed: " << install_cmd);
    }

    DataSourceClientContainer container("sqlite3",
                                        Element::fromJSON(
                                            "{\"database_file\": \"" +
                                            string(db_file) + "\"}"));
    ZoneUpdaterPtr updater = container.getInstance().getUpdater(zname, true);
    masterLoad(rr_stream, zname, zclass, boost::bind(addRRset, updater, _1));
    updater->commit();
}

} // end of unittest
} // end of auth
} // end of isc
