// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/mysql_lease_mgr.h>
#include <dhcpsrv/tests/test_utils.h>
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
#include "schema_copy.h"

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
        (void) mysql_query(mysql, create_statement[i]);
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
    void reopen() {
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
    MySqlLeaseMgr::convertToDatabaseTime(cltt, valid_lft, mysql_expire);

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
    MySqlLeaseMgr::convertFromDatabaseTime(mysql_expire, valid_lft, converted_cltt);
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

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4 (by address) and deleteLease (with an
/// IPv4 address) works.
TEST_F(MySqlLeaseMgrTest, basicLease4) {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen();

    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress4_[1]));
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(ioaddress4_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease (IPv4 address) can handle NULL client-id.
/// (client-id is optional and may not be present)
TEST_F(MySqlLeaseMgrTest, lease4NullClientId) {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Let's clear client-id pointers
    leases[1]->client_id_ = ClientIdPtr();
    leases[2]->client_id_ = ClientIdPtr();
    leases[3]->client_id_ = ClientIdPtr();

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen();

    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Check that we can get the lease by HWAddr
    HWAddr tmp(leases[2]->hwaddr_, HTYPE_ETHER);
    Lease4Collection returned = lmptr_->getLease4(tmp);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[2], *returned.begin());

    l_returned = lmptr_->getLease4(tmp, leases[2]->subnet_id_);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);


    // Check that we can update the lease
    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->subnet_id_;
    leases[1]->valid_lft_ *= 2;
    lmptr_->updateLease4(leases[1]);

    // ... and check that the lease is indeed updated
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);



    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress4_[1]));
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(ioaddress4_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

}

/// @brief Verify that too long hostname for Lease4 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(MySqlLeaseMgrTest, lease4InvalidHostname) {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Create a dummy hostname, consisting of 255 characters.
    leases[1]->hostname_.assign(255, 'a');
    ASSERT_TRUE(lmptr_->addLease(leases[1]));

    // The new lease must be in the database.
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    detailCompareLease(leases[1], l_returned);

    // Let's delete the lease, so as we can try to add it again with
    // invalid hostname.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress4_[1]));

    // Create a hostname with 256 characters. It should not be accepted.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->addLease(leases[1]), DbOperationError);
}

/// @brief Basic Lease6 Checks
///
/// Checks that the addLease, getLease6 (by address) and deleteLease (with an
/// IPv6 address) works.
TEST_F(MySqlLeaseMgrTest, basicLease6) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen();

    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    l_returned = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease6(leasetype6_[3], ioaddress6_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress6_[1]));
    l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(ioaddress6_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);
}

/// @brief Verify that too long hostname for Lease6 is not accepted.
///
/// Checks that the it is not possible to create a lease when the hostname
/// length exceeds 255 characters.
TEST_F(MySqlLeaseMgrTest, lease6InvalidHostname) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();

    // Create a dummy hostname, consisting of 255 characters.
    leases[1]->hostname_.assign(255, 'a');
    ASSERT_TRUE(lmptr_->addLease(leases[1]));

    // The new lease must be in the database.
    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    detailCompareLease(leases[1], l_returned);

    // Let's delete the lease, so as we can try to add it again with
    // invalid hostname.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress6_[1]));

    // Create a hostname with 256 characters. It should not be accepted.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->addLease(leases[1]), DbOperationError);
}

/// @brief Check GetLease4 methods - access by Hardware Address
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DIUID and IAID.
TEST_F(MySqlLeaseMgrTest, getLease4Hwaddr) {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the hardware address of lease 1
    // @todo: Simply use HWAddr directly once 2589 is implemented
    HWAddr tmp(leases[1]->hwaddr_, HTYPE_ETHER);
    Lease4Collection returned = lmptr_->getLease4(tmp);

    // Should be three leases, matching leases[1], [3] and [5].
    ASSERT_EQ(3, returned.size());

    // Easiest way to check is to look at the addresses.
    vector<string> addresses;
    for (Lease4Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        addresses.push_back((*i)->addr_.toText());
    }
    sort(addresses.begin(), addresses.end());
    EXPECT_EQ(straddress4_[1], addresses[0]);
    EXPECT_EQ(straddress4_[3], addresses[1]);
    EXPECT_EQ(straddress4_[5], addresses[2]);

    // Repeat test with just one expected match
    // @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(leases[2]->hwaddr_, HTYPE_ETHER));
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[2], *returned.begin());

    // Check that an empty vector is valid
    EXPECT_TRUE(leases[7]->hwaddr_.empty());
    // @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(leases[7]->hwaddr_, HTYPE_ETHER));
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[7], *returned.begin());

    // Try to get something with invalid hardware address
    vector<uint8_t> invalid(6, 0);
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());
}

// @brief Get lease4 by hardware address (2)
//
// Check that the system can cope with getting a hardware address of
// any size.
TEST_F(MySqlLeaseMgrTest, getLease4HwaddrSize) {

    // Create leases, although we need only one.
    vector<Lease4Ptr> leases = createLeases4();

    // Now add leases with increasing hardware address size.
    for (uint8_t i = 0; i <= HWAddr::MAX_HWADDR_LEN; ++i) {
        leases[1]->hwaddr_.resize(i, i);
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        // @todo: Simply use HWAddr directly once 2589 is implemented
        Lease4Collection returned =
            lmptr_->getLease4(HWAddr(leases[1]->hwaddr_, HTYPE_ETHER));

        ASSERT_EQ(1, returned.size());
        detailCompareLease(leases[1], *returned.begin());
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Database should not let us add one that is too big
    // (The 42 is a random value put in each byte of the address.)
    // @todo: 2589 will make this test impossible
    leases[1]->hwaddr_.resize(HWAddr::MAX_HWADDR_LEN + 100, 42);
    EXPECT_THROW(lmptr_->addLease(leases[1]), isc::dhcp::DbOperationError);
}

/// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of hardware address and subnet ID
TEST_F(MySqlLeaseMgrTest, getLease4HwaddrSubnetId) {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the hardware address of lease 1 and
    // subnet ID of lease 1.  Result should be a single lease - lease 1.
    // @todo: Simply use HWAddr directly once 2589 is implemented
    Lease4Ptr returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_,
        HTYPE_ETHER), leases[1]->subnet_id_);

    ASSERT_TRUE(returned);
    detailCompareLease(leases[1], returned);

    // Try for a match to the hardware address of lease 1 and the wrong
    // subnet ID.
    // @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_, HTYPE_ETHER),
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Try for a match to the subnet ID of lease 1 (and lease 4) but
    // the wrong hardware address.
    vector<uint8_t> invalid_hwaddr(15, 0x77);
    // @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(invalid_hwaddr, HTYPE_ETHER),
                                 leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    // Try for a match to an unknown hardware address and an unknown
    // subnet ID.
    // @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(invalid_hwaddr, HTYPE_ETHER),
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Add a second lease with the same values as the first and check that
    // an attempt to access the database by these parameters throws a
    // "multiple records" exception. (We expect there to be only one record
    // with that combination, so getting them via getLeaseX() (as opposed
    // to getLeaseXCollection() should throw an exception.)
    EXPECT_TRUE(lmptr_->deleteLease(leases[2]->addr_));
    leases[1]->addr_ = leases[2]->addr_;
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    // @todo: Simply use HWAddr directly once 2589 is implemented
    EXPECT_THROW(returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_,
                                                    HTYPE_ETHER),
                                             leases[1]->subnet_id_),
                 isc::dhcp::MultipleRecords);

}

// @brief Get lease4 by hardware address and subnet ID (2)
//
// Check that the system can cope with getting a hardware address of
// any size.
TEST_F(MySqlLeaseMgrTest, getLease4HwaddrSubnetIdSize) {

    // Create leases, although we need only one.
    vector<Lease4Ptr> leases = createLeases4();

    // Now add leases with increasing hardware address size and check
    // that they can be retrieved.
    for (uint8_t i = 0; i <= HWAddr::MAX_HWADDR_LEN; ++i) {
        leases[1]->hwaddr_.resize(i, i);
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        // @todo: Simply use HWAddr directly once 2589 is implemented
        Lease4Ptr returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_,
                                                      HTYPE_ETHER),
                                               leases[1]->subnet_id_);
        ASSERT_TRUE(returned);
        detailCompareLease(leases[1], returned);
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Database should not let us add one that is too big
    // (The 42 is a random value put in each byte of the address.)
    leases[1]->hwaddr_.resize(HWAddr::MAX_HWADDR_LEN + 100, 42);
    EXPECT_THROW(lmptr_->addLease(leases[1]), isc::dhcp::DbOperationError);
}

/// @brief Check GetLease4 methods - access by Client ID
///
/// Adds leases to the database and checks that they can be accessed via
/// the Client ID.
TEST_F(MySqlLeaseMgrTest, getLease4ClientId) {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the Client ID address of lease 1
    Lease4Collection returned = lmptr_->getLease4(*leases[1]->client_id_);

    // Should be four leases, matching leases[1], [4], [5] and [6].
    ASSERT_EQ(4, returned.size());

    // Easiest way to check is to look at the addresses.
    vector<string> addresses;
    for (Lease4Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        addresses.push_back((*i)->addr_.toText());
    }
    sort(addresses.begin(), addresses.end());
    EXPECT_EQ(straddress4_[1], addresses[0]);
    EXPECT_EQ(straddress4_[4], addresses[1]);
    EXPECT_EQ(straddress4_[5], addresses[2]);
    EXPECT_EQ(straddress4_[6], addresses[3]);

    // Repeat test with just one expected match
    returned = lmptr_->getLease4(*leases[3]->client_id_);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[3], *returned.begin());

    // Check that client-id is NULL
    EXPECT_FALSE(leases[7]->client_id_);
    HWAddr tmp(leases[7]->hwaddr_, HTYPE_ETHER);
    returned = lmptr_->getLease4(tmp);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[7], *returned.begin());

    // Try to get something with invalid client ID
    const uint8_t invalid_data[] = {0, 0, 0};
    ClientId invalid(invalid_data, sizeof(invalid_data));
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());
}

// @brief Get Lease4 by client ID (2)
//
// Check that the system can cope with a client ID of any size.
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSize) {

    // Create leases, although we need only one.
    vector<Lease4Ptr> leases = createLeases4();

    // Now add leases with increasing Client ID size can be retrieved.
    // For speed, go from 0 to 128 is steps of 16.
    // Intermediate client_id_max is to overcome problem if
    // ClientId::MAX_CLIENT_ID_LEN is used in an EXPECT_EQ.
    int client_id_max = ClientId::MAX_CLIENT_ID_LEN;
    EXPECT_EQ(128, client_id_max);

    int client_id_min = ClientId::MIN_CLIENT_ID_LEN;
    EXPECT_EQ(2, client_id_min); // See RFC2132, section 9.14

    for (uint8_t i = client_id_min; i <= client_id_max; i += 16) {
        vector<uint8_t> clientid_vec(i, i);
        leases[1]->client_id_.reset(new ClientId(clientid_vec));
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        Lease4Collection returned = lmptr_->getLease4(*leases[1]->client_id_);
        ASSERT_TRUE(returned.size() == 1);
        detailCompareLease(leases[1], *returned.begin());
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Don't bother to check client IDs longer than the maximum -
    // these cannot be constructed, and that limitation is tested
    // in the DUID/Client ID unit tests.
}

/// @brief Check GetLease4 methods - access by Client ID & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of client and subnet IDs.
TEST_F(MySqlLeaseMgrTest, getLease4ClientIdSubnetId) {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the client ID of lease 1 and
    // subnet ID of lease 1.  Result should be a single lease - lease 1.
    Lease4Ptr returned = lmptr_->getLease4(*leases[1]->client_id_,
                                           leases[1]->subnet_id_);
    ASSERT_TRUE(returned);
    detailCompareLease(leases[1], returned);

    // Try for a match to the client ID of lease 1 and the wrong
    // subnet ID.
    returned = lmptr_->getLease4(*leases[1]->client_id_,
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Try for a match to the subnet ID of lease 1 (and lease 4) but
    // the wrong client ID
    const uint8_t invalid_data[] = {0, 0, 0};
    ClientId invalid(invalid_data, sizeof(invalid_data));
    returned = lmptr_->getLease4(invalid, leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    // Try for a match to an unknown hardware address and an unknown
    // subnet ID.
    returned = lmptr_->getLease4(invalid, leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);
}

/// @brief Check GetLease6 methods - access by DUID/IAID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DIUID and IAID.
/// @todo: update this test once type checking/filtering is implemented
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaid) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    ASSERT_LE(6, leases.size());    // Expect to access leases 0 through 5

    // Add them to the database
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the DUID and IAID of lease[1].
    Lease6Collection returned = lmptr_->getLeases6(leasetype6_[1],
                                                   *leases[1]->duid_,
                                                   leases[1]->iaid_);

    // Should be three leases, matching leases[1], [4] and [5].
    ASSERT_EQ(3, returned.size());

    // Easiest way to check is to look at the addresses.
    vector<string> addresses;
    for (Lease6Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        addresses.push_back((*i)->addr_.toText());
    }
    sort(addresses.begin(), addresses.end());
    EXPECT_EQ(straddress6_[1], addresses[0]);
    EXPECT_EQ(straddress6_[4], addresses[1]);
    EXPECT_EQ(straddress6_[5], addresses[2]);

    // Check that nothing is returned when either the IAID or DUID match
    // nothing.
    returned = lmptr_->getLeases6(leasetype6_[1], *leases[1]->duid_,
                                  leases[1]->iaid_ + 1);
    EXPECT_EQ(0, returned.size());

    // Alter the leases[1] DUID to match nothing in the database.
    vector<uint8_t> duid_vector = leases[1]->duid_->getDuid();
    ++duid_vector[0];
    DUID new_duid(duid_vector);
    returned = lmptr_->getLeases6(leasetype6_[1], new_duid, leases[1]->iaid_);
    EXPECT_EQ(0, returned.size());
}

// @brief Get Lease4 by DUID and IAID (2)
//
// Check that the system can cope with a DUID of any size.
/// @todo: update this test once type checking/filtering is implemented
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSize) {

    // Create leases, although we need only one.
    vector<Lease6Ptr> leases = createLeases6();

    // Now add leases with increasing DUID size can be retrieved.
    // For speed, go from 0 to 128 is steps of 16.
    int duid_max = DUID::MAX_DUID_LEN;
    EXPECT_EQ(128, duid_max);

    int duid_min = DUID::MIN_DUID_LEN;
    EXPECT_EQ(1, duid_min);

    for (uint8_t i = duid_min; i <= duid_max; i += 16) {
        vector<uint8_t> duid_vec(i, i);
        leases[1]->duid_.reset(new DUID(duid_vec));
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        Lease6Collection returned = lmptr_->getLeases6(leasetype6_[1],
                                                       *leases[1]->duid_,
                                                       leases[1]->iaid_);
        ASSERT_EQ(1, returned.size());
        detailCompareLease(leases[1], *returned.begin());
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Don't bother to check DUIDs longer than the maximum - these cannot be
    // constructed, and that limitation is tested in the DUID/Client ID unit
    // tests.
}

/// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DIUID and IAID.
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetId) {
    // Get the leases to be used for the test and add them to the database.
    vector<Lease6Ptr> leases = createLeases6();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the DUID and IAID of lease[1].
    Lease6Ptr returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                           leases[1]->iaid_,
                                           leases[1]->subnet_id_);
    ASSERT_TRUE(returned);
    EXPECT_TRUE(*returned == *leases[1]);

    // Modify each of the three parameters (DUID, IAID, Subnet ID) and
    // check that nothing is returned.
    returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                 leases[1]->iaid_ + 1, leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                 leases[1]->iaid_, leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Alter the leases[1] DUID to match nothing in the database.
    vector<uint8_t> duid_vector = leases[1]->duid_->getDuid();
    ++duid_vector[0];
    DUID new_duid(duid_vector);
    returned = lmptr_->getLease6(leasetype6_[1], new_duid, leases[1]->iaid_,
                                 leases[1]->subnet_id_);
    EXPECT_FALSE(returned);
}

// @brief Get Lease4 by DUID, IAID & subnet ID (2)
//
// Check that the system can cope with a DUID of any size.
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaidSubnetIdSize) {

    // Create leases, although we need only one.
    vector<Lease6Ptr> leases = createLeases6();

    // Now add leases with increasing DUID size can be retrieved.
    // For speed, go from 0 to 128 is steps of 16.
    int duid_max = DUID::MAX_DUID_LEN;
    EXPECT_EQ(128, duid_max);

    int duid_min = DUID::MIN_DUID_LEN;
    EXPECT_EQ(1, duid_min);

    for (uint8_t i = duid_min; i <= duid_max; i += 16) {
        vector<uint8_t> duid_vec(i, i);
        leases[1]->duid_.reset(new DUID(duid_vec));
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        Lease6Ptr returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                               leases[1]->iaid_,
                                               leases[1]->subnet_id_);
        ASSERT_TRUE(returned);
        detailCompareLease(leases[1], returned);
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Don't bother to check DUIDs longer than the maximum - these cannot be
    // constructed, and that limitation is tested in the DUID/Client ID unit
    // tests.
}

/// @brief Lease4 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(MySqlLeaseMgrTest, updateLease4) {
    // Get the leases to be used for the test and add them to the database.
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->subnet_id_;
    leases[1]->valid_lft_ *= 2;
    leases[1]->hostname_ = "modified.hostname.";
    leases[1]->fqdn_fwd_ = !leases[1]->fqdn_fwd_;
    leases[1]->fqdn_rev_ = !leases[1]->fqdn_rev_;;
    lmptr_->updateLease4(leases[1]);

    // ... and check what is returned is what is expected.
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Alter the lease again and check.
    ++leases[1]->subnet_id_;
    leases[1]->cltt_ += 6;
    lmptr_->updateLease4(leases[1]);

    // Explicitly clear the returned pointer before getting new data to ensure
    // that the new data is returned.
    l_returned.reset();
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Check we can do an update without changing data.
    lmptr_->updateLease4(leases[1]);
    l_returned.reset();
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Try to update the lease with the too long hostname.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->updateLease4(leases[1]), isc::dhcp::DbOperationError);

    // Try updating a lease not in the database.
    lmptr_->deleteLease(ioaddress4_[2]);
    EXPECT_THROW(lmptr_->updateLease4(leases[2]), isc::dhcp::NoSuchLease);
}

/// @brief Lease6 update tests
///
/// Checks that we are able to update a lease in the database.
TEST_F(MySqlLeaseMgrTest, updateLease6) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    ASSERT_LE(3, leases.size());    // Expect to access leases 0 through 2

    // Add a lease to the database and check that the lease is there.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    lmptr_->commit();

    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease6::LEASE_IA_PD;
    leases[1]->valid_lft_ *= 2;
    leases[1]->hostname_ = "modified.hostname.v6.";
    leases[1]->fqdn_fwd_ = !leases[1]->fqdn_fwd_;
    leases[1]->fqdn_rev_ = !leases[1]->fqdn_rev_;;
    lmptr_->updateLease6(leases[1]);
    lmptr_->commit();

    // ... and check what is returned is what is expected.
    l_returned.reset();
    l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Alter the lease again and check.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease6::LEASE_IA_TA;
    leases[1]->cltt_ += 6;
    leases[1]->prefixlen_ = 93;
    lmptr_->updateLease6(leases[1]);

    l_returned.reset();
    l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Check we can do an update without changing data.
    lmptr_->updateLease6(leases[1]);
    l_returned.reset();
    l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Try to update the lease with the too long hostname.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->updateLease6(leases[1]), isc::dhcp::DbOperationError);

    // Try updating a lease not in the database.
    EXPECT_THROW(lmptr_->updateLease6(leases[2]), isc::dhcp::NoSuchLease);
}

}; // Of anonymous namespace
