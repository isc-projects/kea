// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
HostMgr::create(const std::string& access) {
    getHostMgrPtr().reset(new HostMgr());

    if (!access.empty()) {
        // If the user specified parameters, let's pass them to the create
        // method. It will destroy any prior instances and will create
        // the new one.
        HostDataSourceFactory::create(access);
    } else {
        // Ok, no parameters were specified. We should destroy the existing
        // insteance.
        HostDataSourceFactory::destroy();
    }

    // Now store the host data source pointer. It may be NULL. That's ok as
    // NULL value indicates that there's no host data source configured.
    getHostMgrPtr()->alternate_source_ =
        HostDataSourceFactory::getHostDataSourcePtr();
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
    if (alternate_source_) {
        ConstHostCollection hosts_plus = alternate_source_->getAll(hwaddr, duid);
        hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
    }
    return (hosts);
}

ConstHostCollection
HostMgr::getAll4(const IOAddress& address) const {
    ConstHostCollection hosts = getCfgHosts()->getAll4(address);
    if (alternate_source_) {
        ConstHostCollection hosts_plus = alternate_source_->getAll4(address);
        hosts.insert(hosts.end(), hosts_plus.begin(), hosts_plus.end());
    }
    return (hosts);
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
              const DuidPtr& duid) const {
    ConstHostPtr host = getCfgHosts()->get4(subnet_id, hwaddr, duid);
    if (!host && alternate_source_) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
                  HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_HWADDR_DUID)
            .arg(subnet_id)
            .arg(hwaddr ? hwaddr->toText() : "(no-hwaddr)")
            .arg(duid ? duid->toText() : "(duid)");
        if (duid) {
            host = alternate_source_->get4(subnet_id, HWAddrPtr(), duid);
        }
        if (!host && hwaddr) {
            host = alternate_source_->get4(subnet_id, hwaddr, DuidPtr());
        }
    }
    return (host);
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id,
              const asiolink::IOAddress& address) const {
    ConstHostPtr host = getCfgHosts()->get4(subnet_id, address);
    if (!host && alternate_source_) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
                  HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_ADDRESS4)
            .arg(subnet_id)
            .arg(address.toText());
        host = alternate_source_->get4(subnet_id, address);
    }
    return (host);
}


ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id, const DuidPtr& duid,
               const HWAddrPtr& hwaddr) const {
    ConstHostPtr host = getCfgHosts()->get6(subnet_id, duid, hwaddr);
    if (!host && alternate_source_) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
                  HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_DUID_HWADDR)
            .arg(subnet_id)
            .arg(duid ? duid->toText() : "(duid)")
            .arg(hwaddr ? hwaddr->toText() : "(no-hwaddr)");
        if (duid) {
            host = alternate_source_->get6(subnet_id, duid, HWAddrPtr());
        }
        if (!host && hwaddr) {
            host = alternate_source_->get6(subnet_id, DuidPtr(), hwaddr);
        }
    }
    return (host);
}

ConstHostPtr
HostMgr::get6(const IOAddress& prefix, const uint8_t prefix_len) const {
    ConstHostPtr host = getCfgHosts()->get6(prefix, prefix_len);
    if (!host && alternate_source_) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
                  HOSTS_MGR_ALTERNATE_GET6_PREFIX)
            .arg(prefix.toText())
            .arg(static_cast<int>(prefix_len));
        host = alternate_source_->get6(prefix, prefix_len);
    }
    return (host);
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id,
              const asiolink::IOAddress& addr) const {
    ConstHostPtr host = getCfgHosts()->get6(subnet_id, addr);
    if (!host && alternate_source_) {
        LOG_DEBUG(hosts_logger, HOSTS_DBG_TRACE,
                  HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6)
            .arg(subnet_id)
            .arg(addr.toText());
        host = alternate_source_->get6(subnet_id, addr);
    }
    return (host);
}

void
HostMgr::add(const HostPtr&) {
    isc_throw(isc::NotImplemented, "HostMgr::add is not implemented");
}

} // end of isc::dhcp namespace
} // end of isc namespace
