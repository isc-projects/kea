// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <asiolink/testutils/test_server_unix_socket.h>

namespace isc {
namespace asiolink {
namespace test {

TestServerUnixSocket::TestServerUnixSocket(IOService& io_service,
                                           const std::string& socket_file_path,
                                           const long test_timeout)
    : io_service_(io_service),
      server_endpoint_(socket_file_path),
      server_acceptor_(io_service_.get_io_service()),
      server_socket_(io_service_.get_io_service()),
      test_timer_(io_service_) {
    test_timer_.setup(boost::bind(&TestServerUnixSocket::timeoutHandler, this),
                      test_timeout, IntervalTimer::ONE_SHOT);
}

void
TestServerUnixSocket::bindServerSocket() {
    server_acceptor_.open();
    server_acceptor_.bind(server_endpoint_);
    server_acceptor_.listen();
    server_acceptor_.async_accept(server_socket_,
                                  boost::bind(&TestServerUnixSocket::
                                              acceptHandler, this, _1));
}

void
TestServerUnixSocket::acceptHandler(const boost::system::error_code& ec) {
    if (ec) {
        ADD_FAILURE() << ec.message();
    }
    server_socket_.async_read_some(boost::asio::buffer(&raw_buf_[0],
                                                       raw_buf_.size()),
                                   boost::bind(&TestServerUnixSocket::
                                               readHandler, this, _1, _2));
}

void
TestServerUnixSocket::readHandler(const boost::system::error_code& ec,
                                  size_t bytes_transferred) {
    std::string received(&raw_buf_[0], bytes_transferred);
    std::string response("received " + received);
    boost::asio::write(server_socket_, boost::asio::buffer(response.c_str(),
                                                           response.size()));
    io_service_.stop();
}

void
TestServerUnixSocket::timeoutHandler() {
    ADD_FAILURE() << "Timeout occurred while running the test!";
    io_service_.stop();
}

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc
