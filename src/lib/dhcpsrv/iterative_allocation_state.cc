// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
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
      last_allocated_ia_(lastAddrInPrefix(prefix, prefix_length)),
      last_allocated_ta_(lastAddrInPrefix(prefix, prefix_length)),
      last_allocated_pd_(lastAddrInPrefix(prefix, prefix_length)) {
}

IOAddress
SubnetIterativeAllocationState::getLastAllocated(Lease::Type type) const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLastAllocatedInternal(type));
    } else {
        return (getLastAllocatedInternal(type));
    }
}

void
SubnetIterativeAllocationState::setLastAllocated(Lease::Type type, const IOAddress& address) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        setLastAllocatedInternal(type, address);
    } else {
        setLastAllocatedInternal(type, address);
    }
}

IOAddress
SubnetIterativeAllocationState::getLastAllocatedInternal(Lease::Type type) const {
    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return last_allocated_ia_;
    case Lease::TYPE_TA:
        return last_allocated_ta_;
    case Lease::TYPE_PD:
        return last_allocated_pd_;
    default:
        isc_throw(BadValue, "pool type " << type << " not supported");
    }
}

void
SubnetIterativeAllocationState::setLastAllocatedInternal(Lease::Type type,
                                                         const IOAddress& address) {
    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        last_allocated_ia_ = address;
        break;
    case Lease::TYPE_TA:
        last_allocated_ta_ = address;
        break;
    case Lease::TYPE_PD:
        last_allocated_pd_ = address;
        break;
    default:
        isc_throw(BadValue, "pool type " << type << " not supported");
    }

    // Update the timestamp of last allocation.
    setCurrentAllocatedTimeInternal(type);
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
