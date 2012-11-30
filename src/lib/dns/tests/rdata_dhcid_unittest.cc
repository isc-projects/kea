// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <dns/rdataclass.h>
#include <util/encode/base64.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata;

namespace {

const string string_dhcid(
                   "0LIg0LvQtdGB0YMg0YDQvtC00LjQu9Cw0YHRjCDRkdC70L7Rh9C60LA=");

const in::DHCID rdata_dhcid(string_dhcid);

class Rdata_DHCID_Test : public RdataTest {
};

TEST_F(Rdata_DHCID_Test, createFromString) {
    const in::DHCID rdata_dhcid2(string_dhcid);
    EXPECT_EQ(0, rdata_dhcid2.compare(rdata_dhcid));
}

TEST_F(Rdata_DHCID_Test, badBase64) {
    EXPECT_THROW(const in::DHCID rdata_dhcid_bad("00"), isc::BadValue);
}

TEST_F(Rdata_DHCID_Test, badLength) {
    EXPECT_THROW(const in::DHCID rdata_dhcid_bad("MDA="), InvalidRdataLength);
}

TEST_F(Rdata_DHCID_Test, copy) {
    const in::DHCID rdata_dhcid2(rdata_dhcid);
    EXPECT_EQ(0, rdata_dhcid.compare(rdata_dhcid2));
}

TEST_F(Rdata_DHCID_Test, createFromWire) {
    EXPECT_EQ(0, rdata_dhcid.compare(
                  *rdataFactoryFromFile(RRType("DHCID"), RRClass("IN"),
                                        "rdata_dhcid_fromWire")));
    // TBD: more tests
}

TEST_F(Rdata_DHCID_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_dhcid.compare(
        *test::createRdataUsingLexer(RRType::DHCID(), RRClass::IN(),
                                     string_dhcid)));

    // Check that bad input throws as usual
    EXPECT_THROW({
        *test::createRdataUsingLexer(RRType::DHCID(), RRClass::IN(), "00");
    }, isc::BadValue);
}

TEST_F(Rdata_DHCID_Test, toWireRenderer) {
    rdata_dhcid.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_dhcid_toWire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, renderer.getData(),
                        renderer.getLength(), &data[0], data.size());
}

TEST_F(Rdata_DHCID_Test, toWireBuffer) {
    rdata_dhcid.toWire(obuffer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_dhcid_toWire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, obuffer.getData(),
                        obuffer.getLength(), &data[0], data.size());
}

TEST_F(Rdata_DHCID_Test, toText) {
    EXPECT_EQ(string_dhcid, rdata_dhcid.toText());
}

TEST_F(Rdata_DHCID_Test, getDHCIDDigest) {
    const string string_dhcid1(encodeBase64(rdata_dhcid.getDigest()));

    EXPECT_EQ(string_dhcid, string_dhcid1);
}

TEST_F(Rdata_DHCID_Test, compare) {
    // trivial case: self equivalence
    // cppcheck-suppress uselessCallsCompare
    EXPECT_EQ(0, rdata_dhcid.compare(rdata_dhcid));

    in::DHCID rdata_dhcid1("0YLQvtC/0L7Qu9GPINC00LLQsCDRgNGD0LHQu9GP");
    in::DHCID rdata_dhcid2("0YLQvtC/0L7Qu9GPINGC0YDQuCDRgNGD0LHQu9GP");
    in::DHCID rdata_dhcid3("0YLQvtC/0L7Qu9GPINGH0LXRgtGL0YDQtSDRgNGD0LHQu9GP");

    EXPECT_LT(rdata_dhcid1.compare(rdata_dhcid2), 0);
    EXPECT_GT(rdata_dhcid2.compare(rdata_dhcid1), 0);

    EXPECT_LT(rdata_dhcid2.compare(rdata_dhcid3), 0);
    EXPECT_GT(rdata_dhcid3.compare(rdata_dhcid2), 0);

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_dhcid.compare(*rdata_nomatch), bad_cast); 
}
}
