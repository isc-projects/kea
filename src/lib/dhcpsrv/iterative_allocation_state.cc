// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/addr_utilities.h>
#include <dhcpsrv/iterative_allocation_state.h>
#include <util/multi_threading_mgr.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/make_shared.hpp>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

SubnetIterativeAllocationStatePtr
SubnetIterativeAllocationState::create(const SubnetPtr& subnet) {
    auto subnet_prefix = subnet->get();
    return (boost::make_shared<SubnetIterativeAllocationState>(subnet_prefix.first, subnet_prefix.second));
}

SubnetIterativeAllocationState::SubnetIterativeAllocationState(const IOAddress& prefix,
                                                               const uint8_t prefix_length)
    : SubnetAllocationState(),
      last_allocated_(lastAddrInPrefix(prefix, prefix_length)) {
}

IOAddress
SubnetIterativeAllocationState::getLastAllocated() const {
    MultiThreadingLock lock(*mutex_);
    return (last_allocated_);
}

void
SubnetIterativeAllocationState::setLastAllocated(const IOAddress& address) {
    MultiThreadingLock lock(*mutex_);
    last_allocated_ = address;
    // Update the timestamp of the last allocation.
    setCurrentAllocatedTimeInternal();
}

PoolIterativeAllocationStatePtr
PoolIterativeAllocationState::create(const PoolPtr& pool) {
    return (boost::make_shared<PoolIterativeAllocationState>(pool->getFirstAddress()));
}

PoolIterativeAllocationState::PoolIterativeAllocationState(const IOAddress& first)
    :   last_allocated_(first), last_allocated_valid_(false) {
}

} // end of namespace isc::dhcp
} // end of namespace isc
