// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/readwrite_mutex.h>

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace isc::util;
using namespace std;

namespace {

/// @brief Test Fixture for testing read-write mutexes.
///
/// Each not basic test follows the same schema:
/// @code
/// main thread    work thread
/// <-             started
/// work           ->
///                enter guard
/// <-             done
/// terminate      ->
///                return
/// join
/// @endcode
class ReadWriteMutexTest : public ::testing::Test {
public:

    /// @brief Read-write mutex.
    ReadWriteMutex rw_mutex_;

    /// @brief Synchronization objects for work threads.
    struct Sync {
        bool started = false;
        mutex started_mtx;
        condition_variable started_cv;
        bool work = false;
        mutex work_mtx;
        condition_variable work_cv;
        bool done = false;
        mutex done_mtx;
        condition_variable done_cv;
        bool terminate = false;
        mutex terminate_mtx;
        condition_variable terminate_cv;
    } syncr_, syncw_;

    /// @brief Body of the reader.
    ///
    /// @param rw_mutex The read-write mutex.
    /// @param syncr The reader synchronization object.
    void reader(ReadWriteMutex& rw_mutex, Sync& syncr) {
        // Take mutex to wait for main thread signals.
        unique_lock<mutex> terminate_lock(syncr.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(syncr.started_mtx);
            syncr.started = true;
        }

        // Wait for work.
        {
            unique_lock<mutex> work_lock(syncr.work_mtx);
            // When this thread starts waiting, the main thread is resumed.
            syncr.started_cv.notify_one();
            syncr.work_cv.wait(work_lock, [&](){ return syncr.work; });
        }

        {
            // Enter a read lock guard.
            ReadLockGuard rwlock(rw_mutex);

            // Signal the thread holds the guard.
            {
                lock_guard<mutex> done_lock(syncr.done_mtx);
                syncr.done = true;
            }
            syncr.done_cv.notify_one();
        }

        // Wait to terminate.
        syncr.terminate_cv.wait(terminate_lock, [&](){ return syncr.terminate; });
    }

    /// @brief Body of the writer.
    ///
    /// @param rw_mutex The read-write mutex.
    /// @param syncw The writer synchronization object.
    void writer(ReadWriteMutex& rw_mutex, Sync& syncw) {
        // Take mutex to wait for main thread signals.
        unique_lock<mutex> terminate_lock(syncw.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(syncw.started_mtx);
            syncw.started = true;
        }

        // Wait for work.
        {
            unique_lock<mutex> work_lock(syncw.work_mtx);
            // When this thread starts waiting, the main thread is resumed.
            syncw.started_cv.notify_one();
            syncw.work_cv.wait(work_lock, [&](){ return syncw.work; });
        }

        {
            // Enter a write lock guard.
            WriteLockGuard rwlock(rw_mutex);

            // Signal the thread holds the guard.
            {
                lock_guard<mutex> done_lock(syncw.done_mtx);
                syncw.done = true;
            }
            syncw.done_cv.notify_one();
        }

        // Wait to terminate.
        syncw.terminate_cv.wait(terminate_lock, [&](){ return syncw.terminate; });
    }
};

// Verify basic read lock guard.
TEST_F(ReadWriteMutexTest, basicRead) {
    ReadLockGuard lock(rw_mutex_);
}

// Verify basic write lock guard.
TEST_F(ReadWriteMutexTest, basicWrite) {
    WriteLockGuard lock(rw_mutex_);
}

// Verify read lock guard using a thread.
TEST_F(ReadWriteMutexTest, read) {
    // Take mutex to wait for work thread signals.
    boost::shared_ptr<std::thread> thread;
    {
        unique_lock<mutex> started_lock(syncr_.started_mtx);

        // Create a work thread.
        thread = boost::make_shared<std::thread>([this](){ reader(rw_mutex_, syncr_); });

        // Wait work thread to start.
        syncr_.started_cv.wait(started_lock, [this](){ return syncr_.started; });

        unique_lock<mutex> done_lock(syncr_.done_mtx);

        // Signal the thread to work.
        {
            lock_guard<mutex> work_lock(syncr_.work_mtx);
            syncr_.work = true;
        }
        syncr_.work_cv.notify_one();

        // Wait thread to hold the read lock.
        syncr_.done_cv.wait(done_lock, [this](){ return syncr_.done; });
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncr_.terminate_mtx);
        syncr_.terminate = true;
    }
    syncr_.terminate_cv.notify_one();

    // Join the thread.
    thread->join();
}

// Verify write lock guard using a thread.
TEST_F(ReadWriteMutexTest, write) {
    // Take mutex to wait for work thread signals.
    boost::shared_ptr<std::thread> thread;
    {
        unique_lock<mutex> started_lock(syncw_.started_mtx);

        // Create a work thread.
        thread = boost::make_shared<std::thread>([this](){ writer(rw_mutex_, syncw_); });

        // Wait work thread to start.
        syncw_.started_cv.wait(started_lock, [this](){ return syncw_.started; });

        unique_lock<mutex> done_lock(syncw_.done_mtx);

        // Signal the thread to work.
        {
            lock_guard<mutex> work_lock(syncw_.work_mtx);
            syncw_.work = true;
        }
        syncw_.work_cv.notify_one();

        // Wait thread to hold the write lock.
        syncw_.done_cv.wait(done_lock, [this](){ return syncw_.done; });
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncw_.terminate_mtx);
        syncw_.terminate = true;
    }
    syncw_.terminate_cv.notify_one();

    // Join the thread.
    thread->join();
}

// Verify read lock guard can be acquired by multiple threads.
TEST_F(ReadWriteMutexTest, readRead) {
    // Take mutex to wait for work thread signals.
    boost::shared_ptr<std::thread> thread;
    {
        unique_lock<mutex> started_lock(syncr_.started_mtx);

        // Create a work thread.
        thread = boost::make_shared<std::thread>([this](){ reader(rw_mutex_, syncr_); });

        // Enter a read lock guard.
        ReadLockGuard rwlock(rw_mutex_);

        // Wait work thread to start.
        syncr_.started_cv.wait(started_lock, [this](){ return syncr_.started; });

        unique_lock<mutex> done_lock(syncr_.done_mtx);

        // Signal the thread to work.
        {
            lock_guard<mutex> work_lock(syncr_.work_mtx);
            syncr_.work = true;
        }
        syncr_.work_cv.notify_one();

        // Wait thread to hold the read lock.
        syncr_.done_cv.wait(done_lock, [this](){ return syncr_.done; });
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncr_.terminate_mtx);
        syncr_.terminate = true;
    }
    syncr_.terminate_cv.notify_one();

    // Join the thread.
    thread->join();
}

// Verify write lock guard is exclusive of a reader.
TEST_F(ReadWriteMutexTest, readWrite) {
    // Take mutex to wait for work thread signals.
    boost::shared_ptr<std::thread> thread;
    {
        unique_lock<mutex> started_lock(syncw_.started_mtx);

        // Create a work thread.
        thread = boost::make_shared<std::thread>([this](){ writer(rw_mutex_, syncw_); });

        // Wait work thread to start.
        syncw_.started_cv.wait(started_lock, [this](){ return syncw_.started; });

        unique_lock<mutex> done_lock(syncw_.done_mtx);

        {
            // Enter a read lock guard.
            ReadLockGuard rwlock(rw_mutex_);

            // Signal the thread to work.
            {
                lock_guard<mutex> work_lock(syncw_.work_mtx);
                syncw_.work = true;
            }
            syncw_.work_cv.notify_one();

            // Verify the work thread is waiting for the write lock.
            cout << "pausing for one second" << std::endl;
            bool ret = syncw_.done_cv.wait_for(done_lock, chrono::seconds(1), [this](){ return syncw_.done; });

            EXPECT_FALSE(syncw_.done);
            EXPECT_FALSE(ret);

            // Exiting the read lock guard.
        }

        // Wait thread to hold the write lock.
        syncw_.done_cv.wait(done_lock, [this](){ return syncw_.done; });
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncw_.terminate_mtx);
        syncw_.terminate = true;
    }
    syncw_.terminate_cv.notify_one();

    // Join the thread.
    thread->join();
}

// Verify write lock guard is exclusive of a writer.
TEST_F(ReadWriteMutexTest, writeWrite) {
    // Take mutex to wait for work thread signals.
    boost::shared_ptr<std::thread> thread;
    {
        unique_lock<mutex> started_lock(syncw_.started_mtx);

        // Create a work thread.
        thread = boost::make_shared<std::thread>([this](){ writer(rw_mutex_, syncw_); });

        // Wait work thread to start.
        syncw_.started_cv.wait(started_lock, [this](){ return syncw_.started; });

        unique_lock<mutex> done_lock(syncw_.done_mtx);

        {
            // Enter a write lock guard.
            WriteLockGuard rwlock(rw_mutex_);

            // Signal the thread to work.
            {
                lock_guard<mutex> work_lock(syncw_.work_mtx);
                syncw_.work = true;
            }
            syncw_.work_cv.notify_one();

            // Verify the work thread is waiting for the write lock.
            cout << "pausing for one second" << std::endl;
            bool ret = syncw_.done_cv.wait_for(done_lock, chrono::seconds(1), [this](){ return syncw_.done; });

            EXPECT_FALSE(syncw_.done);
            EXPECT_FALSE(ret);

            // Exiting the write lock guard.
        }

        // Wait thread to hold the write lock.
        syncw_.done_cv.wait(done_lock, [this](){ return syncw_.done; });
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncw_.terminate_mtx);
        syncw_.terminate = true;
    }
    syncw_.terminate_cv.notify_one();

    // Join the thread.
    thread->join();
}

// Verify that a writer has the preference.
TEST_F(ReadWriteMutexTest, readWriteRead) {
    // Take mutex to wait for work thread signals.
    boost::shared_ptr<std::thread> threadw;
    {
        unique_lock<mutex> startedw_lock(syncw_.started_mtx);

        // First thread is a writer.
        threadw = boost::make_shared<std::thread>([this](){ writer(rw_mutex_, syncw_); });

        // Wait work thread to start.
        syncw_.started_cv.wait(startedw_lock, [this](){ return syncw_.started; });
    }

    boost::shared_ptr<std::thread> threadr;
    {
        unique_lock<mutex> startedr_lock(syncr_.started_mtx);

        // Second thread is a reader.
        threadr = boost::make_shared<std::thread>([this](){ reader(rw_mutex_, syncr_); });

        // Wait work thread to start.
        syncr_.started_cv.wait(startedr_lock, [this](){ return syncr_.started; });
    }

    {
        unique_lock<mutex> donew_lock(syncw_.done_mtx);
        {
            // Enter a read lock guard.
            ReadLockGuard rwlock(rw_mutex_);

            // Signal the writer thread to work.
            {
                lock_guard<mutex> work_lock(syncw_.work_mtx);
                syncw_.work = true;
            }
            syncw_.work_cv.notify_one();

            // Verify the writer thread is waiting for the write lock.
            cout << "pausing for one second" << std::endl;
            bool ret = syncw_.done_cv.wait_for(donew_lock, chrono::seconds(1), [this](){ return syncw_.done; });

            EXPECT_FALSE(syncw_.done);
            EXPECT_FALSE(ret);

            {
                unique_lock<mutex> doner_lock(syncr_.done_mtx);

                // Signal the reader thread to work.
                {
                    lock_guard<mutex> work_lock(syncr_.work_mtx);
                    syncr_.work = true;
                }
                syncr_.work_cv.notify_one();

                // Verify the reader thread is waiting for the read lock.
                cout << "pausing for one second" << std::endl;
                bool ret = syncr_.done_cv.wait_for(doner_lock, chrono::seconds(1), [this](){ return syncr_.done; });

                EXPECT_FALSE(syncr_.done);
                EXPECT_FALSE(ret);
            }
            // Exiting the read lock guard.
        }

        {
            unique_lock<mutex> doner_lock(syncr_.done_mtx);
            // Verify the reader thread is still waiting for the read lock.
            cout << "pausing for one second" << std::endl;
            bool ret = syncr_.done_cv.wait_for(doner_lock, chrono::seconds(1), [this](){ return syncr_.done; });

            EXPECT_FALSE(syncr_.done);
            EXPECT_FALSE(ret);
        }

        // Wait writer thread to hold the write lock.
        syncw_.done_cv.wait(donew_lock, [this](){ return syncw_.done; });
    }

    {
        unique_lock<mutex> doner_lock(syncr_.done_mtx);
        // Wait reader thread to hold the read lock.
        syncr_.done_cv.wait(doner_lock, [this](){ return syncr_.done; });
    }

    // Signal the writer thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncw_.terminate_mtx);
        syncw_.terminate = true;
    }
    syncw_.terminate_cv.notify_one();

    // Join the writer thread.
    threadw->join();

    // Signal the reader thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncr_.terminate_mtx);
        syncr_.terminate = true;
    }
    syncr_.terminate_cv.notify_one();

    // Join the reader thread.
    threadr->join();
}

}
