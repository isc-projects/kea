// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible sub-option.

#include <config.h>
#include <flex_option.h>
#include <flex_option_log.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <eval/eval_context.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>

#include <tests/test_flex_option.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
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
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    EXPECT_TRUE(impl_->getOptionConfigMap().empty());
    EXPECT_TRUE(impl_->getSubOptionConfigMap().empty());
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

// Verify that a sub-option configuration must retrieve a space.
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
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    code = Element::create(254);
    sub_option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();
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
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    code = Element::create(65535);
    sub_option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();
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
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

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
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

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

// Verify that the name can be an user defined sub-option.
TEST_F(FlexSubOptionTest, subOptionConfigDefinedName) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-option", 222,
                                                 "my-space", "string"));
    defs.addItem(def);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

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
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(109));
    auto smap = map[109];
    EXPECT_EQ(1, smap.count(222));
}

// Verify that the name can be a last resort space defined sub-option.
TEST_F(FlexSubOptionTest, subOptionConfigLastResortName) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-option", 222,
                                                 VENDOR_ENCAPSULATED_OPTION_SPACE,
                                                 "string"));
    defs.addItem(def);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(DHO_VENDOR_ENCAPSULATED_OPTIONS));
    auto smap = map[DHO_VENDOR_ENCAPSULATED_OPTIONS];
    EXPECT_EQ(1, smap.count(222));
}

// Verify that the sub-option definition can be fetched from the last
// resort space.
TEST_F(FlexSubOptionTest, subOptionConfigLastResortCode) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    // Enable csv-format.
    sub_option->set("csv-format", Element::create(true));
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string msg = "no known sub-option with code '222' in '";
    msg += VENDOR_ENCAPSULATED_OPTION_SPACE;
    msg += "' space";
    EXPECT_EQ(msg, impl_->getErrMsg());

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-option", 222,
                                                 VENDOR_ENCAPSULATED_OPTION_SPACE,
                                                 "string"));
    defs.addItem(def);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();
    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(DHO_VENDOR_ENCAPSULATED_OPTIONS));
    auto smap = map[DHO_VENDOR_ENCAPSULATED_OPTIONS];
    EXPECT_EQ(1, smap.count(222));
}

// Verify that the name can be a vendor defined sub-option.
TEST_F(FlexSubOptionTest, subOptionConfigVendorName) {
    CfgMgr::instance().setFamily(AF_INET6);

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-option", 222,
                                                 "vendor-1234", "string"));
    defs.addItem(def);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("vendor-1234"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(D6O_VENDOR_OPTS));
    auto smap = map[D6O_VENDOR_OPTS];
    EXPECT_EQ(1, smap.count(222));
}

// Verify that the sub-option definition can be fetched from a custom
// vendor space.
TEST_F(FlexSubOptionTest, subOptionConfigVendorCode) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("vendor-1234"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    // Enable csv-format.
    sub_option->set("csv-format", Element::create(true));
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("no known sub-option with code '222' in 'vendor-1234' space",
              impl_->getErrMsg());

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-option", 222,
                                                 "vendor-1234", "string"));
    defs.addItem(def);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(D6O_VENDOR_OPTS));
    auto smap = map[D6O_VENDOR_OPTS];
    EXPECT_EQ(1, smap.count(222));
}

// Verify that the name can be a vendor standard sub-option.
TEST_F(FlexSubOptionTest, subOptionConfigDosSISName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    // VENDOR_ID_CABLE_LABS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("tftp-servers"));
    sub_option->set("name", name);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(DHO_VIVSO_SUBOPTIONS));
    auto smap = map[DHO_VIVSO_SUBOPTIONS];
    // DOCSIS3_V4_TFTP_SERVERS is 2
    EXPECT_EQ(1, smap.count(2));
}

// Verify that the sub-option definition can be fetched from a standard
// vendor space.
TEST_F(FlexSubOptionTest, subOptionConfigDosSISCode) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    // VENDOR_ID_CABLE_LABS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr sub_code = Element::create(DOCSIS3_V4_TFTP_SERVERS);
    sub_option->set("code", sub_code);
    // Enable csv-format.
    sub_option->set("csv-format", Element::create(true));
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(DHO_VIVSO_SUBOPTIONS));
    auto smap = map[DHO_VIVSO_SUBOPTIONS];
    // DOCSIS3_V4_TFTP_SERVERS is 2
    EXPECT_EQ(1, smap.count(2));
}

// Verify that the name must match the code.
TEST_F(FlexSubOptionTest, subOptionConfigCodeNameMismatch) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    // VENDOR_ID_CABLE_LABS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'ab'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("tftp-servers"));
    sub_option->set("name", name);
    // DOCSIS3_V4_TFTP_SERVERS is 2
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "sub-option 'tftp-servers' is defined as code: 2, ";
    expected += "not the specified code: 222";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that the csv-format must be a boolean.
TEST_F(FlexSubOptionTest, subOptionConfigBadCSVFormat) {
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
    ElementPtr csv_format = Element::create(123);
    sub_option->set("csv-format", csv_format);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'csv-format' must be a boolean: 123", impl_->getErrMsg());
}

// Verify that the container-add must be a boolean.
TEST_F(FlexSubOptionTest, subOptionConfigBadContainerAdd) {
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
    ElementPtr container_add = Element::create(123);
    sub_option->set("container-add", container_add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'container-add' must be a boolean: 123", impl_->getErrMsg());
}

// Verify that the container-remove must be a boolean.
TEST_F(FlexSubOptionTest, subOptionConfigBadContainerRemove) {
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
    ElementPtr container_remove = Element::create(123);
    sub_option->set("container-remove", container_remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'container-remove' must be a boolean: 123", impl_->getErrMsg());
}

// Verify that multiple sub-option actions are not accepted.
TEST_F(FlexSubOptionTest, subOptionConfigMultipleAction) {
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

    // Add it a second time.
    sub_options->add(sub_option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("sub-option 222 of option 109 was already specified",
              impl_->getErrMsg());
}

// Verify that the add value must be a string.
TEST_F(FlexSubOptionTest, subOptionConfigAddNotString) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr add = Element::create(true);
    sub_option->set("add", add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'add' must be a string: true", impl_->getErrMsg());
}

// Verify that the add value must not be empty.
TEST_F(FlexSubOptionTest, subOptionConfigEmptyAdd) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr add = Element::create(string());
    sub_option->set("add", add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'add' must not be empty", impl_->getErrMsg());
}

// Verify that the add value must parse.
TEST_F(FlexSubOptionTest, subOptionConfigBadAdd) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr add = Element::create(string("ifelse('a','b','c')"));
    sub_option->set("add", add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "can't parse add expression [ifelse('a','b','c')] ";
    expected += "error: <string>:1.11: syntax error, ";
    expected += "unexpected \",\", expecting == or +";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that the supersede value must be a string.
TEST_F(FlexSubOptionTest, subOptionConfigSupersedeNotString) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr supersede = Element::create(true);
    sub_option->set("supersede", supersede);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'supersede' must be a string: true", impl_->getErrMsg());
}

// Verify that the supersede value must not be empty.
TEST_F(FlexSubOptionTest, subOptionConfigEmptySupersede) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr supersede = Element::create(string());
    sub_option->set("supersede", supersede);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'supersede' must not be empty", impl_->getErrMsg());
}

// Verify that the supersede value must parse.
TEST_F(FlexSubOptionTest, subOptionConfigBadSupersede) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr supersede = Element::create(string("ifelse('a','b','c')"));
    sub_option->set("supersede", supersede);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "can't parse supersede expression [ifelse('a','b','c')] ";
    expected += "error: <string>:1.11: syntax error, ";
    expected += "unexpected \",\", expecting == or +";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that the remove value must be a string.
TEST_F(FlexSubOptionTest, subOptionConfigRemoveNotString) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr remove = Element::createMap();
    sub_option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'remove' must be a string: {  }", impl_->getErrMsg());
}

// Verify that the remove value must not be empty.
TEST_F(FlexSubOptionTest, subOptionConfigEmptyRemove) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr remove = Element::create(string());
    sub_option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'remove' must not be empty", impl_->getErrMsg());
}

// Verify that the remove value must parse.
TEST_F(FlexSubOptionTest, subOptionConfigBadRemove) {
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
    ElementPtr sub_code = Element::create(222);
    sub_option->set("code", sub_code);
    ElementPtr remove = Element::create(string("'abc'"));
    sub_option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "can't parse remove expression ['abc'] error: ";
    expected += "<string>:1.6: syntax error, unexpected end of file, ";
    expected += "expecting == or +";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that a complex example must parse.
TEST_F(FlexSubOptionTest, subOptionConfigComplex) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(109);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);

    ElementPtr sub_option1 = Element::createMap();
    sub_options->add(sub_option1);
    ElementPtr space = Element::create(string("my-space"));
    sub_option1->set("space", space);
    ElementPtr sub_code = Element::create(1);
    sub_option1->set("code", sub_code);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option1->set("add", add);

    ElementPtr sub_option2 = Element::createMap();
    sub_options->add(sub_option2);
    sub_option2->set("space", space);
    sub_code = Element::create(2);
    sub_option2->set("code", sub_code);
    ElementPtr supersede = Element::create(string("'def'"));
    sub_option2->set("supersede", supersede);
    sub_option2->set("container-add", Element::create(false));

    ElementPtr sub_option3 = Element::createMap();
    sub_options->add(sub_option3);
    sub_option3->set("space", space);
    sub_code = Element::create(3);
    sub_option3->set("code", sub_code);
    ElementPtr remove = Element::create(string("'a' == 'b'"));
    sub_option3->set("remove", remove);

    ElementPtr sub_option4 = Element::createMap();
    sub_options->add(sub_option4);
    sub_option4->set("space", space);
    sub_code = Element::create(4);
    sub_option4->set("code", sub_code);
    remove = Element::create(string("'b' == 'a'"));
    sub_option4->set("remove", remove);
    sub_option4->set("container-remove", Element::create(false));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(109));
    auto smap = map[109];
    FlexOptionImpl::SubOptionConfigPtr sub_cfg;
    ASSERT_NO_THROW(sub_cfg = smap.at(1));
    ASSERT_TRUE(sub_cfg);
    EXPECT_EQ(1, sub_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::ADD, sub_cfg->getAction());
    EXPECT_EQ(FlexOptionImpl::ADD, sub_cfg->getContainerAction());
    EXPECT_EQ("'abc'", sub_cfg->getText());
    EXPECT_EQ(109, sub_cfg->getContainerCode());

    ASSERT_NO_THROW(sub_cfg = smap.at(2));
    ASSERT_TRUE(sub_cfg);
    EXPECT_EQ(2, sub_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::SUPERSEDE, sub_cfg->getAction());
    EXPECT_EQ(FlexOptionImpl::NONE, sub_cfg->getContainerAction());
    EXPECT_EQ("'def'", sub_cfg->getText());
    EXPECT_EQ(109, sub_cfg->getContainerCode());

    ASSERT_NO_THROW(sub_cfg = smap.at(3));
    ASSERT_TRUE(sub_cfg);
    EXPECT_EQ(3, sub_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::REMOVE, sub_cfg->getAction());
    EXPECT_EQ(FlexOptionImpl::REMOVE, sub_cfg->getContainerAction());
    EXPECT_EQ("'a' == 'b'", sub_cfg->getText());
    EXPECT_EQ(109, sub_cfg->getContainerCode());

    ASSERT_NO_THROW(sub_cfg = smap.at(4));
    ASSERT_TRUE(sub_cfg);
    EXPECT_EQ(4, sub_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::REMOVE, sub_cfg->getAction());
    EXPECT_EQ(FlexOptionImpl::NONE, sub_cfg->getContainerAction());
    EXPECT_EQ("'b' == 'a'", sub_cfg->getText());
    EXPECT_EQ(109, sub_cfg->getContainerCode());
}

// Empty sub-option config list doing nothing is the same as empty option list.

// Verify that NONE action really does nothing.
TEST_F(FlexSubOptionTest, subProcessNone) {
    auto rai_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                         DHO_DHCP_AGENT_OPTIONS);
    FlexOptionImpl::OptionConfigPtr
        opt_cfg(new FlexOptionImpl::OptionConfig(DHO_DHCP_AGENT_OPTIONS,
                                                 rai_def));
    // RAI_OPTION_AGENT_CIRCUIT_ID is 1 but has no definition.
    OptionDefinitionPtr def;
    FlexOptionImpl::SubOptionConfigPtr
        sub_cfg(new FlexOptionImpl::SubOptionConfig(1, def, opt_cfg));
    auto& map = impl_->getMutableSubOptionConfigMap();
    auto& smap = map[DHO_DHCP_AGENT_OPTIONS];
    smap[1] = sub_cfg;

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
}

// Verify that ADD action adds the specified sub-option in csv format.
TEST_F(FlexSubOptionTest, subProcessAddEnableCSVFormat) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "fqdn", true));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'example.com'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("csv-format", Element::create(true));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    // The fqdn array is the most complex encoding of one element...
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(13, buffer.size());
    EXPECT_EQ(7, buffer[0]);
    EXPECT_EQ(0, memcmp(&buffer[1], "example", 7));
    EXPECT_EQ(3, buffer[8]);
    EXPECT_EQ(0, memcmp(&buffer[9], "com", 3));
    EXPECT_EQ(0, buffer[12]);
}

// Verify that ADD action does nothing when the container does not exist and
// container-add is false.
TEST_F(FlexSubOptionTest, subProcessAddNoContainer) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("container-add", Element::create(false));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(222));
}

// Verify that ADD action adds the specified sub-option in raw format.
TEST_F(FlexSubOptionTest, subProcessAddDisableCSVFormat) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "fqdn", true));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("0x076578616d706c6503636f6d00"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    // csv-format is disabled by default.

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(13, buffer.size());
    EXPECT_EQ(7, buffer[0]);
    EXPECT_EQ(0, memcmp(&buffer[1], "example", 7));
    EXPECT_EQ(3, buffer[8]);
    EXPECT_EQ(0, memcmp(&buffer[9], "com", 3));
    EXPECT_EQ(0, buffer[12]);
}

// Verify that ADD action adds the specified sub-option in an already
// existing container option.
TEST_F(FlexSubOptionTest, subProcessAdd) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    // Only one option with code 222.
    EXPECT_EQ(1, response->options_.count(222));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));

    // Only one sub-option.
    auto const& opts = opt->getOptions();
    EXPECT_EQ(1, opts.size());
}

// Verify that ADD action does not add an already existing sub-option.
TEST_F(FlexSubOptionTest, subProcessAddExisting) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));
    OptionStringPtr str(new OptionString(Option::V4, 1, "xyzt"));
    container->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "xyzt", 4));

    // Only one sub-option.
    auto const& opts = opt->getOptions();
    EXPECT_EQ(1, opts.size());
}

// Verify that ADD action does not add an empty value.
TEST_F(FlexSubOptionTest, subProcessAddEmpty) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("''"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(222));
}

// Verify that ADD action can handle vendor-encapsulated-options 43.
TEST_F(FlexSubOptionTest, subProcessAdd43) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  VENDOR_ENCAPSULATED_OPTION_SPACE,
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'foobar'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    EXPECT_EQ(DHO_VENDOR_ENCAPSULATED_OPTIONS, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that ADD action can handle DocSIS Vivso.
TEST_F(FlexSubOptionTest, subProcessAddDocSISVIVSO) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'10.1.2.3'"));
    sub_option->set("add", add);
    // DocSIS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("tftp-servers"));
    sub_option->set("name", name);
    sub_option->set("csv-format", Element::create(true));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(VENDOR_ID_CABLE_LABS, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(DOCSIS3_V4_TFTP_SERVERS);
    ASSERT_TRUE(sub);
    Option4AddrLstPtr addr = boost::dynamic_pointer_cast<Option4AddrLst>(sub);
    ASSERT_TRUE(addr);
    auto const& addrs = addr->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("10.1.2.3", addrs[0].toText());
}

// Verify that ADD action can handle DocSIS vendor-opts.
TEST_F(FlexSubOptionTest, subProcessAddDocSISVendorOps) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'foobar'"));
    sub_option->set("add", add);
    // DocSIS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    code = Element::create(DOCSIS3_V6_VENDOR_NAME);
    sub_option->set("code", code);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    OptionPtr opt = response->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(VENDOR_ID_CABLE_LABS, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(DOCSIS3_V6_VENDOR_NAME);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that ADD action can handle the Vivso option.
TEST_F(FlexSubOptionTest, subProcessAddVivso) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'foobar'"));
    sub_option->set("add", add);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(123456, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that ADD action can handle the Vivso option with vendor mismatch.
TEST_F(FlexSubOptionTest, subProcessAddVivsoMismatch) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'foobar'"));
    sub_option->set("add", add);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionVendorPtr vendor(new OptionVendor(Option::V4, 67890));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V4, 2, "xyzt"));
    vendor->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);
    vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(67890, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    EXPECT_FALSE(sub);
    sub = vendor->getOption(2);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "xyzt", 4));
}

// Verify that ADD action can handle the vendor-opts option.
TEST_F(FlexSubOptionTest, subProcessAddVendorOpts) {
    CfgMgr::instance().setFamily(AF_INET6);

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'foobar'"));
    sub_option->set("add", add);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    OptionPtr opt = response->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(123456, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that ADD action can handle the vendor-opts option with vendor mismatch.
TEST_F(FlexSubOptionTest, subProcessAddVendorOptsMismatch) {
    CfgMgr::instance().setFamily(AF_INET6);

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr add = Element::create(string("'foobar'"));
    sub_option->set("add", add);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    OptionVendorPtr vendor(new OptionVendor(Option::V6, 67890));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V6, 2, "xyzt"));
    vendor->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(67890, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    EXPECT_FALSE(sub);
    sub = vendor->getOption(2);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "xyzt", 4));
}

// Verify that SUPERSEDE action adds the specified sub-option in csv format.
TEST_F(FlexSubOptionTest, subProcessSupersedeEnableCSVFormat) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "fqdn", true));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr supersede = Element::create(string("'example.com'"));
    sub_option->set("supersede", supersede);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("csv-format", Element::create(true));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    // The fqdn array is the most complex encoding of one element...
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(13, buffer.size());
    EXPECT_EQ(7, buffer[0]);
    EXPECT_EQ(0, memcmp(&buffer[1], "example", 7));
    EXPECT_EQ(3, buffer[8]);
    EXPECT_EQ(0, memcmp(&buffer[9], "com", 3));
    EXPECT_EQ(0, buffer[12]);
}

// Verify that SUPERSEDE action does nothing when the container does not exist
// and container-add is false.
TEST_F(FlexSubOptionTest, subProcessSupersedeNoContainer) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr supersede = Element::create(string("'abc'"));
    sub_option->set("supersede", supersede);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("container-add", Element::create(false));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(222));
}

// Verify that SUPERSEDE action adds the specified sub-option in raw format.
TEST_F(FlexSubOptionTest, subProcessSupersedeDisableCSVFormat) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "fqdn", true));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr supersede = Element::create(string("0x076578616d706c6503636f6d00"));
    sub_option->set("supersede", supersede);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    // csv-format is disabled by default.

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(13, buffer.size());
    EXPECT_EQ(7, buffer[0]);
    EXPECT_EQ(0, memcmp(&buffer[1], "example", 7));
    EXPECT_EQ(3, buffer[8]);
    EXPECT_EQ(0, memcmp(&buffer[9], "com", 3));
    EXPECT_EQ(0, buffer[12]);
}

// Verify that SUPERSEDE action adds the specified sub-option in an already
// existing container option.
TEST_F(FlexSubOptionTest, subProcessSupersede) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr supersede = Element::create(string("'abc'"));
    sub_option->set("supersede", supersede);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    // Only one option with code 222.
    EXPECT_EQ(1, response->options_.count(222));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));

    // Only one sub-option.
    auto const& opts = opt->getOptions();
    EXPECT_EQ(1, opts.size());
}

// Verify that SUPERSEDE action replaces an already existing sub-option.
TEST_F(FlexSubOptionTest, subProcessSupersedeExisting) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr supersede = Element::create(string("'abc'"));
    sub_option->set("supersede", supersede);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));
    OptionStringPtr str(new OptionString(Option::V4, 1, "xyzt"));
    container->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    // Only one option with code 222.
    EXPECT_EQ(1, response->options_.count(222));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));

    // Only one sub-option.
    auto const& opts = opt->getOptions();
    EXPECT_EQ(1, opts.size());
}

// Verify that SUPERSEDE action does not add an empty value.
TEST_F(FlexSubOptionTest, subProcessSupersedeEmpty) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr supersede = Element::create(string("''"));
    sub_option->set("supersede", supersede);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(222));
}

// Verify that SUPERSEDE action can handle vendor-encapsulated-options 43.
TEST_F(FlexSubOptionTest, subProcessSupersede43) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  VENDOR_ENCAPSULATED_OPTION_SPACE,
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr supersede = Element::create(string("'foobar'"));
    sub_option->set("supersede", supersede);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    EXPECT_EQ(DHO_VENDOR_ENCAPSULATED_OPTIONS, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that SUPERSEDE action can handle DocSIS Vivso.
TEST_F(FlexSubOptionTest, subProcessSupersedeDocSISVIVSO) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr supersede = Element::create(string("10.1.2.3"));
    sub_option->set("supersede", supersede);
    // DocSIS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("tftp-servers"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(VENDOR_ID_CABLE_LABS, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(DOCSIS3_V4_TFTP_SERVERS);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    uint8_t expected[] = { 10, 1, 2, 3 };
    EXPECT_EQ(0, memcmp(&buffer[0], expected, 4));
}

// Verify that SUPERSEDE action can handle DocSIS vendor-opts.
TEST_F(FlexSubOptionTest, subProcessSupersedeDocSISVendorOps) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr supersede = Element::create(string("'foobar'"));
    sub_option->set("supersede", supersede);
    // DocSIS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    code = Element::create(DOCSIS3_V6_VENDOR_NAME);
    sub_option->set("code", code);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    OptionPtr opt = response->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(VENDOR_ID_CABLE_LABS, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(DOCSIS3_V6_VENDOR_NAME);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that SUPERSEDE action can handle the Vivso option.
TEST_F(FlexSubOptionTest, subProcessSupersedeVivso) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr supersede = Element::create(string("'foobar'"));
    sub_option->set("supersede", supersede);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(123456, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that SUPERSEDE action can handle the Vivso option with vendor mismatch.
TEST_F(FlexSubOptionTest, subProcessSupersedeVivsoMismatch) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr supersede = Element::create(string("'foobar'"));
    sub_option->set("supersede", supersede);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionVendorPtr vendor(new OptionVendor(Option::V4, 67890));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V4, 2, "xyzt"));
    vendor->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);
    vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(67890, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    EXPECT_FALSE(sub);
    sub = vendor->getOption(2);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "xyzt", 4));
}

// Verify that SUPERSEDE action can handle the vendor-opts option.
TEST_F(FlexSubOptionTest, subProcessSupersedeVendorOpts) {
    CfgMgr::instance().setFamily(AF_INET6);

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr supersede = Element::create(string("'foobar'"));
    sub_option->set("supersede", supersede);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    OptionPtr opt = response->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(123456, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(6, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foobar", 6));
}

// Verify that SUPERSEDE action can handle the vendor-opts option with vendor mismatch.
TEST_F(FlexSubOptionTest, subProcessSupersedeVendorOptsMismatch) {
    CfgMgr::instance().setFamily(AF_INET6);

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr supersede = Element::create(string("'foobar'"));
    sub_option->set("supersede", supersede);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    OptionVendorPtr vendor(new OptionVendor(Option::V6, 67890));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V6, 2, "xyzt"));
    vendor->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(67890, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    EXPECT_FALSE(sub);
    sub = vendor->getOption(2);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "xyzt", 4));
}

// Verify that REMOVE action removes an already existing sub-option.
TEST_F(FlexSubOptionTest, subProcessRemove) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));
    OptionStringPtr str(new OptionString(Option::V4, 1, "xyzt"));
    container->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(222));
}

// Verify that REMOVE action removes an already existing sub-option but
// leaves the container option when container-remove is false.
TEST_F(FlexSubOptionTest, subProcessRemoveLeaveContainer) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("container-remove", Element::create(false));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    string response_txt = response->toText();
    EXPECT_TRUE(response->getOption(222));
    OptionStringPtr str(new OptionString(Option::V4, 1, "xyzt"));
    container->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_FALSE(opt->getOption(1));
    EXPECT_TRUE(opt->getOptions().empty());
}

// Verify that REMOVE action removes an already existing sub-option but
// leaves the container option when it is not empty.
TEST_F(FlexSubOptionTest, subProcessRemoveContainerNotEmpty) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 2, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));
    OptionStringPtr str(new OptionString(Option::V4, 1, "abc"));
    container->addOption(str);
    string response_txt = response->toText();
    str.reset(new OptionString(Option::V4, 2, "xyzt"));
    container->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_FALSE(opt->getOption(2));
    EXPECT_EQ(1, opt->getOptions().size());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

// Verify that REMOVE action does not removes the container option when the
// sub-option does not exist.
TEST_F(FlexSubOptionTest, subProcessRemoveContainerNoSubOption) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("container-remove", Element::create(false));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_TRUE(response->getOption(222));
}

// Verify that REMOVE action does nothing when the expression evaluates to false.
TEST_F(FlexSubOptionTest, subProcessRemoveFalse) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr remove = Element::create(string("'abc' == 'xyz'"));
    sub_option->set("remove", remove);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionPtr container(new Option(Option::V4, 222));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(222));
    OptionStringPtr str(new OptionString(Option::V4, 1, "abc"));
    container->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

// Verify that REMOVE action can handle vendor-encapsulated-options 43.
TEST_F(FlexSubOptionTest, subProcessRemove43) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  VENDOR_ENCAPSULATED_OPTION_SPACE,
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VENDOR_ENCAPSULATED_OPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    OptionPtr container(new Option(Option::V4, DHO_VENDOR_ENCAPSULATED_OPTIONS));
    response->addOption(container);
    EXPECT_TRUE(response->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS));
    OptionStringPtr str(new OptionString(Option::V4, 1, "abc"));
    container->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(DHO_VENDOR_ENCAPSULATED_OPTIONS));
}

// Verify that REMOVE action can handle DocSIS Vivso.
TEST_F(FlexSubOptionTest, subProcessRemoveDocSISVIVSO) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr remove = Element::create(string("member('ALL')"));
    sub_option->set("remove", remove);
    // DocSIS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("tftp-servers"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->addClass("ALL");
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    OptionVendorPtr vendor(new OptionVendor(Option::V4, 4491));
    response->addOption(vendor);
    Option4AddrLstPtr tftp(new Option4AddrLst(DOCSIS3_V4_TFTP_SERVERS,
                                              IOAddress("10.1.2.3")));
    vendor->addOption(tftp);

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(DHO_VIVSO_SUBOPTIONS));
}

// Verify that REMOVE action can handle DocSIS vendor-opts.
TEST_F(FlexSubOptionTest, subProcessRemoveDocSISVendorOps) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    // DocSIS is 4491
    ElementPtr space = Element::create(string("vendor-4491"));
    sub_option->set("space", space);
    code = Element::create(DOCSIS3_V6_VENDOR_NAME);
    sub_option->set("code", code);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    string response_txt = response->toText();
    OptionVendorPtr vendor(new OptionVendor(Option::V6, 4491));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V6, DOCSIS3_V6_VENDOR_NAME,
                                         "foobar"));
    vendor->addOption(str);
    EXPECT_TRUE(response->getOption(D6O_VENDOR_OPTS));

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(D6O_VENDOR_OPTS));
}

// Verify that REMOVE action can handle the Vivso option.
TEST_F(FlexSubOptionTest, subProcessRemoveVivso) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    OptionVendorPtr vendor(new OptionVendor(Option::V4, 123456));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V4, 1, "foobar"));
    vendor->addOption(str);
    EXPECT_TRUE(response->getOption(DHO_VIVSO_SUBOPTIONS));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(DHO_VIVSO_SUBOPTIONS));
}

// Verify that REMOVE action can handle the Vivso option with vendor mismatch.
TEST_F(FlexSubOptionTest, subProcessRemoveVivsoMismatch) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_VIVSO_SUBOPTIONS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr remove = Element::create(string("member('ALL')"));
    sub_option->set("remove", remove);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->addClass("ALL");
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionVendorPtr vendor(new OptionVendor(Option::V4, 67890));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V4, 2, "xyzt"));
    vendor->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(DHO_VIVSO_SUBOPTIONS);
    ASSERT_TRUE(opt);
    vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(67890, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    EXPECT_FALSE(sub);
    sub = vendor->getOption(2);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "xyzt", 4));
}

// Verify that REMOVE action can handle the vendor-opts option.
TEST_F(FlexSubOptionTest, subProcessRemoveVendorOpts) {
    CfgMgr::instance().setFamily(AF_INET6);

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    string response_txt = response->toText();
    OptionVendorPtr vendor(new OptionVendor(Option::V6, 123456));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V6, 1, "foobar"));
    vendor->addOption(str);
    EXPECT_TRUE(response->getOption(D6O_VENDOR_OPTS));

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(D6O_VENDOR_OPTS));
}

// Verify that REMOVE action can handle the vendor-opts option with vendor mismatch.
TEST_F(FlexSubOptionTest, subProcessRemoveVendorOptsMismatch) {
    CfgMgr::instance().setFamily(AF_INET6);

    OptionDefSpaceContainer defs;
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1,
                                                  "vendor-123456", "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_VENDOR_OPTS);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    sub_option->set("remove", remove);
    ElementPtr space = Element::create(string("vendor-123456"));
    sub_option->set("space", space);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    OptionVendorPtr vendor(new OptionVendor(Option::V6, 67890));
    response->addOption(vendor);
    OptionStringPtr str(new OptionString(Option::V6, 2, "xyzt"));
    vendor->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
    OptionPtr opt = response->getOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    EXPECT_EQ(67890, vendor->getVendorId());
    OptionPtr sub = vendor->getOption(1);
    EXPECT_FALSE(sub);
    sub = vendor->getOption(2);
    ASSERT_TRUE(sub);
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(4, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "xyzt", 4));
}

// Verify that the client class must be a string.
TEST_F(FlexSubOptionTest, subOptionConfigBadClass) {
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
    sub_option->set("client-class", Element::create(true));
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'client-class' must be a string: true", impl_->getErrMsg());
}

// Verify that a valid client class is accepted.
TEST_F(FlexSubOptionTest, subOptionConfigGuardValid) {
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
    sub_option->set("client-class", Element::create(string("foobar")));
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    auto map = impl_->getSubOptionConfigMap();
    EXPECT_EQ(1, map.count(109));
    auto smap = map[109];
    FlexOptionImpl::SubOptionConfigPtr sub_cfg;
    ASSERT_NO_THROW(sub_cfg = smap.at(222));
    ASSERT_TRUE(sub_cfg);
    EXPECT_EQ(222, sub_cfg->getCode());
    EXPECT_EQ(109, sub_cfg->getContainerCode());
    EXPECT_EQ("foobar", sub_cfg->getClass());
}

// Verify that a guarded action is skipped when query does not belong to the
// client class of the container option.
TEST_F(FlexSubOptionTest, subOptionConfigGuardOptiondNoMatch) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    option->set("client-class", Element::create(string("foobar")));
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(222));
}

// Verify that a guarded action is applied when query belongs to the class
// class of the container option.
TEST_F(FlexSubOptionTest, subOptionConfigGuardOptiondMatch) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    option->set("client-class", Element::create(string("foobar")));
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->addClass("foobar");
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

// Verify that a guarded action is skipped when query does not belong to the
// client class of the sub-option.
TEST_F(FlexSubOptionTest, subOptionConfigGuardSubOptiondNoMatch) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("client-class", Element::create(string("foobar")));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(222));
}

// Verify that a guarded action is applied when query belongs to the class
// class of the sub-option.
TEST_F(FlexSubOptionTest, subOptionConfigGuardSubOptiondMatch) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-container", 222,
                                                 DHCP4_OPTION_SPACE, "empty",
                                                 "my-space"));
    defs.addItem(def);
    OptionDefinitionPtr sdef(new OptionDefinition("my-option", 1, "my-space",
                                                  "string"));
    defs.addItem(sdef);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(222);
    option->set("code", code);
    ElementPtr sub_options = Element::createList();
    option->set("sub-options", sub_options);
    ElementPtr sub_option = Element::createMap();
    sub_options->add(sub_option);
    ElementPtr space = Element::create(string("my-space"));
    sub_option->set("space", space);
    ElementPtr add = Element::create(string("'abc'"));
    sub_option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    sub_option->set("name", name);
    sub_option->set("client-class", Element::create(string("foobar")));

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty()) << impl_->getErrMsg();

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->addClass("foobar");
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(222));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(222);
    ASSERT_TRUE(opt);
    EXPECT_EQ(222, opt->getType());
    OptionPtr sub = opt->getOption(1);
    ASSERT_TRUE(sub);
    EXPECT_EQ(1, sub->getType());
    const OptionBuffer& buffer = sub->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

} // end of anonymous namespace
