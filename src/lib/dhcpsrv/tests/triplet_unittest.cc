// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/triplet.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <stdint.h>

using namespace isc::dhcp;
using namespace isc;

namespace {

// constructor validation
TEST(TripletTest, constructor) {

    const uint32_t min = 10;
    const uint32_t value = 20;
    const uint32_t max = 30;

    Triplet<uint32_t> x(min, value, max);

    EXPECT_EQ(min, x.getMin());
    EXPECT_EQ(value, x.get());
    EXPECT_EQ(max, x.getMax());
    EXPECT_FALSE(x.unspecified());

    // requested values below min should return allowed min value
    EXPECT_EQ(min, x.get(min - 5));

    EXPECT_EQ(min, x.get(min));

    // requesting a value from within the range (min < x < max) should
    // return the requested value
    EXPECT_EQ(17, x.get(17));

    EXPECT_EQ(max, x.get(max));

    EXPECT_EQ(max, x.get(max + 5));

    // this will be boring. It is expected to return 42 no matter what
    Triplet<uint32_t> y(42);

    EXPECT_EQ(42, y.getMin()); // min, default and max are equal to 42
    EXPECT_EQ(42, y.get());    // it returns ...
    EXPECT_EQ(42, y.getMax()); // the exact value...
    EXPECT_FALSE(x.unspecified());

    // requested values below or above are ignore
    EXPECT_EQ(42, y.get(5));   // all...
    EXPECT_EQ(42, y.get(42));  // the...
    EXPECT_EQ(42, y.get(80));  // time!
}

TEST(TripletTest, unspecified) {
    Triplet<uint32_t> x;
    // When using the constructor without parameters, the triplet
    // value is unspecified.
    EXPECT_EQ(0, x.getMin());
    EXPECT_EQ(0, x.get());
    EXPECT_EQ(0, x.getMax());
    EXPECT_TRUE(x.unspecified());

    // For the triplet which has unspecified value we can call accessors
    // without an exception.
    uint32_t exp_unspec = 0;
    EXPECT_EQ(exp_unspec, x);

    x = 72;
    // Check if the new value has been assigned.
    EXPECT_EQ(72, x.getMin());
    EXPECT_EQ(72, x.get());
    EXPECT_EQ(72, x.getMax());
    // Triplet is now specified.
    EXPECT_FALSE(x.unspecified());
}

// Triplets must be easy to use.
// Simple to/from int conversions must be done on the fly.
TEST(TripletTest, operator) {

    uint32_t x = 47;

    Triplet<uint32_t> foo(1,2,3);
    Triplet<uint32_t> bar(4,5,6);

    foo = bar;

    EXPECT_EQ(4, foo.getMin());
    EXPECT_EQ(5, foo.get());
    EXPECT_EQ(6, foo.getMax());
    EXPECT_FALSE(foo.unspecified());

    // assignment operator: uint32_t => triplet
    Triplet<uint32_t> y(0);
    y = x;

    EXPECT_EQ(x, y.get());

    // let's try the other way around: triplet => uint32_t
    uint32_t z = 0;
    z = y;

    EXPECT_EQ(x, z);
}

// check if specified values are sane
TEST(TripletTest, sanityCheck) {

    // min is larger than default
    EXPECT_THROW(Triplet<uint32_t>(6,5,5), BadValue);

    // max is smaller than default
    EXPECT_THROW(Triplet<uint32_t>(5,5,4), BadValue);

}

}; // end of anonymous namespace
