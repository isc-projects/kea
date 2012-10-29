// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <gtest/gtest.h>

#include <asiolink/io_address.h>
#include <dhcp/lease_mgr_factory.h>
#include <dhcp/mysql_lease_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace std;

namespace {

// Connection strings.  Assume:
// Database: keatest
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

// Clear everything from the database tables
void
clearAll() {
        // Initialise
        MYSQL handle;
        (void) mysql_init(&handle);

        // Open database
        (void) mysql_real_connect(&handle, "localhost", "keatest", "keatest",
                                  "keatest", 0, NULL, 0);

        // Clear the database
        (void) mysql_query(&handle, "DELETE FROM lease4");
        (void) mysql_query(&handle, "DELETE FROM lease6");

        // ... and close
        (void) mysql_close(&handle);
}

/// @brief Test Fixture Class
///
/// Opens the database prior to each test and closes it afterwards.
/// All pending transactions are deleted prior to closure.

class MySqlLeaseMgrTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    MySqlLeaseMgrTest() {
        clearAll();
        LeaseMgrFactory::create(validConnectionString());
        lmptr_ = &(LeaseMgrFactory::instance());
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

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of the
    /// lmptr_ member variable will close the database.  Then
    /// reopen it and delete everything created by the test.
    virtual ~MySqlLeaseMgrTest() {
        lmptr_->rollback();
        LeaseMgrFactory::destroy();
        clearAll();
    }

    LeaseMgr*   lmptr_;         // Pointer to the lease manager
};


/// @brief Check that Database Can Be Opened
///
/// This test checks if the MySqlLeaseMgr can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// MySqlLeaseMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(MySqlOpenTest, OpenDatabase) {
    // Check that database opens correctly and tidy up.  If it fails, print
    // the error message.
    try {
        LeaseMgrFactory::create(validConnectionString());
        EXPECT_NO_THROW((void) LeaseMgrFactory::instance());
        LeaseMgrFactory::destroy();
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what()
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
}

/// @brief Check conversion functions
TEST_F(MySqlLeaseMgrTest, CheckTimeConversion) {
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

/// @brief Check that getVersion() works
TEST_F(MySqlLeaseMgrTest, CheckVersion) {
    // Check version
    pair<uint32_t, uint32_t> version;
    ASSERT_NO_THROW(version = lmptr_->getVersion());
    EXPECT_EQ(CURRENT_VERSION_VERSION, version.first);
    EXPECT_EQ(CURRENT_VERSION_MINOR, version.second);
}

void
detailCompareLease6(const Lease6Ptr& first, const Lease6Ptr& second) {
    EXPECT_EQ(first->type_, second->type_);

    // Compare address strings - odd things happen when they are different
    // as the EXPECT_EQ appears to call the operator uint32_t() function,
    // which causes an exception to be thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_.toText(), second->addr_.toText());
    EXPECT_EQ(first->prefixlen_, second->prefixlen_);
    EXPECT_EQ(first->iaid_, second->iaid_);
    EXPECT_TRUE(*first->duid_ == *second->duid_);
    EXPECT_EQ(first->preferred_lft_, second->preferred_lft_);
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
}

/// @brief Initialize Lease
///
/// Initializes the unused fields in a lease to known values for
/// testing purposes.
void initializeUnusedLease6(Lease6Ptr& lease) {
    lease->t1_ = 0;                             // Not saved
    lease->t2_ = 0;                             // Not saved
    lease->fixed_ = false;                      // Unused
    lease->hostname_ = std::string("");         // Unused
    lease->fqdn_fwd_ = false;                   // Unused
    lease->fqdn_rev_ = false;                   // Unused
    lease->comments_ = std::string("");         // Unused
}

/// @brief Check individual Lease6 methods
///
/// Checks that the add/update/delete works.  All are done within one
/// test so that "rollback" can be used to remove trace of the tests
/// from the database.
///
/// Tests where a collection of leases can be returned are in the test
/// Lease6Collection.
TEST_F(MySqlLeaseMgrTest, BasicLease6) {

    // Define the leases being used for testing.
    const IOAddress L1_ADDRESS(std::string("2001:db8::1"));
    Lease6Ptr l1(new Lease6());
    initializeUnusedLease6(l1);

    l1->type_ = Lease6::LEASE_IA_TA;
    l1->addr_ = L1_ADDRESS;
    l1->prefixlen_ = 0;
    l1->iaid_ = 42;
    l1->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));
    l1->preferred_lft_ = 3600;  // Preferred lifetime
    l1->valid_lft_ = 3677;      // Actual lifetime
    l1->cltt_ = 123456;         // Current time of day
    l1->subnet_id_ = 73;        // Arbitrary number

    const IOAddress L2_ADDRESS(std::string("2001:db8::2"));
    Lease6Ptr l2(new Lease6());
    initializeUnusedLease6(l2);

    l2->type_ = Lease6::LEASE_IA_PD;
    l2->addr_ = L2_ADDRESS;
    l2->prefixlen_ = 7;
    l2->iaid_ = 89;
    l2->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x3a)));
    l2->preferred_lft_ = 1800;  // Preferred lifetime
    l2->valid_lft_ = 5412;      // Actual lifetime
    l2->cltt_ = 234567;         // Current time of day
    l2->subnet_id_ = l1->subnet_id_;    // Same as l1

    const IOAddress L3_ADDRESS(std::string("2001:db8::3"));
    Lease6Ptr l3(new Lease6());
    initializeUnusedLease6(l3);

    l3->type_ = Lease6::LEASE_IA_NA;
    l3->addr_ = L3_ADDRESS;
    l3->prefixlen_ = 28;
    l3->iaid_ = 0xfffffffe;
    vector<uint8_t> duid;
    for (uint8_t i = 0; i < 128; ++i) {
        duid.push_back(i + 5);
    }
    l3->duid_ = boost::shared_ptr<DUID>(new DUID(duid));

    // The times used in the next tests are deliberately restricted - we should
    // be avle to cope with valid lifetimes up to 0xffffffff.  However, this
    // will lead to overflows.
    // @TODO: test overflow conditions when code has been fixed
    l3->preferred_lft_ = 7200;          // Preferred lifetime
    l3->valid_lft_ = 7000;              // Actual lifetime
    l3->cltt_ = 234567;                 // Current time of day
    l3->subnet_id_ = l1->subnet_id_;    // Same as l1

    // Sanity check that the leases are different
    ASSERT_TRUE(*l1 != *l2);
    ASSERT_TRUE(*l1 != *l3);
    ASSERT_TRUE(*l2 != *l3);

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    Lease6Ptr l_returned;

    EXPECT_TRUE(lmptr_->addLease(l1));
    EXPECT_TRUE(lmptr_->addLease(l2));
    EXPECT_TRUE(lmptr_->addLease(l3));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen();

    // check that the values returned are as expected.
    l_returned = lmptr_->getLease6(L1_ADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(l1, l_returned);

    l_returned = lmptr_->getLease6(L2_ADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(l2, l_returned);

    l_returned = lmptr_->getLease6(L3_ADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(l3, l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(l1));

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease6(L1_ADDRESS));
    l_returned = lmptr_->getLease6(L1_ADDRESS);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease6(L1_ADDRESS));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease6(L2_ADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(l2, l_returned);
}

/// @brief Check getName() returns correct database name
TEST_F(MySqlLeaseMgrTest, getName) {
    EXPECT_EQ(std::string("keatest"), lmptr_->getName());

    // @TODO: check for the negative
}

}; // end of anonymous namespace
