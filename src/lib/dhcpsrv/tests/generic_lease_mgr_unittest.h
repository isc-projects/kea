// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef GENERIC_LEASE_MGR_UNITTEST_H
#define GENERIC_LEASE_MGR_UNITTEST_H

#include <dhcpsrv/lease_mgr.h>
#include <gtest/gtest.h>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test Fixture class with utility functions for LeaseMgr backends
///
/// It contains utility functions, like dummy lease creation.
/// All concrete LeaseMgr test classes should be derived from it.
class GenericLeaseMgrTest : public ::testing::Test {
public:

    /// @brief Universe (V4 or V6).
    enum Universe {
        V4,
        V6
    };

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
    /// @return Lease6Ptr.  This will not point to anything if the initialization
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

    // @brief Get lease4 by hardware address (2)
    //
    // Check that the system can cope with getting a hardware address of
    // any size.
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

    /// @brief Check that the DHCPv6 lease can be added, removed and recreated.
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
    /// - all expired and not reclaimed leases are retured
    /// - number of leases returned can be limited
    /// - leases are returned in the order from the most expired to the
    ///   least expired
    /// - reclaimed leases are not returned.
    void testGetExpiredLeases4();

    /// @brief Checks that the expired DHCPv6 leases can be retrieved.
    ///
    /// This test checks the following:
    /// - all expired and not reclaimed leases are retured
    /// - number of leases returned can be limited
    /// - leases are returned in the order from the most expired to the
    ///   least expired
    /// - reclaimed leases are not returned.
    void testGetExpiredLeases6();

    /// @brief Checks that declined DHCPv4 leases that have expired can be retrieved.
    ///
    /// This test checks that the following:
    /// - all expired and not reclaimed leases are returned, regardless if
    ///   they're normal or declined
    /// - the order in which they're updated in LeaseMgr doesn't matter
    /// - leases are returned in the order from most expired to the least
    ///   expired
    void testGetDeclinedLeases4();

    /// @brief Checks that declined DHCPv6 leases that have expired can be retrieved.
    ///
    /// This test checks that the following:
    /// - all expired and not reclaimed leases are returned, regardless if
    ///   they're normal or declined
    /// - the order in which they're updated in LeaseMgr doesn't matter
    /// - leases are returned in the order from most expired to the least
    ///   expired
    void testGetDeclinedLeases6();

    /// @brief Checks that selected expired-reclaimed DHCPv6 leases
    /// are removed.
    ///
    /// This creates a number of DHCPv6 leases and marks some of them
    /// as expired-reclaimed. It later verifies that the expired-reclaimed
    /// leases can be removed.
    void testDeleteExpiredReclaimedLeases6();

    /// @brief Checks that selected expired-reclaimed DHCPv4 leases
    /// are removed.
    ///
    /// This creates a number of DHCPv4 leases and marks some of them
    /// as expired-reclaimed. It later verifies that the expired-reclaimed
    /// leases can be removed.
    void testDeleteExpiredReclaimedLeases4();

    /// @brief String forms of IPv4 addresses
    std::vector<std::string>  straddress4_;

    /// @brief IOAddress forms of IPv4 addresses
    std::vector<isc::asiolink::IOAddress> ioaddress4_;

    /// @brief String forms of IPv6 addresses
    std::vector<std::string>  straddress6_;

    /// @brief Types of IPv6 Leases
    std::vector<Lease::Type> leasetype6_;

    /// @brief IOAddress forms of IPv6 addresses
    std::vector<isc::asiolink::IOAddress> ioaddress6_;

    /// @brief Pointer to the lease manager
    LeaseMgr* lmptr_;
};

}; // namespace test
}; // namespace dhcp
}; // namespace isc

#endif
