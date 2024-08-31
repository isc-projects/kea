// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_LEASE_MGR_UNITTEST_H
#define GENERIC_LEASE_MGR_UNITTEST_H

#include <asiolink/io_service.h>
#include <database/database_connection.h>
#include <dhcpsrv/tracking_lease_mgr.h>
#include <dhcpsrv/timer_mgr.h>

#include <gtest/gtest.h>

#include <boost/make_shared.hpp>
#include <vector>
#include <set>

namespace isc {
namespace dhcp {
namespace test {

/// @brief typedefs to simplify lease statistic testing
struct SubnetPoolVal {
    int64_t value_;
    bool check_pool_;
    SubnetPoolVal() : value_(0), check_pool_(true) {
    };
    SubnetPoolVal(int64_t value) : value_(value), check_pool_(true) {
    };
    SubnetPoolVal(int64_t value, bool check) : value_(value), check_pool_(check) {
    };
};
typedef std::map<std::string, SubnetPoolVal> StatValMap;
typedef std::pair<std::string, SubnetPoolVal> StatValPair;
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

    /// @brief A structure holding a single callback log entry.
    ///
    /// The @c logCallback function inserts logs of this type into the
    /// @c logs vector. The vector can be later examined to see what
    /// callbacks have been invoked.
    typedef struct {
        TrackingLeaseMgr::CallbackType type;
        SubnetID subnet_id;
        LeasePtr lease;
        bool locked;
    } Log;

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
    ///         initialization failed (e.g. unknown address).
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
    /// @param user_context - the lease's user context
    ///
    /// @return pointer to created Lease4
    Lease4Ptr makeLease4(const std::string& address,
                         const SubnetID& subnet_id,
                         const uint32_t state = Lease::STATE_DEFAULT,
                         const data::ConstElementPtr user_context = data::ConstElementPtr());

    /// @brief Constructs a minimal IPv6 lease and adds it to the lease storage
    ///
    /// The DUID is constructed from the address and prefix length.
    ///
    /// @param type - type of lease to create (TYPE_NA, TYPE_PD...)
    /// @param address - IPv6 address/prefix for the lease
    /// @param prefix_len = length of the prefix (should be 0 for TYPE_NA)
    /// @param subnet_id - subnet ID to which the lease belongs
    /// @param state - the state of the lease
    /// @param user_context - the lease's user context
    ///
    /// @return pointer to created Lease6
    Lease6Ptr makeLease6(const Lease::Type& type,
                         const std::string& address,
                         uint8_t prefix_len,
                         const SubnetID& subnet_id,
                         const uint32_t state = Lease::STATE_DEFAULT,
                         const data::ConstElementPtr user_context = data::ConstElementPtr());

    /// @brief Callback function recording its parameters.
    ///
    /// It is used in the unit tests that verify that appropriate callbacks
    /// have been invoked.
    ///
    /// @param type callback type.
    /// @param subnet_id subnet identifier.
    /// @param lease lease instance.
    void logCallback(TrackingLeaseMgr::CallbackType type, SubnetID subnet_id,
                     LeasePtr lease);

    /// @brief Counts log entries.
    ///
    /// It counts the logs associated with the specific callback type, subnet id
    /// and lease type.
    ///
    /// @param type callback type.
    /// @param subnet_id subnet identifier.
    /// @return The number of callback logs associated with the specific type and
    /// the subnet id.
    int countLogs(TrackingLeaseMgr::CallbackType type, SubnetID subnet_id,
                  Lease::Type lease_type) const;

    /// @brief checks that addLease, getLease4(addr) and deleteLease() works
    void testBasicLease4();

    /// @brief checks that invalid dates are safely handled.
    void testMaxDate4();

    /// @brief checks that infinite lifetimes do not overflow.
    void testInfiniteLifeTime4();

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

    /// @brief Test method which returns all IPv4 leases for Hostname.
    void testGetLeases4Hostname();

    /// @brief Test method which returns all IPv4 leases.
    void testGetLeases4();

    /// @brief Test method which returns range of IPv4 leases with paging.
    void testGetLeases4Paged();

    /// @brief Test method which returns all IPv6 leases for Subnet ID.
    void testGetLeases6SubnetId();

    /// @brief Test method which returns all IPv6 leases for Subnet ID
    /// with paging.
    void testGetLeases6SubnetIdPaged();

    /// @brief Test method which returns all IPv6 leases for Hostname.
    void testGetLeases6Hostname();

    /// @brief Test making/fetching leases with IAIDs > signed 32-bit max.
    void testLease6LargeIaidCheck();

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

    /// @brief checks that infinite lifetimes do not overflow.
    void testInfiniteLifeTime6();

    /// @brief Checks that Lease6 can be stored with and without a hardware address.
    void testLease6MAC();

    /// @brief Checks that Lease6 stores hardware type and hardware source.
    void testLease6HWTypeAndSource();

    /// @brief Test that IPv6 lease can be added, retrieved and deleted.
    void testAddGetDelete6();

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
    /// retrieval of non existent DUID.
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

    /// @brief Lease4 concurrent update test
    ///
    /// Checks that the code is not able to concurrently update an IPv4 lease in
    /// the database.
    void testConcurrentUpdateLease4();

    /// @brief Lease6 update test
    ///
    /// Checks that the code is able to update an IPv6 lease in the database.
    void testUpdateLease6();

    /// @brief Lease6 concurrent update test
    ///
    /// Checks that the code is not able to concurrently update an IPv6 lease in
    /// the database.
    void testConcurrentUpdateLease6();

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

    /// @brief Checks that DHCPv4 leases with infinite valid lifetime
    /// will never expire.
    void testInfiniteAreNotExpired4();

    /// @brief Checks that DHCPv6 leases with infinite valid lifetime
    /// will never expire.
    void testInfiniteAreNotExpired6();

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
    /// It creates three subnets with leases in various states in
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
    /// It creates three subnets with leases in various states in
    /// each.  It runs and verifies the returned query contents for
    /// each of the v6 startLeaseQuery variants:
    ///
    /// - startSubnetLeaseQuery()
    /// - startSubneRangetLeaseQuery()
    /// - startLeaseQuery()
    ///
    void testLeaseStatsQuery6();

    /// @brief Checks if v4 LeaseStatsQuery can get bad attribution.
    ///
    /// It creates two subnets with leases and move one from the first
    /// to the second. If counters are not updated this can lead to
    /// bad attribution i.e. a lease is counted in a subnet when it
    /// belongs to another one.
    ///
    void testLeaseStatsQueryAttribution4();

    /// @brief Checks if v6 LeaseStatsQuery can get bad attribution.
    ///
    /// It creates two subnets with leases and move one from the first
    /// to the second. If counters are not updated this can lead to
    /// bad attribution i.e. a lease is counted in a subnet when it
    /// belongs to another one.
    ///
    /// @note We can check the lease type change too but in the real
    /// world this never happens.
    void testLeaseStatsQueryAttribution6();

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

    /// @brief Create a user-context with a given list of classes
    ///
    /// Creates an Element::map with the following content:
    ///
    /// {
    ///     "ISC": {
    ///         "classes": [ "class0", "class1", ... ]
    ///     }
    /// }
    ///
    /// @param classes list of classes to include in the context
    /// @return ElementPtr containing the user-context
    data::ElementPtr makeContextWithClasses(const std::list<ClientClass>& classes);

    /// @brief Tests class lease counts when adding, updating, and deleting
    /// leases with class lists.
    void testClassLeaseCount4();

    /// @brief Tests class lease counts when adding, updating, and deleting
    /// leases with class lists.
    ///
    /// @param ltype type of lease, either Lease::TYPE_NA or Lease::TYPE_PD
    void testClassLeaseCount6(Lease::Type ltype);

    /// @brief Checks a few v4 lease limit checking scenarios.
    void testLeaseLimits4();

    /// @brief Checks a few v6 lease limit checking scenarios.
    void testLeaseLimits6();

    /// @brief Checks if the backends call the callbacks when an
    /// IPv4 lease is added.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackAddLease4(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv6 address lease is added.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackAddLeaseNA(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv6 prefix lease is added.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackAddLeasePD(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv4 lease is updated.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackUpdateLease4(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv6 address lease is updated.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackUpdateLeaseNA(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv6 prefix lease is updated.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackUpdateLeasePD(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv4 lease is deleted.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackDeleteLease4(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv6 address lease is deleted.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackDeleteLeaseNA(bool expect_locked);

    /// @brief Checks if the backends call the callbacks when an
    /// IPv6 prefix lease is deleted.
    ///
    /// @param expect_locked a boolean flag indicating if the test should
    /// expect that the lease is locked before the callback.
    void testTrackDeleteLeasePD(bool expect_locked);

    /// @brief Checks that the lease manager can be recreated and its
    /// registered callbacks preserved, if desired.
    ///
    /// @param access database connection string used for recreating the
    /// lease manager.
    void testRecreateWithCallbacks(const std::string& access);

    /// @brief Checks that the lease manager can be recreated without the
    /// previously registered callbacks.
    ///
    /// @param access database connection string used for recreating the
    /// lease manager.
    void testRecreateWithoutCallbacks(const std::string& access);

    /// @brief Checks that statistic with big integer values are handled correctly.
    void testBigStats();

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

    /// Recorded callback logs.
    std::vector<Log> logs_;

    /// @brief Pointer to the lease manager
    TrackingLeaseMgr* lmptr_;
};

class LeaseMgrDbLostCallbackTest : public ::testing::Test {
public:
    LeaseMgrDbLostCallbackTest()
        : db_lost_callback_called_(0), db_recovered_callback_called_(0),
          db_failed_callback_called_(0),
          io_service_(boost::make_shared<isc::asiolink::IOService>()) {
        db::DatabaseConnection::db_lost_callback_ = 0;
        db::DatabaseConnection::db_recovered_callback_ = 0;
        db::DatabaseConnection::db_failed_callback_ = 0;
        db::DatabaseConnection::setIOService(io_service_);
        TimerMgr::instance()->setIOService(io_service_);
    }

    virtual ~LeaseMgrDbLostCallbackTest() {
        db::DatabaseConnection::db_lost_callback_ = 0;
        db::DatabaseConnection::db_recovered_callback_ = 0;
        db::DatabaseConnection::db_failed_callback_ = 0;
        db::DatabaseConnection::setIOService(isc::asiolink::IOServicePtr());
        TimerMgr::instance()->unregisterTimers();
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

    /// @brief Abstract method for destroying the back end specific schema
    virtual void destroySchema() = 0;

    /// @brief Abstract method for creating the back end specific schema
    virtual void createSchema() = 0;

    /// @brief Abstract method which returns the back end specific connection
    /// string
    virtual std::string validConnectString() = 0;

    /// @brief Abstract method which returns invalid back end specific connection
    /// string
    virtual std::string invalidConnectString() = 0;

    /// @brief Verifies the lease manager's behavior if DB connection can not be
    /// established but succeeds on retry
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// verifies that connectivity is unavailable and then recovered on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked
    void testRetryOpenDbLostAndRecoveredCallback();

    /// @brief Verifies the lease manager's behavior if DB connection can not be
    /// established but fails on retry
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// It verifies that connectivity is unavailable and then fails again on
    /// retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked
    void testRetryOpenDbLostAndFailedCallback();

    /// @brief Verifies the lease manager's behavior if DB connection can not be
    /// established but succeeds on retry
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// verifies that connectivity is unavailable and then recovered on retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    void testRetryOpenDbLostAndRecoveredAfterTimeoutCallback();

    /// @brief Verifies the lease manager's behavior if DB connection can not be
    /// established but fails on retry
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// It verifies that connectivity is unavailable and then fails again on
    /// retry:
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    void testRetryOpenDbLostAndFailedAfterTimeoutCallback();

    /// @brief Verifies open failures do NOT invoke db lost callback
    ///
    /// The db lost callback should only be invoked after successfully
    /// opening the DB and then subsequently losing it. Failing to
    /// open should be handled directly by the application layer.
    void testNoCallbackOnOpenFailure();

    /// @brief Verifies the lease manager's behavior if DB connection is lost
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// verifies connectivity by issuing a known valid query. Next it simulates
    /// connectivity lost by identifying and closing the socket connection to
    /// the CB backend. It then reissues the query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked
    void testDbLostAndRecoveredCallback();

    /// @brief Verifies the lease manager's behavior if DB connection is lost
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// verifies connectivity by issuing a known valid query. Next it simulates
    /// connectivity lost by identifying and closing the socket connection to
    /// the CB backend. It then reissues the query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked
    void testDbLostAndFailedCallback();

    /// @brief Verifies the lease manager's behavior if DB connection is lost
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// verifies connectivity by issuing a known valid query. Next it simulates
    /// connectivity lost by identifying and closing the socket connection to
    /// the CB backend. It then reissues the query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbRecoveredCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    void testDbLostAndRecoveredAfterTimeoutCallback();

    /// @brief Verifies the lease manager's behavior if DB connection is lost
    ///
    /// This function creates a lease manager with a back end that supports
    /// connectivity lost callback (currently only MySQL and PostgreSQL). It
    /// verifies connectivity by issuing a known valid query. Next it simulates
    /// connectivity lost by identifying and closing the socket connection to
    /// the CB backend. It then reissues the query and verifies that:
    /// -# The Query throws DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    /// -# The registered DbFailedCallback was invoked after two reconnect
    /// attempts (once failing and second triggered by timer)
    void testDbLostAndFailedAfterTimeoutCallback();

    /// @brief Callback function registered with the lease manager
    bool db_lost_callback(util::ReconnectCtlPtr /* not_used */) {
        return (++db_lost_callback_called_);
    }

    /// @brief Flag used to detect calls to db_lost_callback function
    uint32_t db_lost_callback_called_;

    /// @brief Callback function registered with the lease manager
    bool db_recovered_callback(util::ReconnectCtlPtr /* not_used */) {
        return (++db_recovered_callback_called_);
    }

    /// @brief Flag used to detect calls to db_recovered_callback function
    uint32_t db_recovered_callback_called_;

    /// @brief Callback function registered with the lease manager
    bool db_failed_callback(util::ReconnectCtlPtr /* not_used */) {
        return (++db_failed_callback_called_);
    }

    /// @brief Flag used to detect calls to db_failed_callback function
    uint32_t db_failed_callback_called_;

    /// The IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr io_service_;
};

}  // namespace test
}  // namespace dhcp
}  // namespace isc

#endif
