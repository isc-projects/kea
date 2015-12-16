// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/buffer.h>

#include <dns/labelsequence.h>
#include <dns/name.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <boost/functional/hash.hpp>

#include <string>
#include <vector>
#include <utility>
#include <set>

using namespace isc::dns;
using namespace std;

// XXX: this is defined as class static constants, but some compilers
// seemingly cannot find the symbols when used in the EXPECT_xxx macros.
const size_t LabelSequence::MAX_SERIALIZED_LENGTH;

namespace {

// Common check that two labelsequences are equal
void check_equal(const LabelSequence& ls1, const LabelSequence& ls2) {
    NameComparisonResult result = ls1.compare(ls2);
    EXPECT_EQ(isc::dns::NameComparisonResult::EQUAL,
              result.getRelation()) << ls1.toText() << " != " << ls2.toText();
    EXPECT_EQ(0, result.getOrder()) << ls1.toText() << " != " << ls2.toText();
    EXPECT_EQ(ls1.getLabelCount(), result.getCommonLabels());
}

// Common check for general comparison of two labelsequences
void check_compare(const LabelSequence& ls1, const LabelSequence& ls2,
                   isc::dns::NameComparisonResult::NameRelation relation,
                   size_t common_labels, bool check_order, int order=0) {
    NameComparisonResult result = ls1.compare(ls2);
    EXPECT_EQ(relation, result.getRelation());
    EXPECT_EQ(common_labels, result.getCommonLabels());
    if (check_order) {
        EXPECT_EQ(order, result.getOrder());
    }
}

class LabelSequenceTest : public ::testing::Test {
public:
    LabelSequenceTest() : n1("example.org"), n2("example.com"),
                          n3("example.org"), n4("foo.bar.test.example"),
                          n5("example.ORG"), n6("ExAmPlE.org"),
                          n7("."), n8("foo.example.org.bar"),
                          n9("\\000xample.org"),
                          n10("\\000xample.org"),
                          n11("\\000xample.com"),
                          n12("\\000xamplE.com"),
                          n_maxlabel("0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
                                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
                                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
                                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
                                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
                                     "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
                                     "0.1.2.3.4.5.6"),
                          ls1(n1), ls2(n2), ls3(n3), ls4(n4), ls5(n5),
                          ls6(n6), ls7(n7), ls8(n8),
                          ls9(n9), ls10(n10), ls11(n11), ls12(n12)
    {};
    // Need to keep names in scope for at least the lifetime of
    // the labelsequences
    Name n1, n2, n3, n4, n5, n6, n7, n8;
    Name n9, n10, n11, n12;
    const Name n_maxlabel;

    LabelSequence ls1, ls2, ls3, ls4, ls5, ls6, ls7, ls8;
    LabelSequence ls9, ls10, ls11, ls12;
};

// Basic equality tests
TEST_F(LabelSequenceTest, equals_sensitive) {
    EXPECT_TRUE(ls1.equals(ls1, true));
    EXPECT_FALSE(ls1.equals(ls2, true));
    EXPECT_TRUE(ls1.equals(ls3, true));
    EXPECT_FALSE(ls1.equals(ls4, true));
    EXPECT_FALSE(ls1.equals(ls5, true));
    EXPECT_FALSE(ls1.equals(ls6, true));
    EXPECT_FALSE(ls1.equals(ls7, true));
    EXPECT_FALSE(ls1.equals(ls8, true));

    EXPECT_FALSE(ls2.equals(ls1, true));
    EXPECT_TRUE(ls2.equals(ls2, true));
    EXPECT_FALSE(ls2.equals(ls3, true));
    EXPECT_FALSE(ls2.equals(ls4, true));
    EXPECT_FALSE(ls2.equals(ls5, true));
    EXPECT_FALSE(ls2.equals(ls6, true));
    EXPECT_FALSE(ls2.equals(ls7, true));
    EXPECT_FALSE(ls2.equals(ls8, true));

    EXPECT_FALSE(ls4.equals(ls1, true));
    EXPECT_FALSE(ls4.equals(ls2, true));
    EXPECT_FALSE(ls4.equals(ls3, true));
    EXPECT_TRUE(ls4.equals(ls4, true));
    EXPECT_FALSE(ls4.equals(ls5, true));
    EXPECT_FALSE(ls4.equals(ls6, true));
    EXPECT_FALSE(ls4.equals(ls7, true));
    EXPECT_FALSE(ls4.equals(ls8, true));

    EXPECT_FALSE(ls5.equals(ls1, true));
    EXPECT_FALSE(ls5.equals(ls2, true));
    EXPECT_FALSE(ls5.equals(ls3, true));
    EXPECT_FALSE(ls5.equals(ls4, true));
    EXPECT_TRUE(ls5.equals(ls5, true));
    EXPECT_FALSE(ls5.equals(ls6, true));
    EXPECT_FALSE(ls5.equals(ls7, true));
    EXPECT_FALSE(ls5.equals(ls8, true));

    EXPECT_TRUE(ls9.equals(ls10, true));
    EXPECT_FALSE(ls9.equals(ls11, true));
    EXPECT_FALSE(ls9.equals(ls12, true));
    EXPECT_FALSE(ls11.equals(ls12, true));
}

TEST_F(LabelSequenceTest, equals_insensitive) {
    EXPECT_TRUE(ls1.equals(ls1));
    EXPECT_FALSE(ls1.equals(ls2));
    EXPECT_TRUE(ls1.equals(ls3));
    EXPECT_FALSE(ls1.equals(ls4));
    EXPECT_TRUE(ls1.equals(ls5));
    EXPECT_TRUE(ls1.equals(ls6));
    EXPECT_FALSE(ls1.equals(ls7));

    EXPECT_FALSE(ls2.equals(ls1));
    EXPECT_TRUE(ls2.equals(ls2));
    EXPECT_FALSE(ls2.equals(ls3));
    EXPECT_FALSE(ls2.equals(ls4));
    EXPECT_FALSE(ls2.equals(ls5));
    EXPECT_FALSE(ls2.equals(ls6));
    EXPECT_FALSE(ls2.equals(ls7));

    EXPECT_TRUE(ls3.equals(ls1));
    EXPECT_FALSE(ls3.equals(ls2));
    EXPECT_TRUE(ls3.equals(ls3));
    EXPECT_FALSE(ls3.equals(ls4));
    EXPECT_TRUE(ls3.equals(ls5));
    EXPECT_TRUE(ls3.equals(ls6));
    EXPECT_FALSE(ls3.equals(ls7));

    EXPECT_FALSE(ls4.equals(ls1));
    EXPECT_FALSE(ls4.equals(ls2));
    EXPECT_FALSE(ls4.equals(ls3));
    EXPECT_TRUE(ls4.equals(ls4));
    EXPECT_FALSE(ls4.equals(ls5));
    EXPECT_FALSE(ls4.equals(ls6));
    EXPECT_FALSE(ls4.equals(ls7));

    EXPECT_TRUE(ls5.equals(ls1));
    EXPECT_FALSE(ls5.equals(ls2));
    EXPECT_TRUE(ls5.equals(ls3));
    EXPECT_FALSE(ls5.equals(ls4));
    EXPECT_TRUE(ls5.equals(ls5));
    EXPECT_TRUE(ls5.equals(ls6));
    EXPECT_FALSE(ls5.equals(ls7));

    EXPECT_TRUE(ls9.equals(ls10));
    EXPECT_FALSE(ls9.equals(ls11));
    EXPECT_FALSE(ls9.equals(ls12));
    EXPECT_TRUE(ls11.equals(ls12));
}

// operator==().  This is mostly trivial wrapper, so it should suffice to
// check some basic cases.
TEST_F(LabelSequenceTest, operatorEqual) {
    // cppcheck-suppress duplicateExpression
    EXPECT_TRUE(ls1 == ls1);      // self equivalence
    EXPECT_TRUE(ls1 == LabelSequence(n1)); // equivalent two different objects
    EXPECT_FALSE(ls1 == ls2);      // non equivalent objects
    EXPECT_TRUE(ls1 == ls5);       // it's always case insensitive
}

// Compare tests
TEST_F(LabelSequenceTest, compare) {
    // "example.org." and "example.org.", case sensitive
    NameComparisonResult result = ls1.compare(ls3, true);
    EXPECT_EQ(isc::dns::NameComparisonResult::EQUAL,
              result.getRelation());
    EXPECT_EQ(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    // "example.org." and "example.ORG.", case sensitive
    result = ls3.compare(ls5, true);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(1, result.getCommonLabels());

    // "example.org." and "example.ORG.", case in-sensitive
    result = ls3.compare(ls5);
    EXPECT_EQ(isc::dns::NameComparisonResult::EQUAL,
              result.getRelation());
    EXPECT_EQ(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    Name na("a.example.org");
    Name nb("b.example.org");
    LabelSequence lsa(na);
    LabelSequence lsb(nb);

    // "a.example.org." and "b.example.org.", case in-sensitive
    result = lsa.compare(lsb);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    // "example.org." and "b.example.org.", case in-sensitive
    lsa.stripLeft(1);
    result = lsa.compare(lsb);
    EXPECT_EQ(isc::dns::NameComparisonResult::SUPERDOMAIN,
              result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    Name nc("g.f.e.d.c.example.org");
    LabelSequence lsc(nc);

    // "g.f.e.d.c.example.org." and "b.example.org" (not absolute), case
    // in-sensitive; the absolute one is always smaller.
    lsb.stripRight(1);
    result = lsc.compare(lsb);
    EXPECT_EQ(isc::dns::NameComparisonResult::NONE, result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(0, result.getCommonLabels());

    // "g.f.e.d.c.example.org." and "example.org.", case in-sensitive
    result = lsc.compare(ls1);
    EXPECT_EQ(isc::dns::NameComparisonResult::SUBDOMAIN,
              result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    // "e.d.c.example.org." and "example.org.", case in-sensitive
    lsc.stripLeft(2);
    result = lsc.compare(ls1);
    EXPECT_EQ(isc::dns::NameComparisonResult::SUBDOMAIN,
              result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    // "example.org." and "example.org.", case in-sensitive
    lsc.stripLeft(3);
    result = lsc.compare(ls1);
    EXPECT_EQ(isc::dns::NameComparisonResult::EQUAL,
              result.getRelation());
    EXPECT_EQ(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    // "." and "example.org.", case in-sensitive
    lsc.stripLeft(2);
    result = lsc.compare(ls1);
    EXPECT_EQ(isc::dns::NameComparisonResult::SUPERDOMAIN,
              result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(1, result.getCommonLabels());

    Name nd("a.b.c.isc.example.org");
    LabelSequence lsd(nd);
    Name ne("w.x.y.isc.EXAMPLE.org");
    LabelSequence lse(ne);

    // "a.b.c.isc.example.org." and "w.x.y.isc.EXAMPLE.org.",
    // case sensitive
    result = lsd.compare(lse, true);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(2, result.getCommonLabels());

    // "a.b.c.isc.example.org." and "w.x.y.isc.EXAMPLE.org.",
    // case in-sensitive
    result = lsd.compare(lse);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(4, result.getCommonLabels());

    // "isc.example.org." and "isc.EXAMPLE.org.", case sensitive
    lsd.stripLeft(3);
    lse.stripLeft(3);
    result = lsd.compare(lse, true);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(2, result.getCommonLabels());

    // "isc.example.org." and "isc.EXAMPLE.org.", case in-sensitive
    result = lsd.compare(lse);
    EXPECT_EQ(isc::dns::NameComparisonResult::EQUAL,
              result.getRelation());
    EXPECT_EQ(0, result.getOrder());
    EXPECT_EQ(4, result.getCommonLabels());

    Name nf("a.b.c.isc.example.org");
    LabelSequence lsf(nf);
    Name ng("w.x.y.isc.EXAMPLE.org");
    LabelSequence lsg(ng);

    // lsf: "a.b.c.isc.example.org."
    // lsg: "w.x.y.isc.EXAMPLE.org" (not absolute), case in-sensitive.
    // the absolute one is always smaller.
    lsg.stripRight(1);
    result = lsg.compare(lsf);  // lsg > lsf
    EXPECT_EQ(isc::dns::NameComparisonResult::NONE, result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(0, result.getCommonLabels());

    // "a.b.c.isc.example.org" (not absolute) and
    // "w.x.y.isc.EXAMPLE.org" (not absolute), case in-sensitive
    lsf.stripRight(1);
    result = lsg.compare(lsf);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(3, result.getCommonLabels());

    // "a.b.c.isc.example" (not absolute) and
    // "w.x.y.isc.EXAMPLE" (not absolute), case in-sensitive
    lsf.stripRight(1);
    lsg.stripRight(1);
    result = lsg.compare(lsf);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_LT(0, result.getOrder());
    EXPECT_EQ(2, result.getCommonLabels());

    // lsf: "a.b.c" (not absolute) and
    // lsg: "w.x.y" (not absolute), case in-sensitive; a.b.c < w.x.y;
    // no common labels.
    lsf.stripRight(2);
    lsg.stripRight(2);
    result = lsf.compare(lsg);
    EXPECT_EQ(isc::dns::NameComparisonResult::NONE, result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(0, result.getCommonLabels());

    // lsf2: a.b.cc (not absolute); a.b.c < a.b.cc, no common labels.
    const Name nf2("a.b.cc");
    LabelSequence lsf2(nf2);
    lsf2.stripRight(1);
    result = lsf.compare(lsf2);
    EXPECT_EQ(isc::dns::NameComparisonResult::NONE, result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(0, result.getCommonLabels());

    Name nh("aexample.org");
    LabelSequence lsh(nh);
    Name ni("bexample.org");
    LabelSequence lsi(ni);

    // "aexample.org" (not absolute) and
    // "bexample.org" (not absolute), case in-sensitive
    lsh.stripRight(1);
    lsi.stripRight(1);
    result = lsh.compare(lsi);
    EXPECT_EQ(isc::dns::NameComparisonResult::COMMONANCESTOR,
              result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(1, result.getCommonLabels());

    // "aexample" (not absolute) and
    // "bexample" (not absolute), case in-sensitive;
    // aexample < bexample; no common labels.
    lsh.stripRight(1);
    lsi.stripRight(1);
    result = lsh.compare(lsi);
    EXPECT_EQ(isc::dns::NameComparisonResult::NONE, result.getRelation());
    EXPECT_GT(0, result.getOrder());
    EXPECT_EQ(0, result.getCommonLabels());

    Name nj("example.org");
    LabelSequence lsj(nj);
    Name nk("example.org");
    LabelSequence lsk(nk);

    // "example.org" (not absolute) and
    // "example.org" (not absolute), case in-sensitive
    lsj.stripRight(1);
    lsk.stripRight(1);
    result = lsj.compare(lsk);
    EXPECT_EQ(isc::dns::NameComparisonResult::EQUAL,
              result.getRelation());
    EXPECT_EQ(0, result.getOrder());
    EXPECT_EQ(2, result.getCommonLabels());

    // "example" (not absolute) and
    // "example" (not absolute), case in-sensitive
    lsj.stripRight(1);
    lsk.stripRight(1);
    result = lsj.compare(lsk);
    EXPECT_EQ(isc::dns::NameComparisonResult::EQUAL,
              result.getRelation());
    EXPECT_EQ(0, result.getOrder());
    EXPECT_EQ(1, result.getCommonLabels());
}

void
getDataCheck(const uint8_t* expected_data, size_t expected_len,
             const LabelSequence& ls)
{
    size_t len;
    const uint8_t* data = ls.getData(&len);
    ASSERT_EQ(expected_len, len) << "Expected data: " << expected_data <<
                                    ", label sequence: " << ls;
    EXPECT_EQ(expected_len, ls.getDataLength()) <<
        "Expected data: " << expected_data <<
        ", label sequence: " << ls;
    for (size_t i = 0; i < len; ++i) {
        EXPECT_EQ(expected_data[i], data[i]) <<
          "Difference at pos " << i << ": Expected data: " << expected_data <<
          ", label sequence: " << ls;
    }
}

// Convenient data converter for expected data.  Label data must be of
// uint8_t*, while it's convenient if we can specify some test data in
// plain string (which is of char*).  This wrapper converts the latter to
// the former in a safer way.
void
getDataCheck(const char* expected_char_data, size_t expected_len,
             const LabelSequence& ls)
{
    const vector<uint8_t> expected_data(expected_char_data,
                                        expected_char_data + expected_len);
    getDataCheck(&expected_data[0], expected_len, ls);
}

TEST_F(LabelSequenceTest, getData) {
    getDataCheck("\007example\003org\000", 13, ls1);
    getDataCheck("\007example\003com\000", 13, ls2);
    getDataCheck("\007example\003org\000", 13, ls3);
    getDataCheck("\003foo\003bar\004test\007example\000", 22, ls4);
    getDataCheck("\007example\003ORG\000", 13, ls5);
    getDataCheck("\007ExAmPlE\003org\000", 13, ls6);
    getDataCheck("\000", 1, ls7);
};

TEST_F(LabelSequenceTest, stripLeft) {
    EXPECT_TRUE(ls1.equals(ls3));
    ls1.stripLeft(0);
    getDataCheck("\007example\003org\000", 13, ls1);
    EXPECT_TRUE(ls1.equals(ls3));
    ls1.stripLeft(1);
    getDataCheck("\003org\000", 5, ls1);
    EXPECT_FALSE(ls1.equals(ls3));
    ls1.stripLeft(1);
    getDataCheck("\000", 1, ls1);
    EXPECT_TRUE(ls1.equals(ls7));

    ls2.stripLeft(2);
    getDataCheck("\000", 1, ls2);
    EXPECT_TRUE(ls2.equals(ls7));
}

TEST_F(LabelSequenceTest, stripRight) {
    EXPECT_TRUE(ls1.equals(ls3));
    ls1.stripRight(1);
    getDataCheck("\007example\003org", 12, ls1);
    EXPECT_FALSE(ls1.equals(ls3));
    ls1.stripRight(1);
    getDataCheck("\007example", 8, ls1);
    EXPECT_FALSE(ls1.equals(ls3));

    ASSERT_FALSE(ls1.equals(ls2));
    ls2.stripRight(2);
    getDataCheck("\007example", 8, ls2);
    EXPECT_TRUE(ls1.equals(ls2));
}

TEST_F(LabelSequenceTest, stripOutOfRange) {
    EXPECT_THROW(ls1.stripLeft(100), isc::OutOfRange);
    EXPECT_THROW(ls1.stripLeft(5), isc::OutOfRange);
    EXPECT_THROW(ls1.stripLeft(4), isc::OutOfRange);
    EXPECT_THROW(ls1.stripLeft(3), isc::OutOfRange);
    getDataCheck("\007example\003org\000", 13, ls1);

    EXPECT_THROW(ls1.stripRight(100), isc::OutOfRange);
    EXPECT_THROW(ls1.stripRight(5), isc::OutOfRange);
    EXPECT_THROW(ls1.stripRight(4), isc::OutOfRange);
    EXPECT_THROW(ls1.stripRight(3), isc::OutOfRange);
    getDataCheck("\007example\003org\000", 13, ls1);
}

TEST_F(LabelSequenceTest, getLabelCount) {
    EXPECT_EQ(3, ls1.getLabelCount());
    ls1.stripLeft(0);
    EXPECT_EQ(3, ls1.getLabelCount());
    ls1.stripLeft(1);
    EXPECT_EQ(2, ls1.getLabelCount());
    ls1.stripLeft(1);
    EXPECT_EQ(1, ls1.getLabelCount());

    EXPECT_EQ(3, ls2.getLabelCount());
    ls2.stripRight(1);
    EXPECT_EQ(2, ls2.getLabelCount());
    ls2.stripRight(1);
    EXPECT_EQ(1, ls2.getLabelCount());

    EXPECT_EQ(3, ls3.getLabelCount());
    ls3.stripRight(2);
    EXPECT_EQ(1, ls3.getLabelCount());

    EXPECT_EQ(5, ls4.getLabelCount());
    ls4.stripRight(3);
    EXPECT_EQ(2, ls4.getLabelCount());

    EXPECT_EQ(3, ls5.getLabelCount());
    ls5.stripLeft(2);
    EXPECT_EQ(1, ls5.getLabelCount());
}

TEST_F(LabelSequenceTest, comparePart) {
    EXPECT_FALSE(ls1.equals(ls8));

    // strip root label from example.org.
    ls1.stripRight(1);
    // strip foo from foo.example.org.bar.
    ls8.stripLeft(1);
    // strip bar. (i.e. bar and root) too
    ls8.stripRight(2);

    EXPECT_TRUE(ls1.equals(ls8));

    // Data comparison
    size_t len;
    const uint8_t* data = ls1.getData(&len);
    getDataCheck(data, len, ls8);
}

TEST_F(LabelSequenceTest, isAbsolute) {
    ASSERT_TRUE(ls1.isAbsolute());

    ls1.stripLeft(1);
    ASSERT_TRUE(ls1.isAbsolute());
    ls1.stripRight(1);
    ASSERT_FALSE(ls1.isAbsolute());

    ASSERT_TRUE(ls2.isAbsolute());
    ls2.stripRight(1);
    ASSERT_FALSE(ls2.isAbsolute());

    ASSERT_TRUE(ls3.isAbsolute());
    ls3.stripLeft(2);
    ASSERT_TRUE(ls3.isAbsolute());
}

TEST_F(LabelSequenceTest, toText) {
    EXPECT_EQ(".", ls7.toText());

    EXPECT_EQ("example.org.", ls1.toText());
    ls1.stripLeft(1);
    EXPECT_EQ("org.", ls1.toText());
    ls1.stripLeft(1);
    EXPECT_EQ(".", ls1.toText());

    EXPECT_EQ("example.com.", ls2.toText());
    ls2.stripRight(1);
    EXPECT_EQ("example.com", ls2.toText());
    ls2.stripRight(1);
    EXPECT_EQ("example", ls2.toText());

    EXPECT_EQ("foo.example.org.bar.", ls8.toText());
    ls8.stripRight(2);
    EXPECT_EQ("foo.example.org", ls8.toText());

    EXPECT_EQ(".", ls7.toText());
    EXPECT_THROW(ls7.stripLeft(1), isc::OutOfRange);

    Name n_long1("012345678901234567890123456789"
                 "012345678901234567890123456789012."
                 "012345678901234567890123456789"
                 "012345678901234567890123456789012."
                 "012345678901234567890123456789"
                 "012345678901234567890123456789012."
                 "012345678901234567890123456789"
                 "0123456789012345678901234567890");
    LabelSequence ls_long1(n_long1);

    EXPECT_EQ("012345678901234567890123456789"
              "012345678901234567890123456789012."
              "012345678901234567890123456789"
              "012345678901234567890123456789012."
              "012345678901234567890123456789"
              "012345678901234567890123456789012."
              "012345678901234567890123456789"
              "0123456789012345678901234567890.", ls_long1.toText());
    ls_long1.stripRight(1);
    EXPECT_EQ("012345678901234567890123456789"
              "012345678901234567890123456789012."
              "012345678901234567890123456789"
              "012345678901234567890123456789012."
              "012345678901234567890123456789"
              "012345678901234567890123456789012."
              "012345678901234567890123456789"
              "0123456789012345678901234567890", ls_long1.toText());

    LabelSequence ls_long2(n_maxlabel);

    EXPECT_EQ("0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.", ls_long2.toText());
    ls_long2.stripRight(1);
    EXPECT_EQ("0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6.7.8.9.0.1.2.3.4.5.6.7.8.9."
              "0.1.2.3.4.5.6", ls_long2.toText());
    ls_long2.stripRight(125);
    EXPECT_EQ("0.1", ls_long2.toText());
}

// The following are test data used in the getHash test below.  Normally
// we use example/documentation domain names for testing, but in this case
// we'd specifically like to use more realistic data, and are intentionally
// using real-world samples: They are the NS names of root and some top level
// domains as of this test.
const char* const root_servers[] = {
    "a.root-servers.net", "b.root-servers.net", "c.root-servers.net",
    "d.root-servers.net", "e.root-servers.net", "f.root-servers.net",
    "g.root-servers.net", "h.root-servers.net", "i.root-servers.net",
    "j.root-servers.net", "k.root-servers.net", "l.root-servers.net",
    "m.root-servers.net", NULL
};

const char* const jp_servers[] = {
    "a.dns.jp", "b.dns.jp", "c.dns.jp", "d.dns.jp", "e.dns.jp",
    "f.dns.jp", "g.dns.jp", NULL
};
const char* const cn_servers[] = {
    "a.dns.cn", "b.dns.cn", "c.dns.cn", "d.dns.cn", "e.dns.cn",
    "ns.cernet.net", NULL
};
const char* const ca_servers[] = {
    "k.ca-servers.ca", "e.ca-servers.ca", "a.ca-servers.ca", "z.ca-servers.ca",
    "tld.isc-sns.net", "c.ca-servers.ca", "j.ca-servers.ca", "l.ca-servers.ca",
    "sns-pb.isc.org", "f.ca-servers.ca", NULL
};

// A helper function used in the getHash test below.
void
hashDistributionCheck(const char* const* servers) {
    const size_t BUCKETS = 64;  // constant used in the MessageRenderer
    set<Name> names;
    vector<size_t> hash_counts(BUCKETS);

    // Store all test names and their super domain names (excluding the
    // "root" label) in the set, calculates their hash values, and increments
    // the counter for the corresponding hash "bucket".
    for (size_t i = 0; servers[i] != NULL; ++i) {
        const Name name(servers[i]);
        for (size_t l = 0; l < name.getLabelCount() - 1; ++l) {
            pair<set<Name>::const_iterator, bool> ret =
                names.insert(name.split(l));
            if (ret.second) {
                hash_counts[LabelSequence((*ret.first)).getHash(false) %
                            BUCKETS]++;
            }
        }
    }

    // See how many conflicts we have in the buckets.  For the testing purpose
    // we expect there's at most 2 conflicts in each set, which is an
    // arbitrary choice (it should happen to succeed with the hash function
    // and data we are using; if it's not the case, maybe with an update to
    // the hash implementation, we should revise the test).
    for (size_t i = 0; i < BUCKETS; ++i) {
        EXPECT_GE(3, hash_counts[i]);
    }
}

TEST_F(LabelSequenceTest, getHash) {
    // Trivial case.  The same sequence should have the same hash.
    EXPECT_EQ(ls1.getHash(true), ls1.getHash(true));

    // Check the case-insensitive mode behavior.
    EXPECT_EQ(ls1.getHash(false), ls5.getHash(false));

    // Check that the distribution of hash values is "not too bad" (such as
    // everything has the same hash value due to a stupid bug).  It's
    // difficult to check such things reliably.  We do some ad hoc tests here.
    hashDistributionCheck(root_servers);
    hashDistributionCheck(jp_servers);
    hashDistributionCheck(cn_servers);
    hashDistributionCheck(ca_servers);
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(LabelSequenceTest, LeftShiftOperator) {
    ostringstream oss;
    oss << ls1;
    EXPECT_EQ(ls1.toText(), oss.str());
}

TEST_F(LabelSequenceTest, serialize) {
    // placeholder for serialized data.  We use a sufficiently large space
    // for testing the overwrapping cases below.
    uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH * 3];

    // vector to store expected and actual data
    vector<LabelSequence> actual_labelseqs;
    typedef pair<size_t, const uint8_t*> DataPair;
    vector<DataPair> expected;

    // An absolute sequence directly constructed from a valid name.
    // labels = 3, offset sequence = 0, 8, 12, data = "example.com."
    actual_labelseqs.push_back(ls1);
    const uint8_t expected_data1[] = {
        3, 0, 8, 12, 7, 'e', 'x', 'a', 'm', 'p', 'l', 'e',
        3, 'o', 'r', 'g', 0 };
    expected.push_back(DataPair(sizeof(expected_data1), expected_data1));

    // Strip the original one from right.
    // labels = 2, offset sequence = 0, 8, data = "example.com" (non absolute)
    LabelSequence ls_rstripped = ls1;
    ls_rstripped.stripRight(1);
    actual_labelseqs.push_back(ls_rstripped);
    const uint8_t expected_data2[] = {
        2, 0, 8, 7, 'e', 'x', 'a', 'm', 'p', 'l', 'e',
        3, 'o', 'r', 'g'};
    expected.push_back(DataPair(sizeof(expected_data2), expected_data2));

    // Strip the original one from left.
    // labels = 2, offset sequence = 0, 4, data = "com."
    // Note that offsets are adjusted so that they begin with 0.
    LabelSequence ls_lstripped = ls1;
    ls_lstripped.stripLeft(1);
    actual_labelseqs.push_back(ls_lstripped);
    const uint8_t expected_data3[] = { 2, 0, 4, 3, 'o', 'r', 'g', 0 };
    expected.push_back(DataPair(sizeof(expected_data3), expected_data3));

    // Root label.
    LabelSequence ls_root(Name::ROOT_NAME());
    actual_labelseqs.push_back(ls_root);
    const uint8_t expected_data4[] = { 1, 0, 0 };
    expected.push_back(DataPair(sizeof(expected_data4), expected_data4));

    // Non absolute single-label.
    LabelSequence ls_single = ls_rstripped;
    ls_single.stripRight(1);
    actual_labelseqs.push_back(ls_single);
    const uint8_t expected_data5[] = {
        1, 0, 7, 'e', 'x', 'a', 'm', 'p', 'l', 'e' };
    expected.push_back(DataPair(sizeof(expected_data5), expected_data5));

    // Labels containing a longest possible label
    const Name name_longlabel(std::string(63, 'x')); // 63 'x's
    LabelSequence ls_longlabel(name_longlabel);
    actual_labelseqs.push_back(ls_longlabel);
    vector<uint8_t> expected_data6;
    expected_data6.push_back(2); // 2 labels
    expected_data6.push_back(0); // 1st offset
    expected_data6.push_back(64); // 2nd offset
    expected_data6.push_back(63); // 1st label length
    expected_data6.insert(expected_data6.end(), 63, 'x'); // 1st label: 63 'x's
    expected_data6.push_back(0); // 2nd label: trailing 0
    expected.push_back(DataPair(expected_data6.size(), &expected_data6[0]));

    // Max number of labels and longest possible name
    EXPECT_EQ(Name::MAX_WIRE, n_maxlabel.getLength());
    LabelSequence ls_maxlabel(n_maxlabel);
    actual_labelseqs.push_back(ls_maxlabel);
    vector<uint8_t> expected_data7;
    expected_data7.push_back(Name::MAX_LABELS); // number of labels
    for (size_t i = 0; i < Name::MAX_LABELS; ++i) {
        expected_data7.push_back(i * 2); // each label has length and 1 byte
    }
    // Copy wire data of the name
    isc::util::OutputBuffer ob(0);
    n_maxlabel.toWire(ob);
    expected_data7.insert(expected_data7.end(),
                          static_cast<const uint8_t*>(ob.getData()),
                          static_cast<const uint8_t*>(ob.getData()) +
                          ob.getLength());
    expected.push_back(DataPair(expected_data7.size(), &expected_data7[0]));

    // For each data set, serialize the labels and compare the data to the
    // expected one.
    vector<DataPair>::const_iterator it = expected.begin();
    vector<LabelSequence>::const_iterator itl = actual_labelseqs.begin();
    for (; it != expected.end(); ++it, ++itl) {
        SCOPED_TRACE(itl->toText());

        const size_t serialized_len = itl->getSerializedLength();

        ASSERT_GE(LabelSequence::MAX_SERIALIZED_LENGTH, serialized_len);
        itl->serialize(labels_buf, serialized_len);
        EXPECT_EQ(it->first, serialized_len);
        EXPECT_EQ(0, memcmp(it->second, labels_buf, serialized_len));

        EXPECT_EQ(NameComparisonResult::EQUAL,
                  LabelSequence(labels_buf).compare(*itl).getRelation());

        // Shift the data to the middle of the buffer for overwrap check
        uint8_t* const bp = labels_buf;
        std::memcpy(bp + serialized_len, bp, serialized_len);
        // Memory layout is now as follows:
        //   <- ser_len ->          <- ser_len ------>
        // bp             bp+ser_len                  bp+(ser_len*2)
        //                           olen,odata,ndata

        // end of buffer would be the first byte of offsets: invalid.
        EXPECT_THROW(LabelSequence(bp + serialized_len).
                     serialize(bp + 2, serialized_len),
                     isc::BadValue);
        // begin of buffer would be the last byte of ndata: invalid.
        EXPECT_THROW(LabelSequence(bp + serialized_len).
                     serialize(bp + (2 * serialized_len) - 1, serialized_len),
                     isc::BadValue);
        // A boundary safe case: buffer is placed after the sequence data.
        // should cause no disruption.
        LabelSequence(bp + serialized_len).
                     serialize(bp + 2 * serialized_len, serialized_len);
        // A boundary safe case: buffer is placed before the sequence data
        // should cause no disruption. (but the original serialized data will
        // be overridden, so it can't be used any more)
        LabelSequence(bp + serialized_len).
                     serialize(bp + 1, serialized_len);
    }

    EXPECT_THROW(ls1.serialize(labels_buf, ls1.getSerializedLength() - 1),
                 isc::BadValue);
}

#ifdef ENABLE_DEBUG

// These checks are enabled only in debug mode in the LabelSequence
// class.
TEST_F(LabelSequenceTest, badDeserialize) {
    EXPECT_THROW(LabelSequence(NULL), isc::BadValue);
    const uint8_t zero_offsets[] = { 0 };
    EXPECT_THROW(LabelSequence ls(zero_offsets), isc::BadValue);
    const uint8_t toomany_offsets[] = { Name::MAX_LABELS + 1 };
    EXPECT_THROW(LabelSequence ls(toomany_offsets), isc::BadValue);

    // (second) offset does not match actual label length
    const uint8_t offsets_wrongoffset[] = { 2, 0, 64, 1 };
    EXPECT_THROW(LabelSequence ls(offsets_wrongoffset), isc::BadValue);

    // offset matches, but exceeds MAX_LABEL_LEN
    const uint8_t offsets_toolonglabel[] = { 2, 0, 64, 64 };
    EXPECT_THROW(LabelSequence ls(offsets_toolonglabel), isc::BadValue);

    // Inconsistent data: an offset is lower than the previous offset
    const uint8_t offsets_lower[] = { 3, // # of offsets
                                      0, 2, 1, // offsets
                                      1, 'a', 1, 'b', 0};
    EXPECT_THROW(LabelSequence ls(offsets_lower), isc::BadValue);

    // Inconsistent data: an offset is equal to the previous offset
    const uint8_t offsets_noincrease[] = { 2, 0, 0, 0, 0 };
    EXPECT_THROW(LabelSequence ls(offsets_noincrease), isc::BadValue);
}

#endif

namespace {

// Helper function; repeatedly calls
// - Initially, all three labelsequences should be the same
// - repeatedly performs:
//   - checks all three are equal
//   - stripLeft on ls1
//   - checks ls1 and ls2 are different, and ls2 and ls3 are equal
//   - stripLeft on ls2
//   - checks ls1 and ls2 are equal, and ls2 and ls3 are different
//   - stripLeft on ls3
//
// (this test makes sure the stripLeft of one has no effect on the other
// two, and that the strip properties hold regardless of how they were
// constructed)
//
void stripLeftCheck(LabelSequence ls1, LabelSequence ls2, LabelSequence ls3) {
    ASSERT_LT(1, ls1.getLabelCount());
    while (ls1.getLabelCount() > 1) {
        check_equal(ls1, ls2);
        check_equal(ls2, ls3);

        ls1.stripLeft(1);
        check_compare(ls1, ls2, isc::dns::NameComparisonResult::SUPERDOMAIN,
                      ls1.getLabelCount(), true, -1);
        check_equal(ls2, ls3);

        ls2.stripLeft(1);
        check_equal(ls1, ls2);
        check_compare(ls2, ls3, isc::dns::NameComparisonResult::SUPERDOMAIN,
                      ls1.getLabelCount(), true, -1);

        ls3.stripLeft(1);
    }
}

// Similar to stripLeftCheck, but using stripRight()
void stripRightCheck(LabelSequence ls1, LabelSequence ls2, LabelSequence ls3) {
    ASSERT_LT(1, ls1.getLabelCount());
    while (ls1.getLabelCount() > 1) {
        check_equal(ls1, ls2);
        check_equal(ls2, ls3);

        ls1.stripRight(1);
        check_compare(ls1, ls2, isc::dns::NameComparisonResult::NONE, 0,
                      false);
        check_equal(ls2, ls3);

        ls2.stripRight(1);
        check_equal(ls1, ls2);
        check_compare(ls2, ls3, isc::dns::NameComparisonResult::NONE, 0,
                      false);

        ls3.stripRight(1);
    }
}

} // end anonymous namespace

class ExtendableLabelSequenceTest : public ::testing::Test {
public:
    ExtendableLabelSequenceTest() : bar("bar."),
                                    example_org("example.org"),
                                    foo("foo."),
                                    foo_bar("foo.bar."),
                                    foo_bar_example_org("foo.bar.example.org."),
                                    foo_bar_foo_bar("foo.bar.foo.bar."),
                                    foo_example("foo.example."),
                                    org("org")
    {
        // explicitly set to non-zero data, to make sure
        // we don't try to use data we don't set
        memset(buf, 0xff, LabelSequence::MAX_SERIALIZED_LENGTH);
    }

    Name bar;
    Name example_org;
    Name foo;
    Name foo_bar;
    Name foo_bar_example_org;
    Name foo_bar_foo_bar;
    Name foo_example;
    Name org;

    uint8_t buf[LabelSequence::MAX_SERIALIZED_LENGTH];
};

// Test that 'extendable' labelsequences behave correctly when using
// stripLeft() and stripRight()
TEST_F(ExtendableLabelSequenceTest, extendableLabelSequence) {
    LabelSequence ls1(example_org);
    LabelSequence ls2(example_org);

    LabelSequence els(ls1, buf);
    // ls1 is absolute, so els should be too
    EXPECT_TRUE(els.isAbsolute());
    check_equal(ls1, els);

    ASSERT_EQ(ls1.getDataLength(), els.getDataLength());
    stripLeftCheck(ls1, els, ls2);
    stripRightCheck(ls1, els, ls2);

    // Creating an extendable labelsequence from a non-absolute
    // label sequence should result in a non-absolute label sequence
    ls1.stripRight(1);
    els = LabelSequence(ls1, buf);
    EXPECT_FALSE(els.isAbsolute());
    check_equal(ls1, els);

    // and extending with the root label should make it absolute again
    els.extend(LabelSequence(Name(".")), buf);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(ls2, els);
}

// Test that 'extendable' LabelSequences behave correctly when initialized
// with a stripped source LabelSequence
TEST_F(ExtendableLabelSequenceTest, extendableLabelSequenceLeftStrippedSource) {
    LabelSequence ls1(foo_bar_example_org);
    LabelSequence ls2(foo_bar_example_org);

    while (ls1.getLabelCount() > 2) {
        ls1.stripLeft(1);
        ls2.stripLeft(1);

        LabelSequence els(ls1, buf);

        ASSERT_EQ(ls1.getDataLength(), els.getDataLength());
        stripLeftCheck(ls1, els, ls2);
        stripRightCheck(ls1, els, ls2);
    }
}

TEST_F(ExtendableLabelSequenceTest, extendableLabelSequenceRightStrippedSource) {
    LabelSequence ls1(foo_bar_example_org);
    LabelSequence ls2(foo_bar_example_org);

    while (ls1.getLabelCount() > 2) {
        ls1.stripRight(1);
        ls2.stripRight(1);

        LabelSequence els(ls1, buf);

        ASSERT_EQ(ls1.getDataLength(), els.getDataLength());
        stripLeftCheck(ls1, els, ls2);
        stripRightCheck(ls1, els, ls2);
    }
}

// Check some basic 'extend' functionality
TEST_F(ExtendableLabelSequenceTest, extend) {
    LabelSequence ls1(foo_bar);
    LabelSequence ls2(foo);
    LabelSequence ls3(bar);
    LabelSequence ls4(foo_bar);

    LabelSequence els(ls2, buf);

    check_compare(ls1, els, isc::dns::NameComparisonResult::COMMONANCESTOR, 1,
                  true, -4);
    els.extend(ls3, buf);
    EXPECT_TRUE(els.isAbsolute());

    check_equal(ls1, els);
    stripLeftCheck(ls1, els, ls4);
    stripRightCheck(ls1, els, ls4);

    // strip, then extend again
    els.stripRight(2); // (2, 1 for root label, 1 for last label)
    els.extend(ls3, buf);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(ls1, els);

    // Extending again should make it different
    els.extend(ls3, buf);
    EXPECT_TRUE(els.isAbsolute());
    check_compare(ls1, els, isc::dns::NameComparisonResult::COMMONANCESTOR, 2,
                  true, 4);

    // Extending with a non-absolute name should make it non-absolute as well
    ls3.stripRight(1);
    els.extend(ls3, buf);
    EXPECT_FALSE(els.isAbsolute());

    Name check_name("foo.bar.bar.bar");
    LabelSequence check_ls(check_name);
    check_ls.stripRight(1);
    check_equal(check_ls, els);

    // And try extending when both are not absolute
    els.stripRight(3);
    ls1.stripRight(1);
    EXPECT_FALSE(els.isAbsolute());
    els.extend(ls3, buf);
    EXPECT_FALSE(els.isAbsolute());
    check_equal(ls1, els);

    // Extending non-absolute with absolute should make it absolute again
    EXPECT_FALSE(els.isAbsolute());
    els.extend(LabelSequence(Name("absolute.")), buf);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(LabelSequence(Name("foo.bar.absolute")), els);
}

TEST_F(ExtendableLabelSequenceTest, extendLeftStripped) {
    LabelSequence ls1(foo_example);
    LabelSequence ls2(example_org);
    LabelSequence ls3(org);

    LabelSequence els(ls1, buf);

    els.stripLeft(1);
    els.extend(ls3, buf);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(ls2, els);
}

// Check that when extending with itself, it does not cause horrible failures
TEST_F(ExtendableLabelSequenceTest, extendWithItself) {
    LabelSequence ls1(foo_bar);
    LabelSequence ls2(foo_bar_foo_bar);

    LabelSequence els(ls1, buf);

    els.extend(els, buf);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(ls2, els);

    // Also try for non-absolute names
    ls2.stripRight(1);
    els = LabelSequence(ls1, buf);
    els.stripRight(1);
    els.extend(els, buf);
    EXPECT_FALSE(els.isAbsolute());
    check_equal(ls2, els);

    // Once more, now start out with non-absolute labelsequence
    ls1.stripRight(1);
    els = LabelSequence(ls1, buf);
    els.extend(els, buf);
    EXPECT_FALSE(els.isAbsolute());
    check_equal(ls2, els);
}

// Test that 'extending' with just a root label is a no-op, iff the original
// was already absolute
TEST_F(ExtendableLabelSequenceTest, extendWithRoot) {
    LabelSequence ls1(example_org);

    LabelSequence els(LabelSequence(ls1, buf));
    check_equal(ls1, els);
    els.extend(LabelSequence(Name(".")), buf);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(ls1, els);

    // but not if the original was not absolute (it will be equal to
    // the original labelsequence used above, but not the one it was based
    // on).
    LabelSequence ls2(example_org);
    ls2.stripRight(1);
    els = LabelSequence(ls2, buf);
    EXPECT_FALSE(els.isAbsolute());
    els.extend(LabelSequence(Name(".")), buf);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(ls1, els);
    check_compare(ls2, els, isc::dns::NameComparisonResult::NONE, 0, true, 3);
}

// Check possible failure modes of extend()
TEST_F(ExtendableLabelSequenceTest, extendBadData) {
    LabelSequence ls1(example_org);

    LabelSequence els(ls1, buf);

    // try use with unrelated labelsequence
    EXPECT_THROW(ls1.extend(ls1, buf), isc::BadValue);

    // Create a long name, but so that we can still extend once
    Name longlabel("1234567890123456789012345678901234567890"
                   "12345678901234567890");
    LabelSequence long_ls(longlabel);
    els = LabelSequence(long_ls, buf);
    els.extend(els, buf);
    els.extend(long_ls, buf);
    els.extend(long_ls, buf);
    ASSERT_EQ(245, els.getDataLength());
    // Extending once more with 10 bytes should still work
    els.extend(LabelSequence(Name("123456789")), buf);
    EXPECT_TRUE(els.isAbsolute());

    // Extended label sequence should now look like
    const Name full_name(
        "123456789012345678901234567890123456789012345678901234567890."
        "123456789012345678901234567890123456789012345678901234567890."
        "123456789012345678901234567890123456789012345678901234567890."
        "123456789012345678901234567890123456789012345678901234567890."
        "123456789.");
    const LabelSequence full_ls(full_name);
    check_equal(full_ls, els);

    // But now, even the shortest extension should fail
    EXPECT_THROW(els.extend(LabelSequence(Name("1")), buf), isc::BadValue);

    // Check it hasn't been changed
    EXPECT_TRUE(els.isAbsolute());
    check_equal(full_ls, els);

    // Also check that extending past MAX_LABELS is not possible
    Name shortname("1.");
    LabelSequence short_ls(shortname);
    els = LabelSequence(short_ls, buf);
    for (size_t i=0; i < 126; ++i) {
        els.extend(short_ls, buf);
    }

    // Should now look like this
    const Name full_name2(
        "1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1."
        "1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1."
        "1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1."
        "1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1.1."
        "1.1.1.1.1.1.1.");
    const LabelSequence full_ls2(full_name2);
    EXPECT_TRUE(els.isAbsolute());
    check_equal(full_ls2, els);

    EXPECT_THROW(els.extend(short_ls, buf), isc::BadValue);

    EXPECT_TRUE(els.isAbsolute());
    check_equal(full_ls2, els);
}

// Check the static fixed 'wildcard' LabelSequence
TEST(WildCardLabelSequence, wildcard) {
    ASSERT_FALSE(LabelSequence::WILDCARD().isAbsolute());
    ASSERT_EQ("*", LabelSequence::WILDCARD().toText());
}

}
