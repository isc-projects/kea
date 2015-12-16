// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>
#include <d2/d2_queue_mgr.h>
#include <dhcp_ddns/ncr_udp.h>
#include <util/time_utilities.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

using namespace std;
using namespace isc;
using namespace isc::dhcp_ddns;
using namespace isc::d2;

namespace {

/// @brief Defines a list of valid JSON NameChangeRequest test messages.
const char *valid_msgs[] =
{
    // Valid Add.
     "{"
     " \"change-type\" : 0 , "
     " \"forward-change\" : true , "
     " \"reverse-change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip-address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease-expires-on\" : \"20130121132405\" , "
     " \"lease-length\" : 1300 "
     "}",
    // Valid Remove.
     "{"
     " \"change-type\" : 1 , "
     " \"forward-change\" : true , "
     " \"reverse-change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip-address\" : \"192.168.2.1\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease-expires-on\" : \"20130121132405\" , "
     " \"lease-length\" : 1300 "
     "}",
     // Valid Add with IPv6 address
     "{"
     " \"change-type\" : 0 , "
     " \"forward-change\" : true , "
     " \"reverse-change\" : false , "
     " \"fqdn\" : \"walah.walah.com\" , "
     " \"ip-address\" : \"fe80::2acf:e9ff:fe12:e56f\" , "
     " \"dhcid\" : \"010203040A7F8E3D\" , "
     " \"lease-expires-on\" : \"20130121132405\" , "
     " \"lease-length\" : 1300 "
     "}"
};

static const  int VALID_MSG_CNT = sizeof(valid_msgs)/sizeof(char*);

const char* TEST_ADDRESS = "127.0.0.1";
const uint32_t LISTENER_PORT = 5301;
const uint32_t SENDER_PORT = LISTENER_PORT+1;
const long TEST_TIMEOUT = 5 * 1000;

/// @brief Tests that construction with max queue size of zero is not allowed.
TEST(D2QueueMgrBasicTest, construction1) {
    asiolink::IOServicePtr io_service;

    // Verify that constructing with null IOServicePtr is not allowed.
    EXPECT_THROW((D2QueueMgr(io_service)), D2QueueMgrError);

    io_service.reset(new isc::asiolink::IOService());
    // Verify that constructing with max queue size of zero is not allowed.
    EXPECT_THROW(D2QueueMgr(io_service, 0), D2QueueMgrError);
}

/// @brief Tests default construction works.
TEST(D2QueueMgrBasicTest, construction2) {
    asiolink::IOServicePtr io_service(new isc::asiolink::IOService());

    // Verify that valid constructor works.
    D2QueueMgrPtr queue_mgr;
    ASSERT_NO_THROW(queue_mgr.reset(new D2QueueMgr(io_service)));
    // Verify queue max is defaulted correctly.
    EXPECT_EQ(D2QueueMgr::MAX_QUEUE_DEFAULT, queue_mgr->getMaxQueueSize());
}

/// @brief Tests construction with custom queue size works properly
TEST(D2QueueMgrBasicTest, construction3) {
    asiolink::IOServicePtr io_service(new isc::asiolink::IOService());

    // Verify that custom queue size constructor works.
    D2QueueMgrPtr queue_mgr;
    ASSERT_NO_THROW(queue_mgr.reset(new D2QueueMgr(io_service, 100)));
    // Verify queue max is the custom value.
    EXPECT_EQ(100, queue_mgr->getMaxQueueSize());
}

/// @brief Tests  QueueMgr's basic queue functions
/// This test verifies that:
/// 1. Following construction queue is empty
/// 2. Attempting to peek at an empty queue is not allowed
/// 3. Attempting to dequeue an empty queue is not allowed
/// 4. Peek returns the first entry on the queue without altering queue content
/// 5. Dequeue removes the first entry on the queue
TEST(D2QueueMgrBasicTest, basicQueue) {
    asiolink::IOServicePtr io_service(new isc::asiolink::IOService());

    // Construct the manager with max queue size set to number of messages
    // we'll use.
    D2QueueMgrPtr queue_mgr;
    ASSERT_NO_THROW(queue_mgr.reset(new D2QueueMgr(io_service, VALID_MSG_CNT)));
    ASSERT_EQ(VALID_MSG_CNT, queue_mgr->getMaxQueueSize());

    // Verify queue is empty after construction.
    EXPECT_EQ(0, queue_mgr->getQueueSize());

    // Verify that peek and dequeue both throw when queue is empty.
    EXPECT_THROW(queue_mgr->peek(), D2QueueMgrQueueEmpty);
    EXPECT_THROW(queue_mgr->dequeue(), D2QueueMgrQueueEmpty);

    // Vector to keep track of the NCRs we que.
    std::vector<NameChangeRequestPtr>ref_msgs;
    NameChangeRequestPtr ncr;

    // Iterate over the list of requests and add each to the queue.
    for (int i = 0; i < VALID_MSG_CNT; i++) {
        // Create the ncr and add to our reference list.
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        ref_msgs.push_back(ncr);

        // Verify that the request can be added to the queue and queue
        // size increments accordingly.
        EXPECT_NO_THROW(queue_mgr->enqueue(ncr));
        EXPECT_EQ(i+1, queue_mgr->getQueueSize());
    }

    // Loop through and verify that the queue contents match the
    // reference list.
    for (int i = 0; i < VALID_MSG_CNT; i++) {
        // Verify that peek on a non-empty queue returns first entry
        // without altering queue content.
        EXPECT_NO_THROW(ncr = queue_mgr->peek());

        // Verify the peeked entry is the one it should be.
        ASSERT_TRUE(ncr);
        EXPECT_TRUE (*(ref_msgs[i]) == *ncr);

        // Verify that peek did not alter the queue size.
        EXPECT_EQ(VALID_MSG_CNT - i, queue_mgr->getQueueSize());

        // Verify the dequeueing from non-empty queue works
        EXPECT_NO_THROW(queue_mgr->dequeue());

        // Verify queue size decrements following dequeue.
        EXPECT_EQ(VALID_MSG_CNT - (i + 1), queue_mgr->getQueueSize());
    }

    // Iterate over the list of requests and add each to the queue.
    for (int i = 0; i < VALID_MSG_CNT; i++) {
        // Create the ncr and add to our reference list.
        ASSERT_NO_THROW(ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        ref_msgs.push_back(ncr);
        EXPECT_NO_THROW(queue_mgr->enqueue(ncr));
    }

    // Verify queue count is correct.
    EXPECT_EQ(VALID_MSG_CNT, queue_mgr->getQueueSize());

    // Verfiy that peekAt returns the correct entry.
    EXPECT_NO_THROW(ncr = queue_mgr->peekAt(1));
    EXPECT_TRUE (*(ref_msgs[1]) == *ncr);

    // Verfiy that dequeueAt removes the correct entry.
    // Removing it, this should shift the queued entries forward by one.
    EXPECT_NO_THROW(queue_mgr->dequeueAt(1));
    EXPECT_NO_THROW(ncr = queue_mgr->peekAt(1));
    EXPECT_TRUE (*(ref_msgs[2]) == *ncr);

    // Verify the peekAt and dequeueAt throw when given indexes beyond the end.
    EXPECT_THROW(queue_mgr->peekAt(VALID_MSG_CNT + 1), D2QueueMgrInvalidIndex);
    EXPECT_THROW(queue_mgr->dequeueAt(VALID_MSG_CNT + 1),
                 D2QueueMgrInvalidIndex);
}

/// @brief Compares two NameChangeRequests for equality.
bool checkSendVsReceived(NameChangeRequestPtr sent_ncr,
                         NameChangeRequestPtr received_ncr) {
    return ((sent_ncr && received_ncr) &&
        (*sent_ncr == *received_ncr));
}

/// @brief Text fixture that allows testing a listener and sender together
/// It derives from both the receive and send handler classes and contains
/// and instance of UDP listener and UDP sender.
class QueueMgrUDPTest : public virtual ::testing::Test,
                        NameChangeSender::RequestSendHandler {
public:
    asiolink::IOServicePtr io_service_;
    NameChangeSenderPtr   sender_;
    isc::asiolink::IntervalTimer test_timer_;
    D2QueueMgrPtr queue_mgr_;

    NameChangeSender::Result send_result_;
    std::vector<NameChangeRequestPtr> sent_ncrs_;
    std::vector<NameChangeRequestPtr> received_ncrs_;

    QueueMgrUDPTest() : io_service_(new isc::asiolink::IOService()),
        test_timer_(*io_service_) {
        isc::asiolink::IOAddress addr(TEST_ADDRESS);
        // Create our sender instance. Note that reuse_address is true.
        sender_.reset(new NameChangeUDPSender(addr, SENDER_PORT,
                                              addr, LISTENER_PORT,
                                              FMT_JSON, *this, 100, true));

        // Set the test timeout to break any running tasks if they hang.
        test_timer_.setup(boost::bind(&QueueMgrUDPTest::testTimeoutHandler,
                                      this),
                          TEST_TIMEOUT);
    }

    void reset_results() {
        sent_ncrs_.clear();
        received_ncrs_.clear();
    }

    /// @brief Implements the send completion handler.
    virtual void operator ()(const NameChangeSender::Result result,
                             NameChangeRequestPtr& ncr) {
        // save the result and the NCR sent.
        send_result_ = result;
        sent_ncrs_.push_back(ncr);
    }

    /// @brief Handler invoked when test timeout is hit.
    ///
    /// This callback stops all running (hanging) tasks on IO service.
    void testTimeoutHandler() {
        io_service_->stop();
        FAIL() << "Test timeout hit.";
    }
};

/// @brief Tests D2QueueMgr's state model.
/// This test verifies that:
/// 1. Upon construction, initial state is NOT_INITTED.
/// 2. Cannot start listening from while state is NOT_INITTED.
/// 3. Successful listener initialization transitions from NOT_INITTED
/// to INITTED.
/// 4. Attempting to initialize the listener from INITTED state is not
/// allowed.
/// 5. Starting listener from INITTED transitions to RUNNING.
/// 6. Stopping the  listener transitions from RUNNING to STOPPED.
/// 7. Starting listener from STOPPED transitions to RUNNING.
TEST_F (QueueMgrUDPTest, stateModel) {
    // Create the queue manager.
    ASSERT_NO_THROW(queue_mgr_.reset(new D2QueueMgr(io_service_,
                                     VALID_MSG_CNT)));

    // Verify that the initial state is NOT_INITTED.
    EXPECT_EQ(D2QueueMgr::NOT_INITTED, queue_mgr_->getMgrState());

    // Verify that trying to listen before when not initialized fails.
    EXPECT_THROW(queue_mgr_->startListening(), D2QueueMgrError);

    // Verify that initializing the listener moves us to INITTED state.
    isc::asiolink::IOAddress addr(TEST_ADDRESS);
    EXPECT_NO_THROW(queue_mgr_->initUDPListener(addr, LISTENER_PORT,
                                              FMT_JSON, true));
    EXPECT_EQ(D2QueueMgr::INITTED, queue_mgr_->getMgrState());

    // Verify that attempting to initialize the listener, from INITTED
    // is not allowed.
    EXPECT_THROW(queue_mgr_->initUDPListener(addr, LISTENER_PORT,
                                              FMT_JSON, true),
                 D2QueueMgrError);

    // Verify that we can enter the RUNNING from INITTED by starting the
    // listener.
    EXPECT_NO_THROW(queue_mgr_->startListening());
    EXPECT_EQ(D2QueueMgr::RUNNING, queue_mgr_->getMgrState());

    // Verify that we can move from RUNNING to STOPPING by stopping the
    // listener.
    EXPECT_NO_THROW(queue_mgr_->stopListening());
    EXPECT_EQ(D2QueueMgr::STOPPING, queue_mgr_->getMgrState());

    // Stopping requires IO cancel, which result in a callback.
    // So process one event and verify we are STOPPED.
    io_service_->run_one();
    EXPECT_EQ(D2QueueMgr::STOPPED, queue_mgr_->getMgrState());

    // Verify that we can re-enter the RUNNING from STOPPED by starting the
    // listener.
    EXPECT_NO_THROW(queue_mgr_->startListening());
    EXPECT_EQ(D2QueueMgr::RUNNING, queue_mgr_->getMgrState());

    // Verify that we cannot remove the listener in the RUNNING state
    EXPECT_THROW(queue_mgr_->removeListener(), D2QueueMgrError);

    // Stop the listener.
    EXPECT_NO_THROW(queue_mgr_->stopListening());
    EXPECT_EQ(D2QueueMgr::STOPPING, queue_mgr_->getMgrState());

    // Stopping requires IO cancel, which result in a callback.
    // So process one event and verify we are STOPPED.
    io_service_->run_one();
    EXPECT_EQ(D2QueueMgr::STOPPED, queue_mgr_->getMgrState());

    // Verify that we can remove the listener in the STOPPED state and
    // end up back in NOT_INITTED.
    EXPECT_NO_THROW(queue_mgr_->removeListener());
    EXPECT_EQ(D2QueueMgr::NOT_INITTED, queue_mgr_->getMgrState());
}

/// @brief Tests D2QueueMgr's ability to manage received requests
/// This test verifies that:
/// 1. Requests can be received, queued, and dequeued
/// 2. Once the queue is full, a subsequent request transitions
/// manager to STOPPED_QUEUE_FULL state.
/// 3. Starting listener returns manager to the RUNNING state.
/// 4. Queue contents are preserved across state transitions.
/// 5. Clearing the queue via the clearQueue() method works.
/// 6. Requests can be received and queued normally after the queue
/// has been emptied.
/// 7. setQueueMax disallows values of 0 or less than current queue size.
TEST_F (QueueMgrUDPTest, liveFeed) {
    NameChangeRequestPtr send_ncr;
    NameChangeRequestPtr received_ncr;

    // Create the queue manager and start listening..
    ASSERT_NO_THROW(queue_mgr_.reset(new D2QueueMgr(io_service_,
                                                    VALID_MSG_CNT)));
    ASSERT_EQ(D2QueueMgr::NOT_INITTED, queue_mgr_->getMgrState());

    // Verify that setting max queue size to 0 is not allowed.
    EXPECT_THROW(queue_mgr_->setMaxQueueSize(0), D2QueueMgrError);
    EXPECT_EQ(VALID_MSG_CNT, queue_mgr_->getMaxQueueSize());

    isc::asiolink::IOAddress addr(TEST_ADDRESS);
    ASSERT_NO_THROW(queue_mgr_->initUDPListener(addr, LISTENER_PORT,
                                              FMT_JSON, true));
    ASSERT_EQ(D2QueueMgr::INITTED, queue_mgr_->getMgrState());

    ASSERT_NO_THROW(queue_mgr_->startListening());
    ASSERT_EQ(D2QueueMgr::RUNNING, queue_mgr_->getMgrState());

    // Place the sender into sending state.
    ASSERT_NO_THROW(sender_->startSending(*io_service_));
    ASSERT_TRUE(sender_->amSending());

    // Iterate over the list of requests sending and receiving
    // each one.  Verify and dequeue as they arrive.
    for (int i = 0; i < VALID_MSG_CNT; i++) {
        // Create the ncr and add to our reference list.
        ASSERT_NO_THROW(send_ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        ASSERT_NO_THROW(sender_->sendRequest(send_ncr));

        // running two should do the send then the receive
        io_service_->run_one();
        io_service_->run_one();

        // Verify that the request can be added to the queue and queue
        // size increments accordingly.
        EXPECT_EQ(1, queue_mgr_->getQueueSize());

        // Verify that peek shows the NCR we just sent
        EXPECT_NO_THROW(received_ncr = queue_mgr_->peek());
        EXPECT_TRUE(checkSendVsReceived(send_ncr, received_ncr));

        // Verify that we and dequeue the request.
        EXPECT_NO_THROW(queue_mgr_->dequeue());
        EXPECT_EQ(0, queue_mgr_->getQueueSize());
    }

    // Iterate over the list of requests, sending and receiving
    // each one. Allow them to accumulate in the queue.
    for (int i = 0; i < VALID_MSG_CNT; i++) {
        // Create the ncr and add to our reference list.
        ASSERT_NO_THROW(send_ncr = NameChangeRequest::fromJSON(valid_msgs[i]));
        ASSERT_NO_THROW(sender_->sendRequest(send_ncr));

        // running two should do the send then the receive
        EXPECT_NO_THROW(io_service_->run_one());
        EXPECT_NO_THROW(io_service_->run_one());
        EXPECT_EQ(i+1, queue_mgr_->getQueueSize());
    }

    // Verify that the queue is at max capacity.
    EXPECT_EQ(queue_mgr_->getMaxQueueSize(), queue_mgr_->getQueueSize());

    // Send another. The send should succeed.
    ASSERT_NO_THROW(sender_->sendRequest(send_ncr));
    EXPECT_NO_THROW(io_service_->run_one());

    // Now execute the receive which should not throw but should move us
    // to STOPPED_QUEUE_FULL state.
    EXPECT_NO_THROW(io_service_->run_one());
    EXPECT_EQ(D2QueueMgr::STOPPED_QUEUE_FULL, queue_mgr_->getMgrState());

    // Verify queue size did not increase beyond max.
    EXPECT_EQ(VALID_MSG_CNT, queue_mgr_->getQueueSize());

    // Verify that setting max queue size to a value less than current size of
    // the queue is not allowed.
    EXPECT_THROW(queue_mgr_->setMaxQueueSize(VALID_MSG_CNT-1), D2QueueMgrError);
    EXPECT_EQ(VALID_MSG_CNT, queue_mgr_->getQueueSize());

    // Verify that we can re-enter RUNNING from STOPPED_QUEUE_FULL.
    EXPECT_NO_THROW(queue_mgr_->startListening());
    EXPECT_EQ(D2QueueMgr::RUNNING, queue_mgr_->getMgrState());

    // Verify that the queue contents were preserved.
    EXPECT_EQ(queue_mgr_->getMaxQueueSize(), queue_mgr_->getQueueSize());

    // Verify that clearQueue works.
    EXPECT_NO_THROW(queue_mgr_->clearQueue());
    EXPECT_EQ(0, queue_mgr_->getQueueSize());


    // Verify that we can again receive requests.
    // Send should be fine.
    ASSERT_NO_THROW(sender_->sendRequest(send_ncr));
    EXPECT_NO_THROW(io_service_->run_one());

    // Receive should succeed.
    EXPECT_NO_THROW(io_service_->run_one());
    EXPECT_EQ(1, queue_mgr_->getQueueSize());
}

} // end of anonymous namespace
