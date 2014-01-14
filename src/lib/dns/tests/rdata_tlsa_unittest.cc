// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <algorithm>
#include <string>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <boost/algorithm/string.hpp>

using isc::UnitTestUtil;
using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {
class Rdata_TLSA_Test : public RdataTest {
protected:
        Rdata_TLSA_Test() :
            tlsa_txt("0 0 1 d2abde240d7cd3ee6b4b28c54df034b9"
                     "7983a1d16e8a410e4561cb106618e971"),
            rdata_tlsa(tlsa_txt)
        {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::TLSA, isc::Exception, isc::Exception>(
            rdata_str, rdata_tlsa, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::TLSA, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_tlsa, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::TLSA, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_tlsa, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <generic::TLSA, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_tlsa, true, false);
    }

    const string tlsa_txt;
    const generic::TLSA rdata_tlsa;
};

const uint8_t rdata_tlsa_wiredata[] = {
    // certificate usage
    0x00,
    // selector
    0x00,
    // matching type
    0x01,
    // certificate association data
    0xd2, 0xab, 0xde, 0x24, 0x0d, 0x7c, 0xd3, 0xee,
    0x6b, 0x4b, 0x28, 0xc5, 0x4d, 0xf0, 0x34, 0xb9,
    0x79, 0x83, 0xa1, 0xd1, 0x6e, 0x8a, 0x41, 0x0e,
    0x45, 0x61, 0xcb, 0x10, 0x66, 0x18, 0xe9, 0x71
};

TEST_F(Rdata_TLSA_Test, createFromText) {
    // Basic test
    checkFromText_None(tlsa_txt);

    // With different spacing
    checkFromText_None("0 0 1    d2abde240d7cd3ee6b4b28c54df034b9"
                       "7983a1d16e8a410e4561cb106618e971");

    // Combination of lowercase and uppercase
    checkFromText_None("0 0 1 D2ABDE240D7CD3EE6B4B28C54DF034B9"
                       "7983a1d16e8a410e4561cb106618e971");

    // spacing in the certificate association data field
    checkFromText_None("0 0 1 d2abde240d7cd3ee6b4b28c54df034b9"
                       "      7983a1d16e8a410e4561cb106618e971");

    // multi-line certificate association data field
    checkFromText_None("0 0 1 ( d2abde240d7cd3ee6b4b28c54df034b9\n"
                       "        7983a1d16e8a410e4561cb106618e971 )");

    // string constructor throws if there's extra text,
    // but lexer constructor doesn't
    checkFromText_BadString(tlsa_txt + "\n" + tlsa_txt);
}

TEST_F(Rdata_TLSA_Test, fields) {
    // Some of these may not be RFC conformant, but we relax the check
    // in our code to work with other field values that may show up in
    // the future.
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("1 0 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("2 0 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("3 0 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("128 0 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("255 0 1 12ab"));

    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 1 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 2 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 3 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 128 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 255 1 12ab"));

    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 0 1 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 0 2 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 0 3 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 0 128 12ab"));
    EXPECT_NO_THROW(const generic::TLSA rdata_tlsa("0 0 255 12ab"));

    // > 255 would be broken
    EXPECT_THROW(const generic::TLSA rdata_tlsa("256 0 1 12ab"),
                 InvalidRdataText);
    EXPECT_THROW(const generic::TLSA rdata_tlsa("0 256 1 12ab"),
                 InvalidRdataText);
    EXPECT_THROW(const generic::TLSA rdata_tlsa("0 0 256 12ab"),
                 InvalidRdataText);
}

TEST_F(Rdata_TLSA_Test, badText) {
    checkFromText_LexerError("1");
    checkFromText_LexerError("ONE 2 3 123456789abcdef67890123456789abcdef67890");
    checkFromText_LexerError("1 TWO 3 123456789abcdef67890123456789abcdef67890");
    checkFromText_LexerError("1 2 THREE 123456789abcdef67890123456789abcdef67890");
    checkFromText_InvalidText("1 2 3 BAABAABLACKSHEEP");
    checkFromText_InvalidText(tlsa_txt + " extra text");

    // yes, these are redundant to the last test cases in the .fields
    // test
    checkFromText_InvalidText(
        "2345 1 2 123456789abcdef67890123456789abcdef67890");
    checkFromText_InvalidText(
        "3 1234 4 123456789abcdef67890123456789abcdef67890");
    checkFromText_InvalidText(
        "5 6 1234 123456789abcdef67890123456789abcdef67890");

    // negative values are trapped in the lexer rather than the
    // constructor
    checkFromText_LexerError("-2 0 1 123456789abcdef67890123456789abcdef67890");
    checkFromText_LexerError("0 -2 1 123456789abcdef67890123456789abcdef67890");
    checkFromText_LexerError("0 0 -2 123456789abcdef67890123456789abcdef67890");
}

TEST_F(Rdata_TLSA_Test, copyAndAssign) {
    // Copy construct
    generic::TLSA rdata_tlsa2(rdata_tlsa);
    EXPECT_EQ(0, rdata_tlsa.compare(rdata_tlsa2));

    // Assignment, mainly to confirm it doesn't cause disruption.
    rdata_tlsa2 = rdata_tlsa;
    EXPECT_EQ(0, rdata_tlsa.compare(rdata_tlsa2));
}

TEST_F(Rdata_TLSA_Test, createFromWire) {
    // Basic test
    EXPECT_EQ(0, rdata_tlsa.compare(
                  *rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                        "rdata_tlsa_fromWire")));
    // Combination of lowercase and uppercase
    EXPECT_EQ(0, rdata_tlsa.compare(
                  *rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                        "rdata_tlsa_fromWire2")));
    // certificate_usage=0, selector=0, matching_type=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                         "rdata_tlsa_fromWire3.wire"));

    // certificate_usage=255, selector=0, matching_type=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                         "rdata_tlsa_fromWire4.wire"));

    // certificate_usage=0, selector=255, matching_type=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                         "rdata_tlsa_fromWire5.wire"));

    // certificate_usage=0, selector=0, matching_type=255
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                         "rdata_tlsa_fromWire6.wire"));

    // certificate_usage=3, selector=1, matching_type=2
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                         "rdata_tlsa_fromWire7.wire"));

    // short certificate association data
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                         "rdata_tlsa_fromWire8.wire"));

    // certificate association data is shorter than rdata len
    EXPECT_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                      "rdata_tlsa_fromWire9"),
                 InvalidBufferPosition);

    // certificate association data is missing
    EXPECT_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                      "rdata_tlsa_fromWire10"),
                 InvalidBufferPosition);

    // all RDATA is missing
    EXPECT_THROW(rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                                      "rdata_tlsa_fromWire11"),
                 InvalidBufferPosition);
}

TEST_F(Rdata_TLSA_Test, createFromParams) {
    const generic::TLSA rdata_tlsa2(
        0, 0, 1, "d2abde240d7cd3ee6b4b28c54df034b9"
                 "7983a1d16e8a410e4561cb106618e971");
    EXPECT_EQ(0, rdata_tlsa2.compare(rdata_tlsa));
}

TEST_F(Rdata_TLSA_Test, toText) {
    EXPECT_TRUE(boost::iequals(tlsa_txt, rdata_tlsa.toText()));

    const string tlsa_txt2("3 2 1");
    const generic::TLSA rdata_tlsa2(tlsa_txt2);
    EXPECT_TRUE(boost::iequals(tlsa_txt2, rdata_tlsa2.toText()));

    const generic::TLSA rdata_tlsa3("3 2 1 ");
    EXPECT_TRUE(boost::iequals(tlsa_txt2, rdata_tlsa3.toText()));
}

TEST_F(Rdata_TLSA_Test, toWire) {
    this->obuffer.clear();
    rdata_tlsa.toWire(this->obuffer);

    EXPECT_EQ(sizeof (rdata_tlsa_wiredata),
              this->obuffer.getLength());

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        rdata_tlsa_wiredata, sizeof(rdata_tlsa_wiredata));
}

TEST_F(Rdata_TLSA_Test, compare) {
    const generic::TLSA rdata_tlsa2("0 0 0");
    EXPECT_EQ(-1, rdata_tlsa2.compare(rdata_tlsa));
    EXPECT_EQ(1, rdata_tlsa.compare(rdata_tlsa2));
}

TEST_F(Rdata_TLSA_Test, getCertificateUsage) {
    EXPECT_EQ(0, rdata_tlsa.getCertificateUsage());
}

TEST_F(Rdata_TLSA_Test, getSelector) {
    EXPECT_EQ(0, rdata_tlsa.getSelector());
}

TEST_F(Rdata_TLSA_Test, getMatchingType) {
    EXPECT_EQ(1, rdata_tlsa.getMatchingType());
}

TEST_F(Rdata_TLSA_Test, getDataLength) {
    EXPECT_EQ(32, rdata_tlsa.getDataLength());
}

TEST_F(Rdata_TLSA_Test, emptyCertificateAssociationDataFromWire) {
    const uint8_t rdf_wiredata[] = {
        // certificate usage
        0x03,
        // selector
        0x01,
        // matching type
        0x02,
    };

    const generic::TLSA rdf =
        dynamic_cast<const generic::TLSA&>
        (*rdataFactoryFromFile(RRType("TLSA"), RRClass("IN"),
                               "rdata_tlsa_fromWire12"));

    EXPECT_EQ(3, rdf.getCertificateUsage());
    EXPECT_EQ(1, rdf.getSelector());
    EXPECT_EQ(2, rdf.getMatchingType());
    EXPECT_EQ(0, rdf.getDataLength());

    this->obuffer.clear();
    rdf.toWire(this->obuffer);

    EXPECT_EQ(3, this->obuffer.getLength());

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        rdf_wiredata, sizeof(rdf_wiredata));
}

TEST_F(Rdata_TLSA_Test, emptyCertificateAssociationDataFromString) {
    const generic::TLSA rdata_tlsa2("3 2 1");
    const uint8_t rdata_tlsa2_wiredata[] = {
        // certificate usage
        0x03,
        // selector
        0x02,
        // matching type
        0x01
    };

    EXPECT_EQ(3, rdata_tlsa2.getCertificateUsage());
    EXPECT_EQ(2, rdata_tlsa2.getSelector());
    EXPECT_EQ(1, rdata_tlsa2.getMatchingType());
    EXPECT_EQ(0, rdata_tlsa2.getDataLength());

    this->obuffer.clear();
    rdata_tlsa2.toWire(this->obuffer);

    EXPECT_EQ(3, this->obuffer.getLength());

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        rdata_tlsa2_wiredata, sizeof(rdata_tlsa2_wiredata));
}
}
