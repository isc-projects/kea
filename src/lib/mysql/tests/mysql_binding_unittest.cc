// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <mysql/mysql_binding.h>
#include <util/optional.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::util;

namespace {

// This test verifies that default string is returned if binding is null.
TEST(MySqlBindingTest, defaultString) {
    auto binding = MySqlBinding::createNull();
    EXPECT_EQ("foo", binding->getStringOrDefault("foo"));

    binding = MySqlBinding::createString("bar");
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ("bar", binding->getStringOrDefault("foo"));
}

// This test verifies that null binding is created for unspecified string
// and the string binding is created for a specified string.
TEST(MySqlBindingTest, conditionalString) {
    auto binding = MySqlBinding::condCreateString(Optional<std::string>());
    EXPECT_TRUE(binding->amNull());

    binding = MySqlBinding::condCreateString("foo");
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ("foo", binding->getString());
}

// This test verifies that empty string is stored in the database.
TEST(MySqlBindingTest, emptyString) {
    auto binding = MySqlBinding::condCreateString(Optional<std::string>(""));
    ASSERT_FALSE(binding->amNull());
    EXPECT_TRUE(binding->getString().empty());
}

// This test verifies that an error is thrown upon an attempt to use
// invalid accessor for a string binding.
TEST(MySqlBindingTest, stringTypeMismatch) {
    auto binding = MySqlBinding::createString("foo");
    EXPECT_NO_THROW(static_cast<void>(binding->getString()));

    EXPECT_THROW(static_cast<void>(binding->getBlob()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint16_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getFloat()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getBool()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getTimestamp()), InvalidOperation);
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

// This test verifies that an error is thrown upon an attempt to use
// invalid accessor for a blob binding.
TEST(MySqlBindingTest, blobTypeMismatch) {
    std::vector<uint8_t> blob(10, 1);
    auto binding = MySqlBinding::createBlob(blob.begin(), blob.end());
    EXPECT_NO_THROW(static_cast<void>(binding->getBlob()));

    EXPECT_THROW(static_cast<void>(binding->getString()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint16_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getFloat()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getBool()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getTimestamp()), InvalidOperation);
}

// This test verifies that default number is returned if binding is null.
TEST(MySqlBindingTest, defaultInteger) {
    auto binding = MySqlBinding::createNull();
    ASSERT_TRUE(binding->amNull());
    EXPECT_EQ(123, binding->getIntegerOrDefault<uint32_t>(123));

    binding = MySqlBinding::createInteger<uint32_t>(1024);
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ(1024, binding->getIntegerOrDefault<uint32_t>(123));
}

// This test verifies that null binding is created for unspecified number
// and the integer binding is created for a specified number.
TEST(MySqlBindingTest, conditionalInteger) {
    auto binding = MySqlBinding::condCreateInteger<uint16_t>(Optional<uint16_t>());
    EXPECT_TRUE(binding->amNull());

    binding = MySqlBinding::condCreateInteger<uint16_t>(1);
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ(1, binding->getInteger<uint16_t>());
}

// This test verifies that an error is thrown upon an attempt to use
// invalid accessor for an integer binding.
TEST(MySqlBindingTest, integerTypeMismatch) {
    auto binding = MySqlBinding::createInteger<uint32_t>(123);
    EXPECT_NO_THROW(static_cast<void>(binding->getInteger<uint32_t>()));

    EXPECT_THROW(static_cast<void>(binding->getString()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getBlob()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint8_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint16_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getFloat()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getBool()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getTimestamp()), InvalidOperation);
}

// This test verifies that null binding is created for unspecified floating
// point value and the float binding is created for the specified value.
TEST(MySqlBindingTest, conditionalFloat) {
    auto binding = MySqlBinding::condCreateFloat(Optional<float>());
    EXPECT_TRUE(binding->amNull());

    binding = MySqlBinding::condCreateFloat<float>(1.567f);
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ(1.567f, binding->getFloat());
}

// This test verifies that an error is thrown upon an attempt to use
// invalid accessor for a float binding.
TEST(MySqlBindingTest, floatTypeMismatch) {
    auto binding = MySqlBinding::createFloat(123.123f);
    EXPECT_NO_THROW(static_cast<void>(binding->getFloat()));

    EXPECT_THROW(static_cast<void>(binding->getString()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getBlob()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint8_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint16_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint32_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getBool()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getTimestamp()), InvalidOperation);
}

// This test verifies that null binding is created for unspecified boolean
// value and the uint8_t binding is created for a specified boolean
// value.
TEST(MySqlBindingTest, conditionalBoolean) {
    auto binding = MySqlBinding::condCreateBool(Optional<bool>());
    EXPECT_TRUE(binding->amNull());

    binding = MySqlBinding::condCreateBool(false);
    ASSERT_FALSE(binding->amNull());
    EXPECT_FALSE(binding->getBool());

    binding = MySqlBinding::condCreateBool(true);
    ASSERT_FALSE(binding->amNull());
    EXPECT_TRUE(binding->getBool());
}

// This test verifies that an error is thrown upon an attempt to use
// invalid accessor for a float binding.
TEST(MySqlBindingTest, booleanTypeMismatch) {
    auto binding = MySqlBinding::createBool(false);
    EXPECT_NO_THROW(static_cast<void>(binding->getBool()));
    EXPECT_NO_THROW(static_cast<void>(binding->getInteger<uint8_t>()));

    EXPECT_THROW(static_cast<void>(binding->getString()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getBlob()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint16_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getInteger<uint32_t>()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getFloat()), InvalidOperation);
    EXPECT_THROW(static_cast<void>(binding->getTimestamp()), InvalidOperation);
}

// This test verifies that null binding is created for unspecified address
// and the uint32_t binding is created for the specified address.
TEST(MySqlBindingTest, conditionalIPv4Address) {
    auto binding = MySqlBinding::condCreateIPv4Address(Optional<IOAddress>());
    EXPECT_TRUE(binding->amNull());

    binding = MySqlBinding::condCreateIPv4Address(IOAddress("192.0.2.1"));
    ASSERT_FALSE(binding->amNull());
    EXPECT_EQ(0xC0000201, binding->getInteger<uint32_t>());

    EXPECT_THROW(MySqlBinding::condCreateIPv4Address(IOAddress("2001:db8:1::1")),
                 isc::BadValue);
}

// This test verifies that default timestamp is returned if binding is null.
TEST(MySqlBindingTest, defaultTimestamp) {
    boost::posix_time::ptime current_time = boost::posix_time::second_clock::local_time();
    boost::posix_time::ptime past_time = current_time - boost::posix_time::hours(1);

    auto binding = MySqlBinding::createNull();
    EXPECT_TRUE(past_time == binding->getTimestampOrDefault(past_time));

    binding = MySqlBinding::createTimestamp(current_time);
    EXPECT_TRUE(current_time == binding->getTimestampOrDefault(past_time));
}

// This test verifies that the binding preserves fractional seconds in
// millisecond precision.
/// @todo This test is disabled until we decide that the minimum
/// supported MySQL version has a fractional seconds precision.
TEST(MySqlBindingTest, DISABLED_millisecondTimestampPrecision) {
    // Set timestamp of 2019-01-28 01:12:10.123

    // Fractional part depends on the clock resolution.
    long fractional = 123*(boost::posix_time::time_duration::ticks_per_second()/1000);
    boost::posix_time::ptime
        test_time(boost::gregorian::date(2019, boost::gregorian::Jan, 28),
                  boost::posix_time::time_duration(1, 12, 10, fractional));

    auto binding = MySqlBinding::createTimestamp(test_time);

    boost::posix_time::ptime returned_test_time = binding->getTimestamp();

    EXPECT_EQ(returned_test_time, test_time);
}

}

