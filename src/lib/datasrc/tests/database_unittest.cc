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

#include <boost/foreach.hpp>

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>
#include <exceptions/exceptions.h>

#include <datasrc/database.h>
#include <datasrc/zone.h>
#include <datasrc/data_source.h>

#include <testutils/dnsmessage_test.h>

#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace isc::datasrc;
using namespace std;
using namespace boost;
using namespace isc::dns;

namespace {

const int READONLY_ZONE_ID = 42;
const int WRITABLE_ZONE_ID = 4200;

/*
 * A virtual database database that pretends it contains single zone --
 * example.org.
 */
class MockAccessor : public DatabaseAccessor {
    typedef std::map<std::string, std::vector< std::vector<std::string> > >
    RECORDS;
public:
    MockAccessor() : search_running_(false), rollbacked_(false),
                     database_name_("mock_database")
    {
        fillData();
    }

    virtual pair<bool, int> getZone(const Name& name) const {
        return (getZone(name.toText()));
    }
    pair<bool, int> getZone(const string& name) const {
        if (name == "example.org.") {
            return (std::pair<bool, int>(true, READONLY_ZONE_ID));
        } else {
            return (std::pair<bool, int>(false, 0));
        }
    }

    virtual void searchForRecords(int zone_id, const std::string& name) {
        search_running_ = true;

        // 'hardcoded' name to trigger exceptions (for testing
        // the error handling of find() (the other on is below in
        // if the name is "exceptiononsearch" it'll raise an exception here
        if (name == "dsexception.in.search.") {
            isc_throw(DataSourceError, "datasource exception on search");
        } else if (name == "iscexception.in.search.") {
            isc_throw(isc::Exception, "isc exception on search");
        } else if (name == "basicexception.in.search.") {
            throw std::exception();
        }
        searched_name_ = name;

        // we're not aiming for efficiency in this test, simply
        // copy the relevant vector from records
        cur_record = 0;
        const RECORDS& cur_records = getRecords(zone_id);
        if (cur_records.count(name) > 0) {
            cur_name = cur_records.find(name)->second;
        } else {
            cur_name.clear();
        }
    }

    virtual bool getNextRecord(std::string columns[], size_t column_count) {
        if (searched_name_ == "dsexception.in.getnext.") {
            isc_throw(DataSourceError, "datasource exception on getnextrecord");
        } else if (searched_name_ == "iscexception.in.getnext.") {
            isc_throw(isc::Exception, "isc exception on getnextrecord");
        } else if (searched_name_ == "basicexception.in.getnext.") {
            throw std::exception();
        }

        if (column_count != DatabaseAccessor::COLUMN_COUNT) {
            isc_throw(DataSourceError, "Wrong column count in getNextRecord");
        }
        if (cur_record < cur_name.size()) {
            for (size_t i = 0; i < column_count; ++i) {
                columns[i] = cur_name[cur_record][i];
            }
            cur_record++;
            return (true);
        } else {
            resetSearch();
            return (false);
        }
    }

    virtual void resetSearch() {
        search_running_ = false;
    }

    virtual pair<bool, int> startUpdateZone(const std::string& zone_name,
                                            bool replace)
    {
        const pair<bool, int> zone_info = getZone(zone_name);
        if (!zone_info.first) {
            return (pair<bool, int>(false, 0));
        }

        // Prepare the record set for update.  If replacing the existing one,
        // we use an empty set; otherwise we use a writable copy of the
        // original.
        if (replace) {
            update_records.clear();
        } else {
            update_records = readonly_records;
        }

        return (pair<bool, int>(true, WRITABLE_ZONE_ID));
    }
    virtual void commitUpdateZone() {
        readonly_records = update_records;
    }
    virtual void rollbackUpdateZone() {
        rollbacked_ = true;
    }
    virtual void addRecordToZone(const vector<string>& columns) {
        // Copy the current value to cur_name.  If it doesn't exist,
        // operator[] will create a new one.
        cur_name = update_records[columns[DatabaseAccessor::ADD_NAME]];
        addRecord(columns[DatabaseAccessor::ADD_TYPE],
                  columns[DatabaseAccessor::ADD_TTL],
                  columns[DatabaseAccessor::ADD_SIGTYPE],
                  columns[DatabaseAccessor::ADD_RDATA]);
        // copy back the added entry.
        update_records[columns[DatabaseAccessor::ADD_NAME]] = cur_name;

        // remember this one so that test cases can check it.
        columns_lastadded = columns;
    }

    // Helper predicate class used in deleteRecordInZone().
    struct deleteMatch {
        deleteMatch(const string& type, const string& rdata) :
            type_(type), rdata_(rdata)
        {}
        bool operator()(const vector<string>& row) const {
            return (row[0] == type_ && row[3] == rdata_);
        }
        const string& type_;
        const string& rdata_;
    };

    virtual void deleteRecordInZone(const vector<string>& params) {
        vector<vector<string> > records =
            update_records[params[DatabaseAccessor::DEL_NAME]];
        records.erase(remove_if(records.begin(), records.end(),
                                deleteMatch(
                                    params[DatabaseAccessor::DEL_TYPE],
                                    params[DatabaseAccessor::DEL_RDATA])),
                      records.end());
        if (records.empty()) {
            update_records.erase(params[DatabaseAccessor::DEL_NAME]);
        } else {
            update_records[params[DatabaseAccessor::DEL_NAME]] = records;
        }
    }

    bool searchRunning() const {
        return (search_running_);
    }

    bool isRollbacked() const {
        return (rollbacked_);
    }

    virtual const std::string& getDBName() const {
        return (database_name_);
    }

    const vector<string>& getLastAdded() const {
        return (columns_lastadded);
    }
private:
    RECORDS readonly_records;
    RECORDS update_records;
    RECORDS empty_records;

    // used as internal index for getNextRecord()
    size_t cur_record;
    // used as temporary storage after searchForRecord() and during
    // getNextRecord() calls, as well as during the building of the
    // fake data
    std::vector< std::vector<std::string> > cur_name;

    // The columns that were most recently added via addRecordToZone()
    vector<string> columns_lastadded;

    // This boolean is used to make sure find() calls resetSearch
    // when it encounters an error
    bool search_running_;

    // Whether rollback operation has been performed for the database.
    // Not useful except for purely testing purpose.
    bool rollbacked_;

    // We store the name passed to searchForRecords, so we can
    // hardcode some exceptions into getNextRecord
    std::string searched_name_;

    const std::string database_name_;

    const RECORDS& getRecords(int zone_id) const {
        if (zone_id == READONLY_ZONE_ID) {
            return (readonly_records);
        } else if (zone_id == WRITABLE_ZONE_ID) {
            return (update_records);
        }
        return (empty_records);
    }

    // Adds one record to the current name in the database
    // The actual data will not be added to 'records' until
    // addCurName() is called
    void addRecord(const std::string& type,
                   const std::string& ttl,
                   const std::string& sigtype,
                   const std::string& rdata) {
        std::vector<std::string> columns;
        columns.push_back(type);
        columns.push_back(ttl);
        columns.push_back(sigtype);
        columns.push_back(rdata);
        cur_name.push_back(columns);
    }

    // Adds all records we just built with calls to addRecords
    // to the actual fake database. This will clear cur_name,
    // so we can immediately start adding new records.
    void addCurName(const std::string& name) {
        ASSERT_EQ(0, readonly_records.count(name));
        readonly_records[name] = cur_name;
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

        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("AAAA", "3600", "", "2001:db8::1");
        addRecord("A", "3600", "", "192.0.2.2");
        addCurName("www2.example.org.");

        addRecord("CNAME", "3600", "", "www.example.org.");
        addCurName("cname.example.org.");

        // some DNSSEC-'signed' data
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
        addRecord("AAAA", "3600", "", "2001:db8::1");
        addRecord("AAAA", "3600", "", "2001:db8::2");
        addRecord("RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("signed1.example.org.");
        addRecord("CNAME", "3600", "", "www.example.org.");
        addRecord("RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("signedcname1.example.org.");
        // special case might fail; sig is for cname, which isn't there (should be ignored)
        // (ignoring of 'normal' other type is done above by www.)
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("acnamesig1.example.org.");

        // let's pretend we have a database that is not careful
        // about the order in which it returns data
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("AAAA", "3600", "", "2001:db8::2");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("AAAA", "3600", "", "2001:db8::1");
        addCurName("signed2.example.org.");
        addRecord("RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("CNAME", "3600", "", "www.example.org.");
        addCurName("signedcname2.example.org.");

        addRecord("RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("acnamesig2.example.org.");

        addRecord("RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addRecord("A", "3600", "", "192.0.2.1");
        addCurName("acnamesig3.example.org.");

        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("A", "360", "", "192.0.2.2");
        addCurName("ttldiff1.example.org.");
        addRecord("A", "360", "", "192.0.2.1");
        addRecord("A", "3600", "", "192.0.2.2");
        addCurName("ttldiff2.example.org.");

        // also add some intentionally bad data
        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("CNAME", "3600", "", "www.example.org.");
        addCurName("badcname1.example.org.");

        addRecord("CNAME", "3600", "", "www.example.org.");
        addRecord("A", "3600", "", "192.0.2.1");
        addCurName("badcname2.example.org.");

        addRecord("CNAME", "3600", "", "www.example.org.");
        addRecord("CNAME", "3600", "", "www.example2.org.");
        addCurName("badcname3.example.org.");

        addRecord("A", "3600", "", "bad");
        addCurName("badrdata.example.org.");

        addRecord("BAD_TYPE", "3600", "", "192.0.2.1");
        addCurName("badtype.example.org.");

        addRecord("A", "badttl", "", "192.0.2.1");
        addCurName("badttl.example.org.");

        addRecord("A", "badttl", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "", "A 5 3 3600 somebaddata 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("badsig.example.org.");

        addRecord("A", "3600", "", "192.0.2.1");
        addRecord("RRSIG", "3600", "TXT", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
        addCurName("badsigtype.example.org.");
    }
};

class DatabaseClientTest : public ::testing::Test {
protected:
    DatabaseClientTest() : qname("www.example.org"), qtype("A"), rrttl(3600) {
        createClient();

        // set up the commonly used finder.
        DataSourceClient::FindResult zone(
            client_->findZone(Name("example.org")));
        assert(zone.code == result::SUCCESS);
        finder = dynamic_pointer_cast<DatabaseClient::Finder>(
            zone.zone_finder);

        rrset.reset(new RRset(qname, RRClass::IN(), qtype, rrttl));
        // Adding an IN/A RDATA.  Intentionally using different data
        // than the initial data configured in MockAccessor::fillData().
        rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                           "192.0.2.2"));

        rrsigset.reset(new RRset(qname, RRClass::IN(), RRType::RRSIG(),
                                 rrttl));
        rrsigset->addRdata(rdata::createRdata(rrsigset->getType(),
                                              rrsigset->getClass(),
                                              "A 5 3 0 20000101000000 "
                                              "20000201000000 0 example.org. "
                                              "FAKEFAKEFAKE"));
    }
    /*
     * We initialize the client from a function, so we can call it multiple
     * times per test.
     */
    void createClient() {
        current_accessor_ = new MockAccessor();
        client_.reset(new DatabaseClient(RRClass::IN(),
                                         shared_ptr<DatabaseAccessor>(
                                             current_accessor_)));
    }
    // Will be deleted by client_, just keep the current value for comparison.
    MockAccessor* current_accessor_;
    shared_ptr<DatabaseClient> client_;
    const std::string database_name_;

    // The zone finder of the test zone commonly used in various tests.
    shared_ptr<DatabaseClient::Finder> finder;

    const Name qname;           // commonly used name to be found
    const RRType qtype;         // commonly used RR type with qname
    const RRTTL rrttl;          // commonly used RR TTL
    RRsetPtr rrset;             // for adding/deleting an RRset
    RRsetPtr rrsigset;          // for adding/deleting an RRset

    ZoneUpdaterPtr updater;
    const std::vector<std::string> empty_rdatas; // for NXRRSET/NXDOMAIN
    std::vector<std::string> expected_rdatas;
    std::vector<std::string> expected_sig_rdatas;

    /**
     * Check the zone finder is a valid one and references the zone ID and
     * database available here.
     */
    void checkZoneFinder(const DataSourceClient::FindResult& zone) {
        ASSERT_NE(ZoneFinderPtr(), zone.zone_finder) << "No zone finder";
        shared_ptr<DatabaseClient::Finder> finder(
            dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
        ASSERT_NE(shared_ptr<DatabaseClient::Finder>(), finder) <<
            "Wrong type of finder";
        EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
        EXPECT_EQ(current_accessor_, &finder->getAccessor());
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

TEST_F(DatabaseClientTest, noAccessorException) {
    EXPECT_THROW(DatabaseClient(RRClass::IN(), shared_ptr<DatabaseAccessor>()),
                 isc::InvalidParameter);
}

TEST_F(DatabaseClientTest, startUpdate) {
    // startUpdate will succeed only when there's an exact match zone.

    EXPECT_EQ(ZoneUpdaterPtr(),
              client_->startUpdateZone(Name("example.com"), false));
    EXPECT_NE(ZoneUpdaterPtr(),
              client_->startUpdateZone(Name("example.org"), false));
    EXPECT_EQ(ZoneUpdaterPtr(),
              client_->startUpdateZone(Name("sub.example.org"), false));
}

namespace {
// checks if the given rrset matches the
// given name, class, type and rdatas
void
checkRRset(isc::dns::ConstRRsetPtr rrset,
           const isc::dns::Name& name,
           const isc::dns::RRClass& rrclass,
           const isc::dns::RRType& rrtype,
           const isc::dns::RRTTL& rrttl,
           const std::vector<std::string>& rdatas) {
    isc::dns::RRsetPtr expected_rrset(
        new isc::dns::RRset(name, rrclass, rrtype, rrttl));
    for (unsigned int i = 0; i < rdatas.size(); ++i) {
        expected_rrset->addRdata(
            isc::dns::rdata::createRdata(rrtype, rrclass,
                                         rdatas[i]));
    }
    isc::testutils::rrsetCheck(expected_rrset, rrset);
}

void
doFindTest(ZoneFinder& finder,
           const isc::dns::Name& name,
           const isc::dns::RRType& type,
           const isc::dns::RRType& expected_type,
           const isc::dns::RRTTL expected_ttl,
           ZoneFinder::Result expected_result,
           const std::vector<std::string>& expected_rdatas,
           const std::vector<std::string>& expected_sig_rdatas)
{
    ZoneFinder::FindResult result =
        finder.find(name, type, NULL, ZoneFinder::FIND_DEFAULT);
    ASSERT_EQ(expected_result, result.code) << name << " " << type;
    if (expected_rdatas.size() > 0) {
        checkRRset(result.rrset, name, finder.getClass(),
                   expected_type, expected_ttl, expected_rdatas);

        if (expected_sig_rdatas.size() > 0) {
            checkRRset(result.rrset->getRRsig(), name,
                       finder.getClass(), isc::dns::RRType::RRSIG(),
                       expected_ttl, expected_sig_rdatas);
        } else {
            EXPECT_EQ(isc::dns::RRsetPtr(), result.rrset->getRRsig());
        }
    } else {
        EXPECT_EQ(isc::dns::RRsetPtr(), result.rrset);
    }
}
} // end anonymous namespace

TEST_F(DatabaseClientTest, find) {
    EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("www2.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("2001:db8::1");
    expected_rdatas.push_back("2001:db8::2");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               isc::dns::RRTTL(3600),
               ZoneFinder::NXRRSET,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("www.example.org.");
    doFindTest(*finder, isc::dns::Name("cname.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::CNAME(),
               isc::dns::RRTTL(3600),
               ZoneFinder::CNAME,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("www.example.org.");
    doFindTest(*finder, isc::dns::Name("cname.example.org."),
               isc::dns::RRType::CNAME(), isc::dns::RRType::CNAME(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    doFindTest(*finder, isc::dns::Name("doesnotexist.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::NXDOMAIN,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("2001:db8::1");
    expected_rdatas.push_back("2001:db8::2");
    expected_sig_rdatas.push_back("AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               isc::dns::RRTTL(3600),
               ZoneFinder::NXRRSET,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("www.example.org.");
    expected_sig_rdatas.push_back("CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signedcname1.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::CNAME(),
               isc::dns::RRTTL(3600),
               ZoneFinder::CNAME,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("2001:db8::2");
    expected_rdatas.push_back("2001:db8::1");
    expected_sig_rdatas.push_back("AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               isc::dns::RRTTL(3600),
               ZoneFinder::NXRRSET,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("www.example.org.");
    expected_sig_rdatas.push_back("CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signedcname2.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::CNAME(),
               isc::dns::RRTTL(3600),
               ZoneFinder::CNAME,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());


    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig1.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig2.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig3.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("ttldiff1.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("ttldiff2.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());

    EXPECT_THROW(finder->find(isc::dns::Name("badcname1.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("badcname2.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("badcname3.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("badrdata.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("badtype.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("badttl.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("badsig.example.org."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());

    // Trigger the hardcoded exceptions and see if find() has cleaned up
    EXPECT_THROW(finder->find(isc::dns::Name("dsexception.in.search."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("iscexception.in.search."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("basicexception.in.search."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 std::exception);
    EXPECT_FALSE(current_accessor_->searchRunning());

    EXPECT_THROW(finder->find(isc::dns::Name("dsexception.in.getnext."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("iscexception.in.getnext."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(current_accessor_->searchRunning());
    EXPECT_THROW(finder->find(isc::dns::Name("basicexception.in.getnext."),
                                              isc::dns::RRType::A(),
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 std::exception);
    EXPECT_FALSE(current_accessor_->searchRunning());

    // This RRSIG has the wrong sigtype field, which should be
    // an error if we decide to keep using that field
    // Right now the field is ignored, so it does not error
    expected_rdatas.clear();
    expected_sig_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("badsigtype.example.org."),
               isc::dns::RRType::A(), isc::dns::RRType::A(),
               isc::dns::RRTTL(3600),
               ZoneFinder::SUCCESS,
               expected_rdatas, expected_sig_rdatas);
    EXPECT_FALSE(current_accessor_->searchRunning());
}

TEST_F(DatabaseClientTest, updaterFinder) {
    updater = client_->startUpdateZone(Name("example.org"), false);
    ASSERT_TRUE(updater);

    // If this update isn't replacing the zone, the finder should work
    // just like the normal find() case.
    EXPECT_EQ(WRITABLE_ZONE_ID, dynamic_cast<DatabaseClient::Finder&>(
                  updater->getFinder()).zone_id());
    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    doFindTest(updater->getFinder(), Name("www.example.org."),
               qtype, qtype, rrttl, ZoneFinder::SUCCESS,
               expected_rdatas, empty_rdatas);

    // When replacing the zone, the updater's finder shouldn't see anything
    // in the zone until something is added.
    updater = client_->startUpdateZone(Name("example.org"), true);
    ASSERT_TRUE(updater);
    EXPECT_EQ(WRITABLE_ZONE_ID, dynamic_cast<DatabaseClient::Finder&>(
                  updater->getFinder()).zone_id());
    doFindTest(updater->getFinder(), Name("www.example.org."),
               RRType::A(), RRType::A(), RRTTL(3600), ZoneFinder::NXDOMAIN,
               empty_rdatas, empty_rdatas);
}

TEST_F(DatabaseClientTest, flushZone) {
    // A simple update case: flush the entire zone

    // Before update, the name exists.
    ZoneFinderPtr finder = client_->findZone(Name("example.org")).zone_finder;
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname, qtype).code);

    // start update in the replace mode.  the normal finder should still
    // be able to see the record, but the updater's finder shouldn't.
    updater = client_->startUpdateZone(Name("example.org"), true);
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname, qtype).code);
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              updater->getFinder().find(qname, qtype).code);

    // commit the update.  now the normal finder shouldn't see it.
    updater->commit();
    EXPECT_EQ(ZoneFinder::NXDOMAIN, finder->find(qname, qtype).code);

    // Check rollback wasn't accidentally performed.
    EXPECT_FALSE(current_accessor_->isRollbacked());
}

TEST_F(DatabaseClientTest, updateCancel) {
    // similar to the previous test, but destruct the updater before commit.

    ZoneFinderPtr finder = client_->findZone(Name("example.org")).zone_finder;
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname, qtype).code);

    updater = client_->startUpdateZone(Name("example.org"), true);
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              updater->getFinder().find(qname, qtype).code);
    // DB should not have been rolled back yet.
    EXPECT_FALSE(current_accessor_->isRollbacked());
    updater.reset();            // destruct without commit

    // reset() should have triggered rollback (although it doesn't affect
    // anything to the mock accessor implementation except for the result of
    // isRollbacked())
    EXPECT_TRUE(current_accessor_->isRollbacked());
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(qname, qtype).code);
}

TEST_F(DatabaseClientTest, duplicateCommit) {
    // duplicate commit.  should result in exception.
    updater = client_->startUpdateZone(Name("example.org"), true);
    updater->commit();
    EXPECT_THROW(updater->commit(), DataSourceError);
}

TEST_F(DatabaseClientTest, addRRsetToNewZone) {
    // Add a single RRset to a fresh empty zone
    updater = client_->startUpdateZone(Name("example.org"), true);
    updater->addRRset(*rrset);

    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }

    // Similar to the previous case, but with RRSIG
    updater = client_->startUpdateZone(Name("example.org"), true);
    updater->addRRset(*rrset);
    updater->addRRset(*rrsigset);

    // confirm the expected columns were passed to the mock accessor.
    const char* const rrsig_added[] = {
        "www.example.org.", "org.example.www.", "3600", "RRSIG", "A",
        "A 5 3 0 20000101000000 20000201000000 0 example.org. FAKEFAKEFAKE"
    };
    int i = 0;
    BOOST_FOREACH(const string& column, current_accessor_->getLastAdded()) {
        EXPECT_EQ(rrsig_added[i++], column);
    }

    expected_sig_rdatas.clear();
    expected_sig_rdatas.push_back(rrsig_added[DatabaseAccessor::ADD_RDATA]);
    {
        SCOPED_TRACE("add RRset with RRSIG");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, expected_sig_rdatas);
    }
}

TEST_F(DatabaseClientTest, addRRsetToCurrentZone) {
    // Similar to the previous test, but not replacing the existing data.
    updater = client_->startUpdateZone(Name("example.org"), false);
    updater->addRRset(*rrset);

    // We should see both old and new data.
    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
    updater->commit();
    {
        SCOPED_TRACE("add RRset after commit");
        doFindTest(*finder, qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, addMultipleRRs) {
    // Similar to the previous case, but the added RRset contains multiple
    // RRs.
    updater = client_->startUpdateZone(Name("example.org"), false);
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "192.0.2.3"));
    updater->addRRset(*rrset);
    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.2");
    expected_rdatas.push_back("192.0.2.3");
    {
        SCOPED_TRACE("add multiple RRs");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, addRRsetOfLargerTTL) {
    // Similar to the previous one, but the TTL of the added RRset is larger
    // than that of the existing record.  The finder should use the smaller
    // one.
    updater = client_->startUpdateZone(Name("example.org"), false);
    rrset->setTTL(RRTTL(7200));
    updater->addRRset(*rrset);

    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of larger TTL");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, addRRsetOfSmallerTTL) {
    // Similar to the previous one, but the added RRset has a smaller TTL.
    // The added TTL should be used by the finder.
    updater = client_->startUpdateZone(Name("example.org"), false);
    rrset->setTTL(RRTTL(1800));
    updater->addRRset(*rrset);

    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of smaller TTL");
        doFindTest(updater->getFinder(), qname, qtype, qtype, RRTTL(1800),
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, addSameRR) {
    // Add the same RR as that is already in the data source.
    // Currently the add interface doesn't try to suppress the duplicate,
    // neither does the finder.  We may want to revisit it in future versions.

    updater = client_->startUpdateZone(Name("example.org"), false);
    rrset.reset(new RRset(qname, RRClass::IN(), qtype, rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "192.0.2.1"));
    updater->addRRset(*rrset);
    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.1");
    expected_rdatas.push_back("192.0.2.1");
    {
        SCOPED_TRACE("add same RR");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, addDeviantRR) {
    updater = client_->startUpdateZone(Name("example.org"), false);

    // RR class mismatch.  This should be detected and rejected.
    rrset.reset(new RRset(qname, RRClass::CH(), RRType::TXT(), rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "test text"));
    EXPECT_THROW(updater->addRRset(*rrset), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    rrset.reset(new RRset(Name("example.com"), RRClass::IN(), qtype, rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "192.0.2.100"));
    updater->addRRset(*rrset);

    expected_rdatas.clear();
    expected_rdatas.push_back("192.0.2.100");
    {
        // Note: with the find() implementation being more strict about
        // zone cuts, this test may fail.  Then the test should be updated.
        SCOPED_TRACE("add out-of-zone RR");
        doFindTest(updater->getFinder(), Name("example.com"), qtype, qtype,
                   rrttl, ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, addEmptyRRset) {
    updater = client_->startUpdateZone(Name("example.org"), false);
    rrset.reset(new RRset(qname, RRClass::IN(), qtype, rrttl));
    EXPECT_THROW(updater->addRRset(*rrset), DataSourceError);
}

TEST_F(DatabaseClientTest, addAfterCommit) {
   updater = client_->startUpdateZone(Name("example.org"), false);
   updater->commit();
   EXPECT_THROW(updater->addRRset(*rrset), DataSourceError);
}

TEST_F(DatabaseClientTest, deleteRRset) {
    rrset.reset(new RRset(qname, RRClass::IN(), qtype, rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "192.0.2.1"));

    // Delete one RR from an RRset
    updater = client_->startUpdateZone(Name("example.org"), false);
    updater->deleteRRset(*rrset);

    // Delete the only RR of a name
    rrset.reset(new RRset(Name("cname.example.org"), RRClass::IN(),
                          RRType::CNAME(), rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "www.example.org"));
    updater->deleteRRset(*rrset);

    // The updater finder should immediately see the deleted results.
    {
        SCOPED_TRACE("delete RRset");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::NXRRSET, empty_rdatas, empty_rdatas);
        doFindTest(updater->getFinder(), Name("cname.example.org"),
                   qtype, qtype, rrttl, ZoneFinder::NXDOMAIN,
                   empty_rdatas, empty_rdatas);
    }

    // before committing the change, the original finder should see the
    // original record.
    {
        SCOPED_TRACE("delete RRset before commit");
        expected_rdatas.push_back("192.0.2.1");
        doFindTest(*finder, qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);

        expected_rdatas.clear();
        expected_rdatas.push_back("www.example.org.");
        doFindTest(*finder, Name("cname.example.org"), qtype,
                   RRType::CNAME(), rrttl,
                   ZoneFinder::CNAME, expected_rdatas, empty_rdatas);
    }

    // once committed, the record should be removed from the original finder's
    // view, too.
    updater->commit();
    {
        SCOPED_TRACE("delete RRset after commit");
        doFindTest(*finder, qname, qtype, qtype, rrttl,
                   ZoneFinder::NXRRSET, empty_rdatas, empty_rdatas);
        doFindTest(*finder, Name("cname.example.org"),
                   qtype, qtype, rrttl, ZoneFinder::NXDOMAIN,
                   empty_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, deleteRRsetToNXDOMAIN) {
    // similar to the previous case, but it removes the only record of the
    // given name.  a subsequent find() should result in NXDOMAIN.
    rrset.reset(new RRset(Name("cname.example.org"), RRClass::IN(),
                          RRType::CNAME(), rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "www.example.org"));

    updater = client_->startUpdateZone(Name("example.org"), false);
    updater->deleteRRset(*rrset);
    {
        SCOPED_TRACE("delete RRset to NXDOMAIN");
        doFindTest(updater->getFinder(), Name("cname.example.org"), qtype,
                   qtype, rrttl, ZoneFinder::NXDOMAIN, empty_rdatas,
                   empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, deleteMultipleRRs) {
    rrset.reset(new RRset(qname, RRClass::IN(), RRType::AAAA(), rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "2001:db8::1"));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "2001:db8::2"));

    updater = client_->startUpdateZone(Name("example.org"), false);
    updater->deleteRRset(*rrset);

    {
        SCOPED_TRACE("delete multiple RRs");
        doFindTest(updater->getFinder(), qname, RRType::AAAA(), qtype, rrttl,
                   ZoneFinder::NXRRSET, empty_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, partialDelete) {
    rrset.reset(new RRset(qname, RRClass::IN(), RRType::AAAA(), rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "2001:db8::1"));
    // This does not exist in the test data source:
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "2001:db8::3"));

    // deleteRRset should succeed "silently", and subsequent find() should
    // find the remaining RR.
    updater = client_->startUpdateZone(Name("example.org"), false);
    updater->deleteRRset(*rrset);
    {
        SCOPED_TRACE("partial delete");
        expected_rdatas.push_back("2001:db8::2");
        doFindTest(updater->getFinder(), qname, RRType::AAAA(),
                   RRType::AAAA(), rrttl, ZoneFinder::SUCCESS,
                   expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, deleteNoMatch) {
    // similar to the previous test, but there's not even a match in the
    // specified RRset.  Essentially there's no difference in the result.
    updater = client_->startUpdateZone(Name("example.org"), false);
    updater->deleteRRset(*rrset);
    {
        SCOPED_TRACE("delete no match");
        expected_rdatas.push_back("192.0.2.1");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::SUCCESS, expected_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, deleteWithDifferentTTL) {
    // Our delete interface simply ignores TTL (may change in a future version)
    rrset.reset(new RRset(qname, RRClass::IN(), qtype, RRTTL(1800)));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "192.0.2.1"));
    updater = client_->startUpdateZone(Name("example.org"), false);
    updater->deleteRRset(*rrset);
    {
        SCOPED_TRACE("delete RRset with a different TTL");
        doFindTest(updater->getFinder(), qname, qtype, qtype, rrttl,
                   ZoneFinder::NXRRSET, empty_rdatas, empty_rdatas);
    }
}

TEST_F(DatabaseClientTest, deleteDeviantRR) {
    updater = client_->startUpdateZone(Name("example.org"), false);

    // RR class mismatch.  This should be detected and rejected.
    rrset.reset(new RRset(qname, RRClass::CH(), RRType::TXT(), rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "test text"));
    EXPECT_THROW(updater->deleteRRset(*rrset), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    rrset.reset(new RRset(Name("example.com"), RRClass::IN(), qtype, rrttl));
    rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                       "192.0.2.100"));
    EXPECT_NO_THROW(updater->deleteRRset(*rrset));
}

TEST_F(DatabaseClientTest, deleteAfterCommit) {
   updater = client_->startUpdateZone(Name("example.org"), false);
   updater->commit();
   EXPECT_THROW(updater->deleteRRset(*rrset), DataSourceError);
}

TEST_F(DatabaseClientTest, deleteEmptyRRset) {
    updater = client_->startUpdateZone(Name("example.org"), false);
    rrset.reset(new RRset(qname, RRClass::IN(), qtype, rrttl));
    EXPECT_THROW(updater->deleteRRset(*rrset), DataSourceError);
}
}
