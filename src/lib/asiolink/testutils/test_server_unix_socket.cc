// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <set>

using namespace boost::asio::local;

namespace isc {
namespace asiolink {
namespace test {

typedef stream_protocol::socket UnixSocket;
typedef boost::shared_ptr<UnixSocket> UnixSocketPtr;

typedef std::function<void()> SentResponseCallback;

class Connection {
public:

    Connection(const UnixSocketPtr& unix_socket,
               const std::string custom_response,
               const SentResponseCallback& sent_response_callback)
        : socket_(unix_socket), custom_response_(custom_response),
          sent_response_callback_(sent_response_callback) {
       socket_->async_read_some(boost::asio::buffer(&raw_buf_[0], raw_buf_.size()),
           boost::bind(&Connection::readHandler, this, _1, _2));
    }

    void
    readHandler(const boost::system::error_code&, size_t bytes_transferred) {
        if (!custom_response_.empty()) {
            boost::asio::write(*socket_,
               boost::asio::buffer(custom_response_.c_str(), custom_response_.size()));

        } else {
            std::string received(&raw_buf_[0], bytes_transferred);
            std::string response("received " + received);
            boost::asio::write(*socket_,
                boost::asio::buffer(response.c_str(), response.size()));
        }

        sent_response_callback_();
    }

    void stop() {
        socket_->close();
    }

private:

    UnixSocketPtr socket_;

    std::string custom_response_;

    /// @brief Receive buffer.
    std::array<char, 1024> raw_buf_;

    SentResponseCallback sent_response_callback_;

};

typedef boost::shared_ptr<Connection> ConnectionPtr;

class ConnectionPool {
public:

    ConnectionPool(IOService& io_service)
        : io_service_(io_service), connections_(), next_socket_(),
          response_num_(0) {
    }

    UnixSocketPtr getSocket() {
        if (!next_socket_) {
            next_socket_.reset(new UnixSocket(io_service_.get_io_service()));
        }
        return (next_socket_);
    }

    void start(const std::string& custom_response) {
        ConnectionPtr conn(new Connection(next_socket_, custom_response, [this] {
            ++response_num_;
        }));

        connections_.insert(conn);
        next_socket_.reset();
    }

    void stop(const ConnectionPtr& conn) {
        conn->stop();
        connections_.erase(conn);
    }

    void stopAll() {
        for (auto conn = connections_.begin(); conn != connections_.end();
             ++conn) {
            (*conn)->stop();
        }
        connections_.clear();
    }

    size_t getResponseNum() const {
        return (response_num_);
    }

private:

    IOService& io_service_;

    std::set<ConnectionPtr> connections_;

    UnixSocketPtr next_socket_;

    size_t response_num_;
};


TestServerUnixSocket::TestServerUnixSocket(IOService& io_service,
                                           const std::string& socket_file_path,
                                           const long test_timeout,
                                           const std::string& custom_response)
    : io_service_(io_service),
      server_endpoint_(socket_file_path),
      server_acceptor_(io_service_.get_io_service()),
      test_timer_(io_service_),
      custom_response_(custom_response),
      connection_pool_(new ConnectionPool(io_service)) {
    test_timer_.setup(boost::bind(&TestServerUnixSocket::timeoutHandler, this),
                      test_timeout, IntervalTimer::ONE_SHOT);
}

TestServerUnixSocket::~TestServerUnixSocket() {
    connection_pool_->stopAll();
}

void
TestServerUnixSocket::bindServerSocket() {
    server_acceptor_.open();
    server_acceptor_.bind(server_endpoint_);
    server_acceptor_.listen();
    accept();
}

void
TestServerUnixSocket::acceptHandler(const boost::system::error_code&) {
    connection_pool_->start(custom_response_);
    accept();
}

void
TestServerUnixSocket::accept() {
    server_acceptor_.async_accept(*(connection_pool_->getSocket()),
        boost::bind(&TestServerUnixSocket::acceptHandler, this, _1));
}

void
TestServerUnixSocket::timeoutHandler() {
    ADD_FAILURE() << "Timeout occurred while running the test!";
    io_service_.stop();
}

size_t
TestServerUnixSocket::getResponseNum() const {
    return (connection_pool_->getResponseNum());
}


} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc
