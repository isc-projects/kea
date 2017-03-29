// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <asiolink/unix_domain_socket.h>
#include <iostream>
using namespace boost::asio::local;

namespace isc {
namespace asiolink {

/// @brief Implementation of the unix domain socket.
class UnixDomainSocketImpl {
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

    /// @brief Closes the socket.
    void close();

    /// @brief Instance of the boost asio unix domain socket.
    stream_protocol::socket socket_;
};

void
UnixDomainSocketImpl::close() {
    static_cast<void>(socket_.close());
}

UnixDomainSocket::UnixDomainSocket(IOService& io_service)
    : impl_(new UnixDomainSocketImpl(io_service)) {
}

int
UnixDomainSocket::getNative() const {
    return (impl_->socket_.native());
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
UnixDomainSocket::close() {
    impl_->close();
}

}
}
