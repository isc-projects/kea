// Copyright (C) 2010  CZ.NIC
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

#include <gtest/gtest.h>
#include <asio.hpp>
#include <boost/bind.hpp>
#include <cstdlib>

#include <dns/question.h>

#include <asiolink/internal/udpdns.h>

using namespace asio;
using namespace isc::dns;
using asio::ip::udp;

namespace {

const asio::ip::address TEST_HOST(asio::ip::address::from_string("127.0.0.1"));
const uint16_t TEST_PORT(5301);
// FIXME Shouldn't we send something that is real message?
const char TEST_DATA[] = "TEST DATA";

class UDPQuery : public ::testing::Test, public asiolink::UDPQuery::Callback {
    public:
        asiolink::UDPQuery::Result expected;
        bool run;
        io_service service;
        Question question;
        // To keep a reference so noone calls delete this;
        OutputBufferPtr buffer;
        asiolink::UDPQuery query;

        UDPQuery() :
            run(false),
            question(Name("example.net"), RRClass::IN(), RRType::A()),
            buffer(new OutputBuffer(512)),
            query(service, question, asiolink::IOAddress(TEST_HOST), TEST_PORT,
                buffer, this, 100)
        { }

        void operator()(asiolink::UDPQuery::Result result) {
            EXPECT_EQ(expected, result);
            run = true;
        }
        void respond(udp::endpoint& remote, udp::socket* socket) {
            // Some data came, just send something back.
            socket->send_to(asio::buffer(TEST_DATA, sizeof TEST_DATA), remote);
            socket->close();
        }
};

TEST_F(UDPQuery, stop) {
    expected = asiolink::UDPQuery::STOPPED;
    service.post(query);
    // Make sure stop is called after executing () of the query
    // Why doesn't boost::bind support default parameters?
    service.post(boost::bind(&asiolink::UDPQuery::stop, query,
        asiolink::UDPQuery::STOPPED));
    service.run();
    EXPECT_TRUE(run);
}

TEST_F(UDPQuery, prematureStop) {
    expected = asiolink::UDPQuery::STOPPED;
    // Stop before it is started
    query.stop();
    service.post(query);
    service.run();
    EXPECT_TRUE(run);
}

TEST_F(UDPQuery, timeout) {
    expected = asiolink::UDPQuery::TIME_OUT;
    service.post(query);
    service.run();
    EXPECT_TRUE(run);
}

TEST_F(UDPQuery, receive) {
    expected = asiolink::UDPQuery::SUCCESS;
    udp::socket socket(service, udp::v4());
    socket.set_option(socket_base::reuse_address(true));
    socket.bind(udp::endpoint(TEST_HOST, TEST_PORT));
    char inbuff[512];
    udp::endpoint remote;
    socket.async_receive_from(asio::buffer(inbuff, 512), remote, boost::bind(
        &UDPQuery::respond, this, remote, &socket));
    service.post(query);
    service.run();
    EXPECT_TRUE(run);
    ASSERT_EQ(sizeof TEST_DATA, buffer->getLength());
    EXPECT_EQ(0, memcmp(TEST_DATA, buffer->getData(), sizeof TEST_DATA));
}

}
