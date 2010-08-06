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

#include "session_unittests_config.h"

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

// This class sets up a domain socket for the session to connect to
// it will impersonate the msgq a tiny bit (if setSendLname() has
// been called, it will send an 'answer' to the lname query that is
// sent in the initialization of Session objects)
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
        ::unlink(BIND10_TEST_SOCKET_FILE);
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
    ::unlink(BIND10_TEST_SOCKET_FILE);
    TestDomainSocket tds(my_io_service, BIND10_TEST_SOCKET_FILE);
    Session sess(my_io_service);
    // set to a short timeout so the test doesn't take too long
    EXPECT_EQ(4000, sess.getTimeout());
    sess.setTimeout(100);
    EXPECT_EQ(100, sess.getTimeout());
    // no answer, should timeout
    EXPECT_THROW(sess.establish(BIND10_TEST_SOCKET_FILE), isc::cc::SessionTimeout);
}

TEST(Session, connect_ok) {
    asio::io_service my_io_service;
    ::unlink(BIND10_TEST_SOCKET_FILE);
    TestDomainSocket tds(my_io_service, BIND10_TEST_SOCKET_FILE);
    tds.setSendLname();

    Session sess(my_io_service);
    sess.establish(BIND10_TEST_SOCKET_FILE);
}

TEST(Session, connect_ok_connection_reset) {
    asio::io_service my_io_service;
    ::unlink(BIND10_TEST_SOCKET_FILE);
    Session sess(my_io_service);

    // Create a fake msgq in a smaller scope, so we can
    // connect the session to it, but later calls on the
    // underlying socket will fail
    {
        TestDomainSocket tds(my_io_service, BIND10_TEST_SOCKET_FILE);
        tds.setSendLname();
        sess.establish(BIND10_TEST_SOCKET_FILE);
    }
    
    isc::data::ElementPtr env, msg;
    EXPECT_THROW(sess.group_recvmsg(env, msg, false, -1), isc::cc::SessionError);
}

