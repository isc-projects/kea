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

}
