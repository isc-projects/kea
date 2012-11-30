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
class Rdata_SRV_Test : public RdataTest {
    // there's nothing to specialize
};

string srv_txt("1 5 1500 a.example.com.");
string srv_txt2("1 5 1400 example.com.");
string too_long_label("012345678901234567890123456789"
    "0123456789012345678901234567890123");

// 1 5 1500 a.example.com.
const uint8_t wiredata_srv[] = {
    0x00, 0x01, 0x00, 0x05, 0x05, 0xdc, 0x01, 0x61, 0x07, 0x65, 0x78,
    0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00};
// 1 5 1400 example.com.
const uint8_t wiredata_srv2[] = {
    0x00, 0x01, 0x00, 0x05, 0x05, 0x78, 0x07, 0x65, 0x78, 0x61, 0x6d,
    0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00};

const in::SRV rdata_srv(srv_txt);
const in::SRV rdata_srv2(srv_txt2);

TEST_F(Rdata_SRV_Test, createFromText) {
    EXPECT_EQ(1, rdata_srv.getPriority());
    EXPECT_EQ(5, rdata_srv.getWeight());
    EXPECT_EQ(1500, rdata_srv.getPort());
    EXPECT_EQ(Name("a.example.com."), rdata_srv.getTarget());
}

TEST_F(Rdata_SRV_Test, badText) {
    // priority is too large (2814...6 is 2^48)
    EXPECT_THROW(in::SRV("281474976710656 5 1500 a.example.com."),
                 InvalidRdataText);
    // weight is too large
    EXPECT_THROW(in::SRV("1 281474976710656 1500 a.example.com."),
                 InvalidRdataText);
    // port is too large
    EXPECT_THROW(in::SRV("1 5 281474976710656 a.example.com."),
                 InvalidRdataText);
    // incomplete text
    EXPECT_THROW(in::SRV("1 5 a.example.com."),
                 InvalidRdataText);
    EXPECT_THROW(in::SRV("1 5 1500a.example.com."),
                 InvalidRdataText);
    // bad name
    EXPECT_THROW(in::SRV("1 5 1500 a.example.com." + too_long_label),
                 TooLongLabel);
}

TEST_F(Rdata_SRV_Test, assignment) {
    in::SRV copy((string(srv_txt2)));
    copy = rdata_srv;
    EXPECT_EQ(0, copy.compare(rdata_srv));

    // Check if the copied data is valid even after the original is deleted
    in::SRV* copy2 = new in::SRV(rdata_srv);
    in::SRV copy3((string(srv_txt2)));
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_srv));

    // Self assignment
    copy = copy;
    EXPECT_EQ(0, copy.compare(rdata_srv));
}

TEST_F(Rdata_SRV_Test, createFromWire) {
    EXPECT_EQ(0, rdata_srv.compare(
                  *rdataFactoryFromFile(RRType("SRV"), RRClass("IN"),
                                        "rdata_srv_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType("SRV"), RRClass("IN"),
                                      "rdata_srv_fromWire", 23),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType("SRV"), RRClass("IN"),
                                      "rdata_srv_fromWire", 46),
                 InvalidRdataLength);
    // incomplete name.  the error should be detected in the name constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType("SRV"), RRClass("IN"),
                                      "rdata_cname_fromWire", 69),
                 DNSMessageFORMERR);
    // parse compressed target name
    EXPECT_EQ(0, rdata_srv.compare(
                  *rdataFactoryFromFile(RRType("SRV"), RRClass("IN"),
                                      "rdata_srv_fromWire", 89)));
}

TEST_F(Rdata_SRV_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_srv.compare(
        *test::createRdataUsingLexer(RRType::SRV(), RRClass::IN(),
                                     "1 5 1500 a.example.com.")));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::SRV(), RRClass::IN(),
                                             "1 5 281474976710656 "
                                             "a.example.com."));
}

TEST_F(Rdata_SRV_Test, toWireBuffer) {
    rdata_srv.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_srv, sizeof(wiredata_srv));
    obuffer.clear();
    rdata_srv2.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_srv2, sizeof(wiredata_srv2));
}

TEST_F(Rdata_SRV_Test, toWireRenderer) {
    rdata_srv.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata_srv, sizeof(wiredata_srv));
    renderer.clear();
    rdata_srv2.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata_srv2, sizeof(wiredata_srv2));
}

TEST_F(Rdata_SRV_Test, toText) {
    EXPECT_EQ(srv_txt, rdata_srv.toText());
    EXPECT_EQ(srv_txt2, rdata_srv2.toText());
}

TEST_F(Rdata_SRV_Test, compare) {
    // test RDATAs, sorted in the ascendent order.
    vector<in::SRV> compare_set;
    compare_set.push_back(in::SRV("1 5 1500 a.example.com."));
    compare_set.push_back(in::SRV("2 5 1500 a.example.com."));
    compare_set.push_back(in::SRV("2 6 1500 a.example.com."));
    compare_set.push_back(in::SRV("2 6 1600 a.example.com."));
    compare_set.push_back(in::SRV("2 6 1600 example.com."));

    EXPECT_EQ(0, compare_set[0].compare(
                  in::SRV("1 5 1500 a.example.com.")));

    vector<in::SRV>::const_iterator it;
    vector<in::SRV>::const_iterator it_end = compare_set.end();
    for (it = compare_set.begin(); it != it_end - 1; ++it) {
        EXPECT_GT(0, (*it).compare(*(it + 1)));
        EXPECT_LT(0, (*(it + 1)).compare(*it));
    }

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_srv.compare(*RdataTest::rdata_nomatch), bad_cast);
}
}
