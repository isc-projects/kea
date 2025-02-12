// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <database/audit_entry.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/testutils/lib_load_test_fixture.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <hooks/library_handle.h>
#include <limits/limit_manager.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

namespace {

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::limits;
using namespace isc::util;
using namespace std;

// Check that null parameters are handled correctly sans crashes.
TEST(LimitManagerTest, v4NullHandleParameters) {
    CalloutHandlePtr cb_updated_handle(HooksManager::createCalloutHandle());
    cb_updated_handle->setArgument("audit_entries", AuditEntryCollectionPtr());
    ASSERT_THROW_MSG(LimitManager::instance().cb_updated<DHCPv4>(*cb_updated_handle), Unexpected,
                     "null audit_entries in LimitManager::cb_updated");

    CalloutHandlePtr pkt_receive_handle(HooksManager::createCalloutHandle());
    pkt_receive_handle->setArgument("query4", Pkt4Ptr());
    ASSERT_THROW_MSG(LimitManager::instance().pkt_receive<DHCPv4>(*pkt_receive_handle), Unexpected,
                     "null packet in LimitManager::pkt_receive");

    CalloutHandlePtr subnet_select_handle(HooksManager::createCalloutHandle());
    subnet_select_handle->setArgument("query4", Pkt4Ptr());
    subnet_select_handle->setArgument("subnet4", ConstSubnet4Ptr());
    subnet_select_handle->setArgument("subnet4collection", Subnet4Collection());
    ASSERT_NO_THROW_LOG(LimitManager::instance().subnet_select<DHCPv4>(*subnet_select_handle));

    CalloutHandlePtr lease_select_handle(HooksManager::createCalloutHandle());
    lease_select_handle->setArgument("query4", Pkt4Ptr());
    lease_select_handle->setArgument("subnet4", ConstSubnet4Ptr());
    lease_select_handle->setArgument("fake_allocation", false);
    lease_select_handle->setArgument("lease4", Lease4Ptr());
    ASSERT_THROW_MSG(LimitManager::instance().lease_callout<DHCPv4>(*lease_select_handle),
                     Unexpected, "null lease in LimitManager::lease_callout");

    // Check that limits can be configured without a LeaseMgr.
    LeaseMgrFactory::destroy();
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
    CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
    srv_configured_handle->setArgument("network_state", NetworkStatePtr());
    srv_configured_handle->setArgument("json_config", ConstElementPtr());
    srv_configured_handle->setArgument("server_config", SrvConfigPtr());
    ASSERT_NO_THROW_LOG(
        LimitManager::instance().dhcp_srv_configured<DHCPv4>(*srv_configured_handle));
    vector<string> arguments(srv_configured_handle->getArgumentNames());
    EXPECT_EQ(std::find(arguments.begin(), arguments.end(), "error"), arguments.end());
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, srv_configured_handle->getStatus());

    // Check that limits can be configured with a LeaseMgr.
    LeaseMgrFactory::destroy();
    LeaseMgrFactory::create("type=memfile persist=false universe=4");
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());
    srv_configured_handle = HooksManager::createCalloutHandle();
    srv_configured_handle->setArgument("network_state", NetworkStatePtr());
    srv_configured_handle->setArgument("json_config", ConstElementPtr());
    srv_configured_handle->setArgument("server_config", SrvConfigPtr());
    ASSERT_NO_THROW_LOG(
        LimitManager::instance().dhcp_srv_configured<DHCPv4>(*srv_configured_handle));
    arguments = srv_configured_handle->getArgumentNames();
    EXPECT_EQ(std::find(arguments.begin(), arguments.end(), "error"), arguments.end());
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, srv_configured_handle->getStatus());

}

// Check that null parameters are handled correctly sans crashes.
TEST(LimitManagerTest, v6NullHandleParameters) {
    CalloutHandlePtr cb_updated_handle(HooksManager::createCalloutHandle());
    cb_updated_handle->setArgument("audit_entries", AuditEntryCollectionPtr());
    ASSERT_THROW_MSG(LimitManager::instance().cb_updated<DHCPv6>(*cb_updated_handle), Unexpected,
                     "null audit_entries in LimitManager::cb_updated");

    CalloutHandlePtr pkt_receive_handle(HooksManager::createCalloutHandle());
    pkt_receive_handle->setArgument("query6", Pkt6Ptr());
    ASSERT_THROW_MSG(LimitManager::instance().pkt_receive<DHCPv6>(*pkt_receive_handle), Unexpected,
                     "null packet in LimitManager::pkt_receive");

    CalloutHandlePtr subnet_select_handle(HooksManager::createCalloutHandle());
    subnet_select_handle->setArgument("query6", Pkt6Ptr());
    subnet_select_handle->setArgument("subnet6", ConstSubnet6Ptr());
    subnet_select_handle->setArgument("subnet6collection", Subnet6Collection());
    ASSERT_NO_THROW_LOG(LimitManager::instance().subnet_select<DHCPv6>(*subnet_select_handle));

    CalloutHandlePtr lease_select_handle(HooksManager::createCalloutHandle());
    lease_select_handle->setArgument("query6", Pkt6Ptr());
    lease_select_handle->setArgument("subnet6", ConstSubnet6Ptr());
    lease_select_handle->setArgument("fake_allocation", false);
    lease_select_handle->setArgument("lease6", Lease6Ptr());
    ASSERT_THROW_MSG(LimitManager::instance().lease_callout<DHCPv6>(*lease_select_handle),
                     Unexpected, "null lease in LimitManager::lease_callout");

    // Check that limits can be configured without a LeaseMgr.
    LeaseMgrFactory::destroy();
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
    CalloutHandlePtr srv_configured_handle(HooksManager::createCalloutHandle());
    srv_configured_handle->setArgument("network_state", NetworkStatePtr());
    srv_configured_handle->setArgument("json_config", ConstElementPtr());
    srv_configured_handle->setArgument("server_config", SrvConfigPtr());
    ASSERT_NO_THROW_LOG(
        LimitManager::instance().dhcp_srv_configured<DHCPv6>(*srv_configured_handle));
    vector<string> arguments(srv_configured_handle->getArgumentNames());
    EXPECT_EQ(std::find(arguments.begin(), arguments.end(), "error"), arguments.end());
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, srv_configured_handle->getStatus());

    // Check that limits can be configured with a LeaseMgr.
    LeaseMgrFactory::destroy();
    LeaseMgrFactory::create("type=memfile persist=false universe=6");
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());
    srv_configured_handle = HooksManager::createCalloutHandle();
    srv_configured_handle->setArgument("network_state", NetworkStatePtr());
    srv_configured_handle->setArgument("json_config", ConstElementPtr());
    srv_configured_handle->setArgument("server_config", SrvConfigPtr());
    ASSERT_NO_THROW_LOG(
        LimitManager::instance().dhcp_srv_configured<DHCPv6>(*srv_configured_handle));
    arguments = srv_configured_handle->getArgumentNames();
    EXPECT_EQ(std::find(arguments.begin(), arguments.end(), "error"), arguments.end());
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, srv_configured_handle->getStatus());
}

}  // namespace
