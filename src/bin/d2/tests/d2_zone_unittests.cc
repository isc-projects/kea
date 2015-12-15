// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <d2/d2_zone.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;
using namespace isc::dns;

namespace {

// This test verifies that Zone object is created and its constructor sets
// appropriate values for its members.
TEST(D2ZoneTest, constructor) {
    // Create first object.
    D2Zone zone1(Name("example.com"), RRClass::ANY());
    EXPECT_EQ("example.com.", zone1.getName().toText());
    EXPECT_EQ(RRClass::ANY().getCode(), zone1.getClass().getCode());
    // Create another object to make sure that constructor doesn't assign
    // fixed values, but they change when constructor's parameters change.
    D2Zone zone2(Name("foo.example.com"), RRClass::IN());
    EXPECT_EQ("foo.example.com.", zone2.getName().toText());
    EXPECT_EQ(RRClass::IN().getCode(), zone2.getClass().getCode());
}

// This test verifies that toText() function returns text representation of
// of the zone in expected format.
TEST(D2ZoneTest, toText) {
    // Create first object.
    D2Zone zone1(Name("example.com"), RRClass::ANY());
    EXPECT_EQ("example.com. ANY SOA\n", zone1.toText());
    // Create another object with different parameters to make sure that the
    // function's output changes accordingly.
    D2Zone zone2(Name("foo.example.com"), RRClass::IN());
    EXPECT_EQ("foo.example.com. IN SOA\n", zone2.toText());
}

// This test verifies that the equality and inequality operators behave as
// expected.
TEST(D2ZoneTest, compare) {
    const Name a("a"), b("b");
    const RRClass in(RRClass::IN()), any(RRClass::ANY());

    // Equality check
    EXPECT_TRUE(D2Zone(a, any) == D2Zone(a, any));
    EXPECT_FALSE(D2Zone(a, any) != D2Zone(a, any));

    // Inequality check, objects differ by class.
    EXPECT_FALSE(D2Zone(a, any) == D2Zone(a, in));
    EXPECT_TRUE(D2Zone(a, any) != D2Zone(a, in));

    // Inequality check, objects differ by name.
    EXPECT_FALSE(D2Zone(a, any) == D2Zone(b, any));
    EXPECT_TRUE(D2Zone(a, any) != D2Zone(b, any));

    // Inequality check, objects differ by name and class.
    EXPECT_FALSE(D2Zone(a, any) == D2Zone(b, in));
    EXPECT_TRUE(D2Zone(a, any) != D2Zone(b, in));
}

} // End of anonymous namespace
