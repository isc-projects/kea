// Copyright (C) 2013-2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/interval_timer.h>
#include <dhcp_ddns/ncr_io.h>
#include <dhcp_ddns/ncr_udp.h>
#include <util/time_utilities.h>
#include <test_utils.h>

#include <boost/asio/ip/udp.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <algorithm>

#include <sys/select.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp_ddns;

namespace {

/// @brief Defines a list of valid JSON NameChangeRequest test messages.
const char *valid_msgs[] =
{
    // Valid Add.
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
    // Valid Remove.
     "{"
     " \"change_type\" : 1 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}",
     // Valid Add with IPv6 address
     "{"
     " \"change_type\" : 0 , "
     " \"forward_change\" : true , "
     " \"reverse_change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip_address\" : \"fe80::2acf:e9ff:fe12:e56f\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease_expires_on\" : \"20130121132405\" , "
     " \"lease_length\" : 1300 "
     "}"
};

const char* TEST_ADDRESS = "127.0.0.1";
const uint32_t LISTENER_PORT = 5301;
const uint32_t SENDER_PORT = LISTENER_PORT+1;
const long TEST_TIMEOUT = 5 * 1000;

/// @brief A NOP derivation for constructor test purposes.
class SimpleListenHandler : public NameChangeListener::RequestReceiveHandler {
public:
    virtual void operator ()(const NameChangeListener::Result,
                             NameChangeRequestPtr&) {
    }
};

/// @brief Tests the NameChangeUDPListener constructors.
/// This test verifies that:
/// 1. Given valid parameters, the listener constructor works
TEST(NameChangeUDPListenerBasicTest, constructionTests) {
    // Verify the default constructor works.
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    uint32_t port = LISTENER_PORT;
    isc::asiolink::IOService io_service;
    SimpleListenHandler ncr_handler;
    // Verify that valid constructor works.
    EXPECT_NO_THROW(NameChangeUDPListener(ip_address, port, FMT_JSON,
                                          ncr_handler));
}

/// @brief Tests NameChangeUDPListener starting and stopping listening .
/// This test verifies that the listener will:
/// 1. Enter listening state
/// 2. If in the listening state, does not allow calls to start listening
/// 3. Exist the listening state
/// 4. Return to the listening state after stopping
TEST(NameChangeUDPListenerBasicTest, basicListenTests) {
    // Verify the default constructor works.
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    uint32_t port = LISTENER_PORT;
    isc::asiolink::IOService io_service;
    SimpleListenHandler ncr_handler;

    NameChangeListenerPtr listener;
    ASSERT_NO_THROW(listener.reset(
        new NameChangeUDPListener(ip_address, port, FMT_JSON, ncr_handler)));

    // Verify that we can start listening.
    EXPECT_NO_THROW(listener->startListening(io_service));

    // Verify that we are in listening mode.
    EXPECT_TRUE(listener->amListening());
    // Verify that a read is in progress.
    EXPECT_TRUE(listener->isIoPending());

    // Verify that attempting to listen when we already are is an error.
    EXPECT_THROW(listener->startListening(io_service), NcrListenerError);

    // Verify that we can stop listening.
    EXPECT_NO_THROW(listener->stopListening());
    EXPECT_FALSE(listener->amListening());

    // Verify that IO pending is still true, as IO cancel event has not yet
    // occurred.
    EXPECT_TRUE(listener->isIoPending());

    // Verify that IO pending is false, after cancel event occurs.
    EXPECT_NO_THROW(io_service.run_one());
    EXPECT_FALSE(listener->isIoPending());

    // Verify that attempting to stop listening when we are not is ok.
    EXPECT_NO_THROW(listener->stopListening());

    // Verify that we can re-enter listening.
    EXPECT_NO_THROW(listener->startListening(io_service));
    EXPECT_TRUE(listener->amListening());
}

/// @brief Compares two NameChangeRequests for equality.
bool checkSendVsReceived(NameChangeRequestPtr sent_ncr,
                         NameChangeRequestPtr received_ncr) {
    return ((sent_ncr && received_ncr) &&
        (*sent_ncr == *received_ncr));
}

/// @brief Text fixture for testing NameChangeUDPListener
class NameChangeUDPListenerTest : public virtual ::testing::Test,
                                  NameChangeListener::RequestReceiveHandler {
public:
    isc::asiolink::IOService io_service_;
    NameChangeListener::Result result_;
    NameChangeRequestPtr sent_ncr_;
    NameChangeRequestPtr received_ncr_;
    NameChangeListenerPtr listener_;
    isc::asiolink::IntervalTimer test_timer_;

    /// @brief Constructor
    //
    // Instantiates the listener member and the test timer. The timer is used
    // to ensure a test doesn't go awry and hang forever.
    NameChangeUDPListenerTest()
        : io_service_(), result_(NameChangeListener::SUCCESS),
          test_timer_(io_service_) {
        isc::asiolink::IOAddress addr(TEST_ADDRESS);
        listener_.reset(new NameChangeUDPListener(addr, LISTENER_PORT,
                                              FMT_JSON, *this, true));

        // Set the test timeout to break any running tasks if they hang.
        test_timer_.setup(boost::bind(&NameChangeUDPListenerTest::
                                      testTimeoutHandler, this),
                          TEST_TIMEOUT);
    }

    virtual ~NameChangeUDPListenerTest(){
    }


    /// @brief Converts JSON string into an NCR and sends it to the listener.
    ///
    void sendNcr(const std::string& msg) {
        // Build an NCR  from json string. This verifies that the
        // test string is valid.
        ASSERT_NO_THROW(sent_ncr_ = NameChangeRequest::fromJSON(msg));

        // Now use the NCR to write JSON to an output buffer.
        isc::util::OutputBuffer ncr_buffer(1024);
        ASSERT_NO_THROW(sent_ncr_->toFormat(FMT_JSON, ncr_buffer));

        // Create a UDP socket through which our "sender" will send the NCR.
        boost::asio::ip::udp::socket
            udp_socket(io_service_.get_io_service(), boost::asio::ip::udp::v4());

        // Create an endpoint pointed at the listener.
        boost::asio::ip::udp::endpoint
            listener_endpoint(boost::asio::ip::address::from_string(TEST_ADDRESS),
                              LISTENER_PORT);

        // A response message is now ready to send. Send it!
        // Note this uses a synchronous send so it ships immediately.
        // If listener isn't in listening mode, it will get missed.
        udp_socket.send_to(boost::asio::buffer(ncr_buffer.getData(),
                                     ncr_buffer.getLength()),
                            listener_endpoint);
    }

    /// @brief RequestReceiveHandler operator implementation for receiving NCRs.
    ///
    /// The fixture acts as the "application" layer.  It derives from
    /// RequestReceiveHandler and as such implements operator() in order to
    /// receive NCRs.
    virtual void operator ()(const NameChangeListener::Result result,
                             NameChangeRequestPtr& ncr) {
        // save the result and the NCR we received
        result_ = result;
        received_ncr_ = ncr;
    }
    // @brief Handler invoked when test timeout is hit.
    //
    // This callback stops all running (hanging) tasks on IO service.
    void testTimeoutHandler() {
        io_service_.stop();
        FAIL() << "Test timeout hit.";
    }
};

/// @brief  Tests NameChangeUDPListener ability to receive NCRs.
/// This test verifies that a listener can enter listening mode and
/// receive NCRs in wire format on its UDP socket; reconstruct the
/// NCRs and delivery them to the "application" layer.
TEST_F(NameChangeUDPListenerTest, basicReceivetest) {
    // Verify we can enter listening mode.
    ASSERT_FALSE(listener_->amListening());
    ASSERT_NO_THROW(listener_->startListening(io_service_));
    ASSERT_TRUE(listener_->amListening());
    ASSERT_TRUE(listener_->isIoPending());

    // Iterate over a series of requests, sending and receiving one
    /// at time.
    int num_msgs = sizeof(valid_msgs)/sizeof(char*);
    for (int i = 0; i < num_msgs; i++) {
        // We are not verifying ability to send, so if we can't test is over.
        ASSERT_NO_THROW(sendNcr(valid_msgs[i]));

        // Execute no more then one event, which should be receive complete.
        EXPECT_NO_THROW(io_service_.run_one());

        // Verify the "application" status value for a successful complete.
        EXPECT_EQ(NameChangeListener::SUCCESS, result_);

        // Verify the received request matches the sent request.
        EXPECT_TRUE(checkSendVsReceived(sent_ncr_, received_ncr_));
    }

    // Verify we can gracefully stop listening.
    EXPECT_NO_THROW(listener_->stopListening());
    EXPECT_FALSE(listener_->amListening());

    // Verify that IO pending is false, after cancel event occurs.
    EXPECT_NO_THROW(io_service_.run_one());
    EXPECT_FALSE(listener_->isIoPending());
}

/// @brief A NOP derivation for constructor test purposes.
class SimpleSendHandler : public NameChangeSender::RequestSendHandler {
public:
    SimpleSendHandler() : pass_count_(0), error_count_(0) {
    }

    virtual void operator ()(const NameChangeSender::Result result,
                             NameChangeRequestPtr&) {
        if (result == NameChangeSender::SUCCESS) {
            ++pass_count_;
        } else {
            ++error_count_;
        }
    }

    int pass_count_;
    int error_count_;
};

/// @brief Tests the NameChangeUDPSender constructors.
/// This test verifies that:
/// 1. Constructing with a max queue size of 0 is not allowed
/// 2. Given valid parameters, the sender constructor works
/// 3. Default construction provides default max queue size
/// 4. Construction with a custom max queue size works
TEST(NameChangeUDPSenderBasicTest, constructionTests) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    uint32_t port = SENDER_PORT;
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;

    // Verify that constructing with an queue size of zero is not allowed.
    EXPECT_THROW(NameChangeUDPSender(ip_address, port,
        ip_address, port, FMT_JSON, ncr_handler, 0), NcrSenderError);

    NameChangeSenderPtr sender;
    // Verify that valid constructor works.
    EXPECT_NO_THROW(sender.reset(
                    new NameChangeUDPSender(ip_address, port, ip_address, port,
                                            FMT_JSON, ncr_handler)));

    // Verify that send queue default max is correct.
    size_t expected = NameChangeSender::MAX_QUEUE_DEFAULT;
    EXPECT_EQ(expected, sender->getQueueMaxSize());

    // Verify that constructor with a valid custom queue size works.
    EXPECT_NO_THROW(sender.reset(
                    new NameChangeUDPSender(ip_address, port, ip_address, port,
                                            FMT_JSON, ncr_handler, 100)));

    EXPECT_EQ(100, sender->getQueueMaxSize());
}

/// @brief Tests NameChangeUDPSender basic send functionality
/// This test verifies that:
TEST(NameChangeUDPSenderBasicTest, basicSendTests) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;

    // Tests are based on a list of messages, get the count now.
    int num_msgs = sizeof(valid_msgs)/sizeof(char*);

    // Create the sender, setting the queue max equal to the number of
    // messages we will have in the list.
    NameChangeUDPSender sender(ip_address, SENDER_PORT, ip_address,
                               LISTENER_PORT, FMT_JSON, ncr_handler,
                               num_msgs, true);

    // Verify that we can start sending.
    EXPECT_NO_THROW(sender.startSending(io_service));
    EXPECT_TRUE(sender.amSending());

    // Verify that attempting to send when we already are is an error.
    EXPECT_THROW(sender.startSending(io_service), NcrSenderError);

    // Verify that we can stop sending.
    EXPECT_NO_THROW(sender.stopSending());
    EXPECT_FALSE(sender.amSending());

    // Verify that attempting to stop sending when we are not is ok.
    EXPECT_NO_THROW(sender.stopSending());

    // Verify that we can re-enter sending after stopping.
    EXPECT_NO_THROW(sender.startSending(io_service));
    EXPECT_TRUE(sender.amSending());

    // Fetch the sender's select-fd.
    int select_fd = sender.getSelectFd();

    // Verify select_fd is valid and currently shows no ready to read.
    ASSERT_NE(util::WatchSocket::SOCKET_NOT_VALID, select_fd);

    // Make sure select_fd does evaluates to not ready via select and
    // that ioReady() method agrees.
    ASSERT_EQ(0, selectCheck(select_fd));
    ASSERT_FALSE(sender.ioReady());

    // Iterate over a series of messages, sending each one. Since we
    // do not invoke IOService::run, then the messages should accumulate
    // in the queue.
    NameChangeRequestPtr ncr;
    NameChangeRequestPtr ncr2;
    for (int i = 0; i < num_msgs; i++) {
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        EXPECT_NO_THROW(sender.sendRequest(ncr));
        // Verify that the queue count increments in step with each send.
        EXPECT_EQ(i+1, sender.getQueueSize());

        // Verify that peekAt(i) returns the NCR we just added.
        ASSERT_NO_THROW(ncr2 = sender.peekAt(i));
        ASSERT_TRUE(ncr2);
        EXPECT_TRUE(*ncr == *ncr2);
    }

    // Verify that attempting to peek beyond the end of the queue, throws.
    ASSERT_THROW(sender.peekAt(sender.getQueueSize()+1), NcrSenderError);

    // Verify that attempting to send an additional message results in a
    // queue full exception.
    EXPECT_THROW(sender.sendRequest(ncr), NcrSenderQueueFull);

    // Loop for the number of valid messages. So long as there is at least
    // on NCR in the queue, select-fd indicate ready to read. Invoke
    // IOService::run_one. This should complete the send of exactly one
    // message and the queue count should decrement accordingly.
    for (int i = num_msgs; i > 0; i--) {
        // Make sure select_fd does evaluates to ready via select and
        // that ioReady() method agrees.
        ASSERT_TRUE(selectCheck(select_fd) > 0);
        ASSERT_TRUE(sender.ioReady());

        // Execute at one ready handler.
        ASSERT_NO_THROW(sender.runReadyIO());

        // Verify that the queue count decrements in step with each run.
        EXPECT_EQ(i-1, sender.getQueueSize());
    }

    // Make sure select_fd does evaluates to not ready via select and
    // that ioReady() method agrees.
    ASSERT_EQ(0, selectCheck(select_fd));
    ASSERT_FALSE(sender.ioReady());

    // Verify that the queue is empty.
    EXPECT_EQ(0, sender.getQueueSize());

    // Verify that we can add back to the queue
    EXPECT_NO_THROW(sender.sendRequest(ncr));
    EXPECT_EQ(1, sender.getQueueSize());

    // Verify that we can remove the current entry at the front of the queue.
    EXPECT_NO_THROW(sender.skipNext());
    EXPECT_EQ(0, sender.getQueueSize());

    // Verify that flushing the queue is not allowed in sending state.
    EXPECT_THROW(sender.clearSendQueue(), NcrSenderError);

    // Put num_msgs messages on the queue.
    for (int i = 0; i < num_msgs; i++) {
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        EXPECT_NO_THROW(sender.sendRequest(ncr));
    }

    // Make sure we have number of messages expected.
    EXPECT_EQ(num_msgs, sender.getQueueSize());

    // Verify that we can gracefully stop sending.
    EXPECT_NO_THROW(sender.stopSending());
    EXPECT_FALSE(sender.amSending());

    // Verify that the queue is preserved after leaving sending state.
    EXPECT_EQ(num_msgs - 1, sender.getQueueSize());

    // Verify that flushing the queue works when not sending.
    EXPECT_NO_THROW(sender.clearSendQueue());
    EXPECT_EQ(0, sender.getQueueSize());
}

/// @brief Tests that sending gets kick-started if the queue isn't empty
/// when startSending is called.
TEST(NameChangeUDPSenderBasicTest, autoStart) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;

    // Tests are based on a list of messages, get the count now.
    int num_msgs = sizeof(valid_msgs)/sizeof(char*);

    // Create the sender, setting the queue max equal to the number of
    // messages we will have in the list.
    NameChangeUDPSender sender(ip_address, SENDER_PORT, ip_address,
                               LISTENER_PORT, FMT_JSON, ncr_handler,
                               num_msgs, true);

    // Verify that we can start sending.
    EXPECT_NO_THROW(sender.startSending(io_service));
    EXPECT_TRUE(sender.amSending());

    // Queue up messages.
    NameChangeRequestPtr ncr;
    for (int i = 0; i < num_msgs; i++) {
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        EXPECT_NO_THROW(sender.sendRequest(ncr));
    }
    // Make sure queue count is what we expect.
    EXPECT_EQ(num_msgs, sender.getQueueSize());

    // Stop sending.
    ASSERT_NO_THROW(sender.stopSending());
    ASSERT_FALSE(sender.amSending());

    // We should have completed the first message only.
    EXPECT_EQ(--num_msgs, sender.getQueueSize());

    // Restart sending.
    EXPECT_NO_THROW(sender.startSending(io_service));

    // We should be able to loop through remaining messages and send them.
    for (int i = num_msgs; i > 0; i--) {
        // ioReady() should evaluate to true.
        ASSERT_TRUE(sender.ioReady());

        // Execute at one ready handler.
        ASSERT_NO_THROW(sender.runReadyIO());
    }

    // Verify that the queue is empty.
    EXPECT_EQ(0, sender.getQueueSize());
}

/// @brief Tests NameChangeUDPSender basic send  with INADDR_ANY and port 0.
TEST(NameChangeUDPSenderBasicTest, anyAddressSend) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    isc::asiolink::IOAddress any_address("0.0.0.0");
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;

    // Tests are based on a list of messages, get the count now.
    int num_msgs = sizeof(valid_msgs)/sizeof(char*);

    // Create the sender, setting the queue max equal to the number of
    // messages we will have in the list.
    NameChangeUDPSender sender(any_address, 0, ip_address, LISTENER_PORT,
                               FMT_JSON, ncr_handler, num_msgs);

    // Enter send mode.
    ASSERT_NO_THROW(sender.startSending(io_service));
    EXPECT_TRUE(sender.amSending());

    // Create and queue up a message.
    NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[0]));
    EXPECT_NO_THROW(sender.sendRequest(ncr));
    EXPECT_EQ(1, sender.getQueueSize());

    // Verify we have a ready IO, then execute at one ready handler.
    ASSERT_TRUE(sender.ioReady());
    ASSERT_NO_THROW(sender.runReadyIO());

    // Verify that sender shows no IO ready.
    // and that the queue is empty.
    ASSERT_FALSE(sender.ioReady());
    EXPECT_EQ(0, sender.getQueueSize());
}

/// @brief Test the NameChangeSender::assumeQueue method.
TEST(NameChangeSender, assumeQueue) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    uint32_t port = SENDER_PORT;
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;
    NameChangeRequestPtr ncr;

    // Tests are based on a list of messages, get the count now.
    int num_msgs = sizeof(valid_msgs)/sizeof(char*);

    // Create two senders with queue max equal to the number of
    // messages we will have in the list.
    NameChangeUDPSender sender1(ip_address, port, ip_address, port,
                               FMT_JSON, ncr_handler, num_msgs);

    NameChangeUDPSender sender2(ip_address, port+1, ip_address, port,
                                FMT_JSON, ncr_handler, num_msgs);

    // Place sender1 into send mode and queue up messages.
    ASSERT_NO_THROW(sender1.startSending(io_service));
    for (int i = 0; i < num_msgs; i++) {
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        ASSERT_NO_THROW(sender1.sendRequest(ncr));
    }

    // Make sure sender1's queue count is as expected.
    ASSERT_EQ(num_msgs, sender1.getQueueSize());

    // Verify sender1 is sending, sender2 is not.
    ASSERT_TRUE(sender1.amSending());
    ASSERT_FALSE(sender2.amSending());

    // Transfer from sender1 to sender2 should fail because
    // sender1 is in send mode.
    ASSERT_THROW(sender2.assumeQueue(sender1), NcrSenderError);

    // Take sender1 out of send mode.
    ASSERT_NO_THROW(sender1.stopSending());
    ASSERT_FALSE(sender1.amSending());
    // Stopping should have completed the first message.
    --num_msgs;
    EXPECT_EQ(num_msgs, sender1.getQueueSize());

    // Transfer should succeed. Verify sender1 has none,
    // and sender2 has num_msgs queued.
    EXPECT_NO_THROW(sender2.assumeQueue(sender1));
    EXPECT_EQ(0, sender1.getQueueSize());
    EXPECT_EQ(num_msgs, sender2.getQueueSize());

    // Reduce sender1's max queue size.
    ASSERT_NO_THROW(sender1.setQueueMaxSize(num_msgs - 1));

    // Transfer should fail as sender1's queue is not large enough.
    ASSERT_THROW(sender1.assumeQueue(sender2), NcrSenderError);

    // Place sender1 into send mode and queue up a message.
    ASSERT_NO_THROW(sender1.startSending(io_service));
    ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[0]));
    ASSERT_NO_THROW(sender1.sendRequest(ncr));

    // Take sender1 out of send mode.
    ASSERT_NO_THROW(sender1.stopSending());

    // Try to transfer from sender1 to sender2. This should fail
    // as sender2's queue is not empty.
    ASSERT_THROW(sender2.assumeQueue(sender1), NcrSenderError);
}

/// @brief Text fixture that allows testing a listener and sender together
/// It derives from both the receive and send handler classes and contains
/// and instance of UDP listener and UDP sender.
class NameChangeUDPTest : public virtual ::testing::Test,
                          NameChangeListener::RequestReceiveHandler,
                          NameChangeSender::RequestSendHandler {
public:
    isc::asiolink::IOService io_service_;
    NameChangeListener::Result recv_result_;
    NameChangeSender::Result send_result_;
    NameChangeListenerPtr listener_;
    NameChangeSenderPtr   sender_;
    isc::asiolink::IntervalTimer test_timer_;

    std::vector<NameChangeRequestPtr> sent_ncrs_;
    std::vector<NameChangeRequestPtr> received_ncrs_;

    NameChangeUDPTest()
        : io_service_(), recv_result_(NameChangeListener::SUCCESS),
          send_result_(NameChangeSender::SUCCESS), test_timer_(io_service_) {
        isc::asiolink::IOAddress addr(TEST_ADDRESS);
        // Create our listener instance. Note that reuse_address is true.
        listener_.reset(
            new NameChangeUDPListener(addr, LISTENER_PORT, FMT_JSON,
                                      *this, true));

        // Create our sender instance. Note that reuse_address is true.
         sender_.reset(
             new NameChangeUDPSender(addr, SENDER_PORT, addr, LISTENER_PORT,
                                     FMT_JSON, *this, 100, true));

        // Set the test timeout to break any running tasks if they hang.
        test_timer_.setup(boost::bind(&NameChangeUDPTest::testTimeoutHandler,
                                      this),
                          TEST_TIMEOUT);
    }

    void reset_results() {
        sent_ncrs_.clear();
        received_ncrs_.clear();
    }

    /// @brief Implements the receive completion handler.
    virtual void operator ()(const NameChangeListener::Result result,
                             NameChangeRequestPtr& ncr) {
        // save the result and the NCR received.
        recv_result_ = result;
        received_ncrs_.push_back(ncr);
    }

    /// @brief Implements the send completion handler.
    virtual void operator ()(const NameChangeSender::Result result,
                             NameChangeRequestPtr& ncr) {
        // save the result and the NCR sent.
        send_result_ = result;
        sent_ncrs_.push_back(ncr);
    }

    // @brief Handler invoked when test timeout is hit.
    //
    // This callback stops all running (hanging) tasks on IO service.
    void testTimeoutHandler() {
        io_service_.stop();
        FAIL() << "Test timeout hit.";
    }
};

/// @brief Uses a sender and listener to test UDP-based NCR delivery
/// Conducts a "round-trip" test using a sender to transmit a set of valid
/// NCRs to a listener.  The test verifies that what was sent matches what
/// was received both in quantity and in content.
TEST_F (NameChangeUDPTest, roundTripTest) {
    // Place the listener into listening state.
    ASSERT_NO_THROW(listener_->startListening(io_service_));
    EXPECT_TRUE(listener_->amListening());

    // Get the number of messages in the list of test messages.
    int num_msgs = sizeof(valid_msgs)/sizeof(char*);

    // Place the sender into sending state.
    ASSERT_NO_THROW(sender_->startSending(io_service_));
    EXPECT_TRUE(sender_->amSending());

    for (int i = 0; i < num_msgs; i++) {
        NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        sender_->sendRequest(ncr);
        EXPECT_EQ(i+1, sender_->getQueueSize());
    }

    // Execute callbacks until we have sent and received all of messages.
    while (sender_->getQueueSize() > 0 || (received_ncrs_.size() < num_msgs)) {
        EXPECT_NO_THROW(io_service_.run_one());
    }

    // Send queue should be empty.
    EXPECT_EQ(0, sender_->getQueueSize());

    // We should have the same number of sends and receives as we do messages.
    ASSERT_EQ(num_msgs, sent_ncrs_.size());
    ASSERT_EQ(num_msgs, received_ncrs_.size());

    // Verify that what we sent matches what we received.
    for (int i = 0; i < num_msgs; i++) {
        EXPECT_TRUE (checkSendVsReceived(sent_ncrs_[i], received_ncrs_[i]));
    }

    // Verify that we can gracefully stop listening.
    EXPECT_NO_THROW(listener_->stopListening());
    EXPECT_FALSE(listener_->amListening());

    // Verify that IO pending is false, after cancel event occurs.
    EXPECT_NO_THROW(io_service_.run_one());
    EXPECT_FALSE(listener_->isIoPending());

    // Verify that we can gracefully stop sending.
    EXPECT_NO_THROW(sender_->stopSending());
    EXPECT_FALSE(sender_->amSending());
}

// Tests error handling of a failure to mark the watch socket ready, when
// sendRequestt() is called.
TEST(NameChangeUDPSenderBasicTest, watchClosedBeforeSendRequest) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;

    // Create the sender and put into send mode.
    NameChangeUDPSender sender(ip_address, 0, ip_address, LISTENER_PORT,
                               FMT_JSON, ncr_handler, 100, true);
    ASSERT_NO_THROW(sender.startSending(io_service));
    ASSERT_TRUE(sender.amSending());

    // Create an NCR.
    NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[0]));

    // Tamper with the watch socket by closing the select-fd.
    close(sender.getSelectFd());

    // Send should fail as we interferred by closing the select-fd.
    ASSERT_THROW(sender.sendRequest(ncr), util::WatchSocketError);

    // Verify we didn't invoke the handler.
    EXPECT_EQ(0, ncr_handler.pass_count_);
    EXPECT_EQ(0, ncr_handler.error_count_);

    // Request remains in the queue. Technically it was sent but its
    // completion handler won't get called.
    EXPECT_EQ(1, sender.getQueueSize());
}

// Tests error handling of a failure to mark the watch socket ready, when
// sendNext() is called during completion handling.
TEST(NameChangeUDPSenderBasicTest, watchClosedAfterSendRequest) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;

    // Create the sender and put into send mode.
    NameChangeUDPSender sender(ip_address, 0, ip_address, LISTENER_PORT,
                               FMT_JSON, ncr_handler, 100, true);
    ASSERT_NO_THROW(sender.startSending(io_service));
    ASSERT_TRUE(sender.amSending());

    // Build and queue up 2 messages.  No handlers will get called yet.
    for (int i = 0; i < 2; i++) {
        NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        sender.sendRequest(ncr);
        EXPECT_EQ(i+1, sender.getQueueSize());
    }

    // Tamper with the watch socket by closing the select-fd.
    close (sender.getSelectFd());

    // Run one handler. This should execute the send completion handler
    // after sending the first message.  Duing completion handling, we will
    // attempt to queue the second message which should fail.
    ASSERT_NO_THROW(sender.runReadyIO());

    // Verify handler got called twice. First request should have be sent
    // without error, second call should have failed to send due to watch
    // socket markReady failure.
    EXPECT_EQ(1, ncr_handler.pass_count_);
    EXPECT_EQ(1, ncr_handler.error_count_);

    // The second request should still be in the queue.
    EXPECT_EQ(1, sender.getQueueSize());
}

// Tests error handling of a failure to clear the watch socket during
// completion handling.
TEST(NameChangeUDPSenderBasicTest, watchSocketBadRead) {
    isc::asiolink::IOAddress ip_address(TEST_ADDRESS);
    isc::asiolink::IOService io_service;
    SimpleSendHandler ncr_handler;

    // Create the sender and put into send mode.
    NameChangeUDPSender sender(ip_address, 0, ip_address, LISTENER_PORT,
                               FMT_JSON, ncr_handler, 100, true);
    ASSERT_NO_THROW(sender.startSending(io_service));
    ASSERT_TRUE(sender.amSending());

    // Build and queue up 2 messages.  No handlers will get called yet.
    for (int i = 0; i < 2; i++) {
        NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        sender.sendRequest(ncr);
        EXPECT_EQ(i+1, sender.getQueueSize());
    }

    // Fetch the sender's select-fd.
    int select_fd = sender.getSelectFd();

    // Verify that select_fd appears ready.
    ASSERT_TRUE(selectCheck(select_fd) > 0);

    // Interfere by reading part of the marker from the select-fd.
    uint32_t buf = 0;
    ASSERT_EQ((read (select_fd, &buf, 1)), 1);
    ASSERT_NE(util::WatchSocket::MARKER, buf);

    // Run one handler. This should execute the send completion handler
    // after sending the message.  Duing completion handling clearing the
    // watch socket should fail, which will close the socket, but not
    // result in a throw.
    ASSERT_NO_THROW(sender.runReadyIO());

    // Verify handler got called twice. First request should have be sent
    // without error, second call should have failed to send due to watch
    // socket markReady failure.
    EXPECT_EQ(1, ncr_handler.pass_count_);
    EXPECT_EQ(1, ncr_handler.error_count_);

    // The second request should still be in the queue.
    EXPECT_EQ(1, sender.getQueueSize());
}

} // end of anonymous namespace
