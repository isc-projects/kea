// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/watched_thread.h>
#include <signal.h>

namespace isc {
namespace util {

void
WatchedThread::start(const std::function<void()>& thread_main) {
    clearReady(ERROR);
    clearReady(READY);
    clearReady(TERMINATE);
    setErrorInternal("no error");
    // Protect us against signals
    sigset_t sset;
    sigset_t osset;
    sigemptyset(&sset);
    sigaddset(&sset, SIGCHLD);
    sigaddset(&sset, SIGINT);
    sigaddset(&sset, SIGHUP);
    sigaddset(&sset, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &sset, &osset);
    try {
        thread_.reset(new std::thread(thread_main));
    } catch (...) {
        // Restore signal mask.
        pthread_sigmask(SIG_SETMASK, &osset, 0);
        throw;
    }
    // Restore signal mask.
    pthread_sigmask(SIG_SETMASK, &osset, 0);
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
    if (sockets_[TERMINATE].isReady()) {
        clearReady(TERMINATE);
        return (true);
    }

    return (false);
}

void
WatchedThread::stop() {
    if (thread_) {
        markReady(TERMINATE);
        thread_->join();
        thread_.reset();
    }

    clearReady(ERROR);
    clearReady(READY);
    setErrorInternal("thread stopped");
}

void
WatchedThread::setErrorInternal(const std::string& error_msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    last_error_ = error_msg;
}

void
WatchedThread::setError(const std::string& error_msg) {
    setErrorInternal(error_msg);
    markReady(ERROR);
}

std::string
WatchedThread::getLastError() {
    std::lock_guard<std::mutex> lock(mutex_);
    return (last_error_);
}

}  // namespace util
}  // namespace isc
