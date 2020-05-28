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

        /// @brief The next query.
        ///
        /// @note This field can be modified from another handler
        /// holding the mutex.
        Pkt4Ptr next_query_;

        /// @brief The continuation to process next query for the client.
        ///
        /// @note This field can be modified from another handler
        /// holding the mutex.
        ContinuationPtr cont_;
    };

    /// @brief The type of shared pointers to clients.
    typedef boost::shared_ptr<Client> ClientPtr;

    /// @brief The type of the client-by-id container.
    typedef boost::multi_index_container<

        // This container stores pointers to client-by-id objects.
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
    > ClientByIdContainer;

    /// @brief The type of the client-by-hwaddr container.
    typedef boost::multi_index_container<

        // This container stores pointers to client-by-hwaddr objects.
        ClientPtr,

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

    /// @brief Lookup a client by id.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param duid The duid of the query from the client.
    /// @return The client found in the by client id container or null.
    static ClientPtr lookup(const DuidPtr& duid);

    /// @brief Lookup a client by hwaddr.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param hwaddr The hardware address of the query from the client.
    /// @return The client found in the by hardware address container or null.
    static ClientPtr lookup(const HWAddrPtr& hwaddr);

    /// @brief Add a client by id.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param client The client to insert into the by id client container.
    static void addById(const ClientPtr& client);

    /// @brief Add a client by hwaddr.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param client The client to insert into the by hwaddr client container.
    static void addByHWAddr(const ClientPtr& client);

    /// @brief Delete a client by id.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param duid The duid to delete from the by id client container.
    static void del(const DuidPtr& duid);

    /// @brief Delete a client by hwaddr.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param hwaddr The hwaddr to delete from the by hwaddr client container.
    static void del(const HWAddrPtr& hwaddr);

    /// @brief Mutex to protect client containers.
    ///
    /// The mutex is used only by public methods for guards.
    static std::mutex mutex_;

    /// @brief The client-by-id container.
    static ClientByIdContainer clients_client_id_;

    /// @brief The client-by-hwaddr container.
    static ClientByHWAddrContainer clients_hwaddr_;

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
    bool tryLock(Pkt4Ptr query, ContinuationPtr cont = ContinuationPtr());

private:

    /// Instance methods and members.

    /// @brief Acquire a client by client ID option.
    ///
    /// The mutex must be held by the caller.
    void lockById();

    /// @brief Acquire a client by hardware address.
    ///
    /// The mutex must be held by the caller.
    void lockByHWAddr();

    /// @brief Release a client by client ID option.
    ///
    /// The mutex must be held by the caller.
    void unLockById();

    /// @brief Release a client by hardware address.
    ///
    /// The mutex must be held by the caller.
    void unLockByHWAddr();

    /// @brief Local client.
    ClientPtr client_;

    /// @brief Client ID locked by this handler.
    DuidPtr locked_client_id_;

    /// @brief Hardware address locked by this handler.
    HWAddrPtr locked_hwaddr_;
};

} // namespace isc
} // namespace dhcp

#endif // CLIENT_HANDLER_H
