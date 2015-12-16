// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
// hacks to make templates work
template <class T>
class RRTYPE : public RRType {
public:
    RRTYPE();
};

template<> RRTYPE<generic::DS>::RRTYPE() : RRType(RRType::DS()) {}
template<> RRTYPE<generic::DLV>::RRTYPE() : RRType(RRType::DLV()) {}

template <class DS_LIKE>
class Rdata_DS_LIKE_Test : public RdataTest {
protected:
    Rdata_DS_LIKE_Test() :
        ds_like_txt("12892 5 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                    "5F0EB5C777586DE18DA6B5"),
        rdata_ds_like(ds_like_txt)
    {}
    const string ds_like_txt;
    const DS_LIKE rdata_ds_like;
};

// The list of types we want to test.
typedef testing::Types<generic::DS, generic::DLV> Implementations;

TYPED_TEST_CASE(Rdata_DS_LIKE_Test, Implementations);

TYPED_TEST(Rdata_DS_LIKE_Test, createFromText) {
    // It's valid for the digest's presentation format to contain
    // spaces. See RFC4034 section 5.3.
    EXPECT_EQ(0, this->rdata_ds_like.compare(
        TypeParam("12892 5 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D5F0EB5"
                  "C777 58 6DE18  \t DA6B5")));
}

TYPED_TEST(Rdata_DS_LIKE_Test, toText_DS_LIKE) {
    EXPECT_EQ(this->ds_like_txt, this->rdata_ds_like.toText());
}

TYPED_TEST(Rdata_DS_LIKE_Test, badText_DS_LIKE) {
    EXPECT_THROW(const TypeParam ds_like2("99999 5 2 BEEF"), InvalidRdataText);
    EXPECT_THROW(const TypeParam ds_like2("11111 555 2 BEEF"),
                 InvalidRdataText);
    EXPECT_THROW(const TypeParam ds_like2("11111 5 22222 BEEF"),
                 InvalidRdataText);
    EXPECT_THROW(const TypeParam ds_like2("11111 5 2"), InvalidRdataText);
    EXPECT_THROW(const TypeParam ds_like2("GARBAGE IN"), InvalidRdataText);
    // no space between the digest type and the digest.
    EXPECT_THROW(const TypeParam ds_like2(
                     "12892 5 2F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                     "5F0EB5C777586DE18DA6B5"), InvalidRdataText);
}

TYPED_TEST(Rdata_DS_LIKE_Test, createFromWire_DS_LIKE) {
    EXPECT_EQ(0, this->rdata_ds_like.compare(
              *this->rdataFactoryFromFile(RRTYPE<TypeParam>(), RRClass::IN(),
                                          "rdata_ds_fromWire")));
}

TYPED_TEST(Rdata_DS_LIKE_Test, createFromLexer_DS_LIKE) {
    EXPECT_EQ(0, this->rdata_ds_like.compare(
        *test::createRdataUsingLexer(RRTYPE<TypeParam>(), RRClass::IN(),
                                     this->ds_like_txt)));

    // Whitespace is okay
    EXPECT_EQ(0, this->rdata_ds_like.compare(
        *test::createRdataUsingLexer(RRTYPE<TypeParam>(), RRClass::IN(),
                                     "12892 5 2 F1E184C0E1D615D20EB3C223ACED3B0"
                                     "3C773DD952D5F0EB5C777 58 6DE18  \t DA6B5"
             )));

    // Exceptions cause NULL to be returned.

    // Bad tag
    EXPECT_FALSE(test::createRdataUsingLexer(RRTYPE<TypeParam>(), RRClass::IN(),
                                             "65536 5 2 BEEF"));

    // Bad algorithm
    EXPECT_FALSE(test::createRdataUsingLexer(RRTYPE<TypeParam>(), RRClass::IN(),
                                             "1024 256 2 BEEF"));

    // Bad digest type
    EXPECT_FALSE(test::createRdataUsingLexer(RRTYPE<TypeParam>(), RRClass::IN(),
                                             "2048 2 256 BEEF"));
}

TYPED_TEST(Rdata_DS_LIKE_Test, assignment_DS_LIKE) {
    TypeParam copy(this->ds_like_txt);
    copy = this->rdata_ds_like;
    EXPECT_EQ(0, copy.compare(this->rdata_ds_like));

    // Check if the copied data is valid even after the original is deleted
    TypeParam* copy2 = new TypeParam(this->rdata_ds_like);
    TypeParam copy3(this->ds_like_txt);
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(this->rdata_ds_like));

    // Self assignment
    copy = copy;
    EXPECT_EQ(0, copy.compare(this->rdata_ds_like));
}

TYPED_TEST(Rdata_DS_LIKE_Test, getTag_DS_LIKE) {
    EXPECT_EQ(12892, this->rdata_ds_like.getTag());
}

TYPED_TEST(Rdata_DS_LIKE_Test, toWireRenderer) {
    Rdata_DS_LIKE_Test<TypeParam>::renderer.skip(2);
    TypeParam rdata_ds_like(this->ds_like_txt);
    rdata_ds_like.toWire(this->renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_ds_fromWire", data);
    matchWireData(&data[2], data.size() - 2,
                  static_cast<const uint8_t*>(this->renderer.getData()) + 2,
                  this->renderer.getLength() - 2);
}

TYPED_TEST(Rdata_DS_LIKE_Test, toWireBuffer) {
    TypeParam rdata_ds_like(this->ds_like_txt);
    rdata_ds_like.toWire(this->obuffer);
}

string ds_like_txt1("12892 5 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                   "5F0EB5C777586DE18DA6B5");
// different tag
string ds_like_txt2("12893 5 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                   "5F0EB5C777586DE18DA6B5");
// different algorithm
string ds_like_txt3("12892 6 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                   "5F0EB5C777586DE18DA6B5");
// different digest type
string ds_like_txt4("12892 5 3 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                   "5F0EB5C777586DE18DA6B5");
// different digest
string ds_like_txt5("12892 5 2 F2E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                   "5F0EB5C777586DE18DA6B5");
// different digest length
string ds_like_txt6("12892 5 2 F2E184C0E1D615D20EB3C223ACED3B03C773DD952D"
                   "5F0EB5C777586DE18DA6B555");

TYPED_TEST(Rdata_DS_LIKE_Test, compare) {
    const string ds_like_txt1(
        "12892 5 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
        "5F0EB5C777586DE18DA6B5");
    // different tag
    const string ds_like_txt2(
        "12893 5 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
        "5F0EB5C777586DE18DA6B5");
    // different algorithm
    const string ds_like_txt3(
        "12892 6 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
        "5F0EB5C777586DE18DA6B5");
    // different digest type
    const string ds_like_txt4(
        "12892 5 3 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
        "5F0EB5C777586DE18DA6B5");
    // different digest
    const string ds_like_txt5(
        "12892 5 2 F2E184C0E1D615D20EB3C223ACED3B03C773DD952D"
        "5F0EB5C777586DE18DA6B5");
    // different digest length
    const string ds_like_txt6(
        "12892 5 2 F2E184C0E1D615D20EB3C223ACED3B03C773DD952D"
        "5F0EB5C777586DE18DA6B555");

    // trivial case: self equivalence
    EXPECT_EQ(0, TypeParam(this->ds_like_txt).
              compare(TypeParam(this->ds_like_txt)));

    // non-equivalence tests
    EXPECT_LT(TypeParam(ds_like_txt1).compare(TypeParam(ds_like_txt2)), 0);
    EXPECT_GT(TypeParam(ds_like_txt2).compare(TypeParam(ds_like_txt1)), 0);

    EXPECT_LT(TypeParam(ds_like_txt1).compare(TypeParam(ds_like_txt3)), 0);
    EXPECT_GT(TypeParam(ds_like_txt3).compare(TypeParam(ds_like_txt1)), 0);

    EXPECT_LT(TypeParam(ds_like_txt1).compare(TypeParam(ds_like_txt4)), 0);
    EXPECT_GT(TypeParam(ds_like_txt4).compare(TypeParam(ds_like_txt1)), 0);

    EXPECT_LT(TypeParam(ds_like_txt1).compare(TypeParam(ds_like_txt5)), 0);
    EXPECT_GT(TypeParam(ds_like_txt5).compare(TypeParam(ds_like_txt1)), 0);

    EXPECT_LT(TypeParam(ds_like_txt1).compare(TypeParam(ds_like_txt6)), 0);
    EXPECT_GT(TypeParam(ds_like_txt6).compare(TypeParam(ds_like_txt1)), 0);

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(this->rdata_ds_like.compare(*this->rdata_nomatch),
                 bad_cast);
}

}
