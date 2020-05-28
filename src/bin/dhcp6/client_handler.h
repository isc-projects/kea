// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <dhcp/pkt6.h>
#include <boost/noncopyable.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <mutex>
#include <thread>

namespace isc {
namespace dhcp {

/// @brief Define the type of packet processing continuation.
typedef std::function<void()> Continuation;

/// @brief Define the type of shared pointers to continuations.
typedef boost::shared_ptr<Continuation> ContinuationPtr;

/// @brief Continuation factory.
///
/// @param cont Continuation rvalue.
inline ContinuationPtr makeContinuation(Continuation&& cont) {
    return (boost::make_shared<Continuation>(cont));
}

/// @brief Client race avoidance RAII handler.
class ClientHandler : public boost::noncopyable {
private:

    /// Class (aka static) types, methods and members.

    /// @brief Structure representing a client.
    struct Client {

        /// @brief Constructor.
        ///
        /// @param query The query.
        /// @param client_id The client ID.
        /// @throw if the query is null or has empty client ID.
        Client(Pkt6Ptr query, DuidPtr client_id);

        /// @brief The query being processed.
        Pkt6Ptr query_;

        /// @brief Cached binary client ID.
        std::vector<uint8_t> duid_;

        /// @brief The ID of the thread processing the query.
        std::thread::id thread_;

        /// @brief The next query.
        ///
        /// @note This field can be modified from another handler
        /// holding the mutex.
        Pkt6Ptr next_query_;

        /// @brief The continuation to process next query for the client.
        ///
        /// @note This field can be modified from another handler
        /// holding the mutex.
        ContinuationPtr cont_;
    };

    /// @brief The type of shared pointers to clients.
    typedef boost::shared_ptr<Client> ClientPtr;

    /// @brief The type of the client container.
    typedef boost::multi_index_container<

        // This container stores pointers to client objects.
        ClientPtr,

        // Start specification of indexes here.
        boost::multi_index::indexed_by<

            // First index is used to search by Duid.
            boost::multi_index::hashed_unique<

                // Client ID binary content as a member of the Client object.
                boost::multi_index::member<
                    Client, std::vector<uint8_t>, &Client::duid_
                >
            >
        >
    > ClientContainer;

    /// @brief Lookup a client.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param duid The duid of the query from the client.
    /// @return The client found in the container or null.
    static ClientPtr lookup(const DuidPtr& duid);

    /// @brief Add a client.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param client The client to insert into the client container.
    static void add(const ClientPtr& client);

    /// @brief Delete a client.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param duid The duid to delete from the client container.
    static void del(const DuidPtr& duid);

    /// @brief Mutex to protect the client container.
    ///
    /// The mutex is used only by public methods for guards.
    static std::mutex mutex_;

    /// @brief The client container.
    static ClientContainer clients_;

public:

    /// Public interface.

    /// @brief Constructor.
    ClientHandler();

    /// @brief Destructor.
    ///
    /// Releases the client if it was acquired.
    virtual ~ClientHandler();

    /// @brief Tries to acquires a client.
    ///
    /// Lookup the client:
    ///  - if not found insert the client in the clients map and return true
    ///  - if found, if has a continuation put it in the holder,
    ///    and return false
    ///
    /// @param query The query from the client.
    /// @param cont The continuation in the case the client was held.
    /// @return true if the client was acquired, false if there is already
    /// a query from the same client.
    bool tryLock(Pkt6Ptr query, ContinuationPtr cont = ContinuationPtr());

private:

    /// Instance methods and members.

    /// @brief Acquire a client.
    ///
    /// The mutex must be held by the caller.
    void lock();

    /// @brief Release a client.
    ///
    /// If the client has a continuation, push it at front of the thread
    /// packet queue.
    ///
    /// The mutex must be held by the only caller: the destructor.
    void unLock();

    /// @brief Local client.
    ClientPtr client_;

    /// @brief Client ID locked by this handler.
    DuidPtr locked_;
};

} // namespace isc
} // namespace dhcp

#endif // CLIENT_HANDLER_H
