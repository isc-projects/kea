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
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <dhcp/cfgmgr.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

// constructor validation
TEST(TripletTest, constructor) {

    uint32_t min = 10;
    uint32_t value = 20;
    uint32_t max = 30;

    Triplet<uint32_t> x(min, value, max);

    EXPECT_EQ(10, x.getMin());
    EXPECT_EQ(20, x.get());
    EXPECT_EQ(30, x.getMax());

    // requested values below min should return allowed min value
    EXPECT_EQ(10, x.get(5));

    EXPECT_EQ(10, x.get(10));

    // requesting a value from within the range (min < x < max) should
    // return the requested value
    EXPECT_EQ(17, x.get(17));

    EXPECT_EQ(30, x.get(30));
    
    EXPECT_EQ(30, x.get(35));

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

// triplets must be easy to use
// simple int conversions must be done on the fly
TEST(TripletTest, operator) {

    uint32_t x = 47;

    // assignment operator: uint32_t => triplet
    Triplet<uint32_t> y = x;

    EXPECT_EQ(47, y.get());

    // let's try the other way around: triplet => uint32_t
    uint32_t z = y;

    EXPECT_EQ(47, z);
}

// check if specified values are sane
TEST(TripletTest, sanity_check) {

    // min is larger than default
    EXPECT_THROW(Triplet<uint32_t>(6,5,5), BadValue);

    // max is smaller than default
    EXPECT_THROW(Triplet<uint32_t>(5,5,4), BadValue);

}

} // end of anonymous namespace
