// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
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

// Verifies that applying multi threading setting works
TEST_F(CfgMultiThreadingTest, apply) {
    EXPECT_FALSE(MultiThreadingMgr::instance().getMode());
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadPoolSize(), 0);
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadQueueSize(), 0);
    ElementPtr param = Element::createMap();
    param->set("enable-multi-threading", Element::create(true));
    param->set("thread-pool-size", Element::create(4));
    param->set("packet-queue-size", Element::create(64));
    CfgMultiThreading::apply(-1, param);
    EXPECT_TRUE(MultiThreadingMgr::instance().getMode());
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadPoolSize(), 4);
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadQueueSize(), 64);
    CfgMultiThreading::apply(8, param);
    EXPECT_TRUE(MultiThreadingMgr::instance().getMode());
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadPoolSize(), 8);
    EXPECT_EQ(MultiThreadingMgr::instance().getThreadQueueSize(), 0);
}

}  // namespace
