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

#include <util/threads/thread.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

// This file tests the Thread class. It's hard to test an actual thread is
// started, but we at least check the function is run and exceptions are
// propagated as they should.
//
// We run some tests mutiple times to see if there happen to be a race
// condition (then it would have better chance showing up).
//
// The detached tests are not run as many times to prevent many threads being
// started in parallel (the other tests wait for the previous one to terminate
// before starting new one).

const size_t iterations = 200;
const size_t detached_iterations = 25;

using namespace isc::util::thread;

namespace {

void
doSomething(int* x) {
    delete[] x;
}

// We just test that we can forget about the thread and nothing
// bad will happen on our side.
TEST(ThreadTest, detached) {
    for (size_t i = 0; i < detached_iterations; ++i) {
        int* x = new int[10];
        Thread thread(boost::bind(&doSomething, x));
    }
}

void
markRun(bool* mark) {
    EXPECT_FALSE(*mark);
    *mark = true;
}

// Wait for a thread to end first. The variable must be set at the time.
TEST(ThreadTest, wait) {
    for (size_t i = 0; i < iterations; ++i) {
        bool mark = false;
        Thread thread(boost::bind(markRun, &mark));
        thread.wait();
        ASSERT_TRUE(mark) << "Not finished yet in " << i << "th iteration";
        // Can't wait second time
        ASSERT_THROW(thread.wait(), isc::InvalidOperation);
    }
}

void
throwSomething() {
    throw 42; // Throw something really unusual, to see everything is caught.
}

void
throwException() {
    throw std::exception();
}

// Exception in the thread we forget about should not do anything to us
TEST(ThreadTest, detachedException) {
    for (size_t i = 0; i < detached_iterations; ++i) {
        Thread thread(throwSomething);
    }
    for (size_t i = 0; i < detached_iterations; ++i) {
        Thread thread(throwException);
    }
}

// An uncaught exception in the thread should propagate through wait
TEST(ThreadTest, exception) {
    for (size_t i = 0; i < iterations; ++i) {
        Thread thread(throwSomething);
        Thread thread2(throwException);
        ASSERT_THROW(thread.wait(), Thread::UncaughtException);
        ASSERT_THROW(thread2.wait(), Thread::UncaughtException);
    }
}

}
