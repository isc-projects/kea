// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <stdint.h>
#include <stdlib.h>

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

    srandom(time(NULL));

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
