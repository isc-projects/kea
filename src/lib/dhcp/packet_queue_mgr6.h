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
///
/// It is implemented as a singleton that can be accessed from any place
/// within the server code. This includes server configuration, data
/// fetching during normal server operation and data management, including
/// processing of control commands implemented within hooks libraries.
class PacketQueueMgr6 : public PacketQueueMgr<PacketQueue6Ptr>,
                        public boost::noncopyable {
public:

    /// @brief virtual Destructor
    virtual ~PacketQueueMgr6(){}

    /// @brief Creates new instance of the @c PacketQueueMgr6.
    ///
    /// If an instance of the @c PacketQueueMgr6 already exists,
    /// it will be replaced by the new instance. Thus, all factories
    /// will be unregistered and config databases will be dropped.
    static void create();

    /// @brief Destroys the instance of the @c PacketQueueMgr6.
    ///
    /// If an instance of the @c PacketQueueMgr6 exists,
    /// it will be destroyed.  Thus, all factories will be unregistered
    /// and config databases will be dropped.
    static void destroy();

    /// @brief Returns a sole instance of the @c PacketQueueMgr6.
    ///
    /// This method is used to retrieve the instance of the of the 
    /// @c PacketQueueMgr6 created by the @c create method. If the 
    /// instance doesn't exist yet, it is created using the @c create
    /// method.
    static PacketQueueMgr6& instance();

private:
    /// @brief Private constructor.
    ///
    /// It registers a default factory for DHCPv6 queues and creates
    /// an default DHCPv6 packet queue.
    PacketQueueMgr6();

    /// @brief Returns a pointer to the currently used instance of the
    /// @c PacketQueueMgr6.
    static boost::scoped_ptr<PacketQueueMgr6>& getPacketQueueMgr6Ptr();
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // PACKET_QUEUE_MGR6_H
