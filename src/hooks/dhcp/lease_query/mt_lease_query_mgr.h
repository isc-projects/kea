// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MT_LEASE_QUERY_LISTENER_MGR_H
#define MT_LEASE_QUERY_LISTENER_MGR_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/io_service_thread_pool.h>
#include <tcp/mt_tcp_listener_mgr.h>
#include <lease_query_listener.h>
#include <thread>
#include <vector>

namespace isc {
namespace lease_query {

/// @brief Manages a thread-pool that is used to drive a LeaseQueryListener
///
/// This class manages an IOServiceThreadPool which in turn is used to
/// drive an internal instance of LeaseQueryListener. This allows the
/// listener connections to each run on their own thread within the
/// pool. The pool can be started, paused, resumed, and stopped.
///
/// @note This class is NOT compatible with Kea core single-threading.
/// It is incumbent upon the owner to ensure the Kea core multi-threading
/// is (or will be) enabled when creating instances of this class.
class MtLeaseQueryListenerMgr : public tcp::MtTcpListenerMgr {
public:
    /// @brief Constructor.
    ///
    /// @param address IP address to listen on for connections.
    /// @param port TCP port to listen on for connections.
    /// @param family protocol family the manager serves (AF_INET or AF_INET6).
    /// @param idle_timeout Timeout after which a TCP connection is
    /// closed by the server.
    /// @param thread_pool_size Maximum Number of threads in the thread pool.
    /// This implicit dictates the maximum number of connections.
    /// @param context TLS context for authenticating connections. Defaults
    /// to empty.
    /// @param connection_filter Callback connections may use to filter
    /// connections by their remote endpoint characteristics (e.g. IP address).
    /// @param max_concurrent_queries maximum number of concurrent queries per
    /// connection. Defaults to zero (unlimited).
    MtLeaseQueryListenerMgr(const asiolink::IOAddress& address,
                            const uint16_t port,
                            const uint16_t family,
                            const tcp::TcpListener::IdleTimeout& idle_timeout,
                            const uint16_t thread_pool_size = 1,
                            asiolink::TlsContextPtr context = asiolink::TlsContextPtr(),
                            tcp::TcpConnectionFilterCallback connection_filter = 0,
                            const size_t max_concurrent_queries = 0);

    /// @brief Destructor
    virtual ~MtLeaseQueryListenerMgr();

    /// @brief Defines a factory function for creating listeners.
    ///
    /// @param io_service IO service to be used by the listener.
    /// @param server_address IP address to listen on for connections.
    /// @param server_port TCP port to listen on for connections.
    /// @param tls_context TLS context for authenticating connections.
    /// @param idle_timeout Timeout after which a TCP connection is
    /// closed by the server.
    /// @param connection_filter Callback connections may use to filter
    /// connections by their remote endpoint characteristics (e.g. ip address)
    tcp::TcpListenerPtr listenerFactory(const asiolink::IOServicePtr& io_service,
                                        const asiolink::IOAddress& server_address,
                                        const unsigned short server_port,
                                        const asiolink::TlsContextPtr& tls_context,
                                        const tcp::TcpListener::IdleTimeout& idle_timeout,
                                        const tcp::TcpConnectionFilterCallback& connection_filter);
private:
    /// @brief Protocol family AF_INET or AF_INET6.
    uint16_t family_;

    /// @brief Maximum number of concurrent queries allowed per connection.
    size_t max_concurrent_queries_;
};

/// @brief Defines a shared pointer to MtLeaseQueryListenerMgr.
typedef boost::shared_ptr<MtLeaseQueryListenerMgr> MtLeaseQueryListenerMgrPtr;

} // namespace isc::lease_query
} // namespace isc

#endif // MT_LEASE_QUERY_LISTENER_MGR_H
