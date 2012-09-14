
// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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
#include <stdint.h>
#include <stdlib.h>

#include <gtest/gtest.h>
#include <vector>

#include <util/addr_utilities.h>

using namespace std;
using namespace isc::util;
using namespace isc::asiolink;

TEST(Pool6Test, lastAddrInPrefix) {
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
}

TEST(Pool6Test, firstAddrInPrefix) {
    IOAddress addr1("2001:db8:1:1234:5678:abcd:1234:beef");

    // Prefixes rounded to nibbles are easy...
    EXPECT_EQ("2001:db8:1:1234:5678:abcd:1234:0",
              firstAddrInPrefix(addr1, 112).toText());
    EXPECT_EQ("2001:db8:1:1234:5678:abcd:1230:0",
              firstAddrInPrefix(addr1, 108).toText());
    EXPECT_EQ("2001:db8:1:1234:5678:abcd:1200:0",
              firstAddrInPrefix(addr1, 104).toText());
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
