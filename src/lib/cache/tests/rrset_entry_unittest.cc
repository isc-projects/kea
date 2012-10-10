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
#include <cache/cache_entry_key.h>
#include <cache/rrset_entry.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>

using namespace isc::cache;
using namespace isc::dns;
using namespace std;

namespace {
class GenCacheKeyTest: public testing::Test {
};

TEST_F(GenCacheKeyTest, genCacheEntryKey1) {
    string name = "example.com.";
    uint16_t type = 12;
    string name_type = "example.com.12";

    EXPECT_EQ(name_type, genCacheEntryName(name, type));
}

TEST_F(GenCacheKeyTest, genCacheEntryKey2) {
    Name name("example.com");
    RRType type(1234);
    string keystr = "example.com.1234";
    EXPECT_EQ(keystr, genCacheEntryName(name, type));
}

class DerivedRRsetEntry: public RRsetEntry {
public:
    DerivedRRsetEntry(const isc::dns::RRset& rrset, const RRsetTrustLevel& level) : RRsetEntry(rrset, level) {};

};

#define TEST_TTL 100
class RRsetEntryTest : public ::testing::Test {
protected:
    RRsetEntryTest():
        name("test.example.com"),
        rrset(name, RRClass::IN(), RRType::A(), RRTTL(TEST_TTL)),
        trust_level(RRSET_TRUST_ADDITIONAL_AA),
        rrset_entry(rrset, trust_level)
    {
    }
    Name name;
    RRset rrset;
    RRsetTrustLevel trust_level;
    RRsetEntry rrset_entry;
};

TEST_F(RRsetEntryTest, constructor) {
    EXPECT_EQ(trust_level, rrset_entry.getTrustLevel());
    EXPECT_EQ(rrset.getName(), rrset_entry.getRRset()->getName());
    EXPECT_EQ(rrset.getClass(), rrset_entry.getRRset()->getClass());
    EXPECT_EQ(rrset.getType(), rrset_entry.getRRset()->getType());
    EXPECT_EQ(rrset.getRdataCount(), rrset_entry.getRRset()->getRdataCount());
}

TEST_F(RRsetEntryTest, updateTTL) {
    uint32_t ttl = rrset_entry.getTTL();
    sleep(1);
    // The TTL should be decreased
    EXPECT_TRUE(rrset_entry.getTTL() < ttl);
}

TEST_F(RRsetEntryTest, TTLExpire) {
    RRset exp_rrset(name, RRClass::IN(), RRType::A(), RRTTL(1));
    RRsetEntry rrset_entry(exp_rrset, RRSET_TRUST_ANSWER_AA);
    sleep(1);
    uint32_t ttl = rrset_entry.getTTL();
    EXPECT_LT(ttl, 1);
    sleep(1);
    ttl = rrset_entry.getTTL();
    EXPECT_LT(ttl, 1);
}

TEST_F(RRsetEntryTest, getExpireTime){
    uint32_t exp_time = time(NULL) + TEST_TTL;
    EXPECT_EQ(exp_time, rrset_entry.getExpireTime());
}

}   // namespace

