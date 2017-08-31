// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/addr_utilities.h>
#include <dhcpsrv/subnet.h>
#include <algorithm>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Function used in calls to std::upper_bound to check
/// if the specified prefix is lower than the first address a pool.
///
/// @return true if prefix is lower than the first address in the pool.
bool
prefixLessThanFirstAddress(const IOAddress& prefix, const PoolPtr& pool) {
    return (prefix < pool->getFirstAddress());
}

/// @brief Function used in calls to std::sort to compare first
/// prefixes of the two pools.
///
/// @param pool1 First pool.
/// @param pool2 Second pool.
///
/// @return true if first prefix of the first pool is smaller than
/// the first address of the second pool.
bool
comparePoolFirstAddress(const PoolPtr& pool1, const PoolPtr& pool2) {
    return (pool1->getFirstAddress() < pool2->getFirstAddress());
};

}

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

    if (!pools.empty()) {
        // Pools are sorted by their first prefixes. For example: 2001::,
        // 2001::db8::, 3000:: etc. If our hint is 2001:db8:5:: we want to
        // find the pool with the longest matching prefix, so: 2001:db8::,
        // rather than 2001::. upper_bound returns the first pool with a prefix
        // that is greater than 2001:db8:5::, i.e. 3000::. To find the longest
        // matching prefix we use decrement operator to go back by one item.
        // If returned iterator points to begin it means that prefixes in all
        // pools are greater than out prefix, and thus there is no match.
        PoolCollection::const_iterator ub =
            std::upper_bound(pools.begin(), pools.end(), hint,
                             prefixLessThanFirstAddress);

        if (ub != pools.begin()) {
            --ub;
            if ((*ub)->inRange(hint)) {
                candidate = *ub;
            }
        }

        // If we don't find anything better, then let's just use the first pool
        if (!candidate && anypool) {
            candidate = *pools.begin();
        }
    }

    // Return a pool or NULL if no match found.
    return (candidate);
}

void
Subnet::addPool(const PoolPtr& pool) {
    // check if the type is valid (and throw if it isn't)
    checkType(pool->getType());

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
                      << pool->getLastAddress() << " does not match"
                      << " the prefix of a subnet: "
                      << prefix_ << "/" << static_cast<int>(prefix_len_)
                      << " to which it is being added");

        }
    }

    bool overlaps = false;
    if (pool->getType() == Lease::TYPE_V4) {
        overlaps = poolOverlaps(Lease::TYPE_V4, pool);

    } else {
        overlaps =
            poolOverlaps(Lease::TYPE_NA, pool) ||
            poolOverlaps(Lease::TYPE_PD, pool) ||
            poolOverlaps(Lease::TYPE_TA, pool);
    }

    if (overlaps) {
        isc_throw(BadValue,"a pool of type "
                  << Lease::typeToText(pool->getType())
                  << ", with the following address range: "
                  << pool->getFirstAddress() << "-"
                  << pool->getLastAddress() << " overlaps with "
                  "an existing pool in the subnet: "
                  << prefix_ << "/" << static_cast<int>(prefix_len_)
                  << " to which it is being added");
    }

    PoolCollection& pools_writable = getPoolsWritable(pool->getType());

    // Add the pool to the appropriate pools collection
    pools_writable.push_back(pool);

    // Sort pools by first address.
    std::sort(pools_writable.begin(), pools_writable.end(),
              comparePoolFirstAddress);
}

void
Subnet::delPools(Lease::Type type) {
    getPoolsWritable(type).clear();
}

bool
Subnet::inPool(Lease::Type type, const isc::asiolink::IOAddress& addr) const {

    // Let's start with checking if it even belongs to that subnet.
    if ((type != Lease::TYPE_PD) && !inRange(addr)) {
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

bool
Subnet::poolOverlaps(const Lease::Type& pool_type, const PoolPtr& pool) const {
    const PoolCollection& pools = getPools(pool_type);

    // If no pools, we don't overlap. Nothing to do.
    if (pools.empty()) {
        return (false);
    }

    // We're going to insert a new pool, likely between two existing pools.
    // So we're going to end up with the following case:
    // |<---- pool1 ---->|    |<-------- pool2 ------>|  |<-- pool3 -->|
    // F1               L1    F2                     L2  F3           L3
    // where pool1 and pool3 are existing pools, pool2 is a pool being
    // inserted and "F"/"L" mark first and last address in the pools
    // respectively. So the following conditions must be fulfilled:
    // F2 > L1 and L2 < F3. Obviously, for any pool: F < L.

    // Search for pool3. We use F2 and upper_bound to find the F3 (upper_bound
    // returns first pool in the sorted container which first address is
    // greater than F2). prefixLessThanPoolAddress with the first argument
    // set to "true" is the custom comparison function for upper_bound, which
    // compares F2 with the first addresses of the existing pools.
    PoolCollection::const_iterator pool3_it =
        std::upper_bound(pools.begin(), pools.end(), pool->getFirstAddress(),
                         prefixLessThanFirstAddress);

    // upper_bound returns a first pool which first address is greater than the
    // address F2. However, it is also possible that there is a pool which first
    // address is equal to F2. Such pool is also in conflict with a new pool.
    // If the returned value is pools.begin() it means that all pools have greater
    // first address than F2, thus none of the pools can have first address equal
    // to F2. Otherwise, we'd need to check them for equality.
    if (pool3_it != pools.begin()) {
        // Go back one pool and check if addresses are equal.
        PoolPtr pool3 = *(pool3_it - 1);
        if (pool3->getFirstAddress() == pool->getFirstAddress()) {
            return (true);
        }
    }

    // If returned value is unequal pools.end() it means that there is a pool3,
    // with F3 > F2.
    if (pool3_it != pools.end()) {
        // Let's store the pointer to this pool.
        PoolPtr pool3 = *pool3_it;
        // F3 must be greater than L2, otherwise pools will overlap.
        if (pool3->getFirstAddress() <= pool->getLastAddress()) {
            return (true);
        }
    }

    // If L2 is ok, we now have to find the pool1. This pool should be
    // right before the pool3 if there is any pool before pool3.
    if (pool3_it != pools.begin()) {
        PoolPtr pool1 = *(pool3_it - 1);
        // F2 must be greater than L1.
        if (pool->getFirstAddress() <= pool1->getLastAddress()) {
            return (true);
        }
    }

    return (false);
}


Subnet6::Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
                 const Triplet<uint32_t>& t1,
                 const Triplet<uint32_t>& t2,
                 const Triplet<uint32_t>& preferred_lifetime,
                 const Triplet<uint32_t>& valid_lifetime,
                 const SubnetID id)
    :Subnet(prefix, length, t1, t2, valid_lifetime, RelayInfo(IOAddress("::")), id),
     preferred_(preferred_lifetime), rapid_commit_(false) {
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

data::ElementPtr
Subnet::toElement() const {
    // Prepare the map
    ElementPtr map = Element::createMap();

    // Set subnet id
    SubnetID id = getID();
    map->set("id", Element::create(static_cast<long long>(id)));

    // Set relay info
    const Subnet::RelayInfo& relay_info = getRelayInfo();
    ElementPtr relay = Element::createMap();
    relay->set("ip-address", Element::create(relay_info.addr_.toText()));
    map->set("relay", relay);

    // Set subnet
    map->set("subnet", Element::create(toText()));

    // Set interface
    const std::string& iface = getIface();
    if (!iface.empty()) {
        map->set("interface", Element::create(iface));
    }

    // Set renew-timer
    map->set("renew-timer",
             Element::create(static_cast<long long>
                                 (getT1().get())));
    // Set rebind-timer
    map->set("rebind-timer",
             Element::create(static_cast<long long>
                                 (getT2().get())));
    // Set valid-lifetime
    map->set("valid-lifetime",
             Element::create(static_cast<long long>
                                 (getValid().get())));

    // Set reservation mode
    Subnet::HRMode hrmode = getHostReservationMode();
    std::string mode;
    switch (hrmode) {
    case Subnet::HR_DISABLED:
        mode = "disabled";
        break;
    case Subnet::HR_OUT_OF_POOL:
        mode = "out-of-pool";
        break;
    case Subnet::HR_ALL:
        mode = "all";
        break;
    default:
        isc_throw(ToElementError,
                  "invalid host reservation mode: " << hrmode);
    }
    map->set("reservation-mode", Element::create(mode));

    // Set client-class
    const ClientClasses& cclasses = getClientClasses();
    if (cclasses.size() > 1) {
        isc_throw(ToElementError, "client-class has too many items: "
                  << cclasses.size());
    } else if (!cclasses.empty()) {
        map->set("client-class", Element::create(*cclasses.cbegin()));
    }

    // Set options
    ConstCfgOptionPtr opts = getCfgOption();
    map->set("option-data", opts->toElement());

    return (map);
}

data::ElementPtr
Subnet4::toElement() const {
    // Prepare the map
    ElementPtr map = Subnet::toElement();

    // Set match-client-id
    map->set("match-client-id", Element::create(getMatchClientId()));

    // Set DHCP4o6
    const Cfg4o6& d4o6 = get4o6();
    isc::data::merge(map, d4o6.toElement());

    // Set next-server
    map->set("next-server", Element::create(getSiaddr().toText()));

    // Set pools
    const PoolCollection& pools = getPools(Lease::TYPE_V4);
    ElementPtr pool_list = Element::createList();
    for (PoolCollection::const_iterator pool = pools.cbegin();
         pool != pools.cend(); ++pool) {
        // Add the elementized pool to the list
        pool_list->add((*pool)->toElement());
    }
    map->set("pools", pool_list);

    return (map);
}

data::ElementPtr
Subnet6::toElement() const {
    // Prepare the map
    ElementPtr map = Subnet::toElement();

    // Set interface-id
    const OptionPtr& ifaceid = getInterfaceId();
    if (ifaceid) {
        std::vector<uint8_t> bin = ifaceid->getData();
        std::string ifid;
        ifid.resize(bin.size());
        if (!bin.empty()) {
            std::memcpy(&ifid[0], &bin[0], bin.size());
        }
        map->set("interface-id", Element::create(ifid));
    } 

    // Set preferred-lifetime
    map->set("preferred-lifetime",
             Element::create(static_cast<long long>
                             (getPreferred().get())));
    // Set rapid-commit
    bool rapid_commit = getRapidCommit();
    map->set("rapid-commit", Element::create(rapid_commit));

    // Set pools
    const PoolCollection& pools = getPools(Lease::TYPE_NA);
    ElementPtr pool_list = Element::createList();
    for (PoolCollection::const_iterator pool = pools.cbegin();
         pool != pools.cend(); ++pool) {
        // Prepare the map for a pool (@todo move this code to pool.cc)
        ElementPtr pool_map = Element::createMap();
        // Set pool
        const IOAddress& first = (*pool)->getFirstAddress();
        const IOAddress& last = (*pool)->getLastAddress();
        std::string range = first.toText() + "-" + last.toText();
        // Try to output a prefix (vs a range)
        int prefix_len = prefixLengthFromRange(first, last);
        if (prefix_len >= 0) {
            std::ostringstream oss;
            oss << first.toText() << "/" << prefix_len;
            range = oss.str();
        }
        pool_map->set("pool", Element::create(range));
        // Set user-context
        ConstElementPtr context = (*pool)->getContext();
        if (!isNull(context)) {
            pool_map->set("user-context", context);
        }
        // Set pool options
        ConstCfgOptionPtr opts = (*pool)->getCfgOption();
        pool_map->set("option-data", opts->toElement());
        // Push on the pool list
        pool_list->add(pool_map);
    }
    map->set("pools", pool_list);
    // Set pd-pools
    const PoolCollection& pdpools = getPools(Lease::TYPE_PD);
    ElementPtr pdpool_list = Element::createList();
    for (PoolCollection::const_iterator pool = pdpools.cbegin();
         pool != pdpools.cend(); ++pool) {
        // Get it as a Pool6 (@todo move this code to pool.cc)
        const Pool6* pdpool = dynamic_cast<Pool6*>(pool->get());
        if (!pdpool) {
            isc_throw(ToElementError, "invalid pd-pool pointer");
        }
        // Prepare the map for a pd-pool
        ElementPtr pool_map = Element::createMap();
        // Set prefix
        const IOAddress& prefix = pdpool->getFirstAddress();
        pool_map->set("prefix", Element::create(prefix.toText()));
        // Set prefix-len (get it from min - max)
        const IOAddress& last = pdpool->getLastAddress();
        int prefix_len = prefixLengthFromRange(prefix, last);
        if (prefix_len < 0) {
            // The pool is bad: give up
            isc_throw(ToElementError, "invalid prefix range "
                      << prefix.toText() << "-" << last.toText());
        }
        pool_map->set("prefix-len", Element::create(prefix_len));
        // Set delegated-len
        uint8_t len = pdpool->getLength();
        pool_map->set("delegated-len",
                      Element::create(static_cast<int>(len)));

        // Set excluded prefix
        const Option6PDExcludePtr& xopt =
            pdpool->getPrefixExcludeOption();
        if (xopt) {
            const IOAddress& xprefix =
                xopt->getExcludedPrefix(prefix, len);
            pool_map->set("excluded-prefix",
                          Element::create(xprefix.toText()));
            uint8_t xlen = xopt->getExcludedPrefixLength();
            pool_map->set("excluded-prefix-len",
                          Element::create(static_cast<int>(xlen)));
        }

        // Set user-context
        ConstElementPtr context = pdpool->getContext();
        if (!isNull(context)) {
            pool_map->set("user-context", context);
        }
        // Set pool options
        ConstCfgOptionPtr opts = pdpool->getCfgOption();
        pool_map->set("option-data", opts->toElement());
        // Push on the pool list
        pdpool_list->add(pool_map);
    }
    map->set("pd-pools", pdpool_list);

    return (map);
}


} // end of isc::dhcp namespace
} // end of isc namespace
