// Copyright (C) 2010, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_TESTUTILS_EXPORT

#include <config.h>

#include <sys/types.h>
#include <netinet/in.h>

#include <dns/message.h>
#include <dns/rcode.h>

#include <asiolink/asiolink.h>

#include <dns/tests/unittest_util.h>

#include <testutils/dnsmessage_test.h>
#include <testutils/srv_test.h>

#include <boost/scoped_ptr.hpp>

using namespace isc::dns;
using namespace isc::util;
using namespace isc::asiolink;

namespace isc {
namespace testutils {
const KEA_TESTUTILS_DATA_API char* const DEFAULT_REMOTE_ADDRESS = "192.0.2.1";
const KEA_TESTUTILS_DATA_API uint16_t DEFAULT_REMOTE_PORT = 53210;

SrvTestBase::SrvTestBase() : request_message(Message::RENDER),
                             parse_message(new Message(Message::PARSE)),
                             response_message(new Message(Message::RENDER)),
                             default_qid(0x1035),
                             opcode(Opcode(Opcode::QUERY())),
                             qname("www.example.com"),
                             qclass(RRClass::IN()),
                             qtype(RRType::A()), io_sock(NULL),
                             io_message(NULL), endpoint(NULL),
                             response_obuffer(new OutputBuffer(0))
{}

void
SrvTestBase::createDataFromFile(const char* const datafile,
                                const int protocol)
{
    data.clear();

    endpoint.reset(IOEndpoint::create(protocol,
                                      IOAddress(DEFAULT_REMOTE_ADDRESS),
                                      DEFAULT_REMOTE_PORT));
    UnitTestUtil::readWireData(datafile, data);
    io_sock = (protocol == IPPROTO_UDP) ? &IOSocket::getDummyUDPSocket() :
        &IOSocket::getDummyTCPSocket();
    io_message.reset(new IOMessage(&data[0], data.size(), *io_sock,
                                   *endpoint));
}

void
SrvTestBase::createRequestPacket(Message& message,
                                 const int protocol, TSIGContext* context,
                                 const char* const remote_address,
                                 uint16_t remote_port)
{
    message.toWire(request_renderer, context);
    endpoint.reset(IOEndpoint::create(protocol, IOAddress(remote_address),
                                      remote_port));
    io_sock = (protocol == IPPROTO_UDP) ? &IOSocket::getDummyUDPSocket() :
        &IOSocket::getDummyTCPSocket();

    io_message.reset(new IOMessage(request_renderer.getData(),
                                   request_renderer.getLength(),
                                   *io_sock, *endpoint));
}

// Unsupported requests.  Should result in NOTIMP.
void
SrvTestBase::unsupportedRequest() {
    for (unsigned int i = 0; i < 16; ++i) {
        // set Opcode to 'i', which iterators over all possible codes except
        // the standard opcodes we support.
        if (i == isc::dns::Opcode::QUERY().getCode() ||
            i == isc::dns::Opcode::NOTIFY().getCode() ||
            i == isc::dns::Opcode::UPDATE().getCode()) {
            continue;
        }
        createDataFromFile("simplequery_fromWire.wire");
        data[2] = ((i << 3) & 0xff);

        parse_message->clear(isc::dns::Message::PARSE);
        processMessage();
        EXPECT_TRUE(dnsserv.hasAnswer());
        headerCheck(*parse_message, default_qid, isc::dns::Rcode::NOTIMP(), i,
                    QR_FLAG, 0, 0, 0, 0);
    }
}

// Multiple questions.  Should result in FORMERR.
void
SrvTestBase::multiQuestion() {
    createDataFromFile("multiquestion_fromWire.wire");
    processMessage();
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, isc::dns::Rcode::FORMERR(),
                opcode.getCode(), QR_FLAG, 2, 0, 0, 0);

    isc::dns::QuestionIterator qit = parse_message->beginQuestion();
    EXPECT_EQ(isc::dns::Name("example.com"), (*qit)->getName());
    EXPECT_EQ(isc::dns::RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(isc::dns::RRType::A(), (*qit)->getType());
    ++qit;
    EXPECT_EQ(isc::dns::Name("example.com"), (*qit)->getName());
    EXPECT_EQ(isc::dns::RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(isc::dns::RRType::AAAA(), (*qit)->getType());
    ++qit;
    EXPECT_TRUE(qit == parse_message->endQuestion());
}

// Incoming data doesn't even contain the complete header.  Must be silently
// dropped.
void
SrvTestBase::shortMessage() {
    createDataFromFile("shortmessage_fromWire");
    processMessage();
    EXPECT_FALSE(dnsserv.hasAnswer());
}

// Response messages.  Must be silently dropped, whether it's a valid response
// or malformed or could otherwise cause a protocol error.
void
SrvTestBase::response() {
    // A valid (although unusual) response
    createDataFromFile("simpleresponse_fromWire.wire");
    processMessage();
    EXPECT_FALSE(dnsserv.hasAnswer());

    // A response with a broken question section.  must be dropped rather than
    //returning FORMERR.
    createDataFromFile("shortresponse_fromWire");
    processMessage();
    EXPECT_FALSE(dnsserv.hasAnswer());

    // A response to iquery.  must be dropped rather than returning NOTIMP.
    createDataFromFile("iqueryresponse_fromWire.wire");
    processMessage();
    EXPECT_FALSE(dnsserv.hasAnswer());
}

// Query with a broken question
void
SrvTestBase::shortQuestion() {
    createDataFromFile("shortquestion_fromWire");
    processMessage();
    EXPECT_TRUE(dnsserv.hasAnswer());
    // Since the query's question is broken, the question section of the
    // response should be empty.
    headerCheck(*parse_message, default_qid, isc::dns::Rcode::FORMERR(),
                opcode.getCode(), QR_FLAG, 0, 0, 0, 0);
}

// Query with a broken answer section
void
SrvTestBase::shortAnswer() {
    createDataFromFile("shortanswer_fromWire.wire");
    processMessage();
    EXPECT_TRUE(dnsserv.hasAnswer());

    // This is a bogus query, but question section is valid.  So the response
    // should copy the question section.
    headerCheck(*parse_message, default_qid, isc::dns::Rcode::FORMERR(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);

    isc::dns::QuestionIterator qit = parse_message->beginQuestion();
    EXPECT_EQ(isc::dns::Name("example.com"), (*qit)->getName());
    EXPECT_EQ(isc::dns::RRClass::IN(), (*qit)->getClass());
    EXPECT_EQ(isc::dns::RRType::A(), (*qit)->getType());
    ++qit;
    EXPECT_TRUE(qit == parse_message->endQuestion());
}

// Query with unsupported version of EDNS.
void
SrvTestBase::ednsBadVers() {
    createDataFromFile("queryBadEDNS_fromWire.wire");
    processMessage();
    EXPECT_TRUE(dnsserv.hasAnswer());

    // The response must have an EDNS OPT RR in the additional section,
    // it will be added automatically at the render time.
    // Note that the DNSSEC DO bit is cleared even if this bit in the query
    // is set.  This is a limitation of the current implementation.
    headerCheck(*parse_message, default_qid, isc::dns::Rcode::BADVERS(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 1);
    EXPECT_FALSE(parse_message->getEDNS()); // EDNS isn't added at this point

    InputBuffer ib(response_obuffer->getData(),
                             response_obuffer->getLength());
    isc::dns::Message parsed(isc::dns::Message::PARSE);
    parsed.fromWire(ib);
    EXPECT_EQ(isc::dns::Rcode::BADVERS(), parsed.getRcode());
    isc::dns::ConstEDNSPtr edns(parsed.getEDNS());
    ASSERT_TRUE(edns);
    EXPECT_FALSE(edns->getDNSSECAwareness());
}

void
SrvTestBase::axfrOverUDP() {
    // AXFR over UDP is invalid and should result in FORMERR.
    UnitTestUtil::createRequestMessage(request_message, opcode, default_qid,
                                       isc::dns::Name("example.com"),
                                       isc::dns::RRClass::IN(),
                                       isc::dns::RRType::AXFR());
    createRequestPacket(request_message, IPPROTO_UDP);
    processMessage();
    EXPECT_TRUE(dnsserv.hasAnswer());
    headerCheck(*parse_message, default_qid, isc::dns::Rcode::FORMERR(),
                opcode.getCode(), QR_FLAG, 1, 0, 0, 0);
}
} // end of namespace testutils
} // end of namespace isc


// Local Variables:
// mode: c++
// End:
