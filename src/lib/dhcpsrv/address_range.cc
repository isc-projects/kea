// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/addr_utilities.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/address_range.h>
#include <exceptions/exceptions.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

AddressRange::AddressRange(const IOAddress& start, const IOAddress& end)
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

PrefixRange::PrefixRange(const asiolink::IOAddress& prefix, const uint8_t length, const uint8_t delegated)
    : start_(prefix), end_(IOAddress::IPV6_ZERO_ADDRESS()), delegated_length_(delegated) {
    if (!start_.isV6()) {
        isc_throw(BadValue, "IPv6 prefix required for prefix delegation range but "
                  << start_ << " was specified");
    }
    if (delegated_length_ < length) {
        isc_throw(BadValue, "delegated length " << static_cast<int>(delegated_length_)
                  << " must not be lower than prefix length " << static_cast<int>(length));
    }
    if ((length > 128) || (delegated_length_ > 128)) {
        isc_throw(BadValue, "delegated length " << static_cast<int>(delegated_length_)
                  << " and prefix length " << static_cast<int>(length)
                  << " must not be greater than 128");
    }
    auto prefixes_num = prefixesInRange(length, delegated_length_);
    uint64_t addrs_in_prefix = static_cast<uint64_t>(1) << (128 - delegated_length_);
    end_ = offsetAddress(prefix, (prefixes_num - 1) * addrs_in_prefix);
}

PrefixRange::PrefixRange(const asiolink::IOAddress& start, const asiolink::IOAddress& end,
                         const uint8_t delegated)
    : start_(start), end_(end), delegated_length_(delegated) {
    if (!start_.isV6() || !end_.isV6()) {
        isc_throw(BadValue, "IPv6 prefix required for prefix delegation range but "
                  << start_ << ":" << end_ << " was specified");
    }
    // The start must be lower or equal the end.
    if (end_ < start_) {
        isc_throw(BadValue, "invalid address range boundaries " << start_ << ":" << end_);
    }
    if (delegated_length_ > 128) {
        isc_throw(BadValue, "delegated length " << static_cast<int>(delegated_length_)
                  << " must not be greater than 128");
    }
}
 
} // end of namespace isc::dhcp
} // end of namespace isc
