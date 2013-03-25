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

using isc::UnitTestUtil;
using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {
class Rdata_DNSKEY_Test : public RdataTest {
    // there's nothing to specialize
};

string dnskey_txt("257 3 5 BEAAAAOhHQDBrhQbtphgq2wQUpEQ5t4DtUHxoMV"
                  "Fu2hWLDMvoOMRXjGrhhCeFvAZih7yJHf8ZGfW6hd38hXG/x"
                  "ylYCO6Krpbdojwx8YMXLA5/kA+u50WIL8ZR1R6KTbsYVMf/"
                  "Qx5RiNbPClw+vT+U8eXEJmO20jIS1ULgqy347cBB1zMnnz/"
                  "4LJpA0da9CbKj3A254T515sNIMcwsB8/2+2E63/zZrQzBkj"
                  "0BrN/9Bexjpiks3jRhZatEsXn3dTy47R09Uix5WcJt+xzqZ"
                  "7+ysyLKOOedS39Z7SDmsn2eA0FKtQpwA6LXeG2w+jxmw3oA"
                  "8lVUgEf/rzeC/bByBNsO70aEFTd");

TEST_F(Rdata_DNSKEY_Test, fromText) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    EXPECT_EQ(dnskey_txt, rdata_dnskey.toText());

    // Space in key data is OK
    EXPECT_NO_THROW(generic::DNSKEY("257 3 5 YmluZDEw LmlzYy5vcmc="));

    // Delimited number in key data is OK
    EXPECT_NO_THROW(generic::DNSKEY("257 3 5 YmluZDEwLmlzYy 5 vcmc="));
}

TEST_F(Rdata_DNSKEY_Test, assign) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    generic::DNSKEY rdata_dnskey2 = rdata_dnskey;
    EXPECT_EQ(0, rdata_dnskey.compare(rdata_dnskey2));
}

TEST_F(Rdata_DNSKEY_Test, badText) {
    EXPECT_THROW(generic::DNSKEY("257 3 5"),
                 InvalidRdataText);
    EXPECT_THROW(generic::DNSKEY("99999 3 5 BAAAAAAAAAAAD"),
                 InvalidRdataText);
    EXPECT_THROW(generic::DNSKEY("257 300 5 BAAAAAAAAAAAD"),
                 InvalidRdataText);
    EXPECT_THROW(generic::DNSKEY("257 3 500 BAAAAAAAAAAAD"),
                 InvalidRdataText);
    EXPECT_THROW(generic::DNSKEY("257 3 5 BAAAAAAAAAAAD"), BadValue);

    // Key data too short for algorithm=1
    EXPECT_THROW(generic::DNSKEY("1 1 1 YQ=="),
                 InvalidRdataLength);

    // Missing algorithm
    EXPECT_THROW(generic::DNSKEY("257 3 YmFiYWJhYmE="),
                 InvalidRdataText);
}

TEST_F(Rdata_DNSKEY_Test, createFromLexer) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    EXPECT_EQ(0, rdata_dnskey.compare(
        *test::createRdataUsingLexer(RRType::DNSKEY(), RRClass::IN(),
                                     dnskey_txt)));

    // Exceptions cause NULL to be returned.

    // Key data missing
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::DNSKEY(), RRClass::IN(),
                                             "257 3 5"));
    // Bad flags
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::DNSKEY(), RRClass::IN(),
                                             "65536 3 5 ABCDABCD"));
    // Bad protocol
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::DNSKEY(), RRClass::IN(),
                                             "1 256 1 ABCDABCD"));
    // Bad algorithm
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::DNSKEY(), RRClass::IN(),
                                             "1 1 256 ABCDABCD"));
    // Key data too short for algorithm=1
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::DNSKEY(), RRClass::IN(),
                                             "1 1 1 YQ=="));
}

TEST_F(Rdata_DNSKEY_Test, toWireRenderer) {
    renderer.skip(2);
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    rdata_dnskey.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_dnskey_fromWire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(renderer.getData()) + 2,
                        renderer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_DNSKEY_Test, toWireBuffer) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    rdata_dnskey.toWire(obuffer);
}

TEST_F(Rdata_DNSKEY_Test, createFromWire) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    EXPECT_EQ(0, rdata_dnskey.compare(
                  *rdataFactoryFromFile(RRType("DNSKEY"), RRClass("IN"),
                                        "rdata_dnskey_fromWire")));
    // Empty keydata should throw
    EXPECT_THROW(rdataFactoryFromFile(RRType("DNSKEY"), RRClass("IN"),
                                      "rdata_dnskey_empty_keydata_fromWire"),
                 InvalidRdataLength);
    // Short keydata for RSA/MD5 should throw
    EXPECT_THROW(rdataFactoryFromFile(RRType("DNSKEY"), RRClass("IN"),
                                      "rdata_dnskey_short_keydata1_fromWire"),
                 InvalidRdataLength);
}

TEST_F(Rdata_DNSKEY_Test, getTag) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    EXPECT_EQ(12892, rdata_dnskey.getTag());
}

TEST_F(Rdata_DNSKEY_Test, getAlgorithm) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    EXPECT_EQ(5, rdata_dnskey.getAlgorithm());
}

TEST_F(Rdata_DNSKEY_Test, getFlags) {
    generic::DNSKEY rdata_dnskey(dnskey_txt);
    EXPECT_EQ(257, rdata_dnskey.getFlags());
}

}
