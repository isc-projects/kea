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
#include <dns/tests/unittest_util.h>
#include <util/buffer.h>
#include "../message_cache.h"
#include "../rrset_cache.h"
#include "../resolver_cache.h"
#include "cache_test_messagefromfile.h"

using namespace isc::cache;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace std;

namespace {

/// \brief Derived from base class to make it easy to test
/// its internals.
class DerivedMessageCache: public MessageCache {
public:
    DerivedMessageCache(const RRsetCachePtr& rrset_cache,
                        uint32_t cache_size, uint16_t message_class,
                        const RRsetCachePtr& negative_soa_cache):
        MessageCache(rrset_cache, cache_size, message_class, negative_soa_cache)
    {}

    uint16_t messages_count() {
        return message_lru_.size();
    }
};

/// \brief Derived from base class to make it easy to test
/// its internals.
class DerivedRRsetCache: public RRsetCache {
public:
    DerivedRRsetCache(uint32_t cache_size, uint16_t rrset_class):
        RRsetCache(cache_size, rrset_class)
    {}

    /// \brief Remove one rrset entry from rrset cache.
    void removeRRsetEntry(Name& name, const RRType& type) {
        const string entry_name = genCacheEntryName(name, type);
        HashKey entry_key = HashKey(entry_name, RRClass(class_));
        RRsetEntryPtr rrset_entry = rrset_table_.get(entry_key);
        if (rrset_entry) {
            rrset_lru_.remove(rrset_entry);
            rrset_table_.remove(entry_key);
        }
    }
};

class MessageCacheTest: public testing::Test {
public:
    MessageCacheTest(): message_parse(Message::PARSE),
                        message_render(Message::RENDER)
    {
        uint16_t class_ = RRClass::IN().getCode();
        rrset_cache_.reset(new DerivedRRsetCache(RRSET_CACHE_DEFAULT_SIZE, class_));
        negative_soa_cache_.reset(new RRsetCache(NEGATIVE_RRSET_CACHE_DEFAULT_SIZE, class_));
        // Set the message cache size to 1, make it easy for unittest.
        message_cache_.reset(new DerivedMessageCache(rrset_cache_, 1, class_,
                                                     negative_soa_cache_));
    }

protected:
    boost::shared_ptr<DerivedMessageCache> message_cache_;
    boost::shared_ptr<DerivedRRsetCache> rrset_cache_;
    RRsetCachePtr negative_soa_cache_;
    Message message_parse;
    Message message_render;
};

void
updateMessageCache(const char* message_file,
                   boost::shared_ptr<DerivedMessageCache> cache)
{
    Message msg(Message::PARSE);
    messageFromFile(msg, message_file);
    cache->update(msg);
}

TEST_F(MessageCacheTest, testLookup) {
    messageFromFile(message_parse, "message_fromWire1");
    EXPECT_TRUE(message_cache_->update(message_parse));

    Name qname("test.example.com.");
    EXPECT_TRUE(message_cache_->lookup(qname, RRType::A(), message_render));
    EXPECT_EQ(message_cache_->messages_count(), 1);

    Message message_net(Message::PARSE);
    messageFromFile(message_net, "message_fromWire2");
    EXPECT_TRUE(message_cache_->update(message_net));
    EXPECT_EQ(message_cache_->messages_count(), 2);

    Name qname1("test.example.net.");
    EXPECT_TRUE(message_cache_->lookup(qname1, RRType::A(), message_render));

    // Test looking up message which has expired rrset or some rrset
    // has been removed from the rrset cache.
    rrset_cache_->removeRRsetEntry(qname1, RRType::A());
    EXPECT_FALSE(message_cache_->lookup(qname1, RRType::A(), message_render));

    // Update one message entry which has expired to message cache.
    updateMessageCache("message_fromWire9", message_cache_);
    EXPECT_EQ(message_cache_->messages_count(), 3);
    // The message entry has been added, but can't be looked up, since
    // it has expired and is removed automatically when being looked up.
    Name qname_org("test.example.org.");
    EXPECT_FALSE(message_cache_->lookup(qname_org, RRType::A(), message_render));
    EXPECT_EQ(message_cache_->messages_count(), 2);
}

TEST_F(MessageCacheTest, testUpdate) {
    messageFromFile(message_parse, "message_fromWire4");
    EXPECT_TRUE(message_cache_->update(message_parse));

    Name qname("example.com.");
    EXPECT_TRUE(message_cache_->lookup(qname, RRType::SOA(), message_render));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_AA));

    Message new_msg(Message::PARSE);
    messageFromFile(new_msg, "message_fromWire3");
    EXPECT_TRUE(message_cache_->update(new_msg));
    Message new_msg_render(Message::RENDER);
    EXPECT_TRUE(message_cache_->lookup(qname, RRType::SOA(), new_msg_render));
    EXPECT_FALSE(new_msg_render.getHeaderFlag(Message::HEADERFLAG_AA));
}

TEST_F(MessageCacheTest, testCacheLruBehavior) {
    // qname = "test.example.com.", qtype = A
    updateMessageCache("message_fromWire1", message_cache_);
    // qname = "test.example.net.", qtype = A
    updateMessageCache("message_fromWire2", message_cache_);
    // qname = "example.com.", qtype = SOA
    updateMessageCache("message_fromWire4", message_cache_);

    Name qname_net("test.example.net.");
    EXPECT_TRUE(message_cache_->lookup(qname_net, RRType::A(), message_render));

    // qname = "a.example.com.", qtype = A
    updateMessageCache("message_fromWire5", message_cache_);
    Name qname_com("test.example.com.");
    EXPECT_FALSE(message_cache_->lookup(qname_com, RRType::A(), message_render));
}

}   // namespace

