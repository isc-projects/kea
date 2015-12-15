// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
using namespace isc::dns::rdata::generic;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_HINFO_Test : public RdataTest {
};

static uint8_t hinfo_rdata[] = {0x07,0x50,0x65,0x6e,0x74,0x69,0x75,0x6d,0x05,
    0x4c,0x69,0x6e,0x75,0x78};
static const char *hinfo_str = "\"Pentium\" \"Linux\"";
static const char *hinfo_str1 = "\"Pen\\\"tium\" \"Linux\"";

static const char *hinfo_str_equal = "\"Pentium\"\"Linux\"";
static const char *hinfo_str_small1 = "\"Lentium\" \"Linux\"";
static const char *hinfo_str_small2 = "\"Pentium\" \"Kinux\"";
static const char *hinfo_str_large1 = "\"Qentium\" \"Linux\"";
static const char *hinfo_str_large2 = "\"Pentium\" \"UNIX\"";

TEST_F(Rdata_HINFO_Test, createFromText) {
    HINFO hinfo(hinfo_str);
    EXPECT_EQ(string("Pentium"), hinfo.getCPU());
    EXPECT_EQ(string("Linux"), hinfo.getOS());
    // Test the text with double quotes in the middle of string
    HINFO hinfo1(hinfo_str1);
    EXPECT_EQ(string("Pen\\\"tium"), hinfo1.getCPU());
}

TEST_F(Rdata_HINFO_Test, badText) {
    // Only 2 fields must exist
    EXPECT_THROW(const HINFO hinfo("\"Pentium\"\"Linux\"\"Computer\""),
                 InvalidRdataText);
    EXPECT_THROW(const HINFO hinfo("\"Pentium\" \"Linux\" \"Computer\""),
                 InvalidRdataText);
    // Field cannot be missing
    EXPECT_THROW(const HINFO hinfo("Pentium"), InvalidRdataText);
    // The <character-string> cannot exceed 255 characters
    string hinfo_str;
    for (int i = 0; i < 257; ++i) {
        hinfo_str += 'A';
    }
    hinfo_str += " Linux";
    EXPECT_THROW(const HINFO hinfo(hinfo_str), CharStringTooLong);
}

TEST_F(Rdata_HINFO_Test, createFromWire) {
    InputBuffer input_buffer(hinfo_rdata, sizeof(hinfo_rdata));
    HINFO hinfo(input_buffer, sizeof(hinfo_rdata));
    EXPECT_EQ(string("Pentium"), hinfo.getCPU());
    EXPECT_EQ(string("Linux"), hinfo.getOS());
}

TEST_F(Rdata_HINFO_Test, createFromLexer) {
    HINFO rdata_hinfo(hinfo_str);
    EXPECT_EQ(0, rdata_hinfo.compare(
        *test::createRdataUsingLexer(RRType::HINFO(), RRClass::IN(),
                                     hinfo_str)));
    EXPECT_EQ(0, rdata_hinfo.compare(
        *test::createRdataUsingLexer(RRType::HINFO(), RRClass::IN(),
                                     "\"Pentium\"\"Linux\"")));
    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::HINFO(), RRClass::IN(),
                                             "\"Pentium\"\"Linux\""
                                             "\"Computer\""));
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::HINFO(), RRClass::IN(),
                                             "\"Pentium\" \"Linux\" "
                                             "\"Computer\""));
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::HINFO(), RRClass::IN(),
                                             "\"Pentium\""));
}

TEST_F(Rdata_HINFO_Test, toText) {
    HINFO hinfo(hinfo_str);
    EXPECT_EQ(hinfo_str, hinfo.toText());

    // will add quotes even if they were not in the original input
    EXPECT_EQ("\"a\" \"b\"", HINFO("a b").toText());
    // will not add additional quotes
    EXPECT_EQ("\"a\" \"b\"", HINFO("\"a\" \"b\"").toText());
    // And make sure escaped quotes and spaces are left intact
    EXPECT_EQ("\"a\\\"\" \"b c\"", HINFO("\"a\\\"\" \"b c\"").toText());
}

TEST_F(Rdata_HINFO_Test, toWire) {
    HINFO hinfo(hinfo_str);

    hinfo.toWire(obuffer);
    matchWireData(hinfo_rdata, sizeof (hinfo_rdata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_HINFO_Test, toWireRenderer) {
    HINFO hinfo(hinfo_str);

    hinfo.toWire(renderer);
    matchWireData(hinfo_rdata, sizeof (hinfo_rdata),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_HINFO_Test, compare) {
    HINFO hinfo(hinfo_str);
    HINFO hinfo_small1(hinfo_str_small1);
    HINFO hinfo_small2(hinfo_str_small2);
    HINFO hinfo_large1(hinfo_str_large1);
    HINFO hinfo_large2(hinfo_str_large2);

    EXPECT_EQ(0, hinfo.compare(HINFO(hinfo_str)));
    EXPECT_EQ(0, hinfo.compare(HINFO(hinfo_str_equal)));
    EXPECT_EQ(1, hinfo.compare(HINFO(hinfo_str_small1)));
    EXPECT_EQ(1, hinfo.compare(HINFO(hinfo_str_small2)));
    EXPECT_EQ(-1, hinfo.compare(HINFO(hinfo_str_large1)));
    EXPECT_EQ(-1, hinfo.compare(HINFO(hinfo_str_large2)));
}

// Copy/assign test
TEST_F(Rdata_HINFO_Test, copy) {
    HINFO hinfo(hinfo_str);
    HINFO hinfo2(hinfo);
    HINFO hinfo3 = hinfo;

    EXPECT_EQ(0, hinfo.compare(hinfo2));
    EXPECT_EQ(0, hinfo.compare(hinfo3));

    hinfo3 = hinfo;
    EXPECT_EQ(0, hinfo.compare(hinfo3));
}

}
