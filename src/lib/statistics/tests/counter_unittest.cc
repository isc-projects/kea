// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <gtest/gtest.h>

#include <statistics/counter.h>

namespace {
enum CounterItems {
    ITEM1 = 0,
    ITEM2 = 1,
    ITEM3 = 2,
    NUMBER_OF_ITEMS = 3
};
}

using namespace isc::statistics;

// This fixture is for testing Counter.
class CounterTest : public ::testing::Test {
protected:
    CounterTest() {}
    ~CounterTest() {}
};

TEST_F(CounterTest, createCounter) {
    // Create counter
    Counter counter(NUMBER_OF_ITEMS);
    // Check if the all counters are initialized with 0
    EXPECT_EQ(counter.get(ITEM1), 0);
    EXPECT_EQ(counter.get(ITEM2), 0);
    EXPECT_EQ(counter.get(ITEM3), 0);
}

TEST_F(CounterTest, incrementCounterItem) {
    // Create counter
    Counter counter(NUMBER_OF_ITEMS);
    // Increment counters
    counter.inc(ITEM1);
    counter.inc(ITEM2);
    counter.inc(ITEM2);
    counter.inc(ITEM3);
    counter.inc(ITEM3);
    counter.inc(ITEM3);
    // Check if the counters have expected values
    EXPECT_EQ(counter.get(ITEM1), 1);
    EXPECT_EQ(counter.get(ITEM2), 2);
    EXPECT_EQ(counter.get(ITEM3), 3);
    // Increment counters once more
    counter.inc(ITEM1);
    counter.inc(ITEM2);
    counter.inc(ITEM2);
    counter.inc(ITEM3);
    counter.inc(ITEM3);
    counter.inc(ITEM3);
    // Check if the counters have expected values
    EXPECT_EQ(counter.get(ITEM1), 2);
    EXPECT_EQ(counter.get(ITEM2), 4);
    EXPECT_EQ(counter.get(ITEM3), 6);
}

TEST_F(CounterTest, invalidCounterSize) {
    // Creating counter with 0 elements will cause an isc::InvalidParameter
    // exception
    EXPECT_THROW(Counter counter(0), isc::InvalidParameter);
}

TEST_F(CounterTest, invalidCounterItem) {
    // Create counter
    Counter counter(NUMBER_OF_ITEMS);
    // Incrementing out-of-bound counter will cause an isc::OutOfRange
    // exception
    EXPECT_THROW(counter.inc(NUMBER_OF_ITEMS), isc::OutOfRange);
    // Trying to get out-of-bound counter will cause an isc::OutOfRange
    // exception
    EXPECT_THROW(counter.get(NUMBER_OF_ITEMS), isc::OutOfRange);
}
