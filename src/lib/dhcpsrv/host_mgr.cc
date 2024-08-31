// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/hosts_log.h>
#include <dhcpsrv/host_data_source_factory.h>

namespace {

/// @brief Convenience function returning a pointer to the hosts configuration
/// for editing.
///
/// This function is called by the @c HostMgr methods requiring access to the
/// host reservations specified in the DHCP server configuration.
///
/// @return A pointer to the non-const hosts reservation configuration.
isc::dhcp::CfgHostsPtr getCfgHostsForEdit() {
    return (isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgHosts());
}

/// @brief Convenience function returning a pointer to the hosts configuration.
///
/// This function is called by the @c HostMgr methods requiring access to the
/// host reservations specified in the DHCP server configuration.
///
/// @return A pointer to the const hosts reservation configuration.
isc::dhcp::ConstCfgHostsPtr getCfgHosts() {
    return (getCfgHostsForEdit());
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {

using namespace isc::asiolink;
using namespace isc::db;

boost::scoped_ptr<HostMgr>&
HostMgr::getHostMgrPtr() {
    static boost::scoped_ptr<HostMgr> host_mgr_ptr;
    return (host_mgr_ptr);
}

void
HostMgr::create() {
    getHostMgrPtr().reset(new HostMgr());
}

void
HostMgr::addBackend(const std::string& access) {
    HostDataSourceFactory::add(getHostMgrPtr()->alternate_sources_, access);
}

bool
HostMgr::delBackend(const std::string& db_type) {
    if (getHostMgrPtr()->cache_ptr_ &&
        getHostMgrPtr()->cache_ptr_->getType() == db_type) {
        getHostMgrPtr()->cache_ptr_.reset();
    }
    return (HostDataSourceFactory::del(getHostMgrPtr()->alternate_sources_,
                                       db_type));
}

bool
HostMgr::delBackend(const std::string& db_type, const std::string& access,
                    bool if_unusable) {
    return (HostDataSourceFactory::del(getHostMgrPtr()->alternate_sources_,
                                       db_type, access, if_unusable));
}

void
HostMgr::delAllBackends() {
    getHostMgrPtr()->alternate_sources_.clear();
}

HostDataSourcePtr
HostMgr::getHostDataSource() const {
    if (alternate_sources_.empty()) {
        return (HostDataSourcePtr());
    }
    return (alternate_sources_[0]);
}

bool
HostMgr::checkCacheBackend(bool logging) {
    if (getHostMgrPtr()->cache_ptr_) {
        return (true);
    }
    HostDataSourceList& sources = getHostMgrPtr()->alternate_sources_;
    if (sources.empty()) {
        return (false);
    }
    CacheHostDataSourcePtr cache_ptr =
        boost::dynamic_pointer_cast<CacheHostDataSource>(sources[0]);
    if (cache_ptr) {
        getHostMgrPtr()->cache_ptr_ = cache_ptr;
        if (logging) {
            LOG_INFO(hosts_logger, HOSTS_CFG_CACHE_HOST_DATA_SOURCE)
                .arg(cache_ptr->getType());
        }
        return (true);
    }
    return (false);
}

HostMgr&
HostMgr::instance() {
    boost::scoped_ptr<HostMgr>& host_mgr_ptr = getHostMgrPtr();
    if (!host_mgr_ptr) {
        create();
    }
    return (*host_mgr_ptr);
}

ConstHostCollection
HostMgr::getAll(const Host::IdentifierType& identifier_type,
                const uint8_t* identifier_begin,
                const size_t identifier_len,
                const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAll(identifier_type, identifier_begin,
                                      identifier_len);
    }
    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus =
                source->getAll(identifier_type, identifier_begin, identifier_len);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll(const Host::IdentifierType& identifier_type,
                const uint8_t* identifier_begin,
                const size_t identifier_len) const {
    return getAll(identifier_type, identifier_begin, identifier_len,
                  HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAll4(const SubnetID& subnet_id, const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAll4(subnet_id);
    }
    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus = source->getAll4(subnet_id);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll4(const SubnetID& subnet_id) const {
    return getAll4(subnet_id, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAll6(const SubnetID& subnet_id, const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAll6(subnet_id);
    }
    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus = source->getAll6(subnet_id);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll6(const SubnetID& subnet_id) const {
    return getAll6(subnet_id, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAllbyHostname(const std::string& hostname, const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAllbyHostname(hostname);
    }
    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus = source->getAllbyHostname(hostname);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAllbyHostname(const std::string& hostname) const {
    return getAllbyHostname(hostname, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAllbyHostname4(const std::string& hostname,
                           const SubnetID& subnet_id,
                           const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAllbyHostname4(hostname, subnet_id);
    }
    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus = source->getAllbyHostname4(hostname,
                                                                    subnet_id);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAllbyHostname4(const std::string& hostname,
                           const SubnetID& subnet_id) const {
    return getAllbyHostname4(hostname, subnet_id, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAllbyHostname6(const std::string& hostname,
                           const SubnetID& subnet_id,
                           const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAllbyHostname6(hostname, subnet_id);
    }
    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus = source->getAllbyHostname6(hostname,
                                                                    subnet_id);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAllbyHostname6(const std::string& hostname,
                           const SubnetID& subnet_id) const {
    return getAllbyHostname6(hostname, subnet_id, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getPage4(const SubnetID& subnet_id,
                  size_t& source_index,
                  uint64_t lower_host_id,
                  const HostPageSize& page_size) const {
    // Return empty if (and only if) sources are exhausted.
    if (source_index > alternate_sources_.size()) {
        return (ConstHostCollection());
    }

    ConstHostCollection hosts;
    // Source index 0 means config file.
    if (source_index == 0) {
        hosts = getCfgHosts()->
            getPage4(subnet_id, source_index, lower_host_id, page_size);
    } else {
        hosts = alternate_sources_[source_index - 1]->
            getPage4(subnet_id, source_index, lower_host_id, page_size);
    }

    // When got something return it.
    if (!hosts.empty()) {
        return (hosts);
    }

    // Nothing from this source: try the next one.
    // Note the recursion is limited to the number of sources in all cases.
    ++source_index;
    return (getPage4(subnet_id, source_index, 0UL, page_size));
}

ConstHostCollection
HostMgr::getPage6(const SubnetID& subnet_id,
                  size_t& source_index,
                  uint64_t lower_host_id,
                  const HostPageSize& page_size) const {
    // Return empty if (and only if) sources are exhausted.
    if (source_index > alternate_sources_.size()) {
        return (ConstHostCollection());
    }

    ConstHostCollection hosts;
    // Source index 0 means config file.
    if (source_index == 0) {
        hosts = getCfgHosts()->
            getPage6(subnet_id, source_index, lower_host_id, page_size);
    } else {
        hosts = alternate_sources_[source_index - 1]->
            getPage6(subnet_id, source_index, lower_host_id, page_size);
    }

    // When got something return it.
    if (!hosts.empty()) {
        return (hosts);
    }

    // Nothing from this source: try the next one.
    // Note the recursion is limited to the number of sources in all cases.
    ++source_index;
    return (getPage6(subnet_id, source_index, 0UL, page_size));
}

ConstHostCollection
HostMgr::getPage4(size_t& source_index,
                  uint64_t lower_host_id,
                  const HostPageSize& page_size) const {
    // Return empty if (and only if) sources are exhausted.
    if (source_index > alternate_sources_.size()) {
        return (ConstHostCollection());
    }

    ConstHostCollection hosts;
    // Source index 0 means config file.
    if (source_index == 0) {
        hosts = getCfgHosts()->
            getPage4(source_index, lower_host_id, page_size);
    } else {
        hosts = alternate_sources_[source_index - 1]->
            getPage4(source_index, lower_host_id, page_size);
    }

    // When got something return it.
    if (!hosts.empty()) {
        return (hosts);
    }

    // Nothing from this source: try the next one.
    // Note the recursion is limited to the number of sources in all cases.
    ++source_index;
    return (getPage4(source_index, 0UL, page_size));
}

ConstHostCollection
HostMgr::getPage6(size_t& source_index,
                  uint64_t lower_host_id,
                  const HostPageSize& page_size) const {
    // Return empty if (and only if) sources are exhausted.
    if (source_index > alternate_sources_.size()) {
        return (ConstHostCollection());
    }

    ConstHostCollection hosts;
    // Source index 0 means config file.
    if (source_index == 0) {
        hosts = getCfgHosts()->
            getPage6(source_index, lower_host_id, page_size);
    } else {
        hosts = alternate_sources_[source_index - 1]->
            getPage6(source_index, lower_host_id, page_size);
    }

    // When got something return it.
    if (!hosts.empty()) {
        return (hosts);
    }

    // Nothing from this source: try the next one.
    // Note the recursion is limited to the number of sources in all cases.
    ++source_index;
    return (getPage6(source_index, 0UL, page_size));
}

ConstHostCollection
HostMgr::getAll4(const IOAddress& address, const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAll4(address);
    }
    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus = source->getAll4(address);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll4(const IOAddress& address) const {
    return getAll4(address, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostPtr
HostMgr::get4Any(const SubnetID& subnet_id,
                 const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin,
                 const size_t identifier_len,
                 const HostMgrOperationTarget target) const {
    ConstHostPtr host;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        host = getCfgHosts()->get4(subnet_id, identifier_type,
                                   identifier_begin, identifier_len);
    }

    // Found it in the config file, there are no backends configured, or
    // querying them is disabled?
    // Then we're done here.
    if (host || alternate_sources_.empty() || !(target & HostMgrOperationTarget::ALTERNATE_SOURCES)) {
        return (host);
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER)
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));

    // Try to find a host in each configured backend. We return as soon
    // as we find first hit.
    for (auto const& source : alternate_sources_) {
        host = source->get4(subnet_id, identifier_type,
                           identifier_begin, identifier_len);

        if (host) {
            LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                      HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_HOST)
                .arg(subnet_id)
                .arg(Host::getIdentifierAsText(identifier_type,
                                               identifier_begin,
                                               identifier_len))
                .arg(source->getType())
                .arg(host->toText());

            if (source != cache_ptr_) {
                cache(host);
            }
            return (host);
        }
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
              HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_NULL)
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));
    return (ConstHostPtr());
}

ConstHostPtr
HostMgr::get4Any(const SubnetID& subnet_id,
                 const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin,
                 const size_t identifier_len) const {
    return get4Any(subnet_id, identifier_type, identifier_begin, identifier_len,
                   HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id,
              const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin,
              const size_t identifier_len,
              const HostMgrOperationTarget target) const {
    ConstHostPtr host = get4Any(subnet_id, identifier_type,
                                identifier_begin, identifier_len, target);
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    } else if (!host && negative_caching_) {
        cacheNegative(subnet_id, SubnetID(SUBNET_ID_UNUSED),
                      identifier_type, identifier_begin, identifier_len);
    }
    return (host);
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id,
              const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin,
              const size_t identifier_len) const {
    return get4(subnet_id, identifier_type, identifier_begin, identifier_len,
                HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id,
              const asiolink::IOAddress& address,
              const HostMgrOperationTarget target) const {
    ConstHostPtr host;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        host = getCfgHosts()->get4(subnet_id, address);
    }

    if (host || alternate_sources_.empty() || !(target & HostMgrOperationTarget::ALTERNATE_SOURCES)) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_ADDRESS4)
        .arg(subnet_id)
        .arg(address.toText());
    for (auto const& source : alternate_sources_) {
        host = source->get4(subnet_id, address);
        if (host && host->getNegative()) {
            return (ConstHostPtr());
        }
        if (host && source != cache_ptr_) {
            cache(host);
        }
        if (host) {
            return (host);
        }
    }
    return (ConstHostPtr());
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id,
              const asiolink::IOAddress& address) const {
    return get4(subnet_id, address, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAll4(const SubnetID& subnet_id,
                 const asiolink::IOAddress& address,
                 const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAll4(subnet_id, address);
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
                HOSTS_MGR_ALTERNATE_GET_ALL_SUBNET_ID_ADDRESS4)
            .arg(subnet_id)
            .arg(address.toText());

        for (auto const& source : alternate_sources_) {
            auto hosts_plus = source->getAll4(subnet_id, address);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll4(const SubnetID& subnet_id,
                 const asiolink::IOAddress& address) const {
    return getAll4(subnet_id, address, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostPtr
HostMgr::get6(const IOAddress& prefix, const uint8_t prefix_len,
              const HostMgrOperationTarget target) const {
    ConstHostPtr host;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        host = getCfgHosts()->get6(prefix, prefix_len);
    }
    if (host || alternate_sources_.empty() || !(target & HostMgrOperationTarget::ALTERNATE_SOURCES)) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE, HOSTS_MGR_ALTERNATE_GET6_PREFIX)
        .arg(prefix.toText())
        .arg(static_cast<int>(prefix_len));
    for (auto const& source : alternate_sources_) {
        host = source->get6(prefix, prefix_len);
        if (host && host->getNegative()) {
            return (ConstHostPtr());
        }
        if (host && source != cache_ptr_) {
            cache(host);
        }
        if (host) {
            return (host);
        }
    }
    return (ConstHostPtr());
}

ConstHostPtr
HostMgr::get6(const IOAddress& prefix, const uint8_t prefix_len) const {
    return get6(prefix, prefix_len, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostPtr
HostMgr::get6Any(const SubnetID& subnet_id,
                 const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin,
                 const size_t identifier_len,
                 const HostMgrOperationTarget target) const {
    ConstHostPtr host;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        host = getCfgHosts()->get6(subnet_id, identifier_type,
                                   identifier_begin, identifier_len);
    }
    if (host || alternate_sources_.empty() || !(target & HostMgrOperationTarget::ALTERNATE_SOURCES)) {
        return (host);
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER)
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));

    for (auto const& source : alternate_sources_) {
        host = source->get6(subnet_id, identifier_type,
                           identifier_begin, identifier_len);

        if (host) {
                LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                          HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_HOST)
                    .arg(subnet_id)
                    .arg(Host::getIdentifierAsText(identifier_type,
                                                   identifier_begin,
                                                   identifier_len))
                    .arg(source->getType())
                    .arg(host->toText());

                if (source != cache_ptr_) {
                    cache(host);
                }
                return (host);
        }
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
              HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_NULL)
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));

    return (ConstHostPtr());
}

ConstHostPtr
HostMgr::get6Any(const SubnetID& subnet_id,
                 const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin,
                 const size_t identifier_len) const {
    return get6Any(subnet_id, identifier_type, identifier_begin, identifier_len,
                   HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id,
              const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin,
              const size_t identifier_len,
              const HostMgrOperationTarget target) const {
    ConstHostPtr host = get6Any(subnet_id, identifier_type,
                                identifier_begin, identifier_len, target);
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    } else if (!host && negative_caching_) {
        cacheNegative(SubnetID(SUBNET_ID_UNUSED), subnet_id,
                      identifier_type, identifier_begin, identifier_len);
    }
    return (host);
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id,
              const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin,
              const size_t identifier_len) const {
    return get6(subnet_id, identifier_type, identifier_begin, identifier_len,
                HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id,
              const asiolink::IOAddress& addr,
              const HostMgrOperationTarget target) const {
    ConstHostPtr host;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        host = getCfgHosts()->get6(subnet_id, addr);
    }
    if (host || alternate_sources_.empty() || !(target & HostMgrOperationTarget::ALTERNATE_SOURCES)) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6)
        .arg(subnet_id)
        .arg(addr.toText());
    for (auto const& source : alternate_sources_) {
        host = source->get6(subnet_id, addr);
        if (host && host->getNegative()) {
            return (ConstHostPtr());
        }
        if (host && source != cache_ptr_) {
            cache(host);
        }
        if (host) {
            return (host);
        }
    }
    return (ConstHostPtr());
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id,
              const asiolink::IOAddress& addr) const {
    return get6(subnet_id, addr, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAll6(const SubnetID& subnet_id,
                 const asiolink::IOAddress& address,
                 const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;

    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAll6(subnet_id, address);
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
                HOSTS_MGR_ALTERNATE_GET_ALL_SUBNET_ID_ADDRESS6)
            .arg(subnet_id)
            .arg(address.toText());

        for (auto const& source : alternate_sources_) {
            auto hosts_plus = source->getAll6(subnet_id, address);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll6(const SubnetID& subnet_id,
                 const asiolink::IOAddress& address) const {
        return getAll6(subnet_id, address, HostMgrOperationTarget::ALL_SOURCES);
}

ConstHostCollection
HostMgr::getAll6(const IOAddress& address) const {
        return (getAll6(address, HostMgrOperationTarget::ALL_SOURCES));
}

ConstHostCollection
HostMgr::getAll6(const IOAddress& address, const HostMgrOperationTarget target) const {
    ConstHostCollection hosts;
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        hosts = getCfgHosts()->getAll6(address);
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        for (auto const& source : alternate_sources_) {
            ConstHostCollection hosts_plus = source->getAll6(address);
            hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
        }
    }

    return (hosts);
}

void
HostMgr::add(const HostPtr& host, const HostMgrOperationTarget target) {
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        getCfgHostsForEdit()->add(host);
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        // Don't throw if all targets were selected.
        if (alternate_sources_.empty() && !(target & HostMgrOperationTarget::PRIMARY_SOURCE)) {
            isc_throw(NoHostDataSourceManager, "Unable to add new host because there is "
                    "no hosts-database configured.");

        }

        for (auto const& source : alternate_sources_) {
            source->add(host);
        }
    }

    // If no backend throws the host should be cached.
    if (cache_ptr_) {
        cache(host);
    }
}

void
HostMgr::add(const HostPtr& host) {
    return add(host, HostMgrOperationTarget::ALTERNATE_SOURCES);
}

bool
HostMgr::del(const SubnetID& subnet_id, const asiolink::IOAddress& addr,
             const HostMgrOperationTarget target) {
    size_t erased = false;

    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        erased = getCfgHostsForEdit()->del(subnet_id, addr);
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        // Don't throw if all targets were selected.
        if (alternate_sources_.empty() && !(target & HostMgrOperationTarget::PRIMARY_SOURCE)) {
            isc_throw(NoHostDataSourceManager, "Unable to delete a host because there is "
                    "no hosts-database configured.");
        }

        for (auto const& source : alternate_sources_) {
            bool alternate_erased = source->del(subnet_id, addr);
            erased = alternate_erased || erased;
        }
    }

    return (erased);
}

bool
HostMgr::del(const SubnetID& subnet_id, const asiolink::IOAddress& addr) {
    return del(subnet_id, addr, HostMgrOperationTarget::ALTERNATE_SOURCES);
}

bool
HostMgr::del4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin, const size_t identifier_len,
              const HostMgrOperationTarget target) {
    bool success = false;

    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        if (getCfgHostsForEdit()->del4(subnet_id, identifier_type,
                                       identifier_begin, identifier_len)) {
            success = true;
        }
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        // Don't throw if all targets were selected.
        if (alternate_sources_.empty() && !(target & HostMgrOperationTarget::PRIMARY_SOURCE)) {
            isc_throw(NoHostDataSourceManager, "Unable to delete a host because there is "
                    "no hosts-database configured.");
        }

        for (auto const& source : alternate_sources_) {
            if (source->del4(subnet_id, identifier_type,
                             identifier_begin, identifier_len)) {
                success = true;
            }
        }
    }
    return (success);
}

bool
HostMgr::del4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin, const size_t identifier_len) {
    return del4(subnet_id, identifier_type, identifier_begin, identifier_len,
                HostMgrOperationTarget::ALTERNATE_SOURCES);
}

bool
HostMgr::del6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin, const size_t identifier_len,
              const HostMgrOperationTarget target) {
    bool success = false;

    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        if (getCfgHostsForEdit()->del6(subnet_id, identifier_type,
                                       identifier_begin, identifier_len)) {
            success = true;
        }
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        // Don't throw if all targets were selected.
        if (alternate_sources_.empty() && !(target & HostMgrOperationTarget::PRIMARY_SOURCE)) {
            isc_throw(NoHostDataSourceManager, "Unable to delete a host because there is "
                    "no hosts-database configured.");
        }

        for (auto const& source : alternate_sources_) {
            if (source->del6(subnet_id, identifier_type,
                             identifier_begin, identifier_len)) {
                success = true;
            }
        }
    }
    return (success);
}

bool
HostMgr::del6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin, const size_t identifier_len) {
    return del6(subnet_id, identifier_type, identifier_begin, identifier_len,
                HostMgrOperationTarget::ALTERNATE_SOURCES);
}

void
HostMgr::update(HostPtr const& host, const HostMgrOperationTarget target) {
    if (target & HostMgrOperationTarget::PRIMARY_SOURCE) {
        getCfgHostsForEdit()->update(host);
    }

    if (target & HostMgrOperationTarget::ALTERNATE_SOURCES) {
        // Don't throw if all targets were selected.
        if (alternate_sources_.empty() && !(target & HostMgrOperationTarget::PRIMARY_SOURCE)) {
            isc_throw(NoHostDataSourceManager,
                    "Unable to update existing host because there is no hosts-database configured.");
        }

        for (HostDataSourcePtr const& source : alternate_sources_) {
            source->update(host);
        }
    }

    // If no backend throws the host should be cached.
    if (cache_ptr_) {
        cache(host);
    }
}

void
HostMgr::update(HostPtr const& host) {
    update(host, HostMgrOperationTarget::ALTERNATE_SOURCES);
}

void
HostMgr::cache(ConstHostPtr host) const {
    if (cache_ptr_) {
        // Need a real host.
        if (!host || host->getNegative()) {
            return;
        }
        // Replace any existing value.
        // Don't check the result as it does not matter?
        cache_ptr_->insert(host, true);
    }
}

void
HostMgr::cacheNegative(const SubnetID& ipv4_subnet_id,
                       const SubnetID& ipv6_subnet_id,
                       const Host::IdentifierType& identifier_type,
                       const uint8_t* identifier_begin,
                       const size_t identifier_len) const {
    if (cache_ptr_ && negative_caching_) {
        HostPtr host(new Host(identifier_begin, identifier_len,
                              identifier_type,
                              ipv4_subnet_id, ipv6_subnet_id,
                              IOAddress::IPV4_ZERO_ADDRESS()));
        host->setNegative(true);
        // Don't replace any existing value.
        // nor matter if it fails.
        cache_ptr_->insert(host, false);
    }
}

bool
HostMgr::setIPReservationsUnique(const bool unique) {
    // Iterate over the alternate sources first, because they may include those
    // for which the new setting is not supported.
    for (auto const& source : alternate_sources_) {
        if (!source->setIPReservationsUnique(unique)) {
            // One of the sources does not support this new mode of operation.
            // Let's log a warning and back off the changes to the default
            // setting which should always be supported.
            ip_reservations_unique_ = true;
            LOG_WARN(hosts_logger, HOSTS_MGR_NON_UNIQUE_IP_UNSUPPORTED)
                .arg(source->getType());
            for (auto const& src : alternate_sources_) {
                src->setIPReservationsUnique(true);
            }
            return (false);
        }
    }
    // Successfully configured the HostMgr to use the new setting.
    // Remember this setting so we can return it via the
    // getIPReservationsUnique.
    ip_reservations_unique_ = unique;
    return (true);
}

} // end of isc::dhcp namespace
} // end of isc namespace
