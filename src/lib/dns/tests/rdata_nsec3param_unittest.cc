// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <exceptions/exceptions.h>

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
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_NSEC3PARAM_Test : public RdataTest {
protected:
    Rdata_NSEC3PARAM_Test() :
        nsec3param_txt("1 1 1 D399EAAB"),
        nsec3param_nosalt_txt("1 1 1 -"),
        rdata_nsec3param(nsec3param_txt)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::NSEC3PARAM, isc::Exception, isc::Exception>(
            rdata_str, rdata_nsec3param, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::NSEC3PARAM, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_nsec3param, true, true);
    }

    void checkFromText_BadValue(const string& rdata_str) {
        checkFromText<generic::NSEC3PARAM, BadValue, BadValue>(
            rdata_str, rdata_nsec3param, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::NSEC3PARAM, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_nsec3param, true, true);
    }

    void checkFromText_BadString(const string& rdata_str,
                                 const generic::NSEC3PARAM& rdata)
    {
        checkFromText
            <generic::NSEC3PARAM, InvalidRdataText, isc::Exception>(
                rdata_str, rdata, true, false);
    }

    const string nsec3param_txt;
    const string nsec3param_nosalt_txt;
    const generic::NSEC3PARAM rdata_nsec3param;
};

TEST_F(Rdata_NSEC3PARAM_Test, fromText) {
    // Empty salt is okay.
    EXPECT_EQ(0, generic::NSEC3PARAM(nsec3param_nosalt_txt).getSalt().size());

    // Salt is missing.
    checkFromText_LexerError("1 1 1");

    // Salt has whitespace within. This only fails in the string
    // constructor, as the lexer constructor stops reading at the end of
    // its RDATA.
    const generic::NSEC3PARAM rdata_nsec3param2("1 1 1 D399");
    checkFromText_BadString("1 1 1 D399 EAAB", rdata_nsec3param2);

    // Hash algorithm out of range.
    checkFromText_InvalidText("256 1 1 D399EAAB");

    // Flags out of range.
    checkFromText_InvalidText("1 256 1 D399EAAB");

    // Iterations out of range.
    checkFromText_InvalidText("1 1 65536 D399EAAB");

    // Bad hex sequence
    checkFromText_BadValue("1 1 256 D399EAABZOO");

    // String instead of number
    checkFromText_LexerError("foo 1 256 D399EAAB");
    checkFromText_LexerError("1 foo 256 D399EAAB");
    checkFromText_LexerError("1 1 foo D399EAAB");

    // Trailing garbage. This should cause only the string constructor
    // to fail, but the lexer constructor must be able to continue
    // parsing from it.
    checkFromText_BadString("1 1 1 D399EAAB ; comment\n"
                            "1 1 1 D399EAAB", rdata_nsec3param);
}

TEST_F(Rdata_NSEC3PARAM_Test, toText) {
    EXPECT_EQ(nsec3param_txt, rdata_nsec3param.toText());

    // Garbage space at the end should be ok. RFC5155 only forbids
    // whitespace within the salt field, but any whitespace afterwards
    // should be fine.
    EXPECT_NO_THROW(generic::NSEC3PARAM("1 1 1 D399EAAB "));

    // Hash algorithm in range.
    EXPECT_NO_THROW(generic::NSEC3PARAM("255 1 1 D399EAAB"));

    // Flags in range.
    EXPECT_NO_THROW(generic::NSEC3PARAM("1 255 1 D399EAAB"));

    // Iterations in range.
    EXPECT_NO_THROW(generic::NSEC3PARAM("1 1 65535 D399EAAB"));
}

TEST_F(Rdata_NSEC3PARAM_Test, createFromWire) {
    EXPECT_EQ(0, rdata_nsec3param.compare(
                  *rdataFactoryFromFile(RRType::NSEC3PARAM(), RRClass::IN(),
                                       "rdata_nsec3param_fromWire1")));

    // Short buffer cases.  The data is valid NSEC3PARAM RDATA, but the buffer
    // is trimmed at the end.  All cases should result in an exception from
    // the buffer class.
    vector<uint8_t> data;
    UnitTestUtil::readWireData("rdata_nsec3param_fromWire1", data);
    const uint16_t rdlen = (data.at(0) << 8) + data.at(1);
    for (int i = 0; i < rdlen; ++i) {
        // intentionally construct a short buffer
        InputBuffer b(&data[0] + 2, i);
        EXPECT_THROW(createRdata(RRType::NSEC3PARAM(), RRClass::IN(), b, 9),
                     InvalidBufferPosition);
    }
}

TEST_F(Rdata_NSEC3PARAM_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_nsec3param.compare(
        *test::createRdataUsingLexer(RRType::NSEC3PARAM(), RRClass::IN(),
                                     nsec3param_txt)));

    // empty salt is also okay.
    const generic::NSEC3PARAM rdata_nosalt_nsec3param(nsec3param_nosalt_txt);
    EXPECT_EQ(0, rdata_nosalt_nsec3param.compare(
        *test::createRdataUsingLexer(RRType::NSEC3PARAM(), RRClass::IN(),
                                     nsec3param_nosalt_txt)));
}

TEST_F(Rdata_NSEC3PARAM_Test, toWireRenderer) {
    renderer.skip(2);
    rdata_nsec3param.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_nsec3param_fromWire1", data);
    matchWireData(&data[2], data.size() - 2,
                  static_cast<const uint8_t *>(renderer.getData()) + 2,
                  renderer.getLength() - 2);
}

TEST_F(Rdata_NSEC3PARAM_Test, toWireBuffer) {
    rdata_nsec3param.toWire(obuffer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_nsec3param_fromWire1", data);
    matchWireData(&data[2], data.size() - 2,
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_NSEC3PARAM_Test, getHashAlg) {
    EXPECT_EQ(1, rdata_nsec3param.getHashalg());
}

TEST_F(Rdata_NSEC3PARAM_Test, getFlags) {
    EXPECT_EQ(1, rdata_nsec3param.getFlags());
}

TEST_F(Rdata_NSEC3PARAM_Test, assign) {
    generic::NSEC3PARAM other_nsec3param("1 1 1 -");
    other_nsec3param = rdata_nsec3param;
    EXPECT_EQ(0, rdata_nsec3param.compare(other_nsec3param));
}

TEST_F(Rdata_NSEC3PARAM_Test, compare) {
    // trivial case: self equivalence
    EXPECT_EQ(0, generic::NSEC3PARAM(nsec3param_txt).
              compare(generic::NSEC3PARAM(nsec3param_txt)));
    EXPECT_EQ(0, generic::NSEC3PARAM("1 1 1 -").
              compare(generic::NSEC3PARAM("1 1 1 -")));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(generic::NSEC3PARAM(nsec3param_txt).compare(*rdata_nomatch),
                 bad_cast);
}

}
