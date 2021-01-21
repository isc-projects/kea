// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PACKET_QUEUE_MGR_H
#define PACKET_QUEUE_MGR_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcp/packet_queue.h>
#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <map>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Invalid Queue type exception
///
/// Thrown when a packet queue manager doesn't recognize the type of the queue.
class InvalidQueueType : public Exception {
public:
    InvalidQueueType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Packet Queue Managers (PQM).
///
/// Base class to manage the registry of packet queue implementations
/// and the creation of and access to the current packet queue.
///
/// @tparam PacktQueueTypePtr Base type of packet queues managed by
/// the manager (e.g. PacketQueue4Ptr, PacketQueue6Ptr).
template<typename PacketQueueTypePtr>
class PacketQueueMgr {
public:
    /// @brief Defines the type of the packet queue factory function.
    ///
    /// Factory function returns a pointer to the instance of the packet
    /// queue created.
    typedef std::function<PacketQueueTypePtr(data::ConstElementPtr)> Factory;

    /// @brief Constructor.
    PacketQueueMgr()
        : factories_(), packet_queue_() {
    }

    /// @brief Registers new queue factory function for a given queue type.
    ///
    /// The typical usage of this function is to make the PQM aware of a
    /// packet queue implementation. This implementation may exist
    /// in a hooks library. In such a case, this function should be called from
    /// the @c load function in this library. When the queue impl is registered,
    /// the server will use it when required by the configuration, i.e. a
    /// user specifies it in "queue-control:queue-type"
    ///
    /// If the given queue type has already been registered, perhaps
    /// by another hooks library, the PQM will refuse to register another
    /// of the same type.
    ///
    /// @param queue_type Queue type, e.g. "kea-ring4"
    /// @param factory Pointer to the queue factory function.
    ///
    /// @return true if the queue type has been successfully registered, false
    /// if the type already exists.
    bool registerPacketQueueFactory(const std::string& queue_type,
                                    Factory factory) {
        // Check if this backend has been already registered.
        if (factories_.count(queue_type)) {
            return (false);
        }

        // Register the new backend.
        factories_.insert(std::make_pair(queue_type, factory));
        return (true);
    }

    /// @brief Unregisters the queue factory function for a given type.
    ///
    /// This function is used to remove the factory function for a given type.
    /// Typically, it would be called when unloading the hook library which
    /// loaded the type, and thus called by the library's @c unload function.
    /// In addition to removing the factory, it will also destroy the current
    /// queue if it is of the same queue-type as the factory being removed.
    /// This avoids the nastiness that occurs when objecs are left in existence
    /// after their library is unloaded.
    ///
    /// @param queue_type queue type, e.g. "kea-ring4".
    ///
    /// @return false if no factory for the given type was unregistered, true
    /// if the factory was removed.
    bool unregisterPacketQueueFactory(const std::string& queue_type) {
        // Look for it.
        auto index = factories_.find(queue_type);

        // Not there so nothing to do.
        if (index == factories_.end()) {
            return (false);
        }

        // If the queue is of the type being unregistered, then remove it. We don't
        // a queue instance outliving its library.
        if ((packet_queue_) && (packet_queue_->getQueueType() == queue_type)) {
            packet_queue_.reset();
        }

        // Remove the factory.
        factories_.erase(index);

        return (true);
    }

    /// @brief Create an instance of a packet queue.
    ///
    /// Replace the current packet queue with a new one based on the
    /// given configuration parameters.  The set of parameters must
    /// contain at least "queue-type".  This value is used to locate
    /// the registered queue factory to invoke to create the new queue.
    ///
    /// The factory is passed the parameters verbatim for its use in
    /// creating the new queue.  Factories are expected to throw exceptions
    /// on creation failure. Note the existing queue is not altered or
    /// replaced unless the new queue is successfully created.
    ///
    /// @throw InvalidQueueParameter if parameters is not map that contains
    /// "queue-type", InvalidQueueType if the queue type requested is not
    /// supported.
    /// @throw Unexpected if the backend factory function returned NULL.
    void createPacketQueue(data::ConstElementPtr parameters) {
        if (!parameters) {
            isc_throw(Unexpected, "createPacketQueue - queue parameters is null");
        }

        // Get the database type to locate a factory function.
        std::string queue_type ;
        try {
            queue_type = data::SimpleParser::getString(parameters, "queue-type");
        } catch (const std::exception& ex) {
            isc_throw(InvalidQueueParameter, "queue-type missing or invalid: " << ex.what());
        }

        // Look up the factory.
        auto index = factories_.find(queue_type);

        // Punt if there is no matching factory.
        if (index == factories_.end()) {
            isc_throw(InvalidQueueType, "The type of the packet queue: '" <<
                      queue_type << "' is not supported"); }

        // Call the factory to create the new queue.
        // Factories should throw InvalidQueueParameter if given
        // bad values in the control.
        auto new_queue = index->second(parameters);
        if (!new_queue) {
            isc_throw(Unexpected, "Packet queue " << queue_type <<
                      " factory returned NULL");
        }

        // Replace the existing queue with the new one.
        packet_queue_ = new_queue;
    }

    /// @brief Returns underlying packet queue.
    PacketQueueTypePtr getPacketQueue() const {
        return (packet_queue_);
    }

    /// @brief Destroys the current packet queue.
    /// Any queued packets will be discarded.
    void destroyPacketQueue() {
        packet_queue_.reset();
    }

protected:
    /// @brief A map holding registered backend factory functions.
    std::map<std::string, Factory> factories_;

    /// @brief the current queue_ ?
    PacketQueueTypePtr packet_queue_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // PACKET_QUEUE_MGR_H
