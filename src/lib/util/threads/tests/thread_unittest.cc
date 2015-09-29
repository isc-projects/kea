// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <util/process_spawn.h>
#include <util/threads/sync.h>
#include <util/threads/thread.h>
#include <util/unittests/check_valgrind.h>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

#include <signal.h>
#include <unistd.h>

// This file tests the Thread class. It's hard to test an actual thread is
// started, but we at least check the function is run and exceptions are
// propagated as they should.
//
// We run some tests multiple times to see if there happen to be a race
// condition (then it would have better chance showing up).
//
// The detached tests are not run as many times to prevent many threads being
// started in parallel (the other tests wait for the previous one to terminate
// before starting new one).

using namespace isc::util;
using namespace isc::util::thread;

namespace {
const size_t iterations = 200;
const size_t detached_iterations = 25;

/// @brief Implements a thread which can be stopped.
///
/// This class implements a worker thread which can be stopped by calling
/// StoppableThread::stop. The call to this function blocks until the thread
/// terminates. This class is useful for testing scenarios when the thread
/// needs to be run for a specific amount of time.
class StoppableThread {
public:

    /// @brief Constructor.
    ///
    /// It doesn't run the thread yet. It merely initializes required
    /// class members.
    StoppableThread()
        : stopping_(false), mutex_(), thread_() {
    }

    /// @brief Destructor.
    ///
    /// Detaches the thread.
    ~StoppableThread() {
    }

    /// @brief Starts the execution of the thread.
    ///
    /// This method will not start the thread if the thread has been stopped.
    /// In order to start the thread again, @c StoppableThread::reset must be
    /// called first.
    void run() {
        if (!amStopping()) {
            thread_.reset(new Thread(boost::bind(&StoppableThread::loop, this)));
        }
    }

    /// @brief Stops the thread as soon as possible.
    void stop() {
        if (!amStopping()) {
            setStopping(true);
            if (thread_) {
                thread_->wait();
                thread_.reset();
            }
        }
    }

    /// @brief Resets the thread state so as it can be ran again.
    void reset() {
        setStopping(false);
    }

private:

    /// @brief Checks if the thread is being stopped.
    ///
    /// @return true if the thread is being stopped.
    bool amStopping() {
        Mutex::Locker lock(mutex_);
        return (stopping_);
    }

    /// @brief Sets the stopping state.
    ///
    /// @param stopping New value for @c stopping_ state.
    void setStopping(const bool stopping) {
        Mutex::Locker lock(mutex_);
        stopping_ = stopping;
    }

    /// @brief Worker thread loop.
    ///
    /// It runs until the @c StoppableThread::stop is called.
    void loop() {
        for (;;) {
            if (amStopping()) {
                break;
            }
            usleep(100);
        }
    }

    /// @brief Flag indicating if the thread is being stopped.
    bool stopping_;
    /// @brief Mutex used for protecting @c stopping_ flag.
    Mutex mutex_;
    /// @brief Pointer to the thread instance.
    boost::scoped_ptr<Thread> thread_;
};

/// @brief Static instance of the stoppable thread.
boost::scoped_ptr<StoppableThread> thread;

class ThreadTest : public ::testing::Test {
public:

    virtual ~ThreadTest() {
        if (thread) {
            thread->stop();
        }
        thread.reset();
    }

    /// @brief No-op method.
    static void doSomething(int*) { }

    /// @brief Marks specified boolean value as true to indicate that the
    /// function has been run.
    static void markRun(bool* mark) {
        EXPECT_FALSE(*mark);
        *mark = true;
    }

    /// @brief Throws 42.
    static void throwSomething() {
        throw 42; // Throw something really unusual, to see everything is caught.
    }

    /// @brief Throws standard exception.
    static void throwException() {
        throw std::exception();
    }

    /// @brief Returns signal mask set for a thread.
    ///
    /// @parm mask Pointer to signal mask set for the calling thread.
    static void getSignalMask(sigset_t* mask) {
        pthread_sigmask(SIG_SETMASK, 0, mask);
    }
};



// We just test that we can forget about the thread and nothing
// bad will happen on our side.
TEST_F(ThreadTest, detached) {
    if (!isc::util::unittests::runningOnValgrind()) {
        int x;
        for (size_t i = 0; i < detached_iterations; ++i) {
            Thread thread(boost::bind(&ThreadTest::doSomething, &x));
        }
    }
}

// Wait for a thread to end first. The variable must be set at the time.
TEST_F(ThreadTest, wait) {
    if (!isc::util::unittests::runningOnValgrind()) {
        for (size_t i = 0; i < iterations; ++i) {
            bool mark = false;
            Thread thread(boost::bind(&ThreadTest::markRun, &mark));
            thread.wait();
            ASSERT_TRUE(mark) << "Not finished yet in " << i << "th iteration";
            // Can't wait second time
            ASSERT_THROW(thread.wait(), isc::InvalidOperation);
        }
    }
}

// Exception in the thread we forget about should not do anything to us
TEST_F(ThreadTest, detachedException) {
    if (!isc::util::unittests::runningOnValgrind()) {
        for (size_t i = 0; i < detached_iterations; ++i) {
            Thread thread(&ThreadTest::throwSomething);
        }
        for (size_t i = 0; i < detached_iterations; ++i) {
            Thread thread(&ThreadTest::throwException);
        }
    }
}

// An uncaught exception in the thread should propagate through wait
TEST_F(ThreadTest, exception) {
    if (!isc::util::unittests::runningOnValgrind()) {
        for (size_t i = 0; i < iterations; ++i) {
            Thread thread(throwSomething);
            Thread thread2(throwException);
            ASSERT_THROW(thread.wait(), Thread::UncaughtException);
            ASSERT_THROW(thread2.wait(), Thread::UncaughtException);
        }
    }
}

// Verify that all signals are blocked.
TEST_F(ThreadTest, sigmask) {
    sigset_t mask;
    sigemptyset(&mask);
    Thread thread(boost::bind(&ThreadTest::getSignalMask, &mask));
    ASSERT_NO_THROW(thread.wait());
    EXPECT_EQ(1, sigismember(&mask, SIGHUP));
    EXPECT_EQ(1, sigismember(&mask, SIGINT));
    EXPECT_EQ(1, sigismember(&mask, SIGTERM));
}


/// The @c ProcessSpawn class spawns new processes using the fork/exec
/// scheme. If the call to exec fails, child process exits with the
/// EXIT_FAILURE status code. The call to exit triggers destruction of
/// all static objects, i.e. destructors of statically declared
/// @c Thread objects are called in the child process. The call to
/// fork doesn't clone threads existing in the main process. So, the
/// @c Thread objects in the child process have invalid state, because
/// they point to non-existing threads. As a result any attempts to
/// detach or join the thread may result in errors or asserts.
///
/// This test verifies that the @c Thread class protects against such
/// errors. It is supposed to detect that the @c Thread object is in
/// the child process and not assert when the destruction fails.
TEST_F(ThreadTest, spawnProcessWithThread) {
    // Initialize and run the stoppable thread. Note that the 'thread'
    // is a static variable, which will be 'cloned' into the child
    // process. Its destructor will be called when the child process
    // terminates with EXIT_FAILURE status. So in fact the destructor
    // of the @c StoppableThread will be called twice: in the main
    // process and in the child process.
    thread.reset(new StoppableThread());
    thread->run();

    // Spawn the new process, using some non-existing executable. The
    // current process will fork but the execvp should fail.
    ProcessSpawn process_spawn("kea-dhcp4-a86570943h");
    pid_t pid = process_spawn.spawn();
    // Wait for the process to terminate.
    while (process_spawn.isRunning(pid)) {
        usleep(100);
    }
    // When the child process terminates it will call destructors of
    // static objects. This means that it will call the destructor of
    // the 'thread' object too. The 'thread' object in the child
    // process points to non-existing thread, but we expect the
    // graceful destruction, i.e. the destructor should not assert.
    // If the destructor asserts the exit code returned here will
    // be 0 - same as if we aborted.
    EXPECT_EQ(EXIT_FAILURE, process_spawn.getExitStatus(pid));
}

}
