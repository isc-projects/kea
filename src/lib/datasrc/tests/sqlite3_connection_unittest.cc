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

#include <datasrc/sqlite3_connection.h>
#include <datasrc/data_source.h>

#include <gtest/gtest.h>

using namespace isc::datasrc;
using isc::data::ConstElementPtr;
using isc::data::Element;

namespace {
// Some test data
ConstElementPtr SQLITE_DBFILE_EXAMPLE = Element::fromJSON(
    "{ \"database_file\": \"" TEST_DATA_DIR "/test.sqlite3\"}");
ConstElementPtr SQLITE_DBFILE_EXAMPLE2 = Element::fromJSON(
    "{ \"database_file\": \"" TEST_DATA_DIR "/example2.com.sqlite3\"}");
ConstElementPtr SQLITE_DBFILE_EXAMPLE_ROOT = Element::fromJSON(
    "{ \"database_file\": \"" TEST_DATA_DIR "/test-root.sqlite3\"}");
ConstElementPtr SQLITE_DBFILE_BROKENDB = Element::fromJSON(
    "{ \"database_file\": \"" TEST_DATA_DIR "/brokendb.sqlite3\"}");
ConstElementPtr SQLITE_DBFILE_MEMORY = Element::fromJSON(
    "{ \"database_file\": \":memory:\"}");

// The following file must be non existent and must be non"creatable";
// the sqlite3 library will try to create a new DB file if it doesn't exist,
// so to test a failure case the create operation should also fail.
// The "nodir", a non existent directory, is inserted for this purpose.
ConstElementPtr SQLITE_DBFILE_NOTEXIST = Element::fromJSON(
    "{ \"database_file\": \"" TEST_DATA_DIR "/nodir/notexist\"}");

// Opening works (the content is tested in different tests)
TEST(SQLite3Open, common) {
    EXPECT_NO_THROW(SQLite3Connection conn(SQLITE_DBFILE_EXAMPLE));
}

// Missing config
TEST(SQLite3Open, noConfig) {
    EXPECT_THROW(SQLite3Connection conn(Element::fromJSON("{}")),
                 DataSourceError);
}

// The file can't be opened
TEST(SQLite3Open, notExist) {
    EXPECT_THROW(SQLite3Connection conn(SQLITE_DBFILE_NOTEXIST), SQLite3Error);
}

// It rejects broken DB
TEST(SQLite3Open, brokenDB) {
    EXPECT_THROW(SQLite3Connection conn(SQLITE_DBFILE_BROKENDB), SQLite3Error);
}

// Test we can create the schema on the fly
TEST(SQLite3Open, memoryDB) {
    EXPECT_NO_THROW(SQLite3Connection conn(SQLITE_DBFILE_MEMORY));
}

}
