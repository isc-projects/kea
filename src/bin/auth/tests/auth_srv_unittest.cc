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
#include <datasrc/memory_datasrc.h>
#include <auth/auth_srv.h>
#include <testutils/srv_unittest.h>
#include <auth/statistics.h>

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

class AuthSrvTest : public SrvTestBase {
protected:
    AuthSrvTest() : server(true, xfrout), rrclass(RRClass::IN()) {
        server.setXfrinSession(&notify_session);
        server.setStatisticsSession(&statistics_session);
    }
    MockSession statistics_session;
    MockXfroutClient xfrout;
    AuthSrv server;
    const RRClass rrclass;
};

// Unsupported requests.  Should result in NOTIMP.
TEST_F(AuthSrvTest, unsupportedRequest) {
    UNSUPPORTED_REQUEST_TEST;
}

// Simple API check
TEST_F(AuthSrvTest, verbose) {
    VERBOSE_TEST;
}

// Multiple questions.  Should result in FORMERR.
TEST_F(AuthSrvTest, multiQuestion) {
    MULTI_QUESTION_TEST;
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
TEST_F(AuthSrvTest, shortMessage) {
    SHORT_MESSAGE_TEST;
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(AuthSrvTest, response) {
    RESPONSE_TEST;
}

// Query with a broken question
TEST_F(AuthSrvTest, shortQuestion) {
    SHORT_QUESTION_TEST;
}

// Query with a broken answer section
TEST_F(AuthSrvTest, shortAnswer) {
    SHORT_ANSWER_TEST;
}

// Query with unsupported version of EDNS.
TEST_F(AuthSrvTest, ednsBadVers) {
    EDNS_BADVERS_TEST;
}

TEST_F(AuthSrvTest, AXFROverUDP) {
    AXFR_OVER_UDP_TEST;
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
updateConfig(AuthSrv* server, const char* const config_data,
             const bool expect_success)
{
    ConstElementPtr config_answer =
        server->updateConfig(Element::fromJSON(config_data));
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

TEST_F(AuthSrvTest, updateWithMemoryDataSrc) {
    // Test configuring memory data source.  Detailed test cases are covered
    // in the configuration tests.  We only check the AuthSrv interface here.

    // By default memory data source isn't enabled
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
    updateConfig(&server,
                 "{\"datasources\": [{\"type\": \"memory\"}]}", true);
    // after successful configuration, we should have one (with empty zoneset).
    ASSERT_NE(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
    EXPECT_EQ(0, server.getMemoryDataSrc(rrclass)->getZoneCount());

    // The memory data source is empty, should return REFUSED rcode.
    createDataFromFile("examplequery_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::REFUSED(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, chQueryWithMemoryDataSrc) {
    // Configure memory data source for class IN
    updateConfig(&server, "{\"datasources\": "
                 "[{\"class\": \"IN\", \"type\": \"memory\"}]}", true);

    // This shouldn't affect the result of class CH query
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("version.bind"),
                                       RRClass::CH(), RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}

TEST_F(AuthSrvTest, cacheSlots) {
    // simple check for the get/set operations
    server.setCacheSlots(10);    // 10 = arbitrary choice
    EXPECT_EQ(10, server.getCacheSlots());

    // 0 is a valid size
    server.setCacheSlots(0);
    EXPECT_EQ(00, server.getCacheSlots());
}

// Submit UDP normal query and check query counter
TEST_F(AuthSrvTest, queryCounterUDPNormal) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, server.getCounter(AuthCounters::COUNTER_UDP_QUERY));
    // Create UDP message and process.
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    // After processing UDP query, the counter should be 1.
    EXPECT_EQ(1, server.getCounter(AuthCounters::COUNTER_UDP_QUERY));
}

// Submit TCP normal query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPNormal) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, server.getCounter(AuthCounters::COUNTER_TCP_QUERY));
    // Create TCP message and process.
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    // After processing TCP query, the counter should be 1.
    EXPECT_EQ(1, server.getCounter(AuthCounters::COUNTER_TCP_QUERY));
}

// Submit TCP AXFR query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPAXFR) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, server.getCounter(AuthCounters::COUNTER_TCP_QUERY));
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // On success, the AXFR query has been passed to a separate process,
    // so we shouldn't have to respond.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    // After processing TCP AXFR query, the counter should be 1.
    EXPECT_EQ(1, server.getCounter(AuthCounters::COUNTER_TCP_QUERY));
}

// class for queryCounterUnexpected test
// getProtocol() returns IPPROTO_IP
class DummyUnknownSocket : public IOSocket {
public:
    DummyUnknownSocket() {}
    virtual int getNative() const { return (0); }
    virtual int getProtocol() const { return (IPPROTO_IP); }
};

// function for queryCounterUnexpected test
// returns a reference to a static object of DummyUnknownSocket
IOSocket&
getDummyUnknownSocket() {
    static DummyUnknownSocket socket;
    return (socket);
}

// Submit unexpected type of query and check it throws isc::Unexpected
TEST_F(AuthSrvTest, queryCounterUnexpected) {
    // This code isn't exception safe, but we'd rather keep the code
    // simpler and more readable as this is only for tests and if it throws
    // the program would immediately terminate anyway.

    // Create UDP query packet.
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    createRequestPacket(request_message, IPPROTO_UDP);

    // Modify the message.
    delete io_message;
    endpoint = IOEndpoint::create(IPPROTO_UDP,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    io_message = new IOMessage(request_renderer.getData(),
                               request_renderer.getLength(),
                               getDummyUnknownSocket(), *endpoint);

    EXPECT_THROW(server.processMessage(*io_message, parse_message,
                                       response_obuffer, &dnsserv),
                 isc::Unexpected);
}
}
