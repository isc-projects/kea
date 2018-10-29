// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <dhcp/socket_info.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include <boost/function.hpp>
#include <boost/circular_buffer.hpp>

namespace isc {

namespace dhcp {

/// @brief Enumerates choices between the two ends of the queue.
enum class QueueEnd {
    FRONT,  // Typically the end packets are read from
    BACK    // Typically the end packets are written to
};

/// @brief Interface for managing a queue of inbound DHCP packets
template<typename PacketTypePtr> 
class PacketQueue {
public:

    /// @brief Constructor
    PacketQueue() {}

    /// @brief virtual Destructor
    virtual ~PacketQueue(){};

    /// @brief Adds a packet to the queue
    ///
    /// Calls @c dropPacket to determine if the packet should be queued
    /// or dropped.  If it should be queued it is added to the end of the
    /// specified by the "to" parameter. 
    ///
    /// @param packet packet to enqueue 
    /// @param source socket the packet came from - this can be
    /// @param to end of the queue from which to remove packet(s).
    /// Defaults to BACK.
    ///
    void enqueuePacket(PacketTypePtr packet, const SocketInfo& source,
                       const QueueEnd& to=QueueEnd::BACK) {
        if (!dropPacket(packet, source)) {
            pushPacket(packet, to);
        }
    }

    /// @brief Dequeues the next packet from the queue
    ///
    /// Calls @eatPackets to discard packets as needed, and then
    /// dequeues the next packet (if any) and returns it.  Packets
    /// are dequeued from the end of the queue specified by the "from"
    /// parameter.
    ///
    /// @param from end of the queue from which to remove packet(s).
    /// Defaults to FRONT.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    PacketTypePtr dequeuePacket(const QueueEnd& from=QueueEnd::FRONT) {
        eatPackets(from);
        return(popPacket(from));
    }

    /// @brief Determines if a packet should be discarded.
    ///
    /// This function is called at the beginning of @enqueuePacket and
    /// provides an opportunity to examine the packet and its source
    /// and decide whether it should be dropped or added to the queue.
    /// Derivations are expected to provide implementations based on 
    /// their own requirements.  Bear in mind that the packet has NOT
    /// been unpacked at this point. The default implementation simply
    /// returns false.
    ///
    /// @param packet the packet under consideration
    /// @param source the socket the packet came from
    ///
    /// @return true if the packet should be dropped, false if it should be
    /// kept.
    virtual bool dropPacket(PacketTypePtr /* packet */, 
                            const SocketInfo& /* source */) {
        return (false);
    }

    /// Discards packets from one end of the queue.
    ///
    /// This function is called at the beginning of @c dequeuPacket and
    /// provides an opportunity to examine and discard packets from
    /// the queue prior to dequeuing the next packet to be
    /// processed.  Derivations are expected to provide implementations 
    /// based on their own requirements.  The default implemenation is to 
    /// to simply returns without skipping any packets.
    ///
    /// @param from end of the queue from which packets should discarded
    /// This is passed in from @c dequeuePackets.
    ///
    /// @return The number of packets discarded.
    virtual int eatPackets(const QueueEnd& /* from */) {
        return (0); 
    }

    /// @brief Pushes a packet onto the queue
    ///
    ///  Adds a packet onto the end of queue specified.
    virtual void pushPacket(PacketTypePtr& packet, const QueueEnd& to=QueueEnd::BACK) = 0;

    /// @brief Pops a packet from the queue
    ///
    /// Removes a packet from the end of the queue specified and returns it.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    virtual PacketTypePtr popPacket(const QueueEnd& from=QueueEnd::FRONT) = 0;

    /// @brief Gets the packet currently at one end of the queue
    ///
    /// Returns a pointer the packet at the specified end of the
    /// queue without dequeuing it.  
    ///
    /// @return A pointer to packet, or an empty pointer if the 
    /// queue is empty.
    virtual const PacketTypePtr peek(const QueueEnd& from=QueueEnd::FRONT) const = 0;

    /// @brief return True if the queue is empty.
    virtual bool empty() const = 0;

    /// @brief Returns the maximum number of packets allowed in the buffer.
    virtual size_t getCapacity() const = 0;

    /// @brief Sets the maximum number of packets allowed in the buffer.
    virtual void setCapacity(size_t capacity) = 0;

    /// @brief Returns the current number of packets in the buffer.
    virtual size_t getSize() const = 0;

    /// @brief Discards all packets currently in the buffer.
    virtual void clear() = 0;
};

/// @brief Defines pointer to the DHCPv4 queue interface used at the application level. 
typedef boost::shared_ptr<PacketQueue<Pkt4Ptr>> PacketQueue4Ptr;

/// @brief Defines pointer to the DHCPv6 queue interface used at the application level. 
typedef boost::shared_ptr<PacketQueue<Pkt6Ptr>> PacketQueue6Ptr;

/// @brief Provides an abstract ring-buffer implementation of the PacketQueue interface.
template<typename PacketTypePtr> 
class PacketQueueRing : public PacketQueue<PacketTypePtr> {
public:
    static const size_t MIN_RING_CAPACITY = 5;

    /// @brief Constructor
    ///
    /// @param queue_capacity maximum number of packets the queue can hold
    /// Defaults to DEFAULT_RING_CAPACITY.
    PacketQueueRing(size_t capacity) { 
        queue_.set_capacity(capacity);
    }

    /// @brief virtual Destructor
    virtual ~PacketQueueRing(){};

    /// @brief Pushes a packet onto the queue
    ///
    ///  Adds a packet onto the end of queue specified.
    virtual void pushPacket(PacketTypePtr& packet, const QueueEnd& to=QueueEnd::BACK) {
        if (to == QueueEnd::BACK) {
            queue_.push_back(packet);
        } else {
            queue_.push_front(packet);
        }
    }

    /// @brief Pops a packet from the queue
    ///
    /// Removes a packet from the end of the queue specified and returns it.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    virtual PacketTypePtr popPacket(const QueueEnd& from = QueueEnd::FRONT) {
        PacketTypePtr packet;
        if (queue_.empty()) {
            return (packet);
        }

        if (from == QueueEnd::FRONT) {
            packet = queue_.front();
            queue_.pop_front();
        } else {
            packet = queue_.back();
            queue_.pop_back();
        }

        return (packet);
    }


    /// @brief Gets the packet currently at one end of the queue
    ///
    /// Returns a pointer the packet at the specified end of the
    /// queue without dequeuing it.  
    ///
    /// @return A pointer to packet, or an empty pointer if the 
    /// queue is empty.
    virtual const PacketTypePtr peek(const QueueEnd& from=QueueEnd::FRONT) const {
        PacketTypePtr packet;
        if (!queue_.empty()) {
            packet = (from == QueueEnd::FRONT ? queue_.front() : queue_.back());
        }

        return (packet);
    }

    /// @brief Returns True if the queue is empty.
    virtual bool empty() const {
        return(queue_.empty());
    } 

    /// @brief Returns the maximum number of packets allowed in the buffer.
    virtual size_t getCapacity() const {
        return (queue_.capacity());
    }

    /// @brief Sets the maximum number of packets allowed in the buffer.
    ///
    /// @throw BadValue if capacity is too low.
    virtual void setCapacity(size_t capacity) {
        if (capacity < MIN_RING_CAPACITY) {
            isc_throw(BadValue, "Queue capacity of " << capacity 
                      << " is invalid.  It must be at least " 
                      << MIN_RING_CAPACITY);
        }

        /// @todo should probably throw if it's zero
        queue_.set_capacity(capacity);
    }

    /// @brief Returns the current number of packets in the buffer.
    virtual size_t getSize() const {
        return (queue_.size());
    }

    /// @brief Discards all packets currently in the buffer.
    virtual void clear()  {
        queue_.clear();
    }

private:

    /// @brief Packet queue
    boost::circular_buffer<PacketTypePtr> queue_;
};


/// @brief Default DHCPv4 packet queue buffer implementation
class PacketQueueRing4 : public PacketQueueRing<Pkt4Ptr> {
public:
    static const size_t DEFAULT_RING_CAPACITY = 500;

    /// @brief Constructor
    ///
    /// @param capacity maximum number of packets the queue can hold
    PacketQueueRing4(size_t capacity=DEFAULT_RING_CAPACITY) 
        : PacketQueueRing(capacity) {
    };

    /// @brief virtual Destructor
    virtual ~PacketQueueRing4(){};
};

/// @brief Default DHCPv6 packet queue buffer implementation
class PacketQueueRing6 : public PacketQueueRing<Pkt6Ptr> {
public:
    static const size_t DEFAULT_RING_CAPACITY = 500;

    /// @brief Constructor
    ///
    /// @param capacity maximum number of packets the queue can hold
    PacketQueueRing6(size_t capacity=DEFAULT_RING_CAPACITY)
        : PacketQueueRing(capacity) {
    };

    /// @brief virtual Destructor
    virtual ~PacketQueueRing6(){};
};



}; // namespace isc::dhcp
}; // namespace isc

#endif // PACKET_QUEUE_H
