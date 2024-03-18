// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <monitored_duration.h>
#include <dhcp/dhcp6.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <sstream>
#include <unordered_set>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfmon;
using namespace boost::posix_time;

namespace {

// Exercises the basic functions of DurationDataInterval.
TEST(DurationDataInterval, basics) {
    auto start_time = PktEvent::now();

    DurationDataIntervalPtr interval;

    // Default Construct a interval.
    interval.reset(new DurationDataInterval());
    ASSERT_TRUE(interval);

    // Verify contents.
    // Start time is set to current time by default.
    EXPECT_GE(interval->getStartTime(), start_time);
    EXPECT_EQ(interval->getOccurrences(), 0);
    EXPECT_EQ(interval->getMinDuration(), pos_infin);
    EXPECT_EQ(interval->getMaxDuration(), neg_infin);
    EXPECT_EQ(interval->getTotalDuration(), DurationDataInterval::ZERO_DURATION());
    EXPECT_EQ(interval->getAverageDuration(), DurationDataInterval::ZERO_DURATION());

    // Verify that start time can be specified.
    interval.reset(new DurationDataInterval(start_time + milliseconds(5000)));
    ASSERT_TRUE(interval);
    EXPECT_EQ(interval->getStartTime() - start_time, milliseconds(5000));

    // Add 100ms duration and check contents.
    Duration d100(milliseconds(100));
    interval->addDuration(d100);
    EXPECT_EQ(interval->getOccurrences(), 1);
    EXPECT_EQ(interval->getMinDuration(), d100);
    EXPECT_EQ(interval->getMaxDuration(), d100);
    EXPECT_EQ(interval->getTotalDuration(), d100);
    EXPECT_EQ(interval->getAverageDuration(), d100);

    // Add 300ms duration and check contents.
    Duration d300(milliseconds(300));
    interval->addDuration(d300);
    EXPECT_EQ(interval->getOccurrences(), 2);
    EXPECT_EQ(interval->getMinDuration(), d100);
    EXPECT_EQ(interval->getMaxDuration(), d300);
    EXPECT_EQ(interval->getTotalDuration(), d100 + d300);
    EXPECT_EQ(interval->getAverageDuration(), Duration(milliseconds(200)));

    // Add 50ms duration and check contents.
    Duration d50(milliseconds(50));
    interval->addDuration(d50);
    EXPECT_EQ(interval->getOccurrences(), 3);
    EXPECT_EQ(interval->getMinDuration(), d50);
    EXPECT_EQ(interval->getMaxDuration(), d300);
    EXPECT_EQ(interval->getTotalDuration(), d100 + d300 + d50);
    EXPECT_EQ(interval->getAverageDuration(), Duration(milliseconds(150)));

    // Add a zero duration and check contents.
    interval->addDuration(DurationDataInterval::ZERO_DURATION());
    EXPECT_EQ(interval->getOccurrences(), 4);
    EXPECT_EQ(interval->getMinDuration(), DurationDataInterval::ZERO_DURATION());
    EXPECT_EQ(interval->getMaxDuration(), d300);
    EXPECT_EQ(interval->getTotalDuration(), d100 + d300 + d50);
    EXPECT_EQ(interval->getAverageDuration(), Duration(microseconds(112500)));
}

// Exercises the basic functions of DurationDataInterval.
TEST(DurationKey, basics) {
    DurationKeyPtr key;

    // Create valid v4 key, verify contents and label.
    ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                  "process_started", "process_completed",
                                  SUBNET_ID_GLOBAL)));
    ASSERT_TRUE(key);
    EXPECT_EQ(key->getFamily(), AF_INET);
    EXPECT_EQ(key->getQueryType(), DHCPDISCOVER);
    EXPECT_EQ(key->getResponseType(), DHCPOFFER);
    EXPECT_EQ(key->getStartEventLabel(), "process_started");
    EXPECT_EQ(key->getStopEventLabel(), "process_completed");
    EXPECT_EQ(key->getSubnetId(), SUBNET_ID_GLOBAL);
    EXPECT_EQ("DHCPDISCOVER-DHCPOFFER.process_started-process_completed.0", key->getLabel());

    // Create valid v6 key, verify contents and label.
    ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                  "mt_queued", "process_started", 77)));
    ASSERT_TRUE(key);
    EXPECT_EQ(key->getFamily(), AF_INET6);
    EXPECT_EQ(key->getQueryType(), DHCPV6_SOLICIT);
    EXPECT_EQ(key->getResponseType(), DHCPV6_ADVERTISE);
    EXPECT_EQ(key->getStartEventLabel(), "mt_queued");
    EXPECT_EQ(key->getStopEventLabel(), "process_started");
    EXPECT_EQ(key->getSubnetId(), 77);
    EXPECT_EQ("SOLICIT-ADVERTISE.mt_queued-process_started.77", key->getLabel());

    // Make sure constructor catches an insane message pairing.
    ASSERT_THROW_MSG(key.reset(new DurationKey(AF_INET6, DHCPV6_ADVERTISE, DHCPV6_SOLICIT,
                               "mt_queued", "process_started", 77)), BadValue,
                     "Query type not supported by monitoring: ADVERTISE");
}

// Verify v4 message pair validation works.
TEST(DurationKey, validateMessagePairs4) {
    //  Defines a test scenario.
    struct Scenario {
        // Query type to use in the scenario.
        uint8_t query_type_;
        // Valid response types for query type (if any).
        std::unordered_set<uint8_t> valid_responses_;
    };

    // List of scenarios to test, one per v4 message type.
    std::list<Scenario> scenarios {
        {DHCP_NOTYPE, {DHCP_NOTYPE, DHCPOFFER, DHCPACK, DHCPNAK}},
        {DHCPDISCOVER, {DHCP_NOTYPE, DHCPOFFER, DHCPNAK}},
        {DHCPOFFER, {}},
        {DHCPREQUEST, {DHCP_NOTYPE, DHCPACK, DHCPNAK}},
        {DHCPDECLINE, {}},
        {DHCPACK, {}},
        {DHCPNAK, {}},
        {DHCPRELEASE, {}},
        {DHCPINFORM, {DHCP_NOTYPE, DHCPACK}},
//      {DHCPFORCERENEW, {}},        commented out in dhcp4.h
        {DHCPLEASEQUERY, {}},
        {DHCPLEASEUNASSIGNED, {}},
        {DHCPLEASEUNKNOWN, {}},
        {DHCPLEASEACTIVE, {}},
        {DHCPBULKLEASEQUERY, {}},
        {DHCPLEASEQUERYDONE, {}},
//      {DHCPACTIVELEASEQUERY, {}}, commented out in dhcp4.h
        {DHCPLEASEQUERYSTATUS, {}},
        {DHCPTLS, {}},
    };

    // Iterate over the scenarios.  Attempt to pair each scenario query type with every v4 message
    // type as a response type.  If the response type is in the scenario's valid list, the pair
    // should validate, otherwise it should throw.
    for (auto const& scenario : scenarios) {
        for (uint8_t response_type = DHCP_NOTYPE; response_type < DHCP_TYPES_EOF; ++response_type) {
            if (scenario.valid_responses_.count(response_type)) {
                ASSERT_NO_THROW_LOG(
                    DurationKey::validateMessagePair(AF_INET, scenario.query_type_, response_type));
            } else {
                ASSERT_THROW(
                    DurationKey::validateMessagePair(AF_INET, scenario.query_type_, response_type),
                    BadValue);
            }
        }
    }
}

// Verify v6 message pair validation works.
TEST(DurationKey, validateMessagePairs6) {
    //  Defines a test scenario.
    struct Scenario {
        // Query type to use in the scenario.
        uint8_t query_type_;
        // Valid response types for query type (if any).
        std::unordered_set<uint8_t> valid_responses_;
    };

    // List of scenarios to test, one per v6 message type.
    std::list<Scenario> scenarios {
        {DHCPV6_NOTYPE, {DHCPV6_NOTYPE, DHCPV6_ADVERTISE, DHCPV6_REPLY}},
        {DHCPV6_SOLICIT, {DHCPV6_NOTYPE, DHCPV6_ADVERTISE, DHCPV6_REPLY}},
        {DHCPV6_ADVERTISE, {}},
        {DHCPV6_REQUEST, {DHCPV6_NOTYPE, DHCPV6_REPLY}},
        {DHCPV6_CONFIRM, {DHCPV6_NOTYPE, DHCPV6_REPLY}},
        {DHCPV6_RENEW, {DHCPV6_NOTYPE, DHCPV6_REPLY}},
        {DHCPV6_REBIND, {DHCPV6_NOTYPE, DHCPV6_REPLY}},
        {DHCPV6_REPLY, {}},
        {DHCPV6_RELEASE, {}},
        {DHCPV6_DECLINE, {}},
        {DHCPV6_RECONFIGURE, {}},
        {DHCPV6_INFORMATION_REQUEST, {}},
        {DHCPV6_RELAY_FORW, {}},
        {DHCPV6_RELAY_REPL, {}},
        {DHCPV6_LEASEQUERY, {}},
        {DHCPV6_LEASEQUERY_REPLY, {}},
        {DHCPV6_LEASEQUERY_DONE, {}},
        {DHCPV6_LEASEQUERY_DATA, {}},
        {DHCPV6_RECONFIGURE_REQUEST, {}},
        {DHCPV6_RECONFIGURE_REPLY, {}},
        {DHCPV6_DHCPV4_QUERY, {}},
        {DHCPV6_DHCPV4_RESPONSE, {}},
        {DHCPV6_ACTIVELEASEQUERY, {}},
        {DHCPV6_STARTTLS, {}},
        {DHCPV6_BNDUPD, {}},
        {DHCPV6_BNDREPLY, {}},
        {DHCPV6_POOLREQ, {}},
        {DHCPV6_POOLRESP, {}},
        {DHCPV6_UPDREQ, {}},
        {DHCPV6_UPDREQALL, {}},
        {DHCPV6_UPDDONE, {}},
        {DHCPV6_CONNECT, {}},
        {DHCPV6_CONNECTREPLY, {}},
        {DHCPV6_DISCONNECT, {}},
        {DHCPV6_STATE, {}},
        {DHCPV6_CONTACT, {}}
    };

    // Iterate over the scenarios.  Attempt to pair each scenario query type with every v6 message
    // type as a response type.  If the response type is in the scenario's valid list, the pair
    // should validate, otherwise it should throw.
    for (auto const& scenario : scenarios) {
        for (uint8_t response_type = DHCPV6_NOTYPE; response_type < DHCPV6_TYPES_EOF; ++response_type) {
            if (scenario.valid_responses_.count(response_type)) {
                ASSERT_NO_THROW_LOG(
                    DurationKey::validateMessagePair(AF_INET6, scenario.query_type_, response_type));
            } else {
                ASSERT_THROW(
                    DurationKey::validateMessagePair(AF_INET6, scenario.query_type_, response_type),
                    BadValue);
            }
        }
    }
}

/// @brief Verify DurationKey equality operator
TEST(DurationKey, equalityOperators) {
    DurationKeyPtr refkey;
    DurationKeyPtr compkey;

    ASSERT_NO_THROW_LOG(refkey.reset(new DurationKey(AF_INET6, DHCPV6_REQUEST, DHCPV6_REPLY,
                                     "event_2", "event_3", 100)));

    ASSERT_NO_THROW_LOG(compkey.reset(new DurationKey(AF_INET6, DHCPV6_REQUEST, DHCPV6_REPLY,
                                      "event_2", "event_3", 100)));
    EXPECT_EQ(*compkey, *refkey);

    ASSERT_NO_THROW_LOG(compkey.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_REPLY,
                                      "event_2", "event_3", 100)));
    EXPECT_NE(*compkey, *refkey);
}

// Verifies MonitoredDuration valid construction.
TEST(MonitoredDuration, validConstructors) {
    MonitoredDurationPtr mond;
    Duration interval_duration(seconds(60));

    // Create valid v4 duration, verify contents and label.
    ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                  "process_started", "process_completed",
                                   SUBNET_ID_GLOBAL, interval_duration)));
    ASSERT_TRUE(mond);
    EXPECT_EQ(mond->getFamily(), AF_INET);
    EXPECT_EQ(mond->getQueryType(), DHCPDISCOVER);
    EXPECT_EQ(mond->getResponseType(), DHCPOFFER);
    EXPECT_EQ(mond->getStartEventLabel(), "process_started");
    EXPECT_EQ(mond->getStopEventLabel(), "process_completed");
    EXPECT_EQ(mond->getSubnetId(), SUBNET_ID_GLOBAL);
    EXPECT_EQ("DHCPDISCOVER-DHCPOFFER.process_started-process_completed.0", mond->getLabel());
    EXPECT_EQ(mond->getIntervalDuration(), interval_duration);
    EXPECT_FALSE(mond->getCurrentInterval());
    EXPECT_FALSE(mond->getPreviousInterval());

    // Create valid v6 key and use that to create an alarm. Verify contents and label.
    DurationKeyPtr key;
    ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                  "mt_queued", "process_started", 77)));

    ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(*key, interval_duration)));
    ASSERT_TRUE(mond);
    EXPECT_EQ(mond->getFamily(), AF_INET6);
    EXPECT_EQ(mond->getQueryType(), DHCPV6_SOLICIT);
    EXPECT_EQ(mond->getResponseType(), DHCPV6_ADVERTISE);
    EXPECT_EQ(mond->getStartEventLabel(), "mt_queued");
    EXPECT_EQ(mond->getStopEventLabel(), "process_started");
    EXPECT_EQ(mond->getSubnetId(), 77);
    EXPECT_EQ("SOLICIT-ADVERTISE.mt_queued-process_started.77", mond->getLabel());
    EXPECT_EQ(mond->getIntervalDuration(), interval_duration);
    EXPECT_FALSE(mond->getCurrentInterval());
    EXPECT_FALSE(mond->getPreviousInterval());
}

// Verifies Copy construction.  Since current and previous intervals are not
// exposed, this test relies on addSample() to alter them.
TEST(MonitoredDuration, copyConstructors) {
    MonitoredDurationPtr mond;
    Duration interval_duration(microseconds(10));

    // Create valid v4 duration, verify contents and label.
    ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                   "process_started", "process_completed",
                                   SUBNET_ID_GLOBAL, interval_duration)));

    // Make a copy.
    MonitoredDurationPtr duplicate;
    duplicate.reset(new MonitoredDuration(*mond));

    // Should have different pointers.
    EXPECT_NE(duplicate, mond);

    // Key values should be equal (DurationKey::operator==).
    EXPECT_EQ(*duplicate, *mond);

    // Check non-key members.
    EXPECT_EQ(duplicate->getIntervalDuration(), mond->getIntervalDuration());
    EXPECT_FALSE(duplicate->getCurrentInterval());
    EXPECT_FALSE(duplicate->getPreviousInterval());

    // Add a sample to the original.
    EXPECT_FALSE(mond->addSample(microseconds(2)));

    // Make a new copy.
    duplicate.reset(new MonitoredDuration(*mond));

    // Current intervals should exist.
    ASSERT_TRUE(mond->getCurrentInterval());
    ASSERT_TRUE(duplicate->getCurrentInterval());
    // They should not be the same object but the content should be equal.
    EXPECT_NE(duplicate->getCurrentInterval(), mond->getCurrentInterval());
    EXPECT_EQ(*duplicate->getCurrentInterval(), *mond->getCurrentInterval());
    // Previous interval should not exist.
    ASSERT_FALSE(mond->getPreviousInterval());
    ASSERT_FALSE(duplicate->getPreviousInterval());

    // Sleep past interval duration.
    usleep(20);

    // Add anoter sample to the original.
    EXPECT_TRUE(mond->addSample(microseconds(2)));

    // Make a new copy.
    duplicate.reset(new MonitoredDuration(*mond));

    // Current intervals should exist.
    ASSERT_TRUE(mond->getCurrentInterval());
    ASSERT_TRUE(duplicate->getCurrentInterval());
    // They should not be the same object but the content should be equal.
    EXPECT_NE(duplicate->getCurrentInterval(), mond->getCurrentInterval());
    EXPECT_EQ(*duplicate->getCurrentInterval(), *mond->getCurrentInterval());

    // Current previous should exist.
    ASSERT_TRUE(mond->getPreviousInterval());
    ASSERT_TRUE(duplicate->getPreviousInterval());
    // They should not be the same object but the content should be equal.
    EXPECT_NE(duplicate->getPreviousInterval(), mond->getPreviousInterval());
    EXPECT_EQ(*duplicate->getPreviousInterval(), *mond->getPreviousInterval());
}

// Verifies MonitoredDuration invalid construction.
TEST(MonitoredDuration, invalidConstructors) {
    MonitoredDurationPtr mond;

    // Make sure we catch an invalid message pairing.
    Duration interval_duration = seconds(60);
    ASSERT_THROW_MSG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPDISCOVER,
                                                      "process_started", "process_completed",
                                                      SUBNET_ID_GLOBAL, interval_duration)),
                     BadValue,
                     "Response type: DHCPDISCOVER not valid for query type: DHCPDISCOVER");

    // Interval duration cannot be zero.
    interval_duration = DurationDataInterval::ZERO_DURATION();
    ASSERT_THROW_MSG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                                      "process_started", "process_completed",
                                                      SUBNET_ID_GLOBAL, interval_duration)),
                     BadValue,
                     "MonitoredDuration - interval_duration 00:00:00,"
                     " is invalid, it must be greater than 0");

    // Interval duration cannot be negative.
    ASSERT_THROW_MSG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                                      "process_started", "process_completed",
                                                      SUBNET_ID_GLOBAL, seconds(-5))),
                     BadValue,
                     "MonitoredDuration - interval_duration -00:00:05,"
                     " is invalid, it must be greater than 0");

    // Create valid v6 key.
    DurationKeyPtr key;
    ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                                  "mt_queued", "process_started", 77)));

    // Interval duration cannot be zero.
    ASSERT_THROW_MSG(mond.reset(new MonitoredDuration(*key, interval_duration)),
                     BadValue,
                     "MonitoredDuration - interval_duration 00:00:00,"
                     " is invalid, it must be greater than 0");

    // Interval duration cannot be negative.
    ASSERT_THROW_MSG(mond.reset(new MonitoredDuration(*key, seconds(-5))),
                     BadValue,
                     "MonitoredDuration - interval_duration -00:00:05,"
                     " is invalid, it must be greater than 0");
}

// Exercises MonitoredDuration::addSample() and MonitoredDuration::clear().
TEST(MonitoredDuration, addSampleAndClear) {
    MonitoredDurationPtr mond;
    Duration interval_duration(milliseconds(50));

    // Create valid v4 duration with interval duration of 50ms.
    ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                                         "process_started", "process_completed",
                                                         SUBNET_ID_GLOBAL, interval_duration)));
    ASSERT_TRUE(mond);

    // Initially there are no intervals.
    EXPECT_FALSE(mond->getCurrentInterval());
    EXPECT_FALSE(mond->getPreviousInterval());

    auto two_ms = milliseconds(2);
    bool should_report = false;

    // Add a sample and verify nothing to report and that it creates a
    // current interval.
    ASSERT_NO_THROW(should_report = mond->addSample(two_ms));
    EXPECT_FALSE(should_report);
    DurationDataIntervalPtr current_interval = mond->getCurrentInterval();
    ASSERT_TRUE(current_interval);

    // First pass, we should only have a current interval,
    // nothing to report, one occurrence and a total duration of 10ms.
    EXPECT_FALSE(mond->getPreviousInterval());
    EXPECT_FALSE(should_report);
    EXPECT_EQ(current_interval->getOccurrences(), 1);
    EXPECT_EQ(current_interval->getTotalDuration(), two_ms);

    // Save a copy of the current interval pointer.
    DurationDataIntervalPtr original_interval = current_interval;

    // Add 4 two ms samples during the current interval.
    DurationDataIntervalPtr previous_interval;
    for (int i = 1; i < 5; ++i) {
        // Add a two ms sample, it should return false as its not
        // time to report.
        ASSERT_NO_THROW(should_report = mond->addSample(two_ms));
        EXPECT_FALSE(should_report);
        current_interval = mond->getCurrentInterval();
        ASSERT_TRUE(current_interval);

        // Make sure the current interval hasn't been replaced and we
        // have no previous interval.
        EXPECT_EQ(current_interval, original_interval);
        EXPECT_FALSE(mond->getPreviousInterval());
        // Verify the sample was added.
        EXPECT_EQ(current_interval->getOccurrences(), (i + 1));
        EXPECT_EQ(current_interval->getTotalDuration(), (two_ms * (i + 1)));
    }

    // Sleep til past the end of interval
    usleep(60 * 1000);

    // Add another sample.
    ASSERT_NO_THROW(should_report = mond->addSample(two_ms));
    current_interval = mond->getCurrentInterval();
    ASSERT_TRUE(current_interval);

    // We should have crossed the interval boundary.
    // Previous interval should be equal to the original interval and
    // should_report should be true.  The new current interval should
    // have 1 occurrence and a total of 10ms.
    previous_interval = mond->getPreviousInterval();
    EXPECT_TRUE(previous_interval);
    EXPECT_EQ(previous_interval, original_interval);
    EXPECT_TRUE(should_report);
    EXPECT_EQ(current_interval->getOccurrences(), 1);
    EXPECT_EQ(current_interval->getTotalDuration(), two_ms);

    // Verify that clear wipes the intervals.
    ASSERT_NO_THROW_LOG(mond->clear());
    EXPECT_FALSE(mond->getCurrentInterval());
    EXPECT_FALSE(mond->getPreviousInterval());
}

TEST(MonitoredDuration, expireInterval) {
    MonitoredDurationPtr mond;
    Duration interval_duration(milliseconds(50));
    auto start_time = PktEvent::now();
    auto ten_ms = milliseconds(10);

    // Create valid v4 duration with interval duration of 50ms.
    ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                                         "process_started", "process_completed",
                                                         SUBNET_ID_GLOBAL, interval_duration)));
    ASSERT_TRUE(mond);

    // Initially there are no intervals.
    EXPECT_FALSE(mond->getCurrentInterval());
    EXPECT_FALSE(mond->getPreviousInterval());
    EXPECT_EQ(mond->getCurrentIntervalStart(), PktEvent::MIN_TIME());

    ASSERT_THROW_MSG(mond->expireCurrentInterval(), InvalidOperation,
                     "MonitoredDuration::expireInterval - no current interval for:"
                     " DHCPDISCOVER-DHCPOFFER.process_started-process_completed.0");

    ASSERT_NO_THROW(mond->addSample(ten_ms));
    auto current_interval = mond->getCurrentInterval();
    ASSERT_TRUE(current_interval);
    EXPECT_EQ(current_interval->getOccurrences(), 1);
    EXPECT_EQ(current_interval->getTotalDuration(), ten_ms);
    EXPECT_FALSE(mond->getPreviousInterval());
    EXPECT_GE(mond->getCurrentIntervalStart(), start_time);
    EXPECT_EQ(mond->getCurrentIntervalStart(), current_interval->getStartTime());

    ASSERT_NO_THROW_LOG(mond->expireCurrentInterval());
    EXPECT_FALSE(mond->getCurrentInterval());

    auto previous_interval = mond->getPreviousInterval();
    EXPECT_EQ(previous_interval, current_interval);
    EXPECT_EQ(mond->getCurrentIntervalStart(), PktEvent::MIN_TIME());
}

} // end of anonymous namespace
