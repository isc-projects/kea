// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/encode/utf8.h>

#include <gtest/gtest.h>

using namespace isc::util;
using namespace isc::util::encode;
using namespace std;

namespace {

// Verify it does nothing for ASCII.
TEST(Utf8Test, foobar) {
    string str("foobar");
    vector<uint8_t> vec8 = encodeUtf8(str);
    ASSERT_FALSE(vec8.empty());
    const char* start = reinterpret_cast<const char*>(&vec8[0]);
    string str8(start, start + vec8.size());
    EXPECT_EQ(str, str8);
}

// Verify it encodes not ASCII as expected.
TEST(Utf8Test, eightc) {
    string str("-\x8c-");
    vector<uint8_t> vec8 = encodeUtf8(str);
    ASSERT_FALSE(vec8.empty());
    const char* start = reinterpret_cast<const char*>(&vec8[0]);
    string str8(start, start + vec8.size());
    string expected("-\xc2\x8c-");
    EXPECT_EQ(expected, str8);
}

// Verify it handles correctly control characters.
TEST(Utf8Test, control) {
    string str("fo\x00\n\bar");
    vector<uint8_t> vec8 = encodeUtf8(str);
    ASSERT_FALSE(vec8.empty());
    const char* start = reinterpret_cast<const char*>(&vec8[0]);
    string str8(start, start + vec8.size());
    EXPECT_EQ(str, str8);
}

}
