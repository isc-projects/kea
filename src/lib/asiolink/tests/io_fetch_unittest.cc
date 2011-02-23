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
#include <boost/bind.hpp>
#include <cstdlib>
#include <string>

#include <string.h>

#include <asio.hpp>

#include <dns/buffer.h>
#include <dns/question.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/name.h>
#include <dns/rcode.h>

#include <asiolink/io_fetch.h>
#include <asiolink/io_service.h>

using namespace asio;
using namespace isc::dns;
using asio::ip::udp;

namespace asiolink {

const asio::ip::address TEST_HOST(asio::ip::address::from_string("127.0.0.1"));
const uint16_t TEST_PORT(5301);
// FIXME Shouldn't we send something that is real message?
const char TEST_DATA[] = "TEST DATA";

/// \brief Test fixture for the asiolink::IOFetch.
class IOFetchTest : public virtual ::testing::Test, public virtual IOFetch::Callback
{
public:
    IOService       service_;       ///< Service to run the query
    IOFetch::Result expected_;      ///< Expected result of the callback
    bool            run_;           ///< Did the callback run already?
    Question        question_;      ///< What to ask
    OutputBufferPtr buff_;          ///< Buffer to hold result
    IOFetch         udp_fetch_;     ///< For UDP query test
    //IOFetch         tcp_fetch_;     ///< For TCP query test

    // The next member is the buffer iin which the "server" (implemented by the
    // response handler method) receives the question sent by the fetch object.
    char            server_buff_[512];  ///< Server buffer

    /// \brief Constructor
    IOFetchTest() :
        service_(),
        expected_(IOFetch::NOTSET),
        run_(false),
        question_(Name("example.net"), RRClass::IN(), RRType::A()),
        buff_(new OutputBuffer(512)),
        udp_fetch_(IPPROTO_UDP, service_, question_, IOAddress(TEST_HOST),
            TEST_PORT, buff_, this, 100)
        // tcp_fetch_(service_, question_, IOAddress(TEST_HOST), TEST_PORT,
        //    buff_, this, 100, IPPROTO_UDP)
        { }

    /// \brief Fetch completion callback
    ///
    /// This is the callback's operator() method which is called when the fetch
    /// is complete.  Check that the data received is the wire format of the
    /// question, then send back an arbitrary response.
    void operator()(IOFetch::Result result) {
        EXPECT_EQ(expected_, result);   // Check correct result returned
        EXPECT_FALSE(run_);             // Check it is run only once
        run_ = true;                    // Note success
        service_.stop();                // ... and exit run loop
    }

    /// \brief Response handler, pretending to be remote DNS server
    ///
    /// This checks that the data sent is what we expected to receive, and
    /// sends back a test answer.
    void respond(udp::endpoint* remote, udp::socket* socket,
            asio::error_code ec = asio::error_code(), size_t length = 0) {

        // Construct the data buffer for question we expect to receive.
        OutputBuffer msgbuf(512);
        Message msg(Message::RENDER);
        msg.setQid(0);
        msg.setOpcode(Opcode::QUERY());
        msg.setRcode(Rcode::NOERROR());
        msg.setHeaderFlag(Message::HEADERFLAG_RD);
        msg.addQuestion(question_);
        MessageRenderer renderer(msgbuf);
        msg.toWire(renderer);

        // The QID in the incoming data is random so set it to 0 for the
        // data comparison check. (It was set to 0 when the buffer containing
        // the expected data was constructed above.)
        server_buff_[0] = server_buff_[1] = 0;

        // Check that lengths are identical.
        EXPECT_EQ(msgbuf.getLength(), length);
        EXPECT_TRUE(memcmp(msgbuf.getData(), server_buff_, length) == 0);

        // ... and return a message back.
        socket->send_to(asio::buffer(TEST_DATA, sizeof TEST_DATA), *remote);
    }
};


/// Test that when we run the query and stop it after it was run,
/// it returns "stopped" correctly.
///
/// That is why stop() is posted to the service_ as well instead
/// of calling it.
TEST_F(IOFetchTest, UdpStop) {
    expected_ = IOFetch::STOPPED;

    // Post the query
    service_.get_io_service().post(udp_fetch_);

    // Post query_.stop() (yes, the boost::bind thing is just
    // query_.stop()).
    service_.get_io_service().post(
       boost::bind(&IOFetch::stop, udp_fetch_, IOFetch::STOPPED));

    // Run both of them.  run() returns when everything in the I/O service
    // queue has completed.
    service_.run();
    EXPECT_TRUE(run_);
}

// Test that when we queue the query to service_ and call stop() before it gets
// executed, it acts sanely as well (eg. has the same result as running stop()
// after - calls the callback).
TEST_F(IOFetchTest, UdpPrematureStop) {
    expected_ = IOFetch::STOPPED;

    // Stop before it is started
    udp_fetch_.stop();
    service_.get_io_service().post(udp_fetch_);

    service_.run();
    EXPECT_TRUE(run_);
}

// Test that it will timeout when no answer arrives.
TEST_F(IOFetchTest, UdpTimeout) {
    expected_ = IOFetch::TIME_OUT;

    service_.get_io_service().post(udp_fetch_);
    service_.run();
    EXPECT_TRUE(run_);
}

// Test that it will succeed when we fake an answer and stores the same data we
// send.  This is done through a real socket on the loopback address.
TEST_F(IOFetchTest, UdpReceive) {
    expected_ = IOFetch::SUCCESS;

    udp::socket socket(service_.get_io_service(), udp::v4());
    socket.set_option(socket_base::reuse_address(true));
    socket.bind(udp::endpoint(TEST_HOST, TEST_PORT));

    udp::endpoint remote;
    socket.async_receive_from(asio::buffer(server_buff_, sizeof(server_buff_)),
        remote,
        boost::bind(&IOFetchTest::respond, this, &remote, &socket, _1, _2));
    service_.get_io_service().post(udp_fetch_);
    service_.run();

    socket.close();

    EXPECT_TRUE(run_);
    ASSERT_EQ(sizeof TEST_DATA, buff_->getLength());
    EXPECT_EQ(0, memcmp(TEST_DATA, buff_->getData(), sizeof TEST_DATA));
}

} // namespace asiolink
