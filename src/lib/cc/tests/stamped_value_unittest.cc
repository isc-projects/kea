// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

// Tests that stamped value from string can be created.
TEST(StampedValueTest, createFromString) {
    boost::scoped_ptr<StampedValue> value;
    ASSERT_NO_THROW(value.reset(new StampedValue("bar", "foo")));
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("foo", value->getValue());
    EXPECT_THROW(value->getSignedIntegerValue(), BadValue);
}

// Tests that stamped value from integer can be created.
TEST(StampedValueTest, createFromInteger) {
    boost::scoped_ptr<StampedValue> value;
    ASSERT_NO_THROW(value.reset(new StampedValue("bar", 5)));
    EXPECT_EQ("bar", value->getName());
    EXPECT_EQ("5", value->getValue());
    int64_t signed_integer;
    ASSERT_NO_THROW(signed_integer = value->getSignedIntegerValue());
    EXPECT_EQ(5, signed_integer);
}

// Tests that Elements can be created from stamped values.
TEST(StampedValueTest, toElement) {
    ElementPtr elem;
    boost::scoped_ptr<StampedValue> value;

    // Make sure we can create a StringElement.
    ASSERT_NO_THROW(value.reset(new StampedValue("foo", "boo")));
    ASSERT_NO_THROW(elem = value->toElement(Element::string));
    ASSERT_EQ(Element::string, elem->getType());
    ASSERT_EQ("boo", elem->stringValue());

    // Make non-string types fail.
    ASSERT_THROW(value->toElement(Element::integer), BadValue);
    ASSERT_THROW(value->toElement(Element::boolean), BadValue);
    ASSERT_THROW(value->toElement(Element::real), BadValue);

    // Make sure we can create a IntElement.
    ASSERT_NO_THROW(value.reset(new StampedValue("foo", "777")));
    ASSERT_NO_THROW(elem = value->toElement(Element::integer));
    ASSERT_EQ(Element::integer, elem->getType());
    ASSERT_EQ(777, elem->intValue());

    // String should work.
    ASSERT_NO_THROW(elem = value->toElement(Element::string));
    ASSERT_EQ("777", elem->stringValue());

    // Real should work.
    ASSERT_NO_THROW(elem = value->toElement(Element::real));
    ASSERT_EQ(777.0, elem->doubleValue());

    // Boolean will fail.
    ASSERT_THROW(value->toElement(Element::boolean), BadValue);

    // Make sure we can create a Boolean.
    ASSERT_NO_THROW(value.reset(new StampedValue("foo", "true")));
    ASSERT_NO_THROW(elem = value->toElement(Element::boolean));
    ASSERT_EQ(Element::boolean, elem->getType());
    ASSERT_TRUE(elem->boolValue());

    ASSERT_NO_THROW(value.reset(new StampedValue("foo", "false")));
    ASSERT_NO_THROW(elem = value->toElement(Element::boolean));
    ASSERT_EQ(Element::boolean, elem->getType());
    ASSERT_FALSE(elem->boolValue());

    // String should work.
    ASSERT_NO_THROW(elem = value->toElement(Element::string));
    ASSERT_EQ("false", elem->stringValue());

    // Make numerics should fail.
    ASSERT_THROW(value->toElement(Element::integer), BadValue);
    ASSERT_THROW(value->toElement(Element::real), BadValue);

    // Make sure only lower case "true" and "false" works for Booleans.
    ASSERT_NO_THROW(value.reset(new StampedValue("foo", "TRUE")));
    ASSERT_THROW(value->toElement(Element::boolean), BadValue);
    ASSERT_NO_THROW(value.reset(new StampedValue("foo", "FALSE")));
    ASSERT_THROW(value->toElement(Element::boolean), BadValue);
    ASSERT_NO_THROW(value.reset(new StampedValue("foo","nonsens")));
    ASSERT_THROW(value->toElement(Element::boolean), BadValue);

    // Make sure we can create a DoubleElement.
    ASSERT_NO_THROW(value.reset(new StampedValue("foo", "45.0")));
    ASSERT_NO_THROW(elem = value->toElement(Element::real));
    ASSERT_EQ(Element::real, elem->getType());
    ASSERT_EQ(45.0, elem->doubleValue());

    // String should work.
    ASSERT_NO_THROW(elem = value->toElement(Element::string));
    ASSERT_EQ("45.0", elem->stringValue());

    // Int and Boolean should fail.
    ASSERT_THROW(value->toElement(Element::integer), BadValue);
    ASSERT_THROW(value->toElement(Element::boolean), BadValue);
}

}
