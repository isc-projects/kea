// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <yang/tests/sysrepo_setup.h>
#include <yang/translator_class.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const client_classes[] = "client classes";

/// @brief Test fixture class for @ref TranslatorClasses.
class TranslatorClassesTestv4 :
    public GenericTranslatorTest<client_classes, TranslatorClasses> {
public:
    /// @brief Constructor
    TranslatorClassesTestv4() {
        model_ = KEA_DHCP4_SERVER;
    }
};  // TranslatorClassesTestv4

class TranslatorClassesTestv6 :
    public GenericTranslatorTest<client_classes, TranslatorClasses> {
public:
    /// @brief Constructor
    TranslatorClassesTestv6() {
        model_ = KEA_DHCP6_SERVER;
    }
};  // TranslatorClassesTestv6

// This test verifies that an empty client class list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorClassesTestv4, getEmpty) {
    // Get the client class list and check if it is empty.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr classes;
    EXPECT_NO_THROW_LOG(classes = translator_->getClassesFromAbsoluteXpath(xpath));
    EXPECT_FALSE(classes);
}

// This test verifies that one client class can be properly translated
// from YANG to JSON.
TEST_F(TranslatorClassesTestv6, get) {
    // Create the client class.
    const string& xpath = "/kea-dhcp6-server:config";
    const string& xclass = xpath + "/client-class[name='foo']";
    const string& xtest = xclass + "/test";
    string const v_test("not member('ALL')");
    EXPECT_NO_THROW_LOG(sess_->setItem(xtest, v_test));
    sess_->applyChanges();

    // Get the client class.
    ConstElementPtr cclass;
    EXPECT_NO_THROW_LOG(cclass = translator_->getClassFromAbsoluteXpath(xclass));
    ASSERT_TRUE(cclass);
    ElementPtr expected = Element::createMap();
    expected->set("name", Element::create("foo"));
    expected->set("test", Element::create("not member('ALL')"));
    EXPECT_TRUE(expected->equals(*cclass));

    // Get the client class list and check if the client class is in it.
    ConstElementPtr classes;
    EXPECT_NO_THROW_LOG(classes = translator_->getClassesFromAbsoluteXpath(xpath));
    ASSERT_TRUE(classes);
    ASSERT_EQ(Element::list, classes->getType());
    ASSERT_EQ(1, classes->size());
    EXPECT_TRUE(cclass->equals(*classes->get(0)));
}

// This test verifies that an empty client class list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorClassesTestv4, setEmpty) {
    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr classes = Element::createList();
    EXPECT_NO_THROW_LOG(translator_->setClasses(xpath, classes));

    // Get it back.
    classes.reset();
    EXPECT_NO_THROW_LOG(classes = translator_->getClassesFromAbsoluteXpath(xpath));
    EXPECT_FALSE(classes);
}

// This test verifies that one client class can be properly translated
// from JSON to YANG.
TEST_F(TranslatorClassesTestv6, set) {
    // Set one client class.
    const string& xpath = "/kea-dhcp6-server:config";
    ElementPtr classes = Element::createList();
    ElementPtr cclass = Element::createMap();
    cclass->set("name", Element::create("foo"));
    cclass->set("test", Element::create("''==''"));
    cclass->set("only-if-required", Element::create(false));
    classes->add(cclass);
    EXPECT_NO_THROW_LOG(translator_->setClasses(xpath, classes));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getClassesFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(Element::list, got->getType());
    ASSERT_EQ(1, got->size());
    EXPECT_TRUE(cclass->equals(*got->get(0)));
}

}  // namespace
