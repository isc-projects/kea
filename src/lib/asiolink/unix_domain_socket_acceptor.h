// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNIX_DOMAIN_SOCKET_ACCEPTOR_H
#define UNIX_DOMAIN_SOCKET_ACCEPTOR_H

#ifndef BOOST_ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/io_acceptor.h>
#include <asiolink/unix_domain_socket.h>
#include <functional>

namespace isc {
namespace asiolink {

/// @brief Implements acceptor service for @ref UnixDomainSocket.
///
/// This class is used to accept new incoming connections over unix domain
/// sockets.
class UnixDomainSocketAcceptor : public IOAcceptor<boost::asio::local::stream_protocol,
                                 std::function<void(const boost::system::error_code&)> > {
public:

    /// @brief Callback type used in call to @ref UnixDomainSocketAcceptor::asyncAccept.
    typedef std::function<void(const boost::system::error_code&)> AcceptHandler;

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service.
    explicit UnixDomainSocketAcceptor(IOService& io_service)
        : IOAcceptor<boost::asio::local::stream_protocol,
                     std::function<void(const boost::system::error_code&)> >(io_service) {
    }

    /// @brief Returns the transport protocol of the socket.
    ///
    /// @return AF_LOCAL.
    virtual int getProtocol() const final {
        return (AF_LOCAL);
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
    /// @tparam SocketType
    void asyncAccept(const UnixDomainSocket& socket, const AcceptHandler& callback) {
        asyncAcceptInternal(socket, callback);
    }
};

} // end of namespace isc::asiolink
} // end of namespace isc

#endif // UNIX_DOMAIN_SOCKET_ACCEPTOR_H
