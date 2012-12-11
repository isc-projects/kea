
// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/addr_utilities.h>

#include <gtest/gtest.h>

#include <vector>

#include <stdint.h>
#include <stdlib.h>

using namespace std;
using namespace isc::dhcp;
using namespace isc::asiolink;

// This test verifies that lastAddrInPrefix is able to handle IPv4 operations.
TEST(AddrUtilitiesTest, lastAddrInPrefix4) {
    IOAddress addr1("192.0.2.1");

    // Prefixes rounded to addresses are easy...
    EXPECT_EQ("192.255.255.255", lastAddrInPrefix(addr1, 8).toText());
    EXPECT_EQ("192.0.255.255",   lastAddrInPrefix(addr1, 16).toText());
    EXPECT_EQ("192.0.2.255",     lastAddrInPrefix(addr1, 24).toText());

    // these are trickier
    EXPECT_EQ("192.0.2.127", lastAddrInPrefix(addr1, 25).toText());
    EXPECT_EQ("192.0.2.63",  lastAddrInPrefix(addr1, 26).toText());
    EXPECT_EQ("192.0.2.31",  lastAddrInPrefix(addr1, 27).toText());
    EXPECT_EQ("192.0.2.15",  lastAddrInPrefix(addr1, 28).toText());
    EXPECT_EQ("192.0.2.7",   lastAddrInPrefix(addr1, 29).toText());
    EXPECT_EQ("192.0.2.3",   lastAddrInPrefix(addr1, 30).toText());

    // that doesn't make much sense as /31 subnet consists of network address
    // and a broadcast address, with 0 usable addresses.
    EXPECT_EQ("192.0.2.1",   lastAddrInPrefix(addr1, 31).toText());
    EXPECT_EQ("192.0.2.1",   lastAddrInPrefix(addr1, 32).toText());

    // Let's check extreme cases
    IOAddress anyAddr("0.0.0.0");
    EXPECT_EQ("127.255.255.255", lastAddrInPrefix(anyAddr, 1).toText());
    EXPECT_EQ("255.255.255.255", lastAddrInPrefix(anyAddr, 0).toText());
    EXPECT_EQ("0.0.0.0", lastAddrInPrefix(anyAddr, 32).toText());
}

// This test checks if firstAddrInPrefix is able to handle IPv4 operations.
TEST(AddrUtilitiesTest, firstAddrInPrefix4) {
    IOAddress addr1("192.223.2.255");

    // Prefixes rounded to addresses are easy...
    EXPECT_EQ("192.0.0.0",   firstAddrInPrefix(addr1, 8).toText());
    EXPECT_EQ("192.223.0.0", firstAddrInPrefix(addr1, 16).toText());
    EXPECT_EQ("192.223.2.0", firstAddrInPrefix(addr1, 24).toText());

    // these are trickier
    EXPECT_EQ("192.223.2.128", firstAddrInPrefix(addr1, 25).toText());
    EXPECT_EQ("192.223.2.192", firstAddrInPrefix(addr1, 26).toText());
    EXPECT_EQ("192.223.2.224", firstAddrInPrefix(addr1, 27).toText());
    EXPECT_EQ("192.223.2.240", firstAddrInPrefix(addr1, 28).toText());
    EXPECT_EQ("192.223.2.248", firstAddrInPrefix(addr1, 29).toText());
    EXPECT_EQ("192.223.2.252", firstAddrInPrefix(addr1, 30).toText());

    // that doesn't make much sense as /31 subnet consists of network address
    // and a broadcast address, with 0 usable addresses.
    EXPECT_EQ("192.223.2.254", firstAddrInPrefix(addr1, 31).toText());
    EXPECT_EQ("192.223.2.255", firstAddrInPrefix(addr1, 32).toText());

    // Let's check extreme cases.
    IOAddress bcast("255.255.255.255");
    EXPECT_EQ("128.0.0.0", firstAddrInPrefix(bcast, 1).toText());
    EXPECT_EQ("0.0.0.0", firstAddrInPrefix(bcast, 0).toText());
    EXPECT_EQ("255.255.255.255", firstAddrInPrefix(bcast, 32).toText());

}

/// This test checks if lastAddrInPrefix properly supports IPv6 operations
TEST(AddrUtilitiesTest, lastAddrInPrefix6) {
    IOAddress addr1("2001:db8:1:1234:5678:abcd:1234:beef");

    // Prefixes rounded to nibbles are easy...
    EXPECT_EQ("2001:db8:1:1234:5678:abcd:1234:ffff",
              lastAddrInPrefix(addr1, 112).toText());
    EXPECT_EQ("2001:db8:1:1234:5678:abcd:123f:ffff",
              lastAddrInPrefix(addr1, 108).toText());
    EXPECT_EQ("2001:db8:1:1234:5678:abcd:12ff:ffff",
              lastAddrInPrefix(addr1, 104).toText());
    EXPECT_EQ("2001:db8:1:1234:ffff:ffff:ffff:ffff",
              lastAddrInPrefix(addr1, 64).toText());

    IOAddress addr2("2001::");

    // These are tricker, though, as they are done in 1 bit increments

    // the last address in 2001::/127 pool should be 2001::1
    EXPECT_EQ("2001::1", lastAddrInPrefix(addr2, 127).toText());

    EXPECT_EQ("2001::3", lastAddrInPrefix(addr2, 126).toText());
    EXPECT_EQ("2001::7", lastAddrInPrefix(addr2, 125).toText());
    EXPECT_EQ("2001::f", lastAddrInPrefix(addr2, 124).toText());
    EXPECT_EQ("2001::1f", lastAddrInPrefix(addr2, 123).toText());
    EXPECT_EQ("2001::3f", lastAddrInPrefix(addr2, 122).toText());
    EXPECT_EQ("2001::7f", lastAddrInPrefix(addr2, 121).toText());
    EXPECT_EQ("2001::ff", lastAddrInPrefix(addr2, 120).toText());

    // Let's check extreme cases
    IOAddress anyAddr("::");
    EXPECT_EQ("7fff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
              lastAddrInPrefix(anyAddr, 1).toText());
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
              lastAddrInPrefix(anyAddr, 0).toText());
    EXPECT_EQ("::", lastAddrInPrefix(anyAddr, 128).toText());
}

/// This test checks if firstAddrInPrefix properly supports IPv6 operations
TEST(AddrUtilitiesTest, firstAddrInPrefix6) {
    IOAddress addr1("2001:db8:1:1234:5678:1234:abcd:beef");

    // Prefixes rounded to nibbles are easy...
    EXPECT_EQ("2001:db8:1:1234:5678:1234::",
              firstAddrInPrefix(addr1, 96).toText());
    EXPECT_EQ("2001:db8:1:1234:5678:1230::",
              firstAddrInPrefix(addr1, 92).toText());
    EXPECT_EQ("2001:db8:1:1234:5678:1200::",
              firstAddrInPrefix(addr1, 88).toText());
    EXPECT_EQ("2001:db8:1:1234::",
              firstAddrInPrefix(addr1, 64).toText());

    IOAddress addr2("2001::ffff");

    // These are tricker, though, as they are done in 1 bit increments

    // the first address in 2001::/127 pool should be 2001::1
    EXPECT_EQ("2001::fffe", firstAddrInPrefix(addr2, 127).toText());

    EXPECT_EQ("2001::fffc", firstAddrInPrefix(addr2, 126).toText());
    EXPECT_EQ("2001::fff8", firstAddrInPrefix(addr2, 125).toText());
    EXPECT_EQ("2001::fff0", firstAddrInPrefix(addr2, 124).toText());
    EXPECT_EQ("2001::ffe0", firstAddrInPrefix(addr2, 123).toText());
    EXPECT_EQ("2001::ffc0", firstAddrInPrefix(addr2, 122).toText());
    EXPECT_EQ("2001::ff80", firstAddrInPrefix(addr2, 121).toText());
    EXPECT_EQ("2001::ff00", firstAddrInPrefix(addr2, 120).toText());
}
