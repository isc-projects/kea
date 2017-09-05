// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcpsrv/network.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

bool
Network::clientSupported(const isc::dhcp::ClientClasses& classes) const {
    if (white_list_.empty()) {
        // There is no class defined for this network, so we do
        // support everyone.
        return (true);
    }

    for (ClientClasses::const_iterator it = white_list_.begin();
         it != white_list_.end(); ++it) {
        if (classes.contains(*it)) {
            return (true);
        }
    }

    return (false);
}

void
Network::allowClientClass(const isc::dhcp::ClientClass& class_name) {
    white_list_.insert(class_name);
}

ElementPtr
Network::toElement() const {
    ElementPtr map = Element::createMap();

    // Set interface
    const std::string& iface = getIface();
    if (!iface.empty()) {
        map->set("interface", Element::create(iface));
    }

    // Set relay info
    const RelayInfo& relay_info = getRelayInfo();
    ElementPtr relay = Element::createMap();
    relay->set("ip-address", Element::create(relay_info.addr_.toText()));
    map->set("relay", relay);

    // Set client-class
    const ClientClasses& cclasses = getClientClasses();
    if (cclasses.size() > 1) {
        isc_throw(ToElementError, "client-class has too many items: "
                  << cclasses.size());
    } else if (!cclasses.empty()) {
        map->set("client-class", Element::create(*cclasses.cbegin()));
    }

    // Set renew-timer
    map->set("renew-timer",
             Element::create(static_cast<long long>
                                 (getT1().get())));
    // Set rebind-timer
    map->set("rebind-timer",
             Element::create(static_cast<long long>
                                 (getT2().get())));
    // Set valid-lifetime
    map->set("valid-lifetime",
             Element::create(static_cast<long long>
                                 (getValid().get())));

    // Set options
    ConstCfgOptionPtr opts = getCfgOption();
    map->set("option-data", opts->toElement());

    return (map);
}

} // end of namespace isc::dhcp
} // end of namespace isc
