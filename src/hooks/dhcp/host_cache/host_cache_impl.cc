// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <host_cache.h>
#include <host_cache_impl.h>

#include <boost/foreach.hpp>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace host_cache {

HostCacheImpl::HostCacheImpl() : maximum_(0) {
}

HostCacheImpl::~HostCacheImpl() {
}

bool
HostCacheImpl::insertResv6(const HostPtr& host) {
    if (!host || (host->getIPv6SubnetID() == SUBNET_ID_UNUSED)) {
        return (true);
    }
    const IPv6ResrvRange& resrv = host->getIPv6Reservations();
    if (std::distance(resrv.first, resrv.second) == 0) {
        return (true);
    }
    // For each IPv6 reservation, insert (address, host) tuple.
    BOOST_FOREACH(auto const& it, resrv) {
        auto ret = cache6_.insert(HostResrv6Tuple(it.second, host));
        // No reason to fail but check anyway.
        if (!ret.second) {
            return (false);
        }
    }
    return (true);
}

void
HostCacheImpl::removeResv6(const HostPtr& host) {
    if (!host || (host->getIPv6SubnetID() == SUBNET_ID_UNUSED)) {
        return;
    }
    const IPv6ResrvRange& resrv = host->getIPv6Reservations();
    if (std::distance(resrv.first, resrv.second) == 0) {
        return;
    }
    // For each IPv6 reservation, remove it.
    const SubnetID& subnet_id = host->getIPv6SubnetID();
    Resv6ContainerAddressIndex& idx0 =
        cache6_.get<Resv6AddressIndexTag>();
    Resv6ContainerSubnetAddressIndex& idx1 =
        cache6_.get<Resv6SubnetAddressIndexTag>();
    BOOST_FOREACH(auto const& it, resrv) {
        const IOAddress& prefix = it.second.getPrefix();
        if (it.first == IPv6Resrv::TYPE_NA) {
            Resv6ContainerSubnetAddressIndexRange r =
                make_pair(idx1.lower_bound(boost::make_tuple(subnet_id, prefix)),
                          idx1.upper_bound(boost::make_tuple(subnet_id, prefix)));
            for (Resv6ContainerSubnetAddressIndex::iterator p = r.first;
                 p != r.second; ++p) {
                if (p->host_ != host) {
                    // Should not happen
                    continue;
                }
                idx1.erase(p);
                break;
            }
        } else if (it.first == IPv6Resrv::TYPE_PD) {
            uint8_t prefix_len = it.second.getPrefixLen();
            Resv6ContainerAddressIndexRange r =
                make_pair(idx0.lower_bound(prefix), idx0.upper_bound(prefix));
            for (Resv6ContainerAddressIndex::iterator p = r.first;
                 p != r.second; ++p) {
                if (p->resrv_.getPrefixLen() == prefix_len) {
                    if (p->host_ != host) {
                        // Should not happen
                        continue;
                    }
                    idx0.erase(p);
                    break;
                }
            }
        }
    }
}

HostPtr
HostCacheImpl::relocate(HostPtr host) {
    if (host) {
        const HostContainerHashedIndex& idx = cache_.get<HostHashedIndexTag>();
        HostContainerHashedIndex::iterator it = idx.find(host);
        if (it == idx.end()) {
            // Should not happen
            // Remove related reservations unconditionally
            removeResv6(host);
            return (HostPtr());
        }
        cache_.relocate(cache_.end(), cache_.project<HostSequencedIndexTag>(it));
    }
    return (host);
}

ConstHostPtr
HostCacheImpl::get4(const dhcp::SubnetID& subnet_id,
                    const dhcp::Host::IdentifierType& identifier_type,
                    const uint8_t* identifier_begin,
                    const size_t identifier_len) {
    HostContainerSequencedIndex::iterator host =
        getHostInternal(subnet_id, false, identifier_type,
                        identifier_begin, identifier_len);
    if (host == cache_.end()) {
        return (ConstHostPtr());
    }
    cache_.relocate(cache_.end(), host);
    return (*host);
}

ConstHostPtr
HostCacheImpl::get4(const dhcp::SubnetID& subnet_id,
                    const asiolink::IOAddress& address) {
    HostContainerSequencedIndex::iterator host =
        getHostInternal4(subnet_id, address);
    if (host == cache_.end()) {
        return (ConstHostPtr());
    }
    cache_.relocate(cache_.end(), host);
    return (*host);
}

ConstHostPtr
HostCacheImpl::get6(const dhcp::SubnetID& subnet_id,
                    const dhcp::Host::IdentifierType& identifier_type,
                    const uint8_t* identifier_begin,
                    const size_t identifier_len) {
    HostContainerSequencedIndex::iterator host =
        getHostInternal(subnet_id, true, identifier_type,
                        identifier_begin, identifier_len);
    if (host == cache_.end()) {
        return (ConstHostPtr());
    }
    cache_.relocate(cache_.end(), host);
    return (*host);
}

ConstHostPtr
HostCacheImpl::get6(const asiolink::IOAddress& prefix,
                    const uint8_t prefix_len) {
    HostPtr host = getHostInternal6(prefix, prefix_len);
    return (relocate(host));
}

ConstHostPtr
HostCacheImpl::get6(const dhcp::SubnetID& subnet_id,
                    const asiolink::IOAddress& address) {
    HostPtr host = getHostInternal6(subnet_id, address);
    return (relocate(host));
}

HostContainerSequencedIndex::iterator
HostCacheImpl::getHostInternal(const SubnetID& subnet_id, const bool subnet6,
                               const Host::IdentifierType& identifier_type,
                               const uint8_t* identifier,
                               const size_t identifier_len) {
    // Use the identifier and identifier type as a composite key.
    const HostContainerIdentifierIndex& idx =
        cache_.get<HostIdentifierIndexTag>();
    boost::tuple<const vector<uint8_t>, const Host::IdentifierType> t =
        boost::make_tuple(vector<uint8_t>(identifier,
                                          identifier + identifier_len),
                          identifier_type);

    for (HostContainerIdentifierIndex::iterator host = idx.lower_bound(t);
         host != idx.upper_bound(t); ++host) {
        // Check if this is IPv4 subnet or IPv6 subnet.
        SubnetID host_subnet_id = subnet6 ? (*host)->getIPv6SubnetID() :
            (*host)->getIPv4SubnetID();

        if (subnet_id == host_subnet_id) {
            return (cache_.project<HostSequencedIndexTag>(host));
        }
    }
    return (cache_.end());
}

HostContainerSequencedIndex::iterator
HostCacheImpl::getHostInternal4(const SubnetID& subnet_id,
                                const IOAddress& address) {
    // Search for the Host using the reserved IPv4 address as a key.
    const HostContainerAddress4Index& idx =
        cache_.get<HostAddress4IndexTag>();
    HostContainerAddress4IndexRange r = idx.equal_range(address);
    for (HostContainerAddress4Index::iterator host = r.first;
         host != r.second; ++host) {
        // Find matching subnet ID.
        if ((*host)->getIPv4SubnetID() == subnet_id) {
            return (cache_.project<HostSequencedIndexTag>(host));
        }
    }
    return (cache_.end());
}

HostPtr
HostCacheImpl::getHostInternal6(const asiolink::IOAddress& prefix,
                                const uint8_t prefix_len) {
    // Let's get all reservations for the prefix
    const Resv6ContainerAddressIndex& idx =
        cache6_.get<Resv6AddressIndexTag>();
    Resv6ContainerAddressIndexRange r = make_pair(idx.lower_bound(prefix),
                                                  idx.upper_bound(prefix));
    BOOST_FOREACH(auto const& resrv, r) {
        if (resrv.resrv_.getPrefixLen() == prefix_len) {
            return (resrv.host_);
        }
    }
    return (HostPtr());
}

HostPtr
HostCacheImpl::getHostInternal6(const dhcp::SubnetID& subnet_id,
                                const asiolink::IOAddress& address) {
    // Search for the reservation that match subnet_id, address.
    const Resv6ContainerSubnetAddressIndex& idx =
        cache6_.get<Resv6SubnetAddressIndexTag>();
    // The index is ordered unique so the range size can be only 0 or 1.
    Resv6ContainerSubnetAddressIndexRange r =
        make_pair(idx.lower_bound(boost::make_tuple(subnet_id, address)),
                  idx.upper_bound(boost::make_tuple(subnet_id, address)));

    BOOST_FOREACH(auto const& resrv, r) {
        return (resrv.host_);
    }
    return (HostPtr());
}

size_t
HostCacheImpl::insert(const ConstHostPtr& host, bool overwrite) {
    HWAddrPtr hwaddr = host->getHWAddress();
    DuidPtr duid = host->getDuid();
    const vector<uint8_t>& id = host->getIdentifier();
    size_t conflicts = 0;

    // Check for duplicates for the specified IPv4 subnet.
    if (host->getIPv4SubnetID() != SUBNET_ID_UNUSED) {
        // Identifier
        if (!id.empty()) {
            HostContainerSequencedIndex::iterator dup;
            while ((dup = getHostInternal(host->getIPv4SubnetID(), false,
                                          host->getIdentifierType(),
                                          &id[0], id.size()))
                   != cache_.end()) {
                ++conflicts;
                if (!overwrite) {
                    return (conflicts);
                } else {
                    removeResv6(*dup);
                    cache_.erase(dup);
                }
            }
        }
        // Reserved IPv4 address.
        const asiolink::IOAddress& address = host->getIPv4Reservation();
        if (!address.isV4Zero()) {
            HostContainerSequencedIndex::iterator dup;
            while ((dup = getHostInternal4(host->getIPv4SubnetID(),
                                           address)) != cache_.end()) {
                ++conflicts;
                if (!overwrite) {
                    return (conflicts);
                } else {
                    removeResv6(*dup);
                    cache_.erase(dup);
                }
            }
        }
    }

    // Check for duplicates for the specified IPv6 subnet.
    if (host->getIPv6SubnetID() != SUBNET_ID_UNUSED) {
        // Identifier.
        if (!id.empty()) {
            HostContainerSequencedIndex::iterator dup;
            while ((dup = getHostInternal(host->getIPv6SubnetID(), true,
                                          host->getIdentifierType(),
                                          &id[0], id.size()))
                   != cache_.end()) {
                ++conflicts;
                if (!overwrite) {
                    return (conflicts);
                } else {
                    removeResv6(*dup);
                    cache_.erase(dup);
                }
            }
        }
        // Reservations.
        const IPv6ResrvRange& resrv = host->getIPv6Reservations();
        BOOST_FOREACH(auto const& it, resrv) {
            if (it.first == IPv6Resrv::TYPE_NA) {
                HostPtr dup;
                while ((dup = getHostInternal6(host->getIPv6SubnetID(),
                                               it.second.getPrefix()))) {
                    ++conflicts;
                    if (!overwrite) {
                        return (conflicts);
                    } else {
                        remove(dup);
                    }
                }
            } else if (it.first == IPv6Resrv::TYPE_PD) {
                HostPtr dup;
                while ((dup = getHostInternal6(it.second.getPrefix(),
                                               it.second.getPrefixLen()))) {
                    ++conflicts;
                    if (!overwrite) {
                        return (conflicts);
                    } else {
                        remove(dup);
                    }
                }
            }
        }
    }

    // This is a new instance - add a copy of it.
    HostPtr host_copy(new Host(*host));
    auto ret = cache_.push_back(host_copy);
    if (!ret.second) {
        // isc_throw(Unexpected, "can't insert");
        ++conflicts;
        return (conflicts);
    } else if (!insertResv6(host_copy)) {
        // isc_throw(Unexpected, "can't insert IPv6 reservation");
        ++conflicts;
        remove(host_copy);
        return (conflicts);
    }

    // Adjust cache size
    if (maximum_ && (cache_.size() > maximum_)) {
        flush(cache_.size() - maximum_);
    }

    return (conflicts);
}

void
HostCacheImpl::update(ConstHostPtr const& host) {
    if (!host) {
        return;
    }

    // At least one subnet ID must be used.
    if (host->getIPv4SubnetID() == SUBNET_ID_UNUSED &&
        host->getIPv6SubnetID() == SUBNET_ID_UNUSED) {
        return;
    }

    /// This is not an upsert, so if the host doesn't exist yet, throw an error.
    /// @todo: If this function ever ends up being used, this brute force search
    /// should be replaced with a host ID index.
    bool found(false);
    for (HostPtr const& h : cache_) {
        if (h->getHostId() == host->getHostId()) {
            found = true;
            break;
        }
    }
    if (!found) {
        isc_throw(NotFound, "host ID " << host->getHostId() << " not found");
    }

    // We're sure the host exists, so an insert with overwrite is equivalent to
    // an update.
    insert(host, /* overwrite = */ true);
}

bool
HostCacheImpl::add(const HostPtr& host) {
    return (insert(host, false) == 0);
}

string
HostCacheImpl::del4(const dhcp::SubnetID& subnet_id,
                    const asiolink::IOAddress& addr) {
    string txt;
    // Search for the Host using the reserved IPv4 address as a key.
    HostContainerAddress4Index& idx = cache_.get<HostAddress4IndexTag>();
    HostContainerAddress4IndexRange r = idx.equal_range(addr);
    for (HostContainerAddress4Index::iterator host = r.first;
         host != r.second; ++host) {
        // Find matching subnet ID.
        if ((*host)->getIPv4SubnetID() == subnet_id) {
            txt = (*host)->toText();
            removeResv6(*host);
            idx.erase(host);
            return (txt);
        }
    }
    return (txt);
}

string
HostCacheImpl::del6(const dhcp::SubnetID& subnet_id,
                    const asiolink::IOAddress& addr) {
    string txt;
    // Search for the reservation that match subnet_id, address.
    const Resv6ContainerSubnetAddressIndex& idx =
        cache6_.get<Resv6SubnetAddressIndexTag>();
    Resv6ContainerSubnetAddressIndex::iterator resrv =
        idx.find(boost::make_tuple(subnet_id, addr));
    if (resrv == idx.end()) {
        return (txt);
    }
    txt = resrv->host_->toText();
    remove(resrv->host_);
    return (txt);
}

string
HostCacheImpl::del4(const dhcp::SubnetID& subnet_id,
                    const dhcp::Host::IdentifierType& identifier_type,
                    const uint8_t* identifier_begin,
                    const size_t identifier_len) {
    string txt;
    // Use the identifier and identifier type as a composite key.
    HostContainerIdentifierIndex& idx = cache_.get<HostIdentifierIndexTag>();
    boost::tuple<const vector<uint8_t>, const Host::IdentifierType> t =
        boost::make_tuple(vector<uint8_t>(identifier_begin,
                                          identifier_begin + identifier_len),
                          identifier_type);
    for (HostContainerIdentifierIndex::iterator host = idx.lower_bound(t);
         host != idx.upper_bound(t); ++host) {
        SubnetID host_subnet_id = (*host)->getIPv4SubnetID();
        if (subnet_id == host_subnet_id) {
            txt = (*host)->toText();
            removeResv6(*host);
            idx.erase(host);
            return (txt);
        }
    }
    return (txt);
}

string
HostCacheImpl::del6(const dhcp::SubnetID& subnet_id,
                    const dhcp::Host::IdentifierType& identifier_type,
                    const uint8_t* identifier_begin,
                    const size_t identifier_len) {
    string txt;
    // Use the identifier and identifier type as a composite key.
    HostContainerIdentifierIndex& idx =
        cache_.get<HostIdentifierIndexTag>();
    boost::tuple<const vector<uint8_t>, const Host::IdentifierType> t =
        boost::make_tuple(vector<uint8_t>(identifier_begin,
                                          identifier_begin + identifier_len),
                          identifier_type);
    for (HostContainerIdentifierIndex::iterator host = idx.lower_bound(t);
         host != idx.upper_bound(t); ++host) {
        SubnetID host_subnet_id = (*host)->getIPv6SubnetID();
        if (subnet_id == host_subnet_id) {
            txt = (*host)->toText();
            removeResv6(*host);
            idx.erase(host);
            return (txt);
        }
    }
    return (txt);
}

bool
HostCacheImpl::remove(const HostPtr& host) {
    // Using the hashed index
    HostContainerHashedIndex& idx = cache_.get<HostHashedIndexTag>();
    HostContainerHashedIndex::iterator host_it = idx.find(host);
    // Remove related reservations unconditionally
    removeResv6(host);
    if (host_it == idx.end()) {
        return (false);
    }
    idx.erase(host_it);
    return (true);
}

void
HostCacheImpl::flush(size_t count) {
    // Flush all entries is handled by clear.
    if (count == 0) {
        return;
    }
    HostContainerSequencedIndex& idx = cache_.get<HostSequencedIndexTag>();
    HostContainerSequencedIndex::iterator host = idx.begin();
    while ((host != idx.end()) && (count > 0)) {
        removeResv6(*host);
        idx.erase(host);
        host = idx.begin();
        --count;
    }
}

ElementPtr
HostCacheImpl::toElement() const {
    ElementPtr result = Element::createList();
    // Iterate using sequenced index to keep the order
    const HostContainerSequencedIndex& idx =
        cache_.get<HostSequencedIndexTag>();
    for (auto const& host : idx) {
        // Convert host to element representation
        ElementPtr map = isc::host_cache::toElement(host);
        // Push it on the list
        result->add(map);
    }
    return (result);
}

ConstHostCollection
HostCacheImpl::get(const dhcp::Host::IdentifierType& identifier_type,
                   const uint8_t* identifier_begin,
                   const size_t identifier_len) const {
    // Use the identifier and identifier type as a composite key.
    const HostContainerIdentifierIndex& idx =
        cache_.get<HostIdentifierIndexTag>();
    boost::tuple<const vector<uint8_t>, const Host::IdentifierType> t =
        boost::make_tuple(vector<uint8_t>(identifier_begin,
                                          identifier_begin + identifier_len),
                          identifier_type);
    ConstHostCollection result;
    for (HostContainerIdentifierIndex::iterator host = idx.lower_bound(t);
         host != idx.upper_bound(t); ++host) {
        result.push_back(*host);
    }
    return (result);
}

} // end of namespace isc::host_cache
} // end of namespace isc
