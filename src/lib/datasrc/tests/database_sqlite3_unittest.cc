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

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>

#include <cstdlib>
#include <string>

using std::string;

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
        isc_throw(isc::Unexpected,
                  "Error setting up; command failed: " << install_cmd);
    }

    // The SQLite accessor implements all API, so we can use the generic
    // loadTestDataGeneric once accessor is created.
    boost::shared_ptr<DatabaseAccessor> accessor(
        new SQLite3Accessor(TEST_DATA_BUILDDIR "/rwtest.sqlite3.copied",
                            "IN"));
    loadTestDataGeneric(*accessor);

    return (accessor);
}

// The test parameter for the SQLite3 accessor.  We can use enableNSEC3Generic
// as this accessor fully supports NSEC3 related APIs.
const DatabaseClientTestParam sqlite3_param = { createSQLite3Accessor,
                                                enableNSEC3Generic };

INSTANTIATE_TEST_CASE_P(SQLite3, DatabaseClientTest,
                        ::testing::Values(&sqlite3_param));

INSTANTIATE_TEST_CASE_P(SQLite3, RRsetCollectionTest,
                        ::testing::Values(&sqlite3_param));
}
