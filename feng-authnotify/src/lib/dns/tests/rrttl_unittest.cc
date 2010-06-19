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
#include <dns/rrttl.h>

#include "unittest_util.h"

using namespace std;
using namespace isc;
using namespace isc::dns;

namespace {
class RRTTLTest : public ::testing::Test {
protected:
    RRTTLTest() : obuffer(0), renderer(obuffer) {}       

    OutputBuffer obuffer;
    MessageRenderer renderer;

    static RRTTL rrttlFactoryFromWire(const char* datafile);
    static const RRTTL ttl_0, ttl_1h, ttl_1d, ttl_32bit, ttl_max;
    static const RRTTL ttl_small, ttl_large;
    static const uint8_t wiredata[20];
};

const RRTTL RRTTLTest::ttl_0(0);
const RRTTL RRTTLTest::ttl_1h(3600);
const RRTTL RRTTLTest::ttl_1d(86400);
const RRTTL RRTTLTest::ttl_32bit(0x12345678);
const RRTTL RRTTLTest::ttl_max(0xffffffff);

const RRTTL RRTTLTest::ttl_small(1);
const RRTTL RRTTLTest::ttl_large(0x80000001);
// This is wire-format data for the above sample RRTTLs rendered in the
// appearing order.
const uint8_t RRTTLTest::wiredata[20] = { 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x0e, 0x10,
                                           0x00, 0x01, 0x51, 0x80,
                                           0x12, 0x34, 0x56, 0x78,
                                           0xff, 0xff, 0xff, 0xff };

RRTTL
RRTTLTest::rrttlFactoryFromWire(const char* datafile)
{
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());

    return (RRTTL(buffer));
}

TEST_F(RRTTLTest, fromText)
{
    EXPECT_EQ(0, ttl_0.getValue());
    EXPECT_EQ(3600, ttl_1h.getValue());
    EXPECT_EQ(86400, ttl_1d.getValue());
    EXPECT_EQ(0x12345678, ttl_32bit.getValue());
    EXPECT_EQ(0xffffffff, ttl_max.getValue());

    EXPECT_THROW(RRTTL("1D"), InvalidRRTTL); // we don't support this form yet
    EXPECT_THROW(RRTTL("0xdeadbeef"), InvalidRRTTL); // must be decimal
    EXPECT_THROW(RRTTL("-1"), InvalidRRTTL); // must be positive
    EXPECT_THROW(RRTTL("1.1"), InvalidRRTTL); // must be integer
    EXPECT_THROW(RRTTL("4294967296"), InvalidRRTTL); // must be 32-bit
}

TEST_F(RRTTLTest, fromWire)
{
    EXPECT_EQ(0x12345678,
              rrttlFactoryFromWire("rrcode32_fromWire1").getValue());
    EXPECT_THROW(rrttlFactoryFromWire("rrcode32_fromWire2"),
                 IncompleteRRTTL);
}

TEST_F(RRTTLTest, toText)
{
    EXPECT_EQ("0", ttl_0.toText());
    EXPECT_EQ("3600", ttl_1h.toText());
    EXPECT_EQ("86400", ttl_1d.toText());
    EXPECT_EQ("305419896", ttl_32bit.toText());
    EXPECT_EQ("4294967295", ttl_max.toText());
}

TEST_F(RRTTLTest, toWireBuffer)
{
    ttl_0.toWire(obuffer);
    ttl_1h.toWire(obuffer);
    ttl_1d.toWire(obuffer);
    ttl_32bit.toWire(obuffer);
    ttl_max.toWire(obuffer);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata, sizeof(wiredata));
}

TEST_F(RRTTLTest, toWireRenderer)
{
    ttl_0.toWire(renderer);
    ttl_1h.toWire(renderer);
    ttl_1d.toWire(renderer);
    ttl_32bit.toWire(renderer);
    ttl_max.toWire(renderer);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata, sizeof(wiredata));
}

TEST_F(RRTTLTest, equal)
{
    EXPECT_TRUE(RRTTL("3600") == ttl_1h);
    EXPECT_TRUE(RRTTL("86400").equals(ttl_1d));

    EXPECT_TRUE(ttl_1d != ttl_1h);
    EXPECT_TRUE(ttl_1d.nequals(ttl_max));
}

//
// The following set of tests confirm the result of <=, <, >=, >
// The test logic is simple, and all tests are just straightforward variations
// of the first one.
//
TEST_F(RRTTLTest, leq)
{
    // small <= large is true
    EXPECT_TRUE(ttl_small.leq(ttl_large));
    EXPECT_TRUE(ttl_small <= ttl_large);

    // small <= small is true
    EXPECT_TRUE(ttl_small.leq(ttl_small));
    EXPECT_TRUE(ttl_small <= ttl_small);

    // large <= small is false
    EXPECT_FALSE(ttl_large.leq(ttl_small));
    EXPECT_FALSE(ttl_large <= ttl_small);
}

TEST_F(RRTTLTest, geq)
{
    EXPECT_TRUE(ttl_large.geq(ttl_small));
    EXPECT_TRUE(ttl_large >= ttl_small);

    EXPECT_TRUE(ttl_large.geq(ttl_large));
    EXPECT_TRUE(ttl_large >= ttl_large);

    EXPECT_FALSE(ttl_small.geq(ttl_large));
    EXPECT_FALSE(ttl_small >= ttl_large);
}

TEST_F(RRTTLTest, lthan)
{
    EXPECT_TRUE(ttl_small.lthan(ttl_large));
    EXPECT_TRUE(ttl_small < ttl_large);

    EXPECT_FALSE(ttl_small.lthan(ttl_small));
    EXPECT_FALSE(ttl_small < ttl_small);

    EXPECT_FALSE(ttl_large.lthan(ttl_small));
    EXPECT_FALSE(ttl_large < ttl_small);
}

TEST_F(RRTTLTest, gthan)
{
    EXPECT_TRUE(ttl_large.gthan(ttl_small));
    EXPECT_TRUE(ttl_large > ttl_small);

    EXPECT_FALSE(ttl_large.gthan(ttl_large));
    EXPECT_FALSE(ttl_large > ttl_large);

    EXPECT_FALSE(ttl_small.gthan(ttl_large));
    EXPECT_FALSE(ttl_small > ttl_large);
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RRTTLTest, LeftShiftOperator)
{
    ostringstream oss;
    oss << ttl_1h;
    EXPECT_EQ(ttl_1h.toText(), oss.str());
}
}
