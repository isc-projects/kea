// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify the subnet ping-check
/// configuration cache.

#include <config.h>
#include <config_cache.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::ping_check;
using namespace isc::test;
using namespace boost::posix_time;

namespace {

/// @brief ConfigCache derivation that allows flush time to be modified.
class TestConfigCache : public ConfigCache {
public:
    /// @brief Constructor
    TestConfigCache() {
    }

    /// @brief Destructor
    virtual ~TestConfigCache() {
    }

    /// @brief Adjusts the last flush time by the given amount.
    ///
    /// @param offset signed value in seconds to add to cache's last
    /// flush time value
    void tweakLastFlushTime(int offset) {
        setModificationTime(getLastFlushTime() + seconds(offset));
    }
};

/// @brief Test fixture for testing ConfigCache.
class ConfigCacheTest : public ::testing::Test {
public:
    /// @brief Constructor
    ConfigCacheTest() {
        isc::util::MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor
    virtual ~ConfigCacheTest() {
    }

    /// @brief Verifies construction of a ConfigCache.
    void testConstruction() {
        // We use a BaseStampedElement to get the current time to ensure we
        // are using the same time perspective (currently local) as StampedElements do.
        BaseStampedElement now;
        ptime start_time = now.getModificationTime();

        // Create a new cache.
        TestConfigCache configs;
        EXPECT_EQ(configs.size(), 0);

        // Verify that last_flush_time_ has been set and that the
        // cache has no entries.
        ptime last_flush_time = configs.getLastFlushTime();
        EXPECT_GE(last_flush_time, start_time);

        // Verify that looking for an entry in an empty cache
        // gracefully finds nothing.
        PingCheckConfigPtr fetched_config;
        EXPECT_FALSE(configs.findConfig(999, fetched_config));
        EXPECT_FALSE(fetched_config);
    }

    /// @brief Verifies that invalid user-context config is rejected gracefully.
    void testInvalidConfig() {
        // Create a new cache.
        TestConfigCache configs;
        EXPECT_EQ(configs.size(), 0);

        // An invalid keyword should fail.
        std::string json =
        R"({
            "ping-check" : {
                "bogus" : 777
            }
        })";

        ConstElementPtr user_context;
        ASSERT_NO_THROW_LOG(user_context = Element::fromJSON(json));

        ASSERT_THROW_MSG(configs.parseAndCacheConfig(1, user_context), DhcpConfigError,
                         "spurious 'bogus' parameter");

        EXPECT_EQ(configs.size(), 0);
    }

    /// @brief Verifies that valid user-context supplied config are cached correctly.
    void testValidConfig() {
        // Create a new cache.
        TestConfigCache configs;
        EXPECT_EQ(configs.size(), 0);

        // A valid config should get cached.
        std::string json =
        R"({
            "ping-check" : {
                "enable-ping-check" : false,
                "min-ping-requests" : 2,
                "reply-timeout" : 375,
                "ping-cltt-secs" : 120,
                "ping-channel-threads" : 6
            }
        })";

        ConstElementPtr user_context;
        ASSERT_NO_THROW_LOG(user_context = Element::fromJSON(json));

        // Verify that we cache a valid config.
        PingCheckConfigPtr config;
        ASSERT_NO_THROW_LOG(config = configs.parseAndCacheConfig(1, user_context));
        ASSERT_TRUE(config);
        EXPECT_EQ(configs.size(), 1);

        // Verify we can retrieve the cached config.
        PingCheckConfigPtr fetched_config;
        ASSERT_TRUE(configs.findConfig(1, fetched_config));
        EXPECT_EQ(fetched_config, config);
    }

    /// @brief Verifies that an empty config pointer can be cached.
    void testConfigCacheEmptyConfig() {
        // Create a new cache.
        TestConfigCache configs;
        EXPECT_EQ(configs.size(), 0);

        // Verify that we can cache an empty config pointer.
        PingCheckConfigPtr no_config;
        ASSERT_NO_THROW_LOG(configs.cacheConfig(1, no_config));
        EXPECT_EQ(configs.size(), 1);

        // Verify we can retrieve the cached empty config pointer.
        PingCheckConfigPtr fetched_config;
        ASSERT_TRUE(configs.findConfig(1, fetched_config));
        ASSERT_FALSE(fetched_config);
    }

    /// @brief Verifies that the cache can be cleared correctly.
    void testFlushCache() {
        // Create a new cache.
        TestConfigCache configs;
        EXPECT_EQ(configs.size(), 0);

        ptime last_flush_time = configs.getLastFlushTime();

        // Now let's wind the clock back on last_flush_time.
        configs.tweakLastFlushTime(-1000);
        EXPECT_LT(configs.getLastFlushTime(), last_flush_time);
        last_flush_time = configs.getLastFlushTime();

        // Make a simple valid config.
        std::string json =
        R"({
            "ping-check": {
                "enable-ping-check" : true
            }
        })";

        ConstElementPtr user_context;
        ASSERT_NO_THROW_LOG(user_context = Element::fromJSON(json));

        for (int id = 1; id < 5; ++id) {
            PingCheckConfigPtr config;
            ASSERT_NO_THROW_LOG(config = configs.parseAndCacheConfig(id, user_context));
            ASSERT_TRUE(config);
            EXPECT_EQ(configs.size(), id);
        }

        // Verify we can explicitly clear the cache.  Should be no entries
        // and last_flush_time should be updated.
        configs.flush();
        EXPECT_GT(configs.getLastFlushTime(), last_flush_time);
        EXPECT_EQ(configs.size(), 0);
    }
};

TEST_F(ConfigCacheTest, construction) {
    testConstruction();
}

TEST_F(ConfigCacheTest, constructionMultiThreading) {
    MultiThreadingTest mt;
    testConstruction();
}

TEST_F(ConfigCacheTest, invalidConfig) {
    testInvalidConfig();
}

TEST_F(ConfigCacheTest, invalidConfigMultiThreading) {
    MultiThreadingTest mt;
    testInvalidConfig();
}

TEST_F(ConfigCacheTest, validConfig) {
    testValidConfig();
}

TEST_F(ConfigCacheTest, validConfigMultiThreading) {
    MultiThreadingTest mt;
    testValidConfig();
}

TEST_F(ConfigCacheTest, configCacheEmptyConfig) {
    testConfigCacheEmptyConfig();
}

TEST_F(ConfigCacheTest, configCacheEmptyConfigMultiThreading) {
    MultiThreadingTest mt;
    testConfigCacheEmptyConfig();
}

TEST_F(ConfigCacheTest, flushCache) {
    testFlushCache();
}

TEST_F(ConfigCacheTest, flushCacheMultiThreading) {
    MultiThreadingTest mt;
    testFlushCache();
}

} // end of anonymous namespace
