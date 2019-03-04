// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

boost::scoped_ptr<ConfigBackendDHCPv4Mgr>&
ConfigBackendDHCPv4Mgr::getConfigBackendDHCPv4MgrPtr() {
    static boost::scoped_ptr<ConfigBackendDHCPv4Mgr> cb_dhcp4_mgr;
    return (cb_dhcp4_mgr);
}

void
ConfigBackendDHCPv4Mgr::create() {
    getConfigBackendDHCPv4MgrPtr().reset(new ConfigBackendDHCPv4Mgr());
}

void
ConfigBackendDHCPv4Mgr::destroy() {
    getConfigBackendDHCPv4MgrPtr().reset();
}

ConfigBackendDHCPv4Mgr&
ConfigBackendDHCPv4Mgr::instance() {
    boost::scoped_ptr<ConfigBackendDHCPv4Mgr>& cb_dhcp4_mgr = getConfigBackendDHCPv4MgrPtr();
    if (!cb_dhcp4_mgr) {
        create();
    }
    return (*cb_dhcp4_mgr);
}

} // end of isc::dhcp namespace
} // end of isc namespace
