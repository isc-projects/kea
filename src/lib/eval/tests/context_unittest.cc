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
#include <eval/token.h>
#include <eval/eval_context.h>
#include <eval/token.h>
#include <dhcp/pkt4.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::dhcp;

namespace {

/// @brief Test class for testing EvalContext aka class test parsing
class EvalContextTest : public ::testing::Test {
public:
    /// @brief checks if the given token is a string with the expected value
    void checkTokenString(const TokenPtr& token, const std::string& expected) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenString> str =
            boost::dynamic_pointer_cast<TokenString>(token);
        ASSERT_TRUE(str);

        Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
        ValueStack values;

        EXPECT_NO_THROW(token->evaluate(*pkt4, values));

        ASSERT_EQ(1, values.size());

        EXPECT_EQ(expected, values.top());
    }

    /// @brief checks if the given token is a hex string with the expected value
    void checkTokenHexString(const TokenPtr& token,
                             const std::string& expected) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenHexString> hex =
            boost::dynamic_pointer_cast<TokenHexString>(token);
        ASSERT_TRUE(hex);

        Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
        ValueStack values;

        EXPECT_NO_THROW(token->evaluate(*pkt4, values));

        ASSERT_EQ(1, values.size());

        EXPECT_EQ(expected, values.top());
    }

    /// @brief checks if the given token is an equal operator
    void checkTokenEq(const TokenPtr& token) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenEqual> eq =
            boost::dynamic_pointer_cast<TokenEqual>(token);
        EXPECT_TRUE(eq);
    }

    /// @brief checks if the given token is an option with the expected code
    void checkTokenOption(const TokenPtr& token, uint16_t expected_code) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenOption> opt =
            boost::dynamic_pointer_cast<TokenOption>(token);
        ASSERT_TRUE(opt);

        EXPECT_EQ(expected_code, opt->getCode());
    }

    /// @brief checks if the given token is a substring operator
    void checkTokenSubstring(const TokenPtr& token) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenSubstring> sub =
            boost::dynamic_pointer_cast<TokenSubstring>(token);
        EXPECT_TRUE(sub);
    }

    /// @brief checks if the given expression raises the expected message
    /// when it is parsed.
    void checkError(const string& expr, const string& msg) {
        EvalContext eval;
        parsed_ = false;
        try {
            parsed_ = eval.parseString(expr);
            FAIL() << "Expected EvalParseError but nothing was raised";
        }
        catch (const EvalParseError& ex) {
            EXPECT_EQ(msg, ex.what());
            EXPECT_FALSE(parsed_);
        }
        catch (...) {
            FAIL() << "Expected EvalParseError but something else was raised";
        }
    }

    /// @brief checks if the given expression raises the expected message
    /// when it is parsed by the strongly typed parser but is accepted
    /// by the untyped one.
    void checkTyped(const string& expr, const string& msg) {
        EvalContext eval;
        parsed_ = false;
        EXPECT_NO_THROW(parsed_ = eval.parseString("untyped:" + expr));
        EXPECT_TRUE(parsed_);
        parsed_ = false;
        try {
            parsed_ = eval.parseString(expr);
            FAIL() << "Expected EvalParseError but nothing was raised";
        }
        catch (const EvalParseError& ex) {
            EXPECT_EQ(msg, ex.what());
            EXPECT_FALSE(parsed_);
        }
        catch (...) {
            FAIL() << "Expected EvalParseError but something else was raised";
        }
    }
  

    bool parsed_; ///< Parsing status
};

// Test the parsing of a basic expression
TEST_F(EvalContextTest, basic) {

    EvalContext tmp;

    EXPECT_NO_THROW(parsed_ = tmp.parseString("option[123] == 'MSFT'"));
    EXPECT_TRUE(parsed_);
}

// Test the parsing of a string terminal
TEST_F(EvalContextTest, string) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ = eval.parseString("untyped: 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(1, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenString(tmp, "foo");
}

// Test the parsing of a basic expression with a constant string holding
// a number.
TEST_F(EvalContextTest, number) {

    EvalContext eval;

    EXPECT_NO_THROW(parsed_ =
        eval.parseString("substring(option[123], '0', '2') == '42'"));
    EXPECT_TRUE(parsed_);
    parsed_ = false;
    EXPECT_NO_THROW(parsed_ =
        eval.parseString("untyped: substring(option[123], '0', '2') == '42'"));
    EXPECT_TRUE(parsed_);

}

// Test the parsing of a hexstring terminal
TEST_F(EvalContextTest, hexstring) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ = eval.parseString("untyped: 0x666f6f"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(1, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenHexString(tmp, "foo");
}

// Test the parsing of a hexstring terminal with an odd number of
// hexadecimal digits
TEST_F(EvalContextTest, oddHexstring) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ = eval.parseString("untyped: 0X7"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(1, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenHexString(tmp, "\a");
}

// Test the parsing of an equal expression
TEST_F(EvalContextTest, equal) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ = eval.parseString("'foo' == 'bar'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp1 = eval.expression.at(0);
    TokenPtr tmp2 = eval.expression.at(1);
    TokenPtr tmp3 = eval.expression.at(2);

    checkTokenString(tmp1, "foo");
    checkTokenString(tmp2, "bar");
    checkTokenEq(tmp3);
}

// Test the parsing of an option terminal
TEST_F(EvalContextTest, option) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ = eval.parseString("untyped: option[123]"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(1, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 123);
}

// Test the parsing of a substring expression
TEST_F(EvalContextTest, substring) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ =
        eval.parseString("untyped: substring('foobar','2','3')"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(4, eval.expression.size());

    TokenPtr tmp1 = eval.expression.at(0);
    TokenPtr tmp2 = eval.expression.at(1);
    TokenPtr tmp3 = eval.expression.at(2);
    TokenPtr tmp4 = eval.expression.at(3);

    checkTokenString(tmp1, "foobar");
    checkTokenString(tmp2, "2");
    checkTokenString(tmp3, "3");
    checkTokenSubstring(tmp4);
}

// Test some scanner error cases
TEST_F(EvalContextTest, scanErrors) {
    checkError("'", "<string>:1.1: Invalid character: '");
    checkError("'\''", "<string>:1.3: Invalid character: '");
    checkError("'\n'", "<string>:1.1: Invalid character: '");
    checkError("0x123h", "<string>:1.6: Invalid character: h");
    checkError("=", "<string>:1.1: Invalid character: =");
    checkError("subtring", "<string>:1.1: Invalid character: s");
    checkError("untype: 'abc'", "<string>:1.1: Invalid character: u");
    checkError("untyped 'abc'", "<string>:1.1: Invalid character: u");
    checkError("foo", "<string>:1.1: Invalid character: f");
    checkError(" bar", "<string>:1.2: Invalid character: b");
}

// Tests some scanner/parser error cases
TEST_F(EvalContextTest, scanParseErrors) {
    checkError("", "<string>:1.1: syntax error, unexpected end of file");
    checkError("untyped:",
               "<string>:1.9: syntax error, unexpected end of file");
    checkError("0x", "<string>:1.1: syntax error, unexpected integer");
    checkError("0abc",
               "<string>:1.1: syntax error, unexpected integer");
    checkError("===", "<string>:1.1-2: syntax error, unexpected ==");
    checkError("option[-1]",
               "<string>:1.8-9: Option code has invalid "
               "value in -1. Allowed range: 0..65535");
    checkError("option[65536]",
               "<string>:1.8-12: Option code has invalid "
               "value in 65536. Allowed range: 0..65535");
    checkError("option[123] < 'foo'", "<string>:1.13: Invalid character: <");
}

// Tests some parser error cases
TEST_F(EvalContextTest, parseErrors) {
    checkError("untyped:'foo''bar'",
               "<string>:1.14-18: syntax error, unexpected "
               "constant string, expecting end of file");
    checkError("'foo''bar'",
               "<string>:1.6-10: syntax error, unexpected constant string, "
               "expecting ==");
    checkError("== 'ab'", "<string>:1.1-2: syntax error, unexpected ==");
    checkError("'foo' ==",
               "<string>:1.9: syntax error, unexpected end of file");
    checkError("option 'ab'",
               "<string>:1.8-11: syntax error, unexpected "
               "constant string, expecting [");
    checkError("option(10) == 'ab'",
               "<string>:1.7: syntax error, "
               "unexpected (, expecting [");
    checkError("option['ab'] == 'foo'",
               "<string>:1.8-11: syntax error, "
               "unexpected constant string, "
               "expecting integer");
    checkError("option[0xa] == 'ab'",
               "<string>:1.8-10: syntax error, "
               "unexpected constant hexstring, "
               "expecting integer");
    checkError("substring('foobar') == 'f'",
               "<string>:1.19: syntax error, "
               "unexpected ), expecting \",\"");
    checkError("substring('foobar','3') == 'bar'",
               "<string>:1.23: syntax error, unexpected ), expecting \",\"");
    checkError("substring('foobar',3,3) == 'bar'",
               "<string>:1.20: syntax error, unexpected integer, "
               "expecting a number in a constant string");
}

// Tests some type error cases (caught only by the strongly typed parser)
TEST_F(EvalContextTest, typeErrors) {
    checkTyped("'foobar'",
               "<string>:1.9: syntax error, unexpected end of file, "
               "expecting ==");
    checkTyped("substring('foobar','a','1') == 'foo'",
               "<string>:1.20-22: syntax error, unexpected constant string, "
               "expecting a number in a constant string");
    checkTyped("substring('foobar','1','a') == 'foo'",
               "<string>:1.24-26: syntax error, unexpected constant string, "
               "expecting a number in a constant string or the all constant "
               "string");
    checkTyped("substring('foobar',0x32,'1') == 'foo'",
               "<string>:1.20-23: syntax error, unexpected constant "
               "hexstring, expecting a number in a constant string");
}

};
