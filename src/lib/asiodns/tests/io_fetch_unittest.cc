// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <algorithm>
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>

#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/asio.hpp>

#include <util/buffer.h>
#include <util/io_utilities.h>

#include <dns/question.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/name.h>
#include <dns/rcode.h>

#include <asiolink/io_address.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_service.h>
#include <asiodns/io_fetch.h>

using namespace boost::asio;
using namespace isc::dns;
using namespace isc::util;
using namespace boost::asio::ip;
using namespace std;
using namespace isc::asiolink;

namespace isc {
namespace asiodns {

const boost::asio::ip::address TEST_HOST(boost::asio::ip::address::from_string("127.0.0.1"));
const uint16_t TEST_PORT(5301);
const int SEND_INTERVAL = 250;      // Interval in ms between TCP sends
const size_t MAX_SIZE = 64 * 1024;  // Should be able to take 64kB

// The tests are complex, so debug output has been left in (although disabled).
// Set this to true to enable it.
const bool DEBUG = false;

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
    uint8_t         receive_buffer_[MAX_SIZE]; ///< Server receive buffer
    OutputBufferPtr expected_buffer_;          ///< Data we expect to receive
    vector<uint8_t> send_buffer_;           ///< Server send buffer
    uint16_t        send_cumulative_;       ///< Data sent so far

    // Other data.
    string          return_data_;           ///< Data returned by server
    string          test_data_;             ///< Large string - here for convenience
    bool            debug_;                 ///< true to enable debug output
    size_t          tcp_send_size_;         ///< Max size of TCP send
    uint8_t         qid_0;                  ///< First octet of qid
    uint8_t         qid_1;                  ///< Second octet of qid

    bool            tcp_short_send_;        ///< If set to true, we do not send
                                            ///  all data in the tcp response

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
            TEST_PORT, result_buff_, this, (24 * SEND_INTERVAL)),
                                        // Timeout interval chosen to ensure no timeout
        protocol_(IOFetch::TCP),        // for initialization - will be changed
        cumulative_(0),
        timer_(service_.get_io_service()),
        receive_buffer_(),
        expected_buffer_(new OutputBuffer(512)),
        send_buffer_(),
        send_cumulative_(0),
        return_data_(""),
        test_data_(""),
        debug_(DEBUG),
        tcp_send_size_(0),
        qid_0(0),
        qid_1(0),
        tcp_short_send_(false)
    {
        // Construct the data buffer for question we expect to receive.
        Message msg(Message::RENDER);
        msg.setQid(0);
        msg.setOpcode(Opcode::QUERY());
        msg.setRcode(Rcode::NOERROR());
        msg.setHeaderFlag(Message::HEADERFLAG_RD);
        msg.addQuestion(question_);
        EDNSPtr msg_edns(new EDNS());
        msg_edns->setUDPSize(Message::DEFAULT_MAX_EDNS0_UDPSIZE);
        msg.setEDNS(msg_edns);

        MessageRenderer renderer;
        renderer.setBuffer(msgbuf_.get());
        msg.toWire(renderer);
        renderer.setBuffer(NULL);

        renderer.setBuffer(expected_buffer_.get());
        msg.toWire(renderer);
        renderer.setBuffer(NULL);

        // Initialize the test data to be returned: tests will return a
        // substring of this data. (It's convenient to have this as a member of
        // the class.)
        //
        // We could initialize the data with a single character, but as an added
        // check we'll make ssre that it has some structure.

        test_data_.clear();
        test_data_.reserve(MAX_SIZE);
        while (test_data_.size() < MAX_SIZE) {
            test_data_ += "A message to be returned to the client that has "
                          "some sort of structure.";
        }
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
    /// \param bad_qid If set to true, the QID in the response will be mangled
    /// \param second_send If set to true, (and bad_qid is too), after the
    ///        mangled qid response has been sent, a second packet will be
    ///        sent with the correct QID.
    /// \param length Amount of data received.
    void udpReceiveHandler(udp::endpoint* remote, udp::socket* socket,
                           boost::system::error_code ec = boost::system::error_code(),
                           size_t length = 0, bool bad_qid = false,
                           bool second_send = false)
    {
        if (debug_) {
            cout << "udpReceiveHandler(): error = " << ec.value() <<
                    ", length = " << length << endl;
        }

        // The QID in the incoming data is random so set it to 0 for the
        // data comparison check. (It is set to 0 in the buffer containing
        // the expected data.)
        qid_0 = receive_buffer_[0];
        qid_1 = receive_buffer_[1];
        receive_buffer_[0] = receive_buffer_[1] = 0;

        // Check that length of the received data and the expected data are
        // identical, then check that the data is identical as well.
        EXPECT_EQ(msgbuf_->getLength(), length);
        EXPECT_TRUE(equal(receive_buffer_, (receive_buffer_ + length - 1),
        static_cast<const uint8_t*>(msgbuf_->getData())));

        // Return a message back to the IOFetch object.
        if (!bad_qid) {
            expected_buffer_->writeUint8At(qid_0, 0);
            expected_buffer_->writeUint8At(qid_1, 1);
        } else {
            expected_buffer_->writeUint8At(qid_0 + 1, 0);
            expected_buffer_->writeUint8At(qid_1 + 1, 1);
        }
        socket->send_to(boost::asio::buffer(expected_buffer_->getData(), length), *remote);

        if (bad_qid && second_send) {
            expected_buffer_->writeUint8At(qid_0, 0);
            expected_buffer_->writeUint8At(qid_1, 1);
            socket->send_to(boost::asio::buffer(expected_buffer_->getData(),
                            expected_buffer_->getLength()), *remote);
        }
        if (debug_) {
            cout << "udpReceiveHandler(): returned " << expected_buffer_->getLength() <<
                    " bytes to the client" << endl;
        }
    }

    /// \brief Completion Handler for accepting TCP data
    ///
    /// Called when the remote system connects to the "server".  It issues
    /// an asynchronous read on the socket to read data.
    ///
    /// \param socket Socket on which data will be received
    /// \param ec Boost error code, value should be zero.
    void tcpAcceptHandler(tcp::socket* socket,
                          boost::system::error_code ec = boost::system::error_code())
    {
        if (debug_) {
            cout << "tcpAcceptHandler(): error = " << ec.value() << endl;
        }

        // Expect that the accept completed without a problem.
        EXPECT_EQ(0, ec.value());

        // Work out the maximum size of data we can send over it when we
        // respond, then subtract 1kB or so for safety.
        tcp::socket::send_buffer_size send_size;
        socket->get_option(send_size);
        if (send_size.value() < (2 * 1024)) {
            FAIL() << "TCP send size is less than 2kB";
        } else {
            tcp_send_size_ = send_size.value() - 1024;
            if (debug_) {
                cout << "tcpacceptHandler(): will use send size = " << tcp_send_size_ << endl;
            }
        }

        // Initiate a read on the socket.
        cumulative_ = 0;
        socket->async_receive(boost::asio::buffer(receive_buffer_, sizeof(receive_buffer_)),
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
    void tcpReceiveHandler(tcp::socket* socket,
                           boost::system::error_code ec = boost::system::error_code(),
                           size_t length = 0)
    {
        if (debug_) {
            cout << "tcpReceiveHandler(): error = " << ec.value() <<
                    ", length = " << length << endl;
        }
        // Expect that the receive completed without a problem.
        EXPECT_EQ(0, ec.value());

        // If we haven't received all the data, issue another read.
        cumulative_ += length;
        bool complete = false;
        if (cumulative_ > 2) {
            uint16_t dns_length = readUint16(receive_buffer_,
                                             sizeof(receive_buffer_));
            complete = ((dns_length + 2) == cumulative_);
        }

        if (!complete) {
            socket->async_receive(boost::asio::buffer((receive_buffer_ + cumulative_),
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
        qid_0 = receive_buffer_[2];
        qid_1 = receive_buffer_[3];

        receive_buffer_[2] = receive_buffer_[3] = 0;
        EXPECT_TRUE(equal((receive_buffer_ + 2), (receive_buffer_ + cumulative_ - 2),
            static_cast<const uint8_t*>(msgbuf_->getData())));

        // ... and return a message back.  This has to be preceded by a two-byte
        // count field.

        send_buffer_.clear();
        send_buffer_.push_back(0);
        send_buffer_.push_back(0);
        // send_buffer_.capacity() seems more logical below, but the
        // code above fills in the first two bytes and size() becomes 2
        // (sizeof uint16_t).
        writeUint16(return_data_.size(), &send_buffer_[0], send_buffer_.size());
        copy(return_data_.begin(), return_data_.end(), back_inserter(send_buffer_));
        if (return_data_.size() >= 2) {
            send_buffer_[2] = qid_0;
            send_buffer_[3] = qid_1;
        }
        // Send the data.  This is done in multiple writes with a delay between
        // each to check that the reassembly of TCP packets from fragments works.
        send_cumulative_ = 0;
        tcpSendData(socket);
    }

    /// \brief Sent Data Over TCP
    ///
    /// Send the TCP data back to the IOFetch object.  The data is sent in
    /// three chunks - two of 16 bytes and the remainder, with a 250ms gap
    /// between each. (Amounts of data smaller than one 32 bytes are sent in
    /// one or two packets.)
    ///
    /// \param socket Socket over which send should take place
    void tcpSendData(tcp::socket* socket) {
        if (debug_) {
            cout << "tcpSendData()" << endl;
        }

        // Decide what to send based on the cumulative count.  At most we'll do
        // two chunks of 16 bytes (with a 250ms gap between) and then the
        // remainder.
        uint8_t* send_ptr = &send_buffer_[send_cumulative_];
                                    // Pointer to data to send
        size_t amount = 16;         // Amount of data to send
        if (send_cumulative_ < (2 * amount)) {
            
            // First or second time through, send at most 16 bytes
            amount = min(amount, (send_buffer_.size() - send_cumulative_));

        } else {

            // For all subsequent times, send the remainder, maximised to
            // whatever we have chosen for the maximum send size.
            amount = min(tcp_send_size_,
                        (send_buffer_.size() - send_cumulative_));
        }

        // This is for the short send test; reduce the actual amount of
        // data we send
        if (tcp_short_send_) {
            if (debug_) {
                cout << "tcpSendData(): sending incomplete data (" <<
                        (amount - 1) << " of " << amount << " bytes)" <<
                        endl;
            }
            --amount;
        } else {
            if (debug_) {
                cout << "tcpSendData(): sending " << amount << " bytes" << endl;
            }
        }

        // ... and send it.  The amount sent is also passed as the first
        // argument of the send callback, as a check.
        socket->async_send(boost::asio::buffer(send_ptr, amount),
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
                        boost::system::error_code ec = boost::system::error_code(),
                        size_t length = 0)
    {
        if (debug_) {
            cout << "tcpSendHandler(): error = " << ec.value() <<
                    ", length = " << length << endl;
        }

        EXPECT_EQ(0, ec.value());       // Expect no error
        EXPECT_EQ(expected, length);    // And that amount sent is as expected

        // Do we need to send more?
        send_cumulative_ += length;
        if (send_cumulative_ < send_buffer_.size()) {

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
        if (debug_) {
            cout << "operator()(): result = " << result << endl;
        }

        EXPECT_EQ(expected_, result);   // Check correct result returned
        EXPECT_FALSE(run_);             // Check it is run only once
        run_ = true;                    // Note success

        // If the expected result for SUCCESS, then this should have been called
        // when one of the "servers" in this class has sent back return_data_.
        // Check the data is as expected/
        if (expected_ == IOFetch::SUCCESS) {
            // In the case of UDP, we actually send back a real looking packet
            // in the case of TCP, we send back a 'random' string
            if (protocol_ == IOFetch::UDP) {
                EXPECT_EQ(expected_buffer_->getLength(), result_buff_->getLength());
                EXPECT_EQ(0, memcmp(expected_buffer_->getData(), result_buff_->getData(),
                          expected_buffer_->getLength()));
            } else {
                EXPECT_EQ(return_data_.size(), result_buff_->getLength());
                // Overwrite the random qid with our own data for the
                // comparison to succeed
                if (result_buff_->getLength() >= 2) {
                    result_buff_->writeUint8At(return_data_[0], 0);
                    result_buff_->writeUint8At(return_data_[1], 1);
                }
                const uint8_t* start = static_cast<const uint8_t*>(result_buff_->getData());
                EXPECT_TRUE(equal(return_data_.begin(), return_data_.end(), start));
            }
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

    /// \brief Send/Receive Test
    ///
    /// Send a query to the server then receives a response.
    ///
    /// \param Test data to return to client
    /// \param short_send If true, do not send all data
    ///                   (should result in timeout)
    void tcpSendReturnTest(const std::string& return_data, bool short_send = false) {
        if (debug_) {
            cout << "tcpSendReturnTest(): data size = " << return_data.size() << endl;
        }
        return_data_ = return_data;
        protocol_ = IOFetch::TCP;
        if (short_send) {
            tcp_short_send_ = true;
            expected_ = IOFetch::TIME_OUT;
        } else {
            expected_ = IOFetch::SUCCESS;
        }

        // Socket into which the connection will be accepted.
        tcp::socket socket(service_.get_io_service());

        // Acceptor object - called when the connection is made, the handler
        // will initiate a read on the socket.
        tcp::acceptor acceptor(service_.get_io_service(),
                               tcp::endpoint(tcp::v4(), TEST_PORT));
        acceptor.async_accept(socket,
            boost::bind(&IOFetchTest::tcpAcceptHandler, this, &socket, _1));

        // Post the TCP fetch object to send the query and receive the response.
        service_.get_io_service().post(tcp_fetch_);

        // ... and execute all the callbacks.  This exits when the fetch
        // completes.
        service_.run();
        EXPECT_TRUE(run_);  // Make sure the callback did execute

        // Tidy up
        socket.close();
    }

    /// Perform a send/receive test over UDP
    ///
    /// \param bad_qid If true, do the test where the QID is mangled
    ///                in the response
    /// \param second_send If true, do the test where the QID is
    ///                    mangled in the response, but a second
    ///                    (correct) packet is used
    void udpSendReturnTest(bool bad_qid, bool second_send) {
        protocol_ = IOFetch::UDP;

        // Set up the server.
        udp::socket socket(service_.get_io_service(), udp::v4());
        socket.set_option(socket_base::reuse_address(true));
        socket.bind(udp::endpoint(TEST_HOST, TEST_PORT));
        return_data_ = "Message returned to the client";

        udp::endpoint remote;
        socket.async_receive_from(boost::asio::buffer(receive_buffer_,
                                               sizeof(receive_buffer_)),
                                  remote,
                                  boost::bind(&IOFetchTest::udpReceiveHandler,
                                              this, &remote, &socket,
                                              _1, _2, bad_qid, second_send));
        service_.get_io_service().post(udp_fetch_);
        if (debug_) {
            cout << "udpSendReceive: async_receive_from posted,"
                "waiting for callback" << endl;
        }
        service_.run();

        socket.close();

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
    expected_ = IOFetch::SUCCESS;

    udpSendReturnTest(false, false);

    EXPECT_TRUE(run_);;
}

TEST_F(IOFetchTest, UdpSendReceiveBadQid) {
    expected_ = IOFetch::TIME_OUT;

    udpSendReturnTest(true, false);

    EXPECT_TRUE(run_);;
}

TEST_F(IOFetchTest, UdpSendReceiveBadQidResend) {
    expected_ = IOFetch::SUCCESS;

    udpSendReturnTest(true, true);

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

// Test with values at or near 2, then at or near the chunk size (16 and 32
// bytes, the sizes of the first two packets) then up to 65535.  These are done
// in separate tests because in practice a new IOFetch is created for each
// query/response exchange and we don't want to confuse matters in the test
// by running the test with an IOFetch that has already done one exchange.
//
// Don't do 0 or 1; the server would not accept the packet
// (since the length is too short to check the qid)
TEST_F(IOFetchTest, TcpSendReceive2) {
    tcpSendReturnTest(test_data_.substr(0, 2));
}

TEST_F(IOFetchTest, TcpSendReceive3) {
    tcpSendReturnTest(test_data_.substr(0, 3));
}

TEST_F(IOFetchTest, TcpSendReceive15) {
    tcpSendReturnTest(test_data_.substr(0, 15));
}

TEST_F(IOFetchTest, TcpSendReceive16) {
    tcpSendReturnTest(test_data_.substr(0, 16));
}

TEST_F(IOFetchTest, TcpSendReceive17) {
    tcpSendReturnTest(test_data_.substr(0, 17));
}

TEST_F(IOFetchTest, TcpSendReceive31) {
    tcpSendReturnTest(test_data_.substr(0, 31));
}

TEST_F(IOFetchTest, TcpSendReceive32) {
    tcpSendReturnTest(test_data_.substr(0, 32));
}

TEST_F(IOFetchTest, TcpSendReceive33) {
    tcpSendReturnTest(test_data_.substr(0, 33));
}

TEST_F(IOFetchTest, TcpSendReceive4096) {
    tcpSendReturnTest(test_data_.substr(0, 4096));
}

TEST_F(IOFetchTest, TcpSendReceive8192) {
    tcpSendReturnTest(test_data_.substr(0, 8192));
}

TEST_F(IOFetchTest, TcpSendReceive16384) {
    tcpSendReturnTest(test_data_.substr(0, 16384));
}

TEST_F(IOFetchTest, TcpSendReceive32768) {
    tcpSendReturnTest(test_data_.substr(0, 32768));
}

TEST_F(IOFetchTest, TcpSendReceive65535) {
    tcpSendReturnTest(test_data_.substr(0, 65535));
}

TEST_F(IOFetchTest, TcpSendReceive2ShortSend) {
    tcpSendReturnTest(test_data_.substr(0, 2), true);
}

TEST_F(IOFetchTest, TcpSendReceive15ShortSend) {
    tcpSendReturnTest(test_data_.substr(0, 15), true);
}

TEST_F(IOFetchTest, TcpSendReceive8192ShortSend) {
    tcpSendReturnTest(test_data_.substr(0, 8192), true);
}


} // namespace asiodns
} // namespace isc
