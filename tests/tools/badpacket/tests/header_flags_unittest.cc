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
#include "../header_flags.h"

using namespace isc::badpacket;


// Test fixture class

class HeaderFlagsTest : public ::testing::Test {
public:
    HeaderFlagsTest() {}
};

// Convenience function to check that all values are zero
void
checkZero(const HeaderFlags& flags) {
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));

    EXPECT_EQ(0, flags.getValue());
}


// Set of tests to check that setting a bit only sets that bit and nothing
// else.

TEST_F(HeaderFlagsTest, QRfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::QR, 1);
    EXPECT_EQ(1, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::QR, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, OPfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::OP, 15);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(15, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::OP, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, AAfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::AA, 1);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(1, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::AA, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, TCfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::TC, 1);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(1, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::TC, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, RDfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::RD, 1);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(1, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::RD, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, RAfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::RA, 1);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(1, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::RA, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, Zfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::Z, 1);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(1, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::Z, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, ADfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::AD, 1);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(1, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::AD, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, CDfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::CD, 1);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(1, flags.get(OptionInfo::CD));
    EXPECT_EQ(0, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::CD, 0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, RCfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::RC, 15);
    EXPECT_EQ(0, flags.get(OptionInfo::QR));
    EXPECT_EQ(0, flags.get(OptionInfo::OP));
    EXPECT_EQ(0, flags.get(OptionInfo::AA));
    EXPECT_EQ(0, flags.get(OptionInfo::TC));
    EXPECT_EQ(0, flags.get(OptionInfo::RD));
    EXPECT_EQ(0, flags.get(OptionInfo::RA));
    EXPECT_EQ(0, flags.get(OptionInfo::Z));
    EXPECT_EQ(0, flags.get(OptionInfo::AD));
    EXPECT_EQ(0, flags.get(OptionInfo::CD));
    EXPECT_EQ(15, flags.get(OptionInfo::RC));
    EXPECT_NE(0, flags.getValue());

    flags.set(OptionInfo::RC, 0);
    checkZero(flags);
}

// Check that the correct bits are set

TEST_F(HeaderFlagsTest, bitValues) {
    HeaderFlags flags;
    checkZero(flags);

    flags.set(OptionInfo::QR, 1);
    EXPECT_EQ(0x8000, flags.getValue());

    flags.set(OptionInfo::QR, 0);
    flags.set(OptionInfo::OP, 15);
    EXPECT_EQ(0x7800, flags.getValue());

    flags.set(OptionInfo::OP, 0);
    flags.set(OptionInfo::AA, 1);
    EXPECT_EQ(0x0400, flags.getValue());

    flags.set(OptionInfo::AA, 0);
    flags.set(OptionInfo::TC, 1);
    EXPECT_EQ(0x0200, flags.getValue());

    flags.set(OptionInfo::TC, 0);
    flags.set(OptionInfo::RD, 1);
    EXPECT_EQ(0x0100, flags.getValue());

    flags.set(OptionInfo::RD, 0);
    flags.set(OptionInfo::RA, 1);
    EXPECT_EQ(0x0080, flags.getValue());

    flags.set(OptionInfo::RA, 0);
    flags.set(OptionInfo::Z, 1);
    EXPECT_EQ(0x0040, flags.getValue());

    flags.set(OptionInfo::Z, 0);
    flags.set(OptionInfo::AD, 1);
    EXPECT_EQ(0x0020, flags.getValue());

    flags.set(OptionInfo::AD, 0);
    flags.set(OptionInfo::CD, 1);
    EXPECT_EQ(0x0010, flags.getValue());

    flags.set(OptionInfo::CD, 0);
    flags.set(OptionInfo::RC, 15);
    EXPECT_EQ(0x000F, flags.getValue());
}
