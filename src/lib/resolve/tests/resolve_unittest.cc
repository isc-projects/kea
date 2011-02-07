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
        message_(new Message(Message::RENDER)),
        question_(new Question(Name("www.example.com"), RRClass::IN(), RRType::A()))
    {
        message_->setOpcode(Opcode::QUERY());
        message_->setRcode(Rcode::NOERROR());
        message_->addQuestion(question_);
    };

    MessagePtr message_;
    QuestionPtr question_;
    
};

TEST_F(ResolveHelperFunctionsTest, makeErrorMessageEmptyMessage) {
    ASSERT_EQ(Rcode::NOERROR(), message_->getRcode());
    ASSERT_EQ(1, message_->getRRCount(Message::SECTION_QUESTION));
    ASSERT_EQ(0, message_->getRRCount(Message::SECTION_ANSWER));
    ASSERT_EQ(0, message_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_EQ(0, message_->getRRCount(Message::SECTION_ADDITIONAL));

    isc::resolve::makeErrorMessage(message_, Rcode::SERVFAIL());
    EXPECT_EQ(Rcode::SERVFAIL(), message_->getRcode());
    EXPECT_EQ(1, message_->getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_->getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_->getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_->getRRCount(Message::SECTION_ADDITIONAL));
}

TEST_F(ResolveHelperFunctionsTest, makeErrorMessageNonEmptyMessage) {
    // We could reuse the same rrset in the different sections,
    // but to be sure, we create separate ones
    RRsetPtr answer_rrset(new RRset(Name("www.example.com"),
                                    RRClass::IN(), RRType::TXT(),
                                    RRTTL(3600)));
    answer_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                              RRClass::IN(),
                                              "Answer"));
    message_->addRRset(Message::SECTION_ANSWER, answer_rrset);

    RRsetPtr auth_rrset(new RRset(Name("www.example.com"),
                                    RRClass::IN(), RRType::TXT(),
                                    RRTTL(3600)));
    auth_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                              RRClass::IN(),
                                              "Authority"));
    auth_rrset->addRdata(rdata::createRdata(RRType::TXT(),
                                              RRClass::IN(),
                                              "Rdata"));
    message_->addRRset(Message::SECTION_AUTHORITY, auth_rrset);

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
    message_->addRRset(Message::SECTION_ADDITIONAL, add_rrset);

    ASSERT_EQ(Rcode::NOERROR(), message_->getRcode());
    ASSERT_EQ(1, message_->getRRCount(Message::SECTION_QUESTION));
    ASSERT_EQ(1, message_->getRRCount(Message::SECTION_ANSWER));
    ASSERT_EQ(2, message_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_EQ(3, message_->getRRCount(Message::SECTION_ADDITIONAL));

    isc::resolve::makeErrorMessage(message_, Rcode::FORMERR());
    EXPECT_EQ(Rcode::FORMERR(), message_->getRcode());
    EXPECT_EQ(1, message_->getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_->getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_->getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_->getRRCount(Message::SECTION_ADDITIONAL));
}


} // Anonymous namespace
