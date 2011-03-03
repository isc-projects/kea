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

#include <algorithm>
#include <cstdlib>
#include <string>
#include <iostream>

#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <asio.hpp>

#include <dns/buffer.h>
#include <dns/question.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/name.h>
#include <dns/rcode.h>

#include <asiolink/asiolink_utilities.h>
#include <asiolink/io_address.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_fetch.h>
#include <asiolink/io_service.h>

using namespace asio;
using namespace isc::dns;
using namespace asio::ip;
using namespace std;

namespace asiolink {

const asio::ip::address TEST_HOST(asio::ip::address::from_string("127.0.0.1"));
const uint16_t TEST_PORT(5301);
// FIXME Shouldn't we send something that is real message?
const char TEST_DATA[] = "Test response from server to client (longer than 30 bytes)";
const int SEND_INTERVAL = 500;   // Interval in ms between TCP sends

/// \brief Test fixture for the asiolink::IOFetch.
class IOFetchTest : public virtual ::testing::Test, public virtual IOFetch::Callback
{
public:
    IOService       service_;       ///< Service to run the query
    IOFetch::Result expected_;      ///< Expected result of the callback
    bool            run_;           ///< Did the callback run already?
    Question        question_;      ///< What to ask
    OutputBufferPtr result_buff_;   ///< Buffer to hold result of fetch
    OutputBufferPtr msgbuf_;        ///< Buffer corresponding to known question
    IOFetch         udp_fetch_;     ///< For UDP query test
    IOFetch         tcp_fetch_;     ///< For TCP query test
    IOFetch::Protocol protocol_;    ///< Protocol being tested
    size_t          cumulative_;    ///< Cumulative data received by "server".
    deadline_timer  timer_;         ///< Timer to measure timeouts

    // The next member is the buffer in which the "server" (implemented by the
    // response handler methods in this class) receives the question sent by the
    // fetch object.
    uint8_t         receive_buffer_[512];   ///< Server receive buffer
    uint8_t         send_buffer_[512];      ///< Server send buffer
    uint16_t        send_size_;             ///< Amount of data to sent
    uint16_t        send_cumulative_;       ///< Data sent so far

    /// \brief Constructor
    IOFetchTest() :
        service_(),
        expected_(IOFetch::NOTSET),
        run_(false),
        question_(Name("example.net"), RRClass::IN(), RRType::A()),
        result_buff_(new OutputBuffer(512)),
        msgbuf_(new OutputBuffer(512)),
        udp_fetch_(IOFetch::UDP, service_, question_, IOAddress(TEST_HOST),
            TEST_PORT, result_buff_, this, 100),
        tcp_fetch_(IOFetch::TCP, service_, question_, IOAddress(TEST_HOST),
            TEST_PORT, result_buff_, this, (4 * SEND_INTERVAL)),
                                        // Timeout interval chosen to ensure no timeout
        protocol_(IOFetch::TCP),        // for initialization - will be changed
        cumulative_(0),
        timer_(service_.get_io_service()),
        receive_buffer_(),
        send_buffer_(),
        send_size_(0),
        send_cumulative_(0)
    {
        // Construct the data buffer for question we expect to receive.
        Message msg(Message::RENDER);
        msg.setQid(0);
        msg.setOpcode(Opcode::QUERY());
        msg.setRcode(Rcode::NOERROR());
        msg.setHeaderFlag(Message::HEADERFLAG_RD);
        msg.addQuestion(question_);
        MessageRenderer renderer(*msgbuf_);
        msg.toWire(renderer);
    }

    /// \brief UDP Response handler (the "remote UDP DNS server")
    ///
    /// When IOFetch is sending data, this response handler emulates the remote
    /// DNS server.  It checks that the data sent by the IOFetch object is what
    /// was expected to have been sent, then sends back a known buffer of data.
    ///
    /// \param remote Endpoint to which to send the answer
    /// \param socket Socket to use to send the answer
    /// \param ec ASIO error code, completion code of asynchronous I/O issued
    ///        by the "server" to receive data.
    /// \param length Amount of data received.
    void udpReceiveHandler(udp::endpoint* remote, udp::socket* socket,
                    error_code ec = error_code(), size_t length = 0) {

        // The QID in the incoming data is random so set it to 0 for the
        // data comparison check. (It is set to 0 in the buffer containing
        // the expected data.)
        receive_buffer_[0] = receive_buffer_[1] = 0;

        // Check that length of the received data and the expected data are
        // identical, then check that the data is identical as well.
        EXPECT_EQ(msgbuf_->getLength(), length);
        EXPECT_TRUE(equal(receive_buffer_, (receive_buffer_ + length - 1),
        static_cast<const uint8_t*>(msgbuf_->getData())));

        // Return a message back to the IOFetch object.
        socket->send_to(asio::buffer(TEST_DATA, sizeof TEST_DATA), *remote);
    }

    /// \brief Completion Handler for accepting TCP data
    ///
    /// Called when the remote system connects to the "server".  It issues
    /// an asynchronous read on the socket to read data.
    ///
    /// \param socket Socket on which data will be received
    /// \param ec Boost error code, value should be zero.
    void tcpAcceptHandler(tcp::socket* socket, error_code ec = error_code())
    {
        // Expect that the accept completed without a problem.
        EXPECT_EQ(0, ec.value());

        // Initiate a read on the socket.
        cumulative_ = 0;
        socket->async_receive(asio::buffer(receive_buffer_, sizeof(receive_buffer_)),
            boost::bind(&IOFetchTest::tcpReceiveHandler, this, socket, _1, _2));
    }

    /// \brief Completion handler for receiving TCP data
    ///
    /// When IOFetch is sending data, this response handler emulates the remote
    /// DNS server.  It that all the data sent by the IOFetch object has been
    /// received, issuing another read if not.  If the data is complete, it is
    /// compared to what is expected and a reply sent back to the IOFetch.
    ///
    /// \param socket Socket to use to send the answer
    /// \param ec ASIO error code, completion code of asynchronous I/O issued
    ///        by the "server" to receive data.
    /// \param length Amount of data received.
    void tcpReceiveHandler(tcp::socket* socket, error_code ec = error_code(),
                           size_t length = 0)
    {
        // Expect that the receive completed without a problem.
        EXPECT_EQ(0, ec.value());

        // If we haven't received all the data, issue another read.
        cumulative_ += length;
        bool complete = false;
        if (cumulative_ > 2) {
            uint16_t dns_length = readUint16(receive_buffer_);
            complete = ((dns_length + 2) == cumulative_);
        }

        if (!complete) {
            socket->async_receive(asio::buffer((receive_buffer_ + cumulative_),
                (sizeof(receive_buffer_) - cumulative_)),
                boost::bind(&IOFetchTest::tcpReceiveHandler, this, socket, _1, _2));
            return;
        }

        // Check that length of the DNS message received is that expected, then
        // compare buffers, zeroing the QID in the received buffer to match
        // that set in our expected question.  Note that due to the length
        // field the QID in the received buffer is in the third and fourth
        // bytes.
        EXPECT_EQ(msgbuf_->getLength() + 2, cumulative_);
        receive_buffer_[2] = receive_buffer_[3] = 0;
        EXPECT_TRUE(equal((receive_buffer_ + 2), (receive_buffer_ + cumulative_ - 2),
            static_cast<const uint8_t*>(msgbuf_->getData())));

        // ... and return a message back.  This has to be preceded by a two-byte
        // count field.  Construct the message.
        assert(sizeof(send_buffer_) > (sizeof(TEST_DATA) + 2));
        writeUint16(sizeof(TEST_DATA), send_buffer_);
        copy(TEST_DATA, TEST_DATA + sizeof(TEST_DATA) - 1, send_buffer_ + 2);
        send_size_ = sizeof(TEST_DATA) + 2;

        // Send the data.  This is done in multiple writes with a delay between
        // each to check that the reassembly of TCP packets from fragments works.
        send_cumulative_ = 0;
        tcpSendData(socket);
    }

    /// \brief Sent Data Over TCP
    ///
    /// Send the TCP data back to the IOFetch object.  The data is sent in
    /// three chunks - two of 16 bytes and the remainder, with a 250ms gap
    /// between each.
    ///
    /// \param socket Socket over which send should take place
    void tcpSendData(tcp::socket* socket) {
        // Decide what to send based on the cumulative count
        uint8_t* send_ptr = &send_buffer_[send_cumulative_];
                                    // Pointer to data to send
        size_t amount = 16;         // Amount of data to send
        if (send_cumulative_ > 30) {
            amount = send_size_ - send_cumulative_;
        }

        // ... and send it.  The amount sent is also passed as the first argument
        // of the send callback, as a check.
        socket->async_send(asio::buffer(send_ptr, amount),
                           boost::bind(&IOFetchTest::tcpSendHandler, this,
                                       amount, socket, _1, _2));
    }

    /// \brief Completion Handler for Sending TCP data
    ///
    /// Called when the asynchronous send of data back to the IOFetch object
    /// by the TCP "server" in this class has completed.  (This send has to
    /// be asynchronous because control needs to return to the caller in order
    /// for the IOService "run()" method to be called to run the handlers.)
    ///
    /// If not all the data has been sent, a short delay is instigated (during
    /// which control returns to the IOService).  This should force the queued
    /// data to actually be sent and the IOFetch receive handler to be triggered.
    /// In this way, the ability of IOFetch to handle fragmented TCP packets
    /// should be checked.
    ///
    /// \param expected Number of bytes that were expected to have been sent.
    /// \param socket Socket over which the send took place.  Only used to
    ///        pass back to the send method.
    /// \param ec Boost error code, value should be zero.
    /// \param length Number of bytes sent.
    void tcpSendHandler(size_t expected, tcp::socket* socket,
                        error_code ec = error_code(), size_t length = 0)
    {
        EXPECT_EQ(0, ec.value());       // Expect no error
        EXPECT_EQ(expected, length);    // And that amount sent is as expected

        // Do we need to send more?
        send_cumulative_ += length;
        if (send_cumulative_ < send_size_) {

            // Yes - set up a timer:  the callback handler for the timer is
            // tcpSendData, which will then send the next chunk.  We pass the
            // socket over which data should be sent as an argument to that
            // function.
            timer_.expires_from_now(boost::posix_time::milliseconds(SEND_INTERVAL));
            timer_.async_wait(boost::bind(&IOFetchTest::tcpSendData, this,
                                          socket));
        }
    }

    /// \brief Fetch completion callback
    ///
    /// This is the callback's operator() method which is called when the fetch
    /// is complete.  It checks that the data received is the wire format of the
    /// data sent back by the server.
    ///
    /// \param result Result indicated by the callback
    void operator()(IOFetch::Result result) {

        EXPECT_EQ(expected_, result);   // Check correct result returned
        EXPECT_FALSE(run_);             // Check it is run only once
        run_ = true;                    // Note success

        // If the expected result for SUCCESS, then this should have been called
        // when one of the "servers" in this class has sent back the TEST_DATA.
        // Check the data is as expected/
        if (expected_ == IOFetch::SUCCESS) {
            EXPECT_EQ(sizeof(TEST_DATA), result_buff_->getLength());

            const uint8_t* start = static_cast<const uint8_t*>(result_buff_->getData());
            EXPECT_TRUE(equal(TEST_DATA, (TEST_DATA + sizeof(TEST_DATA) - 1),
                              start));
        }

        // ... and cause the run loop to exit.
        service_.stop();
    }

    // The next set of methods are the tests themselves.  A number of the TCP
    // and UDP tests are very similar.

    /// \brief Check for stop()
    ///
    /// Test that when we run the query and stop it after it was run, it returns
    /// "stopped" correctly. (That is why stop() is posted to the service_ as
    /// well instead of calling it.)
    ///
    /// \param protocol Test protocol
    /// \param fetch Fetch object being tested
    void stopTest(IOFetch::Protocol protocol, IOFetch& fetch) {
        protocol_ = protocol;
        expected_ = IOFetch::STOPPED;

        // Post the query
        service_.get_io_service().post(fetch);

        // Post query_.stop() (yes, the boost::bind thing is just
        // query_.stop()).
        service_.get_io_service().post(
            boost::bind(&IOFetch::stop, fetch, IOFetch::STOPPED));

        // Run both of them.  run() returns when everything in the I/O service
        // queue has completed.
        service_.run();
        EXPECT_TRUE(run_);
    }

    /// \brief Premature stop test
    ///
    /// Test that when we queue the query to service_ and call stop() before it
    /// gets executed, it acts sanely as well (eg. has the same result as
    /// running stop() after - calls the callback).
    ///
    /// \param protocol Test protocol
    /// \param fetch Fetch object being tested
    void prematureStopTest(IOFetch::Protocol protocol, IOFetch& fetch) {
        protocol_ = protocol;
        expected_ = IOFetch::STOPPED;

        // Stop before it is started
        fetch.stop();
        service_.get_io_service().post(fetch);

        service_.run();
        EXPECT_TRUE(run_);
    }

    /// \brief Timeout test
    ///
    /// Test that fetch times out when no answer arrives.
    ///
    /// \param protocol Test protocol
    /// \param fetch Fetch object being tested
    void timeoutTest(IOFetch::Protocol protocol, IOFetch& fetch) {
        protocol_ = protocol;
        expected_ = IOFetch::TIME_OUT;

        service_.get_io_service().post(fetch);
        service_.run();
        EXPECT_TRUE(run_);
    }
};

// Check the protocol
TEST_F(IOFetchTest, Protocol) {
    EXPECT_EQ(IOFetch::UDP, udp_fetch_.getProtocol());
    EXPECT_EQ(IOFetch::TCP, tcp_fetch_.getProtocol());
}

// UDP Stop test - see IOFetchTest::stopTest() header.
TEST_F(IOFetchTest, UdpStop) {
    stopTest(IOFetch::UDP, udp_fetch_);
}

// UDP premature stop test - see IOFetchTest::prematureStopTest() header.
TEST_F(IOFetchTest, UdpPrematureStop) {
    prematureStopTest(IOFetch::UDP, udp_fetch_);
}

// UDP premature stop test - see IOFetchTest::timeoutTest() header.
TEST_F(IOFetchTest, UdpTimeout) {
    timeoutTest(IOFetch::UDP, udp_fetch_);
}

// UDP SendReceive test.  Set up a UDP server then ports a UDP fetch object.
// This will send question_ to the server and receive the answer back from it.
TEST_F(IOFetchTest, UdpSendReceive) {
    protocol_ = IOFetch::UDP;
    expected_ = IOFetch::SUCCESS;

    // Set up the server.
    udp::socket socket(service_.get_io_service(), udp::v4());
    socket.set_option(socket_base::reuse_address(true));
    socket.bind(udp::endpoint(TEST_HOST, TEST_PORT));

    udp::endpoint remote;
    socket.async_receive_from(asio::buffer(receive_buffer_, sizeof(receive_buffer_)),
        remote,
        boost::bind(&IOFetchTest::udpReceiveHandler, this, &remote, &socket,
                    _1, _2));
    service_.get_io_service().post(udp_fetch_);
    service_.run();

    socket.close();

    EXPECT_TRUE(run_);;
}

// Do the same tests for TCP transport

TEST_F(IOFetchTest, TcpStop) {
    stopTest(IOFetch::TCP, tcp_fetch_);
}

TEST_F(IOFetchTest, TcpPrematureStop) {
    prematureStopTest(IOFetch::TCP, tcp_fetch_);
}

TEST_F(IOFetchTest, TcpTimeout) {
    timeoutTest(IOFetch::TCP, tcp_fetch_);
}

TEST_F(IOFetchTest, TcpSendReceive) {
    protocol_ = IOFetch::TCP;
    expected_ = IOFetch::SUCCESS;

    // Socket into which the connection will be accepted
    tcp::socket socket(service_.get_io_service());

    // Acceptor object - called when the connection is made, the handler will
    // initiate a read on the socket.
    tcp::acceptor acceptor(service_.get_io_service(),
                           tcp::endpoint(tcp::v4(), TEST_PORT));
    acceptor.async_accept(socket,
        boost::bind(&IOFetchTest::tcpAcceptHandler, this, &socket, _1));

    // Post the TCP fetch object to send the query and receive the response.
    service_.get_io_service().post(tcp_fetch_);

    // ... and execute all the callbacks.  This exits when the fetch completes.
    service_.run();
    EXPECT_TRUE(run_);  // Make sure the callback did execute

    socket.close();
}

} // namespace asiolink
