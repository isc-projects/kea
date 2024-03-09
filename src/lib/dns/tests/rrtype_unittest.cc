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
    {"MD", 3, []() -> const RRType& {static const RRType r("MD"); return (r);}},
    {"MF", 4, []() -> const RRType& {static const RRType r("MF"); return (r);}},
    {"CNAME", 5, []() -> const RRType& {static const RRType r("CNAME"); return (r);}},
    {"MB", 7, []() -> const RRType& {static const RRType r("MB"); return (r);}},
    {"MG", 8, []() -> const RRType& {static const RRType r("MG"); return (r);}},
    {"MR", 9, []() -> const RRType& {static const RRType r("MR"); return (r);}},
    {"NULL", 10, []() -> const RRType& {static const RRType r("NULL"); return (r);}},
    {"WKS", 11, []() -> const RRType& {static const RRType r("WKS"); return (r);}},
    {"HINFO", 13, []() -> const RRType& {static const RRType r("HINFO"); return (r);}},
    {"MINFO", 14, []() -> const RRType& {static const RRType r("MINFO"); return (r);}},
    {"MX", 15, []() -> const RRType& {static const RRType r("MX"); return (r);}},
    {"RP", 17, []() -> const RRType& {static const RRType r("RP"); return (r);}},
    {"AFSDB", 18, []() -> const RRType& {static const RRType r("AFSDB"); return (r);}},
    {"X25", 19, []() -> const RRType& {static const RRType r("X25"); return (r);}},
    {"ISDN", 20, []() -> const RRType& {static const RRType r("ISDN"); return (r);}},
    {"RT", 21, []() -> const RRType& {static const RRType r("RT"); return (r);}},
    {"NSAP", 22, []() -> const RRType& {static const RRType r("NSAP"); return (r);}},
    {"NSAP-PTR", 23, []() -> const RRType& {static const RRType r("NSAP-PTR"); return (r);}},
    {"SIG", 24, []() -> const RRType& {static const RRType r("SIG"); return (r);}},
    {"KEY", 25, []() -> const RRType& {static const RRType r("KEY"); return (r);}},
    {"PX", 26, []() -> const RRType& {static const RRType r("PX"); return (r);}},
    {"GPOS", 27, []() -> const RRType& {static const RRType r("GPOS"); return (r);}},
    {"LOC", 29, []() -> const RRType& {static const RRType r("LOC"); return (r);}},
    {"NXT", 30, []() -> const RRType& {static const RRType r("NXT"); return (r);}},
    {"EID", 31, []() -> const RRType& {static const RRType r("EID"); return (r);}},
    {"NIMLOC", 32, []() -> const RRType& {static const RRType r("NIMLOC"); return (r);}},
    {"SRV", 33, []() -> const RRType& {static const RRType r("SRV"); return (r);}},
    {"ATMA", 34, []() -> const RRType& {static const RRType r("ATMA"); return (r);}},
    {"NAPTR", 35, []() -> const RRType& {static const RRType r("NAPTR"); return (r);}},
    {"KX", 36, []() -> const RRType& {static const RRType r("KX"); return (r);}},
    {"CERT", 37, []() -> const RRType& {static const RRType r("CERT"); return (r);}},
    {"A6", 38, []() -> const RRType& {static const RRType r("A6"); return (r);}},
    {"DNAME", 39, []() -> const RRType& {static const RRType r("DNAME"); return (r);}},
    {"SINK", 40, []() -> const RRType& {static const RRType r("SINK"); return (r);}},
    {"APL", 42, []() -> const RRType& {static const RRType r("APL"); return (r);}},
    {"DS", 43, []() -> const RRType& {static const RRType r("DS"); return (r);}},
    {"SSHFP", 44, []() -> const RRType& {static const RRType r("SSHFP"); return (r);}},
    {"IPSECKEY", 45, []() -> const RRType& {static const RRType r("IPSECKEY"); return (r);}},
    {"NSEC", 47, []() -> const RRType& {static const RRType r("NSEC"); return (r);}},
    {"DNSKEY", 48, []() -> const RRType& {static const RRType r("DNSKEY"); return (r);}},
    {"NSEC3", 50, []() -> const RRType& {static const RRType r("NSEC3"); return (r);}},
    {"NSEC3PARAM", 51, []() -> const RRType& {static const RRType r("NSEC3PARAM"); return (r);}},
    {"TLSA", 52, []() -> const RRType& {static const RRType r("TLSA"); return (r);}},
    {"SMIMEA", 53, []() -> const RRType& {static const RRType r("SMIMEA"); return (r);}},
    // Unassigned  54
    {"HIP", 55, []() -> const RRType& {static const RRType r("HIP"); return (r);}},
    {"NINFO", 56, []() -> const RRType& {static const RRType r("NINFO"); return (r);}},
    {"RKEY", 57, []() -> const RRType& {static const RRType r("RKEY"); return (r);}},
    {"TALINK", 58, []() -> const RRType& {static const RRType r("TALINK"); return (r);}},
    {"CDS", 59, []() -> const RRType& {static const RRType r("CDS"); return (r);}},
    {"CDNSKEY", 60, []() -> const RRType& {static const RRType r("CDNSKEY"); return (r);}},
    {"OPENPGPKEY", 61, []() -> const RRType& {static const RRType r("OPENPGPKEY"); return (r);}},
    {"CSYNC", 62 , []() -> const RRType& {static const RRType r("CSYNC"); return (r);}},
    {"ZONEMD", 63, []() -> const RRType& {static const RRType r("ZONEMD"); return (r);}},
    {"SVCB", 64, []() -> const RRType& {static const RRType r("SVCB"); return (r);}},
    {"HTTPS", 65, []() -> const RRType& {static const RRType r("HTTPS"); return (r);}},
    // Unassigned  66-98
    {"SPF", 99, []() -> const RRType& {static const RRType r("SPF"); return (r);}},
    {"UINFO", 100, []() -> const RRType& {static const RRType r("UINFO"); return (r);}},
    {"UID", 101, []() -> const RRType& {static const RRType r("UID"); return (r);}},
    {"GID", 102, []() -> const RRType& {static const RRType r("GID"); return (r);}},
    {"UNSPEC", 103, []() -> const RRType& {static const RRType r("UNSPEC"); return (r);}},
    {"NID", 104, []() -> const RRType& {static const RRType r("NID"); return (r);}},
    {"L32", 105, []() -> const RRType& {static const RRType r("L32"); return (r);}},
    {"L64", 106, []() -> const RRType& {static const RRType r("L64"); return (r);}},
    {"LP", 107, []() -> const RRType& {static const RRType r("LP"); return (r);}},
    {"EUI48", 108, []() -> const RRType& {static const RRType r("EUI48"); return (r);}},
    {"EUI64", 109, []() -> const RRType& {static const RRType r("EUI64"); return (r);}},
    // Unassigned  110-248
    {"IXFR", 251, []() -> const RRType& {static const RRType r("IXFR"); return (r);}},
    {"AXFR",  252, []() -> const RRType& {static const RRType r("AXFR"); return (r);}},
    {"MAILB", 253, []() -> const RRType& {static const RRType r("MAILB"); return (r);}},
    {"MAILA", 254, []() -> const RRType& {static const RRType r("MAILA"); return (r);}},
    {"ANY", 255, []() -> const RRType& {static const RRType r("ANY"); return (r);}}, // also known as "*"
    {"URI", 256, []() -> const RRType& {static const RRType r("URI"); return (r);}},
    {"CAA", 257, []() -> const RRType& {static const RRType r("CAA"); return (r);}},
    {"AVC", 258, []() -> const RRType& {static const RRType r("AVC"); return (r);}},
    {"DOA", 259, []() -> const RRType& {static const RRType r("DOA"); return (r);}},
    {"AMTRELAY", 260, []() -> const RRType& {static const RRType r("AMTRELAY"); return (r);}},
    {"RESINFO", 261, []() -> const RRType& {static const RRType r("RESINFO"); return (r);}},
    // Unassigned  262-32767
    {"TA", 32768, []() -> const RRType& {static const RRType r("TA"); return (r);}},
    {"DLV", 32769, []() -> const RRType& {static const RRType r("DLV"); return (r);}},
    {0, 0, 0}
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
