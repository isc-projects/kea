// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible option.

#include <config.h>
#include <flex_option.h>
#include <flex_option_log.h>
#include <dhcp/option_string.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <eval/eval_context.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::hooks;
using namespace isc::flex_option;

namespace {

/// @brief Test class derived from FlexOptionImpl
class TestFlexOptionImpl : public FlexOptionImpl {
public:
    /// Export getMutableOptionConfigMap.
    using FlexOptionImpl::getMutableOptionConfigMap;

    /// @brief Configure clone which records the error.
    ///
    /// @param options The element with option config list.
    void testConfigure(ConstElementPtr options) {
        err_msg_.clear();
        try {
            configure(options);
        } catch (const std::exception& ex) {
            err_msg_ = string(ex.what());
            throw;
        }
    }

    /// @brief Get the last error message.
    ///
    /// @return The last error message.
    const string& getErrMsg() const {
        return (err_msg_);
    }

private:
    /// @brief Last error message.
    string err_msg_;
};

/// @brief The type of shared pointers to TestFlexOptionImpl
typedef boost::shared_ptr<TestFlexOptionImpl> TestFlexOptionImplPtr;

/// @brief Test fixture for testing the Flex Option library.
class FlexOptionTest : public ::testing::Test {
public:
    /// @brief Constructor.
    FlexOptionTest() {
        impl_.reset(new TestFlexOptionImpl());
        CfgMgr::instance().setFamily(AF_INET);
    }

    /// @brief Destructor.
    virtual ~FlexOptionTest() {
        CfgMgr::instance().setFamily(AF_INET);
        impl_.reset();
    }

    /// @brief Flex Option implementation.
    TestFlexOptionImplPtr impl_;
};

// Verify that the configuration must exist.
TEST_F(FlexOptionTest, noConfig) {
    ElementPtr options;
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'options' parameter is mandatory", impl_->getErrMsg());
}

// Verify that the configuration must be a list.
TEST_F(FlexOptionTest, configNotList) {
    ElementPtr options = Element::createMap();
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'options' parameter must be a list", impl_->getErrMsg());
}

// Verify that the configuration can be the empty list.
TEST_F(FlexOptionTest, configEmpty) {
    ElementPtr options = Element::createList();
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());
}

// Verify that an option configuration must exist.
TEST_F(FlexOptionTest, noOptionConfig) {
    ElementPtr options = Element::createList();
    ElementPtr option;
    options->add(option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("null option element", impl_->getErrMsg());
}

// Verify that an option configuration must be a map.
TEST_F(FlexOptionTest, optionConfigNotMap) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createList();
    options->add(option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("option element is not a map", impl_->getErrMsg());
}

// Verify that an option configuration must have code or name.
TEST_F(FlexOptionTest, optionConfigNoCodeName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    ostringstream errmsg;
    errmsg << "'code' or 'name' must be specified: " << option->str();
    EXPECT_EQ(errmsg.str(), impl_->getErrMsg());
}

// Verify that the v4 option code must be in [1..254].
TEST_F(FlexOptionTest, optionConfigBadCode4) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr code = Element::create(false);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'code' must be an integer: false", impl_->getErrMsg());

    code = Element::create(-1);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value -1 not in [0..255]", impl_->getErrMsg());

    code = Element::create(DHO_PAD);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("invalid 'code' value 0: reserved for PAD", impl_->getErrMsg());

    code = Element::create(DHO_END);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("invalid 'code' value 255: reserved for END", impl_->getErrMsg());

    code = Element::create(256);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value 256 not in [0..255]", impl_->getErrMsg());

    code = Element::create(1);
    option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    code = Element::create(254);
    option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());
}

// Verify that the v6 option code must be in [1..65535].
TEST_F(FlexOptionTest, optionConfigBadCode6) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr code = Element::create(false);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'code' must be an integer: false", impl_->getErrMsg());

    code = Element::create(-1);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value -1 not in [0..65535]", impl_->getErrMsg());

    code = Element::create(0);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("invalid 'code' value 0: reserved", impl_->getErrMsg());

    code = Element::create(65536);
    option->set("code", code);
    EXPECT_THROW(impl_->testConfigure(options), OutOfRange);
    EXPECT_EQ("invalid 'code' value 65536 not in [0..65535]", impl_->getErrMsg());

    code = Element::create(1);
    option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    code = Element::create(65535);
    option->set("code", code);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());
}

// Verify that the name must be a string.
TEST_F(FlexOptionTest, optionConfigBadName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr name = Element::create(true);
    option->set("name", name);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'name' must be a string: true", impl_->getErrMsg());
}

// Verify that the name must not be empty.
TEST_F(FlexOptionTest, optionConfigEmptyName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr name = Element::create(string());
    option->set("name",name);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'name' must not be empty", impl_->getErrMsg());
}

// Verify that the name must be a known option.
TEST_F(FlexOptionTest, optionConfigUnknownName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr name = Element::create(string("foobar"));
    option->set("name",name);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("no known 'foobar' option in 'dhcp4' space", impl_->getErrMsg());
}

// Verify that the name can be a standard option.
TEST_F(FlexOptionTest, optionConfigStandardName) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr name = Element::create(string("host-name"));
    option->set("name", name);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    EXPECT_EQ(1, map.count(DHO_HOST_NAME));
}

// Verify that the name can be an user defined option.
TEST_F(FlexOptionTest, optionConfigDefinedName) {
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("my-option", 222, "string"));
    defs.addItem(def, DHCP4_OPTION_SPACE);
    EXPECT_NO_THROW(LibDHCP::setRuntimeOptionDefs(defs));

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr name = Element::create(string("my-option"));
    option->set("name", name);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    EXPECT_EQ(1, map.count(222));
}

// Last resort is only option 43...

// Verify that the name must match the code.
TEST_F(FlexOptionTest, optionConfigCodeNameMismatch) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr code = Element::create(DHO_HOST_NAME + 1);
    option->set("code", code);
    ElementPtr name = Element::create(string("host-name"));
    option->set("name", name);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "option 'host-name' is defined as code: 12, ";
    expected += "not the specified code: 13";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that an option can be configured only once.
TEST_F(FlexOptionTest, optionConfigTwice) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr add = Element::create(string("'ab'"));
    option->set("add", add);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);

    options->add(option);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("option 12 was already specified", impl_->getErrMsg());
}

// Verify that the add value must be a string.
TEST_F(FlexOptionTest, optionConfigAddNotString) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr add = Element::create(true);
    option->set("add", add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'add' must be a string: true", impl_->getErrMsg());
}

// Verify that the add value must not be empty.
TEST_F(FlexOptionTest, optionConfigEmptyAdd) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr add = Element::create(string());
    option->set("add", add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'add' must not be empty", impl_->getErrMsg());
}

// Verify that the add value must parse.
TEST_F(FlexOptionTest, optionConfigBadAdd) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr add = Element::create(string("ifelse('a','b','c')"));
    option->set("add", add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "can't parse add expression [ifelse('a','b','c')] ";
    expected += "error: <string>:1.11: syntax error, ";
    expected += "unexpected \",\", expecting ==";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that a valid v4 add value is accepted.
TEST_F(FlexOptionTest, optionConfigAdd4) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr add = Element::create(string("'abc'"));
    option->set("add", add);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    FlexOptionImpl::OptionConfigPtr opt_cfg;
    ASSERT_NO_THROW(opt_cfg = map.at(DHO_HOST_NAME));
    ASSERT_TRUE(opt_cfg);
    EXPECT_EQ(DHO_HOST_NAME, opt_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::ADD, opt_cfg->getAction());
    EXPECT_EQ("'abc'", opt_cfg->getText());

    ExpressionPtr expr = opt_cfg->getExpr();
    ASSERT_TRUE(expr);
    ASSERT_EQ(1, expr->size());
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
    ValueStack values;
    EXPECT_NO_THROW(expr->at(0)->evaluate(*pkt4, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("abc", values.top());
}

// Verify that a valid v6 add value is accepted.
TEST_F(FlexOptionTest, optionConfigAdd6) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr add = Element::create(string("'abc'"));
    option->set("add", add);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    FlexOptionImpl::OptionConfigPtr opt_cfg;
    ASSERT_NO_THROW(opt_cfg = map.at(D6O_BOOTFILE_URL));
    ASSERT_TRUE(opt_cfg);
    EXPECT_EQ(D6O_BOOTFILE_URL, opt_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::ADD, opt_cfg->getAction());
    EXPECT_EQ("'abc'", opt_cfg->getText());

    ExpressionPtr expr = opt_cfg->getExpr();
    ASSERT_TRUE(expr);
    ASSERT_EQ(1, expr->size());
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, 12345));
    ValueStack values;
    EXPECT_NO_THROW(expr->at(0)->evaluate(*pkt6, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("abc", values.top());
}

// Verify that the supersede value must be a string.
TEST_F(FlexOptionTest, optionConfigSupersedeNotString) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr supersede = Element::create(123);
    option->set("supersede", supersede);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'supersede' must be a string: 123", impl_->getErrMsg());
}

// Verify that the supersede value must not be empty.
TEST_F(FlexOptionTest, optionConfigEmptySupersede) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr supersede = Element::create(string());
    option->set("supersede", supersede);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'supersede' must not be empty", impl_->getErrMsg());
}

// Verify that the supersede value must parse.
TEST_F(FlexOptionTest, optionConfigBadSupersede) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr supersede = Element::create(string("ifelse('a','b','c')"));
    option->set("supersede", supersede);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "can't parse supersede expression [ifelse('a','b','c')] ";
    expected += "error: <string>:1.11: syntax error, ";
    expected += "unexpected \",\", expecting ==";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that a valid v4 supersede value is accepted.
TEST_F(FlexOptionTest, optionConfigSupersede4) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr supersede = Element::create(string("'abc'"));
    option->set("supersede", supersede);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    FlexOptionImpl::OptionConfigPtr opt_cfg;
    ASSERT_NO_THROW(opt_cfg = map.at(DHO_HOST_NAME));
    ASSERT_TRUE(opt_cfg);
    EXPECT_EQ(DHO_HOST_NAME, opt_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::SUPERSEDE, opt_cfg->getAction());
    EXPECT_EQ("'abc'", opt_cfg->getText());

    ExpressionPtr expr = opt_cfg->getExpr();
    ASSERT_TRUE(expr);
    ASSERT_EQ(1, expr->size());
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
    ValueStack values;
    EXPECT_NO_THROW(expr->at(0)->evaluate(*pkt4, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("abc", values.top());
}

// Verify that a valid v6 supersede value is accepted.
TEST_F(FlexOptionTest, optionConfigSupersede6) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr supersede = Element::create(string("'abc'"));
    option->set("supersede", supersede);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    FlexOptionImpl::OptionConfigPtr opt_cfg;
    ASSERT_NO_THROW(opt_cfg = map.at(D6O_BOOTFILE_URL));
    ASSERT_TRUE(opt_cfg);
    EXPECT_EQ(D6O_BOOTFILE_URL, opt_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::SUPERSEDE, opt_cfg->getAction());
    EXPECT_EQ("'abc'", opt_cfg->getText());

    ExpressionPtr expr = opt_cfg->getExpr();
    ASSERT_TRUE(expr);
    ASSERT_EQ(1, expr->size());
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, 12345));
    ValueStack values;
    EXPECT_NO_THROW(expr->at(0)->evaluate(*pkt6, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("abc", values.top());
}

// Verify that the remove value must be a string.
TEST_F(FlexOptionTest, optionConfigRemoveNotString) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr remove = Element::createMap();
    option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'remove' must be a string: {  }", impl_->getErrMsg());
}

// Verify that the remove value must not be empty.
TEST_F(FlexOptionTest, optionConfigEmptyRemove) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr remove = Element::create(string());
    option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'remove' must not be empty", impl_->getErrMsg());
}

// Verify that the remove value must parse.
TEST_F(FlexOptionTest, optionConfigBadRemove) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr remove = Element::create(string("'abc'"));
    option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    string expected = "can't parse remove expression ['abc'] error: ";
    expected += "<string>:1.6: syntax error, unexpected end of file, ";
    expected += "expecting ==";
    EXPECT_EQ(expected,impl_->getErrMsg());
}

// Verify that a valid v4 remove value is accepted.
TEST_F(FlexOptionTest, optionConfigRemove4) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    option->set("remove", remove);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    FlexOptionImpl::OptionConfigPtr opt_cfg;
    ASSERT_NO_THROW(opt_cfg = map.at(DHO_HOST_NAME));
    ASSERT_TRUE(opt_cfg);
    EXPECT_EQ(DHO_HOST_NAME, opt_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::REMOVE, opt_cfg->getAction());
    EXPECT_EQ("'abc' == 'abc'", opt_cfg->getText());

    ExpressionPtr expr = opt_cfg->getExpr();
    ASSERT_TRUE(expr);
    ASSERT_EQ(3, expr->size());
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
    ValueStack values;
    EXPECT_NO_THROW(expr->at(0)->evaluate(*pkt4, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("abc", values.top());
    EXPECT_NO_THROW(expr->at(1)->evaluate(*pkt4, values));
    ASSERT_EQ(2, values.size());
    EXPECT_NO_THROW(expr->at(2)->evaluate(*pkt4, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("true", values.top());
}

// Verify that a valid v6 remove value is accepted.
TEST_F(FlexOptionTest, optionConfigRemove6) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    option->set("remove", remove);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    FlexOptionImpl::OptionConfigPtr opt_cfg;
    ASSERT_NO_THROW(opt_cfg = map.at(D6O_BOOTFILE_URL));
    ASSERT_TRUE(opt_cfg);
    EXPECT_EQ(D6O_BOOTFILE_URL, opt_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::REMOVE, opt_cfg->getAction());
    EXPECT_EQ("'abc' == 'abc'", opt_cfg->getText());

    ExpressionPtr expr = opt_cfg->getExpr();
    ASSERT_TRUE(expr);
    ASSERT_EQ(3, expr->size());
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, 12345));
    ValueStack values;
    EXPECT_NO_THROW(expr->at(0)->evaluate(*pkt6, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("abc", values.top());
    EXPECT_NO_THROW(expr->at(1)->evaluate(*pkt6, values));
    ASSERT_EQ(2, values.size());
    EXPECT_NO_THROW(expr->at(2)->evaluate(*pkt6, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("true", values.top());
}

// Verify that multiple actions are not accepted.
TEST_F(FlexOptionTest, optionConfigMultipleAction) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);

    // add and supersede.
    ElementPtr add = Element::create(string("'abc'"));
    option->set("add", add);
    ElementPtr supersede = Element::create(string("'abc'"));
    option->set("supersede", supersede);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    ostringstream errmsg;
    errmsg << "multiple actions: " << option->str();
    EXPECT_EQ(errmsg.str(), impl_->getErrMsg());

    // supersede and remove.
    option->remove("add");
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    option->set("remove", remove);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    errmsg.str("");
    errmsg << "multiple actions: " << option->str();
    EXPECT_EQ(errmsg.str(), impl_->getErrMsg());

    // add and remove.
    option->remove("supersede");
    option->set("add", add);
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    errmsg.str("");
    errmsg << "multiple actions: " << option->str();
    EXPECT_EQ(errmsg.str(), impl_->getErrMsg());
}

// Verify that multiple options are accepted.
TEST_F(FlexOptionTest, optionConfigList) {
    ElementPtr options = Element::createList();

    ElementPtr option1 = Element::createMap();
    options->add(option1);
    ElementPtr code1 = Element::create(DHO_HOST_NAME);
    option1->set("code", code1);
    ElementPtr add1 = Element::create(string("'abc'"));
    option1->set("add", add1);

    ElementPtr option2 = Element::createMap();
    options->add(option2);
    ElementPtr code2 = Element::create(DHO_ROOT_PATH);
    option2->set("code", code2);
    ElementPtr supersede2 = Element::create(string("'/'"));
    option2->set("supersede", supersede2);

    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    auto map = impl_->getOptionConfigMap();
    EXPECT_EQ(2, map.size());

    FlexOptionImpl::OptionConfigPtr opt1_cfg;
    ASSERT_NO_THROW(opt1_cfg = map.at(DHO_HOST_NAME));
    ASSERT_TRUE(opt1_cfg);
    EXPECT_EQ(DHO_HOST_NAME, opt1_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::ADD, opt1_cfg->getAction());
    EXPECT_EQ("'abc'", opt1_cfg->getText());

    FlexOptionImpl::OptionConfigPtr opt2_cfg;
    ASSERT_NO_THROW(opt2_cfg = map.at(DHO_ROOT_PATH));
    ASSERT_TRUE(opt2_cfg);
    EXPECT_EQ(DHO_ROOT_PATH, opt2_cfg->getCode());
    EXPECT_EQ(FlexOptionImpl::SUPERSEDE, opt2_cfg->getAction());
    EXPECT_EQ("'/'", opt2_cfg->getText());
}

// Verify that empty option config list does nothing.
TEST_F(FlexOptionTest, processEmpty) {
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
}

// Verify that NONE action really does nothing.
TEST_F(FlexOptionTest, processNone) {
    CfgMgr::instance().setFamily(AF_INET6);

    FlexOptionImpl::OptionConfigPtr
        opt_cfg(new FlexOptionImpl::OptionConfig(D6O_BOOTFILE_URL));
    EXPECT_EQ(FlexOptionImpl::NONE, opt_cfg->getAction());
    auto map = impl_->getMutableOptionConfigMap();
    map[DHO_HOST_NAME] = opt_cfg;

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
}

// Verify that ADD action adds the specified option.
TEST_F(FlexOptionTest, processAdd) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr add = Element::create(string("'abc'"));
    option->set("add", add);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_HOST_NAME);
    ASSERT_TRUE(opt);
    EXPECT_EQ(DHO_HOST_NAME, opt->getType());
    const OptionBuffer& buffer = opt->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

// Verify that ADD action does not add an already existing option.
TEST_F(FlexOptionTest, processAddExisting) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr add = Element::create(string("'abc'"));
    option->set("add", add);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    OptionStringPtr str(new OptionString(Option::V6, D6O_BOOTFILE_URL, "http"));
    response->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    OptionPtr opt = response->getOption(D6O_BOOTFILE_URL);
    ASSERT_TRUE(opt);
    EXPECT_EQ(D6O_BOOTFILE_URL, opt->getType());
    EXPECT_EQ("http", opt->toString());
}

// Verify that ADD action does not add an empty value.
TEST_F(FlexOptionTest, processAddEmpty) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr add = Element::create(string("''"));
    option->set("add", add);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));
}

// Verify that SUPERSEDE action supersedes the specified option.
TEST_F(FlexOptionTest, processSupersede) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr supersede = Element::create(string("'abc'"));
    option->set("supersede", supersede);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_HOST_NAME);
    ASSERT_TRUE(opt);
    EXPECT_EQ(DHO_HOST_NAME, opt->getType());
    const OptionBuffer& buffer = opt->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

// Verify that SUPERSEDE action supersedes an already existing option.
TEST_F(FlexOptionTest, processSupersedeExisting) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr supersede = Element::create(string("0xabcdef"));
    option->set("supersede", supersede);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    OptionStringPtr str(new OptionString(Option::V6, D6O_BOOTFILE_URL, "http"));
    response->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    OptionPtr opt = response->getOption(D6O_BOOTFILE_URL);
    ASSERT_TRUE(opt);
    EXPECT_EQ(D6O_BOOTFILE_URL, opt->getType());
    const OptionBuffer& buffer = opt->getData();
    ASSERT_EQ(3, buffer.size());
    uint8_t expected[] = { 0xab, 0xcd, 0xef };
    EXPECT_EQ(0, memcmp(&buffer[0], expected, 3));
}

// Verify that SUPERSEDE action does not supersede an empty value.
TEST_F(FlexOptionTest, processSupersedeEmpty) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr supersede = Element::create(string("''"));
    option->set("supersede", supersede);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));

    // Empty value does not remove existing values.
    OptionStringPtr str(new OptionString(Option::V4, DHO_HOST_NAME, "abc"));
    response->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_HOST_NAME);
    ASSERT_TRUE(opt);
    EXPECT_EQ(DHO_HOST_NAME, opt->getType());
    const OptionBuffer& buffer = opt->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

// Verify that REMOVE action removes an already existing option.
TEST_F(FlexOptionTest, processRemove) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    option->set("remove", remove);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    OptionStringPtr str(new OptionString(Option::V6, D6O_BOOTFILE_URL, "http"));
    response->addOption(str);

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_FALSE(response->getOption(D6O_BOOTFILE_URL));
}

// Verify that REMOVE action does nothing if the option is not present.
TEST_F(FlexOptionTest, processRemoveNoOption) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr remove = Element::create(string("'abc' == 'abc'"));
    option->set("remove", remove);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));
}

// Verify that REMOVE action does nothing when the expression evaluates to false.
TEST_F(FlexOptionTest, processRemoveFalse) {
    CfgMgr::instance().setFamily(AF_INET6);

    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr remove = Element::create(string("'abc' == 'xyz'"));
    option->set("remove", remove);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    OptionStringPtr str(new OptionString(Option::V6, D6O_BOOTFILE_URL, "http"));
    response->addOption(str);
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
    EXPECT_TRUE(response->getOption(D6O_BOOTFILE_URL));
}

// A more complex check...
TEST_F(FlexOptionTest, processFullTest) {
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_BOOT_FILE_NAME);
    option->set("code", code);
    string expr = "ifelse(option[host-name].exists,";
    expr += "concat(option[host-name].text,'.boot'),'')";
    ElementPtr add = Element::create(expr);
    option->set("add", add);
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    OptionStringPtr str(new OptionString(Option::V4, DHO_HOST_NAME, "foo"));
    query->addOption(str);
    EXPECT_FALSE(response->getOption(DHO_BOOT_FILE_NAME));

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    OptionPtr opt = response->getOption(DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(opt);
    EXPECT_EQ(DHO_BOOT_FILE_NAME, opt->getType());
    const OptionBuffer& buffer = opt->getData();
    ASSERT_EQ(8, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "foo.boot", 8));
}

} // end of anonymous namespace
