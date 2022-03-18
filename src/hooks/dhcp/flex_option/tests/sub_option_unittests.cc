// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible sub-option.

#include <config.h>
#include <flex_option.h>
#include <flex_option_log.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_string.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <eval/eval_context.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>

#include <tests/test_flex_option.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::hooks;
using namespace isc::flex_option;
using namespace isc::flex_option::test;

namespace {

/// @brief Test fixture for testing the Flex Option library.
class FlexSubOptionTest : public BaseFlexOptionTest { };

// Verify that the sub-options configuration must be a list.
TEST_F(FlexSubOptionTest, configNotList) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createMap();
    option->set("sub-options", sub_options);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'sub-options' must be a list: {  }",
              impl_->getErrMsg());
}

// Verify that the sub-options configuration can be the empty list.
TEST_F(FlexSubOptionTest, configEmpty) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    EXPECT_NO_THROW(impl_->testConfigure(options));
}

// Verify that a sub-option configuration must exist.
TEST_F(FlexSubOptionTest, noSubOptionConfig) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option;
    sub_options->add(sub_option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("null sub-option element", impl_->getErrMsg());
}

// Verify that a sub-option configuration must be a map.
TEST_F(FlexSubOptionTest, subOptionConfigNotMap) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createList();
    sub_options->add(sub_option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("sub-option element is not a map", impl_->getErrMsg());
}

// Verify that multiple actions are not accepted.
TEST_F(FlexSubOptionTest, configMultipleAction) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);

    // add and sub-options.
    ElementPtr add = Element::create(string("'abc'"));
    option->set("add", add);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);

    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    ostringstream errmsg;
    errmsg << "'sub-options' and 'add' are incompatible in the same entry";
    EXPECT_EQ(errmsg.str(), impl_->getErrMsg());
}

// Verify that an unknown option keyword is rejected.
TEST_F(FlexSubOptionTest, subOptionConfigUnknown) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr unknown = Element::create(string("'ab'"));
    // The right keyword is remove...
    sub_option->set("delete", unknown);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("unknown parameter 'delete'", impl_->getErrMsg());
}

// Verify that a sub-option configuration must have code or name.
TEST_F(FlexSubOptionTest, subOptionConfigNoCodeName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    ostringstream errmsg;
    errmsg << "'code' or 'name' must be specified: " << sub_option->str();
    EXPECT_EQ(errmsg.str(), impl_->getErrMsg());
}

// Verify that a sub-option configuration must retrive a space.
TEST_F(FlexSubOptionTest, subOptionConfigNoSpace) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("container is not defined: can't get space", impl_->getErrMsg());
}

// Verify that the v4 sub-option code must be an integer in [0..255].
TEST_F(FlexSubOptionTest, subOptionConfigBadCode4) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    code = Element::create(false);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'code' must be an integer: false", impl_->getErrMsg());

    code = Element::create(-1);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value -1 not in [0..255]", impl_->getErrMsg());

    code = Element::create(256);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value 256 not in [0..255]", impl_->getErrMsg());

    code = Element::create(1);
    sub_option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_EQ("", impl_->getErrMsg());
    EXPECT_TRUE(impl_->getErrMsg().empty());

    code = Element::create(254);
    sub_option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());
}

// Verify that the v6 option code must be an integer in [0..65535].
TEST_F(FlexSubOptionTest, subOptionConfigBadCode6) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    code = Element::create(false);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'code' must be an integer: false", impl_->getErrMsg());

    code = Element::create(-1);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value -1 not in [0..65535]", impl_->getErrMsg());

    code = Element::create(65536);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value 65536 not in [0..65535]", impl_->getErrMsg());

    code = Element::create(1);
    sub_option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    code = Element::create(65535);
    sub_option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());
}

// Verify that the space must be a string.
TEST_F(FlexSubOptionTest, subOptionConfigBadSpace) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(true);
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'space' must be a string: true", impl_->getErrMsg());
}

// Verify that the space must be valid.
TEST_F(FlexSubOptionTest, subOptionConfigInvalidSpace) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("-bad-"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    sub_option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'-bad-' is not a valid space name", impl_->getErrMsg());
}

// Verify that the name must be a string.
TEST_F(FlexSubOptionTest, subOptionConfigBadName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(true);
    sub_option->set("name", name);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'name' must be a string: true", impl_->getErrMsg());
}

// Verify that the name must not be empty.
TEST_F(FlexSubOptionTest, subOptionConfigEmptyName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string());
    sub_option->set("name", name);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'name' must not be empty", impl_->getErrMsg());
}

// Verify that the name must be a known option.
TEST_F(FlexSubOptionTest, subOptionConfigUnknownName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("foobar"));
    sub_option->set("name", name);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("no known 'foobar' sub-option in 'my-space' space",
              impl_->getErrMsg());
}

// Verify that the definition is not required when csv-format is not specified.
TEST_F(FlexSubOptionTest, subOptionConfigUnknownCodeNoCSVFormat) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(109));
    auto smap = map[109];
    EXPECT_EQ(1, smap.count(222));
}

// Verify that the definition is not required when csv-format is false.
TEST_F(FlexSubOptionTest, subOptionConfigUnknownCodeDisableCSVFormat) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    // Disable csv-format.
    sub_option->set("csv-format", Element::create(false));
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(109));
    auto smap = map[109];
    EXPECT_EQ(1, smap.count(222));
}

// Verify that the code must be a known sub-option when csv-format is true.
TEST_F(FlexSubOptionTest, subOptionConfigUnknownCodeEnableCSVFormat) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    // Enable csv-format.
    sub_option->set("csv-format", Element::create(true));
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("no known sub-option with code '222' in 'my-space' space",
              impl_->getErrMsg());
}

} // end of anonymous namespace
