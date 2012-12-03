// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace std;

namespace {

// This holds statements to create and destroy the schema.
#include "schema_copy.h"

// IPv4 and IPv6 addresses used in the tests
const char* ADDRESS4[] = {
    "192.0.2.0", "192.0.2.1", "192.0.2.2", "192.0.2.3",
    "192.0.2.4", "192.0.2.5", "192.0.2.6", "192.0.2.7",
    NULL
};
const char* ADDRESS6[] = {
    "2001:db8::0", "2001:db8::1", "2001:db8::2", "2001:db8::3",
    "2001:db8::4", "2001:db8::5", "2001:db8::6", "2001:db8::7",
    NULL
};

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

    // Execute creation statements.
    for (int i = 0; create_statement[i] != NULL; ++i) {
        (void) mysql_query(&handle, create_statement[i]);
    }

    // ... and close
    (void) mysql_close(&handle);
}

/// @brief Test fixture class for testing MySQL Lease Manager
///
/// Opens the database prior to each test and closes it afterwards.
/// All pending transactions are deleted prior to closure.

class MySqlLeaseMgrTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    MySqlLeaseMgrTest() {
        // Initialize address strings and IOAddresses
        for (int i = 0; ADDRESS4[i] != NULL; ++i) {
            string addr(ADDRESS4[i]);
            straddress4_.push_back(addr);
            IOAddress ioaddr(addr);
            ioaddress4_.push_back(ioaddr);
        }

        for (int i = 0; ADDRESS6[i] != NULL; ++i) {
            string addr(ADDRESS6[i]);
            straddress6_.push_back(addr);
            IOAddress ioaddr(addr);
            ioaddress6_.push_back(ioaddr);
        }

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

    /// @brief Initialize Lease4 Fields
    ///
    /// Returns a pointer to a Lease4 structure.  Different values are put into
    /// the lease according to the address passed.
    ///
    /// This is just a convenience function for the test methods.
    ///
    /// @param address Address to use for the initialization
    ///
    /// @return Lease4Ptr.  This will not point to anything if the initialization
    ///         failed (e.g. unknown address).
    Lease4Ptr initializeLease4(std::string address) {
        Lease4Ptr lease(new Lease4());

        // Set the address of the lease
        lease->addr_ = IOAddress(address);

        // Initialize unused fields.
        lease->ext_ = 0;                            // Not saved
        lease->t1_ = 0;                             // Not saved
        lease->t2_ = 0;                             // Not saved
        lease->fixed_ = false;                      // Unused
        lease->hostname_ = std::string("");         // Unused
        lease->fqdn_fwd_ = false;                   // Unused
        lease->fqdn_rev_ = false;                   // Unused
        lease->comments_ = std::string("");         // Unused

        // Set other parameters.  For historical reasons, address 0 is not used.
        if (address == straddress4_[0]) {
            lease->hwaddr_ = vector<uint8_t>(6, 0x08);
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>(8, 0x42)));
            lease->valid_lft_ = 8677;
            lease->cltt_ = 168256;
            lease->subnet_id_ = 23;

        } else if (address == straddress4_[1]) {
            lease->hwaddr_ = vector<uint8_t>(6, 0x19);
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>(8, 0x53)));
            lease->valid_lft_ = 3677;
            lease->cltt_ = 123456;
            lease->subnet_id_ = 73;

        } else if (address == straddress4_[2]) {
            lease->hwaddr_ = vector<uint8_t>(6, 0x2a);
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>(8, 0x64)));
            lease->valid_lft_ = 5412;
            lease->cltt_ = 234567;
            lease->subnet_id_ = 73;                         // Same as lease 1

        } else if (address == straddress4_[3]) {
            lease->hwaddr_ = vector<uint8_t>(6, 0x19);      // Same as lease 1
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>(8, 0x75)));

            // The times used in the next tests are deliberately restricted - we
            // should be able to cope with valid lifetimes up to 0xffffffff.
            //  However, this will lead to overflows.
            // @TODO: test overflow conditions when code has been fixed
            lease->valid_lft_ = 7000;
            lease->cltt_ = 234567;
            lease->subnet_id_ = 37;

        } else if (address == straddress4_[4]) {
            lease->hwaddr_ = vector<uint8_t>(6, 0x4c);
            // Same ClientId as straddr4_[1]
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
            lease->valid_lft_ = 7736;
            lease->cltt_ = 222456;
            lease->subnet_id_ = 85;

        } else if (address == straddress4_[5]) {
            lease->hwaddr_ = vector<uint8_t>(6, 0x19);      // Same as lease 1
            // Same ClientId and IAID as straddress4_1
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
            lease->valid_lft_ = 7832;
            lease->cltt_ = 227476;
            lease->subnet_id_ = 175;

        } else if (address == straddress4_[6]) {
            lease->hwaddr_ = vector<uint8_t>(6, 0x6e);
            // Same ClientId as straddress4_1
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
            lease->valid_lft_ = 1832;
            lease->cltt_ = 627476;
            lease->subnet_id_ = 112;

        } else if (address == straddress4_[7]) {
            lease->hwaddr_ = vector<uint8_t>();             // Empty
            lease->client_id_ = boost::shared_ptr<ClientId>(
                new ClientId(vector<uint8_t>()));           // Empty
            lease->valid_lft_ = 7975;
            lease->cltt_ = 213876;
            lease->subnet_id_ = 19;

        } else {
            // Unknown address, return an empty pointer.
            lease.reset();

        }

        return (lease);
    }

    /// @brief Initialize Lease6 Fields
    ///
    /// Returns a pointer to a Lease6 structure.  Different values are put into
    /// the lease according to the address passed.
    ///
    /// This is just a convenience function for the test methods.
    ///
    /// @param address Address to use for the initialization
    ///
    /// @return Lease6Ptr.  This will not point to anything if the initialization
    ///         failed (e.g. unknown address).
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

        // Set other parameters.  For historical reasons, address 0 is not used.
        if (address == straddress6_[0]) {
            lease->type_ = Lease6::LEASE_IA_TA;
            lease->prefixlen_ = 4;
            lease->iaid_ = 142;
            lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x77)));
            lease->preferred_lft_ = 900;
            lease->valid_lft_ = 8677;
            lease->cltt_ = 168256;
            lease->subnet_id_ = 23;

        } else if (address == straddress6_[1]) {
            lease->type_ = Lease6::LEASE_IA_TA;
            lease->prefixlen_ = 0;
            lease->iaid_ = 42;
            lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
            lease->preferred_lft_ = 3600;
            lease->valid_lft_ = 3677;
            lease->cltt_ = 123456;
            lease->subnet_id_ = 73;

        } else if (address == straddress6_[2]) {
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 7;
            lease->iaid_ = 89;
            lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x3a)));
            lease->preferred_lft_ = 1800;
            lease->valid_lft_ = 5412;
            lease->cltt_ = 234567;
            lease->subnet_id_ = 73;                     // Same as lease 1

        } else if (address == straddress6_[3]) {
            lease->type_ = Lease6::LEASE_IA_NA;
            lease->prefixlen_ = 28;
            lease->iaid_ = 0xfffffffe;
            vector<uint8_t> duid;
            for (uint8_t i = 31; i < 126; ++i) {
                duid.push_back(i);
            }
            lease->duid_ = DuidPtr(new DUID(duid));

            // The times used in the next tests are deliberately restricted - we
            // should be able to cope with valid lifetimes up to 0xffffffff.
            //  However, this will lead to overflows.
            // @TODO: test overflow conditions when code has been fixed
            lease->preferred_lft_ = 7200;
            lease->valid_lft_ = 7000;
            lease->cltt_ = 234567;
            lease->subnet_id_ = 37;

        } else if (address == straddress6_[4]) {
            // Same DUID and IAID as straddress6_1
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 15;
            lease->iaid_ = 42;
            lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
            lease->preferred_lft_ = 4800;
            lease->valid_lft_ = 7736;
            lease->cltt_ = 222456;
            lease->subnet_id_ = 671;

        } else if (address == straddress6_[5]) {
            // Same DUID and IAID as straddress6_1
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 24;
            lease->iaid_ = 42;                          // Same as lease 4
            lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
                                                        // Same as lease 4
            lease->preferred_lft_ = 5400;
            lease->valid_lft_ = 7832;
            lease->cltt_ = 227476;
            lease->subnet_id_ = 175;

        } else if (address == straddress6_[6]) {
            // Same DUID as straddress6_1
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 24;
            lease->iaid_ = 93;
            lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
                                                        // Same as lease 4
            lease->preferred_lft_ = 5400;
            lease->valid_lft_ = 1832;
            lease->cltt_ = 627476;
            lease->subnet_id_ = 112;

        } else if (address == straddress6_[7]) {
            // Same IAID as straddress6_1
            lease->type_ = Lease6::LEASE_IA_PD;
            lease->prefixlen_ = 24;
            lease->iaid_ = 42;
            lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0xe5)));
            lease->preferred_lft_ = 5600;
            lease->valid_lft_ = 7975;
            lease->cltt_ = 213876;
            lease->subnet_id_ = 19;

        } else {
            // Unknown address, return an empty pointer.
            lease.reset();

        }

        return (lease);
    }

    /// @brief Check Leases present and different
    ///
    /// Checks a vector of lease pointers and ensures that all the leases
    /// they point to are present and different.  If not, a GTest assertion
    /// will fail.
    ///
    /// @param leases Vector of pointers to leases
    template <typename T>
    void checkLeasesDifferent(const std::vector<T> leases) const {

        // Check they were created
        for (int i = 0; i < leases.size(); ++i) {
            ASSERT_TRUE(leases[i]);
        }

        // Check they are different
        for (int i = 0; i < (leases.size() - 1); ++i) {
            for (int j = (i + 1); j < leases.size(); ++j) {
                stringstream s;
                s << "Comparing leases " << i << " & " << j << " for equality";
                SCOPED_TRACE(s.str());
                EXPECT_TRUE(*leases[i] != *leases[j]);
            }
        }
    }

    /// @brief Creates leases for the test
    ///
    /// Creates all leases for the test and checks that they are different.
    ///
    /// @return vector<Lease4Ptr> Vector of pointers to leases
    vector<Lease4Ptr> createLeases4() {

        // Create leases for each address
        vector<Lease4Ptr> leases;
        for (int i = 0; i < straddress4_.size(); ++i) {
            leases.push_back(initializeLease4(straddress4_[i]));
        }
        EXPECT_EQ(8, leases.size());

        // Check all were created and that they are different.
        checkLeasesDifferent(leases);

        return (leases);
    }

    /// @brief Creates leases for the test
    ///
    /// Creates all leases for the test and checks that they are different.
    ///
    /// @return vector<Lease6Ptr> Vector of pointers to leases
    vector<Lease6Ptr> createLeases6() {

        // Create leases for each address
        vector<Lease6Ptr> leases;
        for (int i = 0; i < straddress6_.size(); ++i) {
            leases.push_back(initializeLease6(straddress6_[i]));
        }
        EXPECT_EQ(8, leases.size());

        // Check all were created and that they are different.
        checkLeasesDifferent(leases);

        return (leases);
    }


    // Member variables

    LeaseMgr*   lmptr_;             ///< Pointer to the lease manager
    vector<string>  straddress4_;   ///< String forms of IPv4 addresses
    vector<IOAddress> ioaddress4_;  ///< IOAddress forms of IPv4 addresses
    vector<string>  straddress6_;   ///< String forms of IPv6 addresses
    vector<IOAddress> ioaddress6_;  ///< IOAddress forms of IPv6 addresses
};

///@{
/// @brief Test Utilities
///
/// The follow are a set of functions used during the tests.

/// @brief Compare two Lease4 structures for equality
void
detailCompareLease(const Lease4Ptr& first, const Lease4Ptr& second) {
    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_.toText(), second->addr_.toText());
    EXPECT_TRUE(first->hwaddr_ == second->hwaddr_);
    EXPECT_TRUE(*first->client_id_ == *second->client_id_);
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
}

/// @brief Compare two Lease6 structures for equality
void
detailCompareLease(const Lease6Ptr& first, const Lease6Ptr& second) {
    EXPECT_EQ(first->type_, second->type_);

    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_.toText(), second->addr_.toText());
    EXPECT_EQ(first->prefixlen_, second->prefixlen_);
    EXPECT_EQ(first->iaid_, second->iaid_);
    EXPECT_TRUE(*first->duid_ == *second->duid_);
    EXPECT_EQ(first->preferred_lft_, second->preferred_lft_);
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
}

///@}


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

    // @TODO: check for the negative
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
/// Checks that the addLease, getLease4 (by address) and deleteLease4 works.
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
    EXPECT_TRUE(lmptr_->deleteLease4(ioaddress4_[1]));
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease4(ioaddress4_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);
}

/// @brief Basic Lease6 Checks
///
/// Checks that the addLease, getLease6 (by address) and deleteLease6 works.
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

    Lease6Ptr l_returned = lmptr_->getLease6(ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    l_returned = lmptr_->getLease6(ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease6(ioaddress6_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease6(ioaddress6_[1]));
    l_returned = lmptr_->getLease6(ioaddress6_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease6(ioaddress6_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease6(ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);
}

/// @brief Check GetLease4 methods - access by Address and SubnetID
///
/// Adds leases to the database and checks that they can be accessed via
/// a the hardware address
TEST_F(MySqlLeaseMgrTest, getLease4AddressSubnetId) {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Add just one to the database.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));

    // Look for a known lease with a valid Subnet ID
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1], 73);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Look for a lease known to be in the database with an invalid Subnet ID
    l_returned = lmptr_->getLease4(ioaddress4_[1], 74);
    EXPECT_FALSE(l_returned);

    // Look for a lease known not to be in the database with a valid Subnet ID
    l_returned = lmptr_->getLease4(ioaddress4_[2], 73);
    EXPECT_FALSE(l_returned);

    // Look for a lease known not to be in the database with and invalid
    l_returned = lmptr_->getLease4(ioaddress4_[2], 74);
    EXPECT_FALSE(l_returned);
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
    Lease4Collection returned = lmptr_->getLease4(leases[1]->hwaddr_);

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
    returned = lmptr_->getLease4(leases[2]->hwaddr_);
    EXPECT_EQ(1, returned.size());
    detailCompareLease(leases[2], *returned.begin());

    // Check that an empty vector is valid
    EXPECT_TRUE(leases[7]->hwaddr_.empty());
    returned = lmptr_->getLease4(leases[7]->hwaddr_);
    EXPECT_EQ(1, returned.size());
    detailCompareLease(leases[7], *returned.begin());

    // Try to get something with invalid hardware address
    vector<uint8_t> invalid(6, 0);
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());

    // And check that size of the vector matters
    invalid = leases[4]->hwaddr_;
    invalid.push_back(0);
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());
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
    Lease4Ptr returned = lmptr_->getLease4(leases[1]->hwaddr_,
                                           leases[1]->subnet_id_);
    ASSERT_TRUE(returned);
    detailCompareLease(leases[1], returned);

    // Try for a match to the hardware address of lease 1 and the wrong
    // subnet ID.
    returned = lmptr_->getLease4(leases[1]->hwaddr_,
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Try for a match to the subnet ID of lease 1 (and lease 4) but
    // the wrong hardware address.
    vector<uint8_t> invalid_hwaddr(15, 0x77);
    returned = lmptr_->getLease4(invalid_hwaddr,
                                 leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    // Try for a match to an unknown hardware address and an unknown
    // subnet ID.
    returned = lmptr_->getLease4(invalid_hwaddr,
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Add a second lease with the same values as the first and check that
    // an attempt to access the database by these parameters throws a
    // "multiple records" exception. (We expect there to be only one record
    // with that combination, so getting them via getLeaseX() (as opposed
    // to getLeaseXCollection() should throw an exception.)
    EXPECT_TRUE(lmptr_->deleteLease4(leases[2]->addr_));
    leases[1]->addr_ = leases[2]->addr_;
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_THROW(returned = lmptr_->getLease4(leases[1]->hwaddr_,
                                              leases[1]->subnet_id_),
                 isc::dhcp::MultipleRecords);
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
    EXPECT_EQ(1, returned.size());
    detailCompareLease(leases[3], *returned.begin());

    // Check that an empty vector is valid
    EXPECT_TRUE(leases[7]->client_id_->getClientId().empty());
    returned = lmptr_->getLease4(leases[7]->hwaddr_);
    EXPECT_EQ(1, returned.size());
    detailCompareLease(leases[7], *returned.begin());

    // Try to get something with invalid client ID
    const uint8_t invalid_data[] = {0, 0, 0};
    ClientId invalid(invalid_data, sizeof(invalid_data));
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());
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
TEST_F(MySqlLeaseMgrTest, getLease6DuidIaid) {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    ASSERT_LE(6, leases.size());    // Expect to access leases 0 through 5

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
    EXPECT_EQ(straddress6_[1], addresses[0]);
    EXPECT_EQ(straddress6_[4], addresses[1]);
    EXPECT_EQ(straddress6_[5], addresses[2]);

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

    // Try updating a lease not in the database.
    lmptr_->deleteLease4(ioaddress4_[2]);
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

    Lease6Ptr l_returned = lmptr_->getLease6(ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease6::LEASE_IA_PD;
    leases[1]->valid_lft_ *= 2;
    lmptr_->updateLease6(leases[1]);
    lmptr_->commit();

    // ... and check what is returned is what is expected.
    l_returned.reset();
    l_returned = lmptr_->getLease6(ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Alter the lease again and check.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease6::LEASE_IA_TA;
    leases[1]->cltt_ += 6;
    leases[1]->prefixlen_ = 93;
    lmptr_->updateLease6(leases[1]);

    l_returned.reset();
    l_returned = lmptr_->getLease6(ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Check we can do an update without changing data.
    lmptr_->updateLease6(leases[1]);
    l_returned.reset();
    l_returned = lmptr_->getLease6(ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Try updating a lease not in the database.
    EXPECT_THROW(lmptr_->updateLease6(leases[2]), isc::dhcp::NoSuchLease);
}

}; // Of anonymous namespace
