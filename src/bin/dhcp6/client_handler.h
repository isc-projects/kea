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
#include <mutex>
#include <thread>

namespace isc {
namespace dhcp {

/// @brief Client race avoidance RAII handler.
class ClientHandler : public boost::noncopyable {
public:

    /// @brief Constructor.
    ClientHandler();

    /// @brief Destructor.
    ///
    /// Releases the client if it was acquired.
    virtual ~ClientHandler();

    /// @brief Tries to acquires a client.
    ///
    /// @param query The query from the client.
    /// @return true if the client was acquired, false if there is already
    /// a query from the same client.
    bool tryLock(Pkt6Ptr query);

private:

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
    };

    /// @brief The type of unique pointers to clients.
    typedef std::unique_ptr<Client> ClientPtr;

    /// @brief Client ID locked by this handler.
    DuidPtr locked_;

    /// @brief Mutex to protect the client container.
    static std::mutex mutex_;

    /// @brief Lookup a client.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param duid The duid of the query from the client.
    /// @return The held client or null.
    static ClientPtr lookup(const DuidPtr& duid);

    /// @brief Acquire a client.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param client The filled client object.
    void lock(Client client);

    /// @brief Release a client.
    ///
    /// The mutex must be held by the caller.
    void unLock();

    /// @brief The type of the client container.
    typedef boost::multi_index_container<

        // This container stores client objects.
        Client,

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

    /// @brief The client container.
    static ClientContainer clients_;
};

} // namespace isc
} // namespace dhcp

#endif // CLIENT_HANDLER_H
