// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_CONNECTION_ACCEPTOR_H
#define TCP_CONNECTION_ACCEPTOR_H

#include <asiolink/tcp_acceptor.h>
#include <asiolink/tls_acceptor.h>

#include <boost/shared_ptr.hpp>
#include <boost/system/system_error.hpp>
#include <functional>

namespace isc {
namespace tcp {

/// @brief Type of the callback for the TCP acceptor used in this library.
typedef std::function<void(const boost::system::error_code&)> TcpConnectionAcceptorCallback;

/// @brief Type of the TCP acceptor used in this library.
typedef asiolink::TCPAcceptor<TcpConnectionAcceptorCallback> TcpConnectionAcceptor;

/// @brief Type of shared pointer to TCP acceptors.
typedef boost::shared_ptr<TcpConnectionAcceptor> TcpConnectionAcceptorPtr;

/// @brief Type of the TLS acceptor used in this library.
typedef asiolink::TLSAcceptor<TcpConnectionAcceptorCallback> TlsConnectionAcceptor;

/// @brief Type of shared pointer to TLS acceptors.
typedef boost::shared_ptr<TlsConnectionAcceptor> TlsConnectionAcceptorPtr;

} // end of namespace isc::tcp
} // end of namespace isc

#endif
