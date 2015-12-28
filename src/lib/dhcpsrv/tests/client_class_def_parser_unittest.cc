// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <eval/evaluate.h>
#include <gtest/gtest.h>
#include <sstream>
#include <stdint.h>
#include <string>

/// @file client_class_def_parser_unittest.cc Unit tests for client class
/// definition parsing.

using namespace isc::data;
using namespace isc::dhcp;

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
    /// @param universe V4 or V6.
    /// @param expression Textual representation of the expression to be
    /// evaluated.
    /// @param option_string String data to be placed in the hostname
    /// option, being placed in the packet used for evaluation.
    /// @tparam Type of the packet: @c Pkt4 or @c Pkt6.
    template<typename PktType>
    void testValidExpression(const Option::Universe& universe,
                             const std::string& expression,
                             const std::string& option_string) {
        ParserContextPtr context(new ParserContext(universe));
        ExpressionParserPtr parser;
        ExpressionPtr parsed_expr;

        // Turn config into elements.  This may emit exceptions.
        ElementPtr config_element = Element::fromJSON(expression);

        // Create the parser.
        ASSERT_NO_THROW(parser.reset(new ExpressionParser("", parsed_expr,
                                                      context)));
        // Expression should parse and commit.
        ASSERT_NO_THROW(parser->build(config_element));
        ASSERT_NO_THROW(parser->commit());

        // Parsed expression should exist.
        ASSERT_TRUE(parsed_expr);

        // Build a packet that will fail evaluation.
        boost::shared_ptr<PktType> pkt(new PktType(universe == Option::V4 ?
                                                   DHCPDISCOVER : DHCPV6_SOLICIT,
                                                   123));
        EXPECT_FALSE(evaluate(*parsed_expr, *pkt));

        // Now add the option so it will pass. Use a standard option carrying a
        // single string value, i.e. hostname for DHCPv4 and bootfile url for
        // DHCPv6.
        OptionPtr opt(new OptionString(universe, universe == Option::V4 ?
                                       DHO_HOST_NAME : D6O_BOOTFILE_URL,
                                       option_string));
        pkt->addOption(opt);
        EXPECT_TRUE(evaluate(*parsed_expr, *pkt));
    }
};

/// @brief Test fixture class for @c ClientClassDefParser.
class ClientClassDefParserTest : public ::testing::Test {
protected:

    /// @brief Convenience method for parsing a configuration
    ///
    /// Attempt to parse a given client class defintion.
    ///
    /// @param config - JSON string containing the client class configuration
    /// to parse.
    /// @param universe - the universe in which the parsing context should
    /// occur.
    /// @return Returns a pointer to class instance created, or NULL if
    /// for some unforeseen reason it wasn't created in the local dictionary
    /// @throw indirectly, exceptions convertring the JSON text to elements,
    /// or by the parsing itself are not caught
    ClientClassDefPtr parseClientClassDef(const std::string& config,
                                          Option::Universe universe) {
        // Create local dicitonary to which the parser add the class.
        ClientClassDictionaryPtr dictionary(new ClientClassDictionary());
        // Create the "global" context for the parser.
        ParserContextPtr context(new ParserContext(universe));

        // Turn config into elements.  This may emit exceptions.
        ElementPtr config_element = Element::fromJSON(config);

        // Parse the configuration. This may emit exceptions.
        ClientClassDefParser parser("", dictionary, context);
        parser.build(config_element);

        // If we didn't throw, then return the first and only class
        ClientClassDefMapPtr classes = dictionary->getClasses();
        ClientClassDefMap::iterator it = classes->begin();
        if (it != classes->end()) {
            return  (*it).second;
        }

        // Return NULL if for some reason the class doesn't exist.
        return (ClientClassDefPtr());
    }
};

/// @brief Test fixture class for @c ClientClassDefListParser.
class ClientClassDefListParserTest : public ::testing::Test {
protected:

    /// @brief Convenience method for parsing a list of client class
    /// definitions.
    ///
    /// Attempt to parse a given list of client class defintions into a
    /// ClientClassDictionary.
    ///
    /// @param config - JSON string containing the list of definitions to parse.
    /// @param universe - the universe in which the parsing context should
    /// occur.
    /// @return Returns a pointer to class dictionary created
    /// @throw indirectly, execptions convertring the JSON text to elements,
    /// or by the parsing itself are not caught
    ClientClassDictionaryPtr parseClientClassDefList(const std::string& config,
                                                     Option::Universe universe)
    {
        // Create the "global" context for the parser.
        ParserContextPtr context(new ParserContext(universe));

        // Turn config into elements.  This may emit exceptions.
        ElementPtr config_element = Element::fromJSON(config);

        // Parse the configuration. This may emit exceptions.
        ClientClassDefListParser parser("", context);
        parser.build(config_element);

        // Commit should push it to CfgMgr staging
        parser.commit();

        // Return the parser's local dicationary
        return (parser.local_dictionary_);
    }
};

// Verifies that given a valid expression, the ExpressionParser
// produces an Expression which can be evaluated against a v4 packet.
TEST_F(ExpressionParserTest, validExpression4) {
    testValidExpression<Pkt4>(Option::V4, "\"option[12].text == 'hundred4'\"",
                              "hundred4");
}

// Verifies that the option name can be used in the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionName4) {
    testValidExpression<Pkt4>(Option::V4,
                              "\"option[host-name].text == 'hundred4'\"",
                              "hundred4");
}

// Verifies that given a valid expression using .hex operator for option, the
// ExpressionParser produces an Expression which can be evaluated against
// a v4 packet.
TEST_F(ExpressionParserTest, validExpressionWithHex4) {
    testValidExpression<Pkt4>(Option::V4, "\"option[12].hex == 0x68756E6472656434\"",
                              "hundred4");
}

// Verifies that the option name can be used together with .hex operator in
// the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionNameAndHex4) {
    testValidExpression<Pkt6>(Option::V4,
                              "\"option[host-name].text == 0x68756E6472656434\"",
                              "hundred4");
}

// Verifies that given a valid expression, the ExpressionParser
// produces an Expression which can be evaluated against a v6 packet.
TEST_F(ExpressionParserTest, validExpression6) {
    testValidExpression<Pkt6>(Option::V6, "\"option[59].text == 'hundred6'\"",
                              "hundred6");
}

// Verifies that the option name can be used in the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionName6) {
    testValidExpression<Pkt6>(Option::V6,
                              "\"option[bootfile-url].text == 'hundred6'\"",
                              "hundred6");
}

// Verifies that given a valid expression using .hex operator for option, the
// ExpressionParser produces an Expression which can be evaluated against
// a v6 packet.
TEST_F(ExpressionParserTest, validExpressionWithHex6) {
    testValidExpression<Pkt6>(Option::V6, "\"option[59].hex == 0x68756E6472656436\"",
                              "hundred6");
}

// Verifies that the option name can be used together with .hex operator in
// the evaluated expression.
TEST_F(ExpressionParserTest, validExpressionWithOptionNameAndHex6) {
    testValidExpression<Pkt6>(Option::V6,
                              "\"option[bootfile-url].text == 0x68756E6472656436\"",
                              "hundred6");
}

// Verifies that an the ExpressionParser only accepts StringElements.
TEST_F(ExpressionParserTest, invalidExpressionElement) {
    ParserContextPtr context(new ParserContext(Option::V4));
    ExpressionParserPtr parser;
    ExpressionPtr parsed_expr;

    // This will create an integer element should fail.
    std::string cfg_txt = "777";
    ElementPtr config_element = Element::fromJSON(cfg_txt);

    // Create the parser.
    ASSERT_NO_THROW(parser.reset(new ExpressionParser("", parsed_expr,
                                                      context)));
    // Expressionn build() should fail.
    ASSERT_THROW(parser->build(config_element), DhcpConfigError);
}

// Verifies that given an invalid expression with a syntax error,
// the Expression parser will throw a DhdpConfigError.  Note this
// is not intended to be an exhaustive test or expression syntax.
// It is simply to ensure that if the parser fails, it does so
// Properly.
TEST_F(ExpressionParserTest, expressionSyntaxError) {
    ParserContextPtr context(new ParserContext(Option::V4));
    ExpressionParserPtr parser;
    ExpressionPtr parsed_expr;

    // Turn config into elements.
    std::string cfg_txt = "\"option 'bogus'\"";
    ElementPtr config_element = Element::fromJSON(cfg_txt);

    // Create the parser.
    ASSERT_NO_THROW(parser.reset(new ExpressionParser("", parsed_expr,
                                                      context)));
    // Expressionn build() should fail.
    ASSERT_THROW(parser->build(config_element), DhcpConfigError);
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
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, Option::V4));

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
    ASSERT_TRUE(oc = cclass->getCfgOption()->getAll("dhcp4"));
    EXPECT_EQ(0, oc->size());

    // Verify we have no expression.
    ASSERT_FALSE(cclass->getMatchExpr());
}

// Verifies you can create a class with a name, expression,
// but no options.
TEST_F(ClientClassDefParserTest, nameAndExpressionClass) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"class_one\", \n"
        "    \"test\": \"option[100].text == 'works right'\" \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, Option::V4));

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
    ASSERT_TRUE(oc = cclass->getCfgOption()->getAll("dhcp4"));
    EXPECT_EQ(0, oc->size());

    // Verify we can retrieve the expression
    ExpressionPtr match_expr = cclass->getMatchExpr();
    ASSERT_TRUE(match_expr);

    // Build a packet that will fail evaluation.
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 123));
    EXPECT_FALSE(evaluate(*match_expr, *pkt4));

    // Now add the option so it will pass.
    OptionPtr opt(new OptionString(Option::V4, 100, "works right"));
    pkt4->addOption(opt);
    EXPECT_TRUE(evaluate(*match_expr, *pkt4));
}

// Verifies you can create a class with a name and options,
// but no expression.
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
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, Option::V4));

    // We should find our class.
    ASSERT_TRUE(cclass);
    EXPECT_EQ("MICROSOFT", cclass->getName());

    // Our one option should exist.
    OptionDescriptor od = cclass->getCfgOption()->get("dhcp4", 6);
    ASSERT_TRUE(od.option_);
    EXPECT_EQ(6, od.option_->getType());

    // Verify we have no expression
    ASSERT_FALSE(cclass->getMatchExpr());
}


// Verifies you can create a class with a name, expression,
// and options.
TEST_F(ClientClassDefParserTest, basicValidClass) {

    std::string cfg_text =
        "{ \n"
        "    \"name\": \"MICROSOFT\", \n"
        "    \"test\": \"option[100].text == 'booya'\", \n"
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
    ASSERT_NO_THROW(cclass = parseClientClassDef(cfg_text, Option::V4));

    // We should find our class.
    ASSERT_TRUE(cclass);
    EXPECT_EQ("MICROSOFT", cclass->getName());

    // Our one option should exist.
    OptionDescriptor od = cclass->getCfgOption()->get("dhcp4", 6);
    ASSERT_TRUE(od.option_);
    EXPECT_EQ(6, od.option_->getType());

    // Verify we can retrieve the expression
    ExpressionPtr match_expr = cclass->getMatchExpr();
    ASSERT_TRUE(match_expr);

    // Build a packet that will fail evaluation.
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 123));
    EXPECT_FALSE(evaluate(*match_expr, *pkt4));

    // Now add the option so it will pass.
    OptionPtr opt(new OptionString(Option::V4, 100, "booya"));
    pkt4->addOption(opt);
    EXPECT_TRUE(evaluate(*match_expr, *pkt4));
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
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, Option::V4),
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
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, Option::V4),
                 DhcpConfigError);
}


// Verifies that a class with an unknown element, fails to parse.
TEST_F(ClientClassDefParserTest, unknownElement) {
    std::string cfg_text =
        "{ \n"
        "    \"name\": \"one\", \n"
        "    \"bogus\": \"bad\" \n"
        "} \n";

    ClientClassDefPtr cclass;
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, Option::V4),
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
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, Option::V4),
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
    ASSERT_THROW(cclass = parseClientClassDef(cfg_text, Option::V4),
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
    ASSERT_NO_THROW(dictionary = parseClientClassDefList(cfg_text, Option::V4));
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

    // For good measure, make sure we can't find a non-existant class.
    ASSERT_NO_THROW(cclass = dictionary->findClass("bogus"));
    EXPECT_FALSE(cclass);

    // Verify that the dictionary was pushed to the CfgMgr's staging config.
    SrvConfigPtr staging = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(staging);
    ClientClassDictionaryPtr staged_dictionary = staging->getClientClassDictionary();
    ASSERT_TRUE(staged_dictionary);
    EXPECT_TRUE(*staged_dictionary == *dictionary);
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
    ASSERT_THROW(dictionary = parseClientClassDefList(cfg_text, Option::V4),
                 DhcpConfigError);
}

// Verifies that a class list containing an invalid class entry, fails to
// parse.
TEST_F(ClientClassDefListParserTest, invalidClass) {
    std::string cfg_text =
        "[ \n"
        "   { \n"
        "       \"name\": \"one\", \n"
        "       \"bogus\": \"bad\" \n"
        "   } \n"
        "] \n";

    ClientClassDictionaryPtr dictionary;
    ASSERT_THROW(dictionary = parseClientClassDefList(cfg_text, Option::V4),
                 DhcpConfigError);
}

} // end of anonymous namespace
