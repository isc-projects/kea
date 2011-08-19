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

#include <vector>

#include <datasrc/sqlite3_accessor.h>

#include <datasrc/data_source.h>

#include <dns/rrclass.h>

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace std;
using namespace isc::datasrc;
using boost::shared_ptr;
using isc::data::ConstElementPtr;
using isc::data::Element;
using isc::dns::RRClass;
using isc::dns::Name;

namespace {
// Some test data
std::string SQLITE_DBFILE_EXAMPLE = TEST_DATA_DIR "/test.sqlite3";
std::string SQLITE_DBFILE_EXAMPLE2 = TEST_DATA_DIR "/example2.com.sqlite3";
std::string SQLITE_DBNAME_EXAMPLE2 = "sqlite3_example2.com.sqlite3";
std::string SQLITE_DBFILE_EXAMPLE_ROOT = TEST_DATA_DIR "/test-root.sqlite3";
std::string SQLITE_DBNAME_EXAMPLE_ROOT = "sqlite3_test-root.sqlite3";
std::string SQLITE_DBFILE_BROKENDB = TEST_DATA_DIR "/brokendb.sqlite3";
std::string SQLITE_DBFILE_MEMORY = ":memory:";

// The following file must be non existent and must be non"creatable";
// the sqlite3 library will try to create a new DB file if it doesn't exist,
// so to test a failure case the create operation should also fail.
// The "nodir", a non existent directory, is inserted for this purpose.
std::string SQLITE_DBFILE_NOTEXIST = TEST_DATA_DIR "/nodir/notexist";

// Opening works (the content is tested in different tests)
TEST(SQLite3Open, common) {
    EXPECT_NO_THROW(SQLite3Database db(SQLITE_DBFILE_EXAMPLE,
                                       RRClass::IN()));
}

// The file can't be opened
TEST(SQLite3Open, notExist) {
    EXPECT_THROW(SQLite3Database db(SQLITE_DBFILE_NOTEXIST,
                                    RRClass::IN()), SQLite3Error);
}

// It rejects broken DB
TEST(SQLite3Open, brokenDB) {
    EXPECT_THROW(SQLite3Database db(SQLITE_DBFILE_BROKENDB,
                                    RRClass::IN()), SQLite3Error);
}

// Test we can create the schema on the fly
TEST(SQLite3Open, memoryDB) {
    EXPECT_NO_THROW(SQLite3Database db(SQLITE_DBFILE_MEMORY,
                                       RRClass::IN()));
}

// Test fixture for querying the db
class SQLite3Access : public ::testing::Test {
public:
    SQLite3Access() {
        initAccessor(SQLITE_DBFILE_EXAMPLE, RRClass::IN());
    }
    // So it can be re-created with different data
    void initAccessor(const std::string& filename, const RRClass& rrclass) {
        db.reset(new SQLite3Database(filename, rrclass));
    }
    // The tested db
    boost::shared_ptr<SQLite3Database> db;
};

// This zone exists in the data, so it should be found
TEST_F(SQLite3Access, getZone) {
    std::pair<bool, int> result(db->getZone(Name("example.com")));
    EXPECT_TRUE(result.first);
    EXPECT_EQ(1, result.second);
}

// But it should find only the zone, nothing below it
TEST_F(SQLite3Access, subZone) {
    EXPECT_FALSE(db->getZone(Name("sub.example.com")).first);
}

// This zone is not there at all
TEST_F(SQLite3Access, noZone) {
    EXPECT_FALSE(db->getZone(Name("example.org")).first);
}

// This zone is there, but in different class
TEST_F(SQLite3Access, noClass) {
    initAccessor(SQLITE_DBFILE_EXAMPLE, RRClass::CH());
    EXPECT_FALSE(db->getZone(Name("example.com")).first);
}

// This tests the iterator context
TEST_F(SQLite3Access, iterator) {
    // Our test zone is conveniently small, but not empty
    initAccessor(SQLITE_DBFILE_EXAMPLE2, RRClass::IN());

    // Get the iterator context
    DatabaseAccessor::IteratorContextPtr
        context(db->getAllRecords(1));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(),
              context);

    const size_t size(5);
    std::string data[size];
    // Get and check the first and only record
    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("example2.com.", data[4]);
    EXPECT_EQ("SOA", data[0]);
    EXPECT_EQ("master.example2.com. admin.example2.com. "
              "1234 3600 1800 2419200 7200", data[3]);
    EXPECT_EQ("3600", data[1]);
    // Check there's no other
    EXPECT_FALSE(context->getNext(data));
}

TEST_F(SQLite3Access, iteratorColumnCount) {
    // Our test zone is conveniently small, but not empty
    initAccessor(SQLITE_DBFILE_EXAMPLE2, RRClass::IN());

    // Get the iterator context
    DatabaseAccessor::IteratorContextPtr
        context(db->getAllRecords(1));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(),
              context);

    std::string data[DatabaseAccessor::COLUMN_COUNT];
    EXPECT_NO_THROW(context->getNext(data));
}

TEST(SQLite3Open, getDBNameExample2) {
    SQLite3Database db(SQLITE_DBFILE_EXAMPLE2, RRClass::IN());
    EXPECT_EQ(SQLITE_DBNAME_EXAMPLE2, db.getDBName());
}

TEST(SQLite3Open, getDBNameExampleROOT) {
    SQLite3Database db(SQLITE_DBFILE_EXAMPLE_ROOT, RRClass::IN());
    EXPECT_EQ(SQLITE_DBNAME_EXAMPLE_ROOT, db.getDBName());
}

// Simple function to cound the number of records for
// any name
void
checkRecordRow(const std::string columns[],
               const std::string& field0,
               const std::string& field1,
               const std::string& field2,
               const std::string& field3,
               const std::string& field4)
{
    EXPECT_EQ(field0, columns[0]);
    EXPECT_EQ(field1, columns[1]);
    EXPECT_EQ(field2, columns[2]);
    EXPECT_EQ(field3, columns[3]);
    EXPECT_EQ(field4, columns[4]);
}

TEST_F(SQLite3Access, getRecords) {
    const std::pair<bool, int> zone_info(db->getZone(Name("example.com")));
    ASSERT_TRUE(zone_info.first);

    const int zone_id = zone_info.second;
    ASSERT_EQ(1, zone_id);

    const size_t column_count = DatabaseAccessor::COLUMN_COUNT;
    std::string columns[column_count];

    DatabaseAccessor::IteratorContextPtr
        context(db->getRecords(Name("foo.bar"), 1));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(),
              context);
    EXPECT_FALSE(context->getNext(columns));
    checkRecordRow(columns, "", "", "", "", "");

    // now try some real searches
    context = db->getRecords(Name("foo.example.com."), zone_id);
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "CNAME", "3600", "",
                   "cnametest.example.org.", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "3600", "CNAME",
                   "CNAME 5 3 3600 20100322084538 20100220084538 33495 "
                   "example.com. FAKEFAKEFAKEFAKE", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "NSEC", "7200", "",
                   "mail.example.com. CNAME RRSIG NSEC", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "7200", "NSEC",
                   "NSEC 5 3 7200 20100322084538 20100220084538 33495 "
                   "example.com. FAKEFAKEFAKEFAKE", "");
    EXPECT_FALSE(context->getNext(columns));
    // with no more records, the array should not have been modified
    checkRecordRow(columns, "RRSIG", "7200", "NSEC",
                   "NSEC 5 3 7200 20100322084538 20100220084538 33495 "
                   "example.com. FAKEFAKEFAKEFAKE", "");

    context = db->getRecords(Name("example.com."), zone_id);
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "SOA", "3600", "",
                   "master.example.com. admin.example.com. "
                   "1234 3600 1800 2419200 7200", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "3600", "SOA",
                   "SOA 5 2 3600 20100322084538 20100220084538 "
                   "33495 example.com. FAKEFAKEFAKEFAKE", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "NS", "1200", "", "dns01.example.com.", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "NS", "3600", "", "dns02.example.com.", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "NS", "1800", "", "dns03.example.com.", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "3600", "NS",
                   "NS 5 2 3600 20100322084538 20100220084538 "
                   "33495 example.com. FAKEFAKEFAKEFAKE", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "MX", "3600", "", "10 mail.example.com.", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "MX", "3600", "",
                   "20 mail.subzone.example.com.", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "3600", "MX",
                   "MX 5 2 3600 20100322084538 20100220084538 "
                   "33495 example.com. FAKEFAKEFAKEFAKE", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "NSEC", "7200", "",
                   "cname-ext.example.com. NS SOA MX RRSIG NSEC DNSKEY", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "7200", "NSEC",
                   "NSEC 5 2 7200 20100322084538 20100220084538 "
                   "33495 example.com. FAKEFAKEFAKEFAKE", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "DNSKEY", "3600", "",
                   "256 3 5 AwEAAcOUBllYc1hf7ND9uDy+Yz1BF3sI0m4q NGV7W"
                   "cTD0WEiuV7IjXgHE36fCmS9QsUxSSOV o1I/FMxI2PJVqTYHkX"
                   "FBS7AzLGsQYMU7UjBZ SotBJ6Imt5pXMu+lEDNy8TOUzG3xm7g"
                   "0qcbW YF6qCEfvZoBtAqi5Rk7Mlrqs8agxYyMx", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "DNSKEY", "3600", "",
                   "257 3 5 AwEAAe5WFbxdCPq2jZrZhlMj7oJdff3W7syJ tbvzg"
                   "62tRx0gkoCDoBI9DPjlOQG0UAbj+xUV 4HQZJStJaZ+fHU5AwV"
                   "NT+bBZdtV+NujSikhd THb4FYLg2b3Cx9NyJvAVukHp/91HnWu"
                   "G4T36 CzAFrfPwsHIrBz9BsaIQ21VRkcmj7DswfI/i DGd8j6b"
                   "qiODyNZYQ+ZrLmF0KIJ2yPN3iO6Zq 23TaOrVTjB7d1a/h31OD"
                   "fiHAxFHrkY3t3D5J R9Nsl/7fdRmSznwtcSDgLXBoFEYmw6p86"
                   "Acv RyoYNcL1SXjaKVLG5jyU3UR+LcGZT5t/0xGf oIK/aKwEN"
                   "rsjcKZZj660b1M=", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "3600", "DNSKEY",
                   "DNSKEY 5 2 3600 20100322084538 20100220084538 "
                   "4456 example.com. FAKEFAKEFAKEFAKE", "");
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "RRSIG", "3600", "DNSKEY",
                   "DNSKEY 5 2 3600 20100322084538 20100220084538 "
                   "33495 example.com. FAKEFAKEFAKEFAKE", "");
    EXPECT_FALSE(context->getNext(columns));
    // getnextrecord returning false should mean array is not altered
    checkRecordRow(columns, "RRSIG", "3600", "DNSKEY",
                   "DNSKEY 5 2 3600 20100322084538 20100220084538 "
                   "33495 example.com. FAKEFAKEFAKEFAKE", "");
}

//
// Commonly used data for update tests
//
const char* const common_expected_data[] = {
    // Test record already stored in the tested sqlite3 DB file.
    "foo.bar.example.com.", "com.example.bar.foo.", "3600", "A", "",
    "192.0.2.1"
};
const char* const new_data[] = {
    // Newly added data commonly used by some of the tests below
    "newdata.example.com.", "com.example.newdata.", "3600", "A", "",
    "192.0.2.1"
};
const char* const deleted_data[] = {
    // Existing data to be removed commonly used by some of the tests below
    "foo.bar.example.com.", "A", "192.0.2.1"
};

class SQLite3Update : public SQLite3Access {
protected:
    SQLite3Update() {
        ASSERT_EQ(0, system(INSTALL_PROG " " TEST_DATA_DIR
                            "/test.sqlite3 "
                            TEST_DATA_BUILDDIR "/test.sqlite3.copied"));
        initAccessor(TEST_DATA_BUILDDIR "/test.sqlite3.copied", RRClass::IN());
        zone_id = db->getZone(Name("example.com")).second;
        another_db.reset(new SQLite3Database(
                             TEST_DATA_BUILDDIR "/test.sqlite3.copied",
                             RRClass::IN()));
        expected_stored.push_back(common_expected_data);
    }

    int zone_id;
    std::string get_columns[DatabaseAccessor::COLUMN_COUNT];
    std::vector<std::string> update_columns;

    vector<const char* const*> expected_stored; // placeholder for checkRecords
    vector<const char* const*> empty_stored; // indicate no corresponding data

    // Another accessor, emulating one running on a different process/thread
    shared_ptr<SQLite3Database> another_db;
    DatabaseAccessor::IteratorContextPtr iterator;
};

void
checkRecords(SQLite3Database& db, int zone_id, const std::string& name,
             vector<const char* const*> expected_rows)
{
    DatabaseAccessor::IteratorContextPtr iterator =
        db.getRecords(Name(name), zone_id);
    std::string columns[DatabaseAccessor::COLUMN_COUNT];
    vector<const char* const*>::const_iterator it = expected_rows.begin();
    while (iterator->getNext(columns)) {
        ASSERT_TRUE(it != expected_rows.end());
        checkRecordRow(columns, (*it)[3], (*it)[2], (*it)[4], (*it)[5], "");
        ++it;
    }
    EXPECT_TRUE(it == expected_rows.end());
}

TEST_F(SQLite3Update, emptyUpdate) {
    // If we do nothing between start and commit, the zone content
    // should be intact.

    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
    zone_id = db->startUpdateZone("example.com.", false).second;
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
    db->commitUpdateZone();
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, flushZone) {
    // With 'replace' being true startUpdateZone() will flush the existing
    // zone content.

    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
    zone_id = db->startUpdateZone("example.com.", true).second;
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);
    db->commitUpdateZone();
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);
}

TEST_F(SQLite3Update, readWhileUpdate) {
    zone_id = db->startUpdateZone("example.com.", true).second;
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);

    // Until commit is done, the other accessor should see the old data
    checkRecords(*another_db, zone_id, "foo.bar.example.com.",
                 expected_stored);

    // Once the changes are committed, the other accessor will see the new
    // data.
    db->commitUpdateZone();
    checkRecords(*another_db, zone_id, "foo.bar.example.com.", empty_stored);
}

TEST_F(SQLite3Update, rollback) {
    zone_id = db->startUpdateZone("example.com.", true).second;
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);

    // Rollback will revert the change made by startUpdateZone(, true).
    db->rollbackUpdateZone();
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, rollbackFailure) {
    // This test emulates a rare scenario of making rollback attempt fail.
    // The iterator is paused in the middle of getting records, which prevents
    // the rollback operation at the end of the test.

    string columns[DatabaseAccessor::COLUMN_COUNT];
    iterator = db->getRecords(Name("example.com"), zone_id);
    EXPECT_TRUE(iterator->getNext(columns));

    db->startUpdateZone("example.com.", true);
    EXPECT_THROW(db->rollbackUpdateZone(), DataSourceError);
}

TEST_F(SQLite3Update, commitConflict) {
    // Start reading the DB by another accessor.  We should stop at a single
    // call to getNextRecord() to keep holding the lock.
    iterator = another_db->getRecords(Name("foo.example.com"), zone_id);
    EXPECT_TRUE(iterator->getNext(get_columns));

    // Due to getNextRecord() above, the other accessor holds a DB lock,
    // which will prevent commit.
    zone_id = db->startUpdateZone("example.com.", true).second;
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);
    EXPECT_THROW(db->commitUpdateZone(), DataSourceError);
    db->rollbackUpdateZone();   // rollback should still succeed

    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, updateConflict) {
    // Similar to the previous case, but this is a conflict with another
    // update attempt.  Note that these two accessors modify disjoint sets
    // of data; sqlite3 only has a coarse-grained lock so we cannot allow
    // these updates to run concurrently.
    EXPECT_TRUE(another_db->startUpdateZone("sql1.example.com.", true).first);
    EXPECT_THROW(db->startUpdateZone("example.com.", true), DataSourceError);
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, duplicateUpdate) {
    db->startUpdateZone("example.com.", false);
    EXPECT_THROW(db->startUpdateZone("example.com.", false), DataSourceError);
}

TEST_F(SQLite3Update, commitWithoutTransaction) {
    EXPECT_THROW(db->commitUpdateZone(), DataSourceError);
}

TEST_F(SQLite3Update, rollbackWithoutTransaction) {
    EXPECT_THROW(db->rollbackUpdateZone(), DataSourceError);
}

TEST_F(SQLite3Update, addRecord) {
    // Before update, there should be no record for this name
    checkRecords(*db, zone_id, "newdata.example.com.", empty_stored);

    zone_id = db->startUpdateZone("example.com.", false).second;
    update_columns.assign(new_data,
                          new_data + DatabaseAccessor::ADD_COLUMN_COUNT);
    db->addRecordToZone(update_columns);

    expected_stored.clear();
    expected_stored.push_back(new_data);
    checkRecords(*db, zone_id, "newdata.example.com.", expected_stored);

    // Commit the change, and confirm the new data is still there.
    db->commitUpdateZone();
    checkRecords(*db, zone_id, "newdata.example.com.", expected_stored);
}

TEST_F(SQLite3Update, addThenRollback) {
    zone_id = db->startUpdateZone("example.com.", false).second;
    update_columns.assign(new_data,
                          new_data + DatabaseAccessor::ADD_COLUMN_COUNT);
    db->addRecordToZone(update_columns);

    expected_stored.clear();
    expected_stored.push_back(new_data);
    checkRecords(*db, zone_id, "newdata.example.com.", expected_stored);

    db->rollbackUpdateZone();
    checkRecords(*db, zone_id, "newdata.example.com.", empty_stored);
}

TEST_F(SQLite3Update, duplicateAdd) {
    const char* const dup_data[] = {
        "foo.bar.example.com.", "com.example.bar.foo.", "3600", "A", "",
        "192.0.2.1"
    };
    expected_stored.clear();
    expected_stored.push_back(dup_data);
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);

    // Adding exactly the same data.  As this backend is "dumb", another
    // row of the same content will be inserted.
    update_columns.assign(dup_data,
                          dup_data + DatabaseAccessor::ADD_COLUMN_COUNT);
    zone_id = db->startUpdateZone("example.com.", false).second;
    db->addRecordToZone(update_columns);
    expected_stored.push_back(dup_data);
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, invalidAdd) {
    // An attempt of add before an explicit start of transaction
    EXPECT_THROW(db->addRecordToZone(update_columns), DataSourceError);

    // Short column vector
    update_columns.clear();
    zone_id = db->startUpdateZone("example.com.", false).second;
    EXPECT_THROW(db->addRecordToZone(update_columns), DataSourceError);

    // Too many columns
    for (int i = 0; i < DatabaseAccessor::ADD_COLUMN_COUNT + 1; ++i) {
        update_columns.push_back("");
    }
    EXPECT_THROW(db->addRecordToZone(update_columns), DataSourceError);
}

TEST_F(SQLite3Update, deleteRecord) {
    zone_id = db->startUpdateZone("example.com.", false).second;

    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);

    update_columns.assign(deleted_data, deleted_data +
                          DatabaseAccessor::DEL_PARAM_COUNT);
    db->deleteRecordInZone(update_columns);
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);

    // Commit the change, and confirm the deleted data still isn't there.
    db->commitUpdateZone();
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);
}

TEST_F(SQLite3Update, deleteThenRollback) {
    zone_id = db->startUpdateZone("example.com.", false).second;

    update_columns.assign(deleted_data, deleted_data +
                          DatabaseAccessor::DEL_PARAM_COUNT);
    db->deleteRecordInZone(update_columns);
    checkRecords(*db, zone_id, "foo.bar.example.com.", empty_stored);

    // Rollback the change, and confirm the data still exists.
    db->rollbackUpdateZone();
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, deleteNonexistent) {
    zone_id = db->startUpdateZone("example.com.", false).second;
    update_columns.assign(deleted_data, deleted_data +
                          DatabaseAccessor::DEL_PARAM_COUNT);

    // Replace the name with a non existent one, then try to delete it.
    // nothing should happen.
    update_columns[0] = "no-such-name.example.com.";
    checkRecords(*db, zone_id, "no-such-name.example.com.", empty_stored);
    db->deleteRecordInZone(update_columns);
    checkRecords(*db, zone_id, "no-such-name.example.com.", empty_stored);

    // Name exists but the RR type is different.  Delete attempt shouldn't
    // delete only by name.
    update_columns.assign(deleted_data, deleted_data +
                          DatabaseAccessor::DEL_PARAM_COUNT);
    update_columns[1] = "AAAA";
    db->deleteRecordInZone(update_columns);
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);

    // Similar to the previous case, but RDATA is different.
    update_columns.assign(deleted_data, deleted_data +
                          DatabaseAccessor::DEL_PARAM_COUNT);
    update_columns[2] = "192.0.2.2";
    db->deleteRecordInZone(update_columns);
    checkRecords(*db, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, invalidDelete) {
    // An attempt of delete before an explicit start of transaction
    EXPECT_THROW(db->deleteRecordInZone(update_columns), DataSourceError);

    // Short column vector
    update_columns.clear();
    zone_id = db->startUpdateZone("example.com.", false).second;
    EXPECT_THROW(db->deleteRecordInZone(update_columns), DataSourceError);

    // Too many parameters
    for (int i = 0; i < DatabaseAccessor::DEL_PARAM_COUNT + 1; ++i) {
        update_columns.push_back("");
    }
    EXPECT_THROW(db->deleteRecordInZone(update_columns), DataSourceError);
}
} // end anonymous namespace
