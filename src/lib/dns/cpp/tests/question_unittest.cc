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

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include "unittest_util.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;

namespace {
class QuestionTest : public ::testing::Test {
protected:
    QuestionTest() : obuffer(0), renderer(obuffer),
                     test_question(Name("example.com"), RRClass::IN(),
                                   RRType::NS()) 
    {}
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Question test_question;
    static const uint8_t wiredata[];
};

// wire-format representation of "example.com. NS IN"
const uint8_t QuestionTest::wiredata[] = { 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70,
                                           0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d,
                                           0x00, 0x00, 0x02, 0x00, 0x01 };

TEST_F(QuestionTest, fromWire)
{
    InputBuffer ibuffer(wiredata, sizeof(wiredata));
    Question q(ibuffer);
    EXPECT_EQ(test_question, q);
}

TEST_F(QuestionTest, toText)
{
    EXPECT_EQ("example.com. IN NS\n", test_question.toText());
}

TEST_F(QuestionTest, toWire)
{
    test_question.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, obuffer.getData(),
                        obuffer.getLength(), wiredata, sizeof(wiredata));
}
}
