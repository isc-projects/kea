// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/tcp_endpoint.h>
#include <http/connection.h>
#include <http/connection_pool.h>
#include <http/http_acceptor.h>
#include <http/listener.h>
#include <boost/scoped_ptr.hpp>

using namespace isc::asiolink;

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
                     const HttpResponseCreatorFactoryPtr& creator_factory,
                     const long request_timeout,
                     const long idle_timeout);

    /// @brief Returns reference to the current listener endpoint.
    const TCPEndpoint& getEndpoint() const;

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

private:

    /// @brief Creates @ref HttpConnection instance and adds it to the
    /// pool of active connections.
    ///
    /// The next accepted connection will be handled by this instance.
    void accept();

    /// @brief Callback invoked when the new connection is accepted.
    ///
    /// It calls @ref HttpListener::accept to create new @ref HttpConnection
    /// instance.
    ///
    /// @param ec Error code passed to the handler. This is currently ignored.
    void acceptHandler(const boost::system::error_code& ec);

    /// @brief Reference to the IO service.
    asiolink::IOService& io_service_;

    /// @brief Acceptor instance.
    HttpAcceptor acceptor_;

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

HttpListenerImpl::HttpListenerImpl(IOService& io_service,
                                   const asiolink::IOAddress& server_address,
                                   const unsigned short server_port,
                                   const HttpResponseCreatorFactoryPtr& creator_factory,
                                   const long request_timeout,
                                   const long idle_timeout)
    : io_service_(io_service), acceptor_(io_service),
      endpoint_(), creator_factory_(creator_factory),
      request_timeout_(request_timeout), idle_timeout_(idle_timeout) {
    // Try creating an endpoint. This may cause exceptions.
    try {
        endpoint_.reset(new TCPEndpoint(server_address, server_port));

    } catch (...) {
        isc_throw(HttpListenerError, "unable to create TCP endpoint for "
                  << server_address << ":" << server_port);
    }

    // The factory must not be null.
    if (!creator_factory_) {
        isc_throw(HttpListenerError, "HttpResponseCreatorFactory must not"
                  " be null");
    }

    // Request timeout is signed and must be greater than 0.
    if (request_timeout_ <= 0) {
        isc_throw(HttpListenerError, "Invalid desired HTTP request timeout "
                  << request_timeout_);
    }

    // Idle persistent connection timeout is signed and must be greater than 0.
    if (idle_timeout_ <= 0) {
        isc_throw(HttpListenerError, "Invalid desired HTTP idle persistent connection"
                  " timeout " << idle_timeout_);
    }
}

const TCPEndpoint&
HttpListenerImpl::getEndpoint() const {
    return (*endpoint_);
}

void
HttpListenerImpl::start() {
    try {
        acceptor_.open(*endpoint_);
        acceptor_.setOption(HttpAcceptor::ReuseAddress(true));
        acceptor_.bind(*endpoint_);
        acceptor_.listen();

    } catch (const boost::system::system_error& ex) {
        stop();
        isc_throw(HttpListenerError, "unable to setup TCP acceptor for "
                  "listening to the incoming HTTP requests: " << ex.what());
    }

    accept();
}

void
HttpListenerImpl::stop() {
    connections_.stopAll();
    acceptor_.close();
}

void
HttpListenerImpl::accept() {
    // In some cases we may need HttpResponseCreator instance per connection.
    // But, the factory may also return the same instance each time. It
    // depends on the use case.
    HttpResponseCreatorPtr response_creator = creator_factory_->create();
    HttpAcceptorCallback acceptor_callback =
        boost::bind(&HttpListenerImpl::acceptHandler, this, _1);
    HttpConnectionPtr conn(new HttpConnection(io_service_, acceptor_,
                                              connections_,
                                              response_creator,
                                              acceptor_callback,
                                              request_timeout_,
                                              idle_timeout_));
    // Add this new connection to the pool.
    connections_.start(conn);
}

void
HttpListenerImpl::acceptHandler(const boost::system::error_code&) {
    // The new connection has arrived. Set the acceptor to continue
    // accepting new connections.
    accept();
}

HttpListener::HttpListener(IOService& io_service,
                           const asiolink::IOAddress& server_address,
                           const unsigned short server_port,
                           const HttpResponseCreatorFactoryPtr& creator_factory,
                           const HttpListener::RequestTimeout& request_timeout,
                           const HttpListener::IdleTimeout& idle_timeout)
    : impl_(new HttpListenerImpl(io_service, server_address, server_port,
                                 creator_factory, request_timeout.value_,
                                 idle_timeout.value_)) {
}

HttpListener::~HttpListener() {
    stop();
}

IOAddress
HttpListener::getLocalAddress() const {
    return (impl_->getEndpoint().getAddress());
}

uint16_t
HttpListener::getLocalPort() const {
    return (impl_->getEndpoint().getPort());
}

void
HttpListener::start() {
    impl_->start();
}

void
HttpListener::stop() {
    impl_->stop();
}


} // end of namespace isc::http
} // end of namespace isc
