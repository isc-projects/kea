// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <asiolink/io_address.h>
#include <eval/evaluate.h>
#include <gtest/gtest.h>
#include <sstream>
#include <stdint.h>
#include <string>

/// @file client_class_def_parser_unittest.cc Unit tests for client class
/// definition parsing.

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

/// @brief Test fixture class for @c ExpressionParser.
class ExpressionParserTest : public ::testing::Test {
protected:

    /// @brief Test that validate expression can be evaluated against v4 or
    /// v6 packet.
    ///
    /// Verifies that given a valid expression, the ExpressionParser
    /// produces an Expression which can be evaluated against a v4 or v6
    /// packet.
    ///
    /// @param family AF_INET or AF_INET6
    /// @param expression Textual representation of the expression to be
    /// evaluated.
    /// @param option_string String data to be placed in the hostname
    /// option, being placed in the packet used for evaluation.
    /// @tparam Type of the packet: @c Pkt4 or @c Pkt6.
    template<typename PktType>
    void testValidExpression(uint16_t family,
                             const std::string& expression,
                             const std::string& option_string) {
        ExpressionPtr parsed_expr;
        ExpressionParser parser;

        // Turn config into elements.  This may emit exceptions.
        ElementPtr config_element = Element::fromJSON(expression);

        // Expression should parse.
        ASSERT_NO_THROW(parser.parse(parsed_expr, config_element, family));

        // Parsed expression should exist.
        ASSERT_TRUE(parsed_expr);

        // Build a packet that will fail evaluation.
        uint8_t message_type;
        if (family == AF_INET) {
            message_type = DHCPDISCOVER;
        } else {
            message_type = DHCPV6_SOLICIT;
        }
        boost::shared_ptr<PktType> pkt(new PktType(message_type, 123));
        EXPECT_FALSE(evaluateBool(*parsed_expr, *pkt));

        // Now add the option so it will pass. Use a standard option carrying a
        // single string value, i.e. hostname for DHCPv4 and bootfile url for
        // DHCPv6.
        Option::Universe universe(family == AF_INET ? Option::V4 : Option::V6);
        uint16_t option_type;
        if (family == AF_INET) {
            option_type = DHO_HOST_NAME;
        } else {
            option_type = D6O_BOOTFILE_URL;
        }
        OptionPtr opt(new OptionString(universe, option_type, option_string));
        pkt->addOption(opt);
        EXPECT_TRUE(evaluateBool(*parsed_expr, *pkt));
    }
};

/// @brief Test fixture class for @c ClientClassDefParser.
class ClientClassDefParserTest : public ::testing::Test {
protected:

    /// @brief Convenience method for parsing a configuration
    ///
    /// Attempt to parse a given client class definition.
    ///
    /// @param config - JSON string containing the client class configuration
    /// to parse.
    /// @param family - the address family in which the parsing should
    /// occur.
    /// @return Returns a pointer to class instance created, or NULL if
    /// for some unforeseen reason it wasn't created in the local dictionary
    /// @throw indirectly, exceptions convertring the JSON text to elements,
    /// or by the parsing itself are not caught
    ClientClassDefPtr parseClientClassDef(const std::string& config,
                                          uint16_t family) {
        // Create local dictionary to which the parser add the class.
        ClientClassDictionaryPtr dictionary(new ClientClassDictionary());

        // Turn config into elements.  This may emit exceptions.
        ElementPtr config_element = Element::fromJSON(config);

        // Parse the configuration. This may emit exceptions.
        ClientClassDefParser parser;
        parser.parse(dictionary, config_element, family);

        // If we didn't throw, then return the first and only class
        ClientClassDefListPtr classes = dictionary->getClasses();
        ClientClassDefList::const_iterator it = classes->cbegin();
        if (it != classes->cend()) {
            return (*it);
        }

        // Return NULL if for some reason the class doesn't exist.
        return (ClientClassDefPtr());
    }

    /// @brief Test that client class parser throws when unspported parameter
    /// is specfied.
    ///
    /// @param config JSON string containing the client class configuration.
    /// @param family The address family indicating whether the DHCPv4 or
    /// DHCPv6 client class is parsed.
    void testClassParamsUnsupported(const std::string& config,
                                    const uint16_t family) {
        ElementPtr config_element = Element::fromJSON(config);

        ClientClassDefParser parser;
        EXPECT_THROW(parser.checkParametersSupported(config_element, family),
                     DhcpConfigError);
    }
};

/// @brief Test fixture class for @c ClientClassDefListParser.
class ClientClassDefListParserTest : public ::testing::Test {
protected:

    /// @brief Convenience method for parsing a list of client class
    /// definitions.
    ///
    /// Attempt to parse a given list of client class definitions into a
    /// ClientClassDictionary.
    ///
    /// @param config - JSON string containing the list of definitions to parse.
    /// @param family - the address family in which the parsing should
    /// occur.
    /// @return Returns a pointer to class dictionary created
    /// @throw indirectly, execptions convertring the JSON text to elements,
    /// or by the parsing itself are not caught
    ClientClassDictionaryPtr parseClientClassDefList(const std::string& config,
                                                     uint16_t family)
    {
        // Turn config into elements.  This may emit exceptions.
        ElementPtr config_element = Element::fromJSON(config);

        // Parse the configuration. This may emit exceptions.
        ClientClassDefListParser parser;
        return (parser.parse(config_element, family));
    }
};

// Verifies that given a valid expression, the ExpressionParser
// produces an Expression which can be evaluated against a v4 packet.
TEST_F(ExpressionParserTest, validExpression4) {
    testValidExpression<Pkt4>(AF_INET,
                              "\"option[12].text == 'hundred4'\"",
                              "hundred4");
}

// Verifies that the option name can be used in the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionName4) {
    testValidExpression<Pkt4>(AF_INET,
                              "\"option[host-name].text == 'hundred4'\"",
                              "hundred4");
}

// Verifies that given a valid expression using .hex operator for option, the
// ExpressionParser produces an Expression which can be evaluated against
// a v4 packet.
TEST_F(ExpressionParserTest, validExpressionWithHex4) {
    testValidExpression<Pkt4>(AF_INET,
                              "\"option[12].hex == 0x68756E6472656434\"",
                              "hundred4");
}

// Verifies that the option name can be used together with .hex operator in
// the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionNameAndHex4) {
    testValidExpression<Pkt6>(AF_INET,
                              "\"option[host-name].text == 0x68756E6472656434\"",
                              "hundred4");
}

// Verifies that given a valid expression, the ExpressionParser
// produces an Expression which can be evaluated against a v6 packet.
TEST_F(ExpressionParserTest, validExpression6) {
    testValidExpression<Pkt6>(AF_INET6,
                              "\"option[59].text == 'hundred6'\"",
                              "hundred6");
}

// Verifies that the option name can be used in the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionName6) {
    testValidExpression<Pkt6>(AF_INET6,
                              "\"option[bootfile-url].text == 'hundred6'\"",
                              "hundred6");
}

// Verifies that given a valid expression using .hex operator for option, the
// ExpressionParser produces an Expression which can be evaluated against
// a v6 packet.
TEST_F(ExpressionParserTest, validExpressionWithHex6) {
    testValidExpression<Pkt6>(AF_INET6,
                              "\"option[59].hex == 0x68756E6472656436\"",
                              "hundred6");
}

// Verifies that the option name can be used together with .hex operator in
// the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionNameAndHex6) {
    testValidExpression<Pkt6>(AF_INET6,
                              "\"option[bootfile-url].text == 0x68756E6472656436\"",
                              "hundred6");
}

// Verifies that an the ExpressionParser only accepts StringElements.
TEST_F(ExpressionParserTest, invalidExpressionElement) {
    // This will create an integer element should fail.
    std::string cfg_txt = "777";
    ElementPtr config_element = Element::fromJSON(cfg_txt);

    // Create the parser.
    ExpressionPtr parsed_expr;
    ExpressionParser parser;

    // Expression parsing should fail.
    ASSERT_THROW(parser.parse(parsed_expr, config_element, AF_INET6),
                 DhcpConfigError);
}

// Verifies that given an invalid expression with a syntax error,
// the Expression parser will throw a DhdpConfigError.  Note this
// is not intended to be an exhaustive test or expression syntax.
// It is simply to ensure that if the parser fails, it does so
// Properly.
TEST_F(ExpressionParserTest, expressionSyntaxError) {
    // Turn config into elements.
    std::string cfg_txt = "\"option 'bogus'\"";
    ElementPtr config_element = Element::fromJSON(cfg_txt);

    // Create the parser.
    ExpressionPtr parsed_expr;
    ExpressionParser parser;

    // Expression parsing should fail.
    ASSERT_THROW(parser.parse(parsed_expr, config_element, AF_INET),
                 DhcpConfigError);
}

// Verifies that the name parameter is required and must not be empty
TEST_F(ExpressionParserTest, nameEmpty) {
    std::string cfg_txt = "{ \"name\": \"\" }";
    ElementPtr config_element = Element::fromJSON(cfg_txt);

    // Create the parser.
    ExpressionPtr parsed_expr;
    ExpressionParser parser;

    // Expression parsing should fail.
    ASSERT_THROW(parser.parse(parsed_expr, config_element, AF_INET6),
                 DhcpConfigError);
}

// Verifies that the function checking if specified client class parameters
// are supported does not throw if all specified DHCPv4 client class
// parameters are recognized.
TEST_F(ClientClassDefParserTest, checkAllSupported4) {
    std::string cfg_text =
        "{\n"
        "    \"name\": \"foo\","
        "    \"test\": \"member('ALL')\","
        "    \"option-def\": [ ],\n"
        "    \"option-data\": [ ],\n"
        "    \"user-context\": { },\n"
        "    \"only-if-required\": false,\n"
        "    \"next-server\": \"192.0.2.3\",\n"
        "    \"server-hostname\": \"myhost\",\n"
        "    \"boot-file-name\": \"efi\""
        "}\n";

    ElementPtr config_element = Element::fromJSON(cfg_text);

    ClientClassDefParser parser;
    EXPECT_NO_THROW(parser.checkParametersSupported(config_element, AF_INET));
}

// Verifies that the function checking if specified client class parameters
// are supported does not throw if all specified DHCPv6 client class
// parameters are recognized.
TEST_F(ClientClassDefParserTest, checkAllSupported6) {
    std::string cfg_text =
        "{\n"
        "    \"name\": \"foo\","
        "    \"test\": \"member('ALL')\","
        "    \"option-data\": [ ],\n"
        "    \"user-context\": { },\n"
        "    \"only-if-required\": false\n"
        "}\n";

    ElementPtr config_element = Element::fromJSON(cfg_text);

    ClientClassDefParser parser;
    EXPECT_NO_THROW(parser.checkParametersSupported(config_element, AF_INET6));
}

// Verifies that the function checking if specified client class parameters
// are supported throws if DHCPv4 specific parameters are specified for the
// DHCPv6 client class.
TEST_F(ClientClassDefParserTest, checkParams4Unsupported6) {
    std::string cfg_text;

    {
        SCOPED_TRACE("option-def");
        cfg_text =
            "{\n"
            "    \"name\": \"foo\","
            "    \"test\": \"member('ALL')\","
            "    \"option-def\": [ ],\n"
            "    \"option-data\": [ ],\n"
            "    \"user-context\": { },\n"
            "    \"only-if-required\": false\n"
            "}\n";

        testClassParamsUnsupported(cfg_text, AF_INET6);
    }

    {
        SCOPED_TRACE("next-server");
        cfg_text =
            "{\n"
            "    \"name\": \"foo\","
            "    \"test\": \"member('ALL')\","
            "    \"option-data\": [ ],\n"
            "    \"user-context\": { },\n"
            "    \"only-if-required\": false,\n"
            "    \"next-server\": \"192.0.2.3\"\n"
            "}\n";

        testClassParamsUnsupported(cfg_text, AF_INET6);
    }

    {
        SCOPED_TRACE("server-hostname");
        cfg_text =
            "{\n"
            "    \"name\": \"foo\","
            "    \"test\": \"member('ALL')\","
            "    \"option-data\": [ ],\n"
            "    \"user-context\": { },\n"
            "    \"only-if-required\": false,\n"
            "    \"server-hostname\": \"myhost\"\n"
            "}\n";

        testClassParamsUnsupported(cfg_text, AF_INET6);
    }

    {
        SCOPED_TRACE("boot-file-name");
        cfg_text =
            "{\n"
            "    \"name\": \"foo\","
            "    \"test\": \"member('ALL')\","
            "    \"option-data\": [ ],\n"
            "    \"user-context\": { },\n"
            "    \"only-if-required\": false,\n"
            "    \"boot-file-name\": \"efi\""
            "}\n";

        testClassParamsUnsupported(cfg_text, AF_INET6);
    }
}

// Verifies that the function checking if specified DHCPv4 client class
// parameters are supported throws if one of the parameters is not recognized.
TEST_F(ClientClassDefParserTest, checkParams4Unsupported) {
    std::string cfg_text =
        "{\n"
        "    \"name\": \"foo\","
        "    \"unsupported\": \"member('ALL')\""
        "}\n";

    testClassParamsUnsupported(cfg_text, AF_INET);
}

// Verifies that the function checking if specified DHCPv6 client class
// parameters are supported throws if one of the parameters is not recognized.
TEST_F(ClientClassDefParserTest, checkParams6Unsupported) {
    std::string cfg_text =
        "{\n"
        "    \"name\": \"foo\","
        "    \"unsupported\": \"member('ALL')\""
        "}\n";

    testClassParamsUnsupported(cfg_text, AF_INET6);
}

// Verifies you can create a class with only a name
// Whether that's useful or not, remains to be seen.
// For now the class allows it.
TEST_F(ClientClassDefParserTest, nameOnlyValid) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\" \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);
    EXPECT_EQ("MICROSOFT", cclass->getName());

    // CfgOption should be a non-null pointer but there
    // should be no options.  Currently there's no good
    // way to test that there no options.
    CfgOptionPtr cfg_option;
    cfg_option = cclass->getCfgOption();
    ASSERT_TRUE(cfg_option);
    OptionContainerPtr oc;
    ASSERT_TRUE(oc = cclass->getCfgOption()->getAll(DHCP4_OPTION_SPACE));
    EXPECT_EQ(0, oc->size());

    // Verify we have no expression.
    ASSERT_FALSE(cclass->getMatchExpr());
}

// Verifies you can create a class with a name, expression,
// but no options.
// @todo same with AF_INET6
TEST_F(ClientClassDefParserTest, nameAndExpressionClass) {

    std::string test = "option[100].text == 'works right'";
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"class_one\", \n"
        "    \"test\": \"" + test + "\" \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);
    EXPECT_EQ("class_one", cclass->getName());

    // CfgOption should be a non-null pointer but there
    // should be no options.  Currently there's no good
    // way to test that there no options.
    CfgOptionPtr cfg_option;
    cfg_option = cclass->getCfgOption();
    ASSERT_TRUE(cfg_option);
    OptionContainerPtr oc;
    ASSERT_TRUE(oc = cclass->getCfgOption()->getAll(DHCP4_OPTION_SPACE));
    EXPECT_EQ(0, oc->size());

    // Verify we can retrieve the expression
    ExpressionPtr match_expr = cclass->getMatchExpr();
    ASSERT_TRUE(match_expr);

    // Verify the original expression was saved.
    EXPECT_EQ(test, cclass->getTest());

    // Build a packet that will fail evaluation.
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 123));
    EXPECT_FALSE(evaluateBool(*match_expr, *pkt4));

    // Now add the option so it will pass.
    OptionPtr opt(new OptionString(Option::V4, 100, "works right"));
    pkt4->addOption(opt);
    EXPECT_TRUE(evaluateBool(*match_expr, *pkt4));
}

// Verifies you can create a class with a name and options,
// but no expression.
// @todo same with AF_INET6
TEST_F(ClientClassDefParserTest, nameAndOptionsClass) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"code\": 6, \n"
        "           \"space\": \"dhcp4\", \n"
        "           \"csv-format\": true, \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);
    EXPECT_EQ("MICROSOFT", cclass->getName());

    // Our one option should exist.
    OptionDescriptor od = cclass->getCfgOption()->get(DHCP4_OPTION_SPACE, 6);
    ASSERT_TRUE(od.option_);
    EXPECT_EQ(6, od.option_->getType());

    // Verify we have no expression
    ASSERT_FALSE(cclass->getMatchExpr());
}


// Verifies you can create a class with a name, expression,
// and options.
// @todo same with AF_INET6
TEST_F(ClientClassDefParserTest, basicValidClass) {

    std::string test = "option[100].text == 'booya'";
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"test\": \"" + test + "\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"code\": 6, \n"
        "           \"space\": \"dhcp4\", \n"
        "           \"csv-format\": true, \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);
    EXPECT_EQ("MICROSOFT", cclass->getName());

    // Our one option should exist.
    OptionDescriptor od = cclass->getCfgOption()->get(DHCP4_OPTION_SPACE, 6);
    ASSERT_TRUE(od.option_);
    EXPECT_EQ(6, od.option_->getType());

    // Verify we can retrieve the expression
    ExpressionPtr match_expr = cclass->getMatchExpr();
    ASSERT_TRUE(match_expr);

    // Verify the original expression was saved.
    EXPECT_EQ(test, cclass->getTest());

    // Build a packet that will fail evaluation.
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 123));
    EXPECT_FALSE(evaluateBool(*match_expr, *pkt4));

    // Now add the option so it will pass.
    OptionPtr opt(new OptionString(Option::V4, 100, "booya"));
    pkt4->addOption(opt);
    EXPECT_TRUE(evaluateBool(*match_expr, *pkt4));
}

// Verifies that a class with no name, fails to parse.
TEST_F(ClientClassDefParserTest, noClassName) {

    std::string cfg_text =
        "{ \n"
        "    \"test\": \"option[123].text == 'abc'\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"code\": 6, \n"
        "           \"space\": \"dhcp4\", \n"
        "           \"csv-format\": true, \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, AF_INET),
                 DhcpConfigError);
}

// Verifies that a class with a blank name, fails to parse.
TEST_F(ClientClassDefParserTest, blankClassName) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"\", \n"
        "    \"test\": \"option[123].text == 'abc'\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"code\": 6, \n"
        "           \"space\": \"dhcp4\", \n"
        "           \"csv-format\": true, \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, AF_INET),
                 DhcpConfigError);
}

// Verifies that a class with an invalid expression, fails to parse.
TEST_F(ClientClassDefParserTest, invalidExpression) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"one\", \n"
        "    \"test\": 777 \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, AF_INET6),
                 DhcpConfigError);
}

// Verifies that a class with invalid option-def, fails to parse.
TEST_F(ClientClassDefParserTest, invalidOptionDef) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"one\", \n"
        "    \"option-def\": [ \n"
        "      { \"bogus\": \"bad\" } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, AF_INET),
                 DhcpConfigError);
}

// Verifies that a class with invalid option-data, fails to parse.
TEST_F(ClientClassDefParserTest, invalidOptionData) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"one\", \n"
        "    \"option-data\": [ \n"
        "      { \"bogus\": \"bad\" } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, AF_INET),
                 DhcpConfigError);
}


// Verifies that a valid list of client classes will parse.
TEST_F(ClientClassDefListParserTest, simpleValidList) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"one\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"two\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"three\" \n"
        "   } \n"
        "] \n";

    // Parsing the list should succeed.
    ClientClassDictionaryPtr dictionary;
    ASSERT_NO_THROW(dictionary = parseClientClassDefList(cfg_text, AF_INET6));
    ASSERT_TRUE(dictionary);

    // We should have three classes in the dictionary.
    EXPECT_EQ(3, dictionary->getClasses()->size());

    // Make sure we can find all three.
    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = dictionary->findClass("one"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("one", cclass->getName());

    ASSERT_NO_THROW(cclass = dictionary->findClass("two"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("two", cclass->getName());

    ASSERT_NO_THROW(cclass = dictionary->findClass("three"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("three", cclass->getName());

    // For good measure, make sure we can't find a non-existent class.
    ASSERT_NO_THROW(cclass = dictionary->findClass("bogus"));
    EXPECT_FALSE(cclass);
}

// Verifies that class list containing a duplicate class entries, fails
// to parse.
TEST_F(ClientClassDefListParserTest, duplicateClass) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"one\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"two\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"two\" \n"
        "   } \n"
        "] \n";

    ClientClassDictionaryPtr dictionary;
    ASSERT_THROW(dictionary = parseClientClassDefList(cfg_text, AF_INET),
                 DhcpConfigError);
}

// Test verifies that without any class specified, the fixed fields have their
// default, empty value.
// @todo same with AF_INET6
TEST_F(ClientClassDefParserTest, noFixedFields) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);

    // And it should not have any fixed fields set
    EXPECT_EQ(IOAddress("0.0.0.0"), cclass->getNextServer());
    EXPECT_EQ(0, cclass->getSname().size());
    EXPECT_EQ(0, cclass->getFilename().size());

    // Nor option definitions
    CfgOptionDefPtr cfg = cclass->getCfgOptionDef();
    ASSERT_TRUE(cfg->getAll(DHCP4_OPTION_SPACE)->empty());
}

// Test verifies option-def for a bad option fails to parse.
TEST_F(ClientClassDefParserTest, badOptionDef) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"option-def\": [ \n"
        "        { \n"
        "           \"name\": \"foo\", \n"
        "           \"code\": 222, \n"
        "           \"type\": \"uint32\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, AF_INET),
                 DhcpConfigError);
}

// Test verifies option-def works for private options (224-254).
TEST_F(ClientClassDefParserTest, privateOptionDef) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"option-def\": [ \n"
        "        { \n"
        "           \"name\": \"foo\", \n"
        "           \"code\": 232, \n"
        "           \"type\": \"uint32\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);

    // And the option definition.
    CfgOptionDefPtr cfg = cclass->getCfgOptionDef();
    ASSERT_TRUE(cfg);
    EXPECT_TRUE(cfg->get(DHCP4_OPTION_SPACE, 232));
    EXPECT_FALSE(cfg->get(DHCP6_OPTION_SPACE, 232));
    EXPECT_FALSE(cfg->get(DHCP4_OPTION_SPACE, 233));
}

// Test verifies option-def works for option 43.
TEST_F(ClientClassDefParserTest, option43Def) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"test\": \"option[60].text == 'MICROSOFT'\", \n"
        "    \"option-def\": [ \n"
        "        { \n"
        "           \"name\": \"vendor-encapsulated-options\", \n"
        "           \"code\": 43, \n"
        "           \"space\": \"dhcp4\", \n"
        "           \"type\": \"empty\", \n"
        "           \"encapsulate\": \"vsi\" \n"
        "        } \n"
        "      ], \n"
        "    \"option-data\": [ \n"
        "      { \n"
        "         \"name\": \"vendor-encapsulated-options\" \n"
        "      }, \n"
        "      { \n"
        "         \"code\": 1, \n"
        "         \"space\": \"vsi\", \n"
        "         \"csv-format\": false, \n"
        "         \"data\": \"C0000200\" \n"
        "      } \n"
        "    ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);

    // And the option definition.
    CfgOptionDefPtr cfg_def = cclass->getCfgOptionDef();
    ASSERT_TRUE(cfg_def);
    EXPECT_TRUE(cfg_def->get(DHCP4_OPTION_SPACE, 43));

    // Verify the option data.
    OptionDescriptor od = cclass->getCfgOption()->get(DHCP4_OPTION_SPACE, 43);
    ASSERT_TRUE(od.option_);
    EXPECT_EQ(43, od.option_->getType());
    const OptionCollection& oc = od.option_->getOptions();
    ASSERT_EQ(1, oc.size());
    OptionPtr opt = od.option_->getOption(1);
    ASSERT_TRUE(opt);
    EXPECT_EQ(1, opt->getType());
    ASSERT_EQ(4, opt->getData().size());
    const uint8_t expected[4] = { 0xc0, 0x00, 0x02, 0x00 };
    EXPECT_EQ(0, std::memcmp(expected, &opt->getData()[0], 4));
}


// Test verifies that it is possible to define next-server field and it
// is actually set in the class properly.
TEST_F(ClientClassDefParserTest, nextServer) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"next-server\": \"192.0.2.254\",\n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);

    // And it should have next-server set, but everything else not set.
    EXPECT_EQ(IOAddress("192.0.2.254"), cclass->getNextServer());
    EXPECT_EQ(0, cclass->getSname().size());
    EXPECT_EQ(0, cclass->getFilename().size());
}

// Test verifies that the parser rejects bogus next-server value.
TEST_F(ClientClassDefParserTest, nextServerBogus) {

    std::string bogus_v6 =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"next-server\": \"2001:db8::1\",\n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";
    std::string bogus_junk =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"next-server\": \"not-an-address\",\n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";
    std::string bogus_broadcast =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"next-server\": \"255.255.255.255\",\n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    EXPECT_THROW(parseClientClassDef(bogus_v6, AF_INET), DhcpConfigError);
    EXPECT_THROW(parseClientClassDef(bogus_junk, AF_INET), DhcpConfigError);
    EXPECT_THROW(parseClientClassDef(bogus_broadcast, AF_INET), DhcpConfigError);
}

// Test verifies that it is possible to define server-hostname field and it
// is actually set in the class properly.
TEST_F(ClientClassDefParserTest, serverName) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"server-hostname\": \"hal9000\",\n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);

    // And it should not have any fixed fields set
    std::string exp_sname("hal9000");

    EXPECT_EQ(exp_sname, cclass->getSname());
}

// Test verifies that the parser rejects bogus server-hostname value.
TEST_F(ClientClassDefParserTest, serverNameInvalid) {

    std::string cfg_too_long =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"server-hostname\": \"1234567890123456789012345678901234567890"
                                   "1234567890123456789012345\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    EXPECT_THROW(parseClientClassDef(cfg_too_long, AF_INET), DhcpConfigError);
}


// Test verifies that it is possible to define boot-file-name field and it
// is actually set in the class properly.
TEST_F(ClientClassDefParserTest, filename) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"boot-file-name\": \"ipxe.efi\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, AF_INET));

    // We should find our class.
    ASSERT_TRUE(cclass);

    // And it should not have any fixed fields set
    std::string exp_filename("ipxe.efi");
    EXPECT_EQ(exp_filename, cclass->getFilename());
}

// Test verifies that the parser rejects bogus boot-file-name value.
TEST_F(ClientClassDefParserTest, filenameBogus) {

    // boot-file-name is allowed up to 128 bytes, this one is 129.
    std::string cfg_too_long =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"boot-file-name\": \"1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "1234567890123456789012345678901234567890"
                                  "123456789\", \n"
        "    \"option-data\": [ \n"
        "        { \n"
        "           \"name\": \"domain-name-servers\", \n"
        "           \"data\": \"192.0.2.1, 192.0.2.2\" \n"
        "        } \n"
        "      ] \n"
        "} \n";

    EXPECT_THROW(parseClientClassDef(cfg_too_long, AF_INET), DhcpConfigError);
}

// Verifies that backward and built-in dependencies will parse.
TEST_F(ClientClassDefListParserTest, dependentList) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"one\", \n"
        "       \"test\": \"member('VENDOR_CLASS_foo')\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"two\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"three\", \n"
        "       \"test\": \"member('two')\" \n"
        "   } \n"
        "] \n";

    // Parsing the list should succeed.
    ClientClassDictionaryPtr dictionary;
    ASSERT_NO_THROW(dictionary = parseClientClassDefList(cfg_text, AF_INET));
    ASSERT_TRUE(dictionary);

    // We should have three classes in the dictionary.
    EXPECT_EQ(3, dictionary->getClasses()->size());

    // Make sure we can find all three.
    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = dictionary->findClass("one"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("one", cclass->getName());

    ASSERT_NO_THROW(cclass = dictionary->findClass("two"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("two", cclass->getName());

    ASSERT_NO_THROW(cclass = dictionary->findClass("three"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("three", cclass->getName());
}

// Verifies that not defined dependencies will not parse.
TEST_F(ClientClassDefListParserTest, dependentNotDefined) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"one\", \n"
        "       \"test\": \"member('foo')\" \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET6), DhcpConfigError);
}

// Verifies that forward dependencies will not parse.
TEST_F(ClientClassDefListParserTest, dependentForwardError) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"one\", \n"
        "       \"test\": \"member('foo')\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"foo\" \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET6), DhcpConfigError);
}

// Verifies that backward dependencies will parse.
TEST_F(ClientClassDefListParserTest, dependentBackward) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"foo\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"one\", \n"
        "       \"test\": \"member('foo')\" \n"
        "   } \n"
        "] \n";

    EXPECT_NO_THROW(parseClientClassDefList(cfg_text, AF_INET6));
}

// Verifies that the depend on known flag is correctly handled.
TEST_F(ClientClassDefListParserTest, dependOnKnown) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"alpha\", \n"
        "       \"test\": \"member('ALL')\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"beta\", \n"
        "       \"test\": \"member('alpha')\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"gamma\", \n"
        "       \"test\": \"member('KNOWN') and member('alpha')\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"delta\", \n"
        "       \"test\": \"member('beta') and member('gamma')\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"zeta\", \n"
        "       \"test\": \"not member('UNKNOWN') and member('alpha')\" \n"
        "   } \n"
        "] \n";

    // Parsing the list should succeed.
    ClientClassDictionaryPtr dictionary;
    EXPECT_NO_THROW(dictionary = parseClientClassDefList(cfg_text, AF_INET6));
    ASSERT_TRUE(dictionary);

    // We should have five classes in the dictionary.
    EXPECT_EQ(5, dictionary->getClasses()->size());

    // Check alpha.
    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = dictionary->findClass("alpha"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("alpha", cclass->getName());
    EXPECT_FALSE(cclass->getDependOnKnown());

    // Check beta.
    ASSERT_NO_THROW(cclass = dictionary->findClass("beta"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("beta", cclass->getName());
    EXPECT_FALSE(cclass->getDependOnKnown());

    // Check gamma which directly depends on KNOWN.
    ASSERT_NO_THROW(cclass = dictionary->findClass("gamma"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("gamma", cclass->getName());
    EXPECT_TRUE(cclass->getDependOnKnown());

    // Check delta which indirectly depends on KNOWN.
    ASSERT_NO_THROW(cclass = dictionary->findClass("delta"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("delta", cclass->getName());
    EXPECT_TRUE(cclass->getDependOnKnown());

    // Check that zeta which directly depends on UNKNOWN.
    // (and yes I know that I skipped epsilon)
    ASSERT_NO_THROW(cclass = dictionary->findClass("zeta"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("zeta", cclass->getName());
    EXPECT_TRUE(cclass->getDependOnKnown());
}

// Verifies that a built-in class can't be required or evaluated.
TEST_F(ClientClassDefListParserTest, builtinCheckError) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"ALL\" \n"
        "   } \n"
        "] \n";

    EXPECT_NO_THROW(parseClientClassDefList(cfg_text, AF_INET6));

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"ALL\", \n"
        "       \"only-if-required\": true \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET), DhcpConfigError);

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"ALL\", \n"
        "       \"test\": \"'aa' == 'aa'\" \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET6), DhcpConfigError);

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"KNOWN\", \n"
        "       \"only-if-required\": true \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET), DhcpConfigError);

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"KNOWN\", \n"
        "       \"test\": \"'aa' == 'aa'\" \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET6), DhcpConfigError);

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"UNKNOWN\", \n"
        "       \"only-if-required\": true \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET), DhcpConfigError);

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"UNKNOWN\", \n"
        "       \"test\": \"'aa' == 'aa'\" \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET6), DhcpConfigError);
}

// Verifies that the special DROP class can't be required or
// dependent on KNOWN/UNKNOWN
TEST_F(ClientClassDefListParserTest, dropCheckError) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"DROP\", \n"
        "       \"test\": \"option[123].text == 'abc'\" \n"
        "   } \n"
        "] \n";

    EXPECT_NO_THROW(parseClientClassDefList(cfg_text, AF_INET6));

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"DROP\", \n"
        "       \"only-if-required\": true \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET), DhcpConfigError);

    cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"DROP\", \n"
        "       \"test\": \"member('KNOWN')\" \n"
        "   } \n"
        "] \n";

    EXPECT_THROW(parseClientClassDefList(cfg_text, AF_INET6), DhcpConfigError);
}

} // end of anonymous namespace
