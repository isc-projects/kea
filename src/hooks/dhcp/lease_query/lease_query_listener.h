// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_QUERY_LISTENER_H
#define LEASE_QUERY_LISTENER_H

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <dhcp/pkt.h>
#include <tcp/tcp_listener.h>
#include <tcp/tcp_connection.h>
#include <lease_query_connection.h>

namespace isc {
namespace lease_query {

/// @brief Derivation of TcpListener specific to Bulk Lease Query
class LeaseQueryListener : public tcp::TcpListener {
public:
    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the listener.
    /// @param server_address Address on which the TCP service should run.
    /// @param server_port Port number on which the TCP service should run.
    /// @param tls_context TLS context.
    /// @param idle_timeout Timeout after which an idle TCP connection is
    /// @param filter_callback Callback invoked during connection acceptance
    /// that can allow or deny connections based on the remote endpoint.
    /// @param family Protocol family, AF_INET or AF_INET6.
    /// @param max_concurrent_queries Maximum number of in-progress queries allowed.
    /// Defaults to zero (unlimited).
    LeaseQueryListener(const asiolink::IOServicePtr& io_service,
                       const asiolink::IOAddress& server_address,
                       const unsigned short server_port,
                       const asiolink::TlsContextPtr& tls_context,
                       const tcp::TcpListener::IdleTimeout& idle_timeout,
                       const tcp::TcpConnectionFilterCallback& filter_callback,
                       const uint16_t family,
                       const size_t max_concurrent_queries = 0)
        : tcp::TcpListener(io_service,
                           server_address,
                           server_port,
                           tls_context,
                           idle_timeout,
                           filter_callback),
          family_(family),
          max_concurrent_queries_(max_concurrent_queries) {
    }

    /// @brief Destructor.
    virtual ~LeaseQueryListener() {
    }

protected:
    /// @brief Creates an instance of the @c TcpConnection.
    ///
    /// @param acceptor_callback Callback invoked when new connection is accepted.
    /// @param connection_filter Callback invoked during connection acceptance
    /// that can allow or deny connections based on the remote endpoint.
    /// @return Pointer to the created connection.
    virtual tcp::TcpConnectionPtr createConnection(
            const tcp::TcpConnectionAcceptorCallback& acceptor_callback,
            const tcp::TcpConnectionFilterCallback& connection_filter) {
        LeaseQueryConnectionPtr conn(new LeaseQueryConnection(io_service_,
                                                              acceptor_,
                                                              tls_context_,
                                                              connections_,
                                                              acceptor_callback,
                                                              connection_filter,
                                                              idle_timeout_,
                                                              family_,
                                                              max_concurrent_queries_));
        return (conn);
    }

    /// @brief Protocol family AF_INET or AF_INET6
    uint16_t family_;

    /// @brief Maximum number of concurrent queries allowed. Zero means
    /// unlimited.
    size_t max_concurrent_queries_;
};

/// @brief Defines a pointer to a LeaseQueryListener.
typedef boost::shared_ptr<LeaseQueryListener> LeaseQueryListenerPtr;

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // LEASE_QUERY_LISTENER_H
