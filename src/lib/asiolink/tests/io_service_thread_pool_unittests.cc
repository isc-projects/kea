// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <asiolink/io_service_thread_pool.h>
#include <exceptions/exceptions.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;

namespace {

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Simple test fixture for testing IoServiceThreadPool.
class IoServiceThreadPoolTest : public ::testing::Test {
public:
    /// @brief Constructor.
    IoServiceThreadPoolTest()
        : io_service_(new IOService()) {
    }

    /// @brief Destructor.
    virtual ~IoServiceThreadPoolTest() {
        io_service_->stop();
    }

    /// @brief IOService instance used by thread pools.
    IOServicePtr io_service_;
};

// URL contains scheme and hostname.
TEST_F(IoServiceThreadPoolTest, invalidConstruction) {
    IoServiceThreadPoolPtr pool;

    // Constructing with pool size of 0 should fail.
    ASSERT_THROW_MSG(pool.reset(new IoServiceThreadPool(io_service_, 0)),
                     BadValue, "pool_size must be non 0");
}

// Verifies that a pool can be created without starting it.
TEST_F(IoServiceThreadPoolTest, deferredStartConstruction) {
    IoServiceThreadPoolPtr pool;

    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3, true)));

    // State should be stopped.
    // Pool size should be 3.
    // IOService should be there.
    // IOService is new, so it should not be stopped.
    // No threads in the pool.
    ASSERT_TRUE(pool->isStopped());
    EXPECT_EQ(pool->getPoolSize(), 3);
    ASSERT_TRUE(pool->getIOService());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Destructor should not throw.
    ASSERT_NO_THROW_LOG(pool.reset());
}

// Verifies that a pool can be started within the constructor.
TEST_F(IoServiceThreadPoolTest, startDuringConstruction) {
    IoServiceThreadPoolPtr pool;

    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3)));

    // State should be running.
    // Pool size should be 3.
    // IOService should be there.
    // IOService is new, so it should not be stopped.
    // Should have 3 threads in the pool.
    ASSERT_TRUE(pool->isRunning());
    EXPECT_EQ(pool->getPoolSize(), 3);
    ASSERT_TRUE(pool->getIOService());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Destructor should not throw.
    ASSERT_NO_THROW_LOG(pool.reset());
}

// Verifies that pool can move from STOPPED to RUNNING.
TEST_F(IoServiceThreadPoolTest, stoppedToRunning) {
    IoServiceThreadPoolPtr pool;

    // Create a stopped pool.
    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3, true)));
    ASSERT_TRUE(pool->isStopped());

    // Call run from STOPPED.
    ASSERT_NO_THROW_LOG(pool->run());

    // State should be RUNNING, IOService should not be stopped, we should
    // have 3 threads in the pool.
    ASSERT_TRUE(pool->isRunning());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Calling run again should be harmless.
    ASSERT_NO_THROW_LOG(pool->run());

    // State should be RUNNING, IOService should not be stopped, we should
    // have 3 threads in the pool.
    ASSERT_TRUE(pool->isRunning());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Destroying the pool should be fine.
    ASSERT_NO_THROW_LOG(pool.reset());
}

// Verifies that pool can move from RUNNING to STOPPED.
TEST_F(IoServiceThreadPoolTest, runningToStopped) {
    IoServiceThreadPoolPtr pool;

    // Create a running pool.
    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3, false)));
    ASSERT_TRUE(pool->isRunning());

    // Call stop.
    ASSERT_NO_THROW_LOG(pool->stop());

    // State should be STOPPED, IOService should be stopped, we should
    // have 0 threads in the pool.
    ASSERT_TRUE(pool->isStopped());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Calling stop again should be harmless.
    ASSERT_NO_THROW_LOG(pool->stop());

    // State should be STOPPED, IOService should be stopped, we should
    // have 0 threads in the pool.
    ASSERT_TRUE(pool->isStopped());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Destroying the pool should be fine.
    ASSERT_NO_THROW_LOG(pool.reset());
}

// Verifies that pool can move from RUNNING to PAUSED.
TEST_F(IoServiceThreadPoolTest, runningToPaused) {
    IoServiceThreadPoolPtr pool;

    // Create a running pool.
    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3, false)));
    ASSERT_TRUE(pool->isRunning());

    // Call pause from RUNNING.
    ASSERT_NO_THROW_LOG(pool->pause());

    // State should be PAUSED, IOService should be stopped, we should
    // have 3 threads in the pool.
    ASSERT_TRUE(pool->isPaused());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Calling pause again should be harmless.
    ASSERT_NO_THROW_LOG(pool->pause());

    // State should be PAUSED, IOService should be stopped, we should
    // have 3 threads in the pool.
    ASSERT_TRUE(pool->isPaused());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Destroying the pool should be fine.
    ASSERT_NO_THROW_LOG(pool.reset());
}

// Verifies that pool can move from PAUSED to RUNNING.
TEST_F(IoServiceThreadPoolTest, pausedToRunning) {
    IoServiceThreadPoolPtr pool;

    // Create a running pool.
    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3, false)));
    ASSERT_TRUE(pool->isRunning());

    // Call pause from RUNNING.
    ASSERT_NO_THROW_LOG(pool->pause());
    ASSERT_TRUE(pool->isPaused());

    // Call run.
    ASSERT_NO_THROW_LOG(pool->run());

    // State should be RUNNING, IOService should not be stopped, we should
    // have 3 threads in the pool.
    ASSERT_TRUE(pool->isRunning());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 3);

    // Destroying the pool should be fine.
    ASSERT_NO_THROW_LOG(pool.reset());
}

// Verifies that pool can move from PAUSED to STOPPED.
TEST_F(IoServiceThreadPoolTest, pausedToStopped) {
    IoServiceThreadPoolPtr pool;

    // Create a running pool.
    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3, false)));
    ASSERT_TRUE(pool->isRunning());

    // Call pause from RUNNING.
    ASSERT_NO_THROW_LOG(pool->pause());
    ASSERT_TRUE(pool->isPaused());

    // Call stop.
    ASSERT_NO_THROW_LOG(pool->stop());

    // State should be STOPPED, IOService should be stopped, we should
    // have 0 threads in the pool.
    ASSERT_TRUE(pool->isStopped());
    EXPECT_TRUE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Destroying the pool should be fine.
    ASSERT_NO_THROW_LOG(pool.reset());
}

// Verifies that attempting to pause a STOPPED pool has no effect.
TEST_F(IoServiceThreadPoolTest, stoppedToPaused) {
    IoServiceThreadPoolPtr pool;

    // Create a stopped pool.
    ASSERT_NO_THROW_LOG(pool.reset(new IoServiceThreadPool(io_service_, 3, true)));
    ASSERT_TRUE(pool->isStopped());

    // State should be STOPPED, IOService won't be stopped because it was
    // never started. We should have 0 threads in the pool.
    ASSERT_TRUE(pool->isStopped());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Call pause from STOPPED.
    ASSERT_NO_THROW_LOG(pool->pause());

    // Should have no effect.
    ASSERT_TRUE(pool->isStopped());

    // State should be STOPPED, IOService won't be stopped because it was
    // never started. We should have 0 threads in the pool.
    ASSERT_TRUE(pool->isStopped());
    EXPECT_FALSE(pool->getIOService()->stopped());
    EXPECT_EQ(pool->getThreadCount(), 0);

    // Destroying the pool should be fine.
    ASSERT_NO_THROW_LOG(pool.reset());
}

}
