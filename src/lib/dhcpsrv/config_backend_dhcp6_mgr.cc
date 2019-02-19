// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

boost::scoped_ptr<ConfigBackendDHCPv6Mgr>&
ConfigBackendDHCPv6Mgr::getConfigBackendDHCPv6MgrPtr() {
    static boost::scoped_ptr<ConfigBackendDHCPv6Mgr> cb_dhcp6_mgr;
    return (cb_dhcp6_mgr);
}

void
ConfigBackendDHCPv6Mgr::create() {
    getConfigBackendDHCPv6MgrPtr().reset(new ConfigBackendDHCPv6Mgr());
}

void
ConfigBackendDHCPv6Mgr::destroy() {
    getConfigBackendDHCPv6MgrPtr().reset();
}

ConfigBackendDHCPv6Mgr&
ConfigBackendDHCPv6Mgr::instance() {
    boost::scoped_ptr<ConfigBackendDHCPv6Mgr>& cb_dhcp6_mgr = getConfigBackendDHCPv6MgrPtr();
    if (!cb_dhcp6_mgr) {
        create();
    }
    return (*cb_dhcp6_mgr);
}

} // end of isc::dhcp namespace
} // end of isc namespace
