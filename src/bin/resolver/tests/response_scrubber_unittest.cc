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

#include <config.h>

#include <string>
#include <iostream>

#include <gtest/gtest.h>

#include <asiolink/io_endpoint.h>
#include <asiolink/io_address.h>
#include <netinet/in.h>

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


// Class for endpoint checks.  The family of the endpoint is set in the
// constructor; the address family by the string provided for the address.

namespace isc {
namespace asiolink {

class GenericEndpoint : public IOEndpoint {
public:
    GenericEndpoint(const std::string& address, uint16_t port, short protocol) :
        address_(address), port_(port), protocol_(protocol)
    {}
    virtual ~GenericEndpoint()
    {}

    virtual IOAddress getAddress() const {
        return address_;
    }

    virtual uint16_t getPort() const {
        return port_;
    }

    virtual short getProtocol() const {
        return protocol_;
    }

    virtual short getFamily() const {
        return address_.getFamily();
    }

    // This is completely dummy and unused.  Define it just for build.
    virtual const struct sockaddr& getSockAddr() const {
        static struct sockaddr sa;
        return (sa);
    }

private:
    IOAddress   address_;        // Address of endpoint
    uint16_t    port_;          // Port number of endpoint
    short       protocol_;      // Protocol of the endpoint
    };
}
}

using namespace asio::ip;
using namespace isc::dns;
using namespace rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::dns::rdata::in;
using namespace isc::asiolink;

// Test class

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
        rrs_in_cname_www(new RRset(Name("www.example.com"), RRClass::IN(),
            RRType::CNAME(), RRTTL(300))),
        rrs_in_a_wwwnet(new RRset(Name("www.example.net"), RRClass::IN(),
            RRType::A(), RRTTL(300))),
        rrs_in_ns(new RRset(Name("example.com"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_ns_com(new RRset(Name("com"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_ns_net(new RRset(Name("example.net"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_ns_sub(new RRset(Name("subdomain.example.com"), RRClass::IN(),
            RRType::NS(), RRTTL(300))),
        rrs_in_ns_sub2(new RRset(Name("subdomain2.example.com"), RRClass::IN(),
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
    RRsetPtr    rrs_in_cname_www;   // www.example.com IN CNAME
    RRsetPtr    rrs_in_a_wwwnet;    // www.example.net IN A
    RRsetPtr    rrs_in_ns;          // example.com IN NS
    RRsetPtr    rrs_in_ns_com;      // com IN NS
    RRsetPtr    rrs_in_ns_net;      // example.net IN NS
    RRsetPtr    rrs_in_ns_sub;      // subdomain.example.com IN NS
    RRsetPtr    rrs_in_ns_sub2;     // subdomain2.example.com IN NS
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
    GenericEndpoint udp_a("192.0.2.1", 12345, IPPROTO_UDP);

    // Same address, port
    GenericEndpoint udp_b("192.0.2.1", 12345, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::SUCCESS,
        ResponseScrubber::addressCheck(udp_a, udp_b));

    // Different address, same port
    GenericEndpoint udp_c("192.0.2.2", 12345, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(udp_a, udp_c));

    // Same address, different port
    GenericEndpoint udp_d("192.0.2.1", 12346, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::PORT,
        ResponseScrubber::addressCheck(udp_a, udp_d));

    // Different address, different port
    GenericEndpoint udp_e("192.0.2.3", 12347, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(udp_a, udp_e));

}

// Repeat the tests for TCP

TEST_F(ResponseScrubberTest, TCPv4) {

    // Basic TCP Endpoint
    GenericEndpoint tcp_a("192.0.2.1", 12345, IPPROTO_TCP);

    // Same address, port
    GenericEndpoint tcp_b("192.0.2.1", 12345, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::SUCCESS,
        ResponseScrubber::addressCheck(tcp_a, tcp_b));

    // Different address, same port
    GenericEndpoint tcp_c("192.0.2.2", 12345, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(tcp_a, tcp_c));

    // Same address, different port
    GenericEndpoint tcp_d("192.0.2.1", 12346, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::PORT,
        ResponseScrubber::addressCheck(tcp_a, tcp_d));

    // Different address, different port
    GenericEndpoint tcp_e("192.0.2.3", 12347, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(tcp_a, tcp_e));

}

// Repeat the tests for UDP/IPv6

TEST_F(ResponseScrubberTest, UDPv6) {

    // Basic UDP Endpoint
    GenericEndpoint  udp_a("2001:db8::1", 12345, IPPROTO_UDP);

    // Same address and port
    GenericEndpoint  udp_b("2001:db8::1", 12345, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::SUCCESS,
        ResponseScrubber::addressCheck(udp_a, udp_b));

    // Different address, same port
    GenericEndpoint  udp_c("2001:db8::3", 12345, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(udp_a, udp_c));

    // Same address, different port
    GenericEndpoint  udp_d("2001:db8::1", 12346, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::PORT,
        ResponseScrubber::addressCheck(udp_a, udp_d));

    // Different address, different port
    GenericEndpoint  udp_e("2001:db8::3", 12347, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(udp_a, udp_e));

}

// Same again for TCP/IPv6

TEST_F(ResponseScrubberTest, TCPv6) {

    // Basic TCP Endpoint
    GenericEndpoint  tcp_a("2001:db8::1", 12345, IPPROTO_TCP);

    // Same address and port
    GenericEndpoint  tcp_b("2001:db8::1", 12345, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::SUCCESS,
        ResponseScrubber::addressCheck(tcp_a, tcp_b));

    // Different address, same port
    GenericEndpoint  tcp_c("2001:db8::3", 12345, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(tcp_a, tcp_c));

    // Same address, different port
    GenericEndpoint  tcp_d("2001:db8::1", 12346, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::PORT,
        ResponseScrubber::addressCheck(tcp_a, tcp_d));

    // Different address, different port
    GenericEndpoint  tcp_e("2001:db8::3", 12347, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(tcp_a, tcp_e));

}

// Ensure that mixed IPv4/6 addresses don't match.

TEST_F(ResponseScrubberTest, v4v6) {

    // UDP
    GenericEndpoint  udp_a("2001:db8::1", 12345, IPPROTO_UDP);
    GenericEndpoint  udp_b("192.0.2.1", 12345, IPPROTO_UDP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(udp_a, udp_b));

    // TCP
    GenericEndpoint  tcp_a("2001:db8::1", 12345, IPPROTO_TCP);
    GenericEndpoint  tcp_b("192.0.2.1", 12345, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::ADDRESS,
        ResponseScrubber::addressCheck(udp_a, udp_b));
}

// Check mixed protocols are detected

TEST_F(ResponseScrubberTest, Protocol) {
    GenericEndpoint  udp_a("2001:db8::1", 12345, IPPROTO_UDP);
    GenericEndpoint  tcp_a("2001:db8::1", 12345, IPPROTO_TCP);
    EXPECT_EQ(ResponseScrubber::PROTOCOL,
        ResponseScrubber::addressCheck(udp_a, tcp_a));
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

// Check the scrubAllSections() method. As this operates by calling the
// scrubSection() method (with a SUBDOMAIN argument), this is also a check of
// the latter.

TEST_F(ResponseScrubberTest, ScrubAllSectionsValid) {
    Message valid(Message::RENDER);

    // Valid message with nothing out of bailiwick
    valid.addQuestion(qu_in_a_www);
    valid.addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    valid.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns);
    valid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns0);

    // Scrub the message and expect nothing to have been removed.
    int removed = ResponseScrubber::scrubAllSections(valid, bailiwick);
    EXPECT_EQ(0, removed);

    // ... and check that this is the case
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ANSWER, rrs_in_a_www));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns0));

    // Add out-of-bailiwick glue to the additional section (pretend that the
    // NS RRset contained an out-of-domain server.
    valid.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2);
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2));

    // ... and check that it is removed when scrubbed
    removed = ResponseScrubber::scrubAllSections(valid, bailiwick);
    EXPECT_EQ(1, removed);
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ANSWER, rrs_in_a_www));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns));
    EXPECT_TRUE(valid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns0));
    EXPECT_FALSE(valid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2));
 }

TEST_F(ResponseScrubberTest, ScrubAllSectionsInvalid) {
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
    int removed = ResponseScrubber::scrubAllSections(invalid, bailiwick);
    EXPECT_EQ(6, removed);

    // ... and check the sections.  Answer...
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ANSWER, rrs_in_a_www));
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ANSWER, rrs_in_txt_www));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ANSWER, rrs_in_a_org));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ANSWER, rrs_in_a_net));

    // ... authority...
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_com));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_net));
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub));

    // ... additional.
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns0));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns1));
    EXPECT_FALSE(invalid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2));
    EXPECT_TRUE(invalid.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3));
}

// An empty message

TEST_F(ResponseScrubberTest, ScrubAllSectionsEmpty) {
    Message empty(Message::RENDER);

    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ADDITIONAL));

    int removed = ResponseScrubber::scrubAllSections(empty, bailiwick);
    EXPECT_EQ(0, removed);

    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, empty.getRRCount(Message::SECTION_ADDITIONAL));

}

// Check the cross-section scrubbing (checks the general scrubSection()
// method with a SUPERDOMAIN argument.)

// Empty message (apart from question)

TEST_F(ResponseScrubberTest, CrossSectionEmpty) {

    Message message1(Message::RENDER);
    message1.addQuestion(qu_in_a_www);
    int removed = ResponseScrubber::scrubCrossSections(message1);
    EXPECT_EQ(0, removed);
}

// Valid answer section

TEST_F(ResponseScrubberTest, CrossSectionAnswer) {

    // Valid message with nothing out of bailiwick, but the authority
    // (subdomain.example.com) is not authoritative for the answer.
    //
    // TODO: Test the case where the additional section does not match
    // with something in the authority section.
    Message message1(Message::RENDER);
    message1.addQuestion(qu_in_a_www);
    message1.addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    message1.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub);
    message1.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3);
    int removed = ResponseScrubber::scrubCrossSections(message1);
    EXPECT_EQ(1, removed);
    EXPECT_TRUE(message1.hasRRset(Message::SECTION_ANSWER, rrs_in_a_www));
    EXPECT_FALSE(message1.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub));
    EXPECT_TRUE(message1.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3));

    // A repeat of the test, this time with a mixture of incorrect and correct
    // authorities.
    Message message2(Message::RENDER);
    message2.addQuestion(qu_in_a_www);
    message2.addRRset(Message::SECTION_ANSWER, rrs_in_a_www);
    message2.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub);
    message2.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns);
    message2.addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub2);
    message2.addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3);
    removed = ResponseScrubber::scrubCrossSections(message2);
    EXPECT_EQ(2, removed);
    EXPECT_TRUE(message2.hasRRset(Message::SECTION_ANSWER, rrs_in_a_www));
    EXPECT_FALSE(message2.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub));
    EXPECT_TRUE(message2.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns));
    EXPECT_FALSE(message2.hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub2));
    EXPECT_TRUE(message2.hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3));
}

// Test the main "scrub" method.  This is a single to ensure that the
// combination of methods

TEST_F(ResponseScrubberTest, All) {
    MessagePtr mptr(new Message(Message::RENDER));

    // Question is "www.example.com IN A" sent to a nameserver with the
    // bailiwick of "example.com".
    mptr->addQuestion(qu_in_a_www);

    // Answer section.

    // "www.example.com IN CNAME www.example.net" - should be kept
    mptr->addRRset(Message::SECTION_ANSWER, rrs_in_cname_www);

    // "www.example.net IN A a.b.c.d" - should be removed, out of bailiwick
    mptr->addRRset(Message::SECTION_ANSWER, rrs_in_a_wwwnet);

    // Authority section.

    // "example.net IN NS xxxx" - should be removed, out of bailiwick.
    mptr->addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_net);

    // "example.com IN NS xxx" - kept
    mptr->addRRset(Message::SECTION_AUTHORITY, rrs_in_ns);

    // "com IN NS xxx" - removed, out of bailiwick
    mptr->addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_com);

    // "subdomain.example.com IN NS xxx" - removed, not a superdomain of the
    // answer.
    mptr->addRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub);

    // Additional section

    // "ns2.example.net IN A a.b.c.d" - removed, out of bailiwick
    mptr->addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2);

    // "ns3.subdomain.example.com IN A a.b.c.d" - retained.
    mptr->addRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3);

    unsigned int removed = ResponseScrubber::scrub(mptr, bailiwick);
    EXPECT_EQ(5, removed);

    EXPECT_TRUE(mptr->hasRRset(Message::SECTION_ANSWER, rrs_in_cname_www));
    EXPECT_FALSE(mptr->hasRRset(Message::SECTION_ANSWER, rrs_in_a_wwwnet));
    EXPECT_FALSE(mptr->hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_net));
    EXPECT_TRUE(mptr->hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns));
    EXPECT_FALSE(mptr->hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_com));
    EXPECT_FALSE(mptr->hasRRset(Message::SECTION_AUTHORITY, rrs_in_ns_sub));
    EXPECT_FALSE(mptr->hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns2));
    EXPECT_TRUE(mptr->hasRRset(Message::SECTION_ADDITIONAL, rrs_in_a_ns3));

}
} // Anonymous namespace
