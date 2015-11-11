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

using namespace std;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc;

namespace {

TEST(ClientClassDef, construction) {
    boost::scoped_ptr<ClientClassDef> cclass;

    std::string name = "class1";
    ExpressionPtr expr;
    OptionCollectionPtr options;

    // Classes cannot have blank names
    ASSERT_THROW(cclass.reset(new ClientClassDef("", expr, options)), BadValue);

    // Verify we can create a class with a name, expression, and no options
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr)));
    EXPECT_EQ(name, cclass->getName());
    ASSERT_FALSE(cclass->getMatchExpr());

    // Verify we get an empty collection of options
    options = cclass->getOptions();
    ASSERT_TRUE(options);
    EXPECT_EQ(0, options->size());
}

TEST(ClientClassDef, optionsBasics) {
    boost::scoped_ptr<ClientClassDef> cclass;

    std::string name = "class1";
    ExpressionPtr expr;
    OptionCollectionPtr options;
    OptionPtr opt;

    // First construct the class with empty option pointer
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr, options)));

    // We should get back a collection with no entries,
    // not an empty collection pointer
    options = cclass->getOptions();
    ASSERT_TRUE(options);
    EXPECT_EQ(0, options->size());

    // We should not be able find an option
    opt = cclass->findOption(17);
    ASSERT_FALSE(opt);

    // Create an option container with two options
    options.reset(new OptionCollection());
    EXPECT_NO_THROW(opt.reset(new Option(Option::V4, 17)));
    options->insert(make_pair(17, opt));
    EXPECT_NO_THROW(opt.reset(new Option(Option::V4, 18)));
    options->insert(make_pair(18, opt));

    // Now remake the client class with options
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef(name, expr, options)));

    options = cclass->getOptions();
    ASSERT_TRUE(options);
    EXPECT_EQ(2, options->size());

    // We should be able to find option 17
    opt = cclass->findOption(17);
    ASSERT_TRUE(opt);
    EXPECT_EQ(17, opt->getType());

    // We should be able to find option 18
    opt = cclass->findOption(18);
    ASSERT_TRUE(opt);
    EXPECT_EQ(18, opt->getType());

    // We should not be able to find option 90
    opt = cclass->findOption(90);
    ASSERT_FALSE(opt);
}

TEST(ClientClassDictionary, basics) {
    ClientClassDictionaryPtr dictionary;
    ClientClassDefPtr cclass;
    ExpressionPtr expr;
    OptionCollectionPtr options;

    // Verify constructor doesn't throw
    ASSERT_NO_THROW(dictionary.reset(new ClientClassDictionary()));

    // Verify we can fetch a pointer the map of classes and
    // that we start with no classes defined
    const ClientClassDefMapPtr classes = dictionary->getClasses();
    ASSERT_TRUE(classes);
    EXPECT_EQ(0, classes->size());

    // Verify that we can add classes with both addClass variants
    // First addClass(name, expression, options)
    ASSERT_NO_THROW(dictionary->addClass("cc1", expr, options));
    ASSERT_NO_THROW(dictionary->addClass("cc2", expr, options));

    // Verify duplicate add attempt throws
    ASSERT_THROW(dictionary->addClass("cc2", expr, options),
                 DuplicateClientClassDef);

    // Verify that you cannot add a class with no name.
    ASSERT_THROW(dictionary->addClass("", expr, options), BadValue);

    // Now with addClass(class pointer)
    ASSERT_NO_THROW(cclass.reset(new ClientClassDef("cc3", expr, options)));
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

} // end of anonymous namespace
