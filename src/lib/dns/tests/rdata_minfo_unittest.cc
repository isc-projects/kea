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

// minfo text
const char* const minfo_txt = "rmailbox.example.com. emailbox.example.com.";
const char* const minfo_txt2 = "root.example.com. emailbox.example.com.";
const char* const too_long_label = "01234567890123456789012345678901234567"
                                   "89012345678901234567890123";

namespace {
class Rdata_MINFO_Test : public RdataTest {
public:
    Rdata_MINFO_Test():
        rdata_minfo(string(minfo_txt)), rdata_minfo2(string(minfo_txt2)) {}

    const generic::MINFO rdata_minfo;
    const generic::MINFO rdata_minfo2;
};


TEST_F(Rdata_MINFO_Test, createFromText) {
    EXPECT_EQ(Name("rmailbox.example.com."), rdata_minfo.getRmailbox());
    EXPECT_EQ(Name("emailbox.example.com."), rdata_minfo.getEmailbox());

    EXPECT_EQ(Name("root.example.com."), rdata_minfo2.getRmailbox());
    EXPECT_EQ(Name("emailbox.example.com."), rdata_minfo2.getEmailbox());
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
    EXPECT_THROW(generic::MINFO("root.example.com. emailbox.example.com." +
                                string(too_long_label)),
                 TooLongLabel);
    // bad emailbox name
    EXPECT_THROW(generic::MINFO("root.example.com."  +
                          string(too_long_label) + " emailbox.example.com."),
                 TooLongLabel);
}

TEST_F(Rdata_MINFO_Test, createFromWire) {
    // uncompressed names
    EXPECT_EQ(0, rdata_minfo.compare(
                  *rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                     "rdata_minfo_fromWire1.wire")));
    // compressed names
    EXPECT_EQ(0, rdata_minfo.compare(
                  *rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                     "rdata_minfo_fromWire2.wire", 15)));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                     "rdata_minfo_fromWire3.wire"),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                      "rdata_minfo_fromWire4.wire"),
                 InvalidRdataLength);
    // bogus rmailbox name, the error should be detected in the name
    // constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                      "rdata_minfo_fromWire5.wire"),
                 DNSMessageFORMERR);
    // bogus emailbox name, the error should be detected in the name
    // constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                      "rdata_minfo_fromWire6.wire"),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_MINFO_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_minfo.compare(
        *test::createRdataUsingLexer(RRType::MINFO(), RRClass::IN(),
                                     minfo_txt)));
}

TEST_F(Rdata_MINFO_Test, assignment) {
    generic::MINFO copy((string(minfo_txt2)));
    copy = rdata_minfo;
    EXPECT_EQ(0, copy.compare(rdata_minfo));

    // Check if the copied data is valid even after the original is deleted
    generic::MINFO* copy2 = new generic::MINFO(rdata_minfo);
    generic::MINFO copy3((string(minfo_txt2)));
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_minfo));

    // Self assignment
    copy = copy;
    EXPECT_EQ(0, copy.compare(rdata_minfo));
}

TEST_F(Rdata_MINFO_Test, toWireBuffer) {
    rdata_minfo.toWire(obuffer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_minfo_toWireUncompressed1.wire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()),
                        obuffer.getLength(), &data[0], data.size());

    obuffer.clear();
    rdata_minfo2.toWire(obuffer);
    vector<unsigned char> data2;
    UnitTestUtil::readWireData("rdata_minfo_toWireUncompressed2.wire", data2);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()),
                        obuffer.getLength(), &data2[0], data2.size());
}

TEST_F(Rdata_MINFO_Test, toWireRenderer) {
    rdata_minfo.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_minfo_toWire1.wire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(renderer.getData()),
                        renderer.getLength(), &data[0], data.size());
    renderer.clear();
    rdata_minfo2.toWire(renderer);
    vector<unsigned char> data2;
    UnitTestUtil::readWireData("rdata_minfo_toWire2.wire", data2);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(renderer.getData()),
                        renderer.getLength(), &data2[0], data2.size());
}

TEST_F(Rdata_MINFO_Test, toText) {
    EXPECT_EQ(minfo_txt, rdata_minfo.toText());
    EXPECT_EQ(minfo_txt2, rdata_minfo2.toText());
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
