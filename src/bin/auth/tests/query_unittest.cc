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
const char* const cname_txt =
    "cname.example.com. 3600 IN CNAME www.example.com.\n";
const char* const cname_nxdom_txt =
    "cnamenxdom.example.com. 3600 IN CNAME nxdomain.example.com.\n";
// CNAME Leading out of zone
const char* const cname_out_txt =
    "cnameout.example.com. 3600 IN CNAME www.example.org.\n";
// The DNAME to do tests against
const char* const dname_txt =
    "dname.example.com. 3600 IN DNAME "
    "somethinglong.dnametarget.example.com.\n";
// Some data at the dname node (allowed by RFC 2672)
const char* const dname_a_txt =
    "dname.example.com. 3600 IN A 192.0.2.5\n";
// This is not inside the zone, this is created at runtime
const char* const synthetized_cname_txt =
    "www.dname.example.com. 3600 IN CNAME "
    "www.somethinglong.dnametarget.example.com.\n";
// The rest of data won't be referenced from the test cases.
const char* const other_zone_rrs =
    "cnamemailer.example.com. 3600 IN CNAME www.example.com.\n"
    "cnamemx.example.com. 3600 IN MX 10 cnamemailer.example.com.\n"
    "mx.delegation.example.com. 3600 IN A 192.0.2.100\n";

// This is a mock Zone class for testing.
// It is a derived class of ZoneFinder for the convenient of tests.
// Its find() method emulates the common behavior of protocol compliant
// ZoneFinder classes, but simplifies some minor cases and also supports broken
// behavior.
// For simplicity, most names are assumed to be "in zone"; there's only
// one zone cut at the point of name "delegation.example.com".
// Another special name is "dname.example.com".  Query names under this name
// will result in DNAME.
// This mock zone doesn't handle empty non terminal nodes (if we need to test
// such cases find() should have specialized code for it).
class MockZoneFinder : public ZoneFinder {
public:
    MockZoneFinder() :
        origin_(Name("example.com")),
        delegation_name_("delegation.example.com"),
        dname_name_("dname.example.com"),
        has_SOA_(true),
        has_apex_NS_(true),
        rrclass_(RRClass::IN())
    {
        stringstream zone_stream;
        zone_stream << soa_txt << zone_ns_txt << ns_addrs_txt <<
            delegation_txt << mx_txt << www_a_txt << cname_txt <<
            cname_nxdom_txt << cname_out_txt << dname_txt << dname_a_txt <<
            other_zone_rrs;

        masterLoad(zone_stream, origin_, rrclass_,
                   boost::bind(&MockZoneFinder::loadRRset, this, _1));
    }
    virtual isc::dns::Name getOrigin() const { return (origin_); }
    virtual isc::dns::RRClass getClass() const { return (rrclass_); }
    virtual FindResult find(const isc::dns::Name& name,
                            const isc::dns::RRType& type,
                            RRsetList* target = NULL,
                            const FindOptions options = FIND_DEFAULT);

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
    void loadRRset(RRsetPtr rrset) {
        domains_[rrset->getName()][rrset->getType()] = rrset;
        if (rrset->getName() == delegation_name_ &&
            rrset->getType() == RRType::NS()) {
            delegation_rrset_ = rrset;
        } else if (rrset->getName() == dname_name_ &&
            rrset->getType() == RRType::DNAME()) {
            dname_rrset_ = rrset;
        // Add some signatures
        } else if (rrset->getName() == Name("example.com.") &&
                   rrset->getType() == RRType::NS()) {
            rrset->addRRsig(RdataPtr(new generic::RRSIG("NS 5 3 3600 "
                                                        "20000101000000 "
                                                        "20000201000000 "
                                                        "12345 example.com. "
                                                        "FAKEFAKEFAKE")));
        } else if (rrset->getType() == RRType::A()) {
            rrset->addRRsig(RdataPtr(new generic::RRSIG("A 5 3 3600 "
                                                        "20000101000000 "
                                                        "20000201000000 "
                                                        "12345 example.com. "
                                                        "FAKEFAKEFAKE")));
        } else if (rrset->getType() == RRType::AAAA()) {
            rrset->addRRsig(RdataPtr(new generic::RRSIG("AAAA 5 3 3600 "
                                                        "20000101000000 "
                                                        "20000201000000 "
                                                        "12345 example.com. "
                                                        "FAKEFAKEFAKE")));
        }
    }

    const Name origin_;
    // Names where we delegate somewhere else
    const Name delegation_name_;
    const Name dname_name_;
    bool has_SOA_;
    bool has_apex_NS_;
    ConstRRsetPtr delegation_rrset_;
    ConstRRsetPtr dname_rrset_;
    const RRClass rrclass_;
};

ZoneFinder::FindResult
MockZoneFinder::find(const Name& name, const RRType& type,
                     RRsetList* target, const FindOptions options)
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
        return (FindResult(DELEGATION, delegation_rrset_));
    // And under DNAME
    } else if (name.compare(dname_name_).getRelation() ==
        NameComparisonResult::SUBDOMAIN) {
        return (FindResult(DNAME, dname_rrset_));
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

        // If not found but we have a target, fill it with all RRsets here
        if (!found_domain->second.empty() && target != NULL) {
            for (found_rrset = found_domain->second.begin();
                 found_rrset != found_domain->second.end(); ++found_rrset) {
                // Insert RRs under the domain name into target
                target->addRRset(
                    boost::const_pointer_cast<RRset>(found_rrset->second));
            }
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
        mock_finder = new MockZoneFinder();
        memory_client.addZone(ZoneFinderPtr(mock_finder));
    }
    MockZoneFinder* mock_finder;
    // We use InMemoryClient here. We could have some kind of mock client
    // here, but historically, the Query supported only InMemoryClient
    // (originally named MemoryDataSrc) and was tested with it, so we keep
    // it like this for now.
    InMemoryClient memory_client;
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
                    response.endSection(Message::SECTION_ANSWER),
                    check_origin);
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
    InMemoryClient empty_memory_client;
    Query nozone_query(empty_memory_client, qname, qtype, response);
    EXPECT_NO_THROW(nozone_query.process());
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

TEST_F(QueryTest, exactMatch) {
    Query query(memory_client, qname, qtype, response);
    EXPECT_NO_THROW(query.process());
    // find match rrset
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  www_a_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, dnssecPositive) {
    // Just like exactMatch, but the signatures should be included as well
    Query query(memory_client, qname, qtype, response, true);
    EXPECT_NO_THROW(query.process());
    // find match rrset
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  (www_a_txt + std::string("www.example.com. 3600 IN RRSIG "
                                           "AAAA 5 3 3600 20000101000000 "
                                           "20000201000000 12345 example.com. "
                                           "FAKEFAKEFAKE\n")).c_str(),
                  (zone_ns_txt + std::string("example.com. 3600 IN RRSIG NS 5 "
                                             "3 3600 20000101000000 "
                                             "20000201000000 12345 "
                                             "example.com. FAKEFAKEFAKE\n")).
                  c_str(),
                  (ns_addrs_txt + std::string("glue.delegation.example.com. "
                                              "3600 IN RRSIG A 5 3 3600 "
                                              "20000101000000 20000201000000 "
                                              "12345 example.com. "
                                              "FAKEFAKEFAKE\n"
                                              "glue.delegation.example.com. "
                                              "3600 IN RRSIG AAAA 5 3 3600 "
                                              "20000101000000 20000201000000 "
                                              "12345 example.com. "
                                              "FAKEFAKEFAKE\n"
                                              "noglue.example.com. 3600 IN "
                                              "RRSIG A 5 3 3600 "
                                              "20000101000000 20000201000000 "
                                              "12345 example.com. "
                                              "FAKEFAKEFAKE\n")).c_str());
}

TEST_F(QueryTest, exactAddrMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_client, Name("noglue.example.com"), qtype,
                          response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 2,
                  "noglue.example.com. 3600 IN A 192.0.2.53\n", zone_ns_txt,
                  "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
                  "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n");
}

TEST_F(QueryTest, apexNSMatch) {
    // find match rrset, omit authority data which has already been provided
    // in the answer section from the authority section.
    EXPECT_NO_THROW(Query(memory_client, Name("example.com"), RRType::NS(),
                          response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 3, 0, 3,
                  zone_ns_txt, NULL, ns_addrs_txt);
}

// test type any query logic
TEST_F(QueryTest, exactAnyMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_client, Name("noglue.example.com"),
                          RRType::ANY(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 2,
                  "noglue.example.com. 3600 IN A 192.0.2.53\n",
                  zone_ns_txt,
                  "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
                  "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n");
}

TEST_F(QueryTest, apexAnyMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_client, Name("example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 4, 0, 3,
                  "example.com. 3600 IN SOA . . 0 0 0 0 0\n"
                  "example.com. 3600 IN NS glue.delegation.example.com.\n"
                  "example.com. 3600 IN NS noglue.example.com.\n"
                  "example.com. 3600 IN NS example.net.\n",
                  NULL, ns_addrs_txt, mock_finder->getOrigin());
}

TEST_F(QueryTest, mxANYMatch) {
    EXPECT_NO_THROW(Query(memory_client, Name("mx.example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 3, 3, 4,
                  mx_txt, zone_ns_txt,
                  (string(ns_addrs_txt) + string(www_a_txt)).c_str());
}

TEST_F(QueryTest, glueANYMatch) {
    EXPECT_NO_THROW(Query(memory_client, Name("delegation.example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NOERROR(), 0, 0, 4, 3,
                  NULL, delegation_txt, ns_addrs_txt);
}

TEST_F(QueryTest, nodomainANY) {
    EXPECT_NO_THROW(Query(memory_client, Name("nxdomain.example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_finder->getOrigin());
}

// This tests that when we need to look up Zone's apex NS records for
// authoritative answer, and there is no apex NS records. It should
// throw in that case.
TEST_F(QueryTest, noApexNS) {
    // Disable apex NS record
    mock_finder->setApexNSFlag(false);

    EXPECT_THROW(Query(memory_client, Name("noglue.example.com"), qtype,
                       response).process(), Query::NoApexNS);
    // We don't look into the response, as it threw
}

TEST_F(QueryTest, delegation) {
    EXPECT_NO_THROW(Query(memory_client, Name("delegation.example.com"),
                          qtype, response).process());

    responseCheck(response, Rcode::NOERROR(), 0, 0, 4, 3,
                  NULL, delegation_txt, ns_addrs_txt);
}

TEST_F(QueryTest, nxdomain) {
    EXPECT_NO_THROW(Query(memory_client, Name("nxdomain.example.com"), qtype,
                          response).process());
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxrrset) {
    EXPECT_NO_THROW(Query(memory_client, Name("www.example.com"),
                          RRType::TXT(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_finder->getOrigin());
}

/*
 * This tests that when there's no SOA and we need a negative answer. It should
 * throw in that case.
 */
TEST_F(QueryTest, noSOA) {
    // disable zone's SOA RR.
    mock_finder->setSOAFlag(false);

    // The NX Domain
    EXPECT_THROW(Query(memory_client, Name("nxdomain.example.com"),
                       qtype, response).process(), Query::NoSOA);
    // Of course, we don't look into the response, as it throwed

    // NXRRSET
    EXPECT_THROW(Query(memory_client, Name("nxrrset.example.com"),
                       qtype, response).process(), Query::NoSOA);
}

TEST_F(QueryTest, noMatchZone) {
    // there's a zone in the memory datasource but it doesn't match the qname.
    // should result in REFUSED.
    Query(memory_client, Name("example.org"), qtype, response).process();
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

/*
 * Test MX additional processing.
 *
 * The MX RRset has two RRs, one pointing to a known domain with
 * A record, other to unknown out of zone one.
 */
TEST_F(QueryTest, MX) {
    Query(memory_client, Name("mx.example.com"), RRType::MX(),
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
    Query(memory_client, Name("cnamemx.example.com"), RRType::MX(),
          response).process();

    // there shouldn't be no additional RRs for the exchanges (we have 3
    // RRs for the NS).  The normal MX case is tested separately so we don't
    // bother to examine the answer (and authority) sections.
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  NULL, NULL, ns_addrs_txt);
}

/*
 * Tests encountering a cname.
 *
 * There are tests leading to successful answers, NXRRSET, NXDOMAIN and
 * out of the zone.
 *
 * TODO: We currently don't do chaining, so only the CNAME itself should be
 * returned.
 */
TEST_F(QueryTest, CNAME) {
    Query(memory_client, Name("cname.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME) {
    // same owner name as the CNAME test but explicitly query for CNAME RR.
    // expect the same response as we don't provide a full chain yet.
    Query(memory_client, Name("cname.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, CNAME_NX_RRSET) {
    // Leads to www.example.com, it doesn't have TXT
    // note: with chaining, what should be expected is not trivial:
    // BIND 9 returns the CNAME in answer and SOA in authority, no additional.
    // NSD returns the CNAME, NS in authority, A/AAAA for NS in additional.
    Query(memory_client, Name("cname.example.com"), RRType::TXT(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME_NX_RRSET) {
    // same owner name as the NXRRSET test but explicitly query for CNAME RR.
    Query(memory_client, Name("cname.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, CNAME_NX_DOMAIN) {
    // Leads to nxdomain.example.com
    // note: with chaining, what should be expected is not trivial:
    // BIND 9 returns the CNAME in answer and SOA in authority, no additional,
    // RCODE being NXDOMAIN.
    // NSD returns the CNAME, NS in authority, A/AAAA for NS in additional,
    // RCODE being NOERROR.
    Query(memory_client, Name("cnamenxdom.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_nxdom_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME_NX_DOMAIN) {
    // same owner name as the NXDOMAIN test but explicitly query for CNAME RR.
    Query(memory_client, Name("cnamenxdom.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_nxdom_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, CNAME_OUT) {
    /*
     * This leads out of zone. This should have only the CNAME even
     * when we do chaining.
     *
     * TODO: We should be able to have two zones in the mock data source.
     * Then the same test should be done with .org included there and
     * see what it does (depends on what we want to do)
     */
    Query(memory_client, Name("cnameout.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_out_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME_OUT) {
    // same owner name as the OUT test but explicitly query for CNAME RR.
    Query(memory_client, Name("cnameout.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_out_txt, zone_ns_txt, ns_addrs_txt);
}

/*
 * Test a query under a domain with DNAME. We should get a synthetized CNAME
 * as well as the DNAME.
 *
 * TODO: Once we have CNAME chaining, check it works with synthetized CNAMEs
 * as well. This includes tests pointing inside the zone, outside the zone,
 * pointing to NXRRSET and NXDOMAIN cases (similarly as with CNAME).
 */
TEST_F(QueryTest, DNAME) {
    Query(memory_client, Name("www.dname.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 0, 0,
        (string(dname_txt) + synthetized_cname_txt).c_str(),
        NULL, NULL);
}

/*
 * Ask an ANY query below a DNAME. Should return the DNAME and synthetized
 * CNAME.
 *
 * ANY is handled specially sometimes. We check it is not the case with
 * DNAME.
 */
TEST_F(QueryTest, DNAME_ANY) {
    Query(memory_client, Name("www.dname.example.com"), RRType::ANY(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 0, 0,
        (string(dname_txt) + synthetized_cname_txt).c_str(), NULL, NULL);
}

// Test when we ask for DNAME explicitly, it does no synthetizing.
TEST_F(QueryTest, explicitDNAME) {
    Query(memory_client, Name("dname.example.com"), RRType::DNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        dname_txt, zone_ns_txt, ns_addrs_txt);
}

/*
 * Request a RRset at the domain with DNAME. It should not synthetize
 * the CNAME, it should return the RRset.
 */
TEST_F(QueryTest, DNAME_A) {
    Query(memory_client, Name("dname.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        dname_a_txt, zone_ns_txt, ns_addrs_txt);
}

/*
 * Request a RRset at the domain with DNAME that is not there (NXRRSET).
 * It should not synthetize the CNAME.
 */
TEST_F(QueryTest, DNAME_NX_RRSET) {
    EXPECT_NO_THROW(Query(memory_client, Name("dname.example.com"),
        RRType::TXT(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 1, 0,
        NULL, soa_txt, NULL, mock_finder->getOrigin());
}

/*
 * Constructing the CNAME will result in a name that is too long. This,
 * however, should not throw (and crash the server), but respond with
 * YXDOMAIN.
 */
TEST_F(QueryTest, LongDNAME) {
    // A name that is as long as it can be
    Name longname(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "dname.example.com.");
    EXPECT_NO_THROW(Query(memory_client, longname, RRType::A(),
        response).process());

    responseCheck(response, Rcode::YXDOMAIN(), AA_FLAG, 1, 0, 0,
        dname_txt, NULL, NULL);
}

/*
 * Constructing the CNAME will result in a name of maximal length.
 * This tests that we don't reject valid one by some kind of off by
 * one mistake.
 */
TEST_F(QueryTest, MaxLenDNAME) {
    Name longname(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "dname.example.com.");
    EXPECT_NO_THROW(Query(memory_client, longname, RRType::A(),
        response).process());

    // Check the answer is OK
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 0, 0,
        NULL, NULL, NULL);

    // Check that the CNAME has the maximal length.
    bool ok(false);
    for (RRsetIterator i(response.beginSection(Message::SECTION_ANSWER));
        i != response.endSection(Message::SECTION_ANSWER); ++ i) {
        if ((*i)->getType() == RRType::CNAME()) {
            ok = true;
            RdataIteratorPtr ci((*i)->getRdataIterator());
            ASSERT_FALSE(ci->isLast()) << "The CNAME is empty";
            /*
             * Does anybody have a clue why, if the Name::MAX_WIRE is put
             * directly inside ASSERT_EQ, it fails to link and complains
             * it is unresolved external?
             */
            const size_t max_len(Name::MAX_WIRE);
            ASSERT_EQ(max_len, dynamic_cast<const rdata::generic::CNAME&>(
                ci->getCurrent()).getCname().getLength());
        }
    }
    EXPECT_TRUE(ok) << "The synthetized CNAME not found";
}

}
