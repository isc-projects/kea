// Copyright (C) 2014-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfg_hosts_util.h>
#include <dhcpsrv/hosts_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <exceptions/exceptions.h>
#include <util/encode/hex.h>
#include <ostream>
#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::data;

namespace isc {
namespace dhcp {

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
CfgHosts::getAll4(const SubnetID& subnet_id) const {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal4 method.
    ConstHostCollection collection;
    getAllInternal4<ConstHostCollection>(subnet_id, collection);
    return (collection);
}

HostCollection
CfgHosts::getAll4(const SubnetID& subnet_id) {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal4 method.
    HostCollection collection;
    getAllInternal4<HostCollection>(subnet_id, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getAll6(const SubnetID& subnet_id) const {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal6 method.
    ConstHostCollection collection;
    getAllInternal6<ConstHostCollection>(subnet_id, collection);
    return (collection);
}

HostCollection
CfgHosts::getAll6(const SubnetID& subnet_id) {
    // Do not issue logging message here because it will be logged by
    // the getAllInternal6 method.
    HostCollection collection;
    getAllInternal6<HostCollection>(subnet_id, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getAllbyHostname(const std::string& hostname) const {
    // Do not issue logging message here because it will be logged by
    // the getAllbyHostnameInternal method.
    ConstHostCollection collection;
    getAllbyHostnameInternal<ConstHostCollection>(hostname, collection);
    return (collection);
}

HostCollection
CfgHosts::getAllbyHostname(const std::string& hostname) {
    // Do not issue logging message here because it will be logged by
    // the getAllbyHostnameInternal method.
    HostCollection collection;
    getAllbyHostnameInternal<HostCollection>(hostname, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getAllbyHostname4(const std::string& hostname,
                            const SubnetID& subnet_id) const {
    // Do not issue logging message here because it will be logged by
    // the getAllbyHostnameInternal4 method.
    ConstHostCollection collection;
    getAllbyHostnameInternal4<ConstHostCollection>(hostname, subnet_id, collection);
    return (collection);
}

HostCollection
CfgHosts::getAllbyHostname4(const std::string& hostname,
                            const SubnetID& subnet_id) {
    // Do not issue logging message here because it will be logged by
    // the getAllbyHostnameInternal4 method.
    HostCollection collection;
    getAllbyHostnameInternal4<HostCollection>(hostname, subnet_id, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getAllbyHostname6(const std::string& hostname,
                            const SubnetID& subnet_id) const {
    // Do not issue logging message here because it will be logged by
    // the getAllbyHostnameInternal6 method.
    ConstHostCollection collection;
    getAllbyHostnameInternal6<ConstHostCollection>(hostname, subnet_id, collection);
    return (collection);
}

HostCollection
CfgHosts::getAllbyHostname6(const std::string& hostname,
                            const SubnetID& subnet_id) {
    // Do not issue logging message here because it will be logged by
    // the getAllbyHostnameInternal6 method.
    HostCollection collection;
    getAllbyHostnameInternal6<HostCollection>(hostname, subnet_id, collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getPage4(const SubnetID& subnet_id,
                   size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) const {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal4 method.
    ConstHostCollection collection;
    getPageInternal4<ConstHostCollection>(subnet_id,
                                          lower_host_id,
                                          page_size,
                                          collection);
    return (collection);
}

HostCollection
CfgHosts::getPage4(const SubnetID& subnet_id,
                   size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal4 method.
    HostCollection collection;
    getPageInternal4<HostCollection>(subnet_id,
                                     lower_host_id,
                                     page_size,
                                     collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getPage6(const SubnetID& subnet_id,
                   size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) const {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal6 method.
    ConstHostCollection collection;
    getPageInternal6<ConstHostCollection>(subnet_id,
                                          lower_host_id,
                                          page_size,
                                          collection);
    return (collection);
}

HostCollection
CfgHosts::getPage6(const SubnetID& subnet_id,
                   size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal6 method.
    HostCollection collection;
    getPageInternal6<HostCollection>(subnet_id,
                                     lower_host_id,
                                     page_size,
                                     collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getPage4(size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) const {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal method.
    ConstHostCollection collection;
    getPageInternal<ConstHostCollection>(lower_host_id,
                                         page_size,
                                         collection);
    return (collection);
}

HostCollection
CfgHosts::getPage4(size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal method.
    HostCollection collection;
    getPageInternal<HostCollection>(lower_host_id,
                                    page_size,
                                    collection);
    return (collection);
}

ConstHostCollection
CfgHosts::getPage6(size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) const {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal method.
    ConstHostCollection collection;
    getPageInternal<ConstHostCollection>(lower_host_id,
                                         page_size,
                                         collection);
    return (collection);
}

HostCollection
CfgHosts::getPage6(size_t& /*source_index*/,
                   uint64_t lower_host_id,
                   const HostPageSize& page_size) {
    // Do not issue logging message here because it will be logged by
    // the getPageInternal method.
    HostCollection collection;
    getPageInternal<HostCollection>(lower_host_id,
                                    page_size,
                                    collection);
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
CfgHosts::getAllInternal4(const SubnetID& subnet_id,
                          Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_SUBNET_ID4)
        .arg(subnet_id);

    // Use try DHCPv4 subnet id.
    const HostContainerIndex2& idx = hosts_.get<2>();

    // Append each Host object to the storage.
    for (HostContainerIndex2::iterator host = idx.lower_bound(subnet_id);
         host != idx.upper_bound(subnet_id);
         ++host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_SUBNET_ID4_HOST)
            .arg(subnet_id)
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_SUBNET_ID4_COUNT)
        .arg(subnet_id)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getAllInternal6(const SubnetID& subnet_id,
                          Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_SUBNET_ID6)
        .arg(subnet_id);

    // Use try DHCPv6 subnet id.
    const HostContainerIndex3& idx = hosts_.get<3>();

    // Append each Host object to the storage.
    for (HostContainerIndex3::iterator host = idx.lower_bound(subnet_id);
         host != idx.upper_bound(subnet_id);
         ++host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_SUBNET_ID6_HOST)
            .arg(subnet_id)
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_SUBNET_ID6_COUNT)
        .arg(subnet_id)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getAllbyHostnameInternal(const std::string& hostname,
                                   Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_HOSTNAME)
        .arg(hostname);

    // Use try hostname.
    const HostContainerIndex5& idx = hosts_.get<5>();

    // Append each Host object to the storage.
    for (HostContainerIndex5::iterator host = idx.lower_bound(hostname);
         host != idx.upper_bound(hostname);
         ++host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_HOSTNAME_HOST)
            .arg(hostname)
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_HOSTNAME_COUNT)
        .arg(hostname)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getAllbyHostnameInternal4(const std::string& hostname,
                                    const SubnetID& subnet_id,
                                    Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID4)
        .arg(hostname)
        .arg(subnet_id);

    // Use try hostname.
    const HostContainerIndex5& idx = hosts_.get<5>();

    // Append each Host object to the storage.
    for (HostContainerIndex5::iterator host = idx.lower_bound(hostname);
         host != idx.upper_bound(hostname);
         ++host) {
        if ((*host)->getIPv4SubnetID() != subnet_id) {
            continue;
        }
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID4_HOST)
            .arg(hostname)
            .arg(subnet_id)
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
              HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID4_COUNT)
        .arg(hostname)
        .arg(subnet_id)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getAllbyHostnameInternal6(const std::string& hostname,
                                    const SubnetID& subnet_id,
                                    Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID6)
        .arg(hostname)
        .arg(subnet_id);

    // Use try hostname.
    const HostContainerIndex5& idx = hosts_.get<5>();

    // Append each Host object to the storage.
    for (HostContainerIndex5::iterator host = idx.lower_bound(hostname);
         host != idx.upper_bound(hostname);
         ++host) {
        if ((*host)->getIPv6SubnetID() != subnet_id) {
            continue;
        }
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID6_HOST)
            .arg(hostname)
            .arg(subnet_id)
            .arg((*host)->toText());
        storage.push_back(*host);
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
              HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID6_COUNT)
        .arg(hostname)
        .arg(subnet_id)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getPageInternal(uint64_t lower_host_id,
                          const HostPageSize& page_size,
                          Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL);

    // Use the host id last index.
    const HostContainerIndex4& idx = hosts_.get<4>();
    HostContainerIndex4::const_iterator host = idx.lower_bound(lower_host_id);

    // Exclude the lower bound id when it is not zero.
    if (lower_host_id &&
        (host != idx.end()) && ((*host)->getHostId() == lower_host_id)) {
        ++host;
    }

    // Return hosts within the page size.
    for (; host != idx.end(); ++host) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_HOST)
            .arg((*host)->toText());
        storage.push_back(*host);
        if (storage.size() >= page_size.page_size_) {
            break;
        }
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_COUNT)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getPageInternal4(const SubnetID& subnet_id,
                           uint64_t lower_host_id,
                           const HostPageSize& page_size,
                           Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_SUBNET_ID4)
        .arg(subnet_id);

    // Use the host id last index.
    const HostContainerIndex4& idx = hosts_.get<4>();
    HostContainerIndex4::const_iterator host = idx.lower_bound(lower_host_id);

    // Exclude the lower bound id when it is not zero.
    if (lower_host_id &&
        (host != idx.end()) && ((*host)->getHostId() == lower_host_id)) {
        ++host;
    }

    // Return hosts in the subnet within the page size.
    for (; host != idx.end(); ++host) {
        if ((*host)->getIPv4SubnetID() != subnet_id) {
            continue;
        }
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_SUBNET_ID4_HOST)
            .arg(subnet_id)
            .arg((*host)->toText());
        storage.push_back(*host);
        if (storage.size() >= page_size.page_size_) {
            break;
        }
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_SUBNET_ID4_COUNT)
        .arg(subnet_id)
        .arg(storage.size());
}

template<typename Storage>
void
CfgHosts::getPageInternal6(const SubnetID& subnet_id,
                           uint64_t lower_host_id,
                           const HostPageSize& page_size,
                           Storage& storage) const {

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_SUBNET_ID6)
        .arg(subnet_id);

    // Use the host id last index.
    const HostContainerIndex4& idx = hosts_.get<4>();
    HostContainerIndex4::const_iterator host = idx.lower_bound(lower_host_id);

    // Exclude the lower bound id when it is not zero.
    if (lower_host_id &&
        (host != idx.end()) && ((*host)->getHostId() == lower_host_id)) {
        ++host;
    }

    // Return hosts in the subnet within the page size.
    for (; host != idx.end(); ++host) {
        if ((*host)->getIPv6SubnetID() != subnet_id) {
            continue;
        }
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                  HOSTS_CFG_GET_ALL_SUBNET_ID6_HOST)
            .arg(subnet_id)
            .arg((*host)->toText());
        storage.push_back(*host);
        if (storage.size() >= page_size.page_size_) {
            break;
        }
    }

    // Log how many hosts have been found.
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_SUBNET_ID6_COUNT)
        .arg(subnet_id)
        .arg(storage.size());
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

ConstHostCollection
CfgHosts::getAll4(const SubnetID& subnet_id,
                  const asiolink::IOAddress& address) const {
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS4)
        .arg(subnet_id).arg(address.toText());

    ConstHostCollection hosts;
    for (auto host : getAll4(address)) {
        if (host->getIPv4SubnetID() == subnet_id) {
            LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE_DETAIL_DATA,
                      HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS4_HOST)
                .arg(subnet_id)
                .arg(address.toText())
                .arg(host->toText());
            hosts.push_back(host);
        }
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS, HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS4_COUNT)
        .arg(subnet_id)
        .arg(address.toText())
        .arg(hosts.size());

    return (hosts);
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

ConstHostCollection
CfgHosts::getAll6(const SubnetID& subnet_id,
                  const asiolink::IOAddress& address) const {
    ConstHostCollection hosts;
    getAllInternal6(subnet_id, address, hosts);
    return (hosts);
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

    // At least one subnet ID must be used
    if (host->getIPv4SubnetID() == SUBNET_ID_UNUSED &&
        host->getIPv6SubnetID() == SUBNET_ID_UNUSED) {
        isc_throw(BadValue, "must not use both IPv4 and IPv6 subnet ids of"
                  " 0 when adding new host reservation");
    }

    add4(host);

    add6(host);
}

void
CfgHosts::add4(const HostPtr& host) {

    HWAddrPtr hwaddr = host->getHWAddress();
    DuidPtr duid = host->getDuid();

    // There should be at least one resource reserved: hostname, IPv4
    // address, siaddr, sname, file or IPv6 address or prefix.
    /// @todo: this check should be done in add(), not in add4()
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
    if (host->getIPv4SubnetID() != SUBNET_ID_UNUSED) {
        if (hwaddr && !hwaddr->hwaddr_.empty() &&
            get4(host->getIPv4SubnetID(), Host::IDENT_HWADDR,
                 &hwaddr->hwaddr_[0], hwaddr->hwaddr_.size())) {
            isc_throw(DuplicateHost, "failed to add new host using the HW"
                      << " address '" << hwaddr->toText(false)
                      << "' to the IPv4 subnet id '" << host->getIPv4SubnetID()
                      << "' as this host has already been added");
        }
        if (duid && !duid->getDuid().empty() &&
            get4(host->getIPv4SubnetID(), Host::IDENT_DUID,
                 &duid->getDuid()[0], duid->getDuid().size())) {
            isc_throw(DuplicateHost, "failed to add new host using the "
                      << "DUID '" << duid->toText()
                      << "' to the IPv4 subnet id '" << host->getIPv4SubnetID()
                      << "' as this host has already been added");
        }
    // Check for duplicates for the specified IPv6 subnet.
    } else if (host->getIPv6SubnetID() != SUBNET_ID_UNUSED) {
        if (duid && !duid->getDuid().empty() &&
            get6(host->getIPv6SubnetID(), Host::IDENT_DUID,
                 &duid->getDuid()[0], duid->getDuid().size())) {
            isc_throw(DuplicateHost, "failed to add new host using the "
                      << "DUID '" << duid->toText()
                      << "' to the IPv6 subnet id '" << host->getIPv6SubnetID()
                      << "' as this host has already been added");
        }
        if (hwaddr && !hwaddr->hwaddr_.empty() &&
            get6(host->getIPv6SubnetID(), Host::IDENT_HWADDR,
                 &hwaddr->hwaddr_[0], hwaddr->hwaddr_.size())) {
            isc_throw(DuplicateHost, "failed to add new host using the HW"
                      << " address '" << hwaddr->toText(false)
                      << "' to the IPv6 subnet id '" << host->getIPv6SubnetID()
                      << "' as this host has already been added");
        }
    }

    // Check if the address is already reserved for the specified IPv4 subnet.
    if (ip_reservations_unique_ && !host->getIPv4Reservation().isV4Zero() &&
        (host->getIPv4SubnetID() != SUBNET_ID_UNUSED) &&
        get4(host->getIPv4SubnetID(), host->getIPv4Reservation())) {
        isc_throw(ReservedAddress, "failed to add new host using the HW"
                  " address '" << (hwaddr ? hwaddr->toText(false) : "(null)")
                  << " and DUID '" << (duid ? duid->toText() : "(null)")
                  << "' to the IPv4 subnet id '" << host->getIPv4SubnetID()
                  << "' for the address " << host->getIPv4Reservation()
                  << ": There's already a reservation for this address");
    }

    // Check if the (identifier type, identifier) tuple is already used.
    const std::vector<uint8_t>& id = host->getIdentifier();
    if ((host->getIPv4SubnetID() != SUBNET_ID_UNUSED) && !id.empty()) {
        if (get4(host->getIPv4SubnetID(), host->getIdentifierType(), &id[0],
                 id.size())) {
            isc_throw(DuplicateHost, "failed to add duplicate IPv4 host using identifier: "
                      << Host::getIdentifierAsText(host->getIdentifierType(),
                                                   &id[0], id.size()));
        }
    }

    // This is a new instance - add it.
    host->setHostId(++next_host_id_);
    hosts_.insert(host);
}

void
CfgHosts::add6(const HostPtr& host) {

    if (host->getIPv6SubnetID() == SUBNET_ID_UNUSED) {
        // This is IPv4-only host. No need to add it to v6 tables.
        return;
    }

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

        if (ip_reservations_unique_) {
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
        }
        hosts6_.insert(HostResrv6Tuple(it->second, host));
    }
}

bool
CfgHosts::del(const SubnetID& /*subnet_id*/, const asiolink::IOAddress& /*addr*/) {
    /// @todo: Implement host removal
    isc_throw(NotImplemented, "sorry, not implemented");
    return (false);
}

size_t
CfgHosts::delAll4(const SubnetID& subnet_id) {
    HostContainerIndex2& idx = hosts_.get<2>();
    size_t erased = idx.erase(subnet_id);

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_DEL_ALL_SUBNET4)
        .arg(erased)
        .arg(subnet_id);

    return (erased);
}

bool
CfgHosts::del4(const SubnetID& /*subnet_id*/,
               const Host::IdentifierType& /*identifier_type*/,
               const uint8_t* /*identifier_begin*/,
               const size_t /*identifier_len*/) {
    /// @todo: Implement host removal
    isc_throw(NotImplemented, "sorry, not implemented");
    return (false);
}

size_t
CfgHosts::delAll6(const SubnetID& subnet_id) {
    // Delete IPv6 reservations.
    HostContainer6Index2& idx6 = hosts6_.get<2>();
    size_t erased_addresses = idx6.erase(subnet_id);

    // Delete hosts.
    HostContainerIndex3& idx = hosts_.get<3>();
    size_t erased_hosts = idx.erase(subnet_id);

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_CFG_DEL_ALL_SUBNET6)
        .arg(erased_hosts)
        .arg(erased_addresses)
        .arg(subnet_id);

    return (erased_hosts);
}

bool
CfgHosts::del6(const SubnetID& /*subnet_id*/,
               const Host::IdentifierType& /*identifier_type*/,
               const uint8_t* /*identifier_begin*/,
               const size_t /*identifier_len*/) {
    /// @todo: Implement host removal
    isc_throw(NotImplemented, "sorry, not implemented");
    return (false);
}

bool
CfgHosts::setIPReservationsUnique(const bool unique) {
    ip_reservations_unique_ = unique;
    return (true);
}


ElementPtr
CfgHosts::toElement() const {
    uint16_t family = CfgMgr::instance().getFamily();
    if (family == AF_INET) {
        return (toElement4());
    } else if (family == AF_INET6) {
        return (toElement6());
    } else {
        isc_throw(ToElementError, "CfgHosts::toElement: unknown "
                  "address family: " << family);
    }
}

ElementPtr
CfgHosts::toElement4() const {
    CfgHostsList result;
    // Iterate using arbitrary the index 0
    const HostContainerIndex0& idx = hosts_.get<0>();
    for (HostContainerIndex0::const_iterator host = idx.begin();
         host != idx.end(); ++host) {

        // Convert host to element representation
        ElementPtr map = (*host)->toElement4();

        // Push it on the list
        SubnetID subnet_id = (*host)->getIPv4SubnetID();
        result.add(subnet_id, map);
    }
    return (result.externalize());
}

ElementPtr
CfgHosts::toElement6() const {
    CfgHostsList result;
    // Iterate using arbitrary the index 0
    const HostContainerIndex0& idx = hosts_.get<0>();
    for (HostContainerIndex0::const_iterator host = idx.begin();
         host != idx.end(); ++host) {

        // Convert host to Element representation
        ElementPtr map = (*host)->toElement6();

        // Push it on the list
        SubnetID subnet_id = (*host)->getIPv6SubnetID();
        result.add(subnet_id, map);
    }
    return (result.externalize());
}

} // end of namespace isc::dhcp
} // end of namespace isc
