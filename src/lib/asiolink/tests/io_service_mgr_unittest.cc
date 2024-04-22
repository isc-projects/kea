// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_mgr.h>

#include <gtest/gtest.h>

using namespace isc::asiolink;

namespace {

// Test if IOServiceMgr behaves like a singleton.
TEST(IOServiceMgr, singleton) {
    IOServiceMgr& one(IOServiceMgr::instance());
    IOServiceMgr& two(IOServiceMgr::instance());
    EXPECT_EQ(&one, &two);
    EXPECT_FALSE(std::is_copy_constructible<IOServiceMgr>::value);
}

// Test exceptional cases.
TEST(IOServiceMgr, noError) {
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);
    // Regiter null IOService.
    ASSERT_NO_THROW(IOServiceMgr::instance().registerIOService(IOServicePtr()));
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);
    // Unregister null IOService.
    ASSERT_NO_THROW(IOServiceMgr::instance().unregisterIOService(IOServicePtr()));
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);
    // Unregister not registered IOService.
    ASSERT_NO_THROW(IOServiceMgr::instance().unregisterIOService(IOServicePtr(new IOService())));
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);
}

// Create two IOService objects in a local scope and check that all events
// already registered are handled after local scope ends.
TEST(IOServiceMgr, testIOServiceMgrLocalIOServies) {
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);
    int one_io_callback_count = 0;
    auto one_f = [&one_io_callback_count] () {
        one_io_callback_count++;
    };
    int two_io_callback_count = 0;
    auto two_f = [&two_io_callback_count] () {
        two_io_callback_count++;
    };

    {
        IOServicePtr one_io_service(new IOService());
        one_io_service->post(one_f);

        IOServicePtr two_io_service(new IOService());
        two_io_service->post(two_f);

        IOServiceMgr::instance().pollIOServices();
        EXPECT_EQ(one_io_callback_count, 0);
        EXPECT_EQ(two_io_callback_count, 0);

        IOServiceMgr::instance().registerIOService(one_io_service);
        EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 1);

        IOServiceMgr::instance().registerIOService(two_io_service);
        EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 2);

        IOServiceMgr::instance().pollIOServices();
        EXPECT_EQ(one_io_callback_count, 1);
        EXPECT_EQ(two_io_callback_count, 1);
        one_io_service->post(one_f);
        two_io_service->post(two_f);
    }
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 2);
    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 2);
    EXPECT_EQ(two_io_callback_count, 2);

    IOServiceMgr::instance().clearIOServices();
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);
}

// Create two IOService objects and test register, unregister and poll.
TEST(IOServiceMgr, testIOServiceMgrRegisterAndUnregister) {
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);
    int one_io_callback_count = 0;
    auto one_f = [&one_io_callback_count] () {
        one_io_callback_count++;
    };
    int two_io_callback_count = 0;
    auto two_f = [&two_io_callback_count] () {
        two_io_callback_count++;
    };

    IOServicePtr one_io_service(new IOService());
    one_io_service->post(one_f);

    IOServicePtr two_io_service(new IOService());
    two_io_service->post(two_f);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 0);
    EXPECT_EQ(two_io_callback_count, 0);

    IOServiceMgr::instance().registerIOService(one_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 1);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 1);
    EXPECT_EQ(two_io_callback_count, 0);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    IOServiceMgr::instance().registerIOService(two_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 2);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 2);
    EXPECT_EQ(two_io_callback_count, 2);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    ASSERT_NO_THROW(IOServiceMgr::instance().registerIOService(one_io_service));
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 2);

    IOServiceMgr::instance().unregisterIOService(one_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 1);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 2);
    EXPECT_EQ(two_io_callback_count, 3);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    IOServiceMgr::instance().unregisterIOService(two_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 2);
    EXPECT_EQ(two_io_callback_count, 3);
}

} // namespace
