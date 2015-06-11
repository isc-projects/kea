// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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
using namespace isc::dns::rdata::generic;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_NAPTR_Test : public RdataTest {
};

// 10 100 "S" "SIP+D2U" "" _sip._udp.example.com.
static uint8_t naptr_rdata[] = {0x00,0x0a,0x00,0x64,0x01,0x53,0x07,0x53,0x49,
    0x50,0x2b,0x44,0x32,0x55,0x00,0x04,0x5f,0x73,0x69,0x70,0x04,0x5f,0x75,0x64,
    0x70,0x07,0x65,0x78,0x61,0x6d,0x70,0x6c,0x65,0x03,0x63,0x6f,0x6d,0x00};

static const char *naptr_str =
    "10 100 \"S\" \"SIP+D2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str2 =
    "10 100 S SIP+D2U \"\" _sip._udp.example.com.";

static const char *naptr_str_small1 =
    "9 100 \"S\" \"SIP+D2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_small2 =
    "10 90 \"S\" \"SIP+D2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_small3 =
    "10 100 \"R\" \"SIP+D2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_small4 =
    "10 100 \"S\" \"SIP+C2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_small5 =
    "10 100 \"S\" \"SIP+D2U\" \"\" _rip._udp.example.com.";

static const char *naptr_str_large1 =
    "11 100 \"S\" \"SIP+D2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_large2 =
    "10 110 \"S\" \"SIP+D2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_large3 =
    "10 100 \"T\" \"SIP+D2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_large4 =
    "10 100 \"S\" \"SIP+E2U\" \"\" _sip._udp.example.com.";
static const char *naptr_str_large5 =
    "10 100 \"S\" \"SIP+D2U\" \"\" _tip._udp.example.com.";

TEST_F(Rdata_NAPTR_Test, createFromText) {
    NAPTR naptr(naptr_str);
    EXPECT_EQ(10, naptr.getOrder());
    EXPECT_EQ(100, naptr.getPreference());
    EXPECT_EQ(string("S"), naptr.getFlags());
    EXPECT_EQ(string("SIP+D2U"), naptr.getServices());
    EXPECT_EQ(string(""), naptr.getRegexp());
    EXPECT_EQ(Name("_sip._udp.example.com."), naptr.getReplacement());

    // Test <char-string> that separated by space
    NAPTR naptr2(naptr_str2);
    EXPECT_EQ(string("S"), naptr2.getFlags());
    EXPECT_EQ(string("SIP+D2U"), naptr2.getServices());
}

TEST_F(Rdata_NAPTR_Test, badText) {
    // Order number cannot exceed 65535
    EXPECT_THROW_WITH(const NAPTR naptr(
                        "65536 10 S SIP \"\" _sip._udp.example.com."),
                      InvalidRdataText,
                      "Invalid NAPTR text format: order out of range: 65536");
    // Preference number cannot exceed 65535
    EXPECT_THROW_WITH(const NAPTR naptr(
                         "100 65536 S SIP \"\" _sip._udp.example.com."),
                      InvalidRdataText,
                      "Invalid NAPTR text format: "
                      "preference out of range: 65536");
    // No regexp given
    EXPECT_THROW_WITH(const NAPTR naptr("100 10 S SIP _sip._udp.example.com."),
                      InvalidRdataText,
                      "Failed to construct NAPTR RDATA from "
                      "100 10 S SIP _sip._udp.example.com.': "
                      "unexpected end of input");
    // The double quotes seperator must match
    EXPECT_THROW_WITH(const NAPTR naptr(
                        "100 10 \"S SIP \"\" _sip._udp.example.com."),
                      InvalidRdataText,
                      "Failed to construct NAPTR RDATA from "
                      "100 10 \"S SIP \"\" _sip._udp.example.com.': "
                      "unexpected end of input");
    // Order or preference cannot be missed
    EXPECT_THROW_WITH(const NAPTR naptr(
                        "10 \"S\" SIP \"\" _sip._udp.example.com."),
                      InvalidRdataText,
                      "Failed to construct NAPTR RDATA from "
                      "10 \"S\" SIP \"\" _sip._udp.example.com.': "
                      "unexpected quotes");
    // Unquoted fields must be seperated by spaces
    EXPECT_THROW_WITH(const NAPTR naptr(
                        "100 10S SIP \"\" _sip._udp.example.com."),
                      InvalidRdataText,
                      "Failed to construct NAPTR RDATA from "
                      "100 10S SIP \"\" _sip._udp.example.com.': "
                      "not a valid number");
    EXPECT_THROW_WITH(const NAPTR naptr(
                        "10010 \"S\" \"SIP\" \"\" _sip._udp.example.com."),
                      InvalidRdataText,
                      "Failed to construct NAPTR RDATA from "
                      "10010 \"S\" \"SIP\" \"\" _sip._udp.example.com.': "
                      "unexpected quotes");
    EXPECT_THROW_WITH(const NAPTR naptr(
                        "100 10 SSIP \"\" _sip._udp.example.com."),
                      InvalidRdataText,
                      "Failed to construct NAPTR RDATA from "
                      "100 10 SSIP \"\" _sip._udp.example.com.': "
                      "unexpected end of input");
    // Field cannot be missing
    EXPECT_THROW_WITH(const NAPTR naptr("100 10 \"S\""), InvalidRdataText,
                      "Failed to construct NAPTR RDATA from 100 10 \"S\"': "
                      "unexpected end of input");

    // The <character-string> cannot exceed 255 characters
    string naptr_str;
    naptr_str += "100 10 ";
    for (int i = 0; i < 257; ++i) {
        naptr_str += 'A';
    }
    naptr_str += " SIP \"\" _sip._udp.example.com.";
    EXPECT_THROW_WITH(const NAPTR naptr(naptr_str), CharStringTooLong,
                      "character-string is too long: 257(+1) characters");
}

TEST_F(Rdata_NAPTR_Test, createFromWire) {
    InputBuffer input_buffer(naptr_rdata, sizeof(naptr_rdata));
    NAPTR naptr(input_buffer, sizeof(naptr_rdata));
    EXPECT_EQ(10, naptr.getOrder());
    EXPECT_EQ(100, naptr.getPreference());
    EXPECT_EQ(string("S"), naptr.getFlags());
    EXPECT_EQ(string("SIP+D2U"), naptr.getServices());
    EXPECT_EQ(string(""), naptr.getRegexp());
    EXPECT_EQ(Name("_sip._udp.example.com."), naptr.getReplacement());
}

TEST_F(Rdata_NAPTR_Test, createFromWireTooLongDataLen) {
    static uint8_t naptr_rdata_long[] = {
    0x00,0x0a,0x00,0x64,0x01,0x53,0x07,0x53,0x49,0x50,0x2b,0x44,0x32,0x55,
    0x00,0x04,0x5f,0x73,0x69,0x70,0x04,0x5f,0x75,0x64,0x70,0x07,0x65,0x78,
    0x61,0x6d,0x70,0x6c,0x65,0x03,0x63,0x6f,0x6d,0x00,0xff,0xff,0xff,0xff};
    InputBuffer input_buffer(naptr_rdata_long, sizeof(naptr_rdata_long));
    EXPECT_THROW(NAPTR naptr(input_buffer, sizeof(naptr_rdata_long)),
                 isc::dns::DNSMessageFORMERR);
}

TEST_F(Rdata_NAPTR_Test, createFromWireTooShortDataLen) {
    // missing data (just set rdata_len too low)
    for (size_t i = 0; i < sizeof(naptr_rdata); ++i) {
        // Just use existing correct buffer but set rdata_len too low
        InputBuffer input_buffer(naptr_rdata, sizeof(naptr_rdata));
        EXPECT_THROW(NAPTR naptr(input_buffer, i),
                     isc::dns::DNSMessageFORMERR);
    }
}

TEST_F(Rdata_NAPTR_Test, createFromLexer) {
    const NAPTR rdata_naptr(naptr_str);

    EXPECT_EQ(0, rdata_naptr.compare(
        *test::createRdataUsingLexer(RRType::NAPTR(), RRClass::IN(),
                                     naptr_str)));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::NAPTR(), RRClass::IN(),
                                             "65536 10 S SIP \"\" "
                                             "_sip._udp.example.com."));
}

TEST_F(Rdata_NAPTR_Test, toWire) {
    NAPTR naptr(naptr_str);

    naptr.toWire(obuffer);
    matchWireData(naptr_rdata, sizeof(naptr_rdata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_NAPTR_Test, toWireRenderer) {
    NAPTR naptr(naptr_str);

    naptr.toWire(renderer);
    matchWireData(naptr_rdata, sizeof(naptr_rdata),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_NAPTR_Test, toText) {
    NAPTR naptr(naptr_str);
    EXPECT_EQ(naptr_str, naptr.toText());

    // will add quotes even if they were not in the original input
    EXPECT_EQ("10 100 \"S\" \"SIP+D2U\" \".*\" _sip._udp.example.com.",
              NAPTR("10 100 S SIP+D2U .* _sip._udp.example.com.").toText());
    // will not add additional quotes
    EXPECT_EQ("10 100 \"S\" \"SIP+D2U\" \".*\" _sip._udp.example.com.",
              NAPTR("10 100 \"S\" \"SIP+D2U\" \".*\" _sip._udp.example.com.")
                .toText());
}

TEST_F(Rdata_NAPTR_Test, compare) {
    NAPTR naptr(naptr_str);
    NAPTR naptr_small1(naptr_str_small1);
    NAPTR naptr_small2(naptr_str_small2);
    NAPTR naptr_small3(naptr_str_small3);
    NAPTR naptr_small4(naptr_str_small4);
    NAPTR naptr_small5(naptr_str_small5);
    NAPTR naptr_large1(naptr_str_large1);
    NAPTR naptr_large2(naptr_str_large2);
    NAPTR naptr_large3(naptr_str_large3);
    NAPTR naptr_large4(naptr_str_large4);
    NAPTR naptr_large5(naptr_str_large5);

    EXPECT_EQ(0, naptr.compare(NAPTR(naptr_str)));
    EXPECT_EQ(1, naptr.compare(naptr_small1));
    EXPECT_EQ(1, naptr.compare(naptr_small2));
    EXPECT_EQ(1, naptr.compare(naptr_small3));
    EXPECT_EQ(1, naptr.compare(naptr_small4));
    EXPECT_EQ(1, naptr.compare(naptr_small5));
    EXPECT_EQ(-1, naptr.compare(naptr_large1));
    EXPECT_EQ(-1, naptr.compare(naptr_large2));
    EXPECT_EQ(-1, naptr.compare(naptr_large3));
    EXPECT_EQ(-1, naptr.compare(naptr_large4));
    EXPECT_EQ(-1, naptr.compare(naptr_large5));
    EXPECT_EQ(-1, naptr_small1.compare(naptr));
    EXPECT_EQ(-1, naptr_small2.compare(naptr));
    EXPECT_EQ(-1, naptr_small3.compare(naptr));
    EXPECT_EQ(-1, naptr_small4.compare(naptr));
    EXPECT_EQ(-1, naptr_small5.compare(naptr));
    EXPECT_EQ(1, naptr_large1.compare(naptr));
    EXPECT_EQ(1, naptr_large2.compare(naptr));
    EXPECT_EQ(1, naptr_large3.compare(naptr));
    EXPECT_EQ(1, naptr_large4.compare(naptr));
    EXPECT_EQ(1, naptr_large5.compare(naptr));
}

TEST_F(Rdata_NAPTR_Test, copy) {
    NAPTR naptr(naptr_str);
    NAPTR naptr2(naptr);
    NAPTR naptr3 = naptr;

    EXPECT_EQ(0, naptr.compare(naptr2));
    EXPECT_EQ(0, naptr.compare(naptr3));

    naptr3 = naptr;
    EXPECT_EQ(0, naptr.compare(naptr3));
}

}
