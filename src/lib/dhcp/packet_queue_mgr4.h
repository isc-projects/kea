// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_QUEUE_MGR4_H
#define PACKET_QUEUE_MGR4_H

#include <dhcp/packet_queue_mgr.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Packet Queue Manager for DHPCv4 servers.
///
/// Implements the "manager" class which holds information about the
/// supported DHCPv4 packet queue implementations and provides management
/// of the current queue instance.
class PacketQueueMgr4 : public PacketQueueMgr<PacketQueue4Ptr> {

public:
    /// @brief Logical name of the pre-registered, default queue implementation
    static const std::string DEFAULT_QUEUE_TYPE4;

    /// It registers a default factory for DHCPv4 queues. 
    PacketQueueMgr4();

    /// @brief virtual Destructor
    virtual ~PacketQueueMgr4(){}
};

/// @brief Defines a shared pointer to PacketQueueMgr4
typedef boost::shared_ptr<PacketQueueMgr4> PacketQueueMgr4Ptr;


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // PACKET_QUEUE_MGR4_H
