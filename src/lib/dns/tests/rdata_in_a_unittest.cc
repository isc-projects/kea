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
class Rdata_IN_A_Test : public RdataTest {
    // there's nothing to specialize
};

const in::A rdata_in_a("192.0.2.1");
const uint8_t wiredata_in_a[] = { 192, 0, 2, 1 };

TEST_F(Rdata_IN_A_Test, createFromText) {
    EXPECT_EQ(0, rdata_in_a.compare(in::A("192.0.2.1")));
    // should reject an abbreviated form of IPv4 address
    EXPECT_THROW(in::A("10.1"), InvalidRdataText);
    // or an IPv6 address
    EXPECT_THROW(in::A("2001:db8::1234"), InvalidRdataText);
    // or any meaningless text as an IP address
    EXPECT_THROW(in::A("xxx"), InvalidRdataText);
}

TEST_F(Rdata_IN_A_Test, createFromWire) {
    // Valid data
    EXPECT_EQ(0, rdata_in_a.compare(
                  *rdataFactoryFromFile(RRType::A(), RRClass::IN(),
                                        "rdata_in_a_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::A(), RRClass::IN(),
                                      "rdata_in_a_fromWire", 6),
                 DNSMessageFORMERR);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType::A(), RRClass::IN(),
                                      "rdata_in_a_fromWire", 12),
                 DNSMessageFORMERR);
    // buffer too short.
    EXPECT_THROW(rdataFactoryFromFile(RRType::A(), RRClass::IN(),
                                      "rdata_in_a_fromWire", 19),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_IN_A_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_in_a.compare(
        *test::createRdataUsingLexer(RRType::A(), RRClass::IN(), "192.0.2.1")));
}

TEST_F(Rdata_IN_A_Test, toWireBuffer) {
    rdata_in_a.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_in_a, sizeof(wiredata_in_a));
}

TEST_F(Rdata_IN_A_Test, toWireRenderer) {
    rdata_in_a.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata_in_a, sizeof(wiredata_in_a));
}

TEST_F(Rdata_IN_A_Test, toText) {
    EXPECT_EQ("192.0.2.1", rdata_in_a.toText());
    string longaddr("255.255.255.255"); // this shouldn't make the code crash
    EXPECT_EQ(longaddr, in::A(longaddr).toText());
}

TEST_F(Rdata_IN_A_Test, compare) {
    in::A small1("1.1.1.1");
    in::A small2("1.2.3.4");
    in::A large1("255.255.255.255");
    in::A large2("4.3.2.1");

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
    EXPECT_THROW(rdata_in_a.compare(*RdataTest::rdata_nomatch), bad_cast); 
}
}
