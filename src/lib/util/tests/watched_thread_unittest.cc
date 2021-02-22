// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/watched_thread.h>

#include <gtest/gtest.h>

#include <atomic>
#include <functional>
#include <signal.h>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::util;

namespace {

/// @brief Test Fixture for testing @c isc::util::WatchedThread
class WatchedThreadTest : public ::testing::Test {
public:
    /// @brief Maximum number of passes allowed in worker event loop
    static const int WORKER_MAX_PASSES;

    /// @brief Constructor.
    WatchedThreadTest() {}

    /// @brief Destructor.
    ~WatchedThreadTest() {
    }

    /// @brief Sleeps for a given number of event periods sleep
    /// Each period is 50 ms.
    void nap(int periods) {
        usleep(periods * 50 * 1000);
    };

    /// @brief Worker function to be used by the WatchedThread's thread
    ///
    /// The function runs 10 passes through an "event" loop.
    /// On each pass:
    /// - check terminate command
    /// - instigate the desired event (second pass only)
    /// - naps for 1 period (50ms)
    ///
    /// @param watch_type type of event that should occur
    void worker(WatchedThread::WatchType watch_type) {
        sigset_t nsset;
        pthread_sigmask(SIG_SETMASK, 0, &nsset);
        EXPECT_EQ(1, sigismember(&nsset, SIGCHLD));
        EXPECT_EQ(1, sigismember(&nsset, SIGINT));
        EXPECT_EQ(1, sigismember(&nsset, SIGHUP));
        EXPECT_EQ(1, sigismember(&nsset, SIGTERM));
        for (passes_ = 1; passes_ < WORKER_MAX_PASSES; ++passes_) {

            // Stop if we're told to do it.
            if (wthread_->shouldTerminate()) {
                return;
            }

            // On the second pass, set the event.
            if (passes_ == 2) {
                switch (watch_type) {
                case WatchedThread::ERROR:
                    wthread_->setError("we have an error");
                    break;
                case WatchedThread::READY:
                    wthread_->markReady(watch_type);
                    break;
                case WatchedThread::TERMINATE:
                default:
                    // Do nothing, we're waiting to be told to stop.
                    break;
                }
            }

            // Take a nap.
            nap(1);
        }

        // Indicate why we stopped.
        wthread_->setError("thread expired");
    }

    /// @brief Current WatchedThread instance.
    WatchedThreadPtr wthread_;

    /// @brief Counter used to track the number of passes made
    /// within the thread worker function.
    std::atomic<int> passes_;
};

const int WatchedThreadTest::WORKER_MAX_PASSES = 10;

/// Verifies the basic operation of the WatchedThread class.
/// It checks that a WatchedThread can be created, can be stopped,
/// and that in set and clear sockets.
TEST_F(WatchedThreadTest, watchedThreadClassBasics) {

    /// We'll create a WatchedThread and let it run until it expires.  (Note this is more
    /// of a test of WatchedThreadTest itself and ensures that the assumptions made in
    /// our other tests as to why threads have finished are sound.
    wthread_.reset(new WatchedThread());
    ASSERT_FALSE(wthread_->isRunning());
    wthread_->start(std::bind(&WatchedThreadTest::worker, this, WatchedThread::TERMINATE));
    ASSERT_TRUE(wthread_->isRunning());

    // Wait more long enough (we hope) for the thread to expire.
    nap(WORKER_MAX_PASSES * 4);

    // It should have done the maximum number of passes.
    EXPECT_EQ(passes_, WORKER_MAX_PASSES);

    // Error should be ready and error text should be "thread expired".
    ASSERT_TRUE(wthread_->isReady(WatchedThread::ERROR));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::READY));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::TERMINATE));
    EXPECT_EQ("thread expired", wthread_->getLastError());

    // Thread is technically still running, so let's stop it.
    EXPECT_TRUE(wthread_->isRunning());
    ASSERT_NO_THROW(wthread_->stop());
    ASSERT_FALSE(wthread_->isRunning());

    /// Now we'll test stopping a thread.
    /// Start the WatchedThread, let it run a little and then tell it to stop.
    wthread_->start(std::bind(&WatchedThreadTest::worker, this, WatchedThread::TERMINATE));
    ASSERT_TRUE(wthread_->isRunning());

    // No watches should be ready.
    ASSERT_FALSE(wthread_->isReady(WatchedThread::ERROR));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::READY));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::TERMINATE));

    // Wait a little while.
    nap(3);

    // Tell it to stop.
    wthread_->stop();
    ASSERT_FALSE(wthread_->isRunning());

    // It should have done less than the maximum number of passes.
    EXPECT_LT(passes_, WORKER_MAX_PASSES);

    // No watches should be ready.  Error text should be "thread stopped".
    ASSERT_FALSE(wthread_->isReady(WatchedThread::ERROR));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::READY));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::TERMINATE));
    EXPECT_EQ("thread stopped", wthread_->getLastError());


    // Next we'll test error notification.
    // Start the WatchedThread with a thread that sets an error on the second pass.
    wthread_->start(std::bind(&WatchedThreadTest::worker, this, WatchedThread::ERROR));
    ASSERT_TRUE(wthread_->isRunning());

    // No watches should be ready.
    ASSERT_FALSE(wthread_->isReady(WatchedThread::ERROR));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::READY));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::TERMINATE));

    // Wait a little while.
    nap(6);

    // It should now indicate an error.
    ASSERT_TRUE(wthread_->isReady(WatchedThread::ERROR));
    EXPECT_EQ("we have an error", wthread_->getLastError());

    // Tell it to stop.
    wthread_->stop();
    ASSERT_FALSE(wthread_->isRunning());

    // It should have done less than the maximum number of passes.
    EXPECT_LT(passes_, WORKER_MAX_PASSES);

    // No watches should be ready.  Error text should be "thread stopped".
    ASSERT_FALSE(wthread_->isReady(WatchedThread::ERROR));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::READY));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::TERMINATE));
    EXPECT_EQ("thread stopped", wthread_->getLastError());


    // Finally, we'll test data ready notification.
    // We'll start the WatchedThread with a thread that indicates data ready on its second pass.
    wthread_->start(std::bind(&WatchedThreadTest::worker, this, WatchedThread::READY));
    ASSERT_TRUE(wthread_->isRunning());

    // No watches should be ready.
    ASSERT_FALSE(wthread_->isReady(WatchedThread::ERROR));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::READY));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::TERMINATE));

    // Wait a little while.
    nap(6);

    // It should now indicate data ready.
    ASSERT_TRUE(wthread_->isReady(WatchedThread::READY));

    // Tell it to stop.
    wthread_->stop();
    ASSERT_FALSE(wthread_->isRunning());

    // It should have done less than the maximum number of passes.
    EXPECT_LT(passes_, WORKER_MAX_PASSES);

    // No watches should be ready.  Error text should be "thread stopped".
    ASSERT_FALSE(wthread_->isReady(WatchedThread::ERROR));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::READY));
    ASSERT_FALSE(wthread_->isReady(WatchedThread::TERMINATE));
    EXPECT_EQ("thread stopped", wthread_->getLastError());
}

}
