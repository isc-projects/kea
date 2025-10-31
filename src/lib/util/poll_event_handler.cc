// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/poll_event_handler.h>

namespace isc {
namespace util {

PollEventHandler::PollEventHandler() : FDEventHandler(TYPE_POLL) {
    clear();
}

void PollEventHandler::add(int fd, bool read /* = true */, bool write /* = false */) {
    if (fd < 0) {
        isc_throw(BadValue, "invalid negative value for fd");
    }
    struct pollfd data;
    memset(&data, 0, sizeof(data));
    data.fd = fd;
    if (read) {
        // Add this socket to read events
        data.events |= POLLIN;
    }
    if (write) {
        // Add this socket to write events
        data.events |= POLLOUT;
    }
    data_.push_back(data);
}

int PollEventHandler::waitEvent(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }
    int timeout = timeout_sec * 1000 + timeout_usec / 1000;
    map_.clear();
    for (size_t i = 0; i < data_.size(); ++i) {
        map_[data_[i].fd] = &data_[i];
    }
    return (poll(data_.data(), data_.size(), timeout));
}

bool PollEventHandler::readReady(int fd) {
    if (map_.find(fd) == map_.end()) {
        return (false);
    }
    return (map_[fd]->revents & POLLIN);
}

bool PollEventHandler::writeReady(int fd) {
    if (map_.find(fd) == map_.end()) {
        return (false);
    }
    return (map_[fd]->revents & POLLOUT);
}

bool PollEventHandler::hasError(int fd) {
    if (map_.find(fd) == map_.end()) {
        return (false);
    }
    return (map_[fd]->revents & (POLLHUP | POLLERR | POLLNVAL));
}

void PollEventHandler::clear() {
    data_.clear();
    map_.clear();
}

} // end of namespace isc::util
} // end of namespace isc
