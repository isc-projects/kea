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
    ElementPtr remove = Element::create(true);
    sub_option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'remove' must be a string: true", impl_->getErrMsg());
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
    ElementPtr remove = Element::create(string("ifelse('a','b','c')"));
    sub_option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "can't parse remove expression [ifelse('a','b','c')] ";
    expected += "error: <string>:1.11: syntax error, ";
    expected += "unexpected \",\", expecting == or +";
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

    ElementPtr sub_option3 = Element::createMap();
    sub_options->add(sub_option3);
    sub_option3->set("space", space);
    sub_code = Element::create(3);
    sub_option3->set("code", sub_code);
    ElementPtr remove = Element::create(string("'a' == 'b'"));
    sub_option3->set("remove", remove);

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
    EXPECT_EQ("'abc'", sub_cfg->getText());
    EXPECT_EQ(109, sub_cfg->getContainerCode());

    ASSERT_NO_THROW(sub_cfg = smap.at(2));
    ASSERT_TRUE(sub_cfg);
    EXPECT_EQ(2, sub_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::SUPERSEDE, sub_cfg->getAction());
    EXPECT_EQ("'def'", sub_cfg->getText());
    EXPECT_EQ(109, sub_cfg->getContainerCode());

    ASSERT_NO_THROW(sub_cfg = smap.at(3));
    ASSERT_TRUE(sub_cfg);
    EXPECT_EQ(3, sub_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::REMOVE, sub_cfg->getAction());
    EXPECT_EQ("'a' == 'b'", sub_cfg->getText());
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

// Verify that ADD action does not when the container does not exist and
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
    EXPECT_EQ(43, opt->getType());
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
TEST_F(FlexSubOptionTest, subProcessAddvendorOpts) {
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
TEST_F(FlexSubOptionTest, subProcessAddvendorOptsMismatch) {
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

} // end of anonymous namespace
// TEST_F(FlexSubOptionTest, subP
