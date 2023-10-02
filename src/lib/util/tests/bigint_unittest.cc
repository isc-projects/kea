// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <util/bigints.h>

#include <gtest/gtest.h>

#include <limits>

using namespace isc::util;

using namespace std;

namespace {

// C++ doesn't allow very big integer literals, so that's why some tests on big
// numbers might appear like they're unnecessarily circumventing a more obvious
// test choice.

// Checks that int128_t behaves like a signed integer should.
TEST(BigintTest, int128) {
    // Check addition with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(24, int128_t(16) + int128_t(8));
    });

    // Check subtraction with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(48, int128_t(64) - int128_t(16));
    });

    // Check multiplication with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(8, int128_t(2) * int128_t(4));
    });

    // Check division with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(16, int128_t(64) / int128_t(4));
    });

    // Check rounded division with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(16, int128_t(65) / int128_t(4));
    });

    // Check that INT128_MIN < INT64_MIN.
    EXPECT_NO_THROW({
        EXPECT_LT(numeric_limits<int128_t>::min(), numeric_limits<int64_t>::min());
    });

    // Check that UINT64_MAX < INT128_MAX.
    EXPECT_NO_THROW({
        EXPECT_LT(numeric_limits<uint64_t>::max(), numeric_limits<int128_t>::max());
    });

    // Check that int128_t is default-initialized to zero. Not a strict
    // requirement by Kea, but something that the current implementation ensures.
    int128_t i128;
    EXPECT_NO_THROW({
        EXPECT_EQ(0, i128);
    });

    // Shifting to the right beyond zero does not result in an underflow error.
    EXPECT_NO_THROW({
        EXPECT_EQ(0, uint128_t(1) >> 2);
    });

    // Check that dividing by zero throws.
    EXPECT_THROW_MSG(int128_t(1) / 0, overflow_error, "Division by zero.");

    // Check that underflowing results in an error.
    i128 = numeric_limits<int128_t>::min();
    EXPECT_THROW_MSG(i128 - 1, overflow_error, "overflow in addition");
    EXPECT_THROW_MSG(i128 + i128, overflow_error, "overflow in addition");

    // Check that overflowing results in an error.
    i128 = numeric_limits<int128_t>::max();
    EXPECT_THROW_MSG(i128 + 1, overflow_error, "overflow in addition");
    EXPECT_THROW_MSG(i128 + i128, overflow_error, "overflow in addition");
    EXPECT_THROW_MSG(2 * i128, overflow_error, "overflow in multiplication");
    EXPECT_THROW_MSG(i128 << 1, overflow_error, "Shift out of range");
}

// Checks that uint128_t behaves like an unsigned integer should.
TEST(BigintTest, uint128) {
    // Check addition with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(24, uint128_t(16) + uint128_t(8));
    });

    // Check subtraction with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(48, uint128_t(64) - uint128_t(16));
    });

    // Check multiplication with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(8, uint128_t(2) * uint128_t(4));
    });

    // Check division with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(16, uint128_t(64) / uint128_t(4));
    });

    // Check rounded division with small numbers.
    EXPECT_NO_THROW({
        EXPECT_EQ(16, uint128_t(65) / uint128_t(4));
    });

    // Check that UINT128_MIN is 0.
    EXPECT_NO_THROW({
        EXPECT_EQ(0, numeric_limits<uint128_t>::min());
    });

    // Check that UINT64_MAX < UINT128_MAX.
    EXPECT_NO_THROW({
        EXPECT_LT(numeric_limits<uint64_t>::max(), numeric_limits<int128_t>::max());
    });

    // Check that INT128_MAX < UINT128_MAX.
    EXPECT_NO_THROW({
        EXPECT_LT(numeric_limits<uint64_t>::max(), numeric_limits<int128_t>::max());
    });

    // Check that uint128_t is default-initialized to zero. Not a strict
    // requirement by Kea, but something that the current implementation ensures.
    uint128_t u128;
    EXPECT_NO_THROW({
        EXPECT_EQ(0, u128);
    });

    // Shifting to the right beyond zero does not result in an underflow error.
    EXPECT_NO_THROW({
        EXPECT_EQ(0, uint128_t(1) >> 2);
    });

    // Check that dividing by zero throws.
    EXPECT_THROW_MSG(uint128_t(1) / 0, overflow_error, "Division by zero.");

    // Check that underflowing results in an error.
    u128 = numeric_limits<uint128_t>::min();
    EXPECT_THROW_MSG(u128 - 1, range_error, "Subtraction resulted in a negative value, but the type is unsigned");

    // Check that overflowing results in an error.
    u128 = numeric_limits<uint128_t>::max();
    EXPECT_THROW_MSG(u128 + 1, overflow_error, "overflow in addition");
    EXPECT_THROW_MSG(u128 + u128, overflow_error, "overflow in addition");
    EXPECT_THROW_MSG(2 * u128, overflow_error, "overflow in multiplication");
    EXPECT_THROW_MSG(u128 << 1, overflow_error, "Shift out of range");
}

}  // namespace
