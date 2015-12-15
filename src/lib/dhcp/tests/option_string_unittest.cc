// Copyright (C) 2013,2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option_string.h>

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief OptionString test class.
class OptionStringTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Initializes the test buffer with some data.
    OptionStringTest() {
        std::string test_string("This is a test string");
        buf_.assign(test_string.begin(), test_string.end());
    }

    OptionBuffer buf_;

};

// This test verifies that the constructor which creates an option instance
// from a string value will create it properly.
TEST_F(OptionStringTest, constructorFromString) {
    const std::string optv4_value = "some option";
    OptionString optv4(Option::V4, 123, optv4_value);
    EXPECT_EQ(Option::V4, optv4.getUniverse());
    EXPECT_EQ(123, optv4.getType());
    EXPECT_EQ(optv4_value, optv4.getValue());
    EXPECT_EQ(Option::OPTION4_HDR_LEN + optv4_value.size(), optv4.len());

    // Do another test with the same constructor to make sure that
    // different set of parameters would initialize the class members
    // to different values.
    const std::string optv6_value = "other option";
    OptionString optv6(Option::V6, 234, optv6_value);
    EXPECT_EQ(Option::V6, optv6.getUniverse());
    EXPECT_EQ(234, optv6.getType());
    EXPECT_EQ("other option", optv6.getValue());
    EXPECT_EQ(Option::OPTION6_HDR_LEN + optv6_value.size(), optv6.len());

    // Check that an attempt to use empty string in the constructor
    // will result in an exception.
    EXPECT_THROW(OptionString(Option::V6, 123, ""), isc::OutOfRange);
}

// This test verifies that the constructor which creates an option instance
// from a buffer, holding option payload, will create it properly.
// This function calls unpack() internally thus test test is considered
// to cover testing of unpack() functionality.
TEST_F(OptionStringTest, constructorFromBuffer) {
    // Attempt to create an option using empty buffer should result in
    // an exception.
    EXPECT_THROW(
        OptionString(Option::V4, 234, buf_.begin(), buf_.begin()),
        isc::OutOfRange
    );

    // Declare option as a scoped pointer here so as its scope is
    // function wide. The initialization (constructor invocation)
    // is pushed to the ASSERT_NO_THROW macro below, as it may
    // throw exception if buffer is truncated.
    boost::scoped_ptr<OptionString> optv4;
    ASSERT_NO_THROW(
        optv4.reset(new OptionString(Option::V4, 234, buf_.begin(), buf_.end()));
    );
    // Make sure that it has been initialized to non-NULL value.
    ASSERT_TRUE(optv4);

    // Test the instance of the created option.
    const std::string optv4_value = "This is a test string";
    EXPECT_EQ(Option::V4, optv4->getUniverse());
    EXPECT_EQ(234, optv4->getType());
    EXPECT_EQ(Option::OPTION4_HDR_LEN + buf_.size(), optv4->len());
    EXPECT_EQ(optv4_value, optv4->getValue());

    // Do the same test for V6 option.
    boost::scoped_ptr<OptionString> optv6;
    ASSERT_NO_THROW(
        // Let's reduce the size of the buffer by one byte and see if our option
        // will absorb this little change.
        optv6.reset(new OptionString(Option::V6, 123, buf_.begin(), buf_.end() - 1));
    );
    // Make sure that it has been initialized to non-NULL value.
    ASSERT_TRUE(optv6);

    // Test the instance of the created option.
    const std::string optv6_value = "This is a test strin";
    EXPECT_EQ(Option::V6, optv6->getUniverse());
    EXPECT_EQ(123, optv6->getType());
    EXPECT_EQ(Option::OPTION6_HDR_LEN + buf_.size() - 1, optv6->len());
    EXPECT_EQ(optv6_value, optv6->getValue());
}

// This test verifies that the current option value can be overriden
// with new value, using setValue method.
TEST_F(OptionStringTest, setValue) {
    // Create an instance of the option and set some initial value.
    OptionString optv4(Option::V4, 123, "some option");
    EXPECT_EQ("some option", optv4.getValue());
    // Replace the value with the new one, and make sure it has
    // been successful.
    EXPECT_NO_THROW(optv4.setValue("new option value"));
    EXPECT_EQ("new option value", optv4.getValue());
    // Try to set to an empty string. It should throw exception.
    EXPECT_THROW(optv4.setValue(""), isc::OutOfRange);
}

// This test verifies that the pack function encodes the option in
// a on-wire format properly.
TEST_F(OptionStringTest, pack) {
    // Create an instance of the option.
    std::string option_value("sample option value");
    OptionString optv4(Option::V4, 123, option_value);
    // Encode the option in on-wire format.
    OutputBuffer buf(Option::OPTION4_HDR_LEN);
    EXPECT_NO_THROW(optv4.pack(buf));

    // Sanity check the length of the buffer.
    ASSERT_EQ(Option::OPTION4_HDR_LEN + option_value.length(),
              buf.getLength());
    // Copy the contents of the OutputBuffer to InputBuffer because
    // the latter has API to read data from it.
    InputBuffer test_buf(buf.getData(), buf.getLength());
    // First byte holds option code.
    EXPECT_EQ(123, test_buf.readUint8());
    // Second byte holds option length.
    EXPECT_EQ(option_value.size(), test_buf.readUint8());
    // Read the option data.
    std::vector<uint8_t> data;
    test_buf.readVector(data, test_buf.getLength() - test_buf.getPosition());
    // And create a string from it.
    std::string test_string(data.begin(), data.end());
    // This string should be equal to the string used to create
    // option's instance. 
    EXPECT_TRUE(option_value == test_string);
}

// This test checks that the DHCP option holding a single string is
// correctly returned in the textual format.
TEST_F(OptionStringTest, toText) {
    // V4 option
    std::string option_value("lorem ipsum");
    OptionString optv4(Option::V4, 122, option_value);
    EXPECT_EQ("type=122, len=011: \"lorem ipsum\" (string)", optv4.toText());

    // V6 option
    option_value = "is a filler text";
    OptionString optv6(Option::V6, 512, option_value);
    EXPECT_EQ("type=00512, len=00016: \"is a filler text\" (string)", optv6.toText());
}

} // anonymous namespace
