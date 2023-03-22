// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/flq_allocation_state.h>
#include <boost/make_shared.hpp>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

PoolFreeLeaseQueueAllocationStatePtr
PoolFreeLeaseQueueAllocationState::create(const PoolPtr& pool) {
    return (boost::make_shared<PoolFreeLeaseQueueAllocationState>(pool->getType()));
}

PoolFreeLeaseQueueAllocationState::PoolFreeLeaseQueueAllocationState(Lease::Type type)
    : AllocationState(), free_lease4_queue_(), free_lease6_queue_() {
    if (type == Lease::TYPE_V4) {
        free_lease4_queue_ = boost::make_shared<FreeLeaseQueue<uint32_t>>();
    } else {
        free_lease6_queue_ = boost::make_shared<FreeLeaseQueue<IOAddress>>();
    }
}

bool
PoolFreeLeaseQueueAllocationState::exhausted() const {
    return ((free_lease4_queue_ && free_lease4_queue_->empty()) ||
            (free_lease6_queue_ && free_lease6_queue_->empty()));
}

void
PoolFreeLeaseQueueAllocationState::addFreeLease(const asiolink::IOAddress& address) {
    if (free_lease4_queue_) {
        free_lease4_queue_->push_back(address.toUint32());
    } else {
        free_lease6_queue_->push_back(address);
    }
}

void
PoolFreeLeaseQueueAllocationState::deleteFreeLease(const asiolink::IOAddress& address) {
    if (free_lease4_queue_) {
        auto& idx = free_lease4_queue_->get<1>();
        idx.erase(address.toUint32());
    } else {
        auto& idx = free_lease6_queue_->get<1>();
        idx.erase(address);
    }
}

IOAddress
PoolFreeLeaseQueueAllocationState::offerFreeLease() {
    if (free_lease4_queue_) {
        if (free_lease4_queue_->empty()) {
            return (IOAddress::IPV4_ZERO_ADDRESS());
        }
        uint32_t lease = free_lease4_queue_->front();
        free_lease4_queue_->pop_front();
        free_lease4_queue_->push_back(lease);
        return (IOAddress(lease));
    }

    if (free_lease6_queue_->empty()) {
        return (IOAddress::IPV6_ZERO_ADDRESS());
    }
    IOAddress lease = free_lease6_queue_->front();
    free_lease6_queue_->pop_front();
    free_lease6_queue_->push_back(lease);
    return (lease);
}

size_t
PoolFreeLeaseQueueAllocationState::getFreeLeaseCount() const {
    if (free_lease4_queue_) {
        return (free_lease4_queue_->size());
    }
    return (free_lease6_queue_->size());
}

} // end of namespace isc::dhcp
} // end of namespace isc

