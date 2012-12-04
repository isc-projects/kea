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

// This is the common code for TXT and SPF tests.

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/rdataclass.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

#include <gtest/gtest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {

template<class T>
class RRTYPE : public RRType {
public:
    RRTYPE();
};

template<> RRTYPE<generic::TXT>::RRTYPE() : RRType(RRType::TXT()) {}
template<> RRTYPE<generic::SPF>::RRTYPE() : RRType(RRType::SPF()) {}

const uint8_t wiredata_txt_like[] = {
    sizeof("Test-String") - 1,
    'T', 'e', 's', 't', '-', 'S', 't', 'r', 'i', 'n', 'g'
};

const uint8_t wiredata_nulltxt[] = { 0 };

template<class TXT_LIKE>
class Rdata_TXT_LIKE_Test : public RdataTest {
protected:
    Rdata_TXT_LIKE_Test() :
        wiredata_longesttxt(256, 'a'),
        rdata_txt_like("Test-String"),
        rdata_txt_like_empty("\"\""),
        rdata_txt_like_quoted("\"Test-String\"")
    {
        wiredata_longesttxt[0] = 255; // adjust length
    }

    vector<uint8_t> wiredata_longesttxt;
    const TXT_LIKE rdata_txt_like;
    const TXT_LIKE rdata_txt_like_empty;
    const TXT_LIKE rdata_txt_like_quoted;
};

// The list of types we want to test.
typedef testing::Types<generic::TXT, generic::SPF> Implementations;

TYPED_TEST_CASE(Rdata_TXT_LIKE_Test, Implementations);

TYPED_TEST(Rdata_TXT_LIKE_Test, createFromText) {
    // normal case is covered in toWireBuffer.

    // surrounding double-quotes shouldn't change the result.
    EXPECT_EQ(0, this->rdata_txt_like.compare(this->rdata_txt_like_quoted));

    // Null character-string.
    this->obuffer.clear();
    TypeParam(string("")).toWire(this->obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        wiredata_nulltxt, sizeof(wiredata_nulltxt));

    // Longest possible character-string.
    this->obuffer.clear();
    TypeParam(string(255, 'a')).toWire(this->obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        &this->wiredata_longesttxt[0],
                        this->wiredata_longesttxt.size());

    // Too long text for a valid character-string.
    EXPECT_THROW(TypeParam(string(256, 'a')), CharStringTooLong);

    // The escape character makes the double quote a part of character-string,
    // so this is invalid input and should be rejected.
    EXPECT_THROW(TypeParam("\"Test-String\\\""), InvalidRdataText);

    // Terminating double-quote is provided, so this is valid, but in this
    // version of implementation we reject escaped characters.
    EXPECT_THROW(TypeParam("\"Test-String\\\"\""), InvalidRdataText);
}

void
makeLargest(vector<uint8_t>& data) {
    uint8_t ch = 0;

    // create 255 sets of character-strings, each of which has the longest
    // length (255bytes string + 1-byte length field)
    for (int i = 0; i < 255; ++i, ++ch) {
        data.push_back(255);
        data.insert(data.end(), 255, ch);
    }
    // the last character-string should be 255 bytes (including the one-byte
    // length field) in length so that the total length should be in the range
    // of 16-bit integers.
    data.push_back(254);
    data.insert(data.end(), 254, ch);

    assert(data.size() == 65535);
}

TYPED_TEST(Rdata_TXT_LIKE_Test, createFromWire) {
    EXPECT_EQ(0, this->rdata_txt_like.compare(
                  *this->rdataFactoryFromFile(RRTYPE<TypeParam>(),
                                              RRClass("IN"),
                                              "rdata_txt_fromWire1")));

    // Empty character string
    EXPECT_EQ(0, this->rdata_txt_like_empty.compare(
                  *this->rdataFactoryFromFile(RRTYPE<TypeParam>(),
                                              RRClass("IN"),
                                              "rdata_txt_fromWire2.wire")));

    // Multiple character strings
    this->obuffer.clear();
    this->rdataFactoryFromFile(RRTYPE<TypeParam>(), RRClass("IN"),
                         "rdata_txt_fromWire3.wire")->toWire(this->obuffer);
    // the result should be 'wiredata_txt' repeated twice
    vector<uint8_t> expected_data(wiredata_txt_like, wiredata_txt_like +
                                  sizeof(wiredata_txt_like));
    expected_data.insert(expected_data.end(), wiredata_txt_like,
                         wiredata_txt_like + sizeof(wiredata_txt_like));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        &expected_data[0], expected_data.size());

    // Largest length of data.  There's nothing special, but should be
    // constructed safely, and the content should be identical to the original
    // data.
    vector<uint8_t> largest_txt_like_data;
    makeLargest(largest_txt_like_data);
    InputBuffer ibuffer(&largest_txt_like_data[0],
                        largest_txt_like_data.size());
    TypeParam largest_txt_like(ibuffer, largest_txt_like_data.size());
    this->obuffer.clear();
    largest_txt_like.toWire(this->obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        &largest_txt_like_data[0],
                        largest_txt_like_data.size());

    // rdlen parameter is out of range.  This is a rare event because we'd
    // normally call the constructor via a polymorphic wrapper, where the
    // length is validated.  But this should be checked explicitly.
    InputBuffer ibuffer2(&largest_txt_like_data[0],
                         largest_txt_like_data.size());
    EXPECT_THROW(TypeParam(ibuffer2, 65536), InvalidRdataLength);

    // RDATA is empty, which is invalid for TXT_LIKE.
    EXPECT_THROW(this->rdataFactoryFromFile(RRTYPE<TypeParam>(), RRClass("IN"),
                                      "rdata_txt_fromWire4.wire"),
                 DNSMessageFORMERR);

    // character-string length is too large, which could cause overrun.
    EXPECT_THROW(this->rdataFactoryFromFile(RRTYPE<TypeParam>(), RRClass("IN"),
                                      "rdata_txt_fromWire5.wire"),
                 DNSMessageFORMERR);
}

TYPED_TEST(Rdata_TXT_LIKE_Test, createFromLexer) {
    EXPECT_EQ(0, this->rdata_txt_like.compare(
        *test::createRdataUsingLexer(RRTYPE<TypeParam>(), RRClass::IN(),
                                     "Test-String")));
}

TYPED_TEST(Rdata_TXT_LIKE_Test, toWireBuffer) {
    this->rdata_txt_like.toWire(this->obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->obuffer.getData(),
                        this->obuffer.getLength(),
                        wiredata_txt_like, sizeof(wiredata_txt_like));
}

TYPED_TEST(Rdata_TXT_LIKE_Test, toWireRenderer) {
    this->rdata_txt_like.toWire(this->renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        this->renderer.getData(),
                        this->renderer.getLength(),
                        wiredata_txt_like, sizeof(wiredata_txt_like));
}

TYPED_TEST(Rdata_TXT_LIKE_Test, toText) {
    EXPECT_EQ("\"Test-String\"", this->rdata_txt_like.toText());
}

TYPED_TEST(Rdata_TXT_LIKE_Test, assignment) {
    TypeParam rdata1("assignment1");
    TypeParam rdata2("assignment2");
    rdata1 = rdata2;
    EXPECT_EQ(0, rdata2.compare(rdata1));

    // Check if the copied data is valid even after the original is deleted
    TypeParam* rdata3 = new TypeParam(rdata1);
    TypeParam rdata4("assignment3");
    rdata4 = *rdata3;
    delete rdata3;
    EXPECT_EQ(0, rdata4.compare(rdata1));

    // Self assignment
    rdata2 = rdata2;
    EXPECT_EQ(0, rdata2.compare(rdata1));
}

TYPED_TEST(Rdata_TXT_LIKE_Test, compare) {
    string const txt1("aaaaaaaa");
    string const txt2("aaaaaaaaaa");
    string const txt3("bbbbbbbb");
    string const txt4(129, 'a');
    string const txt5(128, 'b');

    EXPECT_EQ(TypeParam(txt1).compare(TypeParam(txt1)), 0);

    EXPECT_LT(TypeParam("").compare(TypeParam(txt1)), 0);
    EXPECT_GT(TypeParam(txt1).compare(TypeParam("")), 0);

    EXPECT_LT(TypeParam(txt1).compare(TypeParam(txt2)), 0);
    EXPECT_GT(TypeParam(txt2).compare(TypeParam(txt1)), 0);

    EXPECT_LT(TypeParam(txt1).compare(TypeParam(txt3)), 0);
    EXPECT_GT(TypeParam(txt3).compare(TypeParam(txt1)), 0);

    // we're comparing the data raw, starting at the length octet, so a shorter
    // string sorts before a longer one no matter the lexicopraphical order
    EXPECT_LT(TypeParam(txt3).compare(TypeParam(txt2)), 0);
    EXPECT_GT(TypeParam(txt2).compare(TypeParam(txt3)), 0);

    // to make sure the length octet compares unsigned
    EXPECT_LT(TypeParam(txt1).compare(TypeParam(txt4)), 0);
    EXPECT_GT(TypeParam(txt4).compare(TypeParam(txt1)), 0);

    EXPECT_LT(TypeParam(txt5).compare(TypeParam(txt4)), 0);
    EXPECT_GT(TypeParam(txt4).compare(TypeParam(txt5)), 0);

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(TypeParam(txt1).compare(*this->rdata_nomatch),
                 bad_cast);
}

}
