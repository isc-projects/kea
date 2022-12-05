// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <tcp/tcp_listener.h>

using namespace isc::asiolink;
namespace ph = std::placeholders;

namespace isc {
namespace tcp {

TcpListener::TcpListener(IOService& io_service,
                         const IOAddress& server_address,
                         const unsigned short server_port,
                         const TlsContextPtr& tls_context,
                         const IdleTimeout& idle_timeout,
                         const TcpConnectionFilterCallback& connection_filter)
    : io_service_(io_service), tls_context_(tls_context), acceptor_(),
      endpoint_(), connections_(), idle_timeout_(idle_timeout.value_),
      connection_filter_(connection_filter) {
    // Create the TCP or TLS acceptor.
    if (!tls_context) {
        acceptor_.reset(new TcpConnectionAcceptor(io_service));
    } else {
        acceptor_.reset(new TlsConnectionAcceptor(io_service));
    }

    // Try creating an endpoint. This may cause exceptions.
    try {
        endpoint_.reset(new TCPEndpoint(server_address, server_port));
    } catch (...) {
        isc_throw(TcpListenerError, "unable to create TCP endpoint for "
                  << server_address << ":" << server_port);
    }

    // Idle connection timeout is signed and must be greater than 0.
    if (idle_timeout_ <= 0) {
        isc_throw(TcpListenerError, "Invalid desired TCP idle connection"
                  " timeout " << idle_timeout_);
    }
}

TcpListener::~TcpListener() {
    stop();
}

const TCPEndpoint&
TcpListener::getEndpoint() const {
    return (*endpoint_);
}

void
TcpListener::start() {
    try {
        acceptor_->open(*endpoint_);
        acceptor_->setOption(TcpConnectionAcceptor::ReuseAddress(true));
        acceptor_->bind(*endpoint_);
        acceptor_->listen();

    } catch (const boost::system::system_error& ex) {
        stop();
        isc_throw(TcpListenerError, "unable to setup TCP acceptor for "
                  "listening for incoming TCP clients: " << ex.what());
    }

    accept();
}

void
TcpListener::stop() {
    connections_.stopAll();
    acceptor_->close();
}

void
TcpListener::accept() {
    TcpConnectionAcceptorCallback acceptor_callback =
        std::bind(&TcpListener::acceptHandler, this, ph::_1);

    TcpConnectionPtr conn = createConnection(acceptor_callback, connection_filter_);

    // Add this new connection to the pool.
    connections_.start(conn);
}

void
TcpListener::acceptHandler(const boost::system::error_code&) {
    // The new connection has arrived. Set the acceptor to continue
    // accepting new connections.
    accept();
}

TcpConnectionPtr
TcpListener::createConnection(const TcpConnectionAcceptorCallback&,
                              const TcpConnectionFilterCallback&) {
    isc_throw(NotImplemented, "TcpListener::createConnection:");
}

IOAddress
TcpListener::getLocalAddress() const {
    return (getEndpoint().getAddress());
}

uint16_t
TcpListener::getLocalPort() const {
    return (getEndpoint().getPort());
}

} // end of namespace isc::tcp
} // end of namespace isc
