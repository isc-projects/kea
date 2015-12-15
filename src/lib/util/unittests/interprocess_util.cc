// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

#include <sys/select.h>
#include <cstddef>

namespace isc {
namespace util {
namespace unittests {

unsigned char
parentReadState(int fd) {
  unsigned char result = 0xff;

  fd_set rfds;
  FD_ZERO(&rfds);
  FD_SET(fd, &rfds);

  struct timeval tv = {5, 0};

  const int nfds = select(fd + 1, &rfds, NULL, NULL, &tv);
  EXPECT_EQ(1, nfds);

  if (nfds == 1) {
      // Read status
      const ssize_t bytes_read = read(fd, &result, sizeof(result));
      EXPECT_EQ(sizeof(result), bytes_read);
  }

  return (result);
}

}
}
}
