// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_CONNECTION_POOL_H
#define TCP_CONNECTION_POOL_H

#include <tcp/tcp_connection.h>

#include <list>
#include <mutex>

namespace isc {
namespace tcp {

/// @brief Type of TCP connection pointer list.
typedef std::list<TcpConnectionPtr> TcpConnectionList;

/// @brief Pool of active TCP connections.
///
/// The TCP server is designed to handle many connections simultaneously.
/// The communication between the client and the server may take long time
/// and the server must be able to react on other events while the communication
/// with the clients is in progress. Thus, the server must track active
/// connections and gracefully close them when needed. An obvious case when the
/// connections must be terminated by the server is when the shutdown signal
/// is received.
///
/// This object is a simple container for the server connections which provides
/// means to terminate them on request.
class TcpConnectionPool {
public:

    /// @brief Start new connection.
    ///
    /// The connection is inserted to the pool and the
    /// @ref TcpConnection::asyncAccept is invoked.
    ///
    /// @param connection Pointer to the new connection.
    void start(const TcpConnectionPtr& connection);

    /// @brief Removes a connection from the pool and shutdown it.
    ///
    /// Shutdown is specific to TLS and is a first part of graceful close
    /// (note it is NOT the same as TCP shutdown system call).
    ///
    /// @note if the TLS connection stalls e.g. the peer does not try I/O
    /// on it the connection has to be explicitly stopped.
    ///
    /// @param connection Pointer to the connection.
    void shutdown(const TcpConnectionPtr& connection);

    /// @brief Removes a connection from the pool and stops it.
    ///
    /// @param connection Pointer to the connection.
    void stop(const TcpConnectionPtr& connection);

    /// @brief Stops all connections and removes them from the pool.
    ///
    /// @note This function is not thread-safe so should be called
    /// when the thread pool is stopped.
    void stopAll();

    /// @brief Returns the number of connections using a given remote IP address.
    ///
    /// Used to limit the number of connections when accepting a new one.
    ///
    /// @param remote_ip The remote IP address.
    /// @param[out] total_connections Size of the connection pool.
    /// @return The number of connections using a given remote IP address.
    size_t usedByRemoteIp(const asiolink::IOAddress& remote_ip,
                          size_t& total_connections);

    /// @brief Class/static started (i.e. added to pool) connection counter.
    static std::atomic<uint64_t> started_counter_;

    /// @brief Class/static stopped (i.e. removed from pool) connection counter.
    static std::atomic<uint64_t> stopped_counter_;

    /// @brief Class/static rejected (by the accept filter) connection counter.
    static std::atomic<uint64_t> rejected_counter_;

protected:

    /// @brief Stops all connections and removes them from the pool.
    ///
    /// Must be called from with a thread-safe context.
    void stopAllInternal();

    /// @brief Returns the number of connections using a given remote IP address.
    ///
    /// Used to limit the number of connections when accepting a new one.
    /// Must be called from with a thread-safe context.
    ///
    /// @param remote_ip The remote IP address.
    /// @param[out] total_connections Size of the connection pool.
    /// @return The number of connections using a given remote IP address.
    size_t usedByRemoteIpInternal(const asiolink::IOAddress& remote_ip,
                                  size_t& total_connections);

    /// @brief Set of connections.
    TcpConnectionList connections_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

}
}

#endif
