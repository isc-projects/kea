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

#include <auth/auth_srv.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;

namespace {
class AuthSrvTest : public ::testing::Test {
protected:
    AuthSrvTest() : request_message(Message::RENDER),
                    parse_message(Message::PARSE), default_qid(0x1035),
                    opcode(Opcode(Opcode::QUERY())), qname("www.example.com"),
                    qclass(RRClass::IN()), qtype(RRType::A()), ibuffer(NULL),
                    request_obuffer(0), request_renderer(request_obuffer),
                    response_obuffer(0), response_renderer(response_obuffer)
    {}
    AuthSrv server;
    Message request_message;
    Message parse_message;
    qid_t default_qid;
    Opcode opcode;
    Name qname;
    RRClass qclass;
    RRType qtype;
    InputBuffer* ibuffer;
    OutputBuffer request_obuffer;
    MessageRenderer request_renderer;
    OutputBuffer response_obuffer;
    MessageRenderer response_renderer;
    vector<uint8_t> data;

    void createDataFromFile(const char* const datafile);
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
AuthSrvTest::createDataFromFile(const char* const datafile) {
    delete ibuffer;
    data.clear();

    UnitTestUtil::readWireData(datafile, data);
    ibuffer = new InputBuffer(&data[0], data.size());
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
    EXPECT_EQ((flags & QR_FLAG) == 1, message.getHeaderFlag(MessageFlag::QR()));
    EXPECT_EQ((flags & AA_FLAG) == 1, message.getHeaderFlag(MessageFlag::AA()));
    EXPECT_EQ((flags & TC_FLAG) == 1, message.getHeaderFlag(MessageFlag::TC()));
    EXPECT_EQ((flags & RA_FLAG) == 1, message.getHeaderFlag(MessageFlag::RA()));
    EXPECT_EQ((flags & RD_FLAG) == 1, message.getHeaderFlag(MessageFlag::RD()));
    EXPECT_EQ((flags & AD_FLAG) == 1, message.getHeaderFlag(MessageFlag::AD()));
    EXPECT_EQ((flags & CD_FLAG) == 1, message.getHeaderFlag(MessageFlag::CD()));

    EXPECT_EQ(qdcount, message.getRRCount(Section::QUESTION()));
    EXPECT_EQ(ancount, message.getRRCount(Section::ANSWER()));
    EXPECT_EQ(nscount, message.getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(arcount, message.getRRCount(Section::ADDITIONAL()));
}

// Unsupported requests.  Should result in NOTIMP.
TEST_F(AuthSrvTest, unsupportedRequest) {
    for (unsigned int i = 1; i < 16; ++i) {
        // set Opcode to 'i', which iterators over all possible codes except
        // the standard query (0)
        createDataFromFile("testdata/simplequery_fromWire");
        data[2] = ((i << 3) & 0xff);

        parse_message.clear(Message::PARSE);
        EXPECT_EQ(true, server.processMessage(*ibuffer, parse_message,
                                              response_renderer, true, false));
        headerCheck(parse_message, default_qid, Rcode::NOTIMP(), i, QR_FLAG,
                    0, 0, 0, 0);
    }
}

// Multiple questions.  Should result in FORMERR.
TEST_F(AuthSrvTest, multiQuestion) {
    createDataFromFile("testdata/multiquestion_fromWire");
    EXPECT_EQ(true, server.processMessage(*ibuffer, parse_message,
                                          response_renderer, true, false));
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
    createDataFromFile("testdata/shortmessage_fromWire");
    EXPECT_EQ(false, server.processMessage(*ibuffer, parse_message,
                                           response_renderer, true, false));
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
TEST_F(AuthSrvTest, response) {
    // A valid (although unusual) response
    createDataFromFile("testdata/simpleresponse_fromWire");
    EXPECT_EQ(false, server.processMessage(*ibuffer, parse_message,
                                           response_renderer, true, false));

    // A response with a broken question section.  must be dropped rather than
    // returning FORMERR.
    createDataFromFile("testdata/shortresponse_fromWire");
    EXPECT_EQ(false, server.processMessage(*ibuffer, parse_message,
                                           response_renderer, true, false));    

    // A response to iquery.  must be dropped rather than returning NOTIMP.
    createDataFromFile("testdata/iqueryresponse_fromWire");
    EXPECT_EQ(false, server.processMessage(*ibuffer, parse_message,
                                           response_renderer, true, false));    

}

}
