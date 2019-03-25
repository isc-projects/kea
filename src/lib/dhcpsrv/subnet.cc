// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <asiolink/addr_utilities.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;

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
               const SubnetID id)
    : id_(id == 0 ? generateNextID() : id), prefix_(prefix),
      prefix_len_(len),
      last_allocated_ia_(lastAddrInPrefix(prefix, len)),
      last_allocated_ta_(lastAddrInPrefix(prefix, len)),
      last_allocated_pd_(lastAddrInPrefix(prefix, len)),
      last_allocated_time_(),
      iface_(),
      shared_network_name_() {
    if ((prefix.isV6() && len > 128) ||
        (prefix.isV4() && len > 32)) {
        isc_throw(BadValue,
                  "Invalid prefix length specified for subnet: " << len);
    }

    // Initialize timestamps for each lease type to negative infinity.
    last_allocated_time_[Lease::TYPE_V4] = boost::posix_time::neg_infin;
    last_allocated_time_[Lease::TYPE_NA] = boost::posix_time::neg_infin;
    last_allocated_time_[Lease::TYPE_TA] = boost::posix_time::neg_infin;
    last_allocated_time_[Lease::TYPE_PD] = boost::posix_time::neg_infin;
}

bool
Subnet::inRange(const isc::asiolink::IOAddress& addr) const {
    IOAddress first = firstAddrInPrefix(prefix_, prefix_len_);
    IOAddress last = lastAddrInPrefix(prefix_, prefix_len_);

    return ((first <= addr) && (addr <= last));
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

boost::posix_time::ptime
Subnet::getLastAllocatedTime(const Lease::Type& lease_type) const {
    auto t = last_allocated_time_.find(lease_type);
    if (t != last_allocated_time_.end()) {
        return (t->second);
    }

    // This shouldn't happen, because we have initialized the structure
    // for all lease types.
    return (boost::posix_time::neg_infin);
}


void Subnet::setLastAllocated(Lease::Type type,
                              const isc::asiolink::IOAddress& addr) {

    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        last_allocated_ia_ = addr;
        break;
    case Lease::TYPE_TA:
        last_allocated_ta_ = addr;
        break;
    case Lease::TYPE_PD:
        last_allocated_pd_ = addr;
        break;
    default:
        isc_throw(BadValue, "Pool type " << type << " not supported");
    }

    // Update the timestamp of last allocation.
    last_allocated_time_[type] = boost::posix_time::microsec_clock::universal_time();
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
Subnet::getPoolCapacity(Lease::Type type,
                        const ClientClasses& client_classes) const {
    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return sumPoolCapacity(pools_, client_classes);
    case Lease::TYPE_TA:
        return sumPoolCapacity(pools_ta_, client_classes);
    case Lease::TYPE_PD:
        return sumPoolCapacity(pools_pd_, client_classes);
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

uint64_t
Subnet::sumPoolCapacity(const PoolCollection& pools,
                        const ClientClasses& client_classes) const {
    uint64_t sum = 0;
    for (PoolCollection::const_iterator p = pools.begin(); p != pools.end(); ++p) {
        if (!(*p)->clientSupported(client_classes)) {
            continue;
        }
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

std::pair<IOAddress, uint8_t>
Subnet::parsePrefixCommon(const std::string& prefix) {
    auto pos = prefix.find('/');
    if ((pos == std::string::npos) ||
        (pos == prefix.size() - 1) ||
        (pos == 0)) {
        isc_throw(BadValue, "unable to parse invalid prefix " << prefix);
    }

    try {
        IOAddress address(prefix.substr(0, pos));
        int length = boost::lexical_cast<int>(prefix.substr(pos + 1));
        return (std::make_pair(address, static_cast<int>(length)));

    } catch (...) {
        isc_throw(BadValue, "unable to parse invalid prefix " << prefix);
    }
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
    : Subnet(prefix, length, id), Network4() {
    if (!prefix.isV4()) {
        isc_throw(BadValue, "Non IPv4 prefix " << prefix.toText()
                  << " specified in subnet4");
    }

    // Timers.
    setT1(t1);
    setT2(t2);
    setValid(valid_lifetime);
}

Subnet4Ptr
Subnet4::getNextSubnet(const Subnet4Ptr& first_subnet) const {
    SharedNetwork4Ptr network;
    getSharedNetwork(network);
    if (network) {
        return (network->getNextSubnet(first_subnet, getID()));
    }

    return (Subnet4Ptr());
}

Subnet4Ptr
Subnet4::getNextSubnet(const Subnet4Ptr& first_subnet,
                       const ClientClasses& client_classes) const {
    SharedNetwork4Ptr network;
    getSharedNetwork(network);
    // We can only get next subnet if shared network has been defined for
    // the current subnet.
    if (network) {
        Subnet4Ptr subnet;
        do {
            // Use subnet identifier of this subnet if this is the first
            // time we're calling getNextSubnet. Otherwise, use the
            // subnet id of the previously returned subnet.
            SubnetID subnet_id = subnet ? subnet->getID() : getID();
            subnet = network->getNextSubnet(first_subnet, subnet_id);
            // If client classes match the subnet, return it. Otherwise,
            // try another subnet.
            if (subnet && subnet->clientSupported(client_classes)) {
                return (subnet);
            }
        } while (subnet);
    }

    // No subnet found.
    return (Subnet4Ptr());
}


bool
Subnet4::clientSupported(const isc::dhcp::ClientClasses& client_classes) const {
    NetworkPtr network;
    getSharedNetwork(network);
    if (network && !network->clientSupported(client_classes)) {
        return (false);
    }

    return (Network4::clientSupported(client_classes));
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

const PoolPtr Subnet::getPool(Lease::Type type,
                              const ClientClasses& client_classes,
                              const isc::asiolink::IOAddress& hint) const {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    const PoolCollection& pools = getPools(type);

    PoolPtr candidate;

    if (!pools.empty()) {
        PoolCollection::const_iterator ub =
            std::upper_bound(pools.begin(), pools.end(), hint,
                             prefixLessThanFirstAddress);

        if (ub != pools.begin()) {
            --ub;
            if ((*ub)->inRange(hint) &&
                (*ub)->clientSupported(client_classes)) {
                candidate = *ub;
            }
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
Subnet::inPool(Lease::Type type,
               const isc::asiolink::IOAddress& addr,
               const ClientClasses& client_classes) const {

    // Let's start with checking if it even belongs to that subnet.
    if ((type != Lease::TYPE_PD) && !inRange(addr)) {
        return (false);
    }

    const PoolCollection& pools = getPools(type);

    for (PoolCollection::const_iterator pool = pools.begin();
         pool != pools.end(); ++pool) {
        if (!(*pool)->clientSupported(client_classes)) {
            continue;
        }
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
    : Subnet(prefix, length, id), Network6() {
    if (!prefix.isV6()) {
        isc_throw(BadValue, "Non IPv6 prefix " << prefix
                  << " specified in subnet6");
    }

    // Timers.
    setT1(t1);
    setT2(t2);
    setPreferred(preferred_lifetime);
    setValid(valid_lifetime);
}

void Subnet6::checkType(Lease::Type type) const {
    if ( (type != Lease::TYPE_NA) && (type != Lease::TYPE_TA) &&
         (type != Lease::TYPE_PD)) {
        isc_throw(BadValue, "Invalid Pool type: " << Lease::typeToText(type)
                  << "(" << static_cast<int>(type)
                  << "), must be TYPE_NA, TYPE_TA or TYPE_PD for Subnet6");
    }
}

Subnet6Ptr
Subnet6::getNextSubnet(const Subnet6Ptr& first_subnet) const {
    SharedNetwork6Ptr network;
    getSharedNetwork(network);
    if (network) {
        return (network->getNextSubnet(first_subnet, getID()));
    }

    return (Subnet6Ptr());
}

Subnet6Ptr
Subnet6::getNextSubnet(const Subnet6Ptr& first_subnet,
                       const ClientClasses& client_classes) const {
    SharedNetwork6Ptr network;
    getSharedNetwork(network);
    // We can only get next subnet if shared network has been defined for
    // the current subnet.
    if (network) {
        Subnet6Ptr subnet;
        do {
            // Use subnet identifier of this subnet if this is the first
            // time we're calling getNextSubnet. Otherwise, use the
            // subnet id of the previously returned subnet.
            SubnetID subnet_id = subnet ? subnet->getID() : getID();
            subnet = network->getNextSubnet(first_subnet, subnet_id);
            // If client classes match the subnet, return it. Otherwise,
            // try another subnet.
            if (subnet && subnet->clientSupported(client_classes)) {
                return (subnet);
            }
        } while (subnet);
    }

    // No subnet found.
    return (Subnet6Ptr());
}

bool
Subnet6::clientSupported(const isc::dhcp::ClientClasses& client_classes) const {
    NetworkPtr network;
    getSharedNetwork(network);
    if (network && !network->clientSupported(client_classes)) {
        return (false);
    }

    return (Network6::clientSupported(client_classes));
}

data::ElementPtr
Subnet::toElement() const {
    ElementPtr map = Element::createMap();

    // Add user-context
    contextToElement(map);

    // Set subnet id
    SubnetID id = getID();
    map->set("id", Element::create(static_cast<long long>(id)));

    // Set subnet
    map->set("subnet", Element::create(toText()));

    return (map);
}

data::ElementPtr
Subnet4::toElement() const {
    // Prepare the map
    ElementPtr map = Subnet::toElement();
    ElementPtr network_map = Network4::toElement();

    merge(map, network_map);

    // Set DHCP4o6
    const Cfg4o6& d4o6 = get4o6();
    isc::data::merge(map, d4o6.toElement());

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

std::pair<IOAddress, uint8_t>
Subnet4::parsePrefix(const std::string& prefix) {
    std::pair<IOAddress, uint8_t> parsed = Subnet::parsePrefixCommon(prefix);
    if (!parsed.first.isV4() || parsed.first.isV4Zero() ||
        (parsed.second > 32) || (parsed.second == 0)) {
        isc_throw(BadValue, "unable to parse invalid IPv4 prefix " << prefix);
    }
    return (parsed);
}

data::ElementPtr
Subnet6::toElement() const {
    // Prepare the map
    ElementPtr map = Subnet::toElement();
    ElementPtr network_map = Network6::toElement();

    merge(map, network_map);

    // Set pools
    const PoolCollection& pools = getPools(Lease::TYPE_NA);
    ElementPtr pool_list = Element::createList();
    for (PoolCollection::const_iterator pool = pools.cbegin();
         pool != pools.cend(); ++pool) {
        // Add the elementized pool to the list
        pool_list->add((*pool)->toElement());
    }
    map->set("pools", pool_list);

    // Set pd-pools
    const PoolCollection& pdpools = getPools(Lease::TYPE_PD);
    ElementPtr pdpool_list = Element::createList();
    for (PoolCollection::const_iterator pool = pdpools.cbegin();
         pool != pdpools.cend(); ++pool) {
        // Add the elementized pool to the list
        pdpool_list->add((*pool)->toElement());
    }
    map->set("pd-pools", pdpool_list);

    return (map);
}

std::pair<IOAddress, uint8_t>
Subnet6::parsePrefix(const std::string& prefix) {
    std::pair<IOAddress, uint8_t> parsed = Subnet::parsePrefixCommon(prefix);
    if (!parsed.first.isV6() || parsed.first.isV6Zero() ||
        (parsed.second > 128) || (parsed.second == 0)) {
        isc_throw(BadValue, "unable to parse invalid IPv6 prefix " << prefix);
    }
    return (parsed);
}


} // end of isc::dhcp namespace
} // end of isc namespace
