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

#include <config.h>

#include <gtest/gtest.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cc/data.h>
#include <cc/session.h>

#include <xfr/xfrout_client.h>

#include <auth/auth_srv.h>
#include <asiolink/asiolink.h>

#include <dns/tests/unittest_util.h>
#include "mockups.h"

using namespace std;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::xfr;
using namespace asiolink;
using isc::UnitTestUtil;

namespace {
const char* const DEFAULT_REMOTE_ADDRESS = "192.0.2.1";

// The base class for Auth and Recurse test case
class SrvTestBase : public ::testing::Test {
protected:
    SrvTestBase() : request_message(Message::RENDER),
                    parse_message(new Message(Message::PARSE)),
                    default_qid(0x1035), opcode(Opcode(Opcode::QUERY())),
                    qname("www.example.com"), qclass(RRClass::IN()),
                    qtype(RRType::A()), io_sock(NULL), 
                    io_message(NULL), endpoint(NULL),
                    request_obuffer(0), request_renderer(request_obuffer),
                    response_obuffer(new OutputBuffer(0))
    {}
    ~SrvTestBase() {
        delete io_message;
        delete endpoint;
    }
    MockSession notify_session;
    MockServer dnsserv;
    Message request_message;
    MessagePtr parse_message;
    const qid_t default_qid;
    const Opcode opcode;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    IOSocket* io_sock;
    IOMessage* io_message;
    const IOEndpoint* endpoint;
    OutputBuffer request_obuffer;
    MessageRenderer request_renderer;
    OutputBufferPtr response_obuffer;
    vector<uint8_t> data;

    void createDataFromFile(const char* const datafile, int protocol);
    void createRequestPacket(Message& message, const int protocol);
};

void
SrvTestBase::createDataFromFile(const char* const datafile,
                                const int protocol = IPPROTO_UDP)
{
    delete io_message;
    data.clear();

    delete endpoint;

    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    UnitTestUtil::readWireData(datafile, data);
    io_sock = (protocol == IPPROTO_UDP) ? &IOSocket::getDummyUDPSocket() :
        &IOSocket::getDummyTCPSocket();
    io_message = new IOMessage(&data[0], data.size(), *io_sock, *endpoint);
}

void
SrvTestBase::createRequestPacket(Message& message,
                                 const int protocol = IPPROTO_UDP)
{
    message.toWire(request_renderer);

    delete io_message;

    endpoint = IOEndpoint::create(protocol,
                                  IOAddress(DEFAULT_REMOTE_ADDRESS), 5300);
    io_sock = (protocol == IPPROTO_UDP) ? &IOSocket::getDummyUDPSocket() :
        &IOSocket::getDummyTCPSocket();
    io_message = new IOMessage(request_renderer.getData(),
                               request_renderer.getLength(),
                               *io_sock, *endpoint);
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
headerCheck(const Message& message, const qid_t qid, const Rcode& rcode,
            const uint16_t opcodeval, const unsigned int flags,
            const unsigned int qdcount,
            const unsigned int ancount, const unsigned int nscount,
            const unsigned int arcount)
{
    EXPECT_EQ(qid, message.getQid());
    EXPECT_EQ(rcode, message.getRcode());
    EXPECT_EQ(opcodeval, message.getOpcode().getCode());
    EXPECT_EQ((flags & QR_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_EQ((flags & AA_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ((flags & TC_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_TC));
    EXPECT_EQ((flags & RA_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_RA));
    EXPECT_EQ((flags & RD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_EQ((flags & AD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_AD));
    EXPECT_EQ((flags & CD_FLAG) != 0,
              message.getHeaderFlag(Message::HEADERFLAG_CD));

    EXPECT_EQ(qdcount, message.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(ancount, message.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(nscount, message.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(arcount, message.getRRCount(Message::SECTION_ADDITIONAL));
}

}
