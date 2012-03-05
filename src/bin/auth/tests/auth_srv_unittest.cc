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

// This is a configuration that uses the in-memory data source containing
// a signed example zone.
const char* const CONFIG_INMEMORY_EXAMPLE =
    "{\"datasources\": [{\"type\": \"memory\","
    "\"zones\": [{\"origin\": \"example\","
    "\"file\": \"" TEST_DATA_DIR "/rfc5155-example.zone.signed\"}]}]}";

class AuthSrvTest : public SrvTestBase {
protected:
    AuthSrvTest() :
        dnss_(ios_, NULL, NULL, NULL),
        server(true, xfrout),
        rrclass(RRClass::IN()),
        // The empty string is expected value of the parameter of
        // requestSocket, not the app_name (there's no fallback, it checks
        // the empty string is passed).
        sock_requestor_(dnss_, address_store_, 53210, "")
    {
        server.setDNSService(dnss_);
        server.setXfrinSession(&notify_session);
        server.setStatisticsSession(&statistics_session);
    }

    virtual void processMessage() {
        // If processMessage has been called before, parse_message needs
        // to be reset. If it hasn't, there's no harm in doing so
        parse_message->clear(Message::PARSE);
        server.processMessage(*io_message, parse_message, response_obuffer,
                              &dnsserv);
    }

    // Helper for checking Rcode statistic counters;
    // Checks for one specific Rcode statistics counter value
    void checkRcodeCounter(const Rcode& rcode, int expected_value) const {
        EXPECT_EQ(expected_value, server.getCounter(rcode)) <<
                  "Expected Rcode count for " << rcode.toText() <<
                  " " << expected_value << ", was: " <<
                  server.getCounter(rcode);
    }

    // Checks whether all Rcode counters are set to zero
    void checkAllRcodeCountersZero() const {
        for (int i = 0; i < 17; i++) {
            checkRcodeCounter(Rcode(i), 0);
        }
    }

    // Checks whether all Rcode counters are set to zero except the given
    // rcode (it is checked to be set to 'value')
    void checkAllRcodeCountersZeroExcept(const Rcode& rcode, int value) const {
        for (int i = 0; i < 17; i++) {
            const Rcode rc(i);
            if (rc == rcode) {
                checkRcodeCounter(Rcode(i), value);
            } else {
                checkRcodeCounter(Rcode(i), 0);
            }
        }
    }

    // Convenience method for tests that expect to return SERVFAIL
    // It calls processMessage, checks if there is an answer, and
    // check the header for default SERVFAIL data
    void processAndCheckSERVFAIL() {
        processMessage();
        EXPECT_TRUE(dnsserv.hasAnswer());
        headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                    opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
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

    MessageRenderer renderer;
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
    checkAllRcodeCountersZeroExcept(Rcode::NOERROR(), 1);
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
    // unsupportedRequest tries 14 different opcodes
    checkAllRcodeCountersZeroExcept(Rcode::NOTIMP(), 14);
}

// Multiple questions.  Should result in FORMERR.
TEST_F(AuthSrvTest, multiQuestion) {
    multiQuestion();
    checkAllRcodeCountersZeroExcept(Rcode::FORMERR(), 1);
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
TEST_F(AuthSrvTest, shortMessage) {
    shortMessage();
    checkAllRcodeCountersZero();
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(AuthSrvTest, response) {
    response();
    checkAllRcodeCountersZero();
}

// Query with a broken question
TEST_F(AuthSrvTest, shortQuestion) {
    shortQuestion();
    checkAllRcodeCountersZeroExcept(Rcode::FORMERR(), 1);
}

// Query with a broken answer section
TEST_F(AuthSrvTest, shortAnswer) {
    shortAnswer();
    checkAllRcodeCountersZeroExcept(Rcode::FORMERR(), 1);
}

// Query with unsupported version of EDNS.
TEST_F(AuthSrvTest, ednsBadVers) {
    ednsBadVers();
    checkAllRcodeCountersZeroExcept(Rcode::BADVERS(), 1);
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
    checkAllRcodeCountersZero();
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

    checkAllRcodeCountersZeroExcept(Rcode::NOERROR(), 1);
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

    checkAllRcodeCountersZeroExcept(Rcode::NOTAUTH(), 1);
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

    checkAllRcodeCountersZeroExcept(Rcode::NOTAUTH(), 1);
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

    checkAllRcodeCountersZeroExcept(Rcode::NOTAUTH(), 1);
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
    // In our usage disconnect() shouldn't fail. But even if it does,
    // it should not disrupt service (so processMessage should have caught it)
    xfrout.disableSend();
    xfrout.disableDisconnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    EXPECT_NO_THROW(server.processMessage(*io_message, parse_message,
                                          response_obuffer, &dnsserv));
    // Since the disconnect failed, we should still be 'connected'
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
    // In our usage disconnect() shouldn't fail, but even if it does,
    // procesMessage() should catch it.
    xfrout.disableSend();
    xfrout.disableDisconnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    EXPECT_NO_THROW(server.processMessage(*io_message, parse_message,
                                          response_obuffer, &dnsserv));
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

    checkAllRcodeCountersZeroExcept(Rcode::NOERROR(), 1);
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
    EXPECT_EQ(expect_success ? 0 : 1, result->get(0)->intValue()) <<
        "Bad result from updateConfig: " << result->str();
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

TEST_F(AuthSrvTest, queryWithInMemoryClientNoDNSSEC) {
    // In this example, we do simple check that query is handled from the
    // query handler class, and confirm it returns no error and a non empty
    // answer section.  Detailed examination on the response content
    // for various types of queries are tested in the query tests.
    updateConfig(&server, CONFIG_INMEMORY_EXAMPLE, true);
    ASSERT_NE(AuthSrv::InMemoryClientPtr(), server.getInMemoryClient(rrclass));
    EXPECT_EQ(1, server.getInMemoryClient(rrclass)->getZoneCount());

    createDataFromFile("nsec3query_nodnssec_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 2, 1);
}

TEST_F(AuthSrvTest, queryWithInMemoryClientDNSSEC) {
    // Similar to the previous test, but the query has the DO bit on.
    // The response should contain RRSIGs, and should have more RRs than
    // the previous case.
    updateConfig(&server, CONFIG_INMEMORY_EXAMPLE, true);
    ASSERT_NE(AuthSrv::InMemoryClientPtr(), server.getInMemoryClient(rrclass));
    EXPECT_EQ(1, server.getInMemoryClient(rrclass)->getZoneCount());

    createDataFromFile("nsec3query_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 2, 3, 3);
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
    // The counter for opcode Query should also be one
    EXPECT_EQ(1, server.getCounter(Opcode::QUERY()));
    // The counter for REFUSED responses should also be one, the rest zero
    checkAllRcodeCountersZeroExcept(Rcode::REFUSED(), 1);
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
    // The counter for SUCCESS responses should also be one
    EXPECT_EQ(1, server.getCounter(Opcode::QUERY()));
    // The counter for REFUSED responses should also be one, the rest zero
    checkAllRcodeCountersZeroExcept(Rcode::REFUSED(), 1);
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
    // No rcodes should be incremented
    checkAllRcodeCountersZero();
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

// Submit unexpected type of query and check it is ignored
TEST_F(AuthSrvTest, queryCounterUnexpected) {
    // This code isn't exception safe, but we'd rather keep the code
    // simpler and more readable as this is only for tests

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

    EXPECT_FALSE(dnsserv.hasAnswer());
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

//
// Tests for catching exceptions in various stages of the query processing
//
// These tests work by defining two proxy classes, that act as an in-memory
// client by default, but can throw exceptions at various points.
//
namespace {

/// A the possible methods to throw in, either in FakeInMemoryClient or
/// FakeZoneFinder
enum ThrowWhen {
    THROW_NEVER,
    THROW_AT_FIND_ZONE,
    THROW_AT_GET_ORIGIN,
    THROW_AT_GET_CLASS,
    THROW_AT_FIND,
    THROW_AT_FIND_ALL,
    THROW_AT_FIND_NSEC3
};

/// convenience function to check whether and what to throw
void
checkThrow(ThrowWhen method, ThrowWhen throw_at, bool isc_exception) {
    if (method == throw_at) {
        if (isc_exception) {
            isc_throw(isc::Exception, "foo");
        } else {
            throw std::exception();
        }
    }
}

/// \brief proxy class for the ZoneFinder returned by the InMemoryClient
///        proxied by FakeInMemoryClient
///
/// See the documentation for FakeInMemoryClient for more information,
/// all methods simply check whether they should throw, and if not, call
/// their proxied equivalent.
class FakeZoneFinder : public isc::datasrc::ZoneFinder {
public:
    FakeZoneFinder(isc::datasrc::ZoneFinderPtr zone_finder,
                   ThrowWhen throw_when,
                   bool isc_exception) :
        real_zone_finder_(zone_finder),
        throw_when_(throw_when),
        isc_exception_(isc_exception)
    {}

    virtual isc::dns::Name
    getOrigin() const {
        checkThrow(THROW_AT_GET_ORIGIN, throw_when_, isc_exception_);
        return (real_zone_finder_->getOrigin());
    }

    virtual isc::dns::RRClass
    getClass() const {
        checkThrow(THROW_AT_GET_CLASS, throw_when_, isc_exception_);
        return (real_zone_finder_->getClass());
    }

    virtual isc::datasrc::ZoneFinder::FindResult
    find(const isc::dns::Name& name,
         const isc::dns::RRType& type,
         isc::datasrc::ZoneFinder::FindOptions options)
    {
        checkThrow(THROW_AT_FIND, throw_when_, isc_exception_);
        return (real_zone_finder_->find(name, type, options));
    }

    virtual FindResult
    findAll(const isc::dns::Name& name,
            std::vector<isc::dns::ConstRRsetPtr> &target,
            const FindOptions options = FIND_DEFAULT)
    {
        checkThrow(THROW_AT_FIND_ALL, throw_when_, isc_exception_);
        return (real_zone_finder_->findAll(name, target, options));
    };

    virtual FindNSEC3Result
    findNSEC3(const isc::dns::Name& name, bool recursive) {
        checkThrow(THROW_AT_FIND_NSEC3, throw_when_, isc_exception_);
        return (real_zone_finder_->findNSEC3(name, recursive));
    };

    virtual isc::dns::Name
    findPreviousName(const isc::dns::Name& query) const {
        return (real_zone_finder_->findPreviousName(query));
    }

private:
    isc::datasrc::ZoneFinderPtr real_zone_finder_;
    ThrowWhen throw_when_;
    bool isc_exception_;
};

/// \brief Proxy InMemoryClient that can throw exceptions at specified times
///
/// It is based on the memory client since that one is easy to override
/// (with setInMemoryClient) with the current design of AuthSrv.
class FakeInMemoryClient : public isc::datasrc::InMemoryClient {
public:
    /// \brief Create a proxy memory client
    ///
    /// \param real_client The real in-memory client to proxy
    /// \param throw_when if set to any value other than never, that is
    ///        the method that will throw an exception (either in this
    ///        class or the related FakeZoneFinder)
    /// \param isc_exception if true, throw isc::Exception, otherwise,
    ///                      throw std::exception
    FakeInMemoryClient(AuthSrv::InMemoryClientPtr real_client,
                       ThrowWhen throw_when,
                       bool isc_exception) :
        real_client_(real_client),
        throw_when_(throw_when),
        isc_exception_(isc_exception)
    {}

    /// \brief proxy call for findZone
    ///
    /// if this instance was constructed with throw_when set to find_zone,
    /// this method will throw. Otherwise, it will return a FakeZoneFinder
    /// instance which will throw at the method specified at the
    /// construction of this instance.
    virtual FindResult
    findZone(const isc::dns::Name& name) const {
        checkThrow(THROW_AT_FIND_ZONE, throw_when_, isc_exception_);
        const FindResult result = real_client_->findZone(name);
        return (FindResult(result.code, isc::datasrc::ZoneFinderPtr(
                                        new FakeZoneFinder(result.zone_finder,
                                        throw_when_,
                                        isc_exception_))));
    }

private:
    AuthSrv::InMemoryClientPtr real_client_;
    ThrowWhen throw_when_;
    bool isc_exception_;
};

} // end anonymous namespace for throwing proxy classes

// Test for the tests
//
// Set the proxies to never throw, this should have the same result as
// queryWithInMemoryClientNoDNSSEC, and serves to test the two proxy classes
TEST_F(AuthSrvTest, queryWithInMemoryClientProxy) {
    // Set real inmem client to proxy
    updateConfig(&server, CONFIG_INMEMORY_EXAMPLE, true);

    AuthSrv::InMemoryClientPtr fake_client(
        new FakeInMemoryClient(server.getInMemoryClient(rrclass),
                               THROW_NEVER,
                               false));

    ASSERT_NE(AuthSrv::InMemoryClientPtr(), server.getInMemoryClient(rrclass));
    server.setInMemoryClient(rrclass, fake_client);

    createDataFromFile("nsec3query_nodnssec_fromWire.wire");
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 2, 1);
}

// Convenience function for the rest of the tests, set up a proxy
// to throw in the given method
// If isc_exception is true, it will throw isc::Exception, otherwise
// it will throw std::exception
void
setupThrow(AuthSrv* server, const char *config, ThrowWhen throw_when,
                   bool isc_exception)
{
    // Set real inmem client to proxy
    updateConfig(server, config, true);

    // Set it to throw on findZone(), this should result in
    // SERVFAIL on any exception
    AuthSrv::InMemoryClientPtr fake_client(
        new FakeInMemoryClient(
            server->getInMemoryClient(isc::dns::RRClass::IN()),
            throw_when,
            isc_exception));

    ASSERT_NE(AuthSrv::InMemoryClientPtr(),
              server->getInMemoryClient(isc::dns::RRClass::IN()));
    server->setInMemoryClient(isc::dns::RRClass::IN(), fake_client);
}

TEST_F(AuthSrvTest, queryWithThrowingProxyServfails) {
    // Test the common cases, all of which should simply return SERVFAIL
    // Use THROW_NEVER as end marker
    ThrowWhen throws[] = { THROW_AT_FIND_ZONE,
                           THROW_AT_GET_ORIGIN,
                           THROW_AT_FIND,
                           THROW_AT_FIND_NSEC3,
                           THROW_NEVER };
    UnitTestUtil::createDNSSECRequestMessage(request_message, opcode,
                                             default_qid, Name("foo.example."),
                                             RRClass::IN(), RRType::TXT());
    for (ThrowWhen* when(throws); *when != THROW_NEVER; ++when) {
        createRequestPacket(request_message, IPPROTO_UDP);
        setupThrow(&server, CONFIG_INMEMORY_EXAMPLE, *when, true);
        processAndCheckSERVFAIL();
        // To be sure, check same for non-isc-exceptions
        createRequestPacket(request_message, IPPROTO_UDP);
        setupThrow(&server, CONFIG_INMEMORY_EXAMPLE, *when, false);
        processAndCheckSERVFAIL();
    }
}

// Throw isc::Exception in getClass(). (Currently?) getClass is not called
// in the processMessage path, so this should result in a normal answer
TEST_F(AuthSrvTest, queryWithInMemoryClientProxyGetClass) {
    createDataFromFile("nsec3query_nodnssec_fromWire.wire");
    setupThrow(&server, CONFIG_INMEMORY_EXAMPLE, THROW_AT_GET_CLASS, true);

    // getClass is not called so it should just answer
    server.processMessage(*io_message, parse_message, response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 2, 1);
}

}
