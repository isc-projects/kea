// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <config.h>
#include <util/watch_socket.h>

#include <gtest/gtest.h>

#include <sys/select.h>
#include <sys/ioctl.h>

#ifdef HAVE_SYS_FILIO_H
// FIONREAD is here on Solaris
#include <sys/filio.h>
#endif

using namespace std;
using namespace isc;
using namespace isc::util;

namespace {

/// @brief Returns the result of select() given an fd to check for read status.
///
/// @param fd_to_check The file descriptor to test
///
/// @return Returns less than one on an error, 0 if the fd is not ready to
/// read, > 0 if it is ready to read. 
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
    EXPECT_NE(select_fd, WatchSocket::SOCKET_NOT_VALID);

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

/// @brief Checks behavior when select_fd is closed externally while in the
/// "cleared" state.
TEST(WatchSocketTest, closedWhileClear) {
    WatchSocketPtr watch;

    /// Verify that we can construct a WatchSocket.
    ASSERT_NO_THROW(watch.reset(new WatchSocket()));
    ASSERT_TRUE(watch);

    /// Verify that post-construction the state the select-fd is valid.
    int select_fd = watch->getSelectFd();
    ASSERT_NE(select_fd, WatchSocket::SOCKET_NOT_VALID);

    // Verify that socket does not appear ready.
    ASSERT_EQ(0, watch->isReady());

    // Interfere by closing the fd.
    ASSERT_EQ(0, close(select_fd));

    // Verify that socket does not appear ready.
    ASSERT_EQ(0, watch->isReady());

    // Verify that clear does NOT throw.
    ASSERT_NO_THROW(watch->clearReady());

    // Verify that trying to mark it fails.
    ASSERT_THROW(watch->markReady(), WatchSocketError);

    // Verify that clear does NOT throw.
    ASSERT_NO_THROW(watch->clearReady());

    // Verify that getSelectFd() returns invalid socket.
    ASSERT_EQ(WatchSocket::SOCKET_NOT_VALID, watch->getSelectFd());
}

/// @brief Checks behavior when select_fd has closed while in the "ready"
/// state.
TEST(WatchSocketTest, closedWhileReady) {
    WatchSocketPtr watch;

    /// Verify that we can construct a WatchSocket.
    ASSERT_NO_THROW(watch.reset(new WatchSocket()));
    ASSERT_TRUE(watch);

    /// Verify that post-construction the state the select-fd is valid.
    int select_fd = watch->getSelectFd();
    ASSERT_NE(select_fd, WatchSocket::SOCKET_NOT_VALID);

    /// Verify that the socket can be marked ready.
    ASSERT_NO_THROW(watch->markReady());
    EXPECT_EQ(1, selectCheck(select_fd));

    // Interfere by closing the fd.
    ASSERT_EQ(0, close(select_fd));

    // Verify that trying to clear it does not throw.
    ASSERT_NO_THROW(watch->clearReady());

    // Verify the select_fd fails as socket is invalid/closed.
    EXPECT_EQ(-1, selectCheck(select_fd));

    // Verify that subsequent attempts to mark it will fail.
    ASSERT_THROW(watch->markReady(), WatchSocketError);
}

/// @brief Checks behavior when select_fd has been marked ready but then
/// emptied by an external read.
TEST(WatchSocketTest, emptyReadySelectFd) {
    WatchSocketPtr watch;

    /// Verify that we can construct a WatchSocket.
    ASSERT_NO_THROW(watch.reset(new WatchSocket()));
    ASSERT_TRUE(watch);

    /// Verify that post-construction the state the select-fd is valid.
    int select_fd = watch->getSelectFd();
    ASSERT_NE(select_fd, WatchSocket::SOCKET_NOT_VALID);

    /// Verify that the socket can be marked ready.
    ASSERT_NO_THROW(watch->markReady());
    EXPECT_EQ(1, selectCheck(select_fd));

    // Interfere by reading the fd. This should empty the read pipe.
    uint32_t buf = 0;
    ASSERT_EQ((read (select_fd, &buf, sizeof(buf))), sizeof(buf));
    ASSERT_EQ(WatchSocket::MARKER, buf);

    // Really nothing that can be done to protect against this, but let's
    // make sure we aren't in a weird state.
    ASSERT_NO_THROW(watch->clearReady());

    // Verify the select_fd fails as socket is invalid/closed.
    EXPECT_EQ(0, selectCheck(select_fd));

    // Verify that getSelectFd() returns is still good.
    ASSERT_EQ(select_fd, watch->getSelectFd());
}

/// @brief Checks behavior when select_fd has been marked ready but then
/// contents have been "corrupted" by a partial read.
TEST(WatchSocketTest, badReadOnClear) {
    WatchSocketPtr watch;

    /// Verify that we can construct a WatchSocket.
    ASSERT_NO_THROW(watch.reset(new WatchSocket()));
    ASSERT_TRUE(watch);

    /// Verify that post-construction the state the select-fd is valid.
    int select_fd = watch->getSelectFd();
    ASSERT_NE(select_fd, WatchSocket::SOCKET_NOT_VALID);

    /// Verify that the socket can be marked ready.
    ASSERT_NO_THROW(watch->markReady());
    EXPECT_EQ(1, selectCheck(select_fd));

    // Interfere by reading the fd. This should empty the read pipe.
    uint32_t buf = 0;
    ASSERT_EQ((read (select_fd, &buf, 1)), 1);
    ASSERT_NE(WatchSocket::MARKER, buf);

    // Really nothing that can be done to protect against this, but let's
    // make sure we aren't in a weird state.
    /// @todo maybe clear should never throw, log only
    ASSERT_THROW(watch->clearReady(), WatchSocketError);

    // Verify the select_fd does not evalute to ready.
    EXPECT_NE(1, selectCheck(select_fd));

    // Verify that getSelectFd() returns INVALID.
    ASSERT_EQ(WatchSocket::SOCKET_NOT_VALID, watch->getSelectFd());

    // Verify that subsequent attempt to mark it fails.
    ASSERT_THROW(watch->markReady(), WatchSocketError);
}

/// @brief Checks if the socket can be explicitly closed.
TEST(WatchSocketTest, explicitClose) {
    WatchSocketPtr watch;

    // Create new instance of the socket.
    ASSERT_NO_THROW(watch.reset(new WatchSocket()));
    ASSERT_TRUE(watch);

    // Make sure it has been opened by checking that its descriptor
    // is valid.
    EXPECT_NE(watch->getSelectFd(), WatchSocket::SOCKET_NOT_VALID);

    // Close the socket.
    std::string error_string;
    ASSERT_TRUE(watch->closeSocket(error_string));

    // Make sure that the descriptor is now invalid which indicates
    // that the socket has been closed.
    EXPECT_EQ(WatchSocket::SOCKET_NOT_VALID, watch->getSelectFd());
    // No errors should be reported.
    EXPECT_TRUE(error_string.empty());
}

} // end of anonymous namespace
