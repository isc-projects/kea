// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <mysql/mysql_binding.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::db;

namespace {

// This test verifies that default string is returned if binding is null.
TEST(MySqlBindingTest, defaultString) {
    auto binding = MySqlBinding::createNull();
    EXPECT_EQ("foo", binding->getStringOrDefault("foo"));

    binding = MySqlBinding::createString("bar");
    EXPECT_EQ("bar", binding->getStringOrDefault("foo"));
}

// This test verifies that null binding is created for empty string.
TEST(MySqlBindingTest, conditionalString) {
    auto binding = MySqlBinding::condCreateString("");
    EXPECT_TRUE(binding->amNull());

    binding = MySqlBinding::condCreateString("foo");
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ("foo", binding->getString());
}

// This test verifies that null JSON is returned if the string binding
// is null, JSON value is returned when string value is valid JSON and
// that exception is thrown if the string is not a valid JSON.
TEST(MySqlBindingTest, getJSON) {
    auto binding = MySqlBinding::createNull();
    EXPECT_FALSE(binding->getJSON());

    binding = MySqlBinding::createString("{ \"foo\": \"bar\" }");
    auto json = binding->getJSON();
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    auto foo = json->get("foo");
    ASSERT_TRUE(foo);
    ASSERT_EQ(Element::string, foo->getType());
    EXPECT_EQ("bar", foo->stringValue());
}

// This test verifies that default blob is returned if binding is null.
TEST(MySqlBindingTest, defaultBlob) {
    std::vector<uint8_t> blob(10, 1);
    std::vector<uint8_t> default_blob(10, 5);
    auto binding = MySqlBinding::createNull();
    EXPECT_EQ(default_blob, binding->getBlobOrDefault(default_blob));

    binding = MySqlBinding::createBlob(blob.begin(), blob.end());
    EXPECT_EQ(blob, binding->getBlobOrDefault(default_blob));
}

// This test verifies that default number is returned if binding is null.
TEST(MySqlBindingTest, defaultInteger) {
    auto binding = MySqlBinding::createNull();
    EXPECT_EQ(123, binding->getIntegerOrDefault<uint32_t>(123));

    binding = MySqlBinding::createInteger<uint32_t>(1024);
    EXPECT_EQ(1024, binding->getIntegerOrDefault<uint32_t>(123));
}

// This test verifies that null binding is created for 0 number.
TEST(MySqlBindingTest, conditionalInteger) {
    auto binding = MySqlBinding::condCreateInteger<uint16_t>(0);
    EXPECT_TRUE(binding->amNull());

    binding = MySqlBinding::condCreateInteger<uint16_t>(1);
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ(1, binding->getInteger<uint16_t>());
}

// This test verifies that default timestamp is returned if binding is null.
TEST(MySqlBindingTest, defaultTimestamp) {
    boost::posix_time::ptime current_time = boost::posix_time::second_clock::universal_time();
    boost::posix_time::ptime past_time = current_time - boost::posix_time::hours(1);

    auto binding = MySqlBinding::createNull();
    EXPECT_TRUE(past_time == binding->getTimestampOrDefault(past_time));

    binding = MySqlBinding::createTimestamp(current_time);
    EXPECT_TRUE(current_time == binding->getTimestampOrDefault(past_time));
}

}

