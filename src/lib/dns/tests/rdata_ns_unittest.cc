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
class Rdata_NS_Test : public RdataTest {
    // there's nothing to specialize
};

const generic::NS rdata_ns("ns.example.com");
const generic::NS rdata_ns2("ns2.example.com");
const uint8_t wiredata_ns[] = {
    0x02, 0x6e, 0x73, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00 };
const uint8_t wiredata_ns2[] = {
    // first name: ns.example.com.
    0x02, 0x6e, 0x73, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00,
    // second name: ns2.example.com.  all labels except the first should be
    // compressed.
    0x03, 0x6e, 0x73, 0x32, 0xc0, 0x03 };

TEST_F(Rdata_NS_Test, createFromText) {
    EXPECT_EQ(0, rdata_ns.compare(generic::NS("ns.example.com")));
    // explicitly add a trailing dot.  should be the same RDATA.
    EXPECT_EQ(0, rdata_ns.compare(generic::NS("ns.example.com.")));
    // should be case sensitive.
    EXPECT_EQ(0, rdata_ns.compare(generic::NS("NS.EXAMPLE.COM")));
    // RDATA of a class-independent type should be recognized for any
    // "unknown" class.
    EXPECT_EQ(0, rdata_ns.compare(*createRdata(RRType("NS"), RRClass(65000),
                                               "ns.example.com")));
}

TEST_F(Rdata_NS_Test, createFromWire) {
    EXPECT_EQ(0, rdata_ns.compare(
                  *rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                        "rdata_ns_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                      "rdata_ns_fromWire", 18),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                      "rdata_ns_fromWire", 36),
                 InvalidRdataLength);
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                      "rdata_ns_fromWire", 71),
                 DNSMessageFORMERR);

    EXPECT_EQ(0, generic::NS("ns2.example.com").compare(
                  *rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                        "rdata_ns_fromWire", 55)));
    EXPECT_THROW(*rdataFactoryFromFile(RRType("NS"), RRClass("IN"),
                                       "rdata_ns_fromWire", 63),
                 InvalidRdataLength);
}

TEST_F(Rdata_NS_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_ns.compare(
        *test::createRdataUsingLexer(RRType::NS(), RRClass::IN(),
                                     "ns.example.com")));

    EXPECT_THROW({
        test::createRdataUsingLexer(RRType::NS(), RRClass::IN(),
                                    "");
    }, IncompleteName);
}

TEST_F(Rdata_NS_Test, toWireBuffer) {
    rdata_ns.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_ns, sizeof(wiredata_ns));
}

TEST_F(Rdata_NS_Test, toWireRenderer) {
    rdata_ns.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata_ns, sizeof(wiredata_ns));
    rdata_ns2.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata_ns2, sizeof(wiredata_ns2));
}

TEST_F(Rdata_NS_Test, toText) {
    EXPECT_EQ("ns.example.com.", rdata_ns.toText());
}

TEST_F(Rdata_NS_Test, compare) {
    generic::NS small("a.example");
    generic::NS large("example");
    EXPECT_TRUE(Name("a.example") > Name("example"));
    EXPECT_GT(0, small.compare(large));
}

TEST_F(Rdata_NS_Test, getNSName) {
    EXPECT_EQ(Name("ns.example.com"), rdata_ns.getNSName());
}
}
