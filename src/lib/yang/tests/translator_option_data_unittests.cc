// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const option_data_list[] = "option data list";

/// @brief Test fixture class for @ref TranslatorOptionDataList.
class TranslatorOptionDataListTestv4 :
    public GenericTranslatorTest<option_data_list, TranslatorOptionDataList> {
public:

    /// Constructor.
    TranslatorOptionDataListTestv4() {
        model_ = KEA_DHCP4_SERVER;
     }
};

class TranslatorOptionDataListTestv6 :
    public GenericTranslatorTest<option_data_list, TranslatorOptionDataList> {
public:

    /// Constructor.
    TranslatorOptionDataListTestv6() {
        model_ = KEA_DHCP6_SERVER;
     }
};

// This test verifies that an empty option data list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorOptionDataListTestv4, getEmpty) {
    // Get the option data list and check if it is empty.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr options;
    EXPECT_NO_THROW(options = t_obj_->getOptionDataList(xpath));
    ASSERT_FALSE(options);
}

// This test verifies that one option data can be properly translated
// from YANG to JSON.
TEST_F(TranslatorOptionDataListTestv6, get) {
    // Create the option code 100.
    const string& xpath = "/kea-dhcp6-server:config";
    const string& xoption = xpath + "/option-data[code='100'][space='dns']";
    const string& xformat = xoption + "/csv-format";
    const string& xdata = xoption + "/data";
    const string& xsend = xoption + "/always-send";
    S_Val s_false(new Val(false));
    ASSERT_NO_THROW_LOG(sess_->set_item(xformat.c_str(), s_false));
    S_Val s_data(new Val("12121212"));
    ASSERT_NO_THROW_LOG(sess_->set_item(xdata.c_str(), s_data));
    ASSERT_NO_THROW_LOG(sess_->set_item(xsend.c_str(), s_false));

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
TEST_F(TranslatorOptionDataListTestv4, setEmpty) {
    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr options = Element::createList();
    EXPECT_NO_THROW(t_obj_->setOptionDataList(xpath, options));

    // Get it back.
    options.reset();
    EXPECT_NO_THROW(options = t_obj_->getOptionDataList(xpath));
    ASSERT_FALSE(options);
}

// This test verifies that one option data can be properly translated
// from JSON to YANG.
TEST_F(TranslatorOptionDataListTestv6, set) {
    // Set one option data.
    const string& xpath = "/kea-dhcp6-server:config";
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

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}  // namespace
