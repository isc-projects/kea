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


#include <gtest/gtest.h>
#include <acl/ip_check.h>

using namespace isc::acl;

/// General tests

TEST(IpCheck, CreateNetmask) {
    size_t  i;

    // 8-bit tests.

    // Invalid arguments should throw.
    EXPECT_THROW(createNetmask<int8_t>(0), isc::OutOfRange);
    EXPECT_THROW(createNetmask<int8_t>(9), isc::OutOfRange);

    // Check on all possible 8-bit values
    int8_t  expected8;
    for (i = 1, expected8 = 0x80; i <= 8; ++i, expected8 >>= 1) {
        EXPECT_EQ(static_cast<int32_t>(expected8),
                  static_cast<int32_t>(createNetmask<int8_t>(i)));
    }

    // Do the same for 32 bits.
    EXPECT_THROW(createNetmask<int32_t>(0), isc::OutOfRange);
    EXPECT_THROW(createNetmask<int32_t>(33), isc::OutOfRange);

    // Check on all possible 8-bit values
    int32_t expected32;
    for (i = 1, expected32 = 0x80000000; i <= 32; ++i, expected32 >>= 1) {
        EXPECT_EQ(expected32, createNetmask<int32_t>(i));
    }
}

// V4 tests

// Check that the constructor expands the network mask and stores the elements
// correctly.  For these tests, we don't worry about the type of the context,
// so we declare it as an int.

TEST(IpCheck, V4ConstructorAddress) {
    // Alternating bits
    Ipv4Check<int> acl1(0x55555555);
    EXPECT_EQ(0x55555555, acl1.getAddress());

    Ipv4Check<int> acl2(0xcccccccc);
    EXPECT_EQ(0xcccccccc, acl2.getAddress());
}

TEST(IpCheck, V4ConstructorMask) {
    // Valid values. Address of "1" is used as a placeholder
    Ipv4Check<int> acl1(1, 1);
    EXPECT_EQ(0x80000000, acl1.getNetmask());
    EXPECT_EQ(1, acl1.getMasksize());

    Ipv4Check<int> acl2(1, 24);
    EXPECT_EQ(0xffffff00, acl2.getNetmask());
    EXPECT_EQ(24, acl2.getMasksize());

    // ... and some invalid network masks
    EXPECT_THROW(Ipv4Check<int>(1, 0), isc::OutOfRange);
}

TEST(IpCheck, V4ConstructorInverse) {
    // Valid values. Address/mask of "1" is used as a placeholder
    Ipv4Check<int> acl1(1, 1);
    EXPECT_FALSE(acl1.getInverse());

    Ipv4Check<int> acl2(1, 1, true);
    EXPECT_TRUE(acl2.getInverse());

    Ipv4Check<int> acl3(1, 1, false);
    EXPECT_FALSE(acl3.getInverse());
}

TEST(IpCheck, V4StringConstructor) {
    Ipv4Check<int> acl1("127.0.0.1");
    EXPECT_EQ(0x7f000001, acl1.getAddress());
    EXPECT_EQ(32, acl1.getMasksize());

    Ipv4Check<int> acl2("255.255.255.0/24");
    EXPECT_EQ(0xffffff00, acl2.getAddress());
    EXPECT_EQ(24, acl2.getMasksize());

    EXPECT_THROW(Ipv4Check<int>("255.255.255.0/0"), isc::OutOfRange);
    EXPECT_THROW(Ipv4Check<int>("255.255.255.0/33"), isc::OutOfRange);
    EXPECT_THROW(Ipv4Check<int>("255.255.255.0/24/3"), isc::InvalidParameter);
    EXPECT_THROW(Ipv4Check<int>("255.255.255.0/ww"), isc::InvalidParameter);
    EXPECT_THROW(Ipv4Check<int>("aa.255.255.0/ww"), isc::InvalidParameter);
}

// Check that the comparison works - until we have a a message structure,
// we can't check the matches function.

TEST(IpCheck, V4Compare) {
    // Exact address - match if given address matches stored address
    Ipv4Check<int> acl1(0x23457f13, 32);
    EXPECT_TRUE(acl1.compare(0x23457f13));
    EXPECT_FALSE(acl1.compare(0x23457f12));
    EXPECT_FALSE(acl1.compare(0x13457f13));

    // Exact address - match if address does not match stored address
    Ipv4Check<int> acl2(0x23457f13, 32, true);
    EXPECT_FALSE(acl2.compare(0x23457f13));
    EXPECT_TRUE(acl2.compare(0x23457f12));
    EXPECT_TRUE(acl2.compare(0x13457f13));

    // Match if the address matches a mask
    Ipv4Check<int> acl3(0x23450000, 16);
    EXPECT_TRUE(acl3.compare(0x23450000));
    EXPECT_TRUE(acl3.compare(0x23450001));
    EXPECT_TRUE(acl3.compare(0x2345ffff));
    EXPECT_FALSE(acl3.compare(0x23460000));
    EXPECT_FALSE(acl3.compare(0x2346ffff));

    // Match if the address does not match a mask
    Ipv4Check<int> acl4(0x23450000, 16, true);
    EXPECT_FALSE(acl4.compare(0x23450000));
    EXPECT_FALSE(acl4.compare(0x23450001));
    EXPECT_FALSE(acl4.compare(0x2345ffff));
    EXPECT_TRUE(acl4.compare(0x23460000));
    EXPECT_TRUE(acl4.compare(0x2346ffff));

    // 
}

