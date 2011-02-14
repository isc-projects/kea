// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/udp_query.h>

using namespace asio;
using namespace isc::dns;
using asio::ip::udp;

namespace {

const asio::ip::address TEST_HOST(asio::ip::address::from_string("127.0.0.1"));
const uint16_t TEST_PORT(5301);
// FIXME Shouldn't we send something that is real message?
const char TEST_DATA[] = "TEST DATA";

// Test fixture for the asiolink::UDPQuery.
class UDPQueryTest : public ::testing::Test,
    public asiolink::UDPQuery::Callback
{
    public:
        // Expected result of the callback
        asiolink::UDPQuery::Result expected_;
        // Did the callback run already?
        bool run_;
        // We use an io_service to run the query
        io_service service_;
        // Something to ask
        Question question_;
        // Buffer where the UDPQuery will store response
        OutputBufferPtr buffer_;
        // The query we are testing
        asiolink::UDPQuery query_;

        UDPQueryTest() :
            run_(false),
            question_(Name("example.net"), RRClass::IN(), RRType::A()),
            buffer_(new OutputBuffer(512)),
            query_(service_, question_, asiolink::IOAddress(TEST_HOST),
                TEST_PORT, buffer_, this, 100)
        { }

        // This is the callback's (), so it can be called.
        void operator()(asiolink::UDPQuery::Result result) {
            // We check the query returns the correct result
            EXPECT_EQ(expected_, result);
            // Check it is called only once
            EXPECT_FALSE(run_);
            // And mark the callback was called
            run_ = true;
        }
        // A response handler, pretending to be remote DNS server
        void respond(udp::endpoint* remote, udp::socket* socket) {
            // Some data came, just send something back.
            socket->send_to(asio::buffer(TEST_DATA, sizeof TEST_DATA),
                *remote);
            socket->close();
        }
};

/*
 * Test that when we run the query and stop it after it was run,
 * it returns "stopped" correctly.
 *
 * That is why stop() is posted to the service_ as well instead
 * of calling it.
 */
TEST_F(UDPQueryTest, stop) {
    expected_ = asiolink::UDPQuery::STOPPED;
    // Post the query
    service_.post(query_);
    // Post query_.stop() (yes, the boost::bind thing is just
    // query_.stop()).
    service_.post(boost::bind(&asiolink::UDPQuery::stop, query_,
        asiolink::UDPQuery::STOPPED));
    // Run both of them
    service_.run();
    EXPECT_TRUE(run_);
}

/*
 * Test that when we queue the query to service_ and call stop()
 * before it gets executed, it acts sanely as well (eg. has the
 * same result as running stop() after - calls the callback).
 */
TEST_F(UDPQueryTest, prematureStop) {
    expected_ = asiolink::UDPQuery::STOPPED;
    // Stop before it is started
    query_.stop();
    service_.post(query_);
    service_.run();
    EXPECT_TRUE(run_);
}

/*
 * Test that it will timeout when no answer will arrive.
 */
TEST_F(UDPQueryTest, timeout) {
    expected_ = asiolink::UDPQuery::TIME_OUT;
    service_.post(query_);
    service_.run();
    EXPECT_TRUE(run_);
}

/*
 * Test that it will succeed when we fake an answer and
 * stores the same data we send.
 *
 * This is done through a real socket on loopback address.
 */
TEST_F(UDPQueryTest, receive) {
    expected_ = asiolink::UDPQuery::SUCCESS;
    udp::socket socket(service_, udp::v4());
    socket.set_option(socket_base::reuse_address(true));
    socket.bind(udp::endpoint(TEST_HOST, TEST_PORT));
    char inbuff[512];
    udp::endpoint remote;
    socket.async_receive_from(asio::buffer(inbuff, 512), remote, boost::bind(
        &UDPQueryTest::respond, this, &remote, &socket));
    service_.post(query_);
    service_.run();
    EXPECT_TRUE(run_);
    ASSERT_EQ(sizeof TEST_DATA, buffer_->getLength());
    EXPECT_EQ(0, memcmp(TEST_DATA, buffer_->getData(), sizeof TEST_DATA));
}

}
