// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <sys/select.h>

namespace isc {
namespace util {

int selectCheck(const int fd_to_check, const unsigned int timeout_sec,
                bool read_check, bool write_check) {
    // @todo implement this using SelectEventHandler
    // @todo: should move to epoll/kqueue?
    if (fd_to_check < 0) {
        return (-1);
    }
    if (fd_to_check >= FD_SETSIZE) {
        return (-1);
    }
    int maxfd = 0;

    fd_set read_fds;
    FD_ZERO(&read_fds);

    fd_set write_fds;
    FD_ZERO(&write_fds);

    maxfd = fd_to_check;

    // Add this socket to read set
    FD_SET(fd_to_check, &read_fds);

    // Add this socket to write set
    FD_SET(fd_to_check, &write_fds);

    struct timeval select_timeout;
    select_timeout.tv_sec = static_cast<time_t>(timeout_sec);
    select_timeout.tv_usec = 0;

    fd_set* read_p = 0;
    fd_set* write_p = 0;

    if (read_check) {
        read_p = &read_fds;
    }

    if (write_check) {
        write_p = &write_fds;
    }

    return (select(maxfd + 1, read_p, write_p, 0, &select_timeout));
}

} // end of isc::util namespace
} // end of isc namespace
