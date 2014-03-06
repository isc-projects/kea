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

#ifndef LIBDHCPSRV_TEST_UTILS_H
#define LIBDHCPSRV_TEST_UTILS_H

#include <dhcpsrv/lease_mgr.h>
#include <gtest/gtest.h>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

// @brief performs details comparison between two IPv6 leases
//
// @param first first lease to compare
// @param second second lease to compare
//
// This method is intended to be run from gtest tests as it
// uses gtest macros and possibly reports gtest failures.
void
detailCompareLease(const Lease6Ptr& first, const Lease6Ptr& second);

// @brief performs details comparison between two IPv4 leases
//
// @param first first lease to compare
// @param second second lease to compare
//
// This method is intended to be run from gtest tests as it
// uses gtest macros and possibly reports gtest failures.
void
detailCompareLease(const Lease4Ptr& first, const Lease4Ptr& second);

/// @brief Test Fixture class with utility functions for LeaseMgr backends
///
/// It contains utility functions, like dummy lease creation.
/// All concrete LeaseMgr test classes should be derived from it.
class GenericLeaseMgrTest : public ::testing::Test {
public:

    /// @brief Default constructor.
    GenericLeaseMgrTest();

    /// @brief Virtual destructor.
    virtual ~GenericLeaseMgrTest();

    /// @brief Reopen the database
    ///
    /// Closes the database and re-open it. This must be implemented
    /// in derived classes.
    virtual void reopen() = 0;

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

    /// @brief Basic Lease6 Checks
    ///
    /// Checks that the addLease, getLease6 (by address) and deleteLease (with an
    /// IPv6 address) works.
    void testBasicLease6();

    /// @brief Test that IPv6 lease can be added, retrieved and deleted.
    ///
    /// This method checks basic IPv6 lease operations. There's check_t1_t2
    /// parameter that controls whether the backend supports storing T1, T2
    /// parameters. memfile supports it, while MySQL doesn't. If T1,T2
    /// storage is not supported, the expected values are 0.
    ///
    /// @param check_t1_t2 controls whether T1,T2 timers should be checked
    void testAddGetDelete6(bool check_t1_t2);

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

    // Member variables
    std::vector<std::string>  straddress4_;   ///< String forms of IPv4 addresses
    std::vector<isc::asiolink::IOAddress> ioaddress4_;  ///< IOAddress forms of IPv4 addresses
    std::vector<std::string>  straddress6_;   ///< String forms of IPv6 addresses
    std::vector<Lease::Type> leasetype6_; ///< Lease types
    std::vector<isc::asiolink::IOAddress> ioaddress6_;  ///< IOAddress forms of IPv6 addresses

    LeaseMgr* lmptr_;                     ///< Pointer to the lease manager
};

};
};
};

#endif
