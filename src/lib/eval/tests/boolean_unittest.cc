// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <eval/eval_context.h>
#include <eval/evaluate.h>
#include <eval/token.h>
#include <dhcp/pkt4.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture for testing booleans.
class BooleanTest : public ::testing::Test {
public:
    void check(const string& expr, bool expected) {
        EvalContext eval(Option::V4);
        ASSERT_TRUE(eval.parseString(expr));
        Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
        if (expected) {
            EXPECT_TRUE(evaluate(eval.expression, *pkt4));
        } else {
            EXPECT_FALSE(evaluate(eval.expression, *pkt4));
        }
    }
};

// A group of tests
TEST_F(BooleanTest, tests) {
    // true and (false or false)
    check("('a' == 'a') and (('a' == 'b') or ('b' == 'a'))", false);
    // (true and false) or false
    check("(('a' == 'a') and ('a' == 'b')) or ('b' == 'a')", false);
    // not true
    check("not ('a' == 'a')", false);
    // not false
    check("not ('a' == 'b')", true);
    // true and true and true and false
    check("('a' == 'a') and ('b' == 'b') and ('c' == 'c') and ('a' == 'c')",
          false);
    // false or false or false or true
    check("('a' == 'b') or ('a' == 'c') or ('b' == 'c') or ('b' == 'b')",
          true);
    // true or false or false or false
    check("('a' == 'a') or ('a' == 'b') or ('a' == 'c') or ('b' == 'c')",
          true);
    // not (true or false)
    check("not (('a' == 'a') or ('a' == 'b'))", false);
    // not (true and false)
    check("not (('a' == 'a') and ('a' == 'b'))", true);
    // (not true) and false
    check("(not ('a' == 'a')) and ('a' == 'b')",false);
}

};
