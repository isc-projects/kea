// Copyright (C) 2012, 2013 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <dhcpsrv/option_space.h>

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
    space.setVendorSpace(false);
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

}; // end of anonymous namespace
