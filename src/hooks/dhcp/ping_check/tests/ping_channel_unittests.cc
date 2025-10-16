// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PingChannel class.

#include <config.h>

#include <ping_channel.h>
#include <ping_test_utils.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service_thread_pool.h>
#include <dhcp/iface_mgr.h>
#include <util/multi_threading_mgr.h>
#include <testutils/multi_threading_utils.h>
#include <testutils/gtest_utils.h>
#include <gtest/gtest.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <queue>
#include <list>
#include <thread>
#include <mutex>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::ping_check;
using namespace isc::util;
using namespace isc::test;
using namespace boost::asio::error;

namespace ph = std::placeholders;

namespace {

/// @brief Tag for index by address.
struct AddressIdSequenceIndexTag { };

/// @brief A multi index container holding pointers ICMPMsgPtr
///
/// The message may be accessed using the following index(es):
/// - using an IPv4 address, id, and sequence number
typedef boost::multi_index_container<
    // It holds pointers to ICMPMsg objects.
    ICMPMsgPtr,
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts PingContexts by IPv4 addresses represented as
        // IOAddress objects.
        // Specification of the first index starts here.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<AddressIdSequenceIndexTag>,
            boost::multi_index::composite_key<
                ICMPMsg,
                // The boolean value specifying if context is waiting for a reply
                boost::multi_index::const_mem_fun<ICMPMsg, const IOAddress&,
                                                  &ICMPMsg::getSource>,
                boost::multi_index::const_mem_fun<ICMPMsg, uint16_t,
                                                  &ICMPMsg::getId>,
                boost::multi_index::const_mem_fun<ICMPMsg, uint16_t,
                                                  &ICMPMsg::getSequence>
            >
        >
    >
> ReplyContainer;

/// @brief Single-threaded test fixture for exercising a PingChannel.
class PingChannelTest : public IOServiceTest {
public:
    /// @brief Constructor
    PingChannelTest() : mutex_(new mutex()), stopped_(false) {
        MultiThreadingMgr::instance().setMode(false);
    };

    /// @brief Destructor
    virtual ~PingChannelTest() {
        stopped_ = true;
        if (channel_) {
            channel_->close();
        }
        if (ios_pool_) {
            ios_pool_->getIOService()->stopAndPoll();
            ios_pool_->stop();
        }
        ios_pool_.reset();
        test_timer_.cancel();
        test_io_service_->stopAndPoll();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Called prior to test destruction.
    /// Ensure we stop the pool in the even a test failed in an unexpected
    /// manner that left it running. Otherwise we can get false TSAN complaints.
    virtual void TearDown() {
        // Stop the thread pool (if one).
        if (ios_pool_) {
            ios_pool_->stop();
        }
    }

    /// @brief Initializes the IOServiceThreadPool
    ///
    /// @param num_threads number of threads in the pool
    /// @param defer_start enables deferred start of the pool's IOService
    void initThreadPool(size_t num_threads = 1, bool defer_start = false) {
        ios_pool_.reset(new IoServiceThreadPool(IOServicePtr(), num_threads, defer_start));
    };

    /// @brief Callback to invoke to fetch the next ping target.
    ///
    /// Fetches the next entry from the front of the send queue (if one).  Checks for
    /// test completion before returning.
    ///
    /// @param[out] next upon return it will contain the next target address.  Contents are
    /// only meaningful if the function returns true.
    ///
    /// @return True another target address exists, false otherwise.
    virtual PingContextPtr nextToSend() {
        if (stopped_) {
            return (PingContextPtr());
        }
        MultiThreadingLock lock(*mutex_);
        if (!send_queue_.empty()) {
            Lease4Ptr lease(new Lease4());
            lease->addr_ = send_queue_.front();
            Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 1234));
            return (PingContextPtr(new PingContext(lease, pkt)));
        }

        stopIfDone();
        return (PingContextPtr());
    }

    /// @brief Callback to call to update context state (does nothing).
    virtual void updateContextToSend(PingContextPtr /* context */) {
    }

    /// @brief Callback to invoke when an ECHO write has completed.
    ///
    /// Ensures the completed echo matches the front of the send queue and then
    /// pops it from the front of the queue. Checks for test completion before
    /// returning.
    ///
    /// @param echo ICMP echo message that as sent
    virtual void echoSent(ICMPMsgPtr& echo, bool send_failed) {
        if (stopped_) {
            return;
        }
        MultiThreadingLock lock(*mutex_);
        ASSERT_EQ(echo->getDestination(), send_queue_.front()) << "send queue mismatch";
        send_queue_.pop();
        if (!send_failed) {
            echos_sent_.push_back(echo);
        }
        stopIfDone();
    }

    /// @brief Callback to invoke when an ICMP reply has been received.
    ///
    /// Stores the reply if it is an ECHO REPLY message.  We check to the
    /// do avoid storing our outbound ECHO REQUESTs when testing with loop back
    /// address.  Checks for test completion before returning.
    ///
    /// @param reply ICMP message that was received
    virtual void replyReceived(ICMPMsgPtr& reply) {
        if (stopped_) {
            return;
        }
        MultiThreadingLock lock(*mutex_);
        if (reply->getType() == ICMPMsg::ECHO_REPLY) {
            // If loopback routing is enabled, Insert the original destination address
            // as the reply's source address.
            if (channel_->route_loopback_) {
                IOAddress address = channel_->loopback_map_.find(reply->getSequence());
                if (address  != IOAddress::IPV4_ZERO_ADDRESS()) {
                    reply->setSource(address);
                }
            }

            replies_received_.push_back(reply);
            storeReply(reply);
        }

        stopIfDone();
    }

    /// @brief Tests that a channel can send and receive, reliably
    /// in either single or multi-threaded mode.
    ///
    /// The test queues the given number of requests, beginning with
    /// address 127.0.0.1 and incrementing the address through the number
    /// of targets.  It then opens the channel and initiates reading and
    /// and writing, running until the test completes or times out.
    /// It expects to receive a reply for every request.
    ///
    /// @param num_threads number of threads in the thread pool. If 0,
    /// the channel will be single-threaded, sharing the test's IOService,
    /// otherwise the channel will be driven by an IOServiceThreadPool with
    /// the given number of threads.
    /// @param num_targets number of target IP addresses to ping. Must not
    /// be greater than 253.
    /// @param set_error_trigger optional function that sets the error trigger
    /// condition.
    void sendReceiveTest(size_t num_threads, size_t num_targets = 25,
                         const std::function<void()>& set_error_trigger = [](){});

    /// @brief Tests for graceful behavior when a channel encounters a read
    /// or write error, in either single or multi-threaded mode.
    ///
    /// The test runs in two passes. The first pass sends and receives until
    /// the error trigger occurs.  The error should induce a graceful cessation
    /// of operations. After verifying expected state of affairs, the second pass
    /// is begun by re-opening the channel and resuming operations until the test
    /// completes or times out.
    ///
    /// @param set_error_trigger function that sets the error trigger condition
    /// @param num_threads number of threads in the thread pool. If 0,
    /// the channel will be single-threaded, sharing the test's IOService,
    /// otherwise the channel will be driven by an IOServiceThreadPool with
    /// the given number of threads.
    /// @param num_targets number of target IP addresses to ping. Must not
    /// be greater than 253.
    void ioErrorTest(const std::function<void()>& set_error_trigger,
                     size_t num_threads, size_t num_targets = 10);

    /// @brief Adds a reply to reply store.
    ///
    /// Fails if a reply for the same address, id, and sequence number is already
    /// in the store.  Must be used in a thread-safe context.
    ///
    /// @param reply reply to store
    void storeReply(ICMPMsgPtr& reply) {
        auto retpair = replies_map_.insert(reply);
        ASSERT_TRUE(retpair.second)
                    << "failed to insert reply for: " << reply->getSource()
                    << ", id: " << reply->getId() << ", sequence: " << reply->getSequence();
    }

    /// @brief Fetches a reply from the store that matches a given ECHO
    ///
    /// Must be used in a thread-safe context.
    ///
    /// @param echo echo for whom a reply is sought
    ///
    /// @return The matching reply if found, otherwise an empty ICMPMsgPtr.
    ICMPMsgPtr findReply(const ICMPMsgPtr& echo) {
        auto const& index = replies_map_.get<AddressIdSequenceIndexTag>();
        auto key = boost::make_tuple(echo->getDestination(), echo->getId(), echo->getSequence());
        auto iter = index.find(key);
        return (iter == index.end() ? ICMPMsgPtr() : *iter);
    }

    /// @brief Channel instance.
    TestablePingChannelPtr channel_;

    /// @brief IoServiceThreadPool instance
    IoServiceThreadPoolPtr ios_pool_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;

    /// @brief Queue of IOAddresses for which to send ECHO REQUESTs.
    std::queue<IOAddress> send_queue_;

    /// @brief List of ECHO REQUESTs that have been successfully sent in the order
    /// they were sent.
    std::list<ICMPMsgPtr> echos_sent_;

    /// @brief List of ECHO REPLYs that have been successfully  received in the
    /// order they were received.
    std::list<ICMPMsgPtr> replies_received_;

    /// @brief Map of ECHO REPLYs received, indexed by source IP, id, and sequence number.
    ReplyContainer replies_map_;

    /// @brief Flag which indicates that the manager has been stopped.
    bool stopped_;
};

// Test fixture used to distinguish tests that require root privileges.
struct RootPingChannelTest : PingChannelTest {};

void
PingChannelTest::sendReceiveTest(size_t num_threads, size_t num_targets /* = 25 */,
                                 const std::function<void()>& set_error_trigger) {
    stopped_ = false;

    // Clear state.
    send_queue_ = {};
    echos_sent_.clear();
    replies_received_.clear();
    replies_map_.clear();

    SKIP_IF(notRoot());

    ASSERT_TRUE(num_targets < 253);
    auto channel_ios = test_io_service_;
    if (num_threads) {
        // Enable MT mode.
        util::MultiThreadingMgr::instance().setMode(true);

        // Initialize the thread pool to num_threads, defer start.
        ASSERT_NO_THROW_LOG(initThreadPool(num_threads, true));
        ASSERT_TRUE(ios_pool_->isStopped());
        channel_ios = ios_pool_->getIOService();
    }

    // Create the channel instance with the appropriate io_service.
    ASSERT_NO_THROW_LOG(channel_.reset(new TestablePingChannel(
        channel_ios,
        std::bind(&PingChannelTest::nextToSend, this),
        std::bind(&PingChannelTest::updateContextToSend, this, ph::_1),
        std::bind(&PingChannelTest::echoSent, this, ph::_1, ph::_2),
        std::bind(&PingChannelTest::replyReceived, this, ph::_1)
    )));

    // Create the callback to check test completion criteria.
    // It returns true if we have sent out all the echos and received
    // all the replies.
    test_done_cb_ = [this]() {
        return (send_queue_.empty() && (echos_sent_.size() == replies_received_.size()));
    };

    //  Fill the send queue with num_target addresses to ping.
    IOAddress target("127.0.0.1");
    for (size_t i = 0; i < num_targets; ++i) {
        send_queue_.push(target);
        target = IOAddress::increase(target);
    }

    (set_error_trigger)();

    // Open the channel.
    ASSERT_NO_THROW_LOG(channel_->open());
    ASSERT_TRUE(channel_->isOpen());

    if (num_threads) {
        ios_pool_->run();
    }

    // Initiate reading and writing.
    ASSERT_NO_THROW_LOG(channel_->startRead());
    ASSERT_NO_THROW_LOG(channel_->startSend());

    // Run the main thread's IOService until we complete or timeout.
    ASSERT_NO_THROW_LOG(runIOService(1000));

    if (ios_pool_) {
        // Stop the thread pool.
        ASSERT_NO_THROW_LOG(ios_pool_->stop());
        ASSERT_TRUE(ios_pool_->isStopped());
    }

    // Send queue should be empty.
    EXPECT_TRUE(send_queue_.empty());

    // Should have as many replies as echos.
    EXPECT_EQ(echos_sent_.size(), replies_received_.size());

    // Should have a reply for every echo.
    for (auto const& echo : echos_sent_) {
        ICMPMsgPtr reply = findReply(echo);
        EXPECT_TRUE(reply) << "no reply found for:" << echo->getDestination()
                           << ", id:" << echo->getId() << ", sequence: " << echo->getSequence();
    }

    stopped_ = true;
    if (channel_) {
        channel_->close();
    }
    if (ios_pool_) {
        ios_pool_->getIOService()->stopAndPoll();
        ios_pool_->stop();
    }
    ios_pool_.reset();
    test_timer_.cancel();
    test_io_service_->stopAndPoll();
    MultiThreadingMgr::instance().setMode(false);
}

void
PingChannelTest::ioErrorTest(const std::function<void()>& set_error_trigger,
                             size_t num_threads, size_t num_targets) {
    ASSERT_TRUE(num_targets < 253);
    SKIP_IF(notRoot());

    ASSERT_TRUE(replies_received_.empty());

    /// If it's an MT test create the thread pool.
    auto channel_ios = test_io_service_;
    if (num_threads) {
        // Enable MT mode.
        util::MultiThreadingMgr::instance().setMode(true);

        // Initialize the thread pool to num_threads, defer start.
        ASSERT_NO_THROW_LOG(initThreadPool(num_threads, true));
        ASSERT_TRUE(ios_pool_->isStopped());
        channel_ios = ios_pool_->getIOService();
    }

    // Set local shutdown called flag to false.
    bool shutdown_cb_called = false;

    // Create the channel instance with the appropriate io_service.
    ASSERT_NO_THROW_LOG(channel_.reset(new TestablePingChannel(
        channel_ios,
        std::bind(&PingChannelTest::nextToSend, this),
        std::bind(&PingChannelTest::updateContextToSend, this, ph::_1),
        std::bind(&PingChannelTest::echoSent, this, ph::_1, ph::_2),
        std::bind(&PingChannelTest::replyReceived, this, ph::_1),
        ([this, &shutdown_cb_called]() {
                shutdown_cb_called = true;
                test_io_service_->stop();
            })
        )));

    // Set the test_done_cb_ to always return false (i.e. test is not
    // done).
    test_done_cb_ = []() {
        return (false);
    };

    //  Fill the send queue with target addresses to ping.
    IOAddress target("127.0.0.1");
    for (size_t i = 0; i < (num_targets / 2); ++i) {
        send_queue_.push(target);
        target = IOAddress::increase(target);
    }

    // Set the error trigger.
    (set_error_trigger)();

    // FIRST PASS

    // Open the channel.
    ASSERT_NO_THROW_LOG(channel_->open());
    ASSERT_TRUE(channel_->isOpen());

    if (num_threads) {
        ios_pool_->run();
    }

    // Initiate reading and writing.
    ASSERT_NO_THROW_LOG(channel_->startRead());
    ASSERT_NO_THROW_LOG(channel_->startSend());

    // Run the main thread's IOService until we stop or timeout.
    ASSERT_NO_THROW_LOG(runIOService(1000));

    // Shutdown callback should have been invoked, the channel should be closed,
    // but the pool should still be running.
    ASSERT_TRUE(shutdown_cb_called);
    ASSERT_FALSE(channel_->isOpen());

    if (ios_pool_) {
        ASSERT_TRUE(ios_pool_->isRunning());

        // Pause the thread pool.
        ASSERT_NO_THROW_LOG(ios_pool_->pause());
        ASSERT_TRUE(ios_pool_->isPaused());
    }

    // Save how many echos sent and replies received during the first pass.
    auto first_pass_echo_count = echos_sent_.size();
    auto first_pass_reply_count = replies_received_.size();

    // Should have sent some but not all.
    EXPECT_LE(first_pass_echo_count, num_targets);

    // SECOND PASS

    // Modify the test done callback to check test completion criteria.
    // It returns true if we have sent out all the echos and received
    // all the replies.
    test_done_cb_ = [this, &first_pass_reply_count]() {
        return (send_queue_.empty() && (replies_received_.size() > first_pass_reply_count));
    };

    //  Fill the send queue with target addresses to ping.
    for (size_t i = 0; i < (num_targets / 2); ++i) {
        send_queue_.push(target);
        target = IOAddress::increase(target);
    }

    // Resume running the thread pool (if one).
    if (ios_pool_) {
        ASSERT_NO_THROW_LOG(ios_pool_->run());
        ASSERT_TRUE(ios_pool_->isRunning());
    }

    // Resume reopening the channel and restarting IO operations.
    ASSERT_NO_THROW_LOG(channel_->open());
    ASSERT_TRUE(channel_->isOpen());
    ASSERT_NO_THROW_LOG(channel_->startRead());
    ASSERT_NO_THROW_LOG(channel_->startSend());

    // Run the main thread's IOService until we complete or timeout.
    ASSERT_NO_THROW_LOG(runIOService(1000));

    // Stop the thread pool (if one).
    if (ios_pool_) {
        ASSERT_NO_THROW_LOG(ios_pool_->stop());
        ASSERT_TRUE(ios_pool_->isStopped());
    }

    // Send queue should be empty.
    EXPECT_TRUE(send_queue_.empty());

    // Should have sent as many echos as we queued.
    EXPECT_EQ(echos_sent_.size(), num_targets);

    // Should have more replies than we had, but likely not all.
    EXPECT_GE(replies_received_.size(), first_pass_reply_count);
}

// Verifies PingChannel open and close operations.
TEST_F(RootPingChannelTest, openCloseST) {
    SKIP_IF(notRoot());

    // Create the channel instance.
    ASSERT_NO_THROW_LOG(channel_.reset(new TestablePingChannel(
        test_io_service_,
        std::bind(&PingChannelTest::nextToSend, this),
        std::bind(&PingChannelTest::updateContextToSend, this, ph::_1),
        std::bind(&PingChannelTest::echoSent, this, ph::_1, ph::_2),
        std::bind(&PingChannelTest::replyReceived, this, ph::_1)
    )));

    ASSERT_TRUE(channel_);

    ASSERT_TRUE(channel_->getSingleThreaded());

    // Verify it is not open.
    ASSERT_FALSE(channel_->isOpen());

    EXPECT_FALSE(channel_->getWatchSocket());
    EXPECT_EQ(channel_->getRegisteredWriteFd(), -1);
    EXPECT_EQ(channel_->getRegisteredReadFd(), -1);

    // Verify that invoking close is harmless.
    ASSERT_NO_THROW_LOG(channel_->close());

    // Attempt to open the channel.
    ASSERT_NO_THROW_LOG(channel_->open());

    // PingChannel::open() is synchronous and while it has a callback
    // it should never be invoked.  Run the service to make sure.
    ASSERT_NO_THROW_LOG(runIOService(1000));

    // Verify the channel is open.
    ASSERT_TRUE(channel_->isOpen());

    // Verify the WatchSocket was created and that its fd and that of the
    // PingSocket are both registered with IfaceMgr.
    ASSERT_TRUE(channel_->getWatchSocket());
    int registered_write_fd = channel_->getRegisteredWriteFd();
    EXPECT_EQ(registered_write_fd, channel_->getWatchSocket()->getSelectFd());
    EXPECT_TRUE(IfaceMgr::instance().isExternalSocket(registered_write_fd));
    int registered_read_fd = channel_->getRegisteredReadFd();
    EXPECT_EQ(registered_read_fd, channel_->getPingSocket()->getNative());
    EXPECT_TRUE(IfaceMgr::instance().isExternalSocket(registered_read_fd));

    // A subsequent open should be harmless.
    ASSERT_NO_THROW_LOG(channel_->open());

    // Closing the socket should work.
    ASSERT_NO_THROW_LOG(channel_->close());

    // Verify watch socket is gone, registered fds are reset, and prior
    // registered fds are no longer registered.
    EXPECT_FALSE(channel_->getWatchSocket());
    EXPECT_EQ(channel_->getRegisteredWriteFd(), -1);
    EXPECT_FALSE(IfaceMgr::instance().isExternalSocket(registered_write_fd));
    EXPECT_EQ(channel_->getRegisteredReadFd(), -1);
    EXPECT_FALSE(IfaceMgr::instance().isExternalSocket(registered_read_fd));

    // Verify it is not open.
    ASSERT_FALSE(channel_->isOpen());
}

// Verifies PingChannel open and close operations.
TEST_F(RootPingChannelTest, openCloseMT) {
    SKIP_IF(notRoot());
    MultiThreadingTest mt;

    // Create the channel instance.
    ASSERT_NO_THROW_LOG(channel_.reset(new TestablePingChannel(
        test_io_service_,
        std::bind(&PingChannelTest::nextToSend, this),
        std::bind(&PingChannelTest::updateContextToSend, this, ph::_1),
        std::bind(&PingChannelTest::echoSent, this, ph::_1, ph::_2),
        std::bind(&PingChannelTest::replyReceived, this, ph::_1)
    )));

    ASSERT_TRUE(channel_);

    ASSERT_FALSE(channel_->getSingleThreaded());

    // Verify it is not open.
    ASSERT_FALSE(channel_->isOpen());

    // Verify that invoking close is harmless.
    ASSERT_NO_THROW_LOG(channel_->close());

    // Attempt to open the channel.
    ASSERT_NO_THROW_LOG(channel_->open());

    // PingChannel::open() is synchronous and while it has a callback
    // it should never be invoked.  Run the service to make sure.
    ASSERT_NO_THROW_LOG(runIOService(1000));

    // Verify the channel is open.
    ASSERT_TRUE(channel_->isOpen());

    // Verify that single-threaded members are not set.
    EXPECT_FALSE(channel_->getWatchSocket());
    EXPECT_EQ(channel_->getRegisteredWriteFd(), -1);
    EXPECT_EQ(channel_->getRegisteredReadFd(), -1);

    // A subsequent open should be harmless.
    ASSERT_NO_THROW_LOG(channel_->open());

    // Closing the socket should work.
    ASSERT_NO_THROW_LOG(channel_->close());

    // Verify it is not open.
    ASSERT_FALSE(channel_->isOpen());
}

// Verifies that a PingChannel can perpetuate sending requests and receiving
// replies when driven by a single-threaded IOService.
TEST_F(RootPingChannelTest, sendReceiveST) {
    sendReceiveTest(0);
}

// Verifies that a PingChannel can perpetuate sending requests and receiving
// replies when driven by a multi-threaded IOServiceThreadPool 3 threads
TEST_F(RootPingChannelTest, sendReceiveMT) {
    // Use a thread pool with 3 threads.
    sendReceiveTest(3);
}

// Verifies that an exception throw from asyncRead triggers graceful channel
// shutdown and that operations can be resumed with a single-threaded channel.
TEST_F(RootPingChannelTest, readExceptionErrorST) {
    ioErrorTest(
        [this]() {
            channel_->throw_on_read_number_ = 5;
        }, 0);
}

// Verifies that an exception throw from asyncRead triggers graceful channel
// shutdown and that operations can be resumed with a multi-threaded channel.
TEST_F(RootPingChannelTest, readExceptionErrorMT) {
    // Use a thread pool with 3 threads.
    ioErrorTest(
        [this]() {
            channel_->throw_on_read_number_ = 5;
        }, 3, 20);
}

// Verifies that a fatal error code passed into socketReadCallback triggers graceful channel
// shutdown and that operations can be resumed with a single-threaded channel.
TEST_F(RootPingChannelTest, readFatalErrorST) {
    ioErrorTest(
        [this]() {
            channel_->ec_on_read_number_ = 3;
            // See boost/asio/error.hpp for error codes
            channel_->read_error_ec_ = make_error_code(fault);
        }, 0);
}

// Verifies that a fatal error code passed into socketReadCallback triggers graceful channel
// shutdown and that operations can be resumed with a single-threaded channel.
TEST_F(RootPingChannelTest, readFatalErrorMT) {
    ioErrorTest(
        [this]() {
            channel_->ec_on_read_number_ = 3;
            // See boost/asio/error.hpp for error codes
            channel_->read_error_ec_ = make_error_code(fault);
        }, 4);
}

// Verifies that a non-fatal, EWOULDBLOCK error passed into socketReadCallback does
// not disrupt reading for a single-threaded channel.
TEST_F(RootPingChannelTest, readAgainErrorST) {
    sendReceiveTest(0, 10,
        [this]() {
            channel_->ec_on_read_number_ = 4;
            // See boost/asio/error.hpp for error codes
            channel_->read_error_ec_ = make_error_code(would_block);
        });
}

// Verifies that a non-fatal, EWOULDBLOCK error passed into socketReadCallback does
// not disrupt reading for a multi-threaded channel.
TEST_F(RootPingChannelTest, readAgainErrorMT) {
    sendReceiveTest(3, 10,
        [this]() {
            channel_->ec_on_read_number_ = 4;
            // See boost/asio/error.hpp for error codes
            channel_->read_error_ec_ = make_error_code(would_block);
        });
}

// Verifies that an exception throw from asyncRead triggers graceful channel
// shutdown and that operations can be resumed with a single-threaded channel.
TEST_F(RootPingChannelTest, writeExceptionErrorST) {
    ioErrorTest(
        [this]() {
            channel_->throw_on_write_number_ = 5;
        }, 0);
}

// Verifies that an exception throw from asyncRead triggers graceful channel
// shutdown and that operations can be resumed with a multi-threaded channel.
TEST_F(RootPingChannelTest, writeExceptionErrorMT) {
    // Use a thread pool with 3 threads.
    ioErrorTest(
        [this]() {
            channel_->throw_on_write_number_ = 5;
        }, 3);
}

// Verifies that a fatal error code passed into socketReadCallback triggers graceful channel
// shutdown and that operations can be resumed with a single-threaded channel.
TEST_F(RootPingChannelTest, writeFatalErrorST) {
    ioErrorTest(
        [this]() {
            channel_->ec_on_write_number_ = 3;
            // See boost/asio/error.hpp for error codes
            channel_->write_error_ec_ = make_error_code(fault);
        }, 0);
}

// Verifies that a fatal error code passed into socketReadCallback triggers graceful channel
// shutdown and that operations can be resumed with a single-threaded channel.
TEST_F(RootPingChannelTest, writeFatalErrorMT) {
    ioErrorTest(
        [this]() {
            channel_->ec_on_write_number_ = 3;
            // See boost/asio/error.hpp for error codes
            channel_->write_error_ec_ = make_error_code(fault);
        }, 4);
}

// Verifies that a non-fatal, EWOULDBLOCK error passed into socketWriteCallback does
// not disrupt writing for a single-threaded channel.
TEST_F(RootPingChannelTest, writeAgainErrorST) {
    sendReceiveTest(0, 10,
        [this]() {
            channel_->ec_on_write_number_ = 6;
            // See boost/asio/error.hpp for error codes
            channel_->write_error_ec_ = make_error_code(would_block);
        });
}

// Verifies that a non-fatal, EWOULDBLOCK error passed into socketWriteCallback
// does not disrupt writing for a multi-threaded channel.
TEST_F(RootPingChannelTest, writeAgainErrorMT) {
    sendReceiveTest(3, 10,
        [this]() {
            channel_->ec_on_write_number_ = 6;
            // See boost/asio/error.hpp for error codes
            channel_->write_error_ec_ = make_error_code(would_block);
        });
}

// Verify the recoverable write errors do not disrupt writing for a
// single-threaded channel.
TEST_F(RootPingChannelTest, writeSendFailedErrorST) {
    SKIP_IF(notRoot());

    std::list<boost::asio::error::basic_errors> errors = {
        boost::asio::error::network_unreachable,
        boost::asio::error::host_unreachable,
        boost::asio::error::network_down,
        boost::asio::error::no_buffer_space,
        boost::asio::error::access_denied
    };

    for (auto const& error : errors) {
        sendReceiveTest(0, 10,
            [this, error]() {
                channel_->ec_on_write_number_ = 6;
                // See boost/asio/error.hpp for error codes
                channel_->write_error_ec_ = make_error_code(error);
            });

        // Sanity check, we should have sent one less than we targeted.
        EXPECT_EQ(echos_sent_.size(), 9);
    }
}

// Verify the recoverable write errors do not disrupt writing for a
// multi-threaded channel.
TEST_F(RootPingChannelTest, writeSendFailedErrorMT) {
    SKIP_IF(notRoot());

    std::list<boost::asio::error::basic_errors> errors = {
        boost::asio::error::network_unreachable,
        boost::asio::error::host_unreachable,
        boost::asio::error::network_down,
        boost::asio::error::no_buffer_space,
        boost::asio::error::access_denied
    };

    for (auto const& error : errors) {
        sendReceiveTest(3, 10,
            [this, error]() {
                channel_->ec_on_write_number_ = 6;
                // See boost/asio/error.hpp for error codes
                channel_->write_error_ec_ = make_error_code(error);
            });

        // Sanity check, we should have sent one less than we targeted.
        EXPECT_EQ(echos_sent_.size(), 9);
    }
}

} // end of anonymous namespace
