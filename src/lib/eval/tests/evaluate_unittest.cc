// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <eval/evaluate.h>
#include <eval/token.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_string.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture for testing evaluation.
///
/// This class provides several convenience objects to be used during testing
/// of the evaluation of classification expressions.
class EvaluateTest : public ::testing::Test {
public:

    /// @brief Initializes Pkt4,Pkt6 and options that can be useful for
    ///        evaluation tests.
    EvaluateTest() {
        e_.clear();

        pkt4_.reset(new Pkt4(DHCPDISCOVER, 12345));
        pkt6_.reset(new Pkt6(DHCPV6_SOLICIT, 12345));

        // Add options with easily identifiable strings in them
        option_str4_.reset(new OptionString(Option::V4, 100, "hundred4"));
        option_str6_.reset(new OptionString(Option::V6, 100, "hundred6"));

        pkt4_->addOption(option_str4_);
        pkt6_->addOption(option_str6_);
    }

    Expression e_; ///< An expression

    bool result_; ///< A decision

    Pkt4Ptr pkt4_; ///< A stub DHCPv4 packet
    Pkt6Ptr pkt6_; ///< A stub DHCPv6 packet

    OptionPtr option_str4_; ///< A string option for DHCPv4
    OptionPtr option_str6_; ///< A string option for DHCPv6

    /// @todo: Add more option types here
};

// This checks the empty expression: it should raise EvalBadStack
// when evaluated with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, empty4) {
    ASSERT_THROW(evaluate(e_, *pkt4_), EvalBadStack);
}

// This checks the empty expression: it should raise EvalBadStack
// when evaluated with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, empty6) {
    ASSERT_THROW(evaluate(e_, *pkt6_), EvalBadStack);
}

// This checks the { "false" } expression: it should return false
// when evaluated with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, false4) {
    TokenPtr tfalse;
    ASSERT_NO_THROW(tfalse.reset(new TokenString("false")));
    e_.push_back(tfalse);
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt4_));
    EXPECT_FALSE(result_);
}

// This checks the { "false" } expression: it should return false
// when evaluated with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, false6) {
    TokenPtr tfalse;
    ASSERT_NO_THROW(tfalse.reset(new TokenString("false")));
    e_.push_back(tfalse);
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt6_));
    EXPECT_FALSE(result_);
}

// This checks the { "true" } expression: it should return true
// when evaluated with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, true4) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt4_));
    EXPECT_TRUE(result_);
}

// This checks the { "true" } expression: it should return true
// when evaluated with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, true6) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt6_));
    EXPECT_TRUE(result_);
}

// This checks the evaluation must lead to "false" or "true"
// with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, bad4) {
    TokenPtr bad;
    ASSERT_NO_THROW(bad.reset(new TokenString("bad")));
    e_.push_back(bad);
    ASSERT_THROW(evaluate(e_, *pkt4_), EvalTypeError);
}

// This checks the evaluation must lead to "false" or "true"
// with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, bad6) {
    TokenPtr bad;
    ASSERT_NO_THROW(bad.reset(new TokenString("bad")));
    e_.push_back(bad);
    ASSERT_THROW(evaluate(e_, *pkt6_), EvalTypeError);
}

// This checks the evaluation must leave only one value on the stack
// with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, two4) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    e_.push_back(ttrue);
    ASSERT_THROW(evaluate(e_, *pkt4_), EvalBadStack);
}

// This checks the evaluation must leave only one value on the stack
// with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, two6) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    e_.push_back(ttrue);
    ASSERT_THROW(evaluate(e_, *pkt6_), EvalBadStack);
}

// A more complex test evaluated with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, compare4) {
    TokenPtr tfoo;
    TokenPtr tbar;
    TokenPtr tequal;

    ASSERT_NO_THROW(tfoo.reset(new TokenString("foo")));
    e_.push_back(tfoo);
    ASSERT_NO_THROW(tbar.reset(new TokenString("bar")));
    e_.push_back(tbar);
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));
    e_.push_back(tequal);

    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt4_));
    EXPECT_FALSE(result_);
}

// A more complex test evaluated with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, compare6) {
    TokenPtr tfoo;
    TokenPtr tbar;
    TokenPtr tequal;

    ASSERT_NO_THROW(tfoo.reset(new TokenString("foo")));
    e_.push_back(tfoo);
    ASSERT_NO_THROW(tbar.reset(new TokenString("bar")));
    e_.push_back(tbar);
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));
    e_.push_back(tequal);

    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt6_));
    EXPECT_FALSE(result_);
}

// A test using packets.
TEST_F(EvaluateTest, packet) {
    TokenPtr toption;
    TokenPtr tstring;
    TokenPtr tequal;

    ASSERT_NO_THROW(toption.reset(new TokenOption(100, TokenOption::TEXTUAL)));
    e_.push_back(toption);
    ASSERT_NO_THROW(tstring.reset(new TokenString("hundred4")));
    e_.push_back(tstring);
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));
    e_.push_back(tequal);

    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt4_));
    EXPECT_TRUE(result_);
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt6_));
    EXPECT_FALSE(result_);
}

// A test which compares option value represented in hexadecimal format.
TEST_F(EvaluateTest, optionHex) {
    TokenPtr toption;
    TokenPtr tstring;
    TokenPtr tequal;

    ASSERT_NO_THROW(toption.reset(new TokenOption(100, TokenOption::HEXADECIMAL)));
    e_.push_back(toption);
    ASSERT_NO_THROW(tstring.reset(new TokenString("hundred4")));
    e_.push_back(tstring);
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));
    e_.push_back(tequal);

    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt4_));
    EXPECT_TRUE(result_);
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt6_));
    EXPECT_FALSE(result_);
}

// A test using substring on an option.
TEST_F(EvaluateTest, complex) {
    TokenPtr toption;
    TokenPtr tstart;
    TokenPtr tlength;
    TokenPtr tsubstring;
    TokenPtr tstring;
    TokenPtr tequal;

    // Get the option, i.e., "hundred[46]"
    ASSERT_NO_THROW(toption.reset(new TokenOption(100, TokenOption::TEXTUAL)));
    e_.push_back(toption);

    // Get substring("hundred[46]", 0, 7), i.e., "hundred"
    ASSERT_NO_THROW(tstart.reset(new TokenString("0")));
    e_.push_back(tstart);
    ASSERT_NO_THROW(tlength.reset(new TokenString("7")));
    e_.push_back(tlength);
    ASSERT_NO_THROW(tsubstring.reset(new TokenSubstring()));
    e_.push_back(tsubstring);

    // Compare with "hundred"
    ASSERT_NO_THROW(tstring.reset(new TokenString("hundred")));
    e_.push_back(tstring);
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));
    e_.push_back(tequal);

    // Should return true for v4 and v6 packets
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt4_));
    EXPECT_TRUE(result_);
    ASSERT_NO_THROW(result_ = evaluate(e_, *pkt6_));
    EXPECT_TRUE(result_);
}

};
