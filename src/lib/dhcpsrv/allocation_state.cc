// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/allocation_state.h>
#include <util/multi_threading_mgr.h>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace isc::util;

namespace isc {
namespace dhcp {

SubnetAllocationState::SubnetAllocationState()
    : AllocationState(), mutex_(new std::mutex) {
    // Initialize timestamps for each lease type to negative infinity.
    last_allocated_time_[Lease::TYPE_V4] = boost::posix_time::neg_infin;
    last_allocated_time_[Lease::TYPE_NA] = boost::posix_time::neg_infin;
    last_allocated_time_[Lease::TYPE_TA] = boost::posix_time::neg_infin;
    last_allocated_time_[Lease::TYPE_PD] = boost::posix_time::neg_infin;
}

boost::posix_time::ptime
SubnetAllocationState::getLastAllocatedTime(Lease::Type type) const {
    MultiThreadingLock lock(*mutex_);
    return (getLastAllocatedTimeInternal(type));
}

boost::posix_time::ptime
SubnetAllocationState::getLastAllocatedTimeInternal(Lease::Type type) const {
    auto t = last_allocated_time_.find(type);
    if (t != last_allocated_time_.end()) {
        return (t->second);
    }

    // This shouldn't happen, because we have initialized the structure
    // for all lease types.
    return (boost::posix_time::neg_infin);
}

void
SubnetAllocationState::setCurrentAllocatedTimeInternal(Lease::Type type) {
    last_allocated_time_[type] = boost::posix_time::microsec_clock::universal_time();
}

}
}
