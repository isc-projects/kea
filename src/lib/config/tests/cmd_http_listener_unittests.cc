// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/cmd_http_listener.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::config;
using namespace isc::data;

namespace {

/// Verifies the construction, starting, stopping, destruction
/// the CmdHttpListener class.
TEST(CmdHttpListener, basics) {
    CmdHttpListenerPtr listener;
    asiolink::IOAddress address("127.0.0.1");
    uint16_t port = 8080;

    // Make sure we can create one.
    ASSERT_NO_THROW_LOG(listener.reset(new CmdHttpListener(address, port)));
    ASSERT_TRUE(listener);

    // Verify the getters get what we expect.
    EXPECT_EQ(listener->getAddress(), address);
    EXPECT_EQ(listener->getPort(), port);
    EXPECT_EQ(listener->getThreadPoolSize(), 1);

    // It should not be listening and have no threads.
    EXPECT_FALSE(listener->isListening());
    EXPECT_EQ(listener->getThreadCount(), 0);

    // Make sure we can start it and it's listening with 1 thread.
    ASSERT_NO_THROW_LOG(listener->start());
    ASSERT_TRUE(listener->isListening());
    EXPECT_EQ(listener->getThreadCount(), 1);

    // Trying to start it again should fail.
    ASSERT_THROW_MSG(listener->start(), InvalidOperation,
                     "CmdHttpListener is already listening!");

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(listener->stop());
    ASSERT_FALSE(listener->isListening());
    EXPECT_EQ(listener->getThreadCount(), 0);

    // Make sure we can call stop again without problems.
    ASSERT_NO_THROW_LOG(listener->stop());

    // We should be able to restart it.
    ASSERT_NO_THROW_LOG(listener->start());
    ASSERT_TRUE(listener->isListening());
    EXPECT_EQ(listener->getThreadCount(), 1);

    // Destroying it should also stop it.
    // If the test timeouts we know it didn't!
    ASSERT_NO_THROW_LOG(listener.reset());

    // Verify we can construct with more than one thread.
    ASSERT_NO_THROW_LOG(listener.reset(new CmdHttpListener(address, port, 4)));
    ASSERT_NO_THROW_LOG(listener->start());
    EXPECT_EQ(listener->getAddress(), address);
    EXPECT_EQ(listener->getPort(), port);
    EXPECT_EQ(listener->getThreadPoolSize(), 4);
    ASSERT_TRUE(listener->isListening());
    EXPECT_EQ(listener->getThreadCount(), 4);

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(listener->stop());
    ASSERT_FALSE(listener->isListening());
    EXPECT_EQ(listener->getThreadCount(), 0);
}

} // end of anonymous namespace
