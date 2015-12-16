// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_SRV_Test : public RdataTest {
public:
    Rdata_SRV_Test() :
        srv_txt("1 5 1500 a.example.com."),
        srv_txt2("1 5 1400 example.com."),
        too_long_label("012345678901234567890123456789"
                       "0123456789012345678901234567890123."),
        rdata_srv(srv_txt),
        rdata_srv2(srv_txt2)
    {}

    const string srv_txt;
    const string srv_txt2;
    const string too_long_label;
    const in::SRV rdata_srv;
    const in::SRV rdata_srv2;
};

// 1 5 1500 a.example.com.
const uint8_t wiredata_srv[] = {
    0x00, 0x01, 0x00, 0x05, 0x05, 0xdc, 0x01, 0x61, 0x07, 0x65, 0x78,
    0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00};
// 1 5 1400 example.com.
const uint8_t wiredata_srv2[] = {
    0x00, 0x01, 0x00, 0x05, 0x05, 0x78, 0x07, 0x65, 0x78, 0x61, 0x6d,
    0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00};

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
    // Extra text at end of line
    EXPECT_THROW(in::SRV("1 5 1500 a.example.com. extra."), InvalidRdataText);
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

    // test::createRdataUsingLexer() constructs relative to
    // "example.org." origin.
    EXPECT_EQ(0, in::SRV("1 5 1500 server16.example.org.").compare(
        *test::createRdataUsingLexer(RRType::SRV(), RRClass::IN(),
                                     "1 5 1500 server16")));

    // Exceptions cause NULL to be returned.

    // Bad priority
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::SRV(), RRClass::IN(),
                                             "65536 5 1500 "
                                             "a.example.com."));
    // Bad weight
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::SRV(), RRClass::IN(),
                                             "1 65536 1500 "
                                             "a.example.com."));
    // Bad port
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::SRV(), RRClass::IN(),
                                             "1 5 281474976710656 "
                                             "a.example.com."));
    // Extra text at end of line
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::SRV(), RRClass::IN(),
                                             "1 5 1500 a.example.com. extra."));
}

TEST_F(Rdata_SRV_Test, toWireBuffer) {
    rdata_srv.toWire(obuffer);
    matchWireData(wiredata_srv, sizeof(wiredata_srv),
                  obuffer.getData(), obuffer.getLength());

    obuffer.clear();
    rdata_srv2.toWire(obuffer);
    matchWireData(wiredata_srv2, sizeof(wiredata_srv2),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_SRV_Test, toWireRenderer) {
    rdata_srv.toWire(renderer);
    matchWireData(wiredata_srv, sizeof(wiredata_srv),
                  renderer.getData(), renderer.getLength());

    renderer.clear();
    rdata_srv2.toWire(renderer);
    matchWireData(wiredata_srv2, sizeof(wiredata_srv2),
                  renderer.getData(), renderer.getLength());
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
