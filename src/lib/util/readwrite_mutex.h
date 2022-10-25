// Copyright (C) 2020-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef READWRITE_MUTEX_H
#define READWRITE_MUTEX_H

/// @file readwrite_mutex.h
///
/// Standard implementation of read-write mutexes with writer preference
/// using C++11 mutex and condition variable.
/// As we need only the RAII wrappers implement only used methods.

#include <exceptions/exceptions.h>
#include <boost/noncopyable.hpp>
#include <climits>
#include <condition_variable>
#include <mutex>

namespace isc {
namespace util {

/// @brief Read-Write Mutex.
///
/// The code is based on Howard Hinnant's reference implementation
/// for C++17 shared_mutex.
class ReadWriteMutex : public boost::noncopyable {
public:

    /// Constants.

    /// @brief The write entered flag (higher bit so 2^31).
    static const unsigned WRITE_ENTERED =
        1U << (sizeof(unsigned) * CHAR_BIT - 1);

    /// @brief The maximum number of readers (flag complement so 2^31 - 1).
    static const unsigned MAX_READERS = ~WRITE_ENTERED;

    /// @brief Constructor.
    ReadWriteMutex() : state_(0) {
    }

    /// @brief Destructor.
    ///
    /// @note: do not check that state is 0 as there is nothing very
    /// useful to do in this case...
    virtual ~ReadWriteMutex() {
        std::lock_guard<std::mutex> lk(mutex_);
    }

    /// @brief Lock write.
    void writeLock() {
        std::unique_lock<std::mutex> lk(mutex_);
        // Wait until the write entered flag can be set.
        gate1_.wait(lk, [&]() { return (!writeEntered()); });
        state_ |= WRITE_ENTERED;
        // Wait until there are no more readers.
        gate2_.wait(lk, [&]() { return (readers() == 0); });
    }

    /// @brief Unlock write.
    ///
    /// @note: do not check that WRITE_ENTERED was set.
    void writeUnlock() {
        std::lock_guard<std::mutex> lk(mutex_);
        state_ = 0;
        // Wake-up waiting threads when exiting the guard.
        gate1_.notify_all();
    }

    /// @brief Lock read.
    void readLock() {
        std::unique_lock<std::mutex> lk(mutex_);
        // Wait if there is a writer or if readers overflow.
        gate1_.wait(lk, [&]() { return (state_ < MAX_READERS); });
        ++state_;
    }

    /// @brief Unlock read.
    ///
    /// @note: do not check that there is a least one reader.
    void readUnlock() {
        std::lock_guard<std::mutex> lk(mutex_);
        unsigned prev = state_--;
        if (writeEntered()) {
            if (readers() == 0) {
                // Last reader: wake up a waiting writer.
                gate2_.notify_one();
            }
        } else {
            if (prev == MAX_READERS) {
                // Reader overflow: wake up one waiting reader.
                gate1_.notify_one();
            }
        }
    }

private:

    /// Helpers.

    /// @brief Check if the write entered flag is set.
    bool writeEntered() const {
        return (state_ & WRITE_ENTERED);
    }

    /// @brief Return the number of readers.
    unsigned readers() const {
        return (state_ & MAX_READERS);
    }

    /// Members.

    /// @brief Mutex.
    ///
    /// Used to protect the state and in condition variables.
    std::mutex mutex_;

    /// @brief First condition variable.
    ///
    /// Used to block while the write entered flag is set or readers overflow.
    std::condition_variable gate1_;

    /// @brief Second condition variable.
    ///
    /// Used to block writers until the reader count decrements to zero.
    std::condition_variable gate2_;

    /// @brief State.
    ///
    /// Used to handle the write entered flag and the reader count.
    unsigned state_;
};

/// @brief Read mutex RAII handler.
///
/// The constructor acquires the lock, the destructor releases it.
class ReadLockGuard : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// @param rw_mutex The read mutex.
    ReadLockGuard(ReadWriteMutex& rw_mutex) : rw_mutex_(rw_mutex) {
        rw_mutex_.readLock();
    }

    /// @brief Destructor.
    virtual ~ReadLockGuard() {
        rw_mutex_.readUnlock();
    }

private:
    /// @brief The read-write mutex.
    ReadWriteMutex& rw_mutex_;

};

/// @brief Write mutex RAII handler.
///
/// The constructor acquires the lock, the destructor releases it.
class WriteLockGuard : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// @param rw_mutex The write mutex.
    WriteLockGuard(ReadWriteMutex& rw_mutex) : rw_mutex_(rw_mutex) {
        rw_mutex_.writeLock();
    }

    /// @brief Destructor.
    virtual ~WriteLockGuard() {
        rw_mutex_.writeUnlock();
    }

private:
    /// @brief The read-write mutex.
    ReadWriteMutex& rw_mutex_;
};

} // namespace util
} // namespace isc

#endif // READWRITE_MUTEX_H
