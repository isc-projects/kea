// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_QUEUE_RING_H
#define PACKET_QUEUE_RING_H

#include <dhcp/packet_queue.h>

#include <boost/circular_buffer.hpp>
#include <boost/scoped_ptr.hpp>
#include <sstream>
#include <mutex>

namespace isc {

namespace dhcp {

/// @brief Provides a ring-buffer implementation of the PacketQueue interface.
///
/// @tparam PacketTypePtr Type of packet the queue contains.
/// This expected to be either isc::dhcp::Pkt4Ptr or isc::dhcp::Pkt6Ptr
template<typename PacketTypePtr>
class PacketQueueRing : public PacketQueue<PacketTypePtr> {
public:
    /// @brief Minimum queue capacity permitted. Below five is pretty much
    /// nonsensical.
    static const size_t MIN_RING_CAPACITY = 5;

    /// @brief Constructor
    ///
    /// @param queue_type logical name of the queue implementation
    /// @param capacity maximum number of packets the queue can hold
    PacketQueueRing(const std::string& queue_type, size_t capacity)
        : PacketQueue<PacketTypePtr>(queue_type) {
        queue_.set_capacity(capacity);
        mutex_.reset(new std::mutex);
    }

    /// @brief virtual Destructor
    virtual ~PacketQueueRing(){};

    /// @brief Adds a packet to the queue
    ///
    /// Calls @c shouldDropPacket to determine if the packet should be queued
    /// or dropped.  If it should be queued it is added to the end of the
    /// queue specified by the "to" parameter.
    ///
    /// @param packet packet to enqueue
    /// @param source socket the packet came from
    virtual void enqueuePacket(PacketTypePtr packet, const SocketInfo& source) {
        if (!shouldDropPacket(packet, source)) {
            pushPacket(packet);
        }
    }

    /// @brief Dequeues the next packet from the queue
    ///
    /// Dequeues the next packet (if any) and returns it.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    virtual PacketTypePtr dequeuePacket() {
        eatPackets(QueueEnd::FRONT);
        return (popPacket());
    }

    /// @brief Determines if a packet should be discarded.
    ///
    /// This function is called in @c enqueuePackets for each packet
    /// in its packet list. It provides an opportunity to examine the
    /// packet and its source and decide whether it should be dropped
    /// or added to the queue. Derivations are expected to provide
    /// implementations based on their own requirements.  Bear in mind
    /// that the packet has NOT been unpacked at this point. The default
    /// implementation simply returns false (i.e. keep the packet).
    ///
    /// @return true if the packet should be dropped, false if it should be
    /// kept.
    virtual bool shouldDropPacket(PacketTypePtr /* packet */,
                            const SocketInfo& /* source */) {
        return (false);
    }

    /// @brief Discards packets from one end of the queue.
    ///
    /// This function is called at the beginning of @c dequeuePacket and
    /// provides an opportunity to examine and discard packets from
    /// the queue prior to dequeuing the next packet to be
    /// processed.  Derivations are expected to provide implementations
    /// based on their own requirements.  The default implementation is to
    /// to simply return without skipping any packets.
    ///
    /// @return The number of packets discarded.
    virtual int eatPackets(const QueueEnd& /* from */) {
        return (0);
    }

    /// @brief Pushes a packet onto the queue
    ///
    ///  Adds a packet onto the end of queue specified.
    ///
    /// @param packet packet to add to the queue
    /// @param to specifies the end of the queue to which the packet
    /// should be added.
    virtual void pushPacket(PacketTypePtr& packet, const QueueEnd& to=QueueEnd::BACK) {
        std::lock_guard<std::mutex> lock(*mutex_);
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
    /// @param from specifies the end of the queue from which the packet
    /// should be taken.  It locks the queue's Mutex upon entry.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    virtual PacketTypePtr popPacket(const QueueEnd& from = QueueEnd::FRONT) {
        PacketTypePtr packet;
        std::lock_guard<std::mutex> lock(*mutex_);

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
    /// @param from specifies which end of the queue to examine.
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
        std::lock_guard<std::mutex> lock(*mutex_);
        return (queue_.empty());
    }

    /// @brief Returns the maximum number of packets allowed in the buffer.
    virtual size_t getCapacity() const {
        return (queue_.capacity());
    }

    /// @brief Sets the maximum number of packets allowed in the buffer.
    ///
    /// @todo - do we want to change size on the fly?  This might need
    /// to be private, called only by constructor
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

    /// @brief Fetches pertinent information
    virtual data::ElementPtr getInfo() const {
       data::ElementPtr info = PacketQueue<PacketTypePtr>::getInfo();
       info->set("capacity", data::Element::create(static_cast<int64_t>(getCapacity())));
       info->set("size", data::Element::create(static_cast<int64_t>(getSize())));
       return (info);
    }

private:

    /// @brief Packet queue
    boost::circular_buffer<PacketTypePtr> queue_;

    /// @brief Mutex for protecting queue accesses.
    boost::scoped_ptr<std::mutex> mutex_;
};


/// @brief DHCPv4 packet queue buffer implementation
///
/// This implementation does not (currently) add any drop
/// or packet skip logic, it operates as a verbatim ring
/// queue for DHCPv4 packets.
///
class PacketQueueRing4 : public PacketQueueRing<Pkt4Ptr> {
public:
    /// @brief Constructor
    ///
    /// @param queue_type logical name of the queue implementation
    /// @param capacity maximum number of packets the queue can hold
    PacketQueueRing4(const std::string& queue_type, size_t capacity)
        : PacketQueueRing(queue_type, capacity) {
    };

    /// @brief virtual Destructor
    virtual ~PacketQueueRing4(){}
};

/// @brief DHCPv6 packet queue buffer implementation
///
/// This implementation does not (currently) add any drop
/// or packet skip logic, it operates as a verbatim ring
/// queue for DHCPv6 packets.
///
class PacketQueueRing6 : public PacketQueueRing<Pkt6Ptr> {
public:
    /// @brief Constructor
    ///
    /// @param queue_type logical name of the queue implementation
    /// @param capacity maximum number of packets the queue can hold
    PacketQueueRing6(const std::string& queue_type, size_t capacity)
        : PacketQueueRing(queue_type, capacity) {
    };

    /// @brief virtual Destructor
    virtual ~PacketQueueRing6(){}
};

}; // namespace isc::dhcp
}; // namespace isc

#endif // PACKET_QUEUE_RING_H
