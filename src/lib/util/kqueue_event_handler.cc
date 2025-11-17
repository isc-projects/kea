// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/kqueue_event_handler.h>

#include <cstring>

#include <unistd.h>

using namespace std;

namespace isc {
namespace util {

KQueueEventHandler::KQueueEventHandler() : FDEventHandler(TYPE_KQUEUE), kqueuefd_(-1) {
    kqueuefd_ = kqueue();
    if (kqueuefd_ == -1) {
        isc_throw(Unexpected, "error opening kqueue: " << strerror(errno));
    }
    if (pipe(pipe_fd_)) {
        close(kqueuefd_);
        isc_throw(Unexpected, "error opening internal kqueue pipe: " << strerror(errno));
    }
    clear();
}

KQueueEventHandler::~KQueueEventHandler() {
    close(kqueuefd_);
    close(pipe_fd_[0]);
    close(pipe_fd_[1]);
}

void KQueueEventHandler::add(int fd) {
    if (fd < 0) {
        isc_throw(BadValue, "invalid negative value for fd");
    }
    struct kevent data;
    memset(&data, 0, sizeof(data));
    // Add this socket to read events
    EV_SET(&data, fd, EVFILT_READ, EV_ADD, 0, 0, 0);
    data_.push_back(data);
}

int KQueueEventHandler::waitEvent(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */,
                                  bool use_timeout /* = true */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }
    struct timespec select_timeout;
    struct timespec* select_timeout_p = 0;
    if (use_timeout) {
        select_timeout.tv_sec = timeout_sec;
        select_timeout.tv_nsec = timeout_usec * 1000;
        select_timeout_p = &select_timeout;
    }
    map_.clear();
    used_data_.clear();
    errors_.clear();
    errno = 0;
    int saved_errno = errno;
    for (auto data : data_) {
        if (kevent(kqueuefd_, &data, 1, 0, 0, 0) == -1) {
            saved_errno = errno;
            errors_.insert(data.ident);
        } else {
            used_data_.push_back(data);
        }
    }
    struct kevent dummy;
    memset(&dummy, 0, sizeof(dummy));
    EV_SET(&dummy, pipe_fd_[0], EVFILT_READ, EV_ADD, 0, 0, 0);
    kevent(kqueuefd_, &dummy, 1, 0, 0, 0);
    used_data_.push_back(dummy);
    int result = 0;
    if (errors_.empty()) {
        result = kevent(kqueuefd_, 0, 0, used_data_.data(), used_data_.size(),
                        select_timeout_p);
        for (int i = 0; i < result; ++i) {
            map_.emplace(used_data_[i].ident, &used_data_[i]);
        }
    }
    for (auto data : data_) {
        EV_SET(&data, data.ident, data.filter, EV_DELETE, 0, 0, 0);
        kevent(kqueuefd_, &data, 1, 0, 0, 0);
    }
    EV_SET(&dummy, dummy.ident, dummy.filter, EV_DELETE, 0, 0, 0);
    kevent(kqueuefd_, &dummy, 1, 0, 0, 0);
    if (result != -1) {
        errno = saved_errno;
    }
    if (errors_.size()) {
        return (-1);
    }
    return (result);
}

bool KQueueEventHandler::readReady(int fd) {
    auto range = map_.equal_range(fd);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second->filter == EVFILT_READ) {
            return (true);
        }
    }
    return (false);
}

void KQueueEventHandler::clear() {
    data_.clear();
    used_data_.clear();
    errors_.clear();
    map_.clear();
    errno = 0;
}

} // end of namespace isc::util
} // end of namespace isc
