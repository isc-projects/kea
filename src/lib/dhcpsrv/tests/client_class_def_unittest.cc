// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcp/option_space.h>
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

    // Verify we get an empty collection of cfg_option
    cfg_option = cclass->getCfgOption();
    ASSERT_TRUE(cfg_option);
    //EXPECT_EQ(0, cfg_option->size());
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


// Tests the basic operation of ClientClassDictionary
// This includes adding, finding, and removing classes
TEST(ClientClassDictionary, basics) {
    ClientClassDictionaryPtr dictionary;
    ClientClassDefPtr cclass;
    ExpressionPtr expr;
    CfgOptionPtr cfg_option;

    // Verify constructor doesn't throw
    ASSERT_NO_THROW(dictionary.reset(new ClientClassDictionary()));

    // Verify we can fetch a pointer the map of classes and
    // that we start with no classes defined
    const ClientClassDefMapPtr classes = dictionary->getClasses();
    ASSERT_TRUE(classes);
    EXPECT_EQ(0, classes->size());

    // Verify that we can add classes with both addClass variants
    // First addClass(name, expression, cfg_option)
    ASSERT_NO_THROW(dictionary->addClass("cc1", expr, cfg_option));
    ASSERT_NO_THROW(dictionary->addClass("cc2", expr, cfg_option));

    // Verify duplicate add attempt throws
    ASSERT_THROW(dictionary->addClass("cc2", expr, cfg_option),
                 DuplicateClientClassDef);

    // Verify that you cannot add a class with no name.
    ASSERT_THROW(dictionary->addClass("", expr, cfg_option), BadValue);

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
    ASSERT_NO_THROW(dictionary->addClass("one", expr, options));
    ASSERT_NO_THROW(dictionary->addClass("two", expr, options));
    ASSERT_NO_THROW(dictionary->addClass("three", expr, options));

    // Copy constructor should succeed.
    ASSERT_NO_THROW(dictionary2.reset(new ClientClassDictionary(*dictionary)));

    // Allocated class map pointers should not be equal
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


    string sname = "This is a very long string that can be a server name";
    string filename = "this-is-a-slightly-longish-name-of-a-file.txt";

    cclass->setNextServer(IOAddress("1.2.3.4"));
    cclass->setSname(sname);
    cclass->setFilename(filename);

    // Let's checks that it doesn't return any nonsense
    ASSERT_EQ(IOAddress("1.2.3.4"), cclass->getNextServer());
    EXPECT_EQ(sname, cclass->getSname());
    EXPECT_EQ(filename, cclass->getFilename());
}


} // end of anonymous namespace
