// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <cc/data.h>
#include <dhcp/socket_info.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include <sstream>

namespace isc {

namespace dhcp {

/// @brief Invalid queue parameter exception
///
/// Thrown when packet queue is supplied an invalid/missing parameter
class InvalidQueueParameter : public Exception {
public:
    InvalidQueueParameter(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Enumerates choices between the two ends of the queue.
enum class QueueEnd {
    FRONT,  // Typically the end packets are read from
    BACK    // Typically the end packets are written to
};

/// @brief Interface for managing a queue of inbound DHCP packets
///
/// This class serves as the abstract interface for packet queue
/// implementations which may be used by @c IfaceMgr to store
/// inbound packets until they are a dequeued for processing.
///
/// @tparam PacketTypePtr Type of packet the queue contains.
/// This expected to be either isc::dhcp::Pkt4Ptr or isc::dhcp::Pkt6Ptr
///
/// @note Derivations of this class MUST BE thread-safe.
template<typename PacketTypePtr>
class PacketQueue {
public:

    /// @brief Constructor
    ///
    /// @param queue_type logical name of the queue implementation
    /// Typically this is assigned by the factory that creates the
    /// queue.  It is the logical name used to register queue
    /// implementations.
    explicit PacketQueue(const std::string& queue_type)
        :  queue_type_(queue_type) {}

    /// Virtual destructor
    virtual ~PacketQueue(){};

    /// @brief Adds a packet to the queue
    ///
    /// Adds the packet to the queue.  Derivations determine
    /// which packets to queue and how to queue them.
    ///
    /// @param packet packet to enqueue
    /// @param source socket the packet came from
    virtual void enqueuePacket(PacketTypePtr packet, const SocketInfo& source) = 0;

    /// @brief Dequeues the next packet from the queue
    ///
    /// Dequeues the next packet (if any) and returns it. Derivations determine
    /// how packets are dequeued.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    virtual PacketTypePtr dequeuePacket() = 0;

    /// @brief return True if the queue is empty.
    virtual bool empty() const = 0;

    /// @brief Returns the current number of packets in the buffer.
    virtual size_t getSize() const = 0;

    /// @brief Discards all packets currently in the buffer.
    virtual void clear() = 0;

    /// @brief Fetches operational information about the current state of
    /// the queue
    ///
    /// Creates and returns an ElementPtr containing a single entry,
    /// "queue-type".  Derivations are expected to call this method first
    /// and then add their own values.  Since implementations may vary
    /// widely on data of interest, this is structured as an ElementPtr
    /// for broad latitude.
    ///
    /// @return an ElementPtr containing elements for values of interest
    virtual data::ElementPtr getInfo() const {
       data::ElementPtr info = data::Element::createMap();
       info->set("queue-type", data::Element::create(queue_type_));
       return (info);
    }

    /// @brief Fetches a JSON string representation of queue operational info
    ///
    /// This method calls @c getInfo() and then converts that into JSON text.
    ///
    /// @return string of JSON text
    std::string getInfoStr() const {
       data::ElementPtr info = getInfo();
       std::ostringstream os;
       info->toJSON(os);
       return (os.str());
    }

    /// @return Fetches the logical name of the type of this queue.
    std::string getQueueType() {
        return (queue_type_);
    };

private:
    /// @brief Logical name of the this queue's implementation type.
    std::string queue_type_;

};

/// @brief Defines pointer to the DHCPv4 queue interface used at the application level.
/// This is the type understood by IfaceMgr and the type that should be returned by
/// DHCPv4 packet queue factories.
typedef boost::shared_ptr<PacketQueue<Pkt4Ptr>> PacketQueue4Ptr;

/// @brief Defines pointer to the DHCPv6 queue interface used at the application level.
/// This is the type understood by IfaceMgr and the type that should be returned by
/// DHCPv6 packet queue factories.
typedef boost::shared_ptr<PacketQueue<Pkt6Ptr>> PacketQueue6Ptr;

}; // namespace isc::dhcp
}; // namespace isc

#endif // PACKET_QUEUE_H
