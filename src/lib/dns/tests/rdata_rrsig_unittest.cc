// Copyright (C) 2010-2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <util/time_utilities.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>
#include <dns/tests/rdata_unittest.h>
#include <util/unittests/test_exceptions.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {

const uint8_t wiredata_rrsig[] = {
    // type covered = A
    0x00, 0x01,
    // algorithm = 5
    0x05,
    // labels = 4
    0x04,
    // original TTL = 43200 (0x0000a8c0)
    0x00, 0x00, 0xa8, 0xc0,
    // signature expiration = 1266961577 (0x4b844ca9)
    0x4b, 0x84, 0x4c, 0xa9,
    // signature inception = 1266875177 (0x4b82fb29)
    0x4b, 0x82, 0xfb, 0x29,
    // key tag = 8496 (0x2130)
    0x21, 0x30,
    // signer's name (isc.org.)
    // 3     i     s     c     3     o     r     g     0
    0x03, 0x69, 0x73, 0x63, 0x03, 0x6f, 0x72, 0x67, 0x00,
    // signature data follows
    0x7a, 0xfc, 0x61, 0x94, 0x6c,
    0x75, 0xde, 0x6a, 0x4a, 0x2d, 0x59, 0x0a, 0xb2,
    0x3a, 0x46, 0xcf, 0x27, 0x12, 0xe6, 0xdc, 0x2d,
    0x22, 0x8c, 0x4e, 0x9a, 0x53, 0x75, 0xe3, 0x0f,
    0x6d, 0xe4, 0x08, 0x33, 0x18, 0x19, 0xb3, 0x76,
    0x21, 0x9d, 0x2c, 0x8a, 0xc5, 0x69, 0xba, 0xab,
    0xef, 0x66, 0x9f, 0xda, 0xb5, 0x2a, 0xf9, 0x40,
    0xc1, 0x28, 0xc5, 0x97, 0xba, 0x3c, 0x19, 0x4d,
    0x95, 0x13, 0xc2, 0xcd, 0xf6, 0xb1, 0x59, 0x5d,
    0x0c, 0xf9, 0x3f, 0x35, 0xbb, 0x9a, 0x70, 0x93,
    0x36, 0xe5, 0xf4, 0x17, 0x7e, 0xfe, 0x66, 0x3b,
    0x70, 0x1f, 0xed, 0x33, 0xa8, 0xa3, 0x0d, 0xc0,
    0x8c, 0xc6, 0x95, 0x1b, 0xd8, 0x9c, 0x8c, 0x25,
    0xb4, 0x57, 0x9e, 0x56, 0x71, 0x64, 0x14, 0x7f,
    0x8f, 0x6d, 0xfa, 0xc5, 0xca, 0x3f, 0x36, 0xe2,
    0xa4, 0xdf, 0x60, 0xfa, 0xcd, 0x59, 0x3e, 0x22,
    0x32, 0xa1, 0xf7
};

class Rdata_RRSIG_Test : public RdataTest {
protected:
    Rdata_RRSIG_Test() :
        rrsig_txt("A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
                  "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                  "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                  "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                  "f49t+sXKPzbipN9g+s1ZPiIyofc="),
        rdata_rrsig(rrsig_txt)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::RRSIG, isc::Exception, isc::Exception>(
            rdata_str, rdata_rrsig, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::RRSIG, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_rrsig, true, true);
    }

    void checkFromText_InvalidType(const string& rdata_str) {
        checkFromText<generic::RRSIG, InvalidRRType, InvalidRRType>(
            rdata_str, rdata_rrsig, true, true);
    }

    void checkFromText_InvalidTime(const string& rdata_str) {
        checkFromText<generic::RRSIG, InvalidTime, InvalidTime>(
            rdata_str, rdata_rrsig, true, true);
    }

    void checkFromText_BadValue(const string& rdata_str) {
        checkFromText<generic::RRSIG, BadValue, BadValue>(
            rdata_str, rdata_rrsig, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::RRSIG, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_rrsig, true, true);
    }

    void checkFromText_MissingOrigin(const string& rdata_str) {
        checkFromText
            <generic::RRSIG, MissingNameOrigin, MissingNameOrigin>(
                rdata_str, rdata_rrsig, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <generic::RRSIG, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_rrsig, true, false);
    }

    const string rrsig_txt;
    const generic::RRSIG rdata_rrsig;
};

TEST_F(Rdata_RRSIG_Test, fromText) {
    EXPECT_EQ(rrsig_txt, rdata_rrsig.toText());
    EXPECT_EQ(isc::dns::RRType::A(), rdata_rrsig.typeCovered());

    // Missing signature is OK
    EXPECT_NO_THROW(const generic::RRSIG sig(
              "A 5 4 43200 20100223214617 20100222214617 8496 isc.org."));

    // Space in signature data is OK
    checkFromText_None(
              "A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
              "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz "
              "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/ "
              "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU "
              "f49t+sXKPzbipN9g+s1ZPiIyofc=");

    // Multi-line signature data is OK, if enclosed in parentheses
    checkFromText_None(
              "A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
              "( evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz\n"
              "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/\n"
              "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU\n"
              "f49t+sXKPzbipN9g+s1ZPiIyofc= )");

    // Trailing garbage. This should cause only the string constructor
    // to fail, but the lexer constructor must be able to continue
    // parsing from it.
    checkFromText_BadString(
              "A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
              "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
              "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
              "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
              "f49t+sXKPzbipN9g+s1ZPiIyofc= ; comment\n"
              "A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
              "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
              "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
              "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
              "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_missingFields) {
    checkFromText_LexerError("A");
    checkFromText_LexerError("A 5");
    checkFromText_LexerError("A 5 4");
    checkFromText_LexerError("A 5 4 43200");
    checkFromText_LexerError("A 5 4 43200 20100223214617");
    checkFromText_LexerError("A 5 4 43200 20100223214617 20100222214617");
    checkFromText_LexerError("A 5 4 43200 20100223214617 20100222214617 "
                              "8496");
}

TEST_F(Rdata_RRSIG_Test, badText_coveredType) {
    checkFromText_InvalidType("SPORK");
}

TEST_F(Rdata_RRSIG_Test, badText_algorithm) {
    checkFromText_InvalidText(
                     "A 555 4 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
    checkFromText_LexerError(
                     "A FIVE 4 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_labels) {
    checkFromText_InvalidText(
                     "A 5 4444 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
    checkFromText_LexerError(
                     "A 5 FOUR 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_ttl) {
    checkFromText_LexerError(
                     "A 5 4 999999999999 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
    checkFromText_LexerError(
                     "A 5 4 TTL "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");

    // alternate form of TTL is not okay
    checkFromText_LexerError(
              "A 5 4 12H 20100223214617 20100222214617 8496 isc.org. "
              "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz "
              "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/ "
              "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU "
              "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_expiration) {
    checkFromText_InvalidTime(
                     "A 5 4 43200 "
                     "201002232 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
    checkFromText_InvalidTime(
                     "A 5 4 43200 "
                     "EXPIRATION 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_inception) {
    checkFromText_InvalidTime(
                     "A 5 4 43200 "
                     "20100223214617 20100227 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
    checkFromText_InvalidTime(
                     "A 5 4 43200 "
                     "20100223214617 INCEPTION 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_keytag) {
    checkFromText_InvalidText(
                     "A 5 4 43200 "
                     "20100223214617 20100222214617 999999 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
    checkFromText_LexerError(
                     "A 5 4 43200 "
                     "20100223214617 20100222214617 TAG isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_signer) {
    checkFromText_MissingOrigin(
                     "A 5 4 43200 "
                     "20100223214617 20100222214617 8496 isc.org "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, badText_signature) {
    checkFromText_BadValue(
                     "A 5 4 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "EEeeeeeeEEEeeeeeeGaaahAAAAAAAAHHHHHHHHHHH!=");

    // no space between the tag and signer
    checkFromText_LexerError(
                     "A 5 4 43200 20100223214617 20100222214617 "
                     "8496isc.org. ofc=");

    // unterminated multi-line base64
    checkFromText_LexerError(
              "A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
              "( evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz\n"
              "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/\n"
              "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU\n"
              "f49t+sXKPzbipN9g+s1ZPiIyofc=");
}

TEST_F(Rdata_RRSIG_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_rrsig.compare(
        *test::createRdataUsingLexer(RRType::RRSIG(), RRClass::IN(),
                                     rrsig_txt)));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::RRSIG(), RRClass::IN(),
                                             "INVALIDINPUT"));
}

TEST_F(Rdata_RRSIG_Test, toWireRenderer) {
    rdata_rrsig.toWire(renderer);

    matchWireData(wiredata_rrsig, sizeof(wiredata_rrsig),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_RRSIG_Test, toWireBuffer) {
    rdata_rrsig.toWire(obuffer);

    matchWireData(wiredata_rrsig, sizeof(wiredata_rrsig),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_RRSIG_Test, createFromWire) {
    const string rrsig_txt2(
        "A 5 2 43200 20100327070149 20100225070149 2658 isc.org. "
        "HkJk/xZTvzePU8NENl/ley8bbUumhk1hXciyqhLnz1VQFzkDooej6neX"
        "ZgWZzQKeTKPOYWrnYtdZW4PnPQFeUl3orgLev7F8J6FZlDn0y/J/ThR5"
        "m36Mo2/Gdxjj8lJ/IjPVkdpKyBpcnYND8KEIma5MyNCNeyO1UkfPQZGHNSQ=");
    EXPECT_EQ(rrsig_txt2,
              rdataFactoryFromFile(RRType("RRSIG"), RRClass("IN"),
                                   "rdata_rrsig_fromWire1")->toText());
    const generic::RRSIG rdata_rrsig2(rrsig_txt2);
    EXPECT_EQ(0, rdata_rrsig2.compare(
                      *rdataFactoryFromFile(RRType("RRSIG"), RRClass("IN"),
                                          "rdata_rrsig_fromWire1")));

    // RDLEN is too short
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::RRSIG(), RRClass::IN(),
                                           "rdata_rrsig_fromWire2.wire"),
                      InvalidRdataLength, "RRSIG too short");
}
}
