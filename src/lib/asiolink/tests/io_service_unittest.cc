// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>

#include <gtest/gtest.h>
#include <functional>
#include <vector>

using namespace isc::asiolink;

namespace {

void
postedEvent(std::vector<int>* destination, int value) {
    destination->push_back(value);
}

// Check the posted events are called, in the same order they are posted.
TEST(IOService, post) {
    std::vector<int> called;
    IOService service;
    // Post two events
    service.post(std::bind(&postedEvent, &called, 1));
    service.post(std::bind(&postedEvent, &called, 2));
    service.post(std::bind(&postedEvent, &called, 3));
    // They have not yet been called
    EXPECT_TRUE(called.empty());
    // Process two events
    service.runOne();
    service.runOne();
    // Both events were called in the right order
    ASSERT_EQ(2, called.size());
    EXPECT_EQ(1, called[0]);
    EXPECT_EQ(2, called[1]);

    // Test that poll() executes the last handler.
    service.poll();
    ASSERT_EQ(3, called.size());
    EXPECT_EQ(3, called[2]);
}

TEST(IOService, externalIOService) {
    IOServicePtr main_io_service(new IOService());
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 0);
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

        main_io_service->pollExternalIOServices();
        EXPECT_EQ(one_io_callback_count, 0);
        EXPECT_EQ(two_io_callback_count, 0);

        main_io_service->registerExternalIOService(one_io_service);
        EXPECT_EQ(main_io_service->externalIOServiceCount(), 1);

        main_io_service->registerExternalIOService(two_io_service);
        EXPECT_EQ(main_io_service->externalIOServiceCount(), 2);

        main_io_service->pollExternalIOServices();
        EXPECT_EQ(one_io_callback_count, 1);
        EXPECT_EQ(two_io_callback_count, 1);
        one_io_service->post(one_f);
        two_io_service->post(two_f);
    }
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 2);
    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 2);
    EXPECT_EQ(two_io_callback_count, 2);

    main_io_service->clearExternalIOServices();
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 0);

    IOServicePtr one_io_service(new IOService());
    one_io_service->post(one_f);

    IOServicePtr two_io_service(new IOService());
    two_io_service->post(two_f);

    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 2);
    EXPECT_EQ(two_io_callback_count, 2);

    main_io_service->registerExternalIOService(one_io_service);
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 1);

    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 3);
    EXPECT_EQ(two_io_callback_count, 2);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    main_io_service->registerExternalIOService(two_io_service);
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 2);

    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 4);
    EXPECT_EQ(two_io_callback_count, 4);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    main_io_service->unregisterExternalIOService(one_io_service);
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 1);

    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 4);
    EXPECT_EQ(two_io_callback_count, 5);
    one_io_service->post(one_f);
    two_io_service->post(two_f);

    main_io_service->unregisterExternalIOService(two_io_service);
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 0);

    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 4);
    EXPECT_EQ(two_io_callback_count, 5);

    EXPECT_NO_THROW(main_io_service->registerExternalIOService(main_io_service));
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 1);
    main_io_service->post(one_f);

    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 5);
    EXPECT_EQ(two_io_callback_count, 5);
    EXPECT_NO_THROW(main_io_service->unregisterExternalIOService(main_io_service));
    EXPECT_EQ(main_io_service->externalIOServiceCount(), 0);

    main_io_service->pollExternalIOServices();
    EXPECT_EQ(one_io_callback_count, 5);
    EXPECT_EQ(two_io_callback_count, 5);
}

}
