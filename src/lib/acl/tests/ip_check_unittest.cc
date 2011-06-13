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

// Declare a derived class to allow the abstract function to be declared
// as a concrete one.

class DerivedV4Check : public Ipv4Check<uint32_t> {
public:
    // Basic constructor
    DerivedV4Check(uint32_t address = 1, size_t masksize = 32,
                   bool inverse = false) :
                   Ipv4Check<uint32_t>(address, masksize, inverse)
    {}

    // String constructor
    DerivedV4Check(const std::string& address, bool inverse = false) :
        Ipv4Check<uint32_t>(address, inverse)
    {}

    // Destructor
    virtual ~DerivedV4Check()
    {}

    // Concrete implementation of abstract method
    virtual bool matches(const uint32_t& context) const {
        return (compare(context));
    }
};


/// Tests of the free functions.

TEST(IpCheck, CreateNetmask) {
    size_t  i;

    // 8-bit tests.

    // Invalid arguments should throw.
    EXPECT_THROW(createNetmask<uint8_t>(0), isc::OutOfRange);
    EXPECT_THROW(createNetmask<uint8_t>(9), isc::OutOfRange);

    // Check on all possible 8-bit values.  Use a signed type to generate a
    // variable with the most significant bits set, as right-shifting it is
    // guaranteed to introduce additional bits.
    int8_t  expected8;
    for (i = 1, expected8 = 0x80; i <= 8; ++i, expected8 >>= 1) {
        EXPECT_EQ(static_cast<uint8_t>(expected8),
                  createNetmask<uint8_t>(i));
    }

    // Do the same for 32 bits.
    EXPECT_THROW(createNetmask<int32_t>(0), isc::OutOfRange);
    EXPECT_THROW(createNetmask<int32_t>(33), isc::OutOfRange);

    // Check on all possible 8-bit values
    int32_t expected32;
    for (i = 1, expected32 = 0x80000000; i <= 32; ++i, expected32 >>= 1) {
        EXPECT_EQ(static_cast<uint32_t>(expected32),
                  createNetmask<uint32_t>(i));
    }
}
// IPV4 tests

// Check that the constructor expands the network mask and stores the elements
// correctly.  For these tests, we don't worry about the type of the context,
// so we declare it as an int.

TEST(IpCheck, V4ConstructorAddress) {
    DerivedV4Check acl1(0x12345678);
    EXPECT_EQ(0x12345678, acl1.getAddress());
}

// The mask is stored in network byte order, so the pattern expected must
// also be converted to network byte order for the comparison to succeed.
TEST(IpCheck, V4ConstructorMask) {
    // Valid values. Address of "1" is used as a placeholder
    DerivedV4Check acl1(1, 1);
    uint32_t expected = htonl(0x80000000);
    EXPECT_EQ(expected, acl1.getNetmask());
    EXPECT_EQ(1, acl1.getMasksize());

    DerivedV4Check acl2(1, 24);
    expected = htonl(0xffffff00);
    EXPECT_EQ(expected, acl2.getNetmask());
    EXPECT_EQ(24, acl2.getMasksize());

    // ... and some invalid network masks
    EXPECT_THROW(DerivedV4Check(1, 0), isc::OutOfRange);
    EXPECT_THROW(DerivedV4Check(1, 33), isc::OutOfRange);
}

TEST(IpCheck, V4ConstructorInverse) {
    // Valid values. Address/mask of "1" is used as a placeholder
    DerivedV4Check acl1(1, 1);
    EXPECT_FALSE(acl1.getInverse());

    DerivedV4Check acl2(1, 1, true);
    EXPECT_TRUE(acl2.getInverse());

    DerivedV4Check acl3(1, 1, false);
    EXPECT_FALSE(acl3.getInverse());
}

TEST(IpCheck, V4StringConstructor) {
    DerivedV4Check acl1("127.0.0.1");
    uint32_t expected = htonl(0x7f000001);
    EXPECT_EQ(expected, acl1.getAddress());
    EXPECT_EQ(32, acl1.getMasksize());

    DerivedV4Check acl2("255.255.255.0/24");
    expected = htonl(0xffffff00);
    EXPECT_EQ(expected, acl2.getAddress());
    EXPECT_EQ(24, acl2.getMasksize());

    EXPECT_THROW(DerivedV4Check("255.255.255.0/0"), isc::OutOfRange);
    EXPECT_THROW(DerivedV4Check("255.255.255.0/33"), isc::OutOfRange);
    EXPECT_THROW(DerivedV4Check("255.255.255.0/24/3"), isc::InvalidParameter);
    EXPECT_THROW(DerivedV4Check("255.255.255.0/ww"), isc::InvalidParameter);
    EXPECT_THROW(DerivedV4Check("aa.255.255.0/ww"), isc::InvalidParameter);
}

// Check that the comparison works - note that "matches" just calls the
// internal compare() code.
//
// Note that addresses passed to the class are expected to be in network-
// byte order.  Therefore for the comparisons to work as expected, we must
// convert the values to network-byte order first.

TEST(IpCheck, V4Compare) {
    // Exact address - match if given address matches stored address.
    DerivedV4Check acl1(htonl(0x23457f13), 32);
    EXPECT_TRUE(acl1.matches(htonl(0x23457f13)));
    EXPECT_FALSE(acl1.matches(htonl(0x23457f12)));
    EXPECT_FALSE(acl1.matches(htonl(0x13457f13)));

    // Exact address - match if address does not match stored address
    DerivedV4Check acl2(htonl(0x23457f13), 32, true);
    EXPECT_FALSE(acl2.matches(htonl(0x23457f13)));
    EXPECT_TRUE(acl2.matches(htonl(0x23457f12)));
    EXPECT_TRUE(acl2.matches(htonl(0x13457f13)));

    // Match if the address matches a mask
    DerivedV4Check acl3(htonl(0x23450000), 16);
    EXPECT_TRUE(acl3.matches(htonl(0x23450000)));
    EXPECT_TRUE(acl3.matches(htonl(0x23450001)));
    EXPECT_TRUE(acl3.matches(htonl(0x2345ffff)));
    EXPECT_FALSE(acl3.matches(htonl(0x23460000)));
    EXPECT_FALSE(acl3.matches(htonl(0x2346ffff)));

    // Match if the address does not match a mask
    DerivedV4Check acl4(htonl(0x23450000), 16, true);
    EXPECT_FALSE(acl4.matches(htonl(0x23450000)));
    EXPECT_FALSE(acl4.matches(htonl(0x23450001)));
    EXPECT_FALSE(acl4.matches(htonl(0x2345ffff)));
    EXPECT_TRUE(acl4.matches(htonl(0x23460000)));
    EXPECT_TRUE(acl4.matches(htonl(0x2346ffff)));

}
