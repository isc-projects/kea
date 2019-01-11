// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/network.h>
#include <boost/pointer_cast.hpp>

using namespace isc::asiolink;
using namespace isc::data;

namespace isc {
namespace dhcp {

void
Network::RelayInfo::addAddress(const asiolink::IOAddress& addr) {
    if (containsAddress(addr)) {
        isc_throw (BadValue, "RelayInfo already contains address: "
                   << addr.toText());
    }

    addresses_.push_back(addr);
}

bool
Network::RelayInfo::hasAddresses() const {
    return (!addresses_.empty());
}

bool
Network::RelayInfo::containsAddress(const asiolink::IOAddress& addr) const {
    for (auto address = addresses_.begin(); address != addresses_.end();
         ++address) {
        if ((*address) == addr) {
            return (true);
        }
    }

    return (false);
}

const IOAddressList&
Network::RelayInfo::getAddresses() const {
    return (addresses_);
}

void
Network::addRelayAddress(const asiolink::IOAddress& addr) {
    relay_.addAddress(addr);
}

bool
Network::hasRelays() const {
    return (relay_.hasAddresses());
}

bool
Network::hasRelayAddress(const asiolink::IOAddress& addr) const {
    return (relay_.containsAddress(addr));
}

const IOAddressList&
Network::getRelayAddresses() const {
    return (relay_.getAddresses());
}

bool
Network::clientSupported(const isc::dhcp::ClientClasses& classes) const {
    if (client_class_.empty()) {
        // There is no class defined for this network, so we do
        // support everyone.
        return (true);
    }

    return (classes.contains(client_class_));
}

void
Network::allowClientClass(const isc::dhcp::ClientClass& class_name) {
    client_class_ = class_name;
}

void
Network::requireClientClass(const isc::dhcp::ClientClass& class_name) {
    if (!required_classes_.contains(class_name)) {
        required_classes_.insert(class_name);
    }
}

const ClientClasses&
Network::getRequiredClasses() const {
    return (required_classes_);
}

ElementPtr
Network::toElement() const {
    ElementPtr map = Element::createMap();

    // Set user-context
    contextToElement(map);

    // Set interface
    const std::string& iface = getIface();
    if (!iface.empty()) {
        map->set("interface", Element::create(iface));
    }

    ElementPtr relay_map = Element::createMap();
    ElementPtr address_list = Element::createList();
    const IOAddressList addresses =  getRelayAddresses();
    for (auto address = addresses.begin(); address != addresses.end(); ++address) {
        address_list->add(Element::create((*address).toText()));
    }

    relay_map->set("ip-addresses", address_list);
    map->set("relay", relay_map);

    // Set client-class
    const ClientClass& cclass = getClientClass();
    if (!cclass.empty()) {
        map->set("client-class", Element::create(cclass));
    }

    // Set require-client-classes
    const ClientClasses& classes = getRequiredClasses();
    if (!classes.empty()) {
        ElementPtr class_list = Element::createList();
        for (ClientClasses::const_iterator it = classes.cbegin();
             it != classes.cend(); ++it) {
            class_list->add(Element::create(*it));
        }
        map->set("require-client-classes", class_list);
    }

    // T1, T2, and Valid are optional for SharedNetworks, and
    // T1 and T2 are optional for Subnet4 thus we will only
    // output them if they are marked as specified.
    if (!getT1().unspecified()) {
        map->set("renew-timer",
                 Element::create(static_cast<long long>(getT1().get())));
    }

    // Set rebind-timer
    if (!getT2().unspecified()) {
        map->set("rebind-timer",
                 Element::create(static_cast<long long>(getT2().get())));
    }

    // Set valid-lifetime
    if (!getValid().unspecified()) {
        map->set("valid-lifetime",
                 Element::create(static_cast<long long>
                                 (getValid().get())));
    }

    // Set reservation mode
    Network::HRMode hrmode = getHostReservationMode();
    std::string mode;
    switch (hrmode) {
    case HR_DISABLED:
        mode = "disabled";
        break;
    case HR_OUT_OF_POOL:
        mode = "out-of-pool";
        break;
    case HR_GLOBAL:
        mode = "global";
        break;
    case HR_ALL:
        mode = "all";
        break;
    default:
        isc_throw(ToElementError,
                  "invalid host reservation mode: " << hrmode);
    }
    map->set("reservation-mode", Element::create(mode));

    // Set options
    ConstCfgOptionPtr opts = getCfgOption();
    map->set("option-data", opts->toElement());

    // Output calcualte-tee-times and percentages if calculation is enabled.
    bool calc_tee_times = getCalculateTeeTimes();
    if (calc_tee_times) {
        map->set("calculate-tee-times", Element::create(calc_tee_times));
        map->set("t1-percent", Element::create(getT1Percent()));
        map->set("t2-percent", Element::create(getT2Percent()));
    }

    return (map);
}

ElementPtr
Network4::toElement() const {
    ElementPtr map = Network::toElement();

    // Set match-client-id
    map->set("match-client-id", Element::create(getMatchClientId()));

    // Set authoritative
    map->set("authoritative", Element::create(getAuthoritative()));

    return (map);
}

IOAddress
Network4::getServerId() const {
    try {
        OptionCustomPtr opt_server_id = boost::dynamic_pointer_cast<OptionCustom>
            (cfg_option_->get(DHCP4_OPTION_SPACE, DHO_DHCP_SERVER_IDENTIFIER).option_);
        if (opt_server_id) {
            return (opt_server_id->readAddress());
        }
    } catch (const std::exception&) {
        // Ignore any exceptions and simply return empty buffer.
    }

    return (IOAddress::IPV4_ZERO_ADDRESS());
}

ElementPtr
Network6::toElement() const {
    ElementPtr map = Network::toElement();

    // Set preferred-lifetime
    map->set("preferred-lifetime",
             Element::create(static_cast<long long>
                             (getPreferred().get())));

    // Set interface-id
    const OptionPtr& ifaceid = getInterfaceId();
    if (ifaceid) {
        std::vector<uint8_t> bin = ifaceid->getData();
        std::string ifid;
        ifid.resize(bin.size());
        if (!bin.empty()) {
            std::memcpy(&ifid[0], &bin[0], bin.size());
        }
        map->set("interface-id", Element::create(ifid));
    }

    // Set rapid-commit
    bool rapid_commit = getRapidCommit();
    map->set("rapid-commit", Element::create(rapid_commit));

    return (map);
}

} // end of namespace isc::dhcp
} // end of namespace isc
