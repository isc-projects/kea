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
#include <dhcp/option.h>
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
    /// @brief constructor to initialize members
    EvalContextTest() : ::testing::Test(),
    universe_(Option::V4), parsed_(false)
    { }

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
        EvalContext eval(universe_);
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

    /// @brief sets the universe
    /// @note the default universe is DHCPv4
    void setUniverse(const Option::Universe& universe) {
        universe_ = universe;
    }

    Option::Universe universe_;
    bool parsed_; ///< Parsing status
};

// Test the parsing of a basic expression
TEST_F(EvalContextTest, basic) {

    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("option[123].text == 'MSFT'"));
    EXPECT_TRUE(parsed_);
}

// Test the parsing of a string terminal
TEST_F(EvalContextTest, string) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("'foo' == 'bar'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp1  = eval.expression.at(0);
    TokenPtr tmp2  = eval.expression.at(1);

    checkTokenString(tmp1, "foo");
    checkTokenString(tmp2, "bar");
}

// Test the parsing of a basic expression using integers
TEST_F(EvalContextTest, integer) {

    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ =
        eval.parseString("substring(option[123].text, 0, 2) == '42'"));
    EXPECT_TRUE(parsed_);
}

// Test the parsing of a hexstring terminal
TEST_F(EvalContextTest, hexstring) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("0x666f6f == 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenHexString(tmp, "foo");
}

// Test the parsing of a hexstring terminal with an odd number of
// hexadecimal digits
TEST_F(EvalContextTest, oddHexstring) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("0X7 == 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenHexString(tmp, "\a");
}

// Test the parsing of an equal expression
TEST_F(EvalContextTest, equal) {
    EvalContext eval(Option::V4);

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
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("option[123].text == 'foo'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 123);
}

// Test parsing of an option identified by name.
TEST_F(EvalContextTest, optionWithName) {
    EvalContext eval(Option::V4);

    // Option 'host-name' is a standard DHCPv4 option defined in the libdhcp++.
    EXPECT_NO_THROW(parsed_ = eval.parseString("option[host-name].text == 'foo'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 12);
}

// Test checking that whitespace can surround option name.
TEST_F(EvalContextTest, optionWithNameAndWhitespace) {
    EvalContext eval(Option::V4);

    // Option 'host-name' is a standard DHCPv4 option defined in the libdhcp++.
    EXPECT_NO_THROW(parsed_ = eval.parseString("option[  host-name  ].text == 'foo'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 12);
}

// Test checking that newlines can surround option name.
TEST_F(EvalContextTest, optionWithNameAndNewline) {
    EvalContext eval(Option::V4);

    // Option 'host-name' is a standard DHCPv4 option defined in the libdhcp++.
    EXPECT_NO_THROW(parsed_ =
        eval.parseString("option[\n host-name \n ].text == \n'foo'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 12);
}

// Test parsing of an option represented as hexadecimal string.
TEST_F(EvalContextTest, optionHex) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("option[123].hex == 0x666F6F"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 123);
}

// Test the parsing of a substring expression
TEST_F(EvalContextTest, substring) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ =
        eval.parseString("substring('foobar',2,all) == 'obar'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(6, eval.expression.size());

    TokenPtr tmp1 = eval.expression.at(0);
    TokenPtr tmp2 = eval.expression.at(1);
    TokenPtr tmp3 = eval.expression.at(2);
    TokenPtr tmp4 = eval.expression.at(3);

    checkTokenString(tmp1, "foobar");
    checkTokenString(tmp2, "2");
    checkTokenString(tmp3, "all");
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
    checkError("foo", "<string>:1.1: Invalid character: f");
    checkError(" bar", "<string>:1.2: Invalid character: b");
}

// Tests some scanner/parser error cases
TEST_F(EvalContextTest, scanParseErrors) {
    checkError("", "<string>:1.1: syntax error, unexpected end of file");
    checkError(" ", "<string>:1.2: syntax error, unexpected end of file");
    checkError("0x", "<string>:1.1: syntax error, unexpected integer");
    checkError("0abc",
               "<string>:1.1: syntax error, unexpected integer");
    checkError("===", "<string>:1.1-2: syntax error, unexpected ==");
    checkError("option[-1].text",
               "<string>:1.8-9: Option code has invalid "
               "value in -1. Allowed range: 0..255");
    checkError("option[256].text",
               "<string>:1.8-10: Option code has invalid "
               "value in 256. Allowed range: 0..255");
    setUniverse(Option::V6);
    checkError("option[65536].text",
               "<string>:1.8-12: Option code has invalid "
               "value in 65536. Allowed range: 0..65535");
    setUniverse(Option::V4);
    checkError("option[12345678901234567890].text",
               "<string>:1.8-27: Failed to convert 12345678901234567890 "
               "to an integer.");
    checkError("option[123]",
               "<string>:1.12: syntax error, unexpected end of file,"
               " expecting .");
    checkError("option[123].text < 'foo'", "<string>:1.18: Invalid"
               " character: <");
    checkError("option[-ab].text", "<string>:1.8: Invalid character: -");
    checkError("option[0ab].text",
               "<string>:1.9-10: syntax error, unexpected option name, "
               "expecting ]");
    checkError("option[ab_].hex", "<string>:1.8: Invalid character: a");
    checkError("option[\nhost-name\n].hex =\n= 'foo'",
               "<string>:3.7: Invalid character: =");
    checkError("substring('foo',12345678901234567890,1)",
               "<string>:1.17-36: Failed to convert 12345678901234567890 "
               "to an integer.");
}

// Tests some parser error cases
TEST_F(EvalContextTest, parseErrors) {
    checkError("'foo''bar'",
               "<string>:1.6-10: syntax error, unexpected constant string, "
               "expecting ==");
    checkError("== 'ab'", "<string>:1.1-2: syntax error, unexpected ==");
    checkError("'foo' ==",
               "<string>:1.9: syntax error, unexpected end of file");
    checkError("('foo' == 'bar'",
               "<string>:1.16: syntax error, unexpected end of file, "
               "expecting )");
    checkError("('foo' == 'bar') ''",
               "<string>:1.18-19: syntax error, unexpected constant string, "
               "expecting end of file");
    checkError("option 'ab'",
               "<string>:1.8-11: syntax error, unexpected "
               "constant string, expecting [");
    checkError("option(10) == 'ab'",
               "<string>:1.7: syntax error, "
               "unexpected (, expecting [");
    checkError("option['ab'].text == 'foo'",
               "<string>:1.8-11: syntax error, "
               "unexpected constant string, "
               "expecting integer or option name");
    checkError("option[ab].text == 'foo'",
               "<string>:1.8-9: option 'ab' is not defined");
    checkError("option[0xa].text == 'ab'",
               "<string>:1.8-10: syntax error, "
               "unexpected constant hexstring, "
               "expecting integer or option name");
    checkError("option[10].bin", "<string>:1.12: Invalid character: b");
    checkError("option[boot-size].bin", "<string>:1.19: Invalid character: b");
    checkError("substring('foobar') == 'f'",
               "<string>:1.19: syntax error, "
               "unexpected ), expecting \",\"");
    checkError("substring('foobar',3) == 'bar'",
               "<string>:1.21: syntax error, unexpected ), expecting \",\"");
    checkError("substring('foobar','3',3) == 'bar'",
               "<string>:1.20-22: syntax error, unexpected constant string, "
               "expecting integer");
    checkError("substring('foobar',1,a) == 'foo'",
               "<string>:1.22: Invalid character: a");
}

// Tests some type error cases (caught only by the strongly typed parser)
TEST_F(EvalContextTest, typeErrors) {
    checkError("'foobar'",
               "<string>:1.9: syntax error, unexpected end of file, "
               "expecting ==");
    checkError("substring('foobar',all,1) == 'foo'",
               "<string>:1.20-22: syntax error, unexpected all, "
               "expecting integer");
    checkError("substring('foobar',0x32,1) == 'foo'",
               "<string>:1.20-23: syntax error, unexpected constant "
               "hexstring, expecting integer");
    checkError("('foo' == 'bar') == 'false'",
               "<string>:1.18-19: syntax error, unexpected ==, "
               "expecting end of file");
}

};
