// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/unix_domain_socket.h>
#include <boost/enable_shared_from_this.hpp>
#include <functional>
#include <iostream>

using namespace boost::asio::local;
namespace ph = std::placeholders;

namespace isc {
namespace asiolink {

/// @brief Implementation of the unix domain socket.
class UnixDomainSocketImpl : public boost::enable_shared_from_this<UnixDomainSocketImpl> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the socket class.
    UnixDomainSocketImpl(IOService& io_service)
        : socket_(io_service.get_io_service()) {
    }

    /// @brief Destructor.
    ///
    /// Closes the socket.
    ~UnixDomainSocketImpl() {
        close();
    }

    /// @brief Asynchronously connects to an endpoint.
    ///
    /// This method schedules asynchronous connect and installs the
    /// @ref UnixDomainSocketImpl::connectHandler as a callback.
    ///
    /// @param endpoint Reference to an endpoint to connect to.
    /// @param handler User supplied handler to be invoked when the connection
    /// is established or when error is signalled.
    void asyncConnect(const stream_protocol::endpoint& endpoint,
                      const UnixDomainSocket::ConnectHandler& handler);

    /// @brief Local handler invoked as a result of asynchronous connection.
    ///
    /// This is a wrapper around the user supplied callback. It ignores
    /// EINPROGRESS errors which are observed on some operating systems as
    /// a result of trying to connect asynchronously. This error code doesn't
    /// necessarily indicate a problem and the subsequent attempts to read
    /// and write to the socket will succeed. Therefore, the handler simply
    /// overrides this error code with success status. The user supplied
    /// handler doesn't need to deal with the EINPROGRESS error codes.
    ///
    /// @param remote_handler User supplied callback.
    /// @param ec Error code returned as a result of connection.
    void connectHandler(const UnixDomainSocket::ConnectHandler& remote_handler,
                        const boost::system::error_code& ec);

    /// @brief Asynchronously sends data over the socket.
    ///
    /// This method schedules an asynchronous send and installs the
    /// @ref UnixDomainSocketImpl::sendHandler as a callback.
    ///
    /// @param data Pointer to data to be sent.
    /// @param length Number of bytes to be sent.
    /// @param handler Callback to be invoked when data have been sent or an
    /// sending error is signalled.
    void asyncSend(const void* data, const size_t length,
                   const UnixDomainSocket::Handler& handler);

    /// @brief Asynchronously sends the data over the socket.
    ///
    /// This method is called by the @ref asyncSend and the @ref sendHandler
    /// if the asynchronous send has to be repeated as a result of receiving
    /// EAGAIN or EWOULDBLOCK.
    ///
    /// @param buffer Buffers holding the data to be sent.
    /// @param handler User supplied callback to be invoked when data have
    /// been sent or sending error is signalled.
    void doSend(const boost::asio::const_buffers_1& buffer,
                const UnixDomainSocket::Handler& handler);


    /// @brief Local handler invoked as a result of asynchronous send.
    ///
    /// This handler is invoked as a result of asynchronous send. It is a
    /// wrapper callback around the user supplied callback. It handles
    /// EWOULDBLOCK and EAGAIN errors by retrying an asynchronous send.
    /// These errors are often returned on some operating systems, even
    /// though one would expect that asynchronous operation would not
    /// return such errors. Because these errors are handled by the
    /// wrapper callback, the user supplied callback never receives
    /// these errors.
    ///
    /// @param remote_handler User supplied callback.
    /// @param buffer Buffers holding the data to be sent.
    /// @param ec Error code returned as a result of sending the data.
    /// @param length Length of the data sent.
    void sendHandler(const UnixDomainSocket::Handler& remote_handler,
                     const boost::asio::const_buffers_1& buffer,
                     const boost::system::error_code& ec,
                     size_t length);

    /// @brief Asynchronously receive data over the socket.
    ///
    /// This method schedules asynchronous receive and installs the
    /// @ref UnixDomainSocketImpl::receiveHandler is a callback.
    ///
    /// @param data Pointer to a buffer into which the data should be read.
    /// @param length Length of the buffer.
    /// @param handler User supplied callback invoked when data have been
    /// received or an error is signalled.
    void asyncReceive(void* data, const size_t length,
                      const UnixDomainSocket::Handler& handler);

    /// @brief Asynchronously receives the data over the socket.
    ///
    /// This method is called @ref asyncReceive and @ref receiveHandler when
    /// EWOULDBLOCK or EAGAIN is returned.
    ///
    /// @param buffer A buffer into which the data should be received.
    /// @param handler User supplied callback invoked when data have been
    /// received on an error is signalled.
    void doReceive(const boost::asio::mutable_buffers_1& buffer,
                   const UnixDomainSocket::Handler& handler);

    /// @brief Local handler invoked as a result of asynchronous receive.
    ///
    /// This handler is invoked as a result of asynchronous receive. It is a
    /// wrapper callback around the user supplied callback. It handles
    /// EWOULDBLOCK and EAGAIN by retrying to asynchronously receive the
    /// data. These errors are often returned on some operating systems, even
    /// though one would expect that asynchronous operation would not
    /// return such errors. Because these errors are handled by the
    /// wrapper callback, the user supplied callback never receives
    /// these errors.
    ///
    /// @param remote_handler User supplied callback.
    /// @param buffer Buffer into which the data are received.
    /// @param ec Error code returned as a result of asynchronous receive.
    /// @param length Size of the received data.
    void receiveHandler(const UnixDomainSocket::Handler& remote_handler,
                        const boost::asio::mutable_buffers_1& buffer,
                        const boost::system::error_code& ec,
                        size_t length);

    /// @brief Disables read and write operations on the socket.
    void shutdown();

    /// @brief Cancels asynchronous operations on the socket.
    void cancel();

    /// @brief Closes the socket.
    void close();

    /// @brief Instance of the boost asio unix domain socket.
    stream_protocol::socket socket_;
};

void
UnixDomainSocketImpl::asyncConnect(const stream_protocol::endpoint& endpoint,
                                   const UnixDomainSocket::ConnectHandler& handler) {
    auto local_handler = std::bind(&UnixDomainSocketImpl::connectHandler,
                                   shared_from_this(),
                                   handler, ph::_1);
    socket_.async_connect(endpoint, local_handler);
}

void
UnixDomainSocketImpl::connectHandler(const UnixDomainSocket::ConnectHandler& remote_handler,
                                     const boost::system::error_code& ec) {
    // It was observed on Debian and Fedora that asynchronous connect may result
    // in EINPROGRESS error. This doesn't really indicate a problem with a
    // connection. If we continue transmitting data over the socket it will
    // succeed. So we suppress this error and return 'success' to the user's
    // handler.
    if (ec.value() == boost::asio::error::in_progress) {
        remote_handler(boost::system::error_code());
    } else {
        remote_handler(ec);
    }
}

void
UnixDomainSocketImpl::asyncSend(const void* data, const size_t length,
                                const UnixDomainSocket::Handler& handler) {
    doSend(boost::asio::buffer(data, length), handler);
}

void
UnixDomainSocketImpl::doSend(const boost::asio::const_buffers_1& buffer,
                             const UnixDomainSocket::Handler& handler) {
    auto local_handler = std::bind(&UnixDomainSocketImpl::sendHandler,
                                   shared_from_this(),
                                   handler, buffer, ph::_1, ph::_2);
    socket_.async_send(buffer, local_handler);
}

void
UnixDomainSocketImpl::sendHandler(const UnixDomainSocket::Handler& remote_handler,
                                  const boost::asio::const_buffers_1& buffer,
                                  const boost::system::error_code& ec,
                                  size_t length) {
    // The asynchronous send may return EWOULDBLOCK or EAGAIN on some
    // operating systems. In this case, we simply retry hoping that it
    // will succeed next time. The user's callback never sees these
    // errors.
    if ((ec.value() == boost::asio::error::would_block) ||
        (ec.value() == boost::asio::error::try_again)) {
        doSend(buffer, remote_handler);

    } else {
        remote_handler(ec, length);
    }
}

void
UnixDomainSocketImpl::asyncReceive(void* data, const size_t length,
                                   const UnixDomainSocket::Handler& handler) {
    doReceive(boost::asio::buffer(data, length), handler);
}

void
UnixDomainSocketImpl::doReceive(const boost::asio::mutable_buffers_1& buffer,
                                const UnixDomainSocket::Handler& handler) {
    auto local_handler = std::bind(&UnixDomainSocketImpl::receiveHandler,
                                   shared_from_this(),
                                   handler, buffer, ph::_1, ph::_2);
    socket_.async_receive(buffer, 0, local_handler);
}

void
UnixDomainSocketImpl::receiveHandler(const UnixDomainSocket::Handler& remote_handler,
                                     const boost::asio::mutable_buffers_1& buffer,
                                     const boost::system::error_code& ec,
                                     size_t length) {
    // The asynchronous receive may return EWOULDBLOCK or EAGAIN on some
    // operating systems. In this case, we simply retry hoping that it
    // will succeed next time. The user's callback never sees these
    // errors.
    if ((ec.value() == boost::asio::error::would_block) ||
        (ec.value() == boost::asio::error::try_again)) {
        doReceive(buffer, remote_handler);

    } else {
        remote_handler(ec, length);
    }
}

void
UnixDomainSocketImpl::shutdown() {
    boost::system::error_code ec;
    static_cast<void>(socket_.shutdown(stream_protocol::socket::shutdown_both, ec));
    if (ec) {
        isc_throw(UnixDomainSocketError, ec.message());
    }
}

void
UnixDomainSocketImpl::cancel() {
    boost::system::error_code ec;
    static_cast<void>(socket_.cancel(ec));
    if (ec) {
        isc_throw(UnixDomainSocketError, ec.message());
    }
}

void
UnixDomainSocketImpl::close() {
    boost::system::error_code ec;
    static_cast<void>(socket_.close(ec));
    if (ec) {
        isc_throw(UnixDomainSocketError, ec.message());
    }
}

UnixDomainSocket::UnixDomainSocket(IOService& io_service)
    : impl_(new UnixDomainSocketImpl(io_service)) {
}

int
UnixDomainSocket::getNative() const {
#if BOOST_VERSION < 106600
    return (impl_->socket_.native());
#else
    return (impl_->socket_.native_handle());
#endif
}

int
UnixDomainSocket::getProtocol() const {
    return (0);
}

void
UnixDomainSocket::connect(const std::string& path) {
    boost::system::error_code ec;
    impl_->socket_.connect(stream_protocol::endpoint(path.c_str()), ec);
    if (ec) {
        isc_throw(UnixDomainSocketError, ec.message());
    }
}

void
UnixDomainSocket::asyncConnect(const std::string& path, const ConnectHandler& handler) {
    impl_->asyncConnect(stream_protocol::endpoint(path.c_str()), handler);
}

size_t
UnixDomainSocket::write(const void* data, size_t length) {
    boost::system::error_code ec;
    size_t res = boost::asio::write(impl_->socket_,
                                    boost::asio::buffer(data, length),
                                    boost::asio::transfer_all(),
                                    ec);
    if (ec) {
        isc_throw(UnixDomainSocketError, ec.message());
    }
    return (res);
}

void
UnixDomainSocket::asyncSend(const void* data, const size_t length,
                            const Handler& handler) {
    impl_->asyncSend(data, length, handler);
}

size_t
UnixDomainSocket::receive(void* data, size_t length) {
    boost::system::error_code ec;
    size_t res = impl_->socket_.receive(boost::asio::buffer(data, length), 0, ec);
    if (ec) {
        isc_throw(UnixDomainSocketError, ec.message());
    }
    return (res);
}

void
UnixDomainSocket::asyncReceive(void* data, const size_t length,
                               const Handler& handler) {
    impl_->asyncReceive(data, length, handler);
}

void
UnixDomainSocket::shutdown() {
    impl_->shutdown();
}

void
UnixDomainSocket::cancel() {
    impl_->cancel();
}

void
UnixDomainSocket::close() {
    impl_->close();
}

boost::asio::local::stream_protocol::socket&
UnixDomainSocket::getASIOSocket() const {
    return (impl_->socket_);
}

} // end of namespace asiolink
} // end of namespace isc
