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

/// RecursiveQuery Test - 2
///
/// The second part of the RecursiveQuery unit tests, this attempts to get the
/// RecursiveQuery object to follow a set of referrals for "www.example.org" to
/// and to invoke TCP fallback on one of the queries.  In particular, we
/// expect that the test will do the following in an attempt to resolve
/// www.example.org:
///
/// - Send a question over UDP to the root servers - get referral to "org".
/// - Send question over UDP to "org" - get referral to "example.org" with TC bit set.
/// - Send question over TCP to "org" - get referral to "example.org".
/// - Send question over UDP to "example.org" - get response for www.example.org.
///
/// The order of queries is partly to test that after there is a fallover to TCP,
/// queries revert to UDP.
///
/// By using the "test_server_" element of RecursiveQuery, all queries are
/// directed to one or other of the "servers" in the RecursiveQueryTest2 class.

namespace asiolink {

const asio::ip::address TEST_HOST(asio::ip::address::from_string("127.0.0.1"));
const uint16_t TEST_PORT(5301);


/// \brief Test fixture for the asiolink::IOFetch.
class RecursiveQueryTest2 : public virtual ::testing::Test, public virtual IOFetch::Callback
{
public:

    /// \brief Status of query
    ///
    /// Set before the query and then by each "server" when responding.
    enum QueryStatus {
        NONE = 0,                   ///< Default
        UDP_ROOT = 1,               ///< Query root server over UDP
        UDP_ORG = 2,                ///< Query ORG server over UDP
        TCP_ORG = 3,                ///< Query ORG server over TCP
        UDP_EXAMPLE_ORG = 4,        ///< Query EXAMPLE.ORG server over UDP
        COMPLETE = 5                ///< Query is complete
    };

    IOService       service_;                   ///< Service to run everything
    Question        question_;                  ///< What to ask
    QueryStatus     last_;                      ///< Last state
    QueryStatus     expected_;                  ///< Expected next state
    OutputBufferPtr question_buffer_;           ///< Question we expect to receive

    size_t          tcp_cumulative_;            ///< Cumulative TCP data received
    tcp::endpoint   tcp_endpoint_;              ///< Endpoint for TCP receives
    size_t          tcp_length_;                ///< Expected length value
    uint8_t         tcp_receive_buffer_[512];   ///< Receive buffer for TCP I/O
    OutputBufferPtr tcp_send_buffer_;           ///< Send buffer for TCP I/O
    tcp::socket     tcp_socket_;                ///< Socket used by TCP server

    /// Data for UDP
    udp::endpoint   udp_endpoint_;              ///< Endpoint for UDP receives
    size_t          udp_length_;                ///< Expected length value
    uint8_t         udp_receive_buffer_[512];   ///< Receive buffer for UDP I/O
    OutputBufferPtr udp_send_buffer_;           ///< Send buffer for UDP I/O
    udp::socket     udp_socket_;                ///< Socket used by UDP server


    /// \brief Constructor
    RecursiveQueryTest2() :
        service_(),
        question_(Name("www.example.org"), RRClass::IN(), RRType::A()),
        last_(NONE),
        expected_(NONE),
        question_buffer_(),
        tcp_cumulative_(0),
        tcp_endpoint_(TEST_HOST, TEST_PORT),
        tcp_length_(0),
        tcp_receive_buffer_(),
        tcp_send_buffer_(),
        tcp_socket_(service_.get_io_service()),
        udp_endpoint_(),
        udp_length_(0),
        udp_receive_buffer_(),
        udp_send_buffer_(),
        udp_socket_(service_.get_io_service(), udp::v4())
    {

    }


    /// \brief Set Common Message Bits
    ///
    /// Sets up the common bits of a response message returned by the handlers.
    ///
    /// \param msg Message buffer in RENDER mode.
    /// \param qid QIT to set the message to
    void setCommonMessage(isc::dns::Message& msg, uint16_t qid = 0) {
        msg.setQid(qid);
        msg.setHeaderFlag(Message::HEADERFLAG_QR);
        msg.setOpcode(Opcode::QUERY());
        msg.setHeaderFlag(Message::HEADERFLAG_AA);
        msg.setRcode(Rcode::NOERROR());
        msg.addQuestion(question_);
    }

    /// \brief Set Referral to "org"
    ///
    /// Sets up the passed-in message (expected to be in "RENDER" mode to
    /// indicate a referral to fictitious .org nameservers.
    ///
    /// \param msg Message to update with referral information.
    void setReferralOrg(isc::dns::Message& msg) {

        // Do a referral to org.  We'll define all NS records as "in-zone"
        // nameservers (and so supply glue) to avoid the possibility of
        // the resolver doing another lookup.
        RRSetPtr org_ns(new RRSet(Name("org."), RRClass::IN(), RRType::NS(), RRTTL(300)));
        org_ns->addRdata(NS("ns1.org."));
        org_ns->addRdata(NS("ns2.org."));
        msg.addRRset(Message::SECTION_AUTHORITY, org_ns);

        RRsetPtr org_ns1(new RRSet(Name("ns1.org."), RRClass::IN(), RRType::A(), RRTTL(300)));
        org_ns1->addRdata(A("192.0.2.1"));
        msg.addRRset(Message::SECTION_ADDITIONAL, org_ns1);

        RRsetPtr org_ns1(new RRSet(Name("ns2.org."), RRClass::IN(), RRType::A(), RRTTL(300)));
        org_ns2->addRdata(A("192.0.2.2"));
        msg.addRRset(Message::SECTION_ADDITIONAL, org_ns2);
    }

    /// \brief Set Referral to "example.org"
    ///
    /// Sets up the passed-in message (expected to be in "RENDER" mode to
    /// indicate a referral to fictitious example.org nameservers.
    ///
    /// \param msg Message to update with referral information.
    void setReferralExampleOrg(isc::dns::Message& msg) {

        // Do a referral to example.org.  As before, we'll define all NS
        // records as "in-zone" nameservers (and so supply glue) to avoid
        // the possibility of the resolver doing another lookup.
        RRSetPtr example_org_ns(new RRSet(Name("example.org."), RRClass::IN(), RRType::NS(), RRTTL(300)));
        example_org_ns->addRdata(NS("ns1.example.org."));
        example_org_ns->addRdata(NS("ns2.example.org."));
        msg.addRRset(Message::SECTION_AUTHORITY, example_org_ns);

        RRsetPtr example_org_ns1(new RRSet(Name("ns1.example.org."), RRClass::IN(), RRType::A(), RRTTL(300)));
        example_org_ns1->addRdata(A("192.0.2.11"));
        msg.addRRset(Message::SECTION_ADDITIONAL, example_org_ns1);

        RRsetPtr org_ns1(new RRSet(Name("ns2.example.org."), RRClass::IN(), RRType::A(), RRTTL(300)));
        example_org_ns2->addRdata(A("192.0.2.12"));
        msg.addRRset(Message::SECTION_ADDITIONAL, example_org_ns2);
    }

    /// \brief Set Answer to "www.example.org"
    ///
    /// Sets up the passed-in message (expected to be in "RENDER" mode to
    /// indicate an authoritative answer to www.example.org.
    ///
    /// \param msg Message to update with referral information.
    void setAnswerWwwExampleOrg(isc::dns::Message& msg) {

        // Give a response for www.example.org.
        RRsetPtr www_example_org_a(new RRSet(Name("www.example.org."), RRClass::IN(), RRType::NS(), RRTTL(300)));
        www_example_org_a->addRdata(A("192.0.2.21"));
        msg.addRRset(Message::SECTION_ANSWER, example_org_ns);

        // ... and add the Authority and Additional sections. (These are the
        // same as in the referral to example.org from the .org nameserver.)
        setReferralExampleOrg(msg);
    }

    /// \brief UDP Receive Handler
    ///
    /// This is invoked when a message is received from the RecursiveQuery
    /// Object.  It formats an answer and sends it, with the UdpSendHandler
    /// method being specified as the completion handler.
    ///
    /// \param remote Endpoint to which to send the answer
    /// \param socket Socket to use to send the answer
    /// \param ec ASIO error code, completion code of asynchronous I/O issued
    ///        by the "server" to receive data.
    /// \param length Amount of data received.
    void udpReceiveHandler(error_code ec = error_code(), size_t length = 0) {

        // Expected state should be one greater than the last state.
        EXPECT_EQ(static_cast<int>(expected_), static_cast<int>(last_) + 1);
        last_ = expected_;

        // The QID in the incoming data is random so set it to 0 for the
        // data comparison check. (It is set to 0 in the buffer containing
        // the expected data.)
        uint16_t qid = readUint16(udp_receive_buffer_);
        udp_receive_buffer_[0] = udp_receive_buffer_[1] = 0;

        // Check that length of the received data and the expected data are
        // identical, then check that the data is identical as well.
        EXPECT_EQ(question_buff_->getLength(), length);
        EXPECT_TRUE(equal(udp_receive_buffer_, (udp_receive_buffer_ + length - 1),
                    static_cast<const uint8_t*>(question_buff_->getData())));

        // The message returned depends on what state we are in.  Set up
        // common stuff first: bits not mentioned are set to 0.
        Message msg(Message::RENDER);
        setCommonMessage(msg, qid);

        // Set up state-dependent bits:
        switch (expected_) {
        case UDP_ROOT:
            // Return a referral to org.  We then expect to query the "org"
            // nameservers over UDP next.
            setReferralOrg(msg);
            expected_ = UDP_ORG;
            break;

         case UDP_ORG:
            // Return a referral to example.org.  We explicitly set the TC bit to
            // force a repeat query to the .org nameservers over TCP.
            setReferralExampleOrg(msg);
            msg.setHeaderFlag(Message::HEADERFLAG_TC);
            expected_ = TCP_ORG;
            break;

         case UDP_EXAMPLE_ORG:
            // Return the answer to the question.
            setAnswerWwwExampleOrg(msg);
            expected_ = COMPLETE;
            break;

         default:
            FAIL() << "UdpReceiveHandler called with unknown state";
        }

        // Convert to wire format
        MessageRenderer renderer(*udp_send_buffer_);
        msg.toWire(renderer);

        // Return a message back to the IOFetch object.
        udp_socket_.send_to(asio::buffer(udp_send_buffer_.getData(),
                                         udp_send_buffer_.getLength()),
                            boost::bind(&RecursiveQueryTest2::UdpSendHandler,
                                        this, _1, _2));

        // Set the expected length for the send handler.
        udp_length_ = udp_send_buffer_.getLength();
    }

    /// \brief UDP Send Handler
    ///
    /// Called when a send operation of the UDP server (i.e. a response
    /// being sent to the RecursiveQuery) has completed, this re-issues
    /// a read call.
    void udpSendHandler(error_code ec = error_code(), size_t length = 0) {

        // Check send was OK
        EXPECT_EQ(0, ec.value());
        EXPECT_EQ(udp_length_, length);

        // Reissue the receive.
        udp_socket_.async_receive_from(
            asio::buffer(udp_receive_buffer_, sizeof(udp_receive_buffer_)),
                udp_endpoint_
                boost::bind(&recursiveQuery2::udpReceiveHandler, this, _1, _2));
    }

    /// \brief Completion Handler for Accepting TCP Data
    ///
    /// Called when the remote system connects to the "server".  It issues
    /// an asynchronous read on the socket to read data.
    ///
    /// \param socket Socket on which data will be received
    /// \param ec Boost error code, value should be zero.
    void tcpAcceptHandler(error_code ec = error_code(), size_t length = 0)
    {
        // Expect that the accept completed without a problem.
        EXPECT_EQ(0, ec.value());

        // Initiate a read on the socket, indicating that nothing has yet been
        // received.
        tcp_cumulative_ = 0;
        tcp_socket_.async_receive(
            asio::buffer(tcp_receive_buffer_, sizeof(tcp_receive_buffer_)),
            boost::bind(&recursiveQuery2::tcpReceiveHandler, this, _1, _2));
    }

    /// \brief Completion Handler for Receiving TCP Data
    ///
    /// Reads data from the RecursiveQuery object and loops, reissuing reads,
    /// until all the message has been read.  It then sends
    ///
    /// \param socket Socket to use to send the answer
    /// \param ec ASIO error code, completion code of asynchronous I/O issued
    ///        by the "server" to receive data.
    /// \param length Amount of data received.
    void tcpReceiveHandler(error_code ec = error_code(), size_t length = 0)
    {
        // Expect that the receive completed without a problem.
        EXPECT_EQ(0, ec.value());

        // Have we received all the data?  We know this by checking if the two-
        // byte length count in the message is equal to the data received.
        tcp_cumulative_ += length;
        bool complete = false;
        if (tcp_cumulative_ > 2) {
            uint16_t dns_length = readUint16(tcp_receive_buffer_);
            complete = ((dns_length + 2) == tcp_cumulative_);
        }

        if (!complete) {

            // Not complete yet, issue another read.
            tcp_socket_.async_receive(
                asio::buffer(tcp_receive_buffer_ + tcp_cumulative_,
                             sizeof(tcp_receive_buffer_) - tcp_cumulative_),
                boost::bind(&recursiveQuery2::tcpReceiveHandler, this, _1, _2));
            return;
        }

        // Have received a TCP message.  Expected state should be one greater
        // than the last state.
        EXPECT_EQ(static_cast<int>(expected_), static_cast<int>(last_) + 1);
        last_ = expected_;

        // Check that length of the received data and the expected data are
        // identical (taking into account the two-byte count), then check that
        // the data is identical as well (after zeroing the QID).
        EXPECT_EQ(question_buff_->getLength() + 2, tcp_cumulative_);
        uint16_t qid = readUint16(&udp_receive_buffer_[2]);
        tcp_receive_buffer_[2] = tcp_receive_buffer_[3] = 0;
        EXPECT_TRUE(equal((tcp_receive_buffer_ + 2),
                          (tcp_receive_buffer_ + tcp_cumulative_),
                           static_cast<const uint8_t*>(question_buff_->getData())));


        // Return a message back.  This is a referral to example.org, which
        // should result in another query over UDP.
        Message msg(Message::RENDER);
        setCommonMessage(msg, qid);
        setReferralExampleOrg(msg);

        // Convert to wire format
        MessageRenderer renderer(*tcp_send_buffer_);
        msg.toWire(renderer);
        
        // Expected next state (when checked) is the UDP query to example.org.
        expected_ = UDP_EXAMPLE_ORG;
        
        // We'll write the message in two parts, the count and the message
        // itself.  When specifying the send handler, the expected size of the
        // data written is passed as the first parameter.
        uint8_t count[2];
        writeUint16(tcp_send_buffer_->getLength(), count);
        socket->async_send(asio::buffer(count, 2),
                           boost::bind(&IOFetchTest::tcpSendHandler, this,
                                       2, _1, _2));
        socket->async_send(asio::buffer(tcp_send_buffer_->getData(),
                                        tcp_send_buffer_->getLength()),
                           boost::bind(&RecursiveQuery2::tcpSendHandler, this,
                                       sizeof(TEST_DATA), _1, _2));
    }

    /// \brief Completion Handler for Sending TCP data
    ///
    /// Called when the asynchronous send of data back to the RecursiveQuery
    /// by the TCP "server" in this class has completed.  (This send has to
    /// be asynchronous because control needs to return to the caller in order
    /// for the IOService "run()" method to be called to run the handlers.)
    ///
    /// \param expected Number of bytes that were expected to have been sent.
    /// \param ec Boost error code, value should be zero.
    /// \param length Number of bytes sent.
    void tcpSendHandler(size_t expected = 0, error_code ec = error_code(),
                        size_t length = 0)
    {
        EXPECT_EQ(0, ec.value());       // Expect no error
        EXPECT_EQ(expected, length);    // And that amount sent is as expected
    }

    /// \brief Resolver Callback Completion
    ///
    /// This is the callback's operator() method which is called when the 
    /// resolution of the query is complete.  It checks that the data received
    /// is the wire format of the data sent back by the server.
    ///
    /// \param result Result indicated by the callback
    void operator()(IOFetch::Result result) {

        EXPECT_EQ(COMPLETE, expected_);
        /*
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
         * */
        service_.stop();
    }

// Sets up the UDP and TCP "servers", then tries a resolution.

TEST_F(RecursiveQueryTest2, Resolve) {

    // Set the state of the 
    // Set up the UDP server and issue the first read.
    udp_socket_.set_option(socket_base::reuse_address(true));
    udp_socket_.bind(udp::endpoint(TEST_HOST, TEST_PORT));
    udp_socket.async_receive_from(asio::buffer(server_buff_, sizeof(server_buff_)),
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
