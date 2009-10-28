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

using ISC::DNS::Name;
using ISC::DNS::RRClass;
using ISC::DNS::RRType;
using ISC::DNS::TTL;
using ISC::DNS::Rdata::IN::A;
using ISC::DNS::RRset;
using ISC::DNS::RRsetPtr;
using ISC::DNS::RR;
using ISC::DNS::Message;
using ISC::DNS::SECTION_QUESTION;
using ISC::DNS::SECTION_ANSWER;
using ISC::DNS::SECTION_AUTHORITY;
using ISC::DNS::SECTION_ADDITIONAL;

// The fixture for testing class RRClass.
class MessageTest : public ::testing::Test {
protected:
    MessageTest()
    {
        query.add_question(Name("www.example.com"), RRClass::IN, RRType::A);
    }
    Message query;
    Message response;
};

TEST_F(MessageTest, check_flags)
{
    EXPECT_EQ(false, query.get_qr());
    query.set_qr(true);
    EXPECT_EQ(true, query.get_qr());

    EXPECT_EQ(false, query.get_aa());
    query.set_aa(true);
    EXPECT_EQ(true, query.get_aa());

    EXPECT_EQ(false, query.get_tc());
    query.set_tc(true);
    EXPECT_EQ(true, query.get_tc());

    EXPECT_EQ(false, query.get_rd());
    query.set_rd(true);
    EXPECT_EQ(true, query.get_rd());

    EXPECT_EQ(false, query.get_ra());
    query.set_ra(true);
    EXPECT_EQ(true, query.get_ra());

    EXPECT_EQ(false, query.get_ad());
    query.set_ad(true);
    EXPECT_EQ(true, query.get_ad());

    EXPECT_EQ(false, query.get_cd());
    query.set_cd(true);
    EXPECT_EQ(true, query.get_cd());
}

TEST_F(MessageTest, get_question)
{
    const std::vector<RRsetPtr>& question = query.get_section(SECTION_QUESTION);
    EXPECT_EQ(1, question.size());
    EXPECT_EQ("www.example.com. IN A", (**question.begin()).to_text());
}

TEST_F(MessageTest, make_response)
{
    query.make_response();
    EXPECT_EQ(true, query.get_qr());
    EXPECT_EQ("www.example.com. IN A",
              (**query.get_section(SECTION_QUESTION).begin()).to_text());
    EXPECT_EQ(0, query.get_section(SECTION_ANSWER).size());
    EXPECT_EQ(0, query.get_section(SECTION_AUTHORITY).size());
    EXPECT_EQ(0, query.get_section(SECTION_ADDITIONAL).size());
}

TEST_F(MessageTest, add_rr)
{
    // Add one RR to the answer section.
    response.add_rr(SECTION_ANSWER, RR(Name("www.example.com"), RRClass::IN,
                                       RRType::A, TTL(3600), A("192.0.2.1")));
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1",
              (**response.get_section(SECTION_ANSWER).begin()).to_text());

    // Add another RR of the same RRset with a larger TTL.  The original
    // (smaller) TTL should remain.
    response.add_rr(SECTION_ANSWER, RR(Name("www.example.com"), RRClass::IN,
                                       RRType::A, TTL(7200), A("192.0.2.2")));
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1\n"
              "www.example.com. 3600 IN A 192.0.2.2",
              (**response.get_section(SECTION_ANSWER).begin()).to_text());

    // Add one more RR of the same RRset with a smaller TTL.  The new (smaller)
    // TTL should replace with the old one.
    response.add_rr(SECTION_ANSWER, RR(Name("www.example.com"), RRClass::IN,
                                       RRType::A, TTL(1800), A("192.0.2.3")));
    EXPECT_EQ("www.example.com. 1800 IN A 192.0.2.1\n"
              "www.example.com. 1800 IN A 192.0.2.2\n"
              "www.example.com. 1800 IN A 192.0.2.3",
              (**response.get_section(SECTION_ANSWER).begin()).to_text());
}
}
