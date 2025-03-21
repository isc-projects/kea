// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PingCheckConfig class.

#include <config.h>
#include <ping_check_config.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <list>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::ping_check;

namespace {

// Verifies PingCheckConfig constructors and accessors.
TEST(PingCheckConfigTest, basics) {
    PingCheckConfig config;

    // Verify initial values.
    EXPECT_TRUE(config.getEnablePingCheck());
    EXPECT_EQ(1, config.getMinPingRequests());
    EXPECT_EQ(100, config.getReplyTimeout());
    EXPECT_EQ(60, config.getPingClttSecs());
    EXPECT_EQ(0, config.getPingChannelThreads());

    // Verify accessors.
    EXPECT_NO_THROW_LOG(config.setEnablePingCheck(false));
    EXPECT_FALSE(config.getEnablePingCheck());

    EXPECT_NO_THROW_LOG(config.setMinPingRequests(4));
    EXPECT_EQ(4, config.getMinPingRequests());

    EXPECT_NO_THROW_LOG(config.setReplyTimeout(250));
    EXPECT_EQ(250, config.getReplyTimeout());

    EXPECT_NO_THROW_LOG(config.setPingClttSecs(120));
    EXPECT_EQ(120, config.getPingClttSecs());

    EXPECT_NO_THROW_LOG(config.setPingChannelThreads(6));
    EXPECT_EQ(6, config.getPingChannelThreads());

    // Verify copy construction.
    PingCheckConfig config2(config);
    EXPECT_FALSE(config2.getEnablePingCheck());
    EXPECT_EQ(4, config2.getMinPingRequests());
    EXPECT_EQ(250, config2.getReplyTimeout());
    EXPECT_EQ(120, config2.getPingClttSecs());
    EXPECT_EQ(6, config2.getPingChannelThreads());
}

// Exercises PingCheckConfig parameter parsing with valid configuration
// permutations.
TEST(PingCheckConfigTest, parseValidScenarios) {
    // Describes a test scenario.
    struct Scenario {
        int line_;                          // Scenario line number
        std::string json_;                  // JSON configuration to parse
        bool exp_enable_ping_check_;        // Expected value for enable-ping-check
        uint32_t exp_min_ping_requests_;    // Expected value for min-ping-requests
        uint32_t exp_reply_timeout_;        // Expected value for reply-timeout
        uint32_t exp_ping_cltt_secs_;       // Expected value for ping-cltt-secs
        size_t exp_num_threads_;            // Expected value for ping-channel-threads
    };

    // List of test scenarios to run.
    list<Scenario> scenarios = {
        {
            // Empty map
            __LINE__,
            R"({ })",
            true, 1, 100, 60, 0
        },
        {
            // Only enable-ping-check",
            __LINE__,
            R"({ "enable-ping-check" : false })",
            false, 1, 100, 60, 0
        },
        {
            // Only min-ping-requests",
            __LINE__,
            R"({ "min-ping-requests" : 3 })",
            true, 3, 100, 60, 0
        },
        {
            // Only reply-timeout",
            __LINE__,
            R"({ "reply-timeout" : 250 })",
            true, 1, 250, 60, 0
        },
        {
            // Only ping-cltt-secs",
            __LINE__,
            R"({ "ping-cltt-secs" : 77 })",
            true, 1, 100, 77, 0
        },
        {
            // Only ping-channel-threads",
            __LINE__,
            R"({ "ping-channel-threads" : 5 })",
            true, 1, 100, 60, 5
        },
        {
            // All parameters",
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : 2,
                "reply-timeout" : 375,
                "ping-cltt-secs" : 120,
                "ping-channel-threads" : 6
            })",
            false, 2, 375, 120, 6
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
        PingCheckConfig config;
        ASSERT_NO_THROW_LOG(config.parse(json_elements));

        // Verify expected values.
        EXPECT_EQ(scenario.exp_enable_ping_check_, config.getEnablePingCheck());
        EXPECT_EQ(scenario.exp_min_ping_requests_, config.getMinPingRequests());
        EXPECT_EQ(scenario.exp_reply_timeout_, config.getReplyTimeout());
        EXPECT_EQ(scenario.exp_ping_cltt_secs_, config.getPingClttSecs());
        EXPECT_EQ(scenario.exp_num_threads_, config.getPingChannelThreads());
    }
}

// Exercises PingCheckConfig parameter parsing with invalid configuration
// permutations.
TEST(PingCheckConfigTest, parseInvalidScenarios) {
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
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : 3,
                "reply-timeout" : 250,
                "ping-cltt-secs" : 90,
                "ping-channel-threads" : 4,
                "bogus" : false
            })",
            "spurious 'bogus' parameter"
        },
        {
            __LINE__,
            R"(
            {
                "enable-ping-check" : "not bool",
                "min-ping-requests" : 3,
                "reply-timeout" : 250,
                "ping-cltt-secs" : 90,
                "ping-channel-threads" : 4
            })",
            "'enable-ping-check' parameter is not a boolean"
        },
        {
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : 0,
                "reply-timeout" : 250,
                "ping-cltt-secs" : 90,
                "ping-channel-threads" : 4
            })",
            "invalid min-ping-requests: '0', must be greater than 0"
        },
        {
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : -2,
                "reply-timeout" : 250,
                "ping-cltt-secs" : 90,
                "ping-channel-threads" : 4
            })",
            "invalid min-ping-requests: '-2', must be greater than 0"
        },
        {
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : 1,
                "reply-timeout" : 0,
                "ping-cltt-secs" : 90,
                "ping-channel-threads" : 4
            })",
            "invalid reply-timeout: '0', must be greater than 0"
        },
        {
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : 1,
                "reply-timeout" : -77,
                "ping-cltt-secs" : 90,
                "ping-channel-threads" : 4
            })",
            "invalid reply-timeout: '-77', must be greater than 0"
        },
        {
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : 1,
                "reply-timeout" : 250,
                "ping-cltt-secs" : -3,
                "ping-channel-threads" : 4
            })",
            "invalid ping-cltt-secs: '-3', cannot be less than 0"
        },
        {
            __LINE__,
            R"(
            {
                "enable-ping-check" : false,
                "min-ping-requests" : 1,
                "reply-timeout" : 250,
                "ping-cltt-secs" : 90,
                "ping-channel-threads" : -1
            })",
            "invalid ping-channel-threads: '-1', cannot be less than 0"
        }
    };

    // Iterate over the scenarios.
    PingCheckConfig default_config;
    for (auto const& scenario : scenarios) {
        stringstream oss;
        oss << "scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());

        // Convert JSON text to a map of parameters.
        ConstElementPtr json_elements;
        ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(scenario.json_));

        // Parsing parameters should throw.
        PingCheckConfig config;
        ASSERT_THROW_MSG(config.parse(json_elements), dhcp::DhcpConfigError,
                         scenario.exp_message_);

        // Original values should be intact.
        EXPECT_EQ(default_config.getEnablePingCheck(), config.getEnablePingCheck());
        EXPECT_EQ(default_config.getMinPingRequests(), config.getMinPingRequests());
        EXPECT_EQ(default_config.getReplyTimeout(), config.getReplyTimeout());
        EXPECT_EQ(default_config.getPingClttSecs(), config.getPingClttSecs());
        EXPECT_EQ(default_config.getPingChannelThreads(), config.getPingChannelThreads());
    }
}

} // end of anonymous namespace
