// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PerfmonConfig class.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <perfmon_config.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <list>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::perfmon;
using namespace boost::posix_time;

namespace {

// These tests excerise AlarmParser which, with the help of DurationKeyParser
// (tested rigorously elsewhere), parses a map of parameters as shown below:
//
// {
//      "duration-key": {
//          "query-type": "DHCPDISCOVER",
//          "response-type": "DHCPOFFER",
//          "start-event": "process-started",
//          "stop-event": "process-completed",
//          "subnet-id": 70
//       },
//       "enable-alarm": true,
//       "high-water-ms": 500,
//       "low-water-ms": 25,
// }

/// @brief Describes a valid test scenario.
struct ValidScenario {
    int line_;                      // Scenario line number
    std::string json_;              // JSON configuration to parse
    Alarm::State exp_state_;        // Expected value for Alarm::state
    uint64_t exp_high_water_ms_;    // Expected value for high-water-ms
    uint64_t exp_low_water_ms_;     // Expected value for low-water-ms
};

/// @brief Describes an invalid test scenario.
struct InvalidScenario {
    int line_;                      // Scenario line number
    std::string json_;              // JSON configuration to parse
    std::string exp_message_;       // Expected error text
};

/// @brief Base class test fixture for testing AlarmParser.
class AlarmParserTest : public ::testing::Test {
public:
    /// @brief Constructor.
    explicit AlarmParserTest(uint16_t family) : family_(family) {
    }

    /// @brief Destructor.
    virtual ~AlarmParserTest() = default;

    /// @brief Prepends json for a family-valid 'duration-key' to json text.
    ///
    /// @param scenario_json text to prepend with the duration-key.
    ///
    /// @return string containing the prepended text.
    virtual std::string makeValidKeyConfig(const std::string& scenario_json) = 0;

    /// @brief Runs a list of valid configurations through AlarmParser::parse().
    void testValidScenarios() {
        // List of test scenarios to run.
        const std::list<ValidScenario> scenarios = {
            {
                // All parameters
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 500,
                    "low-water-ms": 25
                )",
                Alarm::CLEAR, 500, 25
            },
            {
                // No enable-alarm, should default to CLEAR state.
                __LINE__,
                R"(
                    "high-water-ms": 500,
                    "low-water-ms": 25
                )",
                Alarm::CLEAR, 500, 25
            },
            {
                // State should be DISABLED when enable-alarm is false
                __LINE__,
                R"(
                    "enable-alarm": false,
                    "high-water-ms": 500,
                    "low-water-ms": 25
                )",
                Alarm::DISABLED, 500, 25
            }
        };

        // Iterate over the scenarios.
        for (auto const& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());

            // Construct valid key + scenario JSON
            auto json = makeValidKeyConfig(scenario.json_);

            // Convert JSON text to Element map.
            ConstElementPtr json_elements;
            ASSERT_NO_THROW(json_elements = Element::fromJSON(json))
                            << " json: " << json;

            // Parsing should succeed.
            AlarmPtr alarm;
            ASSERT_NO_THROW_LOG(alarm = AlarmParser::parse(json_elements, family_));

            // Verify expected values.
            ASSERT_TRUE(alarm);
            ASSERT_EQ(*alarm, *expected_key_);

            EXPECT_EQ(alarm->getState(), scenario.exp_state_);
            EXPECT_EQ(alarm->getHighWater(), milliseconds(scenario.exp_high_water_ms_));
            EXPECT_EQ(alarm->getLowWater(), milliseconds(scenario.exp_low_water_ms_));
        }
    }

    /// @brief Test scenarios that have valid duration-key elements but flawed
    /// Alarm scalar parameters.
    void testInvalidAlarmScenarios() {
        // List of test scenarios to run. These will be prepended with a valid,
        // family-specific duration-key element prior to parsing.
        list<InvalidScenario> scenarios = {
            {
                // Spurious parameter
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 500,
                    "low-water-ms": 25,
                    "bogus": true
                )",
                "spurious 'bogus' parameter"
            },
            {
                // Invalid type enable-alarm
                __LINE__,
                R"(
                    "enable-alarm": "bogus",
                    "high-water-ms": 500,
                    "low-water-ms": 25,
                    "bogus": true
                )",
                "'enable-alarm' parameter is not a boolean"
            },
            {
                // Missing high-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "low-water-ms": 25
                )",
                "'high-water-ms' parameter is required"
            },
            {
                // Invalid type for high-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": "bogus",
                    "low-water-ms": 25
                )",
                "'high-water-ms' parameter is not an integer"
            },
            {
                // Invalid zero value for high-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 0,
                    "low-water-ms": 25
                )",
                "high-water-ms: '0', must be greater than 0"
            },
            {
                // Invalid negative value for high-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": -1,
                    "low-water-ms": 25
                )",
                "high-water-ms: '-1', must be greater than 0"
            },
            {
                // Missing low-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 500
                )",
                "'low-water-ms' parameter is required"
            },
            {
                // Invalid type for low-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 500,
                    "low-water-ms": "bogus"
                )",
                "'low-water-ms' parameter is not an integer"
            },
            {
                // Invalid zero value for low-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 500,
                    "low-water-ms": 0
                )",
                "low-water-ms: '0', must be greater than 0"
            },
            {
                // Invalid negative value for low-water-ms
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 500,
                    "low-water-ms": -1
                )",
                "low-water-ms: '-1', must be greater than 0"
            },
            {
                // Invalid threshold combination
                __LINE__,
                R"(
                    "enable-alarm": true,
                    "high-water-ms": 25,
                    "low-water-ms": 500
                )",
                "'low-water-ms': 500, must be less than 'high-water-ms': 25"
            },
        };

        testInvalidScenarios(scenarios, true);
    }

    /// @brief Runs a list of invalid configurations through AlarmParser::parse().
    ///
    /// @param list of valid scenarios to run.
    /// @param add_key When true, scenario json will be prepended with valid, family-specific
    /// duration-key element prior to parsing.
    void testInvalidScenarios(std::list<InvalidScenario>& scenarios,
                              bool add_key = true) {
        // Iterate over the scenarios.
        for (auto const& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());

            // If add_key is true prepend the scenario with valid key json
            auto json = (add_key ? makeValidKeyConfig(scenario.json_) : scenario.json_);

            // Convert JSON texts to Element map.
            ConstElementPtr json_elements;
            ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(json));

            // Parsing elements should succeed.
            ASSERT_THROW_MSG(AlarmParser::parse(json_elements, family_), DhcpConfigError,
                             scenario.exp_message_);
        }
    }

    /// @brief Protocol family AF_INET or AF_INET6
    uint16_t family_;

    /// @brief Expected DurationKey in Alarm after valid parsing.
    DurationKeyPtr expected_key_;
};

/// @brief Test fixture for testing AlarmParser for DHCPV4.
class AlarmParserTest4: public AlarmParserTest {
public:
    /// @brief Constructor.
    explicit AlarmParserTest4() : AlarmParserTest(AF_INET) {
        expected_key_.reset(new DurationKey(family_, DHCPDISCOVER, DHCPOFFER,
                                            "start_here", "stop_there", 33));
    }

    /// @brief Destructor.
    virtual ~AlarmParserTest4() = default;

    /// @brief Prepends json for a valid, DHCP 'duration-key' to json text.
    ///
    /// @param scenario_json text to prepend with the duration-key.
    ///
    /// @return string containing the prepended text.
    virtual std::string makeValidKeyConfig(const std::string& scenario_json) {
        std::stringstream oss;
        oss << "{"
            <<
                R"( "duration-key": {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 33
                })"
            << ","
            << scenario_json << "}";

        return (oss.str());
    }
};

/// @brief Test fixture for testing AlarmParser for DHCPV6.
class AlarmParserTest6: public AlarmParserTest {
public:
    /// @brief Constructor.
    explicit AlarmParserTest6() : AlarmParserTest(AF_INET6) {
        expected_key_.reset(new DurationKey(family_, DHCPV6_REQUEST, DHCPV6_REPLY,
                                            "start_here", "stop_there", 33));
    }

    /// @brief Destructor.
    virtual ~AlarmParserTest6() = default;

    /// @brief Prepends json for a valid, DHCPV6 'duration-key' to json text.
    ///
    /// @param scenario_json text to prepend with the duration-key.
    ///
    /// @return string containing the prepended text.
    virtual std::string makeValidKeyConfig(const std::string& scenario_json) {
        std::stringstream oss;
        oss << "{"
            <<
                R"( "duration-key": {
                "query-type": "REQUEST",
                "response-type": "REPLY",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 33
                })"
            << ","
            << scenario_json << "}";

        return (oss.str());
    }
};

TEST_F(AlarmParserTest4, validScenarios) {
    testValidScenarios();
}

TEST_F(AlarmParserTest4, invalidAlarmScenarios) {
    testInvalidAlarmScenarios();
}

TEST_F(AlarmParserTest4, invalidDurationKey) {
    // We test just enough key errors to ensure they're caught.
    // List of test scenarios to run.
    list<InvalidScenario> scenarios = {
        {
            // Missing duration-key element
            __LINE__,
            R"({
                "enable-alarm": true,
                "high-water-ms": 500,
                "low-water-ms": 25
            })",
            "'duration-key' parameter is required"
        },
        {
            // Invalid type for duration-key.
            __LINE__,
            R"({
                "duration-key": "not-a-map",
                "enable-alarm": true,
                "high-water-ms": 500,
                "low-water-ms": 25
            })",
            "'duration-key' parameter is not a map"
        },
        {
            // Wrong messages type for v4.
            __LINE__,
            R"({
                "duration-key": {
                    "query-type": "REQUEST",
                    "response-type": "REPLY",
                    "start-event": "start-here",
                    "stop-event": "stop-here"
                },
                "enable-alarm": true,
                "high-water-ms": 500,
                "low-water-ms": 25
            })",
            "'query-type' parameter is invalid, 'REQUEST' is not a valid DHCP message type"
        },
    };

    testInvalidScenarios(scenarios, false);
}

TEST_F(AlarmParserTest6, validScenarios) {
    testValidScenarios();
}

TEST_F(AlarmParserTest6, invalidScenarios) {
    testInvalidAlarmScenarios();
}

TEST_F(AlarmParserTest6, invalidDurationKey) {
    // We test just enough key errors to ensure they're caught.
    // List of test scenarios to run.
    list<InvalidScenario> scenarios = {
        {
            // Missing duration-key element
            __LINE__,
            R"({
                "enable-alarm": true,
                "high-water-ms": 500,
                "low-water-ms": 25
            })",
            "'duration-key' parameter is required"
        },
        {
            // Invalid type for duration-key.
            __LINE__,
            R"({
                    "duration-key": "not-a-map",
                    "enable-alarm": true,
                    "high-water-ms": 500,
                    "low-water-ms": 25
            })",
            "'duration-key' parameter is not a map"
        },
        {
            // Wrong messages type for v6.
            __LINE__,
            R"({
                "duration-key": {
                    "query-type": "DHCPDISCOVER",
                    "response-type": "DHCPOFFER",
                    "start-event": "start-here",
                    "stop-event": "stop-here"
                },
                "enable-alarm": true,
                "high-water-ms": 500,
                "low-water-ms": 25
            })",
            "'query-type' parameter is invalid, 'DHCPDISCOVER' is not a valid DHCPV6 message type"
        },
    };

    testInvalidScenarios(scenarios, false);
}

} // end of anonymous namespace
