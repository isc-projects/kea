// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PerfMonConfig class.

#include <config.h>
#include <perfmon_config.h>
#include <dhcp/dhcp6.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <list>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::perfmon;

namespace {

/// @brief Test fixture for testing PerfMonConfig parsing of the
/// hook library's 'parameters' element.
class PerfMonConfigTest : public ::testing::Test {
public:
    /// @brief Constructor.
    explicit PerfMonConfigTest(uint16_t family) : family_(family) {
    }

    /// @brief Destructor.
    virtual ~PerfMonConfigTest() = default;

    /// @brief Verifies PerfMonConfig constructors and accessors.
    void testBasics() {
        PerfMonConfigPtr config;

        // Verify that an invalid family is caught.
        ASSERT_THROW_MSG(config.reset(new PerfMonConfig(777)), BadValue,
                         "PerfmonConfig: family must be AF_INET or AF_INET6");

        // Verify initial values.
        ASSERT_NO_THROW_LOG(config.reset(new PerfMonConfig(family_)));
        ASSERT_TRUE(config);
        EXPECT_FALSE(config->getEnableMonitoring());
        EXPECT_EQ(config->getIntervalWidthSecs(), 60);
        EXPECT_TRUE(config->getStatsMgrReporting());
        EXPECT_EQ(config->getAlarmReportSecs(), 300);
        EXPECT_TRUE(config->getAlarmStore());

        // Verify accessors.
        EXPECT_NO_THROW_LOG(config->setEnableMonitoring(true));
        EXPECT_TRUE(config->getEnableMonitoring());

        EXPECT_NO_THROW_LOG(config->setIntervalWidthSecs(4));
        EXPECT_EQ(config->getIntervalWidthSecs(), 4);

        EXPECT_NO_THROW_LOG(config->setStatsMgrReporting(false));
        EXPECT_FALSE(config->getStatsMgrReporting());

        EXPECT_NO_THROW_LOG(config->setAlarmReportSecs(120));
        EXPECT_EQ(config->getAlarmReportSecs(), 120);

        // Verify shallow copy construction.
        PerfMonConfigPtr config2(new PerfMonConfig(*config));
        EXPECT_TRUE(config2->getEnableMonitoring());
        EXPECT_EQ(config2->getIntervalWidthSecs(), 4);
        EXPECT_FALSE(config2->getStatsMgrReporting());
        EXPECT_EQ(config2->getAlarmReportSecs(), 120);
        EXPECT_EQ(config2->getAlarmStore(), config->getAlarmStore());
    }

    /// @brief Exercises PerfMonConfig parameter parsing with valid configuration
    /// permutations.
    /// @todo add alarms
    void testValidScenarios() {
        // Describes a test scenario.
        struct Scenario {
            int line_;                          // Scenario line number
            std::string json_;                  // JSON configuration to parse
            bool exp_enable_monitoring_;        // Expected value for enable-monitoring
            uint32_t exp_interval_width_secs_;  // Expected value for interval-width-secs
            bool exp_stats_mgr_reporting_;      // Expected value for stats-mgr-reporting
            uint32_t exp_alarm_report_secs_;    // Expected value for alarm-report-secs
        };

        // List of test scenarios to run.
        list<Scenario> scenarios = {
            {
                // Empty map
                __LINE__,
                R"({ })",
                false, 60, true, 300
            },
            {
                // Only enable-monitoring",
                __LINE__,
                R"({ "enable-monitoring": true })",
                true, 60, true, 300
            },
            {
                // Only interval-width-secs",
                __LINE__,
                R"({ "interval-width-secs": 3 })",
                false, 3, true, 300
            },
            {
                // Only stats-mgr-reporting",
                __LINE__,
                R"({ "stats-mgr-reporting": false })",
                false, 60, false, 300
            },
            {
                // Only alarm-report-secs",
                __LINE__,
                R"({ "alarm-report-secs": 77 })",
                false, 60, true, 77
            },
            {
                // All parameters",
                __LINE__,
                R"(
                {
                    "enable-monitoring": true,
                    "interval-width-secs": 2,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 120
                })",
                true, 2, false, 120
            },
        };

        // Iterate over the scenarios.
        for (auto const& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());

            // Convert JSON texts to Element map.
            ConstElementPtr json_elements;
            ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(scenario.json_));

            // Parsing elements should succeed.
            PerfMonConfig config(family_);
            ASSERT_NO_THROW_LOG(config.parse(json_elements));

            // Verify expected values.
            EXPECT_EQ(config.getEnableMonitoring(), scenario.exp_enable_monitoring_);
            EXPECT_EQ(config.getIntervalWidthSecs(), scenario.exp_interval_width_secs_);
            EXPECT_EQ(config.getStatsMgrReporting(), scenario.exp_stats_mgr_reporting_);
            EXPECT_EQ(config.getAlarmReportSecs(), scenario.exp_alarm_report_secs_);
        }
    }

    /// @brief Exercises PerfMonConfig parameter parsing with invalid configuration
    /// permutations.  Duplicate alarms are tested elsewhere.
    void testInvalidScenarios() {
        // Describes a test scenario.
        struct Scenario {
            int line_;              // Scenario line number
            string json_;           // JSON configuration to parse
            string exp_message_;    // Expected exception message
        };

        // List of test scenarios to run.  Most scenario supply
        // all valid parameters except one in error.  This allows
        // us to verify that no values are changed if any are in error.
        list<Scenario> scenarios = {
            {
                // Unknown parameter
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 3,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90,
                    "bogus": false
                })",
                "spurious 'bogus' parameter"
            },
            {
                // Invalid type for enable-monitoring
                __LINE__,
                R"(
                {
                    "enable-monitoring": "not bool",
                    "interval-width-secs": 3,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90
                })",
                "'enable-monitoring' parameter is not a boolean"
            },
            {
                // Invalid type for interval-width-secs
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": "bogus",
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90
                })",
                "'interval-width-secs' parameter is not an integer"
            },
            {
                // Value of interval-width-secs is zero
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 0,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90
                })",
                "invalid interval-width-secs: '0', must be greater than 0"
            },
            {
                // Value of interval-width-secs less than zero
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": -2,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90
                })",
                "invalid interval-width-secs: '-2', must be greater than 0"
            },
            {
                // Non-boolean type for stats-mgr-reporting
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 1,
                    "stats-mgr-reporting": "not bool",
                    "alarm-report-secs": 90
                })",
                "'stats-mgr-reporting' parameter is not a boolean"
            },
            {
                // Invalid type for alarm-report-secs
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 5,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": "bogus"
                })",
                "'alarm-report-secs' parameter is not an integer"
            },
            {
                // Value of alarm-report-secs is zero
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 1,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": -3
                })",
                "invalid alarm-report-secs: '-3', cannot be less than 0"
            },
            {
                // Value of alarm-report-secs less than zero
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 1,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": -3
                })",
                "invalid alarm-report-secs: '-3', cannot be less than 0"
            },
            {
                // Value for alarms is not a list.
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 60,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90,
                    "alarms": {}
                })",
                "'alarms' parameter is not a list"
            },
            {
                // Alarms list contains an invalid entry
                __LINE__,
                R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 60,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90,
                    "alarms": [{ "bogus": "alarm" }]
                })",
                "cannot add Alarm to store: spurious 'bogus' parameter"
            }
        };

        // Iterate over the scenarios.
        PerfMonConfig default_config(family_);
        for (auto const& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());

            // Convert JSON text to a map of parameters.
            ConstElementPtr json_elements;
            ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(scenario.json_));

            // Parsing parameters should throw.
            PerfMonConfig config(family_);
            ASSERT_THROW_MSG(config.parse(json_elements), DhcpConfigError,
                             scenario.exp_message_);

            // Original values should be intact.
            EXPECT_EQ(default_config.getEnableMonitoring(), config.getEnableMonitoring());
            EXPECT_EQ(default_config.getIntervalWidthSecs(), config.getIntervalWidthSecs());
            EXPECT_EQ(default_config.getStatsMgrReporting(), config.getStatsMgrReporting());
            EXPECT_EQ(default_config.getAlarmReportSecs(), config.getAlarmReportSecs());
        }
    }

    /// @brief Creates a valid configuration with a list of alarms.
    ///
    /// @parameter keys list of DurationKeyPtrs for alarms that should appear
    /// in the list.
    ///
    /// @return JSON text for the configuration.
    std::string makeConfigWithAlarms(std::vector<DurationKeyPtr> keys) {
        // Create valid configuration test which includes an arbitrary number of
        // family-specific alarms from a set of DurationKeys.
        stringstream joss;
        joss << R"(
                {
                    "enable-monitoring": false,
                    "interval-width-secs": 60,
                    "stats-mgr-reporting": false,
                    "alarm-report-secs": 90,
                    "alarms": [
                )";

        std::string comma = "";
        for (auto const& key : keys) {
            joss << comma << "\t{";
            joss << R"("duration-key": )";
            auto key_elems = DurationKeyParser::toElement(key);
            key_elems->toJSON(joss);
            joss << R"(,
                    "high-water-ms": 500,
                    "low-water-ms": 25
                    }
                )";

            comma = ",";
        }

        joss << "]}";
        return (joss.str());
    }

    /// @brief Verifies a valid configuration that includes a list of Alarms.
    void testValidAlarmsList() {
        // Create valid configuration test which includes an arbitrary number of
        // family-specific alarms from a pre-defined set of unique DurationKeys.
        std::string json_text = makeConfigWithAlarms(keys_);

        // Convert JSON text to a map of parameters.
        ConstElementPtr json_elements;
        ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(json_text));

        // Parsing parameters should throw.
        PerfMonConfig config(family_);
        ASSERT_NO_THROW_LOG(config.parse(json_elements));

        // Get all should retrieve the alarms in ascending order.
        AlarmCollectionPtr alarms = config.getAlarmStore()->getAll();
        ASSERT_EQ(alarms->size(), keys_.size());

        int idx = 0;
        for (auto const& d : *alarms) {
            EXPECT_EQ(*d, *keys_[idx]) << "failed on pass: " << idx;
            ++idx;
        }
    }

    /// @brief Verifies a valid configuration with a list duplicate Alarms.
    void testDuplicateAlarms() {
        std::vector<DurationKeyPtr> duplicate_keys;
        duplicate_keys.push_back(keys_[0]);
        duplicate_keys.push_back(keys_[0]);

        // Create valid configuration test which includes an arbitrary number of
        // family-specific alarms from a pre-defined set of unique DurationKeys.
        std::string json_text = makeConfigWithAlarms(duplicate_keys);

        // Convert JSON text to a map of parameters.
        ConstElementPtr json_elements;
        ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(json_text));

        // Parsing parameters should throw.
        PerfMonConfig config(family_);
        if (family_ == AF_INET) {
            ASSERT_THROW_MSG(config.parse(json_elements), DhcpConfigError,
                             "cannot add Alarm to store: AlarmStore::addAlarm:"
                             " alarm already exists for:"
                             " DHCPDISCOVER-DHCPOFFER.socket_received-buffer_read.0");
        } else {
            ASSERT_THROW_MSG(config.parse(json_elements), DhcpConfigError,
                             "cannot add Alarm to store: AlarmStore::addAlarm:"
                             " alarm already exists for:"
                             " SOLICIT-REPLY.socket_received-buffer_read.0");
        }
    }

    /// @brief Protocol family AF_INET or AF_INET6.
    uint16_t family_;

    /// @brief Collection of valid family-specific keys.
    std::vector<DurationKeyPtr> keys_;
};

/// @brief Test fixture for testing PerfMonConfig for DHCPV4.
class PerfMonConfigTest4: public PerfMonConfigTest {
public:
    /// @brief Constructor.
    explicit PerfMonConfigTest4() : PerfMonConfigTest(AF_INET) {
        for (int subnet = 0; subnet < 3; ++subnet) {
            DurationKeyPtr key(new DurationKey(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                               "socket_received", "buffer_read", subnet));
            keys_.push_back(key);
        }
    }

    /// @brief Destructor.
    virtual ~PerfMonConfigTest4() = default;
};

/// @brief Test fixture for testing PerfMonConfig for DHCPV6.
class PerfMonConfigTest6: public PerfMonConfigTest {
public:
    /// @brief Constructor.
    explicit PerfMonConfigTest6() : PerfMonConfigTest(AF_INET6) {
        for (int subnet = 0; subnet < 3; ++subnet) {
            DurationKeyPtr key(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_REPLY,
                                               "socket_received", "buffer_read", subnet));
            keys_.push_back(key);
        }
    }

    /// @brief Destructor.
    virtual ~PerfMonConfigTest6() = default;
};

TEST_F(PerfMonConfigTest4, basics) {
    testBasics();
}

TEST_F(PerfMonConfigTest6, basics) {
    testBasics();
}

TEST_F(PerfMonConfigTest4, validScenarios) {
    testValidScenarios();
}

TEST_F(PerfMonConfigTest6, validScenarios) {
    testValidScenarios();
}

TEST_F(PerfMonConfigTest4, invalidScenarios) {
    testInvalidScenarios();
}

TEST_F(PerfMonConfigTest6, invalidScenarios) {
    testInvalidScenarios();
}

TEST_F(PerfMonConfigTest4, validAlarmsList) {
    testValidAlarmsList();
}

TEST_F(PerfMonConfigTest6, validAlarmsList) {
    testValidAlarmsList();
}

TEST_F(PerfMonConfigTest4, duplicateAlarms) {
    testDuplicateAlarms();
}

TEST_F(PerfMonConfigTest6, duplicateAlarms) {
    testDuplicateAlarms();
}

} // end of anonymous namespace
