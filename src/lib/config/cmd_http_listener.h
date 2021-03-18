// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CMD_HTTP_LISTENER_H
#define CMD_HTTP_LISTENER_H

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <http/listener.h>
#include <thread>
#include <vector>

namespace isc {
namespace config {

class CmdHttpListener {
public:
    /// @brief Constructor
    CmdHttpListener(const asiolink::IOAddress& address, const uint16_t port,
                    const uint16_t thread_pool_size = 1);

    /// @brief Destructor
    virtual ~CmdHttpListener();

    /// @brief Initiates the listener's worker thread.
    void start();

    /// @brief Stops the listener's worker thread.
    void stop();

    /// @brief Checks if we are listening to the HTTP requests.
    ///
    /// @return true if we are listening.
    bool isListening() const;

    /// @brief Fetches the IP address on which to listen.
    ///
    /// @return IOAddress containing the address on which to listen.
    isc::asiolink::IOAddress& getAddress() {
        return (address_);
    }

    /// @brief Fetches the port number on which to listen.
    ///
    /// @return uint16_t containing the port number on which to listen.
    uint16_t getPort() {
        return (port_);
    }

    /// @brief Fetches the maximum size of the thread pool.
    ///
    /// @return uint16_t containing the maximum size of the thread pool.
    uint16_t getThreadPoolSize() {
        return (thread_pool_size_);
    }

    /// @brief Fetches the number of threads in the pool.
    ///
    /// @return uint16_t containing the number of running threads.
    uint16_t getThreadCount() {
        return (threads_.size());
    }

private:
    /// @brief IP address on which to listen.
    isc::asiolink::IOAddress address_;

    /// @brief Port on which to listen.
    uint16_t port_;

    /// @brief IOService instance that drives our IO.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief The HttpListener instance
    http::HttpListenerPtr http_listener_;

    /// @brief The number of threads that will call IOService_context::run().
    std::size_t thread_pool_size_;

    /// @brief The pool of threads that do IO work.
    std::vector<boost::shared_ptr<std::thread> > threads_;
};

/// @brief Defines a shared pointer to CmdHttpListener.
typedef boost::shared_ptr<CmdHttpListener> CmdHttpListenerPtr;

} // namespace isc::config
} // namespace isc

#endif // CMD_HTTP_LISTENER_H
