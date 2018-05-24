// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_ACCEPTOR_H
#define IO_ACCEPTOR_H

#ifndef BOOST_ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/io_service.h>
#include <asiolink/io_socket.h>

namespace isc {
namespace asiolink {

/// @brief Base class for acceptor services in Kea.
///
/// This is a wrapper class for ASIO acceptor service. Classes implementing
/// services for specific protocol types should derive from this class.
///
/// Acceptor is an IO object which accepts incoming connections into a socket
/// object. This socket is then used for data transmission from the client
/// to server and back. The acceptor is continued to be used to accept new
/// connections while the accepted connection is active.
///
/// @tparam ProtocolType ASIO protocol type, e.g. stream_protocol
/// @tparam CallbackType Callback function type which should have the following
/// signature: @c void(const boost::system::error_code&).
template<typename ProtocolType, typename CallbackType>
class IOAcceptor : public IOSocket {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service.
    explicit IOAcceptor(IOService& io_service)
        : IOSocket(),
          acceptor_(new typename ProtocolType::acceptor(io_service.get_io_service())) {
    }

    /// @brief Destructor.
    virtual ~IOAcceptor() { }

    /// @brief Returns file descriptor of the underlying socket.
    virtual int getNative() const {
#if BOOST_VERSION < 106600
        return (acceptor_->native());
#else
        return (acceptor_->native_handle());
#endif
    }

    /// @brief Opens acceptor socket given the endpoint.
    ///
    /// @param endpoint Reference to the endpoint object defining local
    /// acceptor endpoint.
    ///
    /// @tparam EndpointType Endpoint type.
    template<typename EndpointType>
    void open(const EndpointType& endpoint) {
        acceptor_->open(endpoint.getASIOEndpoint().protocol());
    }

    /// @brief Binds socket to an endpoint.
    ///
    /// @param endpoint Reference to the endpoint object defining local
    /// acceptor endpoint.
    ///
    /// @tparam EndpointType Endpoint type.
    template<typename EndpointType>
    void bind(const EndpointType& endpoint) {
        acceptor_->bind(endpoint.getASIOEndpoint());
    }

    /// @brief Sets socket option.
    ///
    /// @param socket_option Reference to the object encapsulating an option to
    /// be set for the socket.
    /// @tparam SettableSocketOption Type of the object encapsulating socket option
    /// being set.
    template<typename SettableSocketOption>
    void setOption(const SettableSocketOption& socket_option) {
        acceptor_->set_option(socket_option);
    }

    /// @brief Starts listening new connections.
    void listen() {
        acceptor_->listen();
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

protected:

    /// @brief Asynchronously accept new connection.
    ///
    /// This method accepts new connection into the specified socket. When the
    /// new connection arrives or an error occurs the specified callback
    /// function is invoked.
    ///
    /// @param socket Socket into which connection should be accepted.
    /// @param callback Callback function to be invoked when the new connection
    /// arrives.
    /// @tparam SocketType Socket type, e.g. @ref UnixDomainSocket. It must
    /// implement @c getASIOSocket method.
    template<typename SocketType>
    void asyncAcceptInternal(const SocketType& socket,
                             const CallbackType& callback) {
        acceptor_->async_accept(socket.getASIOSocket(), callback);
    }


    /// @brief Underlying ASIO acceptor implementation.
    boost::shared_ptr<typename ProtocolType::acceptor> acceptor_;

};


} // end of namespace asiolink
} // end of isc

#endif // IO_ACCEPTOR_H
