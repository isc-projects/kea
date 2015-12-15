// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_SOA_Test : public RdataTest {
protected:
    Rdata_SOA_Test() :
        rdata_soa(Name("ns.example.com"),
                  Name("root.example.com"),
                  2010012601, 3600, 300, 3600000, 1200)
    {}

    template <typename ExForString, typename ExForLexer>
    void checkFromTextSOA(const string& soa_txt, const Name* origin = NULL,
                          bool throw_str_version = true,
                          bool throw_lexer_version = true)
    {
        checkFromText<generic::SOA, ExForString, ExForLexer>(
            soa_txt, rdata_soa, throw_str_version, throw_lexer_version,
            origin);
    }

    const generic::SOA rdata_soa;
};

TEST_F(Rdata_SOA_Test, createFromText) {
    // Below we specify isc::Exception as a dummy value for the exception type
    // in case it's not expected to throw an exception; the type isn't used
    // in the check code.

    // A simple case.
    checkFromTextSOA<isc::Exception, isc::Exception>(
        "ns.example.com. root.example.com. 2010012601 3600 300 3600000 1200",
        NULL, false, false);

    // Beginning and trailing space are ignored.
    checkFromTextSOA<isc::Exception, isc::Exception>(
        "  ns.example.com. root.example.com. "
        "2010012601 3600 300 3600000 1200  ", NULL, false, false);

    // using extended TTL-like form for some parameters.
    checkFromTextSOA<isc::Exception, isc::Exception>(
        "ns.example.com. root.example.com. 2010012601 1H 5M 1000H 20M",
        NULL, false, false);

    // multi-line.
    checkFromTextSOA<isc::Exception, isc::Exception>(
        "ns.example.com. (root.example.com.\n"
        "2010012601 1H 5M 1000H) 20M", NULL, false, false);

    // relative names for MNAME and RNAME with a separate origin (lexer
    // version only)
    const Name origin("example.com");
    checkFromTextSOA<MissingNameOrigin, isc::Exception>(
        "ns root 2010012601 1H 5M 1000H 20M", &origin, true, false);

    // with the '@' notation with a separate origin (lexer version only;
    // string version would throw)
    const Name full_mname("ns.example.com");
    checkFromTextSOA<MissingNameOrigin, isc::Exception>(
        "@ root.example.com. 2010012601 1H 5M 1000H 20M", &full_mname, true,
        false);

    // bad MNAME/RNAMEs
    checkFromTextSOA<EmptyLabel, EmptyLabel>(
        "bad..example. . 2010012601 1H 5M 1000H 20M");
    checkFromTextSOA<EmptyLabel, EmptyLabel>(
        ". bad..example. 2010012601 1H 5M 1000H 20M");

    // Names shouldn't be quoted.
    checkFromTextSOA<InvalidRdataText, MasterLexer::LexerError>(
        "\".\" . 0 0 0 0 0");
    checkFromTextSOA<InvalidRdataText, MasterLexer::LexerError>(
        ". \".\" 0 0 0 0 0");

    // Missing MAME or RNAME: for the string version, the serial would be
    // tried as RNAME and result in "not absolute".  For the lexer version,
    // it reaches the end-of-line, missing min TTL.
    checkFromTextSOA<MissingNameOrigin, MasterLexer::LexerError>(
        ". 2010012601 0 0 0 0", &Name::ROOT_NAME());

    // bad serial.  the string version converts lexer error to
    // InvalidRdataText.
    checkFromTextSOA<InvalidRdataText, MasterLexer::LexerError>(
        ". . bad 0 0 0 0");

    // bad serial; exceeding the uint32_t range (4294967296 = 2^32)
    checkFromTextSOA<InvalidRdataText, MasterLexer::LexerError>(
        ". . 4294967296 0 0 0 0");

    // Bad format for other numeric parameters.  These will be tried as a TTL,
    // and result in an exception there.
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 bad 0 0 0");
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 4294967296 0 0 0");
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 bad 0 0");
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 4294967296 0 0");
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 0 bad 0");
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 0 4294967296 0");
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 0 0 bad");
    checkFromTextSOA<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 0 0 4294967296");

    // No space between RNAME and serial.  This case is the same as missing
    // M/RNAME.
    checkFromTextSOA<MissingNameOrigin, MasterLexer::LexerError>(
        ". example.0 0 0 0 0", &Name::ROOT_NAME());

    // Extra parameter.  string version immediately detects the error.
    // lexer version defers the check to the upper layer (we pass origin
    // to skip the check with the string version).
    checkFromTextSOA<InvalidRdataText, isc::Exception>(
        "ns.example.com. root.example.com. 2010012601 1H 5M 1000H 20M "
        "extra", &origin, true, false);

    // Likewise.  Redundant newline is also considered an error.  The lexer
    // version accepts trailing newline, but not the beginning one (where
    // the lexer expects a string excluding newline and EOF).
    checkFromTextSOA<InvalidRdataText, isc::Exception>(
        "ns.example.com. root.example.com. 2010012601 1H 5M 1000H 20M\n",
        NULL, true, false);
    checkFromTextSOA<InvalidRdataText, MasterLexer::LexerError>(
        "\nns.example.com. root.example.com. 2010012601 1H 5M 1000H 20M",
        NULL, true, true);
}

TEST_F(Rdata_SOA_Test, createFromWire) {
    EXPECT_EQ(0, rdata_soa.compare(
                  *rdataFactoryFromFile(RRType("SOA"), RRClass("IN"),
                                        "rdata_soa_fromWire")));
    // TBD: more tests
}

TEST_F(Rdata_SOA_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_soa.compare(
        *test::createRdataUsingLexer(RRType::SOA(), RRClass::IN(),
                                     "ns.example.com. root.example.com. "
                                     "2010012601 3600 300 3600000 1200")));
}

TEST_F(Rdata_SOA_Test, toWireRenderer) {
    renderer.skip(2);
    rdata_soa.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_soa_fromWire", data);
    matchWireData(&data[2], data.size() - 2,
                  static_cast<const uint8_t *>(renderer.getData()) + 2,
                  renderer.getLength() - 2);
}

TEST_F(Rdata_SOA_Test, toWireBuffer) {
    obuffer.skip(2);
    rdata_soa.toWire(obuffer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_soa_toWireUncompressed.wire", data);
    matchWireData(&data[2], data.size() - 2,
                  static_cast<const uint8_t *>(obuffer.getData()) + 2,
                  obuffer.getLength() - 2);
}

TEST_F(Rdata_SOA_Test, toText) {
    EXPECT_EQ("ns.example.com. root.example.com. "
              "2010012601 3600 300 3600000 1200", rdata_soa.toText());
}

TEST_F(Rdata_SOA_Test, getSerial) {
    EXPECT_EQ(2010012601, rdata_soa.getSerial().getValue());
}

TEST_F(Rdata_SOA_Test, getMinimum) {
    EXPECT_EQ(1200, rdata_soa.getMinimum());

    // Also check with a very large number (with the MSB being 1).
    EXPECT_EQ(2154848336u, generic::SOA(Name("ns.example.com"),
                                        Name("root.example.com"),
                                        0, 0, 0, 0, 0x80706050).getMinimum());
}

void
compareCheck(const generic::SOA& small, const generic::SOA& large) {
    EXPECT_GT(0, small.compare(large));
    EXPECT_LT(0, large.compare(small));
}

TEST_F(Rdata_SOA_Test, compare) {
    // Check simple equivalence
    EXPECT_EQ(0, rdata_soa.compare(generic::SOA(
                                       "ns.example.com. root.example.com. "
                                       "2010012601 3600 300 3600000 1200")));
    // Check name comparison is case insensitive
    EXPECT_EQ(0, rdata_soa.compare(generic::SOA(
                                       "NS.example.com. root.EXAMPLE.com. "
                                       "2010012601 3600 300 3600000 1200")));

    // Check names are compared in the RDATA comparison semantics (different
    // from DNSSEC ordering for owner names)
    compareCheck(generic::SOA("a.example. . 0 0 0 0 0"),
                 generic::SOA("example. . 0 0 0 0 0"));
    compareCheck(generic::SOA(". a.example. 0 0 0 0 0"),
                 generic::SOA(". example. 0 0 0 0 0"));

    // Compare other numeric fields: 1076895760 = 0x40302010,
    // 270544960 = 0x10203040.  These are chosen to make sure that machine
    // endian doesn't confuse the comparison results.
    compareCheck(generic::SOA(". . 270544960 0 0 0 0"),
                 generic::SOA(". . 1076895760 0 0 0 0"));
    compareCheck(generic::SOA(". . 0 270544960 0 0 0"),
                 generic::SOA(". . 0 1076895760 0 0 0"));
    compareCheck(generic::SOA(". . 0 0 270544960 0 0"),
                 generic::SOA(". . 0 0 1076895760 0 0"));
    compareCheck(generic::SOA(". . 0 0 0 270544960 0"),
                 generic::SOA(". . 0 0 0 1076895760 0"));
    compareCheck(generic::SOA(". . 0 0 0 0 270544960"),
                 generic::SOA(". . 0 0 0 0 1076895760"));
}

}
