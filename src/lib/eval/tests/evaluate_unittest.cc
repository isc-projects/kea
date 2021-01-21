// Copyright (C) 2015-2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <eval/evaluate.h>
#include <eval/eval_context.h>
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

        result_ = false;

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
    ASSERT_THROW(evaluateBool(e_, *pkt4_), EvalBadStack);
}

// This checks the empty expression: it should raise EvalBadStack
// when evaluated with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, empty6) {
    ASSERT_THROW(evaluateBool(e_, *pkt6_), EvalBadStack);
}

// This checks the { "false" } expression: it should return false
// when evaluated with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, false4) {
    TokenPtr tfalse;
    ASSERT_NO_THROW(tfalse.reset(new TokenString("false")));
    e_.push_back(tfalse);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
    EXPECT_FALSE(result_);
}

// This checks the { "false" } expression: it should return false
// when evaluated with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, false6) {
    TokenPtr tfalse;
    ASSERT_NO_THROW(tfalse.reset(new TokenString("false")));
    e_.push_back(tfalse);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
    EXPECT_FALSE(result_);
}

// This checks the { "true" } expression: it should return true
// when evaluated with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, true4) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
    EXPECT_TRUE(result_);
}

// This checks the { "true" } expression: it should return true
// when evaluated with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, true6) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
    EXPECT_TRUE(result_);
}

// This checks the evaluation must lead to "false" or "true"
// with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, bad4) {
    TokenPtr bad;
    ASSERT_NO_THROW(bad.reset(new TokenString("bad")));
    e_.push_back(bad);
    ASSERT_THROW(evaluateBool(e_, *pkt4_), EvalTypeError);
}

// This checks the evaluation must lead to "false" or "true"
// with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, bad6) {
    TokenPtr bad;
    ASSERT_NO_THROW(bad.reset(new TokenString("bad")));
    e_.push_back(bad);
    ASSERT_THROW(evaluateBool(e_, *pkt6_), EvalTypeError);
}

// This checks the evaluation must leave only one value on the stack
// with a Pkt4. (The actual packet is not used)
TEST_F(EvaluateTest, two4) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    e_.push_back(ttrue);
    ASSERT_THROW(evaluateBool(e_, *pkt4_), EvalBadStack);
}

// This checks the evaluation must leave only one value on the stack
// with a Pkt6. (The actual packet is not used)
TEST_F(EvaluateTest, two6) {
    TokenPtr ttrue;
    ASSERT_NO_THROW(ttrue.reset(new TokenString("true")));
    e_.push_back(ttrue);
    e_.push_back(ttrue);
    ASSERT_THROW(evaluateBool(e_, *pkt6_), EvalBadStack);
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

    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
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

    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
    EXPECT_FALSE(result_);
}

// A test using option existence
TEST_F(EvaluateTest, exists) {
    TokenPtr toption;

    ASSERT_NO_THROW(toption.reset(new TokenOption(100, TokenOption::EXISTS)));
    e_.push_back(toption);

    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
    EXPECT_TRUE(result_);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
    EXPECT_TRUE(result_);
}

// A test using option non-existence
TEST_F(EvaluateTest, dontExists) {
    TokenPtr toption;

    ASSERT_NO_THROW(toption.reset(new TokenOption(101, TokenOption::EXISTS)));
    e_.push_back(toption);

    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
    EXPECT_FALSE(result_);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
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

    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
    EXPECT_TRUE(result_);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
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

    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
    EXPECT_TRUE(result_);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
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
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt4_));
    EXPECT_TRUE(result_);
    ASSERT_NO_THROW(result_ = evaluateBool(e_, *pkt6_));
    EXPECT_TRUE(result_);
}

/// @brief Generic class for parsing expressions and evaluating them.
///
/// The main purpose of this class is to provide a generic interface to the
/// eval library, so everything (expression parsing and then evaluation for
/// given packets) can be done in one simple call.
///
/// These tests may be somewhat redundant to other more specialized tests, but
/// the idea here is to mass produce tests that are trivial to write.
class ExpressionsTest : public EvaluateTest {
public:

    /// @brief Checks if expression can be parsed and evaluated to bool
    ///
    /// There are skeleton packets created in pkt4_ and pkt6_. Make sure you
    /// tweak them as needed before calling this method.
    ///
    /// @param u universe (V4 or V6)
    /// @param expr expression to be parsed
    /// @param exp_result expected result (true or false)
    void testExpression(const Option::Universe& u, const std::string& expr,
                        const bool exp_result) {

        EvalContext eval(u);
        bool result = false;
        bool parsed = false;

        EXPECT_NO_THROW(parsed = eval.parseString(expr))
            << " while parsing expression " << expr;
        EXPECT_TRUE(parsed) << " for expression " << expr;

        switch (u) {
        case Option::V4:
            ASSERT_NO_THROW(result = evaluateBool(eval.expression, *pkt4_))
                << " for expression " << expr;
            break;
        case Option::V6:
            ASSERT_NO_THROW(result = evaluateBool(eval.expression, *pkt6_))
                << " for expression " << expr;
            break;
        }

        EXPECT_EQ(exp_result, result) << " for expression " << expr;
    }

    /// @brief Checks if expression can be parsed and evaluated to string
    ///
    /// There are skeleton packets created in pkt4_ and pkt6_. Make sure you
    /// tweak them as needed before calling this method.
    ///
    /// @param u universe (V4 or V6)
    /// @param expr expression to be parsed
    /// @param exp_result expected result (string)
    void testExpressionString(const Option::Universe& u, const std::string& expr,
                              const std::string& exp_result) {

        EvalContext eval(u);
        string result;
        bool parsed = false;

        EXPECT_NO_THROW(parsed = eval.parseString(expr, EvalContext::PARSER_STRING))
            << " while parsing expression " << expr;
        EXPECT_TRUE(parsed) << " for expression " << expr;

        switch (u) {
        case Option::V4:
            ASSERT_NO_THROW(result = evaluateString(eval.expression, *pkt4_))
                << " for expression " << expr;
            break;
        case Option::V6:
            ASSERT_NO_THROW(result = evaluateString(eval.expression, *pkt6_))
                << " for expression " << expr;
            break;
        }

        EXPECT_EQ(exp_result, result) << " for expression " << expr;
    }

    /// @brief Checks that specified expression throws expected exception.
    ///
    /// @tparam ex exception type expected to be thrown
    /// @param expr expression to be evaluated
    template<typename ex>
    void testExpressionNegative(const std::string& expr,
                                const Option::Universe& u = Option::V4,
                                EvalContext::ParserType type = EvalContext::PARSER_BOOL) {
        EvalContext eval(u);

        EXPECT_THROW(eval.parseString(expr, type), ex) << "while parsing expression "
                                                 << expr;
    }
};

// This is a quick way to check if certain expressions are valid or not and
// whether the whole expression makes sense. This particular test checks if
// integers can be used properly in expressions. There are many places where
// integers are used. This particular test checks if pkt6.msgtype returns
// something that can be compared with integers.
//
// For basic things we can take advantage of the skeleton packets created in
// EvaluateTest constructors: The packet type is DISCOVER in DHCPv4 and
// SOLICIT in DHCPv6. There is one option added with code 100 and content
// being either "hundred4" or "hundred6" depending on the universe.

// Tests if pkt6.msgtype returns something that can be compared with integers.
TEST_F(ExpressionsTest, expressionsInteger1) {
    testExpression(Option::V6, "pkt6.msgtype == 1", true);
    testExpression(Option::V6, "pkt6.msgtype == 2", false);

    testExpression(Option::V6, "pkt6.msgtype == 0x00000001", true);
    testExpression(Option::V6, "pkt6.msgtype == 0x00000002", false);
}

// Tests if pkt6.transid returns something that can be compared with integers.
TEST_F(ExpressionsTest, expressionsInteger2) {
    testExpression(Option::V6, "pkt6.transid == 0", false);
    testExpression(Option::V6, "pkt6.transid == 12345", true);
    testExpression(Option::V6, "pkt6.transid == 12346", false);
}

// Tests if pkt4.transid returns something that can be compared with integers.
TEST_F(ExpressionsTest, expressionsInteger3) {
    testExpression(Option::V4, "pkt4.transid == 0", false);
    testExpression(Option::V4, "pkt4.transid == 12345", true);
    testExpression(Option::V4, "pkt4.transid == 12346", false);
}

// Tests if integers can be compared with integers.
TEST_F(ExpressionsTest, expressionsInteger4) {
    testExpression(Option::V6, "0 == 0", true);
    testExpression(Option::V6, "2 == 3", false);
}

// Tests if pkt4.hlen and pkt4.htype return values that can be compared with integers.
TEST_F(ExpressionsTest, expressionsPkt4Hlen) {

    // By default there's no hardware set up. The default Pkt4 constructor
    // creates HWAddr(), which has hlen=0 and htype set to HTYPE_ETHER.
    testExpression(Option::V4, "pkt4.hlen == 0", true);
    testExpression(Option::V4, "pkt4.htype == 1", true);

    // Ok, let's initialize the hardware address to something plausible.
    const size_t hwaddr_len = 6;
    const uint16_t expected_htype = 123;
    std::vector<uint8_t> hw(hwaddr_len,0);
    for (int i = 0; i < hwaddr_len; i++) {
        hw[i] = i + 1;
    }
    pkt4_->setHWAddr(expected_htype, hwaddr_len, hw);

    testExpression(Option::V4, "pkt4.hlen == 0", false);
    testExpression(Option::V4, "pkt4.hlen == 5", false);
    testExpression(Option::V4, "pkt4.hlen == 6", true);
    testExpression(Option::V4, "pkt4.hlen == 7", false);

    testExpression(Option::V4, "pkt4.htype == 0", false);
    testExpression(Option::V4, "pkt4.htype == 122", false);
    testExpression(Option::V4, "pkt4.htype == 123", true);
    testExpression(Option::V4, "pkt4.htype == 124", false);

    testExpression(Option::V4, "pkt4.mac == 0x010203040506", true);
}

// Test if expressions message type can be detected in Pkt4.
// It also doubles as a check for integer comparison here.
TEST_F(ExpressionsTest, expressionsPkt4type) {

    // We can inspect the option content directly, but
    // it requires knowledge of the option type and its format.
    testExpression(Option::V4, "option[53].hex == 0x0", false);
    testExpression(Option::V4, "option[53].hex == 0x1", true);
    testExpression(Option::V4, "option[53].hex == 0x2", false);

    // It's easier to simply use the pkt4.msgtype
    testExpression(Option::V4, "pkt4.msgtype == 0", false);
    testExpression(Option::V4, "pkt4.msgtype == 1", true);
    testExpression(Option::V4, "pkt4.msgtype == 2", false);
}

// This tests if inappropriate values (negative, too large) are
// rejected, but extreme values still allowed for uint32_t are ok.
TEST_F(ExpressionsTest, invalidIntegers) {

    // These are the extreme uint32_t values that still should be accepted.
    testExpression(Option::V4, "4294967295 == 0", false);

    // Negative integers should be rejected.
    testExpressionNegative<EvalParseError>("4294967295 == -1");

    // Oops, one too much.
    testExpressionNegative<EvalParseError>("4294967296 == 0");
}

// Tests whether expressions can be evaluated to a string.
TEST_F(ExpressionsTest, evaluateString) {

    // Check that content of the options is returned properly.
    testExpressionString(Option::V4, "option[100].hex", "hundred4");
    testExpressionString(Option::V6, "option[100].hex", "hundred6");

    // Check that content of non-existing option returns empty string.
    testExpressionString(Option::V4, "option[200].hex", "");
    testExpressionString(Option::V6, "option[200].hex", "");

    testExpressionNegative<EvalParseError>("pkt4.msgtype == 1", Option::V4,
                                           EvalContext::PARSER_STRING);
    testExpressionNegative<EvalParseError>("pkt6.msgtype == 1", Option::V6,
                                           EvalContext::PARSER_STRING);

    // Check that ifelse works as expecting (it was added explicitly for
    // the string evaluation).
    testExpressionString(Option::V4,
                         "ifelse(option[100].exists,'foo','bar')", "foo");
    testExpressionString(Option::V4,
                         "ifelse(option[200].exists,'foo','bar')", "bar");

    // Check that ifelse can be chained.
    testExpressionString(Option::V4,
                         "ifelse(option[200].exists,option[200].hex,"
                                 "ifelse(option[100].exists,"
                                         "option[100].hex,'none?'))",
                         "hundred4");

    // Check that hexstring works as expecting.
    testExpressionString(Option::V4, "hexstring(0x1234,':')", "12:34");
    testExpressionString(Option::V4, "hexstring(0x56789a,'-')", "56-78-9a");
    testExpressionString(Option::V4, "hexstring(0xbcde,'')", "bcde");
    testExpressionString(Option::V4, "hexstring(0xf01234,'..')", "f0..12..34");
}

};
