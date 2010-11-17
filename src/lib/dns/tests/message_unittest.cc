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

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/edns.h>
#include <dns/exceptions.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/question.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::dns::rdata;

//
// Note: we need more tests, including:
// parsing malformed headers
// more complete tests about parsing/rendering header flags, opcode, rcode, etc.
// tests for adding RRsets
// tests for RRset/Question iterators
// But, we'll ship with the current set of tests for now, partly because many
// of the above are covered as part of other tests, and partly due to time
// limitation.  We also expect to revisit the fundamental design of the Message
// class, at which point we'll also revise the tests including more cases.
//

const uint16_t Message::DEFAULT_MAX_UDPSIZE;
const Name test_name("test.example.com");

namespace {
class MessageTest : public ::testing::Test {
protected:
    MessageTest() : obuffer(0), renderer(obuffer),
                    message_parse(Message::PARSE),
                    message_render(Message::RENDER),
                    bogus_section(static_cast<Message::Section>(
                                      Message::SECTION_ADDITIONAL + 1))
    {
        rrset_a = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                     RRType::A(), RRTTL(3600)));
        rrset_a->addRdata(in::A("192.0.2.1"));
        rrset_a->addRdata(in::A("192.0.2.2"));

        rrset_aaaa = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                        RRType::AAAA(), RRTTL(3600)));
        rrset_aaaa->addRdata(in::AAAA("2001:db8::1234"));

        rrset_rrsig = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                        RRType::RRSIG(), RRTTL(3600)));
        rrset_rrsig->addRdata(generic::RRSIG("AAAA 5 3 7200 20100322084538 "
                                             "20100220084538 1 example.com "
                                             "FAKEFAKEFAKEFAKE"));
        rrset_aaaa->addRRsig(rrset_rrsig);
    }
    
    static Question factoryFromFile(const char* datafile);
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message message_parse;
    Message message_render;
    const Message::Section bogus_section;
    RRsetPtr rrset_a;           // A RRset with two RDATAs
    RRsetPtr rrset_aaaa;        // AAAA RRset with one RDATA with RRSIG
    RRsetPtr rrset_rrsig;       // RRSIG for the AAAA RRset
    static void factoryFromFile(Message& message, const char* datafile);
};

void
MessageTest::factoryFromFile(Message& message, const char* datafile) {
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    message.fromWire(buffer);
}

TEST_F(MessageTest, headerFlag) {
    // by default no flag is set
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_TC));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_RA));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_AD));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_CD));

    // set operation: by default it will be on
    message_render.setHeaderFlag(Message::HEADERFLAG_QR);
    EXPECT_TRUE(message_render.getHeaderFlag(Message::HEADERFLAG_QR));

    // it can be set to on explicitly, too
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, true);
    EXPECT_TRUE(message_render.getHeaderFlag(Message::HEADERFLAG_AA));

    // the bit can also be cleared
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, false);
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_AA));

    // Invalid flag values
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0)), InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x7000)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x0800)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x0040)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x10000)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x80000000)),
                 InvalidParameter);

    // set operation isn't allowed in the parse mode.
    EXPECT_THROW(message_parse.setHeaderFlag(Message::HEADERFLAG_QR),
                 InvalidMessageOperation);
}

TEST_F(MessageTest, getEDNS) {
    EXPECT_FALSE(message_parse.getEDNS()); // by default EDNS isn't set

    factoryFromFile(message_parse, "message_fromWire10.wire");
    EXPECT_TRUE(message_parse.getEDNS());
    EXPECT_EQ(0, message_parse.getEDNS()->getVersion());
    EXPECT_EQ(4096, message_parse.getEDNS()->getUDPSize());
    EXPECT_TRUE(message_parse.getEDNS()->getDNSSECAwareness());
}

TEST_F(MessageTest, setEDNS) {
    // setEDNS() isn't allowed in the parse mode
    EXPECT_THROW(message_parse.setEDNS(EDNSPtr(new EDNS())),
                 InvalidMessageOperation);

    EDNSPtr edns = EDNSPtr(new EDNS());
    message_render.setEDNS(edns);
    EXPECT_EQ(edns, message_render.getEDNS());
}

TEST_F(MessageTest, getRRCount) {
    // by default all counters should be 0
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    message_render.addQuestion(Question(Name("test.example.com"),
                                        RRClass::IN(), RRType::A()));
    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));

    // rrset_a contains two RRs
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));

    // parse a message containing a Question and EDNS OPT RR.
    // OPT shouldn't be counted as normal RR, so result of getRRCount
    // shouldn't change.
    factoryFromFile(message_parse, "message_fromWire11.wire");
    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    // out-of-band section ID
    EXPECT_THROW(message_parse.getRRCount(bogus_section), OutOfRange);
}

TEST_F(MessageTest, addRRset) {
    // default case
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    EXPECT_EQ(rrset_a,
              *message_render.beginSection(Message::SECTION_ANSWER));
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));

    // signed RRset, default case
    message_render.clear(Message::RENDER);
    message_render.addRRset(Message::SECTION_ANSWER, rrset_aaaa);
    EXPECT_EQ(rrset_aaaa,
              *message_render.beginSection(Message::SECTION_ANSWER));
    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_ANSWER));

    // signed RRset, add with the RRSIG.  getRRCount() should return 2
    message_render.clear(Message::RENDER);
    message_render.addRRset(Message::SECTION_ANSWER, rrset_aaaa, true);
    EXPECT_EQ(rrset_aaaa,
              *message_render.beginSection(Message::SECTION_ANSWER));
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));

    // signed RRset, add explicitly without RRSIG.
    message_render.clear(Message::RENDER);
    message_render.addRRset(Message::SECTION_ANSWER, rrset_aaaa, false);
    EXPECT_EQ(rrset_aaaa,
              *message_render.beginSection(Message::SECTION_ANSWER));
    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_ANSWER));
}

TEST_F(MessageTest, badAddRRset) {
    // addRRset() isn't allowed in the parse mode.
    EXPECT_THROW(message_parse.addRRset(Message::SECTION_ANSWER,
                                        rrset_a), InvalidMessageOperation);
    // out-of-band section ID
    EXPECT_THROW(message_render.addRRset(bogus_section, rrset_a), OutOfRange);
}

TEST_F(MessageTest, hasRRset) {
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    EXPECT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
                                        RRClass::IN(), RRType::A()));
    // section doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ADDITIONAL, test_name,
                                         RRClass::IN(), RRType::A()));
    // name doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER,
                                         Name("nomatch.example"),
                                         RRClass::IN(), RRType::A()));
    // RR class doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
                                        RRClass::CH(), RRType::A()));
    // RR type doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
                                        RRClass::IN(), RRType::AAAA()));

    // out-of-band section ID
    EXPECT_THROW(message_render.hasRRset(bogus_section, test_name,
                                         RRClass::IN(), RRType::A()),
                 OutOfRange);
}

TEST_F(MessageTest, badBeginSection) {
    // valid cases are tested via other tests
    EXPECT_THROW(message_render.beginSection(Message::SECTION_QUESTION),
                 InvalidMessageSection);
    EXPECT_THROW(message_render.beginSection(bogus_section), OutOfRange);
}

TEST_F(MessageTest, badEndSection) {
    // valid cases are tested via other tests
    EXPECT_THROW(message_render.endSection(Message::SECTION_QUESTION),
                 InvalidMessageSection);
    EXPECT_THROW(message_render.endSection(bogus_section), OutOfRange);
}

TEST_F(MessageTest, fromWire) {
    factoryFromFile(message_parse, "message_fromWire1");
    EXPECT_EQ(0x1035, message_parse.getQid());
    EXPECT_EQ(Opcode::QUERY(), message_parse.getOpcode());
    EXPECT_EQ(Rcode::NOERROR(), message_parse.getRcode());
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_AA));

    QuestionPtr q = *message_parse.beginQuestion();
    EXPECT_EQ(test_name, q->getName());
    EXPECT_EQ(RRType::A(), q->getType());
    EXPECT_EQ(RRClass::IN(), q->getClass());
    EXPECT_EQ(1, message_parse.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(2, message_parse.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_parse.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_parse.getRRCount(Message::SECTION_ADDITIONAL));

    RRsetPtr rrset = *message_parse.beginSection(Message::SECTION_ANSWER);
    EXPECT_EQ(test_name, rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    // TTL should be 3600, even though that of the 2nd RR is 7200
    EXPECT_EQ(RRTTL(3600), rrset->getTTL());
    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("192.0.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(MessageTest, EDNS0ExtRcode) {
    // Extended Rcode = BADVERS
    factoryFromFile(message_parse, "message_fromWire10.wire");
    EXPECT_EQ(Rcode::BADVERS(), message_parse.getRcode());

    // Maximum extended Rcode
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_fromWire11.wire");
    EXPECT_EQ(0xfff, message_parse.getRcode().getCode());
}

TEST_F(MessageTest, BadEDNS0) {
    // OPT RR in the answer section
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire4"),
                 DNSMessageFORMERR);
    // multiple OPT RRs (in the additional section)
    message_parse.clear(Message::PARSE);
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire5"),
                 DNSMessageFORMERR);
}

TEST_F(MessageTest, toWire) {
    message_render.setQid(0x1035);
    message_render.setOpcode(Opcode::QUERY());
    message_render.setRcode(Rcode::NOERROR());
    message_render.setHeaderFlag(Message::HEADERFLAG_QR, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_RD, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, true);
    message_render.addQuestion(Question(Name("test.example.com"), RRClass::IN(),
                                        RRType::A()));
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);

    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    message_render.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("message_toWire1", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, obuffer.getData(),
                        obuffer.getLength(), &data[0], data.size());
}

TEST_F(MessageTest, toWireInParseMode) {
    // toWire() isn't allowed in the parse mode.
    EXPECT_THROW(message_parse.toWire(renderer), InvalidMessageOperation);
}

TEST_F(MessageTest, toWireWithoutOpcode) {
    message_render.setRcode(Rcode::NOERROR());
    EXPECT_THROW(message_render.toWire(renderer), InvalidMessageOperation);
}

TEST_F(MessageTest, toWireWithoutRcode) {
    message_render.setOpcode(Opcode::QUERY());
    EXPECT_THROW(message_render.toWire(renderer), InvalidMessageOperation);
}

TEST_F(MessageTest, toTextWithoutOpcode) {
    message_render.setRcode(Rcode::NOERROR());
    EXPECT_THROW(message_render.toText(), InvalidMessageOperation);
}

TEST_F(MessageTest, toTextWithoutRcode) {
    message_render.setOpcode(Opcode::QUERY());
    EXPECT_THROW(message_render.toText(), InvalidMessageOperation);
}
}
