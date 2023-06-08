// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <util/bigints.h>

#include <gtest/gtest.h>

using namespace isc::util;

namespace {

// C++ doesn't allow very big integer literals, so that's why some tests on big
// numbers might appear like they're unnecessarily circumventing a more obvious
// test choice.

// Checks that int128_t behaves like a signed integer should.
TEST(BigintTest, int128) {
    // Check addition with small numbers.
    EXPECT_EQ(24, int128_t(16) + int128_t(8));

    // Check subtraction with small numbers.
    EXPECT_EQ(48, int128_t(64) - int128_t(16));

    // Check multiplication with small numbers.
    EXPECT_EQ(8, int128_t(2) * int128_t(4));

    // Check division with small numbers.
    EXPECT_EQ(16, int128_t(64) / int128_t(4));

    // Check rounded division with small numbers.
    EXPECT_EQ(16, int128_t(65) / int128_t(4));

    // Check that dividing by zero throws.
    EXPECT_THROW(int128_t(1) / 0, std::overflow_error);

    // Check that underflowing results in a negative number for int128_t.
    EXPECT_EQ(-1, int128_t(0) - 1);

    // Check that UINT64_MAX < INT128_MAX.
    EXPECT_LT(uint64_t(0) - 1, int128_t(uint128_t(0) - 1));

    // Check that int128_t is default-initialized to zero. Not a strict
    // requirement, but something that the current implementation ensures.
    int128_t i128;
    EXPECT_EQ(0, i128);

    // Check that overflowing on big numbers has the correct result.
    i128 = int128_t(0) - 1;
    EXPECT_EQ(i128 - 1, i128 + i128);
}

// Checks that uint128_t behaves like an unsigned integer should.
TEST(BigintTest, uint128) {
    // Check addition with small numbers.
    EXPECT_EQ(24, uint128_t(16) + uint128_t(8));

    // Check subtraction with small numbers.
    EXPECT_EQ(48, uint128_t(64) - uint128_t(16));

    // Check multiplication with small numbers.
    EXPECT_EQ(8, uint128_t(2) * uint128_t(4));

    // Check division with small numbers.
    EXPECT_EQ(16, uint128_t(64) / uint128_t(4));

    // Check rounded division with small numbers.
    EXPECT_EQ(16, uint128_t(65) / uint128_t(4));

    // Check that dividing by zero throws.
    EXPECT_THROW(uint128_t(1) / 0, std::overflow_error);

    // Check that underflowing results in a positive number for uint128_t.
    EXPECT_LT(0, uint128_t(0) - 1);

    // Check that UINT64_MAX < UINT128_MAX.
    EXPECT_LT(uint64_t(0) - 1, uint128_t(0) - 1);

    // Check that uint128_t is default-initialized to zero. Not a strict
    // requirement, but something that the current implementation ensures.
    uint128_t u128;
    EXPECT_EQ(0, u128);

    // Check that overflowing on big numbers has the correct result.
    u128 = uint128_t(0) - 1;
    EXPECT_EQ(u128 - 1, u128 + u128);
}

}  // namespace
