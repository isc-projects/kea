// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/free_lease_queue.h>
#include <exceptions/exceptions.h>

#include <boost/make_shared.hpp>

#include <iostream>
#include <iterator>
#include <tuple>
#include <utility>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

FreeLeaseQueue::Range::Range(const IOAddress& start, const IOAddress& end)
    : start_(start), end_(end) {
    // The start must be lower or equal the end.
    if (end_ < start_) {
        isc_throw(BadValue, "invalid address range boundaries " << start_ << ":" << end_);
    }
    // Two IPv4 or two IPv6 addresses are expected as range boundaries.
    if (start_.getFamily() != end_.getFamily()) {
        isc_throw(BadValue, "address range boundaries must have the same type: " << start_
                  << ":" << end_);
    }
}

FreeLeaseQueue::FreeLeaseQueue()
    : containers_() {
}

void
FreeLeaseQueue::addRange(const Range& range) {
    // If the container with ranges is empty, there are is no need for
    // doing any checks. Let's just add the new range.
    if (!containers_.empty()) {
        // Get the next range in the container relative to the start of the new
        // range. The upper_bound returns the range which starts after the start
        // of the new range.
        auto next_range = containers_.lower_bound(range.start_);
        // Get the range the range that is before that one. It is also possible that
        // there is no previous range in which case we default to end().
        auto previous_range = containers_.end();
        // If the next range is at the beginning of the container there is no
        // previous range.
        if (next_range != containers_.begin()) {
            // This should work fine even if the next range is set to end(). We
            // will get the range that is one position before end() and that
            // should be the range that goes before the new one.
            auto it = next_range;
            --it;
            previous_range = it;
        }

        // Now that we have next and previous ranges set we should check that the
        // new range we're adding does not overlap with them.

        // If the previous range exists, let's check that the start of the new
        // range is neither within that range nor lower. Assuming that the ranges
        // are constructed such that the end must be greater or equal the start
        // it is sufficient to check that the start of the new range is not lower
        // or equal the end of the previous range.
        if ((previous_range != containers_.end()) &&
            (range.start_ <= previous_range->range_end_)) {
            isc_throw(BadValue, "new address range " << range.start_ << ":" << range.end_
                      << " overlaps with the existing range");
        }

        // If the next range exists, let's check that the end of the new range
        // is neither within that range nor higher.
        if ((next_range != containers_.end()) &&
            (next_range->range_start_ <= range.end_)) {
            isc_throw(BadValue, "new address range " << range.start_ << ":" << range.end_
                      << " overlaps with the existing range");
        }
    }

    containers_.insert(ContainerDescriptor{range.start_, range.end_,
                                           boost::make_shared<Container>()});
}

void
FreeLeaseQueue::addRange(const IOAddress& start, const IOAddress& end) {
    addRange(FreeLeaseQueue::Range(start, end));
}

bool
FreeLeaseQueue::removeRange(const Range& range) {
    return (containers_.get<1>().erase(range.start_) > 0);
}

bool
FreeLeaseQueue::append(const IOAddress& address) {
    // If there are no ranges defined, there is nothing to do.
    if (containers_.empty()) {
        return (false);
    }
    // Find the beginning of the range which has the start address
    // greater than the address we're appending.
    auto lb = containers_.upper_bound(address);
    // If the range we found is the first one in the container
    // there is no range matching our address because all existing
    // ranges include higher addresses.
    if (lb == containers_.begin()) {
        return (false);
    }
    --lb;
    // Go one range back and see if our address is within its boundaries.
    if ((lb->range_end_ < address) || (address < lb->range_start_)) {
        return (false);
    }
    // Use the range we found and append the address to it.
    FreeLeaseQueue::Range range(lb->range_start_, lb->range_end_);
    append(range, address);

    // Everything is fine.
    return (true);
}

void
FreeLeaseQueue::append(const FreeLeaseQueue::Range& range, const IOAddress& address) {
    // Make sure the address is within the range boundaries.
    if ((address < range.start_) || (range.end_ < address)) {
        isc_throw(BadValue, "address " << address << " is not within the range of "
                  << range.start_ << ":" << range.end_);
    }
    auto cont = getContainer(range);
    cont->insert(address);
}

void
FreeLeaseQueue::append(const uint64_t range_index, const IOAddress& address) {
    auto desc = getContainerDescriptor(range_index);
    if ((address < desc.range_start_) || (desc.range_end_ < address)) {
        isc_throw(BadValue, "address " << address << " is not within the range of "
                  << desc.range_start_ << ":" << desc.range_end_);
    }
    desc.container_->insert(address);
}

bool
FreeLeaseQueue::use(const FreeLeaseQueue::Range& range, const IOAddress& address) {
    if ((address < range.start_) || (range.end_ < address)) {
        isc_throw(BadValue, "address " << address << " is outside of the range of "
                  << range.start_ << ":" << range.end_);
    }
    auto cont = getContainer(range);
    auto found = cont->find(address);
    if (found != cont->end()) {
        static_cast<void>(cont->erase(found));
        return (true);
    }
    return (false);
}

IOAddress
FreeLeaseQueue::next(const FreeLeaseQueue::Range& range) {
    return (popNextInternal(range, true));
}

IOAddress
FreeLeaseQueue::pop(const FreeLeaseQueue::Range& range) {
    return (popNextInternal(range, false));
}

uint64_t
FreeLeaseQueue::getRangeIndex(const FreeLeaseQueue::Range& range) const {
    auto cont = containers_.get<1>().find(range.start_);
    if (cont == containers_.get<1>().end()) {
        isc_throw(BadValue, "conatiner for the specified address range " << range.start_
                  << ":" << range.end_ << " does not exist");
    }
    return (std::distance(containers_.get<2>().begin(), containers_.project<2>(cont)));
}

FreeLeaseQueue::ContainerPtr
FreeLeaseQueue::getContainer(const FreeLeaseQueue::Range& range) {
    auto cont = containers_.find(range.start_);
    if (cont == containers_.end()) {
        isc_throw(BadValue, "conatiner for the specified address range " << range.start_
                  << ":" << range.end_ << " does not exist");
    }
    return (cont->container_);
}

FreeLeaseQueue::ContainerDescriptor
FreeLeaseQueue::getContainerDescriptor(const uint64_t range_index) {
    if (containers_.get<2>().size() <= range_index) {
        isc_throw(BadValue, "conatiner for the specified range index " << range_index
                  << " does not exist");
    }
    auto cont = containers_.get<2>().at(range_index);
    return (cont);
}

IOAddress
FreeLeaseQueue::popNextInternal(const Range& range, const bool push) {
    auto cont = getContainer(range);
    if (cont->empty()) {
        return (IOAddress::IPV4_ZERO_ADDRESS());
    }
    auto& idx = cont->get<1>();
    auto next = idx.front();
    idx.pop_front();
    if (push) {
        idx.push_back(next);
    }
    return (next);

}

} // end of namespace isc::dhcp
} // end of namespace isc
