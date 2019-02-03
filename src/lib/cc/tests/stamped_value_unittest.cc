// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/stamped_value.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::data;

namespace {

// Tests that the stamped value can be created with a NULL value.
TEST(StampedValueTest, createNull) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar"));

    EXPECT_TRUE(value->amNull());

    EXPECT_THROW(value->getType(), InvalidOperation);
    EXPECT_THROW(value->getValue(), InvalidOperation);
    EXPECT_THROW(value->getIntegerValue(), InvalidOperation);
    EXPECT_THROW(value->getBoolValue(), InvalidOperation);
    EXPECT_THROW(value->getDoubleValue(), InvalidOperation);
}

// Tests that stamped value from string can be created.
TEST(StampedValueTest, createFromString) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", Element::create("foo")));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::string, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("foo", value->getValue());

    EXPECT_THROW(value->getIntegerValue(), TypeError);
    EXPECT_THROW(value->getBoolValue(), TypeError);
    EXPECT_THROW(value->getDoubleValue(), TypeError);
}

// Tests that the stamped value can be created from string using the
// factory function variant that takes parameter type as an argument.
TEST(StampedValueTest, convertStringToString) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", "foo", Element::string));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::string, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("foo", value->getValue());
}

// Tests that stamped value from integer can be created.
TEST(StampedValueTest, createFromInteger) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", Element::create(static_cast<int64_t>(5))));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::integer, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("5", value->getValue());
    int64_t signed_integer;
    ASSERT_NO_THROW(signed_integer = value->getIntegerValue());
    EXPECT_EQ(5, signed_integer);

    EXPECT_THROW(value->getBoolValue(), TypeError);
    EXPECT_THROW(value->getDoubleValue(), TypeError);
}

// Tests that stamped value can be converted from string to integer.
TEST(StampedValueTest, convertStringToInteger) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", "123", Element::integer));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::integer, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ(123, value->getIntegerValue());

    EXPECT_THROW(StampedValue::create("bar", "hoho", Element::integer), BadValue);
}

// Tests that stamped value from bool can be created.
TEST(StampedValueTest, createFromBool) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", Element::create(static_cast<bool>(true))));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::boolean, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("1", value->getValue());
    bool bool_value = false;
    ASSERT_NO_THROW(bool_value = value->getBoolValue());
    EXPECT_TRUE(bool_value);

    EXPECT_THROW(value->getIntegerValue(), TypeError);
    EXPECT_THROW(value->getDoubleValue(), TypeError);
}

// Tests that stamped value can be converted from string to boolean.
TEST(StampedValueTest, convertStringToBoolean) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", "1", Element::boolean));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::boolean, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_TRUE(value->getBoolValue());

    ASSERT_NO_THROW(value = StampedValue::create("foo", "0", Element::boolean));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::boolean, value->getType());
    EXPECT_EQ("foo", value->getName());
    EXPECT_FALSE(value->getBoolValue());

    EXPECT_THROW(StampedValue::create("bar", "888", Element::boolean), BadValue);
}

// Tests that stamped value from real can be created.
TEST(StampedValueTest, createFromDouble) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", Element::create(static_cast<double>(1.45))));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::real, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("1.45", value->getValue());
    double double_value = 0;
    ASSERT_NO_THROW(double_value = value->getDoubleValue());
    EXPECT_EQ(1.45, double_value);

    EXPECT_THROW(value->getIntegerValue(), TypeError);
    EXPECT_THROW(value->getBoolValue(), TypeError);
}

// Tests that stamped value from real can handle a round value.
TEST(StampedValueTest, createFromDoubleRound) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", Element::create(static_cast<double>(7.0))));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::real, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("7.0", value->getValue());
    double double_value = 0;
    ASSERT_NO_THROW(double_value = value->getDoubleValue());
    EXPECT_EQ(7.0, double_value);

    EXPECT_THROW(value->getIntegerValue(), TypeError);
    EXPECT_THROW(value->getBoolValue(), TypeError);
}

// Tests that stamped value can be converted from string to real.
TEST(StampedValueTest, convertStringToDouble) {
    StampedValuePtr value;
    ASSERT_NO_THROW(value = StampedValue::create("bar", "1.67", Element::real));
    EXPECT_FALSE(value->amNull());
    EXPECT_EQ(Element::real, value->getType());
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ(1.67, value->getDoubleValue());

    EXPECT_THROW(StampedValue::create("bar", "hoho", Element::real), BadValue);
}

// Tests that the value must have an allowed type.
TEST(StampedValueTest, createFailures) {
    EXPECT_THROW(StampedValue::create("bar", ElementPtr()), BadValue);
    EXPECT_THROW(StampedValue::create("bar", Element::createMap()), TypeError);
    EXPECT_THROW(StampedValue::create("bar", Element::createList()), TypeError);

    EXPECT_THROW(StampedValue::create("bar", "1", Element::map), TypeError);
    EXPECT_THROW(StampedValue::create("bar", "1", Element::list), TypeError);
    EXPECT_THROW(StampedValue::create("bar", "1", Element::null), TypeError);
}

}
