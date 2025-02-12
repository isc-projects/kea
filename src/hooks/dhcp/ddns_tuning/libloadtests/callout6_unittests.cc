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

/// @brief Test fixture for testing the DHCPv6 ddns_tuning hook library callouts
class Callout6Test : public CalloutTest {
public:
    /// @brief Constructor
    Callout6Test() : CalloutTest("dhcp6_subnet") {
        CfgMgr::instance().setFamily(AF_INET6);
        Daemon::setProcName("kea-dhcp6");

        // Register hook points.
        hook_index_ddns_update_ = HooksManager::registerHook("ddns6_update");
        hook_index_dhcp_srv_configured_ = HooksManager::registerHook("dhcp6_srv_configured");
        hook_index_cb_updated_ = HooksManager::registerHook("cb6_updated");
    }

    /// @brief Destructor
    virtual ~Callout6Test() {
    }

    /// @brief Invokes ddns6_update callback and verifies the outcome.
    ///
    /// This assumes the library has been loaded and configured as desired
    /// prior to the function call.
    ///
    /// @param subnet subnet to pass into the callout
    /// @param exp_hostname expected hostname returned by the callout
    /// @param skip_ddns when true, SKIP_DDNS class is added to the client
    /// query.
    void callDdns6Update(Subnet6Ptr subnet, const std::string& exp_hostname,
                         bool skip_ddns = false) {
        // Make the client query and server response packets.
        Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
        if (skip_ddns) {
            query->addClass("SKIP_DDNS");
        }

        OptionPtr bootfile_url(new OptionString(Option::V6, D6O_BOOTFILE_URL, "boot6"));
        query->addOption(bootfile_url);
        Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));

        // Create DDNS parameters, it needs to be associated with the subnet.
        DdnsParamsPtr ddns_params(new DdnsParams(subnet, true));

        // Get and setup the callout handle.
        ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_ddns_update_));
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();
        handle->setArgument("hostname", std::string("orig_host"));
        handle->setArgument("query6", query);
        handle->setArgument("response6", response);
        ConstSubnet6Ptr subnet6 = subnet;
        handle->setArgument("subnet6", subnet6);
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

    /// @brief Verifies the outcome of invoking the ddns_update6 callout for
    /// several scenarios.
    ///
    /// Each scenario is described by an instance of @c Scenario.  Prior to running
    /// the scenarios the ddns_tuning library ls loaded with a configuration that
    /// specifies a valid, literal host expression.
    void testDdns6UpdateScenarios() {
        // Test scenarios to execute.
        const std::vector<Scenario> scenarios {
            {
            "1. Empty expression, with suffix, should not make changes",
            empty_expr,
            "example.com",
            "orig_host"
            },
            {
            "2. Non-empty expression, with suffix, should change",
            "'subnet_host'",
            "example.com",
            "subnet_host.example.com."
            },
            {
            "3. Non-empty expression, no suffix, should change but without suffix",
            "'subnet_host'",
            no_suffix,
            "subnet_host."
            },
            {
            "4. Non-empty expression, suffix, should change",
            "'subnet_host'",
            "example.com",
            "subnet_host.example.com."
            },
            {
            "5. No expression, with suffix, should use global expression",
            no_expr,
            "example.com",
            "global_host.example.com."
            },
            {
            "6. V6 specific expression, with suffix, should change",
            "option[bootfile-url].hex",
            "example.com",
            "boot6.example.com."
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
            Subnet6Ptr subnet(new Subnet6(IOAddress("3001:1::"), 64, 30, 40, 50, 60, ++subnet_id));

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

            // Run the ddns6_update() callback and verify the calculated host name.
            ASSERT_NO_FATAL_FAILURE(callDdns6Update(subnet, scenario.exp_hostname_));
        }
    }

    /// @brief Verifies that dhcp6_srv_configured() callout functions properly.
    ///
    /// -# Load the library with a global expression
    /// -# Add subnet without an expression to the configuration
    /// -# Call dhcp6_srv_configured
    /// -# Call ddns6_update() callout for the subnet, verify global expression is used
    /// -# Add an expression to subnet
    /// -# Call dhcp6_srv_configured
    /// -# Call ddns6_update() callout for the subnet, verify subnet expression is used
    /// -# Add an invalid expression to subnet
    /// -# Call dhcp6_srv_configured
    /// -# Call ddns6_update() callout for the subnet, verify global expression is used
    void testDhcp6SrvConfigured() {
        // Configure the hook library with a global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global_host'"));
        addLib(DDNS_TUNING_LIB_SO, config);
        loadLibs();

        // Make sure dhcp6_srv_configured callout exists.
        ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_dhcp_srv_configured_));

        // Create a IPv6 subnet.
        Subnet6Ptr subnet(new Subnet6(IOAddress("3001:1::"), 64, 30, 40, 50, 60, 100));

        // Add the subnet to server configuration.
        auto srv_config = CfgMgr::instance().getStagingCfg();
        srv_config->getCfgSubnets6()->add(subnet);

        // Invoke the callout.
        callDhcpSrvConfigured(srv_config);

        // Verify that a call to ddns6_update() uses the  global expression.
        callDdns6Update(subnet, "global_host.");

        // Add a valid expression to the subnet.
        setSubnetExpression(subnet, "'subnet_100'");

        // Invoke the callout. This should add the subnet's expression to the cache.
        callDhcpSrvConfigured(srv_config);

        // Verify that a call to ddns6_update() uses the subnet's expression.
        callDdns6Update(subnet, "subnet_100.");

        // Make the subnet expression invalid.
        setSubnetExpression(subnet, "invalid expression");

        // Execute the callout. The subnet expression should fail to parse (without
        // causing a throw), leaving the subnet without an expression.
        callDhcpSrvConfigured(srv_config, CalloutHandle::NEXT_STEP_DROP);

        // Verify that a call to ddns6_update() now uses the global expression.
        callDdns6Update(subnet, "global_host.");
    }

    /// @brief Verifies that cb6_updated() callout functions properly.
    ///
    /// -# Load the library with a global expression
    /// -# Add subnet without expression to the configuration
    /// -# Call ddns6_update() callout for the subnet, verify global expression is used
    /// -# Add an expression to subnet
    /// -# Call cb6_updated with no audit entries
    /// -# Call ddns6_update() callout for the subnet, verify global expression is used
    /// -# Call cb6_updated with an audit entry for the subnet
    /// -# Call ddns6_update() callout for the subnet, verify subnet expression is used
    void testCb6Updated() {
        // Configure the hook library with a global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global_host'"));
        addLib(DDNS_TUNING_LIB_SO, config);
        loadLibs();

        // Make sure cb6_updated callout exists.
        ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_cb_updated_));

        // Create a IPv6 subnet.
        Subnet6Ptr subnet(new Subnet6(IOAddress("3001:1::"), 64, 30, 40, 50, 60, 100));
        auto srv_config = CfgMgr::instance().getStagingCfg();
        srv_config->getCfgSubnets6()->add(subnet);
        CfgMgr::instance().commit();

        // Verify that we use the global expression, as our subnet currently has no expression.
        callDdns6Update(subnet, "global_host.");

        // Add an expression to the subnet.
        setSubnetExpression(subnet, "'subnet_100'");

        // Call cb update with no audit-entries.
        callCbUpdated(Subnet6Ptr());

        // We should not yet see the subnet's expression.
        callDdns6Update(subnet, "global_host.");

        // Call cb update with an audit-entry for the subnet.
        callCbUpdated(subnet);

        // We should see the subnet's expression.
        callDdns6Update(subnet, "subnet_100.");
    }

    /// @brief Verifies that ddns6_update correctly handles SKIP_DDNS queries.
    void testSkipDdns6() {
        // Configure the hook library with a global expression.
        ElementPtr config = Element::createMap();
        addLib(DDNS_TUNING_LIB_SO, config);
        loadLibs();

        // Create a IPv6 subnet.
        Subnet6Ptr subnet(new Subnet6(IOAddress("3001:1::"), 64, 30, 40, 50, 60, 100));

        // Verify hostname isn't changed but we do set DDNS direction flags false.
        callDdns6Update(subnet, "orig_host", true);

        setSubnetExpression(subnet, "'subnet_100'");

        // Verify hostname is calculated and we set the DDNS direction flags false.
        callDdns6Update(subnet, "orig_host", true);
    }
};

TEST_F(Callout6Test, ddns6UpdateScenarios) {
    testDdns6UpdateScenarios();
}

TEST_F(Callout6Test, ddns6UpdateScenariosMultiThreading) {
    MultiThreadingTest mt(true);
    testDdns6UpdateScenarios();
}

TEST_F(Callout6Test, dhcp6SrvConfigured) {
    testDhcp6SrvConfigured();
};

TEST_F(Callout6Test, dhcp6SrvConfiguredMultiThreading) {
    MultiThreadingTest mt(true);
    testDhcp6SrvConfigured();
};

TEST_F(Callout6Test, cb6Updated) {
    testCb6Updated();
};

TEST_F(Callout6Test, cb6UpdatedMultiThreading) {
    MultiThreadingTest mt(true);
    testCb6Updated();
};


TEST_F(Callout6Test, skipDdns) {
    testSkipDdns6();
}

TEST_F(Callout6Test, skipDdnsMultiThreading) {
    MultiThreadingTest mt(true);
    testSkipDdns6();
}

} // end of anonymous namespace
