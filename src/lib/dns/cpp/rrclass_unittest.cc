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

// $Id$

#include <gtest/gtest.h>

#include "rrparamregistry.h"
#include "rrclass.h"

using isc::dns::RRClass;

namespace {
class RRClassTest : public ::testing::Test {
protected:
};

TEST_F(RRClassTest, construct)
{
    EXPECT_EQ("IN", RRClass("IN").toText());
    EXPECT_EQ("CH", RRClass("CH").toText());

    EXPECT_EQ("CLASS65535", RRClass("CLASS65535").toText());

    // bogus CLASSnnn representations: should trigger an exception
    EXPECT_THROW(RRClass("CLASS"), isc::dns::InvalidRRClass);
    EXPECT_THROW(RRClass("CLASSxxx"), isc::dns::InvalidRRClass);
    EXPECT_THROW(RRClass("CLASS65536"), isc::dns::InvalidRRClass);
    EXPECT_THROW(RRClass("CLASS6500x"), isc::dns::InvalidRRClass);
    EXPECT_THROW(RRClass("CLASS65000 "), isc::dns::InvalidRRClass);
}

TEST_F(RRClassTest, caseConstruct)
{
    EXPECT_EQ("IN", RRClass("in").toText());
    EXPECT_EQ("CH", RRClass("ch").toText());
    EXPECT_EQ("CLASS65535", RRClass("class65535").toText());
}

TEST_F(RRClassTest, toText)
{
    EXPECT_EQ("IN", RRClass(1).toText());
    EXPECT_EQ("CLASS65000", RRClass(65000).toText());
}

TEST_F(RRClassTest, wellKnownClasss)
{
    EXPECT_EQ(1, RRClass::IN().getCode());
    EXPECT_EQ("IN", RRClass::IN().toText());
}

TEST_F(RRClassTest, compare)
{
    EXPECT_TRUE(RRClass(1) == RRClass("IN"));
    EXPECT_TRUE(RRClass(0) != RRClass("IN"));

    EXPECT_TRUE(RRClass("IN") < RRClass("CH"));
    EXPECT_TRUE(RRClass(100) < RRClass(65535));
}
}
