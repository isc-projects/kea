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
using namespace isc::dns::rdata;
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
    MockZone(bool has_SOA = true, bool has_apex_NS = true) :
        origin_(Name("example.com")),
        has_SOA_(has_SOA),
        has_apex_NS_(has_apex_NS),
        rrclass_(RRClass::IN()),
        rrttl_(RRTTL(3600)),
        // delegation.example.com. NS glue.ns.example.com.
        //                         NS noglue.ns.example.com.
        //                         NS cname.example.com.
        //                         NS example.org.
        delegation_rrset(RRsetPtr(new RRset(Name("delegation.example.com"),
                                            rrclass_, RRType::NS(), rrttl_))),
        // cname.example.com. CNAME www.example.com.
        cname_rrset(RRsetPtr(new RRset(Name("cname.example.com"), rrclass_,
                                       RRType::CNAME(), rrttl_))),
        // example.com. NS glue.ns.example.com.
        //              NS noglue.ns.example.com.
        //              NS example.net.
        auth_ns_rrset(RRsetPtr(new RRset(Name("example.com"), rrclass_,
                                         RRType::NS(), rrttl_))),
        // cnamemailer.example.com. CNAME host.example.com.
        mx_cname_rrset_(new RRset(Name("cnamemailer.example.com"), rrclass_,
                                  RRType::CNAME(), rrttl_)),
        // mx.example.com. MX 10 www.example.com.
        //                 MX 20 mailer.example.com.
        //                 MX 30 mx.delegation.example.com.
        mx_rrset_(new RRset(Name("mx.example.com"), rrclass_, RRType::MX(),
                            rrttl_)),
        // host.example.com. A 192.0.2.1
        a_rrset_(new RRset(Name("host.example.com"), rrclass_, RRType::A(),
                           rrttl_))
    {
        delegation_rrset->addRdata(generic::NS(Name("glue.ns.example.com")));
        delegation_rrset->addRdata(generic::NS(Name("noglue.example.com")));
        delegation_rrset->addRdata(generic::NS(Name("cname.example.com")));
        delegation_rrset->addRdata(generic::NS(Name("example.org")));
        cname_rrset->addRdata(generic::CNAME(Name("www.example.com")));
        auth_ns_rrset->addRdata(generic::NS(Name("glue.ns.example.com")));
        auth_ns_rrset->addRdata(generic::NS(Name("noglue.example.com")));
        auth_ns_rrset->addRdata(generic::NS(Name("example.net")));
        mx_rrset_->addRdata(generic::MX(10, Name("www.example.com")));
        mx_rrset_->addRdata(generic::MX(20, Name("mailer.example.org")));
        mx_rrset_->addRdata(generic::MX(30,
                                        Name("mx.delegation.example.com")));
        mx_cname_rrset_->addRdata(generic::CNAME(Name("host.example.com")));
        a_rrset_->addRdata(in::A("192.0.2.1"));
    }
    virtual const isc::dns::Name& getOrigin() const;
    virtual const isc::dns::RRClass& getClass() const;
    void setSOAFlag(bool on) { has_SOA_ = on; }
    void setApexNSFlag(bool on) { has_apex_NS_ = on; }

    FindResult find(const isc::dns::Name& name,
                    const isc::dns::RRType& type,
                    const FindOptions options = FIND_DEFAULT) const;

private:
    Name origin_;
    bool has_SOA_;
    bool has_apex_NS_;
    const RRClass rrclass_;
    const RRTTL rrttl_;
    RRsetPtr delegation_rrset;
    RRsetPtr cname_rrset;
    RRsetPtr auth_ns_rrset;
    RRsetPtr mx_cname_rrset_;
    RRsetPtr mx_rrset_;
    RRsetPtr a_rrset_;
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
        (options & FIND_GLUE_OK) != 0) {
        return (FindResult(SUCCESS, glue_a_rrset));
    } else if (name == Name("noglue.example.com") && (type == RRType::A() ||
        type == RRType::ANY())) {
        return (FindResult(SUCCESS, noglue_a_rrset));
    } else if (name == Name("glue.ns.example.com") && type == RRType::AAAA() &&
        (options & FIND_GLUE_OK) != 0) {
        return (FindResult(SUCCESS, glue_aaaa_rrset));
    } else if (name == Name("example.com") && type == RRType::SOA() &&
        has_SOA_)
    {
        return (FindResult(SUCCESS, soa_rrset));
    } else if (name == Name("example.com") && type == RRType::NS() &&
        has_apex_NS_)
    {
        return (FindResult(SUCCESS, auth_ns_rrset));
    } else if (name == Name("mx.delegation.example.com") &&
        type == RRType::A() && (options & FIND_GLUE_OK) != 0)
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
    } else if (name == Name("cnamemailer.example.com")) {
        return (FindResult(CNAME, mx_cname_rrset_));
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
        mock_zone = new MockZone();
        memory_datasrc.addZone(ZonePtr(mock_zone));
    }
    MockZone* mock_zone;
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
    MemoryDataSrc empty_memory_datasrc;
    Query nozone_query(empty_memory_datasrc, qname, qtype, response);
    EXPECT_NO_THROW(nozone_query.process());
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

TEST_F(QueryTest, exactMatch) {
    // add a matching zone.
    EXPECT_NO_THROW(query.process());
    // find match rrset
    EXPECT_TRUE(response.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
                                  Name("www.example.com"), RRClass::IN(),
                                  RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
                                  Name("example.com"), RRClass::IN(),
                                  RRType::NS()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::AAAA()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("noglue.example.com"),
                                  RRClass::IN(), RRType::A()));
}

TEST_F(QueryTest, exactAddrMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    const Name noglue_name(Name("noglue.example.com"));
    Query noglue_query(memory_datasrc, noglue_name, qtype, response);
    EXPECT_NO_THROW(noglue_query.process());
    EXPECT_TRUE(response.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
                                  Name("noglue.example.com"), RRClass::IN(),
                                  RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
                                  Name("example.com"), RRClass::IN(),
                                  RRType::NS()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::AAAA()));
    EXPECT_FALSE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("noglue.example.com"),
                                  RRClass::IN(), RRType::A()));
}

TEST_F(QueryTest, apexNSMatch) {
    // find match rrset, omit authority data which has already been provided
    // in the answer section from the authority section.
    const Name apex_name(Name("example.com"));
    Query apex_ns_query(memory_datasrc, apex_name, RRType::NS(), response);
    EXPECT_NO_THROW(apex_ns_query.process());
    EXPECT_TRUE(response.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
                                  Name("example.com"), RRClass::IN(),
                                  RRType::NS()));
    EXPECT_FALSE(response.hasRRset(Message::SECTION_AUTHORITY,
                                  Name("example.com"), RRClass::IN(),
                                  RRType::NS()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::AAAA()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("noglue.example.com"),
                                  RRClass::IN(), RRType::A()));
}

TEST_F(QueryTest, exactAnyMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    const Name noglue_name(Name("noglue.example.com"));
    Query noglue_query(memory_datasrc, noglue_name, RRType::ANY(), response);
    EXPECT_NO_THROW(noglue_query.process());
    EXPECT_TRUE(response.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
                                  Name("noglue.example.com"), RRClass::IN(),
                                  RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
                                  Name("example.com"), RRClass::IN(),
                                  RRType::NS()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.ns.example.com"),
                                  RRClass::IN(), RRType::AAAA()));
    EXPECT_FALSE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("noglue.example.com"),
                                  RRClass::IN(), RRType::A()));
}

// This tests that when we need to look up Zone's apex NS records for
// authoritative answer, and there is no apex NS records. It should
// throw in that case.
TEST_F(QueryTest, noApexNS) {
    // Disable apex NS record
    mock_zone->setApexNSFlag(false);
    
    const Name noglue_name(Name("noglue.example.com"));
    Query noglue_query(memory_datasrc, noglue_name, qtype, response);
    EXPECT_THROW(noglue_query.process(), Query::NoApexNS);
    // We don't look into the response, as it throwed
}

TEST_F(QueryTest, delegation) {
    const Name delegation_name(Name("delegation.example.com"));
    Query delegation_query(memory_datasrc, delegation_name, qtype, response);
    EXPECT_NO_THROW(delegation_query.process());
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
}

TEST_F(QueryTest, nxdomain) {
    const Name nxdomain_name(Name("nxdomain.example.com"));
    Query nxdomain_query(memory_datasrc, nxdomain_name, qtype, response);
    EXPECT_NO_THROW(nxdomain_query.process());
    EXPECT_EQ(Rcode::NXDOMAIN(), response.getRcode());
    EXPECT_EQ(0, response.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, response.getRRCount(Message::SECTION_ADDITIONAL));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
        Name("example.com"), RRClass::IN(), RRType::SOA()));
}

TEST_F(QueryTest, nxrrset) {
    const Name nxrrset_name(Name("nxrrset.example.com"));
    Query nxrrset_query(memory_datasrc, nxrrset_name, qtype, response);
    EXPECT_NO_THROW(nxrrset_query.process());
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
    // disable zone's SOA RR.
    mock_zone->setSOAFlag(false);

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
    Name qname("mx.example.com");
    Query mx_query(memory_datasrc, qname, RRType::MX(), response);
    EXPECT_NO_THROW(mx_query.process());
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
        Name("mx.example.com"), RRClass::IN(), RRType::MX()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
        Name("www.example.com"), RRClass::IN(), RRType::A()));
    // We want to skip the additional ones related to authoritative
    RRsetPtr ns;
    for (SectionIterator<RRsetPtr> ai(response.beginSection(
        Message::SECTION_AUTHORITY)); ai != response.endSection(
        Message::SECTION_AUTHORITY); ++ai)
    {
        if ((*ai)->getName() == Name("example.com") && (*ai)->getType() ==
            RRType::NS())
        {
            ns = *ai;
            break;
        }
    }
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
        // Skip the ones for the NS record
        if (ns) {
            for (RdataIteratorPtr nsi(ns->getRdataIterator()); !nsi->isLast();
                nsi->next())
            {
                if ((*ai)->getName() ==
                    dynamic_cast<const isc::dns::rdata::generic::NS&>(
                    nsi->getCurrent()).getNSName())
                {
                    goto NS_ADDITIONAL_DATA;
                }
            }
        }
        // It is not related to the NS, then it must be related to the MX
        ++additional_count;
        EXPECT_EQ(Name("www.example.com"), (*ai)->getName());
        EXPECT_EQ(RRType::A(), (*ai)->getType());
        NS_ADDITIONAL_DATA:;
    }
    EXPECT_EQ(1, additional_count);
}

/*
 * Test when we ask for MX and encounter an alias (CNAME in this case).
 *
 * This should not trigger the additional processing.
 */
TEST_F(QueryTest, MXAlias) {
    Name qname("cnamemailer.example.com");
    Query mx_query(memory_datasrc, qname, RRType::MX(), response);
    EXPECT_NO_THROW(mx_query.process());
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    // We should not have the IP address in additional section
    // Currently, the section should be completely empty
    EXPECT_TRUE(response.beginSection(Message::SECTION_ADDITIONAL) ==
        response.endSection(Message::SECTION_ADDITIONAL));
}
}
