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

#include "faked_nsec3.h"

#include <datasrc/sqlite3_accessor.h>

#include <datasrc/data_source.h>

#include <dns/rrclass.h>

#include <sqlite3.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;
using namespace isc::datasrc;
using namespace isc::datasrc::test;
using boost::lexical_cast;
using isc::data::ConstElementPtr;
using isc::data::Element;
using isc::dns::RRClass;
using isc::dns::Name;

namespace {
// Some test data
const char* const SQLITE_DBFILE_EXAMPLE = TEST_DATA_DIR "/test.sqlite3";
const char* const SQLITE_DBFILE_EXAMPLE2 =
    TEST_DATA_DIR "/example2.com.sqlite3";
const char* const SQLITE_DBNAME_EXAMPLE2 = "sqlite3_example2.com.sqlite3";
const char* const SQLITE_DBFILE_EXAMPLE_ROOT =
    TEST_DATA_DIR "/test-root.sqlite3";
const char* const SQLITE_DBNAME_EXAMPLE_ROOT = "sqlite3_test-root.sqlite3";
const char* const SQLITE_DBFILE_BROKENDB = TEST_DATA_DIR "/brokendb.sqlite3";
const char* const SQLITE_DBFILE_MEMORY = ":memory:";
const char* const SQLITE_DBFILE_EXAMPLE_ORG =
    TEST_DATA_DIR "/example.org.sqlite3";
const char* const SQLITE_DBFILE_DIFFS = TEST_DATA_DIR "/diffs.sqlite3";
const char* const SQLITE_DBFILE_NEWSCHEMA = TEST_DATA_DIR "/newschema.sqlite3";
const char* const SQLITE_DBFILE_OLDSCHEMA = TEST_DATA_DIR "/oldschema.sqlite3";
const char* const SQLITE_DBFILE_NEW_MINOR_SCHEMA =
    TEST_DATA_DIR "/new_minor_schema.sqlite3";

// The following file must be non existent and must be non"creatable";
// the sqlite3 library will try to create a new DB file if it doesn't exist,
// so to test a failure case the create operation should also fail.
// The "nodir", a non existent directory, is inserted for this purpose.
std::string SQLITE_DBFILE_NOTEXIST = TEST_DATA_DIR "/nodir/notexist";

// new db file, we don't need this to be a std::string, and given the
// raw calls we use it in a const char* is more convenient
const char* SQLITE_NEW_DBFILE = TEST_DATA_BUILDDIR "/newdb.sqlite3";

// Opening works (the content is tested in different tests)
TEST(SQLite3Open, common) {
    EXPECT_NO_THROW(SQLite3Accessor accessor(SQLITE_DBFILE_EXAMPLE, "IN"));
}

// The file can't be opened
TEST(SQLite3Open, notExist) {
    EXPECT_THROW(SQLite3Accessor accessor(SQLITE_DBFILE_NOTEXIST, "IN"),
                 SQLite3Error);
}

// It rejects broken DB
TEST(SQLite3Open, brokenDB) {
    EXPECT_THROW(SQLite3Accessor accessor(SQLITE_DBFILE_BROKENDB, "IN"),
                 SQLite3Error);
}

// Different schema versions
TEST(SQLite3Open, differentSchemaVersions) {
    // If the major version is different from the current one, it should fail.
    EXPECT_THROW(SQLite3Accessor(SQLITE_DBFILE_NEWSCHEMA, "IN"),
                 IncompatibleDbVersion);
    EXPECT_THROW(SQLite3Accessor(SQLITE_DBFILE_OLDSCHEMA, "IN"),
                 IncompatibleDbVersion);

    // Difference in the minor version is okay (as of this test written
    // the current minor version is 0, so we can only test the case with a
    // higher minor version).
    EXPECT_NO_THROW(SQLite3Accessor(SQLITE_DBFILE_NEW_MINOR_SCHEMA, "IN"));
}

// Test we can create the schema on the fly
TEST(SQLite3Open, memoryDB) {
    EXPECT_NO_THROW(SQLite3Accessor accessor(SQLITE_DBFILE_MEMORY, "IN"));
}

// Test fixture for querying the db
class SQLite3AccessorTest : public ::testing::Test {
public:
    SQLite3AccessorTest() {
        initAccessor(SQLITE_DBFILE_EXAMPLE, "IN");
    }
    // So it can be re-created with different data
    void initAccessor(const std::string& filename, const string& rrclass) {
        accessor.reset(new SQLite3Accessor(filename, rrclass));
    }
    // The tested accessor
    boost::shared_ptr<SQLite3Accessor> accessor;
};

// This zone exists in the data, so it should be found
TEST_F(SQLite3AccessorTest, getZone) {
    std::pair<bool, int> result(accessor->getZone("example.com."));
    EXPECT_TRUE(result.first);
    EXPECT_EQ(1, result.second);
}

// But it should find only the zone, nothing below it
TEST_F(SQLite3AccessorTest, subZone) {
    EXPECT_FALSE(accessor->getZone("sub.example.com.").first);
}

// This zone is not there at all
TEST_F(SQLite3AccessorTest, noZone) {
    EXPECT_FALSE(accessor->getZone("example.org.").first);
}

// This zone is there, but in different class
TEST_F(SQLite3AccessorTest, noClass) {
    initAccessor(SQLITE_DBFILE_EXAMPLE, "CH");
    EXPECT_FALSE(accessor->getZone("example.com.").first);
}

// Simple check to test that the sequence is valid.  It gets the next record
// from the iterator, checks that it is not null, then checks the data.
void checkRR(DatabaseAccessor::IteratorContextPtr& context,
     std::string name, std::string ttl, std::string type, std::string rdata) {

    // Mark where we are in the text
    SCOPED_TRACE(name + " " + ttl + " " + type + " " + rdata);

    std::string data[DatabaseAccessor::COLUMN_COUNT];

    // Get next record
    EXPECT_TRUE(context->getNext(data));

    // ... and check expected values
    EXPECT_EQ(name, data[DatabaseAccessor::NAME_COLUMN]);
    EXPECT_EQ(ttl, data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ(type, data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ(rdata, data[DatabaseAccessor::RDATA_COLUMN]);
}

// This tests the iterator context
TEST_F(SQLite3AccessorTest, iterator) {
    // Our test zone is conveniently small, but not empty
    initAccessor(SQLITE_DBFILE_EXAMPLE_ORG, "IN");

    const std::pair<bool, int> zone_info(accessor->getZone("example.org."));
    ASSERT_TRUE(zone_info.first);

    // Get the iterator context
    DatabaseAccessor::IteratorContextPtr
        context(accessor->getAllRecords(zone_info.second));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(), context);

    std::string data[DatabaseAccessor::COLUMN_COUNT];

    checkRR(context, "example.org.", "3600", "MX", "10 mail.example.org.");
    checkRR(context, "example.org.", "3600", "NS", "ns1.example.org.");
    checkRR(context, "example.org.", "3600", "NS", "ns2.example.org.");
    checkRR(context, "example.org.", "3600", "NS", "ns3.example.org.");
    checkRR(context, "example.org.", "3600", "SOA",
            "ns1.example.org. admin.example.org. 1234 3600 1800 2419200 7200");
    checkRR(context, "dname.example.org.", "3600", "DNAME",
            "dname.example.info.");
    checkRR(context, "dname2.foo.example.org.", "3600", "DNAME",
            "dname2.example.info.");
    checkRR(context, "mail.example.org.", "3600", "A", "192.0.2.10");
    checkRR(context, "sub.example.org.", "3600", "NS", "ns.sub.example.org.");
    checkRR(context, "ns.sub.example.org.", "3600", "A", "192.0.2.101");
    checkRR(context, "www.example.org.", "3600", "A", "192.0.2.1");
    checkRR(context, "ns3.example.org.", "3600", "NSEC3",
            "1 1 12 aabbccdd 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG");
    checkRR(context, "ns3.example.org.", "3600", "RRSIG",
            "NSEC3 5 3 3600 20000101000000 20000201000000 "
            "12345 ns3.example.org. FAKEFAKEFAKE");

    // Check there's no other
    EXPECT_FALSE(context->getNext(data));

    // And make sure calling it again won't cause problems.
    EXPECT_FALSE(context->getNext(data));
}

// This tests the iterator through the whole zone returns NSEC3 records as
// well. We test this specifically, as it lives in separate table and needs
// extra handling.
TEST_F(SQLite3AccessorTest, nsec3Iterator) {
    // Get the zone
    const std::pair<bool, int>
        zone_info(accessor->getZone("sql2.example.com."));
    ASSERT_TRUE(zone_info.first);

    // Iterate through it
    DatabaseAccessor::IteratorContextPtr
        context(accessor->getAllRecords(zone_info.second));

    // We just pick a random NSEC3 to check, the check of complete iterator
    // is in the above test. In addition, we count the number of NSEC3, RRSIG
    // and all records, as some kind of check it returns all the data.
    std::string data[DatabaseAccessor::COLUMN_COUNT];

    size_t nsec3count(0), rrsigcount(0), recordcount(0);
    bool nsec3match(false);
    while (context->getNext(data)) {
        if (data[DatabaseAccessor::TYPE_COLUMN] == "NSEC3") {
            nsec3count ++;
            if (data[DatabaseAccessor::NAME_COLUMN] ==
                "1BB7SO0452U1QHL98UISNDD9218GELR5.sql2.example.com.") {
                nsec3match = true;
                EXPECT_EQ("7200", data[DatabaseAccessor::TTL_COLUMN]);
                EXPECT_EQ("1 0 10 FEEDABEE 4KLSVDE8KH8G95VU68R7AHBE1CPQN38J",
                          data[DatabaseAccessor::RDATA_COLUMN]);
            }
        } else if (data[DatabaseAccessor::TYPE_COLUMN] == "RRSIG") {
            rrsigcount ++;
        }
        recordcount ++;
    }

    // We counted everything now, so check there's nothing else to count
    EXPECT_EQ(11, nsec3count);
    EXPECT_EQ(22, rrsigcount);
    EXPECT_EQ(46, recordcount);
    EXPECT_TRUE(nsec3match) << "No NSEC3 found when iterating the zone";
}

// This tests getting NSEC3 records
TEST_F(SQLite3AccessorTest, nsec3) {
    const std::pair<bool, int>
        zone_info(accessor->getZone("sql2.example.com."));
    ASSERT_TRUE(zone_info.first);

    DatabaseAccessor::IteratorContextPtr
        context(accessor->getNSEC3Records("1BB7SO0452U1QHL98UISNDD9218GELR5",
                                          zone_info.second));
    // This relies on specific ordering in the DB. Is it OK?
    // The name field is empty, as well as the sigtype one. This is OK, as
    // both are not needed and the interface allows it.
    checkRR(context, "", "7200", "NSEC3",
            "1 0 10 FEEDABEE 4KLSVDE8KH8G95VU68R7AHBE1CPQN38J");
    checkRR(context, "", "7200", "RRSIG",
            "NSEC3 5 4 7200 20100410172647 20100311172647 63192 "
            "sql2.example.com. gNIVj4T8t51fEU6kOPpvK7HOGBFZGbalN5ZK "
            "mInyrww6UWZsUNdw07ge6/U6HfG+/s61RZ/L is2M6yUWHyXbNbj/"
            "QqwqgadG5dhxTArfuR02 xP600x0fWX8LXzW4yLMdKVxGbzYT+vvGz71o "
            "8gHSY5vYTtothcZQa4BMKhmGQEk=");

    // And that's all
    std::string data[DatabaseAccessor::COLUMN_COUNT];
    EXPECT_FALSE(context->getNext(data));

    // Calling again won't hurt
    EXPECT_FALSE(context->getNext(data));

    // This one should be empty ‒ no data here
    context = accessor->getNSEC3Records("NO_SUCH_HASH", zone_info.second);
    EXPECT_FALSE(context->getNext(data));
    // Still nothing? ;-)
    EXPECT_FALSE(context->getNext(data));
}

// This tests getting a previoeus hash in the NSEC3 namespace of a zone,
// including a wrap-around and asking for a hash that does not exist in the.
// zone at all.
TEST_F(SQLite3AccessorTest, nsec3Previous) {
    // Get the zone
    const std::pair<bool, int>
        zone_info(accessor->getZone("sql2.example.com."));
    ASSERT_TRUE(zone_info.first);

    std::string data[DatabaseAccessor::COLUMN_COUNT];

    // Test a previous hash for something that is in the zone
    // (ensuring it is really there)
    DatabaseAccessor::IteratorContextPtr
        context(accessor->getNSEC3Records("703OOGCKF8VEV1N7U64D1JG19URETN8N",
                                          zone_info.second));
    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("56IEQ664LHDAKVPE2FL179MSM3QAOFVC", accessor->
              findPreviousNSEC3Hash(zone_info.second,
                                    "703OOGCKF8VEV1N7U64D1JG19URETN8N"));

    // Test a previous hash for something that is not in the
    // zone
    context = accessor->getNSEC3Records("702OOGCKF8VEV1N7U64D1JG19URETN8N",
                                        zone_info.second);
    EXPECT_FALSE(context->getNext(data));
    EXPECT_EQ("56IEQ664LHDAKVPE2FL179MSM3QAOFVC", accessor->
              findPreviousNSEC3Hash(zone_info.second,
                                    "702OOGCKF8VEV1N7U64D1JG19URETN8N"));

    // Search at the first item, should wrap around
    context = accessor->getNSEC3Records("1BB7SO0452U1QHL98UISNDD9218GELR5",
                                        zone_info.second);
    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("RKBUCQT8T78GV6QBCGBHCHC019LG73SJ", accessor->
              findPreviousNSEC3Hash(zone_info.second,
                                    "1BB7SO0452U1QHL98UISNDD9218GELR5"));

    // Search before the first item, should wrap around
    context = accessor->getNSEC3Records("0BB7SO0452U1QHL98UISNDD9218GELR5",
                                        zone_info.second);
    EXPECT_FALSE(context->getNext(data));
    EXPECT_EQ("RKBUCQT8T78GV6QBCGBHCHC019LG73SJ", accessor->
              findPreviousNSEC3Hash(zone_info.second,
                                    "0BB7SO0452U1QHL98UISNDD9218GELR5"));

    // Search after the last item (should return the last one)
    context = accessor->getNSEC3Records("RRBUCQT8T78GV6QBCGBHCHC019LG73SJ",
                                        zone_info.second);
    EXPECT_FALSE(context->getNext(data));
    EXPECT_EQ("RKBUCQT8T78GV6QBCGBHCHC019LG73SJ", accessor->
              findPreviousNSEC3Hash(zone_info.second,
                                    "RRBUCQT8T78GV6QBCGBHCHC019LG73SJ"));
}

// Check it throws when we want a previous NSEC3 hash in an unsigned zone
TEST_F(SQLite3AccessorTest, nsec3PreviousUnsigned) {
    // This zone did not look signed in the test file.
    const std::pair<bool, int>
        unsigned_zone_info(accessor->getZone("example.com."));

    EXPECT_THROW(accessor->
                 findPreviousNSEC3Hash(unsigned_zone_info.second,
                                       "0BB7SO0452U1QHL98UISNDD9218GELR5"),
                 DataSourceError);
}

// This tests the difference iterator context

// Test that at attempt to create a difference iterator for a serial number
// that does not exist throws an exception.
TEST_F(SQLite3AccessorTest, diffIteratorNoRecords) {

    // Our test zone is conveniently small, but not empty
    initAccessor(SQLITE_DBFILE_DIFFS, "IN");

    const std::pair<bool, int> zone_info(accessor->getZone("example.org."));
    ASSERT_TRUE(zone_info.first);

    // Get the iterator context.  Difference of version 1 does not exist, so
    // this should throw an exception.
    EXPECT_THROW(accessor->getDiffs(zone_info.second, 1, 1234),
                 isc::datasrc::NoSuchSerial);

    // Check that an invalid high version number also throws an exception.
    EXPECT_THROW(accessor->getDiffs(zone_info.second, 1231, 2234),
                 NoSuchSerial);

    // Check that valid versions - but for the wrong zone which does not hold
    // any records - also throws this exception.
    EXPECT_THROW(accessor->getDiffs(zone_info.second + 42, 1231, 1234),
                 NoSuchSerial);

}

// Try to iterate through a valid sets of differences
TEST_F(SQLite3AccessorTest, diffIteratorSequences) {
    std::string data[DatabaseAccessor::COLUMN_COUNT];

    // Our test zone is conveniently small, but not empty
    initAccessor(SQLITE_DBFILE_DIFFS, "IN");
    const std::pair<bool, int> zone_info(accessor->getZone("example.org."));
    ASSERT_TRUE(zone_info.first);


    // Check the difference sequence 1230-1231 (two adjacent differences)
    // Get the iterator context
    DatabaseAccessor::IteratorContextPtr
        context1(accessor->getDiffs(zone_info.second, 1230, 1231));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(), context1);

    // Change: 1230-1231
    checkRR(context1, "example.org.", "1800", "SOA",
            "ns1.example.org. admin.example.org. 1230 3600 1800 2419200 7200");
    checkRR(context1, "example.org.", "3600", "SOA",
            "ns1.example.org. admin.example.org. 1231 3600 1800 2419200 7200");

    // Check there's no other and that calling it again after no records doesn't
    // cause problems.
    EXPECT_FALSE(context1->getNext(data));
    EXPECT_FALSE(context1->getNext(data));


    // Check that the difference sequence 1231-1233 (two separate difference
    // sequences) is OK.
    DatabaseAccessor::IteratorContextPtr
        context2(accessor->getDiffs(zone_info.second, 1231, 1233));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(), context2);

    // Change 1231-1232
    checkRR(context2, "example.org.", "3600", "SOA",
            "ns1.example.org. admin.example.org. 1231 3600 1800 2419200 7200");
    checkRR(context2, "unused.example.org.", "3600", "A", "192.0.2.102");
    checkRR(context2, "example.org.", "3600", "SOA",
            "ns1.example.org. admin.example.org. 1232 3600 1800 2419200 7200");

    // Change: 1232-1233
    checkRR(context2, "example.org.", "3600", "SOA",
            "ns1.example.org. admin.example.org. 1232 3600 1800 2419200 7200");
    checkRR(context2, "example.org.", "3600", "SOA",
            "ns1.example.org. admin.example.org. 1233 3600 1800 2419200 7200");
    checkRR(context2, "sub.example.org.", "3600", "NS", "ns.sub.example.org.");
    checkRR(context2, "ns.sub.example.org.", "3600", "A", "192.0.2.101");

    // Check there's no other and that calling it again after no records doesn't
    // cause problems.
    EXPECT_FALSE(context2->getNext(data));
    EXPECT_FALSE(context2->getNext(data));


    // Check that the difference sequence 4294967280 to 1230 (serial number
    // rollover) is OK
    DatabaseAccessor::IteratorContextPtr
        context3(accessor->getDiffs(zone_info.second, 4294967280U, 1230));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(), context3);

    // Change 4294967280 to 1230.
    checkRR(context3, "example.org.", "3600", "SOA",
            "ns1.example.org. admin.example.org. 4294967280 3600 1800 2419200 7200");
    checkRR(context3, "www.example.org.", "3600", "A", "192.0.2.31");
    checkRR(context3, "example.org.", "1800", "SOA",
            "ns1.example.org. admin.example.org. 1230 3600 1800 2419200 7200");
    checkRR(context3, "www.example.org.", "3600", "A", "192.0.2.21");

    EXPECT_FALSE(context3->getNext(data));
    EXPECT_FALSE(context3->getNext(data));


    // Check the difference sequence 1233-1231 (versions in wrong order).  This
    // should give an empty difference set.
    DatabaseAccessor::IteratorContextPtr
        context4(accessor->getDiffs(zone_info.second, 1233, 1231));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(), context2);

    EXPECT_FALSE(context4->getNext(data));
    EXPECT_FALSE(context4->getNext(data));
}

TEST(SQLite3Open, getDBNameExample2) {
    SQLite3Accessor accessor(SQLITE_DBFILE_EXAMPLE2, "IN");
    EXPECT_EQ(SQLITE_DBNAME_EXAMPLE2, accessor.getDBName());
}

TEST(SQLite3Open, getDBNameExampleROOT) {
    SQLite3Accessor accessor(SQLITE_DBFILE_EXAMPLE_ROOT, "IN");
    EXPECT_EQ(SQLITE_DBNAME_EXAMPLE_ROOT, accessor.getDBName());
}

// Simple function to match records
void
checkRecordRow(const std::string columns[],
               const std::string& field0, // for type
               const std::string& field1, // for TTL
               const std::string& field2, // for "sigtype"
               const std::string& field3, // for rdata
               const std::string& field4) // for name
{
    EXPECT_EQ(field0, columns[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ(field1, columns[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ(field2, columns[DatabaseAccessor::SIGTYPE_COLUMN]);
    EXPECT_EQ(field3, columns[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ(field4, columns[DatabaseAccessor::NAME_COLUMN]);
}

TEST_F(SQLite3AccessorTest, getRecords) {
    const std::pair<bool, int> zone_info(accessor->getZone("example.com."));
    ASSERT_TRUE(zone_info.first);

    const int zone_id = zone_info.second;
    ASSERT_EQ(1, zone_id);

    std::string columns[DatabaseAccessor::COLUMN_COUNT];

    DatabaseAccessor::IteratorContextPtr
        context(accessor->getRecords("foo.bar", 1));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(),
              context);
    EXPECT_FALSE(context->getNext(columns));
    checkRecordRow(columns, "", "", "", "", "");

    // now try some real searches
    context = accessor->getRecords("foo.example.com.", zone_id);
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

    context = accessor->getRecords("example.com.", zone_id);
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

    // check that another getNext does not cause problems
    EXPECT_FALSE(context->getNext(columns));

    // Try searching for subdomain
    // There's foo.bar.example.com in the data
    context = accessor->getRecords("bar.example.com.", zone_id, true);
    ASSERT_TRUE(context->getNext(columns));
    checkRecordRow(columns, "A", "3600", "", "192.0.2.1", "");
    EXPECT_FALSE(context->getNext(columns));
    // But we shouldn't match mix.example.com here
    context = accessor->getRecords("ix.example.com.", zone_id, true);
    EXPECT_FALSE(context->getNext(columns));
}

TEST_F(SQLite3AccessorTest, findPrevious) {
    EXPECT_EQ("dns01.example.com.",
              accessor->findPreviousName(1, "com.example.dns02."));
    // A name that doesn't exist
    EXPECT_EQ("dns01.example.com.",
              accessor->findPreviousName(1, "com.example.dns01x."));
    // Largest name
    EXPECT_EQ("www.example.com.",
              accessor->findPreviousName(1, "com.example.wwww"));
    // Out of zone after the last name
    EXPECT_EQ("www.example.com.",
              accessor->findPreviousName(1, "org.example."));
    // Case insensitive?
    EXPECT_EQ("dns01.example.com.",
              accessor->findPreviousName(1, "com.exaMple.DNS02."));
    // A name that doesn't exist
    EXPECT_EQ("dns01.example.com.",
              accessor->findPreviousName(1, "com.exaMple.DNS01X."));
    // The DB contains foo.bar.example.com., which would be in between
    // these two names. However, that one does not have an NSEC record,
    // which is how this database recognizes glue data, so it should
    // be skipped.
    EXPECT_EQ("example.com.",
              accessor->findPreviousName(1, "com.example.cname-ext."));
    // Throw when we are before the origin
    EXPECT_THROW(accessor->findPreviousName(1, "com.example."),
                 isc::NotImplemented);
    EXPECT_THROW(accessor->findPreviousName(1, "a.example."),
                 isc::NotImplemented);
}

TEST_F(SQLite3AccessorTest, findPreviousNoData) {
    // This one doesn't hold any NSEC records, so it shouldn't work
    // The underlying DB/data don't support DNSSEC, so it's not implemented
    // (does it make sense? Or different exception here?)
    EXPECT_THROW(accessor->findPreviousName(3, "com.example.sql2.www."),
                 isc::NotImplemented);
}

// Test fixture for creating a db that automatically deletes it before start,
// and when done
class SQLite3Create : public ::testing::Test {
public:
    SQLite3Create() {
        remove(SQLITE_NEW_DBFILE);
    }

    ~SQLite3Create() {
        remove(SQLITE_NEW_DBFILE);
    }
};

bool isReadable(const char* filename) {
    return (std::ifstream(filename).is_open());
}

TEST_F(SQLite3Create, creationtest) {
    ASSERT_FALSE(isReadable(SQLITE_NEW_DBFILE));
    // Should simply be created
    SQLite3Accessor accessor(SQLITE_NEW_DBFILE, "IN");
    ASSERT_TRUE(isReadable(SQLITE_NEW_DBFILE));
}

TEST_F(SQLite3Create, emptytest) {
    ASSERT_FALSE(isReadable(SQLITE_NEW_DBFILE));

    // open one manualle
    sqlite3* db;
    ASSERT_EQ(SQLITE_OK, sqlite3_open(SQLITE_NEW_DBFILE, &db));

    // empty, but not locked, so creating it now should work
    SQLite3Accessor accessor2(SQLITE_NEW_DBFILE, "IN");

    sqlite3_close(db);

    // should work now that we closed it
    SQLite3Accessor accessor3(SQLITE_NEW_DBFILE, "IN");
}

TEST_F(SQLite3Create, lockedtest) {
    ASSERT_FALSE(isReadable(SQLITE_NEW_DBFILE));

    // open one manually
    sqlite3* db;
    ASSERT_EQ(SQLITE_OK, sqlite3_open(SQLITE_NEW_DBFILE, &db));
    sqlite3_exec(db, "BEGIN EXCLUSIVE TRANSACTION", NULL, NULL, NULL);

    // should not be able to open it
    EXPECT_THROW(SQLite3Accessor accessor2(SQLITE_NEW_DBFILE, "IN"),
                 SQLite3Error);

    sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, NULL);

    // should work now that we closed it
    SQLite3Accessor accessor3(SQLITE_NEW_DBFILE, "IN");
}

TEST_F(SQLite3AccessorTest, clone) {
    boost::shared_ptr<DatabaseAccessor> cloned = accessor->clone();
    EXPECT_EQ(accessor->getDBName(), cloned->getDBName());

    // The cloned accessor should have a separate connection and search
    // context, so it should be able to perform search in concurrent with
    // the original accessor.
    string columns1[DatabaseAccessor::COLUMN_COUNT];
    string columns2[DatabaseAccessor::COLUMN_COUNT];

    const std::pair<bool, int> zone_info1(
        accessor->getZone("example.com."));
    DatabaseAccessor::IteratorContextPtr iterator1 =
        accessor->getRecords("foo.example.com.", zone_info1.second);
    const std::pair<bool, int> zone_info2(
        accessor->getZone("example.com."));
    DatabaseAccessor::IteratorContextPtr iterator2 =
        cloned->getRecords("foo.example.com.", zone_info2.second);

    ASSERT_TRUE(iterator1->getNext(columns1));
    checkRecordRow(columns1, "CNAME", "3600", "", "cnametest.example.org.",
                   "");

    ASSERT_TRUE(iterator2->getNext(columns2));
    checkRecordRow(columns2, "CNAME", "3600", "", "cnametest.example.org.",
                   "");
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
const char* const nsec3_data[DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT] = {
    // example NSEC3 parameters.  Using "apex_hash" just as a convenient
    // shortcut; otherwise it has nothing to do with the zone apex for the
    // purpose of this test.
    apex_hash, "3600", "NSEC3",
    "1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR NS SOA"
};
const char* const nsec3_sig_data[DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT] = {
    ns1_hash, "3600", "RRSIG",
    "NSEC3 5 3 3600 20000101000000 20000201000000 12345 "
    "example.com. FAKEFAKEFAKE"
};
const char* const nsec3_deleted_data[] = {
    // Delete parameters for nsec3_data
    apex_hash, nsec3_data[DatabaseAccessor::ADD_NSEC3_TYPE],
    nsec3_data[DatabaseAccessor::ADD_NSEC3_RDATA]
};

class SQLite3Update : public SQLite3AccessorTest {
protected:
    SQLite3Update() {
        // Note: if "installing" the test file fails some of the subsequent
        // tests would fail.
        const char *install_cmd = INSTALL_PROG " -c " TEST_DATA_DIR
                                  "/test.sqlite3 " TEST_DATA_BUILDDIR
                                  "/test.sqlite3.copied";
        if (system(install_cmd) != 0) {
            // any exception will do, this is failure in test setup, but nice
            // to show the command that fails, and shouldn't be caught
            isc_throw(isc::Exception,
                      "Error setting up; command failed: " << install_cmd);
        };
        initAccessor(TEST_DATA_BUILDDIR "/test.sqlite3.copied", "IN");
        zone_id = accessor->getZone("example.com.").second;
        another_accessor.reset(new SQLite3Accessor(
                                   TEST_DATA_BUILDDIR "/test.sqlite3.copied",
                                   "IN"));
        expected_stored.push_back(common_expected_data);
    }

    int zone_id;
    std::string get_columns[DatabaseAccessor::COLUMN_COUNT];
    std::string add_columns[DatabaseAccessor::ADD_COLUMN_COUNT];
    std::string add_nsec3_columns[DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT];
    std::string del_params[DatabaseAccessor::DEL_PARAM_COUNT];
    std::string diff_params[DatabaseAccessor::DIFF_PARAM_COUNT];

    vector<const char* const*> expected_stored; // placeholder for checkRecords
    vector<const char* const*> empty_stored; // indicate no corresponding data

    // Another accessor, emulating one running on a different process/thread
    boost::shared_ptr<SQLite3Accessor> another_accessor;
    DatabaseAccessor::IteratorContextPtr iterator;
};

void
checkRecords(SQLite3Accessor& accessor, int zone_id, const std::string& name,
             vector<const char* const*> expected_rows)
{
    DatabaseAccessor::IteratorContextPtr iterator =
        accessor.getRecords(name, zone_id);
    std::string columns[DatabaseAccessor::COLUMN_COUNT];
    vector<const char* const*>::const_iterator it = expected_rows.begin();
    while (iterator->getNext(columns)) {
        ASSERT_TRUE(it != expected_rows.end());
        checkRecordRow(columns, (*it)[3], (*it)[2], (*it)[4], (*it)[5], "");
        ++it;
    }
    EXPECT_TRUE(it == expected_rows.end());
}

// Similar to the previous one, but checking transactions on the nsec3 table.
void
checkNSEC3Records(SQLite3Accessor& accessor, int zone_id,
                  const std::string& hash,
                  vector<const char* const*> expected_rows)
{
    DatabaseAccessor::IteratorContextPtr iterator =
        accessor.getNSEC3Records(hash, zone_id);
    std::string columns[DatabaseAccessor::COLUMN_COUNT];
    vector<const char* const*>::const_iterator it = expected_rows.begin();
    while (iterator->getNext(columns)) {
        ASSERT_TRUE(it != expected_rows.end());
        checkRecordRow(columns, (*it)[DatabaseAccessor::ADD_NSEC3_TYPE],
                       (*it)[DatabaseAccessor::ADD_NSEC3_TTL],
                       "",      // sigtype, should always be empty
                       (*it)[DatabaseAccessor::ADD_NSEC3_RDATA],
                       "");     // name, always empty
        ++it;
    }
    EXPECT_TRUE(it == expected_rows.end());
}

TEST_F(SQLite3Update, emptyUpdate) {
    // If we do nothing between start and commit, the zone content
    // should be intact.

    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
    accessor->commit();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, flushZone) {
    // With 'replace' being true startUpdateZone() will flush the existing
    // zone content.

    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
    zone_id = accessor->startUpdateZone("example.com.", true).second;
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);
    accessor->commit();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);
}

TEST_F(SQLite3Update, flushZoneWithNSEC3) {
    // Similar to the previous case, but make sure the separate nsec3 table
    // is also cleared.  We first need to add something to the table.
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    copy(nsec3_data, nsec3_data + DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT,
         add_nsec3_columns);
    accessor->addNSEC3RecordToZone(add_nsec3_columns);
    accessor->commit();

    // Confirm it surely exists.
    expected_stored.clear();
    expected_stored.push_back(nsec3_data);
    checkNSEC3Records(*accessor, zone_id, apex_hash, expected_stored);

    // Then starting zone replacement.  the NSEC3 record should have been
    // removed.
    zone_id = accessor->startUpdateZone("example.com.", true).second;
    checkNSEC3Records(*accessor, zone_id, apex_hash, empty_stored);
}

TEST_F(SQLite3Update, readWhileUpdate) {
    zone_id = accessor->startUpdateZone("example.com.", true).second;
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);

    // Until commit is done, the other accessor should see the old data
    checkRecords(*another_accessor, zone_id, "foo.bar.example.com.",
                 expected_stored);

    // Once the changes are committed, the other accessor will see the new
    // data.
    accessor->commit();
    checkRecords(*another_accessor, zone_id, "foo.bar.example.com.",
                 empty_stored);
}

TEST_F(SQLite3Update, rollback) {
    zone_id = accessor->startUpdateZone("example.com.", true).second;
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);

    // Rollback will revert the change made by startUpdateZone(, true).
    accessor->rollback();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update,  rollbackFailure) {
    // This test emulates a rare scenario of making rollback attempt fail.
    // The iterator is paused in the middle of getting records, which prevents
    // the rollback operation at the end of the test.

    // Since SQLite3 version 3.7.11, rollbacks do not fail on pending
    // transactions anymore, making this test fail (and moot), but the
    // transactions will fail after it, so, depending on version,
    // we test whether that happens and is caught
    string columns[DatabaseAccessor::COLUMN_COUNT];
    iterator = accessor->getRecords("example.com.", zone_id);
    EXPECT_TRUE(iterator->getNext(columns));

    accessor->startUpdateZone("example.com.", true);
#if SQLITE_VERSION_NUMBER < 3007011
    EXPECT_THROW(accessor->rollback(), DataSourceError);
    EXPECT_NO_THROW(iterator->getNext(columns));
#else
    EXPECT_NO_THROW(accessor->rollback());
    EXPECT_THROW(iterator->getNext(columns), DataSourceError);
#endif
}

TEST_F(SQLite3Update, commitConflict) {
    // Start reading the DB by another accessor.  We should stop at a single
    // call to getNextRecord() to keep holding the lock.
    iterator = another_accessor->getRecords("foo.example.com.", zone_id);
    EXPECT_TRUE(iterator->getNext(get_columns));

    // Due to getNextRecord() above, the other accessor holds a DB lock,
    // which will prevent commit.
    zone_id = accessor->startUpdateZone("example.com.", true).second;
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);
    EXPECT_THROW(accessor->commit(), DataSourceError);
    accessor->rollback();   // rollback should still succeed

    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, updateConflict) {
    // Similar to the previous case, but this is a conflict with another
    // update attempt.  Note that these two accessors modify disjoint sets
    // of data; sqlite3 only has a coarse-grained lock so we cannot allow
    // these updates to run concurrently.
    EXPECT_TRUE(another_accessor->startUpdateZone("sql1.example.com.",
                                                  true).first);
    EXPECT_THROW(accessor->startUpdateZone("example.com.", true),
                 DataSourceError);
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);

    // Once we rollback the other attempt of change, we should be able to
    // start and commit the transaction using the main accessor.
    another_accessor->rollback();
    accessor->startUpdateZone("example.com.", true);
    accessor->commit();
}

TEST_F(SQLite3Update, duplicateUpdate) {
    accessor->startUpdateZone("example.com.", false);
    EXPECT_THROW(accessor->startUpdateZone("example.com.", false),
                 DataSourceError);
}

TEST_F(SQLite3Update, commitWithoutTransaction) {
    EXPECT_THROW(accessor->commit(), DataSourceError);
}

TEST_F(SQLite3Update, rollbackWithoutTransaction) {
    EXPECT_THROW(accessor->rollback(), DataSourceError);
}

TEST_F(SQLite3Update, addRecord) {
    // Before update, there should be no record for this name
    checkRecords(*accessor, zone_id, "newdata.example.com.", empty_stored);

    zone_id = accessor->startUpdateZone("example.com.", false).second;
    copy(new_data, new_data + DatabaseAccessor::ADD_COLUMN_COUNT,
         add_columns);
    accessor->addRecordToZone(add_columns);

    expected_stored.clear();
    expected_stored.push_back(new_data);
    checkRecords(*accessor, zone_id, "newdata.example.com.", expected_stored);

    // Commit the change, and confirm the new data is still there.
    accessor->commit();
    checkRecords(*accessor, zone_id, "newdata.example.com.", expected_stored);
}

TEST_F(SQLite3Update, addNSEC3Record) {
    // Similar to the previous test, but for NSEC3-related records
    checkRecords(*accessor, zone_id, apex_hash, empty_stored);
    checkRecords(*accessor, zone_id, ns1_hash, empty_stored);

    zone_id = accessor->startUpdateZone("example.com.", false).second;
    // Add an NSEC3
    copy(nsec3_data, nsec3_data + DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT,
         add_nsec3_columns);
    accessor->addNSEC3RecordToZone(add_nsec3_columns);

    // Add an RRSIG for NSEC3
    copy(nsec3_sig_data,
         nsec3_sig_data + DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT,
         add_nsec3_columns);
    accessor->addNSEC3RecordToZone(add_nsec3_columns);

    // Check the stored data, before and after commit().
    for (size_t i = 0; i < 2; ++i) {
        expected_stored.clear();
        expected_stored.push_back(nsec3_data);
        checkNSEC3Records(*accessor, zone_id, apex_hash, expected_stored);

        expected_stored.clear();
        expected_stored.push_back(nsec3_sig_data);
        checkNSEC3Records(*accessor, zone_id, ns1_hash, expected_stored);

        if (i == 0) {          // make sure commit() happens only once
            accessor->commit();
        }
    }
}

TEST_F(SQLite3Update, nsec3IteratorOnAdd) {
    // This test checks if an added NSEC3 record will appear in the iterator
    // result, meeting the expectation of addNSEC3RecordToZone.
    // Specifically, it checks if the name column is filled with the complete
    // owner name.

    // We'll replace the zone, and add one NSEC3 record, and only that one.
    zone_id = accessor->startUpdateZone("example.com.", true).second;
    copy(nsec3_data, nsec3_data + DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT,
         add_nsec3_columns);
    accessor->addNSEC3RecordToZone(add_nsec3_columns);
    accessor->commit();

    // the zone should contain only one record we just added.
    DatabaseAccessor::IteratorContextPtr context =
        accessor->getAllRecords(zone_id);
    string data[DatabaseAccessor::COLUMN_COUNT];
    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ(string(apex_hash) + ".example.com.",
              data[DatabaseAccessor::NAME_COLUMN]);
    EXPECT_FALSE(context->getNext(data));
}

TEST_F(SQLite3Update, addThenRollback) {
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    copy(new_data, new_data + DatabaseAccessor::ADD_COLUMN_COUNT,
         add_columns);
    accessor->addRecordToZone(add_columns);

    expected_stored.clear();
    expected_stored.push_back(new_data);
    checkRecords(*accessor, zone_id, "newdata.example.com.", expected_stored);

    // Rollback the transaction, and confirm the zone reverts to the previous
    // state.  We also start another update to check if the accessor can be
    // reused for a new update after rollback.
    accessor->rollback();
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    checkRecords(*accessor, zone_id, "newdata.example.com.", empty_stored);
}

TEST_F(SQLite3Update, duplicateAdd) {
    const char* const dup_data[] = {
        "foo.bar.example.com.", "com.example.bar.foo.", "3600", "A", "",
        "192.0.2.1"
    };
    expected_stored.clear();
    expected_stored.push_back(dup_data);
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);

    // Adding exactly the same data.  As this backend is "dumb", another
    // row of the same content will be inserted.
    copy(dup_data, dup_data + DatabaseAccessor::ADD_COLUMN_COUNT,
         add_columns);
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    accessor->addRecordToZone(add_columns);
    expected_stored.push_back(dup_data);
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, invalidAdd) {
    // An attempt of add before an explicit start of transaction
    EXPECT_THROW(accessor->addRecordToZone(add_columns), DataSourceError);

    // Same for addNSEC3.
    copy(nsec3_data, nsec3_data + DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT,
         add_nsec3_columns);
    EXPECT_THROW(accessor->addNSEC3RecordToZone(add_nsec3_columns),
                 DataSourceError);
}

TEST_F(SQLite3Update, deleteRecord) {
    zone_id = accessor->startUpdateZone("example.com.", false).second;

    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);

    copy(deleted_data, deleted_data + DatabaseAccessor::DEL_PARAM_COUNT,
         del_params);
    accessor->deleteRecordInZone(del_params);
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);

    // Commit the change, and confirm the deleted data still isn't there.
    accessor->commit();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);
}

TEST_F(SQLite3Update, deleteNSEC3Record) {
    // Similar to the previous test, but for NSEC3.
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    checkNSEC3Records(*accessor, zone_id, apex_hash, empty_stored);

    // We first need to add some record.
    copy(nsec3_data, nsec3_data + DatabaseAccessor::ADD_NSEC3_COLUMN_COUNT,
         add_nsec3_columns);
    accessor->addNSEC3RecordToZone(add_nsec3_columns);

    // Now it should exist.
    expected_stored.clear();
    expected_stored.push_back(nsec3_data);
    checkNSEC3Records(*accessor, zone_id, apex_hash, expected_stored);

    // Delete it, and confirm that.
    copy(nsec3_deleted_data,
         nsec3_deleted_data + DatabaseAccessor::DEL_PARAM_COUNT, del_params);
    accessor->deleteNSEC3RecordInZone(del_params);
    checkNSEC3Records(*accessor, zone_id, apex_hash, empty_stored);

    // Commit the change, and confirm the deleted data still isn't there.
    accessor->commit();
    checkNSEC3Records(*accessor, zone_id, apex_hash, empty_stored);
}

TEST_F(SQLite3Update, deleteThenRollback) {
    zone_id = accessor->startUpdateZone("example.com.", false).second;

    copy(deleted_data, deleted_data + DatabaseAccessor::DEL_PARAM_COUNT,
         del_params);
    accessor->deleteRecordInZone(del_params);
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", empty_stored);

    // Rollback the change, and confirm the data still exists.
    accessor->rollback();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, deleteNonexistent) {
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    copy(deleted_data, deleted_data + DatabaseAccessor::DEL_PARAM_COUNT,
         del_params);

    // Replace the name with a non existent one, then try to delete it.
    // nothing should happen.
    del_params[DatabaseAccessor::DEL_NAME] = "no-such-name.example.com.";
    checkRecords(*accessor, zone_id, "no-such-name.example.com.",
                 empty_stored);
    accessor->deleteRecordInZone(del_params);
    checkRecords(*accessor, zone_id, "no-such-name.example.com.",
                 empty_stored);

    // Name exists but the RR type is different.  Delete attempt shouldn't
    // delete only by name.
    copy(deleted_data, deleted_data + DatabaseAccessor::DEL_PARAM_COUNT,
         del_params);
    del_params[DatabaseAccessor::DEL_TYPE] = "AAAA";
    accessor->deleteRecordInZone(del_params);
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);

    // Similar to the previous case, but RDATA is different.
    copy(deleted_data, deleted_data + DatabaseAccessor::DEL_PARAM_COUNT,
         del_params);
    del_params[DatabaseAccessor::DEL_RDATA] = "192.0.2.2";
    accessor->deleteRecordInZone(del_params);
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, invalidDelete) {
    // An attempt of delete before an explicit start of transaction
    EXPECT_THROW(accessor->deleteRecordInZone(del_params), DataSourceError);

    // Same for NSEC3.
    EXPECT_THROW(accessor->deleteNSEC3RecordInZone(del_params),
                 DataSourceError);
}

TEST_F(SQLite3Update, emptyTransaction) {
    // A generic transaction without doing anything inside it.  Just check
    // it doesn't throw or break the database.
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
    accessor->startTransaction();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
    accessor->commit();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
}

TEST_F(SQLite3Update, duplicateTransaction) {
    accessor->startTransaction();
    EXPECT_THROW(accessor->startTransaction(), DataSourceError);
}

TEST_F(SQLite3Update, transactionInUpdate) {
    accessor->startUpdateZone("example.com.", true);
    EXPECT_THROW(accessor->startTransaction(), DataSourceError);
}

TEST_F(SQLite3Update, updateInTransaction) {
    accessor->startTransaction();
    EXPECT_THROW(accessor->startUpdateZone("example.com.", true),
                 DataSourceError);
}

TEST_F(SQLite3Update, updateWithTransaction) {
    // Start a read-only transaction, wherein we execute two reads.
    // Meanwhile we start a write (update) transaction.  The commit attempt
    // for the write transaction will due to the lock held by the read
    // transaction.  The database should be intact.
    another_accessor->startTransaction();
    checkRecords(*another_accessor, zone_id, "foo.bar.example.com.",
                 expected_stored);

    ASSERT_TRUE(accessor->startUpdateZone("example.com.", true).first);
    EXPECT_THROW(accessor->commit(), DataSourceError);

    checkRecords(*another_accessor, zone_id, "foo.bar.example.com.",
                 expected_stored);
    another_accessor->commit(); // this shouldn't throw
}

TEST_F(SQLite3Update, updateWithoutTransaction) {
    // Similar to the previous test, but reads are not protected in a
    // transaction.  So the write transaction will succeed and flush the DB,
    // and the result of the second read is different from the first.
    checkRecords(*another_accessor, zone_id, "foo.bar.example.com.",
                 expected_stored);

    ASSERT_TRUE(accessor->startUpdateZone("example.com.", true).first);
    accessor->commit();

    checkRecords(*another_accessor, zone_id, "foo.bar.example.com.",
                 empty_stored);
}

TEST_F(SQLite3Update, concurrentTransactions) {
    // Two read-only transactions coexist (unlike the read vs write)
    // Start one transaction.
    accessor->startTransaction();
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);

    // Start a new one.
    another_accessor->startTransaction();

    // The second transaction doesn't affect the first or vice versa.
    checkRecords(*accessor, zone_id, "foo.bar.example.com.", expected_stored);
    checkRecords(*another_accessor, zone_id, "foo.bar.example.com.",
                 expected_stored);

    // Commit should be successful for both transactions.
    accessor->commit();
    another_accessor->commit();
}

//
// Commonly used data for diff related tests.  The last two entries are
// a textual representation of "version" and a textual representation of
// diff operation (either DIFF_ADD_TEXT or DIFF_DELETE_TEXT).  We use this
// format for the convenience of generating test data and checking the results.
//
const char* const DIFF_ADD_TEXT = "0";
const char* const DIFF_DELETE_TEXT = "1";
const char* const diff_begin_data[] = {
    "example.com.", "SOA", "3600",
    "ns.example.com. admin.example.com. 1234 3600 1800 2419200 7200",
    "1234", DIFF_DELETE_TEXT
};
const char* const diff_del_a_data[] = {
    "dns01.example.com.", "A", "3600", "192.0.2.1", "1234", DIFF_DELETE_TEXT
};
const char* const diff_end_data[] = {
    "example.com.", "SOA", "3600",
    "ns.example.com. admin.example.com. 1300 3600 1800 2419200 7200",
    "1300", DIFF_ADD_TEXT
};
const char* const diff_add_a_data[] = {
    "dns01.example.com.", "A", "3600", "192.0.2.10", "1300", DIFF_ADD_TEXT
};

// The following two are helper functions to convert textual test data
// to integral zone ID and diff operation.
int
getVersion(const char* const diff_data[]) {
    return (lexical_cast<int>(diff_data[DatabaseAccessor::DIFF_PARAM_COUNT]));
}

DatabaseAccessor::DiffOperation
getOperation(const char* const diff_data[]) {
    return (static_cast<DatabaseAccessor::DiffOperation>(
                lexical_cast<int>(
                    diff_data[DatabaseAccessor::DIFF_PARAM_COUNT + 1])));
}

// Common checker function that compares expected and actual sequence of
// diffs.
void
checkDiffs(const vector<const char* const*>& expected,
           DatabaseAccessor::IteratorContextPtr rr_iterator)
{
    vector<vector<string> > actual;
    string columns_holder[DatabaseAccessor::COLUMN_COUNT];
    while (rr_iterator->getNext(columns_holder)) {
        // Reorder the 'actual' vector to be compatible with the expected one.
        vector<string> columns;
        columns.push_back(columns_holder[DatabaseAccessor::NAME_COLUMN]);
        columns.push_back(columns_holder[DatabaseAccessor::TYPE_COLUMN]);
        columns.push_back(columns_holder[DatabaseAccessor::TTL_COLUMN]);
        columns.push_back(columns_holder[DatabaseAccessor::RDATA_COLUMN]);
        actual.push_back(columns);
    }
    EXPECT_EQ(expected.size(), actual.size());
    const size_t n_diffs = std::min(expected.size(), actual.size());
    for (size_t i = 0; i < n_diffs; ++i) {
        for (int j = 0; j < actual[i].size(); ++j) {
            EXPECT_EQ(expected[i][j], actual[i][j]);
        }
    }
}

TEST_F(SQLite3Update, addRecordDiff) {
    // A simple case of adding diffs: just changing the SOA, and confirm
    // the diffs are stored as expected.
    zone_id = accessor->startUpdateZone("example.com.", false).second;

    copy(diff_begin_data, diff_begin_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_begin_data),
                            getOperation(diff_begin_data), diff_params);

    copy(diff_end_data, diff_end_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_end_data),
                            getOperation(diff_end_data), diff_params);

    // Until the diffs are committed, they are not visible to other accessors.
    EXPECT_THROW(another_accessor->getDiffs(zone_id, 1234, 1300),
                 NoSuchSerial);

    accessor->commit();

    expected_stored.clear();
    expected_stored.push_back(diff_begin_data);
    expected_stored.push_back(diff_end_data);
    checkDiffs(expected_stored, accessor->getDiffs(zone_id, 1234, 1300));
    // Now it should be visible to others, too.
    checkDiffs(expected_stored, another_accessor->getDiffs(zone_id, 1234,
                                                           1300));
}

TEST_F(SQLite3Update, addRecordOfLargeSerial) {
    // This is essentially the same as the previous test, but using a
    // very large "version" (SOA serial), which is actually the possible
    // largest value to confirm the internal code doesn't have an overflow bug
    // or other failure due to the larger value.
    zone_id = accessor->startUpdateZone("example.com.", false).second;

    const char* const begin_data[] = {
        "example.com.", "SOA", "3600",
        "ns.example.com. admin.example.com. 4294967295 3600 1800 2419200 7200",
        "4294967295", DIFF_DELETE_TEXT
    };

    copy(begin_data, begin_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    // For "serial" parameter, we intentionally hardcode the value rather
    // than converting it from the data.
    accessor->addRecordDiff(zone_id, 0xffffffff, getOperation(diff_begin_data),
                            diff_params);
    copy(diff_end_data, diff_end_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_end_data),
                            getOperation(diff_end_data), diff_params);

    accessor->commit();

    expected_stored.clear();
    expected_stored.push_back(begin_data);
    expected_stored.push_back(diff_end_data);
    checkDiffs(expected_stored, accessor->getDiffs(zone_id, 4294967295U, 1300));
}

TEST_F(SQLite3Update, addDiffWithoutUpdate) {
    // Right now we require startUpdateZone() prior to performing
    // addRecordDiff.
    copy(diff_begin_data, diff_begin_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    EXPECT_THROW(accessor->addRecordDiff(0, getVersion(diff_begin_data),
                                         getOperation(diff_begin_data),
                                         diff_params),
                 DataSourceError);

    // For now, we don't allow adding diffs in a general transaction either.
    accessor->startTransaction();
    EXPECT_THROW(accessor->addRecordDiff(0, getVersion(diff_begin_data),
                                         getOperation(diff_begin_data),
                                         diff_params),
                 DataSourceError);
}

TEST_F(SQLite3Update, addDiffWithBadZoneID) {
    // For now, we require zone ID passed to addRecordDiff be equal to
    // that for the zone being updated.
    zone_id = accessor->startUpdateZone("example.com.", false).second;
    copy(diff_begin_data, diff_begin_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    EXPECT_THROW(accessor->addRecordDiff(zone_id + 1,
                                         getVersion(diff_begin_data),
                                         getOperation(diff_begin_data),
                                         diff_params),
                 DataSourceError);
}

TEST_F(SQLite3Update, addDiffRollback) {
    // Rollback tentatively added diffs.  This is no different from the
    // update case, but we test it explicitly just in case.
    zone_id = accessor->startUpdateZone("example.com.", false).second;

    copy(diff_begin_data, diff_begin_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_begin_data),
                            getOperation(diff_begin_data), diff_params);
    accessor->rollback();

    EXPECT_THROW(accessor->getDiffs(zone_id, 1234, 1234), NoSuchSerial);
}

TEST_F(SQLite3Update, addDiffInBadOrder) {
    // At this level, the API is naive, and doesn't care if the diff sequence
    // is a valid IXFR order.
    zone_id = accessor->startUpdateZone("example.com.", false).second;

    // Add diff of 'end', then 'begin'
    copy(diff_end_data, diff_end_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_end_data),
                            static_cast<DatabaseAccessor::DiffOperation>(
                                lexical_cast<int>(DIFF_DELETE_TEXT)),
                            diff_params);

    copy(diff_begin_data, diff_begin_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_begin_data),
                            static_cast<DatabaseAccessor::DiffOperation>(
                                lexical_cast<int>(DIFF_ADD_TEXT)),
                            diff_params);

    accessor->commit();

    expected_stored.clear();
    expected_stored.push_back(diff_end_data);
    expected_stored.push_back(diff_begin_data);
    checkDiffs(expected_stored, accessor->getDiffs(zone_id, 1300, 1234));
}

TEST_F(SQLite3Update, addDiffWithUpdate) {
    // A more realistic example: add corresponding diffs while updating zone.
    // Implementation wise, there should be no reason this could fail if
    // the basic tests so far pass.  But we check it in case we miss something.

    const char* const old_a_record[] = {
        "dns01.example.com.", "A", "192.0.2.1"
    };
    const char* const new_a_record[] = {
        "dns01.example.com.", "com.example.dns01.", "3600", "A", "",
        "192.0.2.10"
    };
    const char* const old_soa_record[] = {
        "example.com.", "SOA",
        "ns.example.com. admin.example.com. 1234 3600 1800 2419200 7200",
    };
    const char* const new_soa_record[] = {
        "dns01.example.com.", "com.example.dns01.", "3600", "A", "",
        "ns.example.com. admin.example.com. 1300 3600 1800 2419200 7200",
    };

    zone_id = accessor->startUpdateZone("example.com.", false).second;

    // Delete SOA (and add that diff)
    copy(old_soa_record, old_soa_record + DatabaseAccessor::DEL_PARAM_COUNT,
         del_params);
    accessor->deleteRecordInZone(del_params);
    copy(diff_begin_data, diff_begin_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_begin_data),
                            getOperation(diff_begin_data), diff_params);

    // Delete A
    copy(old_a_record, old_a_record + DatabaseAccessor::DEL_PARAM_COUNT,
         del_params);
    accessor->deleteRecordInZone(del_params);
    copy(diff_del_a_data, diff_del_a_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_del_a_data),
                            getOperation(diff_del_a_data), diff_params);

    // Add SOA
    copy(new_soa_record, new_soa_record + DatabaseAccessor::ADD_COLUMN_COUNT,
         add_columns);
    accessor->addRecordToZone(add_columns);
    copy(diff_end_data, diff_end_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_end_data),
                            getOperation(diff_end_data), diff_params);

    // Add A
    copy(new_a_record, new_a_record + DatabaseAccessor::ADD_COLUMN_COUNT,
         add_columns);
    accessor->addRecordToZone(add_columns);
    copy(diff_add_a_data, diff_add_a_data + DatabaseAccessor::DIFF_PARAM_COUNT,
         diff_params);
    accessor->addRecordDiff(zone_id, getVersion(diff_add_a_data),
                            getOperation(diff_add_a_data), diff_params);

    accessor->commit();

    expected_stored.clear();
    expected_stored.push_back(diff_begin_data);
    expected_stored.push_back(diff_del_a_data);
    expected_stored.push_back(diff_end_data);
    expected_stored.push_back(diff_add_a_data);

    checkDiffs(expected_stored, accessor->getDiffs(zone_id, 1234, 1300));
}
} // end anonymous namespace
