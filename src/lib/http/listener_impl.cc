// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <http/connection_pool.h>
#include <http/listener.h>
#include <http/listener_impl.h>

using namespace isc::asiolink;
namespace ph = std::placeholders;

namespace isc {
namespace http {

HttpListenerImpl::HttpListenerImpl(IOService& io_service,
                                   const asiolink::IOAddress& server_address,
                                   const unsigned short server_port,
                                   const TlsContextPtr& tls_context,
                                   const HttpResponseCreatorFactoryPtr& creator_factory,
                                   const long request_timeout,
                                   const long idle_timeout)
    : io_service_(io_service), tls_context_(tls_context), acceptor_(),
      endpoint_(), connections_(),
      creator_factory_(creator_factory),
      request_timeout_(request_timeout), idle_timeout_(idle_timeout) {
    // Create the TCP or TLS acceptor.
    if (!tls_context) {
        acceptor_.reset(new HttpAcceptor(io_service));
    } else {
        acceptor_.reset(new HttpsAcceptor(io_service));
    }

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
        acceptor_->open(*endpoint_);
        acceptor_->setOption(HttpAcceptor::ReuseAddress(true));
        acceptor_->bind(*endpoint_);
        acceptor_->listen();

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
    acceptor_->close();
}

void
HttpListenerImpl::accept() {
    // In some cases we may need HttpResponseCreator instance per connection.
    // But, the factory may also return the same instance each time. It
    // depends on the use case.
    HttpResponseCreatorPtr response_creator = creator_factory_->create();
    HttpAcceptorCallback acceptor_callback =
        std::bind(&HttpListenerImpl::acceptHandler, this, ph::_1);
    HttpConnectionPtr conn = createConnection(response_creator,
                                              acceptor_callback);
    // Add this new connection to the pool.
    connections_.start(conn);
}

void
HttpListenerImpl::acceptHandler(const boost::system::error_code&) {
    // The new connection has arrived. Set the acceptor to continue
    // accepting new connections.
    accept();
}

HttpConnectionPtr
HttpListenerImpl::createConnection(const HttpResponseCreatorPtr& response_creator,
                                   const HttpAcceptorCallback& callback) {
    HttpConnectionPtr
        conn(new HttpConnection(io_service_, acceptor_, tls_context_,
                                connections_, response_creator, callback,
                                request_timeout_, idle_timeout_));
    return (conn);
}

} // end of namespace isc::http
} // end of namespace isc
