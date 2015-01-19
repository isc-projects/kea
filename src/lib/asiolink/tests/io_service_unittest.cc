// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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
