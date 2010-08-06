// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id: data_unittests.cc 1899 2010-05-21 12:03:59Z jelte $

#include <config.h>

// for some IPC/network system calls in asio/detail/pipe_select_interrupter.hpp 
#include <unistd.h>
// XXX: the ASIO header must be included before others.  See session.cc.
#include <asio.hpp>

#include <gtest/gtest.h>
#include <session.h>

#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <asio.hpp>
#include <boost/bind.hpp>

using namespace isc::cc;

TEST(AsioSession, establish) {
    asio::io_service io_service_;
    Session sess(io_service_);

    EXPECT_THROW(
        sess.establish("/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                       "/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/"
                  ), isc::cc::SessionError
    );
}


void
my_data_handler_no_answer(const asio::error_code& error, size_t bytes_transferred) {
    std::cout << "[XX] got data" << std::endl;
}

void
my_accept_handler(const asio::error_code& error) {
    std::cout << "[XX] accepted" << std::endl;
}

/*
class TestDomainSocket {

public:
    TestDomainSocket(asio::io_service& io_service, const char* file) : io_service_(io_service).
                                                                       ep_(file),
                                                                       acceptor_(io_service_, ep_),
                                                                       socket_(io_service_) {
        acceptor_.async_accept(socket_,
                               boost::bind(&TestDomainSocket::acceptHandler,
                                           this, _1));
    }
    
    ~TestDomainSocket() {
        std::cout << "[XX] destroy test domain socket" << std::endl;
    }

    void
    start(const char* file)
    {
    }

    void
    acceptHandler(const asio::error_code& error) {
        std::cout << "[XX] accepted" << std::endl;
    }
    
    
    void
    my_data_handler_echo(const asio::error_code& error, size_t bytes_transferred, asio::local::stream_protocol::socket& socket) {
        char data[4] = {0x01, 0x02, 0x03, 0x04};
        socket.send(asio::buffer(data, 4));
    }

    void
    close() {
        //socket_.close();
    }

private:
    asio::io_service& io_service_;
    asio::local::stream_protocol::endpoint ep_;
    asio::local::stream_protocol::acceptor acceptor_;
    asio::local::stream_protocol::socket socket_;
};
*/

class TestDomainSocket {

public:
    TestDomainSocket(asio::io_service& io_service, const char* file) : io_service_(io_service),
                                                                       ep_(file),
                                                                       acceptor_(io_service_, ep_),
                                                                       socket_(io_service_)
    {
        acceptor_.async_accept(socket_,
                               boost::bind(&TestDomainSocket::acceptHandler,
                                           this, _1));
    }
    
    ~TestDomainSocket() {
        socket_.close();
    }

    void
    acceptHandler(const asio::error_code& error) {
    }

    void
    sendmsg(isc::data::ElementPtr& env, isc::data::ElementPtr& msg) {
        std::string header_wire = env->toWire();
        std::string body_wire = msg->toWire();
        unsigned int length = 2 + header_wire.length() + body_wire.length();
        unsigned int length_net = htonl(length);
        unsigned short header_length = header_wire.length();
        unsigned short header_length_net = htons(header_length);
    
        socket_.send(asio::buffer(&length_net, sizeof(length_net)));
        socket_.send(asio::buffer(&header_length_net, sizeof(header_length_net)));
        socket_.send(asio::buffer(header_wire.data(), header_length));
        socket_.send(asio::buffer(body_wire.data(), body_wire.length()));
    }

    void
    sendLname() {
        isc::data::ElementPtr lname_answer1 = isc::data::Element::fromJSON("{ \"type\": \"lname\" }");
        isc::data::ElementPtr lname_answer2 = isc::data::Element::fromJSON("{ \"lname\": \"foobar\" }");
        sendmsg(lname_answer1, lname_answer2);
    }

    void
    setSendLname() {
        // ignore whatever data we get, send back an lname
        asio::async_read(socket_,  asio::buffer(data_buf, 1024), boost::bind(&TestDomainSocket::sendLname, this));
    }
    
private:
    asio::io_service& io_service_;
    asio::local::stream_protocol::endpoint ep_;
    asio::local::stream_protocol::acceptor acceptor_;
    asio::local::stream_protocol::socket socket_;
    char data_buf[1024];
};


TEST(Session, timeout_on_connect) {
    asio::io_service my_io_service;
    ::unlink("/tmp/mysock.sock");
    TestDomainSocket tds(my_io_service, "/tmp/mysock.sock");
    Session sess(my_io_service);

    // no answer, should timeout
    EXPECT_THROW(sess.establish("/tmp/mysock.sock"), isc::cc::SessionTimeout);
}

TEST(Session, connect_ok) {
    asio::io_service my_io_service;
    ::unlink("/tmp/mysock.sock");
    TestDomainSocket tds(my_io_service, "/tmp/mysock.sock");
    tds.setSendLname();

    Session sess(my_io_service);
    sess.establish("/tmp/mysock.sock");
}

