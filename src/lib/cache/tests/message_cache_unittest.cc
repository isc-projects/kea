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
#include <dns/tests/unittest_util.h>
#include <dns/buffer.h>
#include "../message_cache.h"
#include "../rrset_cache.h"
#include "../resolver_cache.h"
#include "cache_test_messagefromfile.h"

using namespace isc::cache;
using namespace isc;
using namespace isc::dns;
using namespace std;

namespace {

/// \brief Derived from base class to make it easy to test
/// its internals.
class DerivedMessageCache: public MessageCache {
public:
    DerivedMessageCache(boost::shared_ptr<RRsetCache> rrset_cache_,
                        uint32_t cache_size, uint16_t message_class):
        MessageCache(rrset_cache_, cache_size, message_class)
    {}

    uint16_t messages_count() {
        return message_lru_.size();
    }
};

class MessageCacheTest: public testing::Test {
public:
    MessageCacheTest(): message_parse(Message::PARSE),
                        message_render(Message::RENDER)
    {
        uint16_t class_ = RRClass::IN().getCode();
        rrset_cache_.reset(new RRsetCache(RRSET_CACHE_DEFAULT_SIZE, class_));
        message_cache_.reset(new DerivedMessageCache(rrset_cache_, 
                                          MESSAGE_CACHE_DEFAULT_SIZE, class_ ));
    }

protected:
    boost::shared_ptr<DerivedMessageCache> message_cache_;
    RRsetCachePtr rrset_cache_;
    Message message_parse;
    Message message_render;
};

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
    EXPECT_TRUE(new_msg_render.getHeaderFlag(Message::HEADERFLAG_AA));
}

}   // namespace

