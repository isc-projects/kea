// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

//
// This test currently simply copies the NS RDATA tests.
//

namespace {
class Rdata_PTR_Test : public RdataTest {
public:
     Rdata_PTR_Test() :
         rdata_ptr("ns.example.com."),
         rdata_ptr2("ns2.example.com.")
     {}

     const generic::PTR rdata_ptr;
     const generic::PTR rdata_ptr2;
};

const uint8_t wiredata_ptr[] = {
    0x02, 0x6e, 0x73, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00 };
const uint8_t wiredata_ptr2[] = {
    // first name: ns.example.com.
    0x02, 0x6e, 0x73, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00,
    // second name: ns2.example.com.  all labels except the first should be
    // compressed.
    0x03, 0x6e, 0x73, 0x32, 0xc0, 0x03 };

TEST_F(Rdata_PTR_Test, createFromText) {
    EXPECT_EQ(0, rdata_ptr.compare(generic::PTR("ns.example.com.")));
    // explicitly add a trailing dot.  should be the same RDATA.
    EXPECT_EQ(0, rdata_ptr.compare(generic::PTR("ns.example.com.")));
    // should be case sensitive.
    EXPECT_EQ(0, rdata_ptr.compare(generic::PTR("NS.EXAMPLE.COM.")));
    // RDATA of a class-independent type should be recognized for any
    // "unknown" class.
    EXPECT_EQ(0, rdata_ptr.compare(*createRdata(RRType("PTR"), RRClass(65000),
                                               "ns.example.com.")));
}

TEST_F(Rdata_PTR_Test, badText) {
    // Extra text at end of line
    EXPECT_THROW(generic::PTR("foo.example.com. extra."), InvalidRdataText);
}

TEST_F(Rdata_PTR_Test, createFromWire) {
    EXPECT_EQ(0, rdata_ptr.compare(
                  *rdataFactoryFromFile(RRType("PTR"), RRClass("IN"),
                                        "rdata_ns_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType("PTR"), RRClass("IN"),
                                      "rdata_ns_fromWire", 18),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType("PTR"), RRClass("IN"),
                                      "rdata_ns_fromWire", 36),
                 InvalidRdataLength);
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType("PTR"), RRClass("IN"),
                                      "rdata_ns_fromWire", 71),
                 DNSMessageFORMERR);

    EXPECT_EQ(0, generic::PTR("ns2.example.com.").compare(
                  *rdataFactoryFromFile(RRType("PTR"), RRClass("IN"),
                                        "rdata_ns_fromWire", 55)));
    EXPECT_THROW(*rdataFactoryFromFile(RRType("PTR"), RRClass("IN"),
                                       "rdata_ns_fromWire", 63),
                 InvalidRdataLength);
}

TEST_F(Rdata_PTR_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_ptr.compare(
        *test::createRdataUsingLexer(RRType::PTR(), RRClass::IN(),
                                     "ns.example.com.")));

    // test::createRdataUsingLexer() constructs relative to
    // "example.org." origin.
    EXPECT_EQ(0, generic::PTR("foo0.example.org.").compare(
        *test::createRdataUsingLexer(RRType::PTR(), RRClass::IN(),
                                     "foo0")));

    // Extra text at end of line
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::PTR(), RRClass::IN(),
                                             "foo.example.com. extra."));
}

TEST_F(Rdata_PTR_Test, toWireBuffer) {
    rdata_ptr.toWire(obuffer);
    matchWireData(wiredata_ptr, sizeof(wiredata_ptr),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_PTR_Test, toWireRenderer) {
    rdata_ptr.toWire(renderer);
    matchWireData(wiredata_ptr, sizeof(wiredata_ptr),
                  renderer.getData(), renderer.getLength());

    rdata_ptr2.toWire(renderer);
    matchWireData(wiredata_ptr2, sizeof(wiredata_ptr2),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_PTR_Test, toText) {
    EXPECT_EQ("ns.example.com.", rdata_ptr.toText());
}

TEST_F(Rdata_PTR_Test, compare) {
    generic::PTR small("a.example.");
    generic::PTR large("example.");
    EXPECT_TRUE(Name("a.example") > Name("example"));
    EXPECT_GT(0, small.compare(large));
}

TEST_F(Rdata_PTR_Test, getPTRName) {
    EXPECT_EQ(Name("ns.example.com"), rdata_ptr.getPTRName());
}
}
