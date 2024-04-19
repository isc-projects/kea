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

TEST(IOServiceMgr, testIOServiceMgr) {
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

    IOServicePtr one_io_service(new IOService());
    one_io_service->post(one_f);

    IOServicePtr two_io_service(new IOService());
    two_io_service->post(two_f);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 2);
    EXPECT_EQ(two_io_callback_count, 2);

    IOServiceMgr::instance().registerIOService(one_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 1);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 3);
    EXPECT_EQ(two_io_callback_count, 2);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    IOServiceMgr::instance().registerIOService(two_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 2);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 4);
    EXPECT_EQ(two_io_callback_count, 4);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    IOServiceMgr::instance().unregisterIOService(one_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 1);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 4);
    EXPECT_EQ(two_io_callback_count, 5);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    IOServiceMgr::instance().unregisterIOService(two_io_service);
    EXPECT_EQ(IOServiceMgr::instance().getIOServiceCount(), 0);

    IOServiceMgr::instance().pollIOServices();
    EXPECT_EQ(one_io_callback_count, 4);
    EXPECT_EQ(two_io_callback_count, 5);
}

} // namespace
