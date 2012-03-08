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

#include <gtest/gtest.h>
#include <vector>

#include <util/range_utilities.h>

using namespace std;
using namespace isc::util;

TEST(RangeUtilitiesTest, isZero) {

    vector<uint8_t> vec(32,0);

    EXPECT_TRUE(isRangeZero(vec.begin(), vec.end()));

    EXPECT_TRUE(isRangeZero(vec.begin(), vec.begin()+1));

    vec[5] = 1;
    EXPECT_TRUE(isRangeZero(vec.begin(), vec.begin()+5));
    EXPECT_FALSE(isRangeZero(vec.begin(), vec.begin()+6));
}

TEST(RangeUtilitiesTest, randomFill) {

    vector<uint8_t> vec1(16,0);
    vector<uint8_t> vec2(16,0);

    // Testing if returned value is actually random is extraordinary difficult.
    // Let's just generate bunch of vectors and see if we get the same
    // value. If we manage to do that in 100 tries, pseudo-random generator
    // really sucks.
    fillRandom(vec1.begin(), vec1.end());
    for (int i=0; i<100; i++) {
        fillRandom(vec2.begin(), vec2.end());
        if (vec1 == vec2)
            FAIL();
    }

}
