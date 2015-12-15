// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <time.h>

#include <util/time_utilities.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::util;

// See time_utilities.cc
namespace isc {
namespace util {
namespace detail {
extern int64_t (*gettimeFunction)();
}
}
}

namespace {

class DNSSECTimeTest : public ::testing::Test {
protected:
    ~DNSSECTimeTest() {
        detail::gettimeFunction = NULL;
    }
};

TEST_F(DNSSECTimeTest, fromText) {
    // In most cases (in practice) the 32-bit and 64-bit versions should
    // behave identically, so we'll mainly test the 32-bit version, which
    // will be more commonly used in actual code (because many of the wire
    // format time field are 32-bit).  The subtle cases where these two
    // return different values will be tested at the end of this test case.

    // These are bogus and should be rejected
    EXPECT_THROW(timeFromText32("2011 101120000"), InvalidTime);
    EXPECT_THROW(timeFromText32("201101011200-0"), InvalidTime);

    // Short length (or "decimal integer" version of representation;
    // it's valid per RFC4034, but is not supported in this implementation)
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
    EXPECT_EQ(4294967295LU, timeFromText32("21060207062815"));

    // After that, timeFromText32() should start returning the second count
    // modulo 2^32.
    EXPECT_EQ(0, timeFromText32("21060207062816"));
    EXPECT_EQ(10, timeFromText32("21060207062826"));

    // On the other hand, the 64-bit version should return monotonically
    // increasing counters.
    EXPECT_EQ(4294967296LL, timeFromText64("21060207062816"));
    EXPECT_EQ(4294967306LL, timeFromText64("21060207062826"));
}

// This helper templated function tells timeToText32 a faked current time.
// The template parameter is that faked time in the form of int64_t seconds
// since epoch.
template <int64_t NOW>
int64_t
testGetTime() {
    return (NOW);
}

// Seconds since epoch for the year 10K eve.  Commonly used in some tests
// below.
const uint64_t YEAR10K_EVE = 253402300799LL;

TEST_F(DNSSECTimeTest, toText) {
    // Check a basic case with the default (normal) gettimeFunction
    // based on the "real current time".
    // Note: this will fail after year 2078, but at that point we won't use
    // this program anyway:-)
    EXPECT_EQ("20100311233000", timeToText32(1268350200));

    // Set the current time to: Feb 18 09:04:14 UTC 2012 (an arbitrary choice
    // in the range of the first half of uint32 since epoch).
    detail::gettimeFunction = testGetTime<1329555854LL>;

    // Test the "year 2038" problem.
    // Check the result of toText() for "INT_MIN" in int32_t.  It's in the
    // 68-year range from the faked current time, so the result should be
    // in year 2038, instead of 1901.
    EXPECT_EQ("20380119031408", timeToText64(0x80000000L));
    EXPECT_EQ("20380119031408", timeToText32(0x80000000L));

    // A controversial case: what should we do with "-1"?  It's out of range
    // in future, but according to RFC time before epoch doesn't seem to be
    // considered "in-range" either.  Our toText() implementation handles
    // this range as a special case and always treats them as future time
    // until year 2038.  This won't be a real issue in practice, though,
    // since such too large values won't be used in actual deployment by then.
    EXPECT_EQ("21060207062815", timeToText32(0xffffffffL));

    // After the singular point of year 2038, the first half of uint32 can
    // point to a future time.
    // Set the current time to: Apr 1 00:00:00 UTC 2038:
    detail::gettimeFunction = testGetTime<2153692800LL>;
    // then time "10" is Feb 7 06:28:26 UTC 2106
    EXPECT_EQ("21060207062826", timeToText32(10));
    // in 64-bit, it's 2^32 + 10
    EXPECT_EQ("21060207062826", timeToText64(0x10000000aLL));

    // After year 2106, the upper half of uint32 can point to past time
    // (as it should).
    detail::gettimeFunction = testGetTime<0x10000000aLL>;
    EXPECT_EQ("21060207062815", timeToText32(0xffffffffL));

    // Try very large time value.  Actually it's the possible farthest time
    // that can be represented in the form of YYYYMMDDHHmmSS.
    EXPECT_EQ("99991231235959", timeToText64(YEAR10K_EVE));
    detail::gettimeFunction = testGetTime<YEAR10K_EVE - 10>;
    EXPECT_EQ("99991231235959", timeToText32(4294197631LU));
}

TEST_F(DNSSECTimeTest, overflow) {
    // Jan 1, Year 10,000.
    EXPECT_THROW(timeToText64(253402300800LL), InvalidTime);
    detail::gettimeFunction = testGetTime<YEAR10K_EVE - 10>;
    EXPECT_THROW(timeToText32(4294197632LU), InvalidTime);
}

}
