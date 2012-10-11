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

#include <cstring>

#include <unistd.h>
#include <signal.h>

using namespace isc::util::thread;

namespace {
TEST(CondVarTest, create) {
    // Just construct and destruct it.  Nothing unusual should happen.
    EXPECT_NO_THROW(CondVar condvar);
}

// Running on a separate thread, just updating the argument and waking up
// the other thread via the condition variable passed.
void
ringSignal(CondVar* condvar, Mutex* mutex, bool* arg) {
    assert(*arg == false);
    Mutex::Locker locker(*mutex);
    *arg = true;
    condvar->signal();
}

void
no_handler(int) {}

// A simple wait-signal operation on a condition variable.
TEST(CondVarTest, waitAndSignal) {
    CondVar condvar;
    Mutex mutex;

    struct sigaction ignored, original;
    std::memset(&ignored, 0, sizeof(ignored));
    ignored.sa_handler = no_handler;
    if (sigaction(SIGALRM, &ignored, &original) != 0) {
        FAIL() << "Couldn't set alarm";
    }
    alarm(10);                  // 10sec duration: arbitrary choice

    Mutex::Locker locker(mutex);
    bool must_become_true = false; // let the other thread reset it to true
    Thread t(boost::bind(&ringSignal, &condvar, &mutex, &must_become_true));
    condvar.wait(mutex);
    t.wait();
    EXPECT_TRUE(must_become_true);

    // Cancel the alarm and return the original handler
    alarm(0);
    if (sigaction(SIGALRM, &original, NULL)) {
        FAIL() << "Couldn't restore alarm";
    }
}

}
