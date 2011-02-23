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
#include <cache/local_zone_data.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include "cache_test_messagefromfile.h"

using namespace isc::cache;
using namespace isc::dns;
using namespace std;

namespace {

class LocalZoneDataTest: public testing::Test {
protected:
    LocalZoneDataTest(): local_zone_data(1) 
    {
    }

    LocalZoneData local_zone_data;
};

TEST_F(LocalZoneDataTest, updateAndLookup) {
    Message msg(Message::PARSE);
    messageFromFile(msg, "message_fromWire3");
    RRsetIterator rrset_iter = msg.beginSection(Message::SECTION_AUTHORITY);
    Name name = (*rrset_iter)->getName();
    RRType type = (*rrset_iter)->getType();

    EXPECT_FALSE(local_zone_data.lookup(name, type));
    local_zone_data.update((*(*rrset_iter).get()));
    EXPECT_TRUE(local_zone_data.lookup(name, type));

    // Test whether the old one is replaced
    uint32_t ttl = (*rrset_iter)->getTTL().getValue();
    // Make sure it is not zero
    ASSERT_NE(ttl / 2, ttl);
    
    RRsetPtr rrset_ptr = local_zone_data.lookup(name, type);
    EXPECT_EQ(ttl, rrset_ptr->getTTL().getValue());

    (*rrset_iter)->setTTL(RRTTL(ttl/2));

    local_zone_data.update((*(*rrset_iter).get()));
    rrset_ptr = local_zone_data.lookup(name, type);
    EXPECT_EQ(ttl/2, rrset_ptr->getTTL().getValue());
}

}
