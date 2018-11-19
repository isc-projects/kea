// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_QUEUE_MGR6_H
#define PACKET_QUEUE_MGR6_H

#include <dhcp/packet_queue_mgr.h>

#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Packet Queue Manager for DHPCv6 servers.
///
/// Implements the "manager" class which holds information about the
/// supported DHCPv6 packet queue implementations and provides management
/// of the current queue instance.
class PacketQueueMgr6 : public PacketQueueMgr<PacketQueue6Ptr>,
                        public boost::noncopyable {
public:
    /// @brief Logical name of the pre-registered, default queue implementation
    static const std::string DEFAULT_QUEUE_TYPE6;

    /// @brief constructor.
    ///
    /// It registers a default factory for DHCPv6 queues.
    PacketQueueMgr6();

    /// @brief virtual Destructor
    virtual ~PacketQueueMgr6(){}
};

/// @brief Defines a shared pointer to PacketQueueMgr6
typedef boost::shared_ptr<PacketQueueMgr6> PacketQueueMgr6Ptr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // PACKET_QUEUE_MGR6_H
