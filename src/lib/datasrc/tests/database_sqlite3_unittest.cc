// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/tests/database_unittest.h>

#include <datasrc/database.h>
#include <datasrc/sqlite3_accessor.h>

#include <exceptions/exceptions.h>

#include <dns/name.h>

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>

#include <cstdlib>
#include <string>

using std::string;

using isc::dns::Name;
using namespace isc::datasrc;
using namespace isc::datasrc::test;

namespace {
boost::shared_ptr<DatabaseAccessor>
createSQLite3Accessor() {
    // To make sure we always have empty diffs table at the beginning of
    // each test, we re-install the writable data source here.
    const char* const install_cmd = INSTALL_PROG " -c " TEST_DATA_COMMONDIR
        "/rwtest.sqlite3 " TEST_DATA_BUILDDIR "/rwtest.sqlite3.copied";
    if (std::system(install_cmd) != 0) {
        // any exception will do, this is failure in test setup, but nice
        // to show the command that fails, and shouldn't be caught
        isc_throw(isc::Exception,
                  "Error setting up; command failed: " << install_cmd);
    }

    boost::shared_ptr<DatabaseAccessor> accessor(
        new SQLite3Accessor(TEST_DATA_BUILDDIR "/rwtest.sqlite3.copied",
                            "IN"));

    accessor->startUpdateZone("example.org.", true);
    string columns[DatabaseAccessor::ADD_COLUMN_COUNT];
    for (int i = 0; TEST_RECORDS[i][0] != NULL; ++i) {
        columns[DatabaseAccessor::ADD_NAME] = TEST_RECORDS[i][0];
        columns[DatabaseAccessor::ADD_REV_NAME] =
            Name(columns[DatabaseAccessor::ADD_NAME]).reverse().toText();
        columns[DatabaseAccessor::ADD_TYPE] = TEST_RECORDS[i][1];
        columns[DatabaseAccessor::ADD_TTL] = TEST_RECORDS[i][2];
        columns[DatabaseAccessor::ADD_SIGTYPE] = TEST_RECORDS[i][3];
        columns[DatabaseAccessor::ADD_RDATA] = TEST_RECORDS[i][4];

        accessor->addRecordToZone(columns);
    }
    // We don't add NSEC3s until we are explicitly told we need them
    // in enableNSEC3(); these would break some non NSEC3 tests.
    accessor->commit();

    return (accessor);
}

void
sqlite3EnableNSEC3(DatabaseAccessor& accessor) {
    accessor.startUpdateZone("example.org.", false);

    // Add NSECPARAM at the zone origin
    for (int i = 0; TEST_NSEC3PARAM_RECORDS[i][0] != NULL; ++i) {
        const string param_columns[DatabaseAccessor::ADD_COLUMN_COUNT] = {
            TEST_NSEC3PARAM_RECORDS[i][0], // name
            Name(param_columns[DatabaseAccessor::ADD_NAME]).reverse().toText(),
            // revname
            TEST_NSEC3PARAM_RECORDS[i][2],   // TTL
            TEST_NSEC3PARAM_RECORDS[i][1],   // RR type
            TEST_NSEC3PARAM_RECORDS[i][3],   // sigtype
            TEST_NSEC3PARAM_RECORDS[i][4] }; // RDATA
        accessor.addRecordToZone(param_columns);
    }

    // Add NSEC3s
    for (int i = 0; TEST_NSEC3_RECORDS[i][0] != NULL; ++i) {
        const string nsec3_columns[DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT] =
            {
                Name(TEST_NSEC3_RECORDS[i][0]).split(0, 1).toText(true),
                TEST_NSEC3_RECORDS[i][2], // TTL
                TEST_NSEC3_RECORDS[i][1], // RR type
                TEST_NSEC3_RECORDS[i][4]  // RDATA
            };
        accessor.addNSEC3RecordToZone(nsec3_columns);
    }

    accessor.commit();
}

const DatabaseClientTestParam sqlite3_param = { createSQLite3Accessor,
                                                sqlite3EnableNSEC3 };

INSTANTIATE_TEST_CASE_P(SQLite3, DatabaseClientTest,
                        ::testing::Values(&sqlite3_param));

INSTANTIATE_TEST_CASE_P(SQLite3, RRsetCollectionTest,
                        ::testing::Values(&sqlite3_param));

INSTANTIATE_TEST_CASE_P(SQLite3, RRsetCollectionAndUpdaterTest,
                        ::testing::Values(&sqlite3_param));
}
