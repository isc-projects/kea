// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/multi_threading_mgr.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <functional>
#include <limits>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;
using namespace isc::http;
using namespace isc::util;

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
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    ~CommunicationStateTest() {
        MultiThreadingMgr::instance().setMode(false);
        io_service_->poll();
    }

    /// @brief Verifies that the partner state is set and retrieved correctly.
    void partnerStateTest();

    /// @brief Verifies that the partner's scopes are set and retrieved correctly.
    void partnerScopesTest();

    /// @brief Verifies that the object is poked right after construction.
    void initialDurationTest();

    /// @brief Verifies that poking the state updates the returned duration.
    void pokeTest();

    /// @brief Test that heartbeat function is triggered.
    void heartbeatTest();

    /// @brief Test that invalid values provided to startHeartbeat are rejected.
    void startHeartbeatInvalidValuesTest();

    /// @brief Test that failure detection works properly for DHCPv4 case.
    void detectFailureV4Test();

    /// @brief This test verifies that it is possible to disable analysis of the DHCPv4
    /// packets in which case the partner's failure is assumed when there is
    /// no connection over the control channel.
    void failureDetectionDisabled4Test();

    /// @brief Test that failure detection works properly for DHCPv6 case.
    void detectFailureV6Test();

    /// @brief This test verifies that it is possible to disable analysis of the DHCPv6
    /// packets in which case the partner's failure is assumed when there is
    /// no connection over the control channel.
    void failureDetectionDisabled6Test();

    /// @brief This test verifies that the clock skew is checked properly by the
    /// clockSkewShouldWarn and clockSkewShouldTerminate functions.
    void clockSkewTest();

    /// @brief This test verifies that the clock skew value is formatted correctly
    /// for logging.
    void logFormatClockSkewTest();

    /// @brief Tests that the communication state report is correct.
    void getReportTest();

    /// @brief Tests unusual values used to create the report.
    void getReportDefaultValuesTest();

    /// @brief Tests that unsent updates count can be incremented and fetched.
    void getUnsentUpdateCountTest();

    /// @brief Tests that unsent updates count from partner can be set and
    /// a difference from previous value detected.
    void hasPartnerNewUnsentUpdatesTest();

    /// @brief Returns test heartbeat implementation.
    ///
    /// @return Pointer to heartbeat implementation function under test.
    std::function<void()> getHeartbeatImpl() {
        return (std::bind(&CommunicationStateTest::heartbeatImpl, this));
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
void
CommunicationStateTest::partnerStateTest() {
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
void
CommunicationStateTest::partnerScopesTest() {
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
void
CommunicationStateTest::initialDurationTest() {
    EXPECT_TRUE(state_.isPoked());
}

// Verifies that  poking the state updates the returned duration.
void
CommunicationStateTest::pokeTest() {
    state_.modifyPokeTime(-30);
    ASSERT_GE(state_.getDurationInMillisecs(), 30000);
    ASSERT_TRUE(state_.isCommunicationInterrupted());
    ASSERT_NO_THROW(state_.poke());
    EXPECT_TRUE(state_.isPoked());
    EXPECT_FALSE(state_.isCommunicationInterrupted());
}

// Test that heartbeat function is triggered.
void
CommunicationStateTest::heartbeatTest() {
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
void
CommunicationStateTest::startHeartbeatInvalidValuesTest() {
    EXPECT_THROW(state_.startHeartbeat(-1, getHeartbeatImpl()), BadValue);
    EXPECT_THROW(state_.startHeartbeat(0, getHeartbeatImpl()), BadValue);
    EXPECT_THROW(state_.startHeartbeat(1, 0), BadValue);
}

// Test that failure detection works properly for DHCPv4 case.
void
CommunicationStateTest::detectFailureV4Test() {
    // Initially, there should be no unacked clients recorded.
    ASSERT_FALSE(state_.failureDetected());
    EXPECT_EQ(0, state_.getUnackedClientsCount());
    EXPECT_EQ(0, state_.getConnectingClientsCount());
    EXPECT_EQ(0, state_.getAnalyzedMessagesCount());

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
    EXPECT_EQ(10, state_.getUnackedClientsCount());
    EXPECT_EQ(10, state_.getConnectingClientsCount());
    EXPECT_EQ(10, state_.getAnalyzedMessagesCount());

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
    EXPECT_EQ(10, state_.getUnackedClientsCount());
    EXPECT_EQ(15, state_.getConnectingClientsCount());
    EXPECT_EQ(20, state_.getAnalyzedMessagesCount());

    // Let's create a message from a new (not recorded yet) client with the
    // "secs" field value below the threshold. It should not be counted as failure.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 10, 10, 6)));

    // Still no failure.
    ASSERT_FALSE(state_.failureDetected());
    EXPECT_EQ(10, state_.getUnackedClientsCount());
    EXPECT_EQ(16, state_.getConnectingClientsCount());
    EXPECT_EQ(21, state_.getAnalyzedMessagesCount());

    // Let's repeat one of the requests which already have been recorded as
    // unacked but with a greater value of "secs" field. This should not
    // be counted because only new clients count.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 3, 3, 20)));
    ASSERT_FALSE(state_.failureDetected());
    EXPECT_EQ(10, state_.getUnackedClientsCount());
    EXPECT_EQ(16, state_.getConnectingClientsCount());
    EXPECT_EQ(22, state_.getAnalyzedMessagesCount());

    // This time let's simulate a client with a MAC address already recorded but
    // with a client identifier. This should be counted as a new unacked request.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 7, 7, 15)));
    ASSERT_TRUE(state_.failureDetected());
    EXPECT_EQ(11, state_.getUnackedClientsCount());
    EXPECT_EQ(16, state_.getConnectingClientsCount());
    EXPECT_EQ(23, state_.getAnalyzedMessagesCount());

    // Poking should cause all counters to reset as it is an indication that the
    // control connection has been re-established.
    ASSERT_NO_THROW(state_.poke());

    // We're back to no failure state.
    EXPECT_FALSE(state_.failureDetected());
    EXPECT_EQ(0, state_.getUnackedClientsCount());
    EXPECT_EQ(0, state_.getConnectingClientsCount());
    EXPECT_EQ(0, state_.getAnalyzedMessagesCount());

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
    EXPECT_EQ(0, state_.getUnackedClientsCount());
    EXPECT_EQ(11, state_.getConnectingClientsCount());
    EXPECT_EQ(11, state_.getAnalyzedMessagesCount());

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
    EXPECT_EQ(11, state_.getUnackedClientsCount());
    EXPECT_EQ(12, state_.getConnectingClientsCount());
    EXPECT_EQ(22, state_.getAnalyzedMessagesCount());
}

// This test verifies that it is possible to disable analysis of the DHCPv4
// packets in which case the partner's failure is assumed when there is
// no connection over the control channel.
void
CommunicationStateTest::failureDetectionDisabled4Test() {
    state_.config_->setMaxUnackedClients(0);
    EXPECT_TRUE(state_.failureDetected());
}

// Test that failure detection works properly for DHCPv6 case.
void
CommunicationStateTest::detectFailureV6Test() {
    // Initially, there should be no unacked clients recorded.
    ASSERT_FALSE(state6_.failureDetected());
    EXPECT_EQ(0, state6_.getUnackedClientsCount());
    EXPECT_EQ(0, state6_.getConnectingClientsCount());
    EXPECT_EQ(0, state6_.getAnalyzedMessagesCount());

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
    EXPECT_EQ(10, state6_.getUnackedClientsCount());
    EXPECT_EQ(10, state6_.getConnectingClientsCount());
    EXPECT_EQ(10, state6_.getAnalyzedMessagesCount());

    // Let's provide similar set of requests but this time the "elapsed time" is
    // below the threshold. This should not reduce the number of unacked or new
    // clients.
    for (uint8_t i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, i,
                                                             900)));
        ASSERT_FALSE(state6_.failureDetected())
            << "failure detected for the request number "
            << static_cast<int>(i);
    }
    EXPECT_EQ(10, state6_.getUnackedClientsCount());
    EXPECT_EQ(10, state6_.getConnectingClientsCount());
    EXPECT_EQ(20, state6_.getAnalyzedMessagesCount());

    // Let's create a message from a new (not recorded yet) client with the
    // "elapsed time" value below the threshold. It should not count as failure.
    ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, 10, 600)));

    // Still no failure.
    ASSERT_FALSE(state6_.failureDetected());
    EXPECT_EQ(10, state6_.getUnackedClientsCount());
    EXPECT_EQ(11, state6_.getConnectingClientsCount());
    EXPECT_EQ(21, state6_.getAnalyzedMessagesCount());

    // Let's repeat one of the requests which already have been recorded as
    // unacked but with a greater value of "elapsed time". This should not
    // be counted because only new clients count.
    ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, 3, 2000)));
    ASSERT_FALSE(state6_.failureDetected());
    EXPECT_EQ(10, state6_.getUnackedClientsCount());
    EXPECT_EQ(11, state6_.getConnectingClientsCount());
    EXPECT_EQ(22, state6_.getAnalyzedMessagesCount());

    // New unacked client should cause failure to be detected.
    ASSERT_NO_THROW(state6_.analyzeMessage(createMessage6(DHCPV6_SOLICIT, 11, 1500)));
    ASSERT_TRUE(state6_.failureDetected());
    EXPECT_EQ(11, state6_.getUnackedClientsCount());
    EXPECT_EQ(12, state6_.getConnectingClientsCount());
    EXPECT_EQ(23, state6_.getAnalyzedMessagesCount());

    // Poking should cause all counters to reset as it is an indication that the
    // control connection has been re-established.
    ASSERT_NO_THROW(state6_.poke());

    // We're back to no failure state.
    EXPECT_FALSE(state6_.failureDetected());
    EXPECT_EQ(0, state6_.getUnackedClientsCount());
    EXPECT_EQ(0, state6_.getConnectingClientsCount());
    EXPECT_EQ(0, state6_.getAnalyzedMessagesCount());
}

// This test verifies that it is possible to disable analysis of the DHCPv6
// packets in which case the partner's failure is assumed when there is
// no connection over the control channel.
void
CommunicationStateTest::failureDetectionDisabled6Test() {
    state6_.config_->setMaxUnackedClients(0);
    EXPECT_TRUE(state6_.failureDetected());
}

// This test verifies that the clock skew is checked properly by the
// clockSkewShouldWarn and clockSkewShouldTerminate functions.
void
CommunicationStateTest::clockSkewTest() {
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
void
CommunicationStateTest::logFormatClockSkewTest() {
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

    // The logFormatClockSkew uses the clock_skew_ value which is computed
    // at the time when setPartnerTime() is called. Therefore, we can't
    // just assume that it is 15s because it may be already slightly off.
    // Let's compare the output with the actual clock_skew_ value remembered
    // in the state_ instance.
    ASSERT_FALSE(state_.clock_skew_.is_special());
    ASSERT_FALSE(state_.clock_skew_.is_negative());
    std::ostringstream s;
    s << state_.clock_skew_.seconds() << "s ahead";
    EXPECT_TRUE(log.find(s.str()) != std::string::npos) <<
                " log content wrong: " << log;

    // Partner time is behind by 15s.
    state_.setPartnerTime(HttpDateTime(now - offset).rfc1123Format());
    ASSERT_NO_THROW(log = state_.logFormatClockSkew());

    // Again, extract the actual clock skew remembered in the state_ instance.
    ASSERT_FALSE(state_.clock_skew_.is_special());
    auto skew = state_.clock_skew_;

    // It must be negative this time.
    ASSERT_TRUE(skew.is_negative());
    // Convert it to positive value so we can use to to build the expected string.
    skew = -skew;
    std::ostringstream s2;
    s2 << skew.seconds() << "s behind";
    EXPECT_TRUE(log.find(s2.str()) != std::string::npos) <<
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

// Tests that the communication state report is correct.
void
CommunicationStateTest::getReportTest() {
    state_.setPartnerState("waiting");

    auto scopes = Element::createList();
    scopes->add(Element::create("server1"));
    state_.setPartnerScopes(scopes);

    state_.poke();

    // Simulate the communications interrupted state.
    state_.modifyPokeTime(-100);

    // Send two DHCP packets of which one has secs value beyond the threshold and
    // the other one lower than the threshold.
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 0, 0, 5)));
    ASSERT_NO_THROW(state_.analyzeMessage(createMessage4(DHCPDISCOVER, 1, 0, 15)));

    // Get the report.
    auto report = state_.getReport();
    ASSERT_TRUE(report);

    // Compare with the expected output.
    std::string expected = "{"
        "    \"age\": 100,"
        "    \"in-touch\": true,"
        "    \"last-scopes\": [ \"server1\" ],"
        "    \"last-state\": \"waiting\","
        "    \"communication-interrupted\": true,"
        "    \"connecting-clients\": 2,"
        "    \"unacked-clients\": 1,"
        "    \"unacked-clients-left\": 10,"
        "    \"analyzed-packets\": 2"
        "}";
    EXPECT_TRUE(isEquivalent(Element::fromJSON(expected), report));
}

// Tests unusual values used to create the report.
void
CommunicationStateTest::getReportDefaultValuesTest() {
    auto report = state_.getReport();
    ASSERT_TRUE(report);

    // Compare with the expected output.
    std::string expected = "{"
        "    \"age\": 0,"
        "    \"in-touch\": false,"
        "    \"last-scopes\": [ ],"
        "    \"last-state\": \"\","
        "    \"communication-interrupted\": false,"
        "    \"connecting-clients\": 0,"
        "    \"unacked-clients\": 0,"
        "    \"unacked-clients-left\": 0,"
        "    \"analyzed-packets\": 0"
        "}";
    EXPECT_TRUE(isEquivalent(Element::fromJSON(expected), report));
}

void
CommunicationStateTest::getUnsentUpdateCountTest() {
    // Initially the count should be 0.
    EXPECT_EQ(0, state_.getUnsentUpdateCount());

    // Increasing the value by 1 several times.
    EXPECT_NO_THROW(state_.increaseUnsentUpdateCount());
    EXPECT_EQ(1, state_.getUnsentUpdateCount());
    EXPECT_NO_THROW(state_.increaseUnsentUpdateCount());
    EXPECT_EQ(2, state_.getUnsentUpdateCount());
    EXPECT_NO_THROW(state_.increaseUnsentUpdateCount());
    EXPECT_EQ(3, state_.getUnsentUpdateCount());

    // Test that the method under test protects against an overflow
    // resetting the value to 0.
    state_.unsent_update_count_ = std::numeric_limits<uint64_t>::max();
    EXPECT_NO_THROW(state_.increaseUnsentUpdateCount());
    EXPECT_EQ(1, state_.getUnsentUpdateCount());
}

void
CommunicationStateTest::hasPartnerNewUnsentUpdatesTest() {
    // Initially the counts should be 0.
    EXPECT_FALSE(state_.hasPartnerNewUnsentUpdates());

    // Set a positive value. It should be noticed.
    EXPECT_NO_THROW(state_.setPartnerUnsentUpdateCount(5));
    EXPECT_TRUE(state_.hasPartnerNewUnsentUpdates());

    // No change, no new unsent updates.
    EXPECT_NO_THROW(state_.setPartnerUnsentUpdateCount(5));
    EXPECT_FALSE(state_.hasPartnerNewUnsentUpdates());

    // Change it again. New updates.
    EXPECT_NO_THROW(state_.setPartnerUnsentUpdateCount(10));
    EXPECT_TRUE(state_.hasPartnerNewUnsentUpdates());

    // Set it to 0 to simulate restart. No updates.
    EXPECT_NO_THROW(state_.setPartnerUnsentUpdateCount(0));
    EXPECT_FALSE(state_.hasPartnerNewUnsentUpdates());
}

TEST_F(CommunicationStateTest, partnerStateTest) {
    partnerStateTest();
}

TEST_F(CommunicationStateTest, partnerStateTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    partnerStateTest();
}

TEST_F(CommunicationStateTest, partnerScopesTest) {
    partnerScopesTest();
}

TEST_F(CommunicationStateTest, partnerScopesTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    partnerScopesTest();
}

TEST_F(CommunicationStateTest, initialDurationTest) {
    initialDurationTest();
}

TEST_F(CommunicationStateTest, initialDurationTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    initialDurationTest();
}

TEST_F(CommunicationStateTest, pokeTest) {
    pokeTest();
}

TEST_F(CommunicationStateTest, pokeTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    pokeTest();
}

TEST_F(CommunicationStateTest, heartbeatTest) {
    heartbeatTest();
}

TEST_F(CommunicationStateTest, heartbeatTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    heartbeatTest();
}

TEST_F(CommunicationStateTest, startHeartbeatInvalidValuesTest) {
    startHeartbeatInvalidValuesTest();
}

TEST_F(CommunicationStateTest, startHeartbeatInvalidValuesTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    startHeartbeatInvalidValuesTest();
}

TEST_F(CommunicationStateTest, detectFailureV4Test) {
    detectFailureV4Test();
}

TEST_F(CommunicationStateTest, detectFailureV4TestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    detectFailureV4Test();
}

TEST_F(CommunicationStateTest, failureDetectionDisabled4Test) {
    failureDetectionDisabled4Test();
}

TEST_F(CommunicationStateTest, failureDetectionDisabled4TestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    failureDetectionDisabled4Test();
}

TEST_F(CommunicationStateTest, detectFailureV6Test) {
    detectFailureV6Test();
}

TEST_F(CommunicationStateTest, detectFailureV6TestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    detectFailureV6Test();
}

TEST_F(CommunicationStateTest, failureDetectionDisabled6Test) {
    failureDetectionDisabled6Test();
}

TEST_F(CommunicationStateTest, failureDetectionDisabled6TestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    failureDetectionDisabled6Test();
}

TEST_F(CommunicationStateTest, clockSkewTest) {
    clockSkewTest();
}

TEST_F(CommunicationStateTest, clockSkewTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    clockSkewTest();
}

TEST_F(CommunicationStateTest, logFormatClockSkewTest) {
    logFormatClockSkewTest();
}

TEST_F(CommunicationStateTest, logFormatClockSkewTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    logFormatClockSkewTest();
}

TEST_F(CommunicationStateTest, getReportTest) {
    getReportTest();
}

TEST_F(CommunicationStateTest, getReportTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    getReportTest();
}

TEST_F(CommunicationStateTest, getReportDefaultValuesTest) {
    getReportDefaultValuesTest();
}

TEST_F(CommunicationStateTest, getReportDefaultValuesTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    getReportDefaultValuesTest();
}

TEST_F(CommunicationStateTest, getUnsentUpdateCountTest) {
    getUnsentUpdateCountTest();
}

TEST_F(CommunicationStateTest, getUnsentUpdateCountTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    getUnsentUpdateCountTest();
}

TEST_F(CommunicationStateTest, hasPartnerNewUnsentUpdatesTest) {
    hasPartnerNewUnsentUpdatesTest();
}

TEST_F(CommunicationStateTest, hasPartnerNewUnsentUpdatesTestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    hasPartnerNewUnsentUpdatesTest();
}

}
