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

// Creation of the schema
#include "schema_copy.h"

// IPv6 addresseses
const char* ADDRESS_0 = "2001:db8::0";
const char* ADDRESS_1 = "2001:db8::1";
const char* ADDRESS_2 = "2001:db8::2";
const char* ADDRESS_3 = "2001:db8::3";
const char* ADDRESS_4 = "2001:db8::4";
const char* ADDRESS_5 = "2001:db8::5";
const char* ADDRESS_6 = "2001:db8::6";
const char* ADDRESS_7 = "2001:db8::7";

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

// @brief Clear everything from the database
//
// There is no error checking in this code: if something fails, one of the
// tests will fall over.
void destroySchema() {
    // Initialise
    MYSQL handle;
    (void) mysql_init(&handle);

    // Open database
    (void) mysql_real_connect(&handle, "localhost", "keatest",
                              "keatest", "keatest", 0, NULL, 0);

    // Get rid of everything in it.
    for (int i = 0; destroy_statement[i] != NULL; ++i) {
        (void) mysql_query(&handle, destroy_statement[i]);
    }

    // ... and close
    (void) mysql_close(&handle);
}

// @brief Create the Schema
//
// Creates all the tables in what is assumed to be an empty database.
//
// There is no error checking in this code: if it fails, one of the tests
// will fall over.
void createSchema() {
    // Initialise
    MYSQL handle;
    (void) mysql_init(&handle);

    // Open database
    (void) mysql_real_connect(&handle, "localhost", "keatest",
                              "keatest", "keatest", 0, NULL, 0);

    // Get rid of everything in it.
    for (int i = 0; create_statement[i] != NULL; ++i) {
        (void) mysql_query(&handle, create_statement[i]);
    }

    // ... and close
    (void) mysql_close(&handle);
}

// Note: Doxygen "///" not used - even though Doxygen is used to
// document class and methods - to avoid the comments appearing
// in the programming manual.

// @brief Test Fixture Class
//
// Opens the database prior to each test and closes it afterwards.
// All pending transactions are deleted prior to closure.

class MySqlLeaseMgrTest : public ::testing::Test {
public:
    // @brief Constructor
    //
    // Deletes everything from the database and opens it.
    MySqlLeaseMgrTest() :
        L0_ADDRESS(ADDRESS_0), L0_IOADDRESS(L0_ADDRESS), 
        L1_ADDRESS(ADDRESS_1), L1_IOADDRESS(L1_ADDRESS), 
        L2_ADDRESS(ADDRESS_2), L2_IOADDRESS(L2_ADDRESS), 
        L3_ADDRESS(ADDRESS_3), L3_IOADDRESS(L3_ADDRESS), 
        L4_ADDRESS(ADDRESS_4), L4_IOADDRESS(L4_ADDRESS), 
        L5_ADDRESS(ADDRESS_5), L5_IOADDRESS(L5_ADDRESS), 
        L6_ADDRESS(ADDRESS_6), L6_IOADDRESS(L6_ADDRESS), 
        L7_ADDRESS(ADDRESS_7), L7_IOADDRESS(L7_ADDRESS) {

        destroySchema();
        createSchema();
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

    // @brief Destructor
    //
    // Rolls back all pending transactions.  The deletion of the
    // lmptr_ member variable will close the database.  Then
    // reopen it and delete everything created by the test.
    virtual ~MySqlLeaseMgrTest() {
        lmptr_->rollback();
        LeaseMgrFactory::destroy();
        destroySchema();
    }

    // @brief Reopen the database
    //
    // Closes the database and re-open it.  Anything committed should be
    // visible.
    void reopen() {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create(validConnectionString());
        lmptr_ = &(LeaseMgrFactory::instance());
    }

    // @brief Initialize Lease6 Fields
    //
    // Returns a pointer to a Lease6 structure.  Different values are put
    // in the lease according to the address passed.
    //
    // This is just a convenience function for the test methods.
    //
    // @param address Address to use for the initialization
    //
    // @return Lease6Ptr.  This will not point to anything if the initialization
    //         failed (e.g. unknown address).
    Lease6Ptr initializeLease6(std::string address) {
        Lease6Ptr lease(new Lease6());

        // Set the address of the lease
        lease->addr_ = IOAddress(address);

        // Initialize unused fields.
        lease->t1_ = 0;                             // Not saved
        lease->t2_ = 0;                             // Not saved
        lease->fixed_ = false;                      // Unused
        lease->hostname_ = std::string("");         // Unused
        lease->fqdn_fwd_ = false;                   // Unused
        lease->fqdn_rev_ = false;                   // Unused
        lease->comments_ = std::string("");         // Unused

        // Set the other parameters.  For historical reasons, L0_ADDRESS is not used.
        if (address == L0_ADDRESS) {
            lease->type_ = Lease6::LEASE_IA_TA;
            lease->prefixlen_ = 4;
            lease->iaid_ = 142;
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x77)));
            lease->preferred_lft_ = 900;   // Preferred lifetime
            lease->valid_lft_ = 8677;      // Actual lifetime
            lease->cltt_ = 168256;         // Current time of day
            lease->subnet_id_ = 23;        // Arbitrary number

        } else if (address == L1_ADDRESS) {
            lease->type_ = Lease6::LEASE_IA_TA;
            lease->prefixlen_ = 0;
            lease->iaid_ = 42;
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));
            lease->preferred_lft_ = 3600;  // Preferred lifetime
            lease->valid_lft_ = 3677;      // Actual lifetime
            lease->cltt_ = 123456;         // Current time of day
            lease->subnet_id_ = 73;        // Arbitrary number

        } else if (address == L2_ADDRESS) {
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 7;
            lease->iaid_ = 89;
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x3a)));
            lease->preferred_lft_ = 1800;  // Preferred lifetime
            lease->valid_lft_ = 5412;      // Actual lifetime
            lease->cltt_ = 234567;         // Current time of day
            lease->subnet_id_ = 73;        // Same as for L1_ADDRESS

        } else if (address == L3_ADDRESS) {
            lease->type_ = Lease6::LEASE_IA_NA;
            lease->prefixlen_ = 28;
            lease->iaid_ = 0xfffffffe;
            vector<uint8_t> duid;
            for (uint8_t i = 31; i < 126; ++i) {
                duid.push_back(i);
            }
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(duid));

            // The times used in the next tests are deliberately restricted - we
            // should be able to cope with valid lifetimes up to 0xffffffff.
            //  However, this will lead to overflows.
            // @TODO: test overflow conditions when code has been fixed
            lease->preferred_lft_ = 7200;  // Preferred lifetime
            lease->valid_lft_ = 7000;      // Actual lifetime
            lease->cltt_ = 234567;         // Current time of day
            lease->subnet_id_ = 37;        // Different from L1 and L2

        } else if (address == L4_ADDRESS) {
            // Same DUID and IAID as L1_ADDRESS
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 15;
            lease->iaid_ = 42;
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));
            lease->preferred_lft_ = 4800;  // Preferred lifetime
            lease->valid_lft_ = 7736;      // Actual lifetime
            lease->cltt_ = 222456;         // Current time of day
            lease->subnet_id_ = 75;        // Arbitrary number

        } else if (address == L5_ADDRESS) {
            // Same DUID and IAID as L1_ADDRESS
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 24;
            lease->iaid_ = 42;
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));
            lease->preferred_lft_ = 5400;  // Preferred lifetime
            lease->valid_lft_ = 7832;      // Actual lifetime
            lease->cltt_ = 227476;         // Current time of day
            lease->subnet_id_ = 175;       // Arbitrary number

        } else if (address == L6_ADDRESS) {
            // Same DUID as L1_ADDRESS
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 24;
            lease->iaid_ = 93;
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));
            lease->preferred_lft_ = 5400;  // Preferred lifetime
            lease->valid_lft_ = 1832;      // Actual lifetime
            lease->cltt_ = 627476;         // Current time of day
            lease->subnet_id_ = 112;       // Arbitrary number

        } else if (address == L7_ADDRESS) {
            // Same IAID as L1_ADDRESS
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 24;
            lease->iaid_ = 42;
            lease->duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0xe5)));
            lease->preferred_lft_ = 5600;  // Preferred lifetime
            lease->valid_lft_ = 7975;      // Actual lifetime
            lease->cltt_ = 213876;         // Current time of day
            lease->subnet_id_ = 19;        // Arbitrary number

        } else {
            // Unknown address, return an empty pointer.
            lease.reset();

        }

        return (lease);
    }

    // @brief Creates Leases for the test
    //
    // Creates all leases for the test and checks that they are different.
    //
    // @return vector<Lease6Ptr> Vector of pointers to leases
    vector<Lease6Ptr> createLeases6() {

        // Create leases
        vector<Lease6Ptr> leases;
        leases.push_back(initializeLease6(L0_ADDRESS));
        leases.push_back(initializeLease6(L1_ADDRESS));
        leases.push_back(initializeLease6(L2_ADDRESS));
        leases.push_back(initializeLease6(L3_ADDRESS));
        leases.push_back(initializeLease6(L4_ADDRESS));
        leases.push_back(initializeLease6(L5_ADDRESS));
        leases.push_back(initializeLease6(L6_ADDRESS));
        leases.push_back(initializeLease6(L7_ADDRESS));

        EXPECT_EQ(8, leases.size());

        // Check they were created
        for (int i = 0; i < leases.size(); ++i) {
            EXPECT_TRUE(leases[i]);
        }

        // Check they are different
        for (int i = 0; i < (leases.size() - 1); ++i) {
            for (int j = (i + 1); j < leases.size(); ++j) {
                EXPECT_TRUE(leases[i] != leases[j]);
            }
        }

        return (leases);
    }


    // Member variables

    LeaseMgr*   lmptr_;         // Pointer to the lease manager

    string L0_ADDRESS;          // String form of address 1
    IOAddress L0_IOADDRESS;     // IOAddress form of L1_ADDRESS

    string L1_ADDRESS;          // String form of address 1
    IOAddress L1_IOADDRESS;     // IOAddress form of L1_ADDRESS

    string L2_ADDRESS;          // String form of address 2
    IOAddress L2_IOADDRESS;     // IOAddress form of L2_ADDRESS

    string L3_ADDRESS;          // String form of address 3
    IOAddress L3_IOADDRESS;     // IOAddress form of L3_ADDRESS

    string L4_ADDRESS;          // String form of address 4
    IOAddress L4_IOADDRESS;     // IOAddress form of L4_ADDRESS

    string L5_ADDRESS;          // String form of address 5
    IOAddress L5_IOADDRESS;     // IOAddress form of L5_ADDRESS

    string L6_ADDRESS;          // String form of address 6
    IOAddress L6_IOADDRESS;     // IOAddress form of L6_ADDRESS

    string L7_ADDRESS;          // String form of address 7
    IOAddress L7_IOADDRESS;     // IOAddress form of L7_ADDRESS
};


// @brief Check that Database Can Be Opened
//
// This test checks if the MySqlLeaseMgr can be instantiated.  This happens
// only if the database can be opened.  Note that this is not part of the
// MySqlLeaseMgr test fixure set.  This test checks that the database can be
// opened: the fixtures assume that and check basic operations.

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

// @brief Check conversion functions
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


// @brief Check getName() returns correct database name
TEST_F(MySqlLeaseMgrTest, getName) {
    EXPECT_EQ(std::string("keatest"), lmptr_->getName());

    // @TODO: check for the negative
}

// @brief Check that getVersion() works
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


// @brief Check individual Lease6 methods
//
// Checks that the add/update/delete works.  All are done within one
// test so that "rollback" can be used to remove trace of the tests
// from the database.
//
// Tests where a collection of leases can be returned are in the test
// Lease6Collection.
TEST_F(MySqlLeaseMgrTest, BasicLease6) {
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

    Lease6Ptr l_returned = lmptr_->getLease6(L1_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[1], l_returned);

    l_returned = lmptr_->getLease6(L2_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[2], l_returned);

    l_returned = lmptr_->getLease6(L3_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease6(L1_IOADDRESS));
    l_returned = lmptr_->getLease6(L1_IOADDRESS);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease6(L1_IOADDRESS));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease6(L2_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[2], l_returned);
}

// @brief Check GetLease6 methods - Access by DUID/IAID
//
// Adds leases to the database and checks that they can be accessed via
// a combination of DIUID and IAID.
TEST_F(MySqlLeaseMgrTest, GetLease6Extended1) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    EXPECT_LE(6, leases.size());    // Expect to access leases 0 through 5

    // Add them to the database
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the DUID and IAID of lease[1].
    Lease6Collection returned = lmptr_->getLease6(*leases[1]->duid_,
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
    EXPECT_EQ(L1_ADDRESS, addresses[0]);
    EXPECT_EQ(L4_ADDRESS, addresses[1]);
    EXPECT_EQ(L5_ADDRESS, addresses[2]);

    // Check that nothing is returned when either the IAID or DUID match
    // nothing.
    returned = lmptr_->getLease6(*leases[1]->duid_, leases[1]->iaid_ + 1);
    EXPECT_EQ(0, returned.size());

    // Alter the leases[1] DUID to match nothing in the database.
    vector<uint8_t> duid_vector = leases[1]->duid_->getDuid();
    ++duid_vector[0];
    DUID new_duid(duid_vector);
    returned = lmptr_->getLease6(new_duid, leases[1]->iaid_);
    EXPECT_EQ(0, returned.size());
}



// @brief Check GetLease6 methods - Access by DUID/IAID/SubnetID
//
// Adds leases to the database and checks that they can be accessed via
// a combination of DIUID and IAID.
TEST_F(MySqlLeaseMgrTest, GetLease6Extended2) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    EXPECT_LE(6, leases.size());    // Expect to access leases 0 through 5

    // Add them to the database
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the DUID and IAID of lease[1].
    Lease6Ptr returned = lmptr_->getLease6(*leases[1]->duid_,
                                           leases[1]->iaid_,
                                           leases[1]->subnet_id_);
    ASSERT_TRUE(returned);
    EXPECT_TRUE(*returned == *leases[1]);

    // Modify each of the three parameters (DUID, IAID, Subnet ID) and
    // check that nothing is returned.
    returned = lmptr_->getLease6(*leases[1]->duid_, leases[1]->iaid_ + 1,
                                 leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    returned = lmptr_->getLease6(*leases[1]->duid_, leases[1]->iaid_,
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Alter the leases[1] DUID to match nothing in the database.
    vector<uint8_t> duid_vector = leases[1]->duid_->getDuid();
    ++duid_vector[0];
    DUID new_duid(duid_vector);
    returned = lmptr_->getLease6(new_duid, leases[1]->iaid_,
                                 leases[1]->subnet_id_);
    EXPECT_FALSE(returned);
}



// @brief Lease6 Update Tests
//
// Checks that we are able to update a lease in the database.
TEST_F(MySqlLeaseMgrTest, UpdateLease6) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    EXPECT_LE(3, leases.size());    // Expect to access leases 0 through 5

    // Add a lease to the database and check that the lease is there.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    lmptr_->commit();

    reopen();
    Lease6Ptr l_returned = lmptr_->getLease6(L1_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[1], l_returned);

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease6::LEASE_IA_PD;
    leases[1]->valid_lft_ *= 2;
    lmptr_->updateLease6(leases[1]);
    lmptr_->commit();
    reopen();

    // ... and check what is returned is what is expected.
    l_returned.reset();
    l_returned = lmptr_->getLease6(L1_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[1], l_returned);

    // Alter the lease again and check.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease6::LEASE_IA_TA;
    leases[1]->cltt_ += 6;
    leases[1]->prefixlen_ = 93;
    lmptr_->updateLease6(leases[1]);

    l_returned.reset();
    l_returned = lmptr_->getLease6(L1_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[1], l_returned);

    // Check we can do an update without changing data.
    lmptr_->updateLease6(leases[1]);
    l_returned.reset();
    l_returned = lmptr_->getLease6(L1_IOADDRESS);
    EXPECT_TRUE(l_returned);
    detailCompareLease6(leases[1], l_returned);

    // Try updating a lease not in the database.
    EXPECT_THROW(lmptr_->updateLease6(leases[2]), isc::dhcp::NoSuchLease);
}

}; // Of anonymous namespace
