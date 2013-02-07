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

#include <datasrc/database.h>
#include <datasrc/tests/faked_nsec3.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>
#include <dns/rrset_collection_base.h>
#include <dns/nsec3hash.h>

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>

namespace isc {
namespace datasrc {
namespace test {

// Commonly used test data
extern const char* const TEST_RECORDS[][5];

// NSEC3PARAM at the zone origin and its RRSIG.  These will be added
// separately for some NSEC3 related tests.
extern const char* TEST_NSEC3PARAM_RECORDS[][5];

// FIXME: Taken from a different test. Fill with proper data when creating a
// test.
extern const char* TEST_NSEC3_RECORDS[][5];

/**
 * Single journal entry in the mock database.
 *
 * All the members there are public for simplicity, as it only stores data.
 * We use the implicit constructor and operator. The members can't be const
 * because of the assignment operator (used in the vectors).
 */
struct JournalEntry {
    JournalEntry(int id, uint32_t serial,
                 DatabaseAccessor::DiffOperation operation,
                 const std::string (&data)[DatabaseAccessor::DIFF_PARAM_COUNT])
        : id_(id), serial_(serial), operation_(operation)
    {
        data_[DatabaseAccessor::DIFF_NAME] = data[DatabaseAccessor::DIFF_NAME];
        data_[DatabaseAccessor::DIFF_TYPE] = data[DatabaseAccessor::DIFF_TYPE];
        data_[DatabaseAccessor::DIFF_TTL] = data[DatabaseAccessor::DIFF_TTL];
        data_[DatabaseAccessor::DIFF_RDATA] =
            data[DatabaseAccessor::DIFF_RDATA];
    }
    JournalEntry(int id, uint32_t serial,
                 DatabaseAccessor::DiffOperation operation,
                 const std::string& name, const std::string& type,
                 const std::string& ttl, const std::string& rdata):
        id_(id), serial_(serial), operation_(operation)
    {
        data_[DatabaseAccessor::DIFF_NAME] = name;
        data_[DatabaseAccessor::DIFF_TYPE] = type;
        data_[DatabaseAccessor::DIFF_TTL] = ttl;
        data_[DatabaseAccessor::DIFF_RDATA] = rdata;
    }
    int id_;
    uint32_t serial_;
    DatabaseAccessor::DiffOperation operation_;
    std::string data_[DatabaseAccessor::DIFF_PARAM_COUNT];
    bool operator==(const JournalEntry& other) const {
        for (size_t i = 0; i < DatabaseAccessor::DIFF_PARAM_COUNT; ++ i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        // No need to check data here, checked above
        return (id_ == other.id_ && serial_ == other.serial_ &&
                operation_ == other.operation_);
    }
};

// This is the type used as the test parameter.  Note that this is
// intentionally a plain old type (i.e. a function pointer), not a class;
// otherwise it could cause initialization fiasco at the instantiation time.
struct DatabaseClientTestParam {
    boost::shared_ptr<DatabaseAccessor> (*accessor_creator)();
    void (*enable_nsec3_fn)(DatabaseAccessor& accessor);
};

// This test fixture is parameterized so that we can share (most of) the test
// cases with different types of data sources.
class DatabaseClientTest :
        public ::testing::TestWithParam<const DatabaseClientTestParam*>
{
public:
    DatabaseClientTest();

    // We create accessor and other objects that depend on it in SetUp, not
    // in the constructor, so derived test classes can override the behavior.
    virtual void SetUp() {
        createClient(GetParam());
    }

    ~DatabaseClientTest() {
        // Make sure we return the default creator no matter if we set it or
        // not
        dns::setNSEC3HashCreator(NULL);
    }

    /*
     * We initialize the client from a function, so we can call it multiple
     * times per test.
     */
    void createClient(const DatabaseClientTestParam* test_param);

    /**
     * Check the zone finder is a valid one and references the zone ID and
     * database available here.
     */
    void checkZoneFinder(const DataSourceClient::FindResult& zone);

    boost::shared_ptr<DatabaseClient::Finder> getFinder();

    // Helper methods for update tests
    bool isRollbacked(bool expected = false) const;

    void checkLastAdded(const char* const expected[]) const;

    void setUpdateAccessor();

    void checkJournal(const std::vector<JournalEntry>& expected);

    // Mock-only; control whether to allow subsequent transaction.
    void allowMoreTransaction(bool is_allowed);

    // Some tests only work for MockAccessor.  We remember whether our accessor
    // is of that type.
    bool is_mock_;

    boost::shared_ptr<DatabaseAccessor> current_accessor_;
    boost::shared_ptr<DatabaseClient> client_;
    const std::string database_name_;

    // The zone finder of the test zone commonly used in various tests.
    boost::shared_ptr<DatabaseClient::Finder> finder_;

    // Some shortcut variables for commonly used test parameters
    const dns::Name zname_; // the zone name stored in the test data source
    const dns::Name qname_; // commonly used name to be found
    const dns::RRClass qclass_;      // commonly used RR class used with qname
    const dns::RRType qtype_;        // commonly used RR type used with qname
    const dns::RRTTL rrttl_;         // commonly used RR TTL
    dns::RRsetPtr rrset_;            // for adding/deleting an RRset
    dns::RRsetPtr rrsigset_;         // for adding/deleting an RRset
    dns::RRsetPtr soa_;              // for adding/deleting an RRset

    // update related objects to be tested
    ZoneUpdaterPtr updater_;
    boost::shared_ptr<const DatabaseAccessor> update_accessor_;

    // placeholders
    const std::vector<std::string> empty_rdatas_; // for NXRRSET/NXDOMAIN
    std::vector<std::string> expected_rdatas_;
    std::vector<std::string> expected_sig_rdatas_;

    // A creator for use in several NSEC3 related tests.
    TestNSEC3HashCreator test_nsec3_hash_creator_;
};

// This test fixture is parameterized so that we can share (most of) the test
// cases with different types of data sources.
class RRsetCollectionTest : public DatabaseClientTest {
protected:
    RRsetCollectionTest() : collection(NULL) {}

    virtual void SetUp() {
        DatabaseClientTest::SetUp();
        updater = client_->getUpdater(zname_, false);
        collection = &updater->getRRsetCollection();
    }

    ZoneUpdaterPtr updater;
    isc::dns::RRsetCollectionBase* collection;
};

// This test fixture is parameterized so that we can share (most of) the test
// cases with different types of data sources.
class RRsetCollectionAndUpdaterTest : public DatabaseClientTest {
protected:
    virtual void SetUp() {
        DatabaseClientTest::SetUp();
        updater_ = client_->getUpdater(zname_, false);
    }

    ZoneUpdaterPtr updater_;
};

} // namespace test
} // namespace datasrc
} // namespace isc

// Local Variables:
// mode: c++
// End:
