// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/hosts_log.h>
#include <exceptions/exceptions.h>
#include <ostream>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

ConstHostCollection
CfgHosts::getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid) const {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal method.
    ConstHostCollection collection;
    getAllInternal<ConstHostCollection>(hwaddr, duid, collection);
    return (collection);
}

HostCollection
CfgHosts::getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid) {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal method.
    HostCollection collection;
    getAllInternal<HostCollection>(hwaddr, duid, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getAll(const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin,
                 const size_t identifier_len) const {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal method.
    ConstHostCollection collection;
    getAllInternal<ConstHostCollection>(identifier_type, identifier_begin,
                                        identifier_len, collection);
    return (collection);
}

HostCollection
CfgHosts::getAll(const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin, const size_t identifier_len) {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal method.
    HostCollection collection;
    getAllInternal<HostCollection>(identifier_type, identifier_begin,
                                   identifier_len, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getAll4(const IOAddress& address) const {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal4 method.
    ConstHostCollection collection;
    getAllInternal4<ConstHostCollection>(address, collection);
    return (collection);
}

HostCollection
CfgHosts::getAll4(const IOAddress& address) {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal4 method.
    HostCollection collection;
    getAllInternal4<HostCollection>(address, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getAll6(const IOAddress& address) const {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal6 method.
    ConstHostCollection collection;
    getAllInternal6<ConstHostCollection>(address, collection);
    return (collection);
}

HostCollection
CfgHosts::getAll6(const IOAddress& address) {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal6 method.
    HostCollection collection;
    getAllInternal6<HostCollection>(address, collection);
    return (collection);
}

template<typename Storage>
void
CfgHosts::getAllInternal(const Host::IdentifierType& identifier_type,
                         const uint8_t* identifier,
                         const size_t identifier_len,
                         Storage& storage) const {

    // Convert host identifier into textual format for logging purposes.
    // This conversion is exception free.
    std::string identifier_text = Host::getIdentifierAsText(identifier_type,
                                                            identifier,
                                                            identifier_len);
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_IDENTIFIER)
        .arg(identifier_text);

    // Use the identifier and identifier type as a composite key.
    const HostContainerIndex0& idx = hosts_.get<0>();
    boost::tuple<const std::vector<uint8_t>, const Host::IdentifierType> t =
        boost::make_tuple(std::vector<uint8_t>(identifier,
                                               identifier + identifier_len),
                                               identifier_type);

    // Append each Host object to the storage.
    for (HostContainerIndex0::iterator host = idx.lower_bound(t);
         host != idx.upper_bound(t);
         ++host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_IDENTIFIER_HOST)
            .arg(identifier_text)
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_IDENTIFIER_COUNT)
        .arg(identifier_text)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getAllInternal(const HWAddrPtr& hwaddr, const DuidPtr& duid,
                         Storage& storage) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_HWADDR_DUID)
        .arg(hwaddr ? hwaddr->toText() : "(no-hwaddr)")
        .arg(duid ? duid->toText() : "(no-duid)");

    // Get hosts using HW address.
    if (hwaddr && !hwaddr->hwaddr_.empty()) {
        getAllInternal<Storage>(Host::IDENT_HWADDR, &hwaddr->hwaddr_[0],
                                hwaddr->hwaddr_.size(), storage);
    }
    // Get hosts using DUID.
    if (duid && !duid->getDuid().empty()) {
        getAllInternal<Storage>(Host::IDENT_DUID, &duid->getDuid()[0],
                                duid->getDuid().size(), storage);
    }
}

template<typename Storage>
void
CfgHosts::getAllInternal4(const IOAddress& address, Storage& storage) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_ADDRESS4)
        .arg(address.toText());

    // Must not specify address other than IPv4.
    if (!address.isV4()) {
        isc_throw(BadHostAddress, "must specify an IPv4 address when searching"
                  " for a host, specified address was " << address);
    }
    // Search for the Host using the reserved IPv4 address as a key.
    const HostContainerIndex1& idx = hosts_.get<1>();
    HostContainerIndex1Range r = idx.equal_range(address);
    // Append each Host object to the storage.
    for (HostContainerIndex1::iterator host = r.first; host != r.second;
         ++host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_ADDRESS4_HOST)
            .arg(address.toText())
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_ADDRESS4_COUNT)
        .arg(address.toText())
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getAllInternal6(const IOAddress& address, Storage& storage) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_ADDRESS6)
        .arg(address.toText());

    // Must not specify address other than IPv6.
    if (!address.isV6()) {
        isc_throw(BadHostAddress, "must specify an IPv6 address when searching"
                  " for a host, specified address was " << address);
    }
    // Search for the Host using the reserved IPv6 address as a key.
    const HostContainerIndex1& idx = hosts_.get<1>();
    HostContainerIndex1Range r = idx.equal_range(address);
    // Append each Host object to the storage.
    for (HostContainerIndex1::iterator host = r.first; host != r.second;
         ++host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_ADDRESS6_HOST)
            .arg(address.toText())
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_ADDRESS6_COUNT)
        .arg(address.toText())
        .arg(storage.size());
}

ConstHostPtr
CfgHosts::get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
               const DuidPtr& duid) const {
    // Do not log here because getHostInternal logs.
    // The false value indicates that it is an IPv4 subnet.
    HostPtr host;
    if (hwaddr && !hwaddr->hwaddr_.empty()) {
        host = getHostInternal(subnet_id, false, Host::IDENT_HWADDR,
                               &hwaddr->hwaddr_[0],
                               hwaddr->hwaddr_.size());
    }
    if (!host && duid && !duid->getDuid().empty()) {
        host = getHostInternal(subnet_id, false, Host::IDENT_DUID,
                               &duid->getDuid()[0],
                               duid->getDuid().size());
    }
    return (host);
}

HostPtr
CfgHosts::get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
               const DuidPtr& duid) {
    // Do not log here because getHostInternal logs.
    // The false value indicates that it is an IPv4 subnet.
    HostPtr host;
    if (hwaddr && !hwaddr->hwaddr_.empty()) {
        host = getHostInternal(subnet_id, false, Host::IDENT_HWADDR,
                               &hwaddr->hwaddr_[0],
                               hwaddr->hwaddr_.size());
    }
    if (!host && duid && !duid->getDuid().empty()) {
        host = getHostInternal(subnet_id, false, Host::IDENT_DUID,
                               &duid->getDuid()[0],
                               duid->getDuid().size());
    }
    return (host);
}

ConstHostPtr
CfgHosts::get4(const SubnetID& subnet_id,
               const Host::IdentifierType& identifier_type,
               const uint8_t* identifier_begin,
               const size_t identifier_len) const {
    return (getHostInternal(subnet_id, false, identifier_type, identifier_begin,
                            identifier_len));
}

HostPtr
CfgHosts::get4(const SubnetID& subnet_id,
               const Host::IdentifierType& identifier_type,
               const uint8_t* identifier_begin,
               const size_t identifier_len) {
    return (getHostInternal(subnet_id, false, identifier_type, identifier_begin,
                            identifier_len));
}

ConstHostPtr
CfgHosts::get4(const SubnetID& subnet_id, const IOAddress& address) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4)
        .arg(subnet_id).arg(address.toText());

    ConstHostCollection hosts = getAll4(address);
    for (ConstHostCollection::const_iterator host = hosts.begin();
         host != hosts.end(); ++host) {
        if ((*host)->getIPv4SubnetID() == subnet_id) {
            LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                      HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_HOST)
                .arg(subnet_id)
                .arg(address.toText())
                .arg((*host)->toText());
            return (*host);
        }
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_NULL)
        .arg(subnet_id).arg(address.toText());
    return (ConstHostPtr());
}


ConstHostPtr
CfgHosts::get6(const SubnetID& subnet_id, const DuidPtr& duid,
               const HWAddrPtr& hwaddr) const {
    // Do not log here because getHostInternal logs.
    // The true value indicates that it is an IPv6 subnet.
    HostPtr host;
    if (duid && !duid->getDuid().empty()) {
        host = getHostInternal(subnet_id, true, Host::IDENT_DUID,
                               &duid->getDuid()[0],
                               duid->getDuid().size());
    }
    if (!host && hwaddr && !hwaddr->hwaddr_.empty()) {
        host = getHostInternal(subnet_id, true, Host::IDENT_HWADDR,
                               &hwaddr->hwaddr_[0],
                               hwaddr->hwaddr_.size());
    }

    return (host);
}

HostPtr
CfgHosts::get6(const SubnetID& subnet_id, const DuidPtr& duid,
               const HWAddrPtr& hwaddr) {
    // Do not log here because getHostInternal logs.
    // The true value indicates that it is an IPv6 subnet.
    HostPtr host;
    if (duid && !duid->getDuid().empty()) {
        host = getHostInternal(subnet_id, true, Host::IDENT_DUID,
                               &duid->getDuid()[0],
                               duid->getDuid().size());
    }
    if (!host && hwaddr && !hwaddr->hwaddr_.empty()) {
        host = getHostInternal(subnet_id, true, Host::IDENT_HWADDR,
                               &hwaddr->hwaddr_[0],
                               hwaddr->hwaddr_.size());
    }

    return (host);
}

ConstHostPtr
CfgHosts::get6(const SubnetID& subnet_id,
               const Host::IdentifierType& identifier_type,
               const uint8_t* identifier_begin,
               const size_t identifier_len) const {
    return (getHostInternal(subnet_id, true, identifier_type, identifier_begin,
                            identifier_len));
}

HostPtr
CfgHosts::get6(const SubnetID& subnet_id,
               const Host::IdentifierType& identifier_type,
               const uint8_t* identifier_begin,
               const size_t identifier_len) {
    return (getHostInternal(subnet_id, true, identifier_type, identifier_begin,
                            identifier_len));
}

ConstHostPtr
CfgHosts::get6(const IOAddress& prefix, const uint8_t prefix_len) const {
    return (getHostInternal6<ConstHostPtr>(prefix, prefix_len));
}

HostPtr
CfgHosts::get6(const IOAddress& prefix, const uint8_t prefix_len) {
    return (getHostInternal6<HostPtr>(prefix, prefix_len));
}

ConstHostPtr
CfgHosts::get6(const SubnetID& subnet_id,
               const asiolink::IOAddress& address) const {
    // Do not log here because getHostInternal6 logs.
    return (getHostInternal6<ConstHostPtr, ConstHostCollection>(subnet_id, address));
}

HostPtr
CfgHosts::get6(const SubnetID& subnet_id,
               const asiolink::IOAddress& address) {
    // Do not log here because getHostInternal6 logs.
    return (getHostInternal6<HostPtr, HostCollection>(subnet_id, address));
}

template<typename ReturnType, typename Storage>
ReturnType
CfgHosts::getHostInternal6(const SubnetID& subnet_id,
                           const asiolink::IOAddress& address) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6)
        .arg(subnet_id).arg(address.toText());

    Storage storage;
    getAllInternal6<Storage>(subnet_id, address, storage);
    switch (storage.size()) {
    case 0:
        LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                  HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_NULL)
            .arg(subnet_id)
            .arg(address.toText());
        return (HostPtr());

    case 1:
        LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                  HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_HOST)
            .arg(subnet_id)
            .arg(address.toText())
            .arg((*storage.begin())->toText());
        return (*storage.begin());

    default:
        isc_throw(DuplicateHost,  "more than one reservation found"
                  " for the host belonging to the subnet with id '"
                  << subnet_id << "' and using the address '"
                  << address.toText() << "'");
    }

}

template<typename ReturnType>
ReturnType
CfgHosts::getHostInternal6(const asiolink::IOAddress& prefix,
                           const uint8_t prefix_len) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ONE_PREFIX)
        .arg(prefix.toText()).arg(static_cast<int>(prefix_len));

    // Let's get all reservations that match subnet_id, address.
    const HostContainer6Index0& idx = hosts6_.get<0>();
    HostContainer6Index0Range r = make_pair(idx.lower_bound(prefix),
                                            idx.upper_bound(prefix));
    for (HostContainer6Index0::iterator resrv = r.first; resrv != r.second;
         ++resrv) {
        if (resrv->resrv_.getPrefixLen() == prefix_len) {
            LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                      HOSTS_CFG_GET_ONE_PREFIX_HOST)
                .arg(prefix.toText())
                .arg(static_cast<int>(prefix_len))
                .arg(resrv->host_->toText());
            return (resrv->host_);
        }
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
              HOSTS_CFG_GET_ONE_PREFIX_NULL)
        .arg(prefix.toText())
        .arg(static_cast<int>(prefix_len));
    return (ReturnType());
}

template<typename Storage>
void
CfgHosts::getAllInternal6(const SubnetID& subnet_id,
                          const asiolink::IOAddress& address,
                          Storage& storage) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6)
        .arg(subnet_id).arg(address.toText());

    // Must not specify address other than IPv6.
    if (!address.isV6()) {
        isc_throw(BadHostAddress, "must specify an IPv6 address when searching"
                  " for a host, specified address was " << address);
    }

    // Let's get all reservations that match subnet_id, address.
    const HostContainer6Index1& idx = hosts6_.get<1>();
    HostContainer6Index1Range r = make_pair(idx.lower_bound(boost::make_tuple(subnet_id, address)),
                                            idx.upper_bound(boost::make_tuple(subnet_id, address)));

    // For each IPv6 reservation, add the host to the results list. Fortunately,
    // in all sane cases, there will be only one such host. (Each host can have
    // multiple addresses reserved, but for each (address, subnet_id) there should
    // be at most one host reserving it).
    for(HostContainer6Index1::iterator resrv = r.first; resrv != r.second; ++resrv) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_HOST)
            .arg(subnet_id)
            .arg(address.toText())
            .arg(resrv->host_->toText());
        storage.push_back(resrv->host_);
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
              HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_COUNT)
        .arg(subnet_id)
        .arg(address.toText())
        .arg(storage.size());
}

HostPtr
CfgHosts::getHostInternal(const SubnetID& subnet_id, const bool subnet6,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier,
                          const size_t identifier_len) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER)
        .arg(subnet6 ? "IPv6" : "IPv4")
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier, identifier_len));

    // Get all hosts for a specified identifier. This may return multiple hosts
    // for different subnets, but the number of hosts returned should be low
    // because one host presumably doesn't show up in many subnets.
    HostCollection hosts;
    getAllInternal<HostCollection>(identifier_type, identifier, identifier_len,
                                   hosts);

    HostPtr host;
    // Iterate over the returned hosts and select those for which the
    // subnet id matches.
    for (HostCollection::const_iterator host_it = hosts.begin();
         host_it != hosts.end(); ++host_it) {
        // Check if this is IPv4 subnet or IPv6 subnet.
        SubnetID host_subnet_id = subnet6 ? (*host_it)->getIPv6SubnetID() :
            (*host_it)->getIPv4SubnetID();

        if (subnet_id == host_subnet_id) {
            // If this is the first occurrence of the host for this subnet,
            // remember it. But, if we find that this is second @c Host object
            // for the same client, it is a misconfiguration. Most likely,
            // the administrator has specified one reservation for a HW
            // address and another one for the DUID, which gives an ambiguous
            // result, and we don't know which reservation we should choose.
            // Therefore, throw an exception.
            if (!host) {
                host = *host_it;

            } else {
                isc_throw(DuplicateHost,  "more than one reservation found"
                          " for the host belonging to the subnet with id '"
                          << subnet_id << "' and using the identifier '"
                          << Host::getIdentifierAsText(identifier_type,
                                                       identifier,
                                                       identifier_len)
                          << "'");
            }
        }
    }

    if (host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                  HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_HOST)
            .arg(subnet_id)
            .arg(Host::getIdentifierAsText(identifier_type, identifier,
                                           identifier_len))
            .arg(host->toText());

    } else {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                  HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_NULL)
            .arg(subnet_id)
            .arg(Host::getIdentifierAsText(identifier_type, identifier,
                                           identifier_len));
    }

    return (host);
}

void
CfgHosts::add(const HostPtr& host) {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_ADD_HOST)
        .arg(host ? host->toText() : "(no-host)");

    // Sanity check that the host is non-null.
    if (!host) {
        isc_throw(BadValue, "specified host object must not be NULL when it"
                  " is added to the configuration");
    }

    // At least one subnet ID must be non-zero
    if (host->getIPv4SubnetID() == 0 && host->getIPv6SubnetID() == 0) {
        isc_throw(BadValue, "must not use both IPv4 and IPv6 subnet ids of"
                  " 0 when adding new host reservation");
    }

    add4(host);

    add6(host);
}

void
CfgHosts::add4(const HostPtr& host) {
    /// @todo This may need further sanity checks.
    HWAddrPtr hwaddr = host->getHWAddress();
    DuidPtr duid = host->getDuid();

    // There should be at least one resource reserved: hostname, IPv4
    // address, siaddr, sname, file or IPv6 address or prefix.
    if (host->getHostname().empty() &&
        (host->getIPv4Reservation().isV4Zero()) &&
        !host->hasIPv6Reservation() &&
        host->getNextServer().isV4Zero() &&
        host->getServerHostname().empty() &&
        host->getBootFileName().empty() &&
        host->getCfgOption4()->empty() &&
        host->getCfgOption6()->empty() &&
        host->getClientClasses4().empty() &&
        host->getClientClasses6().empty()) {
        std::ostringstream s;
        if (hwaddr) {
            s << "for DUID: " << hwaddr->toText();
        } else if (duid) {
            s << "for HW address: " << duid->toText();
        }
        isc_throw(BadValue, "specified reservation " << s.str()
                  << " must include at least one resource, i.e. "
                  "hostname, IPv4 address, IPv6 address/prefix, "
                  "options");
    }

    // Check for duplicates for the specified IPv4 subnet.
    if ((host->getIPv4SubnetID() > 0) &&
        get4(host->getIPv4SubnetID(), hwaddr, duid)) {
        isc_throw(DuplicateHost, "failed to add new host using the HW"
                  " address '" << (hwaddr ? hwaddr->toText(false) : "(null)")
                  << " and DUID '" << (duid ? duid->toText() : "(null)")
                  << "' to the IPv4 subnet id '" << host->getIPv4SubnetID()
                  << "' as this host has already been added");


    // Check for duplicates for the specified IPv6 subnet.
    } else if (host->getIPv6SubnetID() &&
               get6(host->getIPv6SubnetID(), duid, hwaddr)) {
        isc_throw(DuplicateHost, "failed to add new host using the HW"
                  " address '" << (hwaddr ? hwaddr->toText(false) : "(null)")
                  << " and DUID '" << (duid ? duid->toText() : "(null)")
                  << "' to the IPv6 subnet id '" << host->getIPv6SubnetID()
                  << "' as this host has already been added");
    }

    // Check if the address is already reserved for the specified IPv4 subnet.
    if (!host->getIPv4Reservation().isV4Zero() &&
        (host->getIPv4SubnetID() > 0) &&
        get4(host->getIPv4SubnetID(), host->getIPv4Reservation())) {
        isc_throw(ReservedAddress, "failed to add new host using the HW"
                  " address '" << (hwaddr ? hwaddr->toText(false) : "(null)")
                  << " and DUID '" << (duid ? duid->toText() : "(null)")
                  << "' to the IPv4 subnet id '" << host->getIPv4SubnetID()
                  << "' for the address " << host->getIPv4Reservation()
                  << ": There's already a reservation for this address");
    }

    /// @todo This may need further sanity checks.

    // This is a new instance - add it.
    hosts_.insert(host);
}

void
CfgHosts::add6(const HostPtr& host) {
    /// @todo This may need further sanity checks.
    HWAddrPtr hwaddr = host->getHWAddress();
    DuidPtr duid = host->getDuid();

    // Get all reservations for this host.
    IPv6ResrvRange reservations = host->getIPv6Reservations();

    // Check if there are any IPv6 reservations.
    if (std::distance(reservations.first, reservations.second) == 0) {
        // If there aren't, we don't need to add this to hosts6_, which is used
        // for getting hosts by their IPv6 address reservations.
        return;
    }

    // Now for each reservation, insert corresponding (address, host) tuple.
    for (IPv6ResrvIterator it = reservations.first; it != reservations.second;
         ++it) {

        // If there's an entry for this (subnet-id, address), reject it.
        if (get6(host->getIPv6SubnetID(), it->second.getPrefix())) {
            isc_throw(DuplicateHost, "failed to add address reservation for "
                      << "host using the HW address '"
                      << (hwaddr ? hwaddr->toText(false) : "(null)")
                      << " and DUID '" << (duid ? duid->toText() : "(null)")
                      << "' to the IPv6 subnet id '" << host->getIPv6SubnetID()
                      << "' for address/prefix " << it->second.getPrefix()
                      << ": There's already reservation for this address/prefix");
        }
        hosts6_.insert(HostResrv6Tuple(it->second, host));
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
