// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

#include <sys/select.h>
#include <sys/ioctl.h>

using namespace std;

namespace isc {
namespace dhcp_ddns {

int selectCheck(int fd_to_check) {
    fd_set read_fds;
    int maxfd = 0;

    FD_ZERO(&read_fds);

    // Add this socket to listening set
    FD_SET(fd_to_check,  &read_fds);
    maxfd = fd_to_check;

    struct timeval select_timeout;
    select_timeout.tv_sec = 0;
    select_timeout.tv_usec = 0;

    return (select(maxfd + 1, &read_fds, NULL, NULL, &select_timeout));
}

}; // namespace isc::d2
}; // namespace isc
