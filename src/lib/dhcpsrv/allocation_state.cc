// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
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
    last_allocated_time_ = boost::posix_time::neg_infin;
}

boost::posix_time::ptime
SubnetAllocationState::getLastAllocatedTime() const {
    MultiThreadingLock lock(*mutex_);
    return (last_allocated_time_);
}

void
SubnetAllocationState::setCurrentAllocatedTimeInternal() {
    last_allocated_time_ = boost::posix_time::microsec_clock::universal_time();
}

}
}
