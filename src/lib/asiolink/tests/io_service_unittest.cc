// Copyright (C) 2013-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>

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

// Check the runOneFor() operates correctly.
TEST(IOService, runOneFor) {
    IOServicePtr io_service(new IOService());

    // Setup up a timer to expire in 200 ms.
    IntervalTimer timer(io_service);
    size_t wait_ms = 200; 
    bool timer_fired = false;
    timer.setup([&timer_fired] { timer_fired = true; }, 
                wait_ms, IntervalTimer::ONE_SHOT);

    size_t time_outs = 0;
    while (timer_fired == false && time_outs < 5) { 
        // Call runOneFor() with 1/4 of the timer duration.
        bool timed_out = false;
        auto cnt = io_service->runOneFor(50 * 1000, timed_out);
        if (cnt || timer_fired) {
            ASSERT_FALSE(timed_out);
        } else {
            ASSERT_TRUE(timed_out);
            ++time_outs;
        }
    }

    // Should have had at least two time outs.
    EXPECT_GE(time_outs, 2);

    // Timer should have fired.
    EXPECT_EQ(timer_fired, 1);
}

}
