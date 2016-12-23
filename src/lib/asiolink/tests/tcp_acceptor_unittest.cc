// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/tcp_acceptor.h>
#include <asiolink/tcp_endpoint.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <list>
#include <string>

using namespace boost::asio::ip;
using namespace isc::asiolink;

namespace {

class TCPClient;

class SocketCallback {
public:

    void operator()(boost::system::error_code ec = boost::system::error_code(),
                            size_t length = 0) {
        std::cout << "socket callback invoked" << std::endl;
    }

};

typedef boost::shared_ptr<TCPClient> TCPClientPtr;

class TCPClient : public boost::noncopyable {
public:

    TCPClient(IOService& io_service)
        : io_service_(io_service.get_io_service()), socket_(io_service_) {
    }

    void connect() {
        tcp::endpoint endpoint(address::from_string("127.0.0.1"), 18123);
        try {
            socket_.connect(endpoint);
        } catch (const boost::system::system_error& ex) {
            ADD_FAILURE() << "an error occured while connecting over TCP socket: "
                          << ex.what();

            io_service_.stop();
        }
    }

    void close() {
        socket_.close();
    }

private:

    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::socket socket_;

};


typedef boost::function<void(const boost::system::error_code&)> TCPAcceptorCallback;

class Acceptor {
public:

    Acceptor(IOService& io_service, TCPAcceptor<TCPAcceptorCallback>& acceptor,
             const TCPAcceptorCallback& callback)
        : socket_(io_service), acceptor_(acceptor), callback_(callback) {
    }

    void accept() {
        acceptor_.asyncAccept(socket_, callback_);
    }

    void close() {
        socket_.close();
    }

private:

    TCPSocket<SocketCallback> socket_;
    TCPAcceptor<TCPAcceptorCallback>& acceptor_;
    TCPAcceptorCallback callback_;

};

typedef boost::shared_ptr<Acceptor> AcceptorPtr;

class TCPAcceptorTest : public ::testing::Test {
public:

    TCPAcceptorTest()
        : io_service_(), acceptor_(io_service_), test_timer_(io_service_),
          connections_(), clients_(), connections_num_(0), max_connections_(1) {
        test_timer_.setup(boost::bind(&TCPAcceptorTest::timeoutHandler, this),
                                      10000, IntervalTimer::ONE_SHOT);
    }

    virtual ~TCPAcceptorTest() {
        for (auto client = clients_.begin(); client != clients_.end();
             ++client) {
            (*client)->close();
        }

        for (auto conn = connections_.begin(); conn != connections_.end();
             ++conn) {
            (*conn)->close();
        }
    }

    void setMaxConnections(const unsigned int max_connections) {
        max_connections_ = max_connections;
    }

    void accept() {
        TCPAcceptorCallback cb = boost::bind(&TCPAcceptorTest::acceptHandler,
                                             this, _1);
        AcceptorPtr conn(new Acceptor(io_service_, acceptor_, cb));
        connections_.push_back(conn);
        connections_.back()->accept();
    }

    void connect() {
        TCPClientPtr client(new TCPClient(io_service_));
        clients_.push_back(client);
        clients_.back()->connect();
    }

    void acceptHandler(const boost::system::error_code& ec) {
        if (ec) {
            ADD_FAILURE() << "error occurred while accepting connection: "
                          << ec.message();
        }

        if (++connections_num_ >= max_connections_) {
            io_service_.stop();

        } else {
            accept();
        }
    }

    void timeoutHandler() {
        ADD_FAILURE() << "Timeout occurred while running the test!";
        io_service_.stop();
    }

    IOService io_service_;
    TCPAcceptor<TCPAcceptorCallback> acceptor_;
    IntervalTimer test_timer_;
    std::list<AcceptorPtr> connections_;
    std::list<TCPClientPtr> clients_;
    unsigned int connections_num_;
    unsigned int max_connections_;
};

TEST_F(TCPAcceptorTest, asyncAccept) {
    setMaxConnections(10);
    TCPEndpoint endpoint(IOAddress("127.0.0.1"), 18123);
    acceptor_.open(endpoint);
    acceptor_.bind(endpoint);
    acceptor_.listen();

    accept();

    for (unsigned int i = 0; i < 10; ++i) {
        connect();
    }

    io_service_.run();
}

}
