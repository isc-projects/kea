// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PerfmonMgr class.
#include <config.h>
#include <perfmon_mgr.h>
#include <dhcp/dhcp6.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::perfmon;
using namespace isc::test;
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

/// @brief Test fixture for testing PerfMonMgr
class PerfMonMgrTest : public ::testing::Test {
public:
    /// @brief Constructor.
    explicit PerfMonMgrTest(uint16_t family) : family_(family) {
    }

    /// @brief Destructor.
    virtual ~PerfMonMgrTest() = default;

    /// @brief Verifies PerfMonConfig constructors and accessors.
    void testBasics() {
        PerfMonMgrPtr mgr;

        // Verify that an invalid family is caught.
        ASSERT_THROW_MSG(mgr.reset(new PerfMonMgr(777)), BadValue,
                         "PerfmonConfig: family must be AF_INET or AF_INET6");

        // Verify initial values.
        ASSERT_NO_THROW_LOG(mgr.reset(new PerfMonMgr(family_)));
        ASSERT_TRUE(mgr);
        EXPECT_FALSE(mgr->getEnableMonitoring());
        EXPECT_EQ(mgr->getIntervalDuration(), seconds(60));
        EXPECT_TRUE(mgr->getStatsMgrReporting());
        EXPECT_EQ(mgr->getAlarmReportInterval(), seconds(300));

        // Alarm store should exist but be empty.
        EXPECT_TRUE(mgr->getAlarmStore());
        EXPECT_EQ(mgr->getAlarmStore()->getFamily(), family_);
        AlarmCollectionPtr alarms = mgr->getAlarmStore()->getAll();
        ASSERT_EQ(alarms->size(), 0);

        // Duration store should exist but be empty.
        EXPECT_TRUE(mgr->getDurationStore());
        EXPECT_EQ(mgr->getDurationStore()->getFamily(), family_);
        MonitoredDurationCollectionPtr durations = mgr->getDurationStore()->getAll();
        ASSERT_EQ(durations->size(), 0);
    }

    /// @brief Exercises PerfMonConfig parameter parsing with valid configuration
    /// permutations.
    /// @todo add alarms
    void testValidConfig() {
        std::string valid_config =
            R"({
                    "enable-monitoring": false,
                    "interval-width-secs": 5,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 600,
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

        // Convert JSON texts to Element map.
        ConstElementPtr json_elements;
        ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(valid_config));

        PerfMonMgrPtr mgr(new PerfMonMgr(family_));
        ASSERT_NO_THROW_LOG(mgr->configure(json_elements));

        EXPECT_FALSE(mgr->getEnableMonitoring());
        EXPECT_EQ(mgr->getIntervalDuration(), seconds(5));
        EXPECT_FALSE(mgr->getStatsMgrReporting());
        EXPECT_EQ(mgr->getAlarmReportInterval(), seconds(600));

        // AlarmStore should have one alarm.
        EXPECT_TRUE(mgr->getAlarmStore());
        EXPECT_EQ(mgr->getAlarmStore()->getFamily(), family_);
        AlarmCollectionPtr alarms = mgr->getAlarmStore()->getAll();
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
        EXPECT_TRUE(mgr->getDurationStore());
        EXPECT_EQ(mgr->getDurationStore()->getFamily(), family_);
        MonitoredDurationCollectionPtr durations = mgr->getDurationStore()->getAll();
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

        // Convert JSON texts to Element map.
        ConstElementPtr json_elements;
        ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(invalid_config));

        PerfMonMgrPtr mgr(new PerfMonMgr(family_));
        ASSERT_THROW_MSG(mgr->configure(json_elements), DhcpConfigError,
                         "PerfMonMgr::configure failed - "
                         "'alarms' parameter is not a list");

        EXPECT_FALSE(mgr->getEnableMonitoring());
        EXPECT_EQ(mgr->getIntervalDuration(), seconds(60));
        EXPECT_TRUE(mgr->getStatsMgrReporting());
        EXPECT_EQ(mgr->getAlarmReportInterval(), seconds(300));

        // Alarm store should exist but be empty.
        EXPECT_TRUE(mgr->getAlarmStore());
        EXPECT_EQ(mgr->getAlarmStore()->getFamily(), family_);
        AlarmCollectionPtr alarms = mgr->getAlarmStore()->getAll();
        ASSERT_EQ(alarms->size(), 0);

        // Duration store should exist but be empty.
        EXPECT_TRUE(mgr->getDurationStore());
        EXPECT_EQ(mgr->getDurationStore()->getFamily(), family_);
        MonitoredDurationCollectionPtr durations = mgr->getDurationStore()->getAll();
        ASSERT_EQ(durations->size(), 0);
    }

    /// @brief Protocol family AF_INET or AF_INET6
    uint16_t family_;
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

} // end of anonymous namespace
