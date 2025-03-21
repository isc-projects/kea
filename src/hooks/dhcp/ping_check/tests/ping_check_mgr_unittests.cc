// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PingCheckMgr class.
#include <config.h>

#include <ping_check_mgr.h>
#include <ping_test_utils.h>
#include <cc/data.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <hooks/hooks_manager.h>
#include <util/chrono_time_utils.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>
#include <mutex>
#include <chrono>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::asiolink;
using namespace isc::ping_check;
using namespace isc::hooks;
using namespace isc::test;
using namespace std::chrono;
using namespace boost::asio::error;

namespace ph = std::placeholders;

namespace {

// Sanity check the basics for production class, PingCheckMgr, single-threaded mode.
TEST(PingCheckMgr, basicsST) {
    SKIP_IF(IOServiceTest::notRoot());
    MultiThreadingMgr::instance().setMode(false);

    // Create a multi-threaded manager.
    IOServicePtr main_ios(new IOService());
    PingCheckMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new PingCheckMgr(0)));
    ASSERT_TRUE(mgr);
    mgr->setIOService(main_ios);

    // Sanity check the global configuration. More robust tests are done
    // elsewhere.
    auto& config = mgr->getGlobalConfig();
    EXPECT_TRUE(config->getEnablePingCheck());
    EXPECT_EQ(1, config->getMinPingRequests());
    EXPECT_EQ(100, config->getReplyTimeout());
    EXPECT_EQ(60, config->getPingClttSecs());
    EXPECT_EQ(0, config->getPingChannelThreads());

    // Verify we report as stopped.
    EXPECT_FALSE(mgr->isRunning());
    EXPECT_TRUE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Starting it should be OK.
    ASSERT_NO_THROW_LOG(mgr->start());

    // Verify we report as running.
    EXPECT_TRUE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Pausing it should be harmless.
    ASSERT_NO_THROW_LOG(mgr->pause());

    // Verify we report as running.
    EXPECT_TRUE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Resuming it should be harmless.
    ASSERT_NO_THROW_LOG(mgr->resume());

    // Verify we report as running.
    EXPECT_TRUE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Stopping it should be fine
    ASSERT_NO_THROW_LOG(mgr->stop());

    // Verify we report as stopped.
    EXPECT_FALSE(mgr->isRunning());
    EXPECT_TRUE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Re-starting it should be OK.
    ASSERT_NO_THROW_LOG(mgr->start());

    // Verify we report as running.
    EXPECT_TRUE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Calling destructor when its running should be OK.
    ASSERT_NO_THROW_LOG(mgr.reset());

    main_ios->stopAndPoll();
}

// Sanity check the basics for production class, PingCheckMgr. Bulk of testing
// is done with test derivation, TestPingCheckMgr.
TEST(PingCheckMgr, basicsMT) {
    SKIP_IF(IOServiceTest::notRoot());
    MultiThreadingTest mt;

    // Create a multi-threaded manager.
    IOServicePtr main_ios(new IOService());
    PingCheckMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new PingCheckMgr(3)));
    ASSERT_TRUE(mgr);
    mgr->setIOService(main_ios);

    // Sanity check the global configuration. More robust tests are done
    // elsewhere.
    auto& config = mgr->getGlobalConfig();
    EXPECT_TRUE(config->getEnablePingCheck());
    EXPECT_EQ(1, config->getMinPingRequests());
    EXPECT_EQ(100, config->getReplyTimeout());
    EXPECT_EQ(60, config->getPingClttSecs());
    EXPECT_EQ(3, config->getPingChannelThreads());

    // It should not be running yet.
    EXPECT_FALSE(mgr->isRunning());
    EXPECT_TRUE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Starting it should be OK.
    ASSERT_NO_THROW_LOG(mgr->start());

    // Verify it's running.
    EXPECT_TRUE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Pausing it should be fine.
    ASSERT_NO_THROW_LOG(mgr->pause());

    // Verify it's paused.
    EXPECT_FALSE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_TRUE(mgr->isPaused());

    // Resuming it should be fine.
    ASSERT_NO_THROW_LOG(mgr->resume());

    // Verify it's running.
    EXPECT_TRUE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Stopping it should be fine
    ASSERT_NO_THROW_LOG(mgr->stop());

    // It should not be running.
    EXPECT_FALSE(mgr->isRunning());
    EXPECT_TRUE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Re-starting it should be OK.
    ASSERT_NO_THROW_LOG(mgr->start());

    // Verify it's running.
    EXPECT_TRUE(mgr->isRunning());
    EXPECT_FALSE(mgr->isStopped());
    EXPECT_FALSE(mgr->isPaused());

    // Calling destructor when its running should be OK.
    ASSERT_NO_THROW_LOG(mgr.reset());
}

// Verify basic behavior of PingCheckMgr::configure().
TEST(PingCheckMgr, configure) {
    // Create a manager.
    IOServicePtr main_ios(new IOService());
    PingCheckMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new PingCheckMgr()));
    ASSERT_TRUE(mgr);

    // Verify initial global configuration.
    auto& default_config = mgr->getGlobalConfig();
    EXPECT_TRUE(default_config->getEnablePingCheck());
    EXPECT_EQ(1, default_config->getMinPingRequests());
    EXPECT_EQ(100, default_config->getReplyTimeout());
    EXPECT_EQ(60, default_config->getPingClttSecs());
    EXPECT_EQ(0, default_config->getPingChannelThreads());

    //Create a valid configuration.
    std::string valid_json_cfg =
        R"({
            "enable-ping-check" : false,
            "min-ping-requests" : 2,
            "reply-timeout" : 250,
            "ping-cltt-secs" : 90,
            "ping-channel-threads" : 3
        })";

    auto parameters = Element::fromJSON(valid_json_cfg);

    // Parse it.
    ASSERT_NO_THROW_LOG(mgr->configure(parameters));

    // Verify updated global configuration.
    auto& config = mgr->getGlobalConfig();
    ASSERT_TRUE(config);
    EXPECT_FALSE(config->getEnablePingCheck());
    EXPECT_EQ(2, config->getMinPingRequests());
    EXPECT_EQ(250, config->getReplyTimeout());
    EXPECT_EQ(90, config->getPingClttSecs());
    EXPECT_EQ(3, config->getPingChannelThreads());

    // Create an invalid configuration.
    std::string invalid_json_cfg =
        R"({
            "enable-ping-check" : true,
            "min-ping-requests" : 4,
            "reply-timeout" : 500,
            "ping-cltt-secs" : 45,
            "ping-channel-threads" : 6,
            "bogus" : 0
        })";

    parameters = Element::fromJSON(invalid_json_cfg);

    // Parsing it should throw.
    ASSERT_THROW_MSG(mgr->configure(parameters), DhcpConfigError, "spurious 'bogus' parameter");

    // Verify configuration values were left unchanged.
    auto& final_config = mgr->getGlobalConfig();
    ASSERT_TRUE(final_config);
    EXPECT_EQ(final_config->getEnablePingCheck(), config->getEnablePingCheck());
    EXPECT_EQ(final_config->getMinPingRequests(), config->getMinPingRequests());
    EXPECT_EQ(final_config->getReplyTimeout(), config->getReplyTimeout());
    EXPECT_EQ(final_config->getPingClttSecs(), config->getPingClttSecs());
    EXPECT_EQ(final_config->getPingChannelThreads(), config->getPingChannelThreads());
}

/// @brief Defines a callback to invoke at the bottom of sendCompleted()
typedef std::function<void(const ICMPMsgPtr& echo, bool send_failed)> SendCompletedCallback;

/// @brief Defines a callback to invoke at the bottom of replyReceived()
typedef std::function<void(const ICMPMsgPtr& reply)> ReplyReceivedCallback;

/// @brief Testable derivation of PingCheckMgr
///
/// Uses a TestablePingChannel to facilitate more robust testing.
class TestablePingCheckMgr : public PingCheckMgr {
public:
    /// @brief Constructor.
    ///
    /// @param num_threads number of threads to use in the thread pool (0 means follow
    /// core thread pool size)
    /// @param min_echos minimum number of ECHO REQUESTs sent without replies
    /// received required to declare an address free to offer. Defaults to 1,
    /// must be greater than zero.
    /// @param reply_timeout maximum number of milliseconds to wait for an
    /// ECHO REPLY after an ECHO REQUEST has been sent.  Defaults to 100,
    TestablePingCheckMgr(uint32_t num_threads, uint32_t min_echos = 1,
                         uint32_t reply_timeout = 100)
        : PingCheckMgr(num_threads, min_echos, reply_timeout),
          post_send_completed_cb_(SendCompletedCallback()),
          post_reply_received_cb_(ReplyReceivedCallback()) {
    }

    /// @brief Destructor.
    virtual ~TestablePingCheckMgr() {
        post_send_completed_cb_ = SendCompletedCallback();
        post_reply_received_cb_ = ReplyReceivedCallback();
        if (getIOService()) {
            getIOService()->stopAndPoll();
        }
    }

    /// @brief Fetch the current channel instance.
    ///
    /// @return pointer to the TestablePingChannel instance (or an empty pointer).
    TestablePingChannelPtr getChannel() {
        return (boost::dynamic_pointer_cast<TestablePingChannel>(channel_));
    }

    /// @brief Fetches the manager's context store.
    ///
    /// @return Pointer to the PingContextStore.
    PingContextStorePtr getStore() {
        return (store_);
    }

    /// @brief Fetches the expiration timer's current interval (in milliseconds).
    ///
    /// @return current interval as long or 0L if the timer is not currently
    /// running or does not exist.
    long getExpirationTimerInterval() {
        if (expiration_timer_) {
            return (expiration_timer_->getInterval());
        }

        return (0);
    }

protected:
    /// @brief Creates a TestablePingChannel instance.
    ///
    /// This override the base case creator.
    ///
    /// @param io_service IOService that will drive the channel.
    /// @return pointer to the newly created channel.
    virtual PingChannelPtr createChannel(asiolink::IOServicePtr io_service) {
        return (TestablePingChannelPtr(
            new TestablePingChannel(io_service,
                                    std::bind(&PingCheckMgr::nextToSend, this, ph::_1),
                                    std::bind(&TestablePingCheckMgr::sendCompleted,
                                              this, ph::_1, ph::_2),
                                    std::bind(&TestablePingCheckMgr::replyReceived, this, ph::_1),
                                    std::bind(&PingCheckMgr::channelShutdown, this))));
    }

public:
    /// @brief Fetches the current size of the parking lot.
    ///
    /// @return size_t containing the number of entries parked.
    size_t parkingLotSize() const {
        auto const& parking_lot = ServerHooks::getServerHooks().getParkingLotPtr("lease4_offer");
        return (parking_lot->size());
    }

    /// @brief Callback passed to PingChannel to invoke when an ECHO REQUEST
    /// send has completed.
    ///
    /// -# Invokes the base class implementation
    /// -# Invokes an optional callback
    ///
    /// @param echo ICMP echo message that is sent.
    /// @param send_failed True if the send completed with a non-fatal error,
    /// false otherwise.
    virtual void sendCompleted(const ICMPMsgPtr& echo, bool send_failed) {
        // Call the production callback.
        PingCheckMgr::sendCompleted(echo, send_failed);

        // Invoke the post check, if one.
        if (post_send_completed_cb_) {
            (post_send_completed_cb_)(echo, send_failed);
        }
    }

    /// @brief Callback invoked by the channel to process received ICMP messages.
    ///
    /// -# Invokes the base class implementation
    /// -# Pauses the test IOService thread and returns if the parking lot is empty
    /// -# Invokes an option callback passing in the reply received
    ///
    /// @param reply pointer to the ICMP message received.
    virtual void replyReceived(const ICMPMsgPtr& reply) {
        if (reply->getType() == ICMPMsg::ECHO_REQUEST) {
            return;
        }

        // If we're routing loopback messages, look up the original address based
        // on the sequence number and use it as the reply's source address.
        if (getChannel()->route_loopback_) {
            IOAddress address = getChannel()->loopback_map_.find(reply->getSequence());
            if (address  != IOAddress::IPV4_ZERO_ADDRESS()) {
                reply->setSource(address);
            }
        }

        // Call the production callback.
        PingCheckMgr::replyReceived(reply);

        // Invoke the post check, if one.
        if (post_reply_received_cb_) {
            (post_reply_received_cb_)(reply);
        }
    }

    /// @brief Fetches the thread pool (if it exists).
    ///
    /// @return pointer to theIoServiceThreadPool.  Will be empty
    /// in ST mode or if the manager has not been started.
    asiolink::IoServiceThreadPoolPtr getThreadPool() {
        return (thread_pool_);
    }

    /// @brief Sets the network_state object.
    ///
    /// @param network_state pointer to a NetworkState instance.
    void setNetworkState(NetworkStatePtr network_state) {
        network_state_ = network_state;
    }

    /// @brief Callback to invoke at the bottom of sendCompleted().
    SendCompletedCallback post_send_completed_cb_;

    /// @brief Callback to invoke at the bottom of replyReceived().
    ReplyReceivedCallback post_reply_received_cb_;
};

/// @brief Defines a shared pointer to a PingCheckMgr.
typedef boost::shared_ptr<TestablePingCheckMgr> TestablePingCheckMgrPtr;

/// @brief Holds a lease and its associated query.
struct LeaseQueryPair {
public:
    /// @brief Constructor.
    ///
    /// @param lease pointer to the lease.
    /// @param query pointer to the query.
    LeaseQueryPair(Lease4Ptr lease, Pkt4Ptr query) : lease_(lease), query_(query) {
    };

    /// @brief Pointer to the lease.
    Lease4Ptr lease_;

    /// @brief Pointer to the query.
    Pkt4Ptr query_;
};

/// @brief Container of leases and their associated queries.
typedef std::vector<LeaseQueryPair> LeaseQueryPairs;

/// @brief Test fixture for exercising PingCheckMgr.
///
/// Uses a TestablePingCheckMgr instance for all tests and
/// provides numerous helper functions.
class PingCheckMgrTest : public IOServiceTest {
public:
    /// @brief Constructor.
    PingCheckMgrTest() : mgr_(), lease_query_pairs_(), mutex_(new mutex()),
        test_start_time_(PingContext::now()), unparked_(0) {
        MultiThreadingMgr::instance().setMode(false);
    };

    /// @brief Destructor.
    virtual ~PingCheckMgrTest() {
        test_timer_.cancel();
        test_io_service_->stopAndPoll();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Pretest setup.
    ///
    /// Registers the hook point and creates its parking lot.
    virtual void SetUp() {
        HooksManager::registerHook("lease4_offer");
        parking_lot_ = boost::make_shared<ParkingLotHandle>(
                        ServerHooks::getServerHooks().getParkingLotPtr("lease4_offer"));
    }

    /// @brief Ensure we stop cleanly.
    virtual void TearDown() {
        if (mgr_) {
            mgr_->stop();
        }

        HooksManager::clearParkingLots();
    }

    /// @brief Creates the test's manager instance.
    ///
    /// @param num_threads number of threads in the thread pool.
    /// @param min_echos minimum number of echos per ping check.
    /// @param reply_timeout reply timeout per ping.
    /// @param start_and_pause when false, the manager is only created,
    /// when true it is created, started and then paused.  This allows
    /// manipulation of context store contents while the threads are doing
    /// no work.
    void createMgr(uint32_t num_threads,
                   uint32_t min_echos = 1,
                   uint32_t reply_timeout = 100,
                   bool start_and_pause = false) {
        ASSERT_NO_THROW_LOG(
            mgr_.reset(new TestablePingCheckMgr(num_threads, min_echos, reply_timeout)));
        ASSERT_TRUE(mgr_);
        mgr_->setIOService(test_io_service_);

        if (start_and_pause) {
            ASSERT_NO_THROW_LOG(mgr_->start());

            if (!MultiThreadingMgr::instance().getMode()) {
                ASSERT_FALSE(mgr_->getThreadPool());
            } else {
                ASSERT_TRUE(mgr_->getThreadPool());
                ASSERT_NO_THROW_LOG(mgr_->pause());
                ASSERT_TRUE(mgr_->isPaused());
            }
        }
    }

    /// @brief Add a new lease and query pair to the test's list of lease query pairs.
    ///
    /// Creates a bare-bones DHCPv4 lease and DHCPDISCOVER, wraps them in a
    /// LeaseQueryPair and adds the pair to the end of the test's internal
    /// list of pairs, lease_query_pairs_.
    ///
    /// @param target IOAddress of the lease.
    /// @param transid transaction id of the query.
    ///
    /// @return A copy of the newly created pair.
    LeaseQueryPair makeLeaseQueryPair(IOAddress target, uint16_t transid) {
        // Make a lease and query pair
        Lease4Ptr lease(new Lease4());
        lease->addr_ = IOAddress(target);
        Pkt4Ptr query(new Pkt4(DHCPDISCOVER, transid));
        LeaseQueryPair lqp(lease, query);
        lease_query_pairs_.push_back(lqp);
        return (lqp);
    }

    /// @brief Start ping checks for a given number of targets.
    ///
    /// The function first creates and parks the given number of targets, and
    /// then starts a ping check for each of them. Parking them all first
    /// establishes the number of ping checks expected to be conducted during
    /// the test prior to actually starting any of them. This avoids the
    /// parking lot from becoming empty part way through the test.
    ///
    /// It unpark callback lambda increments the unparked_ counter and then
    /// pushes the unparked lease/query pair to either the list of frees
    /// or list of declines.
    ///
    /// @param num_targets number of target ip addresses to ping check.
    /// @param start_address starting target address. Defaults to 127.0.0.1.
    ///
    /// @return last target address started.
    IOAddress startTargets(size_t num_targets, IOAddress start_address = IOAddress("127.0.0.1")) {
        IOAddress target = start_address;
        for (auto i = 0; i < num_targets; ++i) {
            auto lqp = makeLeaseQueryPair(IOAddress(target), i+1);
            HooksManager::park("lease4_offer", lqp.query_,
                [this, lqp]() {
                    MultiThreadingLock lock(*mutex_);
                    ++unparked_;
                    auto handle = lqp.query_->getCalloutHandle();
                    bool offer_address_in_use;
                    handle->getArgument("offer_address_in_use", offer_address_in_use);
                    offer_address_in_use ?  declines_.push_back(lqp) : frees_.push_back(lqp);
               });

            try {
                mgr_->startPing(lqp.lease_, lqp.query_, parking_lot_);
            } catch (const std::exception& ex) {
                ADD_FAILURE() << "startPing threw: " << ex.what();
            }

            target = IOAddress::increase(target);
        }

        return(target);
    }

    /// @brief Fetches the context, by lease address, from the store for a
    /// given lease query pair.
    ///
    /// @param lqp LeaseQueryPair for which the context is desired.
    /// @return pointer to the found context or an empty pointer.
    PingContextPtr getContext(const LeaseQueryPair& lqp) {
        return (getContext(lqp.lease_->addr_));
    }

    /// @brief Fetches the context, by lease address, from the store for address.
    ///
    /// @param address lease ip address for which the context is desired.
    /// @return pointer to the found context or an empty pointer.
    PingContextPtr getContext(const IOAddress& address) {
        return (mgr_->getStore()->getContextByAddress(address));
    }

    /// @brief Updates a context in the store.
    ///
    /// @param context context to update.
    void updateContext(PingContextPtr& context) {
        ASSERT_NO_THROW_LOG(mgr_->getStore()->updateContext(context));
    }

    /// @brief Tests equality of two timestamps within a given tolerance.
    ///
    /// The two time stamps are considered equal if the absolute value of their
    /// difference is between 0 and the specified tolerance (inclusive).
    ///
    /// @param lhs first TimeStamp to compare.
    /// @param rhs second TimeStamp to compare.
    /// @param tolerance margin of difference allowed for equality in milliseconds.
    /// Defaults to 10.
    ///
    /// @return True if the time stamps are "equal", false otherwise.
    bool fuzzyEqual(const TimeStamp& lhs, const TimeStamp& rhs, long tolerance = 10) {
        auto diff = abs(duration_cast<milliseconds>(lhs - rhs).count());
        return (diff >= 0 && diff <= tolerance);
    }

    /// @brief Tests equality of two longs within a given tolerance.
    ///
    /// The two values are considered equal if the absolute value of their
    /// difference is between 0 and the specified tolerance (inclusive).
    ///
    /// @param lhs first value to compare.
    /// @param rhs second value to compare.
    /// @param tolerance margin of difference allowed for equality in milliseconds.
    /// Defaults to 10.
    ///
    /// @return True if the time values are "equal", false otherwise.
    bool fuzzyEqual(const long& lhs, const long& rhs, long tolerance = 10) {
        auto diff = abs(lhs - rhs);
        return (diff >= 0 && diff <= tolerance);
    }

    /// @brief Creates an ECHO REQUEST message from a given address.
    ///
    /// @param target ip address to use as the echo's destination address.
    /// @return Pointer to the new message.
    ICMPMsgPtr makeEchoRequest(const IOAddress& target) {
        ICMPMsgPtr msg(new ICMPMsg());
        msg->setType(ICMPMsg::ECHO_REQUEST);
        msg->setDestination(IOAddress(target));
        msg->setSource(IOAddress("127.0.0.1"));
        return (msg);
    }

    /// @brief Creates an ECHO_REPLY message from a given address.
    ///
    /// @param from ip address to use as the reply's source address.
    /// @return Pointer to the new message.
    ICMPMsgPtr makeEchoReply(const IOAddress& from) {
        ICMPMsgPtr msg(new ICMPMsg());
        msg->setType(ICMPMsg::ECHO_REPLY);
        msg->setSource(IOAddress(from));
        msg->setDestination(IOAddress("127.0.0.1"));
        return (msg);
    }

    /// @brief Creates an TARGET_UNREACHABLE message from a given address.
    ///
    /// @param target ip address to use as the reply's source address.
    /// @return Pointer to the new message.
    ICMPMsgPtr makeUnreachable(const IOAddress& target) {
        // Make the TARGET_UNREACHABLE message first.
        ICMPMsgPtr msg(new ICMPMsg());
        msg->setType(ICMPMsg::TARGET_UNREACHABLE);
        msg->setSource(IOAddress("127.0.0.1"));
        msg->setDestination(IOAddress("127.0.0.1"));

        // Now embed the ping target's "original" echo into the unreachable
        // message's payload.  This includes the IP header followed by the
        // ECHO REQUEST.  First make the IP header and add it to the payload.
        // We only set values we care about.
        struct ip ip_header;
        memset((void *)(&ip_header), 0x00, sizeof(struct ip));
        ip_header.ip_v = 4;
        ip_header.ip_hl = 5;     /* shift left twice = 20 */
        ip_header.ip_len = 48;   /* ip_header + echo length */
        ip_header.ip_dst.s_addr = htonl(target.toUint32());
        ip_header.ip_src.s_addr = htonl(msg->getSource().toUint32());
        msg->setPayload((const uint8_t*)(&ip_header), sizeof(struct ip));

        // Now make the ECHO_REQUEST, pack it and add that to the payload.
        ICMPMsgPtr echo = makeEchoRequest(target);
        ICMPPtr packed_echo = echo->pack();
        msg->setPayload((const uint8_t*)(packed_echo.get()), sizeof(struct icmp));

        return (msg);
    }

    /// @brief Compares a LeaseQueryPair collection to the internal collection
    /// of pairs created (see makeLeaseQueryPairs()).
    ///
    /// @param test_collection Collection of pairs to compare against those in
    /// the creation collection.
    void compareLeaseQueryPairs(LeaseQueryPairs& test_collection) {
        // We should have as many in the test_collection as we have creation
        // collection.
        ASSERT_EQ(test_collection.size(), lease_query_pairs_.size());

        // Order is not guaranteed so we sort both lists then compare.
        std::sort(test_collection.begin(), test_collection.end(),
            [](LeaseQueryPair const& a, LeaseQueryPair const& b)
                { return (a.lease_->addr_ < b.lease_->addr_); });

        std::sort(lease_query_pairs_.begin(), lease_query_pairs_.end(),
            [](LeaseQueryPair const& a, LeaseQueryPair const& b)
                { return (a.lease_->addr_ < b.lease_->addr_); });

        auto dpi = test_collection.begin();
        for (auto const& lqpi : lease_query_pairs_) {
            ASSERT_EQ((*dpi).lease_->addr_, lqpi.lease_->addr_);
            ++dpi;
        }
    }

    /// @brief Exercises the operational basics: create, start, and stop
    /// for TestablePingCheckMgr.
    ///
    /// @param num_threads number of threads in the thread pool.
    void testOperationalBasics(size_t num_threads) {
        SKIP_IF(notRoot());

        // Create manager with the given number of threads.
        ASSERT_NO_THROW_LOG(createMgr(num_threads));
        ASSERT_TRUE(mgr_);

        // Should not be running.
        EXPECT_FALSE(mgr_->isRunning());
        EXPECT_TRUE(mgr_->isStopped());
        EXPECT_FALSE(mgr_->isPaused());

        // Channel should not yet exist.
        ASSERT_FALSE(mgr_->getChannel());

        // Start the manager.
        ASSERT_NO_THROW_LOG(mgr_->start());

        // Thread pool should exist in MT mode only.
        if (MultiThreadingMgr::instance().getMode()) {
            ASSERT_TRUE(mgr_->getThreadPool());
        } else {
            ASSERT_FALSE(mgr_->getThreadPool());
        }

        // Should be running.
        EXPECT_TRUE(mgr_->isRunning());
        EXPECT_FALSE(mgr_->isStopped());
        EXPECT_FALSE(mgr_->isPaused());

        // Channel should exist and be open.
        auto channel = mgr_->getChannel();
        ASSERT_TRUE(channel);
        ASSERT_TRUE(channel->isOpen());

        // Context store should exist and be empty.
        auto store = mgr_->getStore();
        ASSERT_TRUE(store);
        auto pings = store->getAll();
        ASSERT_EQ(0, pings->size());

        // Destruction should be graceful.
        ASSERT_NO_THROW_LOG(mgr_.reset());
    }

    /// @brief Verifies that startPing() creates a new context in the store and
    /// it can be fetched with the nextToSend() callback.
    void testStartPing() {
        SKIP_IF(notRoot());

        // Create manager with thread-pool size of 3, min_echos 2, reply_timeout 250 ms.
        // ST mode should ingore requested thread number.
        ASSERT_NO_THROW_LOG(createMgr(3, 2, 250));
        ASSERT_TRUE(mgr_);

        // Make a lease and query pair
        auto lqp1 = makeLeaseQueryPair(IOAddress("127.0.0.101"), 101);

        // Channel isn't open, startPing should throw.
        ASSERT_THROW_MSG(mgr_->startPing(lqp1.lease_, lqp1.query_, parking_lot_), InvalidOperation,
                         "PingCheckMgr::startPing() - channel isn't open");

        // Start the manager.  This will open the channel.
        ASSERT_NO_THROW_LOG(mgr_->start());
        ASSERT_TRUE(mgr_->isRunning());

        if (mgr_->getThreadPool()) {
            // Pause the manager so startPing() will succeed but no events will occur.
            // This should let us add contexts that sit in WAITING_TO_SEND state.
            ASSERT_NO_THROW_LOG(mgr_->pause());
            ASSERT_TRUE(mgr_->isPaused());
        }

        // Call startPing() again. It should work.
        ASSERT_NO_THROW_LOG(mgr_->startPing(lqp1.lease_, lqp1.query_, parking_lot_));

        // Calling  startPing() on the same lease should fail, duplicates not allowed.
        ASSERT_THROW_MSG(mgr_->startPing(lqp1.lease_, lqp1.query_, parking_lot_), DuplicateContext,
                         "PingContextStore::addContex: context already exists for: 127.0.0.101");

        // Our context should be present.
        auto const& store = mgr_->getStore();
        auto pings = store->getAll();
        ASSERT_EQ(1, pings->size());
        PingContextPtr context1;
        ASSERT_NO_THROW_LOG(context1 = store->getContextByAddress(lqp1.lease_->addr_));
        ASSERT_TRUE(context1);

        // Verify the context's state.
        EXPECT_EQ(2, context1->getMinEchos());
        EXPECT_EQ(250, context1->getReplyTimeout());
        EXPECT_EQ(0, context1->getEchosSent());
        EXPECT_EQ(PingContext::EMPTY_TIME(), context1->getLastEchoSentTime());
        EXPECT_LE(test_start_time_, context1->getSendWaitStart());
        EXPECT_EQ(PingContext::EMPTY_TIME(), context1->getNextExpiry());
        EXPECT_LE(test_start_time_, context1->getCreatedTime());
        EXPECT_EQ(lqp1.lease_, context1->getLease());
        EXPECT_EQ(lqp1.query_, context1->getQuery());
        EXPECT_EQ(PingContext::WAITING_TO_SEND, context1->getState());

        // Sleep a bit to make sure there's a difference in context times.
        usleep(5);

        // Make a second lease and query pair
        auto lqp2 = makeLeaseQueryPair(IOAddress("127.0.0.102"), 102);

        // Start a ping for lease2.
        ASSERT_NO_THROW_LOG(mgr_->startPing(lqp2.lease_, lqp2.query_, parking_lot_));

        // Both contexts should be present.
        pings = store->getAll();
        ASSERT_EQ(2, pings->size());

        // Fetch the second context by address.
        PingContextPtr context2;
        ASSERT_NO_THROW_LOG(context2 = store->getContextByAddress(lqp2.lease_->addr_));
        ASSERT_TRUE(context2);

        // Verify the second context's state.
        EXPECT_EQ(2, context2->getMinEchos());
        EXPECT_EQ(250, context2->getReplyTimeout());
        EXPECT_EQ(0, context2->getEchosSent());
        EXPECT_EQ(PingContext::EMPTY_TIME(), context2->getLastEchoSentTime());
        // Its send_wait_start_time_ should be more recent than context1.
        EXPECT_LE(context1->getSendWaitStart(), context2->getSendWaitStart());
        EXPECT_EQ(PingContext::EMPTY_TIME(), context2->getNextExpiry());
        // Its created_time_ should be more recent than context1.
        EXPECT_LE(context1->getCreatedTime(), context2->getCreatedTime());
        EXPECT_EQ(lqp2.lease_, context2->getLease());
        EXPECT_EQ(lqp2.query_, context2->getQuery());
        EXPECT_EQ(PingContext::WAITING_TO_SEND, context2->getState());
    }

    /// @brief Exercises PingCheckMgr::nextToSend().
    void testNextToSend() {
        SKIP_IF(notRoot());

        // Create a paused manager. 3 threads, 2 echos, 250 ms timeout.
        // ST mode should ingore requested thread number.
        createMgr(3, 2, 250, true);

        // Calling nextToSend() should return false.
        IOAddress next("0.0.0.0");
        ASSERT_FALSE(mgr_->nextToSend(next));

        // Now let's start 3 contexts.
        size_t num_targets = 3;
        IOAddress target("127.0.0.1");
        for (auto i = 0; i < num_targets; ++i) {
            auto lqp = makeLeaseQueryPair(IOAddress(target), i+1);

            // Call startPing().
            ASSERT_NO_THROW_LOG(mgr_->startPing(lqp.lease_, lqp.query_, parking_lot_));
            target = IOAddress::increase(target);

            PingContextPtr context = getContext(lqp);
            ASSERT_TRUE(context);

            // Verify the context's initial state is correct.
            EXPECT_EQ(0, context->getEchosSent());
            EXPECT_EQ(PingContext::EMPTY_TIME(), context->getLastEchoSentTime());
            EXPECT_LE(test_start_time_, context->getSendWaitStart());
            EXPECT_EQ(PingContext::EMPTY_TIME(), context->getNextExpiry());
            EXPECT_LE(test_start_time_, context->getCreatedTime());
            EXPECT_EQ(PingContext::WAITING_TO_SEND, context->getState());

            // Sleep a few before we add the next one to ensure ordering by
            // time is consistent.
            usleep(5);
        }

        // Consecutive calls to nextToSend() should return target addresses
        // in the order they were created.
        for (auto const& lqp : lease_query_pairs_) {
            // Next to send should return the next address to send.
            ASSERT_TRUE(mgr_->nextToSend(next));

            // It should match the lease as created.
            ASSERT_EQ(next, lqp.lease_->addr_);

            // Fetch the corresponding context.
            PingContextPtr context = getContext(next);
            ASSERT_TRUE(context);

            // Verify the state has properly moved to SENDING.
            EXPECT_EQ(0, context->getEchosSent());
            EXPECT_EQ(PingContext::EMPTY_TIME(), context->getLastEchoSentTime());
            EXPECT_EQ(PingContext::EMPTY_TIME(), context->getNextExpiry());
            EXPECT_EQ(PingContext::SENDING, context->getState());
        }

        // A final call to nextToSend should return false.
        ASSERT_FALSE(mgr_->nextToSend(next));
    }

    /// @brief Exercises PingCheckMgr::setNextExpiration.
    void testSetNextExpiration() {
        SKIP_IF(notRoot());

        // Create a paused manager. 3 threads, 2 echos, 500 ms timeout.
        // ST mode should ingore requested thread number.
        createMgr(3, 2, 500, true);

        // Should not have an expiration time, timer should not be running.
        ASSERT_EQ(PingContext::EMPTY_TIME(), mgr_->getNextExpiry());
        ASSERT_EQ(mgr_->getExpirationTimerInterval(), 0);

        // Now let's start 3 contexts.
        size_t num_targets = 3;
        IOAddress target("127.0.0.1");
        for (auto i = 0; i < num_targets; ++i) {
            auto lqp = makeLeaseQueryPair(IOAddress(target), i+1);

            // Call startPing().
            ASSERT_NO_THROW_LOG(mgr_->startPing(lqp.lease_, lqp.query_, parking_lot_));
            target = IOAddress::increase(target);
        }

        // Still should not have an expiration time nor running timer.
        ASSERT_EQ(PingContext::EMPTY_TIME(), mgr_->getNextExpiry());
        EXPECT_EQ(mgr_->getExpirationTimerInterval(), 0);

        // Simulate a completed send for the second context.
        PingContextPtr context2;
        context2 = getContext(lease_query_pairs_[1]);
        ASSERT_TRUE(context2);
        context2->beginWaitingForReply(test_start_time_ - milliseconds(50));
        updateContext(context2);

        // Call setNextExpiration().
        ASSERT_NO_THROW_LOG(mgr_->setNextExpiration());

        // Refresh the context.
        context2 = getContext(lease_query_pairs_[1]);

        // Verify the mgr has the same next expiration as the context and
        // that the expiration timer is running. Allow for some fudge in
        // the checks.
        auto original_mgr_expiry = mgr_->getNextExpiry();
        EXPECT_TRUE(fuzzyEqual(original_mgr_expiry, context2->getNextExpiry()));

        auto original_interval = mgr_->getExpirationTimerInterval();
        EXPECT_TRUE(fuzzyEqual(original_interval, 450));

        // Simulate a completed send for the third context.
        PingContextPtr context3;
        context3 = getContext(lease_query_pairs_[2]);
        ASSERT_TRUE(context3);
        context3->beginWaitingForReply();
        updateContext(context3);

        // Call setNextExpiration().
        ASSERT_NO_THROW_LOG(mgr_->setNextExpiration());

        // Refresh the context.
        context3 = getContext(lease_query_pairs_[2]);

        // Context3 should have a later expiration than context2.
        EXPECT_LT(context2->getNextExpiry(), context3->getNextExpiry());

        // Expiration and timer should still match the original values based on
        // the second context.
        EXPECT_TRUE(fuzzyEqual(mgr_->getNextExpiry(), original_mgr_expiry));
        EXPECT_EQ(mgr_->getExpirationTimerInterval(), original_interval);

        // Simulate a completed send for the first context but use a smaller
        // timeout and back date it.
        PingContextPtr context1;
        context1 = getContext(lease_query_pairs_[0]);
        ASSERT_TRUE(context1);
        context1->setReplyTimeout(50);
        context1->beginWaitingForReply(test_start_time_ - milliseconds(1));
        updateContext(context1);

        // Call setNextExpiration().
        ASSERT_NO_THROW_LOG(mgr_->setNextExpiration());

        // Refresh the context.
        context1 = getContext(lease_query_pairs_[0]);

       // Context1 should have a earlier expiration than context2.
        EXPECT_LT(context1->getNextExpiry(), context2->getNextExpiry());
        // Timer interval should be based on context1.
        EXPECT_TRUE(fuzzyEqual(mgr_->getExpirationTimerInterval(), 50, 20))
                    << " interval: " << mgr_->getExpirationTimerInterval();

        // Move all contexts to TARGET_FREE.  This should leave none
        // still waiting.
        context1->setState(PingContext::TARGET_FREE);
        updateContext(context1);
        context2->setState(PingContext::TARGET_FREE);
        updateContext(context2);
        context3->setState(PingContext::TARGET_FREE);
        updateContext(context3);

        // Call setNextExpiration().
        ASSERT_NO_THROW_LOG(mgr_->setNextExpiration());

        // Should not have an expiration time, timer should not be running.
        ASSERT_EQ(PingContext::EMPTY_TIME(), mgr_->getNextExpiry());
        ASSERT_EQ(mgr_->getExpirationTimerInterval(), 0);
    }

    /// @brief Exercises PingCheckMgr::sendCompleted.
    void testSendCompleted() {
        SKIP_IF(notRoot());

        // Create a paused manager. 3 threads, 2 echos, 500 ms timeout.
        // ST mode should ingore requested thread number.
        createMgr(3, 2, 500, true);

        // Start a ping for an address so we have a context.
        IOAddress target("127.0.0.2");
        auto lqp = makeLeaseQueryPair(IOAddress(target), 102);

        // Call startPing().
        ASSERT_NO_THROW_LOG(mgr_->startPing(lqp.lease_, lqp.query_, parking_lot_));

        // Simulate a completed send for the context.
        PingContextPtr context;
        context = getContext(lqp);
        ASSERT_TRUE(context);

        // Make an ECHO REQUEST packet based on context.
        ICMPMsgPtr echo_request = makeEchoRequest(context->getLease()->addr_);

        // Invoke sendCompleted() with fabricated request. Should succeed.
        ASSERT_NO_THROW_LOG(mgr_->sendCompleted(echo_request, false));

        // Refresh the context.
        context = getContext(context->getLease()->addr_);

        EXPECT_EQ(PingContext::WAITING_FOR_REPLY, context->getState());
        EXPECT_EQ(1, context->getEchosSent());
        EXPECT_GE(context->getLastEchoSentTime(), test_start_time_);

        // Verify the mgr has the same next expiration as the context and
        // that the expiration timer is running. Allow for some fudge in
        // the checks.
        EXPECT_GT(context->getNextExpiry(), test_start_time_);
        EXPECT_TRUE(fuzzyEqual(mgr_->getNextExpiry(), context->getNextExpiry()));
        EXPECT_TRUE(fuzzyEqual(mgr_->getExpirationTimerInterval(), 500));

        // Make an ECHO REQUEST packet for an address that has no context.
        echo_request = makeEchoRequest(IOAddress("192.168.0.1"));

        // Invoking sendCompleted() with request for a non-existent address be harmless.
        ASSERT_NO_THROW_LOG(mgr_->sendCompleted(echo_request, false));

        // Invoking sendCompleted() with an invalid message type should be harmless.
        echo_request->setType(ICMPMsg::ECHO_REPLY);
        ASSERT_NO_THROW_LOG(mgr_->sendCompleted(ICMPMsgPtr(), false));

        // Invoking sendCompleted() with an empty message should be harmless.
        echo_request.reset();
        ASSERT_NO_THROW_LOG(mgr_->sendCompleted(ICMPMsgPtr(), false));

        // Verify expiration values should not have not been altered.
        EXPECT_TRUE(fuzzyEqual(mgr_->getNextExpiry(), context->getNextExpiry()));
        EXPECT_TRUE(fuzzyEqual(mgr_->getExpirationTimerInterval(), 500));
    }

    /// @brief Exercises PingCheckMgr::replyReceived() for ECHO REPLYs. Note this
    /// also exercises handleEchoReply().
    void testReplyReceivedForEchoReply() {
        SKIP_IF(notRoot());

        // Create a paused manager. 3 threads, 2 echos, 500 ms timeout.
        // ST mode should ingore requested thread number.
        createMgr(3, 2, 500, true);

        // Install a post reply received callback to stop the test if we're done.
        mgr_->post_reply_received_cb_ =
            [this](const ICMPMsgPtr& /* reply */) {
                MultiThreadingLock lock(*mutex_);
                if (mgr_->parkingLotSize() == 0) {
                    stopTestService();
                    return;
                }
            };

        // Turn off loopback routing.
        mgr_->getChannel()->route_loopback_ = false;

        // Start a ping for an address so we have a context.
        startTargets(1);
        auto lqp = lease_query_pairs_[0];

        // Simulate a completed send for the context.
        PingContextPtr context;
        context = getContext(lqp);
        ASSERT_TRUE(context);

        // Make an ECHO REQUEST packet based on context and invoke sendCompleted().
        ICMPMsgPtr echo_request = makeEchoRequest(context->getLease()->addr_);
        ASSERT_NO_THROW_LOG(mgr_->sendCompleted(echo_request, false));

        // Should still have one parked query.
        EXPECT_EQ(1, mgr_->parkingLotSize());

        // Verify the expiration timer is running.
        EXPECT_TRUE(fuzzyEqual(mgr_->getExpirationTimerInterval(), 500));

        // Make an ECHO REPLY packet based on context and invoke replyReceived().
        ICMPMsgPtr echo_reply = makeEchoReply(context->getLease()->addr_);
        ASSERT_NO_THROW_LOG(mgr_->replyReceived(echo_reply));

        // Verify the expiration timer is no longer running.
        EXPECT_EQ(mgr_->getExpirationTimerInterval(), 0);

        // The context should no longer be in the store.
        EXPECT_FALSE(getContext(lqp));

        // We should have dropped the query from the lot rather than unparking it.
        EXPECT_EQ(mgr_->parkingLotSize(), 0);
        EXPECT_EQ(unparked_, 1);

        // We should have one decline that matches our lease query pair.
        compareLeaseQueryPairs(declines_);

        // Make an ECHO REPLY packet for an address that has no context.
        echo_reply = makeEchoReply(IOAddress("192.168.0.1"));

        // Invoke replyReceived() for a reply with no matching context,
        // it should not throw.
        ASSERT_NO_THROW_LOG(mgr_->PingCheckMgr::replyReceived(echo_reply));

        // Invoke replyReceived() an empty message, it should not throw.
        // (Bypass test implementation for this check).
        echo_reply.reset();
        ASSERT_NO_THROW_LOG(mgr_->PingCheckMgr::replyReceived(echo_reply));
    }

    /// @brief Exercises PingCheckMgr::replyReceived() for UNREACHABLEs. Note this
    /// also exercises handleTargetUnreachable().
    void testReplyReceivedForTargetUnreachable() {
        SKIP_IF(notRoot());

        // Create a paused manager. 3 threads, 2 echos, 500 ms timeout.
        // ST mode should ingore requested thread number.
        createMgr(3, 2, 500, true);

        // Install a post reply received callback to stop the test if we're done.
        mgr_->post_reply_received_cb_ =
            [this](const ICMPMsgPtr& /* reply */) {
                MultiThreadingLock lock(*mutex_);
                if (mgr_->parkingLotSize() == 0) {
                    stopTestService();
                    return;
                }
            };

        // Turn off loopback routing.
        mgr_->getChannel()->route_loopback_ = false;

        // Start a ping for an address so we have a context.
        startTargets(1);
        auto lqp = lease_query_pairs_[0];

        // Simulate a completed send for the context.
        PingContextPtr context;
        context = getContext(lqp);
        ASSERT_TRUE(context);

        // Make an ECHO REQUEST packet based on context and invoke sendCompleted().
        ICMPMsgPtr echo_request = makeEchoRequest(context->getLease()->addr_);
        ASSERT_NO_THROW_LOG(mgr_->sendCompleted(echo_request, false));

        // Should still have one parked query.
        EXPECT_EQ(1, mgr_->parkingLotSize());

        // Verify the expiration timer is running.
        EXPECT_TRUE(fuzzyEqual(mgr_->getExpirationTimerInterval(), 500));

        // Make an ECHO REPLY packet based on context and invoke replyReceived().
        ICMPMsgPtr unreachable = makeUnreachable(context->getLease()->addr_);
        ASSERT_NO_THROW_LOG(mgr_->replyReceived(unreachable));

        // Verify the expiration timer is no longer running.
        EXPECT_EQ(mgr_->getExpirationTimerInterval(), 0);

        // The context should no longer be in the store.
        EXPECT_FALSE(getContext(lqp));

        // We should have unparked the query from the lot.
        EXPECT_EQ(mgr_->parkingLotSize(), 0);
        EXPECT_EQ(unparked_, 1);

        // We should have one free that matches our lease query pair.
        compareLeaseQueryPairs(frees_);

        // Invoke replyReceived() for an unreachable with no matching context,
        // it should not throw.
        unreachable = makeUnreachable(IOAddress("192.168.0.1"));
        ASSERT_NO_THROW_LOG(mgr_->replyReceived(unreachable));
    }

    /// @brief Verifies expiration processing by invoking expirationTimedout().
    /// This also exercises processExpiredSince(), doNextEcho(), finishFree(),
    /// and setNextExpiration().
    void testExpirationProcessing() {
        SKIP_IF(notRoot());

        // Create a paused manager. 3 threads, 1 echos, 250 ms timeout.
        // ST mode should ingore requested thread number.
        createMgr(3, 1, 250, true);

        // Start four ping checks, then stage them so:
        //
        // First context is WAITING_TO_SEND, no expiry.
        // Second context is WAITING_FOR_REPLY, has expired and has
        // exhausted min_echos_.
        // Third context is  WAITING_FOR_REPLY, has expired but has
        // not exhausted min_echos_.
        // Fourth context is WAITING_FOR_REPLY but has not yet expired.
        //
        size_t num_targets = 4;

        // Start the desired number of targets with an unpark callback
        // that increments the unparked count.
        startTargets(num_targets);

        // Now establish the desired state for each context.
        // First context is in WAITING_TO_SEND, no expiry.
        PingContextPtr context1 = getContext(lease_query_pairs_[0]);
        ASSERT_TRUE(context1);
        EXPECT_EQ(context1->getState(), PingContext::WAITING_TO_SEND);

        // Second context setup: expired and has exhausted min_echos_
        PingContextPtr context2 = getContext(lease_query_pairs_[1]);
        ASSERT_TRUE(context2);
        context2->beginWaitingForReply(test_start_time_ - milliseconds(500));
        updateContext(context2);

        // Third context setup: expired but has not exhausted min_echos_
        PingContextPtr context3 = getContext(lease_query_pairs_[2]);
        ASSERT_TRUE(context3);
        context3->setMinEchos(2);
        context3->beginWaitingForReply(test_start_time_ - milliseconds(500));
        updateContext(context3);

        // Fourth context setup: has not yet expired
        PingContextPtr context4 = getContext(lease_query_pairs_[3]);
        ASSERT_TRUE(context4);
        context4->beginWaitingForReply(test_start_time_);
        updateContext(context4);

        // Now invoke expirationTimedout().
        ASSERT_NO_THROW_LOG(mgr_->expirationTimedOut());

        // Verify the contexts are in the expected states.
        // Context1 should still be WAITING_TO_SEND.
        context1 = getContext(lease_query_pairs_[0]);
        ASSERT_TRUE(context1);
        EXPECT_EQ(context1->getState(), PingContext::WAITING_TO_SEND);

        // Context2 should be gone by unparking and its address freed.
        IOAddress address = lease_query_pairs_[1].lease_->addr_;
        context2 = getContext(address);
        ASSERT_FALSE(context2);
        EXPECT_EQ(unparked_, 1);
        ASSERT_EQ(frees_.size(), 1);
        EXPECT_EQ(frees_[0].lease_->addr_, address);

        // Context3 should be in WAITING_TO_SEND.
        context3 = getContext(lease_query_pairs_[2]);
        ASSERT_TRUE(context3);
        EXPECT_EQ(context3->getState(), PingContext::WAITING_TO_SEND);

        // Context4 should still be WAITING_FOR_REPLY.
        context4 = getContext(lease_query_pairs_[3]);
        ASSERT_TRUE(context4);
        EXPECT_EQ(context4->getState(), PingContext::WAITING_FOR_REPLY);

        // Manager's next_expiry_ should be based on context4?
        EXPECT_TRUE(fuzzyEqual(mgr_->getNextExpiry(), context4->getNextExpiry()));
    }

    /// @brief Generates a number of ping checks to local loop back addresses.
    ///
    /// Pings should all result in ECHO_REPLYs that get "declined".  Declined
    /// addresses are added to a list.  Test completion is gated by the parking
    /// lot becoming empty or test times out.
    void testMultiplePingsWithReply() {
        SKIP_IF(notRoot());

        // Create manager with thread-pool size of 3, min_echos 1,
        // reply_timeout 1000 milliseconds.  Larger time out for this test
        // avoids sporadic expirations which leads to unaccounted for UNPARKs.
        // ST mode should ingore requested thread number.
        ASSERT_NO_THROW_LOG(createMgr(3, 1, 1000));
        ASSERT_TRUE(mgr_);

        // Install a post reply received callback to stop the test if we're done.
        int num_targets = 25;
        mgr_->post_reply_received_cb_ =
            [this, num_targets](const ICMPMsgPtr& /* reply */) {
                MultiThreadingLock lock(*mutex_);
                if (unparked_ == num_targets) {
                    stopTestService();
                    return;
                }
            };

        // Start the manager.  This will open the channel.
        ASSERT_NO_THROW_LOG(mgr_->start());
        ASSERT_TRUE(mgr_->isRunning());

        // Start the ping checks.
        startTargets(num_targets);

        // Run the main thread's IOService until we complete or timeout.
        ASSERT_NO_THROW_LOG(runIOService());

        // Stop the thread pool.
        ASSERT_NO_THROW_LOG(mgr_->stop());
        ASSERT_TRUE(mgr_->isStopped());

        // Calling nextToSend() should return false.
        IOAddress next("0.0.0.0");
        ASSERT_FALSE(mgr_->nextToSend(next));

        // We should have as many declines as we have pairs created.
        compareLeaseQueryPairs(declines_);
    }

    /// @brief Generates a large number of ping checks to local loop back addresses.
    ///
    /// A pause is induced approximately halfway through the number of replies
    /// at which point the manager is paused and then resumed.  This is intended
    /// to demonstrate the ability to pause and resume the manager gracefully.
    /// The pings should all result in ECHO_REPLYs that get "declined".  Declined
    /// addresses are added to a list.  Test completion is gated by the parking
    /// lot becoming empty or test times out.
    void testMultiplePingsWithReplyAndPause() {
        SKIP_IF(notRoot());

        // Create manager with thread-pool size of 3, min_echos 1,
        // reply_timeout 1000 milliseconds.  Larger time out for this test
        // avoids sporadic expirations which leads to unaccounted for UNPARKs.
        // ST mode should ingore requested thread number.
        ASSERT_NO_THROW_LOG(createMgr(3, 1, 1000));
        ASSERT_TRUE(mgr_);

        // Generate ping checks to the desired number of targets.
        // Set up the pause callback to pause at half the number of
        // expected replies.
        size_t num_targets = 24;
        size_t reply_cnt = 0;
        size_t pause_at = num_targets / 2;
        bool test_paused = false;

        // Install post reply callback to stop the test thread when we reach
        // the pause count.
        mgr_->post_reply_received_cb_ =
            [this, &reply_cnt, &test_paused, &pause_at](const ICMPMsgPtr& reply) {
                MultiThreadingLock lock(*mutex_);
                if (reply->getType() == ICMPMsg::ECHO_REPLY) {
                    ++reply_cnt;
                    if (pause_at && (reply_cnt >= pause_at)) {
                        test_paused = true;
                        stopTestService();
                        pause_at = 0;
                    }
                }
            };

        // Start the manager.  This will open the channel.
        ASSERT_NO_THROW_LOG(mgr_->start());
        ASSERT_TRUE(mgr_->isRunning());
        ASSERT_NO_THROW_LOG(mgr_->pause());

        // Start 1/2 desired number of ping checks.
        startTargets(num_targets / 2);

        // Run the main thread's IOService until we pause or timeout.
        ASSERT_NO_THROW_LOG(mgr_->resume());
        ASSERT_TRUE(mgr_->isRunning());
        ASSERT_NO_THROW_LOG(runIOService());

        // Manager should still be running.  Pause it.
        ASSERT_TRUE(mgr_->isRunning());
        if (mgr_->getThreadPool()) {
            ASSERT_NO_THROW_LOG(mgr_->pause());
            ASSERT_TRUE(mgr_->isPaused());
        }

        // Verify that the pause callback is why we stopped, that we
        // received at least as many as we should have before pause
        // and that we have more work to do.  The test is a range as
        // pausing does not happen exactly at the same point from test
        // run to test run.
        ASSERT_TRUE(test_paused);
        ASSERT_TRUE((reply_cnt >= pause_at) && (reply_cnt < num_targets))
                << "reply_cnt " << reply_cnt
                << ", pause_at  " << pause_at
                << ", num_targets " << num_targets;

        mgr_->post_reply_received_cb_ =
            [this, num_targets](const ICMPMsgPtr& /* reply */) {
                MultiThreadingLock lock(*mutex_);
                if (unparked_ == num_targets) {
                    stopTestService();
                    return;
                }
            };

        // Start second batch of targets.
        startTargets(num_targets / 2, IOAddress("127.0.0.15"));

        ASSERT_NO_THROW_LOG(mgr_->resume());
        ASSERT_TRUE(mgr_->isRunning());

        // Restart the main thread's IOService until we complete or timeout.
        ASSERT_NO_THROW_LOG(runIOService());

        ASSERT_NO_THROW_LOG(mgr_->stop());
        ASSERT_TRUE(mgr_->isStopped());

        // Calling nextToSend() should return false.
        IOAddress next("0.0.0.0");
        ASSERT_FALSE(mgr_->nextToSend(next));

        // We should have as many declines as we have pairs created.
        compareLeaseQueryPairs(declines_);
    }

    /// @brief Verifies that a recoverable error completion in sendCompleted() results
    /// in the target address being free to use.  In other words, it should have
    /// the same outcome as the receiving a TARGET_UNREACHABLE reply from the OS.
    void testSendCompletedSendFailed() {
        SKIP_IF(notRoot());

        // Create manager with thread-pool size of 3, min_echos 1,
        // reply_timeout 250 milliseconds.
        // ST mode should ingore requested thread number.
        ASSERT_NO_THROW_LOG(createMgr(3, 1, 250));
        ASSERT_TRUE(mgr_);

        // Install a post send completed callback to stop the test if we're done.
        mgr_->post_send_completed_cb_ =
            [this](const ICMPMsgPtr& /* echo */, bool send_failed) {
                MultiThreadingLock lock(*mutex_);
                if (send_failed) {
                    stopTestService();
                }
            };

        // Start the manager.
        ASSERT_NO_THROW_LOG(mgr_->start());

        // Set the test channel to complete the first send with a network_unreachable
        // error. This saves us from trying to determine an address in the test
        // environment that would cause it.
        mgr_->getChannel()->ec_on_write_number_ = 1;
        mgr_->getChannel()->write_error_ec_ = make_error_code(network_unreachable);

        // Start a ping for one target.
        startTargets(1);
        auto lqp = lease_query_pairs_[0];

        // Run the main thread's IOService until we complete or timeout.
        ASSERT_NO_THROW_LOG(runIOService());

        // Verify the expiration timer is no longer running.
        EXPECT_EQ(mgr_->getExpirationTimerInterval(), 0);

        // The context should no longer be in the store.
        EXPECT_FALSE(getContext(lqp));

        // We should have unparked the query from the lot.
        EXPECT_EQ(mgr_->parkingLotSize(), 0);
        EXPECT_EQ(unparked_, 1);

        // We should have one free that matches our lease query pair.
        compareLeaseQueryPairs(frees_);
    }

    /// @brief Exercises shouldPing().
    void testShouldPingTest() {
        SKIP_IF(notRoot());

        // Create manager with thread-pool size of 3, min_echos 1,
        // reply_timeout 250 milliseconds.
        // ST mode should ingore requested thread number.
        ASSERT_NO_THROW_LOG(createMgr(3, 1, 250));
        ASSERT_TRUE(mgr_);

        // Make a default config.
        PingCheckConfigPtr config(new PingCheckConfig());

        // Make a lease query pair.
        auto lqp1 = makeLeaseQueryPair(IOAddress("127.0.0.2"), 111);
        const uint8_t id1[] = { 0x31, 0x32, 0x33, 0x34 };
        ClientIdPtr cid1(new ClientId(id1, sizeof(id1)));
        lqp1.lease_->client_id_ = cid1;

        Lease4Ptr empty_lease;
        CalloutHandle::CalloutNextStep status;

        // Ping checking enabled, no old lease, channel doesn't exist, should return CONTINUE.
        ASSERT_TRUE(config->getEnablePingCheck());
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp1.lease_, lqp1.query_, empty_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_CONTINUE);

        // Start the manager, then pause it.  This lets us start pings without
        // them changing state.
        ASSERT_NO_THROW_LOG(mgr_->start());
        ASSERT_NO_THROW_LOG(mgr_->pause());

        // Ping checking disabled, no old lease, should return CONTINUE.
        config->setEnablePingCheck(false);
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp1.lease_, lqp1.query_, empty_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_CONTINUE);

        // Ping checking enabled, no old lease, should return PARK.
        config->setEnablePingCheck(true);
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp1.lease_, lqp1.query_, empty_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_PARK);

        // Make an old lease based on the first lease.
        time_t now = time(0);
        Lease4Ptr old_lease(new Lease4(*(lqp1.lease_)));

        // Prior lease belonging to the same client with cltt greater than ping-cltt-secs
        // should return PARK.
        old_lease->cltt_ = now - config->getPingClttSecs() * 2;
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp1.lease_, lqp1.query_, old_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_PARK);

        // Prior lease belonging to the same client but with cltt less than ping-cltt-secs
        // should return CONTINUE.
        old_lease->cltt_ = now - config->getPingClttSecs() / 2;
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp1.lease_, lqp1.query_, old_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_CONTINUE);

        // Prior lease belonging to a different client, should return PARK.
        const uint8_t id2[] = { 0x35, 0x36, 0x37, 0x34 };
        old_lease->client_id_.reset(new ClientId(id2, sizeof(id2)));
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp1.lease_, lqp1.query_, old_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_PARK);

        // Now let's start a ping for the lease-query pair.
        ASSERT_NO_THROW_LOG(mgr_->startPing(lqp1.lease_, lqp1.query_, parking_lot_));

        // Make a second lease query pair.  Same address, different client.
        auto lqp2 = makeLeaseQueryPair(IOAddress("127.0.0.2"), 333);
        lqp2.lease_->client_id_ = old_lease->client_id_;

        // Trying to start a ping for an address already being checked should return DROP.
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp2.lease_, lqp2.query_, empty_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_DROP);

        // Stop the mgr.
        ASSERT_NO_THROW(mgr_->stop());

        // Ping checking enabled, no old lease, channel isn't open, should return CONTINUE.
        ASSERT_TRUE(config->getEnablePingCheck());
        ASSERT_NO_THROW_LOG(status = mgr_->shouldPing(lqp1.lease_, lqp1.query_, empty_lease, config));
        EXPECT_EQ(status, CalloutHandle::NEXT_STEP_CONTINUE);
    }

    /// @brief Exercise's getScopedConfig().
    void testGetScopedConfig() {
        CfgMgr::instance().setFamily(AF_INET);

        // Start with empty cache, any subnet that hasn't been seen should get parsed
        // and, if valid, added to the cache.
        CfgMgr& cfg_mgr = CfgMgr::instance();
        CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();

        // Subnet 1 has no ping-check config. Should return global config.
        ElementPtr user_context = Element::createMap();
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.1.0"), 24, 30, 40, 60, 1));
        subnet->setContext(user_context);
        subnets->add(subnet);

        // Subnet 2 has invalid ping-check content. Should return global config.
        std::string invalid_json_cfg =
            R"({
                "ping-check": {
                    "enable-ping-check" : true,
                    "bogus-key-word" : true
                }
            })";

        user_context = Element::fromJSON(invalid_json_cfg);
        subnet.reset(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 2));
        subnet->setContext(user_context);
        subnets->add(subnet);

        // Subnet 3 has valid ping check.  Should return subnet config
        std::string valid_json_cfg =
            R"({
                "ping-check": {
                    "enable-ping-check" : true,
                    "min-ping-requests" : 13
                }
            })";

        user_context = Element::fromJSON(valid_json_cfg);
        subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 3));
        subnet->setContext(user_context);
        subnets->add(subnet);

        // Commit the subnet configuration.
        cfg_mgr.commit();

        // Create manager with thread-pool size of 3, min_echos 2, reply_timeout 250 ms.
        ASSERT_NO_THROW_LOG(createMgr(3, 2, 250));
        ASSERT_TRUE(mgr_);

        Lease4Ptr lease(new Lease4());
        PingCheckConfigPtr config;

        // Should get the global configuration for subnet 1.
        lease->addr_ = IOAddress("192.0.1.1");
        lease->subnet_id_ = 1;
        ASSERT_NO_THROW_LOG(config = mgr_->getScopedConfig(lease));
        ASSERT_TRUE(config);
        ASSERT_EQ(config, mgr_->getGlobalConfig());

        // Should get the global configuration for subnet 2.
        lease->addr_ = IOAddress("192.0.2.1");
        lease->subnet_id_ = 2;
        ASSERT_NO_THROW_LOG(config = mgr_->getScopedConfig(lease));
        ASSERT_TRUE(config);
        ASSERT_EQ(config, mgr_->getGlobalConfig());

        // Should get subnet configuration for subnet 3.
        lease->addr_ = IOAddress("192.0.3.1");
        lease->subnet_id_ = 3;
        ASSERT_NO_THROW_LOG(config = mgr_->getScopedConfig(lease));
        ASSERT_TRUE(config);
        ASSERT_NE(config, mgr_->getGlobalConfig());
        EXPECT_EQ(config->getMinPingRequests(), 13);
    }

    /// @brief Exercises checkSuspended().
    ///
    /// This is intended to verify that ping checking is suspended and resumed based
    /// on the DHCP service state, not to verify every place that checkSuspended()
    /// is called.
    void testCheckSuspended() {
        SKIP_IF(notRoot());

        // Create manager with thread-pool size of 3, min_echos 1,
        // reply_timeout 250 milliseconds.
        ASSERT_NO_THROW_LOG(createMgr(3, 1, 250));
        ASSERT_TRUE(mgr_);

        // Make a default config.
        PingCheckConfigPtr config(new PingCheckConfig());

        // Give the manager a NetworkState instance.
        NetworkStatePtr network_state(new NetworkState());
        mgr_->setNetworkState(network_state);

        // Verify that ping checking is not suspended.
        ASSERT_FALSE(mgr_->checkSuspended());

        // Start the manager, then pause it.  This lets us start pings without
        // them changing state.
        ASSERT_NO_THROW_LOG(mgr_->start());
        ASSERT_NO_THROW_LOG(mgr_->pause());

        // Verfify the ping store is empty.
        auto store = mgr_->getStore();
        ASSERT_TRUE(store);
        auto pings = store->getAll();
        ASSERT_EQ(0, pings->size());

        // Make a lease query pair.
        auto lqp1 = makeLeaseQueryPair(IOAddress("127.0.0.2"), 111);
        const uint8_t id1[] = { 0x31, 0x32, 0x33, 0x34 };
        ClientIdPtr cid1(new ClientId(id1, sizeof(id1)));
        lqp1.lease_->client_id_ = cid1;

        // Now let's try to start a ping for the lease-query pair.  It should work.
        ASSERT_NO_THROW_LOG(mgr_->startPing(lqp1.lease_, lqp1.query_, parking_lot_));

        // Verify we have an entry in the store.
        pings = store->getAll();
        ASSERT_EQ(1, pings->size());

        // Disable the DHCP service.
        network_state->disableService(NetworkState::USER_COMMAND);

        // Make a second lease query pair.  Different address, different client.
        auto lqp2 = makeLeaseQueryPair(IOAddress("127.0.0.3"), 333);
        const uint8_t id2[] = { 0x31, 0x32, 0x33, 0x35 };
        ClientIdPtr cid2(new ClientId(id1, sizeof(id2)));
        lqp2.lease_->client_id_ = cid2;

        // Try to start a ping. We should not be able to do it.
        ASSERT_THROW_MSG(mgr_->startPing(lqp2.lease_, lqp2.query_, parking_lot_),
                         InvalidOperation,
                         "PingCheckMgr::startPing() - DHCP service is suspended!");

        // Store should be empty, having been flushed by suspension detection.
        pings = store->getAll();
        ASSERT_EQ(0, pings->size());

        // Ping checking should report as suspended.
        ASSERT_TRUE(mgr_->checkSuspended());

        // Re-enable the DHCP service.
        network_state->enableService(NetworkState::USER_COMMAND);

        // Suspension checking should lift the suspension and we should once again
        // be able to start a new ping check.
        ASSERT_NO_THROW_LOG(mgr_->startPing(lqp2.lease_, lqp2.query_, parking_lot_));

        // Store should have one check in it.
        pings = store->getAll();
        ASSERT_EQ(1, pings->size());

        // Ping checking should report as not suspended.
        ASSERT_FALSE(mgr_->checkSuspended());
    }

    /// @brief Manager instance.
    TestablePingCheckMgrPtr mgr_;

    /// @brief List of lease/query pairs used during the test, in the order
    /// they were created.
    LeaseQueryPairs lease_query_pairs_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;

    /// @brief Marks the start time of a test.
    TimeStamp test_start_time_;

    /// @brief Parking lot where the associated query is parked.
    /// If empty parking is not being employed.
    ParkingLotHandlePtr parking_lot_;

    /// @brief Number of queries unparked during a test.
    size_t unparked_;

    /// @brief List of leases that were found to be in-use during a test.
    LeaseQueryPairs declines_;

    /// @brief List of leases that were found to be free to use during a test.
    LeaseQueryPairs frees_;
};

TEST_F(PingCheckMgrTest, operationalBasicsST) {
    testOperationalBasics(0);
}

TEST_F(PingCheckMgrTest, operationalBasicsMT) {
    MultiThreadingTest mt;
    testOperationalBasics(3);
}

TEST_F(PingCheckMgrTest, startPingST) {
    testStartPing();
}

TEST_F(PingCheckMgrTest, startPingMT) {
    MultiThreadingTest mt;
    testStartPing();
}

TEST_F(PingCheckMgrTest, nextToSendST) {
    testNextToSend();
}

TEST_F(PingCheckMgrTest, nextToSendMT) {
    MultiThreadingTest mt;
    testNextToSend();
}

TEST_F(PingCheckMgrTest, setNextExpirationST) {
    testSetNextExpiration();
}

TEST_F(PingCheckMgrTest, setNextExpirationMT) {
    MultiThreadingTest mt;
    testSetNextExpiration();
}

TEST_F(PingCheckMgrTest, sendCompletedST) {
    testSendCompleted();
}

TEST_F(PingCheckMgrTest, sendCompletedMT) {
    MultiThreadingTest mt;
    testSendCompleted();
}

TEST_F(PingCheckMgrTest, replyReceivedForEchoReplyST) {
    testReplyReceivedForEchoReply();
}

TEST_F(PingCheckMgrTest, replyReceivedForEchoReplyMT) {
    MultiThreadingTest mt;
    testReplyReceivedForEchoReply();
}

TEST_F(PingCheckMgrTest, replyReceivedForTargetUnreachableST) {
    testReplyReceivedForTargetUnreachable();
}

TEST_F(PingCheckMgrTest, replyReceivedForTargetUnreachableMT) {
    MultiThreadingTest mt;
    testReplyReceivedForTargetUnreachable();
}

TEST_F(PingCheckMgrTest, expirationProcessingST) {
    testExpirationProcessing();
}

TEST_F(PingCheckMgrTest, expirationProcessingMT) {
    MultiThreadingTest mt;
    testExpirationProcessing();
}

TEST_F(PingCheckMgrTest, multiplePingsWithReplyST) {
    testMultiplePingsWithReply();
}

TEST_F(PingCheckMgrTest, multiplePingsWithReplyMT) {
    MultiThreadingTest mt;
    testMultiplePingsWithReply();
}

TEST_F(PingCheckMgrTest, multiplePingsWithReplyAndPauseST) {
    testMultiplePingsWithReplyAndPause();
}

TEST_F(PingCheckMgrTest, multiplePingsWithReplyAndPauseMT) {
    MultiThreadingTest mt;
    testMultiplePingsWithReplyAndPause();
}

TEST_F(PingCheckMgrTest, sendCompletedSendFailedST) {
    testSendCompletedSendFailed();
}

TEST_F(PingCheckMgrTest, sendCompletedSendFailedMT) {
    MultiThreadingTest mt;
    testSendCompletedSendFailed();
}

TEST_F(PingCheckMgrTest, shouldPingST) {
    testShouldPingTest();
}

TEST_F(PingCheckMgrTest, shouldPingMT) {
    MultiThreadingTest mt;
    testShouldPingTest();
}

TEST_F(PingCheckMgrTest, getScopedConfigST) {
    testGetScopedConfig();
}

TEST_F(PingCheckMgrTest, getScopedConfigMT) {
    MultiThreadingTest mt;
    testGetScopedConfig();
}

TEST_F(PingCheckMgrTest, checkSuspendedST) {
    testCheckSuspended();
}

TEST_F(PingCheckMgrTest, checkSuspendedMT) {
    MultiThreadingTest mt;
    testCheckSuspended();
}

} // end of anonymous namespace
