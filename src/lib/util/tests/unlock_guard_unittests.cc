// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <util/unlock_guard.h>
#include <exceptions/exceptions.h>

#include <mutex>
#include <thread>

using namespace isc::util;
using namespace std;

namespace {

/// @brief test mutex class used to check the internal state of a 'fictional'
/// mutex so that the functionality of the UnlockGuard can be tested
/// @note the test mutex can be recursive which means that a lock can be called
/// on the same thread and not resulting in a dead lock
class TestMutex {
public:
    /// @brief Constructor
    ///
    /// @param recursive sets the mutex as recursive mutex
    TestMutex(bool recursive = false) : lock_(0), dead_lock_(false),
        lock_count_(0), unlock_count_(0), recursive_(recursive) {
    }

    /// @brief lock the mutex
    void lock() {
        lock_guard<mutex> lk(mutex_);
        if (lock_ >= 1) {
            // mutex is already locked
            if (!recursive_) {
                // lock on a non-recursive mutex resulting in a dead lock
                dead_lock_ = true;
                isc_throw(isc::InvalidOperation,
                          "recursive lock on already locked mutex resulting in "
                          "dead lock");
            } else {
                // lock on a recursive mutex
                if (this_thread::get_id() != id_) {
                    // lock on a recursive mutex on a different thread resulting
                    // in a dead lock
                    dead_lock_ = true;
                    isc_throw(isc::InvalidOperation,
                              "recursive lock on a different thread on already "
                              "locked mutex resulting in dead lock");
                }
            }
        }
        // increment the total number of locks
        lock_count_++;
        // increment the lock state
        lock_++;
        // save the thread id
        id_ = this_thread::get_id();
    }

    /// @brief unlock the mutex
    void unlock() {
        lock_guard<mutex> lk(mutex_);
        if (lock_ <= 0) {
            // unlock an unlocked mutex
            isc_throw(isc::InvalidOperation, "unlock on non locked mutex "
                      "resulting in undefined behavior");
        }
        if (lock_ == 1) {
            // only one thread has the lock
            // self healing mutex resetting the dead lock flag
            dead_lock_ = false;
            // reset the thread id
            id_ = std::thread::id();
        }
        // increment the total number of unlocks
        unlock_count_++;
        // decrement the lock state
        lock_--;
    }

    /// @brief get the mutex lock state
    ///
    /// @return the mutex lock state
    int32_t getLock() {
        lock_guard<mutex> lk(mutex_);
        return lock_;
    }

    /// @brief get the mutex dead lock state
    ///
    /// @return the mutex dead lock state
    bool getDeadLock() {
        lock_guard<mutex> lk(mutex_);
        return dead_lock_;
    }

    /// @brief get the number of locks performed on mutex
    ///
    /// @return the mutex number of locks
    uint32_t getLockCount() {
        lock_guard<mutex> lk(mutex_);
        return lock_count_;
    }

    /// @brief get the number of unlocks performed on mutex
    ///
    /// @return the mutex number of unlocks
    uint32_t getUnlockCount() {
        lock_guard<mutex> lk(mutex_);
        return unlock_count_;
    }

    /// @brief test the internal state of the mutex
    ///
    /// @param expected_lock check equality of this value with lock state
    /// @param expected_lock_count check equality of this value with lock count
    /// @param expected_unlock_count check equality of this value with unlock count
    /// @param expected_dead_lock check equality of this value with dead lock state
    void testMutexState(int32_t expected_lock,
                        uint32_t expected_lock_count,
                        uint32_t expected_unlock_count,
                        bool expected_dead_lock) {
        ASSERT_EQ(getLock(), expected_lock);
        ASSERT_EQ(getLockCount(), expected_lock_count);
        ASSERT_EQ(getUnlockCount(), expected_unlock_count);
        ASSERT_EQ(getDeadLock(), expected_dead_lock);
    }

private:
    /// @brief internal lock state of the mutex
    int32_t lock_;

    /// @brief state which indicates that the mutex is in dead lock
    bool dead_lock_;

    /// @brief total number of locks performed on the mutex
    uint32_t lock_count_;

    /// @brief total number of unlocks performed on the mutex
    uint32_t unlock_count_;

    /// @brief flag to indicate if the mutex is recursive or not
    bool recursive_;

    /// @brief mutex used to keep the internal state consistent
    mutex mutex_;

    /// @brief the id of the thread holding the mutex
    std::thread::id id_;
};

/// @brief Test Fixture for testing isc::util::UnlockGuard
class UnlockGuardTest : public ::testing::Test {
};

/// @brief test TestMutex functionality with non-recursive mutex, and recursive
/// mutex
TEST_F(UnlockGuardTest, testMutex) {
    shared_ptr<TestMutex> test_mutex;
    // test non-recursive lock
    test_mutex = make_shared<TestMutex>();
    test_mutex->testMutexState(0, 0, 0, false);
    {
        // call lock_guard constructor which locks mutex
        lock_guard<TestMutex> lock(*test_mutex.get());
        // expect lock 1 lock_count 1 unlock_count 0 dead_lock false
        test_mutex->testMutexState(1, 1, 0, false);
        {
            // call lock_guard constructor which locks mutex resulting in an
            // exception as the mutex is already locked (dead lock)
            EXPECT_THROW(lock_guard<TestMutex> lock(*test_mutex.get()),
                         isc::InvalidOperation);
            // expect lock 1 lock_count 1 unlock_count 0 dead_lock true
            // you should not be able to get here...using a real mutex
            test_mutex->testMutexState(1, 1, 0, true);
        }
        // expect lock 1 lock_count 1 unlock_count 0 dead_lock true
        // you should not be able to get here...using a real mutex
        test_mutex->testMutexState(1, 1, 0, true);
    }
    // expect lock 0 lock_count 1 unlock_count 1 dead_lock false
    // the implementation is self healing when completely unlocking the mutex
    test_mutex->testMutexState(0, 1, 1, false);
    // test recursive lock
    test_mutex = make_shared<TestMutex>(true);
    test_mutex->testMutexState(0, 0, 0, false);
    {
        // call lock_guard constructor which locks mutex
        lock_guard<TestMutex> lock(*test_mutex.get());
        // expect lock 1 lock_count 1 unlock_count 0 dead_lock false
        test_mutex->testMutexState(1, 1, 0, false);
        {
            // call lock_guard constructor which locks mutex but does not block
            // as this is done on the same thread and the mutex is recursive
            EXPECT_NO_THROW(lock_guard<TestMutex> lock(*test_mutex.get()));
            // expect lock 1 lock_count 2 unlock_count 1 dead_lock false
            // the destructor was already called in EXPECT_NO_THROW scope
            test_mutex->testMutexState(1, 2, 1, false);
        }
        // expect lock 1 lock_count 2 unlock_count 1 dead_lock false
        test_mutex->testMutexState(1, 2, 1, false);
    }
    // expect lock 0 lock_count 2 unlock_count 2 dead_lock false
    test_mutex->testMutexState(0, 2, 2, false);
}

/// @brief test UnlockGuard functionality with non-recursive mutex
TEST_F(UnlockGuardTest, testUnlockGuard) {
    shared_ptr<TestMutex> test_mutex;
    // test non-recursive lock
    test_mutex = make_shared<TestMutex>();
    test_mutex->testMutexState(0, 0, 0, false);
    {
        // call lock_guard constructor which locks mutex
        lock_guard<TestMutex> lock(*test_mutex.get());
        // expect lock 1 lock_count 1 unlock_count 0 dead_lock false
        test_mutex->testMutexState(1, 1, 0, false);
        {
            UnlockGuard<TestMutex> unlock_guard(*test_mutex.get());
            // expect lock 0 lock_count 1 unlock_count 1 dead_lock false
            test_mutex->testMutexState(0, 1, 1, false);
        }
        // expect lock 1 lock_count 2 unlock_count 1 dead_lock false
        test_mutex->testMutexState(1, 2, 1, false);
    }
    // expect lock 0 lock_count 2 unlock_count 2 dead_lock false
    test_mutex->testMutexState(0, 2, 2, false);
}

} // namespace
