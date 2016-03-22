// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    /// and representation type
    /// @param token token to be checked
    /// @param expected_code expected option code
    /// @param expected_repr expected representation (text, hex, exists)
    void checkTokenOption(const TokenPtr& token,
                          uint16_t expected_code,
                          TokenOption::RepresentationType expected_repr) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenOption> opt =
            boost::dynamic_pointer_cast<TokenOption>(token);
        ASSERT_TRUE(opt);

        EXPECT_EQ(expected_code, opt->getCode());
        EXPECT_EQ(expected_repr, opt->getRepresentation());
    }

    /// @brief check if the given token is relay4 with the expected code
    /// and representation type
    /// @param token token to be checked
    /// @param expected_code expected option code
    /// @param expected_repr expected representation (text, hex, exists)
    void checkTokenRelay4(const TokenPtr& token,
                          uint16_t expected_code,
                          TokenOption::RepresentationType expected_repr) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenRelay4Option> relay4 =
            boost::dynamic_pointer_cast<TokenRelay4Option>(token);
        EXPECT_TRUE(relay4);

        if (relay4) {
            EXPECT_EQ(expected_code, relay4->getCode());
            EXPECT_EQ(expected_repr, relay4->getRepresentation());
        }
    }

    /// @brief checks if the given token is a substring operator
    void checkTokenSubstring(const TokenPtr& token) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenSubstring> sub =
            boost::dynamic_pointer_cast<TokenSubstring>(token);
        EXPECT_TRUE(sub);
    }

    /// @brief checks if the given token is a concat operator
    void checkTokenConcat(const TokenPtr& token) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenConcat> conc =
            boost::dynamic_pointer_cast<TokenConcat>(token);
        EXPECT_TRUE(conc);
    }

    /// @brief checks if the given token is Pkt6 of specified type
    /// @param token token to be checked
    /// @param type expected type of the Pkt6 field
    void checkTokenPkt6(const TokenPtr& token, TokenPkt6::FieldType type) {
        ASSERT_TRUE(token);

        boost::shared_ptr<TokenPkt6> pkt =
            boost::dynamic_pointer_cast<TokenPkt6>(token);

        ASSERT_TRUE(pkt);

        EXPECT_EQ(type, pkt->getType());
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

    /// @brief Test that verifies access to the DHCPv6 packet fields.
    ///
    /// This test attempts to parse the expression, will check if the number
    /// of tokens is exactly as planned and then will try to verify if the
    /// first token represents expected the field in DHCPv6 packet.
    ///
    /// @param expr expression to be parsed
    /// @param exp_type expected field type to be parsed
    /// @param exp_tokens expected number of tokens
    void testPkt6Field(std::string expr, TokenPkt6::FieldType exp_type,
                       int exp_tokens) {
        EvalContext eval(Option::V6);

        // Parse the expression.
        try {
            parsed_ = eval.parseString(expr);
        }
        catch (const EvalParseError& ex) {
            FAIL() << "Exception thrown: " << ex.what();
            return;
        }

        // Parsing should succeed and return a token.
        EXPECT_TRUE(parsed_);

        // There should be the requested number of tokens
        ASSERT_EQ(exp_tokens, eval.expression.size());

        // Check that the first token is TokenPkt6 instance and has correct type.
        checkTokenPkt6(eval.expression.at(0), exp_type);
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
    checkTokenOption(eval.expression.at(0), 123, TokenOption::TEXTUAL);
}

// Test parsing of an option identified by name.
TEST_F(EvalContextTest, optionWithName) {
    EvalContext eval(Option::V4);

    // Option 'host-name' is a standard DHCPv4 option defined in the libdhcp++.
    EXPECT_NO_THROW(parsed_ = eval.parseString("option[host-name].text == 'foo'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 12, TokenOption::TEXTUAL);
}

// Test parsing of an option existence
TEST_F(EvalContextTest, optionExists) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("option[100].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(1, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 100, TokenOption::EXISTS);
}

// Test checking that whitespace can surround option name.
TEST_F(EvalContextTest, optionWithNameAndWhitespace) {
    EvalContext eval(Option::V4);

    // Option 'host-name' is a standard DHCPv4 option defined in the libdhcp++.
    EXPECT_NO_THROW(parsed_ = eval.parseString("option[  host-name  ].text == 'foo'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 12, TokenOption::TEXTUAL);
}

// Test checking that newlines can surround option name.
TEST_F(EvalContextTest, optionWithNameAndNewline) {
    EvalContext eval(Option::V4);

    // Option 'host-name' is a standard DHCPv4 option defined in the libdhcp++.
    EXPECT_NO_THROW(parsed_ =
        eval.parseString("option[\n host-name \n ].text == \n'foo'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 12, TokenOption::TEXTUAL);
}

// Test parsing of an option represented as hexadecimal string.
TEST_F(EvalContextTest, optionHex) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("option[123].hex == 0x666F6F"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());
    checkTokenOption(eval.expression.at(0), 123, TokenOption::HEXADECIMAL);
}

// This test checks that the relay4[code].hex can be used in expressions.
TEST_F(EvalContextTest, relay4Option) {

    EvalContext eval(Option::V4);
    EXPECT_NO_THROW(parsed_ =
                    eval.parseString("relay4[13].hex == 'thirteen'"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp1 = eval.expression.at(0);
    TokenPtr tmp2 = eval.expression.at(1);
    TokenPtr tmp3 = eval.expression.at(2);

    checkTokenRelay4(tmp1, 13, TokenOption::HEXADECIMAL);
    checkTokenString(tmp2, "thirteen");
    checkTokenEq(tmp3);
}

// This test check the relay4[code].exists is supported.
TEST_F(EvalContextTest, relay4Exists) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ = eval.parseString("relay4[13].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(1, eval.expression.size());
    checkTokenRelay4(eval.expression.at(0), 13, TokenOption::EXISTS);
}

// Verify that relay4[13] is not usable in v6
// There will be a separate relay accessor for v6.
TEST_F(EvalContextTest, relay4Error) {
    universe_ = Option::V6;

    checkError("relay4[13].hex == 'thirteen'",
               "<string>:1.1-6: relay4 can only be used in DHCPv4.");
}

// Tests whether message type field in DHCPv6 can be accessed.
TEST_F(EvalContextTest, pkt6FieldMsgtype) {
    testPkt6Field("pkt6.msgtype == '1'", TokenPkt6::MSGTYPE, 3);
}

// Tests whether transaction id field in DHCPv6 can be accessed.
TEST_F(EvalContextTest, pkt6FieldTransid) {
    testPkt6Field("pkt6.transid == '1'", TokenPkt6::TRANSID, 3);
}

// Test parsing of logical operators
TEST_F(EvalContextTest, logicalOps) {
    // option.exists
    EvalContext eval0(Option::V4);
    EXPECT_NO_THROW(parsed_ = eval0.parseString("option[123].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(1, eval0.expression.size());
    TokenPtr token = eval0.expression.at(0);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenOption> opt =
        boost::dynamic_pointer_cast<TokenOption>(token);
    EXPECT_TRUE(opt);

    // not
    EvalContext evaln(Option::V4);
    EXPECT_NO_THROW(parsed_ = evaln.parseString("not option[123].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(2, evaln.expression.size());
    token = evaln.expression.at(1);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenNot> tnot =
        boost::dynamic_pointer_cast<TokenNot>(token);
    EXPECT_TRUE(tnot);

    // and
    EvalContext evala(Option::V4);
    EXPECT_NO_THROW(parsed_ =
        evala.parseString("option[123].exists and option[123].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, evala.expression.size());
    token = evala.expression.at(2);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenAnd> tand =
        boost::dynamic_pointer_cast<TokenAnd>(token);
    EXPECT_TRUE(tand);

    // or
    EvalContext evalo(Option::V4);
    EXPECT_NO_THROW(parsed_ =
        evalo.parseString("option[123].exists or option[123].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(3, evalo.expression.size());
    token = evalo.expression.at(2);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenOr> tor =
        boost::dynamic_pointer_cast<TokenOr>(token);
    EXPECT_TRUE(tor);
}

// Test parsing of logical operators with precedence
TEST_F(EvalContextTest, logicalPrecedence) {
    // not precedence > and precedence
    EvalContext evalna(Option::V4);
    EXPECT_NO_THROW(parsed_ =
        evalna.parseString("not option[123].exists and option[123].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(4, evalna.expression.size());
    TokenPtr token = evalna.expression.at(3);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenAnd> tand =
        boost::dynamic_pointer_cast<TokenAnd>(token);
    EXPECT_TRUE(tand);

    // and precedence > or precedence
    EvalContext evaloa(Option::V4);
    EXPECT_NO_THROW(parsed_ =
        evaloa.parseString("option[123].exists or option[123].exists "
                         "and option[123].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(5, evaloa.expression.size());
    token = evaloa.expression.at(4);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenOr> tor =
        boost::dynamic_pointer_cast<TokenOr>(token);
    EXPECT_TRUE(tor);
}

// Test parsing of logical operators with parentheses (same than
// with precedence but using parentheses to overwrite precedence)
TEST_F(EvalContextTest, logicalParentheses) {
    // not precedence > and precedence
    EvalContext evalna(Option::V4);
    EXPECT_NO_THROW(parsed_ =
        evalna.parseString("not (option[123].exists and option[123].exists)"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(4, evalna.expression.size());
    TokenPtr token = evalna.expression.at(3);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenNot> tnot =
        boost::dynamic_pointer_cast<TokenNot>(token);
    EXPECT_TRUE(tnot);

    // and precedence > or precedence
    EvalContext evaloa(Option::V4);
    EXPECT_NO_THROW(parsed_ =
        evaloa.parseString("(option[123].exists or option[123].exists) "
                         "and option[123].exists"));
    EXPECT_TRUE(parsed_);
    ASSERT_EQ(5, evaloa.expression.size());
    token = evaloa.expression.at(4);
    ASSERT_TRUE(token);
    boost::shared_ptr<TokenAnd> tand =
        boost::dynamic_pointer_cast<TokenAnd>(token);
    EXPECT_TRUE(tand);
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

// Test the parsing of a concat expression
TEST_F(EvalContextTest, concat) {
    EvalContext eval(Option::V4);

    EXPECT_NO_THROW(parsed_ =
        eval.parseString("concat('foo','bar') == 'foobar'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(5, eval.expression.size());

    TokenPtr tmp1 = eval.expression.at(0);
    TokenPtr tmp2 = eval.expression.at(1);
    TokenPtr tmp3 = eval.expression.at(2);

    checkTokenString(tmp1, "foo");
    checkTokenString(tmp2, "bar");
    checkTokenConcat(tmp3);
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
    checkError("relay[12].hex == 'foo'", "<string>:1.1: Invalid character: r");
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
    checkError("'foo' (",
               "<string>:1.7: syntax error, unexpected (, expecting ==");
    checkError("== 'ab'", "<string>:1.1-2: syntax error, unexpected ==");
    checkError("'foo' ==",
               "<string>:1.9: syntax error, unexpected end of file");
    checkError("('foo' == 'bar'",
               "<string>:1.16: syntax error, unexpected end of file, "
               "expecting ) or and or or");
    checkError("('foo' == 'bar') ''",
               "<string>:1.18-19: syntax error, unexpected constant string, "
               "expecting end of file");
    checkError("not",
               "<string>:1.4: syntax error, unexpected end of file");
    checkError("not 'foo'",
               "<string>:1.10: syntax error, unexpected end of file, "
               "expecting ==");
    checkError("not()",
               "<string>:1.5: syntax error, unexpected )");
    checkError("(not('foo' 'bar')",
               "<string>:1.12-16: syntax error, unexpected constant string, "
               "expecting ==");
    checkError("and",
               "<string>:1.1-3: syntax error, unexpected and");
    checkError("'foo' and",
               "<string>:1.7-9: syntax error, unexpected and, expecting ==");
    checkError("'foo' == 'bar' and",
               "<string>:1.19: syntax error, unexpected end of file");
    checkError("'foo' == 'bar' and ''",
               "<string>:1.22: syntax error, unexpected end of file, "
               "expecting ==");
    checkError("or",
               "<string>:1.1-2: syntax error, unexpected or");
    checkError("'foo' or",
               "<string>:1.7-8: syntax error, unexpected or, expecting ==");
    checkError("'foo' == 'bar' or",
               "<string>:1.18: syntax error, unexpected end of file");
    checkError("'foo' == 'bar' or ''",
               "<string>:1.21: syntax error, unexpected end of file, "
               "expecting ==");
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
    checkError("option[10].exists == 'foo'",
               "<string>:1.19-20: syntax error, unexpected ==, "
               "expecting end of file");
    checkError("substring('foobar') == 'f'",
               "<string>:1.19: syntax error, unexpected ), expecting \",\"");
    checkError("substring('foobar',3) == 'bar'",
               "<string>:1.21: syntax error, unexpected ), expecting \",\"");
    checkError("substring('foobar','3',3) == 'bar'",
               "<string>:1.20-22: syntax error, unexpected constant string, "
               "expecting integer");
    checkError("substring('foobar',1,a) == 'foo'",
               "<string>:1.22: Invalid character: a");
    checkError("concat('foobar') == 'f'",
               "<string>:1.16: syntax error, unexpected ), expecting \",\"");
    checkError("concat('foo','bar','') == 'foobar'",
               "<string>:1.19: syntax error, unexpected \",\", expecting )");
}

// Tests some type error cases
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
    checkError("concat('foo',3) == 'foo3'",
               "<string>:1.14: syntax error, unexpected integer");
    checkError("concat(3,'foo') == '3foo'",
               "<string>:1.8: syntax error, unexpected integer");
    checkError("('foo' == 'bar') == 'false'",
               "<string>:1.18-19: syntax error, unexpected ==, "
               "expecting end of file");
    checkError("not 'true'",
               "<string>:1.11: syntax error, unexpected end of file, "
               "expecting ==");
    checkError("'true' and 'false'",
               "<string>:1.8-10: syntax error, unexpected and, expecting ==");
    checkError("'true' or 'false'",
               "<string>:1.8-9: syntax error, unexpected or, expecting ==");
}

};
