// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <util/threads/sync.h>
#include <util/threads/thread.h>
#include <util/unittests/check_valgrind.h>

#include <boost/bind.hpp>
#include <unistd.h>
#include <signal.h>

using namespace isc::util::thread;

namespace {

#ifdef ENABLE_DEBUG

// If we try to lock the debug mutex multiple times, it should
// throw. This test will complete properly only when pthread debugging
// facilities are enabled by configuring the code for debug build.
TEST(MutexTest, lockMultiple) {
    Mutex mutex;
    EXPECT_FALSE(mutex.locked()); // Debug-only build

    Mutex::Locker l1(mutex);
    EXPECT_TRUE(mutex.locked()); // Debug-only build

    EXPECT_THROW({
        Mutex::Locker l2(mutex); // Attempt to lock again.
    }, isc::InvalidOperation);
    EXPECT_TRUE(mutex.locked()); // Debug-only build

    // block=true explicitly.
    Mutex mutex2;
    EXPECT_FALSE(mutex2.locked()); // Debug-only build
    Mutex::Locker l12(mutex2, true);
    EXPECT_TRUE(mutex2.locked()); // Debug-only build
}

void
testThread(Mutex* mutex)
{
    // block=false (tryLock).  This should not block indefinitely, but
    // throw AlreadyLocked. If block were true, this would block
    // indefinitely here.
    EXPECT_THROW({
        Mutex::Locker l3(*mutex, false);
    }, Mutex::Locker::AlreadyLocked);

    EXPECT_TRUE(mutex->locked()); // Debug-only build
}

// Test the non-blocking variant using a second thread.
TEST(MutexTest, lockNonBlocking) {
    // block=false (tryLock).
    Mutex mutex;
    Mutex::Locker l1(mutex, false);
    EXPECT_TRUE(mutex.locked()); // Debug-only build

    // First, try another locker from the same thread.
    EXPECT_THROW({
        Mutex::Locker l2(mutex, false);
    }, Mutex::Locker::AlreadyLocked);

    EXPECT_TRUE(mutex.locked()); // Debug-only build

    // Now try another locker from a different thread.
    Thread thread(boost::bind(&testThread, &mutex));
    thread.wait();
}

#endif // ENABLE_DEBUG

// Destroying a locked mutex is a bad idea as well
TEST(MutexTest,
#ifdef HAS_UNDEFINED_PTHREAD_BEHAVIOR
     DISABLED_destroyLocked
#else
     destroyLocked
#endif
) {
    if (!isc::util::unittests::runningOnValgrind()) {
        EXPECT_DEATH_IF_SUPPORTED({
            Mutex* mutex = new Mutex;
            new Mutex::Locker(*mutex);
            delete mutex;
            // This'll leak the locker, but inside the slave process, it should
            // not be an issue.
        }, "");
    }
}

// In this test, we try to check if a mutex really locks. We could try that
// with a deadlock, but that's not practical (the test would not end).
//
// Instead, we try do to some operation on the same data from multiple threads
// that's likely to break if not locked. Also, the test must run for a while
// to have an opportunity to manifest.
//
// Currently we try incrementing a double variable. That one is large enough
// and complex enough so it should not be possible for the CPU to do it as an
// atomic operation, at least on common architectures.
const size_t iterations = 100000;

void
performIncrement(volatile double* canary, volatile bool* ready_me,
                 volatile bool* ready_other, Mutex* mutex)
{
    // Loosely (busy) wait for the other thread so both will start
    // approximately at the same time.
    *ready_me = true;
    while (!*ready_other) {}

    for (size_t i = 0; i < iterations; ++i) {
        Mutex::Locker lock(*mutex);
        *canary += 1;
    }
}

void
noHandler(int) {}

TEST(MutexTest, swarm) {
    if (!isc::util::unittests::runningOnValgrind()) {
        // Create a timeout in case something got stuck here
        struct sigaction ignored, original;
        memset(&ignored, 0, sizeof(ignored));
        ignored.sa_handler = noHandler;
        if (sigaction(SIGALRM, &ignored, &original)) {
            FAIL() << "Couldn't set alarm";
        }
        alarm(10);
        // This type has a low chance of being atomic itself, further raising
        // the chance of problems appearing.
        double canary = 0;
        Mutex mutex;
        // Run two parallel threads
        bool ready1 = false;
        bool ready2 = false;
        Thread t1(boost::bind(&performIncrement, &canary, &ready1, &ready2,
                              &mutex));
        Thread t2(boost::bind(&performIncrement, &canary, &ready2, &ready1,
                              &mutex));
        t1.wait();
        t2.wait();
        // Check it the sum is the expected value.
        EXPECT_EQ(iterations * 2, canary) << "Threads are badly synchronized";
        // Cancel the alarm and return the original handler
        alarm(0);
        if (sigaction(SIGALRM, &original, NULL)) {
            FAIL() << "Couldn't restore alarm";
        }
    }
}

}
