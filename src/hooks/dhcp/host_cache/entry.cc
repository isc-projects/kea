// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <host_cache.h>
#include <util/encode/encode.h>

#include <boost/foreach.hpp>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace host_cache {

/// @todo: Update Host::toElement4 and Host::toElement6 and remove
///        this code (trac #5578)
ElementPtr
toElement(const ConstHostPtr& host) {
    // Prepare the map
    ElementPtr map = Element::createMap();
    // Set the user context
    host->contextToElement(map);
    // Set the identifier
    Host::IdentifierType id_type = host->getIdentifierType();
    if (id_type == Host::IDENT_HWADDR) {
        HWAddrPtr hwaddr = host->getHWAddress();
        map->set("hw-address", Element::create(hwaddr->toText(false)));
    } else if (id_type == Host::IDENT_DUID) {
        DuidPtr duid = host->getDuid();
        map->set("duid", Element::create(duid->toText()));
    } else if (id_type == Host::IDENT_CIRCUIT_ID) {
        const vector<uint8_t>& bin = host->getIdentifier();
        string circuit_id = util::encode::encodeHex(bin);
        map->set("circuit-id", Element::create(circuit_id));
    } else if (id_type == Host::IDENT_CLIENT_ID) {
        const vector<uint8_t>& bin = host->getIdentifier();
        string client_id = util::encode::encodeHex(bin);
        map->set("client-id", Element::create(client_id));
    } else if (id_type == Host::IDENT_FLEX) {
        const vector<uint8_t>& bin = host->getIdentifier();
        string client_id = util::encode::encodeHex(bin);
        map->set("flex-id", Element::create(client_id));
    } else {
        isc_throw(ToElementError, "invalid identifier type: " << id_type);
    }

    // Set the IPv4 reservation (if not 0.0.0.0 which may not be re-read)
    const IOAddress& address = host->getIPv4Reservation();
    if (!address.isV4Zero()) {
        map->set("ip-address", Element::create(address.toText()));
    }

    // Set IPv6 reservations (ip-addresses)
    const IPv6ResrvRange& na_resv = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ElementPtr resvs = Element::createList();
    BOOST_FOREACH(auto const& resv, na_resv) {
        resvs->add(Element::create(resv.second.toText()));
    }
    if (resvs->size() > 0) {
        map->set("ip-addresses", resvs);
    }
    // Set reservations (prefixes)
    const IPv6ResrvRange& pd_resv = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    resvs = Element::createList();
    BOOST_FOREACH(auto const& resv, pd_resv) {
        resvs->add(Element::create(resv.second.toText()));
    }
    if (resvs->size() > 0) {
        map->set("prefixes", resvs);
    }

    // Set the hostname
    const string& hostname = host->getHostname();
    map->set("hostname", Element::create(hostname));

    // Set next-server
    const IOAddress& next_server = host->getNextServer();
    map->set("next-server", Element::create(next_server.toText()));
    // Set server-hostname
    const string& server_hostname = host->getServerHostname();
    map->set("server-hostname", Element::create(server_hostname));
    // Set boot-file-name
    const string& boot_file_name = host->getBootFileName();
    map->set("boot-file-name", Element::create(boot_file_name));

    // Set IPv4 client-classes
    const ClientClasses& cclasses4 = host->getClientClasses4();
    ElementPtr classes = Element::createList();
    for (auto const& cclass : cclasses4) {
        classes->add(Element::create(cclass));
    }
    map->set("client-classes4", classes);
    // Set IPv6 client-classes
    const ClientClasses& cclasses6 = host->getClientClasses6();
    classes = Element::createList();
    for (auto const& cclass : cclasses6) {
        classes->add(Element::create(cclass));
    }
    map->set("client-classes6", classes);

    // Set IPv4 option-data
    ConstCfgOptionPtr opts = host->getCfgOption4();
    map->set("option-data4", opts->toElement());
    // Set IPv6 option-data
    opts = host->getCfgOption6();
    map->set("option-data6", opts->toElement());

    // Set IPv4 subnet-id
    SubnetID subnet_id = host->getIPv4SubnetID();
    map->set("subnet-id4", Element::create(static_cast<long long>(subnet_id)));
    // Set IPv6 subnet-id
    subnet_id = host->getIPv6SubnetID();
    map->set("subnet-id6", Element::create(static_cast<long long>(subnet_id)));

    // Set host-id
    uint64_t hid = host->getHostId();
    map->set("host-id", Element::create(static_cast<int64_t>(hid)));

    // Set negative
    if (host->getNegative()) {
        map->set("negative", Element::create(true));
    }

    return (map);
}

} // end of namespace isc::host_cache
} // end of namespace isc
