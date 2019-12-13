// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_test.h>
#include <asiolink/asio_wrapper.h>
#include <communication_state.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <exceptions/exceptions.h>
#include <http/date_time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;
using namespace isc::http;
using namespace boost::posix_time;
using namespace boost::gregorian;


namespace {


/// @brief Test fixture class for @c CommunicationState class.
class CommunicationStateTest : public HATest {
public:

    /// @brief Constructor.
    CommunicationStateTest()
        : state_(io_service_, createValidConfiguration()),
          state6_(io_service_, createValidConfiguration()) {
    }

    /// @brief Destructor.
    ~CommunicationStateTest() {
        io_service_->poll();
    }

    /// @brief Returns test heartbeat implementation.
    ///
    /// @return Pointer to heartbeat implementation function under test.
    boost::function<void()> getHeartbeatImpl() {
        return (boost::bind(&CommunicationStateTest::heartbeatImpl, this));
    }

    /// @brief Test heartbeat implementation.
    ///
    /// It simply pokes the communication state object. Note that the real
    /// implementation would send an actual heartbeat command prior to
    /// poking the state.
    void heartbeatImpl() {
        state_.poke();
    }

    /// @brief Communication state object used throughout the tests.
    NakedCommunicationState4 state_;

    /// @brief Communication state for IPv6 used throughout the tests.
    NakedCommunicationState6 state6_;
};

// Verifies that the partner state is set and retrieved correctly.
TEST_F(CommunicationStateTest, partnerState) {
    // Initially the state is unknown.
    EXPECT_LT(state_.getPartnerState(), 0);

    state_.setPartnerState("hot-standby");
    EXPECT_EQ(HA_HOT_STANDBY_ST, state_.getPartnerState());

    state_.setPartnerState("load-balancing");
    EXPECT_EQ(HA_LOAD_BALANCING_ST, state_.getPartnerState());

    state_.setPartnerState("partner-down");
    EXPECT_EQ(HA_PARTNER_DOWN_ST, state_.getPartnerState());

    state_.setPartnerState("ready");
    EXPECT_EQ(HA_READY_ST, state_.getPartnerState());

    state_.setPartnerState("syncing");
    EXPECT_EQ(HA_SYNCING_ST, state_.getPartnerState());

    state_.setPartnerState("terminated");
    EXPECT_EQ(HA_TERMINATED_ST, state_.getPartnerState());

    state_.setPartnerState("waiting");
    EXPECT_EQ(HA_WAITING_ST, state_.getPartnerState());

    state_.setPartnerState("unavailable");
    EXPECT_EQ(HA_UNAVAILABLE_ST, state_.getPartnerState());

    // An attempt to set unsupported value should result in exception.
    EXPECT_THROW(state_.setPartnerState("unsupported"), BadValue);
}

// Verifies that the partner's scopes are set and retrieved correctly.
TEST_F(CommunicationStateTest, partnerScopes) {
    // Initially, the scopes should be empty.
    ASSERT_TRUE(state_.getPartnerScopes().empty());

    // Set new partner scopes.
    ASSERT_NO_THROW(
        state_.setPartnerScopes(Element::fromJSON("[ \"server1\", \"server2\" ]"))
    );

    // Get them back.
    auto returned = state_.getPartnerScopes();
    EXPECT_EQ(2, returned.size());
    EXPECT_EQ(1, returned.count("server1"));
    EXPECT_EQ(1, returned.count("server2"));

    // Override the scopes.
    ASSERT_NO_THROW(
        state_.setPartnerScopes(Element::fromJSON("[ \"server1\" ]"))
    );
    returned = state_.getPartnerScopes();
    EXPECT_EQ(1, returned.size());
    EXPECT_EQ(1, returned.count("server1"));

    // Clear the scopes.
    ASSERT_NO_THROW(
        state_.setPartnerScopes(Element::fromJSON("[ ]"))
    );
    returned = state_.getPartnerScopes();
    EXPECT_TRUE(returned.empty());

    // An attempt to set invalid JSON should fail.
    EXPECT_THROW(state_.setPartnerScopes(Element::fromJSON("{ \"not-a-list\": 1 }")),
                 BadValue);
}

// Verifies that the object is poked right after construction.
TEST_F(CommunicationStateTest, initialDuration) {
    EXPECT_TRUE(state_.isPoked());
}

// Verifies that  poking the state updates the returned duration.
TEST_F(CommunicationStateTest, poke) {
    state_.modifyPokeTime(-30);
    ASSERT_GE(state_.getDurationInMillisecs(), 30000);
    ASSERT_TRUE(state_.isCommunicationInterrupted());
    ASSERT_NO_THROW(state_.poke());
    EXPECT_TRUE(state_.isPoked());
    EXPECT_FALSE(state_.isCommunicationInterrupted());
}

// Test that heartbeat function is triggered.
TEST_F(CommunicationStateTest, heartbeat) {
    // Set poke time to the past and expect that the object is considered
    // not poked.
    state_.modifyPokeTime(-30);
    EXPECT_FALSE(state_.isPoked());

    // Run heartbeat every 1 second.
    ASSERT_NO_THROW(state_.startHeartbeat(1, getHeartbeatImpl()));
    runIOService(1200);

    // After > than 1 second the state should have been poked.
    EXPECT_TRUE(state_.isPoked());

    // Repeat the test.
    state_.modifyPokeTime(-30);
    EXPECT_FALSE(state_.isPoked());
    ASSERT_NO_THROW(state_.startHeartbeat(1, getHeartbeatImpl()));
    runIOService(1200);
    EXPECT_TRUE(state_.isPoked());
}

// Test that invalid values provided to startHeartbeat are rejected.
TEST_F(CommunicationStateTest, startHeartbeatInvalidValues) {
    EXPECT_THROW(state_.startHeartbeat(-1, getHeartbeatImpl()), BadValue);
    EXPECT_THROW(state_.startHeartbeat(0, getHeartbeatImpl()), BadValue);
    EXPECT_THROW(state_.startHeartbeat(1, 0), BadValue);
}

// Test that failure detection works properly for DHCPv4 case.
TEST_F(CommunicationStateTest, detectFailureV4) {
    // Initially, there should be no unacked clients recorded.
    ASSERT_FALSE(state_.failureDetected());

    // The maximum number of unacked clients is 10. Let's provide 10
    // DHCPDISCOVER messages with the "secs" value of 15 which exceeds
    // the threshold of 10. All these clients should be recorded as
    // unacked.
    for (uint8_t i = 0; i < 10; ++i) {
        // Some of the requests have no client identifier to test that
        // we don't fall over if the client identifier is null.
        const uint8_t client_id_seed = (i < 5 ? i : 0);
        ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, i,
                                                             client_id_seed,
                                                             15)));
        // We don't exceed the maximum of number of unacked clients so the
        // partner failure shouldn't be reported.
        ASSERT_FALSE(state_.failureDetected())
            << "failure detected for the request number "
            << static_cast<int>(i);
    }

    // Let's provide similar set of requests but this time the "secs" field is
    // below the threshold. They should not be counted as failures. Also,
    // all of these requests have client identifier.
    for (uint8_t i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, i, i,
                                                             9)));
        ASSERT_FALSE(state_.failureDetected())
            << "failure detected for the request number "
            << static_cast<int>(i);
    }

    // Let's create a message from a new (not recorded yet) client with the
    // "secs" field value below the threshold. It should not be recorded.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 10, 10, 6)));

    // Still no failure.
    ASSERT_FALSE(state_.failureDetected());

    // Let's repeat one of the requests which already have been recorded as
    // unacked but with a greater value of "secs" field. This should not
    // be counted because only new clients count.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 3, 3, 20)));
    ASSERT_FALSE(state_.failureDetected());

    // This time let's simulate a client with a MAC address already recorded but
    // with a client identifier. This should be counted as a new unacked request.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 7, 7, 15)));
    ASSERT_TRUE(state_.failureDetected());

    // Poking should cause all counters to reset as it is an indication that the
    // control connection has been re-established.
    ASSERT_NO_THROW(state_.poke());

    // We're back to no failure state.
    EXPECT_FALSE(state_.failureDetected());

    // Send 11 DHCPDISCOVER messages with the "secs" field bytes swapped. Swapping
    // bytes was reported for some misbehaving Windows clients. The server should
    // detect bytes swapping when second byte is 0 and the first byte is non-zero.
    // However, the first byte is equal to 5 which is below our threshold so none
    // of the requests below should count as unacked.
    for (uint8_t i = 0; i < 11; ++i) {
        ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, i, i,
                                                             0x0500)));
        ASSERT_FALSE(state_.failureDetected())
            << "failure detected for the request number "
            << static_cast<int>(i)
            << " when testing swapped secs field bytes";
    }

    // Repeat the same test, but this time either the first byte exceeds the
    // secs threshold or the second byte is non-zero. All should be counted
    // as unacked.
    for (uint8_t i = 0; i < 10; ++i) {
        uint16_t secs = (i % 2 == 0 ? 0x0F00 : 0x0501);
        ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, i, i,
                                                             secs)));
        ASSERT_FALSE(state_.failureDetected())
            << "failure detected for the request number "
            << static_cast<int>(i)
            << " when testing swapped secs field bytes";
    }

    // This last message should cause the failure state.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 11, 11,
                                                         0x30)));
    EXPECT_TRUE(state_.failureDetected());
}

// This test verifies that it is possible to disable analysis of the DHCPv4
// packets in which case the partner's failure is assumed when there is
// no connection over the control channel.
TEST_F(CommunicationStateTest, failureDetectionDisabled4) {
    state_.config_->setMaxUnackedClients(0);
    EXPECT_TRUE(state_.failureDetected());
}

// Test that failure detection works properly for DHCPv6 case.
TEST_F(CommunicationStateTest, detectFailureV6) {
    // Initially, there should be no unacked clients recorded.
    ASSERT_FALSE(state6_.failureDetected());

    // The maximum number of unacked clients is 10. Let's provide 10
    // Solicit messages with the "elapsed time" value of 1500 which exceeds
    // the threshold of 10000ms. Note that the elapsed time value is provided
    // in 1/100s of 1 second. All these clients should be recorded as
    // unacked.
    for (uint8_t i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, i,
                                                              1500)));
        // We don't exceed the maximum number of unacked clients so the
        // partner failure shouldn't be reported.
        ASSERT_FALSE(state6_.failureDetected())
            << "failure detected for the request number "
            << static_cast<int>(i);
    }

    // Let's provide similar set of requests but this time the "elapsed time" is
    // below the threshold. They should not be counted as failures. Also,
    // all of these requests have client identifier.
    for (uint8_t i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, i,
                                                             900)));
        ASSERT_FALSE(state6_.failureDetected())
            << "failure detected for the request number "
            << static_cast<int>(i);
    }

    // Let's create a message from a new (not recorded yet) client with the
    // "elapsed time" value below the threshold. It should not be recorded.
    ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, 10, 600)));

    // Still no failure.
    ASSERT_FALSE(state6_.failureDetected());

    // Let's repeat one of the requests which already have been recorded as
    // unacked but with a greater value of "elapsed time". This should not
    // be counted because only new clients count.
    ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, 3, 2000)));
    ASSERT_FALSE(state6_.failureDetected());

    // New unacked client should cause failure to the detected.
    ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, 11, 1500)));
    ASSERT_TRUE(state6_.failureDetected());

    // Poking should cause all counters to reset as it is an indication that the
    // control connection has been re-established.
    ASSERT_NO_THROW(state6_.poke());

    // We're back to no failure state.
    EXPECT_FALSE(state6_.failureDetected());
}

// This test verifies that it is possible to disable analysis of the DHCPv6
// packets in which case the partner's failure is assumed when there is
// no connection over the control channel.
TEST_F(CommunicationStateTest, failureDetectionDisabled6) {
    state6_.config_->setMaxUnackedClients(0);
    EXPECT_TRUE(state6_.failureDetected());
}

// This test verifies that the clock skew is checked properly by the
// clockSkewShouldWarn and clockSkewShouldTerminate functions.
TEST_F(CommunicationStateTest, clockSkew) {
    // Default clock skew is 0.
    EXPECT_FALSE(state_.clockSkewShouldWarn());
    EXPECT_FALSE(state_.clockSkewShouldTerminate());
    state_.setPartnerTime(HttpDateTime().rfc1123Format());

    // Partner time is ahead by 15s (no warning).
    state_.clock_skew_ += boost::posix_time::time_duration(0, 0, 15);
    EXPECT_FALSE(state_.clockSkewShouldWarn());
    EXPECT_FALSE(state_.clockSkewShouldTerminate());

    // Partner time is behind by 15s (no warning).
    state_.setPartnerTime(HttpDateTime().rfc1123Format());
    state_.clock_skew_ -= boost::posix_time::time_duration(0, 0, 15);
    EXPECT_FALSE(state_.clockSkewShouldWarn());
    EXPECT_FALSE(state_.clockSkewShouldTerminate());

    // Partner time is ahead by 35s (warning).
    state_.setPartnerTime(HttpDateTime().rfc1123Format());
    state_.clock_skew_ += boost::posix_time::time_duration(0, 0, 35);
    EXPECT_TRUE(state_.clockSkewShouldWarn());
    EXPECT_FALSE(state_.clockSkewShouldTerminate());

    // Partner time is behind by 35s (warning).
    state_.setPartnerTime(HttpDateTime().rfc1123Format());
    state_.clock_skew_ -= boost::posix_time::time_duration(0, 0, 35);
    state_.last_clock_skew_warn_ = boost::posix_time::ptime();
    EXPECT_TRUE(state_.clockSkewShouldWarn());
    EXPECT_FALSE(state_.clockSkewShouldTerminate());

    // Due to the gating mechanism this should not return true the second
    // time.
    EXPECT_FALSE(state_.clockSkewShouldWarn());

    // But should warn if the warning was issued more than 60 seconds ago.
    state_.last_clock_skew_warn_ -= boost::posix_time::time_duration(0, 1, 30);
    EXPECT_TRUE(state_.clockSkewShouldWarn());

    // Partner time is ahead by 65s (warning and terminate).
    state_.setPartnerTime(HttpDateTime().rfc1123Format());
    state_.clock_skew_ += boost::posix_time::time_duration(0, 1, 5);
    state_.last_clock_skew_warn_ = boost::posix_time::ptime();
    EXPECT_TRUE(state_.clockSkewShouldWarn());
    EXPECT_TRUE(state_.clockSkewShouldTerminate());

    // Partner time is behind by 65s (warning and terminate).
    state_.setPartnerTime(HttpDateTime().rfc1123Format());
    state_.clock_skew_ -= boost::posix_time::time_duration(0, 1, 5);
    state_.last_clock_skew_warn_ = boost::posix_time::ptime();
    EXPECT_TRUE(state_.clockSkewShouldWarn());
    EXPECT_TRUE(state_.clockSkewShouldTerminate());
}

// This test verifies that the clock skew value is formatted correctly
// for logging.
TEST_F(CommunicationStateTest, logFormatClockSkew) {
    // Make sure logFormatClockSkew() does not throw if called prior
    // the first call to setPartnerTime().
    std::string log;
    ASSERT_NO_THROW(log = state_.logFormatClockSkew());
    EXPECT_EQ(std::string("skew not initialized"), log);

    // Get current time.
    boost::posix_time::ptime now = HttpDateTime().getPtime();

    // Partner time is ahead by 15s.
    boost::posix_time::time_duration offset(0,0,15);
    state_.setPartnerTime(HttpDateTime(now + offset).rfc1123Format());
    ASSERT_NO_THROW(log = state_.logFormatClockSkew());

    // We don't check the exact string for obvious reasons.
    EXPECT_TRUE(log.find("15s ahead") != std::string::npos) <<
                " log content wrong: " << log;


    // Partner time is behind by 15s.
    state_.setPartnerTime(HttpDateTime(now - offset).rfc1123Format());
    ASSERT_NO_THROW(log = state_.logFormatClockSkew());
    // We don't check the exact string for obvious reasons.
    EXPECT_TRUE(log.find("15s behind") != std::string::npos) <<
                " log content wrong: " << log;

    offset = hours(18) + minutes(37) + seconds(15);
    ptime mytime(date(2019, Jul, 23), offset);

    state_.my_time_at_skew_ = mytime;
    state_.partner_time_at_skew_ = mytime + seconds(25);
    state_.clock_skew_ = seconds(25);
    ASSERT_NO_THROW(log = state_.logFormatClockSkew());
    std::string expected("my time: 2019-07-23 18:37:15, "
                         "partner's time: 2019-07-23 18:37:40, "
                         "partner's clock is 25s ahead");
    EXPECT_EQ(expected, log);
}

}
