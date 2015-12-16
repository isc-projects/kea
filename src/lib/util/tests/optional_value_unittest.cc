// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/optional_value.h>
#include <gtest/gtest.h>

namespace {

using namespace isc::util;

// This test checks that the constructor sets the values passed as arguments.
TEST(OptionalValueTest, constructor) {
    // Do not specify the second parameter. The default should be that
    // the value is "unspecified".
    OptionalValue<int> value1(10);
    EXPECT_EQ(10, value1.get());
    EXPECT_FALSE(value1.isSpecified());

    // Use the non-default value for second parameter.
    OptionalValue<int> value2(2, true);
    EXPECT_EQ(2, value2.get());
    EXPECT_TRUE(value2.isSpecified());
}

// This test checks that the OptionalValue::set and OptionalValue::specify
// set the values as expected.
TEST(OptionalValueTest, set) {
    OptionalValue<int> value(10);
    ASSERT_EQ(10, value.get());
    ASSERT_FALSE(value.isSpecified());

    // Set new value. This should not change the "specified" flag.
    value.set(100);
    ASSERT_EQ(100, value.get());
    ASSERT_FALSE(value.isSpecified());

    // Mark value "specified". The value itself should not change.
    value.specify(OptionalValueState(true));
    ASSERT_EQ(100, value.get());
    ASSERT_TRUE(value.isSpecified());

    // Once it is "specified", set the new value. It should remain specified.
    value.set(5);
    ASSERT_EQ(5, value.get());
    ASSERT_TRUE(value.isSpecified());

    // Mark it "unspecified". The value should remain the same.
    value.specify(OptionalValueState(false));
    ASSERT_EQ(5, value.get());
    ASSERT_FALSE(value.isSpecified());
}

// This test checks that the OptionalValue::specify functions may be used
// to set the new value and to mark value specified.
TEST(OptionalValueTest, specifyValue) {
    OptionalValue<int> value(10);
    ASSERT_EQ(10, value.get());
    ASSERT_FALSE(value.isSpecified());

    // Set the new value and mark it "specified".
    value.specify(123);
    ASSERT_EQ(123, value.get());
    ASSERT_TRUE(value.isSpecified());

    // Specify another value. The value should be still "specified".
    value.specify(1000);
    ASSERT_EQ(1000, value.get());
    ASSERT_TRUE(value.isSpecified());
}

// This test checks if the assignment operator assigning an actual
// value to the optional value works as expected.
TEST(OptionalValueTest, assignValue) {
    OptionalValue<int> value(10);
    ASSERT_EQ(10, value.get());
    ASSERT_FALSE(value.isSpecified());

    // Set the new value and mark it "specified".
    value = 111;
    ASSERT_EQ(111, value.get());
    ASSERT_TRUE(value.isSpecified());

    // Specify another value. The value should be still "specified".
    value = 1000;
    ASSERT_EQ(1000, value.get());
    ASSERT_TRUE(value.isSpecified());
}

// This test checks if the equality and inequality operators work
// correctly for the optional value.
TEST(OptionalValueTest, equalityOperators) {
    OptionalValue<int> value(10);
    ASSERT_EQ(10, value.get());
    ASSERT_FALSE(value.isSpecified());

    EXPECT_FALSE(value == 10);
    EXPECT_TRUE(value != 10);
    EXPECT_FALSE(value == 123);
    EXPECT_TRUE(value != 123);

    value.specify(OptionalValueState(true));

    EXPECT_TRUE(value == 10);
    EXPECT_FALSE(value != 10);
    EXPECT_FALSE(value == 123);
    EXPECT_TRUE(value != 123);

    value = 123;
    EXPECT_TRUE(value == 123);
    EXPECT_FALSE(value != 123);
    EXPECT_FALSE(value == 10);
    EXPECT_TRUE(value != 10);

    value.specify(OptionalValueState(false));

    EXPECT_FALSE(value == 123);
    EXPECT_TRUE(value != 123);
    EXPECT_FALSE(value == 10);
    EXPECT_TRUE(value != 10);
}

// This test checks if the type case operator returns correct value.
TEST(OptionalValueTest, typeCastOperator) {
    OptionalValue<int> value(-10, true);
    ASSERT_EQ(-10, value.get());
    ASSERT_TRUE(value.isSpecified());

    int actual = value;
    EXPECT_EQ(-10, actual);
}

} // end of anonymous namespace
