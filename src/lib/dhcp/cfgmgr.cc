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

#include <dhcp/addr_utilities.h>
#include <asiolink/io_address.h>
#include <dhcp/cfgmgr.h>

using namespace isc::asiolink;
using namespace isc::util;

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

Subnet::Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
               const Triplet<uint32_t>& t1,
               const Triplet<uint32_t>& t2,
               const Triplet<uint32_t>& valid_lifetime)
    :id_(getNextID()), prefix_(prefix), prefix_len_(len), t1_(t1),
     t2_(t2), valid_(valid_lifetime) {
    if ( (prefix.getFamily() == AF_INET6 && len > 128) ||
         (prefix.getFamily() == AF_INET && len > 32) ) {
        isc_throw(BadValue, "Invalid prefix length specified for subnet: " << len);
    }
}

bool Subnet::inRange(const isc::asiolink::IOAddress& addr) const {
    IOAddress first = firstAddrInPrefix(prefix_, prefix_len_);
    IOAddress last = lastAddrInPrefix(prefix_, prefix_len_);

    return ((first <= addr) && (addr <= last));
}

Subnet6::Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
                 const Triplet<uint32_t>& t1,
                 const Triplet<uint32_t>& t2,
                 const Triplet<uint32_t>& preferred_lifetime,
                 const Triplet<uint32_t>& valid_lifetime)
    :Subnet(prefix, length, t1, t2, valid_lifetime),
     preferred_(preferred_lifetime){
    if (prefix.getFamily() != AF_INET6) {
        isc_throw(BadValue, "Non IPv6 prefix " << prefix.toText()
                  << " specified in subnet6");
    }
}

void Subnet6::addPool6(const Pool6Ptr& pool) {
    IOAddress first_addr = pool->getFirstAddress();
    IOAddress last_addr = pool->getLastAddress();

    if (!inRange(first_addr) || !inRange(last_addr)) {
        isc_throw(BadValue, "Pool6 (" << first_addr.toText() << "-" << last_addr.toText()
                  << " does not belong in this (" << prefix_ << "/" << prefix_len_
                  << ") subnet6");
    }

    /// @todo: Check that pools do not overlap

    pools_.push_back(pool);
}

Pool6Ptr Subnet6::getPool6(const isc::asiolink::IOAddress& hint /* = IOAddress("::")*/ ) {
    Pool6Ptr candidate;
    for (Pool6Collection::iterator pool = pools_.begin(); pool != pools_.end(); ++pool) {

        // if we won't find anything better, then let's just use the first pool
        if (!candidate) {
            candidate = *pool;
        }

        // if the client provided a pool and there's a pool that hint is valid in,
        // then let's use that pool
        if ((*pool)->inRange(hint)) {
            return (*pool);
        }
    }
    return (candidate);
}


CfgMgr&
CfgMgr::instance() {
    static CfgMgr cfg_mgr;
    return (cfg_mgr);
}

Subnet6Ptr
CfgMgr::getSubnet6(const isc::asiolink::IOAddress& hint) {

    // If there's only one subnet configured, let's just use it
    // The idea is to keep small deployments easy. In a small network - one
    // router that also runs DHCPv6 server. Users specifies a single pool and
    // expects it to just work. Without this, the server would complain that it
    // doesn't have IP address on its interfaces that matches that
    // configuration. Such requirement makes sense in IPv4, but not in IPv6.
    // The server does not need to have a global address (using just link-local
    // is ok for DHCPv6 server) from the pool it serves.
    if (subnets6_.size() == 1) {
        return (subnets6_[0]);
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet6Collection::iterator subnet = subnets6_.begin();
         subnet != subnets6_.end(); ++subnet) {
        if ((*subnet)->inRange(hint)) {
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    return (Subnet6Ptr());
}

Subnet6Ptr CfgMgr::getSubnet6(OptionPtr /*interfaceId*/) {
    /// @todo: Implement get subnet6 by interface-id (for relayed traffic)
    isc_throw(NotImplemented, "Relayed DHCPv6 traffic is not supported yet.");
}

void CfgMgr::addSubnet6(const Subnet6Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    subnets6_.push_back(subnet);
}

CfgMgr::CfgMgr() {
}

CfgMgr::~CfgMgr() {
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
