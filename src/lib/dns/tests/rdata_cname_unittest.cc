// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/unittests/test_exceptions.h>
#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_CNAME_Test : public RdataTest {
public:
    Rdata_CNAME_Test() :
        rdata_cname("cn.example.com."),
        rdata_cname2("cn2.example.com.")
    {}

    const generic::CNAME rdata_cname;
    const generic::CNAME rdata_cname2;
};

const uint8_t wiredata_cname[] = {
    0x02, 0x63, 0x6e, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00 };
const uint8_t wiredata_cname2[] = {
    // first name: cn.example.com.
    0x02, 0x63, 0x6e, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00,
    // second name: cn2.example.com.  all labels except the first should be
    // compressed.
    0x03, 0x63, 0x6e, 0x32, 0xc0, 0x03 };

TEST_F(Rdata_CNAME_Test, createFromText) {
    EXPECT_EQ(0, rdata_cname.compare(generic::CNAME("cn.example.com.")));
    // explicitly add a trailing dot.  should be the same RDATA.
    EXPECT_EQ(0, rdata_cname.compare(generic::CNAME("cn.example.com.")));
    // should be case sensitive.
    EXPECT_EQ(0, rdata_cname.compare(generic::CNAME("CN.EXAMPLE.COM.")));
    // RDATA of a class-independent type should be recognized for any
    // "unknown" class.
    EXPECT_EQ(0, rdata_cname.compare(*createRdata(RRType("CNAME"),
                                                  RRClass(65000),
                                                  "cn.example.com.")));
}

TEST_F(Rdata_CNAME_Test, badText) {
    // Extra text at end of line
    EXPECT_THROW_WITH(generic::CNAME("cname.example.com. extra."),
                      InvalidRdataText,
                      "extra input text for CNAME: "
                      "cname.example.com. extra.");
}

TEST_F(Rdata_CNAME_Test, createFromWire) {
    EXPECT_EQ(0, rdata_cname.compare(
                  *rdataFactoryFromFile(RRType("CNAME"), RRClass("IN"),
                                        "rdata_cname_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType("CNAME"), RRClass("IN"),
                                           "rdata_cname_fromWire", 18),
                      InvalidRdataLength, "RDLENGTH mismatch: 16 != 15");
    // RDLENGTH is too long
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType("CNAME"), RRClass("IN"),
                                           "rdata_cname_fromWire", 36),
                      InvalidRdataLength, "RDLENGTH mismatch: 16 != 17");
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType("CNAME"), RRClass("IN"),
                                           "rdata_cname_fromWire", 71),
                      DNSMessageFORMERR, "incomplete wire-format name");

    EXPECT_EQ(0, generic::CNAME("cn2.example.com.").compare(
                  *rdataFactoryFromFile(RRType("CNAME"), RRClass("IN"),
                                        "rdata_cname_fromWire", 55)));
    EXPECT_THROW_WITH(*rdataFactoryFromFile(RRType("CNAME"), RRClass("IN"),
                                            "rdata_cname_fromWire", 63),
                      InvalidRdataLength, "RDLENGTH mismatch: 6 != 17");
}

TEST_F(Rdata_CNAME_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_cname.compare(
        *test::createRdataUsingLexer(RRType::CNAME(), RRClass::IN(),
                                     "cn.example.com.")));

    // test::createRdataUsingLexer() constructs relative to
    // "example.org." origin.
    EXPECT_EQ(0, generic::CNAME("cname10.example.org.").compare(
        *test::createRdataUsingLexer(RRType::CNAME(), RRClass::IN(),
                                     "cname10")));

    // Extra text at end of line
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::CNAME(), RRClass::IN(),
                                             "cname.example.com. extra."));
}

TEST_F(Rdata_CNAME_Test, toWireBuffer) {
    rdata_cname.toWire(obuffer);
    matchWireData(wiredata_cname, sizeof(wiredata_cname),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_CNAME_Test, toWireRenderer) {
    rdata_cname.toWire(renderer);
    matchWireData(wiredata_cname, sizeof(wiredata_cname),
                  renderer.getData(), renderer.getLength());

    rdata_cname2.toWire(renderer);
    matchWireData(wiredata_cname2, sizeof(wiredata_cname2),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_CNAME_Test, toText) {
    EXPECT_EQ("cn.example.com.", rdata_cname.toText());
}

TEST_F(Rdata_CNAME_Test, getCname) {
    EXPECT_EQ(Name("cn.example.com."), rdata_cname.getCname());
}
}
