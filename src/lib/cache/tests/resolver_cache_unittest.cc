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
#include <dns/rrset.h>
#include "resolver_cache.h"
#include "cache_test_messagefromfile.h"
#include "cache_test_sectioncount.h"

using namespace isc::cache;
using namespace isc::dns;
using namespace std;

namespace {

class ResolverCacheTest: public testing::Test {
public:
    ResolverCacheTest() {
        vector<CacheSizeInfo> vec;
        CacheSizeInfo class_in(RRClass::IN(), 100, 200);
        CacheSizeInfo class_ch(RRClass::CH(), 100, 200);
        vec.push_back(class_in);
        vec.push_back(class_ch);
        cache = new ResolverCache(vec);
    }

    ~ResolverCacheTest() {
        delete cache;
    }

    ResolverCache* cache;
};

TEST_F(ResolverCacheTest, testUpdateMessage) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache->update(msg);

    Name qname("example.com.");

    msg.makeResponse();
    EXPECT_TRUE(cache->lookup(qname, RRType::SOA(), RRClass::IN(), msg));
    EXPECT_FALSE(msg.getHeaderFlag(Message::HEADERFLAG_AA));

    // Test whether the old message can be updated
    Message new_msg(Message::PARSE);
    messageFromFile(new_msg, "message_fromWire4");
    cache->update(new_msg);

    new_msg.makeResponse();
    EXPECT_TRUE(cache->lookup(qname, RRType::SOA(), RRClass::IN(), new_msg));
    EXPECT_FALSE(new_msg.getHeaderFlag(Message::HEADERFLAG_AA));
}

TEST_F(ResolverCacheTest, testUpdateRRset) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache->update(msg);

    Name qname("example.com.");

    msg.makeResponse();
    EXPECT_TRUE(cache->lookup(qname, RRType::SOA(), RRClass::IN(), msg));

    Message except_msg(Message::RENDER);
    EXPECT_THROW(cache->lookup(qname, RRType::SOA(), RRClass::IN(), except_msg), 
                 MessageNoQuestionSection);

    // Get one rrset in the message, then use it to 
    // update rrset cache-> Test whether the local zone
    // data is updated.
    RRsetIterator iter = msg.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset_ptr = *iter;
    cache->update(rrset_ptr);

    Message new_msg(Message::RENDER);
    Question question(qname, RRClass::IN(), RRType::NS());
    new_msg.addQuestion(question);
    EXPECT_TRUE(cache->lookup(qname, RRType::NS(), RRClass::IN(), new_msg));
    EXPECT_EQ(0, sectionRRsetCount(new_msg, Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, sectionRRsetCount(new_msg, Message::SECTION_ADDITIONAL));
}

TEST_F(ResolverCacheTest, testLookupUnsupportedClass) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache->update(msg);

    Name qname("example.com.");

    msg.makeResponse();
    EXPECT_FALSE(cache->lookup(qname, RRType::SOA(), RRClass::CH(), msg));
    EXPECT_FALSE(cache->lookup(qname, RRType::SOA(), RRClass::CH()));
}

TEST_F(ResolverCacheTest, testLookupClosestRRset) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache->update(msg);

    Name qname("www.test.example.com.");

    RRsetPtr rrset_ptr = cache->lookupDeepestNS(qname, RRClass::IN());
    EXPECT_TRUE(rrset_ptr);
    EXPECT_EQ(rrset_ptr->getName(), Name("example.com."));

    rrset_ptr = cache->lookupDeepestNS(Name("example.com."), RRClass::IN());
    EXPECT_TRUE(rrset_ptr);
    EXPECT_EQ(rrset_ptr->getName(), Name("example.com."));

    rrset_ptr = cache->lookupDeepestNS(Name("com."), RRClass::IN());
    EXPECT_FALSE(rrset_ptr);
}

}
