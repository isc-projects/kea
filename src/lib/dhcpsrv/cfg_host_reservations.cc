// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <dhcpsrv/cfg_host_reservations.h>
#include <algorithm>

namespace isc {
namespace dhcp {

CfgHostReservations::CfgHostReservations()
    : identifier_types_() {
}

void
CfgHostReservations::addIdentifierType(const std::string& identifier_name) {
    Host::IdentifierType identifier_type = Host::getIdentifierType(identifier_name);
    if (std::find(identifier_types_.begin(), identifier_types_.end(),
                  identifier_type) != identifier_types_.end()) {
        isc_throw(isc::BadValue, "invalid host identifier name '"
                  << identifier_name << "'");
    }
    identifier_types_.push_back(identifier_type);
}

void
CfgHostReservations::clear() {
    identifier_types_.clear();
}

}
}
