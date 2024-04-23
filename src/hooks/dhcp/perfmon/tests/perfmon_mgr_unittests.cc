// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PerfmonMgr class.
#include <config.h>
#include <perfmon_mgr.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/subnet.h>
#include <stats/stats_mgr.h>
#include <testutils/log_utils.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::perfmon;
using namespace isc::stats;
using namespace isc::test;
using namespace isc::dhcp::test;
using namespace boost::posix_time;

namespace {

// Verifies MonitoredDurationStore valid construction.
TEST(PerfMonMgr, constructor) {
    PerfMonMgrPtr mgr;

    EXPECT_NO_THROW_LOG(mgr.reset(new PerfMonMgr(AF_INET)));
    ASSERT_TRUE(mgr);
    EXPECT_EQ(mgr->getFamily(), AF_INET);

    EXPECT_NO_THROW_LOG(mgr.reset(new PerfMonMgr(AF_INET6)));
    ASSERT_TRUE(mgr);
    EXPECT_EQ(mgr->getFamily(), AF_INET6);
}

/// @brief Derivation of PerfMonMgr that uses milliseconds for intervals.
class TestablePerfMonMgr : public PerfMonMgr {
public:
    /// @brief Constructor.
    ///
    /// @param family Protocol family AF_INET or AF_INET6.
    explicit TestablePerfMonMgr(uint16_t family)
        : PerfMonMgr(family) {
    }

    /// @brief Destructor.
    virtual ~TestablePerfMonMgr() = default;

    /// @brief Override base class so we can use milliseconds.
    virtual void init() {
        // Set convenience values.
        interval_duration_ = milliseconds(interval_width_secs_);
        alarm_report_interval_ = milliseconds(alarm_report_secs_);

        // Re-create the duration store.
        duration_store_.reset(new MonitoredDurationStore(family_, interval_duration_));
    }
};

/// @brief Test fixture for testing PerfMonMgr
class PerfMonMgrTest : public LogContentTest {
public:
    /// @brief Constructor.
    explicit PerfMonMgrTest(uint16_t family) : family_(family) {
        StatsMgr::instance();
        StatsMgr::instance().removeAll();
        StatsMgr::instance().setMaxSampleCountAll(1);
        if (family_ == AF_INET) {
            subnet22_.reset(new Subnet4(IOAddress("192.0.22.0"), 8, 100, 200, 300, 22));
            subnet33_.reset(new Subnet4(IOAddress("192.0.33.0"), 8, 100, 200, 300, 33));
        } else {
            subnet22_.reset(new Subnet6(IOAddress("3001:22::"), 64, 100, 200, 300, 300, 22));
            subnet33_.reset(new Subnet6(IOAddress("3002:33::"), 64, 100, 200, 300, 300, 33));
        }
    }

    /// @brief Destructor.
    virtual ~PerfMonMgrTest() = default;

    /// @brief Re-creates and then configures the PerfMonMgr instance with a
    /// given configuration.
    ///
    /// @param config JSON configuration text
    void createMgr(const std::string& config) {
        mgr_.reset(new TestablePerfMonMgr(family_));
        ConstElementPtr json_elements;
        json_elements = Element::fromJSON(config);
        mgr_->configure(json_elements);
    }

    /// @brief Compares an Alarm to the version stored in the Alarm store.
    ///
    /// @param line_no source line of the invocation.
    /// @param before[in/out] pointer to the "before" alarm. It is updated
    /// to the stored Alarm prior to return.
    /// @param exp_state expected Alarm::STATE of the stored Alarm.
    /// @param should_report true if the stored alarm's high_water_last_report
    /// should be more recent than that of the before alarm.
    void beforeAndAfterAlarm(int line_no, AlarmPtr& before, Alarm::State exp_state,
                             bool should_report) {
        std::ostringstream oss;
        oss << "beforeAndAfterAlarm at line " << line_no << " failed";
        SCOPED_TRACE(oss.str());

        // Retrieve the Alarm from the store.
        AlarmPtr after;
        ASSERT_NO_THROW_LOG(after = mgr_->getAlarmStore()->getAlarm(before));
        ASSERT_TRUE(after);
        ASSERT_EQ(exp_state, after->getState());

        if (exp_state == before->getState()) {
            // State should not have changed.
            ASSERT_EQ(before->getStosTime(), after->getStosTime());
            switch(exp_state) {
            case Alarm::CLEAR:
                ASSERT_EQ(after->getLastHighWaterReport(), PktEvent::EMPTY_TIME());
                break;
            case Alarm::TRIGGERED:
                if (should_report) {
                    ASSERT_LT(before->getLastHighWaterReport(), after->getLastHighWaterReport());
                } else {
                    ASSERT_EQ(before->getLastHighWaterReport(), after->getLastHighWaterReport());
                }
                break;
            case Alarm::DISABLED:
                // No use case for this (yet).
                break;
            }
        } else {
            // State should have changed.
            ASSERT_LT(before->getStosTime(), after->getStosTime());
            switch(exp_state) {
            case Alarm::CLEAR:
                ASSERT_EQ(after->getLastHighWaterReport(), PktEvent::EMPTY_TIME());
                break;
            case Alarm::TRIGGERED:
                if (should_report) {
                    ASSERT_EQ(before->getLastHighWaterReport(), PktEvent::EMPTY_TIME());
                    ASSERT_LE(after->getStosTime(), after->getLastHighWaterReport());
                } else {
                    ASSERT_EQ(before->getLastHighWaterReport(), after->getLastHighWaterReport());
                }
                break;
            case Alarm::DISABLED:
                // No use case for this (yet).
                break;
            }
        }

        before = after;
    }

    /// @brief Check the content of a stored MonitoredDuration.
    ///
    /// @param line_no source line of the invocation.
    /// @param key DurationKey of the target duration.
    /// @param exp_current_total_ms expected value of the current interval's total_duration_.
    /// @param exp_previous true if the duration should have previous interval, defaults to false.
    /// @param exp_previous_total_ms expected value of the previous interval's total_duration_.
    void checkDuration(int line_no, DurationKeyPtr key, uint64_t exp_current_total_ms,
                       bool exp_previous = false, uint64_t exp_previous_total_ms = 0) {
        std::ostringstream oss;
        oss << "checkDuration at line " << line_no << " failed";
        SCOPED_TRACE(oss.str());
        MonitoredDurationPtr mond;
        ASSERT_NO_THROW(mond = mgr_->getDurationStore()->getDuration(key));
        ASSERT_TRUE(mond);
        if (!exp_previous) {
            ASSERT_FALSE(mond->getPreviousInterval());
        } else {
            ASSERT_TRUE(mond->getPreviousInterval());
            EXPECT_EQ(milliseconds(exp_previous_total_ms), mond->getPreviousInterval()->getTotalDuration());
        }

        ASSERT_TRUE(mond->getCurrentInterval());
        EXPECT_EQ(milliseconds(exp_current_total_ms), mond->getCurrentInterval()->getTotalDuration());
    }

    /// @brief Verifies PerfMonConfig constructors and accessors.
    void testBasics() {
        // Verify that an invalid family is caught.
        ASSERT_THROW_MSG(mgr_.reset(new PerfMonMgr(777)), BadValue,
                         "PerfmonConfig: family must be AF_INET or AF_INET6");

        // Verify initial values.
        ASSERT_NO_THROW_LOG(mgr_.reset(new PerfMonMgr(family_)));
        ASSERT_TRUE(mgr_);
        EXPECT_FALSE(mgr_->getEnableMonitoring());
        EXPECT_EQ(mgr_->getIntervalDuration(), seconds(60));
        EXPECT_TRUE(mgr_->getStatsMgrReporting());
        EXPECT_EQ(mgr_->getAlarmReportInterval(), seconds(300));

        // Alarm store should exist but be empty.
        EXPECT_TRUE(mgr_->getAlarmStore());
        EXPECT_EQ(mgr_->getAlarmStore()->getFamily(), family_);
        AlarmCollectionPtr alarms = mgr_->getAlarmStore()->getAll();
        ASSERT_EQ(alarms->size(), 0);

        // Duration store should exist but be empty.
        EXPECT_TRUE(mgr_->getDurationStore());
        EXPECT_EQ(mgr_->getDurationStore()->getFamily(), family_);
        MonitoredDurationCollectionPtr durations = mgr_->getDurationStore()->getAll();
        ASSERT_EQ(durations->size(), 0);
    }

    /// @brief Exercises PerfMonConfig parameter parsing with valid configuration
    /// permutations.
    /// @todo add alarms
    void testValidConfig() {
        std::string valid_config =
            R"({
                    "enable-monitoring": false,
                    "interval-width-secs": 5000,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 600000,
                    "alarms": [{
                            "duration-key": {
                                "query-type": "",
                                "response-type": "",
                                "start-event": "process-started",
                                "stop-event": "process-completed",
                                "subnet-id": 70
                                },
                            "enable-alarm": true,
                            "high-water-ms": 500,
                            "low-water-ms": 25
                        }]
                })";

        ASSERT_NO_THROW_LOG(createMgr(valid_config));

        EXPECT_FALSE(mgr_->getEnableMonitoring());
        EXPECT_EQ(mgr_->getIntervalDuration(), seconds(5));
        EXPECT_FALSE(mgr_->getStatsMgrReporting());
        EXPECT_EQ(mgr_->getAlarmReportInterval(), seconds(600));

        // AlarmStore should have one alarm.
        EXPECT_TRUE(mgr_->getAlarmStore());
        EXPECT_EQ(mgr_->getAlarmStore()->getFamily(), family_);
        AlarmCollectionPtr alarms = mgr_->getAlarmStore()->getAll();
        ASSERT_EQ(alarms->size(), 1);
        DurationKeyPtr key(new DurationKey(family_, 0, 0, "process-started",
                                           "process-completed", 70));
        AlarmPtr alarm = (*alarms)[0];
        ASSERT_TRUE(alarm);
        EXPECT_EQ(*alarm, *key) << "alarm:" << alarm->getLabel();
        EXPECT_EQ(alarm->getState(), Alarm::CLEAR);
        EXPECT_EQ(alarm->getHighWater(), milliseconds(500));
        EXPECT_EQ(alarm->getLowWater(), milliseconds(25));

        // Duration store should exist but be empty.
        EXPECT_TRUE(mgr_->getDurationStore());
        EXPECT_EQ(mgr_->getDurationStore()->getFamily(), family_);
        MonitoredDurationCollectionPtr durations = mgr_->getDurationStore()->getAll();
        ASSERT_EQ(durations->size(), 0);
    }

    /// @brief Verifies that PerfMonConfig handles a configuration error properly.
    void testInvalidConfig() {
        std::string invalid_config =
            R"({
                    "enable-monitoring": true,
                    "interval-width-secs": 5,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 600,
                    "alarms": "bogus"
                })";

        ASSERT_THROW_MSG(createMgr(invalid_config), DhcpConfigError,
                         "PerfMonMgr::configure failed - "
                         "'alarms' parameter is not a list");

        EXPECT_FALSE(mgr_->getEnableMonitoring());
        EXPECT_EQ(mgr_->getIntervalDuration(), seconds(60));
        EXPECT_TRUE(mgr_->getStatsMgrReporting());
        EXPECT_EQ(mgr_->getAlarmReportInterval(), seconds(300));

        // Alarm store should exist but be empty.
        EXPECT_TRUE(mgr_->getAlarmStore());
        EXPECT_EQ(mgr_->getAlarmStore()->getFamily(), family_);
        AlarmCollectionPtr alarms = mgr_->getAlarmStore()->getAll();
        ASSERT_EQ(alarms->size(), 0);

        // Duration store should exist but be empty.
        EXPECT_TRUE(mgr_->getDurationStore());
        EXPECT_EQ(mgr_->getDurationStore()->getFamily(), family_);
        MonitoredDurationCollectionPtr durations = mgr_->getDurationStore()->getAll();
        ASSERT_EQ(durations->size(), 0);
    }

    /// @brief Exercises PerfMonMgr::reportToStatsMgr().
    void testReportToStatsMgr() {
        // Minimal valid configuration.
        std::string valid_config =
            R"({
                    "enable-monitoring": true,
                    "interval-width-secs": 5,
                    "stats-mgr-reporting": true
                })";

        ASSERT_NO_THROW_LOG(createMgr(valid_config));

        MonitoredDurationPtr mond;
        ASSERT_THROW_MSG(mgr_->reportToStatsMgr(mond), BadValue,
                         "reportToStatsMgr - duration is empty!");

        ASSERT_NO_THROW_LOG(
            mond.reset(new MonitoredDuration(family_, 0, 0,
                                             "process-started", "process-completed",
                                             70, seconds(60))));

        ASSERT_THROW_MSG(mgr_->reportToStatsMgr(mond), BadValue,
                         "reportToStatsMgr - duration previous interval is empty!");

        mond->addSample(milliseconds(100));
        mond->addSample(milliseconds(250));
        mond->expireCurrentInterval();

        Duration average;
        ASSERT_NO_THROW_LOG(average = mgr_->reportToStatsMgr(mond));
        EXPECT_EQ(milliseconds(175), average);

        auto obs = StatsMgr::instance().getObservation(mond->getStatName("average-ms"));
        ASSERT_TRUE(obs);
        EXPECT_EQ(175, obs->getInteger().first);

        StatsMgr::instance().removeAll();
        mgr_->setStatsMgrReporting(false);

        ASSERT_NO_THROW_LOG(average = mgr_->reportToStatsMgr(mond));
        EXPECT_EQ(milliseconds(175), average);
        obs = StatsMgr::instance().getObservation(mond->getStatName("average-ms"));
        ASSERT_FALSE(obs);
    }

    /// @brief Exercises PerfMonMgr::addDurationSample().
    void testAddDurationSample() {
        // Minimal valid configuration.
        std::string valid_config =
            R"({
                    "enable-monitoring": true,
                    "interval-width-secs": 100,
                    "stats-mgr-reporting": true,
                    "alarm-report-secs": 200,
                    "alarms": [{
                            "duration-key": {
                                "query-type": "*",
                                "response-type": "*",
                                "start-event": "process-started",
                                "stop-event": "process-completed",
                                "subnet-id": 70
                                },
                            "enable-alarm": true,
                            "high-water-ms": 50,
                            "low-water-ms": 25
                        }]
                })";

        ASSERT_NO_THROW_LOG(createMgr(valid_config));

        // Make a duration key to match the alarm.
        DurationKeyPtr key;
        ASSERT_NO_THROW_LOG(
            key.reset(new DurationKey(family_, 0, 0, "process-started",
                                      "process-completed", 70)));

        // Verify the alarm exists but is CLEAR since the duration has not yet reported.
        AlarmPtr before_alarm;
        ASSERT_NO_THROW_LOG(before_alarm = mgr_->getAlarmStore()->getAlarm(key));
        ASSERT_TRUE(before_alarm);
        EXPECT_EQ(Alarm::CLEAR, before_alarm->getState());

        // 1. Add two samples to the duratson inside the current interval.
        // This should create the duration in the store.  Note both samples above
        // high-water-ms.
        ASSERT_NO_THROW_LOG(mgr_->addDurationSample(key, milliseconds(75)));
        ASSERT_NO_THROW_LOG(mgr_->addDurationSample(key, milliseconds(85)));

        // Duration should exist in the store with a current total of 160 ms.
        // It should not yet have a previous interval.
        checkDuration(__LINE__, key, 160, false);

        // Verify the alarm should still be CLEAR since we have not yet completed the interval.
        AlarmPtr after_alarm;
        beforeAndAfterAlarm(__LINE__, before_alarm, Alarm::CLEAR, false);

        // No stats should have been reported.
        EXPECT_EQ(0, StatsMgr::instance().count());

        // Sleep 100ms second to make sure the current interval duration elapses.
        usleep(100 * 1000);

        // 2. Add a new sample after the current interval duration elapses.
        // This should cause the duration to be reported and the alarm to trigger.
        ASSERT_NO_THROW_LOG(mgr_->addDurationSample(key, milliseconds(95)));

        // Duration should have a current total of 95 ms, and a previous total of 160.
        checkDuration(__LINE__, key, 95, true, 160);

        // Should have one stat reported with a average value of 80.
        EXPECT_EQ(1, StatsMgr::instance().count());
        auto obs = StatsMgr::instance().getObservation(key->getStatName("average-ms"));
        ASSERT_TRUE(obs);
        EXPECT_EQ(80, obs->getInteger().first);

        // The alarm should have triggered and reported.
        beforeAndAfterAlarm(__LINE__, before_alarm, Alarm::TRIGGERED, true);
        addString("reported average duration 00:00:00.080000 exceeds high-water-ms: 50");

        // Sleep 100ms second to make sure the current interval duration elapses.
        usleep(100 * 1000);

        // 3. Add another above high water sample.
        ASSERT_NO_THROW_LOG(mgr_->addDurationSample(key, milliseconds(100)));

        // Duration should have a current total of 100 ms, and a previous total of 95.
        checkDuration(__LINE__, key, 100, true, 95);

        // The Alarm should still be TRIGGERED since the newly completed interval is
        // above high water.  The alarm should not report because the reporting
        // interval has not elapsed.
        beforeAndAfterAlarm(__LINE__, before_alarm, Alarm::TRIGGERED, false);

        // Sleep 100ms second to make sure the current interval duration elapses.
        usleep(100 * 1000);

        // 4. Add a below low water duration. This should close the current interval.
        ASSERT_NO_THROW_LOG(mgr_->addDurationSample(key, milliseconds(10)));

        // Duration should have a current total of 10ms, and a previous total of 100.
        checkDuration(__LINE__, key, 10, true, 100);

        // The Alarm should still be TRIGGERED since the newly completed interval is
        // above high water.  The alarm should report again because the reporting
        // interval has elapsed.
        beforeAndAfterAlarm(__LINE__, before_alarm, Alarm::TRIGGERED, true);
        addString("reported average duration 00:00:00.100000 exceeds high-water-ms: 50");

        // Should have one stat reported with a value of 100.
        EXPECT_EQ(1, StatsMgr::instance().count());
        obs = StatsMgr::instance().getObservation(key->getStatName("average-ms"));
        ASSERT_TRUE(obs);
        EXPECT_EQ(100, obs->getInteger().first);

        // Sleep 100ms second to make sure the current interval duration elapses.
        usleep(100 * 1000);

        // 5. Add another below low water duration.  This should close the current interval.
        ASSERT_NO_THROW_LOG(mgr_->addDurationSample(key, milliseconds(15)));

        // Duration should have a current total of 15 ms, and a previous total of 10.
        checkDuration(__LINE__, key, 15, true, 10);

        // The Alarm should now be CLEAR since the newly completed interval is
        // below high water. The alarm should low-water report.
        beforeAndAfterAlarm(__LINE__, before_alarm, Alarm::CLEAR, false);
        addString("reported average duration 00:00:00.010000 is now below low-water-ms: 25");

        // Should have one stat reported with a value of 10.
        EXPECT_EQ(1, StatsMgr::instance().count());
        obs = StatsMgr::instance().getObservation(key->getStatName("average-ms"));
        ASSERT_TRUE(obs);
        EXPECT_EQ(10, obs->getInteger().first);

        // Lastly, verify the log entries.
        EXPECT_TRUE(checkFile());
    }

    /// @brief Exercises error handling in PerfMonMgr::procssPktEventStack().
    void testInvalidProcessPktEventStack() {
        // Minimal valid config.
        std::string valid_config =
            R"({ "enable-monitoring": true })";

        ASSERT_NO_THROW_LOG(createMgr(valid_config));
        PktPtr query;
        PktPtr response;
        // No query
        ASSERT_THROW_MSG(mgr_->processPktEventStack(query, response, SubnetPtr()), Unexpected,
                         "PerfMonMgr::processPktEventStack - query is empty!");

        // Invalid message pair
        query = makeFamilyQuery();
        response = makeFamilyResponse();

        std::ostringstream oss;
        oss << "Query type not supported by monitoring: "
            << (family_ == AF_INET ? Pkt4::getName(response->getType())
                                   : Pkt6::getName(response->getType()));

        ASSERT_THROW_MSG(mgr_->processPktEventStack(response, query, SubnetPtr()), BadValue,
                         oss.str());

        // Packet stack size less than 2.
        query->addPktEvent("just one");
        ASSERT_THROW_MSG(mgr_->processPktEventStack(query, response, SubnetPtr()), Unexpected,
                         "PerfMonMgr::processPtkEventStack - incomplete stack, size: 1");
    }

    /// @brief Exercises PerfMonMgr::procssPktEventStack().
    void testProcessPktEventStack() {
        // Minimal valid configuration.
        std::string valid_config =
            R"({ "enable-monitoring": false })";

        ASSERT_NO_THROW_LOG(createMgr(valid_config));

        // Create family-specific packets.
        PktPtr query = makeFamilyQuery();
        PktPtr response = makeFamilyResponse();

        // Populate the query's packet event stack with some events.
        auto event_time = PktEvent::now();
        query->addPktEvent("socket_received", event_time);
        event_time += milliseconds(5);

        query->addPktEvent("buffer_read", event_time);
        event_time += milliseconds(4);

        query->addPktEvent("process_started", event_time);
        event_time += milliseconds(3);

        query->addPktEvent("process_completed", event_time);

        // Now process the packets on two different subnets.
        // With monitoring disabled no duration data should be stored.
        ASSERT_NO_THROW_LOG(mgr_->processPktEventStack(query, response, SubnetPtr()));
        ASSERT_NO_THROW_LOG(mgr_->processPktEventStack(query, response, subnet22_));
        ASSERT_NO_THROW_LOG(mgr_->processPktEventStack(query, response, subnet33_));

        // Fetch all the durations in primary key order.
        MonitoredDurationCollectionPtr durations = mgr_->getDurationStore()->getAll();
        ASSERT_EQ(durations->size(), 0);

        // Enabled monitoring and process the queries again.
        mgr_->setEnableMonitoring(true);
        ASSERT_NO_THROW_LOG(mgr_->processPktEventStack(query, response, SubnetPtr()));
        ASSERT_NO_THROW_LOG(mgr_->processPktEventStack(query, response, subnet22_));
        ASSERT_NO_THROW_LOG(mgr_->processPktEventStack(query, response, subnet33_));

        // Fetch all the durations in primary key order.
        durations = mgr_->getDurationStore()->getAll();
        ASSERT_EQ(durations->size(), 12);

        // Contains the expected values for single duration.
        struct ExpectedDuration {
            std::string start_event_;
            std::string stop_event_;
            dhcp::SubnetID subnet_id_;
            uint64_t occurrences_;
            uint64_t total_duration_;
        };

        // Specifies the expected durations in the order they should be returned.
        std::list<ExpectedDuration> exp_data_rows {
            { "buffer_read", "process_started", 0,  3, 12 },
            { "buffer_read", "process_started", 22, 1, 4 },
            { "buffer_read", "process_started", 33, 1, 4 },

            { "composite", "total_response", 0,  3, 36 },
            { "composite", "total_response", 22, 1, 12 },
            { "composite", "total_response", 33, 1, 12 },

            { "process_started", "process_completed", 0,  3, 9 },
            { "process_started", "process_completed", 22, 1, 3 },
            { "process_started", "process_completed", 33, 1, 3 },

            { "socket_received", "buffer_read", 0,  3, 15 },
            { "socket_received", "buffer_read", 22, 1,  5 },
            { "socket_received", "buffer_read", 33, 1,  5 }
        };

        // Verify the returne collection is as expected.
        DurationKeyPtr exp_key;
        auto exp_row = exp_data_rows.begin();
        for (auto const& d : *durations) {
            EXPECT_EQ(query->getType(), d->getQueryType());
            EXPECT_EQ(response->getType(), d->getResponseType());
            EXPECT_EQ((*exp_row).start_event_, d->getStartEventLabel());
            EXPECT_EQ((*exp_row).stop_event_, d->getStopEventLabel());
            EXPECT_EQ((*exp_row).subnet_id_, d->getSubnetId());
            ASSERT_TRUE(d->getCurrentInterval());
            EXPECT_EQ((*exp_row).occurrences_, d->getCurrentInterval()->getOccurrences());
            EXPECT_EQ(milliseconds((*exp_row).total_duration_),
                      d->getCurrentInterval()->getTotalDuration());
            ++exp_row;
        }
    }

    /// @brief Make a valid family-specific query.
    ///
    /// @return if family is AF_INET return a pointer to a DHCPDISCOVER
    /// otherwise a pointer to a DHCPV6_SOLICIT.
    PktPtr makeFamilyQuery() {
        if (family_ == AF_INET) {
            return (PktPtr(new Pkt4(DHCPDISCOVER, 7788)));
        }

        return (PktPtr(new Pkt6(DHCPV6_SOLICIT, 7788)));
    }

    /// @brief Make a valid family-specific response.
    ///
    /// @return if family is AF_INET return a pointer to a DHCPOFFER
    /// otherwise a pointer to a DHCPV6_ADVERTISE.
    PktPtr makeFamilyResponse() {
        if (family_ == AF_INET) {
            return (PktPtr(new Pkt4(DHCPOFFER, 7788)));
        }

        return (PktPtr(new Pkt6(DHCPV6_ADVERTISE, 7788)));
    }

    /// @brief Protocol family AF_INET or AF_INET6
    uint16_t family_;

    /// @brief PerfMonMgr instance used in test functions.
    PerfMonMgrPtr mgr_;

    /// @brief Family specific subnets.
    SubnetPtr subnet22_;
    SubnetPtr subnet33_;
};

/// @brief Test fixture for testing PerfMonConfig for DHCPV4.
class PerfMonMgrTest4: public PerfMonMgrTest {
public:
    /// @brief Constructor.
    explicit PerfMonMgrTest4() : PerfMonMgrTest(AF_INET) {
    }

    /// @brief Destructor.
    virtual ~PerfMonMgrTest4() = default;
};

/// @brief Test fixture for testing PerfMonConfig for DHCPV6.
class PerfMonMgrTest6: public PerfMonMgrTest {
public:
    /// @brief Constructor.
    explicit PerfMonMgrTest6() : PerfMonMgrTest(AF_INET6) {
    }

    /// @brief Destructor.
    virtual ~PerfMonMgrTest6() = default;
};

TEST_F(PerfMonMgrTest4, basics) {
    testBasics();
}

TEST_F(PerfMonMgrTest6, basics) {
    testBasics();
}

TEST_F(PerfMonMgrTest4, validConfig) {
    testValidConfig();
}

TEST_F(PerfMonMgrTest6, validConfig) {
    testValidConfig();
}

TEST_F(PerfMonMgrTest4, invalidConfig) {
    testInvalidConfig();
}

TEST_F(PerfMonMgrTest6, invalidConfig) {
    testInvalidConfig();
}

TEST_F(PerfMonMgrTest4, reportToStatsMgr) {
    testReportToStatsMgr();
}

TEST_F(PerfMonMgrTest6, reportToStatsMgr) {
    testReportToStatsMgr();
}

TEST_F(PerfMonMgrTest4, addDurationSample) {
    testAddDurationSample();
}

TEST_F(PerfMonMgrTest6, addDurationSample) {
    testAddDurationSample();
}

TEST_F(PerfMonMgrTest4, invalidProcessPktEventStack) {
    testInvalidProcessPktEventStack();
}

TEST_F(PerfMonMgrTest6, invalidProcessPktEventStack) {
    testInvalidProcessPktEventStack();
}

TEST_F(PerfMonMgrTest4, processPktEventStack) {
    testProcessPktEventStack();
}

TEST_F(PerfMonMgrTest6, processPktEventStack) {
    testProcessPktEventStack();
}

} // end of anonymous namespace
