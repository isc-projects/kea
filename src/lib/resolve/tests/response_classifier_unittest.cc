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

#include <dns/tests/unittest_util.h>

#include <resolve/response_classifier.h>

#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/question.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

using namespace std;
using namespace isc::dns;
using namespace rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::dns::rdata::in;
using namespace isc::resolve;


namespace {
class ResponseClassifierTest : public ::testing::Test {
public:
    /// \brief Constructor
    ///
    /// The naming convention is:
    ///
    /// <category>_<class>_<type>_<name>
    ///
    /// <category> is "qu" (question), "rrs" (rrset),
    /// <qclass> is self-explanatory
    /// <qtype> is self-explanatory
    /// <name> is the first part of the domain name (all expected to be in
    /// example.com)
    ///
    /// Message variables
    ///
    /// msg_<qtype>  Where <qtype> is the type of query.  These are only used
    /// in the early tests where simple messages are required.

    ResponseClassifierTest() :
        msg_a(new Message(Message::RENDER)),
        msg_any(new Message(Message::RENDER)),
        qu_ch_a_www(Name("www.example.com"), RRClass::CH(), RRType::A()),
        qu_in_any_www(Name("www.example.com"), RRClass::IN(), RRType::ANY()),
        qu_in_a_www2(Name("www2.example.com"), RRClass::IN(), RRType::A()),
        qu_in_a_www(Name("www.example.com"), RRClass::IN(), RRType::A()),
        qu_in_cname_www1(Name("www1.example.com"), RRClass::IN(), RRType::A()),
        qu_in_ns_(Name("example.com"), RRClass::IN(), RRType::NS()),
        qu_in_txt_www(Name("www.example.com"), RRClass::IN(), RRType::TXT()),
        rrs_hs_txt_www(new RRset(Name("www.example.com"), RRClass::HS(),
            RRType::TXT(), RRTTL(300))),
        rrs_in_a_mail(new RRset(Name("mail.example.com"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_a_www(new RRset(Name("www.example.com"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_cname_www1(new RRset(Name("www1.example.com"), RRClass::IN(),
            RRType::CNAME(), RRTTL(300))),
        rrs_in_cname_www2(new RRset(Name("www2.example.com"), RRClass::IN(),
            RRType::CNAME(), RRTTL(300))),
        rrs_in_ns_(new RRset(Name("example.com"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_txt_www(new RRset(Name("www.example.com"), RRClass::IN(),
            RRType::TXT(), RRTTL(300)))
    {
        // Set up the message to indicate a successful response to the question
        // "www.example.com A", but don't add in any response sections.
        msg_a->setHeaderFlag(Message::HEADERFLAG_QR);
        msg_a->setOpcode(Opcode::QUERY());
        msg_a->setRcode(Rcode::NOERROR());
        msg_a->addQuestion(qu_in_a_www);

        // ditto for the query "www.example.com ANY"
        msg_any->setHeaderFlag(Message::HEADERFLAG_QR);
        msg_any->setOpcode(Opcode::QUERY());
        msg_any->setRcode(Rcode::NOERROR());
        msg_any->addQuestion(qu_in_any_www);

        // The next set of assignments set up the following zone records
        //
        // example.com           NS     ns0.isc.org
        //                       NS     ns0.example.org
        //
        // www.example.com       A      1.2.3.4
        //                       TXT    "An example text string"
        //
        // mail.example.com      A      4.5.6.7
        //
        // www1.example.com      CNAME  www.example.com
        //
        // www2.example.com      CNAME  www1.example.com

        // Set up an imaginary NS RRset for an authority section
        rrs_in_ns_->addRdata(ConstRdataPtr(new NS(Name("ns0.isc.org"))));
        rrs_in_ns_->addRdata(ConstRdataPtr(new NS(Name("ns0.example.org"))));

        // Set up the records for the www host
        rrs_in_a_www->addRdata(ConstRdataPtr(new A("1.2.3.4")));
        rrs_in_txt_www->addRdata(ConstRdataPtr(
            new TXT("An example text string")));

        // ... for the mail host
        rrs_in_a_mail->addRdata(ConstRdataPtr(new A("5.6.7.8")));

        // ... the CNAME records
        rrs_in_cname_www1->addRdata(ConstRdataPtr(
            new CNAME("www.example.com")));
        rrs_in_cname_www2->addRdata(ConstRdataPtr(
            new CNAME("www1.example.com")));
    }

    MessagePtr  msg_a;              // Pointer to message in RENDER state
    MessagePtr  msg_any;            // Pointer to message in RENDER state
    Question    qu_ch_a_www;        // www.example.com CH A
    Question    qu_in_any_www;      // www.example.com IN ANY
    Question    qu_in_a_www2;       // www.example.com IN ANY
    Question    qu_in_a_www;        // www.example.com IN A
    Question    qu_in_cname_www1;   // www1.example.com IN CNAME
    Question    qu_in_ns_;          // example.com IN NS
    Question    qu_in_txt_www;      // www.example.com IN TXT
    RRsetPtr    rrs_hs_txt_www;     // www.example.com HS TXT
    RRsetPtr    rrs_in_a_mail;      // mail.example.com IN A
    RRsetPtr    rrs_in_a_www;       // www.example.com IN A
    RRsetPtr    rrs_in_cname_www1;  // www1.example.com IN CNAME
    RRsetPtr    rrs_in_cname_www2;  // www2.example.com IN CNAME
    RRsetPtr    rrs_in_ns_;         // example.com IN NS
    RRsetPtr    rrs_in_txt_www;     // www.example.com IN TXT
};

// Test that the error() function categorises the codes correctly.

TEST_F(ResponseClassifierTest, StatusCodes) {
    EXPECT_FALSE(ResponseClassifier::error(ResponseClassifier::ANSWER));
    EXPECT_FALSE(ResponseClassifier::error(ResponseClassifier::ANSWERCNAME));
    EXPECT_FALSE(ResponseClassifier::error(ResponseClassifier::CNAME));
    EXPECT_FALSE(ResponseClassifier::error(ResponseClassifier::NXDOMAIN));
    EXPECT_FALSE(ResponseClassifier::error(ResponseClassifier::REFERRAL));

    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::EMPTY));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::EXTRADATA));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::INVNAMCLASS));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::INVTYPE));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::MISMATQUEST));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::MULTICLASS));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::NOTONEQUEST));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::NOTRESPONSE));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::NOTSINGLE));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::OPCODE));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::RCODE));
    EXPECT_TRUE(ResponseClassifier::error(ResponseClassifier::TRUNCATED));
}

// Test that the system will reject a message which is a query.

TEST_F(ResponseClassifierTest, Query) {

    // Set up message to indicate a query (QR flag = 0, one question).  By
    // default the opcode will be 0 (query)
    msg_a->setHeaderFlag(Message::HEADERFLAG_QR, false);

    // Should be rejected as it is a query, not a response
    EXPECT_EQ(ResponseClassifier::NOTRESPONSE,
        ResponseClassifier::classify(qu_in_a_www, msg_a));
}

// Check that we get an OPCODE error on all but QUERY opcodes.

TEST_F(ResponseClassifierTest, Opcode) {

    uint8_t query = static_cast<uint8_t>(Opcode::QUERY().getCode());

    for (uint8_t i = 0; i < (1 << 4); ++i) {
        msg_a->setOpcode(Opcode(i));
        if (i == query) {
            EXPECT_NE(ResponseClassifier::OPCODE,
                ResponseClassifier::classify(qu_in_a_www, msg_a));
        } else {
            EXPECT_EQ(ResponseClassifier::OPCODE,
                ResponseClassifier::classify(qu_in_a_www, msg_a));
        }
    }
}

// Test that the system will reject a response with anything other than one
// question.

TEST_F(ResponseClassifierTest, MultipleQuestions) {

    // Create a message object for this test that has no question section.
    MessagePtr message(new Message(Message::RENDER));
    message->setHeaderFlag(Message::HEADERFLAG_QR);
    message->setOpcode(Opcode::QUERY());
    message->setRcode(Rcode::NOERROR());

    // Zero questions
    EXPECT_EQ(ResponseClassifier::NOTONEQUEST,
        ResponseClassifier::classify(qu_in_a_www, message));

    // One question
    message->addQuestion(qu_in_a_www);
    EXPECT_NE(ResponseClassifier::NOTONEQUEST,
        ResponseClassifier::classify(qu_in_a_www, message));

    // Two questions
    message->addQuestion(qu_in_ns_);
    EXPECT_EQ(ResponseClassifier::NOTONEQUEST,
        ResponseClassifier::classify(qu_in_a_www, message));

    // And finish the check with three questions
    message->addQuestion(qu_in_txt_www);
    EXPECT_EQ(ResponseClassifier::NOTONEQUEST,
        ResponseClassifier::classify(qu_in_a_www, message));
}

// Test that the question in the question section in the message response
// is equal to the question supplied.

TEST_F(ResponseClassifierTest, SameQuestion) {

    EXPECT_EQ(ResponseClassifier::MISMATQUEST,
        ResponseClassifier::classify(qu_in_ns_, msg_a));
    EXPECT_NE(ResponseClassifier::MISMATQUEST,
        ResponseClassifier::classify(qu_in_a_www, msg_a));
}

// Should get an NXDOMAIN response only on an NXDOMAIN RCODE.

TEST_F(ResponseClassifierTest, NXDOMAIN) {

    uint16_t nxdomain = static_cast<uint16_t>(Rcode::NXDOMAIN().getCode());

    for (uint8_t i = 0; i < (1 << 4); ++i) {
        msg_a->setRcode(Rcode(i));
        if (i == nxdomain) {
            EXPECT_EQ(ResponseClassifier::NXDOMAIN,
                ResponseClassifier::classify(qu_in_a_www, msg_a));
        } else {
            EXPECT_NE(ResponseClassifier::NXDOMAIN,
                ResponseClassifier::classify(qu_in_a_www, msg_a));
        }
    }
}

// Check that we get an RCODE error on all but NXDOMAIN and NOERROR responses.

TEST_F(ResponseClassifierTest, RCODE) {

    uint16_t nxdomain = static_cast<uint16_t>(Rcode::NXDOMAIN().getCode());
    uint16_t noerror = static_cast<uint16_t>(Rcode::NOERROR().getCode());

    for (uint8_t i = 0; i < (1 << 4); ++i) {
        msg_a->setRcode(Rcode(i));
        if ((i == nxdomain) || (i == noerror)) {
            EXPECT_NE(ResponseClassifier::RCODE,
                ResponseClassifier::classify(qu_in_a_www, msg_a));
        } else {
            EXPECT_EQ(ResponseClassifier::RCODE,
                ResponseClassifier::classify(qu_in_a_www, msg_a));
        }
    }
}

// Test that the code will detect a truncated message.  Even if nothing else
// is wrong, we'll want to retry the query if we receive a truncated code.
// However, we give the option to the user of the code aws to whether they
// want to take into account the truncated bit.

TEST_F(ResponseClassifierTest, Truncated) {

    // Don't expect the truncated code whatever option we ask for if the TC
    // bit is not set.
    msg_a->setHeaderFlag(Message::HEADERFLAG_TC, false);
    EXPECT_NE(ResponseClassifier::TRUNCATED,
        ResponseClassifier::classify(qu_in_a_www, msg_a, true));
    EXPECT_NE(ResponseClassifier::TRUNCATED,
        ResponseClassifier::classify(qu_in_a_www, msg_a, false));

    // Expect the truncated code if the TC bit is set, only if we don't ignore
    // it.
    msg_a->setHeaderFlag(Message::HEADERFLAG_TC, true);
    EXPECT_NE(ResponseClassifier::TRUNCATED,
        ResponseClassifier::classify(qu_in_a_www, msg_a, true));
    EXPECT_EQ(ResponseClassifier::TRUNCATED,
        ResponseClassifier::classify(qu_in_a_www, msg_a, false));
}

// Check for an empty packet (i.e. no error, but with the answer and additional
// sections empty).

TEST_F(ResponseClassifierTest, Empty) {

    EXPECT_EQ(ResponseClassifier::EMPTY,
        ResponseClassifier::classify(qu_in_a_www, msg_a));
}

// Anything where we have an empty answer section but something in the
// authority section is a referral (if the status is NOERROR).

TEST_F(ResponseClassifierTest, EmptyAnswerReferral) {

    msg_a->addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_);
    EXPECT_EQ(ResponseClassifier::REFERRAL,
        ResponseClassifier::classify(qu_in_a_www, msg_a));

}

// Check the case where we have a simple answer in the answer section.  This
// occurs when the QNAME/QTYPE/QCLASS matches one of the RRsets in the
// answer section - expect when the QTYPE is ANY, in which case the match
// must be on the QNAME/QCLASS alone.

TEST_F(ResponseClassifierTest, SingleAnswer) {

    // Check a question that matches the answer
    msg_a->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    EXPECT_EQ(ResponseClassifier::ANSWER,
        ResponseClassifier::classify(qu_in_a_www, msg_a));

    // Check an ANY question that matches the answer
    msg_any->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    EXPECT_EQ(ResponseClassifier::ANSWER,
        ResponseClassifier::classify(qu_in_any_www, msg_any));

    // Check a CNAME response that matches the QNAME.
    MessagePtr message_a(new Message(Message::RENDER));
    message_a->setHeaderFlag(Message::HEADERFLAG_QR);
    message_a->setOpcode(Opcode::QUERY());
    message_a->setRcode(Rcode::NOERROR());
    message_a->addQuestion(qu_in_cname_www1);
    message_a->addRRset(Message::SECTION_ANSWER, rrs_in_cname_www1);
    EXPECT_EQ(ResponseClassifier::CNAME,
        ResponseClassifier::classify(qu_in_cname_www1, message_a));

    // Check if the answer QNAME does not match the question
    // Q: www.example.com  IN A
    // A: mail.example.com IN A
    MessagePtr message_b(new Message(Message::RENDER));
    message_b->setHeaderFlag(Message::HEADERFLAG_QR);
    message_b->setOpcode(Opcode::QUERY());
    message_b->setRcode(Rcode::NOERROR());
    message_b->addQuestion(qu_in_a_www);
    message_b->addRRset(Message::SECTION_ANSWER, rrs_in_a_mail);
    EXPECT_EQ(ResponseClassifier::INVNAMCLASS,
        ResponseClassifier::classify(qu_in_a_www, message_b));

    // Check if the answer class does not match the question
    // Q: www.example.com CH A
    // A: www.example.com IN A
    MessagePtr message_c(new Message(Message::RENDER));
    message_c->setHeaderFlag(Message::HEADERFLAG_QR);
    message_c->setOpcode(Opcode::QUERY());
    message_c->setRcode(Rcode::NOERROR());
    message_c->addQuestion(qu_ch_a_www);
    message_c->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    EXPECT_EQ(ResponseClassifier::INVNAMCLASS,
        ResponseClassifier::classify(qu_ch_a_www, message_c));

    // Check if the answer type does not match the question
    // Q: www.example.com IN A
    // A: www.example.com IN TXT
    MessagePtr message_d(new Message(Message::RENDER));
    message_d->setHeaderFlag(Message::HEADERFLAG_QR);
    message_d->setOpcode(Opcode::QUERY());
    message_d->setRcode(Rcode::NOERROR());
    message_d->addQuestion(qu_in_a_www);
    message_d->addRRset(Message::SECTION_ANSWER, rrs_in_txt_www);
    EXPECT_EQ(ResponseClassifier::INVTYPE,
        ResponseClassifier::classify(qu_in_a_www, message_d));
}

// Check what happens if we have multiple RRsets in the answer.

TEST_F(ResponseClassifierTest, MultipleAnswerRRsets) {

    // All the same QNAME but different types is only valid on an ANY query.
    MessagePtr message_a(new Message(Message::RENDER));
    message_a->setHeaderFlag(Message::HEADERFLAG_QR);
    message_a->setOpcode(Opcode::QUERY());
    message_a->setRcode(Rcode::NOERROR());
    message_a->addQuestion(qu_in_any_www);
    message_a->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    message_a->addRRset(Message::SECTION_ANSWER, rrs_in_txt_www);
    EXPECT_EQ(ResponseClassifier::ANSWER,
        ResponseClassifier::classify(qu_in_any_www, message_a));

    // On another type of query, it results in an EXTRADATA error
    MessagePtr message_b(new Message(Message::RENDER));
    message_b->setHeaderFlag(Message::HEADERFLAG_QR);
    message_b->setOpcode(Opcode::QUERY());
    message_b->setRcode(Rcode::NOERROR());
    message_b->addQuestion(qu_in_a_www);
    message_b->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    message_b->addRRset(Message::SECTION_ANSWER, rrs_in_txt_www);
    EXPECT_EQ(ResponseClassifier::EXTRADATA,
        ResponseClassifier::classify(qu_in_a_www, message_b));

    // Same QNAME on an ANY query is not valid with mixed classes
    MessagePtr message_c(new Message(Message::RENDER));
    message_c->setHeaderFlag(Message::HEADERFLAG_QR);
    message_c->setOpcode(Opcode::QUERY());
    message_c->setRcode(Rcode::NOERROR());
    message_c->addQuestion(qu_in_any_www);
    message_c->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    message_c->addRRset(Message::SECTION_ANSWER, rrs_hs_txt_www);
    EXPECT_EQ(ResponseClassifier::MULTICLASS,
        ResponseClassifier::classify(qu_in_any_www, message_c));

    // Mixed QNAME is not valid unless QNAME requested is a CNAME.
    MessagePtr message_d(new Message(Message::RENDER));
    message_d->setHeaderFlag(Message::HEADERFLAG_QR);
    message_d->setOpcode(Opcode::QUERY());
    message_d->setRcode(Rcode::NOERROR());
    message_d->addQuestion(qu_in_a_www);
    message_d->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    message_d->addRRset(Message::SECTION_ANSWER, rrs_in_a_mail);
    EXPECT_EQ(ResponseClassifier::EXTRADATA,
        ResponseClassifier::classify(qu_in_a_www, message_d));

    // Mixed QNAME is not valid when the query is an ANY.
    MessagePtr message_e(new Message(Message::RENDER));
    message_e->setHeaderFlag(Message::HEADERFLAG_QR);
    message_e->setOpcode(Opcode::QUERY());
    message_e->setRcode(Rcode::NOERROR());
    message_e->addQuestion(qu_in_any_www);
    message_e->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    message_e->addRRset(Message::SECTION_ANSWER, rrs_in_txt_www);
    message_e->addRRset(Message::SECTION_ANSWER, rrs_in_a_mail);
    EXPECT_EQ(ResponseClassifier::EXTRADATA,
        ResponseClassifier::classify(qu_in_any_www, message_e));
}

// CNAME chain is CNAME if it terminates in a CNAME, answer if it
// does not, and error if there are RRs left over.
TEST_F(ResponseClassifierTest, CNAMEChain) {

    // Answer contains a single CNAME
    MessagePtr message_a(new Message(Message::RENDER));
    message_a->setHeaderFlag(Message::HEADERFLAG_QR);
    message_a->setOpcode(Opcode::QUERY());
    message_a->setRcode(Rcode::NOERROR());
    message_a->addQuestion(qu_in_a_www2);
    message_a->addRRset(Message::SECTION_ANSWER, rrs_in_cname_www2);
    EXPECT_EQ(ResponseClassifier::CNAME,
        ResponseClassifier::classify(qu_in_a_www2, message_a));

    // Add a CNAME for www1, and it should still return a CNAME
    message_a->addRRset(Message::SECTION_ANSWER, rrs_in_cname_www1);
    EXPECT_EQ(ResponseClassifier::CNAME,
        ResponseClassifier::classify(qu_in_a_www2, message_a));

    // Add the A record for www and it should be an answer
    message_a->addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    EXPECT_EQ(ResponseClassifier::ANSWERCNAME,
        ResponseClassifier::classify(qu_in_a_www2, message_a));

    // Adding an unrelated TXT record should result in EXTRADATA
    message_a->addRRset(Message::SECTION_ANSWER, rrs_in_txt_www);
    EXPECT_EQ(ResponseClassifier::EXTRADATA,
        ResponseClassifier::classify(qu_in_a_www2, message_a));

    // Recreate the chain, but this time end with a TXT RR and not the A
    // record.  This should return INVTYPE.
    MessagePtr message_b(new Message(Message::RENDER));
    message_b->setHeaderFlag(Message::HEADERFLAG_QR);
    message_b->setOpcode(Opcode::QUERY());
    message_b->setRcode(Rcode::NOERROR());
    message_b->addQuestion(qu_in_a_www2);
    message_b->addRRset(Message::SECTION_ANSWER, rrs_in_cname_www2);
    message_b->addRRset(Message::SECTION_ANSWER, rrs_in_cname_www1);
    message_b->addRRset(Message::SECTION_ANSWER, rrs_in_txt_www);

    EXPECT_EQ(ResponseClassifier::INVTYPE,
        ResponseClassifier::classify(qu_in_a_www2, message_b));
}

} // Anonymous namespace
