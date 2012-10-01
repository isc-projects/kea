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

// This test tries if a mutex really locks. We could try that with a deadlock,
// but that's not practical (the test would not end).
//
// So instead, we try to do some operations from multiple threads that are
// likely to break if not locked. Also, they must run for some time so all
// threads are started and the operation must be complicated enough so the
// compiler won't turn it into some kind of single atomic instruction.
//
// FIXME: Any idea for a simpler but non-atomic operation that keeps an
// invariant?
//
// So, we'll have an array of numbers. Each thread will try to repeatedly
// find a number large at least as half of the average, take the number,
// distribute the value across the rest of the positions of the array and
// zero the found position. This operation keeps the sum of the array
// the same. But if two threads access it at the same time, it is likely
// one will add something to the position another one have chosen and
// the other one will then zero it, not taking the new value into account.
// That'd lower the total value of the array.
//
// We run the threads in opposite directions (so we have no chance of them
// keeping the same distance to each other and not meeting). Also, the indexing
// is performed in a circular manner like with a ring buffer.
const unsigned long long length = 1000;
const unsigned long long iterations = 10000;
const unsigned long long value = 2000;
void
performStrangeOperation(std::vector<long long unsigned> array, int direction,
                        Mutex* mutex)
{
    unsigned long long position = 0;
    for (size_t i = 0; i < iterations; i ++) {
        Mutex::Locker lock(*mutex);
        // Find a place with large enough value
        while (array[position % length] < value) {
            position += direction;
        }
        // Take the value
        unsigned long long found_value = array[position % length];
        // And distribute it to places following the found one, by
        // adding 1 to each.
        unsigned long long p2 = position;
        while (found_value > 0) {
            p2 += direction;
            if (p2 % length == position % length) {
                continue;
            }
            array[p2 % length] ++;
            found_value --;
        }
        // Zero the distributed value
        array[position % length] = 0;
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
    std::vector<long long unsigned> array(length);
    for (size_t i = 0; i < length; ++ i) {
        array[i] = value;
    }
    Mutex mutex;
    // Run two parallel threads, each in one direction
    Thread t1(boost::bind(&performStrangeOperation, array, 1, &mutex));
    Thread t2(boost::bind(&performStrangeOperation, array, -1, &mutex));
    t1.wait();
    t2.wait();
    // Check the sum didn't change.
    long long unsigned sum = 0;
    for (size_t i = 0; i < length; ++ i) {
        sum += array[i];
    }
    EXPECT_EQ(length * value, sum) << "Threads are badly synchronized";
    // Cancel the alarm and return the original handler
    alarm(0);
    if (sigaction(SIGALRM, &original, NULL)) {
        FAIL() << "Couldn't restore alarm";
    }
}

}
