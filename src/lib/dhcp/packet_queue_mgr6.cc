// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/packet_queue_mgr6.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

PacketQueueMgr6::PacketQueueMgr6() {
    // Register default queue factory
    registerPacketQueueFactory("kea-ring6", [](const QueueControl& control)
                                          -> PacketQueue6Ptr {
            PacketQueue6Ptr queue(new PacketQueueRing6("kea-ring6", control.getCapacity()));
            return (queue);
        });

    QueueControl control;
    control.setQueueType("kea-ring6");
    // @todo default comes from ?
    control.setCapacity(500);
    createPacketQueue(control);
}

boost::scoped_ptr<PacketQueueMgr6>&
PacketQueueMgr6::getPacketQueueMgr6Ptr() {
    static boost::scoped_ptr<PacketQueueMgr6> packet_mgr;
    return (packet_mgr);
}

void
PacketQueueMgr6::create() {
    getPacketQueueMgr6Ptr().reset(new PacketQueueMgr6());
}

void
PacketQueueMgr6::destroy() {
    getPacketQueueMgr6Ptr().reset(new PacketQueueMgr6());
}

PacketQueueMgr6&
PacketQueueMgr6::instance() {
    boost::scoped_ptr<PacketQueueMgr6>& packet_mgr = getPacketQueueMgr6Ptr();
    if (!packet_mgr) {
        create();
    }
    return (*packet_mgr);
}

} // end of isc::dhcp namespace
} // end of isc namespace
