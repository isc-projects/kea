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

// $Id: rrtype_unittest.cc 476 2010-01-19 00:29:28Z jinmei $

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

#include "unittest_util.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class RRsetListTest : public ::testing::Test {
protected:
    RRsetListTest() {}
    void setupList(RRsetList& list);
    static const in::A rdata_in_a;
    static const in::AAAA rdata_in_aaaa;
    static const generic::NS rdata_ns;
    static const generic::SOA rdata_soa;
    static const generic::CNAME rdata_cname;
};

const in::A RRsetListTest::rdata_in_a("192.0.2.1");
const in::AAAA RRsetListTest::rdata_in_aaaa("2001:db8::1234");
const generic::NS RRsetListTest::rdata_ns("ns.example.com");
const generic::SOA RRsetListTest::rdata_soa(Name("ns.example.com"),
                                            Name("root.example.com"),
                                            2010012601, 3600, 300,
                                            3600000, 1200);
const generic::CNAME RRsetListTest::rdata_cname("target.example.com");

void
RRsetListTest::setupList(RRsetList& list) {
    RRsetPtr a(new RRset(Name("example.com"), RRClass::IN(),
                         RRType::A(), RRTTL(3600)));
    RRsetPtr aaaa(new RRset(Name("example.com"), RRClass::IN(),
                            RRType::AAAA(), RRTTL(3600)));
    RRsetPtr ns(new RRset(Name("example.com"), RRClass::IN(),
                          RRType::NS(), RRTTL(3600)));
    RRsetPtr soa(new RRset(Name("example.com"), RRClass::IN(),
                           RRType::SOA(), RRTTL(3600)));
    RRsetPtr cname(new RRset(Name("example.com"), RRClass::IN(),
                             RRType::CNAME(), RRTTL(3600)));

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

TEST_F(RRsetListTest, extraRRset) {
    RRsetList list;
    setupList(list);
    RRsetPtr cname(new RRset(Name("another.example.com"), RRClass::IN(),
                             RRType::CNAME(), RRTTL(3600)));
    EXPECT_THROW(list.addRRset(cname), DuplicateRRset);
}

TEST_F(RRsetListTest, randomAccess) {
    RRsetList list;
    setupList(list);

    RRsetPtr p;

    p = list[RRType::CNAME()];
    EXPECT_EQ(p->getType(), RRType::CNAME());

    p = list[RRType::AAAA()];
    EXPECT_EQ(p->getType(), RRType::AAAA());

    p = list[RRType::NS()];
    EXPECT_EQ(p->getType(), RRType::NS());

    p = list[RRType::A()];
    EXPECT_EQ(p->getType(), RRType::A());

    p = list[RRType::SOA()];
    EXPECT_EQ(p->getType(), RRType::SOA());
}

TEST_F(RRsetListTest, findRRset) {
    RRsetList list;
    setupList(list);
    EXPECT_EQ(list[RRType::A()], list.findRRset(RRType::A(), RRClass::IN()));
}

TEST_F(RRsetListTest, checkData) {
    RRsetList list;
    RRsetPtr a(new RRset(Name("example.com"), RRClass::IN(),
                         RRType::A(), RRTTL(3600)));
    a->addRdata(rdata_in_a);
    list.addRRset(a);

    RdataIteratorPtr it = list[RRType::A()]->getRdataIterator();
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

