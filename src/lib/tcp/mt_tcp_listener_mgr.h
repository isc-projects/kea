// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MT_TCP_LISTENER_MGR_H
#define MT_TCP_LISTENER_MGR_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/io_service_thread_pool.h>
#include <tcp/tcp_listener.h>
#include <thread>
#include <vector>

namespace isc {
namespace tcp {

/// @brief Default connection idle timeout in milliseconds.
const long TCP_IDLE_CONNECTION_TIMEOUT = 300 * 1000;

/// @brief Defines a factory function for creating TcpListeners.
typedef std::function<
        TcpListenerPtr(asiolink::IOService& io_service,
                       const asiolink::IOAddress& server_address,
                       const unsigned short server_port,
                       const asiolink::TlsContextPtr& tls_context,
                       const TcpListener::IdleTimeout& idle_timeout,
                       const TcpConnectionFilterCallback& connection_filter)
    > TcpListenerFactory;

/// @brief Manages a thread-pool that is used to drive a TcpListener
///
/// This class manages an IOServiceThreadPool which in turn is used to
/// drive an internal instance of TcpListener. This allows the listener connections
/// to each run on their own thread within the pool.  The pool can be started, paused,
/// resumed, and stopped.
///
/// @note This class is NOT compatible with Kea core single-threading.
/// It is incumbent upon the owner to ensure the Kea core multi-threading
/// is (or will be) enabled when creating instances of this class.
class MtTcpListenerMgr {
public:
    /// @brief Constructor
    ///
    /// @param listener_factory Function for instantiating the internal
    /// TcpListener
    /// @param address Ip address to listen on for connections
    /// @param port Ip port to listen on for connections
    /// @param thread_pool_size Maximum Number of threads in the thread pool.
    /// This implicit dictates the maximum number of connections.
    /// @param context TLS context for authenticating connections. Defaults
    /// to empty.
    /// @param connection_filter Callback connections may use to filter
    /// connections by their remote endpoint characteristics (e.g. ip address)
    MtTcpListenerMgr(TcpListenerFactory listener_factory,
                     const asiolink::IOAddress& address,
                     const uint16_t port,
                     const uint16_t thread_pool_size = 1,
                     asiolink::TlsContextPtr context = asiolink::TlsContextPtr(),
                     TcpConnectionFilterCallback connection_filter = 0);

    /// @brief Destructor
    virtual ~MtTcpListenerMgr();

    /// @brief Check if the current thread can perform thread pool state
    /// transition.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPermissions();

    /// @brief Starts running the listener's thread pool.
    void start();

    /// @brief Pauses the listener's thread pool.
    ///
    /// Suspends thread pool event processing.
    void pause();

    /// @brief Resumes running the listener's thread pool.
    ///
    /// Resumes thread pool event processing.
    void resume();

    /// @brief Stops the listener's thread pool.
    void stop();

    /// @brief Indicates if the thread pool is running.
    ///
    /// @return True if the thread pool exists and it is in the RUNNING state,
    /// false otherwise.
    bool isRunning();

    /// @brief Indicates if the thread pool is stopped.
    ///
    /// @return True if the thread pool does not exist or it is in the STOPPED
    /// state, false otherwise.
    bool isStopped();

    /// @brief Indicates if the thread pool is paused.
    ///
    /// @return True if the thread pool exists and it is in the PAUSED state,
    /// false otherwise.
    bool isPaused();

    /// @brief Fetches the IP address on which to listen.
    ///
    /// @return IOAddress containing the address on which to listen.
    isc::asiolink::IOAddress getAddress() const {
        return (address_);
    }

    /// @brief Fetches the port number on which to listen.
    ///
    /// @return uint16_t containing the port number on which to listen.
    uint16_t getPort() const {
        return (port_);
    }

    /// @brief Fetches the maximum size of the thread pool.
    ///
    /// @return uint16_t containing the maximum size of the thread pool.
    uint16_t getThreadPoolSize() const {
        return (thread_pool_size_);
    }

    /// @brief Fetches the TLS context.
    ///
    /// @return TLS context.
    asiolink::TlsContextPtr getTlsContext() const {
        return (tls_context_);
    }

    /// @brief Fetches the number of threads in the pool.
    ///
    /// @return uint16_t containing the number of running threads.
    uint16_t getThreadCount() const {
        if (!thread_pool_) {
            return (0);
        }

        return (thread_pool_->getThreadCount());
    }

    /// @brief Fetches a pointer to the internal IOService used to
    /// drive the thread-pool in multi-threaded mode.
    ///
    /// @return pointer to the IOService instance, or an empty pointer
    /// in single-threaded mode.
    asiolink::IOServicePtr getThreadIOService() const {
        return (thread_io_service_);
    }

    /// @brief Fetch a pointer to the listener.
    const TcpListenerPtr getTcpListener() {
        return(tcp_listener_);
    }

    /// @brief Sets the idle time per connection.
    ///
    /// @param milliseconds Amount of time in milliseconds
    void setIdleTimeout(long milliseconds) {
        idle_timeout_ = TcpListener::IdleTimeout(milliseconds);
    }

    long getIdleTimeout() {
        return (idle_timeout_.value_);
    }

private:
    /// @brief Factory for creating TcpListener instances.
    TcpListenerFactory listener_factory_;

    /// @brief IP address on which to listen.
    isc::asiolink::IOAddress address_;

    /// @brief Port on which to listen.
    uint16_t port_;

    /// @brief IOService instance that drives our IO.
    isc::asiolink::IOServicePtr thread_io_service_;

    /// @brief The TcpListener instance
    TcpListenerPtr tcp_listener_;

    /// @brief The number of threads that will call IOService_context::run().
    std::size_t thread_pool_size_;

    /// @brief The pool of threads that do IO work.
    asiolink::IoServiceThreadPoolPtr thread_pool_;

    /// @brief The TLS context.
    asiolink::TlsContextPtr tls_context_;

    /// @brief Callback the listener may use to reject connections during acceptance.
    TcpConnectionFilterCallback connection_filter_;

    /// @brief Time in milliseconds that a connection can remain idle before
    /// it is closed.
    TcpListener::IdleTimeout idle_timeout_;
};

/// @brief Defines a shared pointer to MtTcpListenerMgr.
typedef boost::shared_ptr<MtTcpListenerMgr> MtTcpListenerMgrPtr;

} // namespace isc::tcp
} // namespace isc

#endif // MT_TCP_LISTENER_MGR_H
