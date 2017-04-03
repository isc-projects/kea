// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
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
        boost::shared_ptr<PktType> pkt(new PktType(family == AF_INET ?
                                                   DHCPDISCOVER : DHCPV6_SOLICIT,
                                                   123));
        EXPECT_FALSE(evaluateBool(*parsed_expr, *pkt));

        // Now add the option so it will pass. Use a standard option carrying a
        // single string value, i.e. hostname for DHCPv4 and bootfile url for
        // DHCPv6.
        Option::Universe universe(family == AF_INET ? Option::V4 : Option::V6);
        OptionPtr opt(new OptionString(universe, family == AF_INET ?
                                       DHO_HOST_NAME : D6O_BOOTFILE_URL,
                                       option_string));
        pkt->addOption(opt);
        EXPECT_TRUE(evaluateBool(*parsed_expr, *pkt));
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

    // For good measure, make sure we can't find a non-existant class.
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

    EXPECT_THROW(parseClientClassDef(bogus_v6, AF_INET), DhcpConfigError);
    EXPECT_THROW(parseClientClassDef(bogus_junk, AF_INET), DhcpConfigError);
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


} // end of anonymous namespace
