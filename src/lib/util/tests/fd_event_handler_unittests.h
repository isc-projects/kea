// Copyright (C) 2012-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <testutils/gtest_utils.h>
#include <util/fd_event_handler.h>
#include <util/poll_event_handler.h>
#include <util/select_event_handler.h>

#include <gtest/gtest.h>

#include <cstring>
#include <thread>
#include <vector>

#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/resource.h>

using namespace isc;
using namespace isc::util;
using namespace std;

const unsigned char MARKER = 0;

namespace {

// Just a NOP function to ignore a signal but let it interrupt function.
void no_handler(int) { }

/// @brief Shared test fixture for testing code using fd event handlers.
class FDEventHandlerTest : public ::testing::Test {
public:
    /// @brief Constructor.
    FDEventHandlerTest() {
        handler_.reset(new FDEventHandlerType);
        EXPECT_EQ(pipe(pipe_fd_), 0);
    }

    /// @brief Destructor.
    ~FDEventHandlerTest() {
        close(pipe_fd_[1]);
        close(pipe_fd_[0]);
    }

    /// @brief Indicates if current user is not root
    ///
    /// @return True if neither the uid or the effective
    /// uid is root.
    static bool notRoot() {
        return (getuid() != 0 && geteuid() != 0);
    }

    /// @brief The tested fd event handler.
    FDEventHandlerPtr handler_;

    /// @brief The pipe used for testing read and write operations.
    int pipe_fd_[2];
};

TEST_F(FDEventHandlerTest, events) {
    EXPECT_NO_THROW(handler_->clear());

    EXPECT_EQ(0, handler_->waitEvent(0, 1000));

    EXPECT_THROW(handler_->add(-1), BadValue);
    EXPECT_THROW(handler_->readReady(-1), BadValue);
    EXPECT_THROW(handler_->hasError(-1), BadValue);

    EXPECT_NO_THROW(handler_->add(pipe_fd_[0]));

    EXPECT_FALSE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
    EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));

    EXPECT_EQ(0, handler_->waitEvent(0, 1000));

    EXPECT_FALSE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
    EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));

    EXPECT_EQ(1, write(pipe_fd_[1], &MARKER, sizeof(MARKER)));

    EXPECT_EQ(1, handler_->waitEvent(0, 1000));

    EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
    EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));

    EXPECT_EQ(1, write(pipe_fd_[1], &MARKER, sizeof(MARKER)));

    EXPECT_EQ(1, handler_->waitEvent(0, 1000));

    EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
    EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));

    unsigned char data;

    EXPECT_EQ(1, read(pipe_fd_[0], &data, sizeof(data)));

    EXPECT_EQ(1, handler_->waitEvent(0, 1000));

    EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
    EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));

    EXPECT_EQ(1, read(pipe_fd_[0], &data, sizeof(data)));

    EXPECT_EQ(0, handler_->waitEvent(0, 1000));

    EXPECT_FALSE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
    EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));

    EXPECT_NO_THROW(handler_->clear());

    EXPECT_EQ(0, handler_->waitEvent(0, 1000));
}

TEST_F(FDEventHandlerTest, signals) {
    struct sigaction ignored, original;
    memset(&ignored, 0, sizeof ignored);
    ignored.sa_handler = no_handler;
    sigaction(SIGINT, &ignored, &original);

    auto tid = pthread_self();
    sigset_t sset;
    sigset_t osset;
    sigemptyset(&sset);
    sigaddset(&sset, SIGINT);
    pthread_sigmask(SIG_BLOCK, &sset, &osset);
    std::thread tr([&tid]() {
        usleep(500);
        pthread_kill(tid, SIGINT);
    });

    pthread_sigmask(SIG_SETMASK, &osset, 0);

    EXPECT_EQ(-1, handler_->waitEvent(1, 0));

    EXPECT_EQ(errno, EINTR);

    tr.join();

    sigaction(SIGINT, &original, NULL);
}

TEST_F(FDEventHandlerTest, badFD) {
    errno = 0;
    int fd = pipe_fd_[0];
    // some event handlers do not allow add of /dev/zero to registered events.
    EXPECT_EQ(1, write(pipe_fd_[1], &MARKER, sizeof(MARKER)));

    ASSERT_GE(fd, 0);

    EXPECT_NO_THROW(handler_->add(fd));

    EXPECT_EQ(1, handler_->waitEvent(0, 1000));

    EXPECT_TRUE(handler_->readReady(fd));
    EXPECT_FALSE(handler_->hasError(fd));

    close(fd);

    int len = 0;
    int result = ioctl(fd, FIONREAD, &len);

    EXPECT_EQ(-1, result);

    EXPECT_EQ(0, len);

    EXPECT_EQ(EBADF, errno);

    errno = 0;

    if (handler_->type() == FDEventHandler::TYPE_SELECT) {
        EXPECT_EQ(-1, handler_->waitEvent(0, 1000));
        // on error readReady is not actually returning the new state,
        // but the read flag added before wait for the fd.
        EXPECT_TRUE(handler_->readReady(fd));
        EXPECT_FALSE(handler_->hasError(fd));
        EXPECT_EQ(EBADF, errno);
    } else if (handler_->type() == FDEventHandler::TYPE_POLL) {
        EXPECT_EQ(1, handler_->waitEvent(0, 1000));
        EXPECT_FALSE(handler_->readReady(fd));
        EXPECT_FALSE(handler_->hasError(fd));
        EXPECT_EQ(0, errno);
    }

    close(pipe_fd_[1]);
    EXPECT_EQ(pipe(pipe_fd_), 0);
}

TEST_F(FDEventHandlerTest, hup) {
    EXPECT_NO_THROW(handler_->add(pipe_fd_[0]));
    close(pipe_fd_[1]);
    EXPECT_EQ(1, handler_->waitEvent(0, 1000));
    EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));

    close(pipe_fd_[0]);
    EXPECT_EQ(pipe(pipe_fd_), 0);
}

TEST_F(FDEventHandlerTest, noLimit) {
    SKIP_IF(notRoot());
    struct rlimit old_l;
    struct rlimit new_l;
    int result = 0;
    result = getrlimit(RLIMIT_NOFILE, &old_l);
    ASSERT_GE(0, result) << "error: " << strerror(errno);
    new_l.rlim_cur = 16 * FD_SETSIZE;
    new_l.rlim_max = 16 * FD_SETSIZE;
    result = setrlimit(RLIMIT_NOFILE, &new_l);
    ASSERT_GE(0, result) << "error: " << strerror(errno);
    if (handler_->type() != FDEventHandler::TYPE_SELECT) {
        vector<int> fds;
        const size_t limit = 2 * FD_SETSIZE;
        for (size_t i = 0; i < limit; ++i) {
            int pipe_fd[2];
            result = pipe(pipe_fd);
            if (result < 0) {
                for (size_t j = 0; j < fds.size(); ++j) {
                    close(fds[j]);
                }
                ASSERT_GE(0, result) << "error: " << strerror(errno);
            }
            fds.push_back(pipe_fd[0]);
            EXPECT_EQ(sizeof(i), write(pipe_fd[1], &i, sizeof(i)));
            fds.push_back(pipe_fd[1]);
            EXPECT_NO_THROW(handler_->add(pipe_fd[0]));
        }
        EXPECT_EQ(limit, handler_->waitEvent(0, 1000));
        for (size_t i = 0; i < fds.size(); i += 2) {
            bool ready = handler_->readReady(fds[i]);
            EXPECT_TRUE(ready);
            EXPECT_FALSE(handler_->hasError(fds[i]));
            size_t data = 0;
            if (ready) {
                EXPECT_EQ(sizeof(i), read(fds[i], &data, sizeof(data)));
            }
            EXPECT_EQ(data, i / 2);
            close(fds[i]);
            close(fds[i + 1]);
        }
    }
    result = setrlimit(RLIMIT_NOFILE, &old_l);
    ASSERT_GE(0, result) << "error: " << strerror(errno);
}

} // end of anonymous namespace
