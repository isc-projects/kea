// Copyright (C) 2013-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/ready_check.h>

#include <gtest/gtest.h>

#include <cstddef>

namespace isc {
namespace util {
namespace unittests {

unsigned char
parentReadState(int fd) {
    unsigned char result = 0xff;

    const int nfds = util::selectCheck(fd, 5);
    EXPECT_EQ(1, nfds);

    if (nfds == 1) {
        // Read status
        const ssize_t bytes_read = read(fd, &result, sizeof(result));
        EXPECT_EQ(static_cast<ssize_t>(sizeof(result)), bytes_read);
    }

    return (result);
}

}
}
}
