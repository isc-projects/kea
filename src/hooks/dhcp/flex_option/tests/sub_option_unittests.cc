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

// multiple.

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

} // end of anonymous namespace
