// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/dhcp_queue_control_parser.h>
#include <testutils/multi_threading_utils.h>
#include <testutils/test_to_element.h>
#include <util/multi_threading_mgr.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::util;

namespace {

/// @brief Test fixture class for @c DHCPQueueControlParser
class DHCPQueueControlParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    DHCPQueueControlParserTest() = default;

    /// @brief Destructor
    virtual ~DHCPQueueControlParserTest() = default;

protected:
    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();
};

void
DHCPQueueControlParserTest::SetUp() {
    CfgMgr::instance().clear();
}

void
DHCPQueueControlParserTest::TearDown() {
    CfgMgr::instance().clear();
}

// Verifies that DHCPQueueControlParser handles
// expected valid dhcp-queue-control content
TEST_F(DHCPQueueControlParserTest, validContent) {
    struct Scenario {
        std::string description_;
        std::string json_;
    };

    std::vector<Scenario> scenarios = {
        {
        "queue disabled",
        "{ \n"
        "   \"enable-queue\": false \n"
        "} \n"
        },
        {
        "queue disabled, arbitrary content allowed",
        "{ \n"
        "   \"enable-queue\": false, \n"
        "   \"foo\": \"bogus\", \n"
        "   \"random-int\" : 1234 \n"
        "} \n"
        },
        {
        "queue enabled, with queue-type",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": \"some-type\" \n"
        "} \n"
        },
        {
        "queue enabled with queue-type and arbitrary content",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": \"some-type\", \n"
        "   \"foo\": \"bogus\", \n"
        "   \"random-int\" : 1234 \n"
        "} \n"
        }
    };

    // Iterate over the valid scenarios and verify they succeed.
    ConstElementPtr config_elems;
    ConstElementPtr queue_control;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            // Construct the config JSON
            ASSERT_NO_THROW(config_elems = Element::fromJSON(scenario.json_))
                            << "invalid JSON, test is broken";

            // Parsing config into a queue control should succeed.
            DHCPQueueControlParser parser;
            try {
                queue_control = parser.parse(config_elems);
            } catch (const std::exception& ex) {
                ADD_FAILURE() << "parser threw an exception: " << ex.what();
            }

            // Verify the resultant queue control.
            ASSERT_TRUE(queue_control);

            // The parser should have created a duplicate of the
            // configuration elements.
            ASSERT_TRUE(queue_control.get() != config_elems.get());
            EXPECT_TRUE(queue_control->equals(*config_elems));
        }
    }
}

// Verifies that DHCPQueueControlParser correctly catches
// invalid dhcp-queue-control content
TEST_F(DHCPQueueControlParserTest, invalidContent) {
    struct Scenario {
        std::string description_;
        std::string json_;
    };

    std::vector<Scenario> scenarios = {
        {
        "enable-queue missing",
        "{ \n"
        "   \"enable-type\": \"some-type\" \n"
        "} \n"
        },
        {
        "enable-queue not boolean",
        "{ \n"
        "   \"enable-queue\": \"always\" \n"
        "} \n"
        },
        {
        "queue enabled, type missing",
        "{ \n"
        "   \"enable-queue\": true \n"
        "} \n"
        },
        {
        "queue enabled, type not a string",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": 7777 \n"
        "} \n"
        }
    };

    // Iterate over the valid scenarios and verify they succeed.
    ConstElementPtr config_elems;
    ConstElementPtr queue_control;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            // Construct the config JSON
            ASSERT_NO_THROW(config_elems = Element::fromJSON(scenario.json_))
                            << "invalid JSON, test is broken";

            // Parsing config into a queue control should succeed.
            DHCPQueueControlParser parser;
            EXPECT_THROW(parser.parse(config_elems), DhcpConfigError);
        }
    }
}

// Verifies that DHCPQueueControlParser disables the queue when multi-threading
// is enabled
TEST_F(DHCPQueueControlParserTest, multiThreading) {
    // Enable config with some queue type.
    std::string config =
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": \"some-type\" \n"
        "} \n";

    // Construct the config JSON.
    ConstElementPtr config_elems;
    ASSERT_NO_THROW(config_elems = Element::fromJSON(config))
        << "invalid JSON, test is broken";

    // Parse config.
    DHCPQueueControlParser parser;
    ConstElementPtr queue_control;
    ASSERT_FALSE(MultiThreadingMgr::instance().getMode());
    ASSERT_NO_THROW(queue_control = parser.parse(config_elems))
        << "parse fails, test is broken";
    // Verify that queue is enabled.
    ASSERT_TRUE(queue_control);
    ASSERT_TRUE(queue_control->get("enable-queue"));
    EXPECT_EQ("true", queue_control->get("enable-queue")->str());

    // Retry with multi-threading.
    MultiThreadingTest mt(true);
    ASSERT_TRUE(MultiThreadingMgr::instance().getMode());
    ASSERT_NO_THROW(queue_control = parser.parse(config_elems));
    ASSERT_TRUE(queue_control);
    ASSERT_TRUE(queue_control->get("enable-queue"));
    EXPECT_EQ("false", queue_control->get("enable-queue")->str());
}

}; // anonymous namespace
