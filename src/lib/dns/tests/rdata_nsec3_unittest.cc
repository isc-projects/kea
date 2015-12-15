// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <exceptions/exceptions.h>

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
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {

// Note: some tests can be shared with NSEC3PARAM.  They are unified as
// typed tests defined in nsec3param_like_unittest.
class Rdata_NSEC3_Test : public RdataTest {
protected:
    Rdata_NSEC3_Test() :
        nsec3_txt("1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6 "
                  "A NS SOA"),
        nsec3_nosalt_txt("1 1 1 - H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA"),
        nsec3_notype_txt("1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6"),
        rdata_nsec3(nsec3_txt)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::NSEC3, isc::Exception, isc::Exception>(
            rdata_str, rdata_nsec3, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::NSEC3, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_nsec3, true, true);
    }

    void checkFromText_BadValue(const string& rdata_str) {
        checkFromText<generic::NSEC3, BadValue, BadValue>(
            rdata_str, rdata_nsec3, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::NSEC3, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_nsec3, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <generic::NSEC3, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_nsec3, true, false);
    }

    const string nsec3_txt;
    const string nsec3_nosalt_txt;
    const string nsec3_notype_txt;
    const generic::NSEC3 rdata_nsec3;
};

TEST_F(Rdata_NSEC3_Test, fromText) {
    // Hash that has the possible max length
    EXPECT_EQ(255, generic::NSEC3("1 1 1 D399EAAB " +
                                  string((255 * 8) / 5, '0') +
                                  " NS").getNext().size());

    // Hash is too long.  Max = 255 bytes, base32-hex converts each 5 bytes
    // of the original to 8 characters, so 260 * 8 / 5 is the smallest length
    // of the encoded string that exceeds the max and doesn't require padding.
    checkFromText_InvalidText("1 1 1 D399EAAB " + string((260 * 8) / 5, '0') +
                              " A NS SOA");

    // Type bitmap is empty.  it's possible and allowed for NSEC3.
    EXPECT_NO_THROW(const generic::NSEC3 rdata_notype_nsec3(nsec3_notype_txt));

    // Empty salt is also okay.
    EXPECT_NO_THROW(const generic::NSEC3 rdata_nosalt_nsec3(nsec3_nosalt_txt));

    // Bad type mnemonics
    checkFromText_InvalidText("1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6"
                              " BIFF POW SPOON");

    // Bad base32hex
    checkFromText_BadValue("1 1 1 D399EAAB "
                           "WXYZWXYZWXYZ=WXYZWXYZ==WXYZWXYZW A NS SOA");

    // Hash algorithm out of range
    checkFromText_InvalidText("256 1 1 D399EAAB "
                              "H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA");

    // Flags out of range
    checkFromText_InvalidText("1 256 1 D399EAAB "
                              "H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA");

    // Iterations out of range
    checkFromText_InvalidText("1 1 65536 D399EAAB "
                              "H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA");

    // Space is not allowed in salt or the next hash. This actually
    // causes the Base32 decoder that parses the next hash that comes
    // afterwards, to throw.
    checkFromText_BadValue("1 1 1 D399 EAAB H9RSFB7FPF2L8"
                           "HG35CMPC765TDK23RP6 A NS SOA");

    // Next hash must not contain padding (trailing '=' characters)
    checkFromText_InvalidText("1 1 1 D399EAAB "
                              "AAECAwQFBgcICQoLDA0ODw== A NS SOA");

    // String instead of number
    checkFromText_LexerError("foo 1 1 D399EAAB "
                             "H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA");
    checkFromText_LexerError("1 foo 1 D399EAAB "
                             "H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA");
    checkFromText_LexerError("1 1 foo D399EAAB "
                             "H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA");

    // Trailing garbage. This should cause only the string constructor
    // to fail, but the lexer constructor must be able to continue
    // parsing from it.
    checkFromText_BadString(
        "1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA ;comment\n"
        "1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A NS SOA");

    // Unmatched parenthesis should cause a lexer error
    checkFromText_LexerError("1 1 1 D399EAAB "
                             "H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A ) NS SOA");
}

TEST_F(Rdata_NSEC3_Test, createFromWire) {
    // A valid NSEC3 RR with empty type bitmap.
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                         "rdata_nsec3_fromWire15.wire"));

    // Invalid bitmap cases are tested in Rdata_NSECBITMAP_Test.

    // hash length is too large
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire12.wire"),
                 DNSMessageFORMERR);

    // empty hash.  invalid.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire14.wire"),
                 DNSMessageFORMERR);

    // RDLEN is too short to hold the hash length field
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire17.wire"),
                 DNSMessageFORMERR);

    // Short buffer cases.  The data is valid NSEC3 RDATA, but the buffer
    // is trimmed at the end.  All cases should result in an exception from
    // the buffer class.
    vector<uint8_t> data;
    UnitTestUtil::readWireData("rdata_nsec3_fromWire1", data);
    const uint16_t rdlen = (data.at(0) << 8) + data.at(1);
    for (int i = 0; i < rdlen; ++i) {
        // intentionally construct a short buffer
        InputBuffer b(&data[0] + 2, i);
        EXPECT_THROW(createRdata(RRType::NSEC3(), RRClass::IN(), b, 39),
                     InvalidBufferPosition);
    }
}

TEST_F(Rdata_NSEC3_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_nsec3.compare(
        *test::createRdataUsingLexer(RRType::NSEC3(), RRClass::IN(),
                                     nsec3_txt)));

    // empty salt is also okay.
    const generic::NSEC3 rdata_nosalt_nsec3(nsec3_nosalt_txt);
    EXPECT_EQ(0, rdata_nosalt_nsec3.compare(
        *test::createRdataUsingLexer(RRType::NSEC3(), RRClass::IN(),
                                     nsec3_nosalt_txt)));
}

TEST_F(Rdata_NSEC3_Test, assign) {
    generic::NSEC3 other_nsec3 = rdata_nsec3;
    EXPECT_EQ(0, rdata_nsec3.compare(other_nsec3));
}

TEST_F(Rdata_NSEC3_Test, compare) {
    // trivial case: self equivalence
    EXPECT_EQ(0, generic::NSEC3(nsec3_txt).compare(generic::NSEC3(nsec3_txt)));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(generic::NSEC3(nsec3_txt).compare(*rdata_nomatch),
                 bad_cast);

    // test RDATAs, sorted in the ascendent order.  We only check comparison
    // on NSEC3-specific fields.  Bitmap comparison is tested in the bitmap
    // tests.  Common cases for NSEC3 and NSECPARAM3 are in their shared tests.
    vector<generic::NSEC3> compare_set;
    compare_set.push_back(generic::NSEC3("1 1 1 FF99EA0000 D1K6GQ38"));
    compare_set.push_back(generic::NSEC3("1 1 1 FF99EA0000 D1K6GQ0000000000"));
    compare_set.push_back(generic::NSEC3("1 1 1 FF99EA0000 D1K6GQ00UUUUUUUU"));

    vector<generic::NSEC3>::const_iterator it;
    const vector<generic::NSEC3>::const_iterator it_end = compare_set.end();
    for (it = compare_set.begin(); it != it_end - 1; ++it) {
        SCOPED_TRACE("compare " + it->toText() + " to " + (it + 1)->toText());
        EXPECT_GT(0, (*it).compare(*(it + 1)));
        EXPECT_LT(0, (*(it + 1)).compare(*it));
    }
}

}
