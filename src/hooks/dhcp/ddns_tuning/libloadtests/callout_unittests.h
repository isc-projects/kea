// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the ddns[46]_update callouts
/// installed by the ddns tuning hook library. In order to test the callouts
/// one must be able to pass to the load function its hook library parameters
/// because the only way to populate these parameters is by actually loading
/// the library via HooksManager::loadLibraries().

#include <config.h>

#include <asiolink/io_address.h>
#include <database/audit_entry.h>
#include <ddns_tuning.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <process/daemon.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::db;
using namespace isc::ddns_tuning;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::test;

namespace isc {
namespace ddns_tuning {
namespace test {

/// @brief Test fixture for testing the ddns_tuning hook library callouts.
class CalloutTest : public ::testing::Test {
public:
    // Structure that describes a callout invocation scenario.
    struct Scenario {
        std::string desc_;          // text description of scenario
        std::string subnet_exp_;    // string to use for subnet expression, "<null>" means none
        std::string suffix_;        // value to use as ddns-qualifying-suffix
        std::string exp_hostname_;  // expected content of "hostname" argument after invocation
    };

    // Mnemonic constants.
    static const std::string empty_expr;
    static const std::string no_expr;
    static const std::string no_suffix;

    /// @brief Constructor.
    CalloutTest(const std::string& subnet_obj_type) : subnet_obj_type_(subnet_obj_type) {
        reset();
    }

    /// @brief Destructor.
    virtual ~CalloutTest() {
        reset();
    }

    /// @brief Unloads libraries, clears configuration manager.
    virtual void reset() {
        HooksManager::unloadLibraries();
        CfgMgr::instance().clear();
        MultiThreadingTest mt(false);
    }

    /// @brief Adds a library to the collection of known libraries.
    ///
    /// @param lib name of the library.
    /// @param params Element map containing the library's configuration parameters.
    void addLib(const std::string& lib, ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    /// @brief Loads the collection of libraries via HooksManager.
    void loadLibs() {
        ASSERT_TRUE(HooksManager::loadLibraries(libraries_));
    }

    /// @brief Unloads all currently loaded libraries.
    void unloadLibs() {
        EXPECT_NO_THROW(HooksManager::unloadLibraries());
    }

    /// @brief Updates a subnet's expression.
    ///
    /// Stores the given expression string in the subnet's user context.  If the
    /// string value is "<null>" then the user context is set to an empty map.
    ///
    /// @param subnet reference to the subnet.
    /// @param expression_str string containing the desired expression or "<null>".
    void setSubnetExpression(SubnetPtr subnet, const std::string expression_str);

    /// @brief Convenience function which invokes dhcp_srv_configured callout.
    ///
    /// @param srv_config the server configuration to use.
    /// @param expected the expected callout status.
    void callDhcpSrvConfigured(SrvConfigPtr srv_config,
                               CalloutHandle::CalloutNextStep expected_status = CalloutHandle::NEXT_STEP_CONTINUE);

    /// @brief Convenience function which invokes cb_updated callout.
    ///
    /// @param subnet the subnet to add to the list of audit entries.
    void callCbUpdated(SubnetPtr subnet);

    /// @brief Audit entry object type for subnet.
    std::string subnet_obj_type_;

    /// @brief Index of ddns<4/6>_update callout.
    int hook_index_ddns_update_;

    /// @brief Index of dhcp<4/6>_srv_configured callout.
    int hook_index_dhcp_srv_configured_;

    /// @brief Index of cb<4/6>_updated callout.
    int hook_index_cb_updated_;

    /// @brief Collection of libraries to load.
    HookLibsCollection libraries_;
};

} // end of namespace isc::ddns_tuning::test
} // end of namespace isc::ddns_tuning
} // end of namespace isc
