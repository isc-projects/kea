// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RANDOM_ALLOCATOR_H
#define RANDOM_ALLOCATOR_H

#include <dhcpsrv/allocator.h>
#include <dhcpsrv/random_allocation_state.h>
#include <dhcpsrv/lease.h>
#include <cstdint>
#include <random>

namespace isc {
namespace dhcp {

/// @brief An allocator offering addresses in a random order.
///
/// This allocator uses @c IPRangePermutation to select random
/// addresses or delegated prefixes from the pools. It guarantees
/// that all offered addresses are unique (do not repeat).
///
/// The allocator also randomly picks pools to ensure that the
/// leases are offered uniformly from the entire subnet rather than
/// from the same pool until it exhausts. When all pools exhaust,
/// the allocator resets their permutations and begins offering
/// leases from these pools again.
class RandomAllocator : public Allocator {
public:

    /// @brief Constructor.
    ///
    /// @param type specifies the type of allocated leases.
    /// @param subnet weak pointer to the subnet owning the allocator.
    RandomAllocator(Lease::Type type, const WeakSubnetPtr& subnet);

    /// @brief Returns the allocator type string.
    ///
    /// @return random string.
    virtual std::string getType() const {
        return ("random");
    }

private:

    /// @brief Returns a random address from the pools in the subnet.
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

    /// @brief Picks a delegated prefix.
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
    virtual asiolink::IOAddress pickPrefixInternal(const ClientClasses& client_classes,
                                                   Pool6Ptr& pool,
                                                   const IdentifierBaseTypePtr& duid,
                                                   PrefixLenMatchType prefix_length_match,
                                                   const asiolink::IOAddress& hint,
                                                   uint8_t hint_prefix_length);

    /// @brief Convenience function returning pool allocation state instance.
    ///
    /// It creates a new pool state instance and assigns it to the pool
    /// if it hasn't been initialized.
    ///
    /// @param pool pool instance.
    /// @return allocation state instance for the pool.
    PoolRandomAllocationStatePtr getPoolState(const PoolPtr& pool) const;

    /// @brief Convenience function returning a random number.
    ///
    /// It is used internally by the @c pickAddressInternal function to
    /// select a random pool.
    ///
    /// @param limit upper bound of the range.
    /// @returns random number between 0 and limit.
    uint64_t getRandomNumber(uint64_t limit);

    /// @brief Random generator used by this class.
    std::mt19937 generator_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // RANDOM_ALLOCATOR_H
