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

#include <dns/message.h>
#include <dns/name.h>
#include <dns/rcode.h>
#include <dns/rrtype.h>

#include <datasrc/zonetable.h>

#include <auth/query.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::auth;

namespace {
class QueryTest : public ::testing::Test {
protected:
    QueryTest() :
        qname(Name("www.example.com")), qclass(RRClass::IN()),
        qtype(RRType::A()), response(Message::RENDER),
        query(zone_table, qname, qtype, response)
    {
        response.setRcode(Rcode::NOERROR());
    }
    ZoneTable zone_table;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    Message response;
    Query query;
};

TEST_F(QueryTest, noZone) {
    // There's no zone in the zone table.  So the response should have
    // SERVFAIL.
    query.process();
    EXPECT_EQ(Rcode::SERVFAIL(), response.getRcode());
}

TEST_F(QueryTest, matchZone) {
    // add a matching zone.  since the zone is empty right now, the response
    // should have NXDOMAIN.
    zone_table.addZone(ZonePtr(new MemoryZone(qclass, Name("example.com"))));
    query.process();
    EXPECT_EQ(Rcode::NXDOMAIN(), response.getRcode());
}

TEST_F(QueryTest, noMatchZone) {
    // there's a zone in the table but it doesn't match the qname.  should
    // result in SERVFAIL.
    zone_table.addZone(ZonePtr(new MemoryZone(qclass, Name("example.org"))));
    query.process();
    EXPECT_EQ(Rcode::SERVFAIL(), response.getRcode());
}
}
