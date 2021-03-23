// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_LISTENER_IMPL_H
#define HTTP_LISTENER_IMPL_H

#include <asiolink/io_service.h>
#include <asiolink/io_address.h>
#include <asiolink/tcp_endpoint.h>
#include <http/connection.h>
#include <http/connection_pool.h>
#include <http/response_creator_factory.h>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace http {

/// @brief Implementation of the @ref HttpListener.
class HttpListenerImpl {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new server endpoint using the specified IP
    /// address and port. It also validates other specified parameters.
    ///
    /// This constructor does not start accepting new connections! To start
    /// accepting connections run @ref HttpListener::start.
    ///
    /// @param io_service IO service to be used by the listener.
    /// @param server_address Address on which the HTTP service should run.
    /// @param server_port Port number on which the HTTP service should run.
    /// @param tls_context TLS context.
    /// @param creator_factory Pointer to the caller-defined
    /// @ref HttpResponseCreatorFactory derivation which should be used to
    /// create @ref HttpResponseCreator instances.
    /// @param request_timeout Timeout after which the HTTP Request Timeout
    /// is generated.
    /// @param idle_timeout Timeout after which an idle persistent HTTP
    /// connection is closed by the server.
    ///
    /// @throw HttpListenerError when any of the specified parameters is
    /// invalid.
    HttpListenerImpl(asiolink::IOService& io_service,
                     const asiolink::IOAddress& server_address,
                     const unsigned short server_port,
                     const asiolink::TlsContextPtr& tls_context,
                     const HttpResponseCreatorFactoryPtr& creator_factory,
                     const long request_timeout,
                     const long idle_timeout);

    /// @brief Virtual destructor.
    virtual ~HttpListenerImpl() {
    }

    /// @brief Returns reference to the current listener endpoint.
    const asiolink::TCPEndpoint& getEndpoint() const;

    /// @brief Starts accepting new connections.
    ///
    /// This method starts accepting and handling new HTTP connections on
    /// the IP address and port number specified in the constructor.
    ///
    /// If the method is invoked successfully, it must not be invoked again
    /// until @ref HttpListener::stop is called.
    ///
    /// @throw HttpListenerError if an error occurred.
    void start();

    /// @brief Stops all active connections and shuts down the service.
    void stop();

protected:

    /// @brief Creates @ref HttpConnection instance and adds it to the
    /// pool of active connections.
    ///
    /// The next accepted connection will be handled by this instance.
    void accept();

    /// @brief Callback invoked when the new connection is accepted.
    ///
    /// It calls @c HttpListener::accept to create new @c HttpConnection
    /// instance.
    ///
    /// @param ec Error code passed to the handler. This is currently ignored.
    void acceptHandler(const boost::system::error_code& ec);

    /// @brief Creates an instance of the @c HttpConnection.
    ///
    /// This method is virtual so as it can be overridden when customized
    /// connections are to be used, e.g. in case of unit testing.
    ///
    /// @param response_creator Pointer to the response creator object used to
    /// create HTTP response from the HTTP request received.
    /// @param callback Callback invoked when new connection is accepted.
    ///
    /// @return Pointer to the created connection.
    virtual HttpConnectionPtr createConnection(const HttpResponseCreatorPtr& response_creator,
                                               const HttpAcceptorCallback& callback);

    /// @brief Reference to the IO service.
    asiolink::IOService& io_service_;

    /// @brief TLS context.
    asiolink::TlsContextPtr tls_context_;

    /// @brief Acceptor instance.
    HttpAcceptorPtr acceptor_;

    /// @brief Pointer to the endpoint representing IP address and port on
    /// which the service is running.
    boost::scoped_ptr<asiolink::TCPEndpoint> endpoint_;

    /// @brief Pool of active connections.
    HttpConnectionPool connections_;

    /// @brief Pointer to the @ref HttpResponseCreatorFactory.
    HttpResponseCreatorFactoryPtr creator_factory_;

    /// @brief Timeout for HTTP Request Timeout desired.
    long request_timeout_;

    /// @brief Timeout after which idle persistent connection is closed by
    /// the server.
    long idle_timeout_;
};


} // end of namespace isc::http
} // end of namespace isc

#endif // HTTP_LISTENER_IMPL_H
