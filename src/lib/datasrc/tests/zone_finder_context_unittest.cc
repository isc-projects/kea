// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/zone.h>
#include <datasrc/memory_datasrc.h>
#include <datasrc/database.h>
#include <datasrc/sqlite3_accessor.h>

#include "test_client.h"
#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using boost::shared_ptr;

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::testutils;

namespace {

// Commonly used test zone file.
const char* const TEST_ZONE_FILE = TEST_DATA_DIR "/contexttest.zone";

// Convenient shortcut
typedef shared_ptr<DataSourceClient> DataSourceClientPtr;

// This is the type used as the test parameter.  Note that this is
// intentionally a plain old type (i.e. a function pointer), not a class;
// otherwise it could cause initialization fiasco at the instantiation time.
typedef DataSourceClientPtr (*ClientCreator)(RRClass, const Name&);

// Creator for the in-memory client to be tested
DataSourceClientPtr
createInMemoryClient(RRClass zclass, const Name& zname) {
    shared_ptr<InMemoryClient> client(new InMemoryClient);

    shared_ptr<InMemoryZoneFinder> finder(
        new InMemoryZoneFinder(zclass, zname));
    finder->load(TEST_ZONE_FILE);

    client->addZone(finder);

    return (client);
}

void
addRRset(ZoneUpdaterPtr updater, ConstRRsetPtr rrset) {
    updater->addRRset(*rrset);
}

DataSourceClientPtr
createSQLite3Client(RRClass zclass, const Name& zname) {
    // We always begin with an empty template SQLite3 DB file and install
    // the zone data from the zone file to ensure both cases have the
    // same test data.
    DataSourceClientPtr client = unittest::createSQLite3Client(
        zclass, zname, TEST_DATA_BUILDDIR "/contexttest.sqlite3.copied",
        TEST_ZONE_FILE);

    // Insert an out-of-zone name to test if it's incorrectly returned.
    // Note that neither updater nor SQLite3 accessor checks this condition,
    // so this should succeed.
    ZoneUpdaterPtr updater = client->getUpdater(zname, false);
    stringstream ss("ns.example.com. 3600 IN A 192.0.2.7");
    masterLoad(ss, Name::ROOT_NAME(), zclass,
               boost::bind(addRRset, updater, _1));
    updater->commit();

    return (client);
}

// The test class.  Its parameterized so we can share the test scnearios
// for any concrete data source implementaitons.
class ZoneFinderContextTest :
        public ::testing::TestWithParam<ClientCreator>
{
protected:
    ZoneFinderContextTest() : qclass_(RRClass::IN()), qzone_("example.org") {
        client_ = (*GetParam())(qclass_, qzone_);
        REQUESTED_A.push_back(RRType::A());
        REQUESTED_AAAA.push_back(RRType::AAAA());
        REQUESTED_BOTH.push_back(RRType::A());
        REQUESTED_BOTH.push_back(RRType::AAAA());
    }
    void SetUp() {
        finder_ = client_->findZone(qzone_).zone_finder;
        ASSERT_TRUE(finder_);
    }

    const RRClass qclass_;
    const Name qzone_;
    DataSourceClientPtr client_;
    ZoneFinderPtr finder_;

    vector<RRType> requested_types_;
    vector<RRType> REQUESTED_A;
    vector<RRType> REQUESTED_AAAA;
    vector<RRType> REQUESTED_BOTH;
    vector<ConstRRsetPtr> result_sets_;
};

// We test the in-memory and SQLite3 data source implementations.
INSTANTIATE_TEST_CASE_P(, ZoneFinderContextTest,
                        ::testing::Values(createInMemoryClient,
                                          createSQLite3Client));

TEST_P(ZoneFinderContextTest, getAdditionalAuthNS) {
    ZoneFinderContextPtr ctx = finder_->find(qzone_, RRType::NS());
    EXPECT_EQ(ZoneFinder::SUCCESS, ctx->code);

    // Getting both A and AAAA NS addresses
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("ns1.example.org. 3600 IN A 192.0.2.1\n"
                "ns1.example.org. 3600 IN AAAA 2001:db8::1\n"
                "ns2.example.org. 3600 IN A 192.0.2.2\n",
                result_sets_.begin(), result_sets_.end());

    // Getting only A
    result_sets_.clear();
    ctx->getAdditional(REQUESTED_A, result_sets_);
    rrsetsCheck("ns1.example.org. 3600 IN A 192.0.2.1\n"
                "ns2.example.org. 3600 IN A 192.0.2.2\n",
                result_sets_.begin(), result_sets_.end());

    // Getting only AAAA
    result_sets_.clear();
    ctx->getAdditional(REQUESTED_AAAA, result_sets_);
    rrsetsCheck("ns1.example.org. 3600 IN AAAA 2001:db8::1\n",
                result_sets_.begin(), result_sets_.end());

    // Getting A again, without clearing the result sets.  This confirms
    // getAdditional() doesn't change the existing vector content.
    ctx->getAdditional(REQUESTED_A, result_sets_);
    // The first element should be the existing AAAA RR, followed by the A's.
    EXPECT_EQ(RRType::AAAA(), result_sets_[0]->getType());
    rrsetsCheck("ns1.example.org. 3600 IN AAAA 2001:db8::1\n"
                "ns1.example.org. 3600 IN A 192.0.2.1\n"
                "ns2.example.org. 3600 IN A 192.0.2.2\n",
                result_sets_.begin(), result_sets_.end());

    // Normally expected type set contain only A and/or AAAA, but others aren't
    // excluded.
    result_sets_.clear();
    requested_types_.push_back(RRType::TXT());
    ctx->getAdditional(requested_types_, result_sets_);
    rrsetsCheck("ns2.example.org. 3600 IN TXT \"text data\"",
                result_sets_.begin(), result_sets_.end());

    // Even empty set is okay.  The result should also be empty.
    result_sets_.clear();
    ctx->getAdditional(vector<RRType>(), result_sets_);
    EXPECT_TRUE(result_sets_.empty());
}

TEST_P(ZoneFinderContextTest, getAdditionalDelegation) {
    // Basically similar to the AuthNS case, but NS names are glues.
    // It contains an out-of-zone NS name.  Its address (even if it's somehow
    // inserted to the zone data) shouldn't be returned.
    const Name qname("www.a.example.org");
    ZoneFinderContextPtr ctx = finder_->find(qname, RRType::AAAA());
    EXPECT_EQ(ZoneFinder::DELEGATION, ctx->code);

    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("ns1.a.example.org. 3600 IN A 192.0.2.5\n"
                "ns2.a.example.org. 3600 IN A 192.0.2.6\n"
                "ns2.a.example.org. 3600 IN AAAA 2001:db8::6\n",
                result_sets_.begin(), result_sets_.end());

    result_sets_.clear();
    ctx->getAdditional(REQUESTED_A, result_sets_);
    rrsetsCheck("ns1.a.example.org. 3600 IN A 192.0.2.5\n"
                "ns2.a.example.org. 3600 IN A 192.0.2.6\n",
                result_sets_.begin(), result_sets_.end());

    result_sets_.clear();
    ctx->getAdditional(REQUESTED_AAAA, result_sets_);
    rrsetsCheck("ns2.a.example.org. 3600 IN AAAA 2001:db8::6\n",
                result_sets_.begin(), result_sets_.end());
}

TEST_P(ZoneFinderContextTest, getAdditionalDelegationAtZoneCut) {
    // Similar to the previous case, but one of the NS addresses is at the
    // zone cut.
    ZoneFinderContextPtr ctx = finder_->find(Name("www.b.example.org"),
                                             RRType::SOA());
    EXPECT_EQ(ZoneFinder::DELEGATION, ctx->code);

    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("b.example.org. 3600 IN AAAA 2001:db8::8\n"
                "ns.b.example.org. 3600 IN A 192.0.2.9\n",
                result_sets_.begin(), result_sets_.end());
}

TEST_P(ZoneFinderContextTest, getAdditionalDelegationWithDname) {
    // Delegation: One of the NS names under a DNAME delegation; another
    // is at the delegation point; yet another is under DNAME below a zone cut.
    // The first should be hidden.
    ZoneFinderContextPtr ctx = finder_->find(Name("www.c.example.org"),
                                             RRType::TXT());
    EXPECT_EQ(ZoneFinder::DELEGATION, ctx->code);

    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("dname.example.org. 3600 IN A 192.0.2.12\n"
                "ns.deepdname.example.org. 3600 IN AAAA 2001:db8::9\n",
                result_sets_.begin(), result_sets_.end());
}

TEST_P(ZoneFinderContextTest, getAdditionalDelegationWithEmptyName) {
    // One of NS names is at an empty non terminal node.  It shouldn't cause
    // any disruption.
    ZoneFinderContextPtr ctx = finder_->find(Name("www.d.example.org"),
                                             RRType::A());
    EXPECT_EQ(ZoneFinder::DELEGATION, ctx->code);

    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("ns1.example.org. 3600 IN A 192.0.2.1\n"
                "ns1.example.org. 3600 IN AAAA 2001:db8::1\n",
                result_sets_.begin(), result_sets_.end());
}

TEST_P(ZoneFinderContextTest, getAdditionalDelegationWithWild) {
    // An NS name needs to be expanded by a wildcard.  Another NS name
    // also matches a wildcard, but it's an empty node, so there's no
    // corresponding additional RR.  The other NS name isn't subject to
    // wildcard expansion, which shouldn't cause any disruption.
    ZoneFinderContextPtr ctx = finder_->find(Name("www.e.example.org"),
                                             RRType::AAAA());
    EXPECT_EQ(ZoneFinder::DELEGATION, ctx->code);
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("ns.wild.example.org. 3600 IN A 192.0.2.15\n"
                "ns2.example.org. 3600 IN A 192.0.2.2\n",
                result_sets_.begin(), result_sets_.end());

    // ns.wild.example.org/A (expanded from a wildcard) should be considered
    // the same kind, whether it's a direct result of find() or a result of
    // getAdditional().
    ctx = finder_->find(Name("ns.wild.example.org"), RRType::A());
    EXPECT_EQ(ZoneFinder::SUCCESS, ctx->code);
    for (vector<ConstRRsetPtr>::const_iterator it = result_sets_.begin();
         it != result_sets_.end(); ++it) {
        const bool same_kind = (*it)->isSameKind(*ctx->rrset);
        EXPECT_EQ((*it)->getName() == ctx->rrset->getName(), same_kind);
    }
}

TEST_P(ZoneFinderContextTest, getAdditionalDelegationForWild) {
    // additional for an answer RRset (MX) as a result of wildcard expansion.
    // note the difference from the previous test.  in this case wildcard
    // applies to the owner name of the answer, not the owner name of the
    // additional.
    ZoneFinderContextPtr ctx = finder_->find(Name("mx.wildmx.example.org"),
                                             RRType::MX());
    EXPECT_EQ(ZoneFinder::SUCCESS, ctx->code);
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("mx1.example.org. 3600 IN A 192.0.2.10\n",
                result_sets_.begin(), result_sets_.end());
}

TEST_P(ZoneFinderContextTest, getAdditionalMX) {
    // Similar to the previous cases, but for MX addresses.  The test zone
    // contains MX name under a zone cut.  Its address shouldn't be returned.
    ZoneFinderContextPtr ctx = finder_->find(qzone_, RRType::MX());
    EXPECT_EQ(ZoneFinder::SUCCESS, ctx->code);

    // Getting both A and AAAA NS addresses
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("mx1.example.org. 3600 IN A 192.0.2.10\n"
                "mx2.example.org. 3600 IN AAAA 2001:db8::10\n",
                result_sets_.begin(), result_sets_.end());

    // Getting only A
    result_sets_.clear();
    ctx->getAdditional(REQUESTED_A, result_sets_);
    rrsetsCheck("mx1.example.org. 3600 IN A 192.0.2.10\n",
                result_sets_.begin(), result_sets_.end());

    // Getting only AAAA
    result_sets_.clear();
    ctx->getAdditional(REQUESTED_AAAA, result_sets_);
    rrsetsCheck("mx2.example.org. 3600 IN AAAA 2001:db8::10\n",
                result_sets_.begin(), result_sets_.end());
}

TEST_P(ZoneFinderContextTest, getAdditionalMXAtZoneCut) {
    ZoneFinderContextPtr ctx = finder_->find(Name("mxatcut.example.org."),
                                             RRType::MX());
    EXPECT_EQ(ZoneFinder::SUCCESS, ctx->code);

    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    EXPECT_TRUE(result_sets_.empty());
}

TEST_P(ZoneFinderContextTest, getAdditionalWithSIG) {
    // Similar to the AuthNS test, but the original find() requested DNSSEC
    // RRSIGs.  Then additional records will also have RRSIGs.
    ZoneFinderContextPtr ctx = finder_->find(qzone_, RRType::NS(),
                                             ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, ctx->code);

    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("ns1.example.org. 3600 IN A 192.0.2.1\n"
                "ns1.example.org. 3600 IN AAAA 2001:db8::1\n"
                "ns2.example.org. 3600 IN A 192.0.2.2\n",
                result_sets_.begin(), result_sets_.end());

    vector<ConstRRsetPtr> sigresult_sets;
    BOOST_FOREACH(ConstRRsetPtr rrset, result_sets_) {
        ConstRRsetPtr sig_rrset = rrset->getRRsig();
        if (sig_rrset) {
            sigresult_sets.push_back(sig_rrset);
        }
    }
    rrsetsCheck("ns1.example.org. 3600 IN RRSIG	A 7 3 3600 20150420235959 "
                "20051021000000 40430 example.org. FAKEFAKE\n"
                "ns1.example.org. 3600 IN RRSIG	AAAA 7 3 3600 20150420235959 "
                "20051021000000 40430 example.org. FAKEFAKEFAKE\n",
                sigresult_sets.begin(), sigresult_sets.end());
}

TEST_P(ZoneFinderContextTest, getAdditionalNoOP) {
    // getAdditional() is only meaningful after SUCCESS or DELEGATION.

    ZoneFinderContextPtr ctx = finder_->find(Name("nxdomain.example.org"),
                                             RRType::NS());
    EXPECT_EQ(ZoneFinder::NXDOMAIN, ctx->code);
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    EXPECT_TRUE(result_sets_.empty());

    ctx = finder_->find(qzone_, RRType::TXT());
    EXPECT_EQ(ZoneFinder::NXRRSET, ctx->code);
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    EXPECT_TRUE(result_sets_.empty());

    ctx = finder_->find(Name("alias.example.org."), RRType::A());
    EXPECT_EQ(ZoneFinder::CNAME, ctx->code);
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    EXPECT_TRUE(result_sets_.empty());

    ctx = finder_->find(Name("www.dname.example.org."), RRType::A());
    EXPECT_EQ(ZoneFinder::DNAME, ctx->code);
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    EXPECT_TRUE(result_sets_.empty());
}

TEST_P(ZoneFinderContextTest, getAdditionalForAny) {
    // getAdditional() after successful type ANY query should return
    // the additional records of all returned RRsets.
    vector<ConstRRsetPtr> all_rrsets;
    ZoneFinderContextPtr ctx = finder_->findAll(qzone_, all_rrsets);
    EXPECT_EQ(ZoneFinder::SUCCESS, ctx->code);

    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("ns1.example.org. 3600 IN A 192.0.2.1\n"
                "ns1.example.org. 3600 IN AAAA 2001:db8::1\n"
                "ns2.example.org. 3600 IN A 192.0.2.2\n"
                "mx1.example.org. 3600 IN A 192.0.2.10\n"
                "mx2.example.org. 3600 IN AAAA 2001:db8::10\n",
                result_sets_.begin(), result_sets_.end());

    // If the type ANY query results in DELEGATION, the result should be the
    // same as normal query.
    all_rrsets.clear();
    result_sets_.clear();
    ctx = finder_->findAll(Name("www.a.example.org"), all_rrsets);
    EXPECT_EQ(ZoneFinder::DELEGATION, ctx->code);
    ctx->getAdditional(REQUESTED_BOTH, result_sets_);
    rrsetsCheck("ns1.a.example.org. 3600 IN A 192.0.2.5\n"
                "ns2.a.example.org. 3600 IN A 192.0.2.6\n"
                "ns2.a.example.org. 3600 IN AAAA 2001:db8::6\n",
                result_sets_.begin(), result_sets_.end());
}

}
