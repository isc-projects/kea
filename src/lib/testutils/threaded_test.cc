// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <testutils/threaded_test.h>

using namespace isc::util::thread;

namespace isc {
namespace test {

ThreadedTest::ThreadedTest()
    : thread_(), condvar_(), ready_(false), stopping_(false),
      stopped_(false) {
}

void
ThreadedTest::doSignal(bool& flag) {
    {
        Mutex::Locker lock(mutex_);
        flag = true;
    }
    condvar_.signal();
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
    Mutex::Locker lock(mutex_);
    while (!flag) {
        condvar_.wait(mutex_);
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
    Mutex::Locker lock(mutex_);
    return (stopping_);
}

} // end of namespace isc::test
} // end of namespace isc
