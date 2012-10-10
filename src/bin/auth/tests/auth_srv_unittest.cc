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

#include <util/io/sockaddr_util.h>
#include <util/memory_segment_local.h>

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
#include <datasrc/client_list.h>
#include <auth/auth_srv.h>
#include <auth/command.h>
#include <auth/common.h>
#include <auth/statistics.h>
#include <auth/statistics_items.h>
#include <auth/datasrc_configurator.h>

#include <util/unittests/mock_socketsession.h>
#include <dns/tests/unittest_util.h>
#include <testutils/dnsmessage_test.h>
#include <testutils/srv_test.h>
#include <testutils/mockups.h>
#include <testutils/portconfig.h>
#include <testutils/socket_request.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>

#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::io::internal;
using namespace isc::util::unittests;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::xfr;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::testutils;
using namespace isc::server_common::portconfig;
using isc::UnitTestUtil;
using boost::scoped_ptr;
using isc::auth::statistics::Counters;

namespace {
const char* const CONFIG_TESTDB =
    "{\"database_file\": \"" TEST_DATA_DIR "/example.sqlite3\"}";
// The following file must be non existent and must be non"creatable" (see
// the sqlite3 test).
const char* const BADCONFIG_TESTDB =
    "{ \"database_file\": \"" TEST_DATA_DIR "/nodir/notexist\"}";

const char* const STATIC_DSRC_FILE = DSRC_DIR "/static.zone";

// This is a configuration that uses the in-memory data source containing
// a signed example zone.
const char* const CONFIG_INMEMORY_EXAMPLE = TEST_DATA_DIR "/rfc5155-example.zone.signed";

class AuthSrvTest : public SrvTestBase {
protected:
    AuthSrvTest() :
        dnss_(),
        server(xfrout, ddns_forwarder),
        // The empty string is expected value of the parameter of
        // requestSocket, not the app_name (there's no fallback, it checks
        // the empty string is passed).
        sock_requestor_(dnss_, address_store_, 53210, "")
    {
        server.setDNSService(dnss_);
        server.setXfrinSession(&notify_session);
        server.createDDNSForwarder();
    }

    ~AuthSrvTest() {
        server.destroyDDNSForwarder();
    }

    virtual void processMessage() {
        // If processMessage has been called before, parse_message needs
        // to be reset. If it hasn't, there's no harm in doing so
        parse_message->clear(Message::PARSE);
        server.processMessage(*io_message, *parse_message, *response_obuffer,
                              &dnsserv);
    }

    // Helper for checking Rcode statistic counters;
    // Checks for one specific Rcode statistics counter value
    void checkRcodeCounter(const std::string& rcode_name, const int rcode_value,
                           const int expected_value) const
    {
            EXPECT_EQ(expected_value, rcode_value) <<
                      "Expected Rcode count for " << rcode_name <<
                      " " << expected_value << ", was: " <<
                      rcode_value;
    }

    // Checks whether all Rcode counters are set to zero
    void checkAllRcodeCountersZero() const {
        const std::map<std::string, ConstElementPtr>
            stats_map(server.getStatistics()->mapValue());

        const std::string rcode_prefix("rcode.");
        for (std::map<std::string, ConstElementPtr>::const_iterator
                 i = stats_map.begin(), e = stats_map.end();
             i != e;
             ++i)
        {
            if (i->first.compare(0, rcode_prefix.size(), rcode_prefix) == 0) {
                checkRcodeCounter(i->first, i->second->intValue(), 0);
            }
        }
    }

    // Checks whether all Rcode counters are set to zero except the given
    // rcode (it is checked to be set to 'value')
    void checkAllRcodeCountersZeroExcept(const Rcode& rcode, int value) const {
        std::string target_rcode_name = rcode.toText();
        std::transform(target_rcode_name.begin(), target_rcode_name.end(),
                       target_rcode_name.begin(), ::tolower);
        // rcode 16 is registered as both BADVERS and BADSIG
        if (target_rcode_name == "badvers") {
            target_rcode_name = "badsigvers";
        }

        const std::map<std::string, ConstElementPtr>
            stats_map(server.getStatistics()->mapValue());

        const std::string rcode_prefix("rcode.");
        for (std::map<std::string, ConstElementPtr>::const_iterator
                 i = stats_map.begin(), e = stats_map.end();
             i != e;
             ++i)
        {
            if (i->first.compare(0, rcode_prefix.size(), rcode_prefix) == 0) {
                if (i->first.compare(rcode_prefix + target_rcode_name) == 0) {
                    checkRcodeCounter(i->first, i->second->intValue(), value);
                } else {
                    checkRcodeCounter(i->first, i->second->intValue(), 0);
                }
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

    // Convenient shortcut of creating a simple request and having the
    // server process it.
    void createAndSendRequest(RRType req_type, Opcode opcode = Opcode::QUERY(),
                              const Name& req_name = Name("example.com"),
                              RRClass req_class = RRClass::IN(),
                              int protocol = IPPROTO_UDP,
                              const char* const remote_address =
                              DEFAULT_REMOTE_ADDRESS,
                              uint16_t remote_port = DEFAULT_REMOTE_PORT)
    {
        UnitTestUtil::createRequestMessage(request_message, opcode,
                                           default_qid, req_name,
                                           req_class, req_type);
        createRequestPacket(request_message, protocol, NULL,
                            remote_address, remote_port);
        parse_message->clear(Message::PARSE);
        server.processMessage(*io_message, *parse_message, *response_obuffer,
                              &dnsserv);
    }

    MockDNSService dnss_;
    MockXfroutClient xfrout;
    MockSocketSessionForwarder ddns_forwarder;
    AuthSrv server;
    vector<uint8_t> response_data;
    AddressList address_store_;
    TestSocketRequestor sock_requestor_;
};

// A helper function that builds a response to version.bind/TXT/CH that
// should be identical to the response from our builtin (static) data source
// by default.  The resulting wire-format data will be stored in 'data'.
void
createBuiltinVersionResponse(const qid_t qid, vector<uint8_t>& data) {
    const Name version_name("VERSION.BIND.");
    const Name apex_name("BIND.");
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

    RRsetPtr rrset_version_ns = RRsetPtr(new RRset(apex_name, RRClass::CH(),
                                                   RRType::NS(), RRTTL(0)));
    rrset_version_ns->addRdata(generic::NS(apex_name));
    message.addRRset(Message::SECTION_AUTHORITY, rrset_version_ns);

    MessageRenderer renderer;
    message.toWire(renderer);

    data.clear();
    data.assign(static_cast<const uint8_t*>(renderer.getData()),
                static_cast<const uint8_t*>(renderer.getData()) +
                renderer.getLength());
}

void
expectCounterItem(ConstElementPtr stats,
                  const std::string& item, const int expected) {
    ConstElementPtr value(Element::create(0));
    if (item == "queries.udp" || item == "queries.tcp" || expected != 0) {
        ASSERT_TRUE(stats->find(item, value)) << "    Item: " << item;
        value = stats->find(item);
        EXPECT_EQ(expected, value->intValue()) << "    Item: " << item;
    } else {
        ASSERT_FALSE(stats->find(item, value)) << "    Item: " << item <<
            std::endl << "   Value: " << value->intValue();
    }
}

// We did not configure any client lists. Therefore it should be REFUSED
TEST_F(AuthSrvTest, noClientList) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("version.bind"),
                                       RRClass::CH(), RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::REFUSED(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}

// Unsupported requests.  Should result in NOTIMP.
TEST_F(AuthSrvTest, unsupportedRequest) {
    unsupportedRequest();
    // unsupportedRequest tries 13 different opcodes
    checkAllRcodeCountersZeroExcept(Rcode::NOTIMP(), 13);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(xfrout.isConnected());
    checkAllRcodeCountersZero();
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
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
    ConstElementPtr stats = server.getStatistics();
    expectCounterItem(stats, "opcode.normal", 0);
    expectCounterItem(stats, "opcode.other", 0);

    checkAllRcodeCountersZeroExcept(Rcode::NOTAUTH(), 1);
}

TEST_F(AuthSrvTest, AXFRConnectFail) {
    EXPECT_FALSE(xfrout.isConnected()); // check prerequisite
    xfrout.disableConnect();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(xfrout.isConnected());

    xfrout.disableSend();
    parse_message->clear(Message::PARSE);
    response_obuffer->clear();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    EXPECT_NO_THROW(server.processMessage(*io_message, *parse_message,
                                          *response_obuffer, &dnsserv));
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(xfrout.isConnected());

    xfrout.disableSend();
    parse_message->clear(Message::PARSE);
    response_obuffer->clear();
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    EXPECT_NO_THROW(server.processMessage(*io_message, *parse_message,
                                          *response_obuffer, &dnsserv));
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifySendFail) {
    notify_session.disableSend();

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);

    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyReceiveFail) {
    notify_session.disableReceive();

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

TEST_F(AuthSrvTest, notifyWithBogusSessionMessage) {
    notify_session.setMessage(Element::fromJSON("{\"foo\": 1}"));

    UnitTestUtil::createRequestMessage(request_message, Opcode::NOTIFY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
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
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}

void
updateDatabase(AuthSrv* server, const char* params) {
    const ConstElementPtr config(Element::fromJSON("{"
        "\"IN\": [{"
        "    \"type\": \"sqlite3\","
        "    \"params\": " + string(params) +
        "}]}"));
    DataSourceConfigurator::testReconfigure(server, config);
}

void
updateInMemory(AuthSrv* server, const char* origin, const char* filename) {
    const ConstElementPtr config(Element::fromJSON("{"
        "\"IN\": [{"
        "   \"type\": \"MasterFiles\","
        "   \"params\": {"
        "       \"" + string(origin) + "\": \"" + string(filename) + "\""
        "   },"
        "   \"cache-enable\": true"
        "}],"
        "\"CH\": [{"
        "   \"type\": \"static\","
        "   \"params\": \"" + string(STATIC_DSRC_FILE) + "\""
        "}]}"));
    DataSourceConfigurator::testReconfigure(server, config);
}

void
updateBuiltin(AuthSrv* server) {
    const ConstElementPtr config(Element::fromJSON("{"
        "\"CH\": [{"
        "   \"type\": \"static\","
        "   \"params\": \"" + string(STATIC_DSRC_FILE) + "\""
        "}]}"));
    DataSourceConfigurator::testReconfigure(server, config);
}

// Try giving the server a TSIG signed request and see it can anwer signed as
// well
#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_TSIGSigned) { // Needs builtin
#else
TEST_F(AuthSrvTest, TSIGSigned) {
#endif
    // Prepare key, the client message, etc
    updateBuiltin(&server);
    const TSIGKey key("key:c2VjcmV0Cg==:hmac-sha1");
    TSIGContext context(key);
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("VERSION.BIND."), RRClass::CH(),
                                       RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP, &context);

    // Run the message through the server
    boost::shared_ptr<TSIGKeyRing> keyring(new TSIGKeyRing);
    keyring->add(key);
    server.setTSIGKeyRing(&keyring);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
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

// Same test emulating the UDPServer class behavior (defined in libasiolink).
// This is not a good test in that it assumes internal implementation details
// of UDPServer, but we've encountered a regression due to the introduction
// of that class, so we add a test for that case to prevent such a regression
// in future.
// Besides, the generalization of UDPServer is probably too much for the
// authoritative only server in terms of performance, and it's quite likely
// we need to drop it for the authoritative server implementation.
// At that point we can drop this test, too.
#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_builtInQueryViaDNSServer) {
#else
TEST_F(AuthSrvTest, builtInQueryViaDNSServer) {
#endif
    updateBuiltin(&server);
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("VERSION.BIND."),
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

    // After it has been run, the message should be cleared
    EXPECT_EQ(0, parse_message->getRRCount(Message::SECTION_QUESTION));
}

// In the following tests we confirm the response data is rendered in
// wire format in the expected way.

// The most primitive check: checking the result of the processMessage()
// method
#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_builtInQuery) {
#else
TEST_F(AuthSrvTest, builtInQuery) {
#endif
    updateBuiltin(&server);
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("VERSION.BIND."),
                                       RRClass::CH(), RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    createBuiltinVersionResponse(default_qid, response_data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        response_obuffer->getData(),
                        response_obuffer->getLength(),
                        &response_data[0], response_data.size());
    checkAllRcodeCountersZeroExcept(Rcode::NOERROR(), 1);
}

// Same type of test as builtInQueryViaDNSServer but for an error response.
#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_iqueryViaDNSServer) { // Needs builtin
#else
TEST_F(AuthSrvTest, iqueryViaDNSServer) { // Needs builtin
#endif
    updateBuiltin(&server);
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

// Install a Sqlite3 data source with testing data.
#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_updateConfig) {
#else
TEST_F(AuthSrvTest, updateConfig) {
#endif
    updateDatabase(&server, CONFIG_TESTDB);

    // query for existent data in the installed data source.  The resulting
    // response should have the AA flag on, and have an RR in each answer
    // and authority section.
    createDataFromFile("examplequery_fromWire.wire");
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(), opcode.getCode(),
                QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}

#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_datasourceFail) {
#else
TEST_F(AuthSrvTest, datasourceFail) {
#endif
    updateDatabase(&server, CONFIG_TESTDB);

    // This query will hit a corrupted entry of the data source (the zoneload
    // tool and the data source itself naively accept it).  This will result
    // in a SERVFAIL response, and the answer and authority sections should
    // be empty.
    createDataFromFile("badExampleQuery_fromWire.wire");
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}

#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_updateConfigFail) {
#else
TEST_F(AuthSrvTest, updateConfigFail) {
#endif
    // First, load a valid data source.
    updateDatabase(&server, CONFIG_TESTDB);

    // Next, try to update it with a non-existent one.  This should fail.
    EXPECT_THROW(updateDatabase(&server, BADCONFIG_TESTDB),
                 isc::datasrc::DataSourceError);

    // The original data source should still exist.
    createDataFromFile("examplequery_fromWire.wire");
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}

TEST_F(AuthSrvTest, updateWithInMemoryClient) {
    // Test configuring memory data source.  Detailed test cases are covered
    // in the configuration tests.  We only check the AuthSrv interface here.

    // Create an empty in-memory
    const ConstElementPtr config(Element::fromJSON("{"
        "\"IN\": [{"
        "   \"type\": \"MasterFiles\","
        "   \"params\": {},"
        "   \"cache-enable\": true"
        "}]}"));
    DataSourceConfigurator::testReconfigure(&server, config);
    // after successful configuration, we should have one (with empty zoneset).

    // The memory data source is empty, should return REFUSED rcode.
    createDataFromFile("examplequery_fromWire.wire");
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::REFUSED(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}

#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_queryWithInMemoryClientNoDNSSEC) {
#else
TEST_F(AuthSrvTest, queryWithInMemoryClientNoDNSSEC) {
#endif
    // In this example, we do simple check that query is handled from the
    // query handler class, and confirm it returns no error and a non empty
    // answer section.  Detailed examination on the response content
    // for various types of queries are tested in the query tests.
    updateInMemory(&server, "example.", CONFIG_INMEMORY_EXAMPLE);

    createDataFromFile("nsec3query_nodnssec_fromWire.wire");
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 2, 1);
}

#ifdef USE_STATIC_LINK
TEST_F(AuthSrvTest, DISABLED_queryWithInMemoryClientDNSSEC) {
#else
TEST_F(AuthSrvTest, queryWithInMemoryClientDNSSEC) {
#endif
    // Similar to the previous test, but the query has the DO bit on.
    // The response should contain RRSIGs, and should have more RRs than
    // the previous case.
    updateInMemory(&server, "example.", CONFIG_INMEMORY_EXAMPLE);

    createDataFromFile("nsec3query_fromWire.wire");
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 2, 3, 3);
}

TEST_F(AuthSrvTest,
#ifdef USE_STATIC_LINK
       DISABLED_chQueryWithInMemoryClient
#else
       chQueryWithInMemoryClient
#endif
    )
{
    // Set up the in-memory
    updateInMemory(&server, "example.", CONFIG_INMEMORY_EXAMPLE);

    // This shouldn't affect the result of class CH query
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("VERSION.BIND."),
                                       RRClass::CH(), RRType::TXT());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 1, 0);
}

// Submit UDP normal query and check query counter
TEST_F(AuthSrvTest, queryCounterUDPNormal) {
    // The counters should be initialized to 0.
    ConstElementPtr stats_init = server.getStatistics();
    expectCounterItem(stats_init, "queries.udp", 0);
    expectCounterItem(stats_init, "queries.tcp", 0);
    expectCounterItem(stats_init, "opcode.query", 0);
    expectCounterItem(stats_init, "rcode.refused", 0);
    // Create UDP message and process.
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    // After processing the UDP query, these counters should be incremented:
    //   request.udp, opcode.query, qtype.ns, rcode.refused, response
    // and these counters should not be incremented:
    //   request.tcp
    ConstElementPtr stats_after = server.getStatistics();
    expectCounterItem(stats_after, "queries.udp", 1);
    expectCounterItem(stats_after, "queries.tcp", 0);
    expectCounterItem(stats_after, "opcode.query", 1);
    expectCounterItem(stats_after, "rcode.refused", 1);
}

// Submit TCP normal query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPNormal) {
    // The counters should be initialized to 0.
    ConstElementPtr stats_init = server.getStatistics();
    expectCounterItem(stats_init, "queries.udp", 0);
    expectCounterItem(stats_init, "queries.tcp", 0);
    expectCounterItem(stats_init, "opcode.query", 0);
    expectCounterItem(stats_init, "rcode.refused", 0);
    // Create TCP message and process.
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());
    createRequestPacket(request_message, IPPROTO_TCP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    // After processing the TCP query, these counters should be incremented:
    //   request.tcp, opcode.query, qtype.ns, rcode.refused, response
    // and these counters should not be incremented:
    //   request.udp
    ConstElementPtr stats_after = server.getStatistics();
    expectCounterItem(stats_after, "queries.udp", 0);
    expectCounterItem(stats_after, "queries.tcp", 1);
    expectCounterItem(stats_after, "opcode.query", 1);
    expectCounterItem(stats_after, "rcode.refused", 1);
}

// Submit TCP AXFR query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPAXFR) {
    // The counters should be initialized to 0.
    ConstElementPtr stats_init = server.getStatistics();
    expectCounterItem(stats_init, "queries.udp", 0);
    expectCounterItem(stats_init, "queries.tcp", 0);
    expectCounterItem(stats_init, "opcode.query", 0);
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // On success, the AXFR query has been passed to a separate process,
    // so auth itself shouldn't respond.
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    // After processing the TCP AXFR query, these counters should be
    // incremented:
    //   request.tcp, opcode.query, qtype.axfr
    // and these counters should not be incremented:
    //   request.udp, response
    ConstElementPtr stats_after = server.getStatistics();
    expectCounterItem(stats_after, "queries.udp", 0);
    expectCounterItem(stats_after, "queries.tcp", 1);
    expectCounterItem(stats_after, "opcode.query", 1);
}

// Submit TCP IXFR query and check query counter
TEST_F(AuthSrvTest, queryCounterTCPIXFR) {
    // The counters should be initialized to 0.
    ConstElementPtr stats_init = server.getStatistics();
    expectCounterItem(stats_init, "queries.udp", 0);
    expectCounterItem(stats_init, "queries.tcp", 0);
    expectCounterItem(stats_init, "opcode.query", 0);
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                         Name("example.com"), RRClass::IN(), RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // On success, the IXFR query has been passed to a separate process,
    // so auth itself shouldn't respond.
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    // After processing the TCP IXFR query, these counters should be
    // incremented:
    //   request.tcp, opcode.query, qtype.ixfr
    // and these counters should not be incremented:
    //   request.udp, response
    ConstElementPtr stats_after = server.getStatistics();
    expectCounterItem(stats_after, "queries.udp", 0);
    expectCounterItem(stats_after, "queries.tcp", 1);
    expectCounterItem(stats_after, "opcode.query", 1);
}

TEST_F(AuthSrvTest, queryCounterOpcodes) {
    // Check for 0..2, 3(=other), 4..5
    // The counter should be initialized to 0.
    for (int i = 0; i < 6; ++i) {
        // The counter should be initialized to 0.
        expectCounterItem(server.getStatistics(),
                          std::string("opcode.") +
                              QRCounterOpcode[QROpCodeToQRCounterType[i] -
                                                  QR_OPCODE_QUERY].name,
                          0);

        // For each possible opcode, create a request message and send it
        UnitTestUtil::createRequestMessage(request_message, Opcode(i),
                                           default_qid, Name("example.com"),
                                           RRClass::IN(), RRType::NS());
        createRequestPacket(request_message, IPPROTO_UDP);

        // "send" the request N-th times where N is i + 1 for i-th code.
        // we intentionally use different values for each code
        for (int j = 0; j <= i; ++j) {
            parse_message->clear(Message::PARSE);
            server.processMessage(*io_message, *parse_message,
                                  *response_obuffer,
                                  &dnsserv);
        }

        // Confirm the counter.
        expectCounterItem(server.getStatistics(),
                          std::string("opcode.") +
                              QRCounterOpcode[QROpCodeToQRCounterType[i] -
                                                  QR_OPCODE_QUERY].name,
                          i + 1);
    }
    // Check for 6..15
    // they are treated as the 'other' opcode
    // the 'other' opcode counter is 4 at this point
    int expected = 4;
    for (int i = 6; i < 16; ++i) {
        // The counter should be initialized to 0.
        expectCounterItem(server.getStatistics(),
                          std::string("opcode.") +
                              QRCounterOpcode[QROpCodeToQRCounterType[i] -
                                              QR_OPCODE_QUERY].name,
                          expected);

        // For each possible opcode, create a request message and send it
        UnitTestUtil::createRequestMessage(request_message, Opcode(i),
                                           default_qid, Name("example.com"),
                                           RRClass::IN(), RRType::NS());
        createRequestPacket(request_message, IPPROTO_UDP);

        // "send" the request once
        parse_message->clear(Message::PARSE);
        server.processMessage(*io_message, *parse_message,
                              *response_obuffer,
                              &dnsserv);

        // the 'other' opcode counter should be incremented
        ++expected;

        // Confirm the counter.
        expectCounterItem(server.getStatistics(),
                          std::string("opcode.") +
                              QRCounterOpcode[QROpCodeToQRCounterType[i] -
                                              QR_OPCODE_QUERY].name,
                          expected);
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

TEST_F(AuthSrvTest, processNormalQuery_reuseRenderer1) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::NS());

    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    EXPECT_NE(request_message.getRcode(), parse_message->getRcode());
}

TEST_F(AuthSrvTest, processNormalQuery_reuseRenderer2) {
    UnitTestUtil::createRequestMessage(request_message, Opcode::QUERY(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());

    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);
    ConstQuestionPtr question = *parse_message->beginQuestion();
    EXPECT_STRNE(question->getType().toText().c_str(),
                 RRType::NS().toText().c_str());
}
//
// Tests for catching exceptions in various stages of the query processing
//
// These tests work by defining two proxy classes, that act as an in-memory
// client by default, but can throw exceptions at various points.
//
namespace {

/// The possible methods to throw in, either in FakeClient or
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

/// \brief proxy class for the ZoneFinder returned by the Client
///        proxied by FakeClient
///
/// See the documentation for FakeClient for more information,
/// all methods simply check whether they should throw, and if not, call
/// their proxied equivalent.
class FakeZoneFinder : public isc::datasrc::ZoneFinder {
public:
    FakeZoneFinder(isc::datasrc::ZoneFinderPtr zone_finder,
                   ThrowWhen throw_when, bool isc_exception,
                   ConstRRsetPtr fake_rrset) :
        real_zone_finder_(zone_finder),
        throw_when_(throw_when),
        isc_exception_(isc_exception),
        fake_rrset_(fake_rrset)
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

    virtual isc::datasrc::ZoneFinderContextPtr
    find(const isc::dns::Name& name,
         const isc::dns::RRType& type,
         isc::datasrc::ZoneFinder::FindOptions options)
    {
        using namespace isc::datasrc;
        checkThrow(THROW_AT_FIND, throw_when_, isc_exception_);
        // If faked RRset was specified on construction and it matches the
        // query, return it instead of searching the real data source.
        if (fake_rrset_ && fake_rrset_->getName() == name &&
            fake_rrset_->getType() == type)
        {
            return (ZoneFinderContextPtr(new ZoneFinder::Context(
                                             *this, options,
                                             ResultContext(SUCCESS,
                                                           fake_rrset_))));
        }
        return (real_zone_finder_->find(name, type, options));
    }

    virtual isc::datasrc::ZoneFinderContextPtr
    findAll(const isc::dns::Name& name,
            std::vector<isc::dns::ConstRRsetPtr> &target,
            const FindOptions options = FIND_DEFAULT)
    {
        checkThrow(THROW_AT_FIND_ALL, throw_when_, isc_exception_);
        return (real_zone_finder_->findAll(name, target, options));
    }

    virtual FindNSEC3Result
    findNSEC3(const isc::dns::Name& name, bool recursive) {
        checkThrow(THROW_AT_FIND_NSEC3, throw_when_, isc_exception_);
        return (real_zone_finder_->findNSEC3(name, recursive));
    }

private:
    isc::datasrc::ZoneFinderPtr real_zone_finder_;
    ThrowWhen throw_when_;
    bool isc_exception_;
    ConstRRsetPtr fake_rrset_;
};

/// \brief Proxy FakeClient that can throw exceptions at specified times
///
/// Currently it is used as an 'InMemoryClient' using setInMemoryClient,
/// but it is in effect a general datasource client.
class FakeClient : public isc::datasrc::DataSourceClient {
public:
    /// \brief Create a proxy memory client
    ///
    /// \param real_client The real (in-memory) client to proxy
    /// \param throw_when if set to any value other than never, that is
    ///        the method that will throw an exception (either in this
    ///        class or the related FakeZoneFinder)
    /// \param isc_exception if true, throw isc::Exception, otherwise,
    ///                      throw std::exception
    /// \param fake_rrset If non NULL, it will be used as an answer to
    /// find() for that name and type.
    FakeClient(const DataSourceClient* real_client,
               ThrowWhen throw_when, bool isc_exception,
               ConstRRsetPtr fake_rrset = ConstRRsetPtr()) :
        real_client_ptr_(real_client),
        throw_when_(throw_when),
        isc_exception_(isc_exception),
        fake_rrset_(fake_rrset)
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
        const FindResult result =
            real_client_ptr_->findZone(name);
        return (FindResult(result.code, isc::datasrc::ZoneFinderPtr(
                                        new FakeZoneFinder(result.zone_finder,
                                                           throw_when_,
                                                           isc_exception_,
                                                           fake_rrset_))));
    }

    isc::datasrc::ZoneUpdaterPtr
    getUpdater(const isc::dns::Name&, bool, bool) const {
        isc_throw(isc::NotImplemented,
                  "Update attempt on in fake data source");
    }
    std::pair<isc::datasrc::ZoneJournalReader::Result,
              isc::datasrc::ZoneJournalReaderPtr>
    getJournalReader(const isc::dns::Name&, uint32_t, uint32_t) const {
        isc_throw(isc::NotImplemented, "Journaling isn't supported for "
                  "fake data source");
    }
private:
    const DataSourceClient* real_client_ptr_;
    ThrowWhen throw_when_;
    bool isc_exception_;
    ConstRRsetPtr fake_rrset_;
};

class FakeList : public isc::datasrc::ConfigurableClientList {
public:
    /// \brief Creates a fake list for the given in-memory client
    ///
    /// It will create a FakeClient for each client in the original list,
    /// with the given arguments, which is used when searching for the
    /// corresponding data source.
    FakeList(const boost::shared_ptr<isc::datasrc::ConfigurableClientList>
             real_list, ThrowWhen throw_when, bool isc_exception,
             ConstRRsetPtr fake_rrset = ConstRRsetPtr()) :
        ConfigurableClientList(RRClass::IN()),
        real_(real_list)
    {
        BOOST_FOREACH(const DataSourceInfo& info, real_->getDataSources()) {
             const isc::datasrc::DataSourceClientPtr
                 client(new FakeClient(info.data_src_client_ != NULL ?
                                       info.data_src_client_ :
                                       info.getCacheClient(),
                                       throw_when, isc_exception, fake_rrset));
             clients_.push_back(client);
             data_sources_.push_back(
                 DataSourceInfo(client.get(),
                                isc::datasrc::DataSourceClientContainerPtr(),
                                false, RRClass::IN(), mem_sgmt_));
        }
    }
private:
    const boost::shared_ptr<isc::datasrc::ConfigurableClientList> real_;
    vector<isc::datasrc::DataSourceClientPtr> clients_;
    MemorySegmentLocal mem_sgmt_;
};

} // end anonymous namespace for throwing proxy classes

// Test for the tests
//
// Set the proxies to never throw, this should have the same result as
// queryWithInMemoryClientNoDNSSEC, and serves to test the two proxy classes
TEST_F(AuthSrvTest,
#ifdef USE_STATIC_LINK
       DISABLED_queryWithInMemoryClientProxy
#else
       queryWithInMemoryClientProxy
#endif
    )
{
    // Set real inmem client to proxy
    updateInMemory(&server, "example.", CONFIG_INMEMORY_EXAMPLE);
    boost::shared_ptr<isc::datasrc::ConfigurableClientList>
        list(new FakeList(server.getClientList(RRClass::IN()), THROW_NEVER,
                          false));
    server.setClientList(RRClass::IN(), list);

    createDataFromFile("nsec3query_nodnssec_fromWire.wire");
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 2, 1);
}

// Convenience function for the rest of the tests, set up a proxy
// to throw in the given method
// If isc_exception is true, it will throw isc::Exception, otherwise
// it will throw std::exception
// If non null rrset is given, it will be passed to the proxy so it can
// return some faked response.
void
setupThrow(AuthSrv* server, ThrowWhen throw_when, bool isc_exception,
           ConstRRsetPtr rrset = ConstRRsetPtr())
{
    updateInMemory(server, "example.", CONFIG_INMEMORY_EXAMPLE);

    boost::shared_ptr<isc::datasrc::ConfigurableClientList>
        list(new FakeList(server->getClientList(RRClass::IN()), throw_when,
                          isc_exception, rrset));
    server->setClientList(RRClass::IN(), list);
}

TEST_F(AuthSrvTest,
#ifdef USE_STATIC_LINK
       DISABLED_queryWithThrowingProxyServfails
#else
       queryWithThrowingProxyServfails
#endif
    )
{
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
        setupThrow(&server, *when, true);
        processAndCheckSERVFAIL();
        // To be sure, check same for non-isc-exceptions
        createRequestPacket(request_message, IPPROTO_UDP);
        setupThrow(&server, *when, false);
        processAndCheckSERVFAIL();
    }
}

// Throw isc::Exception in getClass(). (Currently?) getClass is not called
// in the processMessage path, so this should result in a normal answer
TEST_F(AuthSrvTest,
#ifdef USE_STATIC_LINK
       DISABLED_queryWithInMemoryClientProxyGetClass
#else
       queryWithInMemoryClientProxyGetClass
#endif
    )
{
    createDataFromFile("nsec3query_nodnssec_fromWire.wire");
    setupThrow(&server, THROW_AT_GET_CLASS, true);

    // getClass is not called so it should just answer
    server.processMessage(*io_message, *parse_message, *response_obuffer,
                          &dnsserv);

    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOERROR(),
                opcode.getCode(), QR_FLAG | AA_FLAG, 1, 1, 2, 1);
}

TEST_F(AuthSrvTest,
#ifdef USE_STATIC_LINK
       DISABLED_queryWithThrowingInToWire
#else
       queryWithThrowingInToWire
#endif
    )
{
    // Set up a faked data source.  It will return an empty RRset for the
    // query.
    ConstRRsetPtr empty_rrset(new RRset(Name("foo.example"),
                                        RRClass::IN(), RRType::TXT(),
                                        RRTTL(0)));
    setupThrow(&server, THROW_NEVER, true, empty_rrset);

    // Repeat the query processing two times.  Due to the faked RRset,
    // toWire() should throw, and it should result in SERVFAIL.
    OutputBufferPtr orig_buffer;
    for (int i = 0; i < 2; ++i) {
        UnitTestUtil::createDNSSECRequestMessage(request_message, opcode,
                                                 default_qid,
                                                 Name("foo.example."),
                                                 RRClass::IN(), RRType::TXT());
        createRequestPacket(request_message, IPPROTO_UDP);
        server.processMessage(*io_message, *parse_message, *response_obuffer,
                              &dnsserv);
        headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                    opcode.getCode(), QR_FLAG, 1, 0, 0, 0);

        // Make a backup of the original buffer for latest tests and replace
        // it with a new one
        if (!orig_buffer) {
            orig_buffer = response_obuffer;
            response_obuffer.reset(new OutputBuffer(0));
        }
        request_message.clear(Message::RENDER);
        parse_message->clear(Message::PARSE);
    }

    // Now check if the original buffer is intact
    parse_message->clear(Message::PARSE);
    InputBuffer ibuffer(orig_buffer->getData(), orig_buffer->getLength());
    parse_message->fromWire(ibuffer);
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}

//
// DDNS related tests
//

// Helper subroutine to check if the given socket address has the expected
// address and port.  It depends on specific output of getnameinfo() (while
// there can be multiple textual representation of the same address) but
// in practice it should be reliable.
void
checkAddrPort(const struct sockaddr& actual_sa,
              const string& expected_addr, uint16_t expected_port)
{
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    const int error = getnameinfo(&actual_sa, getSALength(actual_sa), hbuf,
                                  sizeof(hbuf), sbuf, sizeof(sbuf),
                                  NI_NUMERICHOST | NI_NUMERICSERV);
    if (error != 0) {
        isc_throw(isc::Unexpected, "getnameinfo failed: " <<
                  gai_strerror(error));
    }
    EXPECT_EQ(expected_addr, hbuf);
    EXPECT_EQ(boost::lexical_cast<string>(expected_port), sbuf);
}

TEST_F(AuthSrvTest, DDNSForward) {
    EXPECT_FALSE(ddns_forwarder.isConnected());

    // Repeat sending an update request 4 times, differing some network
    // parameters: UDP/IPv4, TCP/IPv4, UDP/IPv6, TCP/IPv6, in this order.
    // By doing that we can also confirm the forwarder connection will be
    // established exactly once, and kept established.
    for (size_t i = 0; i < 4; ++i) {
        // Use different names for some different cases
        const Name zone_name = Name(i < 2 ? "example.com" : "example.org");
        const socklen_t family = (i < 2) ? AF_INET : AF_INET6;
        const char* const remote_addr =
            (family == AF_INET) ? "192.0.2.1" : "2001:db8::1";
        const uint16_t remote_port =
            (family == AF_INET) ? 53214 : 53216;
        const int protocol = ((i % 2) == 0) ? IPPROTO_UDP : IPPROTO_TCP;

        createAndSendRequest(RRType::SOA(), Opcode::UPDATE(), zone_name,
                             RRClass::IN(), protocol, remote_addr,
                             remote_port);
        EXPECT_FALSE(dnsserv.hasAnswer());
        EXPECT_TRUE(ddns_forwarder.isConnected());

        // Examine the pushed data (note: currently "local end" has a dummy
        // value equal to remote)
        EXPECT_EQ(family, ddns_forwarder.getPushedFamily());
        const int expected_type =
            (protocol == IPPROTO_UDP) ? SOCK_DGRAM : SOCK_STREAM;
        EXPECT_EQ(expected_type, ddns_forwarder.getPushedType());
        EXPECT_EQ(protocol, ddns_forwarder.getPushedProtocol());
        checkAddrPort(ddns_forwarder.getPushedRemoteend(),
                      remote_addr, remote_port);
        checkAddrPort(ddns_forwarder.getPushedLocalend(),
                      remote_addr, remote_port);
        EXPECT_EQ(io_message->getDataSize(),
                  ddns_forwarder.getPushedData().size());
        EXPECT_EQ(0, memcmp(io_message->getData(),
                            &ddns_forwarder.getPushedData()[0],
                            ddns_forwarder.getPushedData().size()));
    }
}

TEST_F(AuthSrvTest, DDNSForwardConnectFail) {
    // make connect attempt fail.  It should result in SERVFAIL.  Note that
    // the question (zone) section should be cleared for opcode of update.
    ddns_forwarder.disableConnect();
    createAndSendRequest(RRType::SOA(), Opcode::UPDATE());
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                Opcode::UPDATE().getCode(), QR_FLAG, 0, 0, 0, 0);
    EXPECT_FALSE(ddns_forwarder.isConnected());

    // Now make connect okay again.  Despite the previous failure the new
    // connection should now be established.
    ddns_forwarder.enableConnect();
    createAndSendRequest(RRType::SOA(), Opcode::UPDATE());
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(ddns_forwarder.isConnected());
}

TEST_F(AuthSrvTest, DDNSForwardPushFail) {
    // Make first request succeed, which will establish the connection.
    EXPECT_FALSE(ddns_forwarder.isConnected());
    createAndSendRequest(RRType::SOA(), Opcode::UPDATE());
    EXPECT_TRUE(ddns_forwarder.isConnected());

    // make connect attempt fail.  It should result in SERVFAIL.  The
    // connection should be closed.  Use IPv6 address for varying log output.
    ddns_forwarder.disablePush();
    createAndSendRequest(RRType::SOA(), Opcode::UPDATE(), Name("example.com"),
                         RRClass::IN(), IPPROTO_UDP, "2001:db8::2");
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::SERVFAIL(),
                Opcode::UPDATE().getCode(), QR_FLAG, 0, 0, 0, 0);
    EXPECT_FALSE(ddns_forwarder.isConnected());

    // Allow push again.  Connection will be reopened, and the request will
    // be forwarded successfully.
    ddns_forwarder.enablePush();
    createAndSendRequest(RRType::SOA(), Opcode::UPDATE());
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(ddns_forwarder.isConnected());
}

TEST_F(AuthSrvTest, DDNSForwardClose) {
    scoped_ptr<AuthSrv> tmp_server(new AuthSrv(xfrout, ddns_forwarder));
    tmp_server->createDDNSForwarder();
    UnitTestUtil::createRequestMessage(request_message, Opcode::UPDATE(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    createRequestPacket(request_message, IPPROTO_UDP);
    tmp_server->processMessage(*io_message, *parse_message, *response_obuffer,
                               &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(ddns_forwarder.isConnected());

    // Destroy the server.  The forwarder should close the connection.
    tmp_server.reset();
    EXPECT_FALSE(ddns_forwarder.isConnected());
}

namespace {
    // Send a basic command without arguments, and check the response has
    // result code 0
    void sendSimpleCommand(AuthSrv& server, const std::string& command) {
        ConstElementPtr response = execAuthServerCommand(server, command,
                                                         ConstElementPtr());
        int command_result = -1;
        isc::config::parseAnswer(command_result, response);
        EXPECT_EQ(0, command_result);
    }
} // end anonymous namespace

TEST_F(AuthSrvTest, DDNSForwardCreateDestroy) {
    // Test that AuthSrv returns NOTIMP before ddns forwarder is created,
    // that the ddns_forwarder is connected when the 'start_ddns_forwarder'
    // command has been sent, and that it is no longer connected and auth
    // returns NOTIMP after the stop_ddns_forwarding command is sent.
    scoped_ptr<AuthSrv> tmp_server(new AuthSrv(xfrout, ddns_forwarder));

    // Prepare update message to send
    UnitTestUtil::createRequestMessage(request_message, Opcode::UPDATE(),
                                       default_qid, Name("example.com"),
                                       RRClass::IN(), RRType::SOA());
    createRequestPacket(request_message, IPPROTO_UDP);

    // before creating forwarder. isConnected() should be false and
    // rcode to UPDATE should be NOTIMP
    parse_message->clear(Message::PARSE);
    tmp_server->processMessage(*io_message, *parse_message, *response_obuffer,
                               &dnsserv);
    EXPECT_FALSE(ddns_forwarder.isConnected());
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOTIMP(),
                Opcode::UPDATE().getCode(), QR_FLAG, 0, 0, 0, 0);

    // now create forwarder
    sendSimpleCommand(*tmp_server, "start_ddns_forwarder");

    // our mock does not respond, and since auth is supposed to send it on,
    // there should now be no result when an UPDATE is sent
    parse_message->clear(Message::PARSE);
    tmp_server->processMessage(*io_message, *parse_message, *response_obuffer,
                               &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(ddns_forwarder.isConnected());

    // If we send a start again, the connection should be recreated,
    // visible because isConnected() reports false until an actual message
    // has been forwarded
    sendSimpleCommand(*tmp_server, "start_ddns_forwarder");

    EXPECT_FALSE(ddns_forwarder.isConnected());
    parse_message->clear(Message::PARSE);
    tmp_server->processMessage(*io_message, *parse_message, *response_obuffer,
                               &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
    EXPECT_TRUE(ddns_forwarder.isConnected());

    // Now tell it to stop forwarder, should respond with NOTIMP again
    sendSimpleCommand(*tmp_server, "stop_ddns_forwarder");

    parse_message->clear(Message::PARSE);
    tmp_server->processMessage(*io_message, *parse_message, *response_obuffer,
                               &dnsserv);
    EXPECT_FALSE(ddns_forwarder.isConnected());
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOTIMP(),
                Opcode::UPDATE().getCode(), QR_FLAG, 0, 0, 0, 0);

    // Sending stop again should make no difference
    sendSimpleCommand(*tmp_server, "stop_ddns_forwarder");

    parse_message->clear(Message::PARSE);
    tmp_server->processMessage(*io_message, *parse_message, *response_obuffer,
                               &dnsserv);
    EXPECT_FALSE(ddns_forwarder.isConnected());
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOTIMP(),
                Opcode::UPDATE().getCode(), QR_FLAG, 0, 0, 0, 0);
}

// Check the client list accessors
TEST_F(AuthSrvTest, clientList) {
    // The lists don't exist. Therefore, the list of RRClasses is empty.
    // We also have no IN list.
    EXPECT_TRUE(server.getClientListClasses().empty());
    EXPECT_EQ(boost::shared_ptr<const isc::datasrc::ClientList>(),
              server.getClientList(RRClass::IN()));
    // Put something in.
    const boost::shared_ptr<isc::datasrc::ConfigurableClientList>
        list(new isc::datasrc::ConfigurableClientList(RRClass::IN()));
    const boost::shared_ptr<isc::datasrc::ConfigurableClientList>
        list2(new isc::datasrc::ConfigurableClientList(RRClass::CH()));
    server.setClientList(RRClass::IN(), list);
    server.setClientList(RRClass::CH(), list2);
    // There are two things in the list and they are IN and CH
    vector<RRClass> classes(server.getClientListClasses());
    ASSERT_EQ(2, classes.size());
    EXPECT_EQ(RRClass::IN(), classes[0]);
    EXPECT_EQ(RRClass::CH(), classes[1]);
    // And the lists can be retrieved.
    EXPECT_EQ(list, server.getClientList(RRClass::IN()));
    EXPECT_EQ(list2, server.getClientList(RRClass::CH()));
    // Remove one of them
    server.setClientList(RRClass::CH(),
        boost::shared_ptr<isc::datasrc::ConfigurableClientList>());
    // This really got deleted, including the class.
    classes = server.getClientListClasses();
    ASSERT_EQ(1, classes.size());
    EXPECT_EQ(RRClass::IN(), classes[0]);
    EXPECT_EQ(list, server.getClientList(RRClass::IN()));
}

}
