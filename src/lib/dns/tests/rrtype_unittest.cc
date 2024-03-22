// Copyright (C) 2010-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrparamregistry.h>
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
struct WellKnownTypeParam {
    const char* const txt;      // "A", "AAAA", "NS", etc
    const uint16_t code;        // 1, 28, 2, etc
    const RRType& (*obj)();     // RRType::A(), etc
} well_known_types[] = {
    {"A", 1, RRType::A},
    {"NS", 2, RRType::NS},
    {"SOA", 6, RRType::SOA},
    {"PTR", 12, RRType::PTR},
    {"TXT", 16, RRType::TXT},
    {"AAAA", 28, RRType::AAAA},
    {"OPT", 41, RRType::OPT},
    {"RRSIG", 46, RRType::RRSIG},
    {"DHCID", 49, RRType::DHCID},
    {"TKEY", 249, RRType::TKEY},
    {"TSIG", 250, RRType::TSIG},
    {"ANY", 255, RRType::ANY},
    {0, 0, 0}
};

TEST(RRTypeConstTest, wellKnowns) {
    for (size_t i = 0; well_known_types[i].txt; ++i) {
        SCOPED_TRACE("Checking well known RRType: " +
                     string(well_known_types[i].txt));
        EXPECT_EQ(well_known_types[i].code,
                  RRType(well_known_types[i].txt).getCode());
        EXPECT_EQ(well_known_types[i].code,
                  (*well_known_types[i].obj)().getCode());
    }
}

// Below, we'll check definitions for all registered RR types.
struct RegisteredTypeParam {
    const char* const txt;      // "A", "AAAA", "NS", etc
    const uint16_t code;        // 1, 28, 2, etc
} registered_types[] = {
    {"A", 1},
    {"NS", 2},
    {"MD", 3},
    {"MF", 4},
    {"CNAME", 5},
    {"SOA", 6},
    {"MB", 7},
    {"MG", 8},
    {"MR", 9},
    {"NULL", 10},
    {"WKS", 11},
    {"PTR", 12},
    {"HINFO", 13},
    {"MINFO", 14},
    {"MX", 15},
    {"TXT", 16},
    {"RP", 17},
    {"AFSDB", 18},
    {"X25", 19},
    {"ISDN", 20},
    {"RT", 21},
    {"NSAP", 22},
    {"NSAP-PTR", 23},
    {"SIG", 24},
    {"KEY", 25},
    {"PX", 26},
    {"GPOS", 27},
    {"AAAA", 28},
    {"LOC", 29},
    {"NXT", 30},
    {"EID", 31},
    {"NIMLOC", 32},
    {"SRV", 33},
    {"ATMA", 34},
    {"NAPTR", 35},
    {"KX", 36},
    {"CERT", 37},
    {"A6", 38},
    {"DNAME", 39},
    {"SINK", 40},
    {"OPT", 41},
    {"APL", 42},
    {"DS", 43},
    {"SSHFP", 44},
    {"IPSECKEY", 45},
    {"RRSIG", 46},
    {"NSEC", 47},
    {"DNSKEY", 48},
    {"DHCID", 49},
    {"NSEC3", 50},
    {"NSEC3PARAM", 51},
    {"TLSA", 52},
    {"SMIMEA", 53},
    {"HIP", 55},
    {"NINFO", 56},
    {"RKEY", 57},
    {"TALINK", 58},
    {"CDS", 59},
    {"CDNSKEY", 60},
    {"OPENPGPKEY", 61},
    {"CSYNC", 62},
    {"ZONEMD", 63},
    {"SVCB", 64},
    {"HTTPS", 65},
    {"SPF", 99},
    {"UINFO", 100},
    {"UID", 101},
    {"GID", 102},
    {"UNSPEC", 103},
    {"NID", 104},
    {"L32", 105},
    {"L64", 106},
    {"LP", 107},
    {"EUI48", 108},
    {"EUI64", 109},
    {"TKEY", 249},
    {"TSIG", 250},
    {"IXFR", 251},
    {"AXFR", 252},
    {"MAILB", 253},
    {"MAILA", 254},
    {"ANY", 255},
    {"URI", 256},
    {"CAA", 257},
    {"AVC", 258},
    {"DOA", 259},
    {"AMTRELAY", 260},
    {"RESINFO", 261},
    {"TA", 32768},
    {"DLV", 32769},
    {0, 0}
};

TEST(RRTypeConstTest, registered) {
    for (size_t i = 0; registered_types[i].txt; ++i) {
        SCOPED_TRACE("Checking registered RRType: " +
                     string(registered_types[i].txt));
        uint16_t code = 0;
        EXPECT_NO_THROW(RRParamRegistry::getRegistry().textToTypeCode(registered_types[i].txt, code));
        EXPECT_EQ(code, registered_types[i].code);
        string txt;
        EXPECT_NO_THROW(txt = RRParamRegistry::getRegistry().codeToTypeText(registered_types[i].code));
        EXPECT_EQ(txt, registered_types[i].txt);
    }
}

}
