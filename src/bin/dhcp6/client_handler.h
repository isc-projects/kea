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
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
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
        /// @throw if the query is null or has empty client ID.
        Client(Pkt6Ptr query);

        /// @brief The query being processed.
        Pkt6Ptr query_;

        /// @brief The ID of the thread processing the query.
        std::thread::id thread_;

        /// @brief Key extractor.
        ///
        /// Returns the content of the Duid aka client ID.
        const std::vector<uint8_t>& getClientId() const {
            return (query_->getClientId()->getDuid());
        }
    };

    /// @brief Query locked by this handler.
    Pkt6Ptr locked_;

    /// @brief Mutex to protect the client container.
    static std::mutex mutex_;

    /// @brief Lookup a client.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param duid The duid of the query from the client.
    /// @return The query holding the client or null.
    static Pkt6Ptr lookup(const DuidPtr& duid);

    /// @brief Acquire a client.
    ///
    /// The mutex must be held by the caller.
    void lock();

    /// @brief Release a client.
    ///
    /// The mutex must be held by the caller.
    void unLock();

    /// @brief The type of the client container.
    typedef boost::multi_index_container<

        // This container stores clients.
        Client,

        // Start specification of indexes here.
        boost::multi_index::indexed_by<

            // First index is used to search by Duid.
            boost::multi_index::hashed_unique<

                // Duid content is extracted by calling Client::getClientId()
                boost::multi_index::const_mem_fun<
                    Client, const std::vector<uint8_t>&, &Client::getClientId
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
