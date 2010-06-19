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

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrtype.h>

#include "unittest_util.h"

using namespace std;
using namespace isc;
using namespace isc::dns;

namespace {
class RRTypeTest : public ::testing::Test {
protected:
    RRTypeTest() : obuffer(0), renderer(obuffer) {}

    OutputBuffer obuffer;
    MessageRenderer renderer;

    static RRType rrtypeFactoryFromWire(const char* datafile);
    static const RRType rrtype_1, rrtype_0x80, rrtype_0x800, rrtype_0x8000,
        rrtype_max;
    static const uint8_t wiredata[];
};

const RRType RRTypeTest::rrtype_1(1);
const RRType RRTypeTest::rrtype_0x80(0x80);
const RRType RRTypeTest::rrtype_0x800(0x800);
const RRType RRTypeTest::rrtype_0x8000(0x8000);
const RRType RRTypeTest::rrtype_max(0xffff);
// This is wire-format data for the above sample RRTypes rendered in the
// appearing order.
const uint8_t RRTypeTest::wiredata[] = { 0x00, 0x01, 0x00, 0x80, 0x08,
                                         0x00, 0x80, 0x00, 0xff, 0xff };

RRType
RRTypeTest::rrtypeFactoryFromWire(const char* datafile)
{
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());

    return (RRType(buffer));
}

TEST_F(RRTypeTest, fromText)
{
    EXPECT_EQ("A", RRType("A").toText());
    EXPECT_EQ("NS", RRType("NS").toText());

    EXPECT_EQ("TYPE65535", RRType("TYPE65535").toText());

    // something unusual, but existing implementations accept this form,
    // so do we.
    EXPECT_EQ(53, RRType("TYPE00053").getCode());
    // again, unusual, and the majority of other implementations reject it.
    // In any case, there should be no reasonable reason to accept such a
    // ridiculously long input.
    EXPECT_THROW(RRType("TYPE000053"), InvalidRRType);

    // bogus TYPEnnn representations: should trigger an exception
    EXPECT_THROW(RRType("TYPE"), InvalidRRType);
    EXPECT_THROW(RRType("TYPE-1"), InvalidRRType);
    EXPECT_THROW(RRType("TYPExxx"), InvalidRRType);
    EXPECT_THROW(RRType("TYPE65536"), InvalidRRType);
    EXPECT_THROW(RRType("TYPE6500x"), InvalidRRType);
    EXPECT_THROW(RRType("TYPE65000 "), InvalidRRType);
}

TEST_F(RRTypeTest, fromWire)
{
    EXPECT_EQ(0x1234,
              rrtypeFactoryFromWire("rrcode16_fromWire1").getCode());
    EXPECT_THROW(rrtypeFactoryFromWire("rrcode16_fromWire2"), IncompleteRRType);
}

// from string, lower case
TEST_F(RRTypeTest, caseConstruct)
{
    EXPECT_EQ("A", RRType("a").toText());
    EXPECT_EQ("NS", RRType("ns").toText());
    EXPECT_EQ("TYPE65535", RRType("type65535").toText());
}

TEST_F(RRTypeTest, toText)
{
    EXPECT_EQ("A", RRType(1).toText());
    EXPECT_EQ("TYPE65000", RRType(65000).toText());
}

TEST_F(RRTypeTest, toWireBuffer)
{
    rrtype_1.toWire(obuffer);
    rrtype_0x80.toWire(obuffer);
    rrtype_0x800.toWire(obuffer);
    rrtype_0x8000.toWire(obuffer);
    rrtype_max.toWire(obuffer);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata, sizeof(wiredata));
}

TEST_F(RRTypeTest, toWireRenderer)
{
    rrtype_1.toWire(renderer);
    rrtype_0x80.toWire(renderer);
    rrtype_0x800.toWire(renderer);
    rrtype_0x8000.toWire(renderer);
    rrtype_max.toWire(renderer);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata, sizeof(wiredata));
}

TEST_F(RRTypeTest, wellKnownTypes)
{
    EXPECT_EQ(1, RRType::A().getCode());
    EXPECT_EQ("A", RRType::A().toText());
}

TEST_F(RRTypeTest, compare)
{
    EXPECT_TRUE(RRType(1) == RRType("A"));
    EXPECT_TRUE(RRType(1).equals(RRType("A")));
    EXPECT_TRUE(RRType(0) != RRType("A"));
    EXPECT_TRUE(RRType(0).nequals(RRType("A")));

    EXPECT_TRUE(RRType("A") < RRType("NS"));
    EXPECT_TRUE(RRType(100) < RRType(65535));
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RRTypeTest, LeftShiftOperator)
{
    ostringstream oss;
    oss << RRType::A();
    EXPECT_EQ(RRType::A().toText(), oss.str());
}
}
