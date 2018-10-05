// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_option_data.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;

namespace {

/// @brief Translator name.
extern char const option_data_list[] = "option data list";

/// @brief Test fixture class for @ref TranslatorOptionDataList.
class TranslatorOptionDataListTest :
    public GenericTranslatorTest<option_data_list, TranslatorOptionDataList> {
public:

    /// Constructor.
    TranslatorOptionDataListTest() { }

    /// Destructor (does nothing).
    virtual ~TranslatorOptionDataListTest() { }
};

// This test verifies that an empty option data list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorOptionDataListTest, getEmpty) {
    useModel(KEA_DHCP4_SERVER);

    // Get the option data list and checks it is empty.
    const string& xpath = "/kea-dhcp4-server:config/option-data-list";
    ConstElementPtr options;
    EXPECT_NO_THROW(options = t_obj_->getOptionDataList(xpath));
    ASSERT_TRUE(options);
    ASSERT_EQ(Element::list, options->getType());
    EXPECT_EQ(0, options->size());
}

// This test verifies that one option data can be properly translated
// from YANG to JSON.
TEST_F(TranslatorOptionDataListTest, get) {
    useModel(KEA_DHCP6_SERVER);

    // Create the option code 100.
    const string& xpath = "/kea-dhcp6-server:config/option-data-list";
    const string& xoption = xpath + "/option-data[code='100'][space='dns']";
    const string& xformat = xoption + "/csv-format";
    const string& xdata = xoption + "/data";
    const string& xsend = xoption + "/always-send";
    S_Val s_false(new Val(false));
    ASSERT_NO_THROW(sess_->set_item(xformat.c_str(), s_false));
    S_Val s_data(new Val("12121212"));
    ASSERT_NO_THROW(sess_->set_item(xdata.c_str(), s_data));
    ASSERT_NO_THROW(sess_->set_item(xsend.c_str(), s_false));

    // Get the option data.
    ConstElementPtr option;
    EXPECT_NO_THROW(option = t_obj_->getOptionData(xoption));
    ASSERT_TRUE(option);
    EXPECT_EQ("{"
              " \"always-send\": false,"
              " \"code\": 100,"
              " \"csv-format\": false,"
              " \"data\": \"12121212\","
              " \"space\": \"dns\""
              " }",
              option->str());

    // Get the option data list.
    ConstElementPtr options;
    EXPECT_NO_THROW(options = t_obj_->getOptionDataList(xpath));
    ASSERT_TRUE(options);
    ASSERT_EQ(Element::list, options->getType());
    EXPECT_EQ(1, options->size());
    EXPECT_TRUE(option->equals(*options->get(0)));
}

// This test verifies that an empty option data list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorOptionDataListTest, setEmpty) {
    useModel(KEA_DHCP4_SERVER);

    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config/option-data-list";
    ConstElementPtr options = Element::createList();
    EXPECT_NO_THROW(t_obj_->setOptionDataList(xpath, options));

    // Get it back.
    options.reset();
    EXPECT_NO_THROW(options = t_obj_->getOptionDataList(xpath));
    ASSERT_TRUE(options);
    EXPECT_EQ(0, options->size());

    // Check that the tree representation is empty.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp4-server:config"));
    EXPECT_FALSE(tree);
}

// This test verifies that one option data can be properly translated
// from JSON to YANG.
TEST_F(TranslatorOptionDataListTest, set) {
    useModel(KEA_DHCP6_SERVER);

    // Set one option data.
    const string& xpath = "/kea-dhcp6-server:config/option-data-list";
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create(string("dns")));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create(string("12121212")));
    option->set("always-send", Element::create(false));
    options->add(option);
    EXPECT_NO_THROW(t_obj_->setOptionDataList(xpath, options));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW(got = t_obj_->getOptionDataList(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(1, got->size());
    EXPECT_TRUE(option->equals(*got->get(0)));

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp6-server:config"));
    ASSERT_TRUE(tree);
    string expected =
        "kea-dhcp6-server:config (container)\n"
        " |\n"
        " -- option-data-list (container)\n"
        "     |\n"
        "     -- option-data (list instance)\n"
        "         |\n"
        "         -- code = 100\n"
        "         |\n"
        "         -- space = dns\n"
        "         |\n"
        "         -- data = 12121212\n"
        "         |\n"
        "         -- csv-format = false\n"
        "         |\n"
        "         -- always-send = false\n";
    EXPECT_EQ(expected, tree->to_string(100));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}; // end of anonymous namespace
