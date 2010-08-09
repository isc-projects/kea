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

// $Id$

#include <vector>
#include <sstream>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;

namespace {
class QuestionTest : public ::testing::Test {
protected:
    QuestionTest() : obuffer(0), renderer(obuffer),
                     example_name1(Name("foo.example.com")),
                     example_name2(Name("bar.example.com")),
                     test_question1(example_name1, RRClass::IN(),
                                    RRType::NS()),
                     test_question2(example_name2, RRClass::CH(),
                                    RRType::A())
    {}
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Name example_name1;
    Name example_name2;
    Question test_question1;
    Question test_question2;
    vector<unsigned char> wiredata;
};

Question
questionFromWire(const char* datafile, size_t position = 0)
{
    vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    buffer.setPosition(position);

    return (Question(buffer));
}

TEST_F(QuestionTest, fromWire)
{
    Question q = questionFromWire("question_fromWire");

    EXPECT_EQ(example_name1, q.getName());
    EXPECT_EQ(RRClass::IN(), q.getClass());
    EXPECT_EQ(RRType::NS(), q.getType());

    // owner name of the second Question is compressed.  It's uncommon
    // (to have multiple questions), but isn't prohibited by the protocol.
    q = questionFromWire("question_fromWire", 21);
    EXPECT_EQ(example_name2, q.getName());
    EXPECT_EQ(RRClass::CH(), q.getClass());
    EXPECT_EQ(RRType::A(), q.getType());

    // Pathological cases: Corresponding exceptions will be thrown from
    // the underlying parser.
    EXPECT_THROW(questionFromWire("question_fromWire", 31), DNSMessageFORMERR);
    EXPECT_THROW(questionFromWire("question_fromWire", 36), IncompleteRRClass);
}

TEST_F(QuestionTest, toText)
{
    EXPECT_EQ("foo.example.com. IN NS\n", test_question1.toText());
    EXPECT_EQ("bar.example.com. CH A\n", test_question2.toText());
}

TEST_F(QuestionTest, toWireBuffer)
{
    test_question1.toWire(obuffer);
    test_question2.toWire(obuffer);
    UnitTestUtil::readWireData("question_toWire1", wiredata);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, obuffer.getData(),
                        obuffer.getLength(), &wiredata[0], wiredata.size());
}

TEST_F(QuestionTest, toWireRenderer)
{
    test_question1.toWire(renderer);
    test_question2.toWire(renderer);
    UnitTestUtil::readWireData("question_toWire2", wiredata);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, obuffer.getData(),
                        obuffer.getLength(), &wiredata[0], wiredata.size());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(QuestionTest, LeftShiftOperator)
{
    ostringstream oss;
    oss << test_question1;
    EXPECT_EQ(test_question1.toText(), oss.str());
}

TEST_F(QuestionTest, comparison)
{
    const Name a("a"), b("b");
    const RRClass in(RRClass::IN()), ch(RRClass::CH());
    const RRType ns(RRType::NS()), aaaa(RRType::AAAA());

    EXPECT_TRUE(Question(a, in, ns) < Question(a, in, aaaa));
    EXPECT_FALSE(Question(a, in, aaaa) < Question(a, in, ns));

    EXPECT_TRUE(Question(a, in, ns) < Question(a, ch, ns));
    EXPECT_FALSE(Question(a, ch, ns) < Question(a, in, ns));

    EXPECT_TRUE(Question(a, in, ns) < Question(a, ch, aaaa));
    EXPECT_FALSE(Question(a, ch, aaaa) < Question(a, in, ns));

    EXPECT_TRUE(Question(a, in, ns) < Question(b, in, ns));
    EXPECT_FALSE(Question(a, in, ns) < Question(a, in, ns));

    EXPECT_TRUE(Question(a, in, ns) < Question(b, ch, ns));
    EXPECT_FALSE(Question(b, ch, ns) < Question(a, in, ns));

    EXPECT_TRUE(Question(a, in, ns) < Question(b, ch, aaaa));
    EXPECT_FALSE(Question(b, ch, aaaa) < Question(a, in, ns));

    EXPECT_FALSE(Question(a, in, ns) < Question(a, in, ns));
    EXPECT_FALSE(Question(a, ch, ns) < Question(a, ch, ns));
    EXPECT_FALSE(Question(b, in, ns) < Question(b, in, ns));
    EXPECT_FALSE(Question(b, in, aaaa) < Question(b, in, aaaa));
}

}
