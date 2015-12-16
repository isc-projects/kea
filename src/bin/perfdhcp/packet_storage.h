// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_STORAGE_H
#define PACKET_STORAGE_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <stdint.h>

namespace isc {
namespace perfdhcp {

/// \brief Represents a list of packets with a sequential and random access to
/// list elements.
///
/// The main purpose of this class is to support sending Renew and Release
/// messages from perfdhcp. The Renew and Release messages are sent for existing
/// leases only. Therefore, the typical use case for this class is that it holds
/// a list of Reply messages sent by the server in response to Request messages.
/// The Request messages hold addresses and/or IPv6 prefixes acquired so they
/// can be used to identify existing leases. When perfdhcp needs to send Renew
/// or Release message, it will access one of the elements on this list and
/// will create the Renew or Release message based on its content. Once the
/// element (packet) is returned it is also deleted from the list, so as it is
/// not used again. This class provide either sequential access to the packets
/// or random access. The random access algorithm is much slower but at least
/// it allows to simulate more real scenario when the renewing or releasing
/// client is random.
///
/// \tparam Pkt4 or Pkt6 class, which represents DHCPv4 or DHCPv6 message
/// respectively.
///
/// \note Although the class is intended to hold Pkt4 and Pkt6 objects, the
/// current implementation is generic enough to holds any object wrapped in the
/// boost::shared_ptr.
template<typename T>
class PacketStorage : public boost::noncopyable {
public:
    /// A type which represents the pointer to a packet.
    typedef boost::shared_ptr<T> PacketPtr;

private:
    /// An internal container actually holding packets.
    typedef typename std::list<PacketPtr> PacketContainer;
    /// An iterator to the element in the internal container.
    typedef typename PacketContainer::iterator PacketContainerIterator;

public:

    /// \brief Constructor.
    PacketStorage() { }

    /// \brief Appends the new packet object to the collection.
    ///
    /// \param packet A pointer to an object representing a packet.
    void append(const PacketPtr& packet) {
        storage_.push_back(packet);
        if (storage_.size() == 1) {
            current_pointer_ = storage_.begin();
        }
    }

    /// \brief Removes packets from the storage.
    ///
    /// It is possible to specify a number of packets to be removed
    /// from a storage. Packets are removed from the beginning of the
    /// storage. If specified number is greater than the size of the
    /// storage, all packets are removed.
    ///
    /// @param num A number of packets to be removed. If omitted,
    /// all packets will be removed.
    void clear(const uint64_t num = 0) {
        if (num != 0) {
            PacketContainerIterator last = storage_.begin();
            std::advance(last, num > size() ? size() : num);
            current_pointer_ = storage_.erase(storage_.begin(), last);
        } else {
            storage_.clear();
            current_pointer_ = storage_.begin();
        }
    }

    /// \brief Checks if the storage has no packets.
    ///
    /// \return true if storage is empty, false otherwise.
    bool empty() const {
        return (storage_.empty());
    }

    /// \brief Returns next packet from the storage.
    ///
    /// This function returns packets sequentially (in the same order
    /// in which they have been appended). The returned packet is
    /// instantly removed from the storage.
    ///
    /// \return next packet from the storage.
    PacketPtr getNext() {
        if (storage_.empty()) {
            return (PacketPtr());
        } else if (current_pointer_ == storage_.end()) {
            current_pointer_ = storage_.begin();
        }
        PacketPtr packet = *current_pointer_;
        current_pointer_ = storage_.erase(current_pointer_);
        return (packet);
    }

    /// \brief Returns random packet from the storage.
    ///
    /// This function picks random packet from the storage and returns
    /// it. It is way slower than the @c getNext function because it has to
    /// iterate over all existing entries from the beginning of the storage
    /// to the random packet's position. Therefore, care should be taken
    /// when using this function to access elements when storage is large.
    ///
    /// \return random packet from the storage.
    PacketPtr getRandom() {
        if (empty()) {
            return (PacketPtr());
        }
        current_pointer_ = storage_.begin();
        if (size() > 1) {
            std::advance(current_pointer_, rand() % (size() - 1));
        }
        PacketPtr packet = *current_pointer_;
        current_pointer_ = storage_.erase(current_pointer_);
        return (packet);
    }

    /// \brief Returns number of packets in the storage.
    ///
    /// \return number of packets in the storage.
    uint64_t size() const {
        return (storage_.size());
    }

private:

    std::list<PacketPtr> storage_;            ///< Holds all appended packets.
    PacketContainerIterator current_pointer_; ///< Holds the iterator to the
                                              ///< next element returned.

};

} // namespace perfdhcp
} // namespace isc

#endif // PACKET_STORAGE_H
