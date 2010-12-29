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
#include <dns/rrttl.h>
#include <dns/rrtype.h>

#include <datasrc/memory_datasrc.h>

#include <auth/query.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::auth;

RRsetPtr a_rrset = RRsetPtr(new RRset(Name("www.example.com"),
                                      RRClass::IN(), RRType::A(),
                                      RRTTL(3600)));
RRsetPtr glue_a_rrset(RRsetPtr(new RRset(Name("glue.a.example.com"),
                                         RRClass::IN(), RRType::A(),
                                         RRTTL(3600)))),
RRsetPtr glue_aaaa_rrset(RRsetPtr(new RRset(Name("glue.aaaa.example.com"),
                                            RRClass::IN(), RRType::AAAA(),
                                            RRTTL(3600)))),
namespace {
// This is a mock Zone class for testing.
// It is a derived class of Zone, and simply hardcode the results of find()
// return SUCCESS for "www.example.com",
// return NXDOMAIN for "nxdomain.example.com",
// return NXRRSET for "nxrrset.example.com",
// return CNAME for "cname.example.com",
// else return DNAME
class MockZone : public Zone {
public:
    MockZone() : origin_(Name("example.com")),
                 ns_rrset(RRsetPtr(new RRset(Name("delegation.example.com"),
                                             RRClass::IN(), RRType::NS(),
                                             RRTTL(3600))))
    {
        ns_rrset.addRdata(rdata::generic::NS(
                          Name("glue.a.example.com")));
        ns_rrset.addRdata(rdata::generic::NS(
                          Name("glue.aaaa.example.com")));
    }
    virtual const isc::dns::Name& getOrigin() const;
    virtual const isc::dns::RRClass& getClass() const;

    FindResult find(const isc::dns::Name& name,
            const isc::dns::RRType& type) const;

private:
    Name origin_;
    RRsetPtr ns_rrset;
};

const Name&
MockZone::getOrigin() const {
    return (origin_);
}

const RRClass&
MockZone::getClass() const {
    return (RRClass::IN());
}

Zone::FindResult
MockZone::find(const Name& name, const RRType&) const {
    // hardcode the find results
    if (name == Name("www.example.com")) {
        return (FindResult(SUCCESS, a_rrset));
    } else if (name == Name("glue.a.example.com")) {
        return (FindResult(SUCCESS, glue_a_rrset));
    } else if (name == Name("glue.aaaa.example.com")) {
        return (FindResult(SUCCESS, glue_aaaa_rrset));
    } else if (name == Name("delegation.example.com")) {
        return (FindResult(DELEGATION, ns_rrset));
    } else if (name == Name("nxdomain.example.com")) {
        return (FindResult(NXDOMAIN, RRsetPtr()));
    } else if (name == Name("nxrrset.example.com")) {
        return FindResult(NXRRSET, RRsetPtr());
    } else if ((name == Name("cname.example.com"))) {
        return (FindResult(CNAME, RRsetPtr()));
    } else {
        return (FindResult(DNAME, RRsetPtr()));
    }
}

class QueryTest : public ::testing::Test {
protected:
    QueryTest() :
        qname(Name("www.example.com")), qclass(RRClass::IN()),
        qtype(RRType::A()), response(Message::RENDER),
        query(memory_datasrc, qname, qtype, response)
    {
        response.setRcode(Rcode::NOERROR());
    }
    MemoryDataSrc memory_datasrc;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    Message response;
    Query query;
};

TEST_F(QueryTest, noZone) {
    // There's no zone in the memory datasource.  So the response should have
    // REFUSED.
    query.process();
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

TEST_F(QueryTest, matchZone) {
    // match qname, normal query
    memory_datasrc.addZone(ZonePtr(new MockZone()));
    query.process();
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ANSWER,
                                  Name("www.example.com"), RRClass::IN(),
                                  RRType::A()));

    // Delegation
    const Name delegation_name(Name("delegation.example.com"));
    Query delegation_query(memory_datasrc, delegation_name, qtype, response);
    delegation_query.process();
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
    EXPECT_TRUE(response.hasRRset(Message::SECTION_AUTHORITY,
                                  Name("delegation.example.com"),
                                  RRClass::IN(), RRType::NS()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.a.example.com"),
                                  RRClass::IN(), RRType::A()));
    EXPECT_TRUE(response.hasRRset(Message::SECTION_ADDITIONAL,
                                  Name("glue.aaaa.example.com"),
                                  RRClass::IN(), RRType::AAAA()));

    // NXDOMAIN
    const Name nxdomain_name(Name("nxdomain.example.com"));
    Query nxdomain_query(memory_datasrc, nxdomain_name, qtype, response);
    nxdomain_query.process();
    EXPECT_EQ(Rcode::NXDOMAIN(), response.getRcode());

    // NXRRSET
    const Name nxrrset_name(Name("nxrrset.example.com"));
    Query nxrrset_query(memory_datasrc, nxrrset_name, qtype, response);
    nxrrset_query.process();
    EXPECT_EQ(Rcode::NOERROR(), response.getRcode());
}

TEST_F(QueryTest, noMatchZone) {
    // there's a zone in the memory datasource but it doesn't match the qname.
    // should result in REFUSED.
    memory_datasrc.addZone(ZonePtr(new MockZone()));
    const Name nomatch_name(Name("example.org"));
    Query nomatch_query(memory_datasrc, nomatch_name, qtype, response);
    nomatch_query.process();
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}
}
