// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ITERATIVE_ALLOCATION_STATE_H
#define ITERATIVE_ALLOCATION_STATE_H

#include <asiolink/io_address.h>
#include <dhcpsrv/allocation_state.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <map>

namespace isc {
namespace dhcp {

/// @brief Forward declaration of the @c SubnetIterativeAllocationState.
class SubnetIterativeAllocationState;

/// @brief Type of the pointer to the @c SubnetIterativeAllocationState.
typedef boost::shared_ptr<SubnetIterativeAllocationState> SubnetIterativeAllocationStatePtr;

/// @brief Subnet allocation state used by the iterative allocator.
///
/// It extends the base class with the mechanism to store the last
/// allocated address or delegated prefix. The iterative allocator
/// uses this information to pick the next address or delegated
/// prefix on the next allocation request.
class SubnetIterativeAllocationState : public SubnetAllocationState {
public:

    /// @brief Factory function creating the state instance from subnet.
    ///
    /// @param subnet instance of the subnet for which the allocation
    /// state should be instantiated.
    /// @return new allocation state instance.
    static SubnetIterativeAllocationStatePtr create(const SubnetPtr& subnet);

    /// @brief Constructor.
    ///
    /// @param prefix subnet prefix.
    /// @param prefix_length subnet prefix length.
    SubnetIterativeAllocationState(const asiolink::IOAddress& prefix,
                                   const uint8_t prefix_length);

    /// @brief Returns last allocated address or prefix.
    ///
    /// @return last allocated address or prefix.
    asiolink::IOAddress getLastAllocated() const;

    /// @brief Sets last allocated address or prefix.
    ///
    /// @param address an address or prefix last allocated.
    void setLastAllocated(const asiolink::IOAddress& address);

private:

    /// @brief Last allocated address or delegated prefix.
    ///
    /// This is the last allocated address or delegated prefix that was
    /// previously allocated from the particular subnet. It should be
    /// noted that although the value is usually correct, there are
    /// cases when it is invalid, e.g. after removing a pool,
    /// restarting or changing allocation algorithms. For that purpose
    /// it should be only considered a help that should not be fully
    /// trusted.
    asiolink::IOAddress last_allocated_;
};

/// @brief Forward declaration of the @c PoolIterativeAllocationState.
class PoolIterativeAllocationState;

/// @brief Type of the pointer to the @c PoolIterativeAllocationState.
typedef boost::shared_ptr<PoolIterativeAllocationState> PoolIterativeAllocationStatePtr;

/// @brief Pool allocation state used by the iterative allocator.
///
/// It extends the base class with the information about the last allocated
/// address in the pool.
class PoolIterativeAllocationState : public AllocationState {
public:

    /// @brief Factory function creating the state instance from pool.
    ///
    /// @param pool instance of the pool for which the allocation state
    /// should be instantiated.
    /// @return new allocation state instance.
    static PoolIterativeAllocationStatePtr create(const PoolPtr& pool);

    /// @brief Constructor.
    ///
    /// @param first first address in the pool.
    PoolIterativeAllocationState(const asiolink::IOAddress& first);

    /// @brief Returns the last address that was tried from this pool
    ///
    /// @return address or prefix that was last tried from this pool
    isc::asiolink::IOAddress getLastAllocated() const {
        return (last_allocated_);
    }

    /// @brief Checks if the last address is valid.
    ///
    /// @return true if the last address is valid, false otherwise.
    bool isLastAllocatedValid() const {
        return last_allocated_valid_;
    }

    /// @brief Sets the last address that was tried from this pool.
    ///
    /// @param address address or prefix to that was tried last.
    void setLastAllocated(const asiolink::IOAddress& address) {
        last_allocated_ = address;
        last_allocated_valid_ = true;
    }

    /// @brief Resets the last address to invalid.
    void resetLastAllocated() {
        last_allocated_valid_ = false;
    }

private:

    /// @brief Last allocated address or prefix.
    isc::asiolink::IOAddress last_allocated_;

    /// @brief Last allocated address status.
    bool last_allocated_valid_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // ITERATIVE_ALLOCATION_STATE_H
