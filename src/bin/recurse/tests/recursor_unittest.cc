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

#include <config.h>

#include <gtest/gtest.h>

#include <asiolink/asiolink.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cc/data.h>
#include <cc/session.h>

#include <recurse/recursor.h>
#include <recurse/common.h>

#include <dns/tests/unittest_util.h>

#include <auth/tests/mockups.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::data;
using namespace asiolink;

namespace {
const char* const DEFAULT_REMOTE_ADDRESS = "192.0.2.1";
const char* const TEST_PORT = "53535";

class DummySocket : public IOSocket {
private:
    DummySocket(const DummySocket& source);
    DummySocket& operator=(const DummySocket& source);
public:
    DummySocket(const int protocol) : protocol_(protocol) {}
    virtual int getNative() const { return (-1); }
    virtual int getProtocol() const { return (protocol_); }
private:
    const int protocol_;
};

class RecursorTest : public ::testing::Test {
protected:
    RecursorTest() : ios(*TEST_PORT, true, false, NULL, NULL, NULL),
                    server(*DEFAULT_REMOTE_ADDRESS),
                    request_message(Message::RENDER),
                    parse_message(new Message(Message::PARSE)),
                    default_qid(0x1035), opcode(Opcode(Opcode::QUERY())),
                    qname("www.example.com"),
                    qclass(RRClass::IN()), qtype(RRType::A()),
                    io_message(NULL), endpoint(NULL), request_obuffer(0),
                    request_renderer(request_obuffer),
                    response_obuffer(new OutputBuffer(0))
    {}
    ~RecursorTest() {
        delete io_message;
        delete endpoint;
    }
    MockSession notify_session;
    MockServer dnsserv;
    IOService ios;
    Recursor server;
    Message request_message;
    MessagePtr parse_message;
    const qid_t default_qid;
    const Opcode opcode;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    IOMessage* io_message;
    IOSocket* io_sock;
    const IOEndpoint* endpoint;
    OutputBuffer request_obuffer;
    MessageRenderer request_renderer;
    OutputBufferPtr response_obuffer;
    vector<uint8_t> data;

    void createDataFromFile(const char* const datafile, int protocol);
    void createRequestPacket(Message& message, int protocol);
};

void
RecursorTest::createDataFromFile(const char* const datafile,
                                const int protocol = IPPROTO_UDP)
{
    delete io_message;
    data.clear();

    delete endpoint;
    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    UnitTestUtil::readWireData(datafile, data);
    io_sock = new DummySocket(protocol);
    io_message = new IOMessage(&data[0], data.size(), *io_sock, *endpoint);
}

void
RecursorTest::createRequestPacket(Message& message,
                                  const int protocol = IPPROTO_UDP)
{
    message.toWire(request_renderer);

    delete io_message;

    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    io_sock = new DummySocket(protocol);
    io_message = new IOMessage(request_renderer.getData(),
                               request_renderer.getLength(),
                               *io_sock, *endpoint);
}

// These are flags to indicate whether the corresponding flag bit of the
// DNS header is to be set in the test cases.  (Note that the flag values
// is irrelevant to their wire-format values)
const unsigned int QR_FLAG = 0x1;
const unsigned int AA_FLAG = 0x2;
const unsigned int TC_FLAG = 0x4;
const unsigned int RD_FLAG = 0x8;
const unsigned int RA_FLAG = 0x10;
const unsigned int AD_FLAG = 0x20;
const unsigned int CD_FLAG = 0x40;

void
headerCheck(const Message& message, const qid_t qid, const Rcode& rcode,
            const uint16_t opcodeval, const unsigned int flags,
            const unsigned int qdcount,
            const unsigned int ancount, const unsigned int nscount,
            const unsigned int arcount)
{
    EXPECT_EQ(qid, message.getQid());
    EXPECT_EQ(rcode, message.getRcode());
    EXPECT_EQ(opcodeval, message.getOpcode().getCode());
    EXPECT_EQ((flags & QR_FLAG) != 0, message.getHeaderFlag(MessageFlag::QR()));
    EXPECT_EQ((flags & AA_FLAG) != 0, message.getHeaderFlag(MessageFlag::AA()));
    EXPECT_EQ((flags & TC_FLAG) != 0, message.getHeaderFlag(MessageFlag::TC()));
    EXPECT_EQ((flags & RA_FLAG) != 0, message.getHeaderFlag(MessageFlag::RA()));
    EXPECT_EQ((flags & RD_FLAG) != 0, message.getHeaderFlag(MessageFlag::RD()));
    EXPECT_EQ((flags & AD_FLAG) != 0, message.getHeaderFlag(MessageFlag::AD()));
    EXPECT_EQ((flags & CD_FLAG) != 0, message.getHeaderFlag(MessageFlag::CD()));

    EXPECT_EQ(qdcount, message.getRRCount(Section::QUESTION()));
    EXPECT_EQ(ancount, message.getRRCount(Section::ANSWER()));
    EXPECT_EQ(nscount, message.getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(arcount, message.getRRCount(Section::ADDITIONAL()));
}

// Unsupported requests.  Should result in NOTIMP.
TEST_F(RecursorTest, unsupportedRequest) {
    for (unsigned int i = 0; i < 16; ++i) {
        // set Opcode to 'i', which iterators over all possible codes except
        // the standard query and notify
        if (i == Opcode::QUERY().getCode() ||
            i == Opcode::NOTIFY().getCode()) {
            continue;
        }
        createDataFromFile("simplequery_fromWire");
        data[2] = ((i << 3) & 0xff);

        parse_message->clear(Message::PARSE);
        server.processMessage(*io_message, parse_message,
                              response_obuffer, &dnsserv);
        EXPECT_TRUE(dnsserv.hasAnswer());
        headerCheck(*parse_message, default_qid, Rcode::NOTIMP(), i, QR_FLAG,
                    0, 0, 0, 0);
    }
}

// Simple API check
TEST_F(RecursorTest, verbose) {
    EXPECT_FALSE(server.getVerbose());
    server.setVerbose(true);
    EXPECT_TRUE(server.getVerbose());
    server.setVerbose(false);
    EXPECT_FALSE(server.getVerbose());
}

// Multiple questions.  Should result in FORMERR.
TEST_F(RecursorTest, multiQuestion) {
    createDataFromFile("multiquestion_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 2, 0, 0, 0);

    QuestionIterator qit = parse_message->beginQuestion();
    EXPECT_EQ(Name("example.com"), (*qit)->getName());
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(RRType::A(), (*qit)->getType());
    ++qit;
    EXPECT_EQ(Name("example.com"), (*qit)->getName());
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(RRType::AAAA(), (*qit)->getType());
    ++qit;
    EXPECT_TRUE(qit == parse_message->endQuestion());
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
TEST_F(RecursorTest, shortMessage) {
    createDataFromFile("shortmessage_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(RecursorTest, response) {
    // A valid (although unusual) response
    createDataFromFile("simpleresponse_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());

    // A response with a broken question section.  must be dropped rather than
    // returning FORMERR.
    createDataFromFile("shortresponse_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());

    // A response to iquery.  must be dropped rather than returning NOTIMP.
    createDataFromFile("iqueryresponse_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

// Query with a broken question
TEST_F(RecursorTest, shortQuestion) {
    createDataFromFile("shortquestion_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    // Since the query's question is broken, the question section of the
    // response should be empty.
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 0, 0, 0, 0);
}

// Query with a broken answer section
TEST_F(RecursorTest, shortAnswer) {
    createDataFromFile("shortanswer_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());

    // This is a bogus query, but question section is valid.  So the response
    // should copy the question section.
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);

    QuestionIterator qit = parse_message->beginQuestion();
    EXPECT_EQ(Name("example.com"), (*qit)->getName());
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(RRType::A(), (*qit)->getType());
    ++qit;
    EXPECT_TRUE(qit == parse_message->endQuestion());
}

// Query with unsupported version of EDNS.
TEST_F(RecursorTest, ednsBadVers) {
    createDataFromFile("queryBadEDNS_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());

    // The response must have an EDNS OPT RR in the additional section.
    // Note that the DNSSEC DO bit is cleared even if this bit in the query
    // is set.  This is a limitation of the current implementation.
    headerCheck(*parse_message, default_qid, Rcode::BADVERS(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 1);
    EXPECT_EQ(4096, parse_message->getUDPSize());
    EXPECT_FALSE(parse_message->isDNSSECSupported());
}

TEST_F(RecursorTest, AXFROverUDP) {
    // AXFR over UDP is invalid and should result in FORMERR.
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                        Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
}

TEST_F(RecursorTest, AXFRFail) {
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // AXFR is not implemented and should always send NOTIMP.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOTIMP(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
}

TEST_F(RecursorTest, notifyFail) {
    // Notify should always return NOTAUTH
    request_message.clear(Message::RENDER);
    request_message.setOpcode(Opcode::NOTIFY());
    request_message.setHeaderFlag(MessageFlag::AA());
    request_message.setQid(default_qid);
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOTAUTH(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 0, 0, 0, 0);
}

}
