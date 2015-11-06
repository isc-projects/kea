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

    EXPECT_NO_THROW(parsed_ = eval.parseString("'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(1, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenString(tmp, "foo");
}

// Test the parsing of a hexstring terminal
TEST_F(EvalContextTest, hexstring) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ = eval.parseString("0x666f6f"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(1, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenHexString(tmp, "foo");
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

    EXPECT_NO_THROW(parsed_ = eval.parseString("option[123]"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(1, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 123);
}

// Test the parsing of a substring expression
TEST_F(EvalContextTest, substring) {
    EvalContext eval;

    EXPECT_NO_THROW(parsed_ = eval.parseString("substring('foobar','2','3')"));
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
    checkError("option[65536]", "<string>:1.8-12: Option code has invalid "
                                "value in 65536. Allowed range: 0..65535");
    checkError("subtring", "<string>:1.1: Invalid character: s");
    checkError("foo", "<string>:1.1: Invalid character: f");
    checkError(" bar", "<string>:1.2: Invalid character: b");
}

// Tests some scanner/parser error cases
TEST_F(EvalContextTest, scanParseErrors) {
    checkError("", "<string>:1.1: syntax error, unexpected end of file, "
                   "expecting option or substring or constant string or "
                   "constant hexstring");
    checkError("0x", "<string>:1.1: syntax error, unexpected option code, "
                     "expecting option or substring or constant string or "
                     "constant hexstring");
    checkError("===", "<string>:1.1-2: syntax error, unexpected ==, "
                      "expecting option or substring or constant string "
                      "or constant hexstring");
}

// Tests some parser error cases
TEST_F(EvalContextTest, parseErrors) {
    checkError("'foo''bar'", "<string>:1.6-10: syntax error, unexpected "
                             "constant string, expecting end of file");
    checkError("== 'ab'", "<string>:1.1-2: syntax error, unexpected ==, "
                          "expecting option or substring or constant string "
                          "or constant hexstring");
    checkError("'foo' ==", "<string>:1.9: syntax error, unexpected end "
                           "of file, expecting option or substring or "
                           "constant string or constant hexstring");
    checkError("option 'ab'", "<string>:1.8-11: syntax error, unexpected "
                              "constant string, expecting [");
    checkError("option(10) == 'ab'", "<string>:1.7: syntax error, "
                                     "unexpected (, expecting [");
    checkError("option['ab'] == 'foo'", "<string>:1.8-11: syntax error, "
                                        "unexpected constant string, "
                                        "expecting option code");
    checkError("option[0xa] == 'ab'", "<string>:1.8-10: syntax error, "
                                      "unexpected constant hexstring, "
                                      "expecting option code");
    checkError("substring('foobar') == 'f'", "<string>:1.19: syntax error, "
                                             "unexpected ), expecting \",\"");
    checkError("substring('foobar','3') == 'bar'",
               "<string>:1.23: syntax error, unexpected ), expecting \",\"");
    checkError("substring('foobar',3,3) == 'bar'",
               "<string>:1.20: syntax error, unexpected option code, "
               "expecting option or substring or constant string or "
               "constant hexstring");
}

};
