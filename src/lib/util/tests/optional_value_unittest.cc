// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/optional_value.h>
#include <gtest/gtest.h>

namespace {

using namespace isc::util;

// This test checks that the constructors work correctly.
TEST(OptionalTest, constructor) {
    // Explicitly set a value via constructor. The value becomes
    // specified.
    Optional<int> value1(10);
    EXPECT_EQ(10, value1.get());
    EXPECT_FALSE(value1.unspecified());

    // Do not set a value in a constructor. The value should be
    // unspecified.
    Optional<int> value2;
    EXPECT_EQ(0, value2.get());
    EXPECT_TRUE(value2.unspecified());
}

TEST(OptionalTest, constructorString) {
    Optional<std::string> value1("foo");
    EXPECT_EQ("foo", value1.get());

    Optional<std::string> value2;
    EXPECT_TRUE(value2.get().empty());
}

// This test checks if the assignment operator assigning an actual
// value to the optional value works as expected.
TEST(OptionalTest, assignValue) {
    Optional<int> value(10);
    EXPECT_EQ(10, value.get());
    EXPECT_FALSE(value.unspecified());

    // Assign a new value.
    value = 111;
    EXPECT_EQ(111, value.get());
    EXPECT_FALSE(value.unspecified());

    // Assign another value.
    value = 1000;
    EXPECT_EQ(1000, value.get());
    EXPECT_FALSE(value.unspecified());
}

// This test checks that it is possible to modify the flag that indicates
// if the value is specified or unspecified.
TEST(OptionalTest, modifyUnspecified) {
    Optional<int> value;
    EXPECT_TRUE(value.unspecified());

    value.unspecified(false);
    EXPECT_FALSE(value.unspecified());

    value.unspecified(true);
    EXPECT_TRUE(value.unspecified());
}

// This test checks if the type case operator returns correct value.
TEST(OptionalTest, typeCastOperator) {
    Optional<int> value(-10);
    ASSERT_EQ(-10, value.get());
    ASSERT_FALSE(value.unspecified());

    int actual = value;
    EXPECT_EQ(-10, actual);
}

} // end of anonymous namespace
