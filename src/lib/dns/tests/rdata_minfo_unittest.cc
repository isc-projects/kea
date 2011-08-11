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
const char* const minfo_txt = "rmailbox.example.com. emailbox.example.com.";
const char* const too_long_label = "01234567890123456789012345678901234567"
                                   "89012345678901234567890123";

const generic::MINFO rdata_minfo((string(minfo_txt)));

TEST_F(Rdata_MINFO_Test, createFromText) {
    EXPECT_EQ(Name("rmailbox.example.com."), rdata_minfo.getRmailbox());
    EXPECT_EQ(Name("emailbox.example.com."), rdata_minfo.getEmailbox());
}

TEST_F(Rdata_MINFO_Test, badText) {
    // incomplete text
    EXPECT_THROW(generic::MINFO("root.example.com."),
                 InvalidRdataText);
    // number of fields (must be 2) is incorrect
    EXPECT_THROW(generic::MINFO("root.example.com emailbox.example.com. "
                                "example.com."),
                 InvalidRdataText);
    // bad rmailbox name
    EXPECT_THROW(generic::MINFO("root.example.com. emailbx.example.com." +
                                string(too_long_label)),
                 TooLongLabel);
    // bad emailbox name
    EXPECT_THROW(generic::MINFO("root.example.com."  +
                          string(too_long_label) + " emailbx.example.com."),
                 TooLongLabel);
}

TEST_F(Rdata_MINFO_Test, createFromWire) {
    // compressed emailbx name
    EXPECT_EQ(0, rdata_minfo.compare(
                  *rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                        "rdata_minfo_fromWire")));
    // compressed rmailbx and emailbx name
    EXPECT_EQ(0, rdata_minfo.compare(
                  *rdataFactoryFromFile(RRType("MINFO"), RRClass::IN(),
                                        "rdata_minfo_fromWire", 35)));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                      "rdata_minfo_fromWire", 41),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                      "rdata_minfo_fromWire", 47),
                 InvalidRdataLength);
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType("MINFO"), RRClass::IN(),
                                      "rdata_minfo_fromWire", 53),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_MINFO_Test, toWireBuffer) {
    obuffer.skip(2);
    rdata_minfo.toWire(obuffer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_minfo_toWireUncompressed.wire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_MINFO_Test, toWireRenderer) {
    obuffer.skip(2);
    rdata_minfo.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_minfo_toWire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_MINFO_Test, toText) {
    EXPECT_EQ(minfo_txt, rdata_minfo.toText());
}

TEST_F(Rdata_MINFO_Test, compare) {
    // check reflexivity
    EXPECT_EQ(0, rdata_minfo.compare(rdata_minfo));

    // names must be compared in case-insensitive manner
    EXPECT_EQ(0, rdata_minfo.compare(generic::MINFO("RMAILBOX.example.com. "
                                                  "emailbox.EXAMPLE.com.")));

    // another MINFO whose rmailbox name is larger than that of rdata_minfo.
    const generic::MINFO large1_minfo("zzzzzzzz.example.com. "
                                      "emailbox.example.com.");
    EXPECT_GT(0, rdata_minfo.compare(large1_minfo));
    EXPECT_LT(0, large1_minfo.compare(rdata_minfo));

    // another MINFO whose emailbox name is larger than that of rdata_minfo.
    const generic::MINFO large2_minfo("rmailbox.example.com. "
                                      "zzzzzzzzzzz.example.com.");
    EXPECT_GT(0, rdata_minfo.compare(large2_minfo));
    EXPECT_LT(0, large2_minfo.compare(rdata_minfo));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_minfo.compare(*RdataTest::rdata_nomatch), bad_cast);
}
}
