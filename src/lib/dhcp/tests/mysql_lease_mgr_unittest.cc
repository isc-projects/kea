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

// Connection strings
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
    return (string(type) + space + string(name) + space + string(host) + space +
            string(user) + space + string(password));
}

// Return valid connection string
string validConnectionString() {
    return (connectionString(VALID_TYPE, VALID_NAME, VALID_HOST,
                             VALID_USER, VALID_PASSWORD));
}

/// @brief Test Fixture Class
///
/// Opens the database prior to each test and closes it afterwards.
/// All pending transactions are deleted prior to closure.

class MySqlLeaseMgrTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Open the database.

    MySqlLeaseMgrTest() {
        lmptr_ = LeaseMgrFactory::create(validConnectionString());
    }

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of the
    /// lmptr_ member variable will close the database.

    virtual ~MySqlLeaseMgrTest() {
        //lmptr_->rollback();
    }

    LeaseMgrPtr lmptr_;     // Pointer to the lease manager
};


/// @brief Check that Database Can Be Opened
///
/// This test checks if the MySqlLeaseMgr can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// MySqlLeaseMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(MySqlOpenTest, OpenDatabase) {
    LeaseMgrPtr lmptr;

    // Check that wrong specification of backend throws an exception.
    // (This is really a check on LeaseMgrFactory, but is convenient to
    // perform here.)
    EXPECT_THROW(lmptr = LeaseMgrFactory::create(connectionString(
        INVALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        InvalidParameter);

    // Check that invalid login data causes an exception.
    EXPECT_THROW(lmptr = LeaseMgrFactory::create(connectionString(
        VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(lmptr = LeaseMgrFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(lmptr = LeaseMgrFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(lmptr = LeaseMgrFactory::create(connectionString(
        VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);

    // Check that database opens correctly and that version is as expected
    ASSERT_NO_THROW(lmptr = LeaseMgrFactory::create(validConnectionString()));
    ASSERT_TRUE(lmptr);
}

/// @brief Check conversion functions
TEST_F(MySqlLeaseMgrTest, CheckTimeConversion) {
    const time_t cltt = time(NULL);
    const uint32_t valid_lft = 86400;       // 1 day
    MYSQL_TIME expire;
    uint32_t lease_time;

    MySqlLeaseMgr::convertFromLeaseTime(cltt, valid_lft, expire, lease_time);
    EXPECT_EQ(valid_lft, lease_time);
    EXPECT_LE(2012, expire.year);       // Code was written in 2012
    EXPECT_EQ(0, expire.second_part);
    EXPECT_EQ(0, expire.neg);

    // Convert back
    time_t converted_cltt = 0;
    uint32_t converted_valid_lft = 0;
    MySqlLeaseMgr::convertToLeaseTime(expire, lease_time, converted_cltt,
                                      converted_valid_lft);
    EXPECT_EQ(cltt, converted_cltt);
    EXPECT_EQ(valid_lft, converted_valid_lft);
}

/// @brief Check that getVersion() works
TEST_F(MySqlLeaseMgrTest, CheckVersion) {
    // Check version
    pair<uint32_t, uint32_t> version;
    ASSERT_NO_THROW(version = lmptr_->getVersion());
    EXPECT_EQ(0, version.first);
    EXPECT_EQ(1, version.second);
}


/// @brief Compare Lease4 Structure
bool
compareLease6(const Lease6Ptr& l1, const Lease6Ptr& l2) {
    return (
        l1->type_ == l2->type_ &&
        l1->addr_ == l2->addr_ &&
        l1->prefixlen_ == l2->prefixlen_ &&
        l1->iaid_ == l2->iaid_ &&
        l1->hwaddr_ == l2->hwaddr_ &&
        *l1->duid_ == *l2->duid_ &&
        l1->preferred_lft_ == l2->preferred_lft_ &&
        l1->valid_lft_ == l2->valid_lft_ &&
        l1->cltt_ == l2->cltt_ &&
        l1->subnet_id_ == l2->subnet_id_
        );
}

void
detailCompareLease6(const Lease6Ptr& l1, const Lease6Ptr& l2) {
    EXPECT_EQ(l1->type_, l2->type_);
    EXPECT_EQ(l1->addr_, l2->addr_);
    EXPECT_EQ(l1->prefixlen_, l2->prefixlen_);
    EXPECT_EQ(l1->iaid_, l2->iaid_);
    EXPECT_TRUE(l1->hwaddr_ == l2->hwaddr_);
    EXPECT_TRUE(*l1->duid_ == *l2->duid_);
    EXPECT_EQ(l1->preferred_lft_, l2->preferred_lft_);
    EXPECT_EQ(l1->valid_lft_, l2->valid_lft_);
    EXPECT_EQ(l1->cltt_, l2->cltt_);
    EXPECT_EQ(l1->subnet_id_, l2->subnet_id_);
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
    l1->hwaddr_ = std::vector<uint8_t>(6, 0x42);     // Six hex 42's
    l1->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));
    l1->preferred_lft_ = 3600;  // Preferred lifetime
    l1->valid_lft_ = 3600;      // Actual lifetime
    l1->cltt_ = 123456;         // Current time of day
    l1->subnet_id_ = 73;        // Arbitrary number

    const IOAddress L2_ADDRESS(std::string("2001:db8::2"));
    Lease6Ptr l2(new Lease6());
    initializeUnusedLease6(l2);

    l2->type_ = Lease6::LEASE_IA_TA;
    l2->addr_ = L1_ADDRESS;
    l2->prefixlen_ = 0;
    l2->iaid_ = 89;
    l2->hwaddr_ = std::vector<uint8_t>(6, 0xf43);     // Six hex 42's
    l2->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x3a)));
    l2->preferred_lft_ = 1800;  // Preferred lifetime
    l2->valid_lft_ = 5400;      // Actual lifetime
    l2->cltt_ = 234567;         // Current time of day
    l2->subnet_id_ = l1->subnet_id_;    // Same as l1

    // Sanity check that the leases are different
    ASSERT_FALSE(compareLease6(l1, l2));

    // Start the tests.  Add the first lease to the database.  Then read it
    // back to see whether it is what we think it is.
    Lease6Ptr l_returned;

    ASSERT_TRUE(lmptr_->addLease(l1));
    l_returned = lmptr_->getLease6(L1_ADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(l1, l_returned);
/*
    // Delete the lease and check that it has been deleted.
    EXPECT_TRUE(lmptr_->deleteLease6(L1_ADDRESS));
    l_returned = lmptr_->getLease6(L1_ADDRESS);
    EXPECT_FALSE(l_returned);

    // Add the address again and check that we can't add it a second time
    ASSERT_TRUE(lmptr_->addLease(l1));
    ASSERT_FALSE(lmptr_->addLease(l1));

    // Add the second lease
    ASSERT_TRUE(lmptr_->addLease(l2));

    // Finally, delete the lease and check we can't delete it again.
    EXPECT_TRUE(lmptr_->deleteLease6(L1_ADDRESS));
    EXPECT_FALSE(lmptr_->deleteLease6(L1_ADDRESS));
    */
}

}; // end of anonymous namespace
