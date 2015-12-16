// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>

#include <asiolink/io_error.h>
#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>

#include <algorithm>
#include <cstring>
#include <vector>
#include <sstream>

using namespace isc::asiolink;

TEST(IOAddressTest, fromText) {
    IOAddress io_address_v4("192.0.2.1");
    EXPECT_EQ("192.0.2.1", io_address_v4.toText());

    IOAddress io_address_v6("2001:db8::1234");
    EXPECT_EQ("2001:db8::1234", io_address_v6.toText());

    // bogus IPv4 address-like input
    EXPECT_THROW(IOAddress("192.0.2.2.1"), IOError);

    // bogus IPv4 address-like input: out-of-range octet
    EXPECT_THROW(IOAddress("192.0.2.300"), IOError);

    // bogus IPv6 address-like input
    EXPECT_THROW(IOAddress("2001:db8:::1234"), IOError);

    // bogus IPv6 address-like input
    EXPECT_THROW(IOAddress("2001:db8::efgh"), IOError);
}

TEST(IOAddressTest, Equality) {
    EXPECT_TRUE(IOAddress("192.0.2.1") == IOAddress("192.0.2.1"));
    EXPECT_FALSE(IOAddress("192.0.2.1") != IOAddress("192.0.2.1"));

    EXPECT_TRUE(IOAddress("192.0.2.1") != IOAddress("192.0.2.2"));
    EXPECT_FALSE(IOAddress("192.0.2.1") == IOAddress("192.0.2.2"));

    EXPECT_TRUE(IOAddress("2001:db8::12") == IOAddress("2001:0DB8:0:0::0012"));
    EXPECT_FALSE(IOAddress("2001:db8::12") != IOAddress("2001:0DB8:0:0::0012"));

    EXPECT_TRUE(IOAddress("2001:db8::1234") != IOAddress("2001:db8::1235"));
    EXPECT_FALSE(IOAddress("2001:db8::1234") == IOAddress("2001:db8::1235"));

    EXPECT_TRUE(IOAddress("2001:db8::1234") != IOAddress("192.0.2.3"));
    EXPECT_FALSE(IOAddress("2001:db8::1234") == IOAddress("192.0.2.3"));
}

TEST(IOAddressTest, Family) {
    EXPECT_EQ(AF_INET, IOAddress("192.0.2.1").getFamily());
    EXPECT_EQ(AF_INET6, IOAddress("2001:0DB8:0:0::0012").getFamily());
}

TEST(IOAddressTest, fromBytes) {
    // 2001:db8:1::dead:beef
    uint8_t v6[] = {
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0, 0,
        0, 0, 0, 0, 0xde, 0xad, 0xbe, 0xef };

    uint8_t v4[] = { 192, 0 , 2, 3 };

    IOAddress addr("::");
    EXPECT_NO_THROW({
        addr = IOAddress::fromBytes(AF_INET6, v6);
    });
    EXPECT_EQ("2001:db8:1::dead:beef", addr.toText());

    EXPECT_NO_THROW({
        addr = IOAddress::fromBytes(AF_INET, v4);
    });
    EXPECT_EQ(addr, IOAddress("192.0.2.3"));
}

TEST(IOAddressTest, toBytesV4) {
    // Address and network byte-order representation of the address.
    const char* V4STRING = "192.0.2.1";
    uint8_t V4[] = {0xc0, 0x00, 0x02, 0x01};

    std::vector<uint8_t> actual = IOAddress(V4STRING).toBytes();
    ASSERT_EQ(sizeof(V4), actual.size());
    EXPECT_TRUE(std::equal(actual.begin(), actual.end(), V4));
}

TEST(IOAddressTest, toBytesV6) {
    // Address and network byte-order representation of the address.
    const char* V6STRING = "2001:db8:1::dead:beef";
    uint8_t V6[] = {
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef
    };

    std::vector<uint8_t> actual = IOAddress(V6STRING).toBytes();
    ASSERT_EQ(sizeof(V6), actual.size());
    EXPECT_TRUE(std::equal(actual.begin(), actual.end(), V6));
}

TEST(IOAddressTest, isV4) {
    const IOAddress address4("192.0.2.1");
    const IOAddress address6("2001:db8:1::dead:beef");

    EXPECT_TRUE(address4.isV4());
    EXPECT_FALSE(address6.isV4());
}

TEST(IOAddressTest, isV4Zero) {
    // 0.0.0.0
    const IOAddress address_zero("0.0.0.0");
    EXPECT_TRUE(address_zero.isV4Zero());
    // :: (v6 zero address)
    const IOAddress address_zero_v6("::");
    EXPECT_FALSE(address_zero_v6.isV4Zero());
    // 192.0.2.3
    const IOAddress address_non_zero("192.0.2.3");
    EXPECT_FALSE(address_non_zero.isV4Zero());
    // 0.0.0.100
    const IOAddress address_non_zero1("0.0.0.100");
    EXPECT_FALSE(address_non_zero1.isV4Zero());
    // 64.0.0.0
    const IOAddress address_non_zero2("64.0.0.0");
    EXPECT_FALSE(address_non_zero2.isV4Zero());
}

TEST(IOAddressTest, isV4Bcast) {
    // 255.255.255.255
    const IOAddress address_bcast("255.255.255.255");
    EXPECT_TRUE(address_bcast.isV4Bcast());
    // 10.2.3.4
    const IOAddress address_non_bcast("10.2.3.4");
    EXPECT_FALSE(address_non_bcast.isV4Bcast());
    // 255.255.255.23
    const IOAddress address_non_bcast1("255.255.255.23");
    EXPECT_FALSE(address_non_bcast1.isV4Bcast());
    // 123.255.255.255
    const IOAddress address_non_bcast2("123.255.255.255");
    EXPECT_FALSE(address_non_bcast2.isV4Bcast());

}

TEST(IOAddressTest, isV6) {
    const IOAddress address4("192.0.2.1");
    const IOAddress address6("2001:db8:1::dead:beef");

    EXPECT_FALSE(address4.isV6());
    EXPECT_TRUE(address6.isV6());
}

TEST(IOAddressTest, isV6Zero) {
    // ::
    const IOAddress address_zero("::");
    EXPECT_TRUE(address_zero.isV6Zero());
    // 0.0.0.0
    const IOAddress address_non_zero("0.0.0.0");
    EXPECT_FALSE(address_non_zero.isV6Zero());
    // ::ff
    const IOAddress address_non_zero1("::ff");
    EXPECT_FALSE(address_non_zero1.isV6Zero());
    // ff::
    const IOAddress address_non_zero2("ff::");
    EXPECT_FALSE(address_non_zero2.isV6Zero());
}

TEST(IOAddressTest, uint32) {
    IOAddress addr1("192.0.2.5");

    // operator uint_32() is used here
    uint32_t tmp = addr1;

    uint32_t expected = (192U << 24) +  (0U << 16) + (2U << 8) + 5U;

    EXPECT_EQ(expected, tmp);

    // now let's try opposite conversion
    IOAddress addr3 = IOAddress(expected);

    EXPECT_EQ(addr3.toText(), "192.0.2.5");
}

TEST(IOAddressTest, lessThanEqual) {
    IOAddress addr1("192.0.2.5");
    IOAddress addr2("192.0.2.6");
    IOAddress addr3("0.0.0.0");

    IOAddress addr4("::");
    IOAddress addr5("2001:db8::1");
    IOAddress addr6("2001:db8::1:0");
    IOAddress addr7("2001:db8::1:0"); // the same as 6

    // v4 comparisons
    EXPECT_TRUE(addr1 < addr2);
    EXPECT_FALSE(addr2 < addr1);
    EXPECT_FALSE(addr2 <= addr1);
    EXPECT_TRUE(addr3 < addr1);
    EXPECT_TRUE(addr3 < addr2);
    EXPECT_TRUE(addr3 <= addr2);

    // v6 comparisons
    EXPECT_TRUE(addr4 < addr5);
    EXPECT_TRUE(addr5 < addr6);
    EXPECT_FALSE(addr6 < addr5);
    EXPECT_FALSE(addr6 <= addr5);

    // v4 to v6 - v4 should always be smaller
    EXPECT_TRUE(addr1 < addr4);
    EXPECT_TRUE(addr3 < addr4);
    EXPECT_TRUE(addr2 < addr5);

    EXPECT_TRUE(addr6 <= addr7);
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST(IOAddressTest, LeftShiftOperator) {
    const IOAddress addr("192.0.2.5");

    std::ostringstream oss;
    oss << addr;
    EXPECT_EQ(addr.toText(), oss.str());
}

// Tests address classification methods (which were previously used by accessing
// underlying asio objects directly)
TEST(IOAddressTest, accessClassificationMethods) {
    IOAddress addr1("192.0.2.5"); // IPv4
    IOAddress addr2("::");  // IPv6
    IOAddress addr3("2001:db8::1"); // global IPv6
    IOAddress addr4("fe80::1234");  // link-local
    IOAddress addr5("ff02::1:2");   // multicast

    EXPECT_TRUE (addr1.isV4());
    EXPECT_FALSE(addr1.isV6());
    EXPECT_FALSE(addr1.isV6LinkLocal());
    EXPECT_FALSE(addr1.isV6Multicast());

    EXPECT_FALSE(addr2.isV4());
    EXPECT_TRUE (addr2.isV6());
    EXPECT_FALSE(addr2.isV6LinkLocal());
    EXPECT_FALSE(addr2.isV6Multicast());

    EXPECT_FALSE(addr3.isV4());
    EXPECT_TRUE (addr3.isV6());
    EXPECT_FALSE(addr3.isV6LinkLocal());
    EXPECT_FALSE(addr3.isV6Multicast());

    EXPECT_FALSE(addr4.isV4());
    EXPECT_TRUE (addr4.isV6());
    EXPECT_TRUE (addr4.isV6LinkLocal());
    EXPECT_FALSE(addr4.isV6Multicast());

    EXPECT_FALSE(addr5.isV4());
    EXPECT_TRUE (addr5.isV6());
    EXPECT_FALSE(addr5.isV6LinkLocal());
    EXPECT_TRUE (addr5.isV6Multicast());
}

TEST(IOAddressTest, staticAddresses) {
    EXPECT_EQ(IOAddress("0.0.0.0"), IOAddress::IPV4_ZERO_ADDRESS());
    EXPECT_EQ(IOAddress("255.255.255.255"), IOAddress::IPV4_BCAST_ADDRESS());
    EXPECT_EQ(IOAddress("::"), IOAddress::IPV6_ZERO_ADDRESS());
}

// Tests whether address subtraction works correctly.
TEST(IOAddressTest, subtract) {
    IOAddress addr1("192.0.2.12");
    IOAddress addr2("192.0.2.5");
    IOAddress addr3("192.0.2.0");
    IOAddress addr4("0.0.2.1");
    IOAddress any4("0.0.0.0");
    IOAddress bcast("255.255.255.255");

    EXPECT_EQ("0.0.0.7", IOAddress::subtract(addr1, addr2).toText());
    EXPECT_EQ("0.0.0.12", IOAddress::subtract(addr1, addr3).toText());

    // Subtracting 0.0.0.0 is like subtracting 0.
    EXPECT_EQ("192.0.2.12", IOAddress::subtract(addr1, any4).toText());
    EXPECT_EQ("192.0.2.13", IOAddress::subtract(addr1, bcast).toText());
    EXPECT_EQ("191.255.255.255", IOAddress::subtract(addr3, addr4).toText());

    // Let's check if we can subtract greater address from smaller.
    // This will check if we can "loop"
    EXPECT_EQ("255.255.255.251", IOAddress::subtract(addr3, addr2).toText());

    IOAddress addr6("fe80::abcd");
    IOAddress addr7("fe80::");
    IOAddress addr8("fe80::1234");
    IOAddress addr9("2001:db8::face");
    IOAddress addr10("2001:db8::ffff:ffff:ffff:ffff");
    IOAddress addr11("::1");
    IOAddress any6("::");

    EXPECT_EQ(IOAddress("::abcd"), IOAddress::subtract(addr6, addr7));
    EXPECT_EQ(IOAddress("::9999"), IOAddress::subtract(addr6, addr8));
    EXPECT_EQ("::ffff:ffff:ffff:531", IOAddress::subtract(addr10, addr9).toText());

    // Subtract with borrow, extreme edition. Need to borrow one bit
    // 112 times.
    EXPECT_EQ("fe7f:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
              IOAddress::subtract(addr7, addr11).toText());

    // Now check if we can loop beyond :: (:: - ::1 is a lot of F's)
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
              IOAddress::subtract(any6, addr11).toText());

    // Subtracting :: is like subtracting 0.
    EXPECT_EQ("2001:db8::face", IOAddress::subtract(addr9, any6).toText());

    // Let's check if we can subtract greater address from smaller.
    // This will check if we can "loop"
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:edcc",
              IOAddress::subtract(addr7, addr8).toText());

    // Inter-family relations are not allowed.
    EXPECT_THROW(IOAddress::subtract(addr1, addr6), isc::BadValue);
    EXPECT_THROW(IOAddress::subtract(addr6, addr1), isc::BadValue);
}

// Test checks whether an address can be increased.
TEST(IOAddressTest, increaseAddr) {
    IOAddress addr1("192.0.2.12");
    IOAddress any4("0.0.0.0");
    IOAddress bcast("255.255.255.255");
    IOAddress addr6("2001:db8::ffff:ffff:ffff:ffff");
    IOAddress addr11("::1");
    IOAddress any6("::");
    IOAddress the_last_one("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff");

    EXPECT_EQ("192.0.2.13", IOAddress::increase(addr1).toText());
    EXPECT_EQ("0.0.0.1", IOAddress::increase(any4).toText());
    EXPECT_EQ("0.0.0.0", IOAddress::increase(bcast).toText());
    EXPECT_EQ("2001:db8:0:1::", IOAddress::increase(addr6).toText());
    EXPECT_EQ(IOAddress("::2"), IOAddress::increase(addr11));
    EXPECT_EQ(IOAddress("::1"), IOAddress::increase(any6));
    EXPECT_EQ(IOAddress("::"), IOAddress::increase(the_last_one));
}
