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

#include <sstream>

#include <dns/message.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>

#include <datasrc/memory_datasrc.h>

#include <auth/query.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::auth;
using namespace isc::testutils;

namespace {

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
        //                         NS noglue.example.com.
        //                         NS cname.example.com.
        //                         NS example.org.
        delegation_rrset(RRsetPtr(new RRset(Name("delegation.example.com"),
                                            rrclass_, RRType::NS(), rrttl_))),
        // cname.example.com. CNAME www.example.com.
        cname_rrset(RRsetPtr(new RRset(Name("cname.example.com"), rrclass_,
                                       RRType::CNAME(), rrttl_))),
        // example.com. NS glue.ns.example.com.
        //              NS noglue.example.com.
        //              NS example.net.
        auth_ns_rrset(RRsetPtr(new RRset(Name("example.com"), rrclass_,
                                         RRType::NS(), rrttl_))),
        // cnamemailer.example.com. CNAME www.example.com.
        mx_cname_rrset_(new RRset(Name("cnamemailer.example.com"), rrclass_,
                                  RRType::CNAME(), rrttl_)),
        // mx.example.com. MX 10 www.example.com.
        //                 MX 20 mailer.example.org.
        //                 MX 30 mx.delegation.example.com.
        mx_rrset_(new RRset(Name("mx.example.com"), rrclass_, RRType::MX(),
                            rrttl_)),
        // cnamemx.example.com. MX 10 cnamemailer.example.com.
        cnamemx_rrset_(new RRset(Name("cnamemx.example.com"), rrclass_,
                                 RRType::MX(), rrttl_)),
        // www.example.com. A 192.0.2.80
        a_rrset(new RRset(Name("www.example.com"), rrclass_, RRType::A(),
                          rrttl_)),
        // glue.ns.example.com. A 192.0.2.153
        glue_a_rrset(new RRset(Name("glue.ns.example.com"), rrclass_,
                               RRType::A(), rrttl_)),
        // glue.ns.example.com. AAAA 2001:db8::53
        glue_aaaa_rrset(new RRset(Name("glue.ns.example.com"), rrclass_,
                                  RRType::AAAA(), rrttl_)),

        // example.com. SOA . . 0 0 0 0 0
        soa_rrset(new RRset(Name("example.com"), rrclass_, RRType::SOA(),
                            rrttl_)),

        // noglue.example.com. A 192.0.2.53
        noglue_a_rrset(new RRset(Name("noglue.example.com"), rrclass_,
                                 RRType::A(), rrttl_)),

        // The following RRsets will be used without RDATA for now.
        delegated_mx_a_rrset(new RRset(Name("mx.delegation.example.com"),
                                       rrclass_, RRType::A(), rrttl_))
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
        cnamemx_rrset_->addRdata(generic::MX(10,
                                             Name("cnamemailer.example.com")));
        mx_cname_rrset_->addRdata(generic::CNAME(Name("www.example.com")));
        noglue_a_rrset->addRdata(in::A("192.0.2.53"));
        glue_a_rrset->addRdata(in::A("192.0.2.153"));
        glue_aaaa_rrset->addRdata(in::AAAA("2001:db8::53"));
        soa_rrset->addRdata(generic::SOA(". . 0 0 0 0 0"));
        a_rrset->addRdata(in::A("192.0.2.80"));
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
    RRsetPtr cnamemx_rrset_;
    RRsetPtr a_rrset;
    RRsetPtr glue_a_rrset;
    RRsetPtr glue_aaaa_rrset;
    RRsetPtr soa_rrset;
    RRsetPtr noglue_a_rrset;
    RRsetPtr delegated_mx_a_rrset;
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
    } else if (name == Name("cnamemx.example.com")) {
        return (FindResult(SUCCESS, cnamemx_rrset_));
    } else {
        return (FindResult(DNAME, RRsetPtr()));
    }
}

const char* const soa_txt = "example.com. 3600 IN SOA . . 0 0 0 0 0";
const char* const zone_ns_txt =
    "example.com. 3600 IN NS glue.ns.example.com.\n"
    "example.com. 3600 IN NS noglue.example.com.\n"
    "example.com. 3600 IN NS example.net.";
const char* const glue_txt =
    "glue.ns.example.com. 3600 IN A 192.0.2.153\n"
    "glue.ns.example.com. 3600 IN AAAA 2001:db8::53\n"
    "noglue.example.com. 3600 IN A 192.0.2.53\n";

class QueryTest : public ::testing::Test {
protected:
    QueryTest() :
        qname(Name("www.example.com")), qclass(RRClass::IN()),
        qtype(RRType::A()), response(Message::RENDER),
        qid(response.getQid()), query_code(Opcode::QUERY().getCode())
    {
        response.setRcode(Rcode::NOERROR());
        response.setOpcode(Opcode::QUERY());
        // create and add a matching zone.
        mock_zone = new MockZone();
        memory_datasrc.addZone(ZonePtr(mock_zone));
    }
    MockZone* mock_zone;
    MemoryDataSrc memory_datasrc;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    Message response;
    const qid_t qid;
    const uint16_t query_code;
    stringstream expected_answer;
    stringstream expected_authority;
    stringstream expected_additional;
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
    Query query(memory_datasrc, qname, qtype, response);
    EXPECT_NO_THROW(query.process());
    // find match rrset
    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                AA_FLAG, 0, 1, 3, 3);

    expected_answer << "www.example.com. 3600 IN A 192.0.2.80\n";
    rrsetsCheck(expected_answer,
                response.beginSection(Message::SECTION_ANSWER),
                response.endSection(Message::SECTION_ANSWER));

    expected_authority << zone_ns_txt;
    rrsetsCheck(expected_authority,
                response.beginSection(Message::SECTION_AUTHORITY),
                response.endSection(Message::SECTION_AUTHORITY));

    expected_additional << glue_txt;
    rrsetsCheck(expected_additional,
                response.beginSection(Message::SECTION_ADDITIONAL),
                response.endSection(Message::SECTION_ADDITIONAL));
}

TEST_F(QueryTest, exactAddrMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    const Name noglue_name(Name("noglue.example.com"));
    Query noglue_query(memory_datasrc, noglue_name, qtype, response);
    EXPECT_NO_THROW(noglue_query.process());

    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                AA_FLAG, 0, 1, 3, 2);

    expected_answer << "noglue.example.com. 3600 IN A 192.0.2.53\n";
    rrsetsCheck(expected_answer,
                response.beginSection(Message::SECTION_ANSWER),
                response.endSection(Message::SECTION_ANSWER));

    expected_authority << zone_ns_txt;
    rrsetsCheck(expected_authority,
                response.beginSection(Message::SECTION_AUTHORITY),
                response.endSection(Message::SECTION_AUTHORITY));

    expected_additional << "glue.ns.example.com. 3600 IN A 192.0.2.153\n"
        "glue.ns.example.com. 3600 IN AAAA 2001:db8::53\n";
    rrsetsCheck(expected_additional,
                response.beginSection(Message::SECTION_ADDITIONAL),
                response.endSection(Message::SECTION_ADDITIONAL));
}

TEST_F(QueryTest, apexNSMatch) {
    // find match rrset, omit authority data which has already been provided
    // in the answer section from the authority section.
    const Name apex_name(Name("example.com"));
    Query apex_ns_query(memory_datasrc, apex_name, RRType::NS(), response);
    EXPECT_NO_THROW(apex_ns_query.process());

    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                AA_FLAG, 0, 3, 0, 3);

    expected_answer << zone_ns_txt;
    rrsetsCheck(expected_answer,
                response.beginSection(Message::SECTION_ANSWER),
                response.endSection(Message::SECTION_ANSWER));

    expected_additional << glue_txt;
    rrsetsCheck(expected_additional,
                response.beginSection(Message::SECTION_ADDITIONAL),
                response.endSection(Message::SECTION_ADDITIONAL));
}

TEST_F(QueryTest, exactAnyMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    const Name noglue_name(Name("noglue.example.com"));
    Query noglue_query(memory_datasrc, noglue_name, RRType::ANY(), response);
    EXPECT_NO_THROW(noglue_query.process());

    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                AA_FLAG, 0, 1, 3, 2);

    expected_answer << "noglue.example.com. 3600 IN A 192.0.2.53\n";
    rrsetsCheck(expected_answer,
                response.beginSection(Message::SECTION_ANSWER),
                response.endSection(Message::SECTION_ANSWER));

    expected_authority << zone_ns_txt;
    rrsetsCheck(expected_authority,
                response.beginSection(Message::SECTION_AUTHORITY),
                response.endSection(Message::SECTION_AUTHORITY));

    expected_additional << "glue.ns.example.com. 3600 IN A 192.0.2.153\n"
        "glue.ns.example.com. 3600 IN AAAA 2001:db8::53\n";
    rrsetsCheck(expected_additional,
                response.beginSection(Message::SECTION_ADDITIONAL),
                response.endSection(Message::SECTION_ADDITIONAL));
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

    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                0, 0, 0, 4, 3);

    stringstream expected_authority;
    expected_authority <<
        "delegation.example.com. 3600 IN NS glue.ns.example.com.\n"
        "delegation.example.com. 3600 IN NS noglue.example.com.\n"
        "delegation.example.com. 3600 IN NS cname.example.com.\n"
        "delegation.example.com. 3600 IN NS example.org.\n";
    rrsetsCheck(expected_authority,
                response.beginSection(Message::SECTION_AUTHORITY),
                response.endSection(Message::SECTION_AUTHORITY));

    stringstream expected_additional;
    expected_additional << glue_txt;
    rrsetsCheck(expected_additional,
                response.beginSection(Message::SECTION_ADDITIONAL),
                response.endSection(Message::SECTION_ADDITIONAL));
}

TEST_F(QueryTest, nxdomain) {
    const Name nxdomain_name(Name("nxdomain.example.com"));
    Query nxdomain_query(memory_datasrc, nxdomain_name, qtype, response);
    EXPECT_NO_THROW(nxdomain_query.process());
    headerCheck(response, qid, Rcode::NXDOMAIN(), query_code,
                AA_FLAG, 0, 0, 1, 0);
    expected_authority << soa_txt;
    rrsetsCheck(expected_authority,
                response.beginSection(Message::SECTION_AUTHORITY),
                response.endSection(Message::SECTION_AUTHORITY),
                Name("example.com"));
}

TEST_F(QueryTest, nxrrset) {
    const Name nxrrset_name(Name("nxrrset.example.com"));
    Query nxrrset_query(memory_datasrc, nxrrset_name, qtype, response);
    EXPECT_NO_THROW(nxrrset_query.process());

    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                AA_FLAG, 0, 0, 1, 0);
    expected_authority << soa_txt;
    rrsetsCheck(expected_authority,
                response.beginSection(Message::SECTION_AUTHORITY),
                response.endSection(Message::SECTION_AUTHORITY),
                Name("example.com"));
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

    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                AA_FLAG, 0, 3, 3, 4);

    expected_answer << "mx.example.com. 3600 IN MX 10 www.example.com.\n"
        "mx.example.com. 3600 IN MX 20 mailer.example.org.\n"
        "mx.example.com. 3600 IN MX 30 mx.delegation.example.com.\n";
    rrsetsCheck(expected_answer,
                response.beginSection(Message::SECTION_ANSWER),
                response.endSection(Message::SECTION_ANSWER));

    expected_additional << glue_txt;
    expected_additional << "www.example.com. 3600 IN A 192.0.2.80\n";
    rrsetsCheck(expected_additional,
                response.beginSection(Message::SECTION_ADDITIONAL),
                response.endSection(Message::SECTION_ADDITIONAL));
}

/*
 * Test when we ask for MX whose exchange is an alias (CNAME in this case).
 *
 * This should not trigger the additional processing for the exchange.
 */
TEST_F(QueryTest, MXAlias) {
    Name qname("cnamemx.example.com");
    Query mx_query(memory_datasrc, qname, RRType::MX(), response);
    EXPECT_NO_THROW(mx_query.process());
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    // there shouldn't be no additional RRs for the exchanges (we have 3
    // RRs for the NS)
    headerCheck(response, qid, Rcode::NOERROR(), query_code,
                AA_FLAG, 0, 1, 3, 3);

    expected_additional << glue_txt;
    rrsetsCheck(expected_additional,
                response.beginSection(Message::SECTION_ADDITIONAL),
                response.endSection(Message::SECTION_ADDITIONAL));
}
}
