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

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/rrtype.h>
#include <dns/rrclass.h>

#include <datasrc/query.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace isc::dns;
using namespace isc::datasrc;

namespace {

void
createQuery(Message& m, const Name& qname, const RRClass& qclass,
            const RRType& qtype)
{
    m.setOpcode(Opcode::QUERY());
    m.setHeaderFlag(MessageFlag::RD());
    m.addQuestion(Question(qname, qclass, qtype));
}

QueryTaskPtr
createTask(Message& m, const Name& name, const RRType& rrtype0, HotCache& c) {
    RRType rrtype(rrtype0);
    Query q(m, c, true);
    return (QueryTaskPtr(new QueryTask(q, name, rrtype,
                                       QueryTask::SIMPLE_QUERY)));
}

// Check the QueryTask created using a temporary RRType object will remain
// valid.
TEST(QueryTest, constructWithTemporary) {
    HotCache cache;

    Message m1(Message::RENDER);
    createQuery(m1, Name("www.wild.example.com"), RRClass::IN(), RRType::A()); 
    QueryTaskPtr task_a = createTask(m1, Name("www.wild.example.com"),
                                        RRType::A(), cache);
    EXPECT_EQ(RRType::A(), task_a->qtype);

    Message m2(Message::RENDER);
    createQuery(m2, Name("www.wild.example.com"), RRClass::IN(),
                RRType::AAAA());
    QueryTaskPtr task_aaaa = createTask(m2, Name("www.wild.example.com"),
                                        RRType::AAAA(), cache);
    EXPECT_EQ(RRType::AAAA(), task_aaaa->qtype);

}

}
