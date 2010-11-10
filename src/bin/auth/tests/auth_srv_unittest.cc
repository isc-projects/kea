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

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cc/data.h>
#include <cc/session.h>

#include <xfr/xfrout_client.h>

#include <auth/auth_srv.h>
#include <asiolink/asiolink.h>

#include <dns/tests/unittest_util.h>
#include <auth/tests/mockups.h>

using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::xfr;
using namespace asiolink;
using isc::UnitTestUtil;

namespace {
const char* const CONFIG_TESTDB =
    "{\"database_file\": \"" TEST_DATA_DIR "/example.sqlite3\"}";
// The following file must be non existent and must be non"creatable" (see
// the sqlite3 test).
const char* const BADCONFIG_TESTDB =
    "{ \"database_file\": \"" TEST_DATA_DIR "/nodir/notexist\"}";
const char* const DEFAULT_REMOTE_ADDRESS = "192.0.2.1";

class AuthSrvTest : public ::testing::Test {
protected:
    AuthSrvTest() : server(true, xfrout),
                    request_message(Message::RENDER),
                    parse_message(new Message(Message::PARSE)),
                    default_qid(0x1035), opcode(Opcode(Opcode::QUERY())),
                    qname("www.example.com"), qclass(RRClass::IN()),
                    qtype(RRType::A()), io_message(NULL), endpoint(NULL),
                    request_obuffer(0), request_renderer(request_obuffer),
                    response_obuffer(new OutputBuffer(0))
    {
        server.setXfrinSession(&notify_session);
    }
    ~AuthSrvTest() {
        delete io_message;
        delete endpoint;
    }
    MockSession notify_session;
    MockXfroutClient xfrout;
    MockServer dnsserv;
    AuthSrv server;
    Message request_message;
    MessagePtr parse_message;
    const qid_t default_qid;
    const Opcode opcode;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    IOSocket* io_sock;
    IOMessage* io_message;
    const IOEndpoint* endpoint;
    OutputBuffer request_obuffer;
    MessageRenderer request_renderer;
    OutputBufferPtr response_obuffer;
    vector<uint8_t> data;

    void createDataFromFile(const char* const datafile, int protocol);
    void createRequestPacket(Message& message, const int protocol);
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

    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    UnitTestUtil::readWireData(datafile, data);
    io_sock = (protocol == IPPROTO_UDP) ? &IOSocket::getDummyUDPSocket() :
        &IOSocket::getDummyTCPSocket();
    io_message = new IOMessage(&data[0], data.size(), *io_sock, *endpoint);
}

void
AuthSrvTest::createRequestPacket(Message& message,
                                 const int protocol = IPPROTO_UDP)
{
    message.toWire(request_renderer);

    delete io_message;

    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    io_sock = (protocol == IPPROTO_UDP) ? &IOSocket::getDummyUDPSocket() :
        &IOSocket::getDummyTCPSocket();
    io_message = new IOMessage(request_renderer.getData(),
                               request_renderer.getLength(),
                               *io_sock, *endpoint);
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
    EXPECT_EQ((flags & QR_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_EQ((flags & AA_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ((flags & TC_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_TC));
    EXPECT_EQ((flags & RA_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_RA));
    EXPECT_EQ((flags & RD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_EQ((flags & AD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_AD));
    EXPECT_EQ((flags & CD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_CD));

    EXPECT_EQ(qdcount, message.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(ancount, message.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(nscount, message.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(arcount, message.getRRCount(Message::SECTION_ADDITIONAL));
}

// Unsupported requests.  Should result in NOTIMP.
TEST_F(AuthSrvTest, unsupportedRequest) {
    for (unsigned int i = 0; i < 16; ++i) {
        // set Opcode to 'i', which iterators over all possible codes except
        // the standard query and notify
        if (i == Opcode::QUERY().getCode() ||
            i == Opcode::NOTIFY().getCode()) {
            continue;
        }
        createDataFromFile("simplequery_fromWire.wire");
        data[2] = ((i << 3) & 0xff);

        parse_message->clear(Message::PARSE);
        server.processMessage(*io_message, parse_message, response_obuffer,
                              &dnsserv);
        EXPECT_TRUE(dnsserv.hasAnswer());
        headerCheck(*parse_message, default_qid, Rcode::NOTIMP(), i, QR_FLAG,
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
    createDataFromFile("multiquestion_fromWire.wire");
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
TEST_F(AuthSrvTest, shortMessage) {
    createDataFromFile("shortmessage_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(AuthSrvTest, response) {
    // A valid (although unusual) response
    createDataFromFile("simpleresponse_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());

    // A response with a broken question section.  must be dropped rather than
    // returning FORMERR.
    createDataFromFile("shortresponse_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());

    // A response to iquery.  must be dropped rather than returning NOTIMP.
    createDataFromFile("iqueryresponse_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

// Query with a broken question
TEST_F(AuthSrvTest, shortQuestion) {
    createDataFromFile("shortquestion_fromWire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    // Since the query's question is broken, the question section of the
    // response should be empty.
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 0, 0, 0, 0);
}

// Query with a broken answer section
TEST_F(AuthSrvTest, shortAnswer) {
    createDataFromFile("shortanswer_fromWire.wire");
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
TEST_F(AuthSrvTest, ednsBadVers) {
    createDataFromFile("queryBadEDNS_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());

    // The response must have an EDNS OPT RR in the additional section, but
    // it will be added automatically at the render time.
    // Note that the DNSSEC DO bit is cleared even if this bit in the query
    // is set.  This is a limitation of the current implementation.
    headerCheck(*parse_message, default_qid, Rcode::BADVERS(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 1);
    EXPECT_FALSE(parse_message->getEDNS()); // EDNS isn't added at this point

    InputBuffer ib(response_obuffer->getData(), response_obuffer->getLength());
    Message parsed(Message::PARSE);
    parsed.fromWire(ib);
    EXPECT_EQ(Rcode::BADVERS(), parsed.getRcode());
    ConstEDNSPtr edns(parsed.getEDNS());
    ASSERT_TRUE(edns);
    EXPECT_FALSE(edns->getDNSSECAwareness());
}

TEST_F(AuthSrvTest, AXFROverUDP) {
    // AXFR over UDP is invalid and should result in FORMERR.
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(),
                         RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, AXFRSuccess) {
    EXPECT_FALSE(xfrout.isConnected());
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // On success, the AXFR query has been passed to a separate process,
    // so we shouldn't have to respond.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, AXFRConnectFail) {
    EXPECT_FALSE(xfrout.isConnected()); // check prerequisite
    xfrout.disableConnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
    EXPECT_FALSE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, AXFRSendFail) {
    // first send a valid query, making the connection with the xfr process
    // open.
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(xfrout.isConnected());

    xfrout.disableSend();
    parse_message->clear(Message::PARSE);
    response_obuffer->clear();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);

    // The connection should have been closed due to the send failure.
    EXPECT_FALSE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, AXFRDisconnectFail) {
    // In our usage disconnect() shouldn't fail.  So we'll see the exception
    // should it be thrown.
    xfrout.disableSend();
    xfrout.disableDisconnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    EXPECT_THROW(server.processMessage(*io_message, parse_message,
                                       response_obuffer, &dnsserv),
                 XfroutError);
    EXPECT_TRUE(xfrout.isConnected());
    // XXX: we need to re-enable disconnect.  otherwise an exception would be
    // thrown via the destructor of the server.
    xfrout.enableDisconnect();
}

TEST_F(AuthSrvTest, notify) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());

    // An internal command message should have been created and sent to an
    // external module.  Check them.
    EXPECT_EQ("Zonemgr", notify_session.getMessageDest());
    EXPECT_EQ("notify",
              notify_session.getSentMessage()->get("command")->get(0)->stringValue());
    ConstElementPtr notify_args =
        notify_session.getSentMessage()->get("command")->get(1);
    EXPECT_EQ("example.com.", notify_args->get("zone_name")->stringValue());
    EXPECT_EQ(DEFAULT_REMOTE_ADDRESS,
              notify_args->get("master")->stringValue());
    EXPECT_EQ("IN", notify_args->get("zone_class")->stringValue());

    // On success, the server should return a response to the notify.
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                Opcode::NOTIFY().getCode(), QR_FLAG | AA_FLAG, 1, 0, 0, 0);

    // The question must be identical to that of the received notify
    ConstQuestionPtr question = *parse_message->beginQuestion();
    EXPECT_EQ(Name("example.com"), question->getName());
    EXPECT_EQ(RRClass::IN(), question->getClass());
    EXPECT_EQ(RRType::SOA(), question->getType());
}

TEST_F(AuthSrvTest, notifyForCHClass) {
    // Same as the previous test, but for the CH RRClass.
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::CH(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());

    // Other conditions should be the same, so simply confirm the RR class is
    // set correctly.
    ConstElementPtr notify_args =
        notify_session.getSentMessage()->get("command")->get(1);
    EXPECT_EQ("CH", notify_args->get("zone_class")->stringValue());
}

TEST_F(AuthSrvTest, notifyEmptyQuestion) {
    request_message.clear(Message::RENDER);
    request_message.setOpcode(Opcode::NOTIFY());
    request_message.setRcode(Rcode::NOERROR());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    request_message.setQid(default_qid);
    request_message.toWire(request_renderer);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 0, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyMultiQuestions) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    // add one more SOA question
    request_message.addQuestion(Question(Name("example.com"), RRClass::IN(),
                                         RRType::SOA()));
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 2, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyNonSOAQuestion) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::NS());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithoutAA) {
    // implicitly leave the AA bit off.  our implementation will accept it.
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                Opcode::NOTIFY().getCode(), QR_FLAG | AA_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithErrorRcode) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    request_message.setRcode(Rcode::SERVFAIL());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                Opcode::NOTIFY().getCode(), QR_FLAG | AA_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithoutSession) {
    server.setXfrinSession(NULL);

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);

    // we simply ignore the notify and let it be resent if an internal error
    // happens.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifySendFail) {
    notify_session.disableSend();

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);

    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyReceiveFail) {
    notify_session.disableReceive();

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyWithBogusSessionMessage) {
    notify_session.setMessage(Element::fromJSON("{\"foo\": 1}"));

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyWithSessionMessageError) {
    notify_session.setMessage(
        Element::fromJSON("{\"result\": [1, \"FAIL\"]}"));

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(), default_qid,
                         Name("example.com"), RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

void
updateConfig(AuthSrv* server, const char* const dbfile,
             const bool expect_success)
{
    ConstElementPtr config_answer =
        server->updateConfig(Element::fromJSON(dbfile));
    EXPECT_EQ(Element::map, config_answer->getType());
    EXPECT_TRUE(config_answer->contains("result"));

    ConstElementPtr result = config_answer->get("result");
    EXPECT_EQ(Element::list, result->getType());
    EXPECT_EQ(expect_success ? 0 : 1, result->get(0)->intValue());
}

// Install a Sqlite3 data source with testing data.
TEST_F(AuthSrvTest, updateConfig) {
    updateConfig(&server, CONFIG_TESTDB, true);

    // query for existent data in the installed data source.  The resulting
    // response should have the AA flag on, and have an RR in each answer
    // and authority section.
    createDataFromFile("examplequery_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(), opcode.getCode(),
                QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}

TEST_F(AuthSrvTest, datasourceFail) {
    updateConfig(&server, CONFIG_TESTDB, true);

    // This query will hit a corrupted entry of the data source (the zoneload
    // tool and the data source itself naively accept it).  This will result
    // in a SERVFAIL response, and the answer and authority sections should
    // be empty.
    createDataFromFile("badExampleQuery_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, updateConfigFail) {
    // First, load a valid data source.
    updateConfig(&server, CONFIG_TESTDB, true);

    // Next, try to update it with a non-existent one.  This should fail.
    updateConfig(&server, BADCONFIG_TESTDB, false);

    // The original data source should still exist.
    createDataFromFile("examplequery_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(), opcode.getCode(),
                QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}

TEST_F(AuthSrvTest, cacheSlots) {
    // simple check for the get/set operations
    server.setCacheSlots(10);    // 10 = arbitrary choice
    EXPECT_EQ(10, server.getCacheSlots());

    // 0 is a valid size
    server.setCacheSlots(0);
    EXPECT_EQ(00, server.getCacheSlots());
}
}
