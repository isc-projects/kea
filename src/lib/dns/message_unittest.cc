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

// $Id$

#include <dns/buffer.h>
#include <dns/rrset.h>
#include <dns/message.h>

#include <gtest/gtest.h>

namespace {

using isc::dns::Name;
using isc::dns::RRClass;
using isc::dns::RRType;
using isc::dns::TTL;
using isc::dns::Rdata::IN::A;
using isc::dns::RRset;
using isc::dns::RRsetPtr;
using isc::dns::RR;
using isc::dns::Message;
using isc::dns::SECTION_QUESTION;
using isc::dns::SECTION_ANSWER;
using isc::dns::SECTION_AUTHORITY;
using isc::dns::SECTION_ADDITIONAL;

// The fixture for testing class RRClass.
class MessageTest : public ::testing::Test {
protected:
    MessageTest()
    {
        query.addQuestion(Name("www.example.com"), RRClass::IN, RRType::A);
    }
    Message query;
    Message response;
};

TEST_F(MessageTest, check_flags)
{
    EXPECT_EQ(false, query.getQR());
    query.setQR(true);
    EXPECT_EQ(true, query.getQR());

    EXPECT_EQ(false, query.getAA());
    query.setAA(true);
    EXPECT_EQ(true, query.getAA());

    EXPECT_EQ(false, query.getTC());
    query.setTC(true);
    EXPECT_EQ(true, query.getTC());

    EXPECT_EQ(false, query.getRD());
    query.setRD(true);
    EXPECT_EQ(true, query.getRD());

    EXPECT_EQ(false, query.getRA());
    query.setRA(true);
    EXPECT_EQ(true, query.getRA());

    EXPECT_EQ(false, query.getAD());
    query.setAD(true);
    EXPECT_EQ(true, query.getAD());

    EXPECT_EQ(false, query.getCD());
    query.setCD(true);
    EXPECT_EQ(true, query.getCD());
}

TEST_F(MessageTest, getQuestion)
{
    const std::vector<RRsetPtr>& question = query.getSection(SECTION_QUESTION);
    EXPECT_EQ(1, question.size());
    EXPECT_EQ("www.example.com. IN A", (**question.begin()).toText());
}

TEST_F(MessageTest, makeResponse)
{
    query.makeResponse();
    EXPECT_EQ(true, query.getQR());
    EXPECT_EQ("www.example.com. IN A",
              (**query.getSection(SECTION_QUESTION).begin()).toText());
    EXPECT_EQ(0, query.getSection(SECTION_ANSWER).size());
    EXPECT_EQ(0, query.getSection(SECTION_AUTHORITY).size());
    EXPECT_EQ(0, query.getSection(SECTION_ADDITIONAL).size());
}

TEST_F(MessageTest, addRr)
{
    // Add one RR to the answer section.
    response.addRr(SECTION_ANSWER, RR(Name("www.example.com"), RRClass::IN,
                                       RRType::A, TTL(3600), A("192.0.2.1")));
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1",
              (**response.getSection(SECTION_ANSWER).begin()).toText());

    // Add another RR of the same RRset with a larger TTL.  The original
    // (smaller) TTL should remain.
    response.addRr(SECTION_ANSWER, RR(Name("www.example.com"), RRClass::IN,
                                       RRType::A, TTL(7200), A("192.0.2.2")));
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1\n"
              "www.example.com. 3600 IN A 192.0.2.2",
              (**response.getSection(SECTION_ANSWER).begin()).toText());

    // Add one more RR of the same RRset with a smaller TTL.  The new (smaller)
    // TTL should replace with the old one.
    response.addRr(SECTION_ANSWER, RR(Name("www.example.com"), RRClass::IN,
                                       RRType::A, TTL(1800), A("192.0.2.3")));
    EXPECT_EQ("www.example.com. 1800 IN A 192.0.2.1\n"
              "www.example.com. 1800 IN A 192.0.2.2\n"
              "www.example.com. 1800 IN A 192.0.2.3",
              (**response.getSection(SECTION_ANSWER).begin()).toText());
}
}
