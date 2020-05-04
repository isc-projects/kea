// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/dhcp_queue_control_parser.h>
#include <util/multi_threading_mgr.h>
#include <boost/foreach.hpp>
#include <string>
#include <sys/types.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

ElementPtr
DHCPQueueControlParser::parse(const ConstElementPtr& control_elem) {
    // All we really do here is verify that it is a map that
    // contains at least queue-type.  All other content depends
    // on the packet queue implementation of that type.
    if (control_elem->getType() != Element::map) {
        isc_throw(DhcpConfigError, "dhcp-queue-control must be a map");
    }

    // enable-queue is mandatory.
    bool enable_queue = getBoolean(control_elem, "enable-queue");

    if (enable_queue) {
        ConstElementPtr elem  = control_elem->get("queue-type");
        if (!elem) {
            isc_throw(DhcpConfigError, "when queue is enabled, queue-type is required");
        } else {
            if (elem->getType() != Element::string) {
                isc_throw(DhcpConfigError, "queue-type must be a string");
            }
        }
    }

    // Return a copy of it.
    ElementPtr result = data::copy(control_elem);

    // Currently not compatible with multi-threading.
    if (MultiThreadingMgr::instance().getMode()) {
        // Silently disable it.
        result->set("enable-queue", Element::create(false));
    }

    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc
