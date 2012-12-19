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

#include <gtest/gtest.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>

#include <dns/tests/unittest_util.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;

namespace {
class RRClassTest : public ::testing::Test {
protected:
    RRClassTest() : obuffer(0) {}

    OutputBuffer obuffer;
    MessageRenderer renderer;

    static RRClass rrclassFactoryFromWire(const char* datafile);
    static const RRClass rrclass_1, rrclass_0x80, rrclass_0x800,
        rrclass_0x8000, rrclass_max;
    static const uint8_t wiredata[];
};

const RRClass RRClassTest::rrclass_1(1);
const RRClass RRClassTest::rrclass_0x80(0x80);
const RRClass RRClassTest::rrclass_0x800(0x800);
const RRClass RRClassTest::rrclass_0x8000(0x8000);
const RRClass RRClassTest::rrclass_max(0xffff);
// This is wire-format data for the above sample RRClasss rendered in the
// appearing order.
const uint8_t RRClassTest::wiredata[] = { 0x00, 0x01, 0x00, 0x80, 0x08,
                                          0x00, 0x80, 0x00, 0xff, 0xff };

RRClass
RRClassTest::rrclassFactoryFromWire(const char* datafile) {
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());

    return (RRClass(buffer));
}

TEST_F(RRClassTest, fromTextConstructor) {
    EXPECT_EQ("IN", RRClass("IN").toText());
    EXPECT_EQ("CH", RRClass("CH").toText());

    EXPECT_EQ("CLASS65535", RRClass("CLASS65535").toText());

    // some uncommon cases: see the corresponding RRType tests.
    EXPECT_EQ(53, RRClass("CLASS00053").getCode());
    EXPECT_THROW(RRClass("CLASS000053"), InvalidRRClass);

    // bogus CLASSnnn representations: should trigger an exception
    EXPECT_THROW(RRClass("CLASS"), InvalidRRClass);
    EXPECT_THROW(RRClass("CLASS-1"), InvalidRRClass);
    EXPECT_THROW(RRClass("CLASSxxx"), InvalidRRClass);
    EXPECT_THROW(RRClass("CLASS65536"), InvalidRRClass);
    EXPECT_THROW(RRClass("CLASS6500x"), InvalidRRClass);
    EXPECT_THROW(RRClass("CLASS65000 "), InvalidRRClass);
}

TEST_F(RRClassTest, fromWire) {
    EXPECT_EQ(0x1234,
              rrclassFactoryFromWire("rrcode16_fromWire1").getCode());
    EXPECT_THROW(rrclassFactoryFromWire("rrcode16_fromWire2"),
                 IncompleteRRClass);
}

TEST_F(RRClassTest, caseConstruct) {
    EXPECT_EQ("IN", RRClass("in").toText());
    EXPECT_EQ("CH", RRClass("ch").toText());
    EXPECT_EQ("CLASS65535", RRClass("class65535").toText());
}

TEST_F(RRClassTest, toText) {
    EXPECT_EQ("IN", RRClass(1).toText());
    EXPECT_EQ("CLASS65000", RRClass(65000).toText());
}

TEST_F(RRClassTest, createFromText) {
    MaybeRRClass rrclass("IN");
    EXPECT_TRUE(rrclass);
    EXPECT_EQ("IN", rrclass->toText());
    EXPECT_TRUE(RRClass::createFromText("CH"));
    EXPECT_FALSE(RRClass::createFromText("ZZ"));
}

TEST_F(RRClassTest, toWireBuffer) {
    rrclass_1.toWire(obuffer);
    rrclass_0x80.toWire(obuffer);
    rrclass_0x800.toWire(obuffer);
    rrclass_0x8000.toWire(obuffer);
    rrclass_max.toWire(obuffer);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata, sizeof(wiredata));
}

TEST_F(RRClassTest, toWireRenderer) {
    rrclass_1.toWire(renderer);
    rrclass_0x80.toWire(renderer);
    rrclass_0x800.toWire(renderer);
    rrclass_0x8000.toWire(renderer);
    rrclass_max.toWire(renderer);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata, sizeof(wiredata));
}

TEST_F(RRClassTest, wellKnownClasss) {
    EXPECT_EQ(1, RRClass::IN().getCode());
    EXPECT_EQ("IN", RRClass::IN().toText());
}

TEST_F(RRClassTest, compare) {
    EXPECT_TRUE(RRClass(1) == RRClass("IN"));
    EXPECT_TRUE(RRClass(1).equals(RRClass("IN")));
    EXPECT_TRUE(RRClass(0).nequals(RRClass("IN")));

    EXPECT_TRUE(RRClass("IN") < RRClass("CH"));
    EXPECT_TRUE(RRClass(100) < RRClass(65535));
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RRClassTest, LeftShiftOperator) {
    ostringstream oss;
    oss << RRClass::IN();
    EXPECT_EQ(RRClass::IN().toText(), oss.str());
}
}
