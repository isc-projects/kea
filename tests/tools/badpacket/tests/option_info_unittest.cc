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

TEST_F(OptionInfoTest, FlagValues) {
    EXPECT_STREQ("qr", OptionInfo::name(OptionInfo::QR));
    EXPECT_STREQ("qr", OptionInfo::name(OptionInfo::getIndex('Q')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::QR));
    EXPECT_EQ(0x8000,  OptionInfo::mask(OptionInfo::QR));
    EXPECT_EQ(15,      OptionInfo::offset(OptionInfo::QR));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::QR));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::QR));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::QR));

    EXPECT_STREQ("op", OptionInfo::name(OptionInfo::OP));
    EXPECT_STREQ("op", OptionInfo::name(OptionInfo::getIndex('O')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::OP));
    EXPECT_EQ(0x7800,  OptionInfo::mask(OptionInfo::OP));
    EXPECT_EQ(11,      OptionInfo::offset(OptionInfo::OP));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::OP));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::OP));
    EXPECT_EQ(15,      OptionInfo::maxval(OptionInfo::OP));

    EXPECT_STREQ("aa", OptionInfo::name(OptionInfo::AA));
    EXPECT_STREQ("aa", OptionInfo::name(OptionInfo::getIndex('A')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::AA));
    EXPECT_EQ(0x0400,  OptionInfo::mask(OptionInfo::AA));
    EXPECT_EQ(10,      OptionInfo::offset(OptionInfo::AA));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::AA));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::AA));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::AA));

    EXPECT_STREQ("tc", OptionInfo::name(OptionInfo::TC));
    EXPECT_STREQ("tc", OptionInfo::name(OptionInfo::getIndex('T')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::TC));
    EXPECT_EQ(0x0200,  OptionInfo::mask(OptionInfo::TC));
    EXPECT_EQ(9,       OptionInfo::offset(OptionInfo::TC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::TC));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::TC));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::TC));

    EXPECT_STREQ("rd", OptionInfo::name(OptionInfo::RD));
    EXPECT_STREQ("rd", OptionInfo::name(OptionInfo::getIndex('D')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::RD));
    EXPECT_EQ(0x0100,  OptionInfo::mask(OptionInfo::RD));
    EXPECT_EQ(8,       OptionInfo::offset(OptionInfo::RD));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::RD));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::RD));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::RD));

    EXPECT_STREQ("ra", OptionInfo::name(OptionInfo::RA));
    EXPECT_STREQ("ra", OptionInfo::name(OptionInfo::getIndex('R')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::RA));
    EXPECT_EQ(0x0080,  OptionInfo::mask(OptionInfo::RA));
    EXPECT_EQ(7,       OptionInfo::offset(OptionInfo::RA));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::RA));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::RA));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::RA));

    EXPECT_STREQ("z",  OptionInfo::name(OptionInfo::Z));
    EXPECT_STREQ("z",  OptionInfo::name(OptionInfo::getIndex('Z')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::Z));
    EXPECT_EQ(0x0040,  OptionInfo::mask(OptionInfo::Z));
    EXPECT_EQ(6,       OptionInfo::offset(OptionInfo::Z));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::Z));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::Z));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::Z));

    EXPECT_STREQ("ad", OptionInfo::name(OptionInfo::AD));
    EXPECT_STREQ("ad", OptionInfo::name(OptionInfo::getIndex('U')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::AD));
    EXPECT_EQ(0x0020,  OptionInfo::mask(OptionInfo::AD));
    EXPECT_EQ(5,       OptionInfo::offset(OptionInfo::AD));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::AD));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::AD));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::AD));

    EXPECT_STREQ("cd", OptionInfo::name(OptionInfo::CD));
    EXPECT_STREQ("cd", OptionInfo::name(OptionInfo::getIndex('C')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::CD));
    EXPECT_EQ(0x0010,  OptionInfo::mask(OptionInfo::CD));
    EXPECT_EQ(4,       OptionInfo::offset(OptionInfo::CD));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::CD));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::CD));
    EXPECT_EQ(1,       OptionInfo::maxval(OptionInfo::CD));

    EXPECT_STREQ("rc", OptionInfo::name(OptionInfo::RC));
    EXPECT_STREQ("rc", OptionInfo::name(OptionInfo::getIndex('E')));
    EXPECT_EQ(2,       OptionInfo::word(OptionInfo::RC));
    EXPECT_EQ(0x000F,  OptionInfo::mask(OptionInfo::RC));
    EXPECT_EQ(0,       OptionInfo::offset(OptionInfo::RC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::RC));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::RC));
    EXPECT_EQ(15,      OptionInfo::maxval(OptionInfo::RC));
}

TEST_F(OptionInfoTest, CountValues) {
    EXPECT_STREQ("qc", OptionInfo::name(OptionInfo::QC));
    EXPECT_STREQ("qc", OptionInfo::name(OptionInfo::getIndex('Y')));
    EXPECT_EQ(4,       OptionInfo::word(OptionInfo::QC));
    EXPECT_EQ(1,       OptionInfo::defval(OptionInfo::QC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::QC));
    EXPECT_EQ(0xFFFF,  OptionInfo::maxval(OptionInfo::QC));

    EXPECT_STREQ("ac", OptionInfo::name(OptionInfo::AC));
    EXPECT_STREQ("ac", OptionInfo::name(OptionInfo::getIndex('W')));
    EXPECT_EQ(6,       OptionInfo::word(OptionInfo::AC));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::AC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::AC));
    EXPECT_EQ(0xFFFF,  OptionInfo::maxval(OptionInfo::AC));

    EXPECT_STREQ("uc", OptionInfo::name(OptionInfo::UC));
    EXPECT_STREQ("uc", OptionInfo::name(OptionInfo::getIndex('H')));
    EXPECT_EQ(8,       OptionInfo::word(OptionInfo::UC));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::UC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::UC));
    EXPECT_EQ(0xFFFF,  OptionInfo::maxval(OptionInfo::UC));

    EXPECT_STREQ("dc", OptionInfo::name(OptionInfo::DC));
    EXPECT_STREQ("dc", OptionInfo::name(OptionInfo::getIndex('I')));
    EXPECT_EQ(10,      OptionInfo::word(OptionInfo::DC));
    EXPECT_EQ(0,       OptionInfo::defval(OptionInfo::DC));
    EXPECT_EQ(0,       OptionInfo::minval(OptionInfo::DC));
    EXPECT_EQ(0xFFFF,  OptionInfo::maxval(OptionInfo::DC));
}

TEST_F(OptionInfoTest, OtherValues) {
    EXPECT_STREQ("ms", OptionInfo::name(OptionInfo::MS));
    EXPECT_STREQ("ms", OptionInfo::name(OptionInfo::getIndex('M')));
    EXPECT_EQ(1,       OptionInfo::minval(OptionInfo::MS));
    EXPECT_EQ(65536,   OptionInfo::maxval(OptionInfo::MS));
}
