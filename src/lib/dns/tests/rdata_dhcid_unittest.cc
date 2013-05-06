// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/rdataclass.h>
#include <util/encode/base64.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata;

namespace {

class Rdata_DHCID_Test : public RdataTest {
protected:
    Rdata_DHCID_Test() :
        dhcid_txt("0LIg0LvQtdGB0YMg0YDQvtC00LjQu9Cw0YHRjCDRkdC70L7Rh9C60LA="),
        rdata_dhcid(dhcid_txt)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<in::DHCID, isc::Exception, isc::Exception>(
            rdata_str, rdata_dhcid, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<in::DHCID, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_dhcid, true, true);
    }

    void checkFromText_BadValue(const string& rdata_str) {
        checkFromText<in::DHCID, BadValue, BadValue>(
            rdata_str, rdata_dhcid, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <in::DHCID, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_dhcid, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <in::DHCID, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_dhcid, true, false);
    }

    const string dhcid_txt;
    const in::DHCID rdata_dhcid;
};

TEST_F(Rdata_DHCID_Test, fromText) {
    EXPECT_EQ(dhcid_txt, rdata_dhcid.toText());

    // Space in digest data is OK
    checkFromText_None(
            "0LIg0LvQtdGB0YMg 0YDQvtC00LjQu9Cw 0YHRjCDRkdC70L7R h9C60LA=");

    // Multi-line digest data is OK, if enclosed in parentheses
    checkFromText_None(
            "( 0LIg0LvQtdGB0YMg0YDQvtC00LjQu9Cw\n0YHRjCDRkdC70L7R h9C60LA= )");

    // Trailing garbage. This should cause only the string constructor
    // to fail, but the lexer constructor must be able to continue
    // parsing from it.
    checkFromText_BadString(
            "0LIg0LvQtdGB0YMg0YDQvtC00LjQu9Cw0YHRjCDRkdC70L7Rh9C60LA="
            " ; comment\n"
            "AAIBY2/AuCccgoJbsaxcQc9TUapptP69lOjxfNuVAA2kjEA=");
}

TEST_F(Rdata_DHCID_Test, badText) {
    // missing digest data
    checkFromText_LexerError("");

    // invalid base64
    checkFromText_BadValue("EEeeeeeeEEEeeeeeeGaaahAAAAAAAAHHHHHHHHHHH!=");

    // unterminated multi-line base64
    checkFromText_LexerError(
            "( 0LIg0LvQtdGB0YMg0YDQvtC00LjQu9Cw\n0YHRjCDRkdC70L7R h9C60LA=");
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
                                     dhcid_txt)));
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
    EXPECT_EQ(dhcid_txt, rdata_dhcid.toText());
}

TEST_F(Rdata_DHCID_Test, getDHCIDDigest) {
    const string dhcid_txt1(encodeBase64(rdata_dhcid.getDigest()));

    EXPECT_EQ(dhcid_txt, dhcid_txt1);
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
