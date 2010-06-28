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

#include <gtest/gtest.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cc/data.h>

#include <auth/auth_srv.h>
#include <auth/asio_link.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::data;
using namespace asio_link;

namespace {
const char* CONFIG_TESTDB =
    "{\"database_file\": \"" TEST_DATA_DIR "/example.sqlite3\"}";
// The following file must be non existent and must be non"creatable" (see
// the sqlite3 test).
const char* BADCONFIG_TESTDB =
    "{ \"database_file\": \"" TEST_DATA_DIR "/nodir/notexist\"}";

class AuthSrvTest : public ::testing::Test {
protected:
    AuthSrvTest() : request_message(Message::RENDER),
                    parse_message(Message::PARSE), default_qid(0x1035),
                    opcode(Opcode(Opcode::QUERY())), qname("www.example.com"),
                    qclass(RRClass::IN()), qtype(RRType::A()),
                    io_message(NULL), endpoint(NULL), request_obuffer(0),
                    request_renderer(request_obuffer),
                    response_obuffer(0), response_renderer(response_obuffer)
    {}
    ~AuthSrvTest() {
        delete io_message;
        delete endpoint;
    }
    AuthSrv server;
    Message request_message;
    Message parse_message;
    const qid_t default_qid;
    const Opcode opcode;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    IOMessage* io_message;
    const IOEndpoint* endpoint;
    OutputBuffer request_obuffer;
    MessageRenderer request_renderer;
    OutputBuffer response_obuffer;
    MessageRenderer response_renderer;
    vector<uint8_t> data;

    void createDataFromFile(const char* const datafile, int protocol);
    void createRequest(const Opcode& opcode, const Name& request_name,
                       const RRClass& rrclass, const RRType& rrtype,
                       int protocol);
};

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
AuthSrvTest::createDataFromFile(const char* const datafile,
                                const int protocol = IPPROTO_UDP)
{
    delete io_message;
    data.clear();

    delete endpoint;
    endpoint = IOEndpoint::create(protocol, IOAddress("192.0.2.1"), 5300);
    UnitTestUtil::readWireData(datafile, data);
    io_message = new IOMessage(&data[0], data.size(),
                               IOSocket::getDummyUDPSocket(), *endpoint);
}

void
AuthSrvTest::createRequest(const Opcode& opcode, const Name& request_name,
                           const RRClass& rrclass, const RRType& rrtype,
                           const int protocol = IPPROTO_UDP)
{
    request_message.setOpcode(opcode);
    request_message.setQid(default_qid);
    request_message.addQuestion(Question(request_name, rrclass, rrtype));
    request_message.toWire(request_renderer);

    delete io_message;
    endpoint = IOEndpoint::create(protocol, IOAddress("192.0.2.1"), 5300);
    io_message = new IOMessage(request_renderer.getData(),
                               request_renderer.getLength(),
                               IOSocket::getDummyUDPSocket(), *endpoint);
}

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
TEST_F(AuthSrvTest, unsupportedRequest) {
    for (unsigned int i = 1; i < 16; ++i) {
        // set Opcode to 'i', which iterators over all possible codes except
        // the standard query (0) and notify(4)
        if (i == 4)
            continue;
        createDataFromFile("simplequery_fromWire");
        data[2] = ((i << 3) & 0xff);

        parse_message.clear(Message::PARSE);
        EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                              response_renderer));
        headerCheck(parse_message, default_qid, Rcode::NOTIMP(), i, QR_FLAG,
                    0, 0, 0, 0);
    }
}

// Simple API check
TEST_F(AuthSrvTest, verbose) {
    EXPECT_FALSE(server.getVerbose());
    server.setVerbose(true);
    EXPECT_TRUE(server.getVerbose());
    server.setVerbose(false);
    EXPECT_FALSE(server.getVerbose());
}

// Multiple questions.  Should result in FORMERR.
TEST_F(AuthSrvTest, multiQuestion) {
    createDataFromFile("multiquestion_fromWire");
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 2, 0, 0, 0);

    QuestionIterator qit = parse_message.beginQuestion();
    EXPECT_EQ(Name("example.com"), (*qit)->getName());
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(RRType::A(), (*qit)->getType());
    ++qit;
    EXPECT_EQ(Name("example.com"), (*qit)->getName());
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(RRType::AAAA(), (*qit)->getType());
    ++qit;
    EXPECT_TRUE(qit == parse_message.endQuestion());
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
TEST_F(AuthSrvTest, shortMessage) {
    createDataFromFile("shortmessage_fromWire");
    EXPECT_EQ(false, server.processMessage(*io_message, parse_message,
                                           response_renderer));
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(AuthSrvTest, response) {
    // A valid (although unusual) response
    createDataFromFile("simpleresponse_fromWire");
    EXPECT_EQ(false, server.processMessage(*io_message, parse_message,
                                           response_renderer));

    // A response with a broken question section.  must be dropped rather than
    // returning FORMERR.
    createDataFromFile("shortresponse_fromWire");
    EXPECT_EQ(false, server.processMessage(*io_message, parse_message,
                                           response_renderer));

    // A response to iquery.  must be dropped rather than returning NOTIMP.
    createDataFromFile("iqueryresponse_fromWire");
    EXPECT_EQ(false, server.processMessage(*io_message, parse_message,
                                           response_renderer));
}

// Query with a broken question
TEST_F(AuthSrvTest, shortQuestion) {
    createDataFromFile("shortquestion_fromWire");
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    // Since the query's question is broken, the question section of the
    // response should be empty.
    headerCheck(parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 0, 0, 0, 0);
}

// Query with a broken answer section
TEST_F(AuthSrvTest, shortAnswer) {
    createDataFromFile("shortanswer_fromWire");
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));

    // This is a bogus query, but question section is valid.  So the response
    // should copy the question section.
    headerCheck(parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);

    QuestionIterator qit = parse_message.beginQuestion();
    EXPECT_EQ(Name("example.com"), (*qit)->getName());
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(RRType::A(), (*qit)->getType());
    ++qit;
    EXPECT_TRUE(qit == parse_message.endQuestion());
}

// Query with unsupported version of EDNS.
TEST_F(AuthSrvTest, ednsBadVers) {
    createDataFromFile("queryBadEDNS_fromWire");
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));

    // The response must have an EDNS OPT RR in the additional section.
    // Note that the DNSSEC DO bit is cleared even if this bit in the query
    // is set.  This is a limitation of the current implementation.
    headerCheck(parse_message, default_qid, Rcode::BADVERS(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 1);
    EXPECT_EQ(4096, parse_message.getUDPSize());
    EXPECT_FALSE(parse_message.isDNSSECSupported());
}

TEST_F(AuthSrvTest, AXFROverUDP) {
    // AXFR over UDP is invalid and should result in FORMERR.
    createRequest(opcode, Name("example.com"), RRClass::IN(), RRType::AXFR(),
                  IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyInTest) {
    createRequest(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                  RRType::SOA());
    EXPECT_EQ(false, server.processMessage(*io_message, parse_message,
                                           response_renderer));
}

void
updateConfig(AuthSrv* server, const char* const dbfile,
             const bool expect_success)
{
    const ElementPtr config_answer =
        server->updateConfig(Element::createFromString(dbfile));
    EXPECT_EQ(Element::map, config_answer->getType());
    EXPECT_TRUE(config_answer->contains("result"));

    const ElementPtr result = config_answer->get("result");
    EXPECT_EQ(Element::list, result->getType());
    EXPECT_EQ(expect_success ? 0 : 1, result->get(0)->intValue());
}

// Install a Sqlite3 data source with testing data.
TEST_F(AuthSrvTest, updateConfig) {
    updateConfig(&server, CONFIG_TESTDB, true);

    // query for existent data in the installed data source.  The resulting
    // response should have the AA flag on, and have an RR in each answer
    // and authority section.
    createDataFromFile("examplequery_fromWire");
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::NOERROR(), opcode.getCode(),
                QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}

TEST_F(AuthSrvTest, datasourceFail) {
    updateConfig(&server, CONFIG_TESTDB, true);

    // This query will hit a corrupted entry of the data source (the zoneload
    // tool and the data source itself naively accept it).  This will result
    // in a SERVFAIL response, and the answer and authority sections should
    // be empty.
    createDataFromFile("badExampleQuery_fromWire");
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::SERVFAIL(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, updateConfigFail) {
    // First, load a valid data source.
    updateConfig(&server, CONFIG_TESTDB, true);

    // Next, try to update it with a non-existent one.  This should fail.
    updateConfig(&server, BADCONFIG_TESTDB, false);

    // The original data source should still exist.
    createDataFromFile("examplequery_fromWire");
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::NOERROR(), opcode.getCode(),
                QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}
}
