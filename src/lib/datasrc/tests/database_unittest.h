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

/// \brief Commonly used test data.
///
/// This is an array of 5 C-string tuples, each of the tuples has the
/// following semantics.
/// [0] textual form of fully qualified, dot-terminated domain name
///     (NAME_COLUMN).
/// [1] textual form of RR type, such as "AAAA" (TYPE_COLUMN)
/// [2] textual numeric form of RR TTL (TTL_COLUMN)
/// [3] textual form of RR type, intended to be used to represent the
///     "covered type" of RRSIG RRs, but actually not used at the moment.
///     (SIGTYPE_COLUMN)
/// [4] textual form of RDATA of the type, e.g., "2001:db8::1" for AAAA
///     (RDATA_COLUMN)
///
/// These correspond to the array fields returned by
/// \c DatabaseAccessor::IteratorContext::getNext().  The upper-cased names
/// surrounded by parentheses specify the corresponding field for the specific
/// entry.
///
/// It ends with a special entry of an all-NULL tuple.
///
/// For testing a custom accessor, it's expected to "load" the data of these
/// records on a call to \c accessor_creator member of
/// \c DatabaseClientTestParam (see the structure description).  In tests,
/// the loaded data should be able to be retrieved by subsequent
/// \c getRecords() or \c getNSEC3Records() calls.  The specific realization
/// of the load can be specific to the accessor implementation, but if it
/// conforms to the API of the following methods of \c DatabaseAccessor,
/// it can be done by calling \c loadTestDataGeneric():
/// - startUpdateZone()
/// - addRecordToZone()
/// - commit()
extern const char* const TEST_RECORDS[][5];

/// \brief NSEC3PARAM at the zone origin and its RRSIG.
///
/// The semantics of the data is the same as that for TEST_RECORDS.
///
/// These will be "loaded" on a call to
/// \c DatabaseClientTestParam::enable_nsec3_fn for some tests that tests
/// NSEC3 related behavior.  If the tested accessor skips the support for
/// NSEC3, this data ban be ignored.
extern const char* TEST_NSEC3PARAM_RECORDS[][5];

/// \brief NSEC3 RR data commonly used for NSEC3-related tests.
///
/// This is similar to TEST_RECORDS, but the first entry is base32-hex encoded
/// hash value (which is expected to appear as the first label of NSEC3
/// owner names), not an FQDN.
///
/// These will be "loaded" on a call to
/// \c DatabaseClientTestParam::enable_nsec3_fn for some tests that tests
/// NSEC3 related behavior.  If the tested accessor skips the support for
/// NSEC3, this data ban be ignored.  The loaded data are expected to be
/// retrievable by subsequent \c getNSEC3Records() calls on the tested
/// accessor.
///
/// The specific realization of the load can be specific to the accessor
/// implementation, but if it conforms to the API of the following methods
/// of \c DatabaseAccessor, it can be done by calling \c enableNSEC3Generic():
/// - startUpdateZone()
/// - addRecordToZone()
/// - addNSEC3RecordToZone()
/// - commit()
extern const char* TEST_NSEC3_RECORDS[][5];

/// \brief Test parameter for DatabaseClientTest.
///
/// This is the type of the parameter for the parameterized DatabaseClientTest
/// and its derived variants.  It consists of a set of function pointers,
/// including the factory of tested accessor.  A specific accessor
/// implementation is expected to specify an instance of this structure,
/// filling the members with appropriate functions for that accessor
/// implementation.
///
/// Note that this is intentionally defined to be of plain old type (a plain
/// structure whose members are bare function pointers); otherwise it could
/// cause initialization fiasco at the instantiation time.
struct DatabaseClientTestParam {
    /// \brief The factory of the tested accessor.
    ///
    /// DatabaseClientTest will call this as part of the initialization of
    /// each test case.  This function is expected to "load" the data
    /// specified in TEST_RECORDS so they can be used in the tests.
    ///
    /// The creation of the accessor will be inherently implementation
    /// dependent, but for loading the data it may be sufficient to call
    /// \c loadTestDataGeneric.  See TEST_RECORDS for the condition.
    boost::shared_ptr<DatabaseAccessor> (*accessor_creator)();

    /// \brief Make NSEC3 records for the test.
    ///
    /// Some test cases call this function when they need to test NSEC3-related
    /// scenarios.  It's expected to "load" the data specified in
    /// TEST_NSEC3PARAM_RECORDS and TEST_NSEC3_RECORDS.
    ///
    /// The passed accessor will be the one created by the preceding call
    /// to \c accessor_creator.
    ///
    /// If the accessor implementation meets some condition, this member can
    /// be the generic \c enableNSEC3Generic function.  See TEST_RECORDS
    /// and TEST_NSEC3_RECORDS for the condition.
    void (*enable_nsec3_fn)(DatabaseAccessor& accessor);
};

// forward declaration, needed in the definition of DatabaseClientTest.
// this is private to the test implementation internal otherwise.
struct JournalEntry;

/// \brief Test fixture class for the DatabaseClient implementation.
///
/// The primary purpose of this fixture is to test the implementation of
/// the DatabaseClient with an internal mock DatabaseAccessor accessor.
/// But the test cases can also be used to check specific accessor
/// implementations.  It will be convenient for implementors of new types of
/// accessor.
///
/// This fixture is therefore parameterized so that a specific accessor
/// implementation can customize accessor-specific data of the test
/// (most notably the accessor itself, and also the way to make test data
/// available through the accessor).
///
/// See database_sqlite3_unittest.cc for how to use this test with a specific
/// accessor implementation.
class DatabaseClientTest :
        public ::testing::TestWithParam<const DatabaseClientTestParam*>
{
protected:
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

    // We initialize the client from a function, so we can call it multiple
    // times per test.
    void createClient(const DatabaseClientTestParam* test_param);

    /// Check the zone finder is a valid one and references the zone ID and
    /// database available here.
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

/// \brief Test fixture for RRsetCollectionTest with database updater.
///
/// Inherited from DatabaseClientTest to reuse some of the setup.
/// This test fixture is parameterized just like DatabaseClientTest.
class RRsetCollectionTest : public DatabaseClientTest {
protected:
    RRsetCollectionTest() {}

    virtual void SetUp() {
        DatabaseClientTest::SetUp();
        updater = client_->getUpdater(zname_, false);
    }

    ZoneUpdaterPtr updater;
};

/// \brief Generic test data loader.
///
/// This function is intended to be used within the accessor_creator function
/// of DatabaseClientTestParam for tested accessor that implements the
/// following methods:
/// - startUpdateZone()
/// - addRecordToZone()
/// - commit()
void loadTestDataGeneric(DatabaseAccessor& accessor);

/// \brief Generic helper to prepare NSEC3 related test data.
///
/// This function can be specified for the enable_nsec3_fn member
/// of DatabaseClientTestParam if the tested accessor implements the
/// following methods:
/// - startUpdateZone()
/// - addRecordToZone()
/// - addNSEC3RecordToZone()
/// - commit()
void enableNSEC3Generic(DatabaseAccessor& accessor);

} // namespace test
} // namespace datasrc
} // namespace isc

// Local Variables:
// mode: c++
// End:
