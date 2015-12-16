// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/rdataclass.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc::util;
using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_RP_Test : public RdataTest {
protected:
    Rdata_RP_Test() :
        mailbox_name("root.example.com."),
        text_name("rp-text.example.com."),
        // this also serves as a test for "from text" constructor in a normal
        // case.
        rdata_rp("root.example.com. rp-text.example.com."),
        obuffer(0)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::RP, isc::Exception, isc::Exception>(
            rdata_str, rdata_rp, false, false);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::RP, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_rp, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText<generic::RP, InvalidRdataText, isc::Exception>(
            rdata_str, rdata_rp, true, false);
    }

    void checkFromText_EmptyLabel(const string& rdata_str) {
        checkFromText<generic::RP, EmptyLabel, EmptyLabel>(
            rdata_str, rdata_rp, true, true);
    }

    void checkFromText_MissingOrigin(const string& rdata_str) {
        checkFromText
            <generic::RP, MissingNameOrigin, MissingNameOrigin>(
                rdata_str, rdata_rp, true, true);
    }

    void checkFromText_Origin(const string& rdata_str, const Name* origin) {
        checkFromText<generic::RP, MissingNameOrigin, isc::Exception>(
            rdata_str, rdata_rp, true, false, origin);
    }

    const Name mailbox_name, text_name;
    const generic::RP rdata_rp; // commonly used test RDATA
    OutputBuffer obuffer;
    MessageRenderer renderer;
    vector<uint8_t> expected_wire;
};

TEST_F(Rdata_RP_Test, createFromText) {
    EXPECT_EQ(mailbox_name, rdata_rp.getMailbox());
    EXPECT_EQ(text_name, rdata_rp.getText());

    checkFromText_None("root.example.com. rp-text.example.com.");

    // origin defined for lexer constructor, but not string constructor
    const Name origin("example.com");
    checkFromText_Origin("root rp-text", &origin);

    // lexer constructor accepts extra text, but string constructor doesn't
    checkFromText_BadString("root.example.com. rp-text.example.com. "
                            "extra.example.com.");
}

TEST_F(Rdata_RP_Test, badText) {
    // invalid names
    checkFromText_EmptyLabel("root..example.com. rp-text.example.com.");
    checkFromText_EmptyLabel("root.example.com. rp-text..example.com.");

    // missing field
    checkFromText_LexerError("root.example.com.");

    // missing origin
    checkFromText_MissingOrigin("root.example.com rp-text.example.com.");
    checkFromText_MissingOrigin("root.example.com. rp-text.example.com");
}

TEST_F(Rdata_RP_Test, createFromWire) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::RP(), RRClass::IN(),
                                        "rdata_rp_fromWire1.wire"));
    EXPECT_EQ(mailbox_name, dynamic_cast<generic::RP&>(*rdata).getMailbox());
    EXPECT_EQ(text_name, dynamic_cast<generic::RP&>(*rdata).getText());

    // a similar test with names being compressed
    rdata = rdataFactoryFromFile(RRType::RP(), RRClass::IN(),
                                 "rdata_rp_fromWire2.wire", 30);
    EXPECT_EQ(mailbox_name, dynamic_cast<generic::RP&>(*rdata).getMailbox());
    EXPECT_EQ(Name("rp-text.example.net"),
              dynamic_cast<generic::RP&>(*rdata).getText());
}

TEST_F(Rdata_RP_Test, badFromWire) {
    // RDLEN is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::RP(), RRClass::IN(),
                                      "rdata_rp_fromWire3.wire"),
                 InvalidRdataLength);

    // RDLEN is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType::RP(), RRClass::IN(),
                                      "rdata_rp_fromWire4.wire"),
                 InvalidRdataLength);

    // bogus mailbox name
    EXPECT_THROW(rdataFactoryFromFile(RRType::RP(), RRClass::IN(),
                                      "rdata_rp_fromWire5.wire"),
                 DNSMessageFORMERR);

    // bogus text name
    EXPECT_THROW(rdataFactoryFromFile(RRType::RP(), RRClass::IN(),
                                      "rdata_rp_fromWire6.wire"),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_RP_Test, createFromParams) {
    EXPECT_EQ(mailbox_name, generic::RP(mailbox_name, text_name).getMailbox());
    EXPECT_EQ(text_name, generic::RP(mailbox_name, text_name).getText());
}

TEST_F(Rdata_RP_Test, toWireBuffer) {
    // construct expected data
    UnitTestUtil::readWireData("rdata_rp_toWire1.wire", expected_wire);

    // construct actual data
    rdata_rp.toWire(obuffer);

    // then compare them
    matchWireData(&expected_wire[0], expected_wire.size(),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_RP_Test, toWireRenderer) {
    // similar to toWireBuffer, but names in RDATA could be compressed due to
    // preceding names.  Actually they must not be compressed according to
    // RFC3597, and this test checks that.

    UnitTestUtil::readWireData("rdata_rp_toWire2.wire", expected_wire);

    renderer.writeName(Name("a.example.com"));
    renderer.writeName(Name("b.example.net"));
    generic::RP(mailbox_name, Name("rp-text.example.net")).toWire(renderer);
    matchWireData(&expected_wire[0], expected_wire.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_RP_Test, toText) {
    // there's not much to test for this method.  Only checking a simple case.
    EXPECT_EQ("root.example.com. rp-text.example.com.", rdata_rp.toText());
}

TEST_F(Rdata_RP_Test, compare) {
    // check reflexivity
    EXPECT_EQ(0, rdata_rp.compare(rdata_rp));

    // names must be compared in case-insensitive manner
    EXPECT_EQ(0, rdata_rp.compare(generic::RP("ROOT.example.com. "
                                              "rp-text.EXAMPLE.com.")));

    // another RP whose mailbox name is larger than that of rdata_rp.
    const generic::RP large1_rp("zzzz.example.com. rp-text.example.com.");
    EXPECT_GT(0, rdata_rp.compare(large1_rp));
    EXPECT_LT(0, large1_rp.compare(rdata_rp));

    // yet another RP whose text name is larger than that of rdata_rp.
    const generic::RP large2_rp("root.example.com. zzzzzzz.example.com.");
    EXPECT_GT(0, rdata_rp.compare(large2_rp));
    EXPECT_LT(0, large2_rp.compare(rdata_rp));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_rp.compare(*RdataTest::rdata_nomatch), bad_cast);
}
}
