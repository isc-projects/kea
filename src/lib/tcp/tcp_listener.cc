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
                         const long idle_timeout)
    : io_service_(io_service), tls_context_(tls_context), acceptor_(),
      endpoint_(), connections_(), idle_timeout_(idle_timeout) {

    // Create the TCP or TLS acceptor.
    // @todo TKM - hmmm....  need to understand this better..
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

    // Idle persistent connection timeout is signed and must be greater than 0.
    if (idle_timeout_ <= 0) {
        isc_throw(TcpListenerError, "Invalid desired TCP idle persistent connection"
                  " timeout " << idle_timeout_);
    }
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

    TcpConnectionPtr conn = createConnection(acceptor_callback);

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
TcpListener::createConnection(const TcpConnectionAcceptorCallback& /* callback */) {
#if 1
    isc_throw(NotImplemented, "TcpListener::createConnection:");
#else
    TcpConnectionPtr
/// @todo TKM - I think what we want is to define TcpConnectionFactory
/// instead of a response creator.  Let TcpListener accept a factory
/// for that, which is used here to create for BLQ an LeaseQueryConnection
    return (connection_factory_(io_service_, acceptor_, tls_context_,
                               connections_, callback, idle_timeout_));
#endif
}

} // end of namespace isc::tcp
} // end of namespace isc
