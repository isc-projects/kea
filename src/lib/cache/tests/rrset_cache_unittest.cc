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

#include <config.h>
#include <string>
#include <gtest/gtest.h>
#include <cache/resolver_cache.h>
#include <cache/cache_entry_key.h>
#include <cache/rrset_entry.h>
#include <cache/rrset_cache.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>

using namespace isc::cache;
using namespace isc::dns;
using namespace std;

namespace {

class RRsetCacheTest : public testing::Test {
protected:
    RRsetCacheTest():
        cache_(1, RRClass::IN().getCode()),
        name_("example.com"),
        rrset1_(name_, RRClass::IN(), RRType::A(), RRTTL(20)),
        rrset2_(name_, RRClass::IN(), RRType::A(), RRTTL(10)),
        rrset_entry1_(rrset1_, RRSET_TRUST_ADDITIONAL_AA),
        rrset_entry2_(rrset2_, RRSET_TRUST_PRIM_ZONE_NONGLUE)
    {
    }

    RRsetCache cache_;
    Name name_;
    RRset rrset1_;
    RRset rrset2_;
    RRsetEntry rrset_entry1_;
    RRsetEntry rrset_entry2_;
};

void
updateRRsetCache(RRsetCache& cache, Name& rrset_name,
                 uint32_t ttl = 20,
                 RRsetTrustLevel level = RRSET_TRUST_ADDITIONAL_AA)
{
    RRset rrset(rrset_name, RRClass::IN(), RRType::A(), RRTTL(ttl));
    cache.update(rrset, level);
}

TEST_F(RRsetCacheTest, lookup) {
    const RRType& type = RRType::A();
    EXPECT_TRUE(cache_.lookup(name_, type) == NULL);

    cache_.update(rrset1_, rrset_entry1_.getTrustLevel());
    RRsetEntryPtr rrset_entry_ptr = cache_.lookup(name_, type);
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry1_.getTrustLevel());
    EXPECT_EQ(rrset_entry_ptr->getRRset()->getName(), rrset_entry1_.getRRset()->getName());
    EXPECT_EQ(rrset_entry_ptr->getRRset()->getType(), rrset_entry1_.getRRset()->getType());
    EXPECT_EQ(rrset_entry_ptr->getRRset()->getClass(), rrset_entry1_.getRRset()->getClass());

    // Check whether the expired rrset entry will be removed automatically
    // when looking up.
    Name name_test("test.example.com.");
    updateRRsetCache(cache_, name_test, 0); // Add a rrset with TTL 0 to cache.
    EXPECT_FALSE(cache_.lookup(name_test, RRType::A()));
}

TEST_F(RRsetCacheTest, update) {
    const RRType& type = RRType::A();

    cache_.update(rrset1_, rrset_entry1_.getTrustLevel());
    RRsetEntryPtr rrset_entry_ptr = cache_.lookup(name_, type);
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry1_.getTrustLevel());

    cache_.update(rrset2_, rrset_entry2_.getTrustLevel());
    rrset_entry_ptr = cache_.lookup(name_, type);
    // The trust level should be updated
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry2_.getTrustLevel());

    cache_.update(rrset1_, rrset_entry1_.getTrustLevel());
    // The trust level should not be updated
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry2_.getTrustLevel());
}

// Test whether the lru list in rrset cache works as expected.
TEST_F(RRsetCacheTest, cacheLruBehavior) {
    Name name1("1.example.com.");
    Name name2("2.example.com.");
    Name name3("3.example.com.");
    Name name4("4.example.com.");

    updateRRsetCache(cache_, name1);
    updateRRsetCache(cache_, name2);
    updateRRsetCache(cache_, name3);

    EXPECT_TRUE(cache_.lookup(name1, RRType::A()));

    // Now update the fourth rrset, rrset with name "2.example.com."
    // should has been removed from cache.
    updateRRsetCache(cache_, name4);
    EXPECT_FALSE(cache_.lookup(name2, RRType::A()));

    // Test Update rrset with higher trust level
    updateRRsetCache(cache_, name1, RRSET_TRUST_PRIM_GLUE);
    // Test update rrset with lower trust level.
    updateRRsetCache(cache_, name3, RRSET_TRUST_ADDITIONAL_NONAA);

    // When add rrset with name2, rrset with name4
    // has been removed from the cache.
    updateRRsetCache(cache_, name2);
    EXPECT_FALSE(cache_.lookup(name4, RRType::A()));
}

}
