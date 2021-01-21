// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/addr_utilities.h>
#include <dhcpsrv/free_lease_queue.h>

#include <boost/make_shared.hpp>

#include <iostream>
#include <tuple>
#include <utility>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

FreeLeaseQueue::FreeLeaseQueue()
    : ranges_() {
}

void
FreeLeaseQueue::addRange(const AddressRange& range) {
    // If the container with ranges is empty, there are is no need for
    // doing any checks. Let's just add the new range.
    if (!ranges_.empty()) {
        checkRangeOverlaps(range.start_, range.end_);
    }
    ranges_.insert(RangeDescriptor{range.start_, range.end_, 128, boost::make_shared<Leases>()});
}

void
FreeLeaseQueue::addRange(const IOAddress& start, const IOAddress& end) {
    addRange(AddressRange(start, end));
}

void
FreeLeaseQueue::addRange(const PrefixRange& range) {
    if (!ranges_.empty()) {
        auto last_addr = offsetAddress(range.end_, range.delegated_length_ - 1);
        checkRangeOverlaps(range.start_, last_addr);
    }
    ranges_.insert(RangeDescriptor{range.start_, range.end_, range.delegated_length_,
                                   boost::make_shared<Leases>()});
}

void
FreeLeaseQueue::addRange(const asiolink::IOAddress& prefix, const uint8_t prefix_length,
                         const uint8_t delegated_length) {
    addRange(PrefixRange(prefix, prefix_length, delegated_length));
}

bool
FreeLeaseQueue::append(const IOAddress& address) {
    // If there are no ranges defined, there is nothing to do.
    if (ranges_.empty()) {
        return (false);
    }
    // Find the beginning of the range which has the start address
    // greater than the address we're appending.
    auto lb = ranges_.upper_bound(address);
    // If the range we found is the first one in the container
    // there is no range matching our address because all existing
    // ranges include higher addresses.
    if (lb == ranges_.begin()) {
        return (false);
    }
    --lb;
    // Go one range back and see if our address is within its boundaries.
    if ((lb->range_end_ < address) || (address < lb->range_start_)) {
        return (false);
    }
    // Use the range we found and append the address to it.
    AddressRange range(lb->range_start_, lb->range_end_);
    append(range, address);

    // Everything is fine.
    return (true);
}

bool
FreeLeaseQueue::append(const IOAddress& prefix, const uint8_t delegated_length) {
    // If there are no ranges defined, there is nothing to do.
    if (ranges_.empty()) {
        return (false);
    }
    // Find the beginning of the range which has the start address
    // greater than the address we're appending.
    auto lb = ranges_.upper_bound(prefix);
    // If the range we found is the first one in the container
    // there is no range matching our prefix because all existing
    // ranges include higher addresses.
    if (lb == ranges_.begin()) {
        return (false);
    }
    --lb;
    // Go one range back and see if our prefix is within its boundaries.
    if ((lb->range_end_ < prefix) || (prefix < lb->range_start_) ||
        (delegated_length != lb->delegated_length_)) {
        return (false);
    }
    // Use the range we found and append the prefix to it.
    PrefixRange range(lb->range_start_, lb->range_end_, lb->delegated_length_);
    append(range, prefix);

    // Everything is fine.
    return (true);
}

void
FreeLeaseQueue::append(const AddressRange& range, const IOAddress& address) {
    // Make sure the address is within the range boundaries.
    checkRangeBoundaries(range, address);
    auto cont = getLeases(range);
    cont->insert(address);
}

void
FreeLeaseQueue::append(const uint64_t range_index, const IOAddress& ip) {
    auto desc = getRangeDescriptor(range_index);
    if ((ip < desc.range_start_) || (desc.range_end_ < ip)) {
        isc_throw(BadValue, ip << " is not within the range of " << desc.range_start_
                  << ":" << desc.range_end_);
    }
    desc.leases_->insert(ip);
}

void
FreeLeaseQueue::append(const PrefixRange& range, const asiolink::IOAddress& prefix) {
    checkRangeBoundaries(range, prefix, true);
    auto cont = getLeases(range);
    cont->insert(prefix);
}

bool
FreeLeaseQueue::use(const AddressRange& range, const IOAddress& address) {
    checkRangeBoundaries(range, address);
    auto cont = getLeases(range);
    auto found = cont->find(address);
    if (found != cont->end()) {
        static_cast<void>(cont->erase(found));
        return (true);
    }
    return (false);
}

bool
FreeLeaseQueue::use(const PrefixRange& range, const IOAddress& prefix) {
    checkRangeBoundaries(range, prefix, true);
    auto cont = getLeases(range);
    auto found = cont->find(prefix);
    if (found != cont->end()) {
        static_cast<void>(cont->erase(found));
        return (true);
    }
    return (false);
}

template<typename RangeType>
void
FreeLeaseQueue::checkRangeBoundaries(const RangeType& range, const IOAddress& ip,
                                     const bool prefix) const {
    if ((ip < range.start_) || (range.end_ < ip)) {
        isc_throw(BadValue, (prefix ? "prefix " : "address ") << ip << " is not within the range of "
                  << range.start_ << ":" << range.end_);
    }
}

void
FreeLeaseQueue::checkRangeOverlaps(const IOAddress& start, const IOAddress& end) const {
    // Get the next range in the container relative to the start of the new
    // range. The upper_bound returns the range which starts after the start
    // of the new range.
    auto next_range = ranges_.lower_bound(start);
    // Get the range the range that is before that one. It is also possible that
    // there is no previous range in which case we default to end().
    auto previous_range = ranges_.end();
    // If the next range is at the beginning of the container there is no
    // previous range.
    if (next_range != ranges_.begin()) {
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
    if ((previous_range != ranges_.end()) &&
        (start <= previous_range->range_end_)) {
        isc_throw(BadValue, "new address range " << start << ":" << end
                  << " overlaps with the existing range");
    }

    // If the next range exists, let's check that the end of the new range
    // is neither within that range nor higher.
    if ((next_range != ranges_.end()) &&
        (next_range->range_start_ <= end)) {
        isc_throw(BadValue, "new address range " << start << ":" << end
                  << " overlaps with the existing range");
    }
}


FreeLeaseQueue::LeasesPtr
FreeLeaseQueue::getLeases(const AddressRange& range) const {
    auto cont = ranges_.find(range.start_);
    if (cont == ranges_.end()) {
        isc_throw(BadValue, "container for the specified address range " << range.start_
                  << ":" << range.end_ << " does not exist");
    }
    return (cont->leases_);
}

FreeLeaseQueue::LeasesPtr
FreeLeaseQueue::getLeases(const PrefixRange& range) const {
    auto cont = ranges_.find(range.start_);
    if (cont == ranges_.end()) {
        isc_throw(BadValue, "container for the specified prefix " << range.start_
                  << " and delegated length of " << static_cast<int>(range.delegated_length_)
                  << " does not exist");
    }
    return (cont->leases_);
}

FreeLeaseQueue::RangeDescriptor
FreeLeaseQueue::getRangeDescriptor(const uint64_t range_index) const {
    if (ranges_.get<2>().size() <= range_index) {
        isc_throw(BadValue, "container for the specified range index " << range_index
                  << " does not exist");
    }
    auto cont = ranges_.get<2>().at(range_index);
    return (cont);
}

} // end of namespace isc::dhcp
} // end of namespace isc
