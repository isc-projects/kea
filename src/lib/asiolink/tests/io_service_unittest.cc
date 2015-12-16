// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/io_service.h>

#include <gtest/gtest.h>
#include <boost/bind.hpp>
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
    service.post(boost::bind(&postedEvent, &called, 1));
    service.post(boost::bind(&postedEvent, &called, 2));
    service.post(boost::bind(&postedEvent, &called, 3));
    // They have not yet been called
    EXPECT_TRUE(called.empty());
    // Process two events
    service.run_one();
    service.run_one();
    // Both events were called in the right order
    ASSERT_EQ(2, called.size());
    EXPECT_EQ(1, called[0]);
    EXPECT_EQ(2, called[1]);

    // Test that poll() executes the last handler.
    service.poll();
    ASSERT_EQ(3, called.size());
    EXPECT_EQ(3, called[2]);
}

}
