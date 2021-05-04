// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <http/http_thread_pool.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::http;

namespace {

class HttpThreadPoolTest : public ::testing::Test {
public:
    HttpThreadPoolTest() : io_service_(new IOService()) {
    }

    ~HttpThreadPoolTest() {
        io_service_->stop();
    }

    IOServicePtr io_service_;
};

// URL contains scheme and hostname.
TEST_F(HttpThreadPoolTest, invalidConstruction) {
    HttpThreadPoolPtr pool;

    // Constructing with pool size of 0 should fail.
    ASSERT_THROW_MSG(pool.reset(new HttpThreadPool(io_service_, 0)), BadValue,
                     "HttpThreadPool::ctor pool_size must be > 0");
}

TEST_F(HttpThreadPoolTest, deferredStartConstruction) {
    HttpThreadPoolPtr pool;

    ASSERT_NO_THROW_LOG(pool.reset(new HttpThreadPool(io_service_, 3, true)));

    // Pool size should be 3
    // State should be stopped. 
    // IOService should be there.
    // IOService is new, so it should not stopped,
    // No threads in the pool.
    EXPECT_EQ(pool->getPoolSize(), 3);
    ASSERT_TRUE(pool->getIOService());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(HttpThreadPool::RunState::STOPPED, pool->getRunState());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Stop should not throw.
    ASSERT_NO_THROW_LOG(pool->stop());

    // Nothing should have changed.
    EXPECT_EQ(HttpThreadPool::RunState::STOPPED, pool->getRunState());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Start should not throw.
    ASSERT_NO_THROW_LOG(pool->start());

    // State should be RUN, IOService should not be stopped, 
    // and there should be 3 threads in the pool.
    EXPECT_EQ(pool->getPoolSize(), 3);
    EXPECT_EQ(HttpThreadPool::RunState::RUN, pool->getRunState());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Stopping should not throw.
    ASSERT_NO_THROW_LOG(pool->stop());

    // State should be stopped, IOService should be stopped, and 
    // there should be no threads in the pool.
    EXPECT_EQ(HttpThreadPool::RunState::STOPPED, pool->getRunState());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Destructor should not throw.
    ASSERT_NO_THROW_LOG(pool.reset());
}

TEST_F(HttpThreadPoolTest, startDuringConstruction) {
    HttpThreadPoolPtr pool;

    ASSERT_NO_THROW_LOG(pool.reset(new HttpThreadPool(io_service_, 3)));

    // Pool size should be 3, state should be RUN, IOService should
    // set but not stopped, and we should have 3 threads in the pool.
    EXPECT_EQ(pool->getPoolSize(), 3);
    EXPECT_EQ(HttpThreadPool::RunState::RUN, pool->getRunState());
    ASSERT_TRUE(pool->getIOService());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Starting again should throw.
    ASSERT_THROW_MSG(pool->start(), InvalidOperation,
                     "HttpThreadPool::start already started!");

    // Stop should not throw.
    ASSERT_NO_THROW_LOG(pool->stop());

    // Pool size should be 3, state should STOPPED, IOService should
    // be stopped, and there should be no threads in the pool.
    EXPECT_EQ(pool->getPoolSize(), 3);
    EXPECT_EQ(HttpThreadPool::RunState::STOPPED, pool->getRunState());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Destructor should not throw.
    ASSERT_NO_THROW_LOG(pool.reset());
}

TEST_F(HttpThreadPoolTest, pauseAndResume) {
    HttpThreadPoolPtr pool;

    ASSERT_NO_THROW_LOG(pool.reset(new HttpThreadPool(io_service_, 3)));

    // State should be RUN, IOService not stopped, 3 threads in the pool.
    EXPECT_EQ(HttpThreadPool::RunState::RUN, pool->getRunState());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Pause should not throw.
    ASSERT_NO_THROW_LOG(pool->pause());

    // State should be PAUSED, IOService should be stopped, we should
    // still have 3 threads in the pool.
    EXPECT_EQ(HttpThreadPool::RunState::PAUSED, pool->getRunState());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Pausing again should be harmless.
    ASSERT_NO_THROW_LOG(pool->pause());

    // Nothing should have changed.
    EXPECT_EQ(HttpThreadPool::RunState::PAUSED, pool->getRunState());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Resume should not throw.
    ASSERT_NO_THROW_LOG(pool->resume());

    // State should be PAUSED, IOService should be stopped, we should
    // still have 3 threads in the pool.
    EXPECT_EQ(HttpThreadPool::RunState::RUN, pool->getRunState());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Resuming again should be harmless.
    ASSERT_NO_THROW_LOG(pool->resume());

    // Nothing should have changed.
    EXPECT_EQ(HttpThreadPool::RunState::RUN, pool->getRunState());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Stop should not throw.
    ASSERT_NO_THROW_LOG(pool->stop());

    // State should STOPPED, IOService should be stopped,
    // and there should be no threads in the pool.
    EXPECT_EQ(HttpThreadPool::RunState::STOPPED, pool->getRunState());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Destructor should not throw.
    ASSERT_NO_THROW_LOG(pool.reset());
}

}
