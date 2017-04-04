// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <boost/bind.hpp>

namespace isc {
namespace asiolink {
namespace test {

TestServerUnixSocket::TestServerUnixSocket(IOService& io_service,
                                           const std::string& socket_file_path,
                                           const long test_timeout,
                                           const std::string& custom_response)
    : io_service_(io_service),
      server_endpoint_(socket_file_path),
      server_acceptor_(io_service_.get_io_service()),
      server_sockets_(),
      test_timer_(io_service_),
      custom_response_(custom_response),
      stop_after_count_(1),
      read_count_(0) {
    test_timer_.setup(boost::bind(&TestServerUnixSocket::timeoutHandler, this),
                      test_timeout, IntervalTimer::ONE_SHOT);
}

TestServerUnixSocket::~TestServerUnixSocket() {
    for (auto sock = server_sockets_.begin(); sock != server_sockets_.end(); ++sock) {
        sock->close();
    }
}

void
TestServerUnixSocket::bindServerSocket(const unsigned int stop_after_count) {
    server_acceptor_.open();
    server_acceptor_.bind(server_endpoint_);
    server_acceptor_.listen();
    accept();

    stop_after_count_ = stop_after_count;
}

void
TestServerUnixSocket::acceptHandler(const boost::system::error_code&) {
    server_sockets_.back().async_read_some(boost::asio::buffer(&raw_buf_[0],
                                                               raw_buf_.size()),
        boost::bind(&TestServerUnixSocket::readHandler, this, _1, _2));
}

void
TestServerUnixSocket::accept() {
    server_sockets_.push_back(boost::asio::local::stream_protocol::
                              socket(io_service_.get_io_service()));
    server_acceptor_.async_accept(server_sockets_.back(),
                                  boost::bind(&TestServerUnixSocket::
                                              acceptHandler, this, _1));
}


void
TestServerUnixSocket::readHandler(const boost::system::error_code&,
                                  size_t bytes_transferred) {
    if (!custom_response_.empty()) {
        boost::asio::write(server_sockets_.back(),
                           boost::asio::buffer(custom_response_.c_str(),
                                               custom_response_.size()));

    } else {
        std::string received(&raw_buf_[0], bytes_transferred);
        std::string response("received " + received);
        boost::asio::write(server_sockets_.back(),
                           boost::asio::buffer(response.c_str(), response.size()));
    }

    // Stop IO service if we have reached the maximum number of read messages.
    if (++read_count_ >= stop_after_count_) {
        io_service_.stop();

    } else {
        // Previous connection is done, so let's accept another connection.
        accept();
    }
}

void
TestServerUnixSocket::timeoutHandler() {
    ADD_FAILURE() << "Timeout occurred while running the test!";
    io_service_.stop();
}

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc
