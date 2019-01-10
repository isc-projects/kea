// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/doubles.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::util;

namespace {

// Exercises isc::util::areDoublesEquivalent().
TEST(Doubles, areDoublesEquivalent) {
    std::vector<uint8_t> data;

    // Default tolerance is 0.000001
    EXPECT_TRUE(areDoublesEquivalent( 1.0000000, 1.0000005));
    EXPECT_FALSE(areDoublesEquivalent(1.0000000, 1.000005));

    // Check custome tolerance.
    EXPECT_TRUE(areDoublesEquivalent( 1.000, 1.005, 0.01));
    EXPECT_FALSE(areDoublesEquivalent(1.000, 1.005, 0.001));
}

}
