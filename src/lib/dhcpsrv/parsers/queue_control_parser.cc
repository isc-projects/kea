// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/queue_control_parser.h>
#include <boost/foreach.hpp>
#include <string>
#include <sys/types.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

QueueControlParser::QueueControlParser(const uint16_t family)
    : family_(family) {
    // @todo Not sure we need family but just in case.
    if (family_ != AF_INET && family_ != AF_INET6) {
        isc_throw(BadValue, "QueueControlParser - invalid family: "
                 << family_ << ", must be AF_INET or AF_INET6");
    }
}

QueueControlPtr 
QueueControlParser::parse(const isc::data::ConstElementPtr& queue_elem) {
    QueueControlPtr queue_control(new QueueControl());

    if (queue_elem->getType() != Element::map) {
        isc_throw(DhcpConfigError, "queue-control must be a map");
    }

    try {
        size_t capacity = getInteger(queue_elem, "capacity");
        queue_control->setCapacity(capacity);
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() 
                  << " (" << getPosition("ip-addresses", queue_elem) << ")");
    }

    ConstElementPtr user_context = queue_elem->get("user-context");
    if (user_context) {
        queue_control->setContext(user_context);
    }

    return (queue_control);
}

} // end of namespace isc::dhcp
} // end of namespace isc
