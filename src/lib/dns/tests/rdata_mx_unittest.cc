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
class Rdata_MX_Test : public RdataTest {
public:
    Rdata_MX_Test() :
        rdata_mx(10, Name("mx.example.com"))
    {}

    const generic::MX rdata_mx;
};

TEST_F(Rdata_MX_Test, createFromText) {
    const generic::MX rdata_mx2("10 mx.example.com.");
    EXPECT_EQ(0, rdata_mx2.compare(rdata_mx));
}

TEST_F(Rdata_MX_Test, badText) {
    EXPECT_THROW_WITH(const generic::MX rdata_mx("99999999 mx."),
                      InvalidRdataText, "Invalid MX preference: 99999999");
    EXPECT_THROW_WITH(const generic::MX rdata_mx("10"), InvalidRdataText,
                      "Failed to construct MX from '10': "
                      "unexpected end of input");
    EXPECT_THROW_WITH(const generic::MX rdata_mx("SPOON"), InvalidRdataText,
                      "Failed to construct MX from 'SPOON': "
                      "not a valid number");
    EXPECT_THROW_WITH(const generic::MX rdata_mx("10 mx. example.com."),
                      InvalidRdataText,
                      "extra input text for MX: 10 mx. example.com.");
    // No origin and relative
    EXPECT_THROW_WITH(const generic::MX rdata_mx("10 mx.example.com"),
                      MissingNameOrigin,
                      "No origin available and name is relative");
    // Extra text at end of line
    EXPECT_THROW_WITH(const generic::MX rdata_mx("10 mx.example.com. extra."),
                      InvalidRdataText,
                      "extra input text for MX: 10 mx.example.com. extra.");
}

TEST_F(Rdata_MX_Test, copy) {
    const generic::MX rdata_mx2(rdata_mx);
    EXPECT_EQ(0, rdata_mx.compare(rdata_mx2));
}

TEST_F(Rdata_MX_Test, createFromWire) {
    EXPECT_EQ(0, rdata_mx.compare(
                  *rdataFactoryFromFile(RRType("MX"), RRClass("IN"),
                                        "rdata_mx_fromWire")));
    // TBD: more tests
}

TEST_F(Rdata_MX_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_mx.compare(
        *test::createRdataUsingLexer(RRType::MX(), RRClass::IN(),
                                     "10 mx.example.com.")));

    // test::createRdataUsingLexer() constructs relative to
    // "example.org." origin.
    EXPECT_EQ(0, generic::MX("10 mx2.example.org.").compare(
        *test::createRdataUsingLexer(RRType::MX(), RRClass::IN(),
                                     "10 mx2")));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::MX(), RRClass::IN(),
                                             "10 mx. example.com."));

    // 65536 is larger than maximum possible preference
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::MX(), RRClass::IN(),
                                             "65536 mx.example.com."));

    // Extra text at end of line
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::MX(), RRClass::IN(),
                                             "10 mx.example.com. extra."));
}

TEST_F(Rdata_MX_Test, toWireRenderer) {
    renderer.writeName(Name("example.com"));
    rdata_mx.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_mx_toWire1", data);
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_MX_Test, toWireBuffer) {
    Name("example.com").toWire(obuffer);
    rdata_mx.toWire(obuffer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_mx_toWire2", data);
    matchWireData(&data[0], data.size(),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_MX_Test, toText) {
    EXPECT_EQ("10 mx.example.com.", rdata_mx.toText());
}

TEST_F(Rdata_MX_Test, getMXName) {
    EXPECT_EQ(Name("mx.example.com."), rdata_mx.getMXName());
}

TEST_F(Rdata_MX_Test, getMXPref) {
    EXPECT_EQ(10, rdata_mx.getMXPref());
}

TEST_F(Rdata_MX_Test, compare) {
    generic::MX small1(1, Name("mx.example.com"));
    generic::MX small2(10, Name("mx.example.com"));
    generic::MX large1(65535, Name("mx.example.com"));
    generic::MX large2(256, Name("mx.example.com"));

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
    EXPECT_THROW(rdata_mx.compare(*rdata_nomatch), bad_cast); 
}
}
