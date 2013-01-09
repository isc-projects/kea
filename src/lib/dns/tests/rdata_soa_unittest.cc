// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/buffer.h>
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
class Rdata_SOA_Test : public RdataTest {
protected:
    Rdata_SOA_Test() :
        rdata_soa(Name("ns.example.com"),
                  Name("root.example.com"),
                  2010012601, 3600, 300, 3600000, 1200)
    {}

    // Common check to see if the given text can be used to construct SOA
    // Rdata that is identical rdata_soa.
    void checkFromText(const char* soa_txt, const Name* origin = NULL) {
        std::stringstream ss(soa_txt);
        MasterLexer lexer;
        lexer.pushSource(ss);

        if (origin == NULL) {
            // from-string constructor works correctly only when origin
            // is NULL (by its nature).
            EXPECT_EQ(0, generic::SOA(soa_txt).compare(rdata_soa));
        }
        EXPECT_EQ(0, generic::SOA(lexer, origin, MasterLoader::DEFAULT,
                                  loader_cb).compare(rdata_soa));
    }

    // Common check if given text (which is invalid as SOA RDATA) is rejected
    // with the specified type of exception: ExForString is the expected
    // exception for the "from string" constructor; ExForLexer is for the
    // constructor with master lexer.
    template <typename ExForString, typename ExForLexer>
    void checkFromBadTexxt(const char* soa_txt, const Name* origin = NULL) {
        EXPECT_THROW(generic::SOA soa(soa_txt), ExForString);

        std::stringstream ss(soa_txt);
        MasterLexer lexer;
        lexer.pushSource(ss);
        EXPECT_THROW(generic::SOA soa(lexer, origin, MasterLoader::DEFAULT,
                                      loader_cb), ExForLexer);
    }

    const generic::SOA rdata_soa;
};

TEST_F(Rdata_SOA_Test, createFromText) {
    // A simple case.
    checkFromText("ns.example.com. root.example.com. "
                  "2010012601 3600 300 3600000 1200");

    // Beginning and trailing space are ignored.
    checkFromText("  ns.example.com. root.example.com. "
                  "2010012601 3600 300 3600000 1200  ");

    // using extended TTL-like form for some parameters.
    checkFromText("ns.example.com. root.example.com. "
                  "2010012601 1H 5M 1000H 20M");

    // multi-line.
    checkFromText("ns.example.com. (root.example.com.\n"
                  "2010012601 1H 5M 1000H) 20M");

    // relative names for MNAME and RNAME with a separate origin (lexer
    // version only)
    const Name origin("example.com");
    checkFromText("ns root 2010012601 1H 5M 1000H 20M", &origin);

    // with the '@' notation with a separate origin (lexer version only)
    const Name full_mname("ns.example.com");
    checkFromText("@ root.example.com. 2010012601 1H 5M 1000H 20M",
                  &full_mname);

    // bad MNAME/RNAMEs
    checkFromBadTexxt<EmptyLabel, EmptyLabel>(
        "bad..example. . 2010012601 1H 5M 1000H 20M");
    checkFromBadTexxt<EmptyLabel, EmptyLabel>(
        ". bad..example. 2010012601 1H 5M 1000H 20M");

    // Names shouldn't be quoted. (Note: on completion of #2534, the resulting
    // exception will be different).
    checkFromBadTexxt<MissingNameOrigin, MissingNameOrigin>(
        "\".\" . 0 0 0 0 0");
    checkFromBadTexxt<MissingNameOrigin, MissingNameOrigin>(
        ". \".\" 0 0 0 0 0");

    // Missing MAME or RNAME: for the string version, the serial would be
    // tried as RNAME and result in "not absolute".  For the lexer version,
    // it reaches the end-of-line, missing min TTL.
    checkFromBadTexxt<MissingNameOrigin, MasterLexer::LexerError>(
        ". 2010012601 0 0 0 0", &Name::ROOT_NAME());

    // bad serial.  the string version converts lexer error to
    // InvalidRdataText.
    checkFromBadTexxt<InvalidRdataText, MasterLexer::LexerError>(
        ". . bad 0 0 0 0");

    // bad serial; exceeding the uint32_t range (4294967296 = 2^32)
    checkFromBadTexxt<InvalidRdataText, MasterLexer::LexerError>(
        ". . 4294967296 0 0 0 0");

    // Bad format for other numeric parameters.  These will be tried as a TTL,
    // and result in an exception there.
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(". . 2010012601 bad 0 0 0");
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 4294967296 0 0 0");
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(". . 2010012601 0 bad 0 0");
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 4294967296 0 0");
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(". . 2010012601 0 0 bad 0");
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 0 4294967296 0");
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(". . 2010012601 0 0 0 bad");
    checkFromBadTexxt<InvalidRRTTL, InvalidRRTTL>(
        ". . 2010012601 0 0 0 4294967296");

    // No space between RNAME and serial.  This case is the same as missing
    // M/RNAME.
    checkFromBadTexxt<MissingNameOrigin, MasterLexer::LexerError>(
        ". example.0 0 0 0 0", &Name::ROOT_NAME());

    // Extra parameter.  string version immediately detects the error.
    EXPECT_THROW(generic::SOA soa(". . 0 0 0 0 0 extra"), InvalidRdataText);
    // Likewise.  Redundant newline is also considered an error.
    EXPECT_THROW(generic::SOA soa(". . 0 0 0 0 0\n"), InvalidRdataText);
    EXPECT_THROW(generic::SOA soa("\n. . 0 0 0 0 0"), InvalidRdataText);
    // lexer version defers the check to the upper layer (we pass origin
    // to skip the check with the string version).
    checkFromText("ns root 2010012601 1H 5M 1000H 20M extra", &origin);
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
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(renderer.getData()) + 2,
                        renderer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_SOA_Test, toWireBuffer) {
    obuffer.skip(2);
    rdata_soa.toWire(obuffer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_soa_toWireUncompressed.wire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
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
