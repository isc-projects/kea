// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Convenience function returning a pointer to the hosts configuration.
///
/// This function is called by the @c HostMgr methods requiring access to the
/// host reservations specified in the DHCP server configuration.
///
/// @return A pointer to the const hosts reservation configuration.
isc::dhcp::ConstCfgHostsPtr getCfgHosts() {
    return (isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgHosts());
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {

using namespace isc::asiolink;

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
HostMgr::addSource(const std::string& access) {
    HostDataSourceFactory::add(getHostMgrPtr()->alternate_sources_, access);
}

bool
HostMgr::delSource(const std::string& db_type) {
    return (HostDataSourceFactory::del(getHostMgrPtr()->alternate_sources_, db_type));
}

void
HostMgr::delAllSources() {
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
HostMgr::checkCacheSource(bool logging) {
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
HostMgr::getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid) const {
    ConstHostCollection hosts = getCfgHosts()->getAll(hwaddr, duid);
    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        ConstHostCollection hosts_plus = (*it)->getAll(hwaddr, duid);
        hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll(const Host::IdentifierType& identifier_type,
                const uint8_t* identifier_begin,
                const size_t identifier_len) const {
    ConstHostCollection hosts = getCfgHosts()->getAll(identifier_type,
                                                      identifier_begin,
                                                      identifier_len);
    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        ConstHostCollection hosts_plus =
            (*it)->getAll(identifier_type, identifier_begin, identifier_len);
        hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
    }
    return (hosts);
}


ConstHostCollection
HostMgr::getAll4(const IOAddress& address) const {
    ConstHostCollection hosts = getCfgHosts()->getAll4(address);
    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        ConstHostCollection hosts_plus = (*it)->getAll4(address);
        hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
    }
    return (hosts);
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
              const DuidPtr& duid) const {
    ConstHostPtr host = getCfgHosts()->get4(subnet_id, hwaddr, duid);
    if (host || alternate_sources_.empty()) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_HWADDR_DUID)
        .arg(subnet_id)
        .arg(hwaddr ? hwaddr->toText() : "(no-hwaddr)")
        .arg(duid ? duid->toText() : "(duid)");
    for (auto it = alternate_sources_.begin();
         !host && it != alternate_sources_.end(); ++it) {
        if (hwaddr) {
            host = (*it)->get4(subnet_id, hwaddr, DuidPtr());
        }
        if (!host && duid) {
            host = (*it)->get4(subnet_id, HWAddrPtr(), duid);
        }
        if (host && cache_ptr_ && (it != alternate_sources_.begin())) {
            cache(host);
        }
    }
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    }
    return (host);
}

ConstHostPtr
HostMgr::get4Any(const SubnetID& subnet_id,
                 const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin,
                 const size_t identifier_len) const {
    ConstHostPtr host = getCfgHosts()->get4(subnet_id, identifier_type,
                                            identifier_begin, identifier_len);

    // Found it in the config file or there are no backends configured?
    // Then we're done here.
    if (host || alternate_sources_.empty()) {
        return (host);
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER)
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));

    // Try to find a host in each configured backend. We return as soon
    // as we find first hit.
    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        host = (*it)->get4(subnet_id, identifier_type,
                           identifier_begin, identifier_len);

        if (host) {
            LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                      HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_HOST)
                .arg(subnet_id)
                .arg(Host::getIdentifierAsText(identifier_type,
                                               identifier_begin,
                                               identifier_len))
                .arg((*it)->getType())
                .arg(host->toText());

            if (cache_ptr_ && (it != alternate_sources_.begin())) {
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
    // @todo: remove this
    if (negative_caching_) {
        cacheNegative(subnet_id, SubnetID(0),
                      identifier_type, identifier_begin, identifier_len);
    }
    return (host);
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id,
              const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin,
              const size_t identifier_len) const {
    ConstHostPtr host = get4Any(subnet_id, identifier_type,
                                identifier_begin, identifier_len);
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    }
    return (host);
}
    
ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id,
              const asiolink::IOAddress& address) const {
    ConstHostPtr host = getCfgHosts()->get4(subnet_id, address);
    if (host || alternate_sources_.empty()) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_ADDRESS4)
        .arg(subnet_id)
        .arg(address.toText());
    for (auto it = alternate_sources_.begin();
         !host && it != alternate_sources_.end(); ++it) {
        host = (*it)->get4(subnet_id, address);
        if (host && cache_ptr_ && (it != alternate_sources_.begin())) {
            cache(host);
        }
    }
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    }
    return (host);
}


ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id, const DuidPtr& duid,
               const HWAddrPtr& hwaddr) const {
    ConstHostPtr host = getCfgHosts()->get6(subnet_id, duid, hwaddr);
    if (host || alternate_sources_.empty()) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_DUID_HWADDR)
        .arg(subnet_id)
        .arg(duid ? duid->toText() : "(duid)")
        .arg(hwaddr ? hwaddr->toText() : "(no-hwaddr)");

    for (auto it = alternate_sources_.begin();
         !host && it != alternate_sources_.end(); ++it) {
        if (duid) {
            host = (*it)->get6(subnet_id, duid, HWAddrPtr());
        }
        if (!host && hwaddr) {
            host = (*it)->get6(subnet_id, DuidPtr(), hwaddr);
        }
        if (host && cache_ptr_ && (it != alternate_sources_.begin())) {
            cache(host);
        }
    }
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    }
    return (host);
}

ConstHostPtr
HostMgr::get6(const IOAddress& prefix, const uint8_t prefix_len) const {
    ConstHostPtr host = getCfgHosts()->get6(prefix, prefix_len);
    if (host || alternate_sources_.empty()) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET6_PREFIX)
        .arg(prefix.toText())
        .arg(static_cast<int>(prefix_len));
    for (auto it = alternate_sources_.begin();
         !host && it != alternate_sources_.end(); ++it) {
        host = (*it)->get6(prefix, prefix_len);
        if (host && cache_ptr_ && (it != alternate_sources_.begin())) {
            cache(host);
        }
    }
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    }
    return (host);
}

ConstHostPtr
HostMgr::get6Any(const SubnetID& subnet_id,
                 const Host::IdentifierType& identifier_type,
                 const uint8_t* identifier_begin,
                 const size_t identifier_len) const {
    ConstHostPtr host = getCfgHosts()->get6(subnet_id, identifier_type,
                                            identifier_begin, identifier_len);
    if (host || alternate_sources_.empty()) {
        return (host);
    }

    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER)
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));

    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {

        host = (*it)->get6(subnet_id, identifier_type,
                           identifier_begin, identifier_len);

        if (host) {
                LOG_DEBUG(hosts_logger, HOSTS_DBG_RESULTS,
                          HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_HOST)
                    .arg(subnet_id)
                    .arg(Host::getIdentifierAsText(identifier_type,
                                                   identifier_begin,
                                                   identifier_len))
                    .arg((*it)->getType())
                    .arg(host->toText());

                if (cache_ptr_ && (it != alternate_sources_.begin())) {
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

    // @todo: remove this
    if (negative_caching_) {
        cacheNegative(SubnetID(0), subnet_id,
                      identifier_type, identifier_begin, identifier_len);
    }

    return (host);
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id,
              const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin,
              const size_t identifier_len) const {
    ConstHostPtr host = get6Any(subnet_id, identifier_type,
                                identifier_begin, identifier_len);
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    }
    return (host);
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id,
              const asiolink::IOAddress& addr) const {
    ConstHostPtr host = getCfgHosts()->get6(subnet_id, addr);
    if (host || alternate_sources_.empty()) {
        return (host);
    }
    LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
              HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6)
        .arg(subnet_id)
        .arg(addr.toText());
    for (auto it = alternate_sources_.begin();
         !host && it != alternate_sources_.end(); ++it) {
        host = (*it)->get6(subnet_id, addr);
        if (host && cache_ptr_ && (it != alternate_sources_.begin())) {
            cache(host);
        }
    }
    if (host && host->getNegative()) {
        return (ConstHostPtr());
    }
    return (host);
}

void
HostMgr::add(const HostPtr& host) {
    if (alternate_sources_.empty()) {
        isc_throw(NoHostDataSourceManager, "Unable to add new host because there is "
                  "no hosts-database configured.");
    }
    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        (*it)->add(host);
    }
    // If no backend throws it should be cached.
    if (cache_ptr_) {
        cache(host);
    }
}

bool
HostMgr::del(const SubnetID& subnet_id, const asiolink::IOAddress& addr) {
    if (alternate_sources_.empty()) {
        isc_throw(NoHostDataSourceManager, "Unable to delete a host because there is "
                  "no hosts-database configured.");
    }

    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        if ((*it)->del(subnet_id, addr)) {
            return (true);
        }
    }
    return (false);
}

bool
HostMgr::del4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin, const size_t identifier_len) {
    if (alternate_sources_.empty()) {
        isc_throw(NoHostDataSourceManager, "Unable to delete a host because there is "
                  "no hosts-database configured.");
    }

    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        if ((*it)->del4(subnet_id, identifier_type,
                        identifier_begin, identifier_len)) {
            return (true);
        }
    }
    return (false);
}

bool
HostMgr::del6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
              const uint8_t* identifier_begin, const size_t identifier_len) {
    if (alternate_sources_.empty()) {
        isc_throw(NoHostDataSourceManager, "unable to delete a host because there is "
                  "no alternate host data source present");
    }

    for (auto it = alternate_sources_.begin();
         it != alternate_sources_.end(); ++it) {
        if ((*it)->del6(subnet_id, identifier_type,
                        identifier_begin, identifier_len)) {
            return (true);
        }
    }
    return (false);
}

void
HostMgr::cache(ConstHostPtr host) const {
    if (cache_ptr_) {
        // Replace any existing value.
        int overwrite = 0;
        // Don't check the result as it does not matter?
        cache_ptr_->insert(host, overwrite);
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
        int overwrite = -1;
        // nor matter if it fails.
        cache_ptr_->insert(host, overwrite);
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
