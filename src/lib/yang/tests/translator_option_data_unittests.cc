// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <testutils/test_to_element.h>
#include <yang/tests/sysrepo_setup.h>
#include <yang/translator_option_data.h>
#include <yang/yang_models.h>

#include <sysrepo-cpp/utils/exception.hpp>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::test;
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
    /// @brief Constructor
    TranslatorOptionDataListTestv4() {
        model_ = KEA_DHCP4_SERVER;
     }
};  // TranslatorOptionDataListTestv4

class TranslatorOptionDataListTestv6 :
    public GenericTranslatorTest<option_data_list, TranslatorOptionDataList> {
public:
    /// @brief Constructor
    TranslatorOptionDataListTestv6() {
        model_ = KEA_DHCP6_SERVER;
     }
};  // TranslatorOptionDataListTestv6

// This test verifies that an empty option data list can be properly
// translated from YANG to JSON for v4.
TEST_F(TranslatorOptionDataListTestv4, getEmpty) {
    // Get the option data list and check if it is empty.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr options;
    EXPECT_NO_THROW_LOG(options = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_FALSE(options);
}

// This test verifies that an empty option data list can be properly
// translated from YANG to JSON for v6.
TEST_F(TranslatorOptionDataListTestv6, getEmpty) {
    // Get the option data list and check if it is empty.
    const string& xpath = "/kea-dhcp6-server:config";
    ConstElementPtr options;
    EXPECT_NO_THROW_LOG(options = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_FALSE(options);
}

// This test verifies that one option data can be properly translated
// from YANG to JSON for v4.
TEST_F(TranslatorOptionDataListTestv4, get) {
    // Create the option code 100.
    const string& xpath = "/kea-dhcp4-server:config";
    const string& xoption = xpath + "/option-data[code='100'][space='dns'][data='12121212']";
    const string& xformat = xoption + "/csv-format";
    const string& xalways = xoption + "/always-send";
    const string& xnever = xoption + "/never-send";
    string const s_false("false");
    ASSERT_NO_THROW_LOG(sess_->setItem(xformat, s_false));
    ASSERT_NO_THROW_LOG(sess_->setItem(xalways, s_false));
    ASSERT_NO_THROW_LOG(sess_->setItem(xnever, s_false));
    sess_->applyChanges();

    // Get the option data.
    ConstElementPtr option;
    EXPECT_NO_THROW_LOG(option = translator_->getOptionDataFromAbsoluteXpath(xoption));
    ASSERT_TRUE(option);
    EXPECT_EQ("{"
              " \"always-send\": false,"
              " \"code\": 100,"
              " \"csv-format\": false,"
              " \"data\": \"12121212\","
              " \"never-send\": false,"
              " \"space\": \"dns\""
              " }",
              option->str());

    // Get the option data list.
    ConstElementPtr options;
    EXPECT_NO_THROW_LOG(options = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(options);
    ASSERT_EQ(Element::list, options->getType());
    EXPECT_EQ(1, options->size());
    expectEqWithDiff(option, options->get(0));
}

// This test verifies that one option data can be properly translated
// from YANG to JSON for v6.
TEST_F(TranslatorOptionDataListTestv6, get) {
    // Create the option code 100.
    const string& xpath = "/kea-dhcp6-server:config";
    const string& xoption = xpath + "/option-data[code='100'][space='dns'][data='12121212']";
    const string& xformat = xoption + "/csv-format";
    const string& xalways = xoption + "/always-send";
    const string& xnever = xoption + "/never-send";
    string const s_false("false");
    ASSERT_NO_THROW_LOG(sess_->setItem(xformat, s_false));
    ASSERT_NO_THROW_LOG(sess_->setItem(xalways, s_false));
    ASSERT_NO_THROW_LOG(sess_->setItem(xnever, s_false));
    sess_->applyChanges();

    // Get the option data.
    ConstElementPtr option;
    EXPECT_NO_THROW_LOG(option = translator_->getOptionDataFromAbsoluteXpath(xoption));
    ASSERT_TRUE(option);
    EXPECT_EQ("{"
              " \"always-send\": false,"
              " \"code\": 100,"
              " \"csv-format\": false,"
              " \"data\": \"12121212\","
              " \"never-send\": false,"
              " \"space\": \"dns\""
              " }",
              option->str());

    // Get the option data list.
    ConstElementPtr options;
    EXPECT_NO_THROW_LOG(options = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(options);
    ASSERT_EQ(Element::list, options->getType());
    EXPECT_EQ(1, options->size());
    expectEqWithDiff(option, options->get(0));
}

// This test verifies that an empty option data list can be properly
// translated from JSON to YANG for v4.
TEST_F(TranslatorOptionDataListTestv4, setEmpty) {
    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr options = Element::createList();
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    options.reset();
    EXPECT_NO_THROW_LOG(options = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_FALSE(options);
}

// This test verifies that an empty option data list can be properly
// translated from JSON to YANG for v6.
TEST_F(TranslatorOptionDataListTestv6, setEmpty) {
    // Set empty list.
    const string& xpath = "/kea-dhcp6-server:config";
    ConstElementPtr options = Element::createList();
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    options.reset();
    EXPECT_NO_THROW_LOG(options = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_FALSE(options);
}

// This test verifies that one option data can be properly translated
// from JSON to YANG for v4.
TEST_F(TranslatorOptionDataListTestv4, set) {
    // Negative tests.
    string const xpath("/kea-dhcp4-server:config");
    string const xoption(xpath + "/option-data[code='100'][space='dns'][data='12121212']");
    string const s_code("15");
    string const s_space("dhcp4");
    string const s_data("12121212");
    EXPECT_THROW_MSG(sess_->setItem(xoption + "/code", s_code), sysrepo::Error,
                     "Session::setItem: Couldn't set "
                     "'/kea-dhcp4-server:config/option-data[code='100'][space='dns'][data='12121212']/code' to "
                     "'15': SR_ERR_INVAL_ARG");
    EXPECT_THROW_MSG(sess_->setItem(xoption + "/space", s_space), sysrepo::Error,
                     "Session::setItem: Couldn't set "
                     "'/kea-dhcp4-server:config/option-data[code='100'][space='dns'][data='12121212']/space' to "
                     "'dhcp4': SR_ERR_INVAL_ARG");
    EXPECT_THROW_MSG(sess_->setItem(xoption + "/data", s_data), sysrepo::Error,
                     "Session::setItem: Couldn't set "
                     "'/kea-dhcp4-server:config/option-data[code='100'][space='dns'][data='12121212']/data' to "
                     "'12121212': SR_ERR_INVAL_ARG");

    // Setting the list element directly should work.
    EXPECT_NO_THROW_LOG(sess_->setItem(xoption, std::nullopt));

    // Set one option data.
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create("12121212"));
    option->set("always-send", Element::create(false));
    option->set("never-send", Element::create(false));
    options->add(option);
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(1, got->size());
    expectEqWithDiff(option, options->get(0));
}

// This test verifies that one option data can be properly translated
// from JSON to YANG for v6.
TEST_F(TranslatorOptionDataListTestv6, set) {
    // Negative tests.
    string const xpath("/kea-dhcp6-server:config");
    string const xoption(xpath + "/option-data[code='100'][space='dns'][data='12121212']");
    string const s_code("15");
    string const s_space("dhcp6");
    string const s_data("12121212");
    EXPECT_THROW_MSG(sess_->setItem(xoption + "/code", s_code), sysrepo::Error,
                     "Session::setItem: Couldn't set "
                     "'/kea-dhcp6-server:config/option-data[code='100'][space='dns'][data='12121212']/code' to "
                     "'15': SR_ERR_INVAL_ARG");
    EXPECT_THROW_MSG(sess_->setItem(xoption + "/space", s_space), sysrepo::Error,
                     "Session::setItem: Couldn't set "
                     "'/kea-dhcp6-server:config/option-data[code='100'][space='dns'][data='12121212']/space' to "
                     "'dhcp6': SR_ERR_INVAL_ARG");
    EXPECT_THROW_MSG(sess_->setItem(xoption + "/data", s_data), sysrepo::Error,
                     "Session::setItem: Couldn't set "
                     "'/kea-dhcp6-server:config/option-data[code='100'][space='dns'][data='12121212']/data' to "
                     "'12121212': SR_ERR_INVAL_ARG");

    // Setting the list element directly should work.
    EXPECT_NO_THROW_LOG(sess_->setItem(xoption, std::nullopt));

    // Set one option data.
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create("12121212"));
    option->set("always-send", Element::create(false));
    option->set("never-send", Element::create(false));
    options->add(option);
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(1, got->size());
    expectEqWithDiff(option, options->get(0));
}

// This test verifies that multiple options of same code and space but different data can be
// configured for v4.
TEST_F(TranslatorOptionDataListTestv4, optionsSameCodeAndSpace) {
    string const xpath("/kea-dhcp4-server:config");

    // Set one option data.
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create("12121212"));
    option->set("always-send", Element::create(false));
    option->set("never-send", Element::create(false));
    options->add(option);
    option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create("34343434"));
    option->set("always-send", Element::create(false));
    option->set("never-send", Element::create(false));
    options->add(option);
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(2, got->size());
    expectEqWithDiff(options, got);

    // Now with keys only.
    options = Element::createList();
    option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("data", Element::create("56565656"));
    options->add(option);
    option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("data", Element::create("78787878"));
    options->add(option);
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(4, got->size());
    expectEqWithDiff(options->get(0), got->get(2));
    expectEqWithDiff(options->get(1), got->get(3));
}

// This test verifies that multiple options of same code and space but different data can be
// configured for v6.
TEST_F(TranslatorOptionDataListTestv6, optionsSameCodeAndSpace) {
    string const xpath("/kea-dhcp6-server:config");

    // Set one option data.
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create("12121212"));
    option->set("always-send", Element::create(false));
    option->set("never-send", Element::create(false));
    options->add(option);
    option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create("34343434"));
    option->set("always-send", Element::create(false));
    option->set("never-send", Element::create(false));
    options->add(option);
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(2, got->size());
    expectEqWithDiff(options, got);

    // Now with keys only.
    options = Element::createList();
    option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("data", Element::create("56565656"));
    options->add(option);
    option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create("dns"));
    option->set("data", Element::create("78787878"));
    options->add(option);
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get it back.
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(4, got->size());
    expectEqWithDiff(options->get(0), got->get(2));
    expectEqWithDiff(options->get(1), got->get(3));
}

// This test verifies that multiple options with empty option data can be
// configured for v4.
TEST_F(TranslatorOptionDataListTestv4, emptyData) {
    string const xpath("/kea-dhcp4-server:config");

    // Set two options with empty data.
    ElementPtr const options(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns",
        "csv-format": false,
        "data": "",
        "always-send": false,
        "never-send": false
      },
      {
        "code": 101,
        "space": "dns",
        "csv-format": false,
        "data": "",
        "always-send": false,
        "never-send": false
      }
    ])"));
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get them back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(2, got->size());

    // Expect no "data" whatsoever. This is the same as empty "data" to the Kea DHCP server.
    ElementPtr const expected(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns",
        "csv-format": false,
        "always-send": false,
        "never-send": false
      },
      {
        "code": 101,
        "space": "dns",
        "csv-format": false,
        "always-send": false,
        "never-send": false
      }
    ])"));
    expectEqWithDiff(expected, got);
}

// This test verifies that multiple options with all keys and empty option data can be
// configured for v4.
TEST_F(TranslatorOptionDataListTestv4, emptyDataKeysOnly) {
    string const xpath("/kea-dhcp4-server:config");

    // Set two options with empty data.
    ElementPtr const options(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns",
        "data": ""
      },
      {
        "code": 101,
        "space": "dns",
        "data": ""
      }
    ])"));
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get them back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(2, got->size());

    // Expect no "data" whatsoever. This is the same as empty "data" to the Kea DHCP server.
    ElementPtr const expected(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns"
      },
      {
        "code": 101,
        "space": "dns"
      }
    ])"));
    expectEqWithDiff(expected, got);
}

// This test verifies that multiple options with empty option data can be
// configured for v6.
TEST_F(TranslatorOptionDataListTestv6, emptyData) {
    string const xpath("/kea-dhcp6-server:config");

    // Set two options with empty data.
    ElementPtr const options(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns",
        "csv-format": false,
        "data": "",
        "always-send": false,
        "never-send": false
      },
      {
        "code": 101,
        "space": "dns",
        "csv-format": false,
        "data": "",
        "always-send": false,
        "never-send": false
      }
    ])"));
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get them back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(2, got->size());

    // Expect no "data" whatsoever. This is the same as empty "data" to the Kea DHCP server.
    ElementPtr const expected(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns",
        "csv-format": false,
        "always-send": false,
        "never-send": false
      },
      {
        "code": 101,
        "space": "dns",
        "csv-format": false,
        "always-send": false,
        "never-send": false
      }
    ])"));
    expectEqWithDiff(expected, got);
}

// This test verifies that multiple options with all keys and empty option data can be
// configured for v6.
TEST_F(TranslatorOptionDataListTestv6, emptyDataKeysOnly) {
    string const xpath("/kea-dhcp6-server:config");

    // Set two options with empty data.
    ElementPtr const options(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns",
        "data": ""
      },
      {
        "code": 101,
        "space": "dns",
        "data": ""
      }
    ])"));
    EXPECT_NO_THROW_LOG(translator_->setOptionDataList(xpath, options));

    // Get them back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getOptionDataListFromAbsoluteXpath(xpath));
    ASSERT_TRUE(got);
    EXPECT_EQ(2, got->size());

    // Expect no "data" whatsoever. This is the same as empty "data" to the Kea DHCP server.
    ElementPtr const expected(Element::fromJSON(R"([
      {
        "code": 100,
        "space": "dns"
      },
      {
        "code": 101,
        "space": "dns"
      }
    ])"));
    expectEqWithDiff(expected, got);
}

}  // namespace
