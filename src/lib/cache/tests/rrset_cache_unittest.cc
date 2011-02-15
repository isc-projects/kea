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
        cache(RRSET_CACHE_DEFAULT_SIZE, RRClass::IN().getCode()),
        name("example.com"),
        rrset1(name, RRClass::IN(), RRType::A(), RRTTL(20)),
        rrset2(name, RRClass::IN(), RRType::A(), RRTTL(10)),
        rrset_entry1(rrset1, RRSET_TRUST_ADDITIONAL_AA),
        rrset_entry2(rrset2, RRSET_TRUST_PRIM_ZONE_NONGLUE)
    {
    }

    RRsetCache cache;
    Name name;
    RRset rrset1;
    RRset rrset2;
    RRsetEntry rrset_entry1;
    RRsetEntry rrset_entry2;
};

TEST_F(RRsetCacheTest, lookup) {
    const RRType& type = RRType::A();
    EXPECT_TRUE(cache.lookup(name, type) == NULL);

    cache.update(rrset1, rrset_entry1.getTrustLevel());
    RRsetEntryPtr rrset_entry_ptr = cache.lookup(name, type);
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry1.getTrustLevel());
    EXPECT_EQ(rrset_entry_ptr->getRRset()->getName(), rrset_entry1.getRRset()->getName());
    EXPECT_EQ(rrset_entry_ptr->getRRset()->getType(), rrset_entry1.getRRset()->getType());
    EXPECT_EQ(rrset_entry_ptr->getRRset()->getClass(), rrset_entry1.getRRset()->getClass());
}

TEST_F(RRsetCacheTest, update) {
    const RRType& type = RRType::A();

    cache.update(rrset1, rrset_entry1.getTrustLevel());
    RRsetEntryPtr rrset_entry_ptr = cache.lookup(name, type);
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry1.getTrustLevel());

    cache.update(rrset2, rrset_entry2.getTrustLevel());
    rrset_entry_ptr = cache.lookup(name, type);
    // The trust level should be updated
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry2.getTrustLevel());

    cache.update(rrset1, rrset_entry1.getTrustLevel());
    // The trust level should not be updated
    EXPECT_EQ(rrset_entry_ptr->getTrustLevel(), rrset_entry2.getTrustLevel());
}

}
