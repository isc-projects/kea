// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains common part of flexible option tests.

#ifndef TEST_FLEX_OPTION_H
#define TEST_FLEX_OPTION_H

#include <flex_option.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <gtest/gtest.h>

namespace isc {
namespace flex_option {
namespace test {

/// @brief Test class derived from FlexOptionImpl
class TestFlexOptionImpl : public FlexOptionImpl {
public:
    /// Export getMutableOptionConfigMap.
    using FlexOptionImpl::getMutableOptionConfigMap;

    /// Export getMutableSubOptionConfigMap.
    using FlexOptionImpl::getMutableSubOptionConfigMap;

    /// @Brief Configure clone which records the error.
    ///
    /// @param options The element with option config list.
    void testConfigure(isc::data::ConstElementPtr options) {
        err_msg_.clear();
        try {
            configure(options);
        } catch (const std::exception& ex) {
            err_msg_ = std::string(ex.what());
            throw;
        }
    }

    /// @brief Get the last error message.
    ///
    /// @return The last error message.
    const std::string& getErrMsg() const {
        return (err_msg_);
    }

private:
    /// @brief Last error message.
    std::string err_msg_;
};

/// @brief The type of shared pointers to TestFlexOptionImpl
typedef boost::shared_ptr<TestFlexOptionImpl> TestFlexOptionImplPtr;

/// @brief Base test fixture for testing the Flex Option library.
class BaseFlexOptionTest : public ::testing::Test {
public:
    /// @brief Constructor.
    BaseFlexOptionTest() {
        impl_.reset(new TestFlexOptionImpl());
        isc::dhcp::CfgMgr::instance().setFamily(AF_INET);
    }

    /// @brief Destructor.
    virtual ~BaseFlexOptionTest() {
        LibDHCP::clearRuntimeOptionDefs();
        isc::dhcp::CfgMgr::instance().setFamily(AF_INET);
        impl_.reset();
    }

    /// @brief Flex Option implementation.
    TestFlexOptionImplPtr impl_;
};

} // end of namespace test
} // end of namespace flex_option
} // end of namespace isc

#endif // TEST_FLEX_OPTION_H
