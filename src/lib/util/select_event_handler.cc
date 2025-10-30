// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/select_event_handler.h>

#ifndef FD_COPY
#define FD_COPY(orig, copy) \
    do { \
        memcpy(copy, orig, sizeof(fd_set)); \
    } while (0)
#endif

namespace isc {
namespace util {

SelectEventHandler::SelectEventHandler() : FDEventHandler(TYPE_SELECT), max_fd_(0) {
    clear();
}

void SelectEventHandler::add(int fd, bool read /* = true */, bool write /* = false */) {
    if (fd < 0) {
        isc_throw(BadValue, "invalid negative value for fd");
    }
    if (fd >= FD_SETSIZE) {
        isc_throw(BadValue, "invalid value for fd exceeds maximum allowed " << FD_SETSIZE);
    }
    if (read) {
        // Add this socket to read set
        FD_SET(fd, &read_fd_set_);
    }
    if (write) {
        // Add this socket to write set
        FD_SET(fd, &write_fd_set_);
    }
    if (fd > max_fd_) {
        max_fd_ = fd;
    }
}

int SelectEventHandler::waitEvent(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }
    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    FD_COPY(&read_fd_set_, &read_fd_set_data_);
    FD_COPY(&write_fd_set_, &write_fd_set_data_);

    return (select(max_fd_ + 1, &read_fd_set_data_, &write_fd_set_data_, 0, &select_timeout));
}

bool SelectEventHandler::readReady(int fd) {
    return (FD_ISSET(fd, &read_fd_set_data_));
}

bool SelectEventHandler::writeReady(int fd) {
    return (FD_ISSET(fd, &write_fd_set_data_));
}

void SelectEventHandler::clear() {
    FD_ZERO(&read_fd_set_);
    FD_ZERO(&write_fd_set_);
    max_fd_ = 0;
}

} // end of namespace isc::util
} // end of namespace isc
