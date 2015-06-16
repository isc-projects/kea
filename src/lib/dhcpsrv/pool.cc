// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <asiolink/io_address.h>
#include <dhcpsrv/addr_utilities.h>
#include <dhcpsrv/pool.h>
#include <sstream>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

Pool::Pool(Lease::Type type, const isc::asiolink::IOAddress& first,
           const isc::asiolink::IOAddress& last)
    :id_(getNextID()), first_(first), last_(last), type_(type),
     capacity_(0) {
}

bool Pool::inRange(const isc::asiolink::IOAddress& addr) const {
    return (first_.smallerEqual(addr) && addr.smallerEqual(last_));
}

std::string
Pool::toText() const {
    std::stringstream tmp;
    tmp << "type=" << Lease::typeToText(type_) << ", " << first_
        << "-" << last_;
    return (tmp.str());
}

Pool4::Pool4(const isc::asiolink::IOAddress& first,
             const isc::asiolink::IOAddress& last)
:Pool(Lease::TYPE_V4, first, last) {
    // check if specified address boundaries are sane
    if (!first.isV4() || !last.isV4()) {
        isc_throw(BadValue, "Invalid Pool4 address boundaries: not IPv4");
    }

    if (last < first) {
        isc_throw(BadValue, "Upper boundary is smaller than lower boundary.");
    }

    // This is IPv4 pool, which only has one type. We can calculate
    // the number of theoretically possible leases in it. As there's 2^32
    // possible IPv4 addresses, we'll be able to accurately store that
    // info.
    capacity_ = addrsInRange(first, last);
}

Pool4::Pool4( const isc::asiolink::IOAddress& prefix, uint8_t prefix_len)
:Pool(Lease::TYPE_V4, prefix, IOAddress("0.0.0.0")) {

    // check if the prefix is sane
    if (!prefix.isV4()) {
        isc_throw(BadValue, "Invalid Pool4 address boundaries: not IPv4");
    }

    // check if the prefix length is sane
    if (prefix_len == 0 || prefix_len > 32) {
        isc_throw(BadValue, "Invalid prefix length");
    }

    // Let's now calculate the last address in defined pool
    last_ = lastAddrInPrefix(prefix, prefix_len);

    // This is IPv4 pool, which only has one type. We can calculate
    // the number of theoretically possible leases in it. As there's 2^32
    // possible IPv4 addresses, we'll be able to accurately store that
    // info.
    capacity_ = addrsInRange(prefix, last_);
}

Pool6::Pool6(Lease::Type type, const isc::asiolink::IOAddress& first,
             const isc::asiolink::IOAddress& last)
    :Pool(type, first, last), prefix_len_(128) {

    // check if specified address boundaries are sane
    if (!first.isV6() || !last.isV6()) {
        isc_throw(BadValue, "Invalid Pool6 address boundaries: not IPv6");
    }

    if ( (type != Lease::TYPE_NA) && (type != Lease::TYPE_TA) &&
         (type != Lease::TYPE_PD)) {
        isc_throw(BadValue, "Invalid Pool6 type: " << static_cast<int>(type)
                  << ", must be TYPE_IA, TYPE_TA or TYPE_PD");
    }

    if (last < first) {
        isc_throw(BadValue, "Upper boundary is smaller than lower boundary.");
        // This check is a bit strict. If we decide that it is too strict,
        // we need to comment it and uncomment lines below.
        // On one hand, letting the user specify 2001::f - 2001::1 is nice, but
        // on the other hand, 2001::1 may be a typo and the user really meant
        // 2001::1:0 (or 1 followed by some hex digit), so a at least a warning
        // would be useful.

        // first_  = last;
        // last_ = first;
    }

    // TYPE_PD is not supported by this constructor. first-last style
    // parameters are for IA and TA only. There is another dedicated
    // constructor for that (it uses prefix/length)
    if ((type != Lease::TYPE_NA) && (type != Lease::TYPE_TA)) {
        isc_throw(BadValue, "Invalid Pool6 type specified:"
                  << static_cast<int>(type));
    }

    // Let's calculate the theoretical number of leases in this pool.
    // If the pool is extremely large (i.e. contains more than 2^64 addresses,
    // we'll just cap it at max value of uint64_t).
    capacity_ = addrsInRange(first, last);
}

Pool6::Pool6(Lease::Type type, const isc::asiolink::IOAddress& prefix,
             uint8_t prefix_len, uint8_t delegated_len /* = 128 */)
    :Pool(type, prefix, IOAddress("::")), prefix_len_(delegated_len) {

    // check if the prefix is sane
    if (!prefix.isV6()) {
        isc_throw(BadValue, "Invalid Pool6 address boundaries: not IPv6");
    }

    // check if the prefix length is sane
    if (prefix_len == 0 || prefix_len > 128) {
        isc_throw(BadValue, "Invalid prefix length: " << prefix_len);
    }

    if (prefix_len > delegated_len) {
        isc_throw(BadValue, "Delegated length (" << static_cast<int>(delegated_len)
                  << ") must be longer than or equal to prefix length ("
                  << static_cast<int>(prefix_len) << ")");
    }

    if ( ( (type == Lease::TYPE_NA) || (type == Lease::TYPE_TA)) &&
         (delegated_len != 128)) {
        isc_throw(BadValue, "For IA or TA pools, delegated prefix length must"
                  << " be 128.");
    }

    /// @todo: We should probably implement checks against weird addresses
    /// here, like ::, starting with fe80, starting with ff etc. .

    // Let's now calculate the last address in defined pool
    last_ = lastAddrInPrefix(prefix, prefix_len);

    // Let's calculate the theoretical number of leases in this pool.
    // For addresses, we could use addrsInRange(prefix, last_), but it's
    // much faster to do calculations on prefix lengths.
    capacity_ = prefixesInRange(prefix_len, delegated_len);
}

std::string
Pool6::toText() const {
    std::stringstream tmp;
    tmp << "type=" << Lease::typeToText(type_) << ", " << first_
        << "-" << last_ << ", delegated_len="
        << static_cast<int>(prefix_len_);
    return (tmp.str());
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
