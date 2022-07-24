// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/adaptor_subnet.h>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace yang {

AdaptorSubnet::AdaptorSubnet() {
}

AdaptorSubnet::~AdaptorSubnet() {
}

bool
AdaptorSubnet::collectID(ConstElementPtr subnet, SubnetIDSet& set) {
    ConstElementPtr id = subnet->get("id");
    if (id) {
        set.insert(static_cast<SubnetID>(id->intValue()));
        return (true);
    }
    return (false);
}

void
AdaptorSubnet::assignID(ElementPtr subnet, SubnetIDSet& set, SubnetID& next) {
    ConstElementPtr id = subnet->get("id");
    if (!id) {
        // Skip already used.
        while (set.count(next) > 0) {
            ++next;
        }
        subnet->set("id", Element::create(static_cast<long long>(next)));
        set.insert(next);
        ++next;
    }
}

void
AdaptorSubnet::updateRelay(ElementPtr subnet) {
    ConstElementPtr relay = subnet->get("relay");
    if (!relay) {
        return;
    }
    ConstElementPtr addresses = relay->get("ip-addresses");
    if (!addresses) {
        ConstElementPtr address = relay->get("ip-address");
        if (!address) {
            subnet->remove("relay");
            return;
        }
        ElementPtr addr = Element::create(address->stringValue());
        ElementPtr addrs = Element::createList();
        addrs->add(addr);
        ElementPtr updated = Element::createMap();
        updated->set("ip-addresses", addrs);
        subnet->set("relay", updated);
    } else if (addresses->size() == 0) {
        subnet->remove("relay");
    }
}

}  // end of namespace isc::yang
}  // end of namespace isc
