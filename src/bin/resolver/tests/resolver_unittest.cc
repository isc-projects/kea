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

#include <string>

#include <exceptions/exceptions.h>

#include <dns/name.h>

#include <cc/data.h>
#include <resolver/resolver.h>
#include <dns/tests/unittest_util.h>
#include <testutils/dnsmessage_test.h>
#include <testutils/srv_test.h>

using namespace std;
using namespace isc::dns;
using namespace isc::data;
using isc::acl::dns::RequestACL;
using namespace isc::testutils;
using isc::UnitTestUtil;

namespace {
const char* const TEST_PORT = "53535";

class ResolverTest : public SrvTestBase{
protected:
    ResolverTest() : server() {
        // By default queries from the "default remote address" will be
        // rejected, so we'll need to add an explicit ACL entry to allow that.
        server.updateConfig(Element::fromJSON(
                                "{ \"query_acl\": "
                                "  [ {\"action\": \"ACCEPT\","
                                "     \"from\": \"" +
                                string(DEFAULT_REMOTE_ADDRESS) +
                                "\"} ] }"));
    }
    virtual void processMessage() {
        server.processMessage(*io_message,
                              parse_message,
                              response_message,
                              response_obuffer,
                              &dnsserv);
    }
    Resolver server;
};

// Unsupported requests.  Should result in NOTIMP.
TEST_F(ResolverTest, unsupportedRequest) {
    unsupportedRequest();
}

// Multiple questions.  Should result in FORMERR.
TEST_F(ResolverTest, multiQuestion) {
    multiQuestion(); 
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
TEST_F(ResolverTest, shortMessage) {
    shortMessage();
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(ResolverTest, response) {
     response();
}

// Query with a broken question
TEST_F(ResolverTest, shortQuestion) {
    shortQuestion();
}

// Query with a broken answer section
TEST_F(ResolverTest, shortAnswer) {
    shortAnswer();
}

// Query with unsupported version of EDNS.
TEST_F(ResolverTest, ednsBadVers) {
    ednsBadVers();
}

TEST_F(ResolverTest, AXFROverUDP) {
    axfrOverUDP();
}

TEST_F(ResolverTest, AXFRFail) {
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // AXFR is not implemented and should always send NOTIMP.
    server.processMessage(*io_message,
                          parse_message,
                          response_message,
                          response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOTIMP(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
}

TEST_F(ResolverTest, IXFRFail) {
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::IXFR());
    createRequestPacket(request_message, IPPROTO_TCP);
    // IXFR is not implemented and should always send NOTIMP.
    server.processMessage(*io_message,
                          parse_message,
                          response_message,
                          response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    // the second check is what we'll need in the end (with the values
    // from the first one), but right now the first one is for what
    // will actually be returned to the client
    headerCheck(*parse_message, default_qid, Rcode::NOTIMP(), opcode.getCode(),
                QR_FLAG, 1, 0, 0, 0);
    headerCheck(*response_message, default_qid, Rcode::NOTIMP(), opcode.getCode(),
                0, 0, 0, 0, 0);
}

TEST_F(ResolverTest, notifyFail) {
    // Notify should always return NOTAUTH
    request_message.clear(Message::RENDER);
    request_message.setOpcode(Opcode::NOTIFY());
    request_message.setRcode(Rcode::NOERROR());
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    request_message.setQid(default_qid);
    request_message.setHeaderFlag(Message::HEADERFLAG_AA);
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message,
                          parse_message,
                          response_message,
                          response_obuffer,
                          &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::NOTAUTH(),
                Opcode::NOTIFY().getCode(), QR_FLAG, 0, 0, 0, 0);
}

TEST_F(ResolverTest, setQueryACL) {
    // valid cases are tested through other tests.  We only explicitly check
    // an invalid case: passing a NULL shared pointer.
    EXPECT_THROW(server.setQueryACL(boost::shared_ptr<const RequestACL>()),
                 isc::InvalidParameter);
}

TEST_F(ResolverTest, queryACL) {
    // The "ACCEPT" cases are covered in other tests.  Here we explicitly
    // test "REJECT" and "DROP" cases.

    // Clear the existing ACL, reverting to the "default reject" rule.

    // AXFR over UDP.  This would otherwise result in FORMERR.
    server.updateConfig(Element::fromJSON("{ \"query_acl\": [] }"));
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       Name("example.com"), RRClass::IN(),
                                       RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_UDP);
    server.processMessage(*io_message, parse_message, response_message,
                          response_obuffer, &dnsserv);
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, Rcode::REFUSED(),
                Opcode::QUERY().getCode(), QR_FLAG, 1, 0, 0, 0);

    // Same query, but with an explicit "DROP" ACL entry.  There should be
    // no response.
    server.updateConfig(Element::fromJSON("{ \"query_acl\": "
                                          "  [ {\"action\": \"DROP\","
                                          "     \"from\": \"" +
                                          string(DEFAULT_REMOTE_ADDRESS) +
                                          "\"} ] }"));
    parse_message->clear(Message::PARSE);
    response_message->clear(Message::RENDER);
    response_obuffer->clear();
    server.processMessage(*io_message, parse_message, response_message,
                          response_obuffer, &dnsserv);
    EXPECT_FALSE(dnsserv.hasAnswer());
}


}
