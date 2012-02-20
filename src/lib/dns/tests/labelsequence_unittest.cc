// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>

using namespace isc::dns;

class LabelSequenceTest : public ::testing::Test {
public:
    LabelSequenceTest() : ls1(Name("example.org")),
                          ls2(Name("example.com")),
                          ls3(Name("example.org")),
                          ls4(Name("foo.bar")),
                          ls5(Name("example.ORG")),
                          ls6(Name("ExAmPlE.org")),
                          ls7(Name("."))
    {};

    LabelSequence ls1;
    LabelSequence ls2;
    LabelSequence ls3;
    LabelSequence ls4;
    LabelSequence ls5;
    LabelSequence ls6;
    LabelSequence ls7;
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
    EXPECT_FALSE(ls3.equals(ls5));
    EXPECT_FALSE(ls3.equals(ls6));
    EXPECT_FALSE(ls3.equals(ls7));

    EXPECT_FALSE(ls4.equals(ls1));
    EXPECT_FALSE(ls4.equals(ls2));
    EXPECT_FALSE(ls4.equals(ls3));
    EXPECT_TRUE(ls4.equals(ls4));
    EXPECT_FALSE(ls4.equals(ls5));
    EXPECT_FALSE(ls4.equals(ls6));
    EXPECT_FALSE(ls4.equals(ls7));
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
}


TEST_F(LabelSequenceTest, getData) {
    EXPECT_STREQ("\007example\003org\0", ls1.getData());
    EXPECT_STREQ("\007example\003com\0", ls2.getData());
    EXPECT_STREQ("\007example\003org\0", ls3.getData());
    EXPECT_STREQ("\003foo\003bar\0", ls4.getData());
    EXPECT_STREQ("\007example\003ORG\0", ls5.getData());
    EXPECT_STREQ("\007ExAmPlE\003org\0", ls6.getData());
    EXPECT_STREQ("\0", ls7.getData());
};

TEST_F(LabelSequenceTest, split_pos) {
    ls1.split(0);
    EXPECT_STREQ("\007example\003org\0", ls1.getData());
    ls1.split(1);
    EXPECT_STREQ("\003org\0", ls1.getData());
    ls1.split(1);
    EXPECT_STREQ("\0", ls1.getData());
    EXPECT_TRUE(ls1.equals(ls7));

    ls2.split(2);
    EXPECT_STREQ("\0", ls2.getData());
    EXPECT_TRUE(ls2.equals(ls7));
}

TEST_F(LabelSequenceTest, split_neg) {
    ls1.split(0);
    EXPECT_STREQ("\007example\003org\0", ls1.getData());
    ls1.split(-1);
    EXPECT_STREQ("\007example\0", ls1.getData());
    ls1.split(-1);
    EXPECT_STREQ("\0", ls1.getData());
    EXPECT_TRUE(ls1.equals(ls7));

    ls2.split(-2);
    EXPECT_STREQ("\0", ls2.getData());
    EXPECT_TRUE(ls2.equals(ls7));
}

TEST_F(LabelSequenceTest, getLabelCount) {
    EXPECT_EQ(3, ls1.getLabelCount());
    ls1.split(0);
    EXPECT_EQ(3, ls1.getLabelCount());
    ls1.split(1);
    EXPECT_EQ(2, ls1.getLabelCount());
    ls1.split(1);
    EXPECT_EQ(1, ls1.getLabelCount());

    EXPECT_EQ(3, ls2.getLabelCount());
    ls2.split(2);
    EXPECT_EQ(1, ls2.getLabelCount());

    EXPECT_EQ(3, ls3.getLabelCount());
    ls3.split(-1);
    EXPECT_EQ(2, ls3.getLabelCount());
    ls3.split(-1);
    EXPECT_EQ(1, ls3.getLabelCount());

    EXPECT_EQ(3, ls4.getLabelCount());
    ls4.split(-2);
    EXPECT_EQ(1, ls4.getLabelCount());
}
