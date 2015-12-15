// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfg_rsoo.h>

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


}
}
