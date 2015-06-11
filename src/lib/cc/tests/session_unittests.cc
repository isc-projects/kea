// Copyright (C) 2009, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

// for some IPC/network system calls in asio/detail/pipe_select_interrupter.hpp 
#include <unistd.h>
// XXX: the ASIO header must be included before others.  See session.cc.
#include <asio.hpp>

#include <cc/session.h>
#include <cc/data.h>
#include <cc/tests/session_unittests_config.h>

#include <gtest/gtest.h>
#include <boost/bind.hpp>

#include <exceptions/exceptions.h>

#include <util/unittests/test_exceptions.h>

#include <utility>
#include <list>
#include <string>
#include <iostream>

using namespace isc::cc;
using std::pair;
using std::list;
using std::string;
using isc::data::ConstElementPtr;
using isc::data::Element;

namespace {

TEST(AsioSession, establish) {
    asio::io_service io_service_;
    Session sess(io_service_);

    // can't return socket descriptor before session is established
    EXPECT_THROW_WITH(sess.getSocketDesc(), isc::InvalidOperation,
                      "Can't return socket descriptor: no socket opened.");

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
        socket_(io_service_),
        data_buf_(1024)
    {
        acceptor_.async_accept(socket_, boost::bind(&TestDomainSocket::acceptHandler,
                                                    _1));
    }

    ~TestDomainSocket() {
        socket_.close();
        unlink(BUNDY_TEST_SOCKET_FILE);
    }

    static void acceptHandler(const asio::error_code&) {
    }

    void sendmsg(isc::data::ElementPtr& env, isc::data::ElementPtr& msg) {
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

    void sendLname() {
        isc::data::ElementPtr lname_answer1 =
            isc::data::Element::fromJSON("{ \"type\": \"lname\" }");
        isc::data::ElementPtr lname_answer2 =
            isc::data::Element::fromJSON("{ \"lname\": \"foobar\" }");
        sendmsg(lname_answer1, lname_answer2);
    }

    void setSendLname() {
        // ignore whatever data we get, send back an lname
        asio::async_read(socket_,  asio::buffer(&data_buf_[0], 0),
                         boost::bind(&TestDomainSocket::sendLname, this));
    }

private:
    asio::io_service& io_service_;
    asio::local::stream_protocol::endpoint ep_;
    asio::local::stream_protocol::acceptor acceptor_;
    asio::local::stream_protocol::socket socket_;
    std::vector<char> data_buf_;
};

/// \brief Pair holding header and data of a message sent over the connection.
typedef pair<ConstElementPtr, ConstElementPtr> SentMessage;

// We specialize the tested class a little. We replace some low-level
// methods so we can examine the rest without relying on real network IO
class TestSession : public Session {
public:
    TestSession(asio::io_service& ioservice) :
        Session(ioservice)
    {}
    // Get first message previously sent by sendmsg and remove it from the
    // buffer. Expects there's at leas one message in the buffer.
    SentMessage getSentMessage() {
        assert(!sent_messages_.empty());
        const SentMessage result(sent_messages_.front());
        sent_messages_.pop_front();
        return (result);
    }
private:
    // Override the sendmsg. They are not sent over the real connection, but
    // stored locally and can be extracted by getSentMessage()
    virtual void sendmsg(ConstElementPtr header) {
        sendmsg(header, ConstElementPtr(new isc::data::NullElement));
    }
    virtual void sendmsg(ConstElementPtr header, ConstElementPtr payload) {
        sent_messages_.push_back(SentMessage(header, payload));
    }

    // The sendmsg stores data here.
    list<SentMessage> sent_messages_;
};

class SessionTest : public ::testing::Test {
protected:
    SessionTest() : sess(my_io_service), work(my_io_service) {
        // The TestDomainSocket is held as a 'new'-ed pointer,
        // so we can call unlink() first.
        unlink(BUNDY_TEST_SOCKET_FILE);
        tds = new TestDomainSocket(my_io_service, BUNDY_TEST_SOCKET_FILE);
    }

    ~SessionTest() {
        delete tds;
    }

    // Check the session sent a message with the given header. The
    // message is hardcoded.
    void checkSentMessage(const string& expected_hdr, const char* description)
    {
        SCOPED_TRACE(description);
        const SentMessage& msg(sess.getSentMessage());
        elementsEqual(expected_hdr, msg.first);
        elementsEqual("{\"test\": 42}", msg.second);
    }

private:
    // Check two elements are equal
    void elementsEqual(const string& expected,
                       const ConstElementPtr& actual) const
    {
        EXPECT_TRUE(Element::fromJSON(expected)->equals(*actual)) <<
            "Elements differ, expected: " << expected <<
            ", got: " << actual->toWire();
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
    TestSession sess;
    // Keep run() from stopping right away by informing it it has work to do
    asio::io_service::work work;
};

TEST_F(SessionTest, timeout_on_connect) {
    // set to a short timeout so the test doesn't take too long
    EXPECT_EQ(4000, sess.getTimeout());
    sess.setTimeout(100);
    EXPECT_EQ(100, sess.getTimeout());
    // no answer, should timeout
    EXPECT_THROW_WITH(sess.establish(BUNDY_TEST_SOCKET_FILE), SessionTimeout,
                      "Timeout while reading data from cc session");
}

TEST_F(SessionTest, connect_ok) {
    tds->setSendLname();
    sess.establish(BUNDY_TEST_SOCKET_FILE);
}

TEST_F(SessionTest, connect_ok_no_timeout) {
    tds->setSendLname();

    sess.setTimeout(0);
    sess.establish(BUNDY_TEST_SOCKET_FILE);
}

TEST_F(SessionTest, connect_ok_connection_reset) {
    tds->setSendLname();

    sess.establish(BUNDY_TEST_SOCKET_FILE);
    // Close the session again, so the next recv() should throw
    sess.disconnect();

    isc::data::ConstElementPtr env, msg;
    EXPECT_THROW_WITH(sess.group_recvmsg(env, msg, false, -1),
                      SessionError,
                      "Error while reading data from cc session: "
                      << strerror(EBADF));
}

TEST_F(SessionTest, run_with_handler) {
    tds->setSendLname();

    sess.establish(BUNDY_TEST_SOCKET_FILE);
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

    sess.establish(BUNDY_TEST_SOCKET_FILE);
    sess.startRead(boost::bind(&SessionTest::someHandler, this));
    sess.setTimeout(100);

    isc::data::ElementPtr env = isc::data::Element::fromJSON("{ \"to\": \"me\" }");
    isc::data::ElementPtr msg = isc::data::Element::fromJSON("{ \"some\": \"message\" }");
    tds->sendmsg(env, msg);

    msg = isc::data::Element::fromJSON("{ \"another\": \"message\" }");
    tds->sendmsg(env, msg);

    msg = isc::data::Element::fromJSON("{ \"a third\": \"message\" }");
    tds->sendmsg(env, msg);

    // No follow-up message, should time out.
    ASSERT_THROW_WITH(my_io_service.run(), SessionTimeout,
                      "Timeout while reading data from cc session");
}

TEST_F(SessionTest, get_socket_descr) {
    tds->setSendLname();
    sess.establish(BUNDY_TEST_SOCKET_FILE);

    int socket = 0;
    // session is established, so getSocketDesc() should work
    EXPECT_NO_THROW(socket = sess.getSocketDesc());

    // expect actual socket handle to be returned, not 0
    EXPECT_LT(0, socket);
}

// Test the group_sendmsg sends the correct data.
TEST_F(SessionTest, group_sendmsg) {
    // Connect (to set the lname, so we can see it sets the from)
    tds->setSendLname();
    sess.establish(BUNDY_TEST_SOCKET_FILE);
    // Eat the "get_lname" message, so it doesn't confuse the
    // test below.
    sess.getSentMessage();

    const ConstElementPtr msg(Element::fromJSON("{\"test\": 42}"));
    sess.group_sendmsg(msg, "group");
    checkSentMessage("{"
                     "   \"from\": \"foobar\","
                     "   \"group\": \"group\","
                     "   \"instance\": \"*\","
                     "   \"seq\": 0,"
                     "   \"to\": \"*\","
                     "   \"type\": \"send\","
                     "   \"want_answer\": False"
                     "}", "No instance");
    sess.group_sendmsg(msg, "group", "instance", "recipient");
    checkSentMessage("{"
                     "   \"from\": \"foobar\","
                     "   \"group\": \"group\","
                     "   \"instance\": \"instance\","
                     "   \"seq\": 1,"
                     "   \"to\": \"recipient\","
                     "   \"type\": \"send\","
                     "   \"want_answer\": False"
                     "}", "With instance");
    sess.group_sendmsg(msg, "group", "*", "*", true);
    checkSentMessage("{"
                     "   \"from\": \"foobar\","
                     "   \"group\": \"group\","
                     "   \"instance\": \"*\","
                     "   \"seq\": 2,"
                     "   \"to\": \"*\","
                     "   \"type\": \"send\","
                     "   \"want_answer\": True"
                     "}", "Want answer");
    sess.group_sendmsg(msg, "group", "*", "*", false);
    checkSentMessage("{"
                     "   \"from\": \"foobar\","
                     "   \"group\": \"group\","
                     "   \"instance\": \"*\","
                     "   \"seq\": 3,"
                     "   \"to\": \"*\","
                     "   \"type\": \"send\","
                     "   \"want_answer\": False"
                     "}", "Doesn't want answer");
}

}
