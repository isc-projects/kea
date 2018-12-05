// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/packet_queue_ring.h>
#include <dhcp/packet_queue_mgr4.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

const std::string PacketQueueMgr4::DEFAULT_QUEUE_TYPE4 = "kea-ring4";

PacketQueueMgr4::PacketQueueMgr4() {
    // Register default queue factory
    registerPacketQueueFactory(DEFAULT_QUEUE_TYPE4, [](data::ConstElementPtr parameters)
                                          -> PacketQueue4Ptr {
            size_t capacity;
            try {
                capacity = data::SimpleParser::getInteger(parameters, "capacity");
            } catch (const std::exception& ex) {
                isc_throw(InvalidQueueParameter, DEFAULT_QUEUE_TYPE4 << " factory:"
                          " 'capacity' parameter is missing/invalid: " << ex.what());
            }

            PacketQueue4Ptr queue(new PacketQueueRing4(DEFAULT_QUEUE_TYPE4, capacity));
            return (queue);
        });
}

} // end of isc::dhcp namespace
} // end of isc namespace
