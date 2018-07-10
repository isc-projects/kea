// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_space.h>
#include <testutils/test_to_element.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>
#include <asiolink/io_address.h>

#include <gtest/gtest.h>

/// @file client_class_def_unittest.cc Unit tests for client class storage
/// classes.

using namespace std;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::asiolink;
using namespace isc::test;
using namespace isc;

namespace {

// Tests basic construction of ClientClassDef
TEST(ClientClassDef, construction) {
    boost::scoped_ptr<ClientClassDef> cclass;

    std::string name = "class1";
    ExpressionPtr expr;
    CfgOptionPtr cfg_option;

    // Classes cannot have blank names
    ASSERT_THROW(cclass.reset(new ClientClassDef("", expr, cfg_option)),
                 BadValue);

    // Verify we can create a class with a name, expression, and no cfg_option
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr)));
    EXPECT_EQ(name, cclass->getName());
    ASSERT_FALSE(cclass->getMatchExpr());
    EXPECT_FALSE(cclass->getCfgOptionDef());

    // Verify we get an empty collection of cfg_option
    cfg_option = cclass->getCfgOption();
    ASSERT_TRUE(cfg_option);
    EXPECT_TRUE(cfg_option->empty());

    // Verify we don't depend on something.
    EXPECT_FALSE(cclass->dependOnClass("foobar"));
    EXPECT_FALSE(cclass->dependOnClass(""));
}

// Tests options operations.  Note we just do the basics
// as CfgOption is heavily tested elsewhere.
TEST(ClientClassDef, cfgOptionBasics) {
    boost::scoped_ptr<ClientClassDef> cclass;

    std::string name = "class1";
    ExpressionPtr expr;
    CfgOptionPtr test_options;
    CfgOptionPtr class_options;
    OptionPtr opt;

    // First construct the class with empty option pointer
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr, test_options)));

    // We should get back a collection with no entries,
    // not an empty collection pointer
    class_options = cclass->getCfgOption();
    ASSERT_TRUE(class_options);

    // Create an option container and add some options
    OptionPtr option;
    test_options.reset(new CfgOption());
    option.reset(new Option(Option::V4, 17, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, DHCP4_OPTION_SPACE));

    option.reset(new Option(Option::V6, 101, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, "isc"));

    option.reset(new Option(Option::V6, 100, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, DHCP6_OPTION_SPACE));

    // Now remake the client class with cfg_option
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr, test_options)));
    class_options = cclass->getCfgOption();
    ASSERT_TRUE(class_options);

    // Now make sure we can find all the options
    OptionDescriptor opt_desc = class_options->get(DHCP4_OPTION_SPACE,17);
    ASSERT_TRUE(opt_desc.option_);
    EXPECT_EQ(17, opt_desc.option_->getType());

    opt_desc = class_options->get("isc",101);
    ASSERT_TRUE(opt_desc.option_);
    EXPECT_EQ(101, opt_desc.option_->getType());

    opt_desc = class_options->get(DHCP6_OPTION_SPACE,100);
    ASSERT_TRUE(opt_desc.option_);
    EXPECT_EQ(100, opt_desc.option_->getType());
}

// Verifies copy constructor and equality tools (methods/operators)
TEST(ClientClassDef, copyAndEquality) {

    boost::scoped_ptr<ClientClassDef> cclass;
    ExpressionPtr expr;
    CfgOptionPtr test_options;
    OptionPtr opt;

    // Make an expression
    expr.reset(new Expression());
    TokenPtr token(new TokenString("boo"));
    expr->push_back(token);

    // Create an option container with an option
    OptionPtr option;
    test_options.reset(new CfgOption());
    option.reset(new Option(Option::V4, 17, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, DHCP4_OPTION_SPACE));

    // Now remake the client class with cfg_option
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef("class_one", expr,
                                                    test_options)));

    // Now lets make a copy of it.
    boost::scoped_ptr<ClientClassDef> cclass2;
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef(*cclass)));

    // The allocated Expression pointers should not match
    EXPECT_TRUE(cclass->getMatchExpr().get() !=
                 cclass2->getMatchExpr().get());

    // The allocated CfgOption pointers should not match
    EXPECT_TRUE(cclass->getCfgOption().get() !=
                 cclass2->getCfgOption().get());

    // Verify the equality tools reflect that the classes are equal.
    EXPECT_TRUE(cclass->equals(*cclass2));
    EXPECT_TRUE(*cclass == *cclass2);
    EXPECT_FALSE(*cclass != *cclass2);

    // Verify the required flag is enough to make classes not equal.
    EXPECT_FALSE(cclass->getRequired());
    cclass2->setRequired(true);
    EXPECT_TRUE(cclass2->getRequired());
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);
    cclass2->setRequired(false);
    EXPECT_TRUE(*cclass == *cclass2);

    // Verify the depend on known flag is enough to make classes not equal.
    EXPECT_FALSE(cclass->getDependOnKnown());
    cclass2->setDependOnKnown(true);
    EXPECT_TRUE(cclass2->getDependOnKnown());
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);

    // Make a class that differs from the first class only by name and
    // verify that the equality tools reflect that the classes are not equal.
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef("class_two", expr,
                                                     test_options)));
    EXPECT_FALSE(cclass->equals(*cclass2));
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);

    // Make a class with the same name and options, but no expression
    // verify that the equality tools reflect that the classes are not equal.
    expr.reset();
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef("class_one", expr,
                                                     test_options)));
    EXPECT_FALSE(cclass->equals(*cclass2));
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);

    // Make a class with the same name and options, but different expression,
    // verify that the equality tools reflect that the classes are not equal.
    expr.reset(new Expression());
    token.reset(new TokenString("yah"));
    expr->push_back(token);
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef("class_one", expr,
                                                      test_options)));
    EXPECT_FALSE(cclass->equals(*cclass2));
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);

    // Make a class that with same name, expression and options, but
    // different option definitions, verify that the equality tools reflect
    // that the equality tools reflect that the classes are not equal.
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef(*cclass)));
    EXPECT_TRUE(cclass->equals(*cclass2));
    OptionDefinitionPtr def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE, 43);
    EXPECT_FALSE(def);
    def = LibDHCP::getLastResortOptionDef(DHCP4_OPTION_SPACE, 43);
    EXPECT_TRUE(def);
    CfgOptionDefPtr cfg(new CfgOptionDef());
    ASSERT_NO_THROW(cfg->add(def, DHCP4_OPTION_SPACE));
    cclass2->setCfgOptionDef(cfg);
    EXPECT_FALSE(cclass->equals(*cclass2));
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);

    // Make a class with same name and expression, but no options
    // verify that the equality tools reflect that the classes are not equal.
    test_options.reset(new CfgOption());
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef("class_one", expr,
                                                     test_options)));
    EXPECT_FALSE(cclass->equals(*cclass2));
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);

    // Make a class that with same name and expression, but different options
    // verify that the equality tools reflect that the classes are not equal.
    option.reset(new Option(Option::V4, 20, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, DHCP4_OPTION_SPACE));
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef("class_one", expr,
                                                     test_options)));
    EXPECT_FALSE(cclass->equals(*cclass2));
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);
}

// Verifies assignment.
TEST(ClientClassDef, assign) {

    boost::scoped_ptr<ClientClassDef> cclass;
    ExpressionPtr expr;
    CfgOptionPtr test_options;
    OptionPtr opt;

    // Make an expression
    expr.reset(new Expression());
    TokenPtr token(new TokenString("boo"));
    expr->push_back(token);

    // Create an option container with an option
    OptionPtr option;
    test_options.reset(new CfgOption());
    option.reset(new Option(Option::V4, 17, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, DHCP4_OPTION_SPACE));

    // Now remake the client class with cfg_option
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef("class_one", expr,
                                                    test_options)));

    // Now lets assign a fresh definition to it;
    boost::scoped_ptr<ClientClassDef> cclass2;
    ExpressionPtr expr_empty;
    ASSERT_NO_THROW(cclass2.reset(new ClientClassDef("another", expr_empty)));
    ASSERT_NO_THROW(*cclass2 = *cclass);

    // The allocated Expression pointers should  match
    EXPECT_TRUE(cclass->getMatchExpr().get() ==
                cclass2->getMatchExpr().get());

    // The allocated CfgOption pointers should match
    EXPECT_TRUE(cclass->getCfgOption().get() ==
                cclass2->getCfgOption().get());

    // Verify the equality tools reflect that the classes are equal.
    EXPECT_TRUE(cclass->equals(*cclass2));
    EXPECT_TRUE(*cclass == *cclass2);
    EXPECT_FALSE(*cclass != *cclass2);

    // Verify the required flag is enough to make classes not equal.
    EXPECT_FALSE(cclass->getRequired());
    cclass2->setRequired(true);
    EXPECT_TRUE(cclass2->getRequired());
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);
    cclass2->setRequired(false);
    EXPECT_TRUE(*cclass == *cclass2);

    // Verify the depend on known flag is enough to make classes not equal.
    EXPECT_FALSE(cclass->getDependOnKnown());
    cclass2->setDependOnKnown(true);
    EXPECT_TRUE(cclass2->getDependOnKnown());
    EXPECT_FALSE(*cclass == *cclass2);
    EXPECT_TRUE(*cclass != *cclass2);
}

// Tests dependency.
TEST(ClientClassDef, dependency) {
    boost::scoped_ptr<ClientClassDef> cclass;

    ExpressionPtr expr;

    // Make an expression
    expr.reset(new Expression());
    TokenPtr token(new TokenMember("foo"));
    expr->push_back(token);

    ASSERT_NO_THROW(cclass.reset(new ClientClassDef("class", expr)));
    EXPECT_TRUE(cclass->dependOnClass("foo"));
    EXPECT_FALSE(cclass->dependOnClass("bar"));
}


// Tests the basic operation of ClientClassDictionary
// This includes adding, finding, and removing classes
TEST(ClientClassDictionary, basics) {
    ClientClassDictionaryPtr dictionary;
    ClientClassDefPtr cclass;
    ExpressionPtr expr;
    CfgOptionPtr cfg_option;

    // Verify constructor doesn't throw
    ASSERT_NO_THROW(dictionary.reset(new ClientClassDictionary()));

    // Verify we can fetch a pointer the list of classes and
    // that we start with no classes defined
    const ClientClassDefListPtr classes = dictionary->getClasses();
    ASSERT_TRUE(classes);
    EXPECT_EQ(0, classes->size());

    // Verify that we can add classes with both addClass variants
    // First addClass(name, expression, cfg_option)
    ASSERT_NO_THROW(dictionary->addClass("cc1", expr, "", false,
                                         false, cfg_option));
    ASSERT_NO_THROW(dictionary->addClass("cc2", expr, "", false,
                                         false, cfg_option));

    // Verify duplicate add attempt throws
    ASSERT_THROW(dictionary->addClass("cc2", expr, "", false,
                                      false, cfg_option),
                 DuplicateClientClassDef);

    // Verify that you cannot add a class with no name.
    ASSERT_THROW(dictionary->addClass("", expr, "", false,
                                      false, cfg_option),
                 BadValue);

    // Now with addClass(class pointer)
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef("cc3", expr, cfg_option)));
    ASSERT_NO_THROW(dictionary->addClass(cclass));

    // Verify duplicate add attempt throws
    ASSERT_THROW(dictionary->addClass(cclass), DuplicateClientClassDef);

    // Verify that you cannot add empty class pointer
    cclass.reset();
    ASSERT_THROW(dictionary->addClass(cclass), BadValue);

    // Map should show 3 entries.
    EXPECT_EQ(3, classes->size());

    // Verify we can find them all.
    ASSERT_NO_THROW(cclass = dictionary->findClass("cc1"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("cc1", cclass->getName());

    ASSERT_NO_THROW(cclass = dictionary->findClass("cc2"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("cc2", cclass->getName());

    ASSERT_NO_THROW(cclass = dictionary->findClass("cc3"));
    ASSERT_TRUE(cclass);
    EXPECT_EQ("cc3", cclass->getName());

    // Verify the looking for non-existing returns empty pointer
    ASSERT_NO_THROW(cclass = dictionary->findClass("bogus"));
    EXPECT_FALSE(cclass);

    // Verify that we can remove a class
    ASSERT_NO_THROW(dictionary->removeClass("cc3"));
    EXPECT_EQ(2, classes->size());

    // Shouldn't be able to find anymore
    ASSERT_NO_THROW(cclass = dictionary->findClass("cc3"));
    EXPECT_FALSE(cclass);

    // Verify that we can attempt to remove a non-existing class
    // without harm.
    ASSERT_NO_THROW(dictionary->removeClass("cc3"));
    EXPECT_EQ(2, classes->size());
}

// Verifies copy constructor and equality tools (methods/operators)
TEST(ClientClassDictionary, copyAndEquality) {
    ClientClassDictionaryPtr dictionary;
    ClientClassDictionaryPtr dictionary2;
    ClientClassDefPtr cclass;
    ExpressionPtr expr;
    CfgOptionPtr options;

    dictionary.reset(new ClientClassDictionary());
    ASSERT_NO_THROW(dictionary->addClass("one", expr, "", false,
                                         false, options));
    ASSERT_NO_THROW(dictionary->addClass("two", expr, "", false,
                                         false, options));
    ASSERT_NO_THROW(dictionary->addClass("three", expr, "", false,
                                         false, options));

    // Copy constructor should succeed.
    ASSERT_NO_THROW(dictionary2.reset(new ClientClassDictionary(*dictionary)));

    // Allocated class list pointers should not be equal
    EXPECT_NE(dictionary->getClasses().get(), dictionary2->getClasses().get());

    // Equality tools should reflect that the dictionaries are equal.
    EXPECT_TRUE(dictionary->equals(*dictionary2));
    EXPECT_TRUE(*dictionary == *dictionary2);
    EXPECT_FALSE(*dictionary != *dictionary2);

    // Remove a class from dictionary2.
    ASSERT_NO_THROW(dictionary2->removeClass("two"));

    // Equality tools should reflect that the dictionaries are not equal.
    EXPECT_FALSE(dictionary->equals(*dictionary2));
    EXPECT_FALSE(*dictionary == *dictionary2);
    EXPECT_TRUE(*dictionary != *dictionary2);

    // Create an empty dictionary.
    dictionary2.reset(new ClientClassDictionary());

    // Equality tools should reflect that the dictionaries are not equal.
    EXPECT_FALSE(dictionary->equals(*dictionary2));
    EXPECT_FALSE(*dictionary == *dictionary2);
    EXPECT_TRUE(*dictionary != *dictionary2);
}

// Tests dependency.
TEST(ClientClassDictionary, dependency) {
    ClientClassDictionaryPtr dictionary(new ClientClassDictionary());
    ExpressionPtr expr;
    CfgOptionPtr cfg_option;

    // Make an expression depending on forward class.
    ExpressionPtr expr1;
    expr1.reset(new Expression());
    TokenPtr token1(new TokenMember("cc2"));
    expr1->push_back(token1);

    ASSERT_NO_THROW(dictionary->addClass("cc1", expr1, "", false,
                                         false, cfg_option));

    // Make an expression depending on first class.
    ExpressionPtr expr2;
    expr2.reset(new Expression());
    TokenPtr token2(new TokenMember("cc1"));
    expr2->push_back(token2);

    ASSERT_NO_THROW(dictionary->addClass("cc2", expr2, "", false,
                                         false, cfg_option));

    // Make expression with dependency.
    ASSERT_NO_THROW(dictionary->addClass("cc3", expr, "", false,
                                         false, cfg_option));

    ExpressionPtr expr3;
    expr3.reset(new Expression());
    TokenPtr token3(new TokenMember("cc3"));
    expr3->push_back(token3);

    ASSERT_NO_THROW(dictionary->addClass("cc4", expr3, "", false,
                                         false, cfg_option));

    // Not matching dependency does not match.
    string depend;
    EXPECT_FALSE(dictionary->dependOnClass("foobar", depend));
    EXPECT_TRUE(depend.empty());

    // Forward dependency is ignored.
    depend = "";
    EXPECT_FALSE(dictionary->dependOnClass("cc2", depend));
    EXPECT_TRUE(depend.empty());

    // Backward dependency is detected.
    depend = "";
    EXPECT_TRUE(dictionary->dependOnClass("cc3", depend));
    EXPECT_EQ("cc4", depend);
}

// Tests the default constructor regarding fixed fields
TEST(ClientClassDef, fixedFieldsDefaults) {
    boost::scoped_ptr<ClientClassDef> cclass;

    std::string name = "class1";
    ExpressionPtr expr;
    CfgOptionPtr cfg_option;

    // Classes cannot have blank names
    ASSERT_THROW(cclass.reset(new ClientClassDef("", expr, cfg_option)),
                 BadValue);

    // Verify we can create a class with a name, expression, and no cfg_option
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr)));

    // Let's checks that it doesn't return any nonsense
    EXPECT_FALSE(cclass->getRequired());
    EXPECT_FALSE(cclass->getDependOnKnown());
    EXPECT_FALSE(cclass->getCfgOptionDef());
    string empty;
    ASSERT_EQ(IOAddress("0.0.0.0"), cclass->getNextServer());
    EXPECT_EQ(empty, cclass->getSname());
    EXPECT_EQ(empty, cclass->getFilename());
}

// Tests basic operations of fixed fields
TEST(ClientClassDef, fixedFieldsBasics) {
    boost::scoped_ptr<ClientClassDef> cclass;

    std::string name = "class1";
    ExpressionPtr expr;
    CfgOptionPtr cfg_option;

    // Classes cannot have blank names
    ASSERT_THROW(cclass.reset(new ClientClassDef("", expr, cfg_option)),
                 BadValue);

    // Verify we can create a class with a name, expression, and no cfg_option
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr)));

    cclass->setRequired(true);
    cclass->setDependOnKnown(true);

    string sname = "This is a very long string that can be a server name";
    string filename = "this-is-a-slightly-longish-name-of-a-file.txt";

    cclass->setNextServer(IOAddress("1.2.3.4"));
    cclass->setSname(sname);
    cclass->setFilename(filename);

    // Let's checks that it doesn't return any nonsense
    EXPECT_TRUE(cclass->getRequired());
    EXPECT_TRUE(cclass->getDependOnKnown());
    EXPECT_EQ(IOAddress("1.2.3.4"), cclass->getNextServer());
    EXPECT_EQ(sname, cclass->getSname());
    EXPECT_EQ(filename, cclass->getFilename());
}


// Verifies the unparse method of option class definitions
TEST(ClientClassDef, unparseDef) {
    CfgMgr::instance().setFamily(AF_INET);
    boost::scoped_ptr<ClientClassDef> cclass;

    // Get a client class definition and fill it
    std::string name = "class1";
    ExpressionPtr expr;
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr)));
    std::string test = "option[12].text == 'foo'";
    cclass->setTest(test);
    std::string comment = "bar";
    std::string user_context = "{ \"comment\": \"" + comment + "\", ";
    user_context += "\"bar\": 1 }";
    cclass->setContext(isc::data::Element::fromJSON(user_context));
    cclass->setRequired(true);
    // The depend on known flag in not visible
    cclass->setDependOnKnown(true);
    std::string next_server = "1.2.3.4";
    cclass->setNextServer(IOAddress(next_server));
    std::string sname = "my-server.example.com";
    cclass->setSname(sname);
    std::string filename = "/boot/kernel";
    cclass->setFilename(filename);

    // Unparse it
    std::string expected = "{\n"
        "\"comment\": \"" + comment + "\",\n"
        "\"name\": \"" + name + "\",\n"
        "\"test\": \"" + test + "\",\n"
        "\"only-if-required\": true,\n"
        "\"next-server\": \"" + next_server + "\",\n"
        "\"server-hostname\": \"" + sname + "\",\n"
        "\"boot-file-name\": \"" + filename + "\",\n"
        "\"option-data\": [ ],\n"
        "\"user-context\": { \"bar\": 1 } }\n";
    runToElementTest<ClientClassDef>(expected, *cclass);
}

// Verifies the unparse method of client class dictionaries
TEST(ClientClassDictionary, unparseDict) {
    CfgMgr::instance().setFamily(AF_INET);
    ClientClassDictionaryPtr dictionary;
    ExpressionPtr expr;
    CfgOptionPtr options;

    // Get a client class dictionary and fill it
    dictionary.reset(new ClientClassDictionary());
    ASSERT_NO_THROW(dictionary->addClass("one", expr, "", false,
                                         false, options));
    ASSERT_NO_THROW(dictionary->addClass("two", expr, "", false,
                                         false, options));
    ASSERT_NO_THROW(dictionary->addClass("three", expr, "", false,
                                         false, options));

    // Unparse it
    auto add_defaults =
        [](std::string name) {
            return ("{\n"
                    "\"name\": \"" + name + "\",\n"
                    "\"next-server\": \"0.0.0.0\",\n"
                    "\"server-hostname\": \"\",\n"
                    "\"boot-file-name\": \"\",\n"
                    "\"option-data\": [ ] }");
    };

    std::string expected = "[\n" +
        add_defaults("one") + ",\n" +
        add_defaults("two") + ",\n" +
        add_defaults("three") + "]\n";

    runToElementTest<ClientClassDictionary>(expected, *dictionary);
}

} // end of anonymous namespace
