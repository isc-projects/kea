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
HostReservationModesParser::parse(const ConstElementPtr& control_elem) {
    if (control_elem->getType() != Element::map) {
        isc_throw(DhcpConfigError, "reservation-modes must be a map");
    }

    ConstElementPtr elem;
    uint8_t flags = 0;

    try {
        elem  = control_elem->get("global");
        if (elem) {
            bool value = elem->boolValue();
            if (value) {
                flags |= Network::HR_GLOBAL;
            }
        }

        elem  = control_elem->get("in-subnet");
        if (elem) {
            bool value = elem->boolValue();
            if (value) {
                flags |= Network::HR_IN_SUBNET;
            }
        }

        elem  = control_elem->get("out-of-pool");
        if (elem) {
            bool value = elem->boolValue();
            if (value) {
                flags |= Network::HR_OUT_OF_POOL;
            }
        }
    } catch (const Exception& ex) {
        isc_throw(DhcpConfigError, "error parsing element: " << ex.what());
    }

    return (static_cast<Network::HRMode>(flags));
}

} // end of namespace isc::dhcp
} // end of namespace isc
