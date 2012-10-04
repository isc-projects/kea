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
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <boost/bind.hpp>

#include <asio.hpp>

#include <util/buffer.h>
#include <util/io_utilities.h>

#include <dns/question.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/name.h>
#include <dns/rcode.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>

#include <util/io_utilities.h>
#include <asiodns/dns_service.h>
#include <asiodns/io_fetch.h>
#include <asiolink/io_address.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_service.h>
#include <resolve/recursive_query.h>
#include <resolve/resolver_interface.h>

using namespace asio;
using namespace asio::ip;
using namespace isc::asiolink;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::util;
using namespace isc::resolve;
using namespace std;

/// RecursiveQuery Test - 3
///
/// The second part of the RecursiveQuery unit tests, this attempts to get the
/// RecursiveQuery object to follow a set of EDNS-induced errors, causing the
/// resolver to follow the fallback logic.
///
/// - Send EDNS question over UDP - get FORMERR
/// - Send EDNS question over TCP - get FORMERR
/// - Send non-EDNS question over UDP - get RESPONSE
///
/// By using the "test_server_" element of RecursiveQuery, all queries are
/// directed to one or other of the "servers" in the RecursiveQueryTest3 class.

namespace isc {
namespace asiodns {

const char* TEST_ADDRESS3 = "127.0.0.1";      ///< Servers are on this address
const uint16_t TEST_PORT3 = 5303;             ///< ... and this port
const size_t BUFFER_SIZE = 1024;              ///< For all buffers

const char* DUMMY_ADDR3 = "1.2.3.4";          ///< address to return as A

class MockResolver3 : public isc::resolve::ResolverInterface {
public:
    virtual void resolve(const QuestionPtr& question,
                 const ResolverInterface::CallbackPtr& callback) {
    }

    virtual ~MockResolver3() {}
};



/// \brief Test fixture for the RecursiveQuery Test
class RecursiveQueryTest3 : public virtual ::testing::Test
{
public:

    /// \brief Status of query
    ///
    /// Set before the query and then by each "server" when responding.
    enum QueryStatus {
        NONE = 0,                   ///< Default
        EDNS_UDP = 1,               ///< EDNS query over UDP
        NON_EDNS_UDP = 2,           ///< Non-EDNS query over UDP
        COMPLETE = 6                ///< Query is complete
    };

    // Common stuff
    IOService       service_;                   ///< Service to run everything
    DNSService      dns_service_;               ///< Resolver is part of "server"
    QuestionPtr     question_;                  ///< What to ask
    QueryStatus     last_;                      ///< What was the last state
    QueryStatus     expected_;                  ///< Expected next state
    OutputBufferPtr question_buffer_;           ///< Question we expect to receive
    boost::shared_ptr<MockResolver3> resolver_;  ///< Mock resolver
    isc::nsas::NameserverAddressStore* nsas_;   ///< Nameserver address store
    isc::cache::ResolverCache cache_;           ///< Resolver cache

    // Data for TCP Server
    size_t          tcp_cumulative_;            ///< Cumulative TCP data received
    tcp::endpoint   tcp_endpoint_;              ///< Endpoint for TCP receives
    size_t          tcp_length_;                ///< Expected length value
    uint8_t         tcp_receive_buffer_[BUFFER_SIZE];   ///< Receive buffer for TCP I/O
    OutputBufferPtr tcp_send_buffer_;           ///< Send buffer for TCP I/O
    tcp::socket     tcp_socket_;                ///< Socket used by TCP server

    /// Data for UDP
    udp::endpoint   udp_remote_;                ///< Endpoint for UDP receives
    size_t          udp_length_;                ///< Expected length value
    uint8_t         udp_receive_buffer_[BUFFER_SIZE];   ///< Receive buffer for UDP I/O
    OutputBufferPtr udp_send_buffer_;           ///< Send buffer for UDP I/O
    udp::socket     udp_socket_;                ///< Socket used by UDP server

    /// \brief Constructor
    RecursiveQueryTest3() :
        service_(),
        dns_service_(service_, NULL, NULL, NULL),
        question_(new Question(Name("ednsfallback"),
                  RRClass::IN(), RRType::A())),
        last_(NONE),
        expected_(NONE),
        question_buffer_(new OutputBuffer(BUFFER_SIZE)),
        resolver_(new MockResolver3()),
        nsas_(new isc::nsas::NameserverAddressStore(resolver_)),
        tcp_cumulative_(0),
        tcp_endpoint_(asio::ip::address::from_string(TEST_ADDRESS3),
                      TEST_PORT3),
        tcp_length_(0),
        tcp_receive_buffer_(),
        tcp_send_buffer_(new OutputBuffer(BUFFER_SIZE)),
        tcp_socket_(service_.get_io_service()),
        udp_remote_(),
        udp_length_(0),
        udp_receive_buffer_(),
        udp_send_buffer_(new OutputBuffer(BUFFER_SIZE)),
        udp_socket_(service_.get_io_service(), udp::v4())
    {
    }

    /// \brief Set Common Message Bits
    ///
    /// Sets up the common bits of a response message returned by the handlers.
    ///
    /// \param message Message buffer in RENDER mode.
    /// \param qid QID to set the message to
    void setCommonMessage(isc::dns::Message& message, uint16_t qid) {
        message.setQid(qid);
        message.setHeaderFlag(Message::HEADERFLAG_QR);
        message.setOpcode(Opcode::QUERY());
        message.setHeaderFlag(Message::HEADERFLAG_AA);
        message.addQuestion(*question_);
    }

    /// \brief Set FORMERR answer
    ///
    /// \param message Message to update with FORMERR status
    void setFORMERR(isc::dns::Message& message) {
        message.setRcode(Rcode::FORMERR());
    }

    /// \brief Set Answer
    ///
    /// \param message Message to update with FORMERR status
    void setAnswer(isc::dns::Message& message) {
        // Give a response
        RRsetPtr answer(new RRset(Name("ednsfallback."), RRClass::IN(),
                        RRType::A(), RRTTL(300)));
        answer->addRdata(createRdata(RRType::A(), RRClass::IN(), DUMMY_ADDR3));
        message.addRRset(Message::SECTION_ANSWER, answer);
        message.setRcode(Rcode::NOERROR());
    }

    /// \brief UDP Receive Handler
    ///
    /// This is invoked when a message is received over UDP from the
    /// RecursiveQuery object under test.  It formats an answer and sends it
    /// asynchronously, with the UdpSendHandler method being specified as the
    /// completion handler.
    ///
    /// \param ec ASIO error code, completion code of asynchronous I/O issued
    ///        by the "server" to receive data.
    /// \param length Amount of data received.
    void udpReceiveHandler(error_code ec = error_code(), size_t length = 0) {
        // Expected state should be one greater than the last state.
        EXPECT_EQ(static_cast<int>(expected_), static_cast<int>(last_) + 1);
        last_ = expected_;

        Message query(Message::PARSE);

        // The QID in the incoming data is random so set it to 0 for the
        // data comparison check. (It is set to 0 in the buffer containing
        // the expected data.)
        // And check that question we received is what was expected.
        checkReceivedPacket(udp_receive_buffer_, length, query);

        // The message returned depends on what state we are in.  Set up
        // common stuff first: bits not mentioned are set to 0.
        Message message(Message::RENDER);
        setCommonMessage(message, query.getQid());

        // Set up state-dependent bits:
        switch (expected_) {
        case EDNS_UDP:
            EXPECT_TRUE(query.getEDNS());
            // Return FORMERROR
            setFORMERR(message);
            expected_ = NON_EDNS_UDP;
            break;

        case NON_EDNS_UDP:
            EXPECT_FALSE(query.getEDNS());
            // Return the answer to the question.
            setAnswer(message);
            expected_ = COMPLETE;
            break;

         default:
            FAIL() << "UdpReceiveHandler called with unknown state";
        }

        // Convert to wire format
        udp_send_buffer_->clear();
        MessageRenderer renderer;
        renderer.setBuffer(udp_send_buffer_.get());
        message.toWire(renderer);
        renderer.setBuffer(NULL);

        // Return a message back to the IOFetch object (after setting the
        // expected length of data for the check in the send handler).
        udp_length_ = udp_send_buffer_->getLength();
        udp_socket_.async_send_to(asio::buffer(udp_send_buffer_->getData(),
                                               udp_send_buffer_->getLength()),
                                  udp_remote_,
                              boost::bind(&RecursiveQueryTest3::udpSendHandler,
                                              this, _1, _2));
    }

    /// \brief UDP Send Handler
    ///
    /// Called when a send operation of the UDP server (i.e. a response
    /// being sent to the RecursiveQuery) has completed, this re-issues
    /// a read call.
    ///
    /// \param ec Completion error code of the send.
    /// \param length Actual number of bytes sent.
    void udpSendHandler(error_code ec = error_code(), size_t length = 0) {
        // Check send was OK
        EXPECT_EQ(0, ec.value());
        EXPECT_EQ(udp_length_, length);

        // Reissue the receive call to await the next message.
        udp_socket_.async_receive_from(
            asio::buffer(udp_receive_buffer_, sizeof(udp_receive_buffer_)),
            udp_remote_,
            boost::bind(&RecursiveQueryTest3::udpReceiveHandler,
                        this, _1, _2));
    }

    /// \brief Completion Handler for Accepting TCP Data
    ///
    /// Called when the remote system connects to the "TCP server".  It issues
    /// an asynchronous read on the socket to read data.
    ///
    /// \param socket Socket on which data will be received
    /// \param ec Boost error code, value should be zero.
    void tcpAcceptHandler(error_code ec = error_code(), size_t length = 0) {
        // Expect that the accept completed without a problem.
        EXPECT_EQ(0, ec.value());

        // Initiate a read on the socket, indicating that nothing has yet been
        // received.
        tcp_cumulative_ = 0;
        tcp_socket_.async_receive(
            asio::buffer(tcp_receive_buffer_, sizeof(tcp_receive_buffer_)),
            boost::bind(&RecursiveQueryTest3::tcpReceiveHandler, this, _1, _2));
    }

    /// \brief Completion Handler for Receiving TCP Data
    ///
    /// Reads data from the RecursiveQuery object and loops, reissuing reads,
    /// until all the message has been read.  It then returns an appropriate
    /// response.
    ///
    /// \param socket Socket to use to send the answer
    /// \param ec ASIO error code, completion code of asynchronous I/O issued
    ///        by the "server" to receive data.
    /// \param length Amount of data received.
    void tcpReceiveHandler(error_code ec = error_code(), size_t length = 0) {
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
                boost::bind(&RecursiveQueryTest3::tcpReceiveHandler,
                            this, _1, _2));
            return;
        }

        // Have received a TCP message.  Expected state should be one greater
        // than the last state.
        EXPECT_EQ(static_cast<int>(expected_), static_cast<int>(last_) + 1);
        last_ = expected_;

        Message query(Message::PARSE);

        // Check that question we received is what was expected.  Note that we
        // have to ignore the two-byte header in order to parse the message.
        checkReceivedPacket(tcp_receive_buffer_ + 2, length - 2, query);

        // Return a message back.  This is a referral to example.org, which
        // should result in another query over UDP.  Note the setting of the
        // QID in the returned message with what was in the received message.
        Message message(Message::RENDER);
        setCommonMessage(message, query.getQid());

        // Set up state-dependent bits:
        switch (expected_) {
        default:
            FAIL() << "TcpReceiveHandler called with unknown state";
        }


        // Convert to wire format
        // Use a temporary buffer for the dns wire data (we copy it
        // to the 'real' buffer below)
        MessageRenderer renderer;
        message.toWire(renderer);

        // Also, take this opportunity to clear the accumulated read count in
        // readiness for the next read. (If any - at present, there is only
        // one read in the test, although extensions to this test suite could
        // change that.)
        tcp_cumulative_ = 0;

        // Unless we go through a callback loop we cannot simply use
        // async_send() multiple times, so we cannot send the size first
        // followed by the actual data. We copy them to a new buffer
        // first
        tcp_send_buffer_->clear();
        tcp_send_buffer_->writeUint16(renderer.getLength());
        tcp_send_buffer_->writeData(renderer.getData(), renderer.getLength());
        tcp_socket_.async_send(asio::buffer(tcp_send_buffer_->getData(),
                                            tcp_send_buffer_->getLength()),
                               boost::bind(
                                   &RecursiveQueryTest3::tcpSendHandler,
                                   this,
                                   tcp_send_buffer_->getLength(), _1, _2));
    }

    /// \brief Completion Handler for Sending TCP data
    ///
    /// Called when the asynchronous send of data back to the RecursiveQuery
    /// by the TCP "server" in this class has completed.  (This send has to
    /// be asynchronous because control needs to return to the caller in order
    /// for the IOService "run()" method to be called to run the handlers.)
    ///
    /// \param expected_length Number of bytes that were expected to have been
    /// sent.
    /// \param ec Boost error code, value should be zero.
    /// \param length Number of bytes sent.
    void tcpSendHandler(size_t expected_length = 0,
                        error_code ec = error_code(),
                        size_t length = 0)
    {
        EXPECT_EQ(0, ec.value());       // Expect no error
        EXPECT_EQ(expected_length, length);    // And that amount sent is as
                                               // expected
    }

    /// \brief Check Received Packet
    ///
    /// Checks the packet received from the RecursiveQuery object to ensure
    /// that the question is what is expected.
    ///
    /// \param data Start of data.  This is the start of the received buffer in
    ///        the case of UDP data, and an offset into the buffer past the
    ///        count field for TCP data.
    /// \param length Length of data.
    /// \return The QID of the message
    void checkReceivedPacket(uint8_t* data, size_t length, Message& message) {

        // Decode the received buffer.
        InputBuffer buffer(data, length);
        message.fromWire(buffer);

        // Check the packet.
        EXPECT_FALSE(message.getHeaderFlag(Message::HEADERFLAG_QR));

        Question question = **(message.beginQuestion());
        EXPECT_TRUE(question == *question_);
    }
};

/// \brief Resolver Callback Object
///
/// Holds the success and failure callback methods for the resolver
class ResolverCallback3 : public isc::resolve::ResolverInterface::Callback {
public:
    /// \brief Constructor
    ResolverCallback3(IOService& service) :
        service_(service), run_(false), status_(false)
    {}

    /// \brief Destructor
    virtual ~ResolverCallback3()
    {}

    /// \brief Resolver Callback Success
    ///
    /// Called if the resolver detects that the call has succeeded.
    ///
    /// \param response Answer to the question.
    virtual void success(const isc::dns::MessagePtr response) {
        // There should be one RR each  in the question and answer sections,
        // and two RRs in each of the the authority and additional sections.
        EXPECT_EQ(1, response->getRRCount(Message::SECTION_QUESTION));
        EXPECT_EQ(1, response->getRRCount(Message::SECTION_ANSWER));

        // Check the answer - that the RRset is there...
        EXPECT_TRUE(response->hasRRset(Message::SECTION_ANSWER,
                                       RRsetPtr(new RRset(Name("ednsfallback."),
                                                RRClass::IN(),
                                                RRType::A(),
                                                RRTTL(300)))));
        const RRsetIterator rrset_i = response->beginSection(Message::SECTION_ANSWER);

        // ... get iterator into the Rdata of this RRset and point to first
        // element...
        const RdataIteratorPtr rdata_i = (*rrset_i)->getRdataIterator();
        rdata_i->first();

        // ... and check it is what we expect.
        EXPECT_EQ(string(DUMMY_ADDR3), rdata_i->getCurrent().toText());

        // Flag completion
        run_ = true;
        status_ = true;

        service_.stop();    // Cause run() to exit.
    }

    /// \brief Resolver Failure Completion
    ///
    /// Called if the resolver detects that the resolution has failed.
    virtual void failure() {
        FAIL() << "Resolver reported completion failure";

        // Flag completion
        run_ = true;
        status_ = false;

        service_.stop();    // Cause run() to exit.
    }

    /// \brief Return status of "run" flag
    bool getRun() const {
        return (run_);
    }

    /// \brief Return "status" flag
    bool getStatus() const {
        return (status_);
    }

private:
    IOService&      service_;       ///< Service handling the run queue
    bool            run_;           ///< Set true when completion handler run
    bool            status_;        ///< Set true for success, false on error
};

// Sets up the UDP and TCP "servers", then tries a resolution.

TEST_F(RecursiveQueryTest3, Resolve) {
    // Set up the UDP server and issue the first read.  The endpoint from which
    // the query is sent is put in udp_endpoint_ when the read completes, which
    // is referenced in the callback as the place to which the response is
    // sent.
    udp_socket_.set_option(socket_base::reuse_address(true));
    udp_socket_.bind(udp::endpoint(address::from_string(TEST_ADDRESS3),
                                   TEST_PORT3));
    udp_socket_.async_receive_from(asio::buffer(udp_receive_buffer_,
                                                sizeof(udp_receive_buffer_)),
                                   udp_remote_,
                           boost::bind(&RecursiveQueryTest3::udpReceiveHandler,
                                               this, _1, _2));

    // Set up the TCP server and issue the accept.  Acceptance will cause the
    // read to be issued.
    tcp::acceptor acceptor(service_.get_io_service(),
                           tcp::endpoint(tcp::v4(), TEST_PORT3));
    acceptor.async_accept(tcp_socket_,
                          boost::bind(&RecursiveQueryTest3::tcpAcceptHandler,
                                      this, _1, 0));

    // Set up the RecursiveQuery object. We will also test that it correctly
    // records RTT times by setting up a RTT recorder object as well.
    std::vector<std::pair<std::string, uint16_t> > upstream;         // Empty
    std::vector<std::pair<std::string, uint16_t> > upstream_root;    // Empty
    RecursiveQuery query(dns_service_, *nsas_, cache_,
                         upstream, upstream_root);
    query.setTestServer(TEST_ADDRESS3, TEST_PORT3);

    boost::shared_ptr<RttRecorder> recorder(new RttRecorder());
    query.setRttRecorder(recorder);

    // Set up callback to receive notification that the query has completed.
    isc::resolve::ResolverInterface::CallbackPtr
        resolver_callback(new ResolverCallback3(service_));

    // Kick off the resolution process.
    expected_ = EDNS_UDP;
    query.resolve(question_, resolver_callback);
    service_.run();

    // Check what ran. (We have to cast the callback to ResolverCallback3 as we
    // lost the information on the derived class when we used a
    // ResolverInterface::CallbackPtr to store a pointer to it.)
    ResolverCallback3* rc
                    = static_cast<ResolverCallback3*>(resolver_callback.get());
    EXPECT_TRUE(rc->getRun());
    EXPECT_TRUE(rc->getStatus());

    // Finally, check that all the RTTs were "reasonable" (defined here as
    // being below 2 seconds).  This is an explicit check to test that the
    // variables in the RTT calculation are at least being initialized; if they
    // weren't, we would expect some absurdly high answers.
    vector<uint32_t> rtt = recorder->getRtt();
    EXPECT_GT(rtt.size(), 0);
    for (int i = 0; i < rtt.size(); ++i) {
        EXPECT_LT(rtt[i], 2000);
    }
}

} // namespace asiodns
} // namespace isc
