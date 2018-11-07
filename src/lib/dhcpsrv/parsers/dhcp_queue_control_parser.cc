// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/dhcp_queue_control_parser.h>
#include <boost/foreach.hpp>
#include <string>
#include <sys/types.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

DHCPQueueControlParser::DHCPQueueControlParser(const uint16_t family)
    : family_(family) {
    // @todo Not sure we need family but just in case.
    if (family_ != AF_INET && family_ != AF_INET6) {
        isc_throw(BadValue, "DHCPQueueControlParser - invalid family: "
                 << family_ << ", must be AF_INET or AF_INET6");
    }
}

data::ElementPtr 
DHCPQueueControlParser::parse(const isc::data::ConstElementPtr& control_elem) {
    // All we really do here is verify that it is a map that
    // contains at least queue-type.  All other content depends 
    // on the packet queue implementation of that type.
    if (control_elem->getType() != Element::map) {
        isc_throw(DhcpConfigError, "dhcp-queue-control must be a map");
    }

    ConstElementPtr elem  = control_elem->get("queue-type");
    if (!elem) {
        isc_throw(DhcpConfigError, "queue-type is required");
    } else {
        if (elem->getType() != Element::string) {
            isc_throw(DhcpConfigError, "queue-type must be a string");
        }
    }

    // Return a copy of it.
    return (data::copy(control_elem));
}

} // end of namespace isc::dhcp
} // end of namespace isc
