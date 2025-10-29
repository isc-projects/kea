// Copyright (C) 2011-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <select_event_handler.h>

namespace isc {
namespace dhcp {

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
}

// @brief Wait for events on registered file descriptors.
int SelectEventHandler::waitEvent(uint32_t timeout_sec, uint32_t timeout_usec /* = 0 */) {
    // Sanity check for microsecond timeout.
    if (timeout_usec >= 1000000) {
        isc_throw(BadValue, "fractional timeout must be shorter than"
                  " one million microseconds");
    }
    struct timeval select_timeout;
    select_timeout.tv_sec = timeout_sec;
    select_timeout.tv_usec = timeout_usec;

    return (select(max_fd_ + 1, &read_fd_set_, &write_fd_set_, 0, &select_timeout));
}

// @brief Check if file descriptor is ready for read operation.
//
// @param fd The file descriptor.
//
// @return True if file descriptor is ready for reading.
bool SelectEventHandler::readReady(int fd) {
    return (FD_ISSET(fd, &read_fd_set_));
}

// @brief Check if file descriptor is ready for write operation.
//
// @param fd The file descriptor.
//
// @return True if file descriptor is ready for writing.
bool SelectEventHandler::writeReady(int fd) {
    return (FD_ISSET(fd, &write_fd_set_));
}

void SelectEventHandler::clear() {
    FD_ZERO(&read_fd_set_);
    FD_ZERO(&write_fd_set_);
    max_fd_ = 0;
}

} // end of namespace isc::dhcp
} // end of namespace isc
