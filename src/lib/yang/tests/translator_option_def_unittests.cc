// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_option_def.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const option_definition_list[] = "option definition list";

/// @brief Test fixture class for @ref TranslatorOptionDefList.
class TranslatorOptionDefListTestKeaV4 :
    public GenericTranslatorTest<option_definition_list, TranslatorOptionDefList> {
public:

    /// Constructor.
    TranslatorOptionDefListTestKeaV4() {
        model_ = KEA_DHCP4_SERVER;
    }
};
class TranslatorOptionDefListTestKeaV6 :
    public GenericTranslatorTest<option_definition_list, TranslatorOptionDefList> {
public:

    /// Constructor.
    TranslatorOptionDefListTestKeaV6() {
        model_ = KEA_DHCP6_SERVER;
    }
};
class TranslatorOptionDefListTestIetfV6 :
    public GenericTranslatorTest<option_definition_list, TranslatorOptionDefList> {
public:

    /// Constructor.
    TranslatorOptionDefListTestIetfV6() {
        model_ = IETF_DHCPV6_SERVER;
    }
};

// This test verifies that an empty option definition list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorOptionDefListTestKeaV4, getEmpty) {
    // Get the option definition list and check if it is empty.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr options;
    EXPECT_NO_THROW(options = t_obj_->getOptionDefList(xpath));
    ASSERT_FALSE(options);
}

// This test verifies that one option definition can be properly
// translated from YANG to JSON.
TEST_F(TranslatorOptionDefListTestKeaV6, get) {
    // Create the option code 100.
    const string& xpath = "/kea-dhcp6-server:config";
    const string& xdef = xpath + "/option-def[code='100'][space='isc']";
    const string& xname = xdef + "/name";
    const string& xtype = xdef + "/type";
    const string& xarray = xdef + "/array";
    S_Val s_name(new Val("foo"));
    ASSERT_NO_THROW_LOG(sess_->set_item(xname.c_str(), s_name));
    S_Val s_type(new Val("string"));
    ASSERT_NO_THROW_LOG(sess_->set_item(xtype.c_str(), s_type));
    S_Val s_array(new Val(false));
    ASSERT_NO_THROW_LOG(sess_->set_item(xarray.c_str(), s_array));

    // Get the option def.
    ConstElementPtr def;
    EXPECT_NO_THROW(def = t_obj_->getOptionDef(xdef));
    ASSERT_TRUE(def);
    EXPECT_EQ("{ "
              "\"array\": false, "
              "\"code\": 100, "
              "\"name\": \"foo\", "
              "\"space\": \"isc\", "
              "\"type\": \"string\" }",
              def->str());

    // Get the option definition list.
    ConstElementPtr defs;
    EXPECT_NO_THROW(defs = t_obj_->getOptionDefList(xpath));
    ASSERT_TRUE(defs);
    ASSERT_EQ(Element::list, defs->getType());
    EXPECT_EQ(1, defs->size());
    EXPECT_TRUE(def->equals(*defs->get(0)));
}

// This test verifies that an empty option definition list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorOptionDefListTestKeaV4, setEmpty) {
    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr defs = Element::createList();
    EXPECT_NO_THROW(t_obj_->setOptionDefList(xpath, defs));

    // Get it back.
    defs.reset();
    EXPECT_NO_THROW(defs = t_obj_->getOptionDefList(xpath));
    ASSERT_FALSE(defs);
}

// This test verifies that one option definition can be properly
// translated from JSON to YANG.
TEST_F(TranslatorOptionDefListTestKeaV6, set) {
    // Set one option def.
    const string& xpath = "/kea-dhcp6-server:config";
    ElementPtr defs = Element::createList();
    ElementPtr def = Element::createMap();
    def->set("code", Element::create(100));
    def->set("name", Element::create(string("foo")));
    def->set("space", Element::create(string("isc")));
    def->set("type", Element::create(string("string")));
    def->set("array", Element::create(false));
    defs->add(def);
    EXPECT_NO_THROW(t_obj_->setOptionDefList(xpath, defs));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW(got = t_obj_->getOptionDefList(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(1, got->size());
    EXPECT_TRUE(def->equals(*got->get(0)));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}; // end of anonymous namespace
