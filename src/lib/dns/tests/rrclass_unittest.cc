// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>

#include <boost/scoped_ptr.hpp>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using boost::scoped_ptr;
using isc::util::unittests::matchWireData;

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
    scoped_ptr<RRClass> chclass(RRClass::createFromText("CH"));
    EXPECT_TRUE(chclass);
    EXPECT_EQ("CH", chclass->toText());

    scoped_ptr<RRClass> zzclass(RRClass::createFromText("ZZ"));
    EXPECT_FALSE(zzclass);
}

TEST_F(RRClassTest, toWireBuffer) {
    rrclass_1.toWire(obuffer);
    rrclass_0x80.toWire(obuffer);
    rrclass_0x800.toWire(obuffer);
    rrclass_0x8000.toWire(obuffer);
    rrclass_max.toWire(obuffer);

    matchWireData(wiredata, sizeof (wiredata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(RRClassTest, toWireRenderer) {
    rrclass_1.toWire(renderer);
    rrclass_0x80.toWire(renderer);
    rrclass_0x800.toWire(renderer);
    rrclass_0x8000.toWire(renderer);
    rrclass_max.toWire(renderer);

    matchWireData(wiredata, sizeof (wiredata),
                  renderer.getData(), renderer.getLength());
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

// Below, we'll check definitions for all well-known RR classes; whether they
// are defined and have the correct parameter values.  Test data are generated
// from the list available at:
// http://www.iana.org/assignments/dns-parameters/dns-parameters.xml
struct ClassParam {
    const char* const txt;      // "IN", "CH", etc
    const uint16_t code;        // 1, 3,
    const RRClass& (*obj)();     // RRClass::IN(), etc
} known_classes[] = {
    {"IN", 1, RRClass::IN}, {"CH", 3, RRClass::CH}, {"HS", 4, RRClass::HS},
    {"NONE", 254, RRClass::NONE}, {"ANY", 255, RRClass::ANY},
    {NULL, 0, NULL}
};

TEST(RRClassConstTest, wellKnowns) {
    for (int i = 0; known_classes[i].txt; ++i) {
        SCOPED_TRACE("Checking well known RRClass: " +
                     string(known_classes[i].txt));
        EXPECT_EQ(known_classes[i].code,
                  RRClass(known_classes[i].txt).getCode());
        EXPECT_EQ(known_classes[i].code,
                  (*known_classes[i].obj)().getCode());
    }
}
}
