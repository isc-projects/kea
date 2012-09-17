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
#include <config.h>
#include <string>
#include <gtest/gtest.h>
#include <dns/rrset.h>
#include <dns/rcode.h>
#include "resolver_cache.h"
#include "cache_test_messagefromfile.h"

using namespace isc::cache;
using namespace isc::dns;
using namespace std;

namespace {

class NegativeCacheTest: public testing::Test{
public:
    NegativeCacheTest() {
        vector<CacheSizeInfo> vec;
        CacheSizeInfo class_in(RRClass::IN(), 100, 200);
        vec.push_back(class_in);
        cache = new ResolverCache(vec);
    }

    ~NegativeCacheTest() {
        delete cache;
    }

    ResolverCache *cache;
};

TEST_F(NegativeCacheTest, testNXDOMAIN){
    // NXDOMAIN response for nonexist.example.com
    Message msg_nxdomain(Message::PARSE);
    messageFromFile(msg_nxdomain, "message_nxdomain_with_soa.wire");
    cache->update(msg_nxdomain);

    msg_nxdomain.makeResponse();

    Name non_exist_qname("nonexist.example.com.");
    EXPECT_TRUE(cache->lookup(non_exist_qname, RRType::A(), RRClass::IN(),
                msg_nxdomain));

    RRsetIterator iter = msg_nxdomain.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset_ptr = *iter;

    // The TTL should equal to the TTL of SOA record
    const RRTTL& nxdomain_ttl1 = rrset_ptr->getTTL();
    // May have already crossed seconds boundary
    EXPECT_GE(nxdomain_ttl1.getValue(), 86399);
    EXPECT_LE(nxdomain_ttl1.getValue(), 86400);

    // SOA response for example.com
    Message msg_example_com_soa(Message::PARSE);
    messageFromFile(msg_example_com_soa, "message_example_com_soa.wire");
    cache->update(msg_example_com_soa);

    msg_example_com_soa.makeResponse();
    Name soa_qname("example.com.");
    EXPECT_TRUE(cache->lookup(soa_qname, RRType::SOA(), RRClass::IN(),
                msg_example_com_soa));

    iter = msg_example_com_soa.beginSection(Message::SECTION_ANSWER);
    rrset_ptr = *iter;

    // The TTL should equal to the TTL of SOA record in answer section
    const RRTTL& soa_ttl = rrset_ptr->getTTL();
    // May have already crossed seconds boundary
    EXPECT_GE(soa_ttl.getValue(), 172799);
    EXPECT_LE(soa_ttl.getValue(), 172800);

    // Sleep for 2 seconds. 2 seconds to make sure the final range check
    // does not overlap with the original ones (in which case this test
    // would erroneously pass if the ttl value is not changed)
    sleep(2);

    // Query nonexist.example.com again
    Message msg_nxdomain2(Message::PARSE);
    messageFromFile(msg_nxdomain2, "message_nxdomain_with_soa.wire");
    msg_nxdomain2.makeResponse();

    EXPECT_TRUE(cache->lookup(non_exist_qname, RRType::A(), RRClass::IN(), msg_nxdomain2));
    iter = msg_nxdomain2.beginSection(Message::SECTION_AUTHORITY);
    rrset_ptr = *iter;

    // The TTL should equal to the TTL of negative response SOA record
    // Allow for three second range.
    const RRTTL& nxdomain_ttl2 = rrset_ptr->getTTL();
    EXPECT_GE(nxdomain_ttl2.getValue(), 86396);
    EXPECT_LE(nxdomain_ttl2.getValue(), 86398);
    // No RRset in ANSWER section
    EXPECT_TRUE(msg_nxdomain2.getRRCount(Message::SECTION_ANSWER) == 0);
    // Check that only one SOA record exist in AUTHORITY section
    EXPECT_TRUE(msg_nxdomain2.getRRCount(Message::SECTION_AUTHORITY) == 1);
    iter = msg_nxdomain2.beginSection(Message::SECTION_AUTHORITY);
    rrset_ptr = *iter;
    EXPECT_TRUE(rrset_ptr->getType() == RRType::SOA());

    // Check the normal SOA cache again
    Message msg_example_com_soa2(Message::PARSE);
    messageFromFile(msg_example_com_soa2, "message_example_com_soa.wire");
    msg_example_com_soa2.makeResponse();
    EXPECT_TRUE(cache->lookup(soa_qname, RRType::SOA(), RRClass::IN(),
                              msg_example_com_soa2));

    iter = msg_example_com_soa2.beginSection(Message::SECTION_ANSWER);
    rrset_ptr = *iter;
    const RRTTL& soa_ttl2 = rrset_ptr->getTTL();
    // The TTL should equal to the TTL of SOA record in answer section
    // Allow for three second range.
    EXPECT_GE(soa_ttl2.getValue(), 172796);
    EXPECT_LE(soa_ttl2.getValue(), 172798);
}

TEST_F(NegativeCacheTest, testNXDOMAINWithoutSOA){
    // NXDOMAIN response for nonexist.example.com
    Message msg_nxdomain(Message::PARSE);
    messageFromFile(msg_nxdomain, "message_nxdomain_no_soa.wire");
    cache->update(msg_nxdomain);

    msg_nxdomain.makeResponse();

    Name non_exist_qname("nonexist.example.com.");
    // The message should not be cached
    EXPECT_FALSE(cache->lookup(non_exist_qname, RRType::A(), RRClass::IN(), msg_nxdomain));
}

TEST_F(NegativeCacheTest, testNXDOMAINCname){
    // a.example.org points to b.example.org
    // b.example.org points to c.example.org
    // c.example.org does not exist
    Message msg_nxdomain_cname(Message::PARSE);
    messageFromFile(msg_nxdomain_cname, "message_nxdomain_cname.wire");
    cache->update(msg_nxdomain_cname);

    msg_nxdomain_cname.makeResponse();

    Name a_example_org("a.example.org.");
    // The message should be cached
    EXPECT_TRUE(cache->lookup(a_example_org, RRType::A(), RRClass::IN(), msg_nxdomain_cname));

    EXPECT_EQ(msg_nxdomain_cname.getRcode().getCode(), Rcode::NXDOMAIN().getCode());

    // It should include 2 CNAME records in Answer section
    EXPECT_TRUE(msg_nxdomain_cname.getRRCount(Message::SECTION_ANSWER) == 2);
    RRsetIterator iter = msg_nxdomain_cname.beginSection(Message::SECTION_ANSWER);
    EXPECT_TRUE((*iter)->getType() == RRType::CNAME());
    ++iter;
    EXPECT_TRUE((*iter)->getType() == RRType::CNAME());

    // It should include 1 SOA record in Authority section
    EXPECT_TRUE(msg_nxdomain_cname.getRRCount(Message::SECTION_AUTHORITY) == 1);
    iter = msg_nxdomain_cname.beginSection(Message::SECTION_AUTHORITY);
    EXPECT_TRUE((*iter)->getType() == RRType::SOA());

    const RRTTL& soa_ttl = (*iter)->getTTL();
    EXPECT_EQ(soa_ttl.getValue(), 600);
}

TEST_F(NegativeCacheTest, testNoerrorNodata){
    // NODATA/NOERROR response for MX type query of example.com
    Message msg_nodata(Message::PARSE);
    messageFromFile(msg_nodata, "message_nodata_with_soa.wire");
    cache->update(msg_nodata);

    msg_nodata.makeResponse();

    Name example_dot_com("example.com.");
    EXPECT_TRUE(cache->lookup(example_dot_com, RRType::MX(), RRClass::IN(),
                msg_nodata));

    RRsetIterator iter = msg_nodata.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset_ptr = *iter;

    // The TTL should equal to the TTL of SOA record
    const RRTTL& nodata_ttl1 = rrset_ptr->getTTL();
    EXPECT_GE(nodata_ttl1.getValue(), 86399);
    EXPECT_LE(nodata_ttl1.getValue(), 86400);

    // Normal SOA response for example.com
    Message msg_example_com_soa(Message::PARSE);
    messageFromFile(msg_example_com_soa, "message_example_com_soa.wire");
    cache->update(msg_example_com_soa);

    msg_example_com_soa.makeResponse();
    Name soa_qname("example.com.");
    EXPECT_TRUE(cache->lookup(soa_qname, RRType::SOA(), RRClass::IN(),
                msg_example_com_soa));

    iter = msg_example_com_soa.beginSection(Message::SECTION_ANSWER);
    rrset_ptr = *iter;

    // The TTL should equal to the TTL of SOA record in answer section
    const RRTTL& soa_ttl = rrset_ptr->getTTL();
    EXPECT_GE(soa_ttl.getValue(), 172799);
    EXPECT_LE(soa_ttl.getValue(), 172800);

    // Query MX record of example.com again
    Message msg_nodata2(Message::PARSE);
    messageFromFile(msg_nodata2, "message_nodata_with_soa.wire");
    msg_nodata2.makeResponse();

    // Sleep for 2 seconds. 2 seconds to make sure the final range check
    // does not overlap with the original ones (in which case this test
    // would erroneously pass if the ttl value is not changed)
    sleep(2);

    EXPECT_TRUE(cache->lookup(example_dot_com, RRType::MX(), RRClass::IN(), msg_nodata2));

    // No answer
    EXPECT_EQ(msg_nodata2.getRRCount(Message::SECTION_ANSWER), 0);
    // One SOA record in authority section
    EXPECT_EQ(msg_nodata2.getRRCount(Message::SECTION_AUTHORITY), 1);

    iter = msg_nodata2.beginSection(Message::SECTION_AUTHORITY);
    rrset_ptr = *iter;

    // The TTL should equal to the TTL of negative response SOA record
    // and counted down
    const RRTTL& nodata_ttl2 = rrset_ptr->getTTL();
    EXPECT_GE(nodata_ttl2.getValue(), 86397);
    EXPECT_LE(nodata_ttl2.getValue(), 86398);
}

TEST_F(NegativeCacheTest, testReferralResponse){
    // CNAME exist, but it points to out of zone data, so the server give some reference data
    Message msg_cname_referral(Message::PARSE);
    messageFromFile(msg_cname_referral, "message_cname_referral.wire");
    cache->update(msg_cname_referral);

    msg_cname_referral.makeResponse();

    Name x_example_org("x.example.org.");
    EXPECT_TRUE(cache->lookup(x_example_org, RRType::A(), RRClass::IN(), msg_cname_referral));

    // The Rcode should be NOERROR
    EXPECT_EQ(msg_cname_referral.getRcode().getCode(), Rcode::NOERROR().getCode());

    // One CNAME record in Answer section
    EXPECT_EQ(msg_cname_referral.getRRCount(Message::SECTION_ANSWER), 1);
    RRsetIterator iter = msg_cname_referral.beginSection(Message::SECTION_ANSWER);
    EXPECT_EQ((*iter)->getType(), RRType::CNAME());

    // 13 NS records in Authority section
    EXPECT_EQ(msg_cname_referral.getRRCount(Message::SECTION_AUTHORITY), 13);
    iter = msg_cname_referral.beginSection(Message::SECTION_AUTHORITY);
    EXPECT_EQ((*iter)->getType(), RRType::NS());
}

}
