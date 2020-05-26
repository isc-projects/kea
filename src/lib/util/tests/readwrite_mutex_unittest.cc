// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/readwrite_mutex.h>

#include <gtest/gtest.h>

#include <iostream>
#include <thread>
#include <unistd.h>

using namespace isc::util;
using namespace std;

namespace {

// Verify basic read lock guard.
TEST(ReadWriteMutexTest, basicRead) {
    ReadWriteMutex rw_mutex;
    ReadLockGuard lock(rw_mutex);
}

// Verify basic write lock guard.
TEST(ReadWriteMutexTest, basicWrite) {
    ReadWriteMutex rw_mutex;
    WriteLockGuard lock(rw_mutex);
}

// Verify read lock guard using a thread.
TEST(ReadWriteMutexTest, read) {
    mutex mutex;
    ReadWriteMutex rw_mutex;
    bool started = false;
    bool work = false;
    bool done = false;
    bool terminate = false;

    // Create a thread.
    thread thread(
        [&mutex, &rw_mutex, &started, &work, &done, &terminate] ()
        mutable -> void {
            // Signal the thread started.
            {
                lock_guard<std::mutex> lock(mutex);
                started = true;
            }
            // Wait to work.
            for (;;) {
                bool ready = false;
                {
                    lock_guard<std::mutex> lock(mutex);
                    ready = work;
                }
                if (ready) {
                    break;
                }
                usleep(100);
            }
            {
                // Enter a read lock guard.
                ReadLockGuard rwlock(rw_mutex);
                {
                    // Signal the thread holds the guard.
                    lock_guard<std::mutex> lock(mutex);
                    done = true;
                }
                // Wait to terminate.
                for (;;) {
                    lock_guard<std::mutex> lock(mutex);
                    if (terminate) {
                        return;
                    }
                }
            }
        });

    // Wait thread to start.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = started;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to work.
    {
        lock_guard<std::mutex> lock(mutex);
        work = true;
    }

    // Wait thread to hold the read lock guard.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to terminate.
    {
        lock_guard<std::mutex> lock(mutex);
        terminate = true;
    }

    // Join the thread.
    thread.join();
}

// Verify write lock guard using a thread.
TEST(ReadWriteMutexTest, write) {
    mutex mutex;
    ReadWriteMutex rw_mutex;
    bool started = false;
    bool work = false;
    bool done = false;
    bool terminate = false;

    // Create a thread.
    thread thread(
        [&mutex, &rw_mutex, &started, &work, &done, &terminate] ()
        mutable -> void {
            // Signal the thread started.
            {
                lock_guard<std::mutex> lock(mutex);
                started = true;
            }
            // Wait to work.
            for (;;) {
                bool ready = false;
                {
                    lock_guard<std::mutex> lock(mutex);
                    ready = work;
                }
                if (ready) {
                    break;
                }
                usleep(100);
            }
            {
                // Enter a write lock guard.
                WriteLockGuard rwlock(rw_mutex);
                {
                    // Signal the thread holds the guard.
                    lock_guard<std::mutex> lock(mutex);
                    done = true;
                }
                // Wait to terminate.
                for (;;) {
                    lock_guard<std::mutex> lock(mutex);
                    if (terminate) {
                        return;
                    }
                }
            }
        });

    // Wait thread to start.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = started;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to work.
    {
        lock_guard<std::mutex> lock(mutex);
        work = true;
    }

    // Wait thread to hold the write lock guard.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to terminate.
    {
        lock_guard<std::mutex> lock(mutex);
        terminate = true;
    }

    // Join the thread.
    thread.join();
}

// Verify read lock guard can be acquired by multiple threads.
TEST(ReadWriteMutexTest, readRead) {
    mutex mutex;
    ReadWriteMutex rw_mutex;
    bool started = false;
    bool work = false;
    bool done = false;
    bool terminate = false;

    // Create a thread.
    thread thread(
        [&mutex, &rw_mutex, &started, &work, &done, &terminate] ()
        mutable -> void {
            // Signal the thread started.
            {
                lock_guard<std::mutex> lock(mutex);
                started = true;
            }
            // Wait to work.
            for (;;) {
                bool ready = false;
                {
                    lock_guard<std::mutex> lock(mutex);
                    ready = work;
                }
                if (ready) {
                    break;
                }
                usleep(100);
            }
            {
                // Enter a read lock guard.
                ReadLockGuard rwlock(rw_mutex);
                {
                    // Signal the thread holds the guard.
                    lock_guard<std::mutex> lock(mutex);
                    done = true;
                }
                // Wait to terminate.
                for (;;) {
                    lock_guard<std::mutex> lock(mutex);
                    if (terminate) {
                        return;
                    }
                }
            }
        });

    // Enter a read load guard.
    ReadLockGuard rwlock(rw_mutex);

    // Wait thread to start..
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = started;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to work.
    {
        lock_guard<std::mutex> lock(mutex);
        work = true;
    }

    // Wait thread to hold the read lock guard.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to terminate.
    {
        lock_guard<std::mutex> lock(mutex);
        terminate = true;
    }

    // Join the thread.
    thread.join();
}

// Verify write lock guard is exclusive of a reader.
TEST(ReadWriteMutexTest, readWrite) {
    mutex mutex;
    ReadWriteMutex rw_mutex;
    bool started = false;
    bool work = false;
    bool done = false;
    bool terminate = false;

    // Create a thread.
    thread thread(
        [&mutex, &rw_mutex, &started, &work, &done, &terminate] ()
        mutable -> void {
            // Signal the thread started.
            {
                lock_guard<std::mutex> lock(mutex);
                started = true;
            }
            // Wait to work.
            for (;;) {
                bool ready = false;
                {
                    lock_guard<std::mutex> lock(mutex);
                    ready = work;
                }
                if (ready) {
                    break;
                }
                usleep(100);
            }
            {
                // Enter a write lock guard.
                WriteLockGuard rwlock(rw_mutex);
                {
                    // Signal the thread holds the guard.
                    lock_guard<std::mutex> lock(mutex);
                    done = true;
                }
                // Wait to terminate.
                for (;;) {
                    lock_guard<std::mutex> lock(mutex);
                    if (terminate) {
                        return;
                    }
                }
            }
        });

    // Wait thread to start.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = started;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    {
        // Enter a read load guard.
        ReadLockGuard rwlock(rw_mutex);

        // Signal the thread to work.
        {
            lock_guard<std::mutex> lock(mutex);
            work = true;
        }

        cout << "pausing for one second\n";
        usleep(1000000);
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done;
        }
        EXPECT_FALSE(ready);
    }

    // Wait thread to hold the write lock guard.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to terminate.
    {
        lock_guard<std::mutex> lock(mutex);
        terminate = true;
    }

    // Join the thread.
    thread.join();
}

// Verify write lock guard is exclusive of a writer.
TEST(ReadWriteMutexTest, writeWrite) {
    mutex mutex;
    ReadWriteMutex rw_mutex;
    bool started = false;
    bool work = false;
    bool done = false;
    bool terminate = false;

    // Create a thread.
    thread thread(
        [&mutex, &rw_mutex, &started, &work, &done, &terminate] ()
        mutable -> void {
            // Signal the thread started.
            {
                lock_guard<std::mutex> lock(mutex);
                started = true;
            }
            // Wait to work.
            for (;;) {
                bool ready = false;
                {
                    lock_guard<std::mutex> lock(mutex);
                    ready = work;
                }
                if (ready) {
                    break;
                }
                usleep(100);
            }
            {
                // Enter a write lock guard.
                WriteLockGuard rwlock(rw_mutex);
                {
                    // Signal the thread holds the guard.
                    lock_guard<std::mutex> lock(mutex);
                    done = true;
                }
                // Wait to terminate.
                for (;;) {
                    lock_guard<std::mutex> lock(mutex);
                    if (terminate) {
                        return;
                    }
                }
            }
        });

    // Wait thread to start.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = started;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    {
        // Enter a write lock guard.
        WriteLockGuard rwlock(rw_mutex);

        // Signal the thread to work.
        {
            lock_guard<std::mutex> lock(mutex);
            work = true;
        }

        cout << "pausing for one second\n";
        usleep(1000000);
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done;
        }
        EXPECT_FALSE(ready);
    }

    // Wait thread to hold the write lock guard.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the thread to terminate.
    {
        lock_guard<std::mutex> lock(mutex);
        terminate = true;
    }

    // Join the thread.
    thread.join();
}

// Verify that a writer has the preference.
TEST(ReadWriteMutexTest, readWriteRead) {
    mutex mutex;
    ReadWriteMutex rw_mutex;
    bool started1 = false;
    bool started2 = false;
    bool work1 = false;
    bool work2 = false;
    bool done1 = false;
    bool done2 = false;
    bool terminate1 = false;
    bool terminate2 = false;

    // First thread is a writer.
    thread thread1(
        [&mutex, &rw_mutex, &started1, &work1, &done1, &terminate1] ()
        mutable -> void {
            // Signal the thread started.
            {
                lock_guard<std::mutex> lock(mutex);
                started1 = true;
            }
            // Wait to work.
            for (;;) {
                bool ready = false;
                {
                    lock_guard<std::mutex> lock(mutex);
                    ready = work1;
                }
                if (ready) {
                    break;
                }
                usleep(100);
            }
            {
                // Enter a write lock guard.
                WriteLockGuard rwlock(rw_mutex);
                {
                    // Signal the thread holds the guard.
                    lock_guard<std::mutex> lock(mutex);
                    done1 = true;
                }
                // Wait to terminate.
                for (;;) {
                    lock_guard<std::mutex> lock(mutex);
                    if (terminate1) {
                        return;
                    }
                }
            }
        });

    // Second thread is a writer.
    thread thread2(
        [&mutex, &rw_mutex, &started2, &work2, &done2, &terminate2] ()
        mutable -> void {
            // Signal the thread started.
            {
                lock_guard<std::mutex> lock(mutex);
                started2 = true;
            }
            // Wait to work.
            for (;;) {
                bool ready = false;
                {
                    lock_guard<std::mutex> lock(mutex);
                    ready = work2;
                }
                if (ready) {
                    break;
                }
                usleep(100);
            }
            {
                // Enter a read lock guard.
                ReadLockGuard rwlock(rw_mutex);
                {
                    // Signal the thread holds the guard.
                    lock_guard<std::mutex> lock(mutex);
                    done2 = true;
                }
                // Wait to terminate.
                for (;;) {
                    lock_guard<std::mutex> lock(mutex);
                    if (terminate2) {
                        return;
                    }
                }
            }
        });

    // Wait threads to start.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = started1 && started2;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    {
        // Enter a read load guard.
        ReadLockGuard rwlock(rw_mutex);

        // Signal the writer thread to work.
        {
            lock_guard<std::mutex> lock(mutex);
            work1 = true;
        }

        cout << "pausing for one second\n";
        usleep(1000000);
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done1;
        }
        EXPECT_FALSE(ready);

        // Signal the reader thread to work.
        {
            lock_guard<std::mutex> lock(mutex);
            work2 = true;
        }

        cout << "pausing for one second\n";
        usleep(1000000);
        ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done2;
        }
        EXPECT_FALSE(ready);
    }

    cout << "pausing for one second\n";
    usleep(1000000);
    {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done2;
        }
        EXPECT_FALSE(ready);
    }
    // Signal the writer thread to terminate.
    {
        lock_guard<std::mutex> lock(mutex);
        terminate1 = true;
    }

    // Join the writer thread.
    thread1.join();

    // Wait reader thread to hold the read lock guard.
    for (;;) {
        bool ready = false;
        {
            lock_guard<std::mutex> lock(mutex);
            ready = done2;
        }
        if (ready) {
            break;
        }
        usleep(100);
    }

    // Signal the reader thread to terminate.
    {
        lock_guard<std::mutex> lock(mutex);
        terminate2 = true;
    }

    // Join the thread.
    thread2.join();
}

}
