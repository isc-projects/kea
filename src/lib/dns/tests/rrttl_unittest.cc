// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrttl.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>
#include <util/unittests/test_exceptions.h>

#include <boost/scoped_ptr.hpp>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using boost::scoped_ptr;
using isc::util::unittests::matchWireData;

namespace {
class RRTTLTest : public ::testing::Test {
protected:
    RRTTLTest() : obuffer(0) {}

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
RRTTLTest::rrttlFactoryFromWire(const char* datafile) {
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());

    return (RRTTL(buffer));
}

TEST_F(RRTTLTest, getValue) {
    EXPECT_EQ(0, ttl_0.getValue());
    EXPECT_EQ(3600, ttl_1h.getValue());
    EXPECT_EQ(86400, ttl_1d.getValue());
    EXPECT_EQ(0x12345678, ttl_32bit.getValue());
    EXPECT_EQ(0xffffffff, ttl_max.getValue());
}

TEST_F(RRTTLTest, copyConstruct) {
    const RRTTL ttl1(3600);
    const RRTTL ttl2(ttl1);
    EXPECT_EQ(ttl1.getValue(), ttl2.getValue());
}

TEST_F(RRTTLTest, fromText) {
    // Border cases
    EXPECT_EQ(0, RRTTL("0").getValue());
    EXPECT_EQ(4294967295U, RRTTL("4294967295").getValue());

    // Invalid cases
    // must be decimal
    EXPECT_THROW_WITH(RRTTL("0xdeadbeef"), InvalidRRTTL,
                      "Unknown unit used: x in: 0xdeadbeef");
    // must be positive
    EXPECT_THROW_WITH(RRTTL("-1"), InvalidRRTTL, "TTL out of range: -1");
    // must be integer
    EXPECT_THROW_WITH(RRTTL("1.1"), InvalidRRTTL, "invalid TTL: 1.1");
    // must be 32-bit
    EXPECT_THROW_WITH(RRTTL("4294967296"), InvalidRRTTL,
                      "TTL out of range: 4294967296");
}

TEST_F(RRTTLTest, createFromText) {
    // It returns an actual RRTTL iff the given text is recognized as a
    // valid RR TTL.
    scoped_ptr<RRTTL> good_ttl(RRTTL::createFromText("3600"));
    EXPECT_TRUE(good_ttl);
    EXPECT_EQ(RRTTL(3600), *good_ttl);

    scoped_ptr<RRTTL> bad_ttl(RRTTL::createFromText("bad"));
    EXPECT_FALSE(bad_ttl);
}

void
checkUnit(unsigned multiply, char suffix) {
    SCOPED_TRACE(string("Unit check with suffix ") + suffix);
    const uint32_t value = 10 * multiply;
    const string num = "10";
    // Check both lower and upper version of the suffix
    EXPECT_EQ(value,
              RRTTL(num + static_cast<char>(tolower(suffix))).getValue());
    EXPECT_EQ(value,
              RRTTL(num + static_cast<char>(toupper(suffix))).getValue());
}

// Check parsing the unit form (1D, etc)
TEST_F(RRTTLTest, fromTextUnit) {
    // Check each of the units separately
    checkUnit(1, 'S');
    checkUnit(60, 'M');
    checkUnit(60 * 60, 'H');
    checkUnit(24 * 60 * 60, 'D');
    checkUnit(7 * 24 * 60 * 60, 'W');

    // Some border cases (with units)
    EXPECT_EQ(4294967295U, RRTTL("4294967295S").getValue());
    EXPECT_EQ(0, RRTTL("0W0D0H0M0S").getValue());
    EXPECT_EQ(4294967295U, RRTTL("1193046H1695S").getValue());
    // Leading zeroes are accepted
    EXPECT_EQ(4294967295U, RRTTL("0000000000000004294967295S").getValue());

    // Now some compound ones. We allow any order (it would be much work to
    // check the order anyway).
    EXPECT_EQ(60 * 60 + 3, RRTTL("1H3S").getValue());

    // Awkward, but allowed case - the same unit used twice.
    EXPECT_EQ(20 * 3600, RRTTL("12H8H").getValue());

    // Negative number in part of the expression, but the total is positive.
    // Rejected.
    EXPECT_THROW_WITH(RRTTL("-1S1H"), InvalidRRTTL,
                      "Part of TTL out of range: -1S1H");

    // Some things out of range in the ttl, but it wraps to number in range
    // in int64_t. Should still not get fooled and reject it.

    // First part out of range
    EXPECT_THROW_WITH(RRTTL("9223372036854775807S9223372036854775807S2S"),
                      InvalidRRTTL, "Part of TTL out of range: "
                      "9223372036854775807S9223372036854775807S2S");
    // Second part out of range, but it immediately wraps (2S+2^64-2S)
    EXPECT_THROW_WITH(RRTTL("2S18446744073709551614S"), InvalidRRTTL,
                      "Part of TTL out of range: 2S18446744073709551614S");
    // The whole thing wraps right away (2^64S)
    EXPECT_THROW_WITH(RRTTL("18446744073709551616S"), InvalidRRTTL,
                      "invalid TTL: 18446744073709551616S");
    // Second part out of range, and will become negative with the unit,
    EXPECT_THROW_WITH(RRTTL("256S307445734561825856M"), InvalidRRTTL,
                      "Part of TTL out of range: 256S307445734561825856M");

    // Missing before unit.
    EXPECT_THROW_WITH(RRTTL("W5H"), InvalidRRTTL,
                      "Missing number in TTL: W5H");
    EXPECT_THROW_WITH(RRTTL("5hW"), InvalidRRTTL,
                      "Missing number in TTL: 5hW");

    // Empty string is not allowed
    EXPECT_THROW_WITH(RRTTL(""), InvalidRRTTL, "Empty TTL string");
    // Missing the last unit is not allowed
    EXPECT_THROW_WITH(RRTTL("3D5"), InvalidRRTTL,
                      "Missing the last unit: 3D5");

    // There are some wrong units
    EXPECT_THROW_WITH(RRTTL("13X"), InvalidRRTTL,
                      "Unknown unit used: X in: 13X");
    EXPECT_THROW_WITH(RRTTL("3D5F"), InvalidRRTTL,
                      "Unknown unit used: F in: 3D5F");
}

TEST_F(RRTTLTest, fromWire) {
    EXPECT_EQ(0x12345678,
              rrttlFactoryFromWire("rrcode32_fromWire1").getValue());
    EXPECT_THROW_WITH(rrttlFactoryFromWire("rrcode32_fromWire2"),
                      IncompleteRRTTL, "incomplete wire-format TTL value");
}

TEST_F(RRTTLTest, toText) {
    EXPECT_EQ("0", ttl_0.toText());
    EXPECT_EQ("3600", ttl_1h.toText());
    EXPECT_EQ("86400", ttl_1d.toText());
    EXPECT_EQ("305419896", ttl_32bit.toText());
    EXPECT_EQ("4294967295", ttl_max.toText());
}

TEST_F(RRTTLTest, toWireBuffer) {
    ttl_0.toWire(obuffer);
    ttl_1h.toWire(obuffer);
    ttl_1d.toWire(obuffer);
    ttl_32bit.toWire(obuffer);
    ttl_max.toWire(obuffer);

    matchWireData(wiredata, sizeof(wiredata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(RRTTLTest, toWireRenderer) {
    ttl_0.toWire(renderer);
    ttl_1h.toWire(renderer);
    ttl_1d.toWire(renderer);
    ttl_32bit.toWire(renderer);
    ttl_max.toWire(renderer);

    matchWireData(wiredata, sizeof(wiredata),
                  renderer.getData(), renderer.getLength());
}

TEST_F(RRTTLTest, equal) {
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
TEST_F(RRTTLTest, leq) {
    // small <= large is true
    EXPECT_TRUE(ttl_small.leq(ttl_large));
    EXPECT_TRUE(ttl_small <= ttl_large);

    // small <= small is true
    EXPECT_TRUE(ttl_small.leq(ttl_small));
    EXPECT_LE(ttl_small, ttl_small);

    // large <= small is false
    EXPECT_FALSE(ttl_large.leq(ttl_small));
    EXPECT_FALSE(ttl_large <= ttl_small);
}

TEST_F(RRTTLTest, geq) {
    EXPECT_TRUE(ttl_large.geq(ttl_small));
    EXPECT_TRUE(ttl_large >= ttl_small);

    EXPECT_TRUE(ttl_large.geq(ttl_large));
    EXPECT_GE(ttl_large, ttl_large);

    EXPECT_FALSE(ttl_small.geq(ttl_large));
    EXPECT_FALSE(ttl_small >= ttl_large);
}

TEST_F(RRTTLTest, lthan) {
    EXPECT_TRUE(ttl_small.lthan(ttl_large));
    EXPECT_TRUE(ttl_small < ttl_large);

    EXPECT_FALSE(ttl_small.lthan(ttl_small));
    // cppcheck-suppress duplicateExpression
    EXPECT_FALSE(ttl_small < ttl_small);

    EXPECT_FALSE(ttl_large.lthan(ttl_small));
    EXPECT_FALSE(ttl_large < ttl_small);
}

TEST_F(RRTTLTest, gthan) {
    EXPECT_TRUE(ttl_large.gthan(ttl_small));
    EXPECT_TRUE(ttl_large > ttl_small);

    EXPECT_FALSE(ttl_large.gthan(ttl_large));
    // cppcheck-suppress duplicateExpression
    EXPECT_FALSE(ttl_large > ttl_large);

    EXPECT_FALSE(ttl_small.gthan(ttl_large));
    EXPECT_FALSE(ttl_small > ttl_large);
}

TEST_F(RRTTLTest, maxTTL) {
    EXPECT_EQ((1u << 31) - 1, RRTTL::MAX_TTL().getValue());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RRTTLTest, LeftShiftOperator) {
    ostringstream oss;
    oss << ttl_1h;
    EXPECT_EQ(ttl_1h.toText(), oss.str());
}
}
