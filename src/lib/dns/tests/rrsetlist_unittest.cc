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

// $Id$

#include <vector>
#include <boost/foreach.hpp>

#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrsetlist.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class RRsetListTest : public ::testing::Test {
protected:
    RRsetListTest() : example_name(Name("example.com")),
                      example_ttl(RRTTL(3600))
    {}
    void setupList(RRsetList& list);
    Name example_name;
    RRTTL example_ttl;
};

const in::A rdata_in_a("192.0.2.1");
const in::AAAA rdata_in_aaaa("2001:db8::1234");
const generic::NS rdata_ns("ns.example.com");
const generic::SOA rdata_soa(Name("ns.example.com"), Name("root.example.com"),
                             2010012601, 3600, 300, 3600000, 1200);
const generic::CNAME rdata_cname("target.example.com");
const generic::DNAME rdata_dname("dtarget.example.com");

void
RRsetListTest::setupList(RRsetList& list) {
    RRsetPtr a(new RRset(Name("example.com"), RRClass::IN(),
                         RRType::A(), example_ttl));
    RRsetPtr aaaa(new RRset(Name("example.com"), RRClass::IN(),
                            RRType::AAAA(), example_ttl));
    RRsetPtr ns(new RRset(Name("example.com"), RRClass::IN(),
                          RRType::NS(), example_ttl));
    RRsetPtr soa(new RRset(Name("example.com"), RRClass::IN(),
                           RRType::SOA(), example_ttl));
    RRsetPtr cname(new RRset(Name("example.com"), RRClass::IN(),
                             RRType::CNAME(), example_ttl));

    a->addRdata(rdata_in_a);
    aaaa->addRdata(rdata_in_aaaa);
    ns->addRdata(rdata_ns);
    soa->addRdata(rdata_soa);
    cname->addRdata(rdata_cname);

    list.addRRset(a);
    list.addRRset(aaaa);
    list.addRRset(ns);
    list.addRRset(soa);
    list.addRRset(cname);
}

TEST_F(RRsetListTest, emptyOnInitialCreate) {
    RRsetList list;
    EXPECT_EQ(list.size(), 0);
}

TEST_F(RRsetListTest, addRRsets) {
    RRsetList list;
    setupList(list);
    EXPECT_EQ(list.size(), 5);
}

TEST_F(RRsetListTest, append) {
    RRsetList list1;
    setupList(list1);
    RRsetList list2;
    RRsetPtr dname(new RRset(Name("example.com"), RRClass::IN(),
                             RRType::DNAME(), example_ttl));
    dname->addRdata(rdata_dname);
    list2.addRRset(dname);
    list1.append(list2);
    EXPECT_EQ(list2.size(), 1);
    EXPECT_EQ(list1.size(), 6);

    RRsetPtr rrset = list1.findRRset(RRType::DNAME(), RRClass::IN());
    EXPECT_EQ(RRType::DNAME(), rrset->getType());

    EXPECT_THROW(list1.append(list2), DuplicateRRset);
}

TEST_F(RRsetListTest, extraRRset) {
    RRsetList list;
    setupList(list);
    RRsetPtr cname(new RRset(Name("another.example.com"), RRClass::IN(),
                             RRType::CNAME(), example_ttl));
    EXPECT_THROW(list.addRRset(cname), DuplicateRRset);
}

void
checkFindResult(RRsetList& list, const Name& name,
                const RRType& rrtype, const RRClass& rrclass,
                const RRTTL& rrttl)
{
    RRsetPtr rrset = list.findRRset(rrtype, rrclass);;
    EXPECT_EQ(name, rrset->getName());
    EXPECT_EQ(rrtype, rrset->getType());
    EXPECT_EQ(rrclass, rrset->getClass());
    EXPECT_EQ(rrttl, rrset->getTTL());
}

TEST_F(RRsetListTest, findRRset) {
    RRsetList list;
    setupList(list);
 
    checkFindResult(list, example_name, RRType::A(), RRClass::IN(),
                    example_ttl);
    checkFindResult(list, example_name, RRType::CNAME(), RRClass::IN(),
                    example_ttl);
    checkFindResult(list, example_name, RRType::AAAA(), RRClass::IN(),
                    example_ttl);
    checkFindResult(list, example_name, RRType::NS(), RRClass::IN(),
                    example_ttl);
    checkFindResult(list, example_name, RRType::SOA(), RRClass::IN(),
                    example_ttl);
}

TEST_F(RRsetListTest, checkData) {
    RRsetList list;
    RRsetPtr a(new RRset(Name("example.com"), RRClass::IN(),
                         RRType::A(), example_ttl));
    a->addRdata(rdata_in_a);
    list.addRRset(a);

    RdataIteratorPtr it =
        list.findRRset(RRType::A(), RRClass::IN())->getRdataIterator();
    it->first();
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
}

TEST_F(RRsetListTest, iterate) {
    RRsetList list;
    setupList(list);

    bool has_a = false, has_aaaa = false, has_ns = false, has_soa = false,
        has_cname = false;
    int i = 0;
    BOOST_FOREACH(RRsetPtr rrset, list) {
        if (rrset->getType() == RRType::A()) {
            has_a = true;
        }
        if (rrset->getType() == RRType::AAAA()) {
            has_aaaa = true;
        }
        if (rrset->getType() == RRType::NS()) {
            has_ns = true;
        }
        if (rrset->getType() == RRType::SOA()) {
            has_soa = true;
        }
        if (rrset->getType() == RRType::CNAME()) {
            has_cname = true;
        }
        ++i;
    }
    EXPECT_TRUE(has_a);
    EXPECT_TRUE(has_aaaa);
    EXPECT_TRUE(has_ns);
    EXPECT_TRUE(has_soa);
    EXPECT_TRUE(has_cname);
    EXPECT_TRUE(i == 5);
}

}
