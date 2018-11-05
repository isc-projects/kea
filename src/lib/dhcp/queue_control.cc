// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/queue_control.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

QueueControl::QueueControl()
    : queue_type_(""), capacity_(0) {
}

bool
QueueControl::equals(const QueueControl& other) const {
    return (queue_type_ == other.queue_type_ &&
            capacity_ == other.capacity_);
}

ElementPtr
QueueControl::toElement() const {
    ElementPtr result = Element::createMap();

    // Add "capacity"
    result->set("queue-type", Element::create(queue_type_));

    // Add "capacity"
    result->set("capacity", Element::create(static_cast<long int>(capacity_)));

    // Set user context
    contextToElement(result);


    return (result);
}

} // end of isc::dhcp namespace
} // end of isc namespace
