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

#include <util/addr_utilities.h>
#include <asiolink/io_address.h>
#include <dhcp/cfgmgr.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Pool::Pool(const isc::asiolink::IOAddress& first,
           const isc::asiolink::IOAddress& last,
           const Triplet<uint32_t>& t1,
           const Triplet<uint32_t>& t2,
           const Triplet<uint32_t>& valid_lifetime)
    :id_(getNextID()), first_(first), last_(last), t1_(t1), t2_(t2), valid_(valid_lifetime) {

}

bool Pool::inRange(const isc::asiolink::IOAddress& addr) {
    return ( first_.smallerEqual(addr) && addr.smallerEqual(last_) );
}

Pool6::Pool6(Pool6Type type, const isc::asiolink::IOAddress& first,
             const isc::asiolink::IOAddress& last,
             const Triplet<uint32_t>& t1,
             const Triplet<uint32_t>& t2,
             const Triplet<uint32_t>& preferred_lifetime,
             const Triplet<uint32_t>& valid_lifetime)
    :Pool(first, last, t1, t2, valid_lifetime),
     type_(type), prefix_len_(0), preferred_(preferred_lifetime) {

    if (last < first) {
        isc_throw(BadValue, "Upper boundary is smaller than lower boundary.");
        // This check is strict. If we decide that it is too strict,
        // we need to comment it and uncomment lines below.

        // first_  = last;
        // last_ = first;
    }

    if (first.getFamily() != AF_INET6 || last.getFamily() != AF_INET6) {
        isc_throw(BadValue, "Invalid Pool6 address boundaries: not IPv6");
    }

    // TYPE_PD is not supported by this constructor. first-last style
    // parameters are for IA and TA only. There is another dedicated
    // constructor for that (it uses prefix/length)
    if ((type != TYPE_IA) && (type != TYPE_TA)) {
        isc_throw(BadValue, "Invalid Pool6 type specified");
    }
}

Pool6::Pool6(Pool6Type type, const isc::asiolink::IOAddress& addr,
             uint8_t prefix_len,
             const Triplet<uint32_t>& t1,
             const Triplet<uint32_t>& t2,
             const Triplet<uint32_t>& preferred_lifetime,
             const Triplet<uint32_t>& valid_lifetime)
    :Pool(addr, IOAddress("::"), t1, t2, valid_lifetime),
     type_(type), prefix_len_(prefix_len), preferred_(preferred_lifetime) {

    if (prefix_len == 0 || prefix_len > 128) {
        isc_throw(BadValue, "Invalid prefix length");
    }

    if (addr.getFamily() != AF_INET6) {
        isc_throw(BadValue, "Invalid Pool6 address boundaries: not IPv6");
    }

    // Let's now calculate the last address in defined pool
    last_ = lastAddrInPrefix(addr, prefix_len);
}


Subnet::Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len)
    :id_(getNextID()), prefix_(prefix), len_(len) {
    if ( (prefix.getFamily() == AF_INET6 && len > 128) ||
         (prefix.getFamily() == AF_INET && len > 32) ) {
        isc_throw(BadValue, "Invalid prefix length specified for subnet: " << len);
    }
}

bool Subnet::inRange(const isc::asiolink::IOAddress& addr) {
    IOAddress first = firstAddrInPrefix(prefix_, len_);
    IOAddress last = lastAddrInPrefix(prefix_, len_);

    return ( (first <= addr) && (addr <= last) );
}

Subnet6::Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length)
    :Subnet(prefix, length) {
    if (prefix.getFamily() != AF_INET6) {
        isc_throw(BadValue, "Invalid prefix " << prefix.toText() << " specified in subnet6");
    }
}




}; // end of isc::dhcp namespace
}; // end of isc namespace
