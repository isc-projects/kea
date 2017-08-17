// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_ACCEPTOR_H
#define TCP_ACCEPTOR_H

#ifndef BOOST_ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/io_acceptor.h>
#include <asiolink/io_service.h>
#include <asiolink/io_socket.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/tcp_socket.h>
#include <boost/shared_ptr.hpp>
#include <netinet/in.h>

namespace isc {
namespace asiolink {

/// @brief Provides a service for accepting new TCP connections.
///
/// Internally it uses @c boost::asio::ip::tcp::acceptor class to implement
/// the acceptor service.
///
/// @tparam C Acceptor callback type.
template<typename C>
class TCPAcceptor : public IOAcceptor<boost::asio::ip::tcp, C> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service.
    explicit TCPAcceptor(IOService& io_service)
        : IOAcceptor<boost::asio::ip::tcp, C>(io_service) {
    }

    /// @brief Returns protocol of the socket.
    ///
    /// @return IPPROTO_TCP.
    virtual int getProtocol() const final {
        return (IPPROTO_TCP);
    }

    /// @brief Asynchronously accept new connection.
    ///
    /// This method accepts new connection into the specified socket. When the
    /// new connection arrives or an error occurs the specified callback function
    /// is invoked.
    ///
    /// @param socket Socket into which connection should be accepted.
    /// @param callback Callback function to be invoked when the new connection
    /// arrives.
    /// @tparam SocketCallback Type of the callback for the @ref TCPSocket.
    template<typename SocketCallback>
    void asyncAccept(const TCPSocket<SocketCallback>& socket, C& callback) {
        IOAcceptor<boost::asio::ip::tcp, C>::asyncAcceptInternal(socket, callback);
    }
};


} // namespace asiolink
} // namespace isc

#endif
