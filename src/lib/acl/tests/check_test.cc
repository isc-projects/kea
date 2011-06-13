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

#include <gtest/gtest.h>
#include <acl/check.h>

using namespace isc::acl;

namespace {

// This test has two function. For one, it checks the default implementations
// do what they should and it makes sure the template actually compiles
// (as templates are syntax-checked upon instantiation).

// This is a test check that just passes the boolean it gets.
class Pass : public Check<bool> {
public:
    virtual bool matches(const bool& value) const { return (value); }
};

// This is a simple test compound check. It contains two Pass checks
// and passes result of the first one.

class First : public CompoundCheck<bool> {
public:
    // The internal checks are public, so we can check the addresses
    Pass first, second;
    virtual Checks getSubexpressions() const {
        Checks result;
        result.push_back(&first);
        result.push_back(&second);
        return (result);
    }
    virtual bool matches(const bool& value) const {
        return (first.matches(value));
    }
};

TEST(Check, defaultCheckValues) {
    Pass p;
    EXPECT_EQ(Check<bool>::UNKNOWN_COST, p.cost());
    EXPECT_TRUE(p.matches(true));
    EXPECT_FALSE(p.matches(false));
    // The exact text is compiler dependant, but we check it returns something
    // and can be compiled
    EXPECT_FALSE(p.toText().empty());
}

TEST(Check, defaultCompoundValues) {
    First f;
    EXPECT_EQ(2 * Check<bool>::UNKNOWN_COST, f.cost());
    EXPECT_TRUE(f.pure());
    First::Checks c(f.getSubexpressions());
    ASSERT_EQ(2, c.size());
    EXPECT_EQ(&f.first, c[0]);
    EXPECT_EQ(&f.second, c[1]);
}

}
