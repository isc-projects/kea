// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option.h>
#include <dhcpsrv/cfg_4o6.h>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>

using namespace isc::data;

namespace isc {
namespace dhcp {

ElementPtr
Cfg4o6::toElement() const {
    ElementPtr result = Element::createMap();
    // Set 4o6-interface
    result->set("4o6-interface", Element::create(iface4o6_));
    // Set 4o6-subnet
    if (!subnet4o6_.get().first.isV6Zero() || (subnet4o6_.get().second != 128u)) {
        std::ostringstream oss;
        oss << subnet4o6_.get().first << "/"
            << static_cast<unsigned>(subnet4o6_.get().second);
        result->set("4o6-subnet", Element::create(oss.str()));
    } else {
        result->set("4o6-subnet", Element::create(std::string()));
    }
    // Set 4o6-interface-id
    if (interface_id_) {
        std::vector<uint8_t> bin = interface_id_->toBinary();
        std::string iid;
        iid.resize(bin.size());
        if (!bin.empty()) {
            std::memcpy(&iid[0], &bin[0], bin.size());
        }
        result->set("4o6-interface-id", Element::create(iid));
    } else {
        result->set("4o6-interface-id", Element::create(std::string()));
    }
    return (result);
}

} // end of isc::dhcp namespace
} // end of isc namespace
