// Copyright (C) 2018-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef THREADED_TEST_H
#define THREADED_TEST_H

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace isc {
namespace test {

/// @brief Base class for tests requiring threads.
///
/// This class contains 3 flags to signal when the thread has
/// started, is stopping and when it is stopped. The flags
/// are accessed in thread safe manner.
class ThreadedTest : public ::testing::Test {
protected:

    /// @brief Constructor.
    ThreadedTest();

    /// @brief Sets selected flag to true and signals condition
    /// variable.
    ///
    /// @param flag Reference to flag which should be set to true.
    void doSignal(bool& flag);

    /// @brief Signal that thread is ready.
    void signalReady();

    /// @brief Signal that thread is stopping.
    void signalStopping();

    /// @brief Signal that thread is stopped.
    void signalStopped();

    /// @brief Wait for a selected flag to be set.
    ///
    /// @param flag Reference to a flag on which the thread is
    /// waiting.
    void doWait(bool& flag);

    /// @brief Wait for the thread to be ready.
    void waitReady();

    /// @brief Wait for the thread to be stopping.
    void waitStopping();

    /// @brief Wait for the thread to stop.
    void waitStopped();

    /// @brief Checks if the thread is stopping.
    ///
    /// @return true if the thread is stopping, false otherwise.
    bool isStopping();

    /// @brief Pointer to server thread.
    boost::shared_ptr<std::thread> thread_;

    /// @brief Mutex used to synchronize threads.
    std::mutex mutex_;

    /// Conditional variable for thread waits.
    std::condition_variable condvar_;

    /// Flag indicating that the thread is ready.
    bool ready_;

    /// Flag indicating that the thread is stopping.
    bool stopping_;

    /// Flag indicating that the thread is stopped.
    bool stopped_;
};


} // end of namespace isc::test
} // end of namespace isc

#endif
