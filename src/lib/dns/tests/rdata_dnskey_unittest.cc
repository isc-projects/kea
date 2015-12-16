// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
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
class Rdata_DNSKEY_Test : public RdataTest {
protected:
    Rdata_DNSKEY_Test() :
        dnskey_txt("257 3 5 BEAAAAOhHQDBrhQbtphgq2wQUpEQ5t4DtUHxoMV"
                   "Fu2hWLDMvoOMRXjGrhhCeFvAZih7yJHf8ZGfW6hd38hXG/x"
                   "ylYCO6Krpbdojwx8YMXLA5/kA+u50WIL8ZR1R6KTbsYVMf/"
                   "Qx5RiNbPClw+vT+U8eXEJmO20jIS1ULgqy347cBB1zMnnz/"
                   "4LJpA0da9CbKj3A254T515sNIMcwsB8/2+2E63/zZrQzBkj"
                   "0BrN/9Bexjpiks3jRhZatEsXn3dTy47R09Uix5WcJt+xzqZ"
                   "7+ysyLKOOedS39Z7SDmsn2eA0FKtQpwA6LXeG2w+jxmw3oA"
                   "8lVUgEf/rzeC/bByBNsO70aEFTd"),
        dnskey_txt2("257 3 5 YmluZDEwLmlzYy5vcmc="),
        rdata_dnskey(dnskey_txt),
        rdata_dnskey2(dnskey_txt2)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::DNSKEY, isc::Exception, isc::Exception>(
            rdata_str, rdata_dnskey2, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::DNSKEY, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_dnskey2, true, true);
    }

    void checkFromText_InvalidLength(const string& rdata_str) {
        checkFromText<generic::DNSKEY, InvalidRdataLength, InvalidRdataLength>(
            rdata_str, rdata_dnskey2, true, true);
    }

    void checkFromText_BadValue(const string& rdata_str) {
        checkFromText<generic::DNSKEY, BadValue, BadValue>(
            rdata_str, rdata_dnskey2, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::DNSKEY, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_dnskey2, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <generic::DNSKEY, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_dnskey2, true, false);
    }

    const string dnskey_txt;
    const string dnskey_txt2;
    const generic::DNSKEY rdata_dnskey;
    const generic::DNSKEY rdata_dnskey2;
};

TEST_F(Rdata_DNSKEY_Test, fromText) {
    EXPECT_EQ(dnskey_txt, rdata_dnskey.toText());

    // Space in key data is OK
    checkFromText_None("257 3 5 YmluZDEw LmlzYy5vcmc=");

    // Delimited number in key data is OK
    checkFromText_None("257 3 5 YmluZDEwLmlzYy 5 vcmc=");

    // Missing keydata is OK
    EXPECT_NO_THROW(const generic::DNSKEY rdata_dnskey3("257 3 5"));

    // Key data too short for RSA/MD5 algorithm is OK when
    // constructing. But getTag() on this object would throw (see
    // .getTag tests).
    EXPECT_NO_THROW(const generic::DNSKEY rdata_dnskey4("1 1 1 YQ=="));

    // Flags field out of range
    checkFromText_InvalidText("65536 3 5 YmluZDEwLmlzYy5vcmc=");

    // Protocol field out of range
    checkFromText_InvalidText("257 256 5 YmluZDEwLmlzYy5vcmc=");

    // Algorithm field out of range
    checkFromText_InvalidText("257 3 256 YmluZDEwLmlzYy5vcmc=");

    // Missing algorithm field
    checkFromText_LexerError("257 3 YmluZDEwLmlzYy5vcmc=");

    // Invalid key data field (not Base64)
    checkFromText_BadValue("257 3 5 BAAAAAAAAAAAD");

    // String instead of number
    checkFromText_LexerError("foo 3 5 YmluZDEwLmlzYy5vcmc=");
    checkFromText_LexerError("257 foo 5 YmluZDEwLmlzYy5vcmc=");
    checkFromText_LexerError("257 3 foo YmluZDEwLmlzYy5vcmc=");

    // Trailing garbage. This should cause only the string constructor
    // to fail, but the lexer constructor must be able to continue
    // parsing from it.
    checkFromText_BadString("257 3 5 YmluZDEwLmlzYy5vcmc= ; comment\n"
                            "257 3 4 YmluZDEwLmlzYy5vcmc=");

    // Unmatched parenthesis should cause a lexer error
    checkFromText_LexerError("257 3 5 )YmluZDEwLmlzYy5vcmc=");
}

TEST_F(Rdata_DNSKEY_Test, assign) {
    generic::DNSKEY rdata_dnskey2("257 3 5 YQ==");
    rdata_dnskey2 = rdata_dnskey;
    EXPECT_EQ(0, rdata_dnskey.compare(rdata_dnskey2));
}

TEST_F(Rdata_DNSKEY_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_dnskey.compare(
        *test::createRdataUsingLexer(RRType::DNSKEY(), RRClass::IN(),
                                     dnskey_txt)));
}

TEST_F(Rdata_DNSKEY_Test, toWireRenderer) {
    renderer.skip(2);
    rdata_dnskey.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_dnskey_fromWire.wire", data);
    matchWireData(&data[2], data.size() - 2,
                  static_cast<const uint8_t *>(renderer.getData()) + 2,
                  renderer.getLength() - 2);
}

TEST_F(Rdata_DNSKEY_Test, toWireBuffer) {
    rdata_dnskey.toWire(obuffer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_dnskey_fromWire.wire", data);
    matchWireData(&data[2], data.size() - 2,
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_DNSKEY_Test, createFromWire) {
    EXPECT_EQ(0, rdata_dnskey.compare(
                  *rdataFactoryFromFile(RRType("DNSKEY"), RRClass("IN"),
                                        "rdata_dnskey_fromWire.wire")));

    // Missing keydata is OK
    const generic::DNSKEY rdata_dnskey_missing_keydata("257 3 5");
    EXPECT_EQ(0, rdata_dnskey_missing_keydata.compare(
        *rdataFactoryFromFile(RRType("DNSKEY"), RRClass("IN"),
                              "rdata_dnskey_empty_keydata_fromWire.wire")));
}

TEST_F(Rdata_DNSKEY_Test, getTag) {
    EXPECT_EQ(12892, rdata_dnskey.getTag());

    // Short keydata with algorithm RSA/MD5 must throw.
    const generic::DNSKEY rdata_dnskey_short_keydata1("1 1 1 YQ==");
    EXPECT_THROW(rdata_dnskey_short_keydata1.getTag(), isc::OutOfRange);

    // Short keydata with algorithm not RSA/MD5 must not throw.
    const generic::DNSKEY rdata_dnskey_short_keydata2("257 3 5 YQ==");
    EXPECT_NO_THROW(rdata_dnskey_short_keydata2.getTag());
}

TEST_F(Rdata_DNSKEY_Test, getAlgorithm) {
    EXPECT_EQ(5, rdata_dnskey.getAlgorithm());
}

TEST_F(Rdata_DNSKEY_Test, getFlags) {
    EXPECT_EQ(257, rdata_dnskey.getFlags());
}

}
