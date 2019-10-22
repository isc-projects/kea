// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/multi_threading_mgr.h>

#include <gtest/gtest.h>

using namespace isc::util;

// Verifies that the default mode is false (MT disabled).
TEST(MultiThreadingMgrTest, default) {
    EXPECT_FALSE(MultiThreadingMgr::instance().getMode());
}

// Verifies that the instance can be dynamic cast and setter works.
TEST(MultiThreadingMgrTest, setMode) {
    EXPECT_NO_THROW(dynamic_cast<MultiThreadingMgr&>(MultiThreadingMgr::instance()).setMode(true));
    EXPECT_TRUE(MultiThreadingMgr::instance().getMode());
    EXPECT_NO_THROW(dynamic_cast<MultiThreadingMgr&>(MultiThreadingMgr::instance()).setMode(false));
    EXPECT_FALSE(MultiThreadingMgr::instance().getMode());
}
