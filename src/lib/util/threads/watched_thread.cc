// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/threads/watched_thread.h>

namespace isc {
namespace util {
namespace thread {

void
WatchedThread::start(const boost::function<void()>& thread_main) {
    clearReady(RCV_ERROR);
    clearReady(RCV_READY);
    clearReady(RCV_TERMINATE);
    last_error_ = "no error";
    thread_.reset(new Thread(thread_main));
}

int
WatchedThread::getWatchFd(WatchType watch_type) {
    return(sockets_[watch_type].getSelectFd());
}

void
WatchedThread::markReady(WatchType watch_type)  {
    sockets_[watch_type].markReady();
}

bool
WatchedThread::isReady(WatchType watch_type) {
    return (sockets_[watch_type].isReady());
}

void
WatchedThread::clearReady(WatchType watch_type) {
    sockets_[watch_type].clearReady();
}

bool
WatchedThread::shouldTerminate() {
    if (sockets_[RCV_TERMINATE].isReady()) {
        clearReady(RCV_TERMINATE);
        return (true);
    }

    return (false);
}

void
WatchedThread::stop() {
    if (thread_) {
        markReady(RCV_TERMINATE);
        thread_->wait();
        thread_.reset();
    }

    clearReady(RCV_ERROR);
    clearReady(RCV_READY);
    last_error_ = "thread stopped";
}

void
WatchedThread::setError(const std::string& error_msg) {
    last_error_ = error_msg;
    markReady(RCV_ERROR);
}

std::string
WatchedThread::getLastError() {
    return (last_error_);
}
} // end of namespace isc::util::thread
} // end of namespace isc::util
} // end of namespace isc
