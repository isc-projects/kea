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
#include <dns/rrset.h>
#include "recursor_cache.h"
#include "cache_test_util.h"

using namespace isc::cache;
using namespace isc::dns;
using namespace std;

namespace {

class RecursorCacheTest: public testing::Test {
public:
    RecursorCacheTest() {
        vector<CacheSizeInfo> vec;
        CacheSizeInfo class_in(1, 100, 200);
        CacheSizeInfo class_ch(3, 100, 200);
        vec.push_back(class_in);
        vec.push_back(class_ch);
        cache = RecursorCache(vec);
    }

    RecursorCache cache;
};

TEST_F(RecursorCacheTest, testUpdateMessage) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache.update(msg);

    Name qname("example.com.");
    RRType qtype(6);
    RRClass klass(1);

    msg.makeResponse();
    EXPECT_TRUE(cache.lookup(qname, qtype, klass, msg));
    EXPECT_TRUE(msg.getHeaderFlag(Message::HEADERFLAG_AA));

    // Test whether the old message can be updated
    Message new_msg(Message::PARSE);
    messageFromFile(new_msg, "message_fromWire4");
    cache.update(new_msg);

    new_msg.makeResponse();
    EXPECT_TRUE(cache.lookup(qname, qtype, klass, new_msg));
    EXPECT_FALSE(new_msg.getHeaderFlag(Message::HEADERFLAG_AA));
}

TEST_F(RecursorCacheTest, testUpdateRRset) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache.update(msg);

    Name qname("example.com.");
    RRType qtype(6);
    RRClass klass(1);

    msg.makeResponse();
    EXPECT_TRUE(cache.lookup(qname, qtype, klass, msg));

    Message except_msg(Message::RENDER);
    EXPECT_THROW(cache.lookup(qname, qtype, klass, except_msg), 
                 MessageNoQuestionSection);

    // Get one rrset in the message, then use it to 
    // update rrset cache. Test whether the local zone
    // data is updated.
    RRsetIterator iter = msg.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset_ptr = *iter;
    cache.update(rrset_ptr);

    Message new_msg(Message::RENDER);
    Question question(qname, klass, RRType(2));
    new_msg.addQuestion(question);
    EXPECT_TRUE(cache.lookup(qname, RRType(2), klass, new_msg));
    EXPECT_EQ(0, section_rrset_count(new_msg, Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, section_rrset_count(new_msg, Message::SECTION_ADDITIONAL));
}

TEST_F(RecursorCacheTest, testLookupUnsupportedClass) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache.update(msg);

    Name qname("example.com.");
    RRType qtype(6);

    msg.makeResponse();
    EXPECT_FALSE(cache.lookup(qname, qtype, RRClass(2), msg));
    EXPECT_FALSE(cache.lookup(qname, qtype, RRClass(2)));
}

TEST_F(RecursorCacheTest, testLookupClosestRRset) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    cache.update(msg);

    Name qname("www.test.example.com.");
    RRType qtype(6);
    RRClass klass(1);

    RRsetPtr rrset_ptr = cache.lookupClosestRRset(qname, qtype, klass);
    EXPECT_TRUE(rrset_ptr);
    EXPECT_EQ(rrset_ptr->getName(), Name("example.com."));

    rrset_ptr = cache.lookupClosestRRset(Name("example.com."), RRType(2), klass);
    EXPECT_TRUE(rrset_ptr);
    EXPECT_EQ(rrset_ptr->getName(), Name("example.com."));

    rrset_ptr = cache.lookupClosestRRset(Name("com."), RRType(2), klass);
    EXPECT_FALSE(rrset_ptr);
}

TEST_F(RecursorCacheTest, testClassIsSupported) {
    EXPECT_TRUE(cache.classIsSupported(1));
    EXPECT_TRUE(cache.classIsSupported(3));
    EXPECT_FALSE(cache.classIsSupported(2));
}

}
