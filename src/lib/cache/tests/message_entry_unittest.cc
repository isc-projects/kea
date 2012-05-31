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
#include <dns/message.h>
#include <util/buffer.h>
#include "../message_entry.h"
#include "../rrset_cache.h"
#include "../resolver_cache.h"
#include "cache_test_messagefromfile.h"
#include "cache_test_sectioncount.h"

using namespace isc::cache;
using namespace isc;
using namespace isc::dns;
using namespace std;

static uint32_t MAX_UINT32 = numeric_limits<uint32_t>::max();

namespace {

/// \brief Derived from base class to make it easy to test
/// its internals.
class DerivedMessageEntry: public MessageEntry {
public:
    DerivedMessageEntry(const isc::dns::Message& message,
                        const RRsetCachePtr& rrset_cache_,
                        const RRsetCachePtr& negative_soa_cache_):
             MessageEntry(message, rrset_cache_, negative_soa_cache_)
    {}

    /// \brief Wrap the protected function so that it can be tested.
    void parseSectionForTest(const Message& msg,
                           const Message::Section& section,
                           uint32_t& smaller_ttl,
                           uint16_t& rrset_count)
    {
        parseSection(msg, section, smaller_ttl, rrset_count);
    }

    RRsetTrustLevel getRRsetTrustLevelForTest(const Message& message,
                                              const RRsetPtr rrset,
                                              const Message::Section& section) 
    {
        return getRRsetTrustLevel(message, rrset, section);
    }

    bool getRRsetEntriesForTest(vector<RRsetEntryPtr> vec, time_t now) {
        return getRRsetEntries(vec, now);
    }

    time_t getExpireTime() {
        return expire_time_;
    }

};

class MessageEntryTest: public testing::Test {
public:
    MessageEntryTest(): class_(1),
                        message_parse(Message::PARSE),
                        message_render(Message::RENDER)
    {
        rrset_cache_.reset(new RRsetCache(RRSET_CACHE_DEFAULT_SIZE, class_));
        negative_soa_cache_.reset(new RRsetCache(NEGATIVE_RRSET_CACHE_DEFAULT_SIZE, class_));
    }

protected:
    uint16_t class_;
    RRsetCachePtr rrset_cache_;
    RRsetCachePtr negative_soa_cache_;
    Message message_parse;
    Message message_render;
};

TEST_F(MessageEntryTest, testParseRRset) {
    messageFromFile(message_parse, "message_fromWire3");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    uint32_t ttl = MAX_UINT32;
    uint16_t rrset_count = 0;
    message_entry.parseSectionForTest(message_parse, Message::SECTION_ANSWER, ttl, rrset_count);
    EXPECT_EQ(ttl, 21600);
    EXPECT_EQ(rrset_count, 1);

    ttl = MAX_UINT32;
    message_entry.parseSectionForTest(message_parse, Message::SECTION_AUTHORITY, ttl, rrset_count);
    EXPECT_EQ(ttl, 21600);
    EXPECT_EQ(rrset_count, 1);

    ttl = MAX_UINT32;
    message_entry.parseSectionForTest(message_parse, Message::SECTION_ADDITIONAL, ttl, rrset_count);
    EXPECT_EQ(ttl, 10800);
    EXPECT_EQ(rrset_count, 5);
}

TEST_F(MessageEntryTest, testGetRRsetTrustLevel_AA) {
    messageFromFile(message_parse, "message_fromWire3");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);

    RRsetIterator rrset_iter = message_parse.beginSection(Message::SECTION_ANSWER);
    RRsetTrustLevel level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                                    *rrset_iter,
                                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_AA);

    rrset_iter = message_parse.beginSection(Message::SECTION_AUTHORITY);
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                    *rrset_iter,
                                                    Message::SECTION_AUTHORITY);
    EXPECT_EQ(level, RRSET_TRUST_AUTHORITY_AA);

    rrset_iter = message_parse.beginSection(Message::SECTION_ADDITIONAL);
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                    *rrset_iter,
                                                    Message::SECTION_ADDITIONAL);
    EXPECT_EQ(level, RRSET_TRUST_ADDITIONAL_AA);
}

TEST_F(MessageEntryTest, testGetRRsetTrustLevel_NONAA) {
    messageFromFile(message_parse, "message_fromWire4");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    RRsetIterator rrset_iter = message_parse.beginSection(Message::SECTION_ANSWER);
    RRsetTrustLevel level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                                    *rrset_iter,
                                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_NONAA);

    rrset_iter = message_parse.beginSection(Message::SECTION_AUTHORITY);
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                    *rrset_iter,
                                                    Message::SECTION_AUTHORITY);
    EXPECT_EQ(level, RRSET_TRUST_AUTHORITY_NONAA);

    rrset_iter = message_parse.beginSection(Message::SECTION_ADDITIONAL);
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                    *rrset_iter,
                                                    Message::SECTION_ADDITIONAL);
    EXPECT_EQ(level, RRSET_TRUST_ADDITIONAL_NONAA);
}

TEST_F(MessageEntryTest, testGetRRsetTrustLevel_CNAME) {
    messageFromFile(message_parse, "message_fromWire5");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    RRsetIterator rrset_iter = message_parse.beginSection(Message::SECTION_ANSWER);
    RRsetTrustLevel level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                                    *rrset_iter,
                                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_AA);

    ++rrset_iter; // Get the rrset after the first cname rrset.
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                    *rrset_iter,
                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_NONAA);
}

TEST_F(MessageEntryTest, testGetRRsetTrustLevel_CNAME_and_DNAME) {
    messageFromFile(message_parse, "message_fromWire7");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    RRsetIterator rrset_iter = message_parse.beginSection(Message::SECTION_ANSWER);
    RRsetTrustLevel level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                                    *rrset_iter,
                                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_AA);
    // All the left rrset are non-authoritative
    ++rrset_iter;
    while (rrset_iter != message_parse.endSection(Message::SECTION_ANSWER)) {
        level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                        *rrset_iter,
                                                        Message::SECTION_ANSWER);
        ++rrset_iter;
        EXPECT_EQ(level, RRSET_TRUST_ANSWER_NONAA);
    }
}

TEST_F(MessageEntryTest, testGetRRsetTrustLevel_DNAME_and_CNAME) {
    messageFromFile(message_parse, "message_fromWire8");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    RRsetIterator rrset_iter = message_parse.beginSection(Message::SECTION_ANSWER);
    RRsetTrustLevel level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                                    *rrset_iter,
                                                                    Message::SECTION_ANSWER);
    // Test the deepest DNAME
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_AA);
    ++rrset_iter;
    // Test the synchronized CNAME
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                        *rrset_iter,
                                                        Message::SECTION_ANSWER);
    ++rrset_iter;
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_AA);

    ++rrset_iter;
    // All the left rrset are non-authoritative
    while (rrset_iter != message_parse.endSection(Message::SECTION_ANSWER)) {
        level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                        *rrset_iter,
                                                        Message::SECTION_ANSWER);
        ++rrset_iter;
        EXPECT_EQ(level, RRSET_TRUST_ANSWER_NONAA);
    }
}

TEST_F(MessageEntryTest, testGetRRsetTrustLevel_DNAME) {
    messageFromFile(message_parse, "message_fromWire6");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    RRsetIterator rrset_iter = message_parse.beginSection(Message::SECTION_ANSWER);
    RRsetTrustLevel level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                                    *rrset_iter,
                                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_AA);

    ++rrset_iter; // Get the rrset after the first dname rrset.
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                    *rrset_iter,
                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_AA);

    ++rrset_iter; // Get the second cname rrset
    level = message_entry.getRRsetTrustLevelForTest(message_parse,
                                                    *rrset_iter,
                                                    Message::SECTION_ANSWER);
    EXPECT_EQ(level, RRSET_TRUST_ANSWER_NONAA);
}

// We only test the expire_time of the message entry.
// The test for genMessage() will make sure whether InitMessageEntry()
// is right
TEST_F(MessageEntryTest, testInitMessageEntry) {
    messageFromFile(message_parse, "message_fromWire3");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    time_t expire_time = message_entry.getExpireTime();
    // 1 second should be enough to do the compare
    EXPECT_TRUE((time(NULL) + 10801) > expire_time);
}

TEST_F(MessageEntryTest, testGetRRsetEntries) {
    messageFromFile(message_parse, "message_fromWire3");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    vector<RRsetEntryPtr> vec;

    // the time is bigger than the smallest expire time of
    // the rrset in message.
    time_t expire_time = time(NULL) + 10802;
    EXPECT_FALSE(message_entry.getRRsetEntriesForTest(vec, expire_time));
}

TEST_F(MessageEntryTest, testGenMessage) {
    messageFromFile(message_parse, "message_fromWire3");
    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);
    time_t expire_time = message_entry.getExpireTime();

    Message msg(Message::RENDER);
    EXPECT_FALSE(message_entry.genMessage(expire_time + 2, msg));
    message_entry.genMessage(time(NULL), msg);
    // Check whether the generated message is same with cached one.
    EXPECT_FALSE(msg.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_FALSE(msg.getHeaderFlag(Message::HEADERFLAG_TC));
    EXPECT_EQ(1, sectionRRsetCount(msg, Message::SECTION_ANSWER));
    EXPECT_EQ(1, sectionRRsetCount(msg, Message::SECTION_AUTHORITY));
    EXPECT_EQ(5, sectionRRsetCount(msg, Message::SECTION_ADDITIONAL));

    // Check the rrset in answer section.
    EXPECT_EQ(1, msg.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(5, msg.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(7, msg.getRRCount(Message::SECTION_ADDITIONAL));
}

TEST_F(MessageEntryTest, testMaxTTL) {
    messageFromFile(message_parse, "message_large_ttl.wire");

    // The ttl of rrset from Answer and Authority sections are both 604801 seconds
    RRsetIterator iter = message_parse.beginSection(Message::SECTION_ANSWER);
    EXPECT_EQ(604801, (*iter)->getTTL().getValue());
    iter = message_parse.beginSection(Message::SECTION_AUTHORITY);
    EXPECT_EQ(604801, (*iter)->getTTL().getValue());

    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);

    // The ttl is limited to 604800 seconds (7days)
    EXPECT_EQ(time(NULL) + 604800, message_entry.getExpireTime());
}

TEST_F(MessageEntryTest, testMaxNegativeTTL) {
    messageFromFile(message_parse, "message_nxdomain_large_ttl.wire");

    // The ttl of rrset Authority sections are 10801 seconds
    RRsetIterator iter = message_parse.beginSection(Message::SECTION_AUTHORITY);
    EXPECT_EQ(10801, (*iter)->getTTL().getValue());

    DerivedMessageEntry message_entry(message_parse, rrset_cache_, negative_soa_cache_);

    // The ttl is limited to 10800 seconds (3 hours)
    EXPECT_EQ(time(NULL) + 10800, message_entry.getExpireTime());
}

}   // namespace
