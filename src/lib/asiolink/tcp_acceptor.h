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
class TCPAcceptor : public IOSocket {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service.
    explicit TCPAcceptor(IOService& io_service)
        : IOSocket(),
          acceptor_(new boost::asio::ip::tcp::acceptor(io_service.get_io_service())) {
    }

    /// @brief Destructor.
    virtual ~TCPAcceptor() { }

    /// @brief Returns file descriptor of the underlying socket.
    virtual int getNative() const final {
        return (acceptor_->native());
    }

    /// @brief Returns protocol of the socket.
    ///
    /// @return IPPROTO_TCP.
    virtual int getProtocol() const final {
        return (IPPROTO_TCP);
    }

    /// @brief Opens acceptor socket given the endpoint.
    ///
    /// @param endpoint Reference to the endpoint object which specifies the
    /// address and port on which the acceptor service will run.
    void open(const TCPEndpoint& endpoint) {
        acceptor_->open(endpoint.getASIOEndpoint().protocol());
    }

    /// @brief Sets socket option.
    ///
    /// Typically, this method is used to set SO_REUSEADDR option on the socket:
    /// @code
    /// IOService io_service;
    /// TCPAcceptor<Callback> acceptor(io_service);
    /// acceptor.setOption(TCPAcceptor::ReuseAddress(true))
    /// @endcode
    ///
    /// @param socket_option Reference to the object encapsulating an option to
    /// be set for the socket.
    /// @tparam SettableSocketOption Type of the object encapsulating socket option
    /// being set.
    template<typename SettableSocketOption>
    void setOption(const SettableSocketOption& socket_option) {
        acceptor_->set_option(socket_option);
    }

    /// @brief Binds socket to an endpoint.
    ///
    /// @param endpoint Reference to an endpoint to which the socket is to
    /// be bound.
    void bind(const TCPEndpoint& endpoint) {
        acceptor_->bind(endpoint.getASIOEndpoint());
    }

    /// @brief Starts listening for the new connections.
    void listen() {
        acceptor_->listen();
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
        acceptor_->async_accept(socket.getASIOSocket(), callback);
    }

    /// @brief Checks if the acceptor is open.
    ///
    /// @return true if acceptor is open.
    bool isOpen() const {
        return (acceptor_->is_open());
    }

    /// @brief Closes the acceptor.
    void close() const {
        acceptor_->close();
    }

private:

    /// @brief Underlying ASIO acceptor implementation.
    boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;

};


} // namespace asiolink
} // namespace isc

#endif
