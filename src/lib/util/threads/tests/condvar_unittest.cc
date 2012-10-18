// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <util/threads/sync.h>
#include <util/threads/thread.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <cstring>

#include <unistd.h>
#include <signal.h>

using namespace isc::util::thread;

namespace {
// Used as a signal handler below.
volatile bool do_exit;          // use for emergency escape
void
alarmHandler(int) {
    do_exit = true;
}

class CondVarTest : public ::testing::Test {
protected:
    // We use a signal in case some of the thread synchronization tests
    // unexpectedly cause a deadlock.
    void SetUp() {
        do_exit = false;

        std::memset(&handler_, 0, sizeof(handler_));
        handler_.sa_handler = alarmHandler;
        if (sigaction(SIGALRM, &handler_, &original_) != 0) {
            FAIL() << "Couldn't set alarm";
        }
        alarm(10);                  // 10sec duration: arbitrary choice
    }
    void TearDown() {
        // Cancel the alarm and return the original handler
        alarm(0);
        if (sigaction(SIGALRM, &original_, NULL)) {
            FAIL() << "Couldn't restore alarm";
        }
    }

    CondVar condvar_;
    Mutex mutex_;
private:
    struct sigaction handler_, original_;
};

TEST(CondVarTest0, create) {
    // Just construct and destruct it.  Nothing unusual should happen.
    EXPECT_NO_THROW(CondVar condvar);
}

// Running on a separate thread, just updating the argument and waking up
// the other thread via the condition variable passed.
void
ringSignal(CondVar* condvar, Mutex* mutex, int* arg) {
    assert(*arg == 0);
    Mutex::Locker locker(*mutex);
    ++*arg;
    condvar->signal();
}

// A simple wait-signal operation on a condition variable.
TEST_F(CondVarTest, waitAndSignal) {
    Mutex::Locker locker(mutex_);
    int shared_var = 0; // let the other thread increment this
    Thread t(boost::bind(&ringSignal, &condvar_, &mutex_, &shared_var));
    condvar_.wait(mutex_);
    t.wait();
    EXPECT_EQ(1, shared_var);
}

// Thread's main code for the next test
void
signalAndWait(CondVar* condvar1, CondVar* condvar2, Mutex* mutex, int* arg) {
    Mutex::Locker locker(*mutex);
    ++*arg;
    condvar2->signal();  // let the main thread know this one is ready
    condvar1->wait(*mutex);
    ++*arg;
}

// Similar to the previous test, but having two threads wait for a condvar.
TEST_F(CondVarTest, multiWaits) {
    boost::scoped_ptr<Mutex::Locker> locker(new Mutex::Locker(mutex_));
    CondVar condvar2; // separate cond var for initial synchronization
    int shared_var = 0; // let the other thread increment this
    Thread t1(boost::bind(&signalAndWait, &condvar_, &condvar2, &mutex_,
                          &shared_var));
    Thread t2(boost::bind(&signalAndWait, &condvar_, &condvar2, &mutex_,
                          &shared_var));

    // Wait until both threads are waiting on condvar_.
    while (shared_var < 2 && !do_exit) {
        condvar2.wait(mutex_);
    }
    // Check we exited from the loop successfully.
    ASSERT_FALSE(do_exit);
    ASSERT_EQ(2, shared_var);

    // release the lock, wake up both threads, wait for them to die, and
    // confirm they successfully woke up.
    locker.reset();
    condvar_.signal();
    condvar_.signal();
    t1.wait();
    t2.wait();
    EXPECT_EQ(4, shared_var);
}

// Similar to the previous version of the same function, but just do
// condvar operations.  It will never wake up.
void
signalAndWait(CondVar* condvar, Mutex* mutex) {
    Mutex::Locker locker(*mutex);
    condvar->signal();
    condvar->wait(*mutex);
}

// Temporarily disabled: Solaris seems to make this behavior "undefined"
TEST_F(CondVarTest, DISABLED_destroyWhileWait) {
    // We'll destroy a CondVar object while the thread is still waiting
    // on it.  This will trigger an assertion failure.
    EXPECT_DEATH_IF_SUPPORTED({
            CondVar cond;
            Mutex::Locker locker(mutex_);
            Thread t(boost::bind(&signalAndWait, &cond, &mutex_));
            cond.wait(mutex_);
        }, "");
}

TEST_F(CondVarTest, badWait) {
    // In our implementation, wait() requires acquiring the lock beforehand.
#ifdef ENABLE_DEBUG
    EXPECT_THROW(condvar_.wait(mutex_), isc::InvalidOperation);
#else
    EXPECT_THROW(condvar_.wait(mutex_), isc::BadValue);
#endif // ENABLE_DEBUG
}

TEST_F(CondVarTest, emptySignal) {
    // It's okay to call signal when no one waits.
    EXPECT_NO_THROW(condvar_.signal());
}

}
