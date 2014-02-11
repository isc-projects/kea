// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <algorithm>
#include <string>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <boost/algorithm/string.hpp>

using isc::UnitTestUtil;
using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {
class Rdata_CAA_Test : public RdataTest {
protected:
    Rdata_CAA_Test() :
        caa_txt("0 issue \"ca.example.net\""),
        rdata_caa(caa_txt)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::CAA, isc::Exception, isc::Exception>(
            rdata_str, rdata_caa, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::CAA, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_caa, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::CAA, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_caa, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <generic::CAA, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_caa, true, false);
    }

    const string caa_txt;
    const generic::CAA rdata_caa;
};

const uint8_t rdata_caa_wiredata[] = {
    // flags
    0x00,
    // tag length
    0x5,
    // tag
    'i', 's', 's', 'u', 'e',
    // value
    'c', 'a', '.', 'e', 'x', 'a', 'm', 'p', 'l', 'e',
    '.', 'n', 'e', 't'
};

TEST_F(Rdata_CAA_Test, createFromText) {
    // Basic test
    checkFromText_None(caa_txt);

    // With different spacing
    checkFromText_None("0 issue    \"ca.example.net\"");

    // Combination of lowercase and uppercase
    checkFromText_None("0 IssUE \"ca.example.net\"");

    // string constructor throws if there's extra text,
    // but lexer constructor doesn't
    checkFromText_BadString(caa_txt + "\n" + caa_txt);

    // Missing value field
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 issue"));
}

TEST_F(Rdata_CAA_Test, fields) {
    // Some of these may not be RFC conformant, but we relax the check
    // in our code to work with other field values that may show up in
    // the future.
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("1 issue \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("2 issue \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("3 issue \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("128 issue \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("255 issue \"ca.example.net\""));

    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 foo \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 bar \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 12345 \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 w0x1y2z3 \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 relaxed-too \"ca.example.net\""));
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 RELAXED.too \"ca.example.net\""));

    // No value (this is redundant to the last test case in the
    // .createFromText test
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 issue"));

    // > 255 would be broken
    EXPECT_THROW(const generic::CAA rdata_caa2("256 issue \"ca.example.net\""),
                 InvalidRdataText);

    // Missing tag actually passes because it parses the value as tag
    // and assumes that the value is empty instead.
    EXPECT_NO_THROW(const generic::CAA rdata_caa2("0 \"ca.example.net\""));

    // Tag is too long
    const std::string tag(256, 'a');
    const std::string rdata_txt("0 " + tag + " \"ca.example.net\"");
    EXPECT_THROW(const generic::CAA rdata_caa2(rdata_txt), InvalidRdataText);
}

TEST_F(Rdata_CAA_Test, badText) {
    checkFromText_LexerError("0");
    checkFromText_LexerError("ZERO issue \"ca.example.net\"");
    EXPECT_THROW(const generic::CAA rdata_caa2(caa_txt + " extra text"),
                 InvalidRdataText);

    // Yes, this is redundant to the last test cases in the .fields test
    checkFromText_InvalidText("2345 issue \"ca.example.net\"");

    // negative values are trapped in the lexer rather than the
    // constructor
    checkFromText_LexerError("-2 issue \"ca.example.net\"");
}

TEST_F(Rdata_CAA_Test, copyAndAssign) {
    // Copy construct
    generic::CAA rdata_caa2(rdata_caa);
    EXPECT_EQ(0, rdata_caa.compare(rdata_caa2));

    // Assignment, mainly to confirm it doesn't cause disruption.
    rdata_caa2 = rdata_caa;
    EXPECT_EQ(0, rdata_caa.compare(rdata_caa2));
}

TEST_F(Rdata_CAA_Test, createFromWire) {
    // Basic test
    EXPECT_EQ(0, rdata_caa.compare(
                  *rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                                        "rdata_caa_fromWire1.wire")));

    // Combination of lowercase and uppercase
    EXPECT_EQ(0, rdata_caa.compare(
                  *rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                                        "rdata_caa_fromWire2.wire")));

    // Value field is empty
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                                         "rdata_caa_fromWire3.wire"));

    // Tag field is empty
    EXPECT_THROW(rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                                      "rdata_caa_fromWire4.wire"),
                 InvalidRdataText);

    // Value field is shorter than rdata len
    EXPECT_THROW(rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                                      "rdata_caa_fromWire5"),
                 InvalidBufferPosition);

    // all RDATA is missing
    EXPECT_THROW(rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                                      "rdata_caa_fromWire6"),
                 InvalidBufferPosition);
}

TEST_F(Rdata_CAA_Test, createFromParams) {
    const generic::CAA rdata_caa2(0, "issue", "ca.example.net");
    EXPECT_EQ(0, rdata_caa2.compare(rdata_caa));

    // Tag is empty
    EXPECT_THROW(const generic::CAA rdata_caa3(0, "", "ca.example.net"),
                 isc::InvalidParameter);

    // Tag is too long
    const std::string tag(256, 'a');
    EXPECT_THROW(const generic::CAA rdata_caa3(0, tag, "ca.example.net"),
                 isc::InvalidParameter);

    // Value is too long
    const std::string value(65536, 'a');
    EXPECT_THROW(const generic::CAA rdata_caa3(0, "issue", value),
                 InvalidRdataLength);
}

TEST_F(Rdata_CAA_Test, toText) {
    EXPECT_TRUE(boost::iequals(caa_txt, rdata_caa.toText()));

    const string caa_txt2("1 issue \"\"");
    const generic::CAA rdata_caa2(caa_txt2);
    EXPECT_TRUE(boost::iequals(caa_txt2, rdata_caa2.toText()));
}

TEST_F(Rdata_CAA_Test, toWire) {
    this->obuffer.clear();
    rdata_caa.toWire(this->obuffer);

    EXPECT_EQ(sizeof (rdata_caa_wiredata),
              this->obuffer.getLength());

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        rdata_caa_wiredata, sizeof(rdata_caa_wiredata));
}

TEST_F(Rdata_CAA_Test, compare) {
    // Equality test is repeated from createFromWire tests above.
    EXPECT_EQ(0, rdata_caa.compare(
                  *rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                                        "rdata_caa_fromWire1.wire")));

    const generic::CAA rdata_caa2("1 issue \"ca.example.net\"");

    EXPECT_EQ(1, rdata_caa2.compare(rdata_caa));
    EXPECT_EQ(-1, rdata_caa.compare(rdata_caa2));
}

TEST_F(Rdata_CAA_Test, getFlags) {
    EXPECT_EQ(0, rdata_caa.getFlags());
}

TEST_F(Rdata_CAA_Test, getTag) {
    EXPECT_EQ("issue", rdata_caa.getTag());
}

TEST_F(Rdata_CAA_Test, emptyValueFromWire) {
    const uint8_t rdf_wiredata[] = {
        // flags
        0x00,
        // tag length
        0x5,
        // tag
        'i', 's', 's', 'u', 'e'
    };

    const generic::CAA rdf =
        dynamic_cast<const generic::CAA&>
        (*rdataFactoryFromFile(RRType("CAA"), RRClass("IN"),
                               "rdata_caa_fromWire3.wire"));

    EXPECT_EQ(0, rdf.getFlags());
    EXPECT_EQ("issue", rdf.getTag());

    this->obuffer.clear();
    rdf.toWire(this->obuffer);

    EXPECT_EQ(sizeof(rdf_wiredata), this->obuffer.getLength());

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        rdf_wiredata, sizeof(rdf_wiredata));
}

TEST_F(Rdata_CAA_Test, emptyValueFromString) {
    const generic::CAA rdata_caa2("0 issue");
    const uint8_t rdata_caa2_wiredata[] = {
        // flags
        0x00,
        // tag length
        0x5,
        // tag
        'i', 's', 's', 'u', 'e'
    };

    EXPECT_EQ(0, rdata_caa2.getFlags());
    EXPECT_EQ("issue", rdata_caa2.getTag());

    this->obuffer.clear();
    rdata_caa2.toWire(this->obuffer);

    EXPECT_EQ(sizeof(rdata_caa2_wiredata),
              this->obuffer.getLength());

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        rdata_caa2_wiredata, sizeof(rdata_caa2_wiredata));
}
}
