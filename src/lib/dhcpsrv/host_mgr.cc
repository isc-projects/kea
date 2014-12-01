// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>

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
HostMgr::create(const std::string&) {
    getHostMgrPtr().reset(new HostMgr());
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
    return (getCfgHosts()->getAll(hwaddr, duid));
}

ConstHostCollection
HostMgr::getAll4(const IOAddress& address) const {
    return (getCfgHosts()->getAll4(address));
}

ConstHostPtr
HostMgr::get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
              const DuidPtr& duid) const {
    return (getCfgHosts()->get4(subnet_id, hwaddr, duid));
}

ConstHostPtr
HostMgr::get6(const SubnetID& subnet_id, const DuidPtr& duid,
               const HWAddrPtr& hwaddr) const {
    return (getCfgHosts()->get6(subnet_id, duid, hwaddr));
}

ConstHostPtr
HostMgr::get6(const IOAddress& prefix, const uint8_t prefix_len) const {
    return (getCfgHosts()->get6(prefix, prefix_len));
}

void
HostMgr::add(const HostPtr&) {
    isc_throw(isc::NotImplemented, "HostMgr::add is not implemented");
}

} // end of isc::dhcp namespace
} // end of isc namespace
