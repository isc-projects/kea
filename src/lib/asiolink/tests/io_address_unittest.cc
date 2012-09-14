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

#include <config.h>
#include <gtest/gtest.h>

#include <asiolink/io_error.h>
#include <asiolink/io_address.h>

#include <cstring>

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

TEST(IOAddressTest, from_bytes) {
    // 2001:db8:1::dead:beef
    uint8_t v6[] = {
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0, 0,
        0, 0, 0, 0, 0xde, 0xad, 0xbe, 0xef };

    uint8_t v4[] = { 192, 0 , 2, 3 };

    IOAddress addr("::");
    EXPECT_NO_THROW({
        addr = IOAddress::from_bytes(AF_INET6, v6);
    });
    EXPECT_EQ("2001:db8:1::dead:beef", addr.toText());

    EXPECT_NO_THROW({
        addr = IOAddress::from_bytes(AF_INET, v4);
    });
    EXPECT_EQ(addr.toText(), IOAddress("192.0.2.3").toText());
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

TEST(IOAddressTest, compare) {
    IOAddress addr1("192.0.2.5");
    IOAddress addr2("192.0.2.6");
    IOAddress addr3("0.0.0.0");

    IOAddress addr4("::");
    IOAddress addr5("2001:db8::1");
    IOAddress addr6("2001:db8::1:0");

    // v4 comparisons
    EXPECT_TRUE(addr1 < addr2);
    EXPECT_FALSE(addr2 < addr1);
    EXPECT_TRUE(addr3 < addr1);
    EXPECT_TRUE(addr3 < addr2);

    // v6 comparisons
    EXPECT_TRUE(addr4 < addr5);
    EXPECT_TRUE(addr5 < addr6);
    EXPECT_FALSE(addr6 < addr5);

    // v4 to v6 - v4 should always be smaller
    EXPECT_TRUE(addr1 < addr4);
    EXPECT_TRUE(addr3 < addr4);
    EXPECT_TRUE(addr2 < addr5);
}
