// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/fd_event_handler.h>
#ifdef HAVE_EPOLL
#include <util/epoll_event_handler.h>
#endif
#ifdef HAVE_KQUEUE
#include <util/kqueue_event_handler.h>
#endif
#include <util/poll_event_handler.h>
#include <util/select_event_handler.h>

#include <gtest/gtest.h>

#include <thread>
#include <vector>

#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>

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
        pipe(pipe_fd_);
    }

    /// @brief Destructor.
    ~FDEventHandlerTest() {
        close(pipe_fd_[1]);
        close(pipe_fd_[0]);
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
    // epoll does not allow add of /dev/zero to registered events.
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
        EXPECT_TRUE(handler_->hasError(fd));
        EXPECT_EQ(0, errno);
    } else {
        EXPECT_EQ(-1, handler_->waitEvent(0, 1000));
        EXPECT_FALSE(handler_->readReady(fd));
        EXPECT_TRUE(handler_->hasError(fd));
        EXPECT_EQ(EBADF, errno);
    }

    close(pipe_fd_[1]);
    pipe(pipe_fd_);

    EXPECT_NO_THROW(handler_->clear());
    errno = 0;

    {
        EXPECT_NO_THROW(handler_->add(pipe_fd_[0]));

        std::thread tr([this]() {
            usleep(500);
            close(pipe_fd_[1]);
        });

        EXPECT_EQ(1, handler_->waitEvent(1, 0));

        EXPECT_EQ(0, errno);

        EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
        EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));

        tr.join();

        close(pipe_fd_[0]);
        pipe(pipe_fd_);
    }

    EXPECT_NO_THROW(handler_->clear());
    errno = 0;

    {
        EXPECT_NO_THROW(handler_->add(pipe_fd_[0]));

        std::thread tr([this]() {
            usleep(500);
            close(pipe_fd_[0]);
        });

        if (handler_->type() == FDEventHandler::TYPE_SELECT) {
#if defined(OS_LINUX)
            EXPECT_EQ(1, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
#else
            EXPECT_EQ(-1, handler_->waitEvent(1, 0));

            EXPECT_EQ(EBADF, errno);

            // on error readReady is not actually returning the new state,
            // but the read flag added before wait for the fd.
            EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
#endif
        } else if (handler_->type() == FDEventHandler::TYPE_POLL) {
#if defined(OS_LINUX)
            EXPECT_EQ(1, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_FALSE(handler_->readReady(pipe_fd_[0]));
            EXPECT_TRUE(handler_->hasError(pipe_fd_[0]));
#else
            EXPECT_EQ(0, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_FALSE(handler_->readReady(pipe_fd_[0]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
#endif
        } else {
            EXPECT_EQ(0, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_FALSE(handler_->readReady(pipe_fd_[0]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));
        }

        tr.join();

        close(pipe_fd_[1]);
        pipe(pipe_fd_);
    }

    EXPECT_NO_THROW(handler_->clear());
    errno = 0;

    {
        EXPECT_NO_THROW(handler_->add(pipe_fd_[1]));

        std::thread tr([this]() {
            usleep(500);
            close(pipe_fd_[1]);
        });

        if (handler_->type() == FDEventHandler::TYPE_SELECT) {
#if defined(OS_LINUX)
            EXPECT_EQ(1, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_TRUE(handler_->readReady(pipe_fd_[1]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));
#else
            EXPECT_EQ(-1, handler_->waitEvent(1, 0));

            EXPECT_EQ(EBADF, errno);

            // on error readReady is not actually returning the new state,
            // but the read flag added before wait for the fd.
            EXPECT_TRUE(handler_->readReady(pipe_fd_[1]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));
#endif
        } else if (handler_->type() == FDEventHandler::TYPE_POLL) {
#if defined(OS_LINUX)
            EXPECT_EQ(1, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
            EXPECT_TRUE(handler_->hasError(pipe_fd_[1]));
#else
            EXPECT_EQ(0, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));
#endif
        } else {
            EXPECT_EQ(0, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));
        }

        tr.join();

        close(pipe_fd_[0]);
        pipe(pipe_fd_);
    }

    EXPECT_NO_THROW(handler_->clear());
    errno = 0;

    {
        EXPECT_NO_THROW(handler_->add(pipe_fd_[1]));

        std::thread tr([this]() {
            usleep(500);
            close(pipe_fd_[0]);
        });
        if (handler_->type() == FDEventHandler::TYPE_POLL) {
            EXPECT_EQ(1, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

#if defined(OS_LINUX)
            EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
            EXPECT_TRUE(handler_->hasError(pipe_fd_[1]));
#else
            EXPECT_TRUE(handler_->readReady(pipe_fd_[1]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));
#endif
        } else if (handler_->type() == FDEventHandler::TYPE_EPOLL) {
            EXPECT_EQ(1, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_FALSE(handler_->readReady(pipe_fd_[1]));
            EXPECT_TRUE(handler_->hasError(pipe_fd_[1]));
        } else {
            EXPECT_EQ(1, handler_->waitEvent(1, 0));

            EXPECT_EQ(0, errno);

            EXPECT_TRUE(handler_->readReady(pipe_fd_[1]));
            EXPECT_FALSE(handler_->hasError(pipe_fd_[1]));
        }

        tr.join();

        close(pipe_fd_[1]);
        pipe(pipe_fd_);
    }
}

TEST_F(FDEventHandlerTest, hup) {
    EXPECT_NO_THROW(handler_->add(pipe_fd_[0]));
    close(pipe_fd_[1]);
    EXPECT_EQ(1, handler_->waitEvent(0, 1000));
    EXPECT_TRUE(handler_->readReady(pipe_fd_[0]));
    EXPECT_FALSE(handler_->hasError(pipe_fd_[0]));

    close(pipe_fd_[0]);
    pipe(pipe_fd_);
}

TEST_F(FDEventHandlerTest, noLimit) {
    if (handler_->type() != FDEventHandler::TYPE_SELECT) {
        vector<int> fds;
        const size_t limit = 2  * FD_SETSIZE;
        int result;
        for (size_t i = 0; i < limit; ++i) {
            int pipe_fd[2];
            result = pipe(pipe_fd);
            if (result < 0) {
                for (size_t j = 0; j < fds.size(); ++j) {
                    close(fds[j]);
                }
                ASSERT_GT(result, 0);
            }
            fds.push_back(pipe_fd[0]);
            EXPECT_EQ(sizeof(i), write(pipe_fd[1], &i, sizeof(i)));
            fds.push_back(pipe_fd[1]);
            EXPECT_NO_THROW(handler_->add(pipe_fd[0]));
        }
        EXPECT_EQ(limit, handler_->waitEvent(0, 1000));
        for (size_t i = 0; i < fds.size(); i += 2) {
            size_t data = 0;
            EXPECT_EQ(sizeof(i), read(fds[i], &data, sizeof(data)));
            EXPECT_EQ(data, i / 2);
            close(fds[i]);
            close(fds[i + 1]);
        }
    }
}

} // end of anonymous namespace
