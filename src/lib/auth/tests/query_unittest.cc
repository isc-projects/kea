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

#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rrclass.h>

#include <auth/query.h>

namespace {

using namespace isc::dns;
using namespace isc::auth;


class QueryTest : public ::testing::Test {
protected:
    QueryTest() :
        name(Name("www.example.com")),
        rrtype(RRType::A()),
        rrclass(RRClass::IN())
    {}
    const Name name;
    const RRType rrtype;
    const RRClass rrclass;
};

QueryTaskPtr
createTask(const Name& name, const RRClass& rrclass0, const RRType& rrtype0) {
    RRType rrtype(rrtype0);
    return (QueryTaskPtr(new QueryTask(name, rrclass0, rrtype,
                                       QueryTask::SIMPLE_QUERY)));
}

// Check the QueryTask created using a temporary RRType object will remain
// valid.
TEST_F(QueryTest, constructWithTemporary) {
    QueryTaskPtr task_a = createTask(name, rrclass, RRType::A());
    QueryTaskPtr task_aaaa = createTask(name, rrclass, RRType::AAAA());
    EXPECT_EQ(rrtype, task_a->qtype);
}

}
