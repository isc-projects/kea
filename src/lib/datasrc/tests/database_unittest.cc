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

#include <gtest/gtest.h>

#include <dns/name.h>
#include <exceptions/exceptions.h>

#include <datasrc/database.h>
#include <datasrc/zone.h>
#include <datasrc/data_source.h>

#include <map>

using namespace isc::datasrc;
using namespace std;
using namespace boost;
using isc::dns::Name;

namespace {

/*
 * A virtual database connection that pretends it contains single zone --
 * example.org.
 */
class MockConnection : public DatabaseConnection {
public:
    MockConnection() { fillData(); }

    virtual std::pair<bool, int> getZone(const Name& name) const {
        if (name == Name("example.org")) {
            return (std::pair<bool, int>(true, 42));
        } else {
            return (std::pair<bool, int>(false, 0));
        }
    }

    virtual void searchForRecords(int zone_id, const std::string& name) {
        // we're not aiming for efficiency in this test, simply
        // copy the relevant vector from records
        cur_record = 0;

        if (zone_id == 42) {
            if (records.count(name) > 0) {
                cur_name = records.find(name)->second;
            } else {
                cur_name.clear();
            }
        } else {
            cur_name.clear();
        }
    };

    virtual bool getNextRecord(std::vector<std::string>& columns) {
        if (cur_record < cur_name.size()) {
            columns = cur_name[cur_record++];
            return true;
        } else {
            return false;
        }
    };

private:
    std::map<std::string, std::vector< std::vector<std::string> > > records;
    // used as internal index for getNextRecord()
    size_t cur_record;
    // used as temporary storage after searchForRecord() and during
    // getNextRecord() calls, as well as during the building of the
    // fake data
    std::vector< std::vector<std::string> > cur_name;

    // Adds one record to the current name in the database
    // The actual data will not be added to 'records' until
    // addCurName() is called
    void addRecord(const std::string& name,
                   const std::string& type,
                   const std::string& sigtype,
                   const std::string& rdata) {
        std::vector<std::string> columns;
        columns.push_back(name);
        columns.push_back(type);
        columns.push_back(sigtype);
        columns.push_back(rdata);
        cur_name.push_back(columns);
    }

    // Adds all records we just built with calls to addRecords
    // to the actual fake database. This will clear cur_name,
    // so we can immediately start adding new records.
    void addCurName(const std::string& name) {
        ASSERT_EQ(0, records.count(name));
        records[name] = cur_name;
        cur_name.clear();
    }

    // Fills the database with zone data.
    // This method constructs a number of resource records (with addRecord),
    // which will all be added for one domain name to the fake database
    // (with addCurName). So for instance the first set of calls create
    // data for the name 'www.example.org', which will consist of one A RRset
    // of one record, and one AAAA RRset of two records.
    // The order in which they are added is the order in which getNextRecord()
    // will return them (so we can test whether find() etc. support data that
    // might not come in 'normal' order)
    // It shall immediately fail if you try to add the same name twice.
    void fillData() {
        // some plain data
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("AAAA", "3600", "", "2001:db8::1");
        addRecord("AAAA", "3600", "", "2001:db8::2");
        addCurName("www.example.org.");

        addRecord("CNAME", "3600", "", "www.example.org.");
        addCurName("cname.example.org.");

        // some DNSSEC-'signed' data
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("AAAA", "3600", "", "2001:db8::1");
        addRecord("AAAA", "3600", "", "2001:db8::2");
        addRecord("RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("signed1.example.org.");
        addRecord("CNAME", "3600", "", "www.example.org.");
        addRecord("RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("signedcname1.example.org.");

        // let's pretend we have a database that is not careful
        // about the order in which it returns data
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("AAAA", "3600", "", "2001:db8::2");
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("AAAA", "3600", "", "2001:db8::1");
        addCurName("signed2.example.org.");
        addRecord("RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("CNAME", "3600", "", "www.example.org.");
        addCurName("signedcname2.example.org.");

        // also add some intentionally bad data
        cur_name.push_back(std::vector<std::string>());
        addCurName("emptyvector.example.org.");
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("CNAME", "3600", "", "www.example.org.");
        addCurName("badcname.example.org.");
    }
};

class DatabaseClientTest : public ::testing::Test {
public:
    DatabaseClientTest() {
        createClient();
    }
    /*
     * We initialize the client from a function, so we can call it multiple
     * times per test.
     */
    void createClient() {
        current_connection_ = new MockConnection();
        client_.reset(new DatabaseClient(shared_ptr<DatabaseConnection>(
             current_connection_)));
    }
    // Will be deleted by client_, just keep the current value for comparison.
    MockConnection* current_connection_;
    shared_ptr<DatabaseClient> client_;
    /**
     * Check the zone finder is a valid one and references the zone ID and
     * connection available here.
     */
    void checkZoneFinder(const DataSourceClient::FindResult& zone) {
        ASSERT_NE(ZoneFinderPtr(), zone.zone_finder) << "No zone finder";
        shared_ptr<DatabaseClient::Finder> finder(
            dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
        ASSERT_NE(shared_ptr<DatabaseClient::Finder>(), finder) <<
            "Wrong type of finder";
        EXPECT_EQ(42, finder->zone_id());
        EXPECT_EQ(current_connection_, &finder->connection());
    }
};

TEST_F(DatabaseClientTest, zoneNotFound) {
    DataSourceClient::FindResult zone(client_->findZone(Name("example.com")));
    EXPECT_EQ(result::NOTFOUND, zone.code);
}

TEST_F(DatabaseClientTest, exactZone) {
    DataSourceClient::FindResult zone(client_->findZone(Name("example.org")));
    EXPECT_EQ(result::SUCCESS, zone.code);
    checkZoneFinder(zone);
}

TEST_F(DatabaseClientTest, superZone) {
    DataSourceClient::FindResult zone(client_->findZone(Name(
        "sub.example.org")));
    EXPECT_EQ(result::PARTIALMATCH, zone.code);
    checkZoneFinder(zone);
}

TEST_F(DatabaseClientTest, noConnException) {
    EXPECT_THROW(DatabaseClient(shared_ptr<DatabaseConnection>()),
                 isc::InvalidParameter);
}

namespace {
void
doFindTest(shared_ptr<DatabaseClient::Finder> finder,
           const isc::dns::Name& name,
           const isc::dns::RRType& type,
           const isc::dns::RRType& expected_type,
           ZoneFinder::Result expected_result,
           unsigned int expected_rdata_count,
           unsigned int expected_signature_count)
{
    ZoneFinder::FindResult result = finder->find(name, type,
                                                 NULL, ZoneFinder::FIND_DEFAULT);
    ASSERT_EQ(expected_result, result.code) << name.toText() << " " << type.toText();
    if (expected_rdata_count > 0) {
        EXPECT_EQ(expected_rdata_count, result.rrset->getRdataCount());
        EXPECT_EQ(expected_type, result.rrset->getType());
        if (expected_signature_count > 0) {
            EXPECT_EQ(expected_signature_count, result.rrset->getRRsig()->getRdataCount());
        } else {
            EXPECT_EQ(isc::dns::RRsetPtr(), result.rrset->getRRsig());
        }
    } else {
        EXPECT_EQ(isc::dns::RRsetPtr(), result.rrset);
    }
}
} // end anonymous namespace

TEST_F(DatabaseClientTest, find) {
    DataSourceClient::FindResult zone(client_->findZone(Name("example.org")));
    ASSERT_EQ(result::SUCCESS, zone.code);
    shared_ptr<DatabaseClient::Finder> finder(
        dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
    EXPECT_EQ(42, finder->zone_id());
    isc::dns::Name name("www.example.org.");

    doFindTest(finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               ZoneFinder::SUCCESS, 1, 0);
    doFindTest(finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               ZoneFinder::SUCCESS, 2, 0);
    doFindTest(finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               ZoneFinder::NXRRSET, 0, 0);
    doFindTest(finder, isc::dns::Name("cname.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::CNAME(),
               ZoneFinder::CNAME, 1, 0);
    doFindTest(finder, isc::dns::Name("doesnotexist.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               ZoneFinder::NXDOMAIN, 0, 0);
    doFindTest(finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               ZoneFinder::SUCCESS, 1, 1);
    doFindTest(finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               ZoneFinder::SUCCESS, 2, 1);
    doFindTest(finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               ZoneFinder::NXRRSET, 0, 0);
    doFindTest(finder, isc::dns::Name("signedcname1.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::CNAME(),
               ZoneFinder::CNAME, 1, 1);

    doFindTest(finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               ZoneFinder::SUCCESS, 1, 1);
    doFindTest(finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               ZoneFinder::SUCCESS, 2, 1);
    doFindTest(finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               ZoneFinder::NXRRSET, 0, 0);
    doFindTest(finder, isc::dns::Name("signedcname2.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::CNAME(),
               ZoneFinder::CNAME, 1, 1);

    EXPECT_THROW(finder->find(isc::dns::Name("emptyvector.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badcname.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);

}

}
