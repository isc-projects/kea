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

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <util/unittests/wiredata.h>
#include <util/unittests/test_exceptions.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_DNAME_Test : public RdataTest {
public:
    Rdata_DNAME_Test() :
        rdata_dname("dn.example.com."),
        rdata_dname2("dn2.example.com.")
    {}

    const generic::DNAME rdata_dname;
    const generic::DNAME rdata_dname2;
};

const uint8_t wiredata_dname[] = {
    0x02, 0x64, 0x6e, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00 };
const uint8_t wiredata_dname2[] = {
    // first name: dn.example.com.
    0x02, 0x64, 0x6e, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00,
    // second name: dn2.example.com.  The "example.com" shouldn't be compressed
    // because DNAME is not a well know type per RFC3597.
    0x03, 0x64, 0x6e, 0x32,
    0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03,
    0x63, 0x6f, 0x6d, 0x00 };

TEST_F(Rdata_DNAME_Test, createFromText) {
    EXPECT_EQ(0, rdata_dname.compare(generic::DNAME("dn.example.com.")));
    // explicitly add a trailing dot.  should be the same RDATA.
    EXPECT_EQ(0, rdata_dname.compare(generic::DNAME("dn.example.com.")));
    // should be case sensitive.
    EXPECT_EQ(0, rdata_dname.compare(generic::DNAME("DN.EXAMPLE.COM.")));
    // RDATA of a class-independent type should be recognized for any
    // "unknown" class.
    EXPECT_EQ(0, rdata_dname.compare(*createRdata(RRType("DNAME"),
                                                  RRClass(65000),
                                                  "dn.example.com.")));
}

TEST_F(Rdata_DNAME_Test, badText) {
    // Extra text at end of line
    EXPECT_THROW_WITH(generic::DNAME("dname.example.com. extra."),
                      InvalidRdataText,
                      "extra input text for DNAME: "
                      "dname.example.com. extra.");
}

TEST_F(Rdata_DNAME_Test, createFromWire) {
    EXPECT_EQ(0, rdata_dname.compare(
                  *rdataFactoryFromFile(RRType("DNAME"), RRClass("IN"),
                                        "rdata_dname_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType("DNAME"), RRClass("IN"),
                                           "rdata_dname_fromWire", 18),
                      InvalidRdataLength, "RDLENGTH mismatch: 16 != 15");
    // RDLENGTH is too long
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType("DNAME"), RRClass("IN"),
                                           "rdata_dname_fromWire", 36),
                      InvalidRdataLength, "RDLENGTH mismatch: 16 != 17");
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType("DNAME"), RRClass("IN"),
                                           "rdata_dname_fromWire", 71),
                      DNSMessageFORMERR, "incomplete wire-format name");

    EXPECT_EQ(0, generic::DNAME("dn2.example.com.").compare(
                  *rdataFactoryFromFile(RRType("DNAME"), RRClass("IN"),
                                        "rdata_dname_fromWire", 55)));
    EXPECT_THROW_WITH(*rdataFactoryFromFile(RRType("DNAME"), RRClass("IN"),
                                            "rdata_dname_fromWire", 63),
                      InvalidRdataLength, "RDLENGTH mismatch: 6 != 17");
}

TEST_F(Rdata_DNAME_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_dname.compare(
        *test::createRdataUsingLexer(RRType::DNAME(), RRClass::IN(),
                                     "dn.example.com.")));

    // test::createRdataUsingLexer() constructs relative to
    // "example.org." origin.
    EXPECT_EQ(0, generic::DNAME("dname8.example.org.").compare(
        *test::createRdataUsingLexer(RRType::DNAME(), RRClass::IN(),
                                     "dname8")));

    // Extra text at end of line
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::DNAME(), RRClass::IN(),
                                             "dname.example.com. extra."));
}

TEST_F(Rdata_DNAME_Test, toWireBuffer) {
    rdata_dname.toWire(obuffer);
    matchWireData(wiredata_dname, sizeof(wiredata_dname),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_DNAME_Test, toWireRenderer) {
    rdata_dname.toWire(renderer);
    matchWireData(wiredata_dname, sizeof(wiredata_dname),
                  renderer.getData(), renderer.getLength());

    rdata_dname2.toWire(renderer);
    matchWireData(wiredata_dname2, sizeof(wiredata_dname2),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_DNAME_Test, toText) {
    EXPECT_EQ("dn.example.com.", rdata_dname.toText());
}

TEST_F(Rdata_DNAME_Test, getDname) {
    EXPECT_EQ(Name("dn.example.com."), rdata_dname.getDname());
}
}
