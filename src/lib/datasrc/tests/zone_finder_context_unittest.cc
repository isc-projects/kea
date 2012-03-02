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

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/zone.h>
#include <datasrc/memory_datasrc.h>
#include <datasrc/database.h>
#include <datasrc/sqlite3_accessor.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <cstdlib>

using namespace std;
using namespace isc::dns;
using namespace isc::datasrc;
using boost::shared_ptr;

namespace {

// Commonly used test zone file.
const char* const TEST_ZONE_FILE = TEST_DATA_DIR "/contexttest.zone";

// Convenient shortcut
typedef shared_ptr<DataSourceClient> DataSourceClientPtr;

// This is the type used as the test parameter.  Note that this is
// intentionally a plain old type (i.e. a function pointer), not a class;
// otherwise it could cause initialization fiasco at the instantiation time.
typedef DataSourceClientPtr (*ClientCreator)(RRClass, const Name&);

// Creator for the in-memory client to be tested
DataSourceClientPtr
createInMemoryClient(RRClass zclass, const Name& zname) {
    shared_ptr<InMemoryClient> client(new InMemoryClient);

    shared_ptr<InMemoryZoneFinder> finder(
        new InMemoryZoneFinder(zclass, zname));
    finder->load(TEST_ZONE_FILE);

    client->addZone(finder);

    return (client);
}

// Creator for the SQLite3 client to be tested.  addRRset() is a helper
// subroutine.
void
addRRset(ZoneUpdaterPtr updater, ConstRRsetPtr rrset) {
    updater->addRRset(*rrset);
}

DataSourceClientPtr
createSQLite3Client(RRClass zclass, const Name& zname) {
    // We always begin with an empty template SQLite3 DB file and install
    // the zone data from the zone file to ensure both cases have the
    // same test data.

    const char* const install_cmd = INSTALL_PROG " " TEST_DATA_DIR
        "/rwtest.sqlite3 " TEST_DATA_BUILDDIR "/contexttest.sqlite3.copied";
    if (system(install_cmd) != 0) {
        isc_throw(isc::Unexpected,
                  "Error setting up; command failed: " << install_cmd);
    }

    shared_ptr<SQLite3Accessor> accessor(
        new SQLite3Accessor(TEST_DATA_BUILDDIR "/contexttest.sqlite3.copied",
                            zclass.toText()));
    shared_ptr<DatabaseClient> client(new DatabaseClient(zclass, accessor));

    ZoneUpdaterPtr updater = client->getUpdater(zname, true);
    masterLoad(TEST_ZONE_FILE, zname, zclass, boost::bind(addRRset, updater,
                                                          _1));
    updater->commit();

    return (client);
}

// The test class.  Its parameterized so we can share the test scnearios
// for any concrete data source implementaitons.
class ZoneFinderContextTest :
        public ::testing::TestWithParam<ClientCreator>
{
protected:
    ZoneFinderContextTest() : qclass_(RRClass::IN()), qzone_("example.org") {
        client_ = (*GetParam())(qclass_, qzone_);
    }

    const RRClass qclass_;
    const Name qzone_;
    DataSourceClientPtr client_;
    ZoneFinderPtr finder_;
};

// We test the in-memory and SQLite3 data source implementations.
INSTANTIATE_TEST_CASE_P(, ZoneFinderContextTest,
                        ::testing::Values(createInMemoryClient,
                                          createSQLite3Client));

TEST_P(ZoneFinderContextTest, getAdditional) {
    finder_ = client_->findZone(Name("www.a.example.org")).zone_finder;
    ASSERT_TRUE(finder_);
}

}
