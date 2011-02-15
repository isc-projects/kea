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

using namespace asiolink;

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