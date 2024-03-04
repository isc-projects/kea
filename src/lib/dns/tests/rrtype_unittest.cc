// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrtype.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using isc::util::unittests::matchWireData;

namespace {
class RRTypeTest : public ::testing::Test {
protected:
    RRTypeTest() : obuffer(0) {}

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
RRTypeTest::rrtypeFactoryFromWire(const char* datafile) {
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());

    return (RRType(buffer));
}

TEST_F(RRTypeTest, fromText) {
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

TEST_F(RRTypeTest, fromWire) {
    EXPECT_EQ(0x1234,
              rrtypeFactoryFromWire("rrcode16_fromWire1").getCode());
    EXPECT_THROW(rrtypeFactoryFromWire("rrcode16_fromWire2"), IncompleteRRType);
}

// from string, lower case
TEST_F(RRTypeTest, caseConstruct) {
    EXPECT_EQ("A", RRType("a").toText());
    EXPECT_EQ("NS", RRType("ns").toText());
    EXPECT_EQ("TYPE65535", RRType("type65535").toText());
}

TEST_F(RRTypeTest, toText) {
    EXPECT_EQ("A", RRType(1).toText());
    EXPECT_EQ("TYPE65000", RRType(65000).toText());
}

TEST_F(RRTypeTest, toWireBuffer) {
    rrtype_1.toWire(obuffer);
    rrtype_0x80.toWire(obuffer);
    rrtype_0x800.toWire(obuffer);
    rrtype_0x8000.toWire(obuffer);
    rrtype_max.toWire(obuffer);

    matchWireData(wiredata, sizeof(wiredata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(RRTypeTest, toWireRenderer) {
    rrtype_1.toWire(renderer);
    rrtype_0x80.toWire(renderer);
    rrtype_0x800.toWire(renderer);
    rrtype_0x8000.toWire(renderer);
    rrtype_max.toWire(renderer);

    matchWireData(wiredata, sizeof(wiredata),
                  renderer.getData(), renderer.getLength());
}

TEST_F(RRTypeTest, wellKnownTypes) {
    EXPECT_EQ(1, RRType::A().getCode());
    EXPECT_EQ("A", RRType::A().toText());
}

TEST_F(RRTypeTest, compare) {
    EXPECT_TRUE(RRType(1) == RRType("A"));
    EXPECT_TRUE(RRType(1).equals(RRType("A")));
    EXPECT_TRUE(RRType(0) != RRType("A"));
    EXPECT_TRUE(RRType(0).nequals(RRType("A")));

    EXPECT_TRUE(RRType("A") < RRType("NS"));
    EXPECT_TRUE(RRType(100) < RRType(65535));
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RRTypeTest, LeftShiftOperator) {
    ostringstream oss;
    oss << RRType::A();
    EXPECT_EQ(RRType::A().toText(), oss.str());
}

// Below, we'll check definitions for all well-known RR types; whether they
// are defined and have the correct parameter values.  Test data are generated
// from the list available at:
// http://www.iana.org/assignments/dns-parameters/dns-parameters.xml
struct TypeParam {
    const char* const txt;      // "A", "AAAA", "NS", etc
    const uint16_t code;        // 1, 28, 2, etc
    const RRType& (*obj)();     // RRType::A(), etc
} known_types[] = {
    {"A", 1, RRType::A}, {"NS", 2, RRType::NS},
    {"SOA", 6, RRType::SOA}, {"PTR", 12, RRType::PTR},
    {"TXT", 16, RRType::TXT}, {"AAAA", 28, RRType::AAAA},
    {"OPT", 41, RRType::OPT}, {"RRSIG", 46, RRType::RRSIG},
    {"DHCID", 49, RRType::DHCID}, {"TKEY", 249, RRType::TKEY},
    {"TSIG", 250, RRType::TSIG}, {"ANY", 255, RRType::ANY},
    {NULL, 0, NULL}
};

TEST(RRTypeConstTest, wellKnowns) {
    for (int i = 0; known_types[i].txt; ++i) {
        SCOPED_TRACE("Checking well known RRType: " +
                     string(known_types[i].txt));
        EXPECT_EQ(known_types[i].code, RRType(known_types[i].txt).getCode());
        EXPECT_EQ(known_types[i].code,
                  (*known_types[i].obj)().getCode());
    }
}
}
