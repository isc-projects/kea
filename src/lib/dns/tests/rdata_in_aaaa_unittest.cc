// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
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
class Rdata_IN_AAAA_Test : public RdataTest {
protected:
    Rdata_IN_AAAA_Test() : rdata_in_aaaa("2001:db8::1234") {}

    // Common check to see the result of in::A Rdata construction either from
    // std::string or with MasterLexer object.  If it's expected to succeed
    // the result should be identical to the commonly used test data
    // (rdata_in_a); otherwise it should result in the exception specified as
    // the template parameter.
    void checkFromTextIN_AAAA(const string& in_aaaa_txt,
                              bool throw_str_version = true,
                              bool throw_lexer_version = true)
    {
        checkFromText<in::AAAA, InvalidRdataText, InvalidRdataText>(
            in_aaaa_txt, rdata_in_aaaa, throw_str_version,
            throw_lexer_version);
    }

    const in::AAAA rdata_in_aaaa;
};

const uint8_t wiredata_in_aaaa[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x12, 0x34 };

TEST_F(Rdata_IN_AAAA_Test, createFromText) {
    // Normal case: no exception for either case, so the exception type
    // doesn't matter.
    checkFromText<in::AAAA, isc::Exception, isc::Exception>(
        "2001:db8::1234", rdata_in_aaaa, false, false);

    // should reject an IP4 address.
    checkFromTextIN_AAAA("192.0.2.1");
    // or any meaningless text as an IPv6 address
    checkFromTextIN_AAAA("xxx");

    // trailing white space: only string version throws
    checkFromTextIN_AAAA("2001:db8::1234  ", true, false);
    // same for beginning white space.
    checkFromTextIN_AAAA("  2001:db8::1234", true, false);
    // same for trailing non-space garbage (note that lexer version still
    // ignore it; it's expected to be detected at a higher layer).
    checkFromTextIN_AAAA("2001:db8::1234 xxx", true, false);

    // nul character after a valid textual representation.
    string nul_after_addr = "2001:db8::1234";
    nul_after_addr.push_back(0);
    checkFromTextIN_AAAA(nul_after_addr, true, true);

    // a valid address surrounded by parentheses; only okay with lexer
    checkFromTextIN_AAAA("(2001:db8::1234)", true, false);

    // input that would cause lexer-specific error; it's bad text as an
    // address so should result in the string version, too.
    checkFromText<in::AAAA, InvalidRdataText, MasterLexer::LexerError>(
        ")2001:db8::1234", rdata_in_aaaa);
}

TEST_F(Rdata_IN_AAAA_Test, createFromWire) {
    // Valid data
    EXPECT_EQ(0, rdata_in_aaaa.compare(
                  *rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                        "rdata_in_aaaa_fromWire")));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                      "rdata_in_aaaa_fromWire", 18),
                 DNSMessageFORMERR);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                      "rdata_in_aaaa_fromWire", 36),
                 DNSMessageFORMERR);
    // buffer too short.
    EXPECT_THROW(rdataFactoryFromFile(RRType::AAAA(), RRClass::IN(),
                                      "rdata_in_aaaa_fromWire", 55),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_IN_AAAA_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_in_aaaa.compare(
        *test::createRdataUsingLexer(RRType::AAAA(), RRClass::IN(),
                                     "2001:db8::1234")));
}

TEST_F(Rdata_IN_AAAA_Test, toWireBuffer) {
    rdata_in_aaaa.toWire(obuffer);
    matchWireData(wiredata_in_aaaa, sizeof (wiredata_in_aaaa),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_IN_AAAA_Test, toWireRenderer) {
    rdata_in_aaaa.toWire(renderer);
    matchWireData(wiredata_in_aaaa, sizeof (wiredata_in_aaaa),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_IN_AAAA_Test, toText) {
    EXPECT_EQ("2001:db8::1234", rdata_in_aaaa.toText());
}

TEST_F(Rdata_IN_AAAA_Test, compare) {
    in::AAAA small1("::1");
    in::AAAA small2("1:2:3:4:5:6:7:8");
    in::AAAA large1("ffff::");
    in::AAAA large2("8:7:6:5:4:3:2:1");

    // trivial case: self equivalence
    // cppcheck-suppress uselessCallsCompare
    EXPECT_EQ(0, small1.compare(small1));

    // confirm these are compared as unsigned values
    EXPECT_GT(0, small1.compare(large1));
    EXPECT_LT(0, large1.compare(small1));

    // confirm these are compared in network byte order
    EXPECT_GT(0, small2.compare(large2));
    EXPECT_LT(0, large2.compare(small2));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_in_aaaa.compare(*RdataTest::rdata_nomatch), bad_cast); 
}
}
