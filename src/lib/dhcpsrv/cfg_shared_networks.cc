// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_shared_networks.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

bool
CfgSharedNetworks4::hasNetworkWithServerId(const IOAddress& server_id) const {
    const auto& index = networks_.get<SharedNetworkServerIdIndexTag>();
    auto network_it = index.find(server_id);
    return (network_it != index.cend());
}

} // end of namespace isc::dhcp
} // end of namespace isc
