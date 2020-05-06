// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <dhcp/pkt4.h>
#include <boost/noncopyable.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
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
    bool tryLock(Pkt4Ptr query);

private:

    /// @brief Structure representing a client.
    struct Client {

        /// @brief Constructor.
        ///
        /// @param query The query.
        /// @param client_id The client ID.
        /// @param hwaddr The hardware address.
        /// @throw if the query is null or client_id and hwaddr are null.
        Client(Pkt4Ptr query, DuidPtr client_id, HWAddrPtr hwaddr);

        /// @brief The query being processed.
        Pkt4Ptr query_;

        /// @brief Cached binary client ID.
        std::vector<uint8_t> duid_;

        /// @brief Cached hardware type.
        uint16_t htype_;

        /// @brief Cached binary hardware address.
        std::vector<uint8_t> hwaddr_;

        /// @brief The ID of the thread processing the query.
        std::thread::id thread_;
    };

    /// @brief The type of unique pointers to clients by ID.
    typedef std::unique_ptr<Client> ClientPtr;

    /// @brief Client ID locked by this handler.
    DuidPtr locked_client_id_;

    /// @brief Hardware address locked by this handler.
    HWAddrPtr locked_hwaddr_;

    /// @brief Mutex to protect the client-by-id container.
    static std::mutex mutex_client_id_;

    /// @brief Mutex to protect the client-by-hwaddr container.
    static std::mutex mutex_hwaddr_;

    /// @brief Lookup a client-by-id.
    ///
    /// The by-id mutex must be held by the caller.
    ///
    /// @param duid The duid of the query from the client.
    /// @return The held client or null.
    static ClientPtr lookup(const DuidPtr& duid);

    /// @brief Lookup a client-by-hwaddr.
    ///
    /// The by-hwaddr mutex must be held by the caller.
    ///
    /// @param duid The duid of the query from the client.
    /// @return The held client or null.
    static ClientPtr lookup(const HWAddrPtr& hwaddr);

    /// @brief Acquire a client by client ID option.
    ///
    /// The by-id mutex must be held by the caller.
    ///
    /// @param client The filled client object.
    void lockById(Client client);

    /// @brief Acquire a client by hardware address.
    ///
    /// The by-hwaddr mutex must be held by the caller.
    ///
    /// @param client The filled client object.
    void lockByHWAddr(Client client);

    /// @brief Release a client by client ID option.
    ///
    /// The by-idmutex must be held by the caller.
    void unLockById();

    /// @brief Release a client by hardware address.
    ///
    /// The by-hwaddr mutex must be held by the caller.
    void unLockByHWAddr();

    /// @brief The type of the client-by-id container.
    typedef boost::multi_index_container<

        // This container stores client-by-id objects.
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
    > ClientByIdContainer;

    /// @brief The client-by-id container.
    static ClientByIdContainer clients_client_id_;

    /// @brief The type of the client-by-hwaddr container.
    typedef boost::multi_index_container<

        // This container stores client-by-hwaddr objects.
        Client,

        // Start specification of indexes here.
        boost::multi_index::indexed_by<

            // First index is used to search by HWAddr.
            boost::multi_index::hashed_unique<

                // This is a composite index for type and binary components.
                boost::multi_index::composite_key<
                    Client,
                    boost::multi_index::member<
                        Client, uint16_t, &Client::htype_
                    >,
                    boost::multi_index::member<
                        Client, std::vector<uint8_t>, &Client::hwaddr_
                    >
                >
            >
        >
    > ClientByHWAddrContainer;

    /// @brief The client-by-hwaddr container.
    static ClientByHWAddrContainer clients_hwaddr_;

};

} // namespace isc
} // namespace dhcp

#endif // CLIENT_HANDLER_H
