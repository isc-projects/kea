// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <database/audit_entry.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/testutils/lib_load_test_fixture.h>
#include <eval/token.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <hooks/library_handle.h>
#include <hooks/library_manager_collection.h>
#include <limits/limit_manager.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

namespace {

using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;

using isc::asiolink::IOAddress;

// Fixture for loading, unloading libraries and for testing callouts. Occasionally uses rate limits
// to test reconfiguration. Lease limits are considered to behave the same way in that regard, and
// for that reason, they are not explicitly tested.
class LimitsLibLoadTest : public isc::test::LibLoadTest {
public:

    // Constructor.
    LimitsLibLoadTest() : LibLoadTest(LIBDHCP_LIMITS_SO) {
    }

    // At the beginning of each test, simulate a library unload, effectively removing any
    // configuration and any packet counter in the limit manager. There is no way to remove all
    // client classes and all subnets from the configuration so remove them one by one.
    void SetUp() override {
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->removeClass("foo");

        if (CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getBySubnetId(1)) {
            CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->del(1);
        }
        if (CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getBySubnetId(1)) {
            CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->del(1);
        }

        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->empty())
            << "expected empty client class configuration, found "
            << CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->toElement()->str();
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll()->empty());
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll()->empty());
        CfgMgr::instance().commit();
    }

    // Registers v4 hooks in the hook manager.
    void registerV4Hooks() {
        hook_index_cb4_updated_ = HooksManager::registerHook("cb4_updated");
        hook_index_dhcp4_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
        hook_index_pkt4_receive_ = HooksManager::registerHook("pkt4_receive");
        hook_index_subnet4_select_ = HooksManager::registerHook("subnet4_select");
        hook_index_lease4_select_ = HooksManager::registerHook("lease4_select");
        hook_index_lease4_renew_ = HooksManager::registerHook("lease4_renew");
        LeaseMgrFactory::create("type=memfile persist=false universe=4");
    }

    // Registers v6 hooks in the hook manager.
    void registerV6Hooks() {
        hook_index_cb6_updated_ = HooksManager::registerHook("cb6_updated");
        hook_index_dhcp6_srv_configured_ = HooksManager::registerHook("dhcp6_srv_configured");
        hook_index_pkt6_receive_ = HooksManager::registerHook("pkt6_receive");
        hook_index_subnet6_select_ = HooksManager::registerHook("subnet6_select");
        hook_index_lease6_select_ = HooksManager::registerHook("lease6_select");
        hook_index_lease6_renew_ = HooksManager::registerHook("lease6_renew");
        hook_index_lease6_rebind_ = HooksManager::registerHook("lease6_rebind");
        LeaseMgrFactory::create("type=memfile persist=false universe=6");
    }

    // Checks that all v4 callouts are present.
    void calloutsV4Present() {
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_cb4_updated_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_dhcp4_srv_configured_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_pkt4_receive_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_subnet4_select_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_lease4_select_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_lease4_renew_));
    }

    // Checks that all v6 callouts are present.
    void calloutsV6Present() {
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_cb6_updated_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_dhcp6_srv_configured_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_pkt6_receive_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_subnet6_select_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_lease6_select_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_lease6_renew_));
        EXPECT_TRUE(HooksManager::calloutsPresent(hook_index_lease6_rebind_));
    }

    // Call the cb4_updated callout with client class updates or subnet updates.
    void callCb4Updated(CalloutHandlePtr& handle, bool add_client_class = false, bool add_subnet = false) {
        AuditEntryCollectionPtr audit_entries(boost::make_shared<AuditEntryCollection>());

        if (add_client_class) {
            ClientClassDefPtr client_class(boost::make_shared<ClientClassDef>("foo", ExpressionPtr()));
            client_class->setContext(Element::fromJSON(
                R"({ "limits": { "rate-limit": "1 packet per minute" } })"));
            CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass(client_class);

            audit_entries->insert(boost::make_shared<AuditEntry>("dhcp4_client_class",
                                                                 client_class->getId(),
                                                                 AuditEntry::ModificationType::CREATE,
                                                                 client_class->getModificationTime(),
                                                                 1, "added audit entry"));
        }

        if (add_subnet) {
            Subnet4Ptr subnet(
                boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
            subnet->setContext(Element::fromJSON(R"({ "limits": { "rate-limit": "1 packet per minute" } })"));
            CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);

            audit_entries->insert(boost::make_shared<AuditEntry>("dhcp4_subnet",
                                                                 subnet->getId(),
                                                                 AuditEntry::ModificationType::CREATE,
                                                                 subnet->getModificationTime(),
                                                                 1, "added audit entry"));
        }

        CfgMgr::instance().commit();

        // Add the audit_entries to the callout arguments.
        handle->setArgument("audit_entries", audit_entries);

        // Execute the callout.
        ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_cb4_updated_, *handle));
        ASSERT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
    }

    // Call the cb6_updated callout with client class updates or subnet updates.
    void callCb6Updated(CalloutHandlePtr& handle, bool add_client_class = false, bool add_subnet = false) {
        AuditEntryCollectionPtr audit_entries(boost::make_shared<AuditEntryCollection>());

        if (add_client_class) {
            ClientClassDefPtr client_class(boost::make_shared<ClientClassDef>("foo", ExpressionPtr()));
            client_class->setContext(Element::fromJSON(
                R"({ "limits": { "rate-limit": "1 packet per minute" } })"));
            CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass(client_class);

            audit_entries->insert(boost::make_shared<AuditEntry>("dhcp6_client_class",
                                                                 client_class->getId(),
                                                                 AuditEntry::ModificationType::CREATE,
                                                                 client_class->getModificationTime(),
                                                                 1, "added audit entry"));
        }

        if (add_subnet) {
            Subnet6Ptr subnet(
                boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
            subnet->setContext(Element::fromJSON(R"({ "limits": { "rate-limit": "1 packet per minute" } })"));
            CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);

            audit_entries->insert(boost::make_shared<AuditEntry>("dhcp6_subnet",
                                                                 subnet->getId(),
                                                                 AuditEntry::ModificationType::CREATE,
                                                                 subnet->getModificationTime(),
                                                                 1, "added audit entry"));
        }

        CfgMgr::instance().commit();

        // Add the audit_entries to the callout arguments.
        handle->setArgument("audit_entries", audit_entries);

        // Execute the callout.
        ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_cb6_updated_, *handle));
        ASSERT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
    }

    // Test that the updates from the cb4_updated callout get propagated to the limit manager.
    void testCb4Updated(bool add_client_class, bool add_subnet) {
        addLibrary(LIBDHCP_LIMITS_SO, ElementPtr());
        registerV4Hooks();

        // Load the library.
        EXPECT_TRUE(loadLibraries());
        calloutsV4Present();

        // In a real environment, configuration is committed after libraries are loaded.
        CfgMgr::instance().commit();

        CalloutHandlePtr cb_handle(HooksManager::createCalloutHandle());
        callCb4Updated(cb_handle, add_client_class, add_subnet);

        // Send four packets. Based on the set limit, there should be two drops and two continues.
        for (unsigned int j = 0; j < 4; ++j) {
            {
                CalloutHandlePtr handle(HooksManager::createCalloutHandle());
                Pkt4Ptr packet(boost::make_shared<Pkt4>(1, 128));
                packet->addClass("foo");
                ConstSubnet4Ptr subnet(
                    boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
                handle->setArgument("query4", packet);
                handle->setArgument("subnet4", subnet);

                EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt4_receive_, *handle));
                EXPECT_EQ(handle->getStatus(), add_client_class ?
                    (j < 1 ? CalloutHandle::NEXT_STEP_CONTINUE : CalloutHandle::NEXT_STEP_DROP) :
                    CalloutHandle::NEXT_STEP_CONTINUE);
            }

            {
                CalloutHandlePtr handle(HooksManager::createCalloutHandle());
                Pkt4Ptr packet(boost::make_shared<Pkt4>(1, 128));
                packet->addClass("foo");
                ConstSubnet4Ptr subnet(
                    boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
                handle->setArgument("query4", packet);
                handle->setArgument("subnet4", subnet);

                EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet4_select_, *handle));
                EXPECT_EQ(handle->getStatus(), add_subnet ?
                    (j < 1 ? CalloutHandle::NEXT_STEP_CONTINUE : CalloutHandle::NEXT_STEP_DROP) :
                    CalloutHandle::NEXT_STEP_CONTINUE);
            }
        }
    }

    // Test that the updates from the cb6_updated callout get propagated to the limit manager.
    void testCb6Updated(bool add_client_class, bool add_subnet) {
        addLibrary(LIBDHCP_LIMITS_SO, ElementPtr());
        registerV6Hooks();

        // Load the library.
        EXPECT_TRUE(loadLibraries());
        calloutsV6Present();
        {
            CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
            srv_configured_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());
            ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_dhcp6_srv_configured_,
                                                           *srv_configured_handle));
            ASSERT_EQ(srv_configured_handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        // In a real environment, configuration is committed after libraries are loaded.
        CfgMgr::instance().commit();

        CalloutHandlePtr cb_handle(HooksManager::createCalloutHandle());
        callCb6Updated(cb_handle, add_client_class, add_subnet);

        // Send four packets. Based on the set limit, there should be two drops and two continues.
        for (unsigned int j = 0; j < 4; ++j) {
            {
                CalloutHandlePtr handle(HooksManager::createCalloutHandle());
                Pkt6Ptr packet(boost::make_shared<Pkt6>(1, 128));
                packet->addClass("foo");
                ConstSubnet6Ptr subnet(
                    boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
                handle->setArgument("query6", packet);
                handle->setArgument("subnet6", subnet);

                EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt6_receive_, *handle));
                EXPECT_EQ(handle->getStatus(), add_client_class ?
                    (j < 1 ? CalloutHandle::NEXT_STEP_CONTINUE : CalloutHandle::NEXT_STEP_DROP) :
                    CalloutHandle::NEXT_STEP_CONTINUE);
            }

            {
                CalloutHandlePtr handle(HooksManager::createCalloutHandle());
                Pkt6Ptr packet(boost::make_shared<Pkt6>(1, 128));
                packet->addClass("foo");
                ConstSubnet6Ptr subnet(
                    boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
                handle->setArgument("query6", packet);
                handle->setArgument("subnet6", subnet);

                EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet6_select_, *handle));
                EXPECT_EQ(handle->getStatus(), add_subnet ?
                    (j < 1 ? CalloutHandle::NEXT_STEP_CONTINUE : CalloutHandle::NEXT_STEP_DROP) :
                    CalloutHandle::NEXT_STEP_CONTINUE);
            }
        }
    }

    int hook_index_cb4_updated_;
    int hook_index_cb6_updated_;

    int hook_index_dhcp4_srv_configured_;
    int hook_index_dhcp6_srv_configured_;

    int hook_index_pkt4_receive_;
    int hook_index_pkt6_receive_;

    int hook_index_subnet4_select_;
    int hook_index_subnet6_select_;

    int hook_index_lease4_select_;
    int hook_index_lease6_select_;

    int hook_index_lease4_renew_;
    int hook_index_lease6_renew_;

    int hook_index_lease6_rebind_;
};

// Check that the library can be loaded and unloaded multiple times.
TEST_F(LimitsLibLoadTest, loadUnload) {
    validDaemonTest("kea-dhcp4", AF_INET);
    validDaemonTest("kea-dhcp6", AF_INET6);
}

// Check that parameters are not allowed not even in the form of an empty map.
TEST_F(LimitsLibLoadTest, parametersNotAllowed) {
    invalidDaemonTest("kea-dhcp4", AF_INET, Element::createMap());
    invalidDaemonTest("kea-dhcp6", AF_INET6, Element::createMap());
}

// Check that a v4 packet gets dropped at the right hook and that the library can be reloaded with
// a different configuration.
TEST_F(LimitsLibLoadTest, v4) {
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");
    addLibrary(LIBDHCP_LIMITS_SO, ElementPtr());
    registerV4Hooks();

    // Call everything twice to check subsequent loading and unloading of libraries.
    for (unsigned int i = 0; i < 2; ++i) {
        // Make sure configuration is empty.
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->empty())
            << "expected empty client class configuration, found "
            << CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->toElement()->str();
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll()->empty());

        // Add a client class.
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass(
            "foo", ExpressionPtr(), "", false, false, CfgOptionPtr(), CfgOptionDefPtr(),
            Element::fromJSON(R"({ "limits": { "rate-limit": "2 packets per year" } })"));

        // Load the library.
        EXPECT_TRUE(loadLibraries());
        calloutsV4Present();
        {
            CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
            srv_configured_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());
            ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_dhcp4_srv_configured_,
                                                           *srv_configured_handle));
            ASSERT_EQ(srv_configured_handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        // In a real environment, configuration is committed after libraries are loaded.
        CfgMgr::instance().commit();

        // Send four packets. Based on the set limit, there should be two drops and two continues.
        for (unsigned int j = 0; j < 4; ++j) {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt4Ptr packet(boost::make_shared<Pkt4>(1, 128));
            packet->addClass("foo");
            ConstSubnet4Ptr subnet(
                boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
            handle->setArgument("query4", packet);
            handle->setArgument("subnet4", subnet);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt4_receive_, *handle));
            // Expect drop after the pkt4_receive hook.
            EXPECT_EQ(handle->getStatus(), j < 2 ? CalloutHandle::NEXT_STEP_CONTINUE :
                                                   CalloutHandle::NEXT_STEP_DROP);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet4_select_, *handle));
            EXPECT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        EXPECT_TRUE(unloadLibraries());
    }

    // Call everything twice to check subsequent loading and unloading of libraries.
    for (unsigned int i = 0; i < 2; ++i) {
        // Make sure configuration is empty.
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->empty())
            << "expected empty client class configuration, found "
            << CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->toElement()->str();
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll()->empty());

        // Switch to limiting by subnet ID.
        Subnet4Ptr subnet_for_config(
            boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
        subnet_for_config->setContext(
            Element::fromJSON(R"({ "limits": { "rate-limit": "2 packets per year" } })"));
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_for_config);

        // Load the library.
        EXPECT_TRUE(loadLibraries());
        calloutsV4Present();
        {
            CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
            srv_configured_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());
            ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_dhcp4_srv_configured_,
                                                           *srv_configured_handle));
            ASSERT_EQ(srv_configured_handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        // In a real environment, configuration is committed after libraries are loaded.
        CfgMgr::instance().commit();

        // Send four packets. Based on the set limit, there should be two drops and two continues.
        for (unsigned int j = 0; j < 4; ++j) {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt4Ptr packet(boost::make_shared<Pkt4>(1, 128));
            packet->addClass("foo");
            ConstSubnet4Ptr subnet(
                boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
            handle->setArgument("query4", packet);
            handle->setArgument("subnet4", subnet);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt4_receive_, *handle));
            EXPECT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet4_select_, *handle));
            // Expect drop after the subnet4_select hook.
            EXPECT_EQ(handle->getStatus(), j < 2 ? CalloutHandle::NEXT_STEP_CONTINUE :
                                                   CalloutHandle::NEXT_STEP_DROP);
        }

        EXPECT_TRUE(unloadLibraries());
    }
}

// Check that a v6 packet gets dropped at the right hook and that the library can be reloaded with
// a different configuration.
TEST_F(LimitsLibLoadTest, v6) {
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");
    addLibrary(LIBDHCP_LIMITS_SO, ElementPtr());
    registerV6Hooks();

    // Call everything twice to check subsequent loading and unloading of libraries.
    for (unsigned int i = 0; i < 2; ++i) {
        // Make sure configuration is empty.
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->empty())
            << "expected empty client class configuration, found "
            << CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->toElement()->str();
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll()->empty());

        // Add a client class.
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass(
            "foo", ExpressionPtr(), "", false, false, CfgOptionPtr(), CfgOptionDefPtr(),
            Element::fromJSON(R"({ "limits": { "rate-limit": "2 packets per year" } })"));

        // Load the library.
        EXPECT_TRUE(loadLibraries());
        calloutsV6Present();
        {
            CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
            srv_configured_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());
            ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_dhcp6_srv_configured_,
                                                           *srv_configured_handle));
            ASSERT_EQ(srv_configured_handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        // In a real environment, configuration is committed after libraries are loaded.
        CfgMgr::instance().commit();

        // Send four packets. Based on the set limit, there should be two drops and two continues.
        for (unsigned int j = 0; j < 4; ++j) {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt6Ptr packet(boost::make_shared<Pkt6>(1, 128));
            packet->addClass("foo");
            ConstSubnet6Ptr subnet(
                boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
            handle->setArgument("query6", packet);
            handle->setArgument("subnet6", subnet);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt6_receive_, *handle));
            // Expect drop after the pkt6_receive hook.
            EXPECT_EQ(handle->getStatus(), j < 2 ? CalloutHandle::NEXT_STEP_CONTINUE :
                                                   CalloutHandle::NEXT_STEP_DROP);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet6_select_, *handle));
            EXPECT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        EXPECT_TRUE(unloadLibraries());
    }

    // Call everything twice to check subsequent loading and unloading of libraries.
    for (unsigned int i = 0; i < 2; ++i) {
        // Make sure configuration is empty.
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->empty())
            << "expected empty client class configuration, found "
            << CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->toElement()->str();
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll()->empty());

        // Switch to limiting by subnet ID.
        Subnet6Ptr subnet_for_config(
            boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
        subnet_for_config->setContext(
            Element::fromJSON(R"({ "limits": { "rate-limit": "2 packets per year" } })"));
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet_for_config);

        // Load the library.
        EXPECT_TRUE(loadLibraries());
        calloutsV6Present();
        {
            CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
            srv_configured_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());
            ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_dhcp6_srv_configured_,
                                                           *srv_configured_handle));
            ASSERT_EQ(srv_configured_handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        // In a real environment, configuration is committed after libraries are loaded.
        CfgMgr::instance().commit();

        // Send four packets. Based on the set limit, there should be two drops and two continues.
        for (unsigned int j = 0; j < 4; ++j) {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt6Ptr packet(boost::make_shared<Pkt6>(1, 128));
            packet->addClass("foo");
            ConstSubnet6Ptr subnet(
                boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
            handle->setArgument("query6", packet);
            handle->setArgument("subnet6", subnet);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt6_receive_, *handle));
            EXPECT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet6_select_, *handle));
            // Expect drop after the subnet6_select hook.
            EXPECT_EQ(handle->getStatus(), j < 2 ? CalloutHandle::NEXT_STEP_CONTINUE :
                                                   CalloutHandle::NEXT_STEP_DROP);
        }

        EXPECT_TRUE(unloadLibraries());
    }
}

// ---- The following tests check that CB updates for client classes and subnets are propagated to
// the limits hook library. ----

TEST_F(LimitsLibLoadTest, cb4UpdatedPlain) {
    testCb4Updated(false, false);
}

TEST_F(LimitsLibLoadTest, cb4UpdatedClientClassOnly) {
    testCb4Updated(true, false);
}

TEST_F(LimitsLibLoadTest, cb4UpdatedSubnetOnly) {
    testCb4Updated(false, true);
}

TEST_F(LimitsLibLoadTest, cb4UpdatedClientClassAndSubnet) {
    testCb4Updated(true, true);
}

TEST_F(LimitsLibLoadTest, cb6UpdatedPlain) {
    testCb6Updated(false, false);
}

TEST_F(LimitsLibLoadTest, cb6UpdatedClientClassOnly) {
    testCb6Updated(true, false);
}

TEST_F(LimitsLibLoadTest, cb6UpdatedSubnetOnly) {
    testCb6Updated(false, true);
}

TEST_F(LimitsLibLoadTest, cb6UpdatedClientClassAndSubnet) {
    testCb6Updated(true, true);
}

// ---- The following tests check that subnet_cmds updates for client classes and subnets are
// propagated to the limits hook library. ----

TEST_F(LimitsLibLoadTest, subnetCmdsV4) {
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");
    addLibrary(LIBDHCP_LIMITS_SO, ElementPtr());
    registerV4Hooks();

    // Load the library.
    EXPECT_TRUE(loadLibraries());
    calloutsV4Present();
    {
        CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
        srv_configured_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());
        ASSERT_NO_THROW_LOG(
            HooksManager::callCallouts(hook_index_dhcp4_srv_configured_, *srv_configured_handle));
        ASSERT_EQ(srv_configured_handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
    }

    // In a real environment, configuration is committed after libraries are loaded.
    CfgMgr::instance().commit();

    // Simulate a subnet addition through subnet_cmds.
    Subnet4Ptr subnet_for_config(
        boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
    subnet_for_config->setContext(
        Element::fromJSON(R"({ "limits": { "rate-limit": "2 packets per minute" } })"));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_for_config);
    CfgMgr::instance().commit();

    // Send four packets. Based on the set limit, there should be two drops and two continues.
    for (unsigned int j = 0; j < 4; ++j) {
        {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt4Ptr packet(boost::make_shared<Pkt4>(1, 128));
            ConstSubnet4Ptr subnet(
                boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
            handle->setArgument("query4", packet);
            handle->setArgument("subnet4", subnet);

            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt4_receive_, *handle));
            EXPECT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt4Ptr packet(boost::make_shared<Pkt4>(1, 128));
            ConstSubnet4Ptr subnet(
                boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
            handle->setArgument("query4", packet);
            handle->setArgument("subnet4", subnet);

            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet4_select_, *handle));
            EXPECT_EQ(handle->getStatus(),
                      j < 2 ? CalloutHandle::NEXT_STEP_CONTINUE : CalloutHandle::NEXT_STEP_DROP);
        }
    }

    EXPECT_TRUE(unloadLibraries());
}

TEST_F(LimitsLibLoadTest, subnetCmdsV6) {
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");
    addLibrary(LIBDHCP_LIMITS_SO, ElementPtr());
    registerV6Hooks();

    // Load the library.
    EXPECT_TRUE(loadLibraries());
    calloutsV6Present();
    {
        CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
        srv_configured_handle->setArgument("server_config", CfgMgr::instance().getStagingCfg());
        ASSERT_NO_THROW_LOG(
            HooksManager::callCallouts(hook_index_dhcp6_srv_configured_, *srv_configured_handle));
        ASSERT_EQ(srv_configured_handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
    }

    // In a real environment, configuration is committed after libraries are loaded.
    CfgMgr::instance().commit();

    // Simulate a subnet addition through subnet_cmds.
    Subnet6Ptr subnet_for_config(
        boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
    subnet_for_config->setContext(
        Element::fromJSON(R"({ "limits": { "rate-limit": "2 packets per minute" } })"));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet_for_config);
    CfgMgr::instance().commit();

    // Send four packets. Based on the set limit, there should be two drops and two continues.
    for (unsigned int j = 0; j < 4; ++j) {
        {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt6Ptr packet(boost::make_shared<Pkt6>(1, 128));
            ConstSubnet6Ptr subnet(
                boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
            handle->setArgument("query6", packet);
            handle->setArgument("subnet6", subnet);

            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_pkt6_receive_, *handle));
            EXPECT_EQ(handle->getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        }

        {
            CalloutHandlePtr handle(HooksManager::createCalloutHandle());
            Pkt6Ptr packet(boost::make_shared<Pkt6>(1, 128));
            ConstSubnet6Ptr subnet(
                boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
            handle->setArgument("query6", packet);
            handle->setArgument("subnet6", subnet);

            EXPECT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_subnet6_select_, *handle));
            EXPECT_EQ(handle->getStatus(),
                      j < 2 ? CalloutHandle::NEXT_STEP_CONTINUE : CalloutHandle::NEXT_STEP_DROP);
        }
    }

    EXPECT_TRUE(unloadLibraries());
}

// ----

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(LimitsLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6
    invalidDaemonTest("kea-dhcp4", AF_INET6);

    // V6 is invalid when family is AF_INET
    invalidDaemonTest("kea-dhcp6", AF_INET);

    invalidDaemonTest("kea-ctrl-agent", AF_INET);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET);
    invalidDaemonTest("bogus", AF_INET);
}

}  // namespace
