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
#include <asiolink/io_address.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::asiolink;
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

    /// @brief checks if the given token is an IP address with the expected value
    void checkTokenIpAddress(const TokenPtr& token,
                             const std::string& expected) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenIpAddress> ipaddr =
            boost::dynamic_pointer_cast<TokenIpAddress>(token);
        ASSERT_TRUE(ipaddr);

        Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
        ValueStack values;

        EXPECT_NO_THROW(token->evaluate(*pkt4, values));

        ASSERT_EQ(1, values.size());
        string value = values.top();

        boost::scoped_ptr<IOAddress> exp_ip;
        ASSERT_NO_THROW(exp_ip.reset(new IOAddress(expected)));
        vector<uint8_t> exp_addr = exp_ip->toBytes();
        ASSERT_EQ(exp_addr.size(), value.size());
        EXPECT_EQ(0, memcmp(&exp_addr[0], &value[0], value.size()));
    }

    /// @brief checks if the given token is an equal operator
    void checkTokenEq(const TokenPtr& token) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenEqual> eq =
            boost::dynamic_pointer_cast<TokenEqual>(token);
        EXPECT_TRUE(eq);
    }

    /// @brief Checks if the given token is integer with expected value
    ///
    /// @param token token to be inspected
    /// @param exp_value expected integer value of the token
    void checkTokenInteger(const TokenPtr& token, uint32_t exp_value) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenInteger> integer =
            boost::dynamic_pointer_cast<TokenInteger>(token);
        ASSERT_TRUE(integer);
        EXPECT_EQ(exp_value, integer->getInteger());
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

    /// @brief checks if the given token is a TokenRelay6Option with
    /// the correct nesting level, option code and representation.
    /// @param token token to be checked
    /// @param expected_level expected nesting level
    /// @param expected_code expected option code
    /// @param expected_repr expected representation (text, hex, exists)
    void checkTokenRelay6Option(const TokenPtr& token,
                                uint8_t expected_level,
                                uint16_t expected_code,
                                TokenOption::RepresentationType expected_repr) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenRelay6Option> opt =
            boost::dynamic_pointer_cast<TokenRelay6Option>(token);
        ASSERT_TRUE(opt);

        EXPECT_EQ(expected_level, opt->getNest());
        EXPECT_EQ(expected_code, opt->getCode());
        EXPECT_EQ(expected_repr, opt->getRepresentation());
    }

    /// @brief This tests attempts to parse the expression then checks
    /// if the number of tokens is correct and the TokenRelay6Option
    /// is as expected.
    ///
    /// @param expr expression to be parsed
    /// @param exp_level expected level to be parsed
    /// @param exp_code expected option code to be parsed
    /// @param exp_repr expected representation to be parsed
    /// @param exp_tokens expected number of tokens
    void testRelay6Option(const std::string& expr,
                         uint8_t exp_level,
                         uint16_t exp_code,
                         TokenOption::RepresentationType exp_repr,
                         int exp_tokens) {
        EvalContext eval(Option::V6);

        // parse the expression
        try {
            parsed_ = eval.parseString(expr);
        }
        catch (const EvalParseError& ex) {
            FAIL() <<"Exception thrown: " << ex.what();
            return;
        }

        // Parsing should succeed and return a token.
        EXPECT_TRUE(parsed_);

        // There should be the expected number of tokens.
        ASSERT_EQ(exp_tokens, eval.expression.size());

        // checked that the first token is TokenRelay6Option and that
        // is has the correct attributes
        checkTokenRelay6Option(eval.expression.at(0), exp_level, exp_code, exp_repr);
    }

    /// @brief check if the given token is a Pkt of specified type
    /// @param token token to be checked
    /// @param type expected type of the Pkt metadata
    void checkTokenPkt(const TokenPtr& token, TokenPkt::MetadataType type) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenPkt> pkt =
            boost::dynamic_pointer_cast<TokenPkt>(token);
        ASSERT_TRUE(pkt);

        EXPECT_EQ(type, pkt->getType());
    }

    /// @brief Test that verifies access to the DHCP packet metadata.
    ///
    /// This test attempts to parse the expression, will check if the number
    /// of tokens is exactly as expected and then will try to verify if the
    /// first token represents the expected metadata in DHCP packet.
    ///
    /// @param expr expression to be parsed
    /// @param exp_type expected metadata type to be parsed
    /// @param exp_tokens expected number of tokens
    void testPktMetadata(const std::string& expr,
                         TokenPkt::MetadataType exp_type,
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

        // There should be exactly the expected number of tokens.
        ASSERT_EQ(exp_tokens, eval.expression.size());

        // Check that the first token is TokenPkt instance and has correct type.
        checkTokenPkt(eval.expression.at(0), exp_type);
    }

    /// @brief checks if the given token is Pkt4 of specified type
    /// @param token token to be checked
    /// @param type expected type of the Pkt4 field
    void checkTokenPkt4(const TokenPtr& token, TokenPkt4::FieldType type) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenPkt4> pkt =
            boost::dynamic_pointer_cast<TokenPkt4>(token);
        ASSERT_TRUE(pkt);

        EXPECT_EQ(type, pkt->getType());
    }

    /// @brief Test that verifies access to the DHCPv4 packet fields.
    ///
    /// This test attempts to parse the expression, will check if the number
    /// of tokens is exactly as expected and then will try to verify if the
    /// first token represents the expected field in DHCPv4 packet.
    ///
    /// @param expr expression to be parsed
    /// @param exp_type expected field type to be parsed
    /// @param exp_tokens expected number of tokens
    void testPkt4Field(const std::string& expr,
                       TokenPkt4::FieldType exp_type,
                       int exp_tokens) {
        EvalContext eval(Option::V4);

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

        // There should be exactly the expected number of tokens.
        ASSERT_EQ(exp_tokens, eval.expression.size());

        // Check that the first token is TokenPkt4 instance and has correct type.
        checkTokenPkt4(eval.expression.at(0), exp_type);
    }

    /// @brief checks if the given token is Pkt6 of specified type
    /// @param token token to be checked
    /// @param exp_type expected type of the Pkt6 field
    void checkTokenPkt6(const TokenPtr& token,
                        TokenPkt6::FieldType exp_type) {
        ASSERT_TRUE(token);

        boost::shared_ptr<TokenPkt6> pkt =
            boost::dynamic_pointer_cast<TokenPkt6>(token);

        ASSERT_TRUE(pkt);

        EXPECT_EQ(exp_type, pkt->getType());
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
    void testPkt6Field(const std::string& expr,
                       TokenPkt6::FieldType exp_type,
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

    /// @brief checks if the given token is a TokenRelay with the
    /// correct nesting level and field type.
    /// @param token token to be checked
    /// @param expected_level expected nesting level
    /// @param expected_code expected option code
    /// @param expected_repr expected representation (text, hex, exists)
    void checkTokenRelay6Field(const TokenPtr& token,
                               uint8_t expected_level,
                               TokenRelay6Field::FieldType expected_type) {
        ASSERT_TRUE(token);
        boost::shared_ptr<TokenRelay6Field> opt =
            boost::dynamic_pointer_cast<TokenRelay6Field>(token);
        ASSERT_TRUE(opt);

        EXPECT_EQ(expected_level, opt->getNest());
        EXPECT_EQ(expected_type, opt->getType());
    }

    /// @brief This tests attempts to parse the expression then checks
    /// if the number of tokens is correct and the TokenRelay6Field is as
    /// expected.
    ///
    /// @param expr expression to be parsed
    /// @param exp_level expected level to be parsed
    /// @param exp_type expected field type to be parsed
    /// @param exp_tokens expected number of tokens
    void testRelay6Field(const std::string& expr,
                         uint8_t exp_level,
                         TokenRelay6Field::FieldType exp_type,
                         int exp_tokens) {
        EvalContext eval(Option::V6);

        // parse the expression
        try {
            parsed_ = eval.parseString(expr);
        }
        catch (const EvalParseError& ex) {
            FAIL() <<"Exception thrown: " << ex.what();
            return;
        }

        // Parsing should succeed and return a token.
        EXPECT_TRUE(parsed_);

        // There should be the expected number of tokens.
        ASSERT_EQ(exp_tokens, eval.expression.size());

        // checked that the first token is TokenRelay6Field and that
        // is has the correct attributes
        checkTokenRelay6Field(eval.expression.at(0), exp_level, exp_type);
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

    /// @brief Checks if the given token is TokenVendor and has expected characteristics
    /// @param token token to be checked
    /// @param exp_vendor_id expected vendor-id (aka enterprise number)
    /// @param exp_repr expected representation (either 'exists' or 'hex')
    /// @param exp_option_code expected option code (ignored if 0)
    void checkTokenVendor(const TokenPtr& token, uint32_t exp_vendor_id,
                          uint16_t exp_option_code,
                          TokenOption::RepresentationType exp_repr) {
        ASSERT_TRUE(token);

        boost::shared_ptr<TokenVendor> vendor =
            boost::dynamic_pointer_cast<TokenVendor>(token);

        ASSERT_TRUE(vendor);

        EXPECT_EQ(exp_vendor_id, vendor->getVendorId());
        EXPECT_EQ(exp_repr, vendor->getRepresentation());
        EXPECT_EQ(exp_option_code, vendor->getCode());
    }

    /// @brief Tests if specified token vendor expression can be parsed
    ///
    /// This test assumes the first token will be token vendor. Any additional
    /// tokens are ignored. Tests expressions:
    /// vendor[1234].option[234].hex
    /// vendor[1234].option[234].exists
    ///
    /// @param expr expression to be parsed
    /// @param u universe (V4 or V6)
    /// @param vendor_id expected vendor-id (aka enterprise number)
    /// @param option_code expected option code (ignored if 0)
    /// @param expected_repr expected representation (either 'exists' or 'hex')
    void testVendor(const std::string& expr, Option::Universe u,
                    uint32_t vendor_id, uint16_t option_code,
                    TokenOption::RepresentationType expected_repr) {
        EvalContext eval(u);

        EXPECT_NO_THROW(parsed_ = eval.parseString(expr));
        EXPECT_TRUE(parsed_);

        // We need at least one token, we will evaluate the first one.
        ASSERT_FALSE(eval.expression.empty());

        checkTokenVendor(eval.expression.at(0), vendor_id, option_code, expected_repr);
    }

    /// @brief Checks if token is really a TokenVendor, that the vendor_id was
    /// stored properly and that it has expected representation
    ///
    /// This test is able to handle expressions similar to:
    /// vendor[4491].option[1].hex
    /// vendor[4491].option[1].exists
    /// vendor[4491].exists
    /// vendor[*].exists
    ///
    /// @param expr expression to be parsed
    /// @param u universe (V4 or V6)
    /// @param vendor_id expected vendor-id (aka enterprise number)
    /// @param expected_repr expected representation (either 'exists' or 'hex')
    void testVendor(const std::string& expr, Option::Universe u,
                    uint32_t vendor_id,
                    TokenOption::RepresentationType expected_repr) {
        testVendor(expr, u, vendor_id, 0, expected_repr);
    }

    /// @brief Tests if the expression parses into token vendor that returns enterprise-id
    ///
    /// This test is able to handle expressions similar to:
    /// vendor.enterprise
    ///
    /// @param expr expression to be parsed
    /// @param u universe (V4 or V6)
    void testVendorEnterprise(const std::string& expr,
                              Option::Universe u) {
        EvalContext eval(u);

        EXPECT_NO_THROW(parsed_ = eval.parseString(expr));
        EXPECT_TRUE(parsed_);

        ASSERT_FALSE(eval.expression.empty());

        boost::shared_ptr<TokenVendor> vendor =
            boost::dynamic_pointer_cast<TokenVendor>(eval.expression.at(0));

        ASSERT_TRUE(vendor);
        EXPECT_EQ(TokenVendor::ENTERPRISE_ID, vendor->getField());
    }

    /// @brief This test checks if vendor-class token is correct
    ///
    /// This test checks if EXISTS representation is set correctly.
    /// It covers cases like:
    /// - vendor-class[4491].exists
    /// - vendor-class[*].exists
    ///
    /// @param expr expression to be parsed
    /// @param u universe (V4 or V6)
    /// @param vendor_id expected vendor-id (aka enterprise number)
    void testVendorClass(const std::string& expr,
                         Option::Universe u, uint32_t vendor_id) {
        EvalContext eval(u);

        EXPECT_NO_THROW(parsed_ = eval.parseString(expr));
        EXPECT_TRUE(parsed_);

        ASSERT_EQ(1, eval.expression.size());
        checkTokenVendorClass(eval.expression.at(0), vendor_id, 0, TokenOption::EXISTS,
                              TokenVendor::EXISTS);
    }

    /// @brief Tests if specified token vendor class expression can be parsed
    ///
    /// This test assumes the first token will be token vendor-class.
    /// Any additional tokens are ignored. Tests expressions:
    /// - vendor-class[4491].exists
    /// - vendor-class[*].exists
    /// - vendor-class[4491].data
    /// - vendor-class[4491].data[3]
    ///
    /// @param expr expression to be parsed
    /// @param u universe (V4 or V6)
    /// @param vendor_id expected vendor-id (aka enterprise number)
    /// @param index expected data index
    void testVendorClass(const std::string& expr, Option::Universe u,
                         uint32_t vendor_id, uint16_t index) {
        EvalContext eval(u);

        EXPECT_NO_THROW(parsed_ = eval.parseString(expr));
        EXPECT_TRUE(parsed_);

        // Make sure there's at least one token
        ASSERT_FALSE(eval.expression.empty());

        // The first token should be TokenVendorClass, let's take a closer look.
        checkTokenVendorClass(eval.expression.at(0), vendor_id, index,
                              TokenOption::HEXADECIMAL, TokenVendor::DATA);

    }

    /// @brief Tests if the expression parses into vendor class token that
    ///        returns enterprise-id.
    ///
    /// This test is able to handle expressions similar to:
    /// - vendor-class.enterprise
    ///
    /// @param expr expression to be parsed
    /// @param u universe (V4 or V6)
    void testVendorClassEnterprise(const std::string& expr,
                                   Option::Universe u) {
        EvalContext eval(u);

        EXPECT_NO_THROW(parsed_ = eval.parseString(expr));
        EXPECT_TRUE(parsed_);

        // Make sure there's at least one token
        ASSERT_FALSE(eval.expression.empty());

        // The first token should be TokenVendorClass, let's take a closer look.
        checkTokenVendorClass(eval.expression.at(0), 0, 0, TokenOption::HEXADECIMAL,
                              TokenVendor::ENTERPRISE_ID);
    }

    /// @brief Checks if the given token is TokenVendorClass and has expected characteristics
    ///
    /// @param token token to be checked
    /// @param vendor_id expected vendor-id (aka enterprise number)
    /// @param index expected index (used for data field only)
    /// @param repr expected representation (either 'exists' or 'hex')
    /// @param field expected field (none, enterprise or data)
    void checkTokenVendorClass(const TokenPtr& token, uint32_t vendor_id,
                               uint16_t index, TokenOption::RepresentationType repr,
                               TokenVendor::FieldType field) {
        ASSERT_TRUE(token);

        boost::shared_ptr<TokenVendorClass> vendor =
            boost::dynamic_pointer_cast<TokenVendorClass>(token);

        ASSERT_TRUE(vendor);

        EXPECT_EQ(vendor_id, vendor->getVendorId());
        EXPECT_EQ(index, vendor->getDataIndex());
        EXPECT_EQ(repr, vendor->getRepresentation());
        EXPECT_EQ(field, vendor->getField());
    }

    Option::Universe universe_; ///< Universe (V4 or V6)
    bool parsed_; ///< Parsing status

};

// Test the error method without location
TEST_F(EvalContextTest, error) {

    EvalContext eval(Option::V4);

    EXPECT_THROW(eval.error("an error"), EvalParseError);
}

// Test the fatal method
TEST_F(EvalContextTest, fatal) {

    EvalContext eval(Option::V4);

    EXPECT_THROW(eval.fatal("a fatal error"), isc::Unexpected);
}

// Test the convertOptionCode method with an illegal input
TEST_F(EvalContextTest, badOptionCode) {

    EvalContext eval(Option::V4);

    // the option code must be a number
    EXPECT_THROW(eval.convertOptionCode("bad", location(position())),
                 EvalParseError);
}

// Test the convertNestLevelNumber method with an illegal input
TEST_F(EvalContextTest, badNestLevelNumber) {

    EvalContext eval(Option::V4);

    // the nest level number must be a number
    EXPECT_THROW(eval.convertNestLevelNumber("bad", location(position())),
                 EvalParseError);
}

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

// Test the parsing of an IPv4 address
TEST_F(EvalContextTest, ipaddress4) {
    EvalContext eval(Option::V6);

    EXPECT_NO_THROW(parsed_ = eval.parseString("10.0.0.1 == 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenIpAddress(tmp, "10.0.0.1");
}

// Test the parsing of an IPv6 address
TEST_F(EvalContextTest, ipaddress6) {
    EvalContext eval(Option::V6);

    EXPECT_NO_THROW(parsed_ = eval.parseString("2001:db8::1 == 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenIpAddress(tmp, "2001:db8::1");
}

// Test the parsing of an IPv4 compatible IPv6 address
TEST_F(EvalContextTest, ipaddress46) {
    EvalContext eval(Option::V6);

    EXPECT_NO_THROW(parsed_ = eval.parseString("::10.0.0.1 == 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenIpAddress(tmp, "::10.0.0.1");
}

// Test the parsing of the unspecified IPv6 address
TEST_F(EvalContextTest, ipaddress6unspec) {
    EvalContext eval(Option::V6);

    EXPECT_NO_THROW(parsed_ = eval.parseString(":: == 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenIpAddress(tmp, "::");
}

// Test the parsing of an IPv6 prefix
TEST_F(EvalContextTest, ipaddress6prefix) {
    EvalContext eval(Option::V6);

    EXPECT_NO_THROW(parsed_ = eval.parseString("2001:db8:: == 'foo'"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);

    checkTokenIpAddress(tmp, "2001:db8::");
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

// Test the parsing of a relay6 option
TEST_F(EvalContextTest, relay6Option) {
    EvalContext eval(Option::V6);

    testRelay6Option("relay6[0].option[123].text == 'foo'",
                     0, 123, TokenOption::TEXTUAL, 3);
}

// Test the parsing of existence for a relay6 option
TEST_F(EvalContextTest, relay6OptionExists) {
    EvalContext eval(Option::V6);

    testRelay6Option("relay6[1].option[75].exists",
                     1, 75, TokenOption::EXISTS, 1);
}

// Test the parsing of hex for a relay6 option
TEST_F(EvalContextTest, relay6OptionHex) {
    EvalContext eval(Option::V6);

    testRelay6Option("relay6[2].option[85].hex == 'foo'",
                     2, 85, TokenOption::HEXADECIMAL, 3);
}

// Test the nest level of a relay6 option should be in [0..32[
TEST_F(EvalContextTest, relay6OptionLimits) {
    EvalContext eval(Option::V6);

    // max nest level is hop count limit minus one so 31
    testRelay6Option("relay6[31].option[123].text == 'foo'",
                     31, 123, TokenOption::TEXTUAL, 3);

    universe_ = Option::V6;

    checkError("relay6[32].option[123].text == 'foo'",
               "<string>:1.8-9: Nest level has invalid value in 32. "
               "Allowed range: 0..31");

    // next level must be a positive number
    checkError("relay6[-1].option[123].text == 'foo'",
               "<string>:1.8-9: Invalid value in -1. Allowed range: 0..255");
}

// Verify that relay6[13].option is not usable in v4
TEST_F(EvalContextTest, relay6OptionError) {
    universe_ = Option::V4;

    // nest_level is reduced first so raises the error
    // (if we'd like to get a relay6 error we have to insert an
    //  intermediate action to check the universe)
    checkError("relay6[0].option[123].text == 'foo'",
               "<string>:1.8: Nest level invalid for DHCPv4 packets");
}

// Tests whether iface metadata in DHCP can be accessed.
TEST_F(EvalContextTest, pktMetadataIface) {
    testPktMetadata("pkt.iface == 'eth0'", TokenPkt::IFACE, 3);
}

// Tests whether src metadata in DHCP can be accessed.
TEST_F(EvalContextTest, pktMetadataSrc) {
    testPktMetadata("pkt.src == fe80::1", TokenPkt::SRC, 3);
}

// Tests whether dst metadata in DHCP can be accessed.
TEST_F(EvalContextTest, pktMetadataDst) {
    testPktMetadata("pkt.dst == fe80::2", TokenPkt::DST, 3);
}

// Tests whether len metadata in DHCP can be accessed.
TEST_F(EvalContextTest, pktMetadataLen) {
    testPktMetadata("pkt.len == 0x00000100", TokenPkt::LEN, 3);
}

// Tests whether chaddr field in DHCPv4 can be accessed.
TEST_F(EvalContextTest, pkt4FieldChaddr) {
    testPkt4Field("pkt4.mac == 0x000102030405", TokenPkt4::CHADDR, 3);
}

// Tests whether hlen field in DHCPv4 can be accessed.
TEST_F(EvalContextTest, pkt4FieldHlen) {
    testPkt4Field("pkt4.hlen == 0x6", TokenPkt4::HLEN, 3);
}

// Tests whether htype field in DHCPv4 can be accessed.
TEST_F(EvalContextTest, pkt4FieldHtype) {
    testPkt4Field("pkt4.htype == 0x1", TokenPkt4::HTYPE, 3);
}

// Tests whether ciaddr field in DHCPv4 can be accessed.
TEST_F(EvalContextTest, pkt4FieldCiaddr) {
    testPkt4Field("pkt4.ciaddr == 192.0.2.1", TokenPkt4::CIADDR, 3);
}

// Tests whether giaddr field in DHCPv4 can be accessed.
TEST_F(EvalContextTest, pkt4FieldGiaddr) {
    testPkt4Field("pkt4.giaddr == 192.0.2.1", TokenPkt4::GIADDR, 3);
}

// Tests whether yiaddr field in DHCPv4 can be accessed.
TEST_F(EvalContextTest, pkt4FieldYiaddr) {
    testPkt4Field("pkt4.yiaddr == 192.0.2.1", TokenPkt4::YIADDR, 3);
}

// Tests whether siaddr field in DHCPv4 can be accessed.
TEST_F(EvalContextTest, pkt4FieldSiaddr) {
    testPkt4Field("pkt4.siaddr == 192.0.2.1", TokenPkt4::SIADDR, 3);
}

// Tests whether message type field in DHCPv6 can be accessed.
TEST_F(EvalContextTest, pkt6FieldMsgtype) {
    testPkt6Field("pkt6.msgtype == 1", TokenPkt6::MSGTYPE, 3);
}

// Tests whether transaction id field in DHCPv6 can be accessed.
TEST_F(EvalContextTest, pkt6FieldTransid) {
    testPkt6Field("pkt6.transid == 1", TokenPkt6::TRANSID, 3);
}

// Tests if the linkaddr field in a Relay6 encapsulation can be accessed.
TEST_F(EvalContextTest, relay6FieldLinkAddr) {
    testRelay6Field("relay6[0].linkaddr == ::",
                    0, TokenRelay6Field::LINKADDR, 3);
}

// Tests if the peeraddr field in a Relay6 encapsulation can be accessed.
TEST_F(EvalContextTest, relay6FieldPeerAddr) {
    testRelay6Field("relay6[1].peeraddr == ::",
                    1, TokenRelay6Field::PEERADDR, 3);
}

// Verify that relay6[13].<field> is not usable in v4
TEST_F(EvalContextTest, relay6FieldError) {
    universe_ = Option::V4;

    // nest_level is reduced first so raises the error
    // (if we'd like to get a relay6 error we have to insert an
    //  intermediate action to check the universe)
    checkError("relay6[0].linkaddr == ::",
               "<string>:1.8: Nest level invalid for DHCPv4 packets");
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

//
// Test some scanner error cases
TEST_F(EvalContextTest, scanErrors) {
    checkError("'", "<string>:1.1: Invalid character: '");
    checkError("'\''", "<string>:1.3: Invalid character: '");
    checkError("'\n'", "<string>:1.1: Invalid character: '");
    checkError("0x123h", "<string>:1.6: Invalid character: h");
    checkError(":1", "<string>:1.1: Invalid character: :");
    checkError("=", "<string>:1.1: Invalid character: =");
    checkError("subtring", "<string>:1.1: Invalid character: s");
    checkError("foo", "<string>:1.1: Invalid character: f");
    checkError(" bar", "<string>:1.2: Invalid character: b");
    checkError("relay[12].hex == 'foo'", "<string>:1.1: Invalid character: r");
    checkError("pkt4.ziaddr", "<string>:1.6: Invalid character: z");
}

// Tests some scanner/parser error cases
TEST_F(EvalContextTest, scanParseErrors) {
    checkError("", "<string>:1.1: syntax error, unexpected end of file");
    checkError(" ", "<string>:1.2: syntax error, unexpected end of file");
    checkError("0x", "<string>:1.2: Invalid character: x");
    checkError("0abc",
               "<string>:1.2: Invalid character: a");

    // This one is a little bid odd. This is a truncated address, so it's not
    // recognized as an address. Instead, the first token (10) is recognized as
    // an integer. The only thing we can do with integers right now is test
    // for equality, so the only possible next token is ==. There's a dot
    // instead, so an error is reported.
    checkError("10.0.1", "<string>:1.3: syntax error, unexpected ., expecting ==");

    checkError("10.256.0.1",
               "<string>:1.1-10: Failed to convert 10.256.0.1 to "
               "an IP address.");
    checkError(":::",
               "<string>:1.1-3: Failed to convert ::: to an IP address.");
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

    // With the #4483 addition, all integers are treated as 4 byte strings,
    // so those checks no longer makes sense. Commenting it out.
    // checkError("concat('foo',3) == 'foo3'",
    //            "<string>:1.14: syntax error, unexpected integer");
    // checkError("concat(3,'foo') == '3foo'",
    //           "<string>:1.8: syntax error, unexpected integer");
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


TEST_F(EvalContextTest, vendor4SpecificVendorExists) {
    testVendor("vendor[4491].exists", Option::V4, 4491, TokenOption::EXISTS);
}

TEST_F(EvalContextTest, vendor6SpecificVendorExists) {
    testVendor("vendor[4491].exists", Option::V6, 4491, TokenOption::EXISTS);
}

TEST_F(EvalContextTest, vendor4AnyVendorExists) {
    testVendor("vendor[*].exists", Option::V4, 0, TokenOption::EXISTS);
}

TEST_F(EvalContextTest, vendor6AnyVendorExists) {
    testVendor("vendor[*].exists", Option::V6, 0, TokenOption::EXISTS);
}

TEST_F(EvalContextTest, vendor4enterprise) {
    testVendorEnterprise("vendor.enterprise == 0x1234", Option::V4);
}

TEST_F(EvalContextTest, vendor6enterprise) {
    testVendorEnterprise("vendor.enterprise == 0x1234", Option::V6);
}

TEST_F(EvalContextTest, vendor4SuboptionExists) {
    testVendor("vendor[4491].option[1].exists", Option::V4, 4491, 1, TokenOption::EXISTS);
}

TEST_F(EvalContextTest, vendor6SuboptionExists) {
    testVendor("vendor[4491].option[1].exists", Option::V6, 4491, 1, TokenOption::EXISTS);
}

TEST_F(EvalContextTest, vendor4SuboptionHex) {
    testVendor("vendor[4491].option[1].hex == 0x1234", Option::V4, 4491, 1,
               TokenOption::HEXADECIMAL);
}

TEST_F(EvalContextTest, vendor6SuboptionHex) {
    testVendor("vendor[4491].option[1].hex == 0x1234", Option::V6, 4491, 1,
               TokenOption::HEXADECIMAL);
}

TEST_F(EvalContextTest, vendorClass4SpecificVendorExists) {
    testVendorClass("vendor-class[4491].exists", Option::V4, 4491);
}

TEST_F(EvalContextTest, vendorClass6SpecificVendorExists) {
    testVendorClass("vendor-class[4491].exists", Option::V6, 4491);
}

TEST_F(EvalContextTest, vendorClass4AnyVendorExists) {
    testVendorClass("vendor-class[*].exists", Option::V4, 0);
}

TEST_F(EvalContextTest, vendorClass6AnyVendorExists) {
    testVendorClass("vendor-class[*].exists", Option::V6, 0);
}

TEST_F(EvalContextTest, vendorClass4enterprise) {
    testVendorClassEnterprise("vendor-class.enterprise == 0x1234", Option::V4);
}

TEST_F(EvalContextTest, vendorClass6enterprise) {
    testVendorClassEnterprise("vendor-class.enterprise == 0x1234", Option::V6);
}

TEST_F(EvalContextTest, vendorClass4SpecificVendorData) {
    testVendorClass("vendor-class[4491].data == 0x1234", Option::V4, 4491, 0);
}

TEST_F(EvalContextTest, vendorClass6SpecificVendorData) {
    testVendorClass("vendor-class[4491].data == 0x1234", Option::V6, 4491, 0);
}

TEST_F(EvalContextTest, vendorClass4AnyVendorData) {
    testVendorClass("vendor-class[*].data == 0x1234", Option::V4, 0, 0);
}

TEST_F(EvalContextTest, vendorClass6AnyVendorData) {
    testVendorClass("vendor-class[*].data == 0x1234", Option::V6, 0, 0);
}

TEST_F(EvalContextTest, vendorClass4DataIndex) {
    testVendorClass("vendor-class[4491].data[3] == 0x1234", Option::V4, 4491, 3);
}

TEST_F(EvalContextTest, vendorClass6DataIndex) {
    testVendorClass("vendor-class[4491].data[3] == 0x1234", Option::V6, 4491, 3);
}

// Checks if integer expressions can be parsed and checked for equality.
TEST_F(EvalContextTest, integer1) {

    EvalContext eval(Option::V6);

    EXPECT_NO_THROW(parsed_ = eval.parseString("1 == 2"));
    EXPECT_TRUE(parsed_);

    ASSERT_EQ(3, eval.expression.size());

    TokenPtr tmp = eval.expression.at(0);
    ASSERT_TRUE(tmp);
    checkTokenInteger(tmp, 1);
    tmp = eval.expression.at(1);

    ASSERT_TRUE(tmp);
    checkTokenInteger(tmp, 2);
}

};
