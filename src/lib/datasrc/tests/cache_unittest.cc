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

#include <stdexcept>

#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>

#include <datasrc/cache.h>
#include <datasrc/data_source.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;

namespace {
class CacheTest : public ::testing::Test {
protected:
    CacheTest() : test_name("test.example.com"),
                  test_nsname("ns.example.com"),
                  test_ch("example.com")
    {
        RRsetPtr a(new RRset(test_name, RRClass::IN(), RRType::A(),
                             RRTTL(3600)));
        a->addRdata(in::A("192.0.2.1"));
        a->addRdata(in::A("192.0.2.2"));

        RRsetPtr b(new RRset(test_nsname, RRClass::IN(), RRType::NS(),
                             RRTTL(86400)));
        RRsetPtr c(new RRset(test_ch, RRClass::CH(), RRType::TXT(),
                             RRTTL(0)));
        c->addRdata(generic::TXT("Text record"));

        cache.setSlots(5);

        cache.addPositive(a, 1, 30);
        cache.addPositive(b, 2, 30);
        cache.addPositive(c, 4, 30);
    }

    Name test_name;
    Name test_nsname;
    Name test_ch;

    HotCache cache;
};

class TestRRset : public RRset {
public:
    TestRRset(const Name& name, int& counter) :
        RRset(name, RRClass::IN(), RRType::A(), RRTTL(3600)),
        counter_(counter)
    {
        ++counter_;
    }
    ~TestRRset() {
        --counter_;
    }
    int& counter_;
};

// make sure any remaining cache entries are purged on destruction of the
// cache.
TEST_F(CacheTest, cleanup) {
    HotCache* local_cache(new HotCache);
    int num_rrsets = 0;

    local_cache->addPositive(RRsetPtr(new TestRRset(Name("example.com"),
                                                    num_rrsets)), 0, 10);
    local_cache->addPositive(RRsetPtr(new TestRRset(Name("example.org"),
                                                    num_rrsets)), 0, 10);

    EXPECT_EQ(2, num_rrsets);
    delete local_cache;
    EXPECT_EQ(0, num_rrsets);
}

TEST_F(CacheTest, slots) {
    EXPECT_EQ(5, cache.getSlots());
    EXPECT_EQ(3, cache.getCount());
}

TEST_F(CacheTest, insert) {
    RRsetPtr aaaa(new RRset(Name("foo"), RRClass::IN(), RRType::AAAA(),
                            RRTTL(0)));
    aaaa->addRdata(in::AAAA("2001:db8:3:bb::5"));
    cache.addPositive(aaaa, 0, 4);

    EXPECT_EQ(4, cache.getCount());

    RRsetPtr r;
    uint32_t f;
    bool hit = cache.retrieve(Name("foo"), RRClass::IN(),
                                RRType::AAAA(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(aaaa, r);
}

TEST_F(CacheTest, retrieveOK) {
    bool hit;
    RRsetPtr r;
    uint32_t f;

    // Test repeatedly to ensure that all records remain accessible
    // even after being promoted to the top of the cache
    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(test_name, r->getName());
    EXPECT_EQ(RRClass::IN(), r->getClass());
    EXPECT_EQ(RRType::A(), r->getType());

    hit = cache.retrieve(test_nsname, RRClass::IN(), RRType::NS(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(test_nsname, r->getName());
    EXPECT_EQ(RRClass::IN(), r->getClass());
    EXPECT_EQ(RRType::NS(), r->getType());

    hit = cache.retrieve(test_ch, RRClass::CH(), RRType::TXT(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(test_ch, r->getName());
    EXPECT_EQ(RRClass::CH(), r->getClass());
    EXPECT_EQ(RRType::TXT(), r->getType());
    
    hit = cache.retrieve(test_nsname, RRClass::IN(), RRType::NS(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(test_nsname, r->getName());
    EXPECT_EQ(RRClass::IN(), r->getClass());
    EXPECT_EQ(RRType::NS(), r->getType());

    hit = cache.retrieve(test_ch, RRClass::CH(), RRType::TXT(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(test_ch, r->getName());
    EXPECT_EQ(RRClass::CH(), r->getClass());
    EXPECT_EQ(RRType::TXT(), r->getType());

    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(test_name, r->getName());
    EXPECT_EQ(RRClass::IN(), r->getClass());
    EXPECT_EQ(RRType::A(), r->getType());

    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(test_name, r->getName());
    EXPECT_EQ(RRClass::IN(), r->getClass());
    EXPECT_EQ(RRType::A(), r->getType());
};

TEST_F(CacheTest, flags) {
    bool hit;
    RRsetPtr r;
    uint32_t f;

    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_TRUE(r);
    EXPECT_EQ(DataSrc::REFERRAL, f);

    hit = cache.retrieve(test_nsname, RRClass::IN(), RRType::NS(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_TRUE(r);
    EXPECT_EQ(DataSrc::CNAME_FOUND, f);

    hit = cache.retrieve(test_ch, RRClass::CH(), RRType::TXT(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_TRUE(r);
    EXPECT_EQ(DataSrc::NAME_NOT_FOUND, f);
}

TEST_F(CacheTest, retrieveFail) {
    bool hit;
    RRsetPtr r;
    uint32_t f;

    hit = cache.retrieve(Name("fake"), RRClass::IN(), RRType::A(), r, f);
    EXPECT_FALSE(hit);

    hit = cache.retrieve(test_name, RRClass::CH(), RRType::A(), r, f);
    EXPECT_FALSE(hit);

    hit = cache.retrieve(test_name, RRClass::IN(), RRType::DNSKEY(), r, f);
    EXPECT_FALSE(hit);
}

TEST_F(CacheTest, expire) {
    // Insert "foo" with a duration of 2 seconds; sleep 3.  The
    // record should not be returned from the cache even though it's
    // at the top of the cache.
    RRsetPtr aaaa(new RRset(Name("foo"), RRClass::IN(), RRType::AAAA(),
                            RRTTL(0)));
    aaaa->addRdata(in::AAAA("2001:db8:3:bb::5"));
    cache.addPositive(aaaa, 0, 2);

    sleep(3);

    RRsetPtr r;
    uint32_t f;
    bool hit = cache.retrieve(Name("foo"), RRClass::IN(), RRType::AAAA(), r, f);
    EXPECT_FALSE(hit);
};

TEST_F(CacheTest, LRU) {
    // Retrieve a record, cache four new records; with five slots
    // in the LRU queue this should remove all the previous records
    // except the last one retreived.
    bool hit;
    RRsetPtr r;
    uint32_t f;

    hit = cache.retrieve(test_nsname, RRClass::IN(), RRType::NS(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_EQ(3, cache.getCount());

    RRsetPtr one(new RRset(Name("one"), RRClass::IN(), RRType::TXT(),
                           RRTTL(0)));
    one->addRdata(generic::TXT("one"));
    cache.addPositive(one, 0, 30);
    EXPECT_EQ(4, cache.getCount());

    RRsetPtr two(new RRset(Name("two"), RRClass::IN(), RRType::TXT(),
                           RRTTL(0)));
    two->addRdata(generic::TXT("two"));
    cache.addPositive(two, 0, 30);
    EXPECT_EQ(5, cache.getCount());

    RRsetPtr three(new RRset(Name("three"), RRClass::IN(), RRType::TXT(),
                             RRTTL(0)));
    three->addRdata(generic::TXT("three"));
    cache.addPositive(three, 0, 30);
    EXPECT_EQ(5, cache.getCount());

    RRsetPtr four(new RRset(Name("four"), RRClass::IN(), RRType::TXT(),
                            RRTTL(0)));
    four->addRdata(generic::TXT("four"));
    cache.addPositive(four, 0, 30);
    EXPECT_EQ(5, cache.getCount());

    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_FALSE(hit);

    hit = cache.retrieve(test_nsname, RRClass::IN(), RRType::NS(), r, f);
    EXPECT_TRUE(hit);

    hit = cache.retrieve(test_ch, RRClass::CH(), RRType::TXT(), r, f);
    EXPECT_FALSE(hit);
}

TEST_F(CacheTest, ncache) {
    Name missing("missing.example.com");
    cache.addNegative(missing, RRClass::IN(), RRType::DNSKEY(), 8, 30);

    RRsetPtr r;
    uint32_t f;
    bool hit = cache.retrieve(missing, RRClass::IN(), RRType::DNSKEY(), r, f);

    EXPECT_TRUE(hit);
    EXPECT_FALSE(r);
    EXPECT_EQ(DataSrc::TYPE_NOT_FOUND, f);
}

TEST_F(CacheTest, overwrite) {
    EXPECT_EQ(3, cache.getCount());

    RRsetPtr a(new RRset(test_name, RRClass::IN(), RRType::A(), RRTTL(300)));
    a->addRdata(in::A("192.0.2.100"));

    EXPECT_NO_THROW(cache.addPositive(a, 16, 30));
    EXPECT_EQ(3, cache.getCount());

    RRsetPtr r;
    uint32_t f;
    bool hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_TRUE(r);
    EXPECT_EQ(16, f);

    EXPECT_NO_THROW(cache.addNegative(test_name, RRClass::IN(), RRType::A(), 1, 30));
    EXPECT_EQ(3, cache.getCount());

    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_TRUE(hit);
    EXPECT_FALSE(r);
    EXPECT_EQ(DataSrc::REFERRAL, f);
}

TEST_F(CacheTest, reduceSlots) {
    EXPECT_EQ(3, cache.getCount());
    cache.setSlots(2);
    EXPECT_EQ(2, cache.getCount());
    cache.setSlots(1);
    EXPECT_EQ(1, cache.getCount());
    cache.setSlots(0);
    EXPECT_EQ(1, cache.getCount());
}

TEST_F(CacheTest, setEnabled) {
    cache.setEnabled(false);
    EXPECT_FALSE(cache.getEnabled());
    cache.setEnabled(true);
    EXPECT_TRUE(cache.getEnabled());
}

TEST_F(CacheTest, disabled) {
    bool hit;
    RRsetPtr r;
    uint32_t f;

    cache.setEnabled(false);
    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_FALSE(hit);

    cache.setEnabled(true);
    hit = cache.retrieve(test_name, RRClass::IN(), RRType::A(), r, f);
    EXPECT_TRUE(hit);

    EXPECT_EQ(test_name, r->getName());
    EXPECT_EQ(RRClass::IN(), r->getClass());
    EXPECT_EQ(RRType::A(), r->getType());
}

}
