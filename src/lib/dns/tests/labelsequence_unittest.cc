// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/labelsequence.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

using namespace isc::dns;

class LabelSequenceTest : public ::testing::Test {
public:
    LabelSequenceTest() : n1("example.org"), n2("example.com"),
                          n3("example.org"), n4("foo.bar.test.example"),
                          n5("example.ORG"), n6("ExAmPlE.org"),
                          n7("."), n8("foo.example.org.bar"),
                          ls1(n1), ls2(n2), ls3(n3), ls4(n4), ls5(n5),
                          ls6(n6), ls7(n7), ls8(n8)
    {};
    // Need to keep names in scope for at least the lifetime of
    // the labelsequences
    Name n1, n2, n3, n4, n5, n6, n7, n8;

    LabelSequence ls1, ls2, ls3, ls4, ls5, ls6, ls7, ls8;
};

// Basic equality tests
TEST_F(LabelSequenceTest, equals_sensitive) {
    EXPECT_TRUE(ls1.equals(ls1));
    EXPECT_FALSE(ls1.equals(ls2));
    EXPECT_TRUE(ls1.equals(ls3));
    EXPECT_FALSE(ls1.equals(ls4));
    EXPECT_FALSE(ls1.equals(ls5));
    EXPECT_FALSE(ls1.equals(ls6));
    EXPECT_FALSE(ls1.equals(ls7));
    EXPECT_FALSE(ls1.equals(ls8));

    EXPECT_FALSE(ls2.equals(ls1));
    EXPECT_TRUE(ls2.equals(ls2));
    EXPECT_FALSE(ls2.equals(ls3));
    EXPECT_FALSE(ls2.equals(ls4));
    EXPECT_FALSE(ls2.equals(ls5));
    EXPECT_FALSE(ls2.equals(ls6));
    EXPECT_FALSE(ls2.equals(ls7));
    EXPECT_FALSE(ls2.equals(ls8));

    EXPECT_FALSE(ls4.equals(ls1));
    EXPECT_FALSE(ls4.equals(ls2));
    EXPECT_FALSE(ls4.equals(ls3));
    EXPECT_TRUE(ls4.equals(ls4));
    EXPECT_FALSE(ls4.equals(ls5));
    EXPECT_FALSE(ls4.equals(ls6));
    EXPECT_FALSE(ls4.equals(ls7));
    EXPECT_FALSE(ls4.equals(ls8));

    EXPECT_FALSE(ls5.equals(ls1));
    EXPECT_FALSE(ls5.equals(ls2));
    EXPECT_FALSE(ls5.equals(ls3));
    EXPECT_FALSE(ls5.equals(ls4));
    EXPECT_TRUE(ls5.equals(ls5));
    EXPECT_FALSE(ls5.equals(ls6));
    EXPECT_FALSE(ls5.equals(ls7));
    EXPECT_FALSE(ls5.equals(ls8));
}

TEST_F(LabelSequenceTest, equals_insensitive) {
    EXPECT_TRUE(ls1.equals(ls1, true));
    EXPECT_FALSE(ls1.equals(ls2, true));
    EXPECT_TRUE(ls1.equals(ls3, true));
    EXPECT_FALSE(ls1.equals(ls4, true));
    EXPECT_TRUE(ls1.equals(ls5, true));
    EXPECT_TRUE(ls1.equals(ls6, true));
    EXPECT_FALSE(ls1.equals(ls7, true));

    EXPECT_FALSE(ls2.equals(ls1, true));
    EXPECT_TRUE(ls2.equals(ls2, true));
    EXPECT_FALSE(ls2.equals(ls3, true));
    EXPECT_FALSE(ls2.equals(ls4, true));
    EXPECT_FALSE(ls2.equals(ls5, true));
    EXPECT_FALSE(ls2.equals(ls6, true));
    EXPECT_FALSE(ls2.equals(ls7, true));

    EXPECT_TRUE(ls3.equals(ls1, true));
    EXPECT_FALSE(ls3.equals(ls2, true));
    EXPECT_TRUE(ls3.equals(ls3, true));
    EXPECT_FALSE(ls3.equals(ls4, true));
    EXPECT_TRUE(ls3.equals(ls5, true));
    EXPECT_TRUE(ls3.equals(ls6, true));
    EXPECT_FALSE(ls3.equals(ls7, true));

    EXPECT_FALSE(ls4.equals(ls1, true));
    EXPECT_FALSE(ls4.equals(ls2, true));
    EXPECT_FALSE(ls4.equals(ls3, true));
    EXPECT_TRUE(ls4.equals(ls4, true));
    EXPECT_FALSE(ls4.equals(ls5, true));
    EXPECT_FALSE(ls4.equals(ls6, true));
    EXPECT_FALSE(ls4.equals(ls7, true));

    EXPECT_TRUE(ls5.equals(ls1, true));
    EXPECT_FALSE(ls5.equals(ls2, true));
    EXPECT_TRUE(ls5.equals(ls3, true));
    EXPECT_FALSE(ls5.equals(ls4, true));
    EXPECT_TRUE(ls5.equals(ls5, true));
    EXPECT_TRUE(ls5.equals(ls6, true));
    EXPECT_FALSE(ls5.equals(ls7, true));
}

void
getDataCheck(const char* expected_data, size_t expected_len,
             const LabelSequence& ls)
{
    size_t len;
    const char* data = ls.getData(&len);
    ASSERT_EQ(expected_len, len) << "Expected data: " << expected_data <<
                                    " name: " << ls.getName().toText();
    EXPECT_EQ(expected_len, ls.getDataLength()) <<
        "Expected data: " << expected_data <<
        " name: " << ls.getName().toText();
    for (size_t i = 0; i < len; ++i) {
        EXPECT_EQ(expected_data[i], data[i]) << "Difference at pos " << i <<
                                                ": Expected data: " <<
                                                expected_data <<
                                                " name: " <<
                                                ls.getName().toText();;
    }
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
    const char* data = ls1.getData(&len);
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
