// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CTL_DHCP4_H
#define CB_CTL_DHCP4_H

#include <process/cb_ctl_base.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>

namespace isc {
namespace dhcp {

class CBControlDHCPv4 : public process::CBControlBase<ConfigBackendDHCPv4Mgr> {
public:

    CBControlDHCPv4();
};


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CB_CTL_DHCP4_H
