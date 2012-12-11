// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

    // requested values below or above are ignore
    EXPECT_EQ(42, y.get(5));   // all...
    EXPECT_EQ(42, y.get(42));  // the...
    EXPECT_EQ(42, y.get(80));  // time!
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
TEST(TripletTest, sanity_check) {

    // min is larger than default
    EXPECT_THROW(Triplet<uint32_t>(6,5,5), BadValue);

    // max is smaller than default
    EXPECT_THROW(Triplet<uint32_t>(5,5,4), BadValue);

}

}; // end of anonymous namespace
