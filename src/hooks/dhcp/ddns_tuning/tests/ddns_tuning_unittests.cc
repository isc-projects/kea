// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible option.

#include <config.h>
#include <ddns_tuning.h>
#include <ddns_tuning_log.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_string.h>
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
using namespace isc::ddns_tuning;

namespace {

/// @brief Test class derived from DdnsTuningImpl
class TestDdnsTuningImpl : public DdnsTuningImpl {
public:
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

/// @brief The type of shared pointers to TestDdnsTuningImpl
typedef boost::shared_ptr<TestDdnsTuningImpl> TestDdnsTuningImplPtr;

/// @brief Test fixture for testing the DDNS Tuning library.
class DdnsTuningTest : public ::testing::Test {
public:
    /// @brief Constructor.
    DdnsTuningTest() {
        impl_.reset(new TestDdnsTuningImpl());
        CfgMgr::instance().setFamily(AF_INET);
    }

    /// @brief Destructor.
    virtual ~DdnsTuningTest() {
        CfgMgr::instance().setFamily(AF_INET);
        impl_.reset();
    }

    /// @brief Flex Option implementation.
    TestDdnsTuningImplPtr impl_;
};

// Verify that the configuration must exist.
TEST_F(DdnsTuningTest, noConfig) {
    ElementPtr options;
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'hostname' parameter is mandatory", impl_->getErrMsg());
}

// Verify that the configuration must be a list.
TEST_F(DdnsTuningTest, configNotList) {
    ElementPtr options = Element::createMap();
    EXPECT_THROW(impl_->testConfigure(options), BadValue);
    EXPECT_EQ("'hostname' parameter must be a string", impl_->getErrMsg());
}

// Verify that the configuration can be the empty list.
TEST_F(DdnsTuningTest, configEmpty) {
    ElementPtr options = Element::createList();
    EXPECT_NO_THROW(impl_->testConfigure(options));
    EXPECT_TRUE(impl_->getErrMsg().empty());
}



// Verify that the add value must parse.
TEST_F(DdnsTuningTest, optionConfigBadAdd) {
    ElementPtr params = Element::createList();
    params->set("hostname", Element::create(string("ifelse('a','b','c')")));
    EXPECT_THROW(impl_->testConfigure(params), BadValue);
    string expected = "can't parse add expression [ifelse('a','b','c')] ";
    expected += "error: <string>:1.11: syntax error, ";
    expected += "unexpected \",\", expecting == or +";
    EXPECT_EQ(expected, impl_->getErrMsg());
}

// Verify that a valid v4 add value is accepted.
TEST_F(DdnsTuningTest, optionConfigAdd4) {
    ElementPtr params = Element::createList();
    params->set("hostname", Element::create(string("ifelse('a','b','c')")));
    EXPECT_NO_THROW(impl_->testConfigure(params));
    EXPECT_TRUE(impl_->getErrMsg().empty());

    /* TODO: verify it was really configured
    auto map = impl_->getOptionConfigMap();
    DdnsTuningImpl::OptionConfigPtr opt_cfg;
    ASSERT_NO_THROW(opt_cfg = map.at(DHO_HOST_NAME));
    ASSERT_TRUE(opt_cfg);
    EXPECT_EQ(DHO_HOST_NAME, opt_cfg->getCode());
    EXPECT_EQ(DdnsTuningImpl::ADD, opt_cfg->getAction());
    EXPECT_EQ("'abc'", opt_cfg->getText());

    ExpressionPtr expr = opt_cfg->getExpr();
    ASSERT_TRUE(expr);
    ASSERT_EQ(1, expr->size());
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, 12345));
    ValueStack values;
    EXPECT_NO_THROW(expr->at(0)->evaluate(*pkt4, values));
    ASSERT_EQ(1, values.size());
    EXPECT_EQ("abc", values.top()); */
}

// Verify that empty option config list does nothing.
TEST_F(DdnsTuningTest, processEmpty) {
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt4Ptr>(Option::V4, query, response));

    EXPECT_EQ(response_txt, response->toText());
}

// Verify that NONE action really does nothing.
TEST_F(DdnsTuningTest, processNone) {
    CfgMgr::instance().setFamily(AF_INET6);

    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    string response_txt = response->toText();

    EXPECT_NO_THROW(impl_->process<Pkt6Ptr>(Option::V6, query, response));

    EXPECT_EQ(response_txt, response->toText());
}

// Verify that REMOVE action does nothing if the option is not present.
TEST_F(DdnsTuningTest, processRemoveNoOption) {
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
TEST_F(DdnsTuningTest, processRemoveFalse) {
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
TEST_F(DdnsTuningTest, processFullTest) {
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
