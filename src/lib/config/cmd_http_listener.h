// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CMD_HTTP_LISTENER_H
#define CMD_HTTP_LISTENER_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <http/listener.h>
#include <http/http_thread_pool.h>
#include <thread>
#include <vector>

namespace isc {
namespace config {

/// @brief A multi-threaded HTTP listener that can process API commands
/// requests.
///
/// This class will listen for Command API client requests on a given
/// IP address and port.  It uses its own IOService instance to drive
/// a thread-pool which can service multiple connections concurrently.
/// The number of concurrent connections is currently limited to the
/// configured thread pool size.
///
/// @note This class is NOT compatible with Kea core single-threading.
/// It is incumbent upon the owner to ensure the Kea core multi-threading
/// is (or will be) enabled when creating instances of this class.
class CmdHttpListener {
public:
    /// @brief Constructor
    CmdHttpListener(const asiolink::IOAddress& address, const uint16_t port,
                    const uint16_t thread_pool_size = 1,
                    asiolink::TlsContextPtr context = asiolink::TlsContextPtr());

    /// @brief Destructor
    virtual ~CmdHttpListener();

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

private:
    /// @brief IP address on which to listen.
    isc::asiolink::IOAddress address_;

    /// @brief Port on which to listen.
    uint16_t port_;

    /// @brief IOService instance that drives our IO.
    isc::asiolink::IOServicePtr thread_io_service_;

    /// @brief The HttpListener instance
    http::HttpListenerPtr http_listener_;

    /// @brief The number of threads that will call IOService_context::run().
    std::size_t thread_pool_size_;

    /// @brief The pool of threads that do IO work.
    http::HttpThreadPoolPtr thread_pool_;

    /// @brief The TLS context.
    asiolink::TlsContextPtr tls_context_;
};

/// @brief Defines a shared pointer to CmdHttpListener.
typedef boost::shared_ptr<CmdHttpListener> CmdHttpListenerPtr;

} // namespace isc::config
} // namespace isc

#endif // CMD_HTTP_LISTENER_H
