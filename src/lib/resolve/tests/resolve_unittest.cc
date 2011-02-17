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

#include <iostream>
#include <gtest/gtest.h>

#include <dns/message.h>
#include <dns/question.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <resolve/resolve.h>

using namespace isc::dns;

namespace {

class ResolveHelperFunctionsTest : public ::testing::Test {
public:
    ResolveHelperFunctionsTest() :
        message_a_(new Message(Message::RENDER)),
        message_b_(new Message(Message::RENDER)),
        question_(new Question(Name("www.example.com"), RRClass::IN(), RRType::A()))
    {
        createMessageA();
        createMessageB();
    };

    void createMessageA() {
        message_a_->setOpcode(Opcode::QUERY());
        message_a_->setRcode(Rcode::NOERROR());
        message_a_->addQuestion(question_);
    }

    void createMessageB() {
        message_b_->setOpcode(Opcode::QUERY());
        message_b_->setRcode(Rcode::NOERROR());
        message_b_->addQuestion(question_);

        // We could reuse the same rrset in the different sections,
        // but to be sure, we create separate ones
        RRsetPtr answer_rrset(new RRset(Name("www.example.com"),
                                        RRClass::IN(), RRType::TXT(),
                                        RRTTL(3600)));
        answer_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                                  RRClass::IN(),
                                                  "Answer"));
        message_b_->addRRset(Message::SECTION_ANSWER, answer_rrset);
    
        RRsetPtr auth_rrset(new RRset(Name("www.example.com"),
                                        RRClass::IN(), RRType::TXT(),
                                        RRTTL(3600)));
        auth_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                                  RRClass::IN(),
                                                  "Authority"));
        auth_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                                  RRClass::IN(),
                                                  "Rdata"));
        message_b_->addRRset(Message::SECTION_AUTHORITY, auth_rrset);
    
        RRsetPtr add_rrset(new RRset(Name("www.example.com"),
                                     RRClass::IN(), RRType::TXT(),
                                     RRTTL(3600)));
        add_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                               RRClass::IN(),
                                               "Additional"));
        add_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                               RRClass::IN(),
                                               "Rdata"));
        add_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                               RRClass::IN(),
                                               "fields."));
        message_b_->addRRset(Message::SECTION_ADDITIONAL, add_rrset);
    };

    MessagePtr message_a_;
    MessagePtr message_b_;
    QuestionPtr question_;
};

TEST_F(ResolveHelperFunctionsTest, makeErrorMessageEmptyMessage) {
    ASSERT_EQ(Rcode::NOERROR(), message_a_->getRcode());
    ASSERT_EQ(1, message_a_->getRRCount(Message::SECTION_QUESTION));
    ASSERT_EQ(0, message_a_->getRRCount(Message::SECTION_ANSWER));
    ASSERT_EQ(0, message_a_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_EQ(0, message_a_->getRRCount(Message::SECTION_ADDITIONAL));

    isc::resolve::makeErrorMessage(message_a_, Rcode::SERVFAIL());
    EXPECT_EQ(Rcode::SERVFAIL(), message_a_->getRcode());
    EXPECT_EQ(1, message_a_->getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_a_->getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_a_->getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_a_->getRRCount(Message::SECTION_ADDITIONAL));
}

TEST_F(ResolveHelperFunctionsTest, makeErrorMessageNonEmptyMessage) {

    ASSERT_EQ(Rcode::NOERROR(), message_b_->getRcode());
    ASSERT_EQ(1, message_b_->getRRCount(Message::SECTION_QUESTION));
    ASSERT_EQ(1, message_b_->getRRCount(Message::SECTION_ANSWER));
    ASSERT_EQ(2, message_b_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_EQ(3, message_b_->getRRCount(Message::SECTION_ADDITIONAL));

    isc::resolve::makeErrorMessage(message_b_, Rcode::FORMERR());
    EXPECT_EQ(Rcode::FORMERR(), message_b_->getRcode());
    EXPECT_EQ(1, message_b_->getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_b_->getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_b_->getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_b_->getRRCount(Message::SECTION_ADDITIONAL));
}

void
compareSections(const Message& message_a, const Message& message_b,
                Message::Section section)
{
    RRsetIterator rrs_a = message_a.beginSection(section);
    RRsetIterator rrs_b = message_b.beginSection(section);
    while (rrs_a != message_a.endSection(section) &&
           rrs_b != message_b.endSection(section)
          ) {
        EXPECT_EQ(*rrs_a, *rrs_b);
        ++rrs_a;
        ++rrs_b;
    }
    // can't use EXPECT_EQ here, no eqHelper for endsection comparison
    EXPECT_TRUE(rrs_a == message_a.endSection(section));
    EXPECT_TRUE(rrs_b == message_b.endSection(section));
}

TEST_F(ResolveHelperFunctionsTest, initResponseMessage) {
    Message response_parse(Message::PARSE);
    EXPECT_THROW(isc::resolve::initResponseMessage(*message_a_,
                                                   response_parse),
                 isc::dns::InvalidMessageOperation);
    EXPECT_THROW(isc::resolve::initResponseMessage(*question_,
                                                   response_parse),
                 isc::dns::InvalidMessageOperation);
    
    Message response1(Message::RENDER);
    isc::resolve::initResponseMessage(*message_a_, response1);
    ASSERT_EQ(message_a_->getOpcode(), response1.getOpcode());
    ASSERT_EQ(message_a_->getQid(), response1.getQid());
    isc::dns::QuestionIterator qi = response1.beginQuestion();
    ASSERT_EQ(*question_, **qi);
    ASSERT_TRUE(++qi == response1.endQuestion());

    Message response2(Message::RENDER);
    isc::resolve::initResponseMessage(*question_, response2);
    ASSERT_EQ(Opcode::QUERY(), response2.getOpcode());
    ASSERT_EQ(0, response2.getQid());
    qi = response2.beginQuestion();
    ASSERT_EQ(*question_, **qi);
    ASSERT_TRUE(++qi == response2.endQuestion());
}

TEST_F(ResolveHelperFunctionsTest, copyAnswerMessage) {
    message_b_->setRcode(Rcode::NXDOMAIN());
    
    ASSERT_NE(message_b_->getRcode(), message_a_->getRcode());
    ASSERT_NE(message_b_->getRRCount(Message::SECTION_ANSWER),
              message_a_->getRRCount(Message::SECTION_ANSWER));
    ASSERT_NE(message_b_->getRRCount(Message::SECTION_AUTHORITY),
              message_a_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_NE(message_b_->getRRCount(Message::SECTION_ADDITIONAL),
              message_a_->getRRCount(Message::SECTION_ADDITIONAL));
    ASSERT_EQ(0, message_a_->getRRCount(Message::SECTION_ANSWER));
    ASSERT_EQ(0, message_a_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_EQ(0, message_a_->getRRCount(Message::SECTION_ADDITIONAL));

    isc::resolve::copyResponseMessage(*message_b_, message_a_);

    EXPECT_EQ(message_b_->getRcode(), message_a_->getRcode());
    ASSERT_EQ(message_b_->getRRCount(Message::SECTION_ANSWER),
              message_a_->getRRCount(Message::SECTION_ANSWER));
    ASSERT_EQ(message_b_->getRRCount(Message::SECTION_AUTHORITY),
              message_a_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_EQ(message_b_->getRRCount(Message::SECTION_ADDITIONAL),
              message_a_->getRRCount(Message::SECTION_ADDITIONAL));

    
    compareSections(*message_a_, *message_b_, Message::SECTION_ANSWER);
    compareSections(*message_a_, *message_b_, Message::SECTION_AUTHORITY);
    compareSections(*message_a_, *message_b_, Message::SECTION_ADDITIONAL);
}

} // Anonymous namespace
