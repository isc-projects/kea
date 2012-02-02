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

#include <config.h>

#include <vector>

#include <boost/shared_ptr.hpp>

#include <gtest/gtest.h>

#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>
#include <dns/tsig.h>

#include <server_common/portconfig.h>
#include <server_common/keyring.h>

#include <datasrc/memory_datasrc.h>
#include <auth/auth_srv.h>
#include <auth/common.h>
#include <auth/statistics.h>

#include <dns/tests/unittest_util.h>
#include <testutils/dnsmessage_test.h>
#include <testutils/srv_test.h>
#include <testutils/portconfig.h>
#include <testutils/socket_request.h>

using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::xfr;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::testutils;
using namespace isc::server_common::portconfig;
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
    AuthSrvTest() :
        dnss_(ios_, NULL, NULL, NULL),
        server(true, xfrout),
        rrclass(RRClass::IN()),
        sock_requestor_(dnss_, address_store_, 53210, "")
    {
        server.setDNSService(dnss_);
        server.setXfrinSession(&notify_session);
        server.setStatisticsSession(&statistics_session);
    }
    virtual void processMessage() {
        server.processMessage(*io_message, parse_message, response_obuffer,
                              &dnsserv);
    }
    IOService ios_;
    DNSService dnss_;
    MockSession statistics_session;
    MockXfroutClient xfrout;
    AuthSrv server;
    const RRClass rrclass;
    vector<uint8_t> response_data;
    AddressList address_store_;
    TestSocketRequestor sock_requestor_;
};

// A helper function that builds a response to version.bind/TXT/CH that
// should be identical to the response from our builtin (static) data source
// by default.  The resulting wire-format data will be stored in 'data'.
void
createBuiltinVersionResponse(const qid_t qid, vector<uint8_t>& data) {
    const Name version_name("version.bind");
    Message message(Message::RENDER);

    UnitTestUtil::createRequestMessage(message, Opcode::QUERY(),
                                       qid, version_name,
                                       RRClass::CH(), RRType::TXT());
    message.setHeaderFlag(Message::HEADERFLAG_QR);
    message.setHeaderFlag(Message::HEADERFLAG_AA);
    RRsetPtr rrset_version = RRsetPtr(new RRset(version_name, RRClass::CH(),
                                                RRType::TXT(), RRTTL(0)));
    rrset_version->addRdata(generic::TXT(PACKAGE_STRING));
    message.addRRset(Message::SECTION_ANSWER, rrset_version);

    RRsetPtr rrset_version_ns = RRsetPtr(new RRset(version_name, RRClass::CH(),
                                                   RRType::NS(), RRTTL(0)));
    rrset_version_ns->addRdata(generic::NS(version_name));
    message.addRRset(Message::SECTION_AUTHORITY, rrset_version_ns);

    OutputBuffer obuffer(0);
    MessageRenderer renderer(obuffer);
    message.toWire(renderer);

    data.clear();
    data.assign(static_cast<const uint8_t*>(renderer.getData()),
                static_cast<const uint8_t*>(renderer.getData()) +
                renderer.getLength());
}

// In the following tests we confirm the response data is rendered in
// wire format in the expected way.

// The most primitive check: checking the result of the processMessage()
// method
TEST_F(AuthSrvTest, builtInQuery) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("version.bind"),
                                       RRClass::CH(), RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    createBuiltinVersionResponse(default_qid, response_data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        response_obuffer->getData(),
                        response_obuffer->getLength(),
                        &response_data[0], response_data.size());
}

// Same test emulating the UDPServer class behavior (defined in libasiolink).
// This is not a good test in that it assumes internal implementation details
// of UDPServer, but we've encountered a regression due to the introduction
// of that class, so we add a test for that case to prevent such a regression
// in future.
// Besides, the generalization of UDPServer is probably too much for the
// authoritative only server in terms of performance, and it's quite likely
// we need to drop it for the authoritative server implementation.
// At that point we can drop this test, too.
TEST_F(AuthSrvTest, builtInQueryViaDNSServer) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("version.bind"),
                                       RRClass::CH(), RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP);

    (*server.getDNSLookupProvider())(*io_message, parse_message,
                                     response_message,
                                     response_obuffer, &dnsserv);
    (*server.getDNSAnswerProvider())(*io_message, parse_message,
                                     response_message, response_obuffer);

    createBuiltinVersionResponse(default_qid, response_data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        response_obuffer->getData(),
                        response_obuffer->getLength(),
                        &response_data[0], response_data.size());
}

// Same type of test as builtInQueryViaDNSServer but for an error response.
TEST_F(AuthSrvTest, iqueryViaDNSServer) {
    createDataFromFile("iquery_fromWire.wire");
    (*server.getDNSLookupProvider())(*io_message, parse_message,
                                     response_message,
                                     response_obuffer, &dnsserv);
    (*server.getDNSAnswerProvider())(*io_message, parse_message,
                                     response_message, response_obuffer);

    UnitTestUtil::readWireData("iquery_response_fromWire.wire",
                               response_data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        response_obuffer->getData(),
                        response_obuffer->getLength(),
                        &response_data[0], response_data.size());
}

// Unsupported requests.  Should result in NOTIMP.
TEST_F(AuthSrvTest, unsupportedRequest) {
    unsupportedRequest();
}

// Multiple questions.  Should result in FORMERR.
TEST_F(AuthSrvTest, multiQuestion) {
    multiQuestion();
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
TEST_F(AuthSrvTest, shortMessage) {
    shortMessage();
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(AuthSrvTest, response) {
    response();
}

// Query with a broken question
TEST_F(AuthSrvTest, shortQuestion) {
    shortQuestion();
}

// Query with a broken answer section
TEST_F(AuthSrvTest, shortAnswer) {
    shortAnswer();
}

// Query with unsupported version of EDNS.
TEST_F(AuthSrvTest, ednsBadVers) {
    ednsBadVers();
}

TEST_F(AuthSrvTest, AXFROverUDP) {
    axfrOverUDP();
}

TEST_F(AuthSrvTest, AXFRSuccess) {
    EXPECT_FALSE(xfrout.isConnected());
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // On success, the AXFR query has been passed to a separate process,
    // so we shouldn't have to respond.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(xfrout.isConnected());
}

// Try giving the server a TSIG signed request and see it can anwer signed as
// well
TEST_F(AuthSrvTest, TSIGSigned) {
    // Prepare key, the client message, etc
    const TSIGKey key("key:c2VjcmV0Cg==:hmac-sha1");
    TSIGContext context(key);
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("version.bind"), RRClass::CH(),
                                       RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP, &context);

    // Run the message through the server
    boost::shared_ptr<TSIGKeyRing> keyring(new TSIGKeyRing);
    keyring->add(key);
    server.setTSIGKeyRing(&keyring);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    // What did we get?
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 1, 0);
    // We need to parse the message ourself, or getTSIGRecord won't work
    InputBuffer ib(response_obuffer->getData(), response_obuffer->getLength());
    Message m(Message::PARSE);
    m.fromWire(ib);

    const TSIGRecord* tsig = m.getTSIGRecord();
    ASSERT_TRUE(tsig != NULL) << "Missing TSIG signature";
    TSIGError error(context.verify(tsig, response_obuffer->getData(),
                                   response_obuffer->getLength()));
    EXPECT_EQ(TSIGError::NOERROR(), error) <<
        "The server signed the response, but it doesn't seem to be valid";
}

// Give the server a signed request, but don't give it the key. It will
// not be able to verify it, returning BADKEY
TEST_F(AuthSrvTest, TSIGSignedBadKey) {
    TSIGKey key("key:c2VjcmV0Cg==:hmac-sha1");
    TSIGContext context(key);
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("version.bind"), RRClass::CH(),
                                       RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP, &context);

    // Process the message, but use a different key there
    boost::shared_ptr<TSIGKeyRing> keyring(new TSIGKeyRing);
    server.setTSIGKeyRing(&keyring);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, TSIGError::BAD_KEY().toRcode(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
    // We need to parse the message ourself, or getTSIGRecord won't work
    InputBuffer ib(response_obuffer->getData(), response_obuffer->getLength());
    Message m(Message::PARSE);
    m.fromWire(ib);

    const TSIGRecord* tsig = m.getTSIGRecord();
    ASSERT_TRUE(tsig != NULL) <<
        "Missing TSIG signature (we should have one even at error)";
    EXPECT_EQ(TSIGError::BAD_KEY_CODE, tsig->getRdata().getError());
    EXPECT_EQ(0, tsig->getRdata().getMACSize()) <<
        "It should be unsigned with this error";
}

// Give the server a signed request, but signed by a different key
// (with the same name). It should return BADSIG
TEST_F(AuthSrvTest, TSIGBadSig) {
    TSIGKey key("key:c2VjcmV0Cg==:hmac-sha1");
    TSIGContext context(key);
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("version.bind"), RRClass::CH(),
                                       RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP, &context);

    // Process the message, but use a different key there
    boost::shared_ptr<TSIGKeyRing> keyring(new TSIGKeyRing);
    keyring->add(TSIGKey("key:QkFECg==:hmac-sha1"));
    server.setTSIGKeyRing(&keyring);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, TSIGError::BAD_SIG().toRcode(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
    // We need to parse the message ourself, or getTSIGRecord won't work
    InputBuffer ib(response_obuffer->getData(), response_obuffer->getLength());
    Message m(Message::PARSE);
    m.fromWire(ib);

    const TSIGRecord* tsig = m.getTSIGRecord();
    ASSERT_TRUE(tsig != NULL) <<
        "Missing TSIG signature (we should have one even at error)";
    EXPECT_EQ(TSIGError::BAD_SIG_CODE, tsig->getRdata().getError());
    EXPECT_EQ(0, tsig->getRdata().getMACSize()) <<
        "It should be unsigned with this error";
}

// Give the server a signed unsupported request with a bad signature.
// This checks the server first verifies the signature before anything
// else.
TEST_F(AuthSrvTest, TSIGCheckFirst) {
    TSIGKey key("key:c2VjcmV0Cg==:hmac-sha1");
    TSIGContext context(key);
    // Pass a wrong opcode there. The server shouldn't know what to do
    // about it.
    UnitTestUtil::createRequestMessage(request_message, Opcode::RESERVED14(),
                                       default_qid, Name("version.bind"),
                                       RRClass::CH(), RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP, &context);

    // Process the message, but use a different key there
    boost::shared_ptr<TSIGKeyRing> keyring(new TSIGKeyRing);
    keyring->add(TSIGKey("key:QkFECg==:hmac-sha1"));
    server.setTSIGKeyRing(&keyring);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, TSIGError::BAD_SIG().toRcode(),
                Opcode::RESERVED14().getCode(), QR_FLAG, 0, 0, 0, 0);
    // We need to parse the message ourself, or getTSIGRecord won't work
    InputBuffer ib(response_obuffer->getData(), response_obuffer->getLength());
    Message m(Message::PARSE);
    m.fromWire(ib);

    const TSIGRecord* tsig = m.getTSIGRecord();
    ASSERT_TRUE(tsig != NULL) <<
        "Missing TSIG signature (we should have one even at error)";
    EXPECT_EQ(TSIGError::BAD_SIG_CODE, tsig->getRdata().getError());
    EXPECT_EQ(0, tsig->getRdata().getMACSize()) <<
        "It should be unsigned with this error";
    // TSIG should have failed, and so the per opcode counter shouldn't be
    // incremented.
    EXPECT_EQ(0, server.getCounter(Opcode::RESERVED14()));
}

TEST_F(AuthSrvTest, AXFRConnectFail) {
    EXPECT_FALSE(xfrout.isConnected()); // check prerequisite
    xfrout.disableConnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
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
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(xfrout.isConnected());

    xfrout.disableSend();
    parse_message->clear(Message::PARSE);
    response_obuffer->clear();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
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
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    EXPECT_THROW(server.processMessage(*io_message, parse_message,
                                       response_obuffer, &dnsserv),
                 XfroutError);
    EXPECT_TRUE(xfrout.isConnected());
    // XXX: we need to re-enable disconnect.  otherwise an exception would be
    // thrown via the destructor of the server.
    xfrout.enableDisconnect();
}

TEST_F(AuthSrvTest, IXFRConnectFail) {
    EXPECT_FALSE(xfrout.isConnected()); // check prerequisite
    xfrout.disableConnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
    EXPECT_FALSE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, IXFRSendFail) {
    // first send a valid query, making the connection with the xfr process
    // open.
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(xfrout.isConnected());

    xfrout.disableSend();
    parse_message->clear(Message::PARSE);
    response_obuffer->clear();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);

    // The connection should have been closed due to the send failure.
    EXPECT_FALSE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, IXFRDisconnectFail) {
    // In our usage disconnect() shouldn't fail.  So we'll see the exception
    // should it be thrown.
    xfrout.disableSend();
    xfrout.disableDisconnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::IXFR());
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
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
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
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::CH(), RRType::SOA());
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
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
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
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithoutAA) {
    // implicitly leave the AA bit off.  our implementation will accept it.
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                Opcode::NOTIFY().getCode(), QR_FLAG | AA_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithErrorRcode) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
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

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);

    // we simply ignore the notify and let it be resent if an internal error
    // happens.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifySendFail) {
    notify_session.disableSend();

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);

    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyReceiveFail) {
    notify_session.disableReceive();

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyWithBogusSessionMessage) {
    notify_session.setMessage(Element::fromJSON("{\"foo\": 1}"));

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyWithSessionMessageError) {
    notify_session.setMessage(
        Element::fromJSON("{\"result\": [1, \"FAIL\"]}"));

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
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

TEST_F(AuthSrvTest, updateWithInMemoryClient) {
    // Test configuring memory data source.  Detailed test cases are covered
    // in the configuration tests.  We only check the AuthSrv interface here.

    // By default memory data source isn't enabled
    EXPECT_EQ(AuthSrv::InMemoryClientPtr(), server.getInMemoryClient(rrclass));
    updateConfig(&server,
                 "{\"datasources\": [{\"type\": \"memory\"}]}", true);
    // after successful configuration, we should have one (with empty zoneset).
    ASSERT_NE(AuthSrv::InMemoryClientPtr(), server.getInMemoryClient(rrclass));
    EXPECT_EQ(0, server.getInMemoryClient(rrclass)->getZoneCount());

    // The memory data source is empty, should return REFUSED rcode.
    createDataFromFile("examplequery_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::REFUSED(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, chQueryWithInMemoryClient) {
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
    EXPECT_EQ(0, server.getCounter(AuthCounters::SERVER_UDP_QUERY));
    // Create UDP message and process.
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    // After processing UDP query, the counter should be 1.
    EXPECT_EQ(1, server.getCounter(AuthCounters::SERVER_UDP_QUERY));
}

// Submit TCP normal query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPNormal) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, server.getCounter(AuthCounters::SERVER_TCP_QUERY));
    // Create TCP message and process.
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);
    // After processing TCP query, the counter should be 1.
    EXPECT_EQ(1, server.getCounter(AuthCounters::SERVER_TCP_QUERY));
}

// Submit TCP AXFR query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPAXFR) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, server.getCounter(AuthCounters::SERVER_TCP_QUERY));
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // On success, the AXFR query has been passed to a separate process,
    // so auth itself shouldn't respond.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    // After processing TCP AXFR query, the counter should be 1.
    EXPECT_EQ(1, server.getCounter(AuthCounters::SERVER_TCP_QUERY));
}

// Submit TCP IXFR query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPIXFR) {
    // The counter should be initialized to 0.
    EXPECT_EQ(0, server.getCounter(AuthCounters::SERVER_TCP_QUERY));
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // On success, the IXFR query has been passed to a separate process,
    // so auth itself shouldn't respond.
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    // After processing TCP IXFR query, the counter should be 1.
    EXPECT_EQ(1, server.getCounter(AuthCounters::SERVER_TCP_QUERY));
}

TEST_F(AuthSrvTest, queryCounterOpcodes) {
    for (int i = 0; i < 16; ++i) {
        // The counter should be initialized to 0.
        EXPECT_EQ(0, server.getCounter(Opcode(i)));

        // For each possible opcode, create a request message and send it
        UnitTestUtil::createRequestMessage(request_message, Opcode(i),
                                           default_qid, Name("example.com"),
                                           RRClass::IN(), RRType::NS());
        createRequestPacket(request_message, IPPROTO_UDP);

        // "send" the request N-th times where N is i + 1 for i-th code.
        // we intentionally use different values for each code
        for (int j = 0; j <= i; ++j) {
            parse_message->clear(Message::PARSE);
            server.processMessage(*io_message, parse_message, response_obuffer,
                                  &dnsserv);
        }

        // Confirm the counter.
        EXPECT_EQ(i + 1, server.getCounter(Opcode(i)));
    }
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
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 53210);
    io_message = new IOMessage(request_renderer.getData(),
                               request_renderer.getLength(),
                               getDummyUnknownSocket(), *endpoint);

    EXPECT_THROW(server.processMessage(*io_message, parse_message,
                                       response_obuffer, &dnsserv),
                 isc::Unexpected);
}

TEST_F(AuthSrvTest, stop) {
    // normal case is covered in command_unittest.cc.  we should primarily
    // test it here, but the current design of the stop test takes time,
    // so we consolidate the cases in the command tests.
    // If/when the interval timer has finer granularity we'll probably add
    // our own tests here, so we keep this empty test case.
}

TEST_F(AuthSrvTest, listenAddresses) {
    isc::testutils::portconfig::listenAddresses(server);
    // Check it requests the correct addresses
    const char* tokens[] = {
        "TCP:127.0.0.1:53210:1",
        "UDP:127.0.0.1:53210:2",
        "TCP:::1:53210:3",
        "UDP:::1:53210:4",
        NULL
    };
    sock_requestor_.checkTokens(tokens, sock_requestor_.given_tokens_,
                                "Given tokens");
    // It returns back to empty set of addresses afterwards, so
    // they should be released
    sock_requestor_.checkTokens(tokens, sock_requestor_.released_tokens_,
                                "Released tokens");
}

}
