// Copyright (C) 2012-2013, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
#include <util/unittests/wiredata.h>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_SSHFP_Test : public RdataTest {
protected:
        Rdata_SSHFP_Test() :
            sshfp_txt("2 1 123456789abcdef67890123456789abcdef67890"),
            rdata_sshfp(sshfp_txt)
        {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::SSHFP, isc::Exception, isc::Exception>(
            rdata_str, rdata_sshfp, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::SSHFP, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_sshfp, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::SSHFP, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_sshfp, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <generic::SSHFP, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_sshfp, true, false);
    }

    const string sshfp_txt;
    const generic::SSHFP rdata_sshfp;
};

const uint8_t rdata_sshfp_wiredata[] = {
    // algorithm
    0x02,
    // fingerprint type
    0x01,
    // fingerprint
    0x12, 0x34, 0x56, 0x78,
    0x9a, 0xbc, 0xde, 0xf6,
    0x78, 0x90, 0x12, 0x34,
    0x56, 0x78, 0x9a, 0xbc,
    0xde, 0xf6, 0x78, 0x90
};

TEST_F(Rdata_SSHFP_Test, createFromText) {
    // Basic test
    checkFromText_None(sshfp_txt);

    // With different spacing
    checkFromText_None("2 1   123456789abcdef67890123456789abcdef67890");

    // Combination of lowercase and uppercase
    checkFromText_None("2 1 123456789ABCDEF67890123456789abcdef67890");

    // spacing in the fingerprint field
    checkFromText_None("2 1 123456789abcdef67890 123456789abcdef67890");

    // multi-line fingerprint field
    checkFromText_None("2 1 ( 123456789abcdef67890\n 123456789abcdef67890 )");

    // string constructor throws if there's extra text,
    // but lexer constructor doesn't
    checkFromText_BadString(sshfp_txt + "\n" + sshfp_txt);
}

TEST_F(Rdata_SSHFP_Test, algorithmTypes) {
    // Some of these may not be RFC conformant, but we relax the check
    // in our code to work with algorithm and fingerprint types that may
    // show up in the future.
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("2 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("3 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("128 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("255 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 2 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 3 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 128 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 255 12ab"));

    // 0 is reserved, but we allow that too
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("0 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 0 12ab"));

    // > 255 would be broken
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("256 1 12ab"),
                 InvalidRdataText);
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("2 256 12ab"),
                 InvalidRdataText);
}

TEST_F(Rdata_SSHFP_Test, badText) {
    checkFromText_LexerError("1");
    checkFromText_LexerError("ONE 2 123456789abcdef67890123456789abcdef67890");
    checkFromText_LexerError("1 TWO 123456789abcdef67890123456789abcdef67890");
    checkFromText_InvalidText("1 2 BUCKLEMYSHOE");
    checkFromText_InvalidText(sshfp_txt + " extra text");

    // yes, these are redundant to the last test cases in algorithmTypes
    checkFromText_InvalidText(
        "2345 1 123456789abcdef67890123456789abcdef67890");
    checkFromText_InvalidText(
        "2 1234 123456789abcdef67890123456789abcdef67890");

    // negative values are trapped in the lexer rather than the constructor
    checkFromText_LexerError("-2 1 123456789abcdef67890123456789abcdef67890");
    checkFromText_LexerError("2 -1 123456789abcdef67890123456789abcdef67890");
}

TEST_F(Rdata_SSHFP_Test, copyAndAssign) {
    // Copy construct
    generic::SSHFP rdata_sshfp2(rdata_sshfp);
    EXPECT_EQ(0, rdata_sshfp.compare(rdata_sshfp2));

    // Assignment, mainly to confirm it doesn't cause disruption.
    rdata_sshfp2 = rdata_sshfp;
    EXPECT_EQ(0, rdata_sshfp.compare(rdata_sshfp2));
}

TEST_F(Rdata_SSHFP_Test, createFromWire) {
    // Basic test
    EXPECT_EQ(0, rdata_sshfp.compare(
                  *rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                        "rdata_sshfp_fromWire")));
    // Combination of lowercase and uppercase
    EXPECT_EQ(0, rdata_sshfp.compare(
                  *rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                        "rdata_sshfp_fromWire2")));
    // algorithm=1, fingerprint=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire3.wire"));

    // algorithm=255, fingerprint=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire4.wire"));

    // algorithm=0, fingerprint=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire5.wire"));

    // algorithm=5, fingerprint=0
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire6.wire"));

    // algorithm=255, fingerprint=255
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire7.wire"));

    // short fingerprint data
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire8.wire"));

    // fingerprint is shorter than rdata len
    EXPECT_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                      "rdata_sshfp_fromWire9"),
                 InvalidBufferPosition);

    // fingerprint is missing
    EXPECT_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                      "rdata_sshfp_fromWire10"),
                 InvalidBufferPosition);

    // all rdata is missing
    EXPECT_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                      "rdata_sshfp_fromWire11"),
                 InvalidBufferPosition);
}

TEST_F(Rdata_SSHFP_Test, createFromParams) {
    const generic::SSHFP rdata_sshfp2(
        2, 1, "123456789abcdef67890123456789abcdef67890");
    EXPECT_EQ(0, rdata_sshfp2.compare(rdata_sshfp));
}

TEST_F(Rdata_SSHFP_Test, toText) {
    EXPECT_TRUE(boost::iequals(sshfp_txt, rdata_sshfp.toText()));

    const string sshfp_txt2("2 1");
    const generic::SSHFP rdata_sshfp2(sshfp_txt2);
    EXPECT_TRUE(boost::iequals(sshfp_txt2, rdata_sshfp2.toText()));

    const generic::SSHFP rdata_sshfp3("2 1 ");
    EXPECT_TRUE(boost::iequals(sshfp_txt2, rdata_sshfp3.toText()));
}

TEST_F(Rdata_SSHFP_Test, toWire) {
    this->obuffer.clear();
    rdata_sshfp.toWire(this->obuffer);

    EXPECT_EQ(sizeof (rdata_sshfp_wiredata),
              this->obuffer.getLength());

    matchWireData(rdata_sshfp_wiredata, sizeof(rdata_sshfp_wiredata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_SSHFP_Test, compare) {
    const generic::SSHFP rdata_sshfp2("2 1");
    EXPECT_EQ(-1, rdata_sshfp2.compare(rdata_sshfp));
    EXPECT_EQ(1, rdata_sshfp.compare(rdata_sshfp2));
}

TEST_F(Rdata_SSHFP_Test, getAlgorithmNumber) {
    EXPECT_EQ(2, rdata_sshfp.getAlgorithmNumber());
}

TEST_F(Rdata_SSHFP_Test, getFingerprintType) {
    EXPECT_EQ(1, rdata_sshfp.getFingerprintType());
}

TEST_F(Rdata_SSHFP_Test, getFingerprint) {
    const std::vector<uint8_t>& fingerprint =
        rdata_sshfp.getFingerprint();

    EXPECT_EQ(rdata_sshfp.getFingerprintLength(),
              fingerprint.size());
    for (size_t i = 0; i < fingerprint.size(); ++i) {
        EXPECT_EQ(rdata_sshfp_wiredata[i + 2],
                  fingerprint.at(i));
    }
}

TEST_F(Rdata_SSHFP_Test, getFingerprintLength) {
    EXPECT_EQ(20, rdata_sshfp.getFingerprintLength());
}

TEST_F(Rdata_SSHFP_Test, emptyFingerprintFromWire) {
    const uint8_t rdf_wiredata[] = {
        // algorithm
        0x04,
        // fingerprint type
        0x09
    };

    const generic::SSHFP rdf =
        dynamic_cast<const generic::SSHFP&>
        (*rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                               "rdata_sshfp_fromWire12"));

    EXPECT_EQ(4, rdf.getAlgorithmNumber());
    EXPECT_EQ(9, rdf.getFingerprintType());
    EXPECT_EQ(0, rdf.getFingerprintLength());

    this->obuffer.clear();
    rdf.toWire(this->obuffer);

    EXPECT_EQ(2, this->obuffer.getLength());

    matchWireData(rdf_wiredata, sizeof(rdf_wiredata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_SSHFP_Test, emptyFingerprintFromString) {
    const generic::SSHFP rdata_sshfp2("5 6");
    const uint8_t rdata_sshfp2_wiredata[] = {
        // algorithm
        0x05,
        // fingerprint type
        0x06
    };

    EXPECT_EQ(5, rdata_sshfp2.getAlgorithmNumber());
    EXPECT_EQ(6, rdata_sshfp2.getFingerprintType());
    EXPECT_EQ(0, rdata_sshfp2.getFingerprintLength());

    this->obuffer.clear();
    rdata_sshfp2.toWire(this->obuffer);

    EXPECT_EQ(2, this->obuffer.getLength());

    matchWireData(rdata_sshfp2_wiredata, sizeof(rdata_sshfp2_wiredata),
                  obuffer.getData(), obuffer.getLength());
}
}
