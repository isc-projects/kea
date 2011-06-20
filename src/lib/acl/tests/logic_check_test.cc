// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "logcheck.h"
#include <acl/logic_check.h>

using namespace isc::acl;

namespace {

// Test the defs in AnyOfSpec
TEST(LogicOperators, AnyOfSpec) {
    EXPECT_FALSE(AnyOfSpec::start());
    EXPECT_FALSE(AnyOfSpec::terminate(false));
    EXPECT_TRUE(AnyOfSpec::terminate(true));
}

// Test the defs in AllOfSpec
TEST(LogicOperators, AllOfSpec) {
    EXPECT_TRUE(AllOfSpec::start());
    EXPECT_TRUE(AllOfSpec::terminate(false));
    EXPECT_FALSE(AnyOfSpec::terminate(true));
}

// Generic test of one check
template<typename Mode>
void
testCheck(bool emptyResult) {
    // It can be created
    LogicOperator<Mode, Log> oper;
    // It is empty by default
    EXPECT_EQ(0, oper.getSubexpressions().size());
    // And returns true, as all 0 of the subexpressions return true
    Log log;
    EXPECT_EQ(emptyResult, oper.matches(log));
    log.checkFirst(0);
    // Fill it with some subexpressions
    oper.addSubexpression(shared_ptr<ConstCheck>(new ConstCheck(emptyResult,
                                                                0)));
    oper.addSubexpression(shared_ptr<ConstCheck>(new ConstCheck(emptyResult,
                                                                1)));
    oper.addSubexpression(shared_ptr<ConstCheck>(new ConstCheck(!emptyResult,
                                                                2)));
    oper.addSubexpression(shared_ptr<ConstCheck>(new ConstCheck(!emptyResult,
                                                                3)));
    // They are listed there
    EXPECT_EQ(4, oper.getSubexpressions().size());
    // Now, the last one kills it, but the first ones will run, the fourth
    // won't
    EXPECT_EQ(!emptyResult, oper.matches(log));
    log.checkFirst(4);
}

TEST(LogicOperators, AllOf) {
    testCheck<AllOfSpec>(true);
}

TEST(LogicOperators, AnyOf) {
    testCheck<AnyOfSpec>(false);
}

}
