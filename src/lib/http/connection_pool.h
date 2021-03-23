// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_CONNECTION_POOL_H
#define HTTP_CONNECTION_POOL_H

#include <http/connection.h>

#include <list>
#include <mutex>

namespace isc {
namespace http {

/// @brief Pool of active HTTP connections.
///
/// The HTTP server is designed to handle many connections simultaneously.
/// The communication between the client and the server may take long time
/// and the server must be able to react on other events while the communication
/// with the clients is in progress. Thus, the server must track active
/// connections and gracefully close them when needed. An obvious case when the
/// connections must be terminated by the server is when the shutdown signal
/// is received.
///
/// This object is a simple container for the server connections which provides
/// means to terminate them on request.
class HttpConnectionPool {
public:

    /// @brief Start new connection.
    ///
    /// The connection is inserted to the pool and the
    /// @ref HttpConnection::asyncAccept is invoked.
    ///
    /// @param connection Pointer to the new connection.
    void start(const HttpConnectionPtr& connection);

    /// @brief Removes a connection from the pool and shutdown it.
    ///
    /// Shutdown is specific to TLS and is a first part of graceful close (note it is
    /// NOT the same as TCP shutdown system call).
    ///
    /// @note if the TLS connection stalls e.g. the peer does not try I/O
    /// on it the connection has to be explicitly stopped.
    ///
    /// @param connection Pointer to the connection.
    void shutdown(const HttpConnectionPtr& connection);

    /// @brief Removes a connection from the pool and stops it.
    ///
    /// @param connection Pointer to the connection.
    void stop(const HttpConnectionPtr& connection);

    /// @brief Stops all connections and removes them from the pool.
    void stopAll();

protected:

    /// @brief Stops all connections and removes them from the pool.
    ///
    /// Must be called from with a thread-safe context.
    void stopAllInternal();

    /// @brief Set of connections.
    std::list<HttpConnectionPtr> connections_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

}
}

#endif

