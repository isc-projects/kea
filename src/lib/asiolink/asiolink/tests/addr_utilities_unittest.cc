// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <vector>

#include <stdint.h>
#include <stdlib.h>

using namespace std;
using namespace isc::asiolink;

namespace {

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

    // These are trickier, though, as they are done in 1 bit increments

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

    // These are trickier, though, as they are done in 1 bit increments

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

// Checks if IPv4 netmask is generated properly
TEST(AddrUtilitiesTest, getNetmask4) {
    EXPECT_EQ("0.0.0.0", getNetmask4(0).toText());
    EXPECT_EQ("128.0.0.0", getNetmask4(1).toText());
    EXPECT_EQ("192.0.0.0", getNetmask4(2).toText());
    EXPECT_EQ("224.0.0.0", getNetmask4(3).toText());
    EXPECT_EQ("240.0.0.0", getNetmask4(4).toText());
    EXPECT_EQ("248.0.0.0", getNetmask4(5).toText());
    EXPECT_EQ("252.0.0.0", getNetmask4(6).toText());
    EXPECT_EQ("254.0.0.0", getNetmask4(7).toText());
    EXPECT_EQ("255.0.0.0", getNetmask4(8).toText());

    EXPECT_EQ("255.128.0.0", getNetmask4(9).toText());
    EXPECT_EQ("255.192.0.0", getNetmask4(10).toText());
    EXPECT_EQ("255.224.0.0", getNetmask4(11).toText());
    EXPECT_EQ("255.240.0.0", getNetmask4(12).toText());
    EXPECT_EQ("255.248.0.0", getNetmask4(13).toText());
    EXPECT_EQ("255.252.0.0", getNetmask4(14).toText());
    EXPECT_EQ("255.254.0.0", getNetmask4(15).toText());
    EXPECT_EQ("255.255.0.0", getNetmask4(16).toText());

    EXPECT_EQ("255.255.128.0", getNetmask4(17).toText());
    EXPECT_EQ("255.255.192.0", getNetmask4(18).toText());
    EXPECT_EQ("255.255.224.0", getNetmask4(19).toText());
    EXPECT_EQ("255.255.240.0", getNetmask4(20).toText());
    EXPECT_EQ("255.255.248.0", getNetmask4(21).toText());
    EXPECT_EQ("255.255.252.0", getNetmask4(22).toText());
    EXPECT_EQ("255.255.254.0", getNetmask4(23).toText());
    EXPECT_EQ("255.255.255.0", getNetmask4(24).toText());

    EXPECT_EQ("255.255.255.128", getNetmask4(25).toText());
    EXPECT_EQ("255.255.255.192", getNetmask4(26).toText());
    EXPECT_EQ("255.255.255.224", getNetmask4(27).toText());
    EXPECT_EQ("255.255.255.240", getNetmask4(28).toText());
    EXPECT_EQ("255.255.255.248", getNetmask4(29).toText());
    EXPECT_EQ("255.255.255.252", getNetmask4(30).toText());
    EXPECT_EQ("255.255.255.254", getNetmask4(31).toText());
    EXPECT_EQ("255.255.255.255", getNetmask4(32).toText());

    EXPECT_THROW(getNetmask4(33), isc::BadValue);
}

// Checks if the calculation for IPv4 addresses in range are correct.
TEST(AddrUtilitiesTest, addrsInRange4) {

    // Let's start with something simple
    EXPECT_EQ(1, addrsInRange(IOAddress("192.0.2.0"), IOAddress("192.0.2.0")));
    EXPECT_EQ(10, addrsInRange(IOAddress("192.0.2.10"), IOAddress("192.0.2.19")));
    EXPECT_EQ(256, addrsInRange(IOAddress("192.0.2.0"), IOAddress("192.0.2.255")));
    EXPECT_EQ(65536, addrsInRange(IOAddress("192.0.0.0"), IOAddress("192.0.255.255")));
    EXPECT_EQ(16777216, addrsInRange(IOAddress("10.0.0.0"), IOAddress("10.255.255.255")));

    // Let's check if the network boundaries are crossed correctly.
    EXPECT_EQ(3, addrsInRange(IOAddress("10.0.0.255"), IOAddress("10.0.1.1")));

    // Let's go a bit overboard with this! How many addresses are there in
    // IPv4 address space? That's a slightly tricky question, as the answer
    // cannot be stored in uint32_t.
    EXPECT_EQ(uint64_t(std::numeric_limits<uint32_t>::max()) + 1,
              addrsInRange(IOAddress("0.0.0.0"), IOAddress("255.255.255.255")));

    // The upper bound cannot be smaller than the lower bound.
    EXPECT_THROW(addrsInRange(IOAddress("192.0.2.5"), IOAddress("192.0.2.4")),
                 isc::BadValue);
}

// Checks if the calculation for IPv6 addresses in range are correct.
TEST(AddrUtilitiesTest, addrsInRange6) {

    // Let's start with something simple
    EXPECT_EQ(1, addrsInRange(IOAddress("::"), IOAddress("::")));
    EXPECT_EQ(16, addrsInRange(IOAddress("fe80::1"), IOAddress("fe80::10")));
    EXPECT_EQ(65536, addrsInRange(IOAddress("fe80::"), IOAddress("fe80::ffff")));
    EXPECT_EQ(uint64_t(std::numeric_limits<uint32_t>::max()) + 1,
              addrsInRange(IOAddress("fe80::"), IOAddress("fe80::ffff:ffff")));

    // There's 2^80 addresses between those. Due to uint64_t limits, this method is
    // capped at 2^64 -1.
    EXPECT_EQ(std::numeric_limits<uint64_t>::max(),
              addrsInRange(IOAddress("2001:db8:1::"), IOAddress("2001:db8:2::")));

    // Let's check if the network boundaries are crossed correctly.
    EXPECT_EQ(3, addrsInRange(IOAddress("2001:db8::ffff"), IOAddress("2001:db8::1:1")));

    // Let's go a bit overboard with this! How many addresses are there in
    // IPv6 address space? That's a really tricky question, as the answer
    // wouldn't fit even in uint128_t (if we had it). This method is capped
    // at max value of uint64_t.
    EXPECT_EQ(std::numeric_limits<uint64_t>::max(), addrsInRange(IOAddress("::"),
              IOAddress("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")));

    EXPECT_THROW(addrsInRange(IOAddress("fe80::5"), IOAddress("fe80::4")),
                 isc::BadValue);
}

// Checks if IPv4 address ranges can be converted to prefix / prefix_len
TEST(AddrUtilitiesTest, prefixLengthFromRange4) {
    // Use a shorter name
    const auto& plfr = prefixLengthFromRange;

    // Let's start with something simple
    EXPECT_EQ(32, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.0")));
    EXPECT_EQ(31, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.1")));
    EXPECT_EQ(30, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.3")));
    EXPECT_EQ(29, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.7")));
    EXPECT_EQ(28, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.15")));
    EXPECT_EQ(27, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.31")));
    EXPECT_EQ(26, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.63")));
    EXPECT_EQ(25, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.127")));
    EXPECT_EQ(24, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.2.255")));
    EXPECT_EQ(23, plfr(IOAddress("192.0.2.0"), IOAddress("192.0.3.255")));
    EXPECT_EQ(16, plfr(IOAddress("10.0.0.0"), IOAddress("10.0.255.255")));
    EXPECT_EQ(8, plfr(IOAddress("10.0.0.0"), IOAddress("10.255.255.255")));
    EXPECT_EQ(0, plfr(IOAddress("0.0.0.0"), IOAddress("255.255.255.255")));

    // Fail if a network boundary is crossed
    EXPECT_EQ(-1, plfr(IOAddress("10.0.0.255"), IOAddress("10.0.1.1")));

    // Fail if first is not at the begin
    EXPECT_EQ(-1, plfr(IOAddress("10.0.0.2"), IOAddress("10.0.0.5")));

    // The upper bound cannot be smaller than the lower bound
    EXPECT_THROW(plfr(IOAddress("192.0.2.5"), IOAddress("192.0.2.4")),
                 isc::BadValue);
}

// Checks if IPv6 address ranges can be converted to prefix / prefix_len
TEST(AddrUtilitiesTest, prefixLengthFromRange6) {
    // Use a shorter name
    const auto& plfr = prefixLengthFromRange;

    // Let's start with something simple
    EXPECT_EQ(128, plfr(IOAddress("::"), IOAddress("::")));
    EXPECT_EQ(112, plfr(IOAddress("fe80::"),  IOAddress("fe80::ffff")));
    EXPECT_EQ(96, plfr(IOAddress("fe80::"),  IOAddress("fe80::ffff:ffff")));
    EXPECT_EQ(80, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::ffff:ffff:ffff")));
    EXPECT_EQ(64, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::ffff:ffff:ffff:ffff")));
    EXPECT_EQ(63, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::1:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(62, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::3:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(61, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::7:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(60, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::f:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(59, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::1f:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(58, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::3f:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(57, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::7f:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(56, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::ff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(55, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::1ff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(54, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::3ff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(53, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::7ff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(52, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::fff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(51, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::1fff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(50, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::3fff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(49, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::7fff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(48, plfr(IOAddress("fe80::"),
                       IOAddress("fe80::ffff:ffff:ffff:ffff:ffff")));
    EXPECT_EQ(0, plfr(IOAddress("::"),
                      IOAddress("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")));

    // Fail if a network boundary is crossed
    EXPECT_EQ(-1, plfr(IOAddress("2001:db8::ffff"),
                       IOAddress("2001:db8::1:1")));

    // Fail if first is not at the begin
    EXPECT_EQ(-1, plfr(IOAddress("2001:db8::2"), IOAddress("2001:db8::5")));
    EXPECT_EQ(-1, plfr(IOAddress("2001:db8::2:0"),
                       IOAddress("2001:db8::5:ffff")));
    EXPECT_EQ(-1, plfr(IOAddress("2001:db8::2:ff00:0"),
                       IOAddress("2001:db8::3:00ff:ffff")));

    // The upper bound cannot be smaller than the lower bound
    EXPECT_THROW(plfr(IOAddress("fe80::5"), IOAddress("fe80::4")),
                 isc::BadValue);

    // Address family must match
    EXPECT_THROW(plfr(IOAddress("192.0.2.0"), IOAddress("fe80::1")),
                 isc::BadValue);
}

// Checks if prefixInRange returns valid number of prefixes in specified range.
TEST(AddrUtilitiesTest, prefixesInRange) {

    // How many /64 prefixes are in /64 pool?
    EXPECT_EQ(1, prefixesInRange(64, 64));

    // How many /63 prefixes are in /64 pool?
    EXPECT_EQ(2, prefixesInRange(63, 64));

    // How many /64 prefixes are in /48 pool?
    EXPECT_EQ(65536, prefixesInRange(48, 64));

    // How many /127 prefixes are in /64 pool?
    EXPECT_EQ(uint64_t(9223372036854775808ull), prefixesInRange(64, 127));

    // How many /128 prefixes are in /64 pool?
    EXPECT_EQ(std::numeric_limits<uint64_t>::max(),
              prefixesInRange(64, 128));

    // Let's go overboard again. How many IPv6 addresses are there?
    EXPECT_EQ(std::numeric_limits<uint64_t>::max(),
              prefixesInRange(0, 128));

}

// Checks the function which finds an IPv4 address from input address and offset.
TEST(AddrUtilitiesTest, offsetIPv4Address) {
    EXPECT_EQ("10.1.2.46", offsetAddress(IOAddress("10.1.1.45"), 257).toText());
    EXPECT_EQ("10.1.7.9", offsetAddress(IOAddress("10.1.1.45"), 1500).toText());
    // Using very large offset. The maximum IPv4 address should be returned.
    EXPECT_EQ("255.255.255.255", offsetAddress(IOAddress("255.255.254.254"), 0xFFFFFFFFFFFFFFFA).toText());
}

// Checks the function which finds an IPv6 address from input address and offset.
TEST(AddrUtilitiesTest, offsetIPv6Address) {
    EXPECT_EQ("2001:db8:1::4", offsetAddress(IOAddress("2001:db8:1::4"), 0).toText());
    EXPECT_EQ("2001:db8:1::10:3", offsetAddress(IOAddress("2001:db8:1::4"), 0xFFFFF).toText());
    EXPECT_EQ("2001:db8:2::", offsetAddress(IOAddress("2001:db8:1:FFFF::1"), 0xFFFFFFFFFFFFFFFF).toText());
    EXPECT_EQ("3000::1c", offsetAddress(IOAddress("3000::15"), 7).toText());
}

}; // end of anonymous namespace
