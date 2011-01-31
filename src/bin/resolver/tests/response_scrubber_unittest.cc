// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <asio.hpp>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/question.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <resolver/response_scrubber.h>

using namespace asio::ip;
using namespace isc::dns;
using namespace rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::dns::rdata::in;

namespace {
class ResponseScrubberTest : public ::testing::Test {
public:
    ResponseScrubberTest() :
        bailiwick("example.com"),
        qu_in_any_www(Name("www.example.com"), RRClass::IN(), RRType::ANY()),
        qu_in_a_www(Name("www.example.com"), RRClass::IN(), RRType::A()),
        qu_in_ns(Name("example.com"), RRClass::IN(), RRType::NS()),
        qu_in_txt_www(Name("www.example.com"), RRClass::IN(), RRType::TXT()),
        rrs_in_a_org(new RRset(Name("mail.example.org"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_a_net(new RRset(Name("mail.example.net"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_a_www(new RRset(Name("www.example.com"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_ns(new RRset(Name("example.com"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_ns_com(new RRset(Name("com"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_ns_net(new RRset(Name("example.net"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_ns_sub(new RRset(Name("subdomain.example.com"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_a_ns0(new RRset(Name("ns0.example.com"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_a_ns1(new RRset(Name("ns1.com"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_a_ns2(new RRset(Name("ns2.example.net"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_a_ns3(new RRset(Name("ns3.subdomain.example.com"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_txt_www(new RRset(Name("www.example.com"), RRClass::IN(),
            RRType::TXT(), RRTTL(300)))
    {}
    Name        bailiwick;          // Bailiwick of the server queried
    Question    qu_in_any_www;      // www.example.com IN ANY
    Question    qu_in_a_www;        // www.example.com IN A
    Question    qu_in_ns;           // example.com IN NS
    Question    qu_in_txt_www;      // www.example.com IN TXT
    RRsetPtr    rrs_in_a_org;       // mail.example.org IN A
    RRsetPtr    rrs_in_a_net;       // mail.example.org IN A
    RRsetPtr    rrs_in_a_www;       // www.example.com IN A
    RRsetPtr    rrs_in_ns;          // example.com IN NS
    RRsetPtr    rrs_in_ns_com;      // com IN NS
    RRsetPtr    rrs_in_ns_net;      // example.net IN NS
    RRsetPtr    rrs_in_ns_sub;      // subdomain.example.com IN NS
    RRsetPtr    rrs_in_a_ns0;       // ns0.example.com IN A
    RRsetPtr    rrs_in_a_ns1;       // ns1.com IN A
    RRsetPtr    rrs_in_a_ns2;       // ns2.example.net IN A
    RRsetPtr    rrs_in_a_ns3;       // ns3.subdomain.example.net IN A
    RRsetPtr    rrs_in_txt_www;     // www.example.com IN TXT
};


// Check that the IP addresses/ports/protocol for the packets sent and received
// both match if both types are IP V4.

TEST_F(ResponseScrubberTest, UDPv4) {

    // Basic UDP Endpoint
    udp::endpoint   udp_a;
    udp_a.address(address_v4::from_string("192.0.2.1"));
    udp_a.port(12345);

    // Same address and port
    udp::endpoint   udp_b;
    udp_b.address(address_v4::from_string("192.0.2.1"));
    udp_b.port(12345);
    ASSERT_EQ(ResponseScrubber::SUCCESS,
        ResponseScrubber::addressPortCheck(udp_a, udp_b));

    // Different address, same port
    udp::endpoint   udp_c;
    udp_c.address(address_v4::from_string("192.0.2.2"));
    udp_c.port(12345);
    ASSERT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressPortCheck(udp_a, udp_c));

    // Same address, different port
    udp::endpoint   udp_d;
    udp_d.address(address_v4::from_string("192.0.2.1"));
    udp_d.port(12346);
    ASSERT_EQ(ResponseScrubber::PORT,
        ResponseScrubber::addressPortCheck(udp_a, udp_d));

    // Different address, different port
    udp::endpoint   udp_e;
    udp_e.address(address_v4::from_string("192.0.2.3"));
    udp_e.port(12347);
    ASSERT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressPortCheck(udp_a, udp_e));

}

// Repeat the tests for IPv6

TEST_F(ResponseScrubberTest, UDPv6) {

    // Basic UDP Endpoint
    udp::endpoint   udp_a;
    udp_a.address(address_v6::from_string("2001:db8::1"));
    udp_a.port(12345);

    // Same address and port
    udp::endpoint   udp_b;
    udp_b.address(address_v6::from_string("2001:db8::1"));
    udp_b.port(12345);
    ASSERT_EQ(ResponseScrubber::SUCCESS,
        ResponseScrubber::addressPortCheck(udp_a, udp_b));

    // Different address, same port
    udp::endpoint   udp_c;
    udp_c.address(address_v6::from_string("2001:db8::2"));
    udp_c.port(12345);
    ASSERT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressPortCheck(udp_a, udp_c));

    // Same address, different port
    udp::endpoint   udp_d;
    udp_d.address(address_v6::from_string("2001:db8::1"));
    udp_d.port(12346);
    ASSERT_EQ(ResponseScrubber::PORT,
        ResponseScrubber::addressPortCheck(udp_a, udp_d));

    // Different address, different port
    udp::endpoint   udp_e;
    udp_e.address(address_v6::from_string("2001:db8::3"));
    udp_e.port(12347);
    ASSERT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressPortCheck(udp_a, udp_e));

}

// Ensure that mixed IPv4/6 addresses don't match.

TEST_F(ResponseScrubberTest, UDPv4v6) {

    // Basic UDP Endpoint
    udp::endpoint   udp_a;
    udp_a.address(address_v4::from_string("192.0.2.1"));
    udp_a.port(12345);

    // Same address and port
    udp::endpoint   udp_b;
    udp_b.address(address_v6::from_string("2001:db8::1"));
    udp_b.port(12345);
    ASSERT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressPortCheck(udp_a, udp_b));
}

// Check that the QIDs check OK

TEST_F(ResponseScrubberTest, Qid) {
    Message a(Message::RENDER);
    a.setQid(27);

    Message b(Message::RENDER);
    b.setQid(27);
    EXPECT_TRUE(ResponseScrubber::qidCheck(a, b));

    Message c(Message::RENDER);
    c.setQid(28);
    EXPECT_FALSE(ResponseScrubber::qidCheck(a, c));
}

// Check the scrub() method. As this operates by calling the scrubSection()
// method, this is also a check of the latter.

TEST_F(ResponseScrubberTest, ValidMessage) {
    Message valid(Message::RENDER);

    // Valid message with nothing out of bailiwick
    valid.addQuestion(qu_in_a_www);
    valid.addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    valid.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns);
    valid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns0);

    // Scrub the message and expect nothing to have been removed.
    int removed = ResponseScrubber::scrub(bailiwick, valid);
    EXPECT_EQ(0, removed);

    // ... and check that this is the case
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ANSWER,
        rrs_in_a_www->getName(), rrs_in_a_www->getClass(), rrs_in_a_www->getType()));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_AUTHORITY,
        rrs_in_ns->getName(), rrs_in_ns->getClass(), rrs_in_ns->getType()));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns0->getName(), rrs_in_a_ns0->getClass(), rrs_in_a_ns0->getType()));

    // Add out-of-bailiwick glue to the additional section (pretend that the
    // NS RRset contained an out-of-domain server.
    valid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2);
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns2->getName(), rrs_in_a_ns2->getClass(), rrs_in_a_ns2->getType()));

    // ... and check that it is removed when scrubbed
    removed = ResponseScrubber::scrub(bailiwick, valid);
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ANSWER,
        rrs_in_a_www->getName(), rrs_in_a_www->getClass(), rrs_in_a_www->getType()));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_AUTHORITY,
        rrs_in_ns->getName(), rrs_in_ns->getClass(), rrs_in_ns->getType()));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns0->getName(), rrs_in_a_ns0->getClass(), rrs_in_a_ns0->getType()));
    EXPECT_FALSE(valid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns2->getName(), rrs_in_a_ns2->getClass(), rrs_in_a_ns2->getType()));
}

TEST_F(ResponseScrubberTest, InvalidMessage) {
    Message invalid(Message::RENDER);

    // Invalid message, with various things in and out of bailiwick.

    invalid.addQuestion(qu_in_a_www);

    // Answer section
    //
    // rrs_in_a_www - "www.example.com A", in bailiwick
    // rrs_in_txt_www - "www.example.com TXT", in bailiwick
    // rrs_in_a_org - "mail.example.org A", out of bailiwick - the qname is
    //     related to the bailiwick name by having a common ancestor at the root
    // rrs_in_a_net - "mail.example.net A", out of bailiwick - the qname is
    //     related to the bailiwick name by having a common ancestor at the root
    invalid.addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    invalid.addRRset(Message::SECTION_ANSWER, rrs_in_txt_www);
    invalid.addRRset(Message::SECTION_ANSWER, rrs_in_a_org);
    invalid.addRRset(Message::SECTION_ANSWER, rrs_in_a_net);

    // Authority section
    //
    // rrs_in_ns - "example.com NS", in bailiwick (qname is bailiwick name)
    // rrs_in_ns_com - "com NS", out of bailiwick as the qname is a superdomain
    //     (direct ancestor) of the bailiwick name
    // rrs_in_ns_net - "example.net NS", out of bailiwick - the qname is related
    //     to the bailiwick name by having a common ancestor at the root
    // rrs_in_ns_sub - "subdomain.example.com", in bailiwick as the qname is
    //     a subdomain of the bailiwick name
    invalid.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns);
    invalid.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_com);
    invalid.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_net);
    invalid.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub);

    // Additional section
    //
    // rrs_in_a_ns0 - "ns0.example.com", in bailiwick because the qname is
    //     a subdomain of the bailiwick name
    // rrs_in_a_ns1 - "ns1.com", out of bailiwick because the qname is a
    //     sibling to the bailiwick name
    // rrs_in_a_ns2 - "ns2.example.net", out of bailiwick because qname is
    //     related by having a common ancestor and the root.
    // rrs_in_a_ns3 - "ns3.subdomain.example.com", in bailiwick because the
    //     qname is a direct descendent of the bailiwick name.
    invalid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns0);
    invalid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns1);
    invalid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2);
    invalid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3);

    // Scrub the message
    int removed = ResponseScrubber::scrub(bailiwick, invalid);
    EXPECT_EQ(6, removed);

    // ... and check the sections.  Answer...
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ANSWER,
        rrs_in_a_www->getName(), rrs_in_a_www->getClass(), rrs_in_a_www->getType()));
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ANSWER,
        rrs_in_txt_www->getName(), rrs_in_txt_www->getClass(), rrs_in_txt_www->getType()));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ANSWER,
        rrs_in_a_org->getName(), rrs_in_a_org->getClass(), rrs_in_a_org->getType()));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ANSWER,
        rrs_in_a_net->getName(), rrs_in_a_net->getClass(), rrs_in_a_net->getType()));

    // ... authority...
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_AUTHORITY,
        rrs_in_ns->getName(), rrs_in_ns->getClass(), rrs_in_ns->getType()));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_AUTHORITY,
        rrs_in_ns_com->getName(), rrs_in_ns_com->getClass(), rrs_in_ns_com->getType()));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_AUTHORITY,
        rrs_in_ns_net->getName(), rrs_in_ns_net->getClass(), rrs_in_ns_net->getType()));
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_AUTHORITY,
        rrs_in_ns_sub->getName(), rrs_in_ns_sub->getClass(), rrs_in_ns_sub->getType()));

    // ... additional.
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns0->getName(), rrs_in_a_ns0->getClass(), rrs_in_a_ns0->getType()));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns1->getName(), rrs_in_a_ns1->getClass(), rrs_in_a_ns1->getType()));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns2->getName(), rrs_in_a_ns2->getClass(), rrs_in_a_ns2->getType()));
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ADDITIONAL,
        rrs_in_a_ns3->getName(), rrs_in_a_ns3->getClass(), rrs_in_a_ns3->getType()));
}

// Finally, an empty message

TEST_F(ResponseScrubberTest, EmptyMessage) {
    Message empty(Message::RENDER);

    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ADDITIONAL));

    int removed = ResponseScrubber::scrub(bailiwick, empty);
    EXPECT_EQ(0, removed);

    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ADDITIONAL));

}

} // Anonymous namespace