// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cb_ctl_dhcp4.h>

using namespace isc::process;

namespace isc {
namespace dhcp {

CBControlDHCPv4::CBControlDHCPv4()
    : CBControlBase<ConfigBackendDHCPv4Mgr>() {
}

} // end of namespace isc::dhcp
} // end of namespace isc
