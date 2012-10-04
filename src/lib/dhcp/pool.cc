// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/addr_utilities.h>
#include <dhcp/pool.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

Pool::Pool(const isc::asiolink::IOAddress& first,
           const isc::asiolink::IOAddress& last)
    :id_(getNextID()), first_(first), last_(last) {
}

bool Pool::inRange(const isc::asiolink::IOAddress& addr) const {
    return (first_.smallerEqual(addr) && addr.smallerEqual(last_));
}

Pool6::Pool6(Pool6Type type, const isc::asiolink::IOAddress& first,
             const isc::asiolink::IOAddress& last)
    :Pool(first, last), type_(type), prefix_len_(0) {

    // check if specified address boundaries are sane
    if (first.getFamily() != AF_INET6 || last.getFamily() != AF_INET6) {
        isc_throw(BadValue, "Invalid Pool6 address boundaries: not IPv6");
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
    if ((type != TYPE_IA) && (type != TYPE_TA)) {
        isc_throw(BadValue, "Invalid Pool6 type specified");
    }
}

Pool6::Pool6(Pool6Type type, const isc::asiolink::IOAddress& prefix,
             uint8_t prefix_len)
    :Pool(prefix, IOAddress("::")),
     type_(type), prefix_len_(prefix_len) {

    // check if the prefix is sane
    if (prefix.getFamily() != AF_INET6) {
        isc_throw(BadValue, "Invalid Pool6 address boundaries: not IPv6");
    }

    // check if the prefix length is sane
    if (prefix_len == 0 || prefix_len > 128) {
        isc_throw(BadValue, "Invalid prefix length");
    }

    /// @todo: We should probably implement checks against weird addresses
    /// here, like ::, starting with fe80, starting with ff etc. .

    // Let's now calculate the last address in defined pool
    last_ = lastAddrInPrefix(prefix, prefix_len);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
