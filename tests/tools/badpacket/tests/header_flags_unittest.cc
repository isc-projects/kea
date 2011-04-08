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
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());

    EXPECT_EQ(0, flags.getValue());
}


// Set of tests to check that setting a bit only sets that bit and nothing
// else.

TEST_F(HeaderFlagsTest, QRfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setQR(1);
    EXPECT_EQ(1, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setQR(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, OPfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setOP(15);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(15, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setOP(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, AAfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setAA(1);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(1, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setAA(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, TCfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setTC(1);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(1, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setTC(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, RDfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setRD(1);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(1, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setRD(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, RAfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setRA(1);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(1, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setRA(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, Zfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setZ(1);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(1, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setZ(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, ADfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setAD(1);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(1, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setAD(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, CDfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setCD(1);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(1, flags.getCD());
    EXPECT_EQ(0, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setCD(0);
    checkZero(flags);
}

TEST_F(HeaderFlagsTest, RCfield) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setRC(7);
    EXPECT_EQ(0, flags.getQR());
    EXPECT_EQ(0, flags.getOP());
    EXPECT_EQ(0, flags.getAA());
    EXPECT_EQ(0, flags.getTC());
    EXPECT_EQ(0, flags.getRD());
    EXPECT_EQ(0, flags.getRA());
    EXPECT_EQ(0, flags.getZ());
    EXPECT_EQ(0, flags.getAD());
    EXPECT_EQ(0, flags.getCD());
    EXPECT_EQ(7, flags.getRC());
    EXPECT_NE(0, flags.getValue());

    flags.setRC(0);
    checkZero(flags);
}

// Check that the correct bits are set

TEST_F(HeaderFlagsTest, bitValues) {
    HeaderFlags flags;
    checkZero(flags);

    flags.setQR(1);
    EXPECT_EQ(0x8000, flags.getValue());

    flags.setQR(0);
    flags.setOP(15);
    EXPECT_EQ(0x7800, flags.getValue());

    flags.setOP(0);
    flags.setAA(1);
    EXPECT_EQ(0x0400, flags.getValue());

    flags.setAA(0);
    flags.setTC(1);
    EXPECT_EQ(0x0200, flags.getValue());

    flags.setTC(0);
    flags.setRD(1);
    EXPECT_EQ(0x0100, flags.getValue());

    flags.setRD(0);
    flags.setRA(1);
    EXPECT_EQ(0x0080, flags.getValue());

    flags.setRA(0);
    flags.setZ(1);
    EXPECT_EQ(0x0040, flags.getValue());

    flags.setZ(0);
    flags.setAD(1);
    EXPECT_EQ(0x0020, flags.getValue());

    flags.setAD(0);
    flags.setCD(1);
    EXPECT_EQ(0x0010, flags.getValue());

    flags.setCD(0);
    flags.setRC(15);
    EXPECT_EQ(0x000F, flags.getValue());
}
