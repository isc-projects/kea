// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SFLQ_ALLOCATOR_H
#define SFLQ_ALLOCATOR_H

#include <dhcpsrv/allocator.h>
#include <dhcpsrv/sflq_allocation_state.h>
#include <dhcpsrv/lease.h>
#include <cstdint>

namespace isc {
namespace dhcp {

/// @brief An allocator maintaining a shared queue of free leases.
///
/// This allocator is part of the Shared Free Lease Queue (SFLQ) Allocation
/// scheme. The concept is similar to FLQ Allocation but rather than the
/// creating and maintaining free lease data locally, it is created and
/// maintained in the lease back end where it can be shared by other
/// servers.
///
/// Th allocator relies on stored procedures in the lease back end to
/// return free leases for a given IP address range (i.e. pool).  This can
/// greatly reduces the number of queries made to lease back end as only
/// addresses that are actually free are returned. The allocation engine
/// must still check for HR conflicts but generally, the maximum number
/// of queries for a client request is one query per client-qualified
/// pool rather than one query * the total number of addresses in the
/// pools.
///
/// The SFLQ data tracks the last address picked for each SFLQ pool such
/// that consecutive queries for the same pool will return a different
/// free address.  This should minimize conflicts with other servers until
/// the number of free addresses approaches zero.
///
/// This allocator should only be used for reasonably small pools due to the
/// overhead to populate the free leases. A reasonably small pool is an IPv4
/// pool (including /8) and the prefix delegation pools with similar capacity.
/// This allocator is not suitable for a typical IPv6 address pool (e.g., /64).
/// An attempt to populate free leases for such a giant pool would freeze the
/// server and likely exhaust the database server's storage.
///
/// As opposed to FLQ, free leases are populated in sequential order.
class SharedFlqAllocator : public Allocator {
public:

    /// @brief Constructor.
    ///
    /// @param type specifies the type of allocated leases.
    /// @param subnet weak pointer to the subnet owning the allocator.
    SharedFlqAllocator(Lease::Type type, const WeakSubnetPtr& subnet);

    /// @brief Returns the allocator type string.
    ///
    /// @return shared-flq string.
    virtual std::string getType() const {
        return ("shared-flq");
    }

    /// @brief Sets the global in-use flag.
    ///
    /// @param in_use new value to assign to the in-use flag.
    static void setInUse(bool in_use);

    /// @brief Returns the global in-use flag.
    ///
    /// @return True if at least one subnet in the current configuration
    /// is using Shared FLQ allocation.
    static bool inUse();

    /// @brief Returns the allocation state for the subnet pool_type;
    ///
    /// @return The allocation state.
    SubnetSflqAllocationStatePtr getSubnetState() const;

    /// @brief Sanity checks the subnet and pool configuration
    /// for use with SFLQ.
    ///
    /// @param subnet Subnet to check
    ///
    /// @throw BadValue if the capacity exceeds limit.
    static void sanityChecksSflqAllocator4(Subnet4Ptr subnet);

    /// @brief Sanity checks the subnet and pool configuration
    /// for use with SFLQ.
    ///
    /// @param subnet Subnet to check
    ///
    /// @throw BadValue if the capacity exceeds limit.
    static void sanityChecksSflqAllocator6(Subnet6Ptr subnet);

    /// @brief Maximum capacity of a V4 pool supported by SFLQ.
    static constexpr size_t MAX_V4_POOL_SIZE = 16777216;

    /// @brief Maximum capacity of a V6 pool supported by SFLQ.
    static constexpr size_t MAX_V6_POOL_SIZE = 16777216;

private:

    /// @brief Performs allocator initialization after server's reconfiguration.
    ///
    /// The allocator calls the appropriate lease back end function
    /// (sflqCreateFlqPool4 or sflqCreateFlqPool6) to create the SFLQ pools
    /// for each pool in the subnet.
    virtual void initAfterConfigureInternal();

    /// @brief Returns next available address from the pool.
    ///
    /// Internal thread-unsafe implementation of the @c pickAddress.
    ///
    /// @param client_classes list of classes client belongs to.
    /// @param duid client DUID (ignored).
    /// @param hint client hint (ignored).
    ///
    /// @return next available address or the protocol-appropriate zero address.
    virtual asiolink::IOAddress pickAddressInternal(const ClientClasses& client_classes,
                                                    const IdentifierBaseTypePtr& duid,
                                                    const asiolink::IOAddress& hint);

    /// @brief Returns next available delegated prefix from the pool.
    ///
    /// Internal thread-unsafe implementation of the @c pickPrefix.
    ///
    /// @param client_classes list of classes client belongs to.
    /// @param pool the selected pool satisfying all required conditions.
    /// @param duid Client's DUID.
    /// @param prefix_length_match type which indicates the selection criteria
    ///        for the pools relative to the provided hint prefix length
    /// @param hint Client's hint.
    /// @param hint_prefix_length the hint prefix length that the client
    ///        provided. The 0 value means that there is no hint and that any
    ///        pool will suffice.
    ///
    /// @return the next prefix or v6 zero address (i.e. '::').
    virtual isc::asiolink::IOAddress
    pickPrefixInternal(const ClientClasses& client_classes,
                       Pool6Ptr& pool,
                       const IdentifierBaseTypePtr& duid,
                       PrefixLenMatchType prefix_length_match,
                       const isc::asiolink::IOAddress& hint,
                       uint8_t hint_prefix_length);

    /// @brief Convenience function returning a random number.
    ///
    /// It is used internally by the @c pickAddressInternal and @c pickPrefixInternal
    /// functions to select a random pool.
    ///
    /// @param limit upper bound of the range.
    /// @returns random number between 0 and limit.
    uint64_t getRandomNumber(uint64_t limit);

    /// @brief Random generator used by this class.
    std::mt19937 generator_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SFLQ_ALLOCATOR_H
