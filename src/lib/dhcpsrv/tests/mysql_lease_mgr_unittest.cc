// Copyright (C) 2012-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/mysql_lease_mgr.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <dhcpsrv/testutils/generic_lease_mgr_unittest.h>
#include <dhcpsrv/testutils/mysql_generic_backend_unittest.h>
#include <exceptions/exceptions.h>
#include <mysql/mysql_connection.h>
#include <mysql/testutils/mysql_schema.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>
#include <util/multi_threading_mgr.h>

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
using namespace isc::test;
using namespace isc::util;
using namespace std;

namespace {


/// @brief Test fixture class for testing MySQL Lease Manager
///
/// Opens the database prior to each test and closes it afterwards.
/// All pending transactions are deleted prior to closure.

class MySqlLeaseMgrTest : public GenericLeaseMgrTest {
public:
    /// @brief Clears the database and opens connection to it.
    void initializeTest() {
        // Ensure we have the proper schema with no transient data.
        createMySQLSchema();

        // Connect to the database
        try {
            LeaseMgrFactory::create(validMySQLConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        lmptr_ = &(LeaseMgrFactory::instance());

        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destroys the LM and the schema.
    void destroyTest() {
        LeaseMgrFactory::destroy();
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroyMySQLSchema();

        // Disable Multi-Threading.
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    MySqlLeaseMgrTest() {
        initializeTest();
    }

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of lmptr_ will close
    /// the database.  Then reopen it and delete everything created by the test.
    virtual ~MySqlLeaseMgrTest() {
        destroyTest();
    }

    /// @brief Reopen the database
    ///
    /// Closes the database and re-open it.  Anything committed should be
    /// visible.
    ///
    /// Parameter is ignored for MySQL backend as the v4 and v6 leases share
    /// the same database.
    void reopen(Universe) {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create(validMySQLConnectionString());
        lmptr_ = &(LeaseMgrFactory::instance());
    }
};

/// @brief Check that database can be opened
///
/// This test checks if the MySqlLeaseMgr can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// MySqlLeaseMgr test fixture set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.
TEST(MySqlOpenTest, OpenDatabase) {
    // Explicitly disable Multi-Threading.
    MultiThreadingMgr::instance().setMode(false);

    // Schema needs to be created for the test to work.
    createMySQLSchema(true);

    // Check that lease manager opens the database correctly and tidy up.  If it
    // fails, print the error message.
    try {
        LeaseMgrFactory::create(validMySQLConnectionString());
        EXPECT_NO_THROW((void)LeaseMgrFactory::instance());
        LeaseMgrFactory::destroy();
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
    }

    // Check that lease manager opens the database correctly with a longer
    // timeout.  If it fails, print the error message.
    try {
        string connection_string = validMySQLConnectionString() + string(" ") +
                                   string(VALID_TIMEOUT);
        LeaseMgrFactory::create(connection_string);
        EXPECT_NO_THROW((void) LeaseMgrFactory::instance());
        LeaseMgrFactory::destroy();
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
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
        MYSQL_VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);

#ifndef OS_OSX
    // Under MacOS, connecting with an invalid host can cause a TCP/IP socket
    // to be orphaned and never closed.  This can interfere with subsequent tests
    // which attempt to locate and manipulate MySQL client socket descriptor.
    // In the interests of progress, we'll just avoid this test.
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
#endif

    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);

    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);

    // Check for invalid timeouts
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_1)),
        DbInvalidTimeout);

    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_2)),
        DbInvalidTimeout);

    // Check for missing parameters
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        MYSQL_VALID_TYPE, NULL, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        NoDatabaseName);

    // Check for extended info tables.
    const char* EX_INFO = "extended-info-tables=true";
    EXPECT_NO_THROW(LeaseMgrFactory::create(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, EX_INFO)));
    LeaseMgrFactory::destroy();

    // Tidy up after the test
    destroyMySQLSchema(true);
    LeaseMgrFactory::destroy();
}

/// @brief Check that database can be opened with Multi-Threading
TEST(MySqlOpenTest, OpenDatabaseMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);

    // Schema needs to be created for the test to work.
    createMySQLSchema(true);

    // Check that lease manager opens the database correctly and tidy up.  If it
    // fails, print the error message.
    try {
        LeaseMgrFactory::create(validMySQLConnectionString());
        EXPECT_NO_THROW((void)LeaseMgrFactory::instance());
        LeaseMgrFactory::destroy();
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
    }

    // Tidy up after the test
    destroyMySQLSchema(true);
    LeaseMgrFactory::destroy();
}

/// @brief Check the getType() method
///
/// getType() returns a string giving the type of the backend, which should
/// always be "mysql".
TEST_F(MySqlLeaseMgrTest, getType) {
    EXPECT_EQ(std::string("mysql"), lmptr_->getType());
}

/// @brief Check conversion functions
///
/// The server works using cltt and valid_filetime.  In the database, the
/// information is stored as expire_time and valid-lifetime, which are
/// related by
///
/// expire_time = cltt + valid_lifetime
///
/// This test checks that the conversion is correct.  It does not check that the
/// data is entered into the database correctly, only that the MYSQL_TIME
/// structure used for the entry is correctly set up.
TEST_F(MySqlLeaseMgrTest, checkTimeConversion) {
    const time_t cltt = time(NULL);
    const uint32_t valid_lft = 86400;       // 1 day
    struct tm tm_expire;
    MYSQL_TIME mysql_expire;

    // Work out what the broken-down time will be for one day
    // after the current time.
    time_t expire_time = cltt + valid_lft;
    (void) localtime_r(&expire_time, &tm_expire);

    // Convert to the database time
    MySqlConnection::convertToDatabaseTime(cltt, valid_lft, mysql_expire);

    // Are the times the same?
    EXPECT_EQ(tm_expire.tm_year + 1900, mysql_expire.year);
    EXPECT_EQ(tm_expire.tm_mon + 1,  mysql_expire.month);
    EXPECT_EQ(tm_expire.tm_mday, mysql_expire.day);
    EXPECT_EQ(tm_expire.tm_hour, mysql_expire.hour);
    EXPECT_EQ(tm_expire.tm_min, mysql_expire.minute);
    EXPECT_EQ(tm_expire.tm_sec, mysql_expire.second);
    EXPECT_EQ(0, mysql_expire.second_part);
    EXPECT_EQ(0, mysql_expire.neg);

    // Convert back
    time_t converted_cltt = 0;
    MySqlConnection::convertFromDatabaseTime(mysql_expire, valid_lft, converted_cltt);
    EXPECT_EQ(cltt, converted_cltt);
}

/// @brief Check getName() returns correct database name
TEST_F(MySqlLeaseMgrTest, getName) {
    EXPECT_EQ(std::string("keatest"), lmptr_->getName());
}

/// @brief Check that getVersion() returns the expected version
TEST_F(MySqlLeaseMgrTest, checkVersion) {
    // Check version
    pair<uint32_t, uint32_t> version;
    ASSERT_NO_THROW(version = lmptr_->getVersion());
    EXPECT_EQ(MYSQL_SCHEMA_VERSION_MAJOR, version.first);
    EXPECT_EQ(MYSQL_SCHEMA_VERSION_MINOR, version.second);
}

////////////////////////////////////////////////////////////////////////////////
/// LEASE4 /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4 (by address) and deleteLease (with an
/// IPv4 address) works.
TEST_F(MySqlLeaseMgrTest, basicLease4) {
    testBasicLease4();
}

/// @brief Basic Lease4 Checks
TEST_F(MySqlLeaseMgrTest, basicLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testBasicLease4();
}

/// @brief Check that Lease4 code safely handles invalid dates.
TEST_F(MySqlLeaseMgrTest, maxDate4) {
    testMaxDate4();
}

/// @brief Check that Lease4 code safely handles invalid dates.
TEST_F(MySqlLeaseMgrTest, maxDate4MultiThreading) {
    MultiThreadingTest mt(true);
    testMaxDate4();
}

/// @brief checks that infinite lifetimes do not overflow.
TEST_F(MySqlLeaseMgrTest, infiniteLifeTime4) {
    testInfiniteLifeTime4();
}

/// @brief Lease4 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(MySqlLeaseMgrTest, updateLease4) {
    testUpdateLease4();
}

/// @brief Lease4 update tests
TEST_F(MySqlLeaseMgrTest, updateLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testUpdateLease4();
}

/// @brief Lease4 concurrent update tests
///
/// Checks that we are not able to concurrently update a lease in the database.
TEST_F(MySqlLeaseMgrTest, concurrentUpdateLease4) {
    testConcurrentUpdateLease4();
}

/// @brief Lease4 concurrent update tests
///
/// Checks that we are not able to concurrently update a lease in the database.
TEST_F(MySqlLeaseMgrTest, concurrentUpdateLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testConcurrentUpdateLease4();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(MySqlLeaseMgrTest, getLease4HWAddr1) {
    testGetLease4HWAddr1();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(MySqlLeaseMgrTest, getLease4HWAddr1MultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4HWAddr1();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(MySqlLeaseMgrTest, getLease4HWAddr2) {
    testGetLease4HWAddr2();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(MySqlLeaseMgrTest, getLease4HWAddr2MultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4HWAddr2();
}

/// @brief Get lease4 by hardware address (2)
///
/// Check that the system can cope with getting a hardware address of
/// any size.
TEST_F(MySqlLeaseMgrTest, getLease4HWAddrSize) {
    testGetLease4HWAddrSize();
}

/// @brief Get lease4 by hardware address (2)
TEST_F(MySqlLeaseMgrTest, getLease4HWAddrSizeMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4HWAddrSize();
}

/// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of hardware address and subnet ID
TEST_F(MySqlLeaseMgrTest, getLease4HwaddrSubnetId) {
    testGetLease4HWAddrSubnetId();
}

/// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
TEST_F(MySqlLeaseMgrTest, getLease4HwaddrSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4HWAddrSubnetId();
}

/// @brief Get lease4 by hardware address and subnet ID (2)
///
/// Check that the system can cope with getting a hardware address of
/// any size.
TEST_F(MySqlLeaseMgrTest, getLease4HWAddrSubnetIdSize) {
    testGetLease4HWAddrSubnetIdSize();
}

/// @brief Get lease4 by hardware address and subnet ID (2)
TEST_F(MySqlLeaseMgrTest, getLease4HWAddrSubnetIdSizeMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4HWAddrSubnetIdSize();
}

/// @brief This test was derived from memfile.
TEST_F(MySqlLeaseMgrTest, getLease4ClientId) {
    testGetLease4ClientId();
}

/// @brief This test was derived from memfile.
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4ClientId();
}

/// @brief Check GetLease4 methods - access by Client ID
///
/// Adds leases to the database and checks that they can be accessed via
/// the Client ID.
TEST_F(MySqlLeaseMgrTest, getLease4ClientId2) {
    testGetLease4ClientId2();
}

/// @brief Check GetLease4 methods - access by Client ID
TEST_F(MySqlLeaseMgrTest, getLease4ClientId2MultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4ClientId2();
}

/// @brief Get Lease4 by client ID (2)
///
/// Check that the system can cope with a client ID of any size.
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSize) {
    testGetLease4ClientIdSize();
}

/// @brief Get Lease4 by client ID (2)
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSizeMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4ClientIdSize();
}

/// @brief Check GetLease4 methods - access by Client ID & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of client and subnet IDs.
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSubnetId) {
    testGetLease4ClientIdSubnetId();
}

/// @brief Check GetLease4 methods - access by Client ID & Subnet ID
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease4ClientIdSubnetId();
}

/// @brief This test checks that all IPv4 leases for a specified subnet id are returned.
TEST_F(MySqlLeaseMgrTest, getLeases4SubnetId) {
    testGetLeases4SubnetId();
}

/// @brief This test checks that all IPv4 leases for a specified subnet id are returned.
TEST_F(MySqlLeaseMgrTest, getLeases4SubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4SubnetId();
}

/// @brief This test checks that all IPv4 leases with a specified hostname are returned.
TEST_F(MySqlLeaseMgrTest, getLeases4Hostname) {
    testGetLeases4Hostname();
}

/// @brief This test checks that all IPv4 leases with a specified hostname are returned.
TEST_F(MySqlLeaseMgrTest, getLeases4HostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4Hostname();
}

/// @brief This test checks that all IPv4 leases are returned.
TEST_F(MySqlLeaseMgrTest, getLeases4) {
    testGetLeases4();
}

/// @brief This test checks that all IPv4 leases are returned.
TEST_F(MySqlLeaseMgrTest, getLeases4MultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4();
}

/// @brief Test that a range of IPv4 leases is returned with paging.
TEST_F(MySqlLeaseMgrTest, getLeases4Paged) {
    testGetLeases4Paged();
}

/// @brief Test that a range of IPv4 leases is returned with paging.
TEST_F(MySqlLeaseMgrTest, getLeases4PagedMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4Paged();
}

/// @brief This test checks that all IPv6 leases for a specified subnet id are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6SubnetId) {
    testGetLeases6SubnetId();
}

/// @brief This test checks that all IPv6 leases for a specified subnet id are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6SubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6SubnetId();
}

/// @brief This test checks that all IPv6 leases for a specified subnet id
/// with paging are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6SubnetIdPaged) {
    testGetLeases6SubnetIdPaged();
}

/// @brief This test checks that all IPv6 leases for a specified subnet id
/// with paging are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6SubnetIdPagedMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6SubnetIdPaged();
}

/// @brief This test checks that all IPv6 leases with a specified hostname are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6Hostname) {
    testGetLeases6Hostname();
}

/// @brief This test checks that all IPv6 leases with a specified hostname are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6HostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6Hostname();
}

/// @brief This test checks that all IPv6 leases are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6) {
    testGetLeases6();
}

/// @brief This test checks that all IPv6 leases are returned.
TEST_F(MySqlLeaseMgrTest, getLeases6MultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6();
}

/// @brief Test that a range of IPv6 leases is returned with paging.
TEST_F(MySqlLeaseMgrTest, getLeases6Paged) {
    testGetLeases6Paged();
}

/// @brief Test that a range of IPv6 leases is returned with paging.
TEST_F(MySqlLeaseMgrTest, getLeases6PagedMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6Paged();
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease can handle NULL client-id.
/// (client-id is optional and may not be present)
TEST_F(MySqlLeaseMgrTest, lease4NullClientId) {
    testLease4NullClientId();
}

/// @brief Basic Lease4 Checks
TEST_F(MySqlLeaseMgrTest, lease4NullClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4NullClientId();
}

/// @brief Verify that too long hostname for Lease4 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(MySqlLeaseMgrTest, lease4InvalidHostname) {
    testLease4InvalidHostname();
}

/// @brief Verify that too long hostname for Lease4 is not accepted.
TEST_F(MySqlLeaseMgrTest, lease4InvalidHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4InvalidHostname();
}

/// @brief Check that the expired DHCPv4 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(MySqlLeaseMgrTest, getExpiredLeases4) {
    testGetExpiredLeases4();
}

/// @brief Check that the expired DHCPv4 leases can be retrieved.
TEST_F(MySqlLeaseMgrTest, getExpiredLeases4MultiThreading) {
    MultiThreadingTest mt(true);
    testGetExpiredLeases4();
}

/// @brief Checks that DHCPv4 leases with infinite valid lifetime
/// will never expire.
TEST_F(MySqlLeaseMgrTest, infiniteAreNotExpired4) {
    testInfiniteAreNotExpired4();
}

/// @brief Check that expired reclaimed DHCPv4 leases are removed.
TEST_F(MySqlLeaseMgrTest, deleteExpiredReclaimedLeases4) {
    testDeleteExpiredReclaimedLeases4();
}

/// @brief Check that expired reclaimed DHCPv4 leases are removed.
TEST_F(MySqlLeaseMgrTest, deleteExpiredReclaimedLeases4MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteExpiredReclaimedLeases4();
}

////////////////////////////////////////////////////////////////////////////////
/// LEASE6 /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/// @brief Test checks whether simple add, get and delete operations
/// are possible on Lease6
TEST_F(MySqlLeaseMgrTest, testAddGetDelete6) {
    testAddGetDelete6();
}

/// @brief Test checks whether simple add, get and delete operations
/// are possible on Lease6
TEST_F(MySqlLeaseMgrTest, testAddGetDelete6MultiThreading) {
    MultiThreadingTest mt(true);
    testAddGetDelete6();
}

/// @brief Basic Lease6 Checks
///
/// Checks that the addLease, getLease6 (by address) and deleteLease (with an
/// IPv6 address) works.
TEST_F(MySqlLeaseMgrTest, basicLease6) {
    testBasicLease6();
}

/// @brief Basic Lease6 Checks
TEST_F(MySqlLeaseMgrTest, basicLease6MultiThreading) {
    MultiThreadingTest mt(true);
    testBasicLease6();
}

/// @brief Check that Lease6 code safely handles invalid dates.
TEST_F(MySqlLeaseMgrTest, maxDate6) {
    testMaxDate6();
}

/// @brief Check that Lease6 code safely handles invalid dates.
TEST_F(MySqlLeaseMgrTest, maxDate6MultiThreading) {
    MultiThreadingTest mt(true);
    testMaxDate6();
}

/// @brief checks that infinite lifetimes do not overflow.
TEST_F(MySqlLeaseMgrTest, infiniteLifeTime6) {
    testInfiniteLifeTime6();
}

/// @brief Verify that too long hostname for Lease6 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(MySqlLeaseMgrTest, lease6InvalidHostname) {
    testLease6InvalidHostname();
}

/// @brief Verify that too long hostname for Lease6 is not accepted.
TEST_F(MySqlLeaseMgrTest, lease6InvalidHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6InvalidHostname();
}

/// @brief Verify that large IAID values work correctly.
///
/// Adds lease with a large IAID to the database and verifies it can
/// fetched correctly.
TEST_F(MySqlLeaseMgrTest, leases6LargeIaidCheck) {
    testLease6LargeIaidCheck();
}

/// @brief Verify that large IAID values work correctly.
TEST_F(MySqlLeaseMgrTest, leases6LargeIaidCheckMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6LargeIaidCheck();
}

/// @brief Check GetLease6 methods - access by DUID/IAID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DUID and IAID.
TEST_F(MySqlLeaseMgrTest, getLeases6DuidIaid) {
    testGetLeases6DuidIaid();
}

/// @brief Check GetLease6 methods - access by DUID/IAID
TEST_F(MySqlLeaseMgrTest, getLeases6DuidIaidMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6DuidIaid();
}

/// @brief Check that the system can cope with a DUID of allowed size.
TEST_F(MySqlLeaseMgrTest, getLeases6DuidSize) {
    testGetLeases6DuidSize();
}

/// @brief Check that the system can cope with a DUID of allowed size.
TEST_F(MySqlLeaseMgrTest, getLeases6DuidSizeMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6DuidSize();
}

/// @brief Check that getLease6 methods discriminate by lease type.
///
/// Adds six leases, two per lease type all with the same duid and iad but
/// with alternating subnet_ids.
/// It then verifies that all of getLeases6() method variants correctly
/// discriminate between the leases based on lease type alone.
TEST_F(MySqlLeaseMgrTest, lease6LeaseTypeCheck) {
    testLease6LeaseTypeCheck();
}

/// @brief Check that getLease6 methods discriminate by lease type.
TEST_F(MySqlLeaseMgrTest, lease6LeaseTypeCheckMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6LeaseTypeCheck();
}

/// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DIUID and IAID.
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetId) {
    testGetLease6DuidIaidSubnetId();
}

/// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease6DuidIaidSubnetId();
}

/// @brief Test checks that getLease6() works with different DUID sizes
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetIdSize) {
    testGetLease6DuidIaidSubnetIdSize();
}

/// @brief Test checks that getLease6() works with different DUID sizes
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetIdSizeMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLease6DuidIaidSubnetIdSize();
}

/// @brief check leases could be retrieved by DUID
///
/// Create leases, add them to backend and verify if it can be queried
/// using DUID index
TEST_F(MySqlLeaseMgrTest, getLeases6Duid) {
    testGetLeases6Duid();
}

/// @brief check leases could be retrieved by DUID
TEST_F(MySqlLeaseMgrTest, getLeases6DuidMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6Duid();
}

/// @brief Lease6 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(MySqlLeaseMgrTest, updateLease6) {
    testUpdateLease6();
}

/// @brief Lease6 update tests
TEST_F(MySqlLeaseMgrTest, updateLease6MultiThreading) {
    MultiThreadingTest mt(true);
    testUpdateLease6();
}

/// @brief Lease6 concurrent update tests
///
/// Checks that we are not able to concurrently update a lease in the database.
TEST_F(MySqlLeaseMgrTest, concurrentUpdateLease6) {
    testConcurrentUpdateLease6();
}

/// @brief Lease6 concurrent update tests
///
/// Checks that we are not able to concurrently update a lease in the database.
TEST_F(MySqlLeaseMgrTest, concurrentUpdateLease6MultiThreading) {
    MultiThreadingTest mt(true);
    testConcurrentUpdateLease6();
}

/// @brief DHCPv4 Lease recreation tests
///
/// Checks that the lease can be created, deleted and recreated with
/// different parameters. It also checks that the re-created lease is
/// correctly stored in the lease database.
TEST_F(MySqlLeaseMgrTest, testRecreateLease4) {
    testRecreateLease4();
}

/// @brief DHCPv4 Lease recreation tests
TEST_F(MySqlLeaseMgrTest, testRecreateLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testRecreateLease4();
}

/// @brief DHCPv6 Lease recreation tests
///
/// Checks that the lease can be created, deleted and recreated with
/// different parameters. It also checks that the re-created lease is
/// correctly stored in the lease database.
TEST_F(MySqlLeaseMgrTest, testRecreateLease6) {
    testRecreateLease6();
}

/// @brief DHCPv6 Lease recreation tests
TEST_F(MySqlLeaseMgrTest, testRecreateLease6MultiThreading) {
    MultiThreadingTest mt(true);
    testRecreateLease6();
}

/// @brief Checks that null DUID is not allowed.
TEST_F(MySqlLeaseMgrTest, nullDuid) {
    testNullDuid();
}

/// @brief Checks that null DUID is not allowed.
TEST_F(MySqlLeaseMgrTest, nullDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testNullDuid();
}

/// @brief Tests whether MySQL can store and retrieve hardware addresses
TEST_F(MySqlLeaseMgrTest, testLease6Mac) {
    testLease6MAC();
}

/// @brief Tests whether MySQL can store and retrieve hardware addresses
TEST_F(MySqlLeaseMgrTest, testLease6MacMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6MAC();
}

/// @brief Tests whether MySQL can store and retrieve hardware addresses
TEST_F(MySqlLeaseMgrTest, testLease6HWTypeAndSource) {
    testLease6HWTypeAndSource();
}

/// @brief Tests whether MySQL can store and retrieve hardware addresses
TEST_F(MySqlLeaseMgrTest, testLease6HWTypeAndSourceMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6HWTypeAndSource();
}

/// @brief Check that the expired DHCPv6 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(MySqlLeaseMgrTest, getExpiredLeases6) {
    testGetExpiredLeases6();
}

/// @brief Check that the expired DHCPv6 leases can be retrieved.
TEST_F(MySqlLeaseMgrTest, getExpiredLeases6MultiThreading) {
    MultiThreadingTest mt(true);
    testGetExpiredLeases6();
}

/// @brief Checks that DHCPv6 leases with infinite valid lifetime
/// will never expire.
TEST_F(MySqlLeaseMgrTest, infiniteAreNotExpired6) {
    testInfiniteAreNotExpired6();
}

/// @brief Check that expired reclaimed DHCPv6 leases are removed.
TEST_F(MySqlLeaseMgrTest, deleteExpiredReclaimedLeases6) {
    testDeleteExpiredReclaimedLeases6();
}

/// @brief Check that expired reclaimed DHCPv6 leases are removed.
TEST_F(MySqlLeaseMgrTest, deleteExpiredReclaimedLeases6MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteExpiredReclaimedLeases6();
}

/// @brief Verifies that IPv4 lease statistics can be recalculated.
TEST_F(MySqlLeaseMgrTest, recountLeaseStats4) {
    testRecountLeaseStats4();
}

/// @brief Verifies that IPv4 lease statistics can be recalculated.
TEST_F(MySqlLeaseMgrTest, recountLeaseStats4MultiThreading) {
    MultiThreadingTest mt(true);
    testRecountLeaseStats4();
}

/// @brief Verifies that IPv6 lease statistics can be recalculated.
TEST_F(MySqlLeaseMgrTest, recountLeaseStats6) {
    testRecountLeaseStats6();
}

/// @brief Verifies that IPv6 lease statistics can be recalculated.
TEST_F(MySqlLeaseMgrTest, recountLeaseStats6MultiThreading) {
    MultiThreadingTest mt(true);
    testRecountLeaseStats6();
}

/// @brief Tests that leases from specific subnet can be removed.
TEST_F(MySqlLeaseMgrTest, DISABLED_wipeLeases4) {
    testWipeLeases4();
}

/// @brief Tests that leases from specific subnet can be removed.
TEST_F(MySqlLeaseMgrTest, DISABLED_wipeLeases4MultiThreading) {
    MultiThreadingTest mt(true);
    testWipeLeases4();
}

/// @brief Tests that leases from specific subnet can be removed.
TEST_F(MySqlLeaseMgrTest, DISABLED_wipeLeases6) {
    testWipeLeases6();
}

/// @brief Tests that leases from specific subnet can be removed.
TEST_F(MySqlLeaseMgrTest, DISABLED_wipeLeases6MultiThreading) {
    MultiThreadingTest mt(true);
    testWipeLeases6();
}

/// @brief Test fixture class for validating @c LeaseMgr using
/// MySQL as back end and MySQL connectivity loss.
class MySqlLeaseMgrDbLostCallbackTest : public LeaseMgrDbLostCallbackTest {
public:
    virtual void destroySchema() {
        destroyMySQLSchema();
    }

    virtual void createSchema() {
        createMySQLSchema();
    }

    virtual std::string validConnectString() {
        return (validMySQLConnectionString());
    }

    virtual std::string invalidConnectString() {
        return (connectionString(MYSQL_VALID_TYPE, INVALID_NAME, VALID_HOST,
                                 VALID_USER, VALID_PASSWORD));
    }
};

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testRetryOpenDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testRetryOpenDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testRetryOpenDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testNoCallbackOnOpenFailure) {
    MultiThreadingTest mt(false);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testNoCallbackOnOpenFailureMultiThreading) {
    MultiThreadingTest mt(true);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySqlLeaseMgrDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Tests v4 lease stats query variants.
TEST_F(MySqlLeaseMgrTest, leaseStatsQuery4) {
    testLeaseStatsQuery4();
}

/// @brief Tests v4 lease stats query variants.
TEST_F(MySqlLeaseMgrTest, leaseStatsQuery4MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseStatsQuery4();
}

/// @brief Tests v6 lease stats query variants.
TEST_F(MySqlLeaseMgrTest, leaseStatsQuery6) {
    testLeaseStatsQuery6();
}

/// @brief Tests v6 lease stats query variants.
TEST_F(MySqlLeaseMgrTest, leaseStatsQuery6MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseStatsQuery6();
}

/// @brief Tests v4 lease stats to be attributed to the wrong subnet.
TEST_F(MySqlLeaseMgrTest, leaseStatsQueryAttribution4) {
    testLeaseStatsQueryAttribution4();
}

/// @brief Tests v4 lease stats to be attributed to the wrong subnet.
TEST_F(MySqlLeaseMgrTest, leaseStatsQueryAttribution4MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseStatsQueryAttribution4();
}

/// @brief Tests v6 lease stats to be attributed to the wrong subnet.
TEST_F(MySqlLeaseMgrTest, leaseStatsQueryAttribution6) {
    testLeaseStatsQueryAttribution6();
}

/// @brief Tests v6 lease stats to be attributed to the wrong subnet.
TEST_F(MySqlLeaseMgrTest, leaseStatsQueryAttribution6MultiThreading) {
    MultiThreadingTest mt(true);
    testLeaseStatsQueryAttribution6();
}

/// @brief This test is a basic check for the generic backend test class,
///        rather than any production code check.
TEST_F(MySqlGenericBackendTest, leaseCount) {

    // Create database connection parameter list
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";

    // Create and open the database connection
    MySqlConnection conn(params);
    conn.openDatabase();

    // Check that the countRows is working. It's used extensively in other
    // tests, so basic check is enough here.
    EXPECT_EQ(0, countRows(conn, "lease4"));
}

/// @brief Checks that no exceptions are thrown when inquiring about JSON
/// support and prints an informative message.
TEST_F(MySqlLeaseMgrTest, isJsonSupported) {
    bool json_supported;
    ASSERT_NO_THROW_LOG(json_supported = LeaseMgrFactory::instance().isJsonSupported());
    std::cout << "JSON support is " << (json_supported ? "" : "not ") <<
                 "enabled in the database." << std::endl;
}

// Verifies that v4 class lease counts are correctly adjusted
// when leases have class lists.
TEST_F(MySqlLeaseMgrTest, classLeaseCount4) {
    SKIP_IF(!LeaseMgrFactory::instance().isJsonSupported());

    testClassLeaseCount4();
}

// Verifies that v6 IA_NA class lease counts are correctly adjusted
// when leases have class lists.
TEST_F(MySqlLeaseMgrTest, classLeaseCount6_NA) {
    SKIP_IF(!LeaseMgrFactory::instance().isJsonSupported());

    testClassLeaseCount6(Lease::TYPE_NA);
}

// Verifies that v6 IA_PD class lease counts are correctly adjusted
// when leases have class lists.
TEST_F(MySqlLeaseMgrTest, classLeaseCount6_PD) {
    SKIP_IF(!LeaseMgrFactory::instance().isJsonSupported());

    testClassLeaseCount6(Lease::TYPE_PD);
}

/// @brief Checks that a null user context allows allocation.
TEST_F(MySqlLeaseMgrTest, checkLimitsNull) {
    std::string text;
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits4(nullptr));
    EXPECT_TRUE(text.empty());
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(nullptr));
    EXPECT_TRUE(text.empty());
}

/// @brief Checks a few v4 limit checking scenarios.
TEST_F(MySqlLeaseMgrTest, checkLimits4) {
    SKIP_IF(!LeaseMgrFactory::instance().isJsonSupported());

    // The rest of the checks are only for databases with JSON support.
    testLeaseLimits4();
}

/// @brief Checks a few v6 limit checking scenarios.
TEST_F(MySqlLeaseMgrTest, checkLimits6) {
    SKIP_IF(!LeaseMgrFactory::instance().isJsonSupported());

    // The rest of the checks are only for databases with JSON support.
    testLeaseLimits6();
}

/// @brief Checks if the backends call the callbacks when an
/// IPv4 lease is added.
TEST_F(MySqlLeaseMgrTest, trackAddLease4) {
    testTrackAddLease4(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv4 lease is added.
TEST_F(MySqlLeaseMgrTest, trackAddLease4MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackAddLease4(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 address lease is added.
TEST_F(MySqlLeaseMgrTest, trackAddLeaseNA) {
    testTrackAddLeaseNA(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 address lease is added.
TEST_F(MySqlLeaseMgrTest, trackAddLeaseNAMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackAddLeaseNA(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 prefix lease is added.
TEST_F(MySqlLeaseMgrTest, trackAddLeasePD) {
    testTrackAddLeasePD(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 prefix lease is added.
TEST_F(MySqlLeaseMgrTest, trackAddLeasePDMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackAddLeasePD(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv4 lease is updated.
TEST_F(MySqlLeaseMgrTest, trackUpdateLease4) {
    testTrackUpdateLease4(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv4 lease is updated.
TEST_F(MySqlLeaseMgrTest, trackUpdateLease4MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackUpdateLease4(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 address lease is updated.
TEST_F(MySqlLeaseMgrTest, trackUpdateLeaseNA) {
    testTrackUpdateLeaseNA(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 address lease is updated.
TEST_F(MySqlLeaseMgrTest, trackUpdateLeaseNAMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackUpdateLeaseNA(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 prefix lease is updated.
TEST_F(MySqlLeaseMgrTest, trackUpdateLeasePD) {
    testTrackUpdateLeasePD(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 prefix lease is updated.
TEST_F(MySqlLeaseMgrTest, trackUpdateLeasePDMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackUpdateLeasePD(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv4 lease is deleted.
TEST_F(MySqlLeaseMgrTest, trackDeleteLease4) {
    testTrackDeleteLease4(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv4 lease is deleted.
TEST_F(MySqlLeaseMgrTest, trackDeleteLease4MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackDeleteLease4(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 address lease is deleted.
TEST_F(MySqlLeaseMgrTest, trackDeleteLeaseNA) {
    testTrackDeleteLeaseNA(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 address lease is deleted.
TEST_F(MySqlLeaseMgrTest, trackDeleteLeaseNAMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackDeleteLeaseNA(true);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 prefix lease is deleted.
TEST_F(MySqlLeaseMgrTest, trackDeleteLeasePD) {
    testTrackDeleteLeasePD(false);
}

/// @brief Checks if the backends call the callbacks when an
/// IPv6 prefix lease is deleted.
TEST_F(MySqlLeaseMgrTest, trackDeleteLeasePDMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testTrackDeleteLeasePD(true);
}

/// @brief Checks that the lease manager can be recreated and its
/// registered callbacks preserved, if desired.
TEST_F(MySqlLeaseMgrTest, recreateWithCallbacks) {
    testRecreateWithCallbacks(validMySQLConnectionString());
}

/// @brief Checks that the lease manager can be recreated without the
/// previously registered callbacks.
TEST_F(MySqlLeaseMgrTest, recreateWithoutCallbacks) {
    testRecreateWithoutCallbacks(validMySQLConnectionString());
}

TEST_F(MySqlLeaseMgrTest, bigStats) {
    testBigStats();
}

}  // namespace
