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
    /// @brief Constructor
    ThreadPoolTest() : thread_count_(0), count_(0), wait_(false) {
    }

    /// @brief task function which registers the thread id and signals main
    /// thread to stop waiting and then waits for main thread to signal to exit
    void runAndWait() {
        // run task
        run();
        // wait for main thread signal to exit
        unique_lock<mutex> lk(wait_mutex_);
        wait_cv_.wait(lk, [&]{ return (wait() == false); });
    }

    /// @brief task function which registers the thread id and signals main
    /// thread to stop waiting
    void run() {
        // make sure this thread has started and it is accounted for
        lock_guard<mutex> lk(mutex_);
        auto id = this_thread::get_id();
        // register this thread as doing work on items
        ids_.emplace(id);
        // finish task
        ++count_;
        // register this task on the history of this thread
        history_[id].push_back(count_);
        // wake main thread if it is waiting for this thread to process
        cv_.notify_all();
    }

    /// @brief reset all counters and internal test state
    void reset(uint32_t thread_count) {
        // stop test threads
        stopThreads();
        // reset the internal state of the test
        thread_count_ = thread_count;
        count_ = 0;
        wait_ = true;
        history_.clear();
    }

    /// @brief start test threads and block main thread until all tasks have
    /// been processed
    ///
    /// @param thread_count number of threads to be started
    /// @param items_count number of items to wait for being processed
    /// @param start create processing threads
    /// @param signal give main thread control over the threads exit
    void waitTasks(uint32_t thread_count, uint32_t items_count,
                   bool start = false, bool signal = true) {
        // make sure we have all threads running when performing all the checks
        unique_lock<mutex> lck(mutex_);
        if (start) {
            // start test threads if explicitly specified
            startThreads(thread_count, signal);
        }
        // wait for the threads to process all the items
        cv_.wait(lck, [&]{ return (count() == items_count); });
    }

    /// @brief start test threads
    ///
    /// @param thread_count number of threads to be started
    /// @param signal give main thread control over the threads exit
    void startThreads(uint32_t thread_count, bool signal = true) {
        // set default task function to wait for main thread signal
        auto runFunction = &ThreadPoolTest::runAndWait;
        if (!signal) {
            // set the task function to finish immediately
            runFunction = &ThreadPoolTest::run;
        }
        // start test threads
        for (uint32_t i = 0; i < thread_count; ++i) {
            threads_.push_back(make_shared<std::thread>(runFunction, this));
        }
    }

    /// @brief stop test threads
    void stopThreads() {
        // signal threads that are waiting
        signalThreads();
        // wait for all test threads to exit
        for (auto thread : threads_) {
            thread->join();
        }
        // reset all threads
        threads_.clear();
    }

    /// @brief function used by main thread to unblock processing threads
    void signalThreads() {
        lock_guard<mutex> lk(wait_mutex_);
        // clear the wait flag so that threads will no longer wait for the main
        // thread signal
        wait_ = false;
        // wake all thread if waiting for main thread
        wait_cv_.notify_all();
    }

    /// @brief number of completed tasks
    ///
    /// @return the number of completed tasks
    uint32_t count() {
        return count_;
    }

    /// @brief flag which indicates if working thread should wait for main
    /// thread signal
    ///
    /// @return the wait flag
    bool wait() {
        return wait_;
    }

    /// @brief check the total number of tasks that have been processed
    /// Some of the tasks may have been run on the same thread and none may have
    /// been processed by other threads
    void checkRunHistory(uint32_t items_count) {
        uint32_t count = 0;
        // iterate over all threads history and count all the processed tasks
        for (auto element : history_) {
            count += element.second.size();
        }
        ASSERT_EQ(count, items_count);
    }

    /// @brief check the total number of threads that have processed tasks
    void checkIds(uint32_t count) {
        ASSERT_EQ(ids_.size(), count);
    }

private:
    /// @brief thread count used by the test
    uint32_t thread_count_;

    /// @brief mutex used to keep the internal state consistent
    std::mutex mutex_;

    /// @brief condition variable used to signal main thread that all threads
    /// have started processing
    condition_variable cv_;

    /// @brief mutex used to keep the internal state consistent
    /// related to the control of the main thread over the working threads exit
    std::mutex wait_mutex_;

    /// @brief condition variable used to signal working threads to exit
    condition_variable wait_cv_;

    /// @brief number of completed tasks
    uint32_t count_;

    /// @brief flag which indicates if working thread should wait for main
    /// thread signal
    bool wait_;

    /// @brief the set of thread ids which have completed tasks
    set<std::thread::id> ids_;

    /// @brief the list of completed tasks run by each thread
    map<std::thread::id, list<uint32_t>> history_;

    /// @brief the list of test threads
    list<shared_ptr<std::thread>> threads_;
};

/// @brief test ThreadPool add and count
TEST_F(ThreadPoolTest, testAddAndCount) {
    uint32_t items_count;
    ThreadPool::WorkItemCallBack call_back;
    ThreadPool thread_pool;
    ASSERT_EQ(thread_pool.count(), 0);
    ASSERT_EQ(thread_pool.size(), 0);

    items_count = 4;

    call_back = std::bind(&ThreadPoolTest::run, this);

    // add items to stopped thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    // the item count sould match
    ASSERT_EQ(thread_pool.count(), items_count);
}

/// @brief test ThreadPool create and destroy
TEST_F(ThreadPoolTest, testCreateAndDestroy) {
    uint32_t items_count;
    uint32_t thread_count;
    ThreadPool::WorkItemCallBack call_back;
    ThreadPool thread_pool;
    ASSERT_EQ(thread_pool.count(), 0);

    items_count = 4;
    thread_count = 4;
    // prepare setup
    reset(thread_count);

    // create tasks which block thread pool threads until signaled by main
    // to force all threads of the thread pool to run exactly one task
    call_back = std::bind(&ThreadPoolTest::runAndWait, this);

    // add items to stopped thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    // the item count should match
    ASSERT_EQ(thread_pool.count(), items_count);

    // calling create with false should not create threads and should remove all
    // queued items
    thread_pool.create(thread_count, false);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // add items to stopped thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    // the item count should match
    ASSERT_EQ(thread_pool.count(), items_count);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // calling destroy should clear all threads and should remove all queued
    // items
    thread_pool.destroy();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // do it once again to check if it works
    thread_pool.destroy();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // calling create with false should not create threads and should remove all
    // queued items
    thread_pool.create(thread_count, false);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // add items to stopped thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    // the item count should match
    ASSERT_EQ(thread_pool.count(), items_count);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // calling create with true should create threads and should remove all
    // queued items
    thread_pool.create(thread_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);

    // add items to running thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }

    // wait for all items to be processed
    waitTasks(thread_count, items_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);
    // as each thread pool thread is still waiting on main to unblock, each
    // thread should have been registered in ids list
    checkIds(items_count);
    // all items should have been processed
    ASSERT_EQ(count(), items_count);

    // check that the number of processed tasks matches the number of items
    checkRunHistory(items_count);

    // signal thread pool tasks to continue
    signalThreads();

    // calling destroy should clear all threads and should remove all queued
    // items
    thread_pool.destroy();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // do it once again to check if it works
    thread_pool.destroy();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    items_count = 64;
    thread_count = 16;
    // prepare setup
    reset(thread_count);

    // create tasks which do not block the thread pool threads so that several
    // tasks can be run on the same thread and some of the threads never even
    // having a chance to run
    call_back = std::bind(&ThreadPoolTest::run, this);

    // calling create with true should create threads and should remove all
    // queued items
    thread_pool.create(thread_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);

    // add items to running thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }

    // wait for all items to be processed
    waitTasks(thread_count, items_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);
    // all items should have been processed
    ASSERT_EQ(count(), items_count);

    // check that the number of processed tasks matches the number of items
    checkRunHistory(items_count);

    // calling destroy should clear all threads and should remove all queued
    // items
    thread_pool.destroy();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);
}

/// @brief test ThreadPool start and stop
TEST_F(ThreadPoolTest, testStartAndStop) {
    uint32_t items_count;
    uint32_t thread_count;
    ThreadPool::WorkItemCallBack call_back;
    ThreadPool thread_pool;
    ASSERT_EQ(thread_pool.count(), 0);

    items_count = 4;
    thread_count = 4;
    // prepare setup
    reset(thread_count);

    // create tasks which block thread pool threads until signaled by main
    // to force all threads of the thread pool to run exactly one task
    call_back = std::bind(&ThreadPoolTest::runAndWait, this);

    // calling start should create the threads and should keep the queued items
    thread_pool.start(thread_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);

    // do it once again to check if it works
    thread_pool.start(thread_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);

    // calling stop with false should clear all threads and should keep queued
    // items
    thread_pool.stop();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // do it once again to check if it works
    thread_pool.stop();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // add items to stopped thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    // the item count sould match
    ASSERT_EQ(thread_pool.count(), items_count);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // calling stop with false should clear all threads and should keep queued
    // items
    thread_pool.stop();
    // the item count sould match
    ASSERT_EQ(thread_pool.count(), items_count);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // calling stop with true should clear all threads and should remove all
    // queued items
    thread_pool.stop(true);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // calling start should create the threads and should keep the queued items
    thread_pool.start(thread_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), thread_count);

    // add items to running thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }

    // wait for all items to be processed
    waitTasks(thread_count, items_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);
    // as each thread pool thread is still waiting on main to unblock, each
    // thread should have been registered in ids list
    checkIds(items_count);
    // all items should have been processed
    ASSERT_EQ(count(), items_count);

    // check that the number of processed tasks matches the number of items
    checkRunHistory(items_count);

    // signal thread pool tasks to continue
    signalThreads();

    // calling stop with false should clear all threads and should keep queued
    // items
    thread_pool.stop();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    items_count = 64;
    thread_count = 16;
    // prepare setup
    reset(thread_count);

    // create tasks which do not block the thread pool threads so that several
    // tasks can be run on the same thread and some of the threads never even
    // having a chance to run
    call_back = std::bind(&ThreadPoolTest::run, this);

    // add items to stopped thread pool
    for (uint32_t i = 0; i < items_count; ++i) {
        thread_pool.add(call_back);
    }
    // the item count sould match
    ASSERT_EQ(thread_pool.count(), items_count);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);

    // calling start should create the threads and should keep the queued items
    thread_pool.start(thread_count);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);

    // wait for all items to be processed
    waitTasks(thread_count, items_count);
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should match
    ASSERT_EQ(thread_pool.size(), thread_count);
    // all items should have been processed
    ASSERT_EQ(count(), items_count);

    // check that the number of processed tasks matches the number of items
    checkRunHistory(items_count);

    // calling stop with false should clear all threads and should keep queued
    // items
    thread_pool.stop();
    // the item count sould be 0
    ASSERT_EQ(thread_pool.count(), 0);
    // the thread count should be 0
    ASSERT_EQ(thread_pool.size(), 0);
}

}  // namespace
