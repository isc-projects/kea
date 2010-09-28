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

namespace {
class MessageTest : public ::testing::Test {
protected:
    MessageTest() : obuffer(0), renderer(obuffer),
                    message_parse(Message::PARSE),
                    message_render(Message::RENDER)
    {}
    
    static Question factoryFromFile(const char* datafile);
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message message_parse;
    Message message_render;
    static void factoryFromFile(Message& message, const char* datafile);
};

const Name test_name("test.example.com");

void
MessageTest::factoryFromFile(Message& message, const char* datafile) {
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    message.fromWire(buffer);
}

TEST_F(MessageTest, fromWire) {
    factoryFromFile(message_parse, "message_fromWire1");
    EXPECT_EQ(0x1035, message_parse.getQid());
    EXPECT_EQ(Opcode::QUERY(), message_parse.getOpcode());
    EXPECT_EQ(Rcode::NOERROR(), message_parse.getRcode());
    EXPECT_TRUE(message_parse.getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(message_parse.getHeaderFlag(MessageFlag::RD()));
    EXPECT_TRUE(message_parse.getHeaderFlag(MessageFlag::AA()));

    QuestionPtr q = *message_parse.beginQuestion();
    EXPECT_EQ(test_name, q->getName());
    EXPECT_EQ(RRType::A(), q->getType());
    EXPECT_EQ(RRClass::IN(), q->getClass());
    EXPECT_EQ(1, message_parse.getRRCount(Section::QUESTION()));
    EXPECT_EQ(2, message_parse.getRRCount(Section::ANSWER()));
    EXPECT_EQ(0, message_parse.getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(0, message_parse.getRRCount(Section::ADDITIONAL()));

    RRsetPtr rrset = *message_parse.beginSection(Section::ANSWER());
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

TEST_F(MessageTest, opcode) {    // for get/setOpcode
    EXPECT_THROW(message_parse.setOpcode(Opcode::NOTIFY()),
                 InvalidMessageOperation);
    message_render.setOpcode(Opcode::UPDATE());
    EXPECT_EQ(Opcode::UPDATE(), message_render.getOpcode());
    EXPECT_THROW(message_parse.getOpcode(), InvalidMessageOperation);
}

TEST_F(MessageTest, rcode) {    // for get/setRcode
    EXPECT_THROW(message_parse.setRcode(Rcode::BADVERS()),
                 InvalidMessageOperation);
    message_render.setRcode(Rcode::BADVERS());
    EXPECT_EQ(Rcode::BADVERS(), message_render.getRcode());
    EXPECT_THROW(message_parse.getRcode(), InvalidMessageOperation);
}

TEST_F(MessageTest, GetEDNS0DOBit) {
    // Without EDNS0, DNSSEC is considered to be unsupported.
    factoryFromFile(message_parse, "message_fromWire1");
    EXPECT_FALSE(message_parse.isDNSSECSupported());

    // If DO bit is on, DNSSEC is considered to be supported.
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_fromWire2");
    EXPECT_TRUE(message_parse.isDNSSECSupported());

    // If DO bit is off, DNSSEC is considered to be unsupported.
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_fromWire3");
    EXPECT_FALSE(message_parse.isDNSSECSupported());
}

TEST_F(MessageTest, SetEDNS0DOBit) {
    // By default, it's false, and we can enable/disable it.
    EXPECT_FALSE(message_render.isDNSSECSupported());
    message_render.setDNSSECSupported(true);
    EXPECT_TRUE(message_render.isDNSSECSupported());
    message_render.setDNSSECSupported(false);
    EXPECT_FALSE(message_render.isDNSSECSupported());

    // A message in the parse mode doesn't allow this flag to be set.
    EXPECT_THROW(message_parse.setDNSSECSupported(true),
                 InvalidMessageOperation);
    // Once converted to the render mode, it works as above
    message_parse.makeResponse();
    EXPECT_FALSE(message_parse.isDNSSECSupported());
    message_parse.setDNSSECSupported(true);
    EXPECT_TRUE(message_parse.isDNSSECSupported());
    message_parse.setDNSSECSupported(false);
    EXPECT_FALSE(message_parse.isDNSSECSupported());
}

TEST_F(MessageTest, GetEDNS0UDPSize) {
    // Without EDNS0, the default max UDP size is used.
    factoryFromFile(message_parse, "message_fromWire1");
    EXPECT_EQ(Message::DEFAULT_MAX_UDPSIZE, message_parse.getUDPSize());

    // If the size specified in EDNS0 > default max, use it.
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_fromWire2");
    EXPECT_EQ(4096, message_parse.getUDPSize());

    // If the size specified in EDNS0 < default max, keep using the default.
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_fromWire8");
    EXPECT_EQ(Message::DEFAULT_MAX_UDPSIZE, message_parse.getUDPSize());
}

TEST_F(MessageTest, SetEDNS0UDPSize) {
    // The default size if unspecified
    EXPECT_EQ(Message::DEFAULT_MAX_UDPSIZE, message_render.getUDPSize());
    // A common buffer size with EDNS, should succeed
    message_render.setUDPSize(4096);
    EXPECT_EQ(4096, message_render.getUDPSize());
    // Unusual large value, but accepted
    message_render.setUDPSize(0xffff);
    EXPECT_EQ(0xffff, message_render.getUDPSize());
    // Too small is value is rejected
    EXPECT_THROW(message_render.setUDPSize(511), InvalidMessageUDPSize);

    // A message in the parse mode doesn't allow the set operation.
    EXPECT_THROW(message_parse.setUDPSize(4096), InvalidMessageOperation);
    // Once converted to the render mode, it works as above.
    message_parse.makeResponse();
    message_parse.setUDPSize(4096);
    EXPECT_EQ(4096, message_parse.getUDPSize());
    message_parse.setUDPSize(0xffff);
    EXPECT_EQ(0xffff, message_parse.getUDPSize());
    EXPECT_THROW(message_parse.setUDPSize(511), InvalidMessageUDPSize);
}

TEST_F(MessageTest, EDNS0ExtCode) {
    // Extended Rcode = BADVERS
    factoryFromFile(message_parse, "message_fromWire10");
    EXPECT_EQ(Rcode::BADVERS(), message_parse.getRcode());

    // Maximum extended Rcode
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_fromWire11");
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
    // OPT RR of a non root name
    message_parse.clear(Message::PARSE);
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire6"),
                 DNSMessageFORMERR);
    // Compressed owner name of OPT RR points to a root name.
    // Not necessarily bogus, but very unusual and mostly pathological.
    // We accept it, but is it okay?
    message_parse.clear(Message::PARSE);
    EXPECT_NO_THROW(factoryFromFile(message_parse, "message_fromWire7"));
    // Unsupported Version
    message_parse.clear(Message::PARSE);
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire9"),
                 DNSMessageBADVERS);
}

TEST_F(MessageTest, toWire) {
    message_render.setQid(0x1035);
    message_render.setOpcode(Opcode::QUERY());
    message_render.setRcode(Rcode::NOERROR());
    message_render.setHeaderFlag(MessageFlag::QR());
    message_render.setHeaderFlag(MessageFlag::RD());
    message_render.setHeaderFlag(MessageFlag::AA());
    message_render.addQuestion(Question(Name("test.example.com"), RRClass::IN(),
                                        RRType::A()));
    RRsetPtr rrset = RRsetPtr(new RRset(Name("test.example.com"), RRClass::IN(),
                                        RRType::A(), RRTTL(3600)));
    rrset->addRdata(in::A("192.0.2.1"));
    rrset->addRdata(in::A("192.0.2.2"));
    message_render.addRRset(Section::ANSWER(), rrset);

    EXPECT_EQ(1, message_render.getRRCount(Section::QUESTION()));
    EXPECT_EQ(2, message_render.getRRCount(Section::ANSWER()));
    EXPECT_EQ(0, message_render.getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(0, message_render.getRRCount(Section::ADDITIONAL()));

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
