// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
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

} // end of namespace isc::dhcp
} // end of namespace isc
