// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/mysql_connection.h>
#include <dhcpsrv/mysql_lease_mgr.h>
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
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace std;

namespace {

// This holds statements to create and destroy the schema.
#include "schema_mysql_copy.h"

// Connection strings.
// Database: keatest
// Host: localhost
// Username: keatest
// Password: keatest
const char* VALID_TYPE = "type=mysql";
const char* INVALID_TYPE = "type=unknown";
const char* VALID_NAME = "name=keatest";
const char* INVALID_NAME = "name=invalidname";
const char* VALID_HOST = "host=localhost";
const char* INVALID_HOST = "host=invalidhost";
const char* VALID_USER = "user=keatest";
const char* INVALID_USER = "user=invaliduser";
const char* VALID_PASSWORD = "password=keatest";
const char* INVALID_PASSWORD = "password=invalid";

// Given a combination of strings above, produce a connection string.
string connectionString(const char* type, const char* name, const char* host,
                        const char* user, const char* password) {
    const string space = " ";
    string result = "";

    if (type != NULL) {
        result += string(type);
    }
    if (name != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(name);
    }

    if (host != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(host);
    }

    if (user != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(user);
    }

    if (password != NULL) {
        if (! result.empty()) {
            result += space;
        }
        result += string(password);
    }

    return (result);
}

// Return valid connection string
string
validConnectionString() {
    return (connectionString(VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

// @brief Clear everything from the database
//
// There is no error checking in this code: if something fails, one of the
// tests will (should) fall over.
void destroySchema() {
    MySqlHolder mysql;

    // Open database
    (void) mysql_real_connect(mysql, "localhost", "keatest",
                              "keatest", "keatest", 0, NULL, 0);

    // Get rid of everything in it.
    for (int i = 0; destroy_statement[i] != NULL; ++i) {
        (void) mysql_query(mysql, destroy_statement[i]);
    }
}

// @brief Create the Schema
//
// Creates all the tables in what is assumed to be an empty database.
//
// There is no error checking in this code: if it fails, one of the tests
// will fall over.
void createSchema() {
    MySqlHolder mysql;

    // Open database
    (void) mysql_real_connect(mysql, "localhost", "keatest",
                              "keatest", "keatest", 0, NULL, 0);

    // Execute creation statements.
    for (int i = 0; create_statement[i] != NULL; ++i) {
        ASSERT_EQ(0, mysql_query(mysql, create_statement[i]))
            << "Failed on statement " << i << ": " << create_statement[i];
    }
}

/// @brief Test fixture class for testing MySQL Lease Manager
///
/// Opens the database prior to each test and closes it afterwards.
/// All pending transactions are deleted prior to closure.

class MySqlLeaseMgrTest : public GenericLeaseMgrTest {
public:
    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    MySqlLeaseMgrTest() {

        // Ensure schema is the correct one.
        destroySchema();
        createSchema();

        // Connect to the database
        try {
            LeaseMgrFactory::create(validConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
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
    virtual ~MySqlLeaseMgrTest() {
        lmptr_->rollback();
        LeaseMgrFactory::destroy();
        destroySchema();
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
        LeaseMgrFactory::create(validConnectionString());
        lmptr_ = &(LeaseMgrFactory::instance());
    }

};

/// @brief Check that database can be opened
///
/// This test checks if the MySqlLeaseMgr can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// MySqlLeaseMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(MySqlOpenTest, OpenDatabase) {

    // Schema needs to be created for the test to work.
    destroySchema();
    createSchema();

    // Check that lease manager open the database opens correctly and tidy up.
    //  If it fails, print the error message.
    try {
        LeaseMgrFactory::create(validConnectionString());
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
        VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);

    // Check for missing parameters
    EXPECT_THROW(LeaseMgrFactory::create(connectionString(
        VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        NoDatabaseName);

    // Tidy up after the test
    destroySchema();
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
    EXPECT_EQ(CURRENT_VERSION_VERSION, version.first);
    EXPECT_EQ(CURRENT_VERSION_MINOR, version.second);
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

/// @brief Check that Lease4 code safely handles invalid dates.
TEST_F(MySqlLeaseMgrTest, maxDate4) {
    testMaxDate4();
}

/// @brief Lease4 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(MySqlLeaseMgrTest, updateLease4) {
    testUpdateLease4();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(MySqlLeaseMgrTest, getLease4HWAddr1) {
    testGetLease4HWAddr1();
}

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(MySqlLeaseMgrTest, getLease4HWAddr2) {
    testGetLease4HWAddr2();
}

// @brief Get lease4 by hardware address (2)
//
// Check that the system can cope with getting a hardware address of
// any size.
TEST_F(MySqlLeaseMgrTest, getLease4HWAddrSize) {
    testGetLease4HWAddrSize();
}

/// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of hardware address and subnet ID
TEST_F(MySqlLeaseMgrTest, getLease4HwaddrSubnetId) {
    testGetLease4HWAddrSubnetId();
}

// @brief Get lease4 by hardware address and subnet ID (2)
//
// Check that the system can cope with getting a hardware address of
// any size.
TEST_F(MySqlLeaseMgrTest, getLease4HWAddrSubnetIdSize) {
    testGetLease4HWAddrSubnetIdSize();
}

// This test was derived from memfile.
TEST_F(MySqlLeaseMgrTest, getLease4ClientId) {
    testGetLease4ClientId();
}

/// @brief Check GetLease4 methods - access by Client ID
///
/// Adds leases to the database and checks that they can be accessed via
/// the Client ID.
TEST_F(MySqlLeaseMgrTest, getLease4ClientId2) {
    testGetLease4ClientId2();
}

// @brief Get Lease4 by client ID (2)
//
// Check that the system can cope with a client ID of any size.
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSize) {
    testGetLease4ClientIdSize();
}

/// @brief Check GetLease4 methods - access by Client ID & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of client and subnet IDs.
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSubnetId) {
    testGetLease4ClientIdSubnetId();
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease (IPv4 address) can handle NULL client-id.
/// (client-id is optional and may not be present)
TEST_F(MySqlLeaseMgrTest, lease4NullClientId) {
    testLease4NullClientId();
}

/// @brief Verify that too long hostname for Lease4 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(MySqlLeaseMgrTest, lease4InvalidHostname) {
    testLease4InvalidHostname();
}

////////////////////////////////////////////////////////////////////////////////
/// LEASE6 /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Test checks whether simple add, get and delete operations are possible
// on Lease6
TEST_F(MySqlLeaseMgrTest, testAddGetDelete6) {
    testAddGetDelete6(false);
}

/// @brief Basic Lease6 Checks
///
/// Checks that the addLease, getLease6 (by address) and deleteLease (with an
/// IPv6 address) works.
TEST_F(MySqlLeaseMgrTest, basicLease6) {
    testBasicLease6();
}

/// @brief Check that Lease6 code safely handles invalid dates.
TEST_F(MySqlLeaseMgrTest, maxDate6) {
    testMaxDate6();
}

/// @brief Verify that too long hostname for Lease6 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(MySqlLeaseMgrTest, lease6InvalidHostname) {
    testLease6InvalidHostname();
}

/// @brief Check GetLease6 methods - access by DUID/IAID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DUID and IAID.
TEST_F(MySqlLeaseMgrTest, getLeases6DuidIaid) {
    testGetLeases6DuidIaid();
}

// Check that the system can cope with a DUID of allowed size.
TEST_F(MySqlLeaseMgrTest, getLeases6DuidSize) {
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

/// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DIUID and IAID.
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetId) {
    testGetLease6DuidIaidSubnetId();
}

// Test checks that getLease6() works with different DUID sizes
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetIdSize) {
    testGetLease6DuidIaidSubnetIdSize();
}

/// @brief Lease6 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(MySqlLeaseMgrTest, updateLease6) {
    testUpdateLease6();
}

/// @brief DHCPv4 Lease recreation tests
///
/// Checks that the lease can be created, deleted and recreated with
/// different parameters. It also checks that the re-created lease is
/// correctly stored in the lease database.
TEST_F(MySqlLeaseMgrTest, testRecreateLease4) {
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

/// @brief Checks that null DUID is not allowed.
TEST_F(MySqlLeaseMgrTest, nullDuid) {
    testNullDuid();
}

/// @brief Tests whether memfile can store and retrieve hardware addresses
TEST_F(MySqlLeaseMgrTest, testLease6Mac) {
    testLease6MAC();
}

/// @brief Tests whether memfile can store and retrieve hardware addresses
TEST_F(MySqlLeaseMgrTest, testLease6HWTypeAndSource) {
    testLease6HWTypeAndSource();
}

}; // Of anonymous namespace
