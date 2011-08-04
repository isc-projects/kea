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

    void addCurName(const std::string& name) {
        records[name] = cur_name;
        cur_name.clear();
    }

    void fillData() {
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("AAAA", "3600", "", "2001:db8::1");
        addRecord("AAAA", "3600", "", "2001:db8::2");
        addCurName("www.example.org.");
        addRecord("CNAME", "3600", "", "www.example.org.");
        addCurName("cname.example.org.");

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

TEST_F(DatabaseClientTest, find) {
    DataSourceClient::FindResult zone(client_->findZone(Name("example.org")));
    ASSERT_EQ(result::SUCCESS, zone.code);
    shared_ptr<DatabaseClient::Finder> finder(
        dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
    EXPECT_EQ(42, finder->zone_id());
    isc::dns::Name name("www.example.org.");

    ZoneFinder::FindResult result1 = finder->find(name, isc::dns::RRType::A(),
                                                  NULL, ZoneFinder::FIND_DEFAULT);
    ASSERT_EQ(ZoneFinder::SUCCESS, result1.code);
    EXPECT_EQ(1, result1.rrset->getRdataCount());
    EXPECT_EQ(isc::dns::RRType::A(), result1.rrset->getType());

    ZoneFinder::FindResult result2 = finder->find(name, isc::dns::RRType::AAAA(),
                                                  NULL, ZoneFinder::FIND_DEFAULT);
    ASSERT_EQ(ZoneFinder::SUCCESS, result2.code);
    EXPECT_EQ(2, result2.rrset->getRdataCount());
    EXPECT_EQ(isc::dns::RRType::AAAA(), result2.rrset->getType());

    ZoneFinder::FindResult result3 = finder->find(name, isc::dns::RRType::TXT(),
                                                  NULL, ZoneFinder::FIND_DEFAULT);
    ASSERT_EQ(ZoneFinder::NXRRSET, result3.code);
    EXPECT_EQ(isc::dns::ConstRRsetPtr(), result3.rrset);

    ZoneFinder::FindResult result4 = finder->find(isc::dns::Name("cname.example.org."),
                                                  isc::dns::RRType::A(),
                                                  NULL, ZoneFinder::FIND_DEFAULT);
    ASSERT_EQ(ZoneFinder::CNAME, result4.code);
    EXPECT_EQ(1, result4.rrset->getRdataCount());
    EXPECT_EQ(isc::dns::RRType::CNAME(), result4.rrset->getType());

    ZoneFinder::FindResult result5 = finder->find(isc::dns::Name("doesnotexist.example.org."),
                                                  isc::dns::RRType::A(),
                                                  NULL, ZoneFinder::FIND_DEFAULT);
    ASSERT_EQ(ZoneFinder::NXDOMAIN, result5.code);
    EXPECT_EQ(isc::dns::ConstRRsetPtr(), result5.rrset);

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
