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

// $Id: rrtype_unittest.cc 476 2010-01-19 00:29:28Z jinmei $

#include <vector>

#include "buffer.h"
#include "messagerenderer.h"
#include "rdata.h"
#include "rrclass.h"
#include "rrtype.h"

#include <gtest/gtest.h>

#include "unittest_util.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class RdataTest : public ::testing::Test {
protected:
    RdataTest() : obuffer(0), renderer(obuffer) {}
    static RdataPtr rdataFactoryFromFile(const RRType& rrtype,
                                         const RRClass& rrclass,
                                         const char* datafile,
                                         size_t position = 0);
    OutputBuffer obuffer;
    MessageRenderer renderer;
    static const in::A rdata_in_a;
    static const in::AAAA rdata_in_aaaa;
    static const uint8_t wiredata_in_a[];
    static const uint8_t wiredata_in_aaaa[];
    static const uint8_t wiredata_ns[];
    static const uint8_t wiredata_ns2[];
    static const uint8_t wiredata_txt[];
    static const generic::NS rdata_ns;
    static const generic::NS rdata_ns2;
    static const generic::SOA rdata_soa;
    static const generic::MX rdata_mx;
    static const generic::TXT rdata_txt;
    static const generic::TXT rdata_txt_quoated;
};

const in::A RdataTest::rdata_in_a("192.0.2.1");
const in::AAAA RdataTest::rdata_in_aaaa("2001:db8::1234");
const generic::NS RdataTest::rdata_ns("ns.example.com");
const generic::NS RdataTest::rdata_ns2("ns2.example.com");
const generic::SOA RdataTest::rdata_soa(Name("ns.example.com"),
                                        Name("root.example.com"),
                                        2010012601, 3600, 300, 3600000, 1200);
const generic::MX RdataTest::rdata_mx(10, Name("mx.example.com"));
const generic::TXT RdataTest::rdata_txt("Test String");
const generic::TXT RdataTest::rdata_txt_quoated("\"Test String\"");

const uint8_t RdataTest::wiredata_in_a[] = { 192, 0, 2, 1 };
const uint8_t RdataTest::wiredata_in_aaaa[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x12, 0x34 };
const uint8_t RdataTest::wiredata_ns[] = {
    0x02, 0x6e, 0x73, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00 };
const uint8_t RdataTest::wiredata_ns2[] = {
    // first name: ns.example.com.
    0x02, 0x6e, 0x73, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00,
    // second name: ns2.example.com.  all labels except the first should be
    // compressed.
    0x03, 0x6e, 0x73, 0x32, 0xc0, 0x03 };
const uint8_t RdataTest::wiredata_txt[] = {
    sizeof("Test String") - 1,
    'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
};

RdataPtr
RdataTest::rdataFactoryFromFile(const RRType& rrtype, const RRClass& rrclass,
                                const char* datafile, size_t position)
{
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    buffer.setPosition(position);

    uint16_t rdlen = buffer.readUint16();
    return (createRdata(rrtype, rrclass, buffer, rdlen));
}

TEST_F(RdataTest, createFromText_IN_A)
{
    rdata_in_a.compare(in::A(string("192.0.2.1")));
    //EXPECT_EQ(0, rdata_in_a.compare(in::A("192.0.2.1")));
    // should reject an abbreviated form of IPv4 address
    EXPECT_THROW(in::A("10.1"), InvalidRdataText);
    // or an IPv6 address
    EXPECT_THROW(in::A("2001:db8::1234"), InvalidRdataText);
    // or any meaningless text as an IP address
    EXPECT_THROW(in::A("xxx"), InvalidRdataText);
}

TEST_F(RdataTest, createFromWire_IN_A)
{
    // Valid data
    EXPECT_EQ(0, rdata_in_a.compare(
                  *rdataFactoryFromFile(RRType("A"), RRClass("IN"),
                                        "testdata/rdata_in_a_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType("A"), RRClass("IN"),
                                      "testdata/rdata_in_a_fromWire", 6),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType("A"), RRClass("IN"),
                                      "testdata/rdata_in_a_fromWire", 12),
                 InvalidRdataLength);
    // buffer too short.  the error should be detected in buffer read
    EXPECT_THROW(rdataFactoryFromFile(RRType("A"), RRClass("IN"),
                                      "testdata/rdata_in_a_fromWire", 19),
                 InvalidBufferPosition);
}

TEST_F(RdataTest, toWireBuffer_IN_A)
{
    rdata_in_a.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_in_a, sizeof(wiredata_in_a));
}

TEST_F(RdataTest, toWireRenderer_IN_A)
{
    rdata_in_a.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_in_a, sizeof(wiredata_in_a));
}

TEST_F(RdataTest, toText_IN_A)
{
    EXPECT_EQ("192.0.2.1", rdata_in_a.toText());
    string longaddr("255.255.255.255"); // this shouldn't make the code crash
    EXPECT_EQ(longaddr, in::A(longaddr).toText());
}

TEST_F(RdataTest, compare_IN_A)
{
    in::A small1("1.1.1.1");
    in::A small2("1.2.3.4");
    in::A large1("255.255.255.255");
    in::A large2("4.3.2.1");

    // trivial case: self equivalence
    EXPECT_EQ(0, small1.compare(small1));

    // confirm these are compared as unsigned values
    EXPECT_GT(0, small1.compare(large1));
    EXPECT_LT(0, large1.compare(small1));

    // confirm these are compared in network byte order
    EXPECT_GT(0, small2.compare(large2));
    EXPECT_LT(0, large2.compare(small2));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_in_a.compare(rdata_ns), bad_cast); 
}

TEST_F(RdataTest, createFromText_IN_AAAA)
{
    rdata_in_aaaa.compare(in::AAAA(string("2001:db8::1234")));
    EXPECT_THROW(in::AAAA("192.0.2.1"), InvalidRdataText);
    EXPECT_THROW(in::AAAA("xxx"), InvalidRdataText);
}

TEST_F(RdataTest, createFromWire_IN_AAAA)
{
    // Valid data
    EXPECT_EQ(0, rdata_in_aaaa.compare(
                  *rdataFactoryFromFile(RRType("AAAA"), RRClass("IN"),
                                        "testdata/rdata_in_aaaa_fromWire")));
    //TBD: more tests
}

TEST_F(RdataTest, toWireBuffer_IN_AAAA)
{
    rdata_in_aaaa.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_in_aaaa, sizeof(wiredata_in_aaaa));
}

TEST_F(RdataTest, toWireRenderer_IN_AAAA)
{
    rdata_in_aaaa.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_in_aaaa, sizeof(wiredata_in_aaaa));
}

TEST_F(RdataTest, toText_IN_AAAA)
{
    EXPECT_EQ("2001:db8::1234", rdata_in_aaaa.toText());
}

TEST_F(RdataTest, compare_IN_AAAA)
{
    in::AAAA small1("::1");
    in::AAAA small2("1:2:3:4:5:6:7:8");
    in::AAAA large1("ffff::");
    in::AAAA large2("8:7:6:5:4:3:2:1");

    // trivial case: self equivalence
    EXPECT_EQ(0, small1.compare(small1));

    // confirm these are compared as unsigned values
    EXPECT_GT(0, small1.compare(large1));
    EXPECT_LT(0, large1.compare(small1));

    // confirm these are compared in network byte order
    EXPECT_GT(0, small2.compare(large2));
    EXPECT_LT(0, large2.compare(small2));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_in_aaaa.compare(rdata_ns), bad_cast); 
}

TEST_F(RdataTest, createFromText_NS)
{
    EXPECT_EQ(0, rdata_ns.compare(generic::NS("ns.example.com")));
    // explicitly add a trailing dot.  should be the same RDATA.
    EXPECT_EQ(0, rdata_ns.compare(generic::NS("ns.example.com.")));
    // should be case sensitive.
    EXPECT_EQ(0, rdata_ns.compare(generic::NS("NS.EXAMPLE.COM")));
}

TEST_F(RdataTest, createFromWire_NS)
{
    EXPECT_EQ(0, rdata_ns.compare(
                  *rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                        "testdata/rdata_ns_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                      "testdata/rdata_ns_fromWire", 18),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                      "testdata/rdata_ns_fromWire", 36),
                 InvalidRdataLength);
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                      "testdata/rdata_ns_fromWire", 71),
                 IncompleteName);

    EXPECT_EQ(0, generic::NS("ns2.example.com").compare(
                  *rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                        "testdata/rdata_ns_fromWire", 55)));
    EXPECT_THROW(*rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                       "testdata/rdata_ns_fromWire", 63),
                 InvalidRdataLength);
}

TEST_F(RdataTest, toWireBuffer_NS)
{
    rdata_ns.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_ns, sizeof(wiredata_ns));
}

TEST_F(RdataTest, toWireRenderer_NS)
{
    rdata_ns.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_ns, sizeof(wiredata_ns));
    rdata_ns2.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_ns2, sizeof(wiredata_ns2));
}

TEST_F(RdataTest, toText_NS)
{
    EXPECT_EQ("ns.example.com.", rdata_ns.toText());
}

TEST_F(RdataTest, compare_NS)
{
    generic::NS small("a.example");
    generic::NS large("example");
    EXPECT_EQ(true, Name("a.example") > Name("example"));
    EXPECT_GT(0, small.compare(large));
}

TEST_F(RdataTest, getNSName)
{
    EXPECT_EQ(Name("ns.example.com"), rdata_ns.getNSName());
}

TEST_F(RdataTest, createFromText_SOA)
{
    //TBD
}

TEST_F(RdataTest, createFromWire_SOA)
{
    EXPECT_EQ(0, rdata_soa.compare(
                  *rdataFactoryFromFile(RRType("SOA"), RRClass("IN"),
                                        "testdata/rdata_soa_fromWire")));
    // TBD: more tests
}

TEST_F(RdataTest, toWireRenderer_SOA)
{
    renderer.skip(2);
    rdata_soa.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("testdata/rdata_soa_fromWire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[0] + 2, data.size() - 2);
}

TEST_F(RdataTest, toText_SOA)
{
    EXPECT_EQ("ns.example.com. root.example.com. "
              "2010012601 3600 300 3600000 1200", rdata_soa.toText());
}

TEST_F(RdataTest, createFromText_MX)
{
    //TBD
}

TEST_F(RdataTest, createFromWire_MX)
{
    EXPECT_EQ(0, rdata_mx.compare(
                  *rdataFactoryFromFile(RRType("MX"), RRClass("IN"),
                                        "testdata/rdata_mx_fromWire")));
    // TBD: more tests
}

TEST_F(RdataTest, toWireRenderer_MX)
{
    renderer.writeName(Name("example.com"));
    rdata_mx.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("testdata/rdata_mx_toWire1", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, obuffer.getData(),
                        obuffer.getLength(), &data[0], data.size());
}

TEST_F(RdataTest, toText_MX)
{
    EXPECT_EQ("10 mx.example.com.", rdata_mx.toText());
}

TEST_F(RdataTest, compare_IN_MX)
{
    generic::MX small1(1, Name("mx.example.com"));
    generic::MX small2(10, Name("mx.example.com"));
    generic::MX large1(65535, Name("mx.example.com"));
    generic::MX large2(256, Name("mx.example.com"));

    // trivial case: self equivalence
    EXPECT_EQ(0, small1.compare(small1));

    // confirm these are compared as unsigned values
    EXPECT_GT(0, small1.compare(large1));
    EXPECT_LT(0, large1.compare(small1));

    // confirm these are compared in network byte order
    EXPECT_GT(0, small2.compare(large2));
    EXPECT_LT(0, large2.compare(small2));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_mx.compare(rdata_ns), bad_cast); 
}

TEST_F(RdataTest, createFromText_TXT)
{
    EXPECT_EQ(0, rdata_txt.compare(rdata_txt_quoated));
}

TEST_F(RdataTest, createFromWire_TXT)
{
    EXPECT_EQ(0, rdata_txt.compare(
                  *rdataFactoryFromFile(RRType("TXT"), RRClass("IN"),
                                        "testdata/rdata_txt_fromWire")));
}

TEST_F(RdataTest, toWireBuffer_TXT)
{
    rdata_txt.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_txt, sizeof(wiredata_txt));
}

TEST_F(RdataTest, toText_TXT)
{
    EXPECT_EQ("\"Test String\"", rdata_txt.toText());
}

}
