// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/cfg_host_operations.h>
#include <algorithm>
#include <string>

using namespace isc::data;

namespace isc {
namespace dhcp {

CfgHostOperations::CfgHostOperations()
    : identifier_types_() {
}

CfgHostOperationsPtr
CfgHostOperations::createConfig4() {
    // If this list is modified, please update reservations4-tuning section in
    // doc/guide/dhcp4-srv.xml
    CfgHostOperationsPtr cfg(new CfgHostOperations());
    cfg->addIdentifierType("hw-address");
    cfg->addIdentifierType("duid");
    cfg->addIdentifierType("circuit-id");
    cfg->addIdentifierType("client-id");
    return (cfg);
}

CfgHostOperationsPtr
CfgHostOperations::createConfig6() {
    // If this list is modified, please update reservations6-tuning section in
    // doc/guide/dhcp6-srv.xml
    CfgHostOperationsPtr cfg(new CfgHostOperations());
    cfg->addIdentifierType("hw-address");
    cfg->addIdentifierType("duid");
    return (cfg);
}

void
CfgHostOperations::addIdentifierType(const std::string& identifier_name) {
    Host::IdentifierType identifier_type = Host::getIdentifierType(identifier_name);
    if (std::find(identifier_types_.begin(), identifier_types_.end(),
                  identifier_type) != identifier_types_.end()) {
        isc_throw(isc::BadValue, "duplicate host identifier '"
                  << identifier_name << "'");
    }
    identifier_types_.push_back(identifier_type);
}

void
CfgHostOperations::clearIdentifierTypes() {
    identifier_types_.clear();
}

ElementPtr
CfgHostOperations::toElement() const {
    ElementPtr result = Element::createList();
    for (IdentifierTypes::const_iterator id = identifier_types_.begin();
         id != identifier_types_.end(); ++id) {
        const std::string& name = Host::getIdentifierName(*id);
        result->add(Element::create(name));
    }
    return (result);
}

}
}
