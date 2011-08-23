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
#include <datasrc/sqlite3_accessor.h>

#include <datasrc/data_source.h>

#include <dns/rrclass.h>

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace isc::datasrc;
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
std::string SQLITE_DBFILE_EXAMPLE_ORG = TEST_DATA_DIR "/example.org.sqlite3";

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
    std::pair<bool, int> result(db->getZone("example.com."));
    EXPECT_TRUE(result.first);
    EXPECT_EQ(1, result.second);
}

// But it should find only the zone, nothing below it
TEST_F(SQLite3Access, subZone) {
    EXPECT_FALSE(db->getZone("sub.example.com.").first);
}

// This zone is not there at all
TEST_F(SQLite3Access, noZone) {
    EXPECT_FALSE(db->getZone("example.org.").first);
}

// This zone is there, but in different class
TEST_F(SQLite3Access, noClass) {
    initAccessor(SQLITE_DBFILE_EXAMPLE, RRClass::CH());
    EXPECT_FALSE(db->getZone("example.com.").first);
}

// This tests the iterator context
TEST_F(SQLite3Access, iterator) {
    // Our test zone is conveniently small, but not empty
    initAccessor(SQLITE_DBFILE_EXAMPLE_ORG, RRClass::IN());

    const std::pair<bool, int> zone_info(db->getZone("example.org."));
    ASSERT_TRUE(zone_info.first);

    // Get the iterator context
    DatabaseAccessor::IteratorContextPtr
        context(db->getAllRecords(zone_info.second));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(),
              context);

    std::string data[DatabaseAccessor::COLUMN_COUNT];
    // Get and check the first and only record
    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("DNAME", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("dname.example.info.", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("dname.example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("DNAME", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("dname2.example.info.", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("dname2.foo.example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("MX", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("10 mail.example.org.", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("NS", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("ns1.example.org.", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("NS", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("ns2.example.org.", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("NS", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("ns3.example.org.", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("SOA", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("ns1.example.org. admin.example.org. "
              "1234 3600 1800 2419200 7200",
              data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("A", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("192.0.2.10", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("mail.example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("A", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("192.0.2.101", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("ns.sub.example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("NS", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("ns.sub.example.org.", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("sub.example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    EXPECT_TRUE(context->getNext(data));
    EXPECT_EQ("A", data[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ("3600", data[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ("192.0.2.1", data[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ("www.example.org.", data[DatabaseAccessor::NAME_COLUMN]);

    // Check there's no other
    EXPECT_FALSE(context->getNext(data));

    // And make sure calling it again won't cause problems.
    EXPECT_FALSE(context->getNext(data));
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
    EXPECT_EQ(field0, columns[DatabaseAccessor::TYPE_COLUMN]);
    EXPECT_EQ(field1, columns[DatabaseAccessor::TTL_COLUMN]);
    EXPECT_EQ(field2, columns[DatabaseAccessor::SIGTYPE_COLUMN]);
    EXPECT_EQ(field3, columns[DatabaseAccessor::RDATA_COLUMN]);
    EXPECT_EQ(field4, columns[DatabaseAccessor::NAME_COLUMN]);
}

TEST_F(SQLite3Access, getRecords) {
    const std::pair<bool, int> zone_info(db->getZone("example.com."));
    ASSERT_TRUE(zone_info.first);

    const int zone_id = zone_info.second;
    ASSERT_EQ(1, zone_id);

    std::string columns[DatabaseAccessor::COLUMN_COUNT];

    DatabaseAccessor::IteratorContextPtr
        context(db->getRecords("foo.bar", 1));
    ASSERT_NE(DatabaseAccessor::IteratorContextPtr(),
              context);
    EXPECT_FALSE(context->getNext(columns));
    checkRecordRow(columns, "", "", "", "", "");

    // now try some real searches
    context = db->getRecords("foo.example.com.", zone_id);
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

    context = db->getRecords("example.com.", zone_id);
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
}

} // end anonymous namespace
