// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>

#include <auth/datasrc_clients_mgr.h>
#include "test_datasrc_clients_mgr.h"

#include <gtest/gtest.h>

#include <boost/function.hpp>

using isc::data::ConstElementPtr;
using namespace isc::auth::internal;

namespace {
class DataSrcClientsBuilderTest : public ::testing::Test {
protected:
    DataSrcClientsBuilderTest() :
        builder(&command_queue, &cond, &queue_mutex),
        cond(command_queue, delayed_command_queue),
        shutdown_cmd(SHUTDOWN, ConstElementPtr()),
        noop_cmd(NOOP, ConstElementPtr())
    {}

    TestDataSrcClientsBuilder builder;
    std::list<Command> command_queue; // test command queue
    std::list<Command> delayed_command_queue; // commands available after wait
    TestCondVar cond;
    TestMutex queue_mutex;
    const Command shutdown_cmd;
    const Command noop_cmd;
};

TEST_F(DataSrcClientsBuilderTest, runSingleCommand) {
    // A simplest case, just to check the basic behavior.
    command_queue.push_back(shutdown_cmd);
    builder.run();
    EXPECT_TRUE(command_queue.empty());
    EXPECT_EQ(0, cond.wait_count); // no wait because command queue is not empty
    EXPECT_EQ(1, queue_mutex.lock_count);
    EXPECT_EQ(1, queue_mutex.unlock_count);
}

TEST_F(DataSrcClientsBuilderTest, runMultiCommands) {
    // Two NOOP commands followed by SHUTDOWN.  We should see two doNoop()
    // calls.
    command_queue.push_back(noop_cmd);
    command_queue.push_back(noop_cmd);
    command_queue.push_back(shutdown_cmd);
    builder.run();
    EXPECT_TRUE(command_queue.empty());
    EXPECT_EQ(1, queue_mutex.lock_count);
    EXPECT_EQ(1, queue_mutex.unlock_count);
    EXPECT_EQ(2, queue_mutex.noop_count);
}

TEST_F(DataSrcClientsBuilderTest, condWait) {
    // command_queue is originally empty, so it will require waiting on
    // condvar.  specialized wait() will make the delayed command available.
    delayed_command_queue.push_back(shutdown_cmd);
    builder.run();

    // There should be one call to wait()
    EXPECT_EQ(1, cond.wait_count);
    // wait() effectively involves one more set of lock/unlock, so we have
    // two in total
    EXPECT_EQ(2, queue_mutex.lock_count);
    EXPECT_EQ(2, queue_mutex.unlock_count);
}

TEST_F(DataSrcClientsBuilderTest, shutdown) {
    EXPECT_FALSE(builder.handleCommand(shutdown_cmd));
}

} // unnamed namespace
