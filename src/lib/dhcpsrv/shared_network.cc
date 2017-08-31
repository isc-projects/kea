// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcpsrv/shared_network.h>

using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace dhcp {

ElementPtr
SharedNetwork::toElement() const {
    ElementPtr map = Network::toElement();

    // Set shared network name.
    if (!name_.empty()) {
        map->set("name", Element::create(name_));
    }

    return (map);
}

NetworkPtr
SharedNetwork4::sharedFromThis() {
    return (shared_from_this());
}

void
SharedNetwork4::add(const Subnet4Ptr& subnet) {
    SharedNetwork::add(subnets_, subnet);
}

void
SharedNetwork4::del(const SubnetID& subnet_id) {
    SharedNetwork::del(subnets_, subnet_id);
}

Subnet4Ptr
SharedNetwork4::getSubnet(const SubnetID& subnet_id) const {
    return (SharedNetwork::getSubnet<Subnet4Ptr>(subnets_, subnet_id));
}

Subnet4Ptr
SharedNetwork4::getNextSubnet(const Subnet4Ptr& first_subnet,
                              const Subnet4Ptr& current_subnet) const {
    return (SharedNetwork::getNextSubnet(subnets_, first_subnet,
                                         current_subnet));
}

ElementPtr
SharedNetwork4::toElement() const {
    ElementPtr map = SharedNetwork::toElement();

    ElementPtr subnet4 = Element::createList();
    for (auto subnet = subnets_.cbegin(); subnet != subnets_.cend(); ++subnet) {
        subnet4->add((*subnet)->toElement());
    }

    map->set("subnet4", subnet4);

    return (map);
}

NetworkPtr
SharedNetwork6::sharedFromThis() {
    return (shared_from_this());
}

void
SharedNetwork6::add(const Subnet6Ptr& subnet) {
    SharedNetwork::add(subnets_, subnet);
}

void
SharedNetwork6::del(const SubnetID& subnet_id) {
    SharedNetwork::del(subnets_, subnet_id);
}

Subnet6Ptr
SharedNetwork6::getSubnet(const SubnetID& subnet_id) const {
    return (SharedNetwork::getSubnet<Subnet6Ptr>(subnets_, subnet_id));
}

Subnet6Ptr
SharedNetwork6::getNextSubnet(const Subnet6Ptr& first_subnet,
                              const Subnet6Ptr& current_subnet) const {
    return (SharedNetwork::getNextSubnet(subnets_, first_subnet,
                                         current_subnet));
}

ElementPtr
SharedNetwork6::toElement() const {
    ElementPtr map = SharedNetwork::toElement();

    ElementPtr subnet6 = Element::createList();
    for (auto subnet = subnets_.cbegin(); subnet != subnets_.cend(); ++subnet) {
        subnet6->add((*subnet)->toElement());
    }

    map->set("subnet6", subnet6);

    return (map);
}

} // end of namespace isc::dhcp
} // end of namespace isc
