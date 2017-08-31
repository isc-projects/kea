// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcpsrv/network.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

ElementPtr
Network::toElement() const {
    ElementPtr map = Element::createMap();

    // Set interface
    const std::string& iface = getIface();
    if (!iface.empty()) {
        map->set("interface", Element::create(iface));
    }

    // Set options
    ConstCfgOptionPtr opts = getCfgOption();
    map->set("option-data", opts->toElement());

    return (map);
}

} // end of namespace isc::dhcp
} // end of namespace isc
