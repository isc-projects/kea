// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <dhcpsrv/thread_pool.h>

using namespace isc::dhcp;
using namespace std;

namespace {

/// @brief Test Fixture for testing isc::dhcp::ThreadPool
class ThreadPoolTest : public ::testing::Test {
public:
    ThreadPoolTest() : thread_count_(0), count_(0), wait_(false) {
    }

    /// @brief task function which registers the thread id and signals main
    /// thread to wake
    void runAndWait() {
        run();
        unique_lock<mutex> lk(wait_mutex_);
        wait_cv_.wait(lk, [&]{ return (wait() == false); });
    }

    void run() {
        // make sure this thread has started and it is accounted for
        lock_guard<mutex> lk(mutex_);
        auto id = this_thread::get_id();
        ids_.emplace(id);
        ++count_;
        history_[id].push_back(count_);
        // wake main thread if it is waiting for this thread to start
        cv_.notify_all();
    }

    void reset(uint32_t thread_count) {
        stopThreads();
        thread_count_ = thread_count;
        count_ = 0;
        wait_ = true;
        history_.clear();
    }

    void waitThreads(uint32_t thread_count, bool start = false) {
        // make sure we have all threads running when performing all the checks
        unique_lock<mutex> lck(mutex_);
        if (start) {
            startThreads(thread_count);
        }
        cv_.wait(lck, [&]{ return (count() == thread_count); });
    }

    void startThreads(uint32_t thread_count) {
        for (uint32_t i = 0; i < thread_count; ++i) {
            threads_.push_back(make_shared<std::thread>(&ThreadPoolTest::run, this));
        }
    }

    void stopThreads() {
        signalThreads();
        for (auto thread : threads_) {
            thread->join();
        }
        threads_.clear();
    }

    void signalThreads() {
        lock_guard<mutex> lk(wait_mutex_);
        if (wait_) {
            // wake all thread if waiting for main thread
            wait_cv_.notify_all();
        }
        wait_ = false;
    }

    uint32_t count() {
        return count_;
    }

    bool wait() {
        return wait_;
    }

    void checkRunHistory(uint32_t items_count) {
        uint32_t count = 0;
        for (auto element : history_) {
            count += element.second.size();
        }
        ASSERT_EQ(count, items_count);
    }

    uint32_t thread_count_;

    std::mutex mutex_;

    condition_variable cv_;

    std::mutex wait_mutex_;

    condition_variable wait_cv_;

    uint32_t count_;

    bool wait_;

    set<std::thread::id> ids_;

    map<std::thread::id, list<uint32_t>> history_;

    list<shared_ptr<std::thread>> threads_;
};

/// @brief test ThreadPool functionality
TEST_F(ThreadPoolTest, testCreateAndDestroy) {
    uint32_t items_count = 4;
    reset(items_count);
    ThreadPool::WorkItemCallBack call_back;

    ThreadPool thread_pool;
    ASSERT_EQ(thread_pool.count(), 0);

    // create tasks which block thread pool threads until signaled by main
    // to force all threads of the thread pool to run exactly one task
    call_back = std::bind(&ThreadPoolTest::runAndWait, this);

    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    ASSERT_EQ(thread_pool.count(), items_count);

    thread_pool.create(items_count, false);
    ASSERT_EQ(thread_pool.count(), 0);

    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    ASSERT_EQ(thread_pool.count(), items_count);

    thread_pool.destroy();
    ASSERT_EQ(thread_pool.count(), 0);

    thread_pool.create(items_count);

    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }

    waitThreads(items_count);
    ASSERT_EQ(thread_pool.count(), 0);
    ASSERT_EQ(ids_.size(), items_count);
    ASSERT_EQ(count(), items_count);

    checkRunHistory(items_count);

    signalThreads();

    thread_pool.destroy();
    ASSERT_EQ(thread_pool.count(), 0);

    reset(items_count);

    // create tasks which do not block the thread pool threads so that several
    // tasks can be run on the same thread and some of the threads never even
    // having a chance to run
    call_back = std::bind(&ThreadPoolTest::run, this);

    thread_pool.create(items_count);

    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }

    waitThreads(items_count);
    ASSERT_EQ(thread_pool.count(), 0);
    ASSERT_EQ(count(), items_count);

    checkRunHistory(items_count);
}

}  // namespace
