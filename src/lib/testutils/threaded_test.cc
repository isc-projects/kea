// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/threaded_test.h>

namespace isc {
namespace test {

ThreadedTest::ThreadedTest()
    : thread_(), condvar_(), ready_(false), stopping_(false),
      stopped_(false) {
}

void
ThreadedTest::doSignal(bool& flag) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        flag = true;
    }
    condvar_.notify_one();
}

void
ThreadedTest::signalReady() {
    doSignal(ready_);
}

void
ThreadedTest::signalStopping() {
    doSignal(stopping_);
}

void
ThreadedTest::signalStopped() {
    doSignal(stopped_);
}

void
ThreadedTest::doWait(bool& flag) {
    std::unique_lock<std::mutex> lock(mutex_);
    while (!flag) {
        condvar_.wait(lock);
    }
}

void
ThreadedTest::waitReady() {
    doWait(ready_);
}

void
ThreadedTest::waitStopping() {
    doWait(stopping_);
}

void
ThreadedTest::waitStopped() {
    doWait(stopped_);
}

bool
ThreadedTest::isStopping() {
    std::lock_guard<std::mutex> lock(mutex_);
    return (stopping_);
}

} // end of namespace isc::test
} // end of namespace isc
