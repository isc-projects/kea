// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for generic
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

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {
class Rdata_MINFO_Test : public RdataTest {
    // there's nothing to specialize
};

// minfo text
string minfo_txt("root.example.com. emailbx.example.com.");
string minfo_txt2("rmailbx.example.com. emailbx.example.com.");
string too_long_label("012345678901234567890123456789"
    "0123456789012345678901234567890123");

// root.example.com. emailbx.example.com.
const uint8_t uncompressed_wiredata_minfo[] = {
    0x04, 0x72, 0x6f, 0x6f, 0x74, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70,
    0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x07, 0x65, 0x6d, 0x61,
    0x69, 0x6c, 0x62, 0x78, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c,
    0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00};
// rmailbx.example.com. emailbx.example.com.
const uint8_t uncompressed_wiredata_minfo2[] = {
    0x07, 0x72, 0x6d, 0x61, 0x69, 0x6c, 0x62, 0x78, 0x07, 0x65, 0x78,
    0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x07,
    0x65, 0x6d, 0x61, 0x69, 0x6c, 0x62, 0x78, 0x07, 0x65, 0x78, 0x61,
    0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00};

// root.example.com. emailbx.example.com.
const uint8_t compressed_wiredata_minfo[] = {
    0x04, 0x72, 0x6f, 0x6f, 0x74, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70,
    0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x07, 0x65, 0x6d, 0x61,
    0x69, 0x6c, 0x62, 0x78, 0xc0, 0x05};
// rmailbx.example.com. emailbx.example.com.
const uint8_t compressed_wiredata_minfo2[] = {
    0x07, 0x72, 0x6d, 0x61, 0x69, 0x6c, 0x62, 0x78, 0x07, 0x65, 0x78,
    0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x07,
    0x65, 0x6d, 0x61, 0x69, 0x6c, 0x62, 0x78, 0xc0, 0x08};

const generic::MINFO rdata_minfo(minfo_txt);
const generic::MINFO rdata_minfo2(minfo_txt2);

TEST_F(Rdata_MINFO_Test, createFromText) {
    EXPECT_EQ(Name("root.example.com."), rdata_minfo.getRmailbox());
    EXPECT_EQ(Name("emailbx.example.com."), rdata_minfo.getEmailbox());
}

TEST_F(Rdata_MINFO_Test, badText) {
    // incomplete text
    EXPECT_THROW(generic::MINFO("root.example.com."),
                 InvalidRdataText);
    // bad name
    EXPECT_THROW(generic::MINFO("root.example.com. emailbx.example.com." +
                                too_long_label),
                 TooLongLabel);
}

TEST_F(Rdata_MINFO_Test, createFromWire) {
    // compressed emailbx name
    EXPECT_EQ(0, rdata_minfo.compare(
                  *rdataFactoryFromFile(RRType("MINFO"), RRClass("IN"),
                                        "rdata_minfo_fromWire")));
    // compressed rmailbx and emailbx name
    EXPECT_EQ(0, rdata_minfo.compare(
                  *rdataFactoryFromFile(RRType("MINFO"), RRClass("IN"),
                                        "rdata_minfo_fromWire", 30)));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType("MINFO"), RRClass("IN"),
                                      "rdata_minfo_fromWire", 36),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType("MINFO"), RRClass("IN"),
                                      "rdata_minfo_fromWire", 42),
                 InvalidRdataLength);
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType("MINFO"), RRClass("IN"),
                                      "rdata_cname_fromWire", 48),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_MINFO_Test, toWireBuffer) {
    rdata_minfo.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        uncompressed_wiredata_minfo,
                        sizeof(uncompressed_wiredata_minfo));
    obuffer.clear();
    rdata_minfo2.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        uncompressed_wiredata_minfo2,
                        sizeof(uncompressed_wiredata_minfo2));
}

TEST_F(Rdata_MINFO_Test, toWireRenderer) {
    rdata_minfo.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        compressed_wiredata_minfo,
                        sizeof(compressed_wiredata_minfo));
    renderer.clear();
    rdata_minfo2.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        compressed_wiredata_minfo2,
                        sizeof(compressed_wiredata_minfo2));
}

TEST_F(Rdata_MINFO_Test, toText) {
    EXPECT_EQ(minfo_txt, rdata_minfo.toText());
    EXPECT_EQ(minfo_txt2, rdata_minfo2.toText());
}

TEST_F(Rdata_MINFO_Test, compare) {
    // check reflexivity
    EXPECT_EQ(0, rdata_minfo.compare(rdata_minfo));

    // names must be compared in case-insensitive manner
    EXPECT_EQ(0, rdata_minfo.compare(generic::MINFO("ROOT.example.com. "
                                                  "emailbx.EXAMPLE.com.")));

    // another MINFO whose rmailbox name is larger than that of rdata_minfo.
    const generic::MINFO large1_minfo("zzzz.example.com. "
                                      "emailbox.example.com.");
    EXPECT_GT(0, rdata_minfo.compare(large1_minfo));
    EXPECT_LT(0, large1_minfo.compare(rdata_minfo));

    // another MINFO whose emailbox name is larger than that of rdata_minfo.
    const generic::MINFO large2_minfo("root.example.com. "
                                      "zzzzzzz.example.com.");
    EXPECT_GT(0, rdata_minfo.compare(large2_minfo));
    EXPECT_LT(0, large2_minfo.compare(rdata_minfo));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_minfo.compare(*RdataTest::rdata_nomatch), bad_cast);
}
}
