// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/random_allocation_state.h>
#include <boost/make_shared.hpp>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

PoolRandomAllocationStatePtr
PoolRandomAllocationState::create(const PoolPtr& pool) {
    if (pool->getType() == Lease::TYPE_PD) {
        // Pool classes ensure that the proper type is used for
        // the IPv6 specific lease types, so we can just cast
        // to the Pool6 pointer.
        auto pd_pool = boost::dynamic_pointer_cast<Pool6>(pool);
        return (boost::make_shared<PoolRandomAllocationState>(pd_pool->getFirstAddress(),
                                                              pd_pool->getLastAddress(),
                                                              pd_pool->getLength()));
    }
    return (boost::make_shared<PoolRandomAllocationState>(pool->getFirstAddress(), pool->getLastAddress()));
}

PoolRandomAllocationState::PoolRandomAllocationState(const IOAddress& first, const IOAddress& last)
    : permutation_(new IPRangePermutation(AddressRange(first, last))) {
}

PoolRandomAllocationState::PoolRandomAllocationState(const IOAddress& first, const IOAddress& last,
                                                     const uint8_t delegated)
    : permutation_(new IPRangePermutation(PrefixRange(first, last, delegated))) {
}

} // end of namespace isc::dhcp
} // end of namespace isc
