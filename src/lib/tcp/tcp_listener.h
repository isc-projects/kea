// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H

#include <asiolink/io_service.h>
#include <asiolink/io_address.h>
#include <asiolink/tcp_endpoint.h>
#include <tcp/tcp_connection_pool.h>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace tcp {

/// @brief A generic error raised by the @ref TcpListener class.
class TcpListenerError : public Exception {
public:
    TcpListenerError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Implements a class that listens for, accepts, and manages
/// TCP connections.
class TcpListener {
public:
    /// @brief Idle connection timeout.
    struct IdleTimeout {
        /// @brief Constructor.
        ///
        /// @param value Connection idle timeout value in milliseconds.
        explicit IdleTimeout(long value)
            : value_(value) {
        }
        long value_; ///< Connection idle timeout value specified.
    };

    /// @brief Constructor.
    ///
    /// This constructor creates new server endpoint using the specified IP
    /// address and port. It also validates other specified parameters.
    ///
    /// This constructor does not start accepting new connections! To start
    /// accepting connections run @ref TcpListener::start.
    ///
    /// @param io_service IO service to be used by the listener.
    /// @param server_address Address on which the TCP service should run.
    /// @param server_port Port number on which the TCP service should run.
    /// @param tls_context TLS context.
    /// @param idle_timeout Timeout after which an idle TCP connection is
    /// @param connection_filter Callback invoked during connection acceptance
    /// that can allow or deny connections based on the remote endpoint.
    ///
    /// @throw TcpListenerError when any of the specified parameters is
    /// invalid.
    TcpListener(asiolink::IOService& io_service,
                const asiolink::IOAddress& server_address,
                const unsigned short server_port,
                const asiolink::TlsContextPtr& tls_context,
                const IdleTimeout& idle_timeout,
                const TcpConnectionFilterCallback& connection_filter = 0);

    /// @brief Virtual destructor.
    virtual ~TcpListener();

    /// @brief Returns reference to the current listener endpoint.
    const asiolink::TCPEndpoint& getEndpoint() const;

    /// @brief Starts accepting new connections.
    ///
    /// This method starts accepting and handling new TCP connections on
    /// the IP address and port number specified in the constructor.
    ///
    /// If the method is invoked successfully, it must not be invoked again
    /// until @ref TcpListener::stop is called.
    ///
    /// @throw TcpListenerError if an error occurred.
    void start();

    /// @brief Stops all active connections and shuts down the service.
    void stop();

    /// @brief Returns local address on which server is listening.
    asiolink::IOAddress getLocalAddress() const;

    /// @brief Returns local port on which server is listening.
    uint16_t getLocalPort() const;

    /// @brief Returns the idle timeout (in milliseconds).
    long getIdleTimeout() const {
        return (idle_timeout_);
    }

    /// @brief Returns the number of connections using a given remote IP address.
    ///
    /// Used to limit the number of connections when accepting a new one.
    ///
    /// @param remote_ip The remote IP address.
    /// @param[out] total_connections Size of the connection pool.
    /// @return The number of connections using a given remote IP address.
    size_t usedByRemoteIp(const asiolink::IOAddress& remote_ip,
                          size_t& total_connections) {
        return (connections_.usedByRemoteIp(remote_ip, total_connections));
    }

protected:

    /// @brief Creates @ref TcpConnection instance and adds it to the
    /// pool of active connections.
    ///
    /// The next accepted connection will be handled by this instance.
    void accept();

    /// @brief Callback invoked when the new connection is accepted.
    ///
    /// It calls @c TcpListener::accept to create new @c TcpConnection
    /// instance.
    ///
    /// @param ec Error code passed to the handler. This is currently ignored.
    void acceptHandler(const boost::system::error_code& ec);

    /// @brief Creates an instance of the @c TcpConnection.
    ///
    /// This method is virtual so as it can be overridden when customized
    /// connections are to be used, e.g. in case of unit testing.
    ///
    /// @param acceptor_callback Callback invoked when new connection is accepted.
    /// @param connection_filter Callback invoked during acceptance which may
    /// allow of deny connections based on their remote address.
    /// @return Pointer to the created connection.
    virtual TcpConnectionPtr createConnection(
        const TcpConnectionAcceptorCallback& acceptor_callback,
        const TcpConnectionFilterCallback& connection_filter);

    /// @brief Reference to the IO service.
    asiolink::IOService& io_service_;

    /// @brief TLS context.
    asiolink::TlsContextPtr tls_context_;

    /// @brief Acceptor instance.
    TcpConnectionAcceptorPtr acceptor_;

    /// @brief Pointer to the endpoint representing IP address and port on
    /// which the service is running.
    boost::scoped_ptr<asiolink::TCPEndpoint> endpoint_;

    /// @brief Pool of active connections.
    TcpConnectionPool connections_;

    /// @brief Timeout after which idle connection is closed by
    /// the server.
    long idle_timeout_;

    /// @brief Callback invoked during acceptance which may
    /// reject connections.
    TcpConnectionFilterCallback connection_filter_;
};

/// @brief Pointer to a TcpListener.
typedef boost::shared_ptr<TcpListener> TcpListenerPtr;

} // end of namespace isc::asiolink
} // end of namespace isc

#endif // TCP_LISTENER_H
