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
#include <vector>
#include <map>

#include <boost/bind.hpp>

#include <dns/masterload.h>
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

// This is the content of the mock zone (see below).
// It's a sequence of textual RRs that is supposed to be parsed by
// dns::masterLoad().  Some of the RRs are also used as the expected
// data in specific tests, in which case they are referenced via specific
// local variables (such as soa_txt).
const char* const soa_txt = "example.com. 3600 IN SOA . . 0 0 0 0 0\n";
const char* const zone_ns_txt =
    "example.com. 3600 IN NS glue.delegation.example.com.\n"
    "example.com. 3600 IN NS noglue.example.com.\n"
    "example.com. 3600 IN NS example.net.\n";
const char* const ns_addrs_txt =
    "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
    "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n"
    "noglue.example.com. 3600 IN A 192.0.2.53\n";
const char* const delegation_txt =
        "delegation.example.com. 3600 IN NS glue.delegation.example.com.\n"
        "delegation.example.com. 3600 IN NS noglue.example.com.\n"
        "delegation.example.com. 3600 IN NS cname.example.com.\n"
        "delegation.example.com. 3600 IN NS example.org.\n";
const char* const mx_txt =
    "mx.example.com. 3600 IN MX 10 www.example.com.\n"
    "mx.example.com. 3600 IN MX 20 mailer.example.org.\n"
    "mx.example.com. 3600 IN MX 30 mx.delegation.example.com.\n";
const char* const www_a_txt = "www.example.com. 3600 IN A 192.0.2.80\n";
// The rest of data won't be referenced from the test cases.
const char* const other_zone_rrs =
    "cname.example.com. 3600 IN CNAME www.example.com.\n"
    "cnamemailer.example.com. 3600 IN CNAME www.example.com.\n"
    "cnamemx.example.com. 3600 IN MX 10 cnamemailer.example.com.\n"
    "mx.delegation.example.com. 3600 IN A 192.0.2.100\n";

// This is a mock Zone class for testing.
// It is a derived class of Zone for the convenient of tests.
// Its find() method emulates the common behavior of protocol compliant
// zone classes, but simplifies some minor cases and also supports broken
// behavior.
// For simplicity, most names are assumed to be "in zone"; there's only
// one zone cut at the point of name "delegation.example.com".
// It doesn't handle empty non terminal nodes (if we need to test such cases
// find() should have specialized code for it).
class MockZone : public Zone {
public:
    MockZone() :
        origin_(Name("example.com")),
        delegation_name_("delegation.example.com"),
        has_SOA_(true),
        has_apex_NS_(true),
        rrclass_(RRClass::IN())
    {
        stringstream zone_stream;
        zone_stream << soa_txt << zone_ns_txt << ns_addrs_txt <<
            delegation_txt << mx_txt << www_a_txt << other_zone_rrs;

        masterLoad(zone_stream, origin_, rrclass_,
                   boost::bind(&MockZone::loadRRset, this, _1));
    }
    virtual const isc::dns::Name& getOrigin() const { return (origin_); }
    virtual const isc::dns::RRClass& getClass() const { return (rrclass_); }
    virtual FindResult find(const isc::dns::Name& name,
                            const isc::dns::RRType& type,
                            const FindOptions options = FIND_DEFAULT) const;

    // If false is passed, it makes the zone broken as if it didn't have the
    // SOA.
    void setSOAFlag(bool on) { has_SOA_ = on; }

    // If false is passed, it makes the zone broken as if it didn't have
    // the apex NS.
    void setApexNSFlag(bool on) { has_apex_NS_ = on; }

private:
    typedef map<RRType, ConstRRsetPtr> RRsetStore;
    typedef map<Name, RRsetStore> Domains;
    Domains domains_;
    void loadRRset(ConstRRsetPtr rrset) {
        domains_[rrset->getName()][rrset->getType()] = rrset;
        if (rrset->getName() == delegation_name_ &&
            rrset->getType() == RRType::NS()) {
            delegation_rrset = rrset;
        }
    }

    const Name origin_;
    const Name delegation_name_;
    bool has_SOA_;
    bool has_apex_NS_;
    ConstRRsetPtr delegation_rrset;
    const RRClass rrclass_;
};

Zone::FindResult
MockZone::find(const Name& name, const RRType& type,
               const FindOptions options) const
{
    // Emulating a broken zone: mandatory apex RRs are missing if specifically
    // configured so (which are rare cases).
    if (name == origin_ && type == RRType::SOA() && !has_SOA_) {
        return (FindResult(NXDOMAIN, RRsetPtr()));
    } else if (name == origin_ && type == RRType::NS() && !has_apex_NS_) {
        return (FindResult(NXDOMAIN, RRsetPtr()));
    }

    // Special case for names on or under a zone cut
    if ((options & FIND_GLUE_OK) == 0 &&
        (name == delegation_name_ ||
         name.compare(delegation_name_).getRelation() ==
         NameComparisonResult::SUBDOMAIN)) {
        return (FindResult(DELEGATION, delegation_rrset));
    }

    // normal cases.  names are searched for only per exact-match basis
    // for simplicity.
    const Domains::const_iterator found_domain = domains_.find(name);
    if (found_domain != domains_.end()) {
        // First, try exact match.
        RRsetStore::const_iterator found_rrset =
            found_domain->second.find(type);
        if (found_rrset != found_domain->second.end()) {
            return (FindResult(SUCCESS, found_rrset->second));
        }

        // If not found but the qtype is ANY, return the first RRset
        if (type == RRType::ANY()) {
            return (FindResult(SUCCESS, found_domain->second.begin()->second));
        }

        // Otherwise, if this domain name has CNAME, return it.
        found_rrset = found_domain->second.find(RRType::CNAME());
        if (found_rrset != found_domain->second.end()) {
            return (FindResult(CNAME, found_rrset->second));
        }

        // Otherwise it's NXRRSET case.
        return (FindResult(NXRRSET, RRsetPtr()));
    }

    // query name isn't found in our domains.  returns NXDOMAIN.
    return (FindResult(NXDOMAIN, RRsetPtr()));
}

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
};

// A wrapper to check resulting response message commonly used in
// tests below.
// check_origin needs to be specified only when the authority section has
// an SOA RR.  The interface is not generic enough but should be okay
// for our test cases in practice.
void
responseCheck(Message& response, const isc::dns::Rcode& rcode,
              unsigned int flags, const unsigned int ancount,
              const unsigned int nscount, const unsigned int arcount,
              const char* const expected_answer,
              const char* const expected_authority,
              const char* const expected_additional,
              const Name& check_origin = Name::ROOT_NAME())
{
    // In our test cases QID, Opcode, and QDCOUNT should be constant, so
    // we don't bother the test cases specifying these values.
    headerCheck(response, response.getQid(), rcode, Opcode::QUERY().getCode(),
                flags, 0, ancount, nscount, arcount);
    if (expected_answer != NULL) {
        rrsetsCheck(expected_answer,
                    response.beginSection(Message::SECTION_ANSWER),
                    response.endSection(Message::SECTION_ANSWER));
    }
    if (expected_authority != NULL) {
        rrsetsCheck(expected_authority,
                    response.beginSection(Message::SECTION_AUTHORITY),
                    response.endSection(Message::SECTION_AUTHORITY),
                    check_origin);
    }
    if (expected_additional != NULL) {
        rrsetsCheck(expected_additional,
                    response.beginSection(Message::SECTION_ADDITIONAL),
                    response.endSection(Message::SECTION_ADDITIONAL));
    }
}

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
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  www_a_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, exactAddrMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_datasrc, Name("noglue.example.com"), qtype,
                          response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 2,
                  "noglue.example.com. 3600 IN A 192.0.2.53\n", zone_ns_txt,
                  "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
                  "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n");
}

TEST_F(QueryTest, apexNSMatch) {
    // find match rrset, omit authority data which has already been provided
    // in the answer section from the authority section.
    EXPECT_NO_THROW(Query(memory_datasrc, Name("example.com"), RRType::NS(),
                          response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 3, 0, 3,
                  zone_ns_txt, NULL, ns_addrs_txt);
}

TEST_F(QueryTest, exactAnyMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_datasrc, Name("noglue.example.com"),
                          RRType::ANY(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 2,
                  "noglue.example.com. 3600 IN A 192.0.2.53\n",
                  zone_ns_txt,
                  "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
                  "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n");
}

// This tests that when we need to look up Zone's apex NS records for
// authoritative answer, and there is no apex NS records. It should
// throw in that case.
TEST_F(QueryTest, noApexNS) {
    // Disable apex NS record
    mock_zone->setApexNSFlag(false);

    EXPECT_THROW(Query(memory_datasrc, Name("noglue.example.com"), qtype,
                       response).process(), Query::NoApexNS);
    // We don't look into the response, as it threw
}

TEST_F(QueryTest, delegation) {
    EXPECT_NO_THROW(Query(memory_datasrc, Name("delegation.example.com"),
                          qtype, response).process());

    responseCheck(response, Rcode::NOERROR(), 0, 0, 4, 3,
                  NULL, delegation_txt, ns_addrs_txt);
}

TEST_F(QueryTest, nxdomain) {
    EXPECT_NO_THROW(Query(memory_datasrc, Name("nxdomain.example.com"), qtype,
                          response).process());
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_zone->getOrigin());
}

TEST_F(QueryTest, nxrrset) {
    EXPECT_NO_THROW(Query(memory_datasrc, Name("www.example.com"),
                          RRType::TXT(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_zone->getOrigin());
}

/*
 * This tests that when there's no SOA and we need a negative answer. It should
 * throw in that case.
 */
TEST_F(QueryTest, noSOA) {
    // disable zone's SOA RR.
    mock_zone->setSOAFlag(false);

    // The NX Domain
    EXPECT_THROW(Query(memory_datasrc, Name("nxdomain.example.com"),
                       qtype, response).process(), Query::NoSOA);
    // Of course, we don't look into the response, as it throwed

    // NXRRSET
    EXPECT_THROW(Query(memory_datasrc, Name("nxrrset.example.com"),
                       qtype, response).process(), Query::NoSOA);
}

TEST_F(QueryTest, noMatchZone) {
    // there's a zone in the memory datasource but it doesn't match the qname.
    // should result in REFUSED.
    Query(memory_datasrc, Name("example.org"), qtype, response).process();;
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

/*
 * Test MX additional processing.
 *
 * The MX RRset has two RRs, one pointing to a known domain with
 * A record, other to unknown out of zone one.
 */
TEST_F(QueryTest, MX) {
    Query(memory_datasrc, Name("mx.example.com"), RRType::MX(),
          response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 3, 3, 4,
                  mx_txt, NULL,
                  (string(ns_addrs_txt) + string(www_a_txt)).c_str());
}

/*
 * Test when we ask for MX whose exchange is an alias (CNAME in this case).
 *
 * This should not trigger the additional processing for the exchange.
 */
TEST_F(QueryTest, MXAlias) {
    Query(memory_datasrc, Name("cnamemx.example.com"), RRType::MX(),
          response).process();

    // there shouldn't be no additional RRs for the exchanges (we have 3
    // RRs for the NS).  The normal MX case is tested separately so we don't
    // bother to examine the answer (and authority) sections.
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  NULL, NULL, ns_addrs_txt);
}
}
