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
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/question.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include "unittest_util.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

const uint16_t Message::DEFAULT_MAX_UDPSIZE;

namespace {
class MessageTest : public ::testing::Test {
protected:
    MessageTest() : obuffer(0), renderer(obuffer) {}
    static Question factoryFromFile(const char* datafile);
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message message;
    static void factoryFromFile(Message& message, const char* datafile);
};

const Name test_name("test.example.com");

void
MessageTest::factoryFromFile(Message& message, const char* datafile)
{
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    message.fromWire(buffer);
}

TEST_F(MessageTest, RcodeConstruct)
{
    // normal cases
    EXPECT_EQ(0, Rcode(0).getCode());
    EXPECT_EQ(0xfff, Rcode(0xfff).getCode()); // possible max code

    // should fail on attempt of construction with an out of range code
    EXPECT_THROW(Rcode(0x1000), isc::OutOfRange);
    EXPECT_THROW(Rcode(0xffff), isc::OutOfRange);
}

TEST_F(MessageTest, RcodeToText)
{
    EXPECT_EQ("NOERROR", Rcode::NOERROR().toText());
    EXPECT_EQ("BADVERS", Rcode::BADVERS().toText());
    EXPECT_EQ("17", Rcode(Rcode::BADVERS().getCode() + 1).toText());
    EXPECT_EQ("4095", Rcode(Rcode(0xfff)).toText());
}

TEST_F(MessageTest, fromWire)
{
    factoryFromFile(message, "testdata/message_fromWire1");
    EXPECT_EQ(0x1035, message.getQid());
    EXPECT_EQ(Opcode::QUERY(), message.getOpcode());
    EXPECT_EQ(Rcode::NOERROR(), message.getRcode());
    EXPECT_TRUE(message.getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(message.getHeaderFlag(MessageFlag::RD()));
    EXPECT_TRUE(message.getHeaderFlag(MessageFlag::AA()));

    QuestionPtr q = *message.beginQuestion();
    EXPECT_EQ(test_name, q->getName());
    EXPECT_EQ(RRType::A(), q->getType());
    EXPECT_EQ(RRClass::IN(), q->getClass());
    EXPECT_EQ(1, message.getRRCount(Section::QUESTION()));
    EXPECT_EQ(2, message.getRRCount(Section::ANSWER()));
    EXPECT_EQ(0, message.getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(0, message.getRRCount(Section::ADDITIONAL()));

    RRsetPtr rrset = *message.beginSection(Section::ANSWER());
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

TEST_F(MessageTest, EDNS0DOBit)
{
    // Without EDNS0, DNSSEC is considered to be unsupported.
    factoryFromFile(message, "testdata/message_fromWire1");
    EXPECT_FALSE(message.isDNSSECSupported());

    // If DO bit is on, DNSSEC is considered to be supported.
    message.clear();
    factoryFromFile(message, "testdata/message_fromWire2");
    EXPECT_TRUE(message.isDNSSECSupported());

    // If DO bit is off, DNSSEC is considered to be unsupported.
    message.clear();
    factoryFromFile(message, "testdata/message_fromWire3");
    EXPECT_FALSE(message.isDNSSECSupported());
}

TEST_F(MessageTest, EDNS0UDPSize)
{
    // Without EDNS0, the default max UDP size is used.
    factoryFromFile(message, "testdata/message_fromWire1");
    EXPECT_EQ(Message::DEFAULT_MAX_UDPSIZE, message.getUDPSize());

    // If the size specified in EDNS0 > default max, use it.
    message.clear();
    factoryFromFile(message, "testdata/message_fromWire2");
    EXPECT_EQ(4096, message.getUDPSize());

    // If the size specified in EDNS0 < default max, keep using the default.
    message.clear();
    factoryFromFile(message, "testdata/message_fromWire8");
    EXPECT_EQ(Message::DEFAULT_MAX_UDPSIZE, message.getUDPSize());
}

TEST_F(MessageTest, EDNS0ExtCode)
{
    // Extended Rcode = BADVERS
    factoryFromFile(message, "testdata/message_fromWire10");
    EXPECT_EQ(Rcode::BADVERS(), message.getRcode());

    // Maximum extended Rcode
    message.clear();
    factoryFromFile(message, "testdata/message_fromWire11");
    EXPECT_EQ(0xfff, message.getRcode().getCode());
}

TEST_F(MessageTest, BadEDNS0)
{
    // OPT RR in the answer section
    EXPECT_THROW(factoryFromFile(message, "testdata/message_fromWire4"),
                 DNSMessageFORMERR);
    // multiple OPT RRs (in the additional section)
    message.clear();
    EXPECT_THROW(factoryFromFile(message, "testdata/message_fromWire5"),
                 DNSMessageFORMERR);
    // OPT RR of a non root name
    message.clear();
    EXPECT_THROW(factoryFromFile(message, "testdata/message_fromWire6"),
                 DNSMessageFORMERR);
    // Compressed owner name of OPT RR points to a root name.
    // Not necessarily bogus, but very unusual and mostly pathological.
    // We accept it, but is it okay?
    message.clear();
    EXPECT_NO_THROW(factoryFromFile(message, "testdata/message_fromWire7"));
    // Unsupported Version
    message.clear();
    EXPECT_THROW(factoryFromFile(message, "testdata/message_fromWire9"),
                 DNSMessageBADVERS);
}

TEST_F(MessageTest, toWire)
{
    message.setQid(0x1035);
    message.setOpcode(Opcode::QUERY());
    message.setRcode(Rcode::NOERROR());
    message.setHeaderFlag(MessageFlag::QR());
    message.setHeaderFlag(MessageFlag::RD());
    message.setHeaderFlag(MessageFlag::AA());
    message.addQuestion(Question(Name("test.example.com"), RRClass::IN(),
                                     RRType::A()));
    RRsetPtr rrset = RRsetPtr(new RRset(Name("test.example.com"), RRClass::IN(),
                                        RRType::A(), RRTTL(3600)));
    rrset->addRdata(in::A("192.0.2.1"));
    rrset->addRdata(in::A("192.0.2.2"));
    message.addRRset(Section::ANSWER(), rrset);

    EXPECT_EQ(1, message.getRRCount(Section::QUESTION()));
    EXPECT_EQ(2, message.getRRCount(Section::ANSWER()));
    EXPECT_EQ(0, message.getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(0, message.getRRCount(Section::ADDITIONAL()));

    message.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("testdata/message_toWire1", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, obuffer.getData(),
                        obuffer.getLength(), &data[0], data.size());
}
}
