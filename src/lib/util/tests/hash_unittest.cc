// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/hash.h>

#include <gtest/gtest.h>

#include <cstring>
#include <vector>

using namespace isc::util;
using namespace std;

namespace {

TEST(HashTest, empty) {
    EXPECT_EQ(14695981039346656037ull, Hash64::hash(0, 0));
}

TEST(HashTest, foobar) {
    EXPECT_EQ(9625390261332436968ull, Hash64::hash(string("foobar")));
}

TEST(HashTest, chongo) {
    EXPECT_EQ(5080352029159061781ull,
              Hash64::hash(string("chongo was here!\n")));
}

}
