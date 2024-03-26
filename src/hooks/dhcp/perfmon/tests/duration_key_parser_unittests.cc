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

namespace {

// These tests excerise DurationKeyParser which parses a map of
// parameters as shown below:
//  "duration-key": {
//      "query-type": "DHCPDISCOVER",
//      "response-type": "DHCPOFFER",
//      "start-event": "process-started",
//      "stop-event": "process-completed",
//      "subnet-id": 70
// }

/// @brief Describes a valid test scenario.
struct ValidScenario {
    int line_;                      // Scenario line number
    std::string json_;              // JSON configuration to parse
    uint16_t exp_query_type_;       // Expected value for query-type
    uint16_t exp_response_type_;    // Expected value for response-type
    std::string exp_start_event_;   // Expected value for start-event
    std::string exp_stop_event_;    // Expected value for stop-event
    SubnetID exp_subnet_id_;        // Expected value for subnet-id
};

/// @brief Describes an invalid test scenario.
struct InvalidScenario {
    int line_;                      // Scenario line number
    std::string json_;              // JSON configuration to parse
    std::string exp_message_;       // Expected error text
};

/// @brief Test fixture for testing DurationKeyParser.
class DurationKeyParserTest : public ::testing::Test {
public:
    /// @brief Constructor.
    DurationKeyParserTest() = default;

    /// @brief Destructor.
    virtual ~DurationKeyParserTest() = default;

    /// @brief Runs a list of valid configurations through parsing.
    ///
    /// @param list of valid scenarios to run.
    /// @param family protocol family to use when parsing.
    void testValidScenarios(std::list<ValidScenario>& scenarios, uint16_t family) {
        // Iterate over the scenarios.
        for (auto const& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());

            // Convert JSON texts to Element map.
            ConstElementPtr json_elements;
            ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(scenario.json_));

            // Parsing elements should succeed.
            DurationKeyPtr key;
            ASSERT_NO_THROW_LOG(key = DurationKeyParser::parse(json_elements, family));

            // Verify expected values.
            ASSERT_TRUE(key);
            EXPECT_EQ(key->getQueryType(), scenario.exp_query_type_);
            EXPECT_EQ(key->getResponseType(), scenario.exp_response_type_);
            EXPECT_EQ(key->getStartEventLabel(), scenario.exp_start_event_);
            EXPECT_EQ(key->getStopEventLabel(), scenario.exp_stop_event_);
            EXPECT_EQ(key->getSubnetId(), scenario.exp_subnet_id_);
        }
    }

    /// @brief Runs a list of invalid configurations through parsing.
    ///
    /// @param list of valid scenarios to run.
    /// @param family protocol family to use when parsing.
    void testInvalidScenarios(std::list<InvalidScenario>& scenarios, uint16_t family) {
        // Iterate over the scenarios.
        for (auto const& scenario : scenarios) {
            stringstream oss;
            oss << "scenario at line: " << scenario.line_;
            SCOPED_TRACE(oss.str());

            // Convert JSON texts to Element map.
            ConstElementPtr json_elements;
            ASSERT_NO_THROW_LOG(json_elements = Element::fromJSON(scenario.json_));

            // Parsing elements should succeed.
            ASSERT_THROW_MSG(DurationKeyParser::parse(json_elements, family), DhcpConfigError,
                             scenario.exp_message_);
        }
    }
};

TEST_F(DurationKeyParserTest, validScenarios4) {
    // List of test scenarios to run.
    std::list<ValidScenario> scenarios = {
        {
            // All parameters,
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            DHCPDISCOVER, DHCPOFFER, "start_here", "stop_there",  700
        },
        {
            // Empty message types - we allow empty types for API lookups
            __LINE__,
            R"(
            {
                "query-type": "",
                "response-type": "",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            DHCP_NOTYPE, DHCP_NOTYPE, "start_here", "stop_there",  700
        },
        {
            // Empty event labels - we allow empty events for API lookups
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "",
                "stop-event": "",
                "subnet-id": 700
            })",
            DHCPDISCOVER, DHCPOFFER, "", "",  700
        },
        {
            // Subnet id zero,
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 0
            })",
            DHCPDISCOVER, DHCPOFFER, "start_here", "stop_there", SUBNET_ID_GLOBAL
        },
        {
            // "*" message types should map to DHCP_NOTYPE
            __LINE__,
            R"(
            {
                "query-type": "*",
                "response-type": "*",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 701
            })",
            DHCP_NOTYPE, DHCP_NOTYPE, "start_here", "stop_there", 701
        },
    };

    testValidScenarios(scenarios, AF_INET);
}

TEST_F(DurationKeyParserTest, invalidScenarios4) {
    // List of test scenarios to run.
    list<InvalidScenario> scenarios = {
        {
            // Spurious parameter
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700,
                "bogus": true
            })",
            "spurious 'bogus' parameter"
        },
        {
            // Missing query-type
            __LINE__,
            R"(
            {
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'query-type' parameter is required"
        },
        {
            // Non-string value for query-type
            __LINE__,
            R"(
            {
                "query-type": 1234,
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'query-type' parameter is not a string"
        },
        {
            // Non-existent query-type
            __LINE__,
            R"(
            {
                "query-type": "BOGUS",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'query-type' parameter is invalid, 'BOGUS' is not a valid DHCP message type"
        },
        {
            // Missing response-type
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'response-type' parameter is required"
        },
        {
            // Non-string value for response-type
            __LINE__,
            R"(
            {
                "query-type": "DHCDISCOVER",
                "response-type": 5768,
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'response-type' parameter is not a string"
        },
        {
            // Non-existent response-type
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "BOGUS",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'response-type' parameter is invalid, 'BOGUS' is not a valid DHCP message type"
        },
        {
            // Missing start-event
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'start-event' parameter is required"
        },
        {
            // Non-string start-event
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": 5678,
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'start-event' parameter is not a string"
        },
        {
            // Missing stop-event
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "subnet-id": 700
            })",
            "'stop-event' parameter is required"
        },
        {
            // Non-string start-event
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": 1234,
                "subnet-id": 700
            })",
            "'stop-event' parameter is not a string"
        },
        {
            // Non-integer subnet-id
            __LINE__,
            R"(
            {
                "query-type": "DHCPDISCOVER",
                "response-type": "DHCPOFFER",
                "start-event": "start_here",
                "stop-event": "stop_here",
                "subnet-id": false
            })",
            "'subnet-id' parameter is not an integer"
        },
    };

    testInvalidScenarios(scenarios,  AF_INET);
}

TEST_F(DurationKeyParserTest, validScenarios6) {
    // List of test scenarios to run.
    std::list<ValidScenario> scenarios = {
        {
            // All parameters,
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            DHCPV6_SOLICIT, DHCPV6_ADVERTISE, "start_here", "stop_there",  700
        },
        {
            // Empty message types - we allow empty types for API lookups
            __LINE__,
            R"(
            {
                "query-type": "",
                "response-type": "",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            DHCP_NOTYPE, DHCP_NOTYPE, "start_here", "stop_there",  700
        },
        {
            // Empty event labels - we allow empty events for API lookups
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": "",
                "stop-event": "",
                "subnet-id": 700
            })",
            DHCPV6_SOLICIT, DHCPV6_ADVERTISE, "", "",  700
        },
        {
            // Subnet id zero,
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 0
            })",
            DHCPV6_SOLICIT, DHCPV6_ADVERTISE, "start_here", "stop_there", SUBNET_ID_GLOBAL
        },
        {
            // "*" message types should map to DHCPV6_NOTYPE
            __LINE__,
            R"(
            {
                "query-type": "*",
                "response-type": "*",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 701
            })",
            DHCPV6_NOTYPE, DHCPV6_NOTYPE, "start_here", "stop_there", 701
        },
    };

    testValidScenarios(scenarios, AF_INET6);
}

TEST_F(DurationKeyParserTest, invalidScenarios6) {
    // List of test scenarios to run.
    list<InvalidScenario> scenarios = {
        {
            // Spurious parameter
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700,
                "bogus": true
            })",
            "spurious 'bogus' parameter"
        },
        {
            // Missing query-type
            __LINE__,
            R"(
            {
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'query-type' parameter is required"
        },
        {
            // Non-string value for query-type
            __LINE__,
            R"(
            {
                "query-type": 1234,
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'query-type' parameter is not a string"
        },
        {
            // Non-existent query-type
            __LINE__,
            R"(
            {
                "query-type": "BOGUS",
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'query-type' parameter is invalid, 'BOGUS' is not a valid DHCPV6 message type"
        },
        {
            // Missing response-type
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'response-type' parameter is required"
        },
        {
            // Non-string value for response-type
            __LINE__,
            R"(
            {
                "query-type": "DHCDISCOVER",
                "response-type": 5768,
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'response-type' parameter is not a string"
        },
        {
            // Non-existent response-type
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "BOGUS",
                "start-event": "start_here",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'response-type' parameter is invalid, 'BOGUS' is not a valid DHCPV6 message type"
        },
        {
            // Missing start-event
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'start-event' parameter is required"
        },
        {
            // Non-string start-event
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": 5678,
                "stop-event": "stop_there",
                "subnet-id": 700
            })",
            "'start-event' parameter is not a string"
        },
        {
            // Missing stop-event
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "subnet-id": 700
            })",
            "'stop-event' parameter is required"
        },
        {
            // Non-string start-event
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": 1234,
                "subnet-id": 700
            })",
            "'stop-event' parameter is not a string"
        },
        {
            // Non-integer subnet-id
            __LINE__,
            R"(
            {
                "query-type": "SOLICIT",
                "response-type": "ADVERTISE",
                "start-event": "start_here",
                "stop-event": "stop_here",
                "subnet-id": false
            })",
            "'subnet-id' parameter is not an integer"
        },
    };

    testInvalidScenarios(scenarios, AF_INET6);
}

} // end of anonymous namespace
