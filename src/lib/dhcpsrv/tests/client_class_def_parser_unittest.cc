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

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <gtest/gtest.h>
#include <sstream>
#include <stdint.h>
#include <string>

/// @file client_class_def_parser_unittest.cc Unit tests for client class
/// definition parsing.

using namespace isc::data;
using namespace isc::dhcp;

namespace {

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
    /// @throw indirectly, execptions convertring the JSON text to elements,
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


// Verifies basic operation of an ExpressionParser. Until we tie
// this into the actual Bison parsing there's not much to test.
TEST(ExpressionParserTest, simpleStringExpression) {
    ParserContextPtr context(new ParserContext(Option::V4));
    ExpressionParserPtr parser;
    ExpressionPtr parsed_expr;

    // Turn config into elements.  This may emit exceptions.
    std::string cfg_txt = "\"astring\"";
    ElementPtr config_element = Element::fromJSON(cfg_txt);

    // Create the parser.
    ASSERT_NO_THROW(parser.reset(new ExpressionParser("", parsed_expr,
                                                      context)));
    // Expression should parse and commit.
    ASSERT_NO_THROW(parser->build(config_element));
    ASSERT_NO_THROW(parser->commit());

    // Parsed expression should exist.
    ASSERT_TRUE(parsed_expr);

    // Evaluate it. For now the result will be the
    // expression string as dummy ExpressionParser
    // just makes an expression of one TokenString
    // containing the expression string itself.
    ValueStack vstack;
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
    (*parsed_expr)[0]->evaluate(*pkt4, vstack);
    EXPECT_EQ(vstack.top(), "\"astring\"");
}

// Verifies that given an invalid expression, the Expression parser
// will throw a DhdpConfigError.  Note this is not intended to be
// an exhaustive test or expression syntax.  It is simply to ensure
// that if the parser fails, it does so properly.  For now, since
// our parser is a dummy parser which only checks that it's given
// Element::string so send it an integer.
TEST(ExpressionParserTest, invalidExpression) {
    ParserContextPtr context(new ParserContext(Option::V4));
    ExpressionParserPtr parser;
    ExpressionPtr parsed_expr;

    // Turn config into elements.
    std::string cfg_txt = "777";
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
        "    \"name\": \"MICROSOFT\", \n"
        "    \"test\": \"vendor-class-identifier == 'MSFT'\" \n"
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

    // Verify we can retrieve the expression
    ExpressionPtr match_expr = cclass->getMatchExpr();
    ASSERT_TRUE(match_expr);

    // Evaluate it. For now the result will be the
    // expression string as dummy ExpressionParser
    // just makes an expression of one TokenString
    // containing the expression string itself.
    ValueStack vstack;
    Pkt4Ptr pkt4;
    pkt4.reset(new Pkt4(DHCPDISCOVER, 12345));
    (*match_expr)[0]->evaluate(*pkt4, vstack);
    EXPECT_EQ(vstack.top(), "\"vendor-class-identifier == 'MSFT'\"");
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
        "    \"test\": \"vendor-class-identifier == 'MSFT'\", \n"
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

    // Evaluate it. For now the result will be the
    // expression string as dummy ExpressionParser
    // just makes an expression of one TokenString
    // containing the expression string itself.
    ValueStack vstack;
    Pkt4Ptr pkt4;
    pkt4.reset(new Pkt4(DHCPDISCOVER, 12345));
    (*match_expr)[0]->evaluate(*pkt4, vstack);
    EXPECT_EQ(vstack.top(), "\"vendor-class-identifier == 'MSFT'\"");
}

// Verifies that a class with no name, fails to parse.
TEST_F(ClientClassDefParserTest, noClassName) {

    std::string cfg_text =
        "{ \n"
        "    \"test\": \"vendor-class-identifier == 'MSFT'\", \n"
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
