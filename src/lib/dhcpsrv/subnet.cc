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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/addr_utilities.h>
#include <dhcpsrv/subnet.h>

#include <sstream>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

// This is an initial value of subnet-id. See comments in subnet.h for details.
SubnetID Subnet::static_id_ = 1;

Subnet::Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
               const Triplet<uint32_t>& t1,
               const Triplet<uint32_t>& t2,
               const Triplet<uint32_t>& valid_lifetime,
               const isc::dhcp::Subnet::RelayInfo& relay,
               const SubnetID id)
    :id_(id == 0 ? generateNextID() : id), prefix_(prefix), prefix_len_(len),
     t1_(t1), t2_(t2), valid_(valid_lifetime),
     last_allocated_ia_(lastAddrInPrefix(prefix, len)),
     last_allocated_ta_(lastAddrInPrefix(prefix, len)),
     last_allocated_pd_(lastAddrInPrefix(prefix, len)), relay_(relay),
     host_reservation_mode_(HR_ALL), cfg_option_(new CfgOption())
      {
    if ((prefix.isV6() && len > 128) ||
        (prefix.isV4() && len > 32)) {
        isc_throw(BadValue,
                  "Invalid prefix length specified for subnet: " << len);
    }
}

Subnet::RelayInfo::RelayInfo(const isc::asiolink::IOAddress& addr)
    :addr_(addr) {
}

bool
Subnet::inRange(const isc::asiolink::IOAddress& addr) const {
    IOAddress first = firstAddrInPrefix(prefix_, prefix_len_);
    IOAddress last = lastAddrInPrefix(prefix_, prefix_len_);

    return ((first <= addr) && (addr <= last));
}

void
Subnet::setRelayInfo(const isc::dhcp::Subnet::RelayInfo& relay) {
    relay_ = relay;
}

bool
Subnet::clientSupported(const isc::dhcp::ClientClasses& classes) const {
    if (white_list_.empty()) {
        return (true); // There is no class defined for this subnet, so we do
                       // support everyone.
    }

    for (ClientClasses::const_iterator it = white_list_.begin();
         it != white_list_.end(); ++it) {
        if (classes.contains(*it)) {
            return (true);
        }
    }

    return (false);
}

void
Subnet::allowClientClass(const isc::dhcp::ClientClass& class_name) {
    white_list_.insert(class_name);
}

isc::asiolink::IOAddress Subnet::getLastAllocated(Lease::Type type) const {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return last_allocated_ia_;
    case Lease::TYPE_TA:
        return last_allocated_ta_;
    case Lease::TYPE_PD:
        return last_allocated_pd_;
    default:
        isc_throw(BadValue, "Pool type " << type << " not supported");
    }
}

void Subnet::setLastAllocated(Lease::Type type,
                              const isc::asiolink::IOAddress& addr) {

    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        last_allocated_ia_ = addr;
        return;
    case Lease::TYPE_TA:
        last_allocated_ta_ = addr;
        return;
    case Lease::TYPE_PD:
        last_allocated_pd_ = addr;
        return;
    default:
        isc_throw(BadValue, "Pool type " << type << " not supported");
    }
}

std::string
Subnet::toText() const {
    std::stringstream tmp;
    tmp << prefix_ << "/" << static_cast<unsigned int>(prefix_len_);
    return (tmp.str());
}

uint64_t
Subnet::getPoolCapacity(Lease::Type type) const {
    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return sumPoolCapacity(pools_);
    case Lease::TYPE_TA:
        return sumPoolCapacity(pools_ta_);
    case Lease::TYPE_PD:
        return sumPoolCapacity(pools_pd_);
    default:
        isc_throw(BadValue, "Unsupported pool type: "
                  << static_cast<int>(type));
    }
}

uint64_t
Subnet::sumPoolCapacity(const PoolCollection& pools) const {
    uint64_t sum = 0;
    for (PoolCollection::const_iterator p = pools.begin(); p != pools.end(); ++p) {
        uint64_t x = (*p)->getCapacity();

        // Check if we can add it. If sum + x > uint64::max, then we would have
        // overflown if we tried to add it.
        if (x > std::numeric_limits<uint64_t>::max() - sum) {
            return (std::numeric_limits<uint64_t>::max());
        }

        sum += x;
    }

    return (sum);
}

void Subnet4::checkType(Lease::Type type) const {
    if (type != Lease::TYPE_V4) {
        isc_throw(BadValue, "Only TYPE_V4 is allowed for Subnet4");
    }
}

Subnet4::Subnet4(const isc::asiolink::IOAddress& prefix, uint8_t length,
                 const Triplet<uint32_t>& t1,
                 const Triplet<uint32_t>& t2,
                 const Triplet<uint32_t>& valid_lifetime,
                 const SubnetID id)
    : Subnet(prefix, length, t1, t2, valid_lifetime, RelayInfo(IOAddress("0.0.0.0")), id),
      siaddr_(IOAddress("0.0.0.0")), match_client_id_(true) {
    if (!prefix.isV4()) {
        isc_throw(BadValue, "Non IPv4 prefix " << prefix.toText()
                  << " specified in subnet4");
    }
}

void Subnet4::setSiaddr(const isc::asiolink::IOAddress& siaddr) {
    if (!siaddr.isV4()) {
        isc_throw(BadValue, "Can't set siaddr to non-IPv4 address "
                  << siaddr);
    }
    siaddr_ = siaddr;
}

isc::asiolink::IOAddress Subnet4::getSiaddr() const {
    return (siaddr_);
}

const PoolCollection& Subnet::getPools(Lease::Type type) const {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return (pools_);
    case Lease::TYPE_TA:
        return (pools_ta_);
    case Lease::TYPE_PD:
        return (pools_pd_);
    default:
        isc_throw(BadValue, "Unsupported pool type: "
                  << static_cast<int>(type));
    }
}

PoolCollection& Subnet::getPoolsWritable(Lease::Type type) {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return (pools_);
    case Lease::TYPE_TA:
        return (pools_ta_);
    case Lease::TYPE_PD:
        return (pools_pd_);
    default:
        isc_throw(BadValue, "Invalid pool type specified: "
                  << static_cast<int>(type));
    }
}

const PoolPtr Subnet::getPool(Lease::Type type, const isc::asiolink::IOAddress& hint,
                        bool anypool /* true */) const {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    const PoolCollection& pools = getPools(type);

    PoolPtr candidate;
    for (PoolCollection::const_iterator pool = pools.begin();
         pool != pools.end(); ++pool) {

        // if we won't find anything better, then let's just use the first pool
        if (anypool && !candidate) {
            candidate = *pool;
        }

        // if the client provided a pool and there's a pool that hint is valid
        // in, then let's use that pool
        if ((*pool)->inRange(hint)) {
            return (*pool);
        }
    }
    return (candidate);
}

void
Subnet::addPool(const PoolPtr& pool) {
    // Check that the pool is in range with a subnet only if this is
    // not a pool of IPv6 prefixes. The IPv6 prefixes delegated for
    // the particular subnet don't need to match the prefix of the
    // subnet.
    if (pool->getType() != Lease::TYPE_PD) {
        if (!inRange(pool->getFirstAddress()) || !inRange(pool->getLastAddress())) {
            isc_throw(BadValue, "a pool of type "
                      << Lease::typeToText(pool->getType())
                      << ", with the following address range: "
                      << pool->getFirstAddress() << "-"
                      << pool->getLastAddress() << " does not match "
                      << " the prefix of a subnet: "
                      << prefix_ << "/" << static_cast<int>(prefix_len_)
                      << " to which it is being added");
        }
    }

    /// @todo: Check that pools do not overlap

    // check if the type is valid (and throw if it isn't)
    checkType(pool->getType());

    // Add the pool to the appropriate pools collection
    getPoolsWritable(pool->getType()).push_back(pool);
}

void
Subnet::delPools(Lease::Type type) {
    getPoolsWritable(type).clear();
}

void
Subnet::setIface(const std::string& iface_name) {
    iface_ = iface_name;
}

std::string
Subnet::getIface() const {
    return (iface_);
}

bool
Subnet::inPool(Lease::Type type, const isc::asiolink::IOAddress& addr) const {

    // Let's start with checking if it even belongs to that subnet.
    if (!inRange(addr)) {
        return (false);
    }

    const PoolCollection& pools = getPools(type);

    for (PoolCollection::const_iterator pool = pools.begin();
         pool != pools.end(); ++pool) {
        if ((*pool)->inRange(addr)) {
            return (true);
        }
    }
    // There's no pool that address belongs to
    return (false);
}

Subnet6::Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
                 const Triplet<uint32_t>& t1,
                 const Triplet<uint32_t>& t2,
                 const Triplet<uint32_t>& preferred_lifetime,
                 const Triplet<uint32_t>& valid_lifetime,
                 const SubnetID id)
:Subnet(prefix, length, t1, t2, valid_lifetime, RelayInfo(IOAddress("::")), id),
     preferred_(preferred_lifetime) {
    if (!prefix.isV6()) {
        isc_throw(BadValue, "Non IPv6 prefix " << prefix
                  << " specified in subnet6");
    }
}

void Subnet6::checkType(Lease::Type type) const {
    if ( (type != Lease::TYPE_NA) && (type != Lease::TYPE_TA) &&
         (type != Lease::TYPE_PD)) {
        isc_throw(BadValue, "Invalid Pool type: " << Lease::typeToText(type)
                  << "(" << static_cast<int>(type)
                  << "), must be TYPE_NA, TYPE_TA or TYPE_PD for Subnet6");
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
