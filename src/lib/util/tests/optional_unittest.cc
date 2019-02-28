// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/optional.h>
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

    // Use the non-default value for second parameter.
    Optional<bool> value3(true, true);
    EXPECT_TRUE(value3.get());
    EXPECT_TRUE(value3.unspecified());
}

// This test checks if the constructors for a string value
// work correctly.
TEST(OptionalTest, constructorString) {
    Optional<std::string> value1("foo");
    EXPECT_EQ("foo", value1.get());
    EXPECT_FALSE(value1.unspecified());

    Optional<std::string> value2;
    EXPECT_TRUE(value2.get().empty());
    EXPECT_TRUE(value2.unspecified());
}

// This test checks if the assignment operator assigning an actual
// value to the optional value works as expected.
TEST(OptionalTest, assignValue) {
    Optional<int> value(10, true);
    EXPECT_EQ(10, value.get());
    EXPECT_TRUE(value.unspecified());

    // Assign a new value.
    value = 111;
    EXPECT_EQ(111, value.get());
    EXPECT_FALSE(value.unspecified());

    // Assign another value.
    value = 1000;
    EXPECT_EQ(1000, value.get());
    EXPECT_FALSE(value.unspecified());
}

// This test checks if the assignment operator assigning an actual
// string value to the optional value works as expected.
TEST(OptionalTest, assignStringValue) {
    Optional<std::string> value("foo");
    EXPECT_EQ("foo", value.get());
    EXPECT_FALSE(value.unspecified());

    value = "bar";
    EXPECT_EQ("bar", value.get());
    EXPECT_FALSE(value.unspecified());

    value = "foobar";
    EXPECT_EQ("foobar", value.get());
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
    EXPECT_EQ(-10, value.get());
    EXPECT_FALSE(value.unspecified());

    int actual = value;
    EXPECT_EQ(-10, actual);
}

// This test checks if the type case operator returns correct string
// value.
TEST(OptionalTest, stringCastOperator) {
    Optional<std::string> value("xyz");
    EXPECT_EQ("xyz", value.get());
    EXPECT_FALSE(value.unspecified());

    std::string actual = value;
    EXPECT_EQ("xyz", actual);
}

// This test checks that the equality operators work as expected.
TEST(OptionalTest, equality) {
    int exp_value = 1234;
    Optional<int> value(1234);
    EXPECT_TRUE(value == exp_value);
    EXPECT_FALSE(value != exp_value);
}

// This test checks that the equality operators for strings work as
// expected.
TEST(OptionalTest, stringEquality) {
    const char* exp_value = "foo";
    Optional<std::string> value("foo");
    EXPECT_TRUE(value == exp_value);
    EXPECT_FALSE(value != exp_value);
}

// This test checks that an exception is thrown when calling an empty()
// method on non-string optional value.
TEST(OptionalTest, empty) {
    Optional<int> value(10);
    EXPECT_THROW(value.empty(), isc::InvalidOperation);
}

// This test checks that no exception is thrown when calling an empty()
// method on string optional value and that it returns an expected
// boolean value.
TEST(OptionalTest, stringEmpty) {
    Optional<std::string> value("foo");
    bool is_empty = true;
    ASSERT_NO_THROW(is_empty = value.empty());
    EXPECT_FALSE(is_empty);

    value = "";
    ASSERT_NO_THROW(is_empty = value.empty());
    EXPECT_TRUE(is_empty);
}

} // end of anonymous namespace
