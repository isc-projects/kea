// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ITERATIVE_ALLOCATOR_H
#define ITERATIVE_ALLOCATOR_H

#include <dhcpsrv/allocator.h>
#include <dhcpsrv/iterative_allocation_state.h>
#include <dhcpsrv/lease.h>

#include <cstdint>

namespace isc {
namespace dhcp {

/// @brief Address/prefix allocator that iterates over all addresses.
///
/// This class implements an iterative algorithm that returns all addresses in
/// a pool iteratively, one after another. Once the last address is reached,
/// it starts allocating from the beginning of the first pool (i.e. it loops
/// over).
class IterativeAllocator : public Allocator {
public:

    /// @brief Constructor.
    ///
    /// @param type specifies the type of allocated leases.
    /// @param subnet weak pointer to the subnet owning the allocator.
    IterativeAllocator(Lease::Type type, const WeakSubnetPtr& subnet);

private:

    /// @brief Returns the next address from the pools in the subnet.
    ///
    /// Internal thread-unsafe implementation of the @c pickAddress.
    ///
    /// @param client_classes list of classes client belongs to.
    /// @param duid client DUID (ignored).
    /// @param hint client hint (ignored).
    ///
    /// @return next offered address.
    virtual asiolink::IOAddress pickAddressInternal(const ClientClasses& client_classes,
                                                    const DuidPtr& duid,
                                                    const asiolink::IOAddress& hint);

    /// @brief Convenience function returning subnet allocation state instance.
    ///
    /// It creates a new subnet state instance and assigns it to the subnet
    /// if it hasn't been initialized.
    ///
    /// @return allocation state instance for the subnet.
    SubnetIterativeAllocationStatePtr getSubnetState() const;

    /// @brief Convenience function returning pool allocation state instance.
    ///
    /// It creates a new pool state instance and assigns it to the pool
    /// if it hasn't been initialized.
    ///
    /// @param pool pool instance.
    /// @return allocation state instance for the pool.
    PoolIterativeAllocationStatePtr getPoolState(const PoolPtr& pool) const;

protected:

    /// @brief Returns the next prefix.
    ///
    /// This method works for IPv6 addresses only. It increases the
    /// specified prefix by a given prefix_len. For example, 2001:db8::
    /// increased by prefix length /32 will become 2001:db9::. This method
    /// is used to iterate over IPv6 prefix pools
    ///
    /// @param prefix prefix to be increased.
    /// @param prefix_len length of the prefix to be increased.
    ///
    /// @return next prefix.
    static asiolink::IOAddress increasePrefix(const asiolink::IOAddress& prefix,
                                              const uint8_t prefix_len);

    /// @brief Returns the next address or prefix.
    ///
    /// This method works for IPv4 addresses, IPv6 addresses and
    /// IPv6 prefixes.
    ///
    /// @param address address or prefix to be increased
    /// @param prefix true when the previous argument is a prefix.
    /// @param prefix_len length of the prefix.
    ///
    /// @return result address or prefix
    static asiolink::IOAddress increaseAddress(const asiolink::IOAddress& address,
                                               bool prefix,
                                               const uint8_t prefix_len);
};

}  // namespace dhcp
}  // end of namespace isc

#endif  // ITERATIVE_ALLOCATOR_H
