// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

/// @todo TKM rewrite this...

/// Each Kea server supporting Configuration Backend feature implements
/// a "manager" class which holds information about supported and
/// configured backends and provides access to the backends. This is
/// similar to @c HostMgr and @c LeaseMgr singletons being used by the
/// DHCP servers.
///
/// The Config Backend Managers are typically implemented as singletons
/// which can be accessed from any place within the server code. This
/// includes server configuration, data fetching during normal server
/// operation and data management, including processing of control
/// commands implemented within hooks libraries.
///
/// The @c BaseConfigBackendMgr is a base class for all PQMs implemented
/// for respective Kea servers. It includes mechanisms to register config
/// backend factory functions and to create instances of the backends using
/// those factory functions as a result of server configuration. The mechanism
/// of factory functions registration is useful in cases when the config
/// backend is implemented within the hook library. Such hook library
/// registers factory function in its @c load function and the server
/// simply calls this function to create the instance of this backend when
/// instructed to do so via configuration. Similar mechanism exists in
/// DHCP @c HostMgr.
///
/// Unlike @c HostMgr, the PQMs do not directly expose API to fetch and
/// manipulate the data in the database. This is done via, so called,
/// Configuration Backends Pools. See @c BaseConfigBackendPool for
/// details. The @c BaseConfigBackendMgr is provided with the pool type
/// via class template parameter. Respective PQM implementations
/// use their own pools, which provide APIs appropriate for those
/// implementations.
///
/// @tparam ConfgBackendPoolType Type of the configuration backend pool
/// to be used by the manager. It must derive from @c BaseConfigBackendPool
/// template class.
template<typename PacketQueueTypePtr>
class PacketQueueMgr {
public:
    /// @brief Type of the backend factory function.
    ///
    /// Factory function returns a pointer to the instance of the configuration
    /// backend created.
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
                                const Factory& factory) {
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
    ///
    /// @param queue_type queue type, e.g. "kea-ring4".
    ///
    /// @return false if no factory for the given type was unregistered, true
    /// if the factory was removed.
    bool unregisterPacketQueueFactory(const std::string& queue_type) {
        // Look for it.
        auto index = factories_.find(queue_type);

        // If it's there remove it
        if (index != factories_.end()) {
            factories_.erase(index);
        // @todo What do we do here, if we only have one queue?
        // I think we don't care, as we should be reloading/reconfiging...
        // It may be that PQM doesn't retain the instance at all?
        //  pool_->delAllBackends(db_type);
            return (true);

        }

        return (false);
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
        } catch (std::exception& ex) {
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

protected:
    /// @brief A map holding registered backend factory functions.
    std::map<std::string, Factory> factories_;

    /// @brief the current queue_ ?
    PacketQueueTypePtr packet_queue_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // PACKET_QUEUE_MGR_H
