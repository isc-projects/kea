// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/readwrite_mutex.h>

#include <gtest/gtest.h>

#include <chrono>
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
    ReadWriteMutex rw_mutex;

    // Synchronization objects for the work thread.
    struct {
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
    } sync;

    // Take mutexes for from work thread signals.
    unique_lock<mutex> started_lock(sync.started_mtx);
    unique_lock<mutex> done_lock(sync.done_mtx);

    // Create a work thread.
    thread thread([&rw_mutex, &sync] () mutable -> void {
        // Take mutexes for from main thread signals.
        unique_lock<mutex> work_lock(sync.work_mtx);
        unique_lock<mutex> terminate_lock(sync.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(sync.started_mtx);
            sync.started = true;
        }
        sync.started_cv.notify_one();

        // Wait for work.
        while (!sync.work) {
            sync.work_cv.wait(work_lock);
        }

        // Enter a read lock guard.
        ReadLockGuard rwlock(rw_mutex);

        // Signal the thread holds the guard.
        {
            lock_guard<mutex> done_lock(sync.done_mtx);
            sync.done = true;
        }
        sync.done_cv.notify_one();

        // Wait to terminate.
        while (!sync.terminate) {
            sync.terminate_cv.wait(terminate_lock);
        }
    });

    // Wait work thread to start.
    while (!sync.started) {
        sync.started_cv.wait(started_lock);
    }

    // Signal the thread to work.
    {
        lock_guard<mutex> work_lock(sync.work_mtx);
        sync.work = true;
    }
    sync.work_cv.notify_one();

    // Wait thread to hold the read lock.
    while (!sync.done) {
        sync.done_cv.wait(done_lock);
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(sync.terminate_mtx);
        sync.terminate = true;
    }
    sync.terminate_cv.notify_one();

    // Join the thread.
    thread.join();
}

// Verify write lock guard using a thread.
TEST(ReadWriteMutexTest, write) {
    ReadWriteMutex rw_mutex;

    // Synchronization objects for the work thread.
    struct {
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
    } sync;

    // Take mutexes for from work thread signals.
    unique_lock<mutex> started_lock(sync.started_mtx);
    unique_lock<mutex> done_lock(sync.done_mtx);

    // Create a work thread.
    thread thread([&rw_mutex, &sync] () mutable -> void {
        // Take mutexes for from main thread signals.
        unique_lock<mutex> work_lock(sync.work_mtx);
        unique_lock<mutex> terminate_lock(sync.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(sync.started_mtx);
            sync.started = true;
        }
        sync.started_cv.notify_one();

        // Wait for work.
        while (!sync.work) {
            sync.work_cv.wait(work_lock);
        }

        // Enter a write lock guard.
        WriteLockGuard rwlock(rw_mutex);

        // Signal the thread holds the guard.
        {
            lock_guard<mutex> done_lock(sync.done_mtx);
            sync.done = true;
        }
        sync.done_cv.notify_one();

        // Wait to terminate.
        while (!sync.terminate) {
            sync.terminate_cv.wait(terminate_lock);
        }
    });

    // Wait work thread to start.
    while (!sync.started) {
        sync.started_cv.wait(started_lock);
    }

    // Signal the thread to work.
    {
        lock_guard<mutex> work_lock(sync.work_mtx);
        sync.work = true;
    }
    sync.work_cv.notify_one();

    // Wait thread to hold the write lock.
    while (!sync.done) {
        sync.done_cv.wait(done_lock);
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(sync.terminate_mtx);
        sync.terminate = true;
    }
    sync.terminate_cv.notify_one();

    // Join the thread.
    thread.join();
}

// Verify read lock guard can be acquired by multiple threads.
TEST(ReadWriteMutexTest, readRead) {
    ReadWriteMutex rw_mutex;

    // Synchronization objects for the work thread.
    struct {
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
    } sync;

    // Take mutexes for from work thread signals.
    unique_lock<mutex> started_lock(sync.started_mtx);
    unique_lock<mutex> done_lock(sync.done_mtx);

    // Create a work thread.
    thread thread([&rw_mutex, &sync] () mutable -> void {
        // Take mutexes for from main thread signals.
        unique_lock<mutex> work_lock(sync.work_mtx);
        unique_lock<mutex> terminate_lock(sync.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(sync.started_mtx);
            sync.started = true;
        }
        sync.started_cv.notify_one();

        // Wait for work.
        while (!sync.work) {
            sync.work_cv.wait(work_lock);
        }

        // Enter a read lock guard.
        ReadLockGuard rwlock(rw_mutex);

        // Signal the thread holds the guard.
        {
            lock_guard<mutex> done_lock(sync.done_mtx);
            sync.done = true;
        }
        sync.done_cv.notify_one();

        // Wait to terminate.
        while (!sync.terminate) {
            sync.terminate_cv.wait(terminate_lock);
        }
    });

    // Enter a read load guard.
    ReadLockGuard rwlock(rw_mutex);

    // Wait work thread to start.
    while (!sync.started) {
        sync.started_cv.wait(started_lock);
    }

    // Signal the thread to work.
    {
        lock_guard<mutex> work_lock(sync.work_mtx);
        sync.work = true;
    }
    sync.work_cv.notify_one();

    // Wait thread to hold the read lock.
    while (!sync.done) {
        sync.done_cv.wait(done_lock);
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(sync.terminate_mtx);
        sync.terminate = true;
    }
    sync.terminate_cv.notify_one();

    // Join the thread.
    thread.join();
}

// Verify write lock guard is exclusive of a reader.
TEST(ReadWriteMutexTest, readWrite) {
    ReadWriteMutex rw_mutex;

    // Synchronization objects for the work thread.
    struct {
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
    } sync;

    // Take mutexes for from work thread signals.
    unique_lock<mutex> started_lock(sync.started_mtx);
    unique_lock<mutex> done_lock(sync.done_mtx);

    // Create a work thread.
    thread thread([&rw_mutex, &sync] () mutable -> void {
        // Take mutexes for from main thread signals.
        unique_lock<mutex> work_lock(sync.work_mtx);
        unique_lock<mutex> terminate_lock(sync.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(sync.started_mtx);
            sync.started = true;
        }
        sync.started_cv.notify_one();

        // Wait for work.
        while (!sync.work) {
            sync.work_cv.wait(work_lock);
        }

        // Enter a write lock guard.
        WriteLockGuard rwlock(rw_mutex);

        // Signal the thread holds the guard.
        {
            lock_guard<mutex> done_lock(sync.done_mtx);
            sync.done = true;
        }
        sync.done_cv.notify_one();

        // Wait to terminate.
        while (!sync.terminate) {
            sync.terminate_cv.wait(terminate_lock);
        }
    });

    // Wait work thread to start.
    while (!sync.started) {
        sync.started_cv.wait(started_lock);
    }

    {
        // Enter a read load guard.
        ReadLockGuard rwlock(rw_mutex);

        // Signal the thread to work.
        {
            lock_guard<mutex> work_lock(sync.work_mtx);
            sync.work = true;
        }
        sync.work_cv.notify_one();

        // Verify the work thread is waiting for the write lock.
        cout << "pausing for one second\n";
        bool timeout = false;
        while (!timeout && !sync.done) {
            auto one_sec = chrono::seconds(1);
            auto status = sync.done_cv.wait_for(done_lock, one_sec);
            if (status == cv_status::timeout) {
                timeout = true;
            }
        }

        EXPECT_FALSE(sync.done);
        EXPECT_TRUE(timeout);

        // Exiting the read lock guard.
    }

    // Wait thread to hold the write lock.
    while (!sync.done) {
        sync.done_cv.wait(done_lock);
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(sync.terminate_mtx);
        sync.terminate = true;
    }
    sync.terminate_cv.notify_one();

    // Join the thread.
    thread.join();
}

// Verify write lock guard is exclusive of a writer.
TEST(ReadWriteMutexTest, writeWrite) {
    ReadWriteMutex rw_mutex;

    // Synchronization objects for the work thread.
    struct {
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
    } sync;

    // Take mutexes for from work thread signals.
    unique_lock<mutex> started_lock(sync.started_mtx);
    unique_lock<mutex> done_lock(sync.done_mtx);

    // Create a work thread.
    thread thread([&rw_mutex, &sync] () mutable -> void {
        // Take mutexes for from main thread signals.
        unique_lock<mutex> work_lock(sync.work_mtx);
        unique_lock<mutex> terminate_lock(sync.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(sync.started_mtx);
            sync.started = true;
        }
        sync.started_cv.notify_one();

        // Wait for work.
        while (!sync.work) {
            sync.work_cv.wait(work_lock);
        }

        // Enter a write lock guard.
        WriteLockGuard rwlock(rw_mutex);

        // Signal the thread holds the guard.
        {
            lock_guard<mutex> done_lock(sync.done_mtx);
            sync.done = true;
        }
        sync.done_cv.notify_one();

        // Wait to terminate.
        while (!sync.terminate) {
            sync.terminate_cv.wait(terminate_lock);
        }
    });

    // Wait work thread to start.
    while (!sync.started) {
        sync.started_cv.wait(started_lock);
    }

    {
        // Enter a write lock guard.
        WriteLockGuard rwlock(rw_mutex);

        // Signal the thread to work.
        {
            lock_guard<mutex> work_lock(sync.work_mtx);
            sync.work = true;
        }
        sync.work_cv.notify_one();

        // Verify the work thread is waiting for the write lock.
        cout << "pausing for one second\n";
        bool timeout = false;
        while (!timeout && !sync.done) {
            auto one_sec = chrono::seconds(1);
            auto status = sync.done_cv.wait_for(done_lock, one_sec);
            if (status == cv_status::timeout) {
                timeout = true;
            }
        }

        EXPECT_FALSE(sync.done);
        EXPECT_TRUE(timeout);

        // Exiting the write lock guard.
    }

    // Wait thread to hold the write lock.
    while (!sync.done) {
        sync.done_cv.wait(done_lock);
    }

    // Signal the thread to terminate.
    {
        lock_guard<mutex> terminate_lock(sync.terminate_mtx);
        sync.terminate = true;
    }
    sync.terminate_cv.notify_one();

    // Join the thread.
    thread.join();
}

// Verify that a writer has the preference.
TEST(ReadWriteMutexTest, readWriteRead) {
    ReadWriteMutex rw_mutex;

    // Synchronization objects for the work threads.
    struct {
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
    } syncw, syncr;

    // Take mutexes for from work thread signals.
    unique_lock<mutex> startedw_lock(syncw.started_mtx);
    unique_lock<mutex> startedr_lock(syncr.started_mtx);
    unique_lock<mutex> donew_lock(syncw.done_mtx);
    unique_lock<mutex> doner_lock(syncr.done_mtx);

    // First thread is a writer.
    thread threadw([&rw_mutex, &syncw] () mutable -> void {
        // Take mutexes for from main thread signals.
        unique_lock<mutex> work_lock(syncw.work_mtx);
        unique_lock<mutex> terminate_lock(syncw.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(syncw.started_mtx);
            syncw.started = true;
        }
        syncw.started_cv.notify_one();

        // Wait for work.
        while (!syncw.work) {
            syncw.work_cv.wait(work_lock);
        }

        // Enter a write lock guard.
        WriteLockGuard rwlock(rw_mutex);

        // Signal the thread holds the guard.
        {
            lock_guard<mutex> done_lock(syncw.done_mtx);
            syncw.done = true;
        }
        syncw.done_cv.notify_one();

        // Wait to terminate.
        while (!syncw.terminate) {
            syncw.terminate_cv.wait(terminate_lock);
        }
    });

    // Second thread is a reader.
    thread threadr([&rw_mutex, &syncr] () mutable -> void {
        // Take mutexes for from main thread signals.
        unique_lock<mutex> work_lock(syncr.work_mtx);
        unique_lock<mutex> terminate_lock(syncr.terminate_mtx);

        // Signal the thread started.
        {
            lock_guard<mutex> lock(syncr.started_mtx);
            syncr.started = true;
        }
        syncr.started_cv.notify_one();

        // Wait for work.
        while (!syncr.work) {
            syncr.work_cv.wait(work_lock);
        }

        // Enter a read lock guard.
        ReadLockGuard rwlock(rw_mutex);

        // Signal the thread holds the guard.
        {
            lock_guard<mutex> done_lock(syncr.done_mtx);
            syncr.done = true;
        }
        syncr.done_cv.notify_one();

        // Wait to terminate.
        while (!syncr.terminate) {
            syncr.terminate_cv.wait(terminate_lock);
        }
    });

    // Wait threads to started.
    while (!syncw.started) {
        syncw.started_cv.wait(startedw_lock);
    }
    while (!syncr.started) {
        syncr.started_cv.wait(startedr_lock);
    }

    {
        // Enter a read load guard.
        ReadLockGuard rwlock(rw_mutex);

        // Signal the writer thread to work.
        {
            lock_guard<mutex> work_lock(syncw.work_mtx);
            syncw.work = true;
        }
        syncw.work_cv.notify_one();

        // Verify the writer thread is waiting for the write lock.
        cout << "pausing for one second\n";
        bool timeout = false;
        while (!timeout && !syncw.done) {
            auto one_sec = chrono::seconds(1);
            auto status = syncw.done_cv.wait_for(donew_lock, one_sec);
            if (status == cv_status::timeout) {
                timeout = true;
            }
        }

        EXPECT_FALSE(syncw.done);
        EXPECT_TRUE(timeout);

        // Signal the reader thread to work.
        {
            lock_guard<mutex> work_lock(syncr.work_mtx);
            syncr.work = true;
        }
        syncr.work_cv.notify_one();

        // Verify the reader thread is waiting for the rea lock.
        cout << "pausing for one second\n";
        timeout = false;
        while (!timeout && !syncr.done) {
            auto one_sec = chrono::seconds(1);
            auto status = syncr.done_cv.wait_for(doner_lock, one_sec);
            if (status == cv_status::timeout) {
                timeout = true;
            }
        }

        EXPECT_FALSE(syncr.done);
        EXPECT_TRUE(timeout);

        // Exiting the read lock guard.
    }

    // Verify the reader thread is still waiting for the read lock.
    cout << "pausing for one second\n";
    bool timeout = false;
    while (!timeout && !syncr.done) {
        auto one_sec = chrono::seconds(1);
        auto status = syncr.done_cv.wait_for(doner_lock, one_sec);
        if (status == cv_status::timeout) {
            timeout = true;
        }
    }

    EXPECT_FALSE(syncr.done);
    EXPECT_TRUE(timeout);

    // Wait writer thread to hold the write lock.
    while (!syncw.done) {
        syncw.done_cv.wait(donew_lock);
    }

    // Signal the writer thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncw.terminate_mtx);
        syncw.terminate = true;
    }
    syncw.terminate_cv.notify_one();

    // Join the writer thread.
    threadw.join();

    // Wait reader thread to hold the read lock.
    while (!syncr.done) {
        syncr.done_cv.wait(doner_lock);
    }

    // Signal the reader thread to terminate.
    {
        lock_guard<mutex> terminate_lock(syncr.terminate_mtx);
        syncr.terminate = true;
    }
    syncr.terminate_cv.notify_one();

    // Join the writer thread.
    threadr.join();
}

}
