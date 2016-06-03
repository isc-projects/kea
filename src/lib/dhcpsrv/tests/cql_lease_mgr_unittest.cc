// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/cql_lease_mgr.h>
#include <dhcpsrv/tests/test_utils.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>
#include <dhcpsrv/testutils/cql_schema.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace isc;
using namespace isc::asiolink;
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
    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    CqlLeaseMgrTest() {

        // Ensure schema is the correct one.
        destroyCqlSchema();
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

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of lmptr_ will close
    /// the database.  Then reopen it and delete everything created by the test.
    virtual ~CqlLeaseMgrTest() {
        lmptr_->rollback();
        LeaseMgrFactory::destroy();
        destroyCqlSchema();
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

};

/// @brief Check that database can be opened
///
/// This test checks if the CqlLeaseMgr can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// CqlLeaseMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(CQLOpenTest, OpenDatabase) {

    // Schema needs to be created for the test to work.
    destroyCqlSchema();
    createCqlSchema();

    // Check that lease manager open the database opens correctly and tidy up.
    //  If it fails, print the error message.
    try {
        LeaseMgrFactory::create(validCqlConnectionString());
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

    // Check that invalid login data causes an exception.
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);

    // Check for missing parameters
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        CQL_VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        NoDatabaseName);

    // Tidy up after the test
    destroyCqlSchema();
}

/// @brief Check the getType() method
///
/// getType() returns a string giving the type of the backend, which should
/// always be "cassandra".
TEST_F(CqlLeaseMgrTest, getType) {
    EXPECT_EQ(std::string("cassandra"), lmptr_->getType());
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

    time_t converted_cltt = 0;
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
    EXPECT_EQ(CQL_CURRENT_VERSION, version.first);
    EXPECT_EQ(CQL_CURRENT_MINOR, version.second);
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

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease (IPv4 address) can handle NULL client-id.
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

/// @brief Tests whether memfile can store and retrieve hardware addresses
TEST_F(CqlLeaseMgrTest, testLease6Mac) {
    testLease6MAC();
}

/// @brief Tests whether memfile can store and retrieve hardware addresses
TEST_F(CqlLeaseMgrTest, testLease6HWTypeAndSource) {
    testLease6HWTypeAndSource();
}

/// @brief Check that the expired DHCPv4 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(CqlLeaseMgrTest, getExpiredLeases4) {
    testGetExpiredLeases4();
}

/// @brief Check that the expired DHCPv6 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(CqlLeaseMgrTest, getExpiredLeases6) {
    testGetExpiredLeases6();
}

/// @brief Check that expired reclaimed DHCPv6 leases are removed.
TEST_F(CqlLeaseMgrTest, deleteExpiredReclaimedLeases6) {
    testDeleteExpiredReclaimedLeases6();
}

/// @brief Check that expired reclaimed DHCPv4 leases are removed.
TEST_F(CqlLeaseMgrTest, deleteExpiredReclaimedLeases4) {
    testDeleteExpiredReclaimedLeases4();
}

}; // Of anonymous namespace
