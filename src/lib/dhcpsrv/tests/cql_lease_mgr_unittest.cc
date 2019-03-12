// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2015-2017 Deutsche Telekom AG.
//
// Authors: Razvan Becheriu <razvan.becheriu@qualitance.com>
//          Andrei Pavel <andrei.pavel@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <asiolink/io_address.h>
#include <cql/cql_connection.h>
#include <cql/testutils/cql_schema.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/cql_lease_mgr.h>
#include <dhcpsrv/tests/test_utils.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace std;

namespace {


/// @brief Test fixture class for testing Cassandra Lease Manager
///
/// Opens the database prior to each test and closes it afterwards.
/// All pending transactions are deleted prior to closure.

class CqlLeaseMgrTest : public GenericLeaseMgrTest {
public:
    /// @brief Clears the database and opens connection to it.
    void initializeTest() {
        // Ensure we have the proper schema with no transient data.
        createCqlSchema();

        // Connect to the database
        try {
            LeaseMgrFactory::create(validCqlConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the CQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        lmptr_ = &(LeaseMgrFactory::instance());
    }

    /// @brief Destroys the LM and the schema.
    void destroyTest() {
        try {
            lmptr_->rollback();
        } catch (...) {
            // Rollback may fail if backend is in read only mode. That's ok.
        }
        LeaseMgrFactory::destroy();
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroyCqlSchema();
    }

    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    CqlLeaseMgrTest() {
        initializeTest();
    }

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of lmptr_ will close
    /// the database.  Then reopen it and delete everything created by the test.
    virtual ~CqlLeaseMgrTest() {
        destroyTest();
    }

    /// @brief Reopen the database
    ///
    /// Closes the database and re-open it.  Anything committed should be
    /// visible.
    ///
    /// Parameter is ignored for CQL backend as the v4 and v6 leases share
    /// the same database.
    void reopen(Universe) {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create(validCqlConnectionString());
        lmptr_ = &(LeaseMgrFactory::instance());
    }

    // This is the CQL implementation for
    // GenericLeaseMgrTest::testGetExpiredLeases4().
    // The GenericLeaseMgrTest implementation checks for the order of expired
    // leases to be from the most expired to the least expired. Cassandra
    // doesn't support ORDER BY without imposing a EQ / IN restriction on the
    // columns. Because of that, the order check has been excluded.
    void testCqlGetExpiredLeases4() {
        // Get the leases to be used for the test.
        std::vector<Lease4Ptr> leases = createLeases4();
        // Make sure we have at least 6 leases there.
        ASSERT_GE(leases.size(), 6u);

        // Use the same current time for all leases.
        time_t current_time = time(NULL);

        // Add them to the database
        for (size_t i = 0u; i < leases.size(); ++i) {
            // Mark every other lease as expired.
            if (i % 2u == 0u) {
                // Set client last transmission time to the value older than the
                // valid lifetime to make it expired. The expiration time also
                // depends on the lease index, so as we can later check that the
                // leases are ordered by the expiration time.
                leases[i]->cltt_ =
                    current_time - leases[i]->valid_lft_ - 10 - i;
            } else {
                // Set current time as cltt for remaining leases. These leases
                // are
                // not expired.
                leases[i]->cltt_ = current_time;
            }
            ASSERT_TRUE(lmptr_->addLease(leases[i]));
        }

        // Retrieve at most 1000 expired leases.
        Lease4Collection expired_leases;
        ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 1000));

        // Leases with even indexes should be returned as expired.
        ASSERT_EQ(static_cast<size_t>(leases.size() / 2u),
                  expired_leases.size());

        // Update current time for the next test.
        current_time = time(NULL);
        // Also, remove expired leases collected during the previous test.
        expired_leases.clear();

        // This time let's reverse the expiration time and see if they will be
        // returned
        // in the correct order.
        for (size_t i = 0u; i < leases.size(); ++i) {
            // Update the time of expired leases with even indexes.
            if (i % 2u == 0u) {
                leases[i]->cltt_ =
                    current_time - leases[i]->valid_lft_ - 1000 + i;
            } else {
                // Make sure remaining leases remain unexpired.
                leases[i]->cltt_ = current_time + 100;
            }
            ASSERT_NO_THROW(lmptr_->updateLease4(leases[i]));
        }

        // Retrieve expired leases again. The limit of 0 means return all
        // expired leases.
        ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 0));

        // The same leases should be returned.
        ASSERT_EQ(static_cast<size_t>(leases.size() / 2u),
                  expired_leases.size());

        // Remember expired leases returned.
        std::vector<Lease4Ptr> saved_expired_leases = expired_leases;

        // Remove expired leases again.
        expired_leases.clear();

        // Limit the number of leases to be returned to 2.
        ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 2));

        // Make sure we have exactly 2 leases returned.
        ASSERT_EQ(2u, expired_leases.size());

        // Mark every other expired lease as reclaimed.
        for (size_t i = 0u; i < saved_expired_leases.size(); ++i) {
            if (i % 2u != 0u) {
                saved_expired_leases[i]->state_ =
                    Lease::STATE_EXPIRED_RECLAIMED;
            }
            ASSERT_NO_THROW(lmptr_->updateLease4(saved_expired_leases[i]));
        }

        expired_leases.clear();

        // This the returned leases should exclude reclaimed ones. So the number
        // of returned leases should be roughly half of the expired leases.
        ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 0u));
        ASSERT_EQ(static_cast<size_t>(saved_expired_leases.size() / 2u),
                  expired_leases.size());

        // Make sure that returned leases are those that are not reclaimed, i.e.
        // those that have even index.
        for (Lease4Collection::iterator lease = expired_leases.begin();
             lease != expired_leases.end(); ++lease) {
            int32_t index = static_cast<int32_t>(
                std::distance(expired_leases.begin(), lease));
            EXPECT_EQ(saved_expired_leases[2 * index]->addr_, (*lease)->addr_);
        }
    }

    // This is the CQL implementation for
    // GenericLeaseMgrTest::testGetExpiredLeases6().
    // The GenericLeaseMgrTest implementation checks for the order of expired
    // leases to be from the most expired to the least expired. Cassandra
    // doesn't support ORDER BY without imposing a EQ / IN restriction on the
    // columns. Because of that, the order check has been excluded.
    void testCqlGetExpiredLeases6() {
        // Get the leases to be used for the test.
        std::vector<Lease6Ptr> leases = createLeases6();
        // Make sure we have at least 6 leases there.
        ASSERT_GE(leases.size(), 6u);

        // Use the same current time for all leases.
        time_t current_time = time(NULL);

        // Add them to the database
        for (size_t i = 0u; i < leases.size(); ++i) {
            // Mark every other lease as expired.
            if (i % 2u == 0u) {
                // Set client last transmission time to the value older than the
                // valid lifetime to make it expired. The expiration time also
                // depends on the lease index, so as we can later check that the
                // leases are ordered by the expiration time.
                leases[i]->cltt_ =
                    current_time - leases[i]->valid_lft_ - 10 - i;
            } else {
                // Set current time as cltt for remaining leases. These leases
                // are
                // not expired.
                leases[i]->cltt_ = current_time;
            }
            ASSERT_TRUE(lmptr_->addLease(leases[i]));
        }

        // Retrieve at most 1000 expired leases.
        Lease6Collection expired_leases;
        ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 1000));

        // Leases with even indexes should be returned as expired.
        ASSERT_EQ(static_cast<size_t>(leases.size() / 2u),
                  expired_leases.size());

        // Update current time for the next test.
        current_time = time(NULL);
        // Also, remove expired leases collected during the previous test.
        expired_leases.clear();

        // This time let's reverse the expiration time and see if they will be
        // returned
        // in the correct order.
        for (size_t i = 0u; i < leases.size(); ++i) {
            // Update the time of expired leases with even indexes.
            if (i % 2u == 0u) {
                leases[i]->cltt_ =
                    current_time - leases[i]->valid_lft_ - 1000 + i;
            } else {
                // Make sure remaining leases remain unexpired.
                leases[i]->cltt_ = current_time + 100;
            }
            ASSERT_NO_THROW(lmptr_->updateLease6(leases[i]));
        }

        // Retrieve expired leases again. The limit of 0 means return all
        // expired leases.
        ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 0));

        // The same leases should be returned.
        ASSERT_EQ(static_cast<size_t>(leases.size() / 2u),
                  expired_leases.size());

        // Remember expired leases returned.
        std::vector<Lease6Ptr> saved_expired_leases = expired_leases;

        // Remove expired leases again.
        expired_leases.clear();

        // Limit the number of leases to be returned to 2.
        ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 2));

        // Make sure we have exactly 2 leases returned.
        ASSERT_EQ(2u, expired_leases.size());

        // Mark every other expired lease as reclaimed.
        for (size_t i = 0u; i < saved_expired_leases.size(); ++i) {
            if (i % 2u != 0u) {
                saved_expired_leases[i]->state_ =
                    Lease::STATE_EXPIRED_RECLAIMED;
            }
            ASSERT_NO_THROW(lmptr_->updateLease6(saved_expired_leases[i]));
        }

        expired_leases.clear();

        // This the returned leases should exclude reclaimed ones. So the number
        // of returned leases should be roughly half of the expired leases.
        ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 0));

        // Make sure that returned leases are those that are not reclaimed, i.e.
        // those that have even index.
        for (Lease6Collection::iterator lease = expired_leases.begin();
             lease != expired_leases.end(); ++lease) {
            int32_t index = static_cast<int32_t>(
                std::distance(expired_leases.begin(), lease));
            EXPECT_EQ(saved_expired_leases[2 * index]->addr_, (*lease)->addr_);
        }
    }
};

/// @brief Check that database can be opened
///
/// This test checks if the CqlLeaseMgr can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// CqlLeaseMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(CqlOpenTest, OpenDatabase) {

    // Schema needs to be created for the test to work.
    createCqlSchema();

    // Check that lease manager open the database opens correctly and tidy up.
    // If it fails, print the error message.
    try {
        LeaseMgrFactory::create(validCqlConnectionString());
        EXPECT_NO_THROW((void)LeaseMgrFactory::instance());
        LeaseMgrFactory::destroy();
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the CQL tests will run correctly.\n";
    }

    // Check that lease manager open the database opens correctly with a longer
    // timeout.  If it fails, print the error message.
    try {
        // CQL specifies the timeout values in ms, not seconds. Therefore
        // we need to add extra 000 to the "connect-timeout=10" string.
        string connection_string = validCqlConnectionString() + string(" ") +
            string(VALID_TIMEOUT) + "000";
        LeaseMgrFactory::create(connection_string);
        EXPECT_NO_THROW((void) LeaseMgrFactory::instance());
        LeaseMgrFactory::destroy();
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the CQL tests will run correctly.\n";
    }

    // Check that attempting to get an instance of the lease manager when
    // none is set throws an exception.
    EXPECT_THROW(LeaseMgrFactory::instance(), NoLeaseManager);

    // Check that wrong specification of backend throws an exception.
    // (This is really a check on LeaseMgrFactory, but is convenient to
    // perform here.)
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        NULL, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        InvalidParameter);

    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        INVALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        InvalidType);

    // Check that invalid login data does not cause an exception, CQL should use
    // default values.
    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)));

    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)));

    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)));

    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)));

    // Check for invalid timeouts
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_1)),
        DbOperationError);

    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_2)),
        DbOperationError);

    // Check for missing parameters
    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)));

    // Check that invalid login data does not cause an exception, CQL should use
    // default values.
    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)));

    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)));

    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)));

    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)));

    // Check that invalid timeouts throw DbOperationError.
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD,
        INVALID_TIMEOUT_1)),
        DbOperationError);
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD,
        INVALID_TIMEOUT_2)),
        DbOperationError);

    // Check that CQL allows the hostname to not be specified.
    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)));

    // Tidy up after the test
    destroyCqlSchema();
}

/// @brief Check the getType() method
///
/// getType() returns a string giving the type of the backend, which should
/// always be "cql".
TEST_F(CqlLeaseMgrTest, getType) {
    EXPECT_EQ(std::string("cql"), lmptr_->getType());
}

/// @brief Check conversion functions
///
/// The server works using cltt and valid_filetime.  In the database, the
/// information is stored as expire_time and valid-lifetime, which are
/// related by
///
/// expire_time = cltt + valid_lifetime
///
/// This test checks that the conversion is correct.
TEST_F(CqlLeaseMgrTest, checkTimeConversion) {
    const time_t cltt = time(NULL);
    const uint32_t valid_lft = 86400;  // 1 day
    cass_int64_t cql_expire;

    // Convert to the database time.
    CqlExchange::convertToDatabaseTime(cltt, valid_lft, cql_expire);

    // Convert back
    time_t converted_cltt = 0;
    CqlExchange::convertFromDatabaseTime(cql_expire, valid_lft, converted_cltt);
    EXPECT_EQ(cltt, converted_cltt);
}

/// @brief Check getName() returns correct database name
TEST_F(CqlLeaseMgrTest, getName) {
    EXPECT_EQ(std::string("keatest"), lmptr_->getName());
}

/// @brief Check that getVersion() returns the expected version
TEST_F(CqlLeaseMgrTest, checkVersion) {
    // Check version
    pair<uint32_t, uint32_t> version;
    ASSERT_NO_THROW(version = lmptr_->getVersion());
    EXPECT_EQ(CQL_SCHEMA_VERSION_MAJOR, version.first);
    EXPECT_EQ(CQL_SCHEMA_VERSION_MINOR, version.second);
}

////////////////////////////////////////////////////////////////////////////////
/// LEASE4 /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4 (by address) and deleteLease (with an
/// IPv4 address) works.
TEST_F(CqlLeaseMgrTest, basicLease4) {
    testBasicLease4();
}

/// @brief Check that Lease4 code safely handles invalid dates.
TEST_F(CqlLeaseMgrTest, maxDate4) {
    testMaxDate4();
}

/// @brief Lease4 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(CqlLeaseMgrTest, updateLease4) {
    testUpdateLease4();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(CqlLeaseMgrTest, getLease4HWAddr1) {
    testGetLease4HWAddr1();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(CqlLeaseMgrTest, getLease4HWAddr2) {
    testGetLease4HWAddr2();
}

// @brief Get lease4 by hardware address (2)
//
// Check that the system can cope with getting a hardware address of
// any size.
TEST_F(CqlLeaseMgrTest, getLease4HWAddrSize) {
    testGetLease4HWAddrSize();
}

/// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of hardware address and subnet ID
TEST_F(CqlLeaseMgrTest, getLease4HwaddrSubnetId) {
    testGetLease4HWAddrSubnetId();
}

// @brief Get lease4 by hardware address and subnet ID (2)
//
// Check that the system can cope with getting a hardware address of
// any size.
TEST_F(CqlLeaseMgrTest, getLease4HWAddrSubnetIdSize) {
    testGetLease4HWAddrSubnetIdSize();
}

// This test was derived from memfile.
TEST_F(CqlLeaseMgrTest, getLease4ClientId) {
    testGetLease4ClientId();
}

/// @brief Check GetLease4 methods - access by Client ID
///
/// Adds leases to the database and checks that they can be accessed via
/// the Client ID.
TEST_F(CqlLeaseMgrTest, getLease4ClientId2) {
    testGetLease4ClientId2();
}

// @brief Get Lease4 by client ID (2)
//
// Check that the system can cope with a client ID of any size.
TEST_F(CqlLeaseMgrTest, getLease4ClientIdSize) {
    testGetLease4ClientIdSize();
}

/// @brief Check GetLease4 methods - access by Client ID & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of client and subnet IDs.
TEST_F(CqlLeaseMgrTest, getLease4ClientIdSubnetId) {
    testGetLease4ClientIdSubnetId();
}

// This test checks that all IPv4 leases for a specified subnet id are returned.
TEST_F(CqlLeaseMgrTest, getLeases4SubnetId) {
    testGetLeases4SubnetId();
}

// This test checks that all IPv4 leases are returned.
TEST_F(CqlLeaseMgrTest, getLeases4) {
    testGetLeases4();
}

// Test that a range of IPv4 leases is returned with paging.
TEST_F(CqlLeaseMgrTest, getLeases4Paged) {
    testGetLeases4Paged();
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease can handle NULL client-id.
/// (client-id is optional and may not be present)
TEST_F(CqlLeaseMgrTest, lease4NullClientId) {
    testLease4NullClientId();
}

/// @brief Verify that too long hostname for Lease4 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(CqlLeaseMgrTest, lease4InvalidHostname) {
    testLease4InvalidHostname();
}

/// @brief Check that the expired DHCPv4 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(CqlLeaseMgrTest, getExpiredLeases4) {
    testCqlGetExpiredLeases4();
}

/// @brief Check that expired reclaimed DHCPv4 leases are removed.
TEST_F(CqlLeaseMgrTest, deleteExpiredReclaimedLeases4) {
    testDeleteExpiredReclaimedLeases4();
}

////////////////////////////////////////////////////////////////////////////////
/// LEASE6 /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Test checks whether simple add, get and delete operations are possible
// on Lease6
TEST_F(CqlLeaseMgrTest, testAddGetDelete6) {
    testAddGetDelete6(false);
}

/// @brief Basic Lease6 Checks
///
/// Checks that the addLease, getLease6 (by address) and deleteLease (with an
/// IPv6 address) works.
TEST_F(CqlLeaseMgrTest, basicLease6) {
    testBasicLease6();
}

/// @brief Check that Lease6 code safely handles invalid dates.
TEST_F(CqlLeaseMgrTest, maxDate6) {
    testMaxDate6();
}

/// @brief Verify that too long hostname for Lease6 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(CqlLeaseMgrTest, lease6InvalidHostname) {
    testLease6InvalidHostname();
}

/// @brief Check GetLease6 methods - access by DUID/IAID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DUID and IAID.
TEST_F(CqlLeaseMgrTest, getLeases6DuidIaid) {
    testGetLeases6DuidIaid();
}

// Check that the system can cope with a DUID of allowed size.
TEST_F(CqlLeaseMgrTest, getLeases6DuidSize) {
    testGetLeases6DuidSize();
}

/// @brief Check that getLease6 methods discriminate by lease type.
///
/// Adds six leases, two per lease type all with the same duid and iad but
/// with alternating subnet_ids.
/// It then verifies that all of getLeases6() method variants correctly
/// discriminate between the leases based on lease type alone.
TEST_F(CqlLeaseMgrTest, lease6LeaseTypeCheck) {
    testLease6LeaseTypeCheck();
}

/// @brief Verifies the getLeases6(DUID) method
///
/// Adds 3 lease and verifies fetch by DUID.
/// Verifies retrival of non existant DUID fails
TEST_F(CqlLeaseMgrTest, getLeases6Duid) {
    testGetLeases6Duid();
}

/// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DIUID and IAID.
TEST_F(CqlLeaseMgrTest, getLease6DuidIaidSubnetId) {
    testGetLease6DuidIaidSubnetId();
}

// Test checks that getLease6() works with different DUID sizes
TEST_F(CqlLeaseMgrTest, getLease6DuidIaidSubnetIdSize) {
    testGetLease6DuidIaidSubnetIdSize();
}

// Test that a range of IPv6 leases is returned with paging.
TEST_F(CqlLeaseMgrTest, getLeases6Paged) {
    testGetLeases6Paged();
}

/// @brief Lease6 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(CqlLeaseMgrTest, updateLease6) {
    testUpdateLease6();
}

/// @brief DHCPv4 Lease recreation tests
///
/// Checks that the lease can be created, deleted and recreated with
/// different parameters. It also checks that the re-created lease is
/// correctly stored in the lease database.
TEST_F(CqlLeaseMgrTest, testRecreateLease4) {
    testRecreateLease4();
}

/// @brief DHCPv6 Lease recreation tests
///
/// Checks that the lease can be created, deleted and recreated with
/// different parameters. It also checks that the re-created lease is
/// correctly stored in the lease database.
TEST_F(CqlLeaseMgrTest, testRecreateLease6) {
    testRecreateLease6();
}

/// @brief Checks that null DUID is not allowed.
TEST_F(CqlLeaseMgrTest, nullDuid) {
    testNullDuid();
}

/// @brief Tests whether CQL can store and retrieve hardware addresses
TEST_F(CqlLeaseMgrTest, testLease6Mac) {
    testLease6MAC();
}

/// @brief Tests whether CQL can store and retrieve hardware addresses
TEST_F(CqlLeaseMgrTest, testLease6HWTypeAndSource) {
    testLease6HWTypeAndSource();
}

/// @brief Check that the expired DHCPv6 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(CqlLeaseMgrTest, getExpiredLeases6) {
    testCqlGetExpiredLeases6();
}

/// @brief Check that expired reclaimed DHCPv6 leases are removed.
TEST_F(CqlLeaseMgrTest, deleteExpiredReclaimedLeases6) {
    testDeleteExpiredReclaimedLeases6();
}

/// @brief Verifies that IPv4 lease statistics can be recalculated.
TEST_F(CqlLeaseMgrTest, recountLeaseStats4) {
    testRecountLeaseStats4();
}

/// @brief Verifies that IPv6 lease statistics can be recalculated.
TEST_F(CqlLeaseMgrTest, recountLeaseStats6) {
    testRecountLeaseStats6();
}

/// @brief Tests that leases from specific subnet can be removed.
/// @todo: uncomment this once lease wipe is implemented
/// for Cassandra (see #5485)
TEST_F(CqlLeaseMgrTest, DISABLED_wipeLeases4) {
    testWipeLeases4();
}

/// @brief Tests that leases from specific subnet can be removed.
/// @todo: uncomment this once lease wipe is implemented
/// for Cassandra (see #5485)
TEST_F(CqlLeaseMgrTest, DISABLED_wipeLeases6) {
    testWipeLeases6();
}

// Tests v4 lease stats query variants.
TEST_F(CqlLeaseMgrTest, leaseStatsQuery4) {
    testLeaseStatsQuery4();
}

// Tests v6 lease stats query variants.
TEST_F(CqlLeaseMgrTest, leaseStatsQuery6) {
    testLeaseStatsQuery6();
}

}  // namespace
