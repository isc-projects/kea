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
#include <datasrc/sqlite3_accessor.h>

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

// Imaginary zone IDs used in the mock accessor below.
const int READONLY_ZONE_ID = 42;
const int WRITABLE_ZONE_ID = 4200;

// Commonly used test data
const char* const TEST_RECORDS[][5] = {
    // some plain data
    {"www.example.org.", "A", "3600", "", "192.0.2.1"},
    {"www.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"www.example.org.", "AAAA", "3600", "", "2001:db8::2"},

    {"www2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"www2.example.org.","AAAA", "3600", "", "2001:db8::1"},
    {"www2.example.org.", "A", "3600", "", "192.0.2.2"},

    {"cname.example.org.", "CNAME", "3600", "", "www.example.org."},

    // some DNSSEC-'signed' data
    {"signed1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"signed1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signed1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE"},
    {"signed1.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"signed1.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"signed1.example.org.", "RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"signedcname1.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"signedcname1.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // special case might fail; sig is for cname, which isn't there (should be ignored)
    // (ignoring of 'normal' other type is done above by www.)
    {"acnamesig1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"acnamesig1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig1.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // let's pretend we have a database that is not careful
    // about the order in which it returns data
    {"signed2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"signed2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"signed2.example.org.", "RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "AAAA", "3600", "", "2001:db8::1"},

    {"signedcname2.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signedcname2.example.org.", "CNAME", "3600", "", "www.example.org."},

    {"acnamesig2.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"acnamesig2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"acnamesig3.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig3.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig3.example.org.", "A", "3600", "", "192.0.2.1"},

    {"ttldiff1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"ttldiff1.example.org.", "A", "360", "", "192.0.2.2"},

    {"ttldiff2.example.org.", "A", "360", "", "192.0.2.1"},
    {"ttldiff2.example.org.", "A", "3600", "", "192.0.2.2"},

    // also add some intentionally bad data
    {"badcname1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"badcname1.example.org.", "CNAME", "3600", "", "www.example.org."},

    {"badcname2.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"badcname2.example.org.", "A", "3600", "", "192.0.2.1"},

    {"badcname3.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"badcname3.example.org.", "CNAME", "3600", "", "www.example2.org."},

    {"badrdata.example.org.", "A", "3600", "", "bad"},

    {"badtype.example.org.", "BAD_TYPE", "3600", "", "192.0.2.1"},

    {"badttl.example.org.", "A", "badttl", "", "192.0.2.1"},

    {"badsig.example.org.", "A", "badttl", "", "192.0.2.1"},
    {"badsig.example.org.", "RRSIG", "3600", "", "A 5 3 3600 somebaddata 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"badsigtype.example.org.", "A", "3600", "", "192.0.2.1"},
    {"badsigtype.example.org.", "RRSIG", "3600", "TXT", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {NULL, NULL, NULL, NULL, NULL},
};

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
        const char* prev_name = NULL;
        for (int i = 0; TEST_RECORDS[i][0] != NULL; ++i) {
            if (prev_name != NULL &&
                strcmp(prev_name, TEST_RECORDS[i][0]) != 0) {
                addCurName(prev_name);
            }
            prev_name = TEST_RECORDS[i][0];
            addRecord(TEST_RECORDS[i][1], TEST_RECORDS[i][2],
                      TEST_RECORDS[i][3], TEST_RECORDS[i][4]);
        }
        addCurName(prev_name);
    }
};

class TestSQLite3Accessor : public SQLite3Accessor {
public:
    TestSQLite3Accessor() : SQLite3Accessor(
        TEST_DATA_BUILDDIR "/rwtest.sqlite3.copied",
        RRClass::IN())
    {
        startUpdateZone("example.org.", true);
        vector<string> columns;
        for (int i = 0; TEST_RECORDS[i][0] != NULL; ++i) {
            columns.assign(DatabaseAccessor::ADD_COLUMN_COUNT, "");
            columns[ADD_NAME] = TEST_RECORDS[i][0];
            columns[ADD_REV_NAME] = Name(columns[ADD_NAME]).reverse().toText();
            columns[ADD_TYPE] = TEST_RECORDS[i][1];
            columns[ADD_TTL] = TEST_RECORDS[i][2];
            columns[ADD_SIGTYPE] = TEST_RECORDS[i][3];
            columns[ADD_RDATA] = TEST_RECORDS[i][4];

            addRecordToZone(columns);
        }
        commitUpdateZone();
    }
};

template <typename ACCESSOR_TYPE>
class DatabaseClientTest : public ::testing::Test {
protected:
    DatabaseClientTest() : zname("example.org"), qname("www.example.org"),
                           qclass(RRClass::IN()), qtype(RRType::A()),
                           rrttl(3600)
    {
        createClient();

        // set up the commonly used finder.
        DataSourceClient::FindResult zone(
            client_->findZone(Name("example.org")));
        assert(zone.code == result::SUCCESS);
        finder = dynamic_pointer_cast<DatabaseClient::Finder>(
            zone.zone_finder);

        rrset.reset(new RRset(qname, qclass, qtype, rrttl));
        // Adding an IN/A RDATA.  Intentionally using different data
        // than the initial data configured in TEST_RECORDS.
        rrset->addRdata(rdata::createRdata(rrset->getType(), rrset->getClass(),
                                           "192.0.2.2"));

        rrsigset.reset(new RRset(qname, qclass, RRType::RRSIG(),
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
        current_accessor_ = new ACCESSOR_TYPE();
        is_mock_ = (dynamic_cast<MockAccessor*>(current_accessor_) != NULL);
        client_.reset(new DatabaseClient(qclass,
                                         shared_ptr<DatabaseAccessor>(
                                             current_accessor_)));
    }

    bool searchRunning(bool expected = false) const {
        if (is_mock_) {
            const MockAccessor* mock_accessor =
                dynamic_cast<const MockAccessor*>(current_accessor_);
            return (mock_accessor->searchRunning());
        } else {
            return (expected);
        }
    }

    bool isRollbacked(bool expected = false) const {
        if (is_mock_) {
            const MockAccessor* mock_accessor =
                dynamic_cast<const MockAccessor*>(current_accessor_);
            return (mock_accessor->isRollbacked());
        } else {
            return (expected);
        }
    }

    void checkLastAdded(const char* const expected[]) const {
        if (is_mock_) {
            const MockAccessor* mock_accessor =
                dynamic_cast<const MockAccessor*>(current_accessor_);
            int i = 0;
            BOOST_FOREACH(const string& column,
                          mock_accessor->getLastAdded()) {
                EXPECT_EQ(expected[i++], column);
            }
        }
    }

    // Some tests only work for MockAccessor.  We remember whether our accessor
    // is of that type.
    bool is_mock_;

    // Will be deleted by client_, just keep the current value for comparison.
    DatabaseAccessor* current_accessor_;
    shared_ptr<DatabaseClient> client_;
    const std::string database_name_;

    // The zone finder of the test zone commonly used in various tests.
    shared_ptr<DatabaseClient::Finder> finder;

    const Name zname;           // the zone name stored in the test data source
    const Name qname;           // commonly used name to be found
    const RRClass qclass;       // commonly used RR class with qname
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
        if (is_mock_) {
            EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
        }
        EXPECT_EQ(current_accessor_, &finder->getAccessor());
    }
};

typedef ::testing::Types<MockAccessor, TestSQLite3Accessor> TestAccessorTypes;
TYPED_TEST_CASE(DatabaseClientTest, TestAccessorTypes);

TYPED_TEST(DatabaseClientTest, zoneNotFound) {
    DataSourceClient::FindResult zone(
        this->client_->findZone(Name("example.com")));
    EXPECT_EQ(result::NOTFOUND, zone.code);
}

TYPED_TEST(DatabaseClientTest, exactZone) {
    DataSourceClient::FindResult zone( this->client_->findZone(this->zname));
    EXPECT_EQ(result::SUCCESS, zone.code);
    this->checkZoneFinder(zone);
}

TYPED_TEST(DatabaseClientTest, superZone) {
    DataSourceClient::FindResult zone(this->client_->findZone(Name(
        "sub.example.org")));
    EXPECT_EQ(result::PARTIALMATCH, zone.code);
    this->checkZoneFinder(zone);
}

// This test doesn't depend on derived accessor class, so we use TEST().
TEST(GenericDatabaseClientTest, noAccessorException) {
    EXPECT_THROW(DatabaseClient(RRClass::IN(), shared_ptr<DatabaseAccessor>()),
                 isc::InvalidParameter);
}

TYPED_TEST(DatabaseClientTest, startUpdate) {
    // startUpdate will succeed only when there's an exact match zone.

    EXPECT_EQ(ZoneUpdaterPtr(),
              this->client_->startUpdateZone(Name("example.com"), false));
    EXPECT_NE(ZoneUpdaterPtr(),
              this->client_->startUpdateZone(this->zname, false));

    EXPECT_EQ(ZoneUpdaterPtr(),
              this->client_->startUpdateZone(Name("sub.example.org"), false));
}

// checks if the given rrset matches the
// given name, class, type and rdatas
void
checkRRset(isc::dns::ConstRRsetPtr rrset,
           const Name& name,
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
           const Name& name,
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

TYPED_TEST(DatabaseClientTest, find) {
    if (this->is_mock_) {
        EXPECT_EQ(READONLY_ZONE_ID, this->finder->zone_id());
    }
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    doFindTest(*this->finder, Name("www.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.2");
    doFindTest(*this->finder, Name("www2.example.org."),
               this->qtype, this->qtype,
               this->rrttl,
               ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("2001:db8::1");
    this->expected_rdatas.push_back("2001:db8::2");
    doFindTest(*this->finder, Name("www.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl,
               ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    doFindTest(*this->finder, Name("www.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               this->rrttl, ZoneFinder::NXRRSET,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("www.example.org.");
    doFindTest(*this->finder, Name("cname.example.org."),
               this->qtype, isc::dns::RRType::CNAME(), this->rrttl,
               ZoneFinder::CNAME,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("www.example.org.");
    doFindTest(*this->finder, Name("cname.example.org."),
               isc::dns::RRType::CNAME(), isc::dns::RRType::CNAME(),
               this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    doFindTest(*this->finder, Name("doesnotexist.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::NXDOMAIN,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("signed1.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("2001:db8::1");
    this->expected_rdatas.push_back("2001:db8::2");
    this->expected_sig_rdatas.push_back("AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("signed1.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    doFindTest(*this->finder, Name("signed1.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(), this->rrttl,
               ZoneFinder::NXRRSET,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("www.example.org.");
    this->expected_sig_rdatas.push_back("CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("signedcname1.example.org."),
               this->qtype, isc::dns::RRType::CNAME(), this->rrttl,
               ZoneFinder::CNAME,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("signed2.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("2001:db8::2");
    this->expected_rdatas.push_back("2001:db8::1");
    this->expected_sig_rdatas.push_back("AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("signed2.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(), this->rrttl,
               ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    doFindTest(*this->finder, Name("signed2.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(), this->rrttl,
               ZoneFinder::NXRRSET,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("www.example.org.");
    this->expected_sig_rdatas.push_back("CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("signedcname2.example.org."),
               this->qtype, isc::dns::RRType::CNAME(), this->rrttl,
               ZoneFinder::CNAME,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());


    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("acnamesig1.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("acnamesig2.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("acnamesig3.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.2");
    doFindTest(*this->finder, Name("ttldiff1.example.org."),
               this->qtype, this->qtype, isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.2");
    doFindTest(*this->finder, Name("ttldiff2.example.org."),
               this->qtype, this->qtype, isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());

    EXPECT_THROW(this->finder->find(Name("badcname1.example.org."),
                                    this->qtype, NULL,
                                    ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(this->searchRunning());
    EXPECT_THROW(this->finder->find(Name("badcname2.example.org."),
                                    this->qtype, NULL,
                                    ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(this->searchRunning());
    EXPECT_THROW(this->finder->find(Name("badcname3.example.org."),
                                    this->qtype, NULL,
                                    ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(this->searchRunning());
    EXPECT_THROW(this->finder->find(Name("badrdata.example.org."),
                                    this->qtype, NULL,
                                    ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(this->searchRunning());
    EXPECT_THROW(this->finder->find(Name("badtype.example.org."),
                                    this->qtype, NULL,
                                    ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(this->searchRunning());
    EXPECT_THROW(this->finder->find(Name("badttl.example.org."),
                                    this->qtype, NULL,
                                    ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(this->searchRunning());
    EXPECT_THROW(this->finder->find(Name("badsig.example.org."),
                                    this->qtype, NULL,
                                    ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_FALSE(this->searchRunning());

    // Trigger the hardcoded exceptions and see if find() has cleaned up.
    // This can only work for a mock accessor.
    if (this->is_mock_) {
        EXPECT_THROW(this->finder->find(Name("dsexception.in.search."),
                                        this->qtype, NULL,
                                        ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_FALSE(this->searchRunning());
        EXPECT_THROW(this->finder->find(Name("iscexception.in.search."),
                                        this->qtype, NULL,
                                        ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_FALSE(this->searchRunning());
        EXPECT_THROW(this->finder->find(
                         Name("basicexception.in.search."),
                         this->qtype, NULL, ZoneFinder::FIND_DEFAULT),
                     std::exception);
        EXPECT_FALSE(this->searchRunning());

        EXPECT_THROW(this->finder->find(Name("dsexception.in.getnext."),
                                        this->qtype, NULL,
                                        ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_FALSE(this->searchRunning());
        EXPECT_THROW(this->finder->find(Name("iscexception.in.getnext."),
                                        this->qtype, NULL,
                                        ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_FALSE(this->searchRunning());
        EXPECT_THROW(this->finder->find(Name("basicexception.in.getnext."),
                                        this->qtype, NULL,
                                        ZoneFinder::FIND_DEFAULT),
                     std::exception);
        EXPECT_FALSE(this->searchRunning());
    }

    // This RRSIG has the wrong sigtype field, which should be
    // an error if we decide to keep using that field
    // Right now the field is ignored, so it does not error
    this->expected_rdatas.clear();
    this->expected_sig_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_sig_rdatas.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*this->finder, Name("badsigtype.example.org."),
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->expected_sig_rdatas);
    EXPECT_FALSE(this->searchRunning());
}

TYPED_TEST(DatabaseClientTest, updaterFinder) {
    this->updater = this->client_->startUpdateZone(this->zname, false);
    ASSERT_TRUE(this->updater);

    // If this update isn't replacing the zone, the finder should work
    // just like the normal find() case.
    if (this->is_mock_) {
        EXPECT_EQ(WRITABLE_ZONE_ID, dynamic_cast<DatabaseClient::Finder&>(
                      this->updater->getFinder()).zone_id());
    }
    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    doFindTest(this->updater->getFinder(), this->qname,
               this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
               this->expected_rdatas, this->empty_rdatas);

    // When replacing the zone, the updater's finder shouldn't see anything
    // in the zone until something is added.
    this->updater.reset();
    this->updater = this->client_->startUpdateZone(this->zname, true);
    ASSERT_TRUE(this->updater);
    if (this->is_mock_) {
        EXPECT_EQ(WRITABLE_ZONE_ID, dynamic_cast<DatabaseClient::Finder&>(
                      this->updater->getFinder()).zone_id());
    }
    doFindTest(this->updater->getFinder(), this->qname,
               RRType::A(), RRType::A(), RRTTL(3600), ZoneFinder::NXDOMAIN,
               this->empty_rdatas, this->empty_rdatas);
}

TYPED_TEST(DatabaseClientTest, flushZone) {
    // A simple update case: flush the entire zone

    // Before update, the name exists.
    EXPECT_EQ(ZoneFinder::SUCCESS, this->finder->find(this->qname,
                                                      this->qtype).code);

    // start update in the replace mode.  the normal finder should still
    // be able to see the record, but the updater's finder shouldn't.
    this->updater = this->client_->startUpdateZone(this->zname, true);
    EXPECT_EQ(ZoneFinder::SUCCESS,
              this->finder->find(this->qname, this->qtype).code);
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              this->updater->getFinder().find(this->qname, this->qtype).code);

    // commit the update.  now the normal finder shouldn't see it.
    this->updater->commit();
    EXPECT_EQ(ZoneFinder::NXDOMAIN, this->finder->find(this->qname,
                                                       this->qtype).code);

    // Check rollback wasn't accidentally performed.
    EXPECT_FALSE(this->isRollbacked());
}


TYPED_TEST(DatabaseClientTest, updateCancel) {
    // similar to the previous test, but destruct the updater before commit.

    ZoneFinderPtr finder = this->client_->findZone(this->zname).zone_finder;
    EXPECT_EQ(ZoneFinder::SUCCESS, this->finder->find(this->qname,
                                                      this->qtype).code);

    this->updater = this->client_->startUpdateZone(this->zname, true);
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              this->updater->getFinder().find(this->qname, this->qtype).code);
    // DB should not have been rolled back yet.
    EXPECT_FALSE(this->isRollbacked());
    this->updater.reset();            // destruct without commit

    // reset() should have triggered rollback (although it doesn't affect
    // anything to the mock accessor implementation except for the result of
    // isRollbacked())
    EXPECT_TRUE(this->isRollbacked(true));
    EXPECT_EQ(ZoneFinder::SUCCESS, this->finder->find(this->qname,
                                                      this->qtype).code);
}

TYPED_TEST(DatabaseClientTest, duplicateCommit) {
    // duplicate commit.  should result in exception.
    this->updater = this->client_->startUpdateZone(this->zname, true);
    this->updater->commit();
    EXPECT_THROW(this->updater->commit(), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, addRRsetToNewZone) {
    // Add a single RRset to a fresh empty zone
    this->updater = this->client_->startUpdateZone(this->zname, true);
    this->updater->addRRset(*this->rrset);

    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }

    // Similar to the previous case, but with RRSIG
    this->updater.reset();
    this->updater = this->client_->startUpdateZone(this->zname, true);
    this->updater->addRRset(*this->rrset);
    this->updater->addRRset(*this->rrsigset);

    // confirm the expected columns were passed to the accessor (if checkable).
    const char* const rrsig_added[] = {
        "www.example.org.", "org.example.www.", "3600", "RRSIG", "A",
        "A 5 3 0 20000101000000 20000201000000 0 example.org. FAKEFAKEFAKE"
    };
    this->checkLastAdded(rrsig_added);

    this->expected_sig_rdatas.clear();
    this->expected_sig_rdatas.push_back(
        rrsig_added[DatabaseAccessor::ADD_RDATA]);
    {
        SCOPED_TRACE("add RRset with RRSIG");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->expected_sig_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, addRRsetToCurrentZone) {
    // Similar to the previous test, but not replacing the existing data.
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->updater->addRRset(*this->rrset);

    // We should see both old and new data.
    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
    this->updater->commit();
    {
        SCOPED_TRACE("add RRset after commit");
        doFindTest(*this->finder, this->qname, this->qtype, this->qtype,
                   this->rrttl, ZoneFinder::SUCCESS, this->expected_rdatas,
                   this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, addMultipleRRs) {
    // Similar to the previous case, but the added RRset contains multiple
    // RRs.
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "192.0.2.3"));
    this->updater->addRRset(*this->rrset);
    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.2");
    this->expected_rdatas.push_back("192.0.2.3");
    {
        SCOPED_TRACE("add multiple RRs");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, addRRsetOfLargerTTL) {
    // Similar to the previous one, but the TTL of the added RRset is larger
    // than that of the existing record.  The finder should use the smaller
    // one.
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->rrset->setTTL(RRTTL(7200));
    this->updater->addRRset(*this->rrset);

    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of larger TTL");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, addRRsetOfSmallerTTL) {
    // Similar to the previous one, but the added RRset has a smaller TTL.
    // The added TTL should be used by the finder.
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->rrset->setTTL(RRTTL(1800));
    this->updater->addRRset(*this->rrset);

    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of smaller TTL");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, RRTTL(1800), ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, addSameRR) {
    // Add the same RR as that is already in the data source.
    // Currently the add interface doesn't try to suppress the duplicate,
    // neither does the finder.  We may want to revisit it in future versions.

    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->rrset.reset(new RRset(this->qname, this->qclass, this->qtype,
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "192.0.2.1"));
    this->updater->addRRset(*this->rrset);
    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.1");
    this->expected_rdatas.push_back("192.0.2.1");
    {
        SCOPED_TRACE("add same RR");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, addDeviantRR) {
    this->updater = this->client_->startUpdateZone(this->zname, false);

    // RR class mismatch.  This should be detected and rejected.
    this->rrset.reset(new RRset(this->qname, RRClass::CH(), RRType::TXT(),
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "test text"));
    EXPECT_THROW(this->updater->addRRset(*this->rrset), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    this->rrset.reset(new RRset(Name("example.com"), this->qclass, this->qtype,
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "192.0.2.100"));
    this->updater->addRRset(*this->rrset);

    this->expected_rdatas.clear();
    this->expected_rdatas.push_back("192.0.2.100");
    {
        // Note: with the find() implementation being more strict about
        // zone cuts, this test may fail.  Then the test should be updated.
        SCOPED_TRACE("add out-of-zone RR");
        doFindTest(this->updater->getFinder(), Name("example.com"),
                   this->qtype, this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, addEmptyRRset) {
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->rrset.reset(new RRset(this->qname, this->qclass, this->qtype,
                                this->rrttl));
    EXPECT_THROW(this->updater->addRRset(*this->rrset), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, addAfterCommit) {
   this->updater = this->client_->startUpdateZone(this->zname, false);
   this->updater->commit();
   EXPECT_THROW(this->updater->addRRset(*this->rrset), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, deleteRRset) {
    this->rrset.reset(new RRset(this->qname, this->qclass, this->qtype,
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "192.0.2.1"));

    // Delete one RR from an RRset
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->updater->deleteRRset(*this->rrset);

    // Delete the only RR of a name
    this->rrset.reset(new RRset(Name("cname.example.org"), this->qclass,
                          RRType::CNAME(), this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "www.example.org"));
    this->updater->deleteRRset(*this->rrset);

    // The updater finder should immediately see the deleted results.
    {
        SCOPED_TRACE("delete RRset");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::NXRRSET,
                   this->empty_rdatas, this->empty_rdatas);
        doFindTest(this->updater->getFinder(), Name("cname.example.org"),
                   this->qtype, this->qtype, this->rrttl, ZoneFinder::NXDOMAIN,
                   this->empty_rdatas, this->empty_rdatas);
    }

    // before committing the change, the original finder should see the
    // original record.
    {
        SCOPED_TRACE("delete RRset before commit");
        this->expected_rdatas.push_back("192.0.2.1");
        doFindTest(*this->finder, this->qname, this->qtype, this->qtype,
                   this->rrttl, ZoneFinder::SUCCESS, this->expected_rdatas,
                   this->empty_rdatas);

        this->expected_rdatas.clear();
        this->expected_rdatas.push_back("www.example.org.");
        doFindTest(*this->finder, Name("cname.example.org"), this->qtype,
                   RRType::CNAME(), this->rrttl, ZoneFinder::CNAME,
                   this->expected_rdatas, this->empty_rdatas);
    }

    // once committed, the record should be removed from the original finder's
    // view, too.
    this->updater->commit();
    {
        SCOPED_TRACE("delete RRset after commit");
        doFindTest(*this->finder, this->qname, this->qtype, this->qtype,
                   this->rrttl, ZoneFinder::NXRRSET, this->empty_rdatas,
                   this->empty_rdatas);
        doFindTest(*this->finder, Name("cname.example.org"),
                   this->qtype, this->qtype, this->rrttl, ZoneFinder::NXDOMAIN,
                   this->empty_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, deleteRRsetToNXDOMAIN) {
    // similar to the previous case, but it removes the only record of the
    // given name.  a subsequent find() should result in NXDOMAIN.
    this->rrset.reset(new RRset(Name("cname.example.org"), this->qclass,
                          RRType::CNAME(), this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "www.example.org"));

    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->updater->deleteRRset(*this->rrset);
    {
        SCOPED_TRACE("delete RRset to NXDOMAIN");
        doFindTest(this->updater->getFinder(), Name("cname.example.org"),
                   this->qtype, this->qtype, this->rrttl, ZoneFinder::NXDOMAIN,
                   this->empty_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, deleteMultipleRRs) {
    this->rrset.reset(new RRset(this->qname, this->qclass, RRType::AAAA(),
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "2001:db8::1"));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "2001:db8::2"));

    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->updater->deleteRRset(*this->rrset);

    {
        SCOPED_TRACE("delete multiple RRs");
        doFindTest(this->updater->getFinder(), this->qname, RRType::AAAA(),
                   this->qtype, this->rrttl, ZoneFinder::NXRRSET,
                   this->empty_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, partialDelete) {
    this->rrset.reset(new RRset(this->qname, this->qclass, RRType::AAAA(),
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "2001:db8::1"));
    // This does not exist in the test data source:
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "2001:db8::3"));

    // deleteRRset should succeed "silently", and subsequent find() should
    // find the remaining RR.
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->updater->deleteRRset(*this->rrset);
    {
        SCOPED_TRACE("partial delete");
        this->expected_rdatas.push_back("2001:db8::2");
        doFindTest(this->updater->getFinder(), this->qname, RRType::AAAA(),
                   RRType::AAAA(), this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, deleteNoMatch) {
    // similar to the previous test, but there's not even a match in the
    // specified RRset.  Essentially there's no difference in the result.
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->updater->deleteRRset(*this->rrset);
    {
        SCOPED_TRACE("delete no match");
        this->expected_rdatas.push_back("192.0.2.1");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::SUCCESS,
                   this->expected_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, deleteWithDifferentTTL) {
    // Our delete interface simply ignores TTL (may change in a future version)
    this->rrset.reset(new RRset(this->qname, this->qclass, this->qtype,
                                RRTTL(1800)));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "192.0.2.1"));
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->updater->deleteRRset(*this->rrset);
    {
        SCOPED_TRACE("delete RRset with a different TTL");
        doFindTest(this->updater->getFinder(), this->qname, this->qtype,
                   this->qtype, this->rrttl, ZoneFinder::NXRRSET,
                   this->empty_rdatas, this->empty_rdatas);
    }
}

TYPED_TEST(DatabaseClientTest, deleteDeviantRR) {
    this->updater = this->client_->startUpdateZone(this->zname, false);

    // RR class mismatch.  This should be detected and rejected.
    this->rrset.reset(new RRset(this->qname, RRClass::CH(), RRType::TXT(),
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "test text"));
    EXPECT_THROW(this->updater->deleteRRset(*this->rrset), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    this->rrset.reset(new RRset(Name("example.com"), this->qclass, this->qtype,
                                this->rrttl));
    this->rrset->addRdata(rdata::createRdata(this->rrset->getType(),
                                             this->rrset->getClass(),
                                             "192.0.2.100"));
    EXPECT_NO_THROW(this->updater->deleteRRset(*this->rrset));
}

TYPED_TEST(DatabaseClientTest, deleteAfterCommit) {
   this->updater = this->client_->startUpdateZone(this->zname, false);
   this->updater->commit();
   EXPECT_THROW(this->updater->deleteRRset(*this->rrset), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, deleteEmptyRRset) {
    this->updater = this->client_->startUpdateZone(this->zname, false);
    this->rrset.reset(new RRset(this->qname, this->qclass, this->qtype,
                                this->rrttl));
    EXPECT_THROW(this->updater->deleteRRset(*this->rrset), DataSourceError);
}
}
