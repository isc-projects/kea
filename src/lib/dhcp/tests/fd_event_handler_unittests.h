// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/fd_event_handler.h>
#include <dhcp/select_event_handler.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

const unsigned char MARKER = 0;

namespace {

// Just a NOP function to ignore a signal but let it interrupt function.
void no_handler(int) { }

/// @brief Shared test fixture for testing code using fd event handlers.
class FDEventHandlerTest : public ::testing::Test {
public:
    /// @brief Constructor.
    FDEventHandlerTest() {
        handler_.reset(new isc::dhcp::FDEventHandlerType);
        pipe(pipefd);
    }

    /// @brief Destructor.
    ~FDEventHandlerTest() {
        close(pipefd[1]);
        close(pipefd[0]);
    }

    /// @brief The tested fd event handler.
    FDEventHandlerPtr handler_;

    /// @brief The pipe used tor testing read and write operations.
    int pipefd[2];
};

TEST_F(FDEventHandlerTest, events) {
    EXPECT_NO_THROW(handler_->clear());

    EXPECT_EQ(0, handler_->waitEvent(0, 1000));

    handler_->add(pipefd[0], true, false);
    handler_->add(pipefd[1], false, true);

    EXPECT_FALSE(handler_->readReady(pipefd[0]));
    EXPECT_FALSE(handler_->writeReady(pipefd[0]));
    EXPECT_FALSE(handler_->readReady(pipefd[1]));
    EXPECT_FALSE(handler_->writeReady(pipefd[1]));

    EXPECT_EQ(1, handler_->waitEvent(0, 1000));

    EXPECT_FALSE(handler_->readReady(pipefd[0]));
    EXPECT_FALSE(handler_->writeReady(pipefd[0]));
    EXPECT_FALSE(handler_->readReady(pipefd[1]));
    EXPECT_TRUE(handler_->writeReady(pipefd[1]));

    EXPECT_EQ(1, write(pipefd[1], &MARKER, sizeof(MARKER)));

    EXPECT_EQ(2, handler_->waitEvent(0, 1000));

    EXPECT_TRUE(handler_->readReady(pipefd[0]));
    EXPECT_FALSE(handler_->writeReady(pipefd[0]));
    EXPECT_FALSE(handler_->readReady(pipefd[1]));
    EXPECT_TRUE(handler_->writeReady(pipefd[1]));

    EXPECT_EQ(1, write(pipefd[1], &MARKER, sizeof(MARKER)));

    EXPECT_EQ(2, handler_->waitEvent(0, 1000));

    EXPECT_TRUE(handler_->readReady(pipefd[0]));
    EXPECT_FALSE(handler_->writeReady(pipefd[0]));
    EXPECT_FALSE(handler_->readReady(pipefd[1]));
    EXPECT_TRUE(handler_->writeReady(pipefd[1]));

    unsigned char data;

    EXPECT_EQ(1, read(pipefd[0], &data, sizeof(data)));

    EXPECT_EQ(2, handler_->waitEvent(0, 1000));

    EXPECT_TRUE(handler_->readReady(pipefd[0]));
    EXPECT_FALSE(handler_->writeReady(pipefd[0]));
    EXPECT_FALSE(handler_->readReady(pipefd[1]));
    EXPECT_TRUE(handler_->writeReady(pipefd[1]));

    EXPECT_EQ(1, read(pipefd[0], &data, sizeof(data)));

    EXPECT_EQ(1, handler_->waitEvent(0, 1000));

    EXPECT_FALSE(handler_->readReady(pipefd[0]));
    EXPECT_FALSE(handler_->writeReady(pipefd[0]));
    EXPECT_FALSE(handler_->readReady(pipefd[1]));
    EXPECT_TRUE(handler_->writeReady(pipefd[1]));

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

} // end of anonymous namespace
