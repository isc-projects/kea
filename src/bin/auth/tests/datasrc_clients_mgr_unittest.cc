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

#include <exceptions/exceptions.h>

#include <dns/rrclass.h>

#include <cc/data.h>

#include <datasrc/client_list.h>

#include <auth/datasrc_clients_mgr.h>
#include "test_datasrc_clients_mgr.h"

#include <gtest/gtest.h>

#include <boost/function.hpp>

using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::auth;
using namespace isc::auth::datasrc_clientmgr_internal;

namespace {
void
shutdownCheck() {
    // Check for common points on shutdown.  The manager should have acquired
    // the lock, put a SHUTDOWN command to the queue, and should have signaled
    // the builder. It should check again for the callback queue, with the lock
    EXPECT_EQ(2, FakeDataSrcClientsBuilder::queue_mutex->lock_count);
    EXPECT_EQ(1, FakeDataSrcClientsBuilder::cond->signal_count);
    EXPECT_EQ(1, FakeDataSrcClientsBuilder::command_queue->size());
    const Command& cmd = FakeDataSrcClientsBuilder::command_queue->front();
    EXPECT_EQ(SHUTDOWN, cmd.id);
    EXPECT_FALSE(cmd.params);   // no argument

    // Finally, the manager should wait for the thread to terminate.
    EXPECT_TRUE(FakeDataSrcClientsBuilder::thread_waited);
}

// Commonly used pattern of checking member variables shared between the
// manager and builder.
void
checkSharedMembers(size_t expected_queue_lock_count,
                   size_t expected_queue_unlock_count,
                   size_t expected_map_lock_count,
                   size_t expected_map_unlock_count,
                   size_t expected_cond_signal_count,
                   size_t expected_command_queue_size)
{
    EXPECT_EQ(expected_queue_lock_count,
              FakeDataSrcClientsBuilder::queue_mutex->lock_count);
    EXPECT_EQ(expected_queue_unlock_count,
              FakeDataSrcClientsBuilder::queue_mutex->unlock_count);
    EXPECT_EQ(expected_map_lock_count,
              FakeDataSrcClientsBuilder::map_mutex->lock_count);
    EXPECT_EQ(expected_map_unlock_count,
              FakeDataSrcClientsBuilder::map_mutex->unlock_count);
    EXPECT_EQ(expected_cond_signal_count,
              FakeDataSrcClientsBuilder::cond->signal_count);
    EXPECT_EQ(expected_command_queue_size,
              FakeDataSrcClientsBuilder::command_queue->size());
}

TEST(DataSrcClientsMgrTest, start) {
    // When we create a manager, builder's run() method should be called.
    FakeDataSrcClientsBuilder::started = false;
    {
        TestDataSrcClientsMgr mgr;
        EXPECT_TRUE(FakeDataSrcClientsBuilder::started);
        EXPECT_TRUE(FakeDataSrcClientsBuilder::command_queue->empty());

        // Check pre-destroy conditions
        EXPECT_EQ(0, FakeDataSrcClientsBuilder::cond->signal_count);
        EXPECT_FALSE(FakeDataSrcClientsBuilder::thread_waited);
    } // mgr and builder have been destroyed by this point.

    // We stopped the manager implicitly (without shutdown()).  The manager
    // will internally notify it
    shutdownCheck();
}

TEST(DataSrcClientsMgrTest, shutdownWithUncaughtException) {
    // Emulating the case when the builder exists on exception.  shutdown()
    // will encounter UncaughtException exception and catch it.
    EXPECT_NO_THROW({
            TestDataSrcClientsMgr mgr;
            FakeDataSrcClientsBuilder::thread_throw_on_wait =
                FakeDataSrcClientsBuilder::THROW_UNCAUGHT_EX;
        });
}

TEST(DataSrcClientsMgrTest, shutdownWithException) {
    EXPECT_NO_THROW({
            TestDataSrcClientsMgr mgr;
            FakeDataSrcClientsBuilder::thread_throw_on_wait =
                FakeDataSrcClientsBuilder::THROW_OTHER;
        });
}

TEST(DataSrcClientsMgrTest, reconfigure) {
    TestDataSrcClientsMgr mgr;

    // Check pre-command condition
    checkSharedMembers(0, 0, 0, 0, 0, 0);

    // A valid reconfigure argument
    ConstElementPtr reconfigure_arg = Element::fromJSON(
        "{""\"IN\": [{\"type\": \"MasterFiles\", \"params\": {},"
        "             \"cache-enable\": true}]}");

    // On reconfigure(), it just send the RECONFIGURE command to the builder
    // thread with the given argument intact.
    mgr.reconfigure(reconfigure_arg);

    // The manager should have acquired the queue lock, send RECONFIGURE
    // command with the arg, wake up the builder thread by signal.  It doesn't
    // touch or refer to the map, so it shouldn't acquire the map lock.
    checkSharedMembers(1, 1, 0, 0, 1, 1);
    const Command& cmd1 = FakeDataSrcClientsBuilder::command_queue->front();
    EXPECT_EQ(RECONFIGURE, cmd1.id);
    EXPECT_EQ(reconfigure_arg, cmd1.params);

    // Non-null, but semantically invalid argument.  The manager doesn't do
    // this check, so it should result in the same effect.
    FakeDataSrcClientsBuilder::command_queue->clear();
    reconfigure_arg = isc::data::Element::create("{ \"foo\": \"bar\" }");
    mgr.reconfigure(reconfigure_arg);
    checkSharedMembers(2, 2, 0, 0, 2, 1);
    const Command& cmd2 = FakeDataSrcClientsBuilder::command_queue->front();
    EXPECT_EQ(RECONFIGURE, cmd2.id);
    EXPECT_EQ(reconfigure_arg, cmd2.params);

    // Passing NULL argument is immediately rejected
    EXPECT_THROW(mgr.reconfigure(ConstElementPtr()), isc::InvalidParameter);
    checkSharedMembers(2, 2, 0, 0, 2, 1); // no state change
}

TEST(DataSrcClientsMgrTest, holder) {
    TestDataSrcClientsMgr mgr;

    {
        // Initially it's empty, so findClientList() will always return NULL
        TestDataSrcClientsMgr::Holder holder(mgr);
        EXPECT_FALSE(holder.findClientList(RRClass::IN()));
        EXPECT_FALSE(holder.findClientList(RRClass::CH()));
        EXPECT_TRUE(holder.getClasses().empty());
        // map should be protected here
        EXPECT_EQ(1, FakeDataSrcClientsBuilder::map_mutex->lock_count);
        EXPECT_EQ(0, FakeDataSrcClientsBuilder::map_mutex->unlock_count);
    }
    // map lock has been released
    EXPECT_EQ(1, FakeDataSrcClientsBuilder::map_mutex->unlock_count);

    // Put something in, that should become visible.
    ConstElementPtr reconfigure_arg = Element::fromJSON(
        "{\"IN\": [{\"type\": \"MasterFiles\", \"params\": {},"
        "           \"cache-enable\": true}],"
        " \"CH\": [{\"type\": \"MasterFiles\", \"params\": {},"
        "           \"cache-enable\": true}]}");
    mgr.reconfigure(reconfigure_arg);
    {
        TestDataSrcClientsMgr::Holder holder(mgr);
        EXPECT_TRUE(holder.findClientList(RRClass::IN()));
        EXPECT_TRUE(holder.findClientList(RRClass::CH()));
        EXPECT_EQ(2, holder.getClasses().size());
    }
    // We need to clear command queue by hand
    FakeDataSrcClientsBuilder::command_queue->clear();

    // Replace the lists with new lists containing only one list.
    // The CH will disappear again.
    reconfigure_arg = Element::fromJSON(
        "{\"IN\": [{\"type\": \"MasterFiles\", \"params\": {},"
        "           \"cache-enable\": true}]}");
    mgr.reconfigure(reconfigure_arg);
    {
        TestDataSrcClientsMgr::Holder holder(mgr);
        EXPECT_TRUE(holder.findClientList(RRClass::IN()));
        EXPECT_FALSE(holder.findClientList(RRClass::CH()));
        EXPECT_EQ(RRClass::IN(), holder.getClasses()[0]);
    }

    // Duplicate lock acquisition is prohibited (only test mgr can detect
    // this reliably, so this test may not be that useful)
    TestDataSrcClientsMgr::Holder holder1(mgr);
    EXPECT_THROW(TestDataSrcClientsMgr::Holder holder2(mgr), isc::Unexpected);
}

TEST(DataSrcClientsMgrTest, reload) {
    TestDataSrcClientsMgr mgr;
    EXPECT_TRUE(FakeDataSrcClientsBuilder::started);
    EXPECT_TRUE(FakeDataSrcClientsBuilder::command_queue->empty());

    isc::data::ElementPtr args =
        isc::data::Element::fromJSON("{ \"class\": \"IN\","
                                     "  \"origin\": \"example.com\" }");
    mgr.loadZone(args);
    EXPECT_EQ(1, FakeDataSrcClientsBuilder::command_queue->size());
    mgr.loadZone(args);
    EXPECT_EQ(2, FakeDataSrcClientsBuilder::command_queue->size());

    // Should fail with non-string 'class' value
    args->set("class", Element::create(1));
    EXPECT_THROW(mgr.loadZone(args), CommandError);
    EXPECT_EQ(2, FakeDataSrcClientsBuilder::command_queue->size());

    // And with badclass
    args->set("class", Element::create("BADCLASS"));
    EXPECT_THROW(mgr.loadZone(args), CommandError);
    EXPECT_EQ(2, FakeDataSrcClientsBuilder::command_queue->size());

    // Should succeed without 'class'
    args->remove("class");
    mgr.loadZone(args);
    EXPECT_EQ(3, FakeDataSrcClientsBuilder::command_queue->size());

    // but fail without origin, without sending new commands
    args->remove("origin");
    EXPECT_THROW(mgr.loadZone(args), CommandError);
    EXPECT_EQ(3, FakeDataSrcClientsBuilder::command_queue->size());

    // And for 'origin' that is not a string
    args->set("origin", Element::create(1));
    EXPECT_THROW(mgr.loadZone(args), CommandError);
    EXPECT_EQ(3, FakeDataSrcClientsBuilder::command_queue->size());

    // And origin that is not a correct name
    args->set("origin", Element::create(".."));
    EXPECT_THROW(mgr.loadZone(args), CommandError);
    EXPECT_EQ(3, FakeDataSrcClientsBuilder::command_queue->size());

    // same for empty data and data that is not a map
    EXPECT_THROW(mgr.loadZone(isc::data::ConstElementPtr()), CommandError);
    EXPECT_THROW(mgr.loadZone(isc::data::Element::createList()), CommandError);
    EXPECT_EQ(3, FakeDataSrcClientsBuilder::command_queue->size());
}

TEST(DataSrcClientsMgrTest, segmentUpdate) {
    TestDataSrcClientsMgr mgr;
    EXPECT_TRUE(FakeDataSrcClientsBuilder::started);
    EXPECT_TRUE(FakeDataSrcClientsBuilder::command_queue->empty());

    isc::data::ElementPtr args =
        isc::data::Element::fromJSON("{\"data-source-class\": \"IN\","
                                     " \"data-source-name\": \"sqlite3\","
                                     " \"segment-params\": {}}");
    mgr.segmentInfoUpdate(args);
    EXPECT_EQ(1, FakeDataSrcClientsBuilder::command_queue->size());
    // Some invalid inputs
    EXPECT_THROW(mgr.segmentInfoUpdate(isc::data::Element::fromJSON(
        "{\"data-source-class\": \"IN\","
        " \"data-source-name\": \"sqlite3\"}")), CommandError);
    EXPECT_THROW(mgr.segmentInfoUpdate(isc::data::Element::fromJSON(
        "{\"data-source-name\": \"sqlite3\","
        " \"segment-params\": {}}")), CommandError);
    EXPECT_THROW(mgr.segmentInfoUpdate(isc::data::Element::fromJSON(
        "{\"data-source-class\": \"IN\","
        " \"segment-params\": {}}")), CommandError);
    EXPECT_EQ(1, FakeDataSrcClientsBuilder::command_queue->size());
}

void
callback(bool* called, int *tag_target, int tag_value) {
    *called = true;
    *tag_target = tag_value;
}

// Test we can wake up the main thread by writing to the file descriptor and
// that the callbacks are executed and removed when woken up.
TEST(DataSrcClientsMgrTest, wakeup) {
    bool called = false;
    int tag;
    {
        TestDataSrcClientsMgr mgr;
        // There's some real file descriptor (or something that looks so)
        ASSERT_GT(FakeDataSrcClientsBuilder::wakeup_fd, 0);
        // Push a callback in and wake the manager
        FakeDataSrcClientsBuilder::callback_queue->
            push_back(boost::bind(callback, &called, &tag, 1));
        EXPECT_EQ(1, write(FakeDataSrcClientsBuilder::wakeup_fd, "w", 1));
        mgr.run_one();
        EXPECT_TRUE(called);
        EXPECT_EQ(1, tag);
        EXPECT_TRUE(FakeDataSrcClientsBuilder::callback_queue->empty());

        called = false;
        // If we wake up and don't push anything, it doesn't break.
        EXPECT_EQ(1, write(FakeDataSrcClientsBuilder::wakeup_fd, "w", 1));
        mgr.run_one();
        EXPECT_FALSE(called);

        // When we terminate, it should process whatever is left
        // of the callbacks. So push and terminate (and don't directly
        // wake).
        FakeDataSrcClientsBuilder::callback_queue->
            push_back(boost::bind(callback, &called, &tag, 2));
    }
    EXPECT_TRUE(called);
    EXPECT_EQ(2, tag);
    EXPECT_TRUE(FakeDataSrcClientsBuilder::callback_queue->empty());
}

TEST(DataSrcClientsMgrTest, realThread) {
    // Using the non-test definition with a real thread.  Just checking
    // no disruption happens.
    isc::asiolink::IOService service;
    DataSrcClientsMgr mgr(service);
}

} // unnamed namespace
