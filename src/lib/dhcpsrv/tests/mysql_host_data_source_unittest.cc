// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/tests/test_utils.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/mysql_connection.h>
#include <dhcpsrv/mysql_host_data_source.h>
#include <dhcpsrv/tests/generic_host_data_source_unittest.h>
#include <dhcpsrv/tests/mysql_schema.h>
#include <dhcpsrv/host_data_source_factory.h>

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

class MySqlHostDataSourceTest : public GenericHostDataSourceTest {
public:
    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    MySqlHostDataSourceTest() {

        // Ensure schema is the correct one.
        destroyMySQLSchema();
        createMySQLSchema();

        // Connect to the database
        try {
            HostDataSourceFactory::create(validMySQLConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        hdsptr_ = HostDataSourceFactory::getHostDataSourcePtr();
    }

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of myhdsptr_ will close
    /// the database.  Then reopen it and delete everything created by the test.
    virtual ~MySqlHostDataSourceTest() {
        hdsptr_->rollback();
        HostDataSourceFactory::destroy();
        destroyMySQLSchema();
    }

    /// @brief Reopen the database
    ///
    /// Closes the database and re-open it.  Anything committed should be
    /// visible.
    ///
    /// Parameter is ignored for MySQL backend as the v4 and v6 leases share
    /// the same database.
    void reopen(Universe) {
        HostDataSourceFactory::destroy();
        HostDataSourceFactory::create(validMySQLConnectionString());
        hdsptr_ = HostDataSourceFactory::getHostDataSourcePtr();
    }

};

/// @brief Check that database can be opened
///
/// This test checks if the MySqlHostDataSource can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// MySqlLeaseMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(MySqlHostDataSource, OpenDatabase) {

    // Schema needs to be created for the test to work.
    destroyMySQLSchema();
    createMySQLSchema();

    // Check that lease manager open the database opens correctly and tidy up.
    //  If it fails, print the error message.
    try {
        HostDataSourceFactory::create(validMySQLConnectionString());
        EXPECT_NO_THROW((void) HostDataSourceFactory::getHostDataSourcePtr());
        HostDataSourceFactory::destroy();
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
    }

    // Check that attempting to get an instance of the lease manager when
    // none is set throws an exception.
    EXPECT_FALSE(HostDataSourceFactory::getHostDataSourcePtr());

    // Check that wrong specification of backend throws an exception.
    // (This is really a check on LeaseMgrFactory, but is convenient to
    // perform here.)
    EXPECT_THROW(HostDataSourceFactory::create(connectionString(
        NULL, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        InvalidParameter);
    EXPECT_THROW(HostDataSourceFactory::create(connectionString(
        INVALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        InvalidType);

    // Check that invalid login data causes an exception.
    EXPECT_THROW(HostDataSourceFactory::create(connectionString(
        VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostDataSourceFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostDataSourceFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostDataSourceFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);

    // Check for missing parameters
    EXPECT_THROW(HostDataSourceFactory::create(connectionString(
        VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        NoDatabaseName);

    // Tidy up after the test
    destroyMySQLSchema();
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
TEST(MySqlConnection, checkTimeConversion) {
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

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses hw address as identifier.
TEST_F(MySqlHostDataSourceTest, basic4HWAddr) {
    testBasic4(true);
}

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses client-id (DUID) as identifier.
TEST_F(MySqlHostDataSourceTest, basic4ClientId) {
    testBasic4(false);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses HW addresses as identifiers.
TEST_F(MySqlHostDataSourceTest, getByIPv4HWaddr) {
    testGetByIPv4(true);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses client-id (DUID) as identifiers.
TEST_F(MySqlHostDataSourceTest, getByIPv4ClientId) {
    testGetByIPv4(false);
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(MySqlHostDataSourceTest, get4ByHWaddr) {
    testGet4ByHWAddr();
}

// Test verifies if a host reservation can be added and later retrieved by
// client identifier.
TEST_F(MySqlHostDataSourceTest, get4ByClientId) {
    testGet4ByClientId();
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(MySqlHostDataSourceTest, hwaddrNotClientId1) {
    testHWAddrNotClientId();
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(MySqlHostDataSourceTest, hwaddrNotClientId2) {
    testClientIdNotHWAddr();
}

// Test verifies if a host with FQDN hostname can be stored and later retrieved.
TEST_F(MySqlHostDataSourceTest, hostnameFQDN) {
    testHostname("foo.example.org", 1);
}

// Test verifies if 100 hosts with unique FQDN hostnames can be stored and later
// retrieved.
TEST_F(MySqlHostDataSourceTest, hostnameFQDN100) {
    testHostname("foo.example.org", 100);
}

// Test verifies if a host without any hostname specified can be stored and later
// retrieved.
TEST_F(MySqlHostDataSourceTest, noHostname) {
    testHostname("", 1);
}

// Test verifies if the hardware or client-id query can match hardware address.
TEST_F(MySqlHostDataSourceTest, DISABLED_hwaddrOrClientId1) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with hardware address X, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

// Test verifies if the hardware or client-id query can match client-id.
TEST_F(MySqlHostDataSourceTest, DISABLED_hwaddrOrClientId2) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with client identifier Y, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

// Test verifies that host with IPv6 address and DUID can be added and
// later retrieved by IPv6 address.
TEST_F(MySqlHostDataSourceTest, get6AddrWithDuid) {
    /// @todo: Uncomment when IPv6 support (4212) is implemented.
    testGetByIPv6(BaseHostDataSource::ID_DUID, false);
}

// Test verifies that host with IPv6 address and HWAddr can be added and
// later retrieved by IPv6 address.
TEST_F(MySqlHostDataSourceTest, get6AddrWithHWAddr) {
    /// @todo: Uncomment when IPv6 support (4212) is implemented.
    testGetByIPv6(BaseHostDataSource::ID_HWADDR, false);
}

// Test verifies that host with IPv6 prefix and DUID can be added and
// later retrieved by IPv6 prefix.
TEST_F(MySqlHostDataSourceTest, get6PrefixWithDuid) {
    /// @todo: Uncomment when IPv6 support (4212) is implemented.
    testGetByIPv6(BaseHostDataSource::ID_DUID, true);
}

// Test verifies that host with IPv6 prefix and HWAddr can be added and
// later retrieved by IPv6 prefix.
TEST_F(MySqlHostDataSourceTest, get6PrefixWithHWaddr) {
    /// @todo: Uncomment when IPv6 support (4212) is implemented.
    testGetByIPv6(BaseHostDataSource::ID_HWADDR, true);
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(MySqlHostDataSourceTest, get6ByHWaddr) {
    /// @todo: Uncomment when IPv6 support (4212) is implemented.
    testGet6ByHWAddr();
}

// Test verifies if a host reservation can be added and later retrieved by
// client identifier.
TEST_F(MySqlHostDataSourceTest, get6ByClientId) {
    /// @todo: Uncomment when IPv6 support (4212) is implemented.
    testGet6ByClientId();
}

// Test verifies if a host reservation can be stored with both IPv6 address and
// prefix.
TEST_F(MySqlHostDataSourceTest, addr6AndPrefix) {
    /// @todo: Implement this test as part of #4212.

    /// @todo: Add host reservation with an IPv6 address and IPv6 prefix,
    /// retrieve it and verify that both v6 address and prefix are retrieved
    /// correctly.
}

// Test verifies if multiple client classes for IPv4 can be stored.
TEST_F(MySqlHostDataSourceTest, DISABLED_multipleClientClasses4) {
    /// @todo: Implement this test as part of #4213.

    /// Add host reservation with a multiple v4 client-classes, retrieve it and
    /// make sure that all client classes are retrieved properly.
}

// Test verifies if multiple client classes for IPv6 can be stored.
TEST_F(MySqlHostDataSourceTest, DISABLED_multipleClientClasses6) {
    /// @todo: Implement this test as part of #4213.

    /// Add host reservation with a multiple v6 client-classes, retrieve it and
    /// make sure that all client classes are retrieved properly.
}

// Test verifies if multiple client classes for both IPv4 and IPv6 can be stored.
TEST_F(MySqlHostDataSourceTest, DISABLED_multipleClientClassesBoth) {
    /// @todo: Implement this test as part of #4213.

    /// Add host reservation with a multiple v4 and v6 client-classes, retrieve
    /// it and make sure that all client classes are retrieved properly. Also,
    /// check that the classes are not confused.
}

// Test if the same host can have reservations in different subnets (with the
// same hardware address). The test logic is as follows:
// Insert 10 host reservations for a given physical host (the same
// hardware address), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them all correctly.
TEST_F(MySqlHostDataSourceTest, multipleSubnetsHWAddr) {
    testMultipleSubnets(10, true);
}

// Test if the same host can have reservations in different subnets (with the
// same client identifier). The test logic is as follows:
//
// Insert 10 host reservations for a given physical host (the same
// client-identifier), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them correctly.
TEST_F(MySqlHostDataSourceTest, multipleSubnetsClientId) {
    testMultipleSubnets(10, false);
}

// Test if host reservations made for different IPv6 subnets are handled correctly.
// The test logic is as follows:
//
// Insert 10 host reservations for different subnets. Make sure that
// get6(subnet-id, ...) calls return correct reservation.
TEST_F(MySqlHostDataSourceTest, subnetId6) {
    testSubnetId6(10, BaseHostDataSource::ID_HWADDR);
}

// Test if the duplicate host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
TEST_F(MySqlHostDataSourceTest, addDuplicate) {
    testAddDuplicate();
}

}; // Of anonymous namespace
