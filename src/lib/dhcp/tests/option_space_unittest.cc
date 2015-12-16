// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option_space.h>

#include <gtest/gtest.h>

using namespace isc::dhcp;
using namespace isc;

namespace {

// The purpose of this test is to verify that the constructor
// creates an object with members initialized to correct values.
TEST(OptionSpaceTest, constructor) {
    // Create some option space.
    OptionSpace space("isc", true);
    EXPECT_EQ("isc", space.getName());
    EXPECT_TRUE(space.isVendorSpace());

    // Create another object with different values
    // to check that the values will change.
    OptionSpace space2("abc", false);
    EXPECT_EQ("abc", space2.getName());
    EXPECT_FALSE(space2.isVendorSpace());

    // Verify that constructor throws exception if invalid
    // option space name is provided.
    EXPECT_THROW(OptionSpace("invalid%space.name"), InvalidOptionSpace);
}

// The purpose of this test is to verify that the vendor-space flag
// can be overriden.
TEST(OptionSpaceTest, setVendorSpace) {
    OptionSpace space("isc", true);
    EXPECT_EQ("isc", space.getName());
    EXPECT_TRUE(space.isVendorSpace());

    // Override the vendor space flag.
    space.clearVendorSpace();
    EXPECT_FALSE(space.isVendorSpace());
}

// The purpose of this test is to verify that the static function
// to validate the option space name works correctly.
TEST(OptionSpaceTest, validateName) {
    // Positive test scenarios: letters, digits, dashes, underscores
    // lower/upper case allowed.
    EXPECT_TRUE(OptionSpace::validateName("abc"));
    EXPECT_TRUE(OptionSpace::validateName("dash-allowed"));
    EXPECT_TRUE(OptionSpace::validateName("two-dashes-allowed"));
    EXPECT_TRUE(OptionSpace::validateName("underscore_allowed"));
    EXPECT_TRUE(OptionSpace::validateName("underscore_three_times_allowed"));
    EXPECT_TRUE(OptionSpace::validateName("digits0912"));
    EXPECT_TRUE(OptionSpace::validateName("1234"));
    EXPECT_TRUE(OptionSpace::validateName("UPPER_CASE_allowed"));

    // Negative test scenarions: empty strings, dots, spaces are not
    // allowed
    EXPECT_FALSE(OptionSpace::validateName(""));
    EXPECT_FALSE(OptionSpace::validateName(" "));
    EXPECT_FALSE(OptionSpace::validateName(" isc "));
    EXPECT_FALSE(OptionSpace::validateName("isc "));
    EXPECT_FALSE(OptionSpace::validateName(" isc"));
    EXPECT_FALSE(OptionSpace::validateName("isc with-space"));

    // Hyphens and underscores are not allowed at the beginning
    // and at the end of the option space name.
    EXPECT_FALSE(OptionSpace::validateName("-isc"));
    EXPECT_FALSE(OptionSpace::validateName("isc-"));
    EXPECT_FALSE(OptionSpace::validateName("_isc"));
    EXPECT_FALSE(OptionSpace::validateName("isc_"));

    // Test other special characters
    const char specials[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
                              '+', '=', '[', ']', '{', '}', ';', ':', '"', '\'',
                              '\\', '|', '<','>', ',', '.', '?', '~', '`' };
    for (int i = 0; i < sizeof(specials); ++i) {
        std::ostringstream stream;
        // Concatenate valid option space name: "abc" with an invalid character.
        // That way we get option space names like: "abc!", "abc$" etc. It is
        // expected that the validating function fails form them.
        stream << "abc" << specials[i];
        EXPECT_FALSE(OptionSpace::validateName(stream.str()))
            << "Test failed for special character '" << specials[i] << "'.";
    }
}

// The purpose of this test is to verify that the constructors of the
// OptionSpace6 class set the class members to correct values.
TEST(OptionSpace6Test, constructor) {
    // Create some option space and do not specify enterprise number.
    // In such case the vendor space flag is expected to be
    // set to false.
    OptionSpace6 space1("abcd");
    EXPECT_EQ("abcd", space1.getName());
    EXPECT_FALSE(space1.isVendorSpace());

    // Create an option space and specify an enterprise number. In this
    // case the vendor space flag is expected to be set to true and the
    // enterprise number should be set to a desired value.
    OptionSpace6 space2("abcd", 2145);
    EXPECT_EQ("abcd", space2.getName());
    EXPECT_TRUE(space2.isVendorSpace());
    EXPECT_EQ(2145, space2.getEnterpriseNumber());

    // Verify that constructors throw an exception when invalid option
    // space name has been specified.
    EXPECT_THROW(OptionSpace6("isc dhcp"), InvalidOptionSpace);
    EXPECT_THROW(OptionSpace6("isc%dhcp", 2145), InvalidOptionSpace);
}

// The purpose of this test is to verify an option space can be marked
// vendor option space and enterprise number can be set.
TEST(OptionSpace6Test, setVendorSpace) {
    OptionSpace6 space("isc");
    EXPECT_EQ("isc", space.getName());
    EXPECT_FALSE(space.isVendorSpace());

    // Mark it vendor option space and set enterprise id.
    space.setVendorSpace(1234);
    EXPECT_TRUE(space.isVendorSpace());
    EXPECT_EQ(1234, space.getEnterpriseNumber());

    // Override the enterprise number to make sure and make sure that
    // the new number is returned by the object.
    space.setVendorSpace(2345);
    EXPECT_TRUE(space.isVendorSpace());
    EXPECT_EQ(2345, space.getEnterpriseNumber());

    // Clear the vendor option space flag.
    space.clearVendorSpace();
    EXPECT_FALSE(space.isVendorSpace());
}


}; // end of anonymous namespace
