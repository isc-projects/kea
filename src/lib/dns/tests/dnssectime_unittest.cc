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

#include <string>

#include <time.h>

#include <dns/dnssectime.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;

namespace {

TEST(DNSSECTimeTest, fromText) {
    // In most cases (in practice) the 32-bit and 64-bit versions should
    // behave identically, so we'll mainly test the 32-bit version, which
    // will be more commonly used in actual code (because many of the wire
    // format time field are 32-bit).  The subtle cases where these two
    // return different values will be tested at the end of this test case.

    // These are bogus and should be rejected
    EXPECT_THROW(timeFromText32("2011 101120000"), InvalidTime);
    EXPECT_THROW(timeFromText32("201101011200-0"), InvalidTime);

    // Short length
    EXPECT_THROW(timeFromText32("20100223"), InvalidTime);

    // Leap year checks
    EXPECT_THROW(timeFromText32("20110229120000"), InvalidTime);
    EXPECT_THROW(timeFromText32("21000229120000"), InvalidTime);
    EXPECT_NO_THROW(timeFromText32("20000229120000"));
    EXPECT_NO_THROW(timeFromText32("20120229120000"));

    // unusual case: this implementation allows SS=60 for "leap seconds"
    EXPECT_NO_THROW(timeFromText32("20110101120060"));

    // Out of range parameters
    EXPECT_THROW(timeFromText32("19100223214617"), InvalidTime); // YY<1970
    EXPECT_THROW(timeFromText32("20110001120000"), InvalidTime); // MM=00
    EXPECT_THROW(timeFromText32("20111301120000"), InvalidTime); // MM=13
    EXPECT_THROW(timeFromText32("20110100120000"), InvalidTime); // DD=00
    EXPECT_THROW(timeFromText32("20110132120000"), InvalidTime); // DD=32
    EXPECT_THROW(timeFromText32("20110431120000"), InvalidTime); // 'Apr31'
    EXPECT_THROW(timeFromText32("20110101250000"), InvalidTime); // HH=25
    EXPECT_THROW(timeFromText32("20110101126000"), InvalidTime); // mm=60
    EXPECT_THROW(timeFromText32("20110101120061"), InvalidTime); // SS=61

    // Feb 7, 06:28:15 UTC 2106 is the possible maximum time that can be
    // represented as an unsigned 32bit integer without overflow.
    EXPECT_EQ(4294967295L, timeFromText32("21060207062815"));

    // After that, timeFromText32() should start returning the second count
    // modulo 2^32.
    EXPECT_EQ(0, timeFromText32("21060207062816"));
    EXPECT_EQ(10, timeFromText32("21060207062826"));

    // On the other hand, the 64-bit version should return monotonically
    // increasing counters.
    EXPECT_EQ(4294967296LL, timeFromText64("21060207062816"));
    EXPECT_EQ(4294967306LL, timeFromText64("21060207062826"));
}

TEST(DNSSECTimeTest, toText) {
    EXPECT_EQ("19700101000000", timeToText(0));
    EXPECT_EQ("20100311233000", timeToText(1268350200));
}

TEST(DNSSECTimeTest, overflow) {
    // Jan 1, Year 10,000.
    if (sizeof(time_t) > 4) {
        EXPECT_THROW(timeToText(static_cast<time_t>(253402300800LL)),
                     InvalidTime);
    }
}

}
