// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
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
#include <asiolink/tcp_endpoint.h>
#include <asiolink/tcp_socket.h>

namespace isc {
namespace asiolink {

template<typename C>
class TCPAcceptor {
public:

    TCPAcceptor(IOService& io_service)
        : acceptor_(io_service.get_io_service()) {
    }

    void open(const TCPEndpoint& endpoint) {
        acceptor_.open(endpoint.getASIOEndpoint().protocol());
        acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));

    }

//    void setOption(const SettableSocketOption& socket_option);

    void bind(const TCPEndpoint& endpoint) {
        acceptor_.bind(endpoint.getASIOEndpoint());
    }

    void listen() {
        acceptor_.listen();
    }

    template<typename SocketCallback>
    void asyncAccept(const TCPSocket<SocketCallback>& socket, C& callback) {
        acceptor_.async_accept(socket.getASIOSocket(), callback);
    }

    bool isOpen() const {
        return (acceptor_.is_open());
    }

private:

    boost::asio::ip::tcp::acceptor acceptor_;

};


} // namespace asiolink
} // namespace isc

#endif
