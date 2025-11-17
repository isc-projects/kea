// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/epoll_event_handler.h>

#include <cstring>

#include <unistd.h>

using namespace std;

namespace isc {
namespace util {

EPollEventHandler::EPollEventHandler() : FDEventHandler(TYPE_EPOLL), epollfd_(-1) {
    epollfd_ = epoll_create1(EPOLL_CLOEXEC);
    if (epollfd_ == -1) {
        isc_throw(Unexpected, "error opening epoll: " << strerror(errno));
    }
    if (pipe(pipe_fd_)) {
        close(epollfd_);
        isc_throw(Unexpected, "error opening internal epoll pipe: " << strerror(errno));
    }
    clear();
}

EPollEventHandler::~EPollEventHandler() {
    close(epollfd_);
    close(pipe_fd_[0]);
    close(pipe_fd_[1]);
}

void EPollEventHandler::add(int fd) {
    if (fd < 0) {
        isc_throw(BadValue, "invalid negative value for fd");
    }
    struct epoll_event data;
    memset(&data, 0, sizeof(data));
    data.data.fd = fd;
    // Add this socket to read events
    data.events |= EPOLLIN;
    data_.push_back(data);
}

int EPollEventHandler::waitEvent(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */,
                                 bool use_timeout /* = true */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }
    int timeout = -1;
    if (use_timeout) {
        timeout = timeout_sec * 1000 + timeout_usec / 1000;
    }
    map_.clear();
    used_data_.clear();
    errors_.clear();
    errno = 0;
    int saved_errno = errno;
    for (auto data : data_) {
        if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, data.data.fd, &data) == -1) {
            saved_errno = errno;
            errors_.insert(data.data.fd);
        } else {
            used_data_.push_back(data);
        }
    }
    struct epoll_event dummy;
    memset(&dummy, 0, sizeof(dummy));
    dummy.data.fd = pipe_fd_[0];
    dummy.events |= EPOLLIN;
    epoll_ctl(epollfd_, EPOLL_CTL_ADD, dummy.data.fd, &dummy);
    used_data_.push_back(dummy);
    int result = 0;
    if (errors_.empty()) {
        result = epoll_wait(epollfd_, used_data_.data(), used_data_.size(), timeout);
        for (int i = 0; i < result; ++i) {
             map_[used_data_[i].data.fd] = &used_data_[i];
        }
    }
    for (auto data : data_) {
        epoll_ctl(epollfd_, EPOLL_CTL_DEL, data.data.fd, &data);
    }
    epoll_ctl(epollfd_, EPOLL_CTL_DEL, dummy.data.fd, &dummy);
    if (result != -1) {
        errno = saved_errno;
    }
    if (errors_.size()) {
        return (-1);
    }
    return (result);
}

bool EPollEventHandler::readReady(int fd) {
    if (map_.find(fd) == map_.end()) {
        return (false);
    }
    return (map_[fd]->events & EPOLLIN);
}

void EPollEventHandler::clear() {
    data_.clear();
    used_data_.clear();
    errors_.clear();
    map_.clear();
    errno = 0;
}

} // end of namespace isc::util
} // end of namespace isc
