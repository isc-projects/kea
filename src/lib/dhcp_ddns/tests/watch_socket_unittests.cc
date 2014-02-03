// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <dhcp_ddns/watch_socket.h>

#include <gtest/gtest.h>

#include <sys/select.h>
#include <sys/ioctl.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp_ddns;

namespace {

/// @brief Returns the result of select() given an fd to check for read status.
///
/// @param fd_to_check The file descriptor to test
/// @return Returns less than one on an error, 0 if the fd is not ready to
/// read, > 0 if it is ready to read. 
int selectCheck(int fd_to_check). 

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


/// @brief Tests the basic functionality of WatchSocket.
TEST(WatchSocketTest, basics) {
    WatchSocketPtr watch;

    /// Verify that we can construct a WatchSocket.
    ASSERT_NO_THROW(watch.reset(new WatchSocket()));
    ASSERT_TRUE(watch);

    /// Verify that post-construction the state the select-fd is valid.
    int select_fd = watch->getSelectFd();
    EXPECT_NE(select_fd, WatchSocket::INVALID_SOCKET);
   
    /// Verify that isReady() is false and that a call to select agrees. 
    EXPECT_FALSE(watch->isReady());
    EXPECT_EQ(0, selectCheck(select_fd));

    /// Verify that the socket can be marked ready.
    ASSERT_NO_THROW(watch->markReady());

    /// Verify that we have exactly one marker waiting to be read.
    int count = 0;
    EXPECT_FALSE(ioctl(select_fd, FIONREAD, &count));
    EXPECT_EQ(sizeof(WatchSocket::MARKER), count);

    /// Verify that we can call markReady again without error.
    ASSERT_NO_THROW(watch->markReady());

    /// Verify that we STILL have exactly one marker waiting to be read.
    EXPECT_FALSE(ioctl(select_fd, FIONREAD, &count));
    EXPECT_EQ(sizeof(WatchSocket::MARKER), count);

    /// Verify that isReady() is true and that a call to select agrees. 
    EXPECT_TRUE(watch->isReady());
    EXPECT_EQ(1, selectCheck(select_fd));

    /// Verify that the socket can be cleared.
    ASSERT_NO_THROW(watch->clearReady());

    /// Verify that isReady() is false and that a call to select agrees. 
    EXPECT_FALSE(watch->isReady());
    EXPECT_EQ(0, selectCheck(select_fd));
}

} // end of anonymous namespace
