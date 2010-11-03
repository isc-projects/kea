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
#include <recurse/recursor.h>
#include <auth/tests/srv_test.h>
#include <auth/tests/srv_unittest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::data;
using namespace asiolink;

namespace {
const char* const TEST_PORT = "53535";

class RecursorTest : public SrvTestBase{
protected:
    RecursorTest() : server(*DEFAULT_REMOTE_ADDRESS){}
    Recursor server;
};

// Unsupported requests.  Should result in NOTIMP.
TEST_F(RecursorTest, unsupportedRequest) {
    UNSUPPORTED_REQUEST_TEST;
}

// Simple API check
TEST_F(RecursorTest, verbose) {
    VERBOSE_TEST;
}

// Multiple questions.  Should result in FORMERR.
TEST_F(RecursorTest, multiQuestion) {
    MULTI_QUESTION_TEST; 
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
TEST_F(RecursorTest, shortMessage) {
    SHORT_MESSAGE_TEST;
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(RecursorTest, response) {
    RESPONSE_TEST;
}

// Query with a broken question
TEST_F(RecursorTest, shortQuestion) {
    SHORT_QUESTION_TEST;
}

// Query with a broken answer section
TEST_F(RecursorTest, shortAnswer) {
    SHORT_ANSWER_TEST;
}

// Query with unsupported version of EDNS.
TEST_F(RecursorTest, ednsBadVers) {
    EDNS_BADVERS_TEST;
}

TEST_F(RecursorTest, AXFROverUDP) {
    AXFR_OVER_UDP_TEST;
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
