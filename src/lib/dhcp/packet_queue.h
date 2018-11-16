// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/threads/sync.h>

#include <boost/function.hpp>
#include <boost/circular_buffer.hpp>
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
/// @note Derivations of this class MUST BE thread-safe.
/// @endnote
///
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
    /// Calls @c shouldDropPacket to determine if the packet should be queued
    /// or dropped.  If it should be queued it is added to the end of the
    /// queue specified by the "to" parameter.
    ///
    /// @param packet packet to enqueue
    /// @param source socket the packet came from
    /// @param to end of the queue from which to remove packet(s).
    /// Defaults to BACK.
    ///
    void enqueuePacket(PacketTypePtr packet, const SocketInfo& source,
                       const QueueEnd& to=QueueEnd::BACK) {
        if (!shouldDropPacket(packet, source)) {
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
    /// This function is called at the beginning of @c enqueuePacket and
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
    /// based on their own requirements.  The default implemenation is to
    /// to simply return without skipping any packets.
    ///
    /// @param from end of the queue from which packets should discarded
    /// This is passed in from @c dequeuePackets.
    ///
    /// @param from specifies the end of the queue from which packets
    /// should be discarded.
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
    virtual void pushPacket(PacketTypePtr& packet, const QueueEnd& to=QueueEnd::BACK) = 0;

    /// @brief Pops a packet from the queue
    ///
    /// Removes a packet from the end of the queue specified and returns it.
    ///
    /// @param from specifies the end of the queue from which the packet
    /// should be taken.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    virtual PacketTypePtr popPacket(const QueueEnd& from=QueueEnd::FRONT) = 0;

    /// @brief Gets the packet currently at one end of the queue
    ///
    /// Returns a pointer the packet at the specified end of the
    /// queue without dequeuing it.
    ///
    /// @param from specifies which end of the queue to examine.
    ///
    /// @return A pointer to packet, or an empty pointer if the
    /// queue is empty.
    virtual const PacketTypePtr peek(const QueueEnd& from=QueueEnd::FRONT) const = 0;

    /// @brief return True if the queue is empty.
    virtual bool empty() const = 0;

    /// @todo size may not apply either... what if there are two internal buffers?
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
       return(info);
    }

    /// @brief Fetches a JSON string representation of queue operational info
    ///
    /// This method calls @c getInfo() and then converts that into JSON text.
    ///
    /// @return string of JSON text
    virtual std::string getInfoStr() const {
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


/// @brief Provides an abstract ring-buffer implementation of the PacketQueue interface.
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
    }

    /// @brief virtual Destructor
    virtual ~PacketQueueRing(){};

    /// @brief Pushes a packet onto the queue
    ///
    ///  Adds a packet onto the end of queue specified.  Note that this
    ///  function is protected by a Mutex.
    ///
    /// @param packet packet to add to the queue
    /// @param to specifies the end of the queue to which the packet
    /// should be added.
    virtual void pushPacket(PacketTypePtr& packet, const QueueEnd& to=QueueEnd::BACK) {
        isc::util::thread::Mutex::Locker lock(mutex_);
        if (to == QueueEnd::BACK) {
            queue_.push_back(packet);
        } else {
            queue_.push_front(packet);
        }
    }

    /// @brief Pops a packet from the queue
    ///
    /// Removes a packet from the end of the queue specified and returns it.  Note
    /// that this function is protected by a Mutex.
    ///
    /// @param from specifies the end of the queue from which the packet
    /// should be taken.
    ///
    /// @return A pointer to dequeued packet, or an empty pointer
    /// if the queue is empty.
    virtual PacketTypePtr popPacket(const QueueEnd& from = QueueEnd::FRONT) {
        isc::util::thread::Mutex::Locker lock(mutex_);
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
        return(queue_.empty());
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
       return(info);
    }

private:

    /// @brief Packet queue
    boost::circular_buffer<PacketTypePtr> queue_;

    /// @brief Mutex for protecting queue accesses.
    isc::util::thread::Mutex mutex_;
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

#endif // PACKET_QUEUE_H
