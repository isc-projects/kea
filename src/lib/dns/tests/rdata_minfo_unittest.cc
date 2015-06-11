// Copyright (C) 2011-2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <util/unittests/test_exceptions.h>

using namespace std;
using namespace isc::util;
using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_MINFO_Test : public RdataTest {
protected:
    Rdata_MINFO_Test():
        minfo_txt("rmailbox.example.com. emailbox.example.com."),
        minfo_txt2("root.example.com. emailbox.example.com."),
        too_long_label("01234567890123456789012345678901234567"
                       "89012345678901234567890123."),
        rdata_minfo(minfo_txt),
        rdata_minfo2(minfo_txt2)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::MINFO, isc::Exception, isc::Exception>(
            rdata_str, rdata_minfo, false, false);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::MINFO, InvalidRdataText, MasterLexer::LexerError>(
            rdata_str, rdata_minfo, true, true);
    }

    void checkFromText_TooLongLabel(const string& rdata_str) {
        checkFromText<generic::MINFO, TooLongLabel, TooLongLabel>(
            rdata_str, rdata_minfo, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText<generic::MINFO, InvalidRdataText, isc::Exception>(
            rdata_str, rdata_minfo, true, false);
    }

    void checkFromText_EmptyLabel(const string& rdata_str) {
        checkFromText<generic::MINFO, EmptyLabel, EmptyLabel>(
            rdata_str, rdata_minfo, true, true);
    }

    void checkFromText_MissingOrigin(const string& rdata_str) {
        checkFromText
            <generic::MINFO, MissingNameOrigin, MissingNameOrigin>(
                rdata_str, rdata_minfo, true, true);
    }

    void checkFromText_Origin(const string& rdata_str, const Name* origin) {
        checkFromText<generic::MINFO, MissingNameOrigin, isc::Exception>(
            rdata_str, rdata_minfo, true, false, origin);
    }

    const string minfo_txt;
    const string minfo_txt2;
    const string too_long_label;
    const generic::MINFO rdata_minfo;
    const generic::MINFO rdata_minfo2;
};


TEST_F(Rdata_MINFO_Test, createFromText) {
    EXPECT_EQ(Name("rmailbox.example.com."), rdata_minfo.getRmailbox());
    EXPECT_EQ(Name("emailbox.example.com."), rdata_minfo.getEmailbox());

    EXPECT_EQ(Name("root.example.com."), rdata_minfo2.getRmailbox());
    EXPECT_EQ(Name("emailbox.example.com."), rdata_minfo2.getEmailbox());

    checkFromText_None(minfo_txt);

    // origin defined for lexer constructor, but not string constructor
    const Name origin("example.com");
    checkFromText_Origin("rmailbox emailbox", &origin);

    // lexer constructor accepts extra text, but string constructor doesn't
    checkFromText_BadString("rmailbox.example.com. emailbox.example.com. "
                            "extra.example.com.");
}

TEST_F(Rdata_MINFO_Test, badText) {
    // too long names
    checkFromText_TooLongLabel("root.example.com."  + too_long_label +
                               " emailbox.example.com.");
    checkFromText_TooLongLabel("root.example.com. emailbox.example.com." +
                               too_long_label);

    // invalid names
    checkFromText_EmptyLabel("root..example.com. emailbox.example.com.");
    checkFromText_EmptyLabel("root.example.com. emailbox..example.com.");

    // missing name
    checkFromText_LexerError("root.example.com.");

    // missing origin
    checkFromText_MissingOrigin("root.example.com emailbox.example.com.");
    checkFromText_MissingOrigin("root.example.com. emailbox.example.com");
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
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                           "rdata_minfo_fromWire3.wire"),
                      InvalidRdataLength, "RDLENGTH mismatch: 33 != 3");
    // RDLENGTH is too long
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                           "rdata_minfo_fromWire4.wire"),
                      InvalidRdataLength, "RDLENGTH mismatch: 33 != 80");
    // bogus rmailbox name, the error should be detected in the name
    // constructor
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                           "rdata_minfo_fromWire5.wire"),
                      DNSMessageFORMERR, "unknown label character: 67");
    // bogus emailbox name, the error should be detected in the name
    // constructor
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::MINFO(), RRClass::IN(),
                                           "rdata_minfo_fromWire6.wire"),
                      DNSMessageFORMERR, "unknown label character: 67");
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
    matchWireData(&data[0], data.size(),
                  obuffer.getData(), obuffer.getLength());

    obuffer.clear();
    rdata_minfo2.toWire(obuffer);
    vector<unsigned char> data2;
    UnitTestUtil::readWireData("rdata_minfo_toWireUncompressed2.wire", data2);
    matchWireData(&data2[0], data2.size(),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_MINFO_Test, toWireRenderer) {
    rdata_minfo.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_minfo_toWire1.wire", data);
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());

    renderer.clear();
    rdata_minfo2.toWire(renderer);
    vector<unsigned char> data2;
    UnitTestUtil::readWireData("rdata_minfo_toWire2.wire", data2);
    matchWireData(&data2[0], data2.size(),
                  renderer.getData(), renderer.getLength());
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
