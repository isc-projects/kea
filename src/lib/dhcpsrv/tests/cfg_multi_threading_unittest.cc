// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <util/multi_threading_mgr.h>

#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief Test fixture class for @c MultiThreadingConfigParser
class CfgMultiThreadingTest : public ::testing::Test {
public:

    /// @brief Constructor
    CfgMultiThreadingTest() = default;

    /// @brief Destructor
    virtual ~CfgMultiThreadingTest() = default;

protected:

    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c MultiThreadingMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c MultiThreadingMgr.
    virtual void TearDown();
};

void
CfgMultiThreadingTest::SetUp() {
    MultiThreadingMgr::instance().apply(false, 0, 0);
}

void
CfgMultiThreadingTest::TearDown() {
    MultiThreadingMgr::instance().apply(false, 0 , 0);
}

/// @brief Verifies that extracting multi threading settings works
TEST_F(CfgMultiThreadingTest, extract) {
    bool enabled = false;
    uint32_t thread_count = 0;
    uint32_t queue_size = 0;
    std::string content_json =
        "{"
        "    \"enable-multi-threading\": true,\n"
        "    \"thread-pool-size\": 4,\n"
        "    \"packet-queue-size\": 64\n"
        "}";
    ConstElementPtr param;
    ASSERT_NO_THROW(param = Element::fromJSON(content_json))
                            << "invalid context_json, test is broken";
    ASSERT_NO_THROW(CfgMultiThreading::extract(param, enabled, thread_count,
                                               queue_size));
    EXPECT_EQ(enabled, true);
    EXPECT_EQ(thread_count, 4);
    EXPECT_EQ(queue_size, 64);

    content_json = "{}";
    ASSERT_NO_THROW(param = Element::fromJSON(content_json))
                            << "invalid context_json, test is broken";
    //check empty config
    ASSERT_NO_THROW(CfgMultiThreading::extract(param, enabled, thread_count,
                    queue_size));
    EXPECT_EQ(enabled, false);
    EXPECT_EQ(thread_count, 0);
    EXPECT_EQ(queue_size, 0);

    enabled = true;
    thread_count = 4;
    queue_size = 64;
    // check empty data
    ASSERT_NO_THROW(CfgMultiThreading::extract(ConstElementPtr(), enabled,
                    thread_count, queue_size));
    EXPECT_EQ(enabled, false);
    EXPECT_EQ(thread_count, 0);
    EXPECT_EQ(queue_size, 0);
}

/// @brief Verifies that applying multi threading settings works
TEST_F(CfgMultiThreadingTest, apply) {
    EXPECT_FALSE(MultiThreadingMgr::instance().getMode());
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadPoolSize(), 0);
    EXPECT_EQ(MultiThreadingMgr::instance().getPacketQueueSize(), 0);
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadPool().getMaxQueueSize(), 0);
    std::string content_json =
        "{"
        "    \"enable-multi-threading\": true,\n"
        "    \"thread-pool-size\": 4,\n"
        "    \"packet-queue-size\": 64\n"
        "}";
    ConstElementPtr param;
    ASSERT_NO_THROW(param = Element::fromJSON(content_json))
                            << "invalid context_json, test is broken";
    CfgMultiThreading::apply(param);
    EXPECT_TRUE(MultiThreadingMgr::instance().getMode());
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadPoolSize(), 4);
    EXPECT_EQ(MultiThreadingMgr::instance().getPacketQueueSize(), 64);
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadPool().getMaxQueueSize(), 64);
}

}  // namespace
