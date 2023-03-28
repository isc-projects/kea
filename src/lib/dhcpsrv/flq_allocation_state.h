// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FLQ_ALLOCATION_STATE_H
#define FLQ_ALLOCATION_STATE_H

#include <dhcpsrv/allocation_state.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>

namespace isc {
namespace dhcp {

/// @brief Forward declaration of the @c PoolFreeLeaseQueueAllocationState.
class PoolFreeLeaseQueueAllocationState;

/// @brief Type of the pointer to the @c PoolFreeLeaseQueueAllocationState.
typedef boost::shared_ptr<PoolFreeLeaseQueueAllocationState> PoolFreeLeaseQueueAllocationStatePtr;

/// @brief Pool allocation state used by the FLQ allocator.
class PoolFreeLeaseQueueAllocationState : public AllocationState {
public:

    /// @brief Factory function creating the state instance from a pool.
    ///
    /// @param pool instance of the pool for which the allocation state
    /// should be instantiated.
    /// @return new allocation state instance.
    static PoolFreeLeaseQueueAllocationStatePtr create(const PoolPtr& pool);

    /// @brief Constructor.
    ///
    /// Instantiates the allocation state for the specified lease type.
    ///
    /// @param type lease type.
    PoolFreeLeaseQueueAllocationState(Lease::Type type);

    /// @brief Checks if the pool has run out of free leases.
    ///
    /// @return true if the pool has no free leases, false otherwise.
    bool exhausted() const;

    /// @brief Adds a free lease to the queue.
    ///
    /// @param address lease address.
    void addFreeLease(const asiolink::IOAddress& address);

    /// @brief Deletes free lease from the queue.
    ///
    /// @param address lease address.
    void deleteFreeLease(const asiolink::IOAddress& address);

    /// @brief Returns next available lease.
    ///
    /// @return next free lease address or IPv4/IPv6 zero address when
    /// there are no free leases.
    asiolink::IOAddress offerFreeLease();

    /// @brief Returns the current number of free leases in the queue.
    ///
    /// @return the number of free leases in the queue.
    size_t getFreeLeaseCount() const;

private:

    /// @brief A multi-index container holding free leases.
    ///
    /// When it is used as a storage for IPv4 leases, the @c AddressType
    /// should be @c uint32_t. For IPv6 leases, it should be @c IOAddress.
    /// Note that using the @c uint32_t for the IPv4 case significantly reduces
    /// the amount of memory occupied by the container by removing the overhead
    /// of holding the entire IOAddress instance.
    template<typename AddressType>
    using FreeLeaseQueue = boost::multi_index_container<
        AddressType,
        boost::multi_index::indexed_by<
            boost::multi_index::sequenced<>,
            boost::multi_index::hashed_unique<
                boost::multi_index::identity<AddressType>
            >
        >
    >;

    /// @brief A multi-index container holding free IPv4 leases.
    typedef boost::shared_ptr<FreeLeaseQueue<uint32_t>> FreeLease4QueuePtr;

    /// @brief A multi-index container holding free IPv6 leases.
    typedef boost::shared_ptr<FreeLeaseQueue<asiolink::IOAddress>> FreeLease6QueuePtr;

    /// @brief An instance of the multi-index container holding
    /// free IPv4 leases.
    FreeLease4QueuePtr free_lease4_queue_;

    /// @brief An instance of the multi-index container holding
    /// free IPv6 leases.
    FreeLease6QueuePtr free_lease6_queue_;
};


} // end of isc::dhcp namespace
} // end of isc namespace

#endif // FLQ_ALLOCATION_STATE_H
