// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <d2/d2_zone.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;
using namespace isc::dns;

namespace {

TEST(D2ZoneTest, constructor) {
    D2Zone zone1(Name("example.com"), RRClass::ANY());
    EXPECT_EQ("example.com.", zone1.getName().toText());
    EXPECT_EQ(RRClass::ANY().getCode(), zone1.getClass().getCode());

    D2Zone zone2(Name("foo.example.com"), RRClass::IN());
    EXPECT_EQ("foo.example.com.", zone2.getName().toText());
    EXPECT_EQ(RRClass::IN().getCode(), zone2.getClass().getCode());
}

TEST(D2ZoneTest, toText) {
    D2Zone zone1(Name("example.com"), RRClass::ANY());
    EXPECT_EQ("example.com. ANY SOA\n", zone1.toText());

    D2Zone zone2(Name("foo.example.com"), RRClass::IN());
    EXPECT_EQ("foo.example.com. IN SOA\n", zone2.toText());
}

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
