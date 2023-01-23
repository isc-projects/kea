// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RANDOM_ALLOCATION_STATE_H
#define RANDOM_ALLOCATION_STATE_H

#include <dhcpsrv/allocation_state.h>
#include <dhcpsrv/ip_range_permutation.h>
#include <dhcpsrv/pool.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>

namespace isc {
namespace dhcp {

/// @brief Forward declaration of the @c PoolRandomAllocationState.
class PoolRandomAllocationState;

/// @brief Type of the pointer to the @c PoolRandomAllocationState.
typedef boost::shared_ptr<PoolRandomAllocationState> PoolRandomAllocationStatePtr;

/// @brief Pool allocation state used by the random allocator.
///
/// It extends the base class with the mechanism that maintains
/// an address or delegated prefix pool permutation. The
/// permutation serves random, non-repeating leases.
class PoolRandomAllocationState : public AllocationState {
public:

    /// @brief Factory function creating the state instance from pool.
    ///
    /// @param pool instance of the pool for which the allocation state
    /// should be instantiated.
    /// @return new allocation state instance.
    static PoolRandomAllocationStatePtr create(const PoolPtr& pool);

    /// @brief Constructor from an IP address pool.
    ///
    /// @param first first address in the pool.
    /// @param last last address in the pool.
    PoolRandomAllocationState(const asiolink::IOAddress& first,
                              const asiolink::IOAddress& last);

    /// @brief Constructor from a delegated prefix pool.
    ///
    /// @param first first address in the pool.
    /// @param last last prefix in the pool.
    /// @param delegated delegated prefix length.
    PoolRandomAllocationState(const asiolink::IOAddress& first,
                              const asiolink::IOAddress& last,
                              const uint8_t delegated);

    /// @brief Returns a pointer to the permutation of addresses
    /// or delegated prefixes.
    ///
    /// @return permutation instance.
    IPRangePermutationPtr getPermutation() const {
        return (permutation_);
    }

private:

    /// @brief Permutation instance for the pool.
    IPRangePermutationPtr permutation_;
};


} // end of isc::dhcp namespace
} // end of isc namespace

#endif // RANDOM_ALLOCATION_STATE_H
