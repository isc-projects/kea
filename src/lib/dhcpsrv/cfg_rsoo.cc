// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfg_rsoo.h>
#include <boost/lexical_cast.hpp>

using namespace isc::data;

namespace isc {
namespace dhcp {

CfgRSOO::CfgRSOO()
    : rsoo_options_() {
    rsoo_options_.insert(D6O_ERP_LOCAL_DOMAIN_NAME);
}

void
CfgRSOO::clear() {
    rsoo_options_.clear();
}

bool
CfgRSOO::enabled(const uint16_t code) const {
    return (rsoo_options_.find(code) != rsoo_options_.end());
}

void
CfgRSOO::enable(const uint16_t code) {
    if (rsoo_options_.find(code) == rsoo_options_.end()) {
        // If there's no such code added yet, let's add it
        rsoo_options_.insert(code);
    }
}

ElementPtr
CfgRSOO::toElement() const {
    ElementPtr result = Element::createList();
    // We can use LibDHCP::getOptionDef(DHCP6_OPTION_SPACE, *opt) too...
    for (std::set<uint16_t>::const_iterator opt = rsoo_options_.cbegin();
         opt != rsoo_options_.cend(); ++opt) {
        const std::string& code = boost::lexical_cast<std::string>(*opt);
        result->add(Element::create(code));
    }
    return (result);
}

}
}
