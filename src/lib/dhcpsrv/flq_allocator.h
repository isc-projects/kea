// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FLQ_ALLOCATOR_H
#define FLQ_ALLOCATOR_H

#include <dhcpsrv/allocator.h>
#include <dhcpsrv/flq_allocation_state.h>
#include <dhcpsrv/lease.h>
#include <cstdint>

namespace isc {
namespace dhcp {

/// @brief An allocator maintaining a queue of free leases.
///
/// This allocator populates the queue of free leases during the initialization.
/// It also installs the callbacks in the @c LeaseMgr, to track the subsequent
/// lease changes. It allows for maintaining the running queue of free leases.
///
/// The allocator offers the leases from the queue, minimizing the number of
/// the allocation engine's attempts to check if some other client is using
/// the offered lease. Ideally, only one check should suffice. However, when
/// several servers share a lease database, the collisions may occur because
/// the servers don't observe each others' allocations.
///
/// This allocator should only be used for reasonably small pools due to the
/// overhead to populate the free leases. A reasonably small pool is an IPv4
/// pool (including /8) and the prefix delegation pools with similar capacity.
/// This allocator is not suitable for a typical IPv6 address pool (e.g., /64).
/// An attempt to populate free leases for such a giant pool would freeze the
/// server and likely exhaust its memory.
///
/// Free leases are populated in a random order.
class FreeLeaseQueueAllocator : public Allocator {
public:

    /// @brief Constructor.
    ///
    /// @param type specifies the type of allocated leases.
    /// @param subnet weak pointer to the subnet owning the allocator.
    FreeLeaseQueueAllocator(Lease::Type type, const WeakSubnetPtr& subnet);

    /// @brief Returns the allocator type string.
    ///
    /// @return flq string.
    virtual std::string getType() const {
        return ("flq");
    }

private:

    /// @brief Performs allocator initialization after server's reconfiguration.
    ///
    /// The allocator installs the callbacks in the lease manager to keep track of
    /// the lease allocations and maintain the free leases queue.
    virtual void initAfterConfigureInternal();

    /// @brief Populates the queue of free addresses (IPv4 and IPv6).
    ///
    /// It adds each address in the subnet pools that does not exist in the
    /// list of leases to the free leases queue. The addresses are added
    /// in a random order.
    ///
    /// @param lease collection of leases in the database for a subnet.
    /// @param pools collection of pools in the subnet.
    /// @tparam LeaseCollectionType Type of the lease collection returned from the
    /// database (i.e., @c Lease4Collection or @c Lease6Collection).
    template<typename LeaseCollectionType>
    void populateFreeAddressLeases(const LeaseCollectionType& leases, const PoolCollection& pools);

    /// @brief Populates the queue of free delegated prefixes.
    ///
    /// It adds each delegated prefix in the subnet pools that does not exist in the
    /// list of leases to the free leases queue. The delegated prefixes are added
    /// in a random order.
    ///
    /// @param lease collection of delegated prefixes in the database for a subnet.
    /// @param pools collection of prefix delegation pools in the subnet.
    void populateFreePrefixDelegationLeases(const Lease6Collection& leases, const PoolCollection& pools);

    /// @brief Returns next available address from the queue.
    ///
    /// Internal thread-unsafe implementation of the @c pickAddress.
    ///
    /// @param client_classes list of classes client belongs to.
    /// @param duid client DUID (ignored).
    /// @param hint client hint (ignored).
    ///
    /// @return next offered address.
    virtual asiolink::IOAddress pickAddressInternal(const ClientClasses& client_classes,
                                                    const IdentifierBaseTypePtr& duid,
                                                    const asiolink::IOAddress& hint);

    /// @brief Returns next available delegated prefix from the queue.
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
    /// @return the next prefix.
    virtual isc::asiolink::IOAddress
    pickPrefixInternal(const ClientClasses& client_classes,
                       Pool6Ptr& pool,
                       const IdentifierBaseTypePtr& duid,
                       PrefixLenMatchType prefix_length_match,
                       const isc::asiolink::IOAddress& hint,
                       uint8_t hint_prefix_length);

    /// @brief Convenience function returning pool allocation state instance.
    ///
    /// It creates a new pool state instance and assigns it to the pool
    /// if it hasn't been initialized.
    ///
    /// @param pool pool instance.
    /// @return allocation state instance for the pool.
    PoolFreeLeaseQueueAllocationStatePtr getPoolState(const PoolPtr& pool) const;

    /// @brief Returns a pool in the subnet the lease belongs to.
    ///
    /// This function is used in the interface manager callbacks to find
    /// a pool for a lease modified in the database.
    ///
    /// @param lease lease instance for which the pool should be returned.
    /// @return A pool found for a lease or null pointer if such a pool does
    /// not exist.
    PoolPtr getLeasePool(const LeasePtr& lease) const;

    /// @brief Thread safe callback for adding a lease.
    ///
    /// Removes the lease from the free lease queue.
    ///
    /// @param lease added lease.
    void addLeaseCallback(LeasePtr lease);

    /// @brief Thread unsafe callback for adding a lease.
    ///
    /// Removes the lease from the free lease queue.
    ///
    /// @param lease added lease.
    void addLeaseCallbackInternal(LeasePtr lease);

    /// @brief Thread safe callback for updating a lease.
    ///
    /// If the lease is reclaimed in this update it is added to the
    /// free lease queue. If the lease is valid after the update,
    /// the lease is removed from the free lease queue, if exists.
    ///
    /// @param lease updated lease.
    void updateLeaseCallback(LeasePtr lease);

    /// @brief Thread unsafe callback for updating a lease.
    ///
    /// If the lease is reclaimed in this update it is added to the
    /// free lease queue. If the lease is valid after the update,
    /// the lease is removed from the free lease queue, if exists.
    ///
    /// @param lease updated lease.
    void updateLeaseCallbackInternal(LeasePtr lease);

    /// @brief Thread safe callback for deleting a lease.
    ///
    /// Adds the lease to the free lease queue.
    ///
    /// @param lease deleted lease.
    void deleteLeaseCallback(LeasePtr lease);

    /// @brief Thread unsafe callback for updating a lease.
    ///
    /// Adds the lease to the free lease queue.
    ///
    /// @param lease deleted lease.
    void deleteLeaseCallbackInternal(LeasePtr lease);

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

#endif // FLQ_ALLOCATOR_H
