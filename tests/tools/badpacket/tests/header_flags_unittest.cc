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


    /// \brief Checks that all options are zero
    ///
    /// Checks that all flags options are set to zero.
    ///
    /// \param flags Flags structure to check.
    /// \param except Index not to check. (This allows options not being tested
    ///        to be checked to see that they are at the default value.)  As all
    ///        index values are positive, a negative value means check
    ///        everything.
    void checkZero(const HeaderFlags& flags, int except = -1) {

        // Check individual fields
        for (int i = OptionInfo::FLAGS_START; i < OptionInfo::FLAGS_END; ++i) {
            if (i != except) {
                EXPECT_EQ(0, flags.get(i));
            }
        }

        // ... and check the composite
        if (except == -1) {
            EXPECT_EQ(0, flags.getValue());
        } else {
            EXPECT_NE(0, flags.getValue());
        }
    }

    /// \brief Check Option
    ///
    /// Checks that an option will only set the appropriate bits in the flags
    /// field.
    ///
    /// \param index Index of the flags field to check.
    /// \param maxval Maximum value of the header field.
    void checkOption(int index, uint32_t maxval) {

        // Create header flags and check initialized properly.
        HeaderFlags flags;
        checkZero(flags);

        // Check we can set field to maximum.
        flags.set(index, maxval);
        EXPECT_EQ(maxval, flags.get(index));
        checkZero(flags, index);

        // Check we can reset it to zero.
        flags.set(index, 0);
        checkZero(flags);
    }
};

// Set of tests to check that setting a bit only sets that bit and nothing
// else.

TEST_F(HeaderFlagsTest, fields) {
    checkOption(OptionInfo::QR, 1);
    checkOption(OptionInfo::OP, 15);
    checkOption(OptionInfo::AA, 1);
    checkOption(OptionInfo::TC, 1);
    checkOption(OptionInfo::RD, 1);
    checkOption(OptionInfo::RA, 1);
    checkOption(OptionInfo::Z,  1);
    checkOption(OptionInfo::AD, 1);
    checkOption(OptionInfo::CD, 1);
    checkOption(OptionInfo::RC, 15);
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
