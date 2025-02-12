// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
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
#include <callout_unittests.h>
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
using namespace isc::ddns_tuning::test;

namespace {

/// @brief Test fixture for testing the DHCPv4 ddns_tuning hook library callouts
class Callout4Test : public CalloutTest {
public:
    /// @brief Constructor
    Callout4Test() : CalloutTest("dhcp4_subnet") {
        CfgMgr::instance().setFamily(AF_INET);
        Daemon::setProcName("kea-dhcp4");

        // Register hook points.
        hook_index_ddns_update_ = HooksManager::registerHook("ddns4_update");
        hook_index_dhcp_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
        hook_index_cb_updated_ = HooksManager::registerHook("cb4_updated");
    }

    /// @brief Destructor
    virtual ~Callout4Test() {
    }

    /// @brief Invokes ddns4_update callback and verifies the outcome.
    ///
    /// This assumes the library has been loaded and configured as desired
    /// prior to the function call.
    ///
    /// @param subnet subnet to pass into the callout
    /// @param exp_hostname expected hostname returned by the callout
    /// @param skip_ddns when true, SKIP_DDNS class is added to the client
    /// query.
    void callDdns4Update(Subnet4Ptr subnet, const std::string& exp_hostname, bool skip_ddns = false) {
        // Make the client query and server response packets.
        Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
        if (skip_ddns) {
            query->addClass("SKIP_DDNS");
        }

        OptionPtr bootfile(new OptionString(Option::V4, DHO_BOOT_FILE_NAME, "boot4"));
        query->addOption(bootfile);
        Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));

        // Create DDNS parameters, it needs to be associated with the subnet.
        DdnsParamsPtr ddns_params(new DdnsParams(subnet, true));

        // Get and setup the callout handle.
        ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_ddns_update_));
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("hostname", std::string("orig_host"));
        handle->setArgument("query4", query);
        handle->setArgument("response4", response);
        ConstSubnet4Ptr subnet4 = subnet;
        handle->setArgument("subnet4", subnet4);
        handle->setArgument("ddns-params", ddns_params);
        handle->setArgument("fwd-update", true);
        handle->setArgument("rev-update", true);

        // Execute the callout.
        ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_ddns_update_, *handle));
        ASSERT_EQ(0, handle->getStatus());

        // Hostname should match the expected hostname.
        std::string calculated_hostname;
        handle->getArgument("hostname", calculated_hostname);
        ASSERT_EQ(calculated_hostname, exp_hostname);

        // Verify the DDNS direction flags.
        bool fwd_update;
        handle->getArgument("fwd-update", fwd_update);
        EXPECT_EQ(!skip_ddns, fwd_update);

        bool rev_update;
        handle->getArgument("rev-update", rev_update);
        EXPECT_EQ(!skip_ddns, rev_update);
    }

    /// @brief Verifies the outcome of invoking the ddns_update4 callout for
    /// several scenarios.
    ///
    /// Each scenario is described by an instance of @c Scenario.  Prior to running
    /// the scenarios the ddns_tuning library ls loaded with a configuration that
    /// specifies a valid, literal host expression.
    void testDdns4UpdateScenarios() {
        // Test scenarios to execute.
        const std::vector<Scenario> scenarios {
            {
            "1. Empty expression, with suffix, hostname, should not make changes",
            empty_expr,
            "example.com",
            "orig_host"
            },
            {
            "2. Non-empty expression, with suffix, hostname, should change all",
            "'subnet_host'",
            "example.com",
            "subnet_host.example.com"
            },
            {
            "3. Non-empty expression, no suffix, hostname, should change but without suffix",
            "'subnet_host'",
            no_suffix,
            "subnet_host"
            },
            {
            "4. Non-empty expression, with suffix, no hostname, should change",
            "'subnet_host'",
            "example.com",
            "subnet_host.example.com"
            },
            {
            "5. No expression, with suffix, hostname, should use global expression",
            no_expr,
            "example.com",
            "global_host.example.com"
            },
            {
            "6. V4 specific expression, with suffix, should change",
            "option[boot-file-name].hex",
            "example.com",
            "boot4.example.com"
            },
        };

        // Configure the hook library with a global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global_host'"));
        addLib(DDNS_TUNING_LIB_SO, config);
        loadLibs();

        // Run the scenarios.
        SubnetID subnet_id = 100;
        for (auto const& scenario : scenarios) {
            SCOPED_TRACE(scenario.desc_);

            // Make a new subnet. We use a new subnet ID so each scenario gets
            // a subnet that the cache has not seen. We don't care that the
            // subnets all have the same prefix.
            Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.100.0"), 24, 30, 40, 60, ++subnet_id));

            // Add its expression.
            if (scenario.subnet_exp_ != "<null>") {
                ElementPtr user_context = Element::createMap();
                ElementPtr ddns_tuning = Element::createMap();
                ddns_tuning->set("hostname-expr", Element::create(scenario.subnet_exp_));
                user_context->set("ddns-tuning", ddns_tuning);
                subnet->setContext(user_context);
            }

            // Set the qualifying suffix if not empty.
            if (!scenario.suffix_.empty()) {
                subnet->setDdnsQualifyingSuffix(scenario.suffix_);
            }

            // Run the ddns4_update() callback and verify the calculated host name.
            ASSERT_NO_FATAL_FAILURE(callDdns4Update(subnet, scenario.exp_hostname_));
        }
    }

    /// @brief Verifies that dhcp4_srv_configured() callout functions properly.
    ///
    /// -# Load the library with a global expression
    /// -# Add subnet without an expression to the configuration
    /// -# Call dhcp4_srv_configured
    /// -# Call ddns4_update() callout for the subnet, verify global expression is used
    /// -# Add an expression to subnet
    /// -# Call dhcp4_srv_configured
    /// -# Call ddns4_update() callout for the subnet, verify subnet expression is used
    /// -# Add an invalid expression to subnet
    /// -# Call dhcp4_srv_configured
    /// -# Call ddns4_update() callout for the subnet, verify global expression is used
    void testDhcp4SrvConfigured() {
        // Configure the hook library with a global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global_host'"));
        addLib(DDNS_TUNING_LIB_SO, config);
        loadLibs();

        // Make sure dhcp4_srv_configured callout exists.
        ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_dhcp_srv_configured_));

        // Create a IPv4 subnet.
        util::Triplet<uint32_t> unspecified;
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.168.0.1"), 24, unspecified, unspecified, 4000, 100));

        // Add the subnet to server configuration.
        auto srv_config = CfgMgr::instance().getStagingCfg();
        srv_config->getCfgSubnets4()->add(subnet);

        // Invoke the callout.
        callDhcpSrvConfigured(srv_config);

        // Verify that a call to ddns4_update() uses the  global expression.
        callDdns4Update(subnet, "global_host");

        // Add a valid expression to the subnet.
        setSubnetExpression(subnet, "'subnet_100'");

        // Invoke the callout. This should add the subnet's expression to the cache.
        callDhcpSrvConfigured(srv_config);

        // Verify that a call to ddns4_update() uses the subnet's expression.
        callDdns4Update(subnet, "subnet_100");

        // Make the subnet expression invalid.
        setSubnetExpression(subnet, "invalid expression");

        // Execute the callout. The subnet expression should fail to parse (without
        // causing a throw), leaving the subnet without an expression.
        callDhcpSrvConfigured(srv_config, CalloutHandle::NEXT_STEP_DROP);

        // Verify that a call to ddns4_update() now uses the global expression.
        callDdns4Update(subnet, "global_host");
    }

    /// @brief Verifies that cb4_updated() callout functions properly.
    ///
    /// -# Load the library with a global expression
    /// -# Add subnet without expression to the configuration
    /// -# Call ddns4_update() callout for the subnet, verify global expression is used
    /// -# Add an expression to subnet
    /// -# Call cb4_updated with no audit entries
    /// -# Call ddns4_update() callout for the subnet, verify global expression is used
    /// -# Call cb4_updated with an audit entry for the subnet
    /// -# Call ddns4_update() callout for the subnet, verify subnet expression is used
    void testCb4Updated() {
        // Configure the hook library with a global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global_host'"));
        addLib(DDNS_TUNING_LIB_SO, config);
        loadLibs();

        // Make sure cb4_updated callout exists.
        ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_cb_updated_));

        // Create a IPv4 subnet.
        util::Triplet<uint32_t> unspecified;
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.168.0.1"), 24, unspecified, unspecified, 4000, 100));
        auto srv_config = CfgMgr::instance().getStagingCfg();
        srv_config->getCfgSubnets4()->add(subnet);
        CfgMgr::instance().commit();

        // Verify that we use the global expression, as our subnet currently has no expression.
        callDdns4Update(subnet, "global_host");

        // Add an expression to the subnet.
        setSubnetExpression(subnet, "'subnet_100'");

        // Call cb update with no audit-entries.
        callCbUpdated(Subnet4Ptr());

        // We should not yet see the subnet's expression.
        callDdns4Update(subnet, "global_host");

        // Call cb update with an audit-entry for the subnet.
        callCbUpdated(subnet);

        // We should see the subnet's expression.
        callDdns4Update(subnet, "subnet_100");
    }

    /// @brief Verifies that ddns4_update correctly handles SKIP_DDNS queries.
    void testSkipDdns4() {
        // Configure the hook library with a global expression.
        ElementPtr config = Element::createMap();
        addLib(DDNS_TUNING_LIB_SO, config);
        loadLibs();

        // Create a IPv4 subnet.
        util::Triplet<uint32_t> unspecified;
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.168.0.1"), 24, unspecified, unspecified, 4000, 100));

        // Verify hostname isn't changed but we do set DDNS direction flags false.
        callDdns4Update(subnet, "orig_host", true);

        setSubnetExpression(subnet, "'subnet_100'");

        // Verify hostname is calculated and we set the DDNS direction flags false.
        callDdns4Update(subnet, "orig_host", true);
    }
};

TEST_F(Callout4Test, ddns4UpdateScenarios) {
    testDdns4UpdateScenarios();
}

TEST_F(Callout4Test, ddns4UpdateScenariosMultiThreading) {
    MultiThreadingTest mt(true);
    testDdns4UpdateScenarios();
}

TEST_F(Callout4Test, dhcp4SrvConfigured) {
    testDhcp4SrvConfigured();
}

TEST_F(Callout4Test, dhcp4SrvConfiguredMultiThreading) {
    MultiThreadingTest mt(true);
    testDhcp4SrvConfigured();
}

TEST_F(Callout4Test, cb4Updated) {
    testCb4Updated();
}

TEST_F(Callout4Test, cb4UpdatedMultiThreading) {
    MultiThreadingTest mt(true);
    testCb4Updated();
}

TEST_F(Callout4Test, skipDdns) {
    testSkipDdns4();
}

TEST_F(Callout4Test, skipDdnsMultiThreading) {
    MultiThreadingTest mt(true);
    testSkipDdns4();
}

} // end of anonymous namespace
