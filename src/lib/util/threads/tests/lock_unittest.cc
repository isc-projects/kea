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

#include <util/threads/lock.h>
#include <util/threads/thread.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <unistd.h>
#include <signal.h>

using namespace isc::util::thread;

namespace {

TEST(MutexTest, direct) {
    Mutex mutex;
    EXPECT_FALSE(mutex.locked()); // Debug-only build

    mutex.lock();
    EXPECT_TRUE(mutex.locked()); // Debug-only build

    EXPECT_FALSE(mutex.tryLock());

    mutex.unlock();
    EXPECT_FALSE(mutex.locked()); // Debug-only build

    EXPECT_TRUE(mutex.tryLock());

    mutex.unlock();
    EXPECT_FALSE(mutex.locked()); // Debug-only build
}

// If we try to lock the debug mutex multiple times, it should throw.
TEST(MutexTest, lockMultiple) {
    // TODO: Once we support non-debug mutexes, disable the test if we compile
    // with them.
    Mutex mutex;
    EXPECT_FALSE(mutex.locked()); // Debug-only build
    Mutex::Locker l1(mutex);
    EXPECT_TRUE(mutex.locked()); // Debug-only build
    EXPECT_THROW({
        Mutex::Locker l2(mutex); // Attempt to lock again.
    }, isc::InvalidOperation);
    EXPECT_TRUE(mutex.locked()); // Debug-only build
}

// Destroying a locked mutex is a bad idea as well
#ifdef EXPECT_DEATH
TEST(MutexTest, destroyLocked) {
    EXPECT_DEATH({
        Mutex* mutex = new Mutex;
        new Mutex::Locker(*mutex);
        delete mutex;
        // This'll leak the locker, but inside the slave process, it should
        // not be an issue.
    }, "");
}
#endif

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
no_handler(int) {}

TEST(MutexTest, swarm) {
    // Create a timeout in case something got stuck here
    struct sigaction ignored, original;
    memset(&ignored, 0, sizeof ignored);
    ignored.sa_handler = no_handler;
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
