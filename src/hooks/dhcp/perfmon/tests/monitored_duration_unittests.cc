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

/// @brief Exercises the basic functions of DurationDataInterval.
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
    EXPECT_GE(interval->getStartTime() - start_time, milliseconds(5000));

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

/// @brief Exercises the basic functions of DurationDataInterval.
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
    EXPECT_EQ(key->getEndEventLabel(), "process_completed");
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
    EXPECT_EQ(key->getEndEventLabel(), "process_started");
    EXPECT_EQ(key->getSubnetId(), 77);
    EXPECT_EQ("SOLICIT-ADVERTISE.mt_queued-process_started.77", key->getLabel());

    // Make sure constructor catches an insane message pairing.
    ASSERT_THROW_MSG(key.reset(new DurationKey(AF_INET6, DHCPV6_ADVERTISE, DHCPV6_SOLICIT,
                               "mt_queued", "process_started", 77)), BadValue,
                     "Query type not supported by monitoring: ADVERTISE");
}

/// @brief Verify v4 message pair validation works.
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
        { DHCP_NOTYPE, {DHCP_NOTYPE, DHCPOFFER, DHCPACK, DHCPNAK}},
        { DHCPDISCOVER, {DHCP_NOTYPE, DHCPOFFER, DHCPNAK}},
        { DHCPOFFER, {}},
        { DHCPREQUEST, {DHCP_NOTYPE, DHCPACK, DHCPNAK}},
        { DHCPDECLINE, {}},
        { DHCPACK, {}},
        { DHCPNAK, {}},
        { DHCPRELEASE, {}},
        { DHCPINFORM, {DHCP_NOTYPE, DHCPACK}},
//      { DHCPFORCERENEW, {}},        commented out in dhcp4.h
        { DHCPLEASEQUERY, {}},
        { DHCPLEASEUNASSIGNED, {}},
        { DHCPLEASEUNKNOWN, {}},
        { DHCPLEASEACTIVE, {}},
        { DHCPBULKLEASEQUERY, {}},
        { DHCPLEASEQUERYDONE, {}},
//      {  DHCPACTIVELEASEQUERY, {}}, commented out in dhcp4.h
        { DHCPLEASEQUERYSTATUS, {}},
        { DHCPTLS, {}},
    };

    // Iterate over the scenarios.  Attempt to pair each scenario query type with every v6 message
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

/// @brief Verify v4 message pair validation works.
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

/// @brief Verifies Alarm construction.
TEST(Alarm, validConstructors) {
    AlarmPtr alarm;

    auto start_time = PktEvent::now();

    // Create valid v4 alarm, verify contents and label.
    Duration low_water(milliseconds(50));
    Duration high_water(milliseconds(250));
    ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(AF_INET, DHCPDISCOVER, DHCPOFFER,
                              "process_started", "process_completed",
                              SUBNET_ID_GLOBAL,
                              low_water, high_water)));
    ASSERT_TRUE(alarm);
    EXPECT_EQ(alarm->getFamily(), AF_INET);
    EXPECT_EQ(alarm->getQueryType(), DHCPDISCOVER);
    EXPECT_EQ(alarm->getResponseType(), DHCPOFFER);
    EXPECT_EQ(alarm->getStartEventLabel(), "process_started");
    EXPECT_EQ(alarm->getEndEventLabel(), "process_completed");
    EXPECT_EQ(alarm->getSubnetId(), SUBNET_ID_GLOBAL);
    EXPECT_EQ("DHCPDISCOVER-DHCPOFFER.process_started-process_completed.0", alarm->getLabel());
    EXPECT_EQ(alarm->getSubnetId(), SUBNET_ID_GLOBAL);
    EXPECT_EQ(alarm->getLowWater(), low_water);
    EXPECT_EQ(alarm->getHighWater(), high_water);
    EXPECT_EQ(alarm->getState(), Alarm::CLEAR);
    EXPECT_GE(alarm->getStosTime(), start_time);

    start_time = PktEvent::now();

    // Create valid v6 key and use that to create an alarm. Verify contents and label.
    DurationKeyPtr key;
    ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                  "mt_queued", "process_started", 77)));

    ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(*key, low_water, high_water, false)));
    ASSERT_TRUE(alarm);
    EXPECT_EQ(alarm->getFamily(), AF_INET6);
    EXPECT_EQ(alarm->getQueryType(), DHCPV6_SOLICIT);
    EXPECT_EQ(alarm->getResponseType(), DHCPV6_ADVERTISE);
    EXPECT_EQ(alarm->getStartEventLabel(), "mt_queued");
    EXPECT_EQ(alarm->getEndEventLabel(), "process_started");
    EXPECT_EQ(alarm->getSubnetId(), 77);
    EXPECT_EQ("SOLICIT-ADVERTISE.mt_queued-process_started.77", alarm->getLabel());
    EXPECT_EQ(alarm->getLowWater(), low_water);
    EXPECT_EQ(alarm->getHighWater(), high_water);
    EXPECT_EQ(alarm->getState(), Alarm::DISABLED);
    EXPECT_GE(alarm->getStosTime(), start_time);
}

/// @brief Verifies Alarm invalid construction.
TEST(Alarm, invalidConstructors) {
    AlarmPtr alarm;

    // Make sure we catch an invalid message pairing.
    Duration low_water(milliseconds(50));
    Duration high_water(milliseconds(250));
    ASSERT_THROW_MSG(alarm.reset(new Alarm(AF_INET, DHCPDISCOVER, DHCPDISCOVER,
                                 "process_started", "process_completed",
                                 SUBNET_ID_GLOBAL, low_water, high_water)),
                      BadValue,
                      "Response type: DHCPDISCOVER not valid for query type: DHCPDISCOVER");

    // Low water too high, should throw.
    ASSERT_THROW_MSG(alarm.reset(new Alarm(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                "process_started", "process_completed",
                                 SUBNET_ID_GLOBAL, high_water, low_water)),
                      BadValue,
                      "low water: 00:00:00.250000, must be less than high water:"
                      " 00:00:00.050000");

    // Create valid v6 key.
    DurationKeyPtr key;
    ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                  "mt_queued", "process_started", 77)));

    // Low water too high, should throw.
    ASSERT_THROW_MSG(alarm.reset(new Alarm(*key, high_water, low_water)),
                     BadValue,
                     "low water: 00:00:00.250000, must be less than high water:"
                     " 00:00:00.050000");
}

TEST(Alarm, lowWaterHighWaterSetters) {
    // Create valid v4 alarm.
    Duration low_water(milliseconds(50));
    Duration high_water(milliseconds(250));
    AlarmPtr alarm;
    ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(AF_INET, DHCPDISCOVER, DHCPOFFER,
                              "process_started", "process_completed",
                              SUBNET_ID_GLOBAL,
                              low_water, high_water)));

    // Should be able to set thresholds to new, valid values.
    low_water += milliseconds(50);
    high_water -= milliseconds(100);
    ASSERT_NO_THROW(alarm->setLowWater(low_water));
    EXPECT_EQ(alarm->getLowWater(), low_water);
    ASSERT_NO_THROW(alarm->setHighWater(high_water));
    EXPECT_EQ(alarm->getHighWater(), high_water);

    // Setting low too high should fail and leave Alarm intact.
    ASSERT_THROW_MSG(alarm->setLowWater(high_water), BadValue,
                     "low water: 00:00:00.150000, must be less than high water: 00:00:00.150000");
    EXPECT_EQ(alarm->getLowWater(), low_water);

    // Setting high too low should fail and leave Alarm intact.
    ASSERT_THROW_MSG(alarm->setHighWater(low_water), BadValue,
                     "high water: 00:00:00.100000, must be greater than low water: 00:00:00.100000");
    EXPECT_EQ(alarm->getHighWater(), high_water);
}

TEST(Alarm, clearAndDisable) {
    auto start_time = PktEvent::now();
    AlarmPtr alarm;
    ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(AF_INET, DHCPDISCOVER, DHCPOFFER,
                              "process_started", "process_completed",
                              SUBNET_ID_GLOBAL, milliseconds(100), milliseconds(200))));

    // Initial state should be CLEAR, stos_time_ should be close to now, no report time.
    EXPECT_EQ(alarm->getState(), Alarm::CLEAR);
    EXPECT_GE(alarm->getStosTime(), start_time);
    EXPECT_EQ(alarm->getLastHighWaterReport(), PktEvent::EMPTY_TIME());

    // Save stos then nap.
    auto prev_time = alarm->getStosTime();
    usleep(100);

    // Change the state to DISABLED.  Should have a later stos_time_.
    ASSERT_NO_THROW(alarm->disable());
    EXPECT_EQ(alarm->getState(), Alarm::DISABLED);
    EXPECT_GE(alarm->getStosTime(), prev_time);
    EXPECT_EQ(alarm->getLastHighWaterReport(), PktEvent::EMPTY_TIME());

    // While we're disabled verify operations that are not allowed.
    ASSERT_THROW_MSG(alarm->checkSample(milliseconds(75), seconds(60)), InvalidOperation,
                     "Alarm::checkSample() - should not be called when alarm is DISABLED");

    // Save stos then nap.
    prev_time = alarm->getStosTime();
    usleep(100);

    // Restore the alarm to CLEAR.
    ASSERT_NO_THROW(alarm->clear());
    EXPECT_EQ(alarm->getState(), Alarm::CLEAR);
    EXPECT_GE(alarm->getStosTime(), prev_time);
    EXPECT_EQ(alarm->getLastHighWaterReport(), PktEvent::EMPTY_TIME());
}

/// @brief Verifies the result of Alarm::checkSample() over the range of scenarios.
/// The alarm is created in either the CLEAR or TRIGGERED state and then checkSample()
/// is invoked.  The scenarios tested are described by the table below:
///
/// ```
///                     INPUT                           |          OUTPUT
///    Test sample relationship       Input  Report Int.|
//     to the thresholds              State   Elapsed   | Report  State  Stos   Last Report
///    -------------------------------------------------|----------------------------------
///    sample < low_water                C      false   | false     C      -       -
///    sample < low_water                C      true    | false     C      -       -
///    sample < low_water                T      false   | true      C    updated  reset
///    sample < low_water                T      true    | true      C    updated  reset
///                                                     |
///    sample == low_water               C      false   | false     C      -       -
///    sample == low_water               C      true    | false     C      -       -
///    sample == low_water               T      false   | false     T      -       -
///    sample == low_water               T      true    | true      T             updated
///                                                     |
///    low_water < sample < high_water   C      false   | false     C      -       -
///    low_water < sample < high_water   C      true    | false     C      -       -
///    low_water < sample < high_water   T      false   | false     T      -       -
///    low_water < sample < high_water   T      true    | true      T      -      updated
///                                                     |
///    sample == high water              C      false   | false     C      -       -
///    sample == high water              C      true    | false     C      -       -
///    sample == high water              T      false   | false     T      -       -
///    sample == high water              T      true    | true      T      -      updated
///                                                     |
///    sample > high water               C      false   | true      T    updated  set
///    sample > high water               C      true    | true      T    updated  set
///    sample > high water               T      false   | false     T      -       -
///    sample > high water               T      true    | true      T      -      updated
/// ```
TEST(Alarm, checkSample) {
    // Create mnemonic constants.
    Duration low_water(milliseconds(100));
    Duration high_water(milliseconds(200));
    Duration lt_low_water(milliseconds(50));
    Duration eq_low_water = low_water;
    Duration mid_range(milliseconds(150));
    Duration eq_high_water = high_water;
    Duration gt_high_water(milliseconds(250));
    Duration report_interval(milliseconds(25));

    bool report_elapsed = true;
    bool should_report = true;

    // Enumerates possible outcomes for last_high_water_report.
    enum TimeChange {
        none,       // no change
        set,        // from empty time to time
        updated,    // updated to a more recent time
        reset       // reset to empty time
    };

    // Embodies a test scenario based on the table in the commentary. It does not
    // include a column for stos_time_ changes as they are easily inferred.
    struct Scenario {
        Duration sample_;                   // duration to test the alarm with
        Alarm::State input_state_;          // Starting state of the Alarm (CLEAR or TRIGGERED)
        bool report_interval_elapsed_;      // True if report interval has elapsed
        bool should_report_;                // True if checkSample() should return true
        Alarm::State output_state_;         // Alarm state after calling checkSample()
        TimeChange last_report_chg_;        // Expected change to last_high_water_report_
    };

    // Scenarios as described in the commentary.
    std::list<Scenario> scenarios = {
        { lt_low_water,   Alarm::CLEAR,     !report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { lt_low_water,   Alarm::CLEAR,      report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { lt_low_water,   Alarm::TRIGGERED, !report_elapsed,  should_report, Alarm::CLEAR,     TimeChange::reset },
        { lt_low_water,   Alarm::TRIGGERED,  report_elapsed,  should_report, Alarm::CLEAR,     TimeChange::reset },

        { eq_low_water,   Alarm::CLEAR,     !report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { eq_low_water,   Alarm::CLEAR,      report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { eq_low_water,   Alarm::TRIGGERED, !report_elapsed, !should_report, Alarm::TRIGGERED, TimeChange::none },
        { eq_low_water,   Alarm::TRIGGERED,  report_elapsed,  should_report, Alarm::TRIGGERED, TimeChange::updated },

        { mid_range,      Alarm::CLEAR,     !report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { mid_range,      Alarm::CLEAR,      report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { mid_range,      Alarm::TRIGGERED, !report_elapsed, !should_report, Alarm::TRIGGERED, TimeChange::none },
        { mid_range,      Alarm::TRIGGERED,  report_elapsed,  should_report, Alarm::TRIGGERED, TimeChange::updated },

        { eq_high_water,  Alarm::CLEAR,     !report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { eq_high_water,  Alarm::CLEAR,      report_elapsed, !should_report, Alarm::CLEAR,     TimeChange::none },
        { eq_high_water,  Alarm::TRIGGERED, !report_elapsed, !should_report, Alarm::TRIGGERED, TimeChange::none },
        { eq_high_water,  Alarm::TRIGGERED,  report_elapsed,  should_report, Alarm::TRIGGERED, TimeChange::updated },

        { gt_high_water,  Alarm::CLEAR,     !report_elapsed,  should_report, Alarm::TRIGGERED, TimeChange::set },
        { gt_high_water,  Alarm::CLEAR,      report_elapsed,  should_report, Alarm::TRIGGERED, TimeChange::set },
        { gt_high_water,  Alarm::TRIGGERED, !report_elapsed, !should_report, Alarm::TRIGGERED, TimeChange::none },
        { gt_high_water,  Alarm::TRIGGERED,  report_elapsed,  should_report, Alarm::TRIGGERED, TimeChange::updated },
    };

    AlarmPtr alarm;
    DurationKey key(AF_INET, DHCPDISCOVER, DHCPOFFER,
                    "process_started", "process_completed", SUBNET_ID_GLOBAL);
    size_t pass = 0;
    for (auto const& scenario : scenarios) {
        std::ostringstream oss;
        oss << "scenario: " << pass++;
        SCOPED_TRACE(oss.str());

        auto start_time = PktEvent::now();

        // Create an Alarm with the scenario starting characteristics.
        ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(key, low_water, high_water)));
        if (scenario.input_state_ == Alarm::TRIGGERED) {
            alarm->setState(Alarm::TRIGGERED);
            alarm->setLastHighWaterReport(!scenario.report_interval_elapsed_ ?
                                          PktEvent::now() : start_time - (report_interval * 2));
        }

        // Save the current timestamps.
        auto prev_stos_time = alarm->getStosTime();
        auto prev_report_time = alarm->getLastHighWaterReport();

        // Take a little nap.
        usleep(50);

        // Invoke checkSample() with the scenario sample duration.  It should not throw.
        bool should_report;
        ASSERT_NO_THROW_LOG(should_report = alarm->checkSample(scenario.sample_, report_interval));

        //  Verify that we returned the expected value for a reportable event (or not).
        EXPECT_EQ(should_report, scenario.should_report_);

        // Verify we ended up in the expected state.
        ASSERT_EQ(alarm->getState(), scenario.output_state_);

        // If the state changed, stos_time_ should have been updated.
        if (scenario.input_state_ != scenario.output_state_) {
            EXPECT_GT(alarm->getStosTime(), prev_stos_time);
        } else {
            EXPECT_EQ(alarm->getStosTime(), prev_stos_time);
        }

        // Verify the last_high_water_report_ outcome.
        switch(scenario.last_report_chg_) {
        case TimeChange::none:
            EXPECT_EQ(alarm->getLastHighWaterReport(), prev_report_time);
            break;
        case TimeChange::set:
            EXPECT_EQ(prev_report_time, PktEvent::EMPTY_TIME());
            EXPECT_GE(alarm->getLastHighWaterReport(), alarm->getStosTime());
            break;
        case TimeChange::updated:
            EXPECT_GT(alarm->getLastHighWaterReport(), prev_report_time);
            break;
        case TimeChange::reset:
            EXPECT_EQ(alarm->getLastHighWaterReport(), PktEvent::EMPTY_TIME());
            break;
        }
    }
}

/// @brief Verifies MonitoredDuration valid construction.
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
    EXPECT_EQ(mond->getEndEventLabel(), "process_completed");
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
    EXPECT_EQ(mond->getEndEventLabel(), "process_started");
    EXPECT_EQ(mond->getSubnetId(), 77);
    EXPECT_EQ("SOLICIT-ADVERTISE.mt_queued-process_started.77", mond->getLabel());
    EXPECT_EQ(mond->getIntervalDuration(), interval_duration);
    EXPECT_FALSE(mond->getCurrentInterval());
    EXPECT_FALSE(mond->getPreviousInterval());
}

/// @brief Verifies MonitoredDuration invalid construction.
TEST(MonitoredDuration, invalidConstructors) {
    MonitoredDurationPtr mond;

    // Make sure we catch an invalid message pairing.
    Duration interval_duration = seconds(60);
    ASSERT_THROW_MSG(mond.reset(new MonitoredDuration(AF_INET, DHCPDISCOVER, DHCPDISCOVER,
                                "process_started", "process_completed",
                                SUBNET_ID_GLOBAL, interval_duration)),
                     BadValue,
                     "Response type: DHCPDISCOVER not valid for query type: DHCPDISCOVER");

    // Interval duration cannot be than zero.
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

    // Interval duration cannot be than zero.
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

    // Iterate over a 60ms period, adding a 10ms sample to a duration
    // on each pass.  Sleep for 10ms in between iterations.
    DurationDataIntervalPtr original_interval;
    DurationDataIntervalPtr current_interval;
    DurationDataIntervalPtr previous_interval;
    auto ten_ms = milliseconds(10);
    bool should_report;
    for (int i = 0; i < 6; ++i) {
        ASSERT_NO_THROW(should_report = mond->addSample(ten_ms));
        current_interval = mond->getCurrentInterval();
        ASSERT_TRUE(current_interval);
        switch(i) {
        case 0:
            // First pass, we should only have a current interval,
            // nothing to report, one occurrence and a total duration of 10ms.
            original_interval = current_interval;
            EXPECT_FALSE(mond->getPreviousInterval());
            EXPECT_FALSE(should_report);
            EXPECT_EQ(current_interval->getOccurrences(), 1);
            EXPECT_EQ(current_interval->getTotalDuration(), ten_ms);
            break;
        default:
            // On passes that occur during the duration interval, we should
            // still only have a current interval and nothing to report.
            // Current interval occurrences and total duration should be increasing.
            EXPECT_EQ(current_interval, original_interval);
            EXPECT_FALSE(mond->getPreviousInterval());
            EXPECT_FALSE(should_report);
            EXPECT_EQ(current_interval->getOccurrences(), (i + 1));
            EXPECT_EQ(current_interval->getTotalDuration(), (ten_ms * (i + 1)));
            break;
        case 5:
            // On the last pass we should have crossed the interval boundary.
            // Previous interval should be equal to the original interval and
            // should_report should be true.  The new current interval should
            // have 1 occurrence and a total of 10ms.
            previous_interval = mond->getPreviousInterval();
            EXPECT_TRUE(previous_interval);
            EXPECT_EQ(previous_interval, original_interval);
            EXPECT_TRUE(should_report);
            EXPECT_EQ(current_interval->getOccurrences(), 1);
            EXPECT_EQ(current_interval->getTotalDuration(), ten_ms);
            break;
        }

        // Sleep for 10ms.
        usleep(10000);
    }

    // Verify that clear wipes the intervals.
    ASSERT_NO_THROW_LOG(mond->clear());
    EXPECT_FALSE(mond->getCurrentInterval());
    EXPECT_FALSE(mond->getPreviousInterval());
}

} // end of anonymous namespace
