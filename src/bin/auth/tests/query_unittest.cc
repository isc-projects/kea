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

#include <dns/message.h>
#include <dns/name.h>
#include <dns/rcode.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>

#include <datasrc/memory_datasrc.h>

#include <auth/query.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::auth;

namespace {

RRsetPtr a_rrset = RRsetPtr(new RRset(Name("www.example.com"),
                                      RRClass::IN(), RRType::A(),
                                      RRTTL(3600)));
RRsetPtr soa_rrset = RRsetPtr(new RRset(Name("example.com"),
                                        RRClass::IN(), RRType::SOA(),
                                        RRTTL(3600)));
RRsetPtr ns_rrset(RRsetPtr(new RRset(Name("ns.example.com"),
                                     RRClass::IN(), RRType::NS(),
                                     RRTTL(3600))));
RRsetPtr glue_a_rrset(RRsetPtr(new RRset(Name("glue.ns.example.com"),
                                         RRClass::IN(), RRType::A(),
                                         RRTTL(3600))));
RRsetPtr glue_aaaa_rrset(RRsetPtr(new RRset(Name("glue.ns.example.com"),
                                            RRClass::IN(), RRType::AAAA(),
                                            RRTTL(3600))));
RRsetPtr noglue_a_rrset(RRsetPtr(new RRset(Name("noglue.example.com"),
                                         RRClass::IN(), RRType::A(),
                                         RRTTL(3600))));
RRsetPtr delegated_mx_a_rrset(RRsetPtr(new RRset(
    Name("mx.delegation.example.com"), RRClass::IN(), RRType::A(),
    RRTTL(3600))));

// This is a mock Zone class for testing.
// It is a derived class of Zone, and simply hardcodes the results of find()
// See the find() implementation if you want to know its content.
class MockZone : public Zone {
public:
    MockZone(bool has_SOA = true) :
        origin_(Name("example.com")),
        has_SOA_(has_SOA),
        delegation_rrset(RRsetPtr(new RRset(Name("delegation.example.com"),
                                            RRClass::IN(), RRType::NS(),
                                            RRTTL(3600)))),
        cname_rrset(RRsetPtr(new RRset(Name("cname.example.com"),
                                       RRClass::IN(), RRType::CNAME(),
                                       RRTTL(3600)))),
        mx_rrset_(new RRset(Name("mx.example.com"), RRClass::IN(),
            RRType::MX(), RRTTL(3600)))
    {
        delegation_rrset->addRdata(rdata::generic::NS(
                          Name("glue.ns.example.com")));
        delegation_rrset->addRdata(rdata::generic::NS(
                          Name("noglue.example.com")));
        delegation_rrset->addRdata(rdata::generic::NS(
                          Name("cname.example.com")));
        delegation_rrset->addRdata(rdata::generic::NS(
                          Name("example.org")));
        cname_rrset->addRdata(rdata::generic::CNAME(
                          Name("www.example.com")));
        mx_rrset_->addRdata(isc::dns::rdata::generic::MX(10,
            Name("www.example.com")));
        mx_rrset_->addRdata(isc::dns::rdata::generic::MX(20,
            Name("mailer.example.org")));
        mx_rrset_->addRdata(isc::dns::rdata::generic::MX(30,
            Name("mx.delegation.example.com")));
    }
    virtual const isc::dns::Name& getOrigin() const;
    virtual const isc::dns::RRClass& getClass() const;

    FindResult find(const isc::dns::Name& name,
                    const isc::dns::RRType& type,
                    const FindOptions options = FIND_DEFAULT) const;

private:
    Name origin_;
    bool has_SOA_;
    RRsetPtr delegation_rrset;
    RRsetPtr cname_rrset;
    RRsetPtr mx_rrset_;
};

const Name&
MockZone::getOrigin() const {
    return (origin_);
}

const RRClass&
MockZone::getClass() const {
    return (RRClass::IN());
}

Zone::FindResult
MockZone::find(const Name& name, const RRType& type,
               const FindOptions options) const
{
    // hardcode the find results
    if (name == Name("www.example.com") && type == RRType::A()) {
        return (FindResult(SUCCESS, a_rrset));
    } else if (name == Name("www.example.com")) {
        return (FindResult(NXRRSET, RRsetPtr()));
    } else if (name == Name("glue.ns.example.com") && type == RRType::A() &&
        (options & FIND_GLUE_OK)) {
        return (FindResult(SUCCESS, glue_a_rrset));
    } else if (name == Name("noglue.example.com") && type == RRType::A()) {
        return (FindResult(SUCCESS, noglue_a_rrset));
    } else if (name == Name("glue.ns.example.com") && type == RRType::AAAA() &&
        (options & FIND_GLUE_OK)) {
        return (FindResult(SUCCESS, glue_aaaa_rrset));
    } else if (name == Name("example.com") && type == RRType::SOA() &&
        has_SOA_)
    {
        return (FindResult(SUCCESS, soa_rrset));
    } else if (name == Name("mx.delegation.example.com") &&
        type == RRType::A() && (options & FIND_GLUE_OK))
    {
        return (FindResult(SUCCESS, delegated_mx_a_rrset));
    } else if (name == Name("delegation.example.com") ||
        name.compare(Name("delegation.example.com")).getRelation() ==
        NameComparisonResult::SUBDOMAIN)
    {
        return (FindResult(DELEGATION, delegation_rrset));
    } else if (name == Name("ns.example.com")) {
        return (FindResult(DELEGATION, ns_rrset));
    } else if (name == Name("nxdomain.example.com")) {
        return (FindResult(NXDOMAIN, RRsetPtr()));
    } else if (name == Name("nxrrset.example.com")) {
        return (FindResult(NXRRSET, RRsetPtr()));
    } else if ((name == Name("cname.example.com"))) {
        return (FindResult(CNAME, cname_rrset));
    } else if (name == Name("mx.example.com")) {
        return (FindResult(SUCCESS, mx_rrset_));
    } else {
        return (FindResult(DNAME, RRsetPtr()));
    }
}

class QueryTest : public ::testing::Test {
protected:
    QueryTest() :
        qname(Name("www.example.com")), qclass(RRClass::IN()),
        qtype(RRType::A()), response(Message::RENDER),
        query(memory_datasrc, qname, qtype, response)
    {
        response.setRcode(Rcode::NOERROR());
    }
    MemoryDataSrc memory_datasrc;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    Message response;
    Query query;
};

TEST_F(QueryTest, noZone) {
    // There's no zone in the memory datasource.  So the response should have
    // REFUSED.
    query.process();
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

TEST_F(QueryTest, matchZone) {
    // add a matching zone.
    memory_datasrc.addZone(ZonePtr(new MockZone()));
    query.process();
    EXPECT_TRUE(response.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
                                  Name("www.example.com"), RRClass::IN(),
                                  RRType::A()));

    // Delegation
    const Name delegation_name(Name("delegation.example.com"));
    Query delegation_query(memory_datasrc, delegation_name, qtype, response);
    delegation_query.process();
    EXPECT_FALSE(response.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
                                  Name("delegation.example.com"),
                                  RRClass::IN(), RRType::NS()));
    // glue address records
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::AAAA()));
    // noglue address records
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("noglue.example.com"),
                                  RRClass::IN(), RRType::A()));
    // NS name has a CNAME
    EXPECT_FALSE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("www.example.com"),
                                  RRClass::IN(), RRType::A()));
    // NS name is out of zone
    EXPECT_FALSE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("example.org"),
                                  RRClass::IN(), RRType::A()));

    // NXDOMAIN
    const Name nxdomain_name(Name("nxdomain.example.com"));
    Query nxdomain_query(memory_datasrc, nxdomain_name, qtype, response);
    nxdomain_query.process();
    EXPECT_EQ(Rcode::NXDOMAIN(), response.getRcode());
    EXPECT_EQ(0, response.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, response.getRRCount(Message::SECTION_ADDITIONAL));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
        Name("example.com"), RRClass::IN(), RRType::SOA()));

    // NXRRSET
    const Name nxrrset_name(Name("nxrrset.example.com"));
    Query nxrrset_query(memory_datasrc, nxrrset_name, qtype, response);
    nxrrset_query.process();
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_EQ(0, response.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, response.getRRCount(Message::SECTION_ADDITIONAL));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
        Name("example.com"), RRClass::IN(), RRType::SOA()));
}

/*
 * This tests that when there's no SOA and we need a negative answer. It should
 * throw in that case.
 */
TEST_F(QueryTest, noSOA) {
    memory_datasrc.addZone(ZonePtr(new MockZone(false)));

    // The NX Domain
    const Name nxdomain_name(Name("nxdomain.example.com"));
    Query nxdomain_query(memory_datasrc, nxdomain_name, qtype, response);
    EXPECT_THROW(nxdomain_query.process(), Query::NoSOA);
    // Of course, we don't look into the response, as it throwed

    // NXRRSET
    const Name nxrrset_name(Name("nxrrset.example.com"));
    Query nxrrset_query(memory_datasrc, nxrrset_name, qtype, response);
    EXPECT_THROW(nxrrset_query.process(), Query::NoSOA);
}

TEST_F(QueryTest, noMatchZone) {
    // there's a zone in the memory datasource but it doesn't match the qname.
    // should result in REFUSED.
    memory_datasrc.addZone(ZonePtr(new MockZone()));
    const Name nomatch_name(Name("example.org"));
    Query nomatch_query(memory_datasrc, nomatch_name, qtype, response);
    nomatch_query.process();
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

/*
 * Test MX additional processing.
 *
 * The MX RRset has two RRs, one pointing to a known domain with
 * A record, other to unknown out of zone one.
 */
TEST_F(QueryTest, MX) {
    memory_datasrc.addZone(ZonePtr(new MockZone()));
    Name qname("mx.example.com");
    Query mx_query(memory_datasrc, qname, RRType::MX(), response);
    EXPECT_NO_THROW(mx_query.process());
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
        Name("mx.example.com"), RRClass::IN(), RRType::MX()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
        Name("www.example.com"), RRClass::IN(), RRType::A()));
    /*
     * In fact, the MX RRset mentions three names, but we don't know anything
     * about one of them and one is under a zone cut, so we should have just
     * one RRset (A for www.example.com)
     */
    // We can't use getRRCount, as it counts RRs, not RRsets
    unsigned additional_count(0);
    for (SectionIterator<RRsetPtr> ai(response.beginSection(
        Message::SECTION_ADDITIONAL)); ai != response.endSection(
        Message::SECTION_ADDITIONAL); ++ai)
    {
        additional_count++;
        EXPECT_EQ(Name("www.example.com"), (*ai)->getName());
        EXPECT_EQ(RRType::A(), (*ai)->getType());
    }
    EXPECT_EQ(1, additional_count);
}

}
