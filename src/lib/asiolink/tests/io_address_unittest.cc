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

#include <algorithm>
#include <cstring>
#include <vector>

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
    EXPECT_EQ(addr.toText(), IOAddress("192.0.2.3").toText());
}

TEST(IOAddressTest, toBytes) {

    // Address and network byte-order representation of the address.
    const char* V4STRING = "192.0.2.1";
    uint8_t V4[] = {0xc0, 0x00, 0x02, 0x01};

    const char* V6STRING = "2001:db8:1::dead:beef";
    uint8_t V6[] = {
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef 
    };


    // Do the V4 check.
    IOAddress v4address(V4STRING);
    std::vector<uint8_t> v4bytes = v4address.toBytes();
    EXPECT_EQ(sizeof(V4), v4bytes.size());
    EXPECT_TRUE(std::equal(v4bytes.begin(), v4bytes.end(), &V4[0]));

    // Do the same for V6.
    IOAddress v6address(V6STRING);
    std::vector<uint8_t> v6bytes = v6address.toBytes();
    EXPECT_EQ(sizeof(V6), v6bytes.size());
    EXPECT_TRUE(std::equal(v6bytes.begin(), v6bytes.end(), &V6[0]));
}

TEST(IOAddressTest, isV4) {
    const IOAddress address4("192.0.2.1");
    const IOAddress address6("2001:db8:1::dead:beef");

    EXPECT_TRUE(address4.isV4());
    EXPECT_FALSE(address6.isV4());
}

TEST(IOAddressTest, isV6) {
    const IOAddress address4("192.0.2.1");
    const IOAddress address6("2001:db8:1::dead:beef");

    EXPECT_FALSE(address4.isV6());
    EXPECT_TRUE(address6.isV6());
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
