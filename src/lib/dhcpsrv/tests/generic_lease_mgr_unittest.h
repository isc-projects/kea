// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_LEASE_MGR_UNITTEST_H
#define GENERIC_LEASE_MGR_UNITTEST_H

#include <dhcpsrv/lease_mgr.h>
#include <gtest/gtest.h>
#include <vector>
#include <set>

namespace isc {
namespace dhcp {
namespace test {

/// @brief typedefs to simplify lease statistic testing
typedef std::map<std::string, int64_t> StatValMap;
typedef std::pair<std::string, int64_t> StatValPair;
typedef std::vector<StatValMap> StatValMapList;
typedef std::set<LeaseStatsRow> RowSet;

/// @brief Test Fixture class with utility functions for LeaseMgr backends
///
/// It contains utility functions, like dummy lease creation.
/// All concrete LeaseMgr test classes should be derived from it.
class GenericLeaseMgrTest : public ::testing::Test {
public:
    /// @brief Universe (V4 or V6).
    enum Universe { V4, V6 };

    /// @brief Default constructor.
    GenericLeaseMgrTest();

    /// @brief Virtual destructor.
    virtual ~GenericLeaseMgrTest();

    /// @brief Reopen the database
    ///
    /// Closes the database and re-opens it. It must be implemented
    /// in derived classes.
    ///
    /// @param u Universe (V4 or V6), required by some backends.
    virtual void reopen(Universe u = V4) = 0;

    /// @brief Initialize Lease4 Fields
    ///
    /// Returns a pointer to a Lease4 structure.  Different values are put into
    /// the lease according to the address passed.
    ///
    /// This is just a convenience function for the test methods.
    ///
    /// @param address Address to use for the initialization
    ///
    /// @return Lease4Ptr.  This will not point to anything if the
    ///         initialization failed (e.g. unknown address).
    Lease4Ptr initializeLease4(std::string address);

    /// @brief Initialize Lease6 Fields
    ///
    /// Returns a pointer to a Lease6 structure.  Different values are put into
    /// the lease according to the address passed.
    ///
    /// This is just a convenience function for the test methods.
    ///
    /// @param address Address to use for the initialization
    ///
    /// @return Lease6Ptr.  This will not point to anything if the
    /// initialization
    ///         failed (e.g. unknown address).
    Lease6Ptr initializeLease6(std::string address);

    /// @brief Check Leases present and different
    ///
    /// Checks a vector of lease pointers and ensures that all the leases
    /// they point to are present and different.  If not, a GTest assertion
    /// will fail.
    ///
    /// @param leases Vector of pointers to leases
    /// @tparam Type of the leases held in the vector: @c Lease4 or
    /// @c Lease6.
    template <typename T>
    void checkLeasesDifferent(const std::vector<T>& leases) const;

    /// @brief Creates leases for the test
    ///
    /// Creates all leases for the test and checks that they are different.
    ///
    /// @return vector<Lease4Ptr> Vector of pointers to leases
    std::vector<Lease4Ptr> createLeases4();

    /// @brief Creates leases for the test
    ///
    /// Creates all leases for the test and checks that they are different.
    ///
    /// @return vector<Lease6Ptr> Vector of pointers to leases
    std::vector<Lease6Ptr> createLeases6();

    /// @brief Compares a StatsMgr statistic to an expected value
    ///
    /// Attempt to fetch the named statistic from the StatsMg and if
    /// found, compare its observed value to the given value.
    /// Fails if the stat is not found or if the values do not match.
    ///
    /// @param name StatsMgr name for the statistic to check
    /// @param expected_value expected value of the statistic
    void checkStat(const std::string& name, const int64_t expected_value);

    /// @brief Compares StatsMgr statistics against an expected list of values
    ///
    /// Iterates over a list of statistic names and expected values, attempting
    /// to fetch each from the StatsMgr and if found, compare its observed value
    /// to the expected value.  Fails if any of the expected stats are not
    /// found or if the values do not match.
    ///
    /// @param expected_stats Map of expected static names and values.
    void checkLeaseStats(const StatValMapList& expected_stats);

    /// @brief Constructs a minimal IPv4 lease and adds it to the lease storage
    ///
    /// @param address - IPv4 address for the lease
    /// @param subnet_id - subnet ID to which the lease belongs
    /// @param state - the state of the lease
    void makeLease4(const std::string& address, const SubnetID& subnet_id,
                    const uint32_t state = Lease::STATE_DEFAULT);

    /// @brief Constructs a minimal IPv6 lease and adds it to the lease storage
    ///
    /// The DUID is constructed from the address and prefix length.
    ///
    /// @param type - type of lease to create (TYPE_NA, TYPE_PD...)
    /// @param address - IPv6 address/prefix for the lease
    /// @param prefix_len = length of the prefix (should be 0 for TYPE_NA)
    /// @param subnet_id - subnet ID to which the lease belongs
    /// @param state - the state of the lease
    void makeLease6(const Lease::Type& type, const std::string& address,
                    uint8_t prefix_len, const SubnetID& subnet_id,
                    const uint32_t state = Lease::STATE_DEFAULT);

    /// @brief checks that addLease, getLease4(addr) and deleteLease() works
    void testBasicLease4();

    /// @brief checks that invalid dates are safely handled.
    void testMaxDate4();

    /// @brief Test lease retrieval using client id.
    void testGetLease4ClientId();

    /// @brief Test lease retrieval when leases with NULL client id are present.
    void testGetLease4NullClientId();

    /// @brief Test lease retrieval using HW address.
    void testGetLease4HWAddr1();

    /// @brief Check GetLease4 methods - access by Hardware Address
    ///
    /// Adds leases to the database and checks that they can be accessed using
    /// HWAddr information.
    void testGetLease4HWAddr2();

    /// @brief Test lease retrieval using client id, HW address and subnet id.
    void testGetLease4ClientIdHWAddrSubnetId();

    /// @brief Get lease4 by hardware address (2)
    ///
    /// Check that the system can cope with getting a hardware address of
    /// any size.
    void testGetLease4HWAddrSize();

    /// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
    ///
    /// Adds leases to the database and checks that they can be accessed via
    /// a combination of hardware address and subnet ID
    void testGetLease4HWAddrSubnetId();

    /// @brief Get lease4 by hardware address and subnet ID (2)
    ///
    /// Check that the system can cope with getting a hardware address of
    /// any size.
    void testGetLease4HWAddrSubnetIdSize();

    /// @brief Check GetLease4 methods - access by Client ID
    ///
    /// Adds leases to the database and checks that they can be accessed via
    /// the Client ID.
    void testGetLease4ClientId2();

    /// @brief Get Lease4 by client ID (2)
    ///
    /// Check that the system can cope with a client ID of any size.
    void testGetLease4ClientIdSize();

    /// @brief Check GetLease4 methods - access by Client ID & Subnet ID
    ///
    /// Adds leases to the database and checks that they can be accessed via
    /// a combination of client and subnet IDs.
    void testGetLease4ClientIdSubnetId();

    /// @brief Test method which returns all IPv4 leases for Subnet ID.
    void testGetLeases4SubnetId();

    /// @brief Test method which returns all IPv4 leases.
    void testGetLeases4();

    /// @brief Test method which returns range of IPv4 leases with paging.
    void testGetLeases4Paged();

    /// @brief Test method which returns all IPv6 leases for Subnet ID.
    void testGetLeases6SubnetId();

    /// @brief Test method which returns all IPv6 leases.
    void testGetLeases6();

    /// @brief Test method which returns range of IPv6 leases with paging.
    void testGetLeases6Paged();

    /// @brief Basic Lease4 Checks
    ///
    /// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
    /// updateLease4() and deleteLease (IPv4 address) can handle NULL client-id.
    /// (client-id is optional and may not be present)
    ///
    /// @todo: check if it does overlap with @ref testGetLease4NullClientId()
    void testLease4NullClientId();

    /// @brief Check that the DHCPv4 lease can be added, removed and recreated.
    ///
    /// This test creates a lease, removes it and then recreates it with some
    /// of the attributes changed. Next it verifies that the lease in the
    /// persistent storage has been updated as expected.
    void testRecreateLease4();

    /// @brief Basic Lease6 Checks
    ///
    /// Checks that the addLease, getLease6 (by address) and deleteLease (with an
    /// IPv6 address) works.
    void testBasicLease6();

    /// @brief Checks that invalid dates are safely handled.
    void testMaxDate6();

    /// @brief Checks that Lease6 can be stored with and without a hardware address.
    void testLease6MAC();

    /// @brief Checks that Lease6 stores hardware type and hardware source.
    void testLease6HWTypeAndSource();

    /// @brief Test that IPv6 lease can be added, retrieved and deleted.
    ///
    /// This method checks basic IPv6 lease operations. There's check_t1_t2
    /// parameter that controls whether the backend supports storing T1, T2
    /// parameters. memfile supports it, while MySQL doesn't. If T1,T2
    /// storage is not supported, the expected values are 0.
    ///
    /// @param check_t1_t2 controls whether T1,T2 timers should be checked
    void testAddGetDelete6(bool check_t1_t2);

    /// @brief Check GetLease6 methods - access by DUID/IAID
    ///
    /// Adds leases to the database and checks that they can be accessed via
    /// a combination of DUID and IAID.
    void testGetLeases6DuidIaid();

    /// @brief Check that the system can cope with a DUID of allowed size.
    void testGetLeases6DuidSize();

    /// @brief Check that getLease6 methods discriminate by lease type.
    ///
    /// Adds six leases, two per lease type all with the same duid and iad but
    /// with alternating subnet_ids.
    /// It then verifies that all of getLeases6() method variants correctly
    /// discriminate between the leases based on lease type alone.
    void testLease6LeaseTypeCheck();

    /// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
    ///
    /// Adds leases to the database and checks that they can be accessed via
    /// a combination of DIUID and IAID.
    void testGetLease6DuidIaidSubnetId();
    
    /// @brief verifies getLeases6 method by DUID
    ///
    /// Adds 3 leases to backend and retrieves, verifes empty
    /// retrival of non existent DUID.
    void testGetLeases6Duid();

    /// @brief Checks that getLease6() works with different DUID sizes
    void testGetLease6DuidIaidSubnetIdSize();

    /// @brief Verify that too long hostname for Lease4 is not accepted.
    ///
    /// Checks that the it is not possible to create a lease when the hostname
    /// length exceeds 255 characters.
    void testLease4InvalidHostname();

    /// @brief Verify that too long hostname for Lease6 is not accepted.
    ///
    /// Checks that the it is not possible to create a lease when the hostname
    /// length exceeds 255 characters.
    void testLease6InvalidHostname();

    /// @brief Lease4 update test
    ///
    /// Checks that the code is able to update an IPv4 lease in the database.
    void testUpdateLease4();

    /// @brief Lease6 update test
    ///
    /// Checks that the code is able to update an IPv6 lease in the database.
    void testUpdateLease6();

    /// @brief Check that the IPv6 lease can be added, removed and recreated.
    ///
    /// This test creates a lease, removes it and then recreates it with some
    /// of the attributes changed. Next it verifies that the lease in the
    /// persistent storage has been updated as expected.
    void testRecreateLease6();

    /// @brief Verifies that a null DUID is not allowed.
    void testNullDuid();

    /// @brief Verifies that the backend reports expected version numbers.
    /// @param major Expected major version to be reported.
    /// @param minor Expected minor version to be reported.
    void testVersion(int major, int minor);

    /// @brief Checks that the expired DHCPv4 leases can be retrieved.
    ///
    /// This test checks the following:
    /// - all expired and not reclaimed leases are returned
    /// - number of leases returned can be limited
    /// - leases are returned in the order from the most expired to the
    ///   least expired
    /// - reclaimed leases are not returned.
    void testGetExpiredLeases4();

    /// @brief Checks that the expired IPv6 leases can be retrieved.
    ///
    /// This test checks the following:
    /// - all expired and not reclaimed leases are returned
    /// - number of leases returned can be limited
    /// - leases are returned in the order from the most expired to the
    ///   least expired
    /// - reclaimed leases are not returned.
    void testGetExpiredLeases6();

    /// @brief Checks that declined IPv4 leases that have expired can be retrieved.
    ///
    /// This test checks that the following:
    /// - all expired and not reclaimed leases are returned, regardless if
    ///   they're normal or declined
    /// - the order in which they're updated in LeaseMgr doesn't matter
    /// - leases are returned in the order from most expired to the least
    ///   expired
    void testGetDeclinedLeases4();

    /// @brief Checks that declined IPv6 leases that have expired can be retrieved.
    ///
    /// This test checks that the following:
    /// - all expired and not reclaimed leases are returned, regardless if
    ///   they're normal or declined
    /// - the order in which they're updated in LeaseMgr doesn't matter
    /// - leases are returned in the order from most expired to the least
    ///   expired
    void testGetDeclinedLeases6();

    /// @brief Checks that selected expired-reclaimed IPv6 leases
    /// are removed.
    ///
    /// This creates a number of DHCPv6 leases and marks some of them
    /// as expired-reclaimed. It later verifies that the expired-reclaimed
    /// leases can be removed.
    void testDeleteExpiredReclaimedLeases6();

    /// @brief Checks that selected expired-reclaimed IPv4 leases
    /// are removed.
    ///
    /// This creates a number of DHCPv4 leases and marks some of them
    /// as expired-reclaimed. It later verifies that the expired-reclaimed
    /// leases can be removed.
    void testDeleteExpiredReclaimedLeases4();

    /// @brief Check that the IPv4 lease statistics can be recounted
    ///
    /// This test creates two subnets and several leases associated with
    /// them, then verifies that lease statistics are recalculated correctly
    /// after altering the lease states in various ways.
    void testRecountLeaseStats4();

    /// @brief Check that the IPv6 lease statistics can be recounted
    ///
    /// This test creates two subnets and several leases associated with
    /// them, then verifies that lease statistics are recalculated correctly
    /// after altering the lease states in various ways.
    void testRecountLeaseStats6();


    /// @brief Check if wipeLeases4 works properly.
    ///
    /// This test creates a bunch of leases in several subnets and then
    /// attempts to delete them, one subnet at a time.
    void testWipeLeases4();

    /// @brief Check if wipeLeases6 works properly.
    ///
    /// This test creates a bunch of leases in several subnets and then
    /// attempts to delete them, one subnet at a time.
    void testWipeLeases6();

    /// @brief Checks operation of v4 LeaseStatsQuery variants
    ///
    /// It creates three subnets with leasese in various states in
    /// each.  It runs and verifies the returned query contents for
    /// each of the v4 startLeaseQuery variants:
    ///
    /// - startSubnetLeaseQuery()
    /// - startSubneRangetLeaseQuery()
    /// - startLeaseQuery()
    ///
    void testLeaseStatsQuery4();

    /// @brief Checks operation of v6 LeaseStatsQuery variants
    ///
    /// It creates three subnets with leasese in various states in
    /// each.  It runs and verifies the returned query contents for
    /// each of the v6 startLeaseQuery variants:
    ///
    /// - startSubnetLeaseQuery()
    /// - startSubneRangetLeaseQuery()
    /// - startLeaseQuery()
    ///
    void testLeaseStatsQuery6();

    /// @brief Compares LeaseQueryStats content to expected set of rows
    ///
    /// @param qry - a started LeaseStatsQuery
    /// @param row_set - set of rows expected to be found in the query rows
    void checkQueryAgainstRowSet(const LeaseStatsQueryPtr& qry, const RowSet& row_set);

    /// @brief Checks if specified range of leases was returned.
    ///
    /// @param returned collection of leases returned.
    /// @param expected_addresses ordered collection of expected addresses.
    void checkLeaseRange(const Lease4Collection& returned,
                         const std::vector<std::string>& expected_addresses);

    /// @brief String forms of IPv4 addresses
    std::vector<std::string> straddress4_;

    /// @brief IOAddress forms of IPv4 addresses
    std::vector<isc::asiolink::IOAddress> ioaddress4_;

    /// @brief String forms of IPv6 addresses
    std::vector<std::string> straddress6_;

    /// @brief Types of IPv6 Leases
    std::vector<Lease::Type> leasetype6_;

    /// @brief IOAddress forms of IPv6 addresses
    std::vector<isc::asiolink::IOAddress> ioaddress6_;

    /// @brief Pointer to the lease manager
    LeaseMgr* lmptr_;
};

class LeaseMgrDbLostCallbackTest : public ::testing::Test {
public:
    LeaseMgrDbLostCallbackTest() {
        db::DatabaseConnection::db_lost_callback = 0;
    }

    virtual ~LeaseMgrDbLostCallbackTest() {
        db::DatabaseConnection::db_lost_callback = 0;
    }

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and wipe out any residual lease manager
    virtual void SetUp();

    /// @brief Pre-text exit clean up
    ///
    /// Invoked by gtest upon test exit, we destroy the schema
    /// we created and toss our lease manager.
    virtual void TearDown();

    /// @brief Abstract method for destroying the back end specific shcema
    virtual void destroySchema() = 0;

    /// @brief Abstract method for creating the back end specific shcema
    virtual void createSchema() = 0;

    /// @brief Abstract method which returns the back end specific connection
    /// string
    virtual std::string validConnectString() = 0;

    /// @brief Abstract method which returns invalid back end specific connection
    /// string
    virtual std::string invalidConnectString() = 0;

    /// @brief Verifies open failures do NOT invoke db lost callback
    ///
    /// The db lost callback should only be invoked after successfully
    /// opening the DB and then subsequently losing it. Failing to
    /// open should be handled directly by the application layer.
    void testNoCallbackOnOpenFailure();

    /// @brief Verifies the host manager's behavior if DB connection is lost
    ///
    /// This function creates a lease manager with an back end that
    /// supports connectivity lost callback (currently only MySQL and
    /// PostgreSQL currently).  It verifies connectivity by issuing a known
    /// valid query.  Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the host backend.  It then reissues
    /// the query and verifies that:
    /// -# The Query throws  DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    void testDbLostCallback();

    /// @brief Callback function registered with the host manager
    bool db_lost_callback(db::ReconnectCtlPtr /* not_used */) {
        return (callback_called_ = true);
    }

    /// @brief Flag used to detect calls to db_lost_callback function
    bool callback_called_;

};

}  // namespace test
}  // namespace dhcp
}  // namespace isc

#endif
