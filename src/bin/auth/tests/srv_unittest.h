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

// $Id: auth_srv_unittest.cc 3310 2010-10-21 23:10:24Z each $

namespace {

// Unsupported requests.  Should result in NOTIMP.
#define UNSUPPORTED_REQUEST_TEST \
    for (unsigned int i = 0; i < 16; ++i) { \
        /* set Opcode to 'i', which iterators over all possible codes except \
           the standard query and notify */ \
        if (i == Opcode::QUERY().getCode() || \
            i == Opcode::NOTIFY().getCode()) { \
            continue; \
        } \
        createDataFromFile("simplequery_fromWire"); \
        data[2] = ((i << 3) & 0xff); \
 \
        parse_message->clear(Message::PARSE); \
        server.processMessage(*io_message, parse_message, response_obuffer, \
                              &dnsserv); \
        EXPECT_TRUE(dnsserv.hasAnswer()); \
        headerCheck(*parse_message, default_qid, Rcode::NOTIMP(), i, QR_FLAG, \
                    0, 0, 0, 0); \
    }

// Simple API check
#define VERBOSE_TEST \
    EXPECT_FALSE(server.getVerbose()); \
    server.setVerbose(true); \
    EXPECT_TRUE(server.getVerbose()); \
    server.setVerbose(false); \
    EXPECT_FALSE(server.getVerbose()); \


// Multiple questions.  Should result in FORMERR.
#define MULTI_QUESTION_TEST \
    createDataFromFile("multiquestion_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_TRUE(dnsserv.hasAnswer()); \
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(), \
                QR_FLAG, 2, 0, 0, 0); \
 \
    QuestionIterator qit = parse_message->beginQuestion(); \
    EXPECT_EQ(Name("example.com"), (*qit)->getName()); \
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass()); \
    EXPECT_EQ(RRType::A(), (*qit)->getType()); \
    ++qit; \
    EXPECT_EQ(Name("example.com"), (*qit)->getName()); \
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass()); \
    EXPECT_EQ(RRType::AAAA(), (*qit)->getType()); \
    ++qit; \
    EXPECT_TRUE(qit == parse_message->endQuestion());

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
#define SHORT_MESSAGE_TEST \
    createDataFromFile("shortmessage_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_FALSE(dnsserv.hasAnswer());

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
#define RESPONSE_TEST \
    /* A valid (although unusual) response */\
    createDataFromFile("simpleresponse_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_FALSE(dnsserv.hasAnswer()); \
 \
    /* A response with a broken question section.  must be dropped rather than \
       returning FORMERR. */\
    createDataFromFile("shortresponse_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_FALSE(dnsserv.hasAnswer()); \
 \
    /* A response to iquery.  must be dropped rather than returning NOTIMP. */\
    createDataFromFile("iqueryresponse_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_FALSE(dnsserv.hasAnswer());

// Query with a broken question
#define SHORT_QUESTION_TEST \
    createDataFromFile("shortquestion_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_TRUE(dnsserv.hasAnswer()); \
    /* Since the query's question is broken, the question section of the \
       response should be empty. */\
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(), \
                QR_FLAG, 0, 0, 0, 0);

// Query with a broken answer section
#define SHORT_ANSWER_TEST \
    createDataFromFile("shortanswer_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_TRUE(dnsserv.hasAnswer()); \
 \
    /* This is a bogus query, but question section is valid.  So the response \
       should copy the question section. */ \
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(), \
                QR_FLAG, 1, 0, 0, 0); \
 \
    QuestionIterator qit = parse_message->beginQuestion(); \
    EXPECT_EQ(Name("example.com"), (*qit)->getName()); \
    EXPECT_EQ(RRClass::IN(), (*qit)->getClass()); \
    EXPECT_EQ(RRType::A(), (*qit)->getType()); \
    ++qit; \
    EXPECT_TRUE(qit == parse_message->endQuestion());

// Query with unsupported version of EDNS.
#define EDNS_BADVERS_TEST \
    createDataFromFile("queryBadEDNS_fromWire"); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_TRUE(dnsserv.hasAnswer()); \
 \
    /* The response must have an EDNS OPT RR in the additional section. \
       Note that the DNSSEC DO bit is cleared even if this bit in the query \
       is set.  This is a limitation of the current implementation. */ \
    headerCheck(*parse_message, default_qid, Rcode::BADVERS(), opcode.getCode(), \
                QR_FLAG, 1, 0, 0, 1); \
    EXPECT_EQ(4096, parse_message->getUDPSize()); \
    EXPECT_FALSE(parse_message->isDNSSECSupported());

#define AXFR_OVER_UDP_TEST \
    /* AXFR over UDP is invalid and should result in FORMERR. */\
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid, \
                         Name("example.com"), RRClass::IN(), \
                         RRType::AXFR()); \
    createRequestPacket(request_message, IPPROTO_UDP); \
    server.processMessage(*io_message, parse_message, response_obuffer, &dnsserv); \
    EXPECT_TRUE(dnsserv.hasAnswer()); \
    headerCheck(*parse_message, default_qid, Rcode::FORMERR(), opcode.getCode(), \
                QR_FLAG, 1, 0, 0, 0);

}

