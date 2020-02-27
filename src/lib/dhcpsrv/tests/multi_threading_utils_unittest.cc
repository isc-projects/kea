// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/multi_threading_utils.h>
#include <util/multi_threading_mgr.h>

#include <gtest/gtest.h>

using namespace isc::dhcp;
using namespace isc::util;

namespace {

TEST(MultiThreadingUtil, constructorAndDestructor) {
    // get the thread pool instance
    auto & thread_pool = MultiThreadingMgr::instance().getPktThreadPool();
    // thread pool should be stopped
    EXPECT_EQ(thread_pool.size(), 0);
    // apply multi-threading configuration with 16 threads
    MultiThreadingMgr::instance().apply(true, 16);
    // thread count should match
    EXPECT_EQ(thread_pool.size(), 16);
    // use scope to test constructor and destructor
    {
        MultiThreadingCriticalSection cs;
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
        // use scope to test constructor and destructor
        {
            MultiThreadingCriticalSection inner_cs;
            // thread pool should be stopped
            EXPECT_EQ(thread_pool.size(), 0);
        }
    }
    // thread count should match
    EXPECT_EQ(thread_pool.size(), 16);
    // use scope to test constructor and destructor
    {
        MultiThreadingCriticalSection cs;
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
        // apply multi-threading configuration with 64 threads
        MultiThreadingMgr::instance().apply(true, 64);
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
    }
    // thread count should match
    EXPECT_EQ(thread_pool.size(), 64);
    // use scope to test constructor and destructor
    {
        MultiThreadingCriticalSection cs;
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
        // apply multi-threading configuration with 0 threads
        MultiThreadingMgr::instance().apply(false, 64);
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
    }
    // thread count should match
    EXPECT_EQ(thread_pool.size(), 0);
    // use scope to test constructor and destructor
    {
        MultiThreadingCriticalSection cs;
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
        // use scope to test constructor and destructor
        {
            MultiThreadingCriticalSection inner_cs;
            // thread pool should be stopped
            EXPECT_EQ(thread_pool.size(), 0);
        }
    }
    // thread count should match
    EXPECT_EQ(thread_pool.size(), 0);
    // use scope to test constructor and destructor
    {
        MultiThreadingCriticalSection cs;
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
        // apply multi-threading configuration with 64 threads
        MultiThreadingMgr::instance().apply(true, 64);
        // thread pool should be stopped
        EXPECT_EQ(thread_pool.size(), 0);
    }
    // thread count should match
    EXPECT_EQ(thread_pool.size(), 64);
}

}  // namespace
