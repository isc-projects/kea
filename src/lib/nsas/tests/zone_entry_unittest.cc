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

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

#include <dns/rrclass.h>

#include "../asiolink.h"
#include "../zone_entry.h"
#include "../nameserver_entry.h"
#include "../address_request_callback.h"
#include "../nsas_entry_compare.h"
#include "../hash_deleter.h"

#include "nsas_test.h"

using namespace isc::nsas;
using namespace asiolink;
using namespace std;
using namespace boost;
using namespace isc::dns;

namespace {

/// \brief Test Fixture Class
class ZoneEntryTest : public TestWithRdata {
protected:
    /// \brief Constructor
    ZoneEntryTest() :
        nameservers_hash_(new NsasEntryCompare<NameserverEntry>),
        nameservers_lru_((3 * nameservers_hash_.tableSize()),
            new HashDeleter<NameserverEntry>(nameservers_hash_)),
        resolver_(new TestResolver),
        callback_(new Callback)
    { }
    /// \brief Tables of nameservers to pass into zone entry constructor
    HashTable<NameserverEntry> nameservers_hash_;
    LruList<NameserverEntry> nameservers_lru_;
    shared_ptr<TestResolver> resolver_;

    struct Callback : public AddressRequestCallback {
        Callback() : unreachable_count_(0) {}
        size_t unreachable_count_;
        vector<IOAddress> successes_;
        virtual void unreachable() { unreachable_count_ ++; }
        virtual void success(const IOAddress& address) {
            successes_.push_back(address);
        }
    };
    shared_ptr<Callback> callback_;
};

/// \brief Inherited version with access into its internals for tests
class InheritedZoneEntry : public ZoneEntry {
    public:
        InheritedZoneEntry(shared_ptr<ResolverInterface> resolver,
            const isc::dns::AbstractRRset& authority,
            const std::vector<const isc::dns::AbstractRRset*>& additional,
            HashTable<NameserverEntry>& nameservers,
            LruList<NameserverEntry>& nameserver_lru) :
            ZoneEntry(resolver, authority, additional, nameservers,
                nameserver_lru)
        { }
        InheritedZoneEntry(shared_ptr<ResolverInterface> resolver,
            const std::string& name, uint16_t class_code) :
            ZoneEntry(resolver, name, class_code)
        { }
        NameserverVector& nameservers() { return nameservers_; }
};

/// Tests of the default constructor
TEST_F(ZoneEntryTest, DefaultConstructor) {

    // Default constructor should not create any RRsets
    InheritedZoneEntry alpha(resolver_, EXAMPLE_CO_UK,
        RRClass::IN().getCode());
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
    EXPECT_EQ(RRClass::IN().getCode(), alpha.getClass());
    EXPECT_TRUE(alpha.nameservers().empty());
}

/// Tests of constructor from referral data
TEST_F(ZoneEntryTest, ReferralConstructor) {
    InheritedZoneEntry alpha(resolver_, rr_single_,
        vector<const AbstractRRset*>(), nameservers_hash_, nameservers_lru_);
    // It should load the name and class from the referral info
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
    EXPECT_EQ(RRClass::IN().getCode(), alpha.getClass());
    EXPECT_EQ(1, alpha.nameservers().size());
    EXPECT_EQ("ns.example.net.", alpha.nameservers()[0]->getName());
    // TODO Test with some additional data once NameserverEntry supports them?
}

TEST_F(ZoneEntryTest, CallbackNoNS) {
    shared_ptr<InheritedZoneEntry> zone(new InheritedZoneEntry(resolver_,
        rr_empty_, vector<const AbstractRRset*>(), nameservers_hash_,
        nameservers_lru_));
    // It should accept the callback
    EXPECT_TRUE(zone->addCallback(callback_, ANY_OK, zone));
    // And tell imediatelly that it is unreachable (when it has no nameservers)
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(1, callback_->unreachable_count_);
}

TEST_F(ZoneEntryTest, CallbackZeroTTL) {
    shared_ptr<InheritedZoneEntry> zone(new InheritedZoneEntry(resolver_,
        rr_single_, vector<const AbstractRRset*>(), nameservers_hash_,
        nameservers_lru_));
    // It should accept the callback
    EXPECT_TRUE(zone->addCallback(callback_, ANY_OK, zone));
    // It should not be answered yet, it should ask for the IP addresses
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    resolver_->asksIPs(Name("ns.example.net."), 0, 1);
    // It should reject another one, as it has zero TTL
    EXPECT_FALSE(zone->addCallback(callback_, ANY_OK, zone));
}

}   // namespace
