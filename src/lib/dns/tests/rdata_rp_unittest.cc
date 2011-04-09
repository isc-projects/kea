// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/rdataclass.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class Rdata_RP_Test : public RdataTest {
protected:
    Rdata_RP_Test() :
        mailbox_name("root.example.com."),
        text_name("rp-text.example.com."),
        // this also serves as a test for "from text" constructor in a normal
        // case.
        rdata_rp("root.example.com. rp-text.example.com."),
        obuffer(0), renderer(obuffer)
    {}

    const Name mailbox_name, text_name;
    const generic::RP rdata_rp; // commonly used test RDATA
    OutputBuffer obuffer;
    MessageRenderer renderer;
    vector<uint8_t> expected_wire;
};

TEST_F(Rdata_RP_Test, createFromText) {
    EXPECT_EQ(mailbox_name, rdata_rp.getMailbox());
    EXPECT_EQ(text_name, rdata_rp.getText());

    // Invalid textual input cases follow:
    // names are invalid
    EXPECT_THROW(generic::RP("bad..name. rp-text.example.com"), EmptyLabel);
    EXPECT_THROW(generic::RP("mailbox.example.com. bad..name"), EmptyLabel);

    // missing field
    EXPECT_THROW(generic::RP("mailbox.example.com."), InvalidRdataText);

    // redundant field
    EXPECT_THROW(generic::RP("mailbox.example.com. rp-text.example.com. "
                             "redundant.example."), InvalidRdataText);
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
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        &expected_wire[0], expected_wire.size());
}

TEST_F(Rdata_RP_Test, toWireRenderer) {
    // similar to toWireBuffer, but names in RDATA should be compressed.
    UnitTestUtil::readWireData("rdata_rp_toWire2.wire", expected_wire);

    renderer.writeName(Name("a.example.com"));
    renderer.writeName(Name("b.example.net"));
    generic::RP(mailbox_name, Name("rp-text.example.net")).toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        &expected_wire[0], expected_wire.size());
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
