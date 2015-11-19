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
#include <dhcpsrv/client_class_def.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

/// @file client_class_def_unittest.cc Unit tests for client class storage
/// classes.

using namespace std;
using namespace isc::dhcp;
using namespace isc::util;
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
    ASSERT_NO_THROW(test_options->add(option, false, "dhcp4"));

    option.reset(new Option(Option::V6, 101, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, "isc"));

    option.reset(new Option(Option::V6, 100, OptionBuffer(10, 0xFF)));
    ASSERT_NO_THROW(test_options->add(option, false, "dhcp6"));

    // Now remake the client class with cfg_option
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr, test_options)));
    class_options = cclass->getCfgOption();
    ASSERT_TRUE(class_options);

    // Now make sure we can find all the options
    OptionDescriptor opt_desc = class_options->get("dhcp4",17);
    ASSERT_TRUE(opt_desc.option_);
    EXPECT_EQ(17, opt_desc.option_->getType());

    opt_desc = class_options->get("isc",101);
    ASSERT_TRUE(opt_desc.option_);
    EXPECT_EQ(101, opt_desc.option_->getType());

    opt_desc = class_options->get("dhcp6",100);
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
    ASSERT_NO_THROW(test_options->add(option, false, "dhcp4"));

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
    ASSERT_NO_THROW(test_options->add(option, false, "dhcp4"));
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

    // Verify that you cannot add emtpy class pointer
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

    // Verify the looking for non-existant returns empty pointer
    ASSERT_NO_THROW(cclass = dictionary->findClass("bogus"));
    EXPECT_FALSE(cclass);

    // Verify that we can remove a class
    ASSERT_NO_THROW(dictionary->removeClass("cc3"));
    EXPECT_EQ(2, classes->size());

    // Shouldn't be able to find anymore
    ASSERT_NO_THROW(cclass = dictionary->findClass("cc3"));
    EXPECT_FALSE(cclass);

    // Verify that we can attempt to remove a non-existant class
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

} // end of anonymous namespace
