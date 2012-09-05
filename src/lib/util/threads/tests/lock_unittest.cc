// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include "../lock.h"
#include "../thread.h"

#include <gtest/gtest.h>

#include <boost/bind.hpp>

using namespace std;
using namespace isc::util::thread;

namespace {

// Test a recursive mutex can be locked multiple times
TEST(MutexTest, recursiveLockMultiple) {
    Mutex mutex(true);
    EXPECT_FALSE(mutex.locked()); // Debug-only build
    Mutex::Locker l1(mutex);
    EXPECT_TRUE(mutex.locked()); // Debug-only build
    Mutex::Locker l2(mutex);
    Mutex::Locker l3(mutex);
    Mutex::Locker l4(mutex);
    Mutex::Locker l5(mutex);
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
//
// FIXME: The test is disabled, since it screws something up in the VM (other
// tests fail then with rather cryptic messages, memory dumps and stuff).
// Any idea how to make the test work and reasonably safe?
TEST(MutexTest, DISABLED_destroyLocked) {
    // TODO: This probably won't work for non-debug mutexes. Disable on non-debug
    // compilation.
    Mutex* mutex = new Mutex;
    new Mutex::Locker(*mutex);
    EXPECT_THROW(delete mutex, isc::InvalidOperation);
    // Note: This leaks the locker. But this is a test for development aid
    // exception. The exception won't happen in normal build anyway and seeing
    // it means there's a bug. And we can't delete the locker now, since it
    // would access uninitialized memory.
}

// This test tries if a mutex really locks. We could try that with a deadlock,
// but that's not practical (the test would not end).
//
// So instead, we try to do some operations from multiple threads that are
// likely to break if not locked. Also, they must run for some time so all
// threads are started and the operation must be complicated enough so the
// compiler won't turn it into some kind of single atomic instruction.
//
// So, we'll have an array of numbers. Each thread will try to repeatedly
// find a number large at least as half of the average, take the number,
// distribute the value across the rest of the positions of the array and
// zero the found position. This operation keeps the sum of the array
// the same. But if two threads access it at the same time, it is likely
// one will add something to the position another one have chosen and
// the other one will then zero it, not taking the new value into account.
// That'd lower the total value of the array.
const unsigned long long length = 1000;
const unsigned long long iterations = 10000;
const unsigned long long value = 2000;
void
performStrangeOperation(long long unsigned* array, int direction,
                        Mutex* mutex)
{
    unsigned long long position = 0;
    for (size_t i = 0; i < iterations; i ++) {
        Mutex::Locker lock(*mutex);
        while (array[position % length] < value) {
            position += direction;
        }
        unsigned long long value = array[position % length];
        unsigned long long p2 = position;
        while (value > 0) {
            p2 += direction;
            if (p2 % length == position % length) {
                continue;
            }
            array[p2 % length] ++;
            value --;
        }
        array[position % length] = 0;
    }
}

TEST(MutexTest, swarm) {
    // This type has a low chance of being atomic itself, further raising
    // the chance of problems appearing.
    long long unsigned array[length];
    for (size_t i = 0; i < length; ++ i) {
        array[i] = value;
    }
    Mutex mutex;
    Thread t1(boost::bind(&performStrangeOperation, array, 1, &mutex));
    Thread t2(boost::bind(&performStrangeOperation, array, -1, &mutex));
    t1.wait();
    t2.wait();
    long long unsigned sum = 0;
    for (size_t i = 0; i < length; ++ i) {
        sum += array[i];
    }
    EXPECT_EQ(length * value, sum) << "Threads are badly synchronized";
}

}
