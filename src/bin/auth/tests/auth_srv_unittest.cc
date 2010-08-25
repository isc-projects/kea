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
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cc/data.h>
#include <cc/session.h>

#include <xfr/xfrout_client.h>

#include <auth/auth_srv.h>
#include <auth/asio_link.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::xfr;
using namespace asio_link;

namespace {
const char* const CONFIG_TESTDB =
    "{\"database_file\": \"" TEST_DATA_DIR "/example.sqlite3\"}";
// The following file must be non existent and must be non"creatable" (see
// the sqlite3 test).
const char* const BADCONFIG_TESTDB =
    "{ \"database_file\": \"" TEST_DATA_DIR "/nodir/notexist\"}";
const char* const DEFAULT_REMOTE_ADDRESS = "192.0.2.1";

class AuthSrvTest : public ::testing::Test {
private:
    class MockXfroutClient : public AbstractXfroutClient {
    public:
        MockXfroutClient() :
            is_connected_(false), connect_ok_(true), send_ok_(true),
            disconnect_ok_(true)
        {}
        virtual void connect();
        virtual void disconnect();
        virtual int sendXfroutRequestInfo(int tcp_sock, const void* msg_data,
                                          uint16_t msg_len);
        bool isConnected() const { return (is_connected_); }
        void disableConnect() { connect_ok_ = false; }
        void disableDisconnect() { disconnect_ok_ = false; }
        void enableDisconnect() { disconnect_ok_ = true; }
        void disableSend() { send_ok_ = false; }
    private:
        bool is_connected_;
        bool connect_ok_;
        bool send_ok_;
        bool disconnect_ok_;
    };

    class MockSession : public AbstractSession {
    public:
        MockSession() :
            // by default we return a simple "success" message.
            msg_(Element::fromJSON("{\"result\": [0, \"SUCCESS\"]}")),
            send_ok_(true), receive_ok_(true)
        {}
        virtual void establish(const char* socket_file);
        virtual void disconnect();
        virtual int group_sendmsg(ConstElementPtr msg, string group,
                                  string instance, string to);
        virtual bool group_recvmsg(ConstElementPtr& envelope,
                                   ConstElementPtr& msg,
                                   bool nonblock, int seq);
        virtual void subscribe(string group, string instance);
        virtual void unsubscribe(string group, string instance);
        virtual void startRead(boost::function<void()> read_callback);
        virtual int reply(ConstElementPtr envelope, ConstElementPtr newmsg);
        virtual bool hasQueuedMsgs() const;
        virtual void setTimeout(size_t timeout UNUSED_PARAM) {};
        virtual size_t getTimeout() const { return 0; };

        void setMessage(ConstElementPtr msg) { msg_ = msg; }
        void disableSend() { send_ok_ = false; }
        void disableReceive() { receive_ok_ = false; }

        ConstElementPtr sent_msg;
        string msg_destination;
    private:
        ConstElementPtr msg_;
        bool send_ok_;
        bool receive_ok_;
    };

protected:
    AuthSrvTest() : server(true, xfrout),
                    request_message(Message::RENDER),
                    parse_message(Message::PARSE), default_qid(0x1035),
                    opcode(Opcode(Opcode::QUERY())), qname("www.example.com"),
                    qclass(RRClass::IN()), qtype(RRType::A()),
                    io_message(NULL), endpoint(NULL), request_obuffer(0),
                    request_renderer(request_obuffer),
                    response_obuffer(0), response_renderer(response_obuffer)
    {
        server.setXfrinSession(&notify_session);
    }
    ~AuthSrvTest() {
        delete io_message;
        delete endpoint;
    }
    MockSession notify_session;
    MockXfroutClient xfrout;
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
    void createRequestMessage(const Opcode& opcode, const Name& request_name,
                              const RRClass& rrclass, const RRType& rrtype);
    void createRequestPacket(const Opcode& opcode, const Name& request_name,
                             const RRClass& rrclass, const RRType& rrtype,
                             int protocol);
    void createRequestPacket(int protocol);
};

void
AuthSrvTest::MockSession::establish(const char* socket_file UNUSED_PARAM) {}

void
AuthSrvTest::MockSession::disconnect() {}

void
AuthSrvTest::MockSession::subscribe(string group UNUSED_PARAM,
                                    string instance UNUSED_PARAM)
{}

void
AuthSrvTest::MockSession::unsubscribe(string group UNUSED_PARAM,
                                      string instance UNUSED_PARAM)
{}

void
AuthSrvTest::MockSession::startRead(
    boost::function<void()> read_callback UNUSED_PARAM)
{}

int
AuthSrvTest::MockSession::reply(ConstElementPtr envelope UNUSED_PARAM,
                                ConstElementPtr newmsg UNUSED_PARAM)
{
    return (-1);
}

bool
AuthSrvTest::MockSession::hasQueuedMsgs() const {
    return (false);
}

int
AuthSrvTest::MockSession::group_sendmsg(ConstElementPtr msg, string group,
                                        string instance UNUSED_PARAM,
                                        string to UNUSED_PARAM)
{
    if (!send_ok_) {
        isc_throw(XfroutError, "mock session send is disabled for test");
    }

    sent_msg = msg;
    msg_destination = group;
    return (0);
}

bool
AuthSrvTest::MockSession::group_recvmsg(ConstElementPtr& envelope UNUSED_PARAM,
                                        ConstElementPtr& msg,
                                        bool nonblock UNUSED_PARAM,
                                        int seq UNUSED_PARAM)
{
    if (!receive_ok_) {
        isc_throw(XfroutError, "mock session receive is disabled for test");
    }

    msg = msg_;
    return (true);
}

void
AuthSrvTest::MockXfroutClient::connect() {
    if (!connect_ok_) {
        isc_throw(XfroutError, "xfrout connection disabled for test");
    }
    is_connected_ = true;
}

void
AuthSrvTest::MockXfroutClient::disconnect() {
    if (!disconnect_ok_) {
        isc_throw(XfroutError,
                  "closing xfrout connection is disabled for test");
    }
    is_connected_ = false;
}

int
AuthSrvTest::MockXfroutClient::sendXfroutRequestInfo(
    const int tcp_sock UNUSED_PARAM,
    const void* msg_data UNUSED_PARAM,
    const uint16_t msg_len UNUSED_PARAM)
{
    if (!send_ok_) {
        isc_throw(XfroutError, "xfrout connection send is disabled for test");
    }
    return (0);
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
AuthSrvTest::createDataFromFile(const char* const datafile,
                                const int protocol = IPPROTO_UDP)
{
    delete io_message;
    data.clear();

    delete endpoint;
    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    UnitTestUtil::readWireData(datafile, data);
    io_message = new IOMessage(&data[0], data.size(),
                               protocol == IPPROTO_UDP ?
                               IOSocket::getDummyUDPSocket() :
                               IOSocket::getDummyTCPSocket(), *endpoint);
}

void
AuthSrvTest::createRequestMessage(const Opcode& opcode,
                                  const Name& request_name,
                                  const RRClass& rrclass,
                                  const RRType& rrtype)
{
    request_message.clear(Message::RENDER);
    request_message.setOpcode(opcode);
    request_message.setQid(default_qid);
    request_message.addQuestion(Question(request_name, rrclass, rrtype));
}

void
AuthSrvTest::createRequestPacket(const Opcode& opcode,
                                 const Name& request_name,
                                 const RRClass& rrclass, const RRType& rrtype,
                                 const int protocol = IPPROTO_UDP)
{
    createRequestMessage(opcode, request_name, rrclass, rrtype);
    createRequestPacket(protocol);
}

void
AuthSrvTest::createRequestPacket(const int protocol = IPPROTO_UDP) {
    request_message.toWire(request_renderer);

    delete io_message;
    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    io_message = new IOMessage(request_renderer.getData(),
                               request_renderer.getLength(),
                               protocol == IPPROTO_UDP ?
                               IOSocket::getDummyUDPSocket() :
                               IOSocket::getDummyTCPSocket(), *endpoint);
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
    for (unsigned int i = 0; i < 16; ++i) {
        // set Opcode to 'i', which iterators over all possible codes except
        // the standard query and notify
        if (i == Opcode::QUERY().getCode() ||
            i == Opcode::NOTIFY().getCode()) {
            continue;
        }
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
    createRequestPacket(opcode, Name("example.com"), RRClass::IN(),
                        RRType::AXFR(), IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, AXFRSuccess) {
    EXPECT_FALSE(xfrout.isConnected());
    createRequestPacket(opcode, Name("example.com"), RRClass::IN(),
                        RRType::AXFR(), IPPROTO_TCP);
    // On success, the AXFR query has been passed to a separate process,
    // so we shouldn't have to respond.
    EXPECT_EQ(false, server.processMessage(*io_message, parse_message,
                                           response_renderer));
    EXPECT_FALSE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, AXFRConnectFail) {
    EXPECT_FALSE(xfrout.isConnected()); // check prerequisite
    xfrout.disableConnect();
    createRequestPacket(opcode, Name("example.com"), RRClass::IN(),
                        RRType::AXFR(), IPPROTO_TCP);
    EXPECT_TRUE(server.processMessage(*io_message, parse_message,
                                      response_renderer));
    headerCheck(parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
    // For a shot term workaround with xfrout we currently close the connection
    // for each AXFR attempt
    EXPECT_FALSE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, AXFRSendFail) {
    // first send a valid query, making the connection with the xfr process
    // open.
    createRequestPacket(opcode, Name("example.com"), RRClass::IN(),
                        RRType::AXFR(), IPPROTO_TCP);
    server.processMessage(*io_message, parse_message, response_renderer);
    EXPECT_FALSE(xfrout.isConnected()); // see above

    xfrout.disableSend();
    parse_message.clear(Message::PARSE);
    response_renderer.clear();
    createRequestPacket(opcode, Name("example.com"), RRClass::IN(),
                        RRType::AXFR(), IPPROTO_TCP);
    EXPECT_TRUE(server.processMessage(*io_message, parse_message,
                                      response_renderer));
    headerCheck(parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);

    // The connection should have been closed due to the send failure.
    EXPECT_FALSE(xfrout.isConnected());
}

TEST_F(AuthSrvTest, AXFRDisconnectFail) {
    // In our usage disconnect() shouldn't fail.  So we'll see the exception
    // should it be thrown.
    xfrout.disableSend();
    xfrout.disableDisconnect();
    createRequestPacket(opcode, Name("example.com"), RRClass::IN(),
                        RRType::AXFR(), IPPROTO_TCP);
    EXPECT_THROW(server.processMessage(*io_message, parse_message,
                                       response_renderer),
                 XfroutError);
    EXPECT_TRUE(xfrout.isConnected());
    // XXX: we need to re-enable disconnect.  otherwise an exception would be
    // thrown via the destructor of the server.
    xfrout.enableDisconnect();
}

TEST_F(AuthSrvTest, notify) {
    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));

    // An internal command message should have been created and sent to an
    // external module.  Check them.
    EXPECT_EQ("Zonemgr", notify_session.msg_destination);
    EXPECT_EQ("notify",
              notify_session.sent_msg->get("command")->get(0)->stringValue());
    ConstElementPtr notify_args =
        notify_session.sent_msg->get("command")->get(1);
    EXPECT_EQ("example.com.", notify_args->get("zone_name")->stringValue());
    EXPECT_EQ(DEFAULT_REMOTE_ADDRESS,
              notify_args->get("master")->stringValue());
    EXPECT_EQ("IN", notify_args->get("zone_class")->stringValue());

    // On success, the server should return a response to the notify.
    headerCheck(parse_message, default_qid, Rcode::NOERROR(),
                Opcode::NOTIFY().getCode(), QR_FLAG | AA_FLAG, 1, 0, 0, 0);

    // The question must be identical to that of the received notify
    ConstQuestionPtr question = *parse_message.beginQuestion();
    EXPECT_EQ(Name("example.com"), question->getName());
    EXPECT_EQ(RRClass::IN(), question->getClass());
    EXPECT_EQ(RRType::SOA(), question->getType());
}

TEST_F(AuthSrvTest, notifyForCHClass) {
    // Same as the previous test, but for the CH RRClass.
    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::CH(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));

    // Other conditions should be the same, so simply confirm the RR class is
    // set correctly.
    ConstElementPtr notify_args =
        notify_session.sent_msg->get("command")->get(1);
    EXPECT_EQ("CH", notify_args->get("zone_class")->stringValue());
}

TEST_F(AuthSrvTest, notifyEmptyQuestion) {
    request_message.clear(Message::RENDER);
    request_message.setOpcode(Opcode::NOTIFY());
    request_message.setHeaderFlag(MessageFlag::AA());
    request_message.setQid(default_qid);
    request_message.toWire(request_renderer);
    createRequestPacket(IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::FORMERR(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 0, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyMultiQuestions) {
    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    // add one more SOA question
    request_message.addQuestion(Question(Name("example.com"), RRClass::IN(),
                                         RRType::SOA()));
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::FORMERR(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 2, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyNonSOAQuestion) {
    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::NS());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::FORMERR(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithoutAA) {
    // implicitly leave the AA bit off.  our implementation will accept it.
    createRequestPacket(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::NOERROR(),
                Opcode::NOTIFY().getCode(), QR_FLAG | AA_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithErrorRcode) {
    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    request_message.setRcode(Rcode::SERVFAIL());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_EQ(true, server.processMessage(*io_message, parse_message,
                                          response_renderer));
    headerCheck(parse_message, default_qid, Rcode::NOERROR(),
                Opcode::NOTIFY().getCode(), QR_FLAG | AA_FLAG, 1, 0, 0, 0);
}

TEST_F(AuthSrvTest, notifyWithoutSession) {
    server.setXfrinSession(NULL);

    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);

    // we simply ignore the notify and let it be resent if an internal error
    // happens.
    EXPECT_FALSE(server.processMessage(*io_message, parse_message,
                                       response_renderer));
}

TEST_F(AuthSrvTest, notifySendFail) {
    notify_session.disableSend();

    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);

    EXPECT_FALSE(server.processMessage(*io_message, parse_message,
                                       response_renderer));
}

TEST_F(AuthSrvTest, notifyReceiveFail) {
    notify_session.disableReceive();

    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_FALSE(server.processMessage(*io_message, parse_message,
                                       response_renderer));
}

TEST_F(AuthSrvTest, notifyWithBogusSessionMessage) {
    notify_session.setMessage(Element::fromJSON("{\"foo\": 1}"));

    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_FALSE(server.processMessage(*io_message, parse_message,
                                       response_renderer));
}

TEST_F(AuthSrvTest, notifyWithSessionMessageError) {
    notify_session.setMessage(
        Element::fromJSON("{\"result\": [1, \"FAIL\"]}"));

    createRequestMessage(Opcode::NOTIFY(), Name("example.com"), RRClass::IN(),
                        RRType::SOA());
    request_message.setHeaderFlag(MessageFlag::AA());
    createRequestPacket(IPPROTO_UDP);
    EXPECT_FALSE(server.processMessage(*io_message, parse_message,
                                       response_renderer));
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
    headerCheck(parse_message, default_qid, Rcode::SERVFAIL(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
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
