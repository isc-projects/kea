// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/parsers/multi_threading_config_parser.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <util/multi_threading_mgr.h>
#include <testutils/test_to_element.h>

#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::util;

namespace {

/// @brief Test fixture class for @c MultiThreadingConfigParser
class MultiThreadingConfigParserTest : public ::testing::Test {
public:

    /// @brief Constructor
    MultiThreadingConfigParserTest() = default;

    /// @brief Destructor
    virtual ~MultiThreadingConfigParserTest() = default;

protected:

    /// @brief Setup for each test.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    virtual void TearDown();
};

void
MultiThreadingConfigParserTest::SetUp() {
    MultiThreadingMgr::instance().setMode(false);
}

void
MultiThreadingConfigParserTest::TearDown() {
    MultiThreadingMgr::instance().setMode(false);
}

// Verifies that MultiThreadingConfigParser handles
// expected valid content
TEST_F(MultiThreadingConfigParserTest, validContent) {
    struct Scenario {
        std::string description_;
        std::string json_;
    };

    std::vector<Scenario> scenarios = {
        {
        "enable-multi-threading, without thread-pool-size or packet-queue-size",
        "{ \n"
        "   \"enable-multi-threading\": true \n"
        "} \n"
        },
        {
        "enable-multi-threading disabled",
        "{ \n"
        "   \"enable-multi-threading\": false \n"
        "} \n"
        },
        {
        "enable-multi-threading, with thread-pool-size and packet-queue-size",
        "{ \n"
        "   \"enable-multi-threading\": true, \n"
        "   \"thread-pool-size\": 4, \n"
        "   \"packet-queue-size\": 64 \n"
        "} \n"
        }
    };

    // Iterate over the valid scenarios and verify they succeed.
    ConstElementPtr config_elems;
    ConstElementPtr multi_threading_config;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            SrvConfig srv_config;
            // Construct the config JSON
            ASSERT_NO_THROW(config_elems = Element::fromJSON(scenario.json_))
                            << "invalid JSON, test is broken";

            // Parsing config should succeed.
            MultiThreadingConfigParser parser;
            try {
                parser.parse(srv_config, config_elems);
            } catch (const std::exception& ex) {
                ADD_FAILURE() << "parser threw an exception: " << ex.what();
            }

            multi_threading_config = srv_config.getDHCPMultiThreading();
            // Verify the resultant configuration.
            ASSERT_TRUE(multi_threading_config);

            bool enabled = false;
            uint32_t thread_count = 0;
            uint32_t queue_size = 0;

            CfgMultiThreading::extract(multi_threading_config, enabled,
                                       thread_count, queue_size);

            EXPECT_EQ(MultiThreadingMgr::instance().getMode(), enabled);

            EXPECT_TRUE(multi_threading_config->equals(*config_elems));
        }
    }
}

// Verifies that MultiThreadingConfigParser correctly catches
// invalid content
TEST_F(MultiThreadingConfigParserTest, invalidContent) {
    struct Scenario {
        std::string description_;
        std::string json_;
    };

    std::vector<Scenario> scenarios = {
        {
        "enable-multi-threading not boolean",
        "{ \n"
        "   \"enable-multi-threading\": \"always\" \n"
        "} \n"
        },
        {
        "thread-pool-size not integer",
        "{ \n"
        "   \"thread-pool-size\": true \n"
        "} \n"
        },
        {
        "thread-pool-size negative",
        "{ \n"
        "   \"thread-pool-size\": -1 \n"
        "} \n"
        },
        {
        "thread-pool-size too large",
        "{ \n"
        "   \"thread-pool-size\": 200000 \n"
        "} \n"
        },
        {
        "packet-queue-size not integer",
        "{ \n"
        "   \"packet-queue-size\": true \n"
        "} \n"
        },
        {
        "packet-queue-size-size negative",
        "{ \n"
        "   \"packet-queue-size\": -1 \n"
        "} \n"
        },
        {
        "packet-queue-size too large",
        "{ \n"
        "   \"packet-queue-size\": 200000 \n"
        "} \n"
        }
    };

    // Iterate over the valid scenarios and verify they succeed.
    ConstElementPtr config_elems;
    ConstElementPtr queue_control;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            SrvConfig srv_config;
            // Construct the config JSON
            ASSERT_NO_THROW(config_elems = Element::fromJSON(scenario.json_))
                            << "invalid JSON, test is broken";

            // Parsing config into a queue control should succeed.
            MultiThreadingConfigParser parser;
            EXPECT_THROW(parser.parse(srv_config, config_elems), DhcpConfigError);
        }
    }
}

}  // namespace
