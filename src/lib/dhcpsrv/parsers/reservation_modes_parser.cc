// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/reservation_modes_parser.h>

#include <string>
#include <sys/types.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

Network::HRMode
HostReservationModesParser::parse(const ConstElementPtr& config_elem) {
    if (config_elem->getType() != Element::map) {
        isc_throw(DhcpConfigError, "configuration must be a map");
    }

    ConstElementPtr elem;
    uint8_t flags = 0;

    try {
        elem  = config_elem->get("reservations-global");
        if (elem) {
            bool value = elem->boolValue();
            if (value) {
                flags |= Network::HR_GLOBAL;
            }
        }

        elem  = config_elem->get("reservations-in-subnet");
        if (elem) {
            bool value = elem->boolValue();
            if (value) {
                flags |= Network::HR_IN_SUBNET;
            }
        }

        elem  = config_elem->get("reservations-out-of-pool");
        if (elem) {
            bool value = elem->boolValue();
            if (value) {
                flags |= Network::HR_IN_SUBNET | Network::HR_OUT_OF_POOL;
            }
        }
    } catch (const Exception& ex) {
        isc_throw(DhcpConfigError, "error parsing element: " << ex.what());
    }

    return (static_cast<Network::HRMode>(flags));
}

} // end of namespace isc::dhcp
} // end of namespace isc
