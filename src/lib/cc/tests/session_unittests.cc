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
#include <boost/bind.hpp>

#include <exceptions/exceptions.h>

#include <cc/session.h>
#include <cc/data.h>
#include <session_unittests_config.h>

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
    TestDomainSocket(asio::io_service& io_service, const char* file) :
        io_service_(io_service),
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
        unlink(BIND10_TEST_SOCKET_FILE);
    }

    void
    acceptHandler(const asio::error_code& error UNUSED_PARAM) {
    }

    void
    sendmsg(isc::data::ElementPtr& env, isc::data::ElementPtr& msg) {
        const std::string header_wire = env->toWire();
        const std::string body_wire = msg->toWire();
        const unsigned int length = 2 + header_wire.length() +
            body_wire.length();
        const unsigned int length_net = htonl(length);
        const unsigned short header_length = header_wire.length();
        const unsigned short header_length_net = htons(header_length);
    
        socket_.send(asio::buffer(&length_net, sizeof(length_net)));
        socket_.send(asio::buffer(&header_length_net,
                                  sizeof(header_length_net)));
        socket_.send(asio::buffer(header_wire.data(), header_length));
        socket_.send(asio::buffer(body_wire.data(), body_wire.length()));
    }

    void
    sendLname() {
        isc::data::ElementPtr lname_answer1 =
            isc::data::Element::fromJSON("{ \"type\": \"lname\" }");
        isc::data::ElementPtr lname_answer2 =
            isc::data::Element::fromJSON("{ \"lname\": \"foobar\" }");
        sendmsg(lname_answer1, lname_answer2);
    }

    void
    setSendLname() {
        // ignore whatever data we get, send back an lname
        asio::async_read(socket_,  asio::buffer(data_buf, 0),
                         boost::bind(&TestDomainSocket::sendLname, this));
    }
    
private:
    asio::io_service& io_service_;
    asio::local::stream_protocol::endpoint ep_;
    asio::local::stream_protocol::acceptor acceptor_;
    asio::local::stream_protocol::socket socket_;
    char data_buf[1024];
};

class SessionTest : public ::testing::Test {
protected:
    SessionTest() : sess(my_io_service), work(my_io_service) {
        // The TestDomainSocket is held as a 'new'-ed pointer,
        // so we can call unlink() first.
        unlink(BIND10_TEST_SOCKET_FILE);
        tds = new TestDomainSocket(my_io_service, BIND10_TEST_SOCKET_FILE);
    }

    ~SessionTest() {
        delete tds;
    }

public:
    // used in the handler test
    // This handler first reads (and ignores) whatever message caused
    // it to be invoked. Then it calls group_recv for a second message.
    // If this message is { "command": "stop" } it'll tell the
    // io_service it is done. Otherwise it'll re-register this handler
    void someHandler() {
        isc::data::ConstElementPtr env, msg;
        sess.group_recvmsg(env, msg, false, -1);

        sess.group_recvmsg(env, msg, false, -1);
        if (msg && msg->contains("command") &&
            msg->get("command")->stringValue() == "stop") {
            my_io_service.stop();
        } else {
            sess.startRead(boost::bind(&SessionTest::someHandler, this));
        }
    }

protected:
    asio::io_service my_io_service;
    TestDomainSocket* tds;
    Session sess;
    // Keep run() from stopping right away by informing it it has work to do
    asio::io_service::work work;
};

TEST_F(SessionTest, timeout_on_connect) {
    // set to a short timeout so the test doesn't take too long
    EXPECT_EQ(4000, sess.getTimeout());
    sess.setTimeout(100);
    EXPECT_EQ(100, sess.getTimeout());
    // no answer, should timeout
    EXPECT_THROW(sess.establish(BIND10_TEST_SOCKET_FILE), SessionTimeout);
}

TEST_F(SessionTest, connect_ok) {
    tds->setSendLname();
    sess.establish(BIND10_TEST_SOCKET_FILE);
}

TEST_F(SessionTest, connect_ok_no_timeout) {
    tds->setSendLname();

    sess.setTimeout(0);
    sess.establish(BIND10_TEST_SOCKET_FILE);
}

TEST_F(SessionTest, connect_ok_connection_reset) {
    tds->setSendLname();

    sess.establish(BIND10_TEST_SOCKET_FILE);
    // Close the session again, so the next recv() should throw
    sess.disconnect();

    isc::data::ConstElementPtr env, msg;
    EXPECT_THROW(sess.group_recvmsg(env, msg, false, -1), SessionError);
}

TEST_F(SessionTest, run_with_handler) {
    tds->setSendLname();

    sess.establish(BIND10_TEST_SOCKET_FILE);
    sess.startRead(boost::bind(&SessionTest::someHandler, this));

    isc::data::ElementPtr env = isc::data::Element::fromJSON("{ \"to\": \"me\" }");
    isc::data::ElementPtr msg = isc::data::Element::fromJSON("{ \"some\": \"message\" }");
    tds->sendmsg(env, msg);

    msg = isc::data::Element::fromJSON("{ \"another\": \"message\" }");
    tds->sendmsg(env, msg);

    msg = isc::data::Element::fromJSON("{ \"a third\": \"message\" }");
    tds->sendmsg(env, msg);

    msg = isc::data::Element::fromJSON("{ \"command\": \"stop\" }");
    tds->sendmsg(env, msg);


    size_t count = my_io_service.run();
    ASSERT_EQ(2, count);
}

TEST_F(SessionTest, run_with_handler_timeout) {
    tds->setSendLname();

    sess.establish(BIND10_TEST_SOCKET_FILE);
    sess.startRead(boost::bind(&SessionTest::someHandler, this));
    sess.setTimeout(100);

    isc::data::ElementPtr env = isc::data::Element::fromJSON("{ \"to\": \"me\" }");
    isc::data::ElementPtr msg = isc::data::Element::fromJSON("{ \"some\": \"message\" }");
    tds->sendmsg(env, msg);

    msg = isc::data::Element::fromJSON("{ \"another\": \"message\" }");
    tds->sendmsg(env, msg);

    msg = isc::data::Element::fromJSON("{ \"a third\": \"message\" }");
    tds->sendmsg(env, msg);

    // No followup message, should time out.
    ASSERT_THROW(my_io_service.run(), SessionTimeout);
}


