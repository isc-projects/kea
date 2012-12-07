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

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {
class Rdata_IN_AAAA_Test : public RdataTest {
    // there's nothing to specialize
};

const in::AAAA rdata_in_aaaa("2001:db8::1234");
const uint8_t wiredata_in_aaaa[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x12, 0x34 };

TEST_F(Rdata_IN_AAAA_Test, createFromText) {
    rdata_in_aaaa.compare(in::AAAA(string("2001:db8::1234")));
    EXPECT_THROW(in::AAAA("192.0.2.1"), InvalidRdataText);
    EXPECT_THROW(in::AAAA("xxx"), InvalidRdataText);
}

TEST_F(Rdata_IN_AAAA_Test, createFromWire) {
    // Valid data
    EXPECT_EQ(0, rdata_in_aaaa.compare(
                  *rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                        "rdata_in_aaaa_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                      "rdata_in_aaaa_fromWire", 18),
                 DNSMessageFORMERR);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                      "rdata_in_aaaa_fromWire", 36),
                 DNSMessageFORMERR);
    // buffer too short.
    EXPECT_THROW(rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                      "rdata_in_aaaa_fromWire", 55),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_IN_AAAA_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_in_aaaa.compare(
        *test::createRdataUsingLexer(RRType::AAAA(), RRClass::IN(),
                                     "2001:db8::1234")));
}

TEST_F(Rdata_IN_AAAA_Test, toWireBuffer) {
    rdata_in_aaaa.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_in_aaaa, sizeof(wiredata_in_aaaa));
}

TEST_F(Rdata_IN_AAAA_Test, toWireRenderer) {
    rdata_in_aaaa.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata_in_aaaa, sizeof(wiredata_in_aaaa));
}

TEST_F(Rdata_IN_AAAA_Test, toText) {
    EXPECT_EQ("2001:db8::1234", rdata_in_aaaa.toText());
}

TEST_F(Rdata_IN_AAAA_Test, compare) {
    in::AAAA small1("::1");
    in::AAAA small2("1:2:3:4:5:6:7:8");
    in::AAAA large1("ffff::");
    in::AAAA large2("8:7:6:5:4:3:2:1");

    // trivial case: self equivalence
    // cppcheck-suppress uselessCallsCompare
    EXPECT_EQ(0, small1.compare(small1));

    // confirm these are compared as unsigned values
    EXPECT_GT(0, small1.compare(large1));
    EXPECT_LT(0, large1.compare(small1));

    // confirm these are compared in network byte order
    EXPECT_GT(0, small2.compare(large2));
    EXPECT_LT(0, large2.compare(small2));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_in_aaaa.compare(*RdataTest::rdata_nomatch), bad_cast); 
}
}
