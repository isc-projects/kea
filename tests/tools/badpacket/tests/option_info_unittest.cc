// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <cstddef>
#include <stdint.h>
#include <gtest/gtest.h>

#include "../option_info.h"

using namespace isc::badpacket;


// Test fixture class

class OptionInfoTest : public ::testing::Test {
public:
    OptionInfoTest() {}
};


// Check the values are as expected

TEST_F(OptionInfoTest, values) {

    EXPECT_STREQ("qr", OptionInfo::name(OptionInfo::QR));
    EXPECT_EQ(0x8000,  OptionInfo::mask(OptionInfo::QR));
    EXPECT_EQ(15,      OptionInfo::offset(OptionInfo::QR));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::QR));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::QR));

    EXPECT_STREQ("op", OptionInfo::name(OptionInfo::OP));
    EXPECT_EQ(0x7800,  OptionInfo::mask(OptionInfo::OP));
    EXPECT_EQ(11,      OptionInfo::offset(OptionInfo::OP));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::OP));
    EXPECT_EQ(15,      OptionInfo::maxval(OptionInfo::OP));

    EXPECT_STREQ("aa", OptionInfo::name(OptionInfo::AA));
    EXPECT_EQ(0x0400,  OptionInfo::mask(OptionInfo::AA));
    EXPECT_EQ(10,      OptionInfo::offset(OptionInfo::AA));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::AA));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::AA));

    EXPECT_STREQ("tc", OptionInfo::name(OptionInfo::TC));
    EXPECT_EQ(0x0200,  OptionInfo::mask(OptionInfo::TC));
    EXPECT_EQ(9,       OptionInfo::offset(OptionInfo::TC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::TC));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::TC));

    EXPECT_STREQ("rd", OptionInfo::name(OptionInfo::RD));
    EXPECT_EQ(0x0100,  OptionInfo::mask(OptionInfo::RD));
    EXPECT_EQ(8,       OptionInfo::offset(OptionInfo::RD));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::RD));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::RD));

    EXPECT_STREQ("ra", OptionInfo::name(OptionInfo::RA));
    EXPECT_EQ(0x0080,  OptionInfo::mask(OptionInfo::RA));
    EXPECT_EQ(7,       OptionInfo::offset(OptionInfo::RA));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::RA));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::RA));

    EXPECT_STREQ("z",  OptionInfo::name(OptionInfo::Z));
    EXPECT_EQ(0x0040,  OptionInfo::mask(OptionInfo::Z));
    EXPECT_EQ(6,       OptionInfo::offset(OptionInfo::Z));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::Z));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::Z));

    EXPECT_STREQ("ad", OptionInfo::name(OptionInfo::AD));
    EXPECT_EQ(0x0020,  OptionInfo::mask(OptionInfo::AD));
    EXPECT_EQ(5,       OptionInfo::offset(OptionInfo::AD));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::AD));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::AD));

    EXPECT_STREQ("cd", OptionInfo::name(OptionInfo::CD));
    EXPECT_EQ(0x0010,  OptionInfo::mask(OptionInfo::CD));
    EXPECT_EQ(4,       OptionInfo::offset(OptionInfo::CD));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::CD));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::CD));

    EXPECT_STREQ("rc", OptionInfo::name(OptionInfo::RC));
    EXPECT_EQ(0x000F,  OptionInfo::mask(OptionInfo::RC));
    EXPECT_EQ(0,       OptionInfo::offset(OptionInfo::RC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::RC));
    EXPECT_EQ(15,      OptionInfo::maxval(OptionInfo::RC));
}
