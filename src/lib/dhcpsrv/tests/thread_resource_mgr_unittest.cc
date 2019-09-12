// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <dhcpsrv/thread_resource_mgr.h>

#include <boost/noncopyable.hpp>

#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

using namespace isc::dhcp;
using namespace std;

namespace {

/// @brief test class to keep track of all constructed objects of a specific
/// class type
///
/// @template parameter class to make this functionality available for a wide
/// range of 'similar' but distinct classes
template <typename T>
class Resource : public boost::noncopyable {
public:
    /// @brief Constructor
    Resource() : data_() {
        lock_guard<std::mutex> lk(mutex_);
        // increase current number of instances of this class
        Resource::count_++;
        // increase the total number of instances ever created
        Resource::created_count_++;
        // check that this instance is not found in the verification set
        EXPECT_TRUE(Resource::set_.find(&data_) == Resource::set_.end());
        // add this instance to the verification set
        Resource::set_.emplace(&data_);
    }

    /// @brief Destructor
    virtual ~Resource() {
        lock_guard<std::mutex> lk(mutex_);
        // decrease current number of instances of this class
        Resource::count_--;
        // increase the total number of instances ever destroyed
        Resource::destroyed_count_++;
        // check that this instance is found in the verification set
        EXPECT_FALSE(Resource::set_.find(&data_) == Resource::set_.end());
        // remove this instance from the verification set
        Resource::set_.erase(&data_);
    }

    /// @brief count number of current allocated instances of the class
    ///
    /// @return number of current allocated instances of the class
    static uint32_t count() {
        lock_guard<std::mutex> lk(mutex_);
        return Resource::count_;
    }

    /// @brief count number of class instances ever created
    ///
    /// @return number of class instances ever created
    static uint32_t createdCount() {
        lock_guard<std::mutex> lk(mutex_);
        return Resource::created_count_;
    }

    /// @brief count number of class instances ever destroyed
    ///
    /// @return number of class instances ever destroyed
    static uint32_t destroyedCount() {
        lock_guard<std::mutex> lk(mutex_);
        return Resource::destroyed_count_;
    }

    /// @brief reset all statistics for this class
    static void reset() {
        lock_guard<std::mutex> lk(mutex_);
        // reset all statistics for this class
        Resource::count_ = 0;
        Resource::created_count_ = 0;
        Resource::destroyed_count_ = 0;
        Resource::set_.clear();
    }

private:
    /// @brief data element
    T data_;

    /// @brief total number of instances at any given time
    static uint32_t count_;

    /// @brief total number of instances ever created
    static uint32_t created_count_;

    /// @brief total number of instances ever destroyed
    static uint32_t destroyed_count_;

    /// @brief mutex used to keep the internal state consistent
    static std::mutex mutex_;

    /// @brief set to hold the distinct identification data of each instance
    static std::set<T*> set_;
};

template <typename T>
uint32_t Resource<T>::count_;
template <typename T>
uint32_t Resource<T>::created_count_;
template <typename T>
uint32_t Resource<T>::destroyed_count_;
template <typename T>
std::mutex Resource<T>::mutex_;
template <typename T>
std::set<T*> Resource<T>::set_;

/// @brief Test Fixture for testing isc::dhcp::ThreadResourceMgr
class ThreadResourceMgrTest : public ::testing::Test {
public:
    /// @brief Constructor
    ThreadResourceMgrTest() : wait_thread_(false), wait_(false) {
    }

    /// @brief Destructor
    ~ThreadResourceMgrTest() {
    }

    /// @brief flag which indicates if main thread should wait for the test
    /// thread to start
    ///
    /// @return the wait flag
    bool waitThread() {
        return wait_thread_;
    }

    /// @brief flag which indicates if working thread should wait for main
    /// thread signal
    ///
    /// @return the wait flag
    bool waitMain() {
        return wait_;
    }

    /// @brief block main thread until testing thread has processed the task
    void wait() {
        unique_lock<mutex> lck(mutex_);
        // wait for the testing thread to process
        cv_.wait(lck, [&]{ return (waitThread() == false); });
    }


    /// @brief function used by main thread to unblock processing threads
    void signalThreads() {
        lock_guard<mutex> lk(wait_mutex_);
        // clear the wait flag so that threads will no longer wait for the main
        // thread signal
        wait_ = false;
        // wake all threads if waiting for main thread signal
        wait_cv_.notify_all();
    }

    /// @brief reset resource manager for the specific class type and perform
    /// sanity checks, then reset the wait flag so threads wait for the main
    /// thread signal to exit
    template <typename T>
    void reset() {
        // reset the resource manager
        get<T>() = make_shared<ThreadResourceMgr<Resource<T>>>();
        // perform sanity checks
        sanityCheck<T>();
        // reset the wait flag
        wait_ = true;
    }

    /// @brief reset wait thread flag
    void resetWaitThread() {
        wait_thread_ = true;
    }

    /// @brief check statistics
    ///
    /// @param expected_count check equality of this value with the number of
    /// class instances
    /// @param expected_created check equality of this value with the number of
    /// class instances ever created
    /// @param expected_destroyed check equality of this value with the number
    /// of class instances ever destroyed
    template <typename T>
    void checkInstances(uint32_t expected_count,
                        uint32_t expected_created,
                        uint32_t expected_destroyed) {
        ASSERT_EQ(Resource<T>::count(), expected_count);
        ASSERT_EQ(Resource<T>::createdCount(), expected_created);
        ASSERT_EQ(Resource<T>::destroyedCount(), expected_destroyed);
    }

    /// @brief get the instance of the resource manager responsible for a
    /// specific class type
    ///
    /// @return the resource manager responsible for a specific class type
    template <typename T>
    shared_ptr<ThreadResourceMgr<Resource<T>>> &get() {
        static shared_ptr<ThreadResourceMgr<Resource<T>>> container;
        return container;
    }

    /// @brief run function which accesses the resource allocated for the
    /// calling thread and verifies the class statistics
    /// @param expected_count check equality of this value with the number of
    /// class instances
    /// @param expected_created check equality of this value with the number of
    /// class instances ever created
    /// @param expected_destroyed check equality of this value with the number
    /// of class instances ever destroyed
    /// @param signal indicate if the function should wait for signal from main
    /// thread or exit immediately
    template <typename T>
    void run(uint32_t expected_count,
             uint32_t expected_created,
             uint32_t expected_destroyed,
             bool signal = false) {
        // get resource for this thread
        auto left = get<T>()->resource().get();
        // verify statistics
        checkInstances<T>(expected_count, expected_created, expected_destroyed);
        // get the resource for this thread once more
        auto right = get<T>()->resource().get();
        // check that it is the same resource
        ASSERT_EQ(left, right);
        // verify statistics which should have not changed on multiple
        // sequential requests for the same resource
        checkInstances<T>(expected_count, expected_created, expected_destroyed);

        {
            // make sure this thread has started
            lock_guard<mutex> lk(mutex_);
            // reset wait thread flag
            wait_thread_ = false;
            // wake main thread if it is waiting for this thread to process
            cv_.notify_all();
        }

        if (signal) {
            unique_lock<std::mutex> lk(wait_mutex_);
            // if specified, wait for signal from main thread
            wait_cv_.wait(lk, [&]{ return (waitMain() == false); });
        }
    }

private:
    /// @brief sanity check that the number of created instances is equal to the
    /// number of destroyed instances
    template <typename T>
    void sanityCheck() {
        // the number of created instances should match the number of destroyed
        // instances
        ASSERT_EQ(Resource<T>::createdCount(), Resource<T>::destroyedCount());
    }

    /// @brief mutex used to keep the internal state consistent
    std::mutex mutex_;

    /// @brief condition variable used to signal main thread that test thread
    /// has started processing
    condition_variable cv_;

    /// @brief mutex used to keep the internal state consistent
    /// related to the control of the main thread over the working threads exit
    std::mutex wait_mutex_;

    /// @brief condition variable used to signal working threads to exit
    condition_variable wait_cv_;

    /// @brief flag which indicates if main thread should wait for test thread
    /// to start
    bool wait_thread_;

    /// @brief flag which indicates if working thread should wait for main
    /// thread signal
    bool wait_;
};

/// @brief This test verifies that each thread can access it's own allocated
/// resource. Multiple threads are created and run in parallel. The checks are
/// done while threads are still running.
/// It is very important for the threads to run in parallel and not just run and
/// join the thread as this will cause newer threads to use the old thread id
/// and receive the same resource.
/// If destroying threads, the resource manager should also be reset.
TEST_F(ThreadResourceMgrTest, testThreadResources) {
    std::list<shared_ptr<std::thread>> threads;

    // reset statistics for uint_32 type
    reset<uint32_t>();
    // call run function on main thread and verify statistics
    run<uint32_t>(1, 1, 0);
    // configure wait for test thread
    resetWaitThread();
    // call run on a different thread and verify statistics
    threads.push_back(std::make_shared<std::thread>(std::bind(
        &ThreadResourceMgrTest::run<uint32_t>, this, 2, 2, 0, true)));
    // wait for the thread to process
    wait();
    // configure wait for test thread
    resetWaitThread();
    // call run again on a different thread and verify statistics
    threads.push_back(std::make_shared<std::thread>(std::bind(
        &ThreadResourceMgrTest::run<uint32_t>, this, 3, 3, 0, true)));
    // wait for the thread to process
    wait();
    // signal all threads
    signalThreads();
    // wait for all threads to finish
    for (auto &thread : threads) {
        thread->join();
    }
    // reset statistics for uint_32 type
    reset<uint32_t>();
    // verify statistics 0 instances, 3 created, 3 destroyed
    checkInstances<uint32_t>(0, 3, 3);

    threads.clear();

    // reset statistics for bool type
    reset<bool>();
    // call run function on main thread and verify statistics
    run<bool>(1, 1, 0);
    // configure wait for test thread
    resetWaitThread();
    // call run on a different thread and verify statistics
    threads.push_back(std::make_shared<std::thread>(std::bind(
        &ThreadResourceMgrTest::run<bool>, this, 2, 2, 0, true)));
    // wait for the thread to process
    wait();
    // configure wait for test thread
    resetWaitThread();
    // call run again on a different thread and verify statistics
    threads.push_back(std::make_shared<std::thread>(std::bind(
        &ThreadResourceMgrTest::run<bool>, this, 3, 3, 0, true)));
    // wait for the thread to process
    wait();
    // signal all threads
    signalThreads();
    // wait for all threads to finish
    for (auto &thread : threads) {
        thread->join();
    }
    // reset statistics for bool type
    reset<bool>();
    // verify statistics 0 instances, 3 created, 3 destroyed
    checkInstances<bool>(0, 3, 3);
}

}  // namespace
