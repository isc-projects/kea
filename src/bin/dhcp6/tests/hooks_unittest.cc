// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp6/json_config_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <util/buffer.h>
#include <util/range_utilities.h>
#include <hooks/server_hooks.h>
#include <hooks/callout_manager.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/tests/pkt_captures.h>
#include <cc/command_interpreter.h>
#include <dhcp6/tests/marker_file.h>
#include <dhcp6/tests/test_libraries.h>
#include <stats/stats_mgr.h>
#include <util/multi_threading_mgr.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp::test;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::hooks;
using namespace isc::stats;
using namespace std;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace {

// Checks if hooks are implemented properly.
TEST_F(Dhcpv6SrvTest, Hooks) {
    NakedDhcpv6Srv srv(0);

    // check if appropriate hooks are registered
    int hook_index_buffer6_receive   = -1;
    int hook_index_buffer6_send      = -1;
    int hook_index_lease6_renew      = -1;
    int hook_index_lease6_release    = -1;
    int hook_index_lease6_rebind     = -1;
    int hook_index_lease6_decline    = -1;
    int hook_index_pkt6_received     = -1;
    int hook_index_select_subnet     = -1;
    int hook_index_leases6_committed = -1;
    int hook_index_pkt6_send         = -1;
    int hook_index_host6_identifier  = -1;

    // check if appropriate indexes are set
    EXPECT_NO_THROW(hook_index_buffer6_receive = ServerHooks::getServerHooks()
                    .getIndex("buffer6_receive"));
    EXPECT_NO_THROW(hook_index_buffer6_send = ServerHooks::getServerHooks()
                    .getIndex("buffer6_send"));
    EXPECT_NO_THROW(hook_index_lease6_renew = ServerHooks::getServerHooks()
                    .getIndex("lease6_renew"));
    EXPECT_NO_THROW(hook_index_lease6_release = ServerHooks::getServerHooks()
                    .getIndex("lease6_release"));
    EXPECT_NO_THROW(hook_index_lease6_rebind = ServerHooks::getServerHooks()
                    .getIndex("lease6_rebind"));
    EXPECT_NO_THROW(hook_index_lease6_decline = ServerHooks::getServerHooks()
                    .getIndex("lease6_decline"));
    EXPECT_NO_THROW(hook_index_pkt6_received = ServerHooks::getServerHooks()
                    .getIndex("pkt6_receive"));
    EXPECT_NO_THROW(hook_index_select_subnet = ServerHooks::getServerHooks()
                    .getIndex("subnet6_select"));
    EXPECT_NO_THROW(hook_index_leases6_committed = ServerHooks::getServerHooks()
                    .getIndex("leases6_committed"));
    EXPECT_NO_THROW(hook_index_pkt6_send = ServerHooks::getServerHooks()
                    .getIndex("pkt6_send"));
    EXPECT_NO_THROW(hook_index_host6_identifier = ServerHooks::getServerHooks()
                    .getIndex("host6_identifier"));


    EXPECT_TRUE(hook_index_pkt6_received     > 0);
    EXPECT_TRUE(hook_index_select_subnet     > 0);
    EXPECT_TRUE(hook_index_leases6_committed > 0);
    EXPECT_TRUE(hook_index_pkt6_send         > 0);
    EXPECT_TRUE(hook_index_buffer6_receive   > 0);
    EXPECT_TRUE(hook_index_buffer6_send      > 0);
    EXPECT_TRUE(hook_index_lease6_renew      > 0);
    EXPECT_TRUE(hook_index_lease6_release    > 0);
    EXPECT_TRUE(hook_index_lease6_rebind     > 0);
    EXPECT_TRUE(hook_index_lease6_decline    > 0);
    EXPECT_TRUE(hook_index_host6_identifier  > 0);
}

/// @brief a class dedicated to Hooks testing in DHCPv6 server
///
/// This class has a number of static members, because each non-static
/// method has implicit 'this' parameter, so it does not match callout
/// signature and couldn't be registered. Furthermore, static methods
/// can't modify non-static members (for obvious reasons), so many
/// fields are declared static. It is still better to keep them as
/// one class rather than unrelated collection of global objects.
class HooksDhcpv6SrvTest : public Dhcpv6SrvTest {

public:

    /// @brief creates Dhcpv6Srv and prepares buffers for callouts
    HooksDhcpv6SrvTest()
        : Dhcpv6SrvTest() {

        HooksManager::setTestMode(false);
        bool status = HooksManager::unloadLibraries();
        if (!status) {
            cerr << "(fixture ctor) unloadLibraries failed" << endl;
        }

        // Allocate new DHCPv6 Server
        srv_.reset(new NakedDhcpv6Srv(0));

        // Clear static buffers
        resetCalloutBuffers();

        io_service_ = boost::make_shared<IOService>();

        // Reset the hook system in its original state
        HooksManager::unloadLibraries();

        // Clear statistics.
        StatsMgr::instance().removeAll();
    }

    /// @brief destructor (deletes Dhcpv6Srv)
    ~HooksDhcpv6SrvTest() {
        // Clear static buffers
        resetCalloutBuffers();

        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("buffer6_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("pkt6_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("pkt6_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("buffer6_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("subnet6_select");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("leases6_committed");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease6_renew");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease6_release");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease6_rebind");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease6_decline");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("host6_identifier");

        // Clear statistics.
        StatsMgr::instance().removeAll();

        HooksManager::setTestMode(false);
        bool status = HooksManager::unloadLibraries();
        if (!status) {
            cerr << "(fixture dtor) unloadLibraries failed" << endl;
        }
    }

    /// @brief creates an option with specified option code
    ///
    /// This method is static, because it is used from callouts
    /// that do not have a pointer to HooksDhcpv6SSrvTest object
    ///
    /// @param option_code code of option to be created
    ///
    /// @return pointer to create option object
    static OptionPtr createOption(uint16_t option_code) {

        uint8_t payload[] = {
            0xa, 0xb, 0xc, 0xe, 0xf, 0x10, 0x11, 0x12, 0x13, 0x14
        };

        OptionBuffer tmp(payload, payload + sizeof(payload));
        return OptionPtr(new Option(Option::V6, option_code, tmp));
    }

    /// @brief Checks if the state of the callout handle associated with a query
    /// was reset after the callout invocation.
    ///
    /// The check includes verification if the status was set to 'continue' and
    /// that all arguments were deleted.
    ///
    /// @param query pointer to the query which callout handle is associated
    /// with.
    void checkCalloutHandleReset(const Pkt6Ptr& query) {
        CalloutHandlePtr callout_handle = query->getCalloutHandle();
        ASSERT_TRUE(callout_handle);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
        EXPECT_TRUE(callout_handle->getArgumentNames().empty());
    }

    /// test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt6_receive");

        callout_handle.getArgument("query6", callback_qry_pkt6_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// test callback that changes client-id value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_receive_change_clientid(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("query6", pkt);

        // Get rid of the old client-id
        pkt->delOption(D6O_CLIENTID);

        // Add a new option
        pkt->addOption(createOption(D6O_CLIENTID));

        // Carry on as usual
        return pkt6_receive_callout(callout_handle);
    }

    /// Test callback that deletes client-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_receive_delete_clientid(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("query6", pkt);

        // Get rid of the old client-id
        pkt->delOption(D6O_CLIENTID);

        // Carry on as usual
        return pkt6_receive_callout(callout_handle);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_receive_skip(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("query6", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // Carry on as usual
        return pkt6_receive_callout(callout_handle);
    }

    /// Test callback that sets drop flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_receive_drop(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("query6", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // Carry on as usual
        return pkt6_receive_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("buffer6_receive");

        callout_handle.getArgument("query6", callback_qry_pkt6_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// Test callback that changes first byte of client-id value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_receive_change_clientid(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("query6", pkt);

        // If there is at least one option with data
        if (pkt->data_.size() > Pkt6::DHCPV6_PKT_HDR_LEN + Option::OPTION6_HDR_LEN) {
            // Offset of the first byte of the first option. Let's set this byte
            // to some new value that we could later check
            pkt->data_[Pkt6::DHCPV6_PKT_HDR_LEN + Option::OPTION6_HDR_LEN] = 0xff;
        }

        // Carry on as usual
        return buffer6_receive_callout(callout_handle);
    }

    /// Test callback that deletes client-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_receive_delete_clientid(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("query6", pkt);

        // this is modified SOLICIT (with missing mandatory client-id)
        uint8_t data[] = {
        1,  // type 1 = SOLICIT
        0xca, 0xfe, 0x01, // trans-id = 0xcafe01
        0, 3, // option type 3 (IA_NA)
        0, 12, // option length 12
        0, 0, 0, 1, // iaid = 1
        0, 0, 0, 0, // T1 = 0
        0, 0, 0, 0  // T2 = 0
        };

        OptionBuffer modifiedMsg(data, data + sizeof(data));

        pkt->data_ = modifiedMsg;

        // carry on as usual
        return buffer6_receive_callout(callout_handle);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_receive_skip(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // Carry on as usual
        return buffer6_receive_callout(callout_handle);
    }

    /// Test callback that sets drop flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_receive_drop(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // Carry on as usual
        return buffer6_receive_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt6_send");

        callout_handle.getArgument("response6", callback_resp_pkt6_);

        callout_handle.getArgument("query6", callback_qry_pkt6_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        if (callback_resp_pkt6_) {
            callback_resp_options_copy_ = callback_resp_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    // Test callback that changes server-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_send_change_serverid(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("response6", pkt);

        // Get rid of the old server-id
        pkt->delOption(D6O_SERVERID);

        // Add a new option
        pkt->addOption(createOption(D6O_SERVERID));

        // Carry on as usual
        return pkt6_send_callout(callout_handle);
    }

    /// Test callback that deletes server-id
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_send_delete_serverid(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("response6", pkt);

        // Get rid of the old client-id
        pkt->delOption(D6O_SERVERID);

        // Carry on as usual
        return pkt6_send_callout(callout_handle);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_send_skip(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("response6", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // carry on as usual
        return pkt6_send_callout(callout_handle);
    }

    /// Test callback that sets drop flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_send_drop(CalloutHandle& callout_handle) {

        Pkt6Ptr pkt;
        callout_handle.getArgument("response6", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // carry on as usual
        return pkt6_send_callout(callout_handle);
    }

    /// @brief Test callback that stores response packet.
    /// @param callout_handle handle passed by the hooks framework.
    /// @return always 0
    static int
    buffer6_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("buffer6_send");

        callback_argument_names_ = callout_handle.getArgumentNames();

        callout_handle.getArgument("response6", callback_resp_pkt6_);

        if (callback_resp_pkt6_) {
            callback_resp_options_copy_ = callback_resp_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_send_skip(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // carry on as usual
        return buffer6_send_callout(callout_handle);
    }

    /// Test callback that sets drop flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_send_drop(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // carry on as usual
        return buffer6_send_callout(callout_handle);
    }

    /// Test callback that stores received callout name and subnet6 values
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet6_select_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("subnet6_select");

        callout_handle.getArgument("query6", callback_qry_pkt6_);
        callout_handle.getArgument("subnet6", callback_subnet6_);
        callout_handle.getArgument("subnet6collection", callback_subnet6collection_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// Test callback that picks the other subnet if possible.
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet6_select_different_subnet(CalloutHandle& callout_handle) {

        // Call the basic callout to record all passed values
        subnet6_select_callout(callout_handle);

        const Subnet6Collection* subnets;
        Subnet6Ptr subnet;
        callout_handle.getArgument("subnet6", subnet);
        callout_handle.getArgument("subnet6collection", subnets);

        // Let's change to a different subnet
        if (subnets->size() > 1) {
            subnet = *std::next(subnets->begin()); // Let's pick the other subnet
            callout_handle.setArgument("subnet6", subnet);
        }

        return (0);
    }

    /// Test callback that sets skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet6_select_skip(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // Carry on as usual
        return subnet6_select_callout(callout_handle);
    }

    /// Test callback that sets drop flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet6_select_drop(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // Carry on as usual
        return subnet6_select_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_renew_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_renew");

        callout_handle.getArgument("query6", callback_qry_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);
        callout_handle.getArgument("ia_na", callback_ia_na_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// The following values are used by the callout to override
    /// renewed lease parameters
    static const uint32_t override_iaid_;
    static const uint32_t override_preferred_;
    static const uint32_t override_valid_;

    /// Test callback that overrides received lease. It updates
    /// T1, T2, preferred and valid lifetimes
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_renew_update(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_renew");

        callout_handle.getArgument("query6", callback_qry_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);
        callout_handle.getArgument("ia_na", callback_ia_na_);

        // Should be an ASSERT but it is not allowed here
        EXPECT_TRUE(callback_lease6_);
        // Let's override some values in the lease
        callback_lease6_->iaid_          = override_iaid_;
        callback_lease6_->preferred_lft_ = override_preferred_;
        callback_lease6_->valid_lft_     = override_valid_;

        // Should be an ASSERT but it is not allowed here
        EXPECT_TRUE(callback_ia_na_);
        // Override the values to be sent to the client as well
        callback_ia_na_->setIAID(override_iaid_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that sets the skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_renew_skip_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_renew");

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        return (0);
    }

    /// Test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_rebind_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_rebind");

        callout_handle.getArgument("query6", callback_qry_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);
        callout_handle.getArgument("ia_na", callback_ia_na_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// Test callback that overrides received lease. It updates
    /// T1, T2, preferred and valid lifetimes
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_rebind_update(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_rebind");

        callout_handle.getArgument("query6", callback_qry_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);
        callout_handle.getArgument("ia_na", callback_ia_na_);

        // Should be an ASSERT but it is not allowed here
        EXPECT_TRUE(callback_lease6_);
        // Let's override some values in the lease
        callback_lease6_->iaid_          = override_iaid_;
        callback_lease6_->preferred_lft_ = override_preferred_;
        callback_lease6_->valid_lft_     = override_valid_;

        // Should be an ASSERT but it is not allowed here
        EXPECT_TRUE(callback_ia_na_);
        // Override the values to be sent to the client as well
        callback_ia_na_->setIAID(override_iaid_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Lease6_rebind callout that sets status to SKIP
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_rebind_skip(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        return (lease6_rebind_callout(callout_handle));
    }

    /// Lease6_rebind callout that sets status to DROP
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_rebind_drop_callout(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        return (lease6_rebind_callout(callout_handle));
    }


    /// Test callback that stores received callout name passed parameters
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_release_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_release");

        callout_handle.getArgument("query6", callback_qry_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// Test callback that sets the skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_release_skip(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_release");

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        return (0);
    }

    /// Test callback that sets the drop flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_release_drop(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_release");

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        return (0);
    }

    /// Lease6_decline test callback
    ///
    /// Stores all parameters in callback_* fields.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_decline_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_decline");
        callout_handle.getArgument("query6", callback_qry_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// Lease6_decline callout that sets status to SKIP
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_decline_skip(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        return (lease6_decline_callout(callout_handle));
    }

    /// Lease6_decline callout that sets status to DROP
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_decline_drop(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        return (lease6_decline_callout(callout_handle));
    }

    /// Test callback that stores values passed to leases6_committed.
    static int
    leases6_committed_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("leases6_committed");

        callout_handle.getArgument("query6", callback_qry_pkt6_);

        callout_handle.getArgument("leases6", callback_new_leases6_);

        callout_handle.getArgument("deleted_leases6", callback_deleted_leases6_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    static void
    leases6_committed_unpark(ParkingLotHandlePtr parking_lot, Pkt6Ptr query) {
        parking_lot->unpark(query);
    }

    /// Test callback which asks the server to park the packet.
    static int
    leases6_committed_park_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("leases6_committed");

        callout_handle.getArgument("query6", callback_qry_pkt6_);

        io_service_->post(std::bind(&HooksDhcpv6SrvTest::leases6_committed_unpark,
                                    callout_handle.getParkingLotHandlePtr(),
                                    callback_qry_pkt6_));

        callout_handle.getParkingLotHandlePtr()->reference(callback_qry_pkt6_);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_PARK);

        callout_handle.getArgument("leases6", callback_new_leases6_);

        callout_handle.getArgument("deleted_leases6", callback_deleted_leases6_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt6_) {
            callback_qry_options_copy_ = callback_qry_pkt6_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test host6_identifier by setting identifier to "foo"
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    host6_identifier_foo_callout(CalloutHandle& handle) {
        callback_name_ = string("host6_identifier");

        // Make sure the query6 parameter is passed.
        handle.getArgument("query6", callback_qry_pkt6_);

        // Make sure id_type parameter is passed.
        Host::IdentifierType type = Host::IDENT_FLEX;
        handle.getArgument("id_type", type);

        // Make sure id_value parameter is passed.
        std::vector<uint8_t> id_test;
        handle.getArgument("id_value", id_test);

        // Ok, now set the identifier.
        std::vector<uint8_t> id = { 0x66, 0x6f, 0x6f };  // foo
        handle.setArgument("id_value", id);
        handle.setArgument("id_type", Host::IDENT_FLEX);

        return (0);
    }

    /// @brief Test host6_identifier callout by setting identifier to hwaddr
    ///
    /// This callout always returns fixed HWADDR: 00:01:02:03:04:05
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    host6_identifier_hwaddr_callout(CalloutHandle& handle) {
        callback_name_ = string("host6_identifier");

        // Make sure the query6 parameter is passed.
        handle.getArgument("query6", callback_qry_pkt6_);

        // Make sure id_type parameter is passed.
        Host::IdentifierType type = Host::IDENT_FLEX;
        handle.getArgument("id_type", type);

        // Make sure id_value parameter is passed.
        std::vector<uint8_t> id_test;
        handle.getArgument("id_value", id_test);

        // Ok, now set the identifier to 00:01:02:03:04:05
        std::vector<uint8_t> id = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
        handle.setArgument("id_value", id);
        handle.setArgument("id_type", Host::IDENT_HWADDR);

        return (0);
    }


    /// Resets buffers used to store data received by callouts
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_qry_pkt6_.reset();
        callback_resp_pkt6_.reset();
        callback_subnet6_.reset();
        callback_lease6_.reset();
        callback_new_leases6_.reset();
        callback_deleted_leases6_.reset();
        callback_ia_na_.reset();
        callback_subnet6collection_ = NULL;
        callback_argument_names_.clear();
        callback_qry_options_copy_ = false;
        callback_resp_options_copy_ = false;
    }

    /// @brief Fetches the current value of the given statistic.
    /// @param name name of the desired statistic.
    /// @return Current value of the statistic, or zero if the
    /// statistic is not found.
    uint64_t getStatistic(const std::string& name) {
        ObservationPtr stat = StatsMgr::instance().getObservation(name);
        if (!stat) {
            return (0);
        }

        return (stat->getInteger().first);
    }

    /// Pointer to Dhcpv6Srv that is used in tests
    boost::shared_ptr<NakedDhcpv6Srv> srv_;

    /// Pointer to the IO service used in the tests.
    static IOServicePtr io_service_;

    // The following fields are used in testing pkt6_receive_callout

    /// String name of the received callout
    static string callback_name_;

    /// Client's query Pkt6 structure returned in the callout
    static Pkt6Ptr callback_qry_pkt6_;

    /// Server's response Pkt6 structure returned in the callout
    static Pkt6Ptr callback_resp_pkt6_;

    /// Pointer to lease6 structure returned in the leases6_committed callout
    static Lease6Ptr callback_lease6_;

    /// Pointers to lease6 structures returned in the leases6_committed callout
    static Lease6CollectionPtr callback_new_leases6_;
    static Lease6CollectionPtr callback_deleted_leases6_;

    /// Pointer to IA_NA option being renewed or rebound
    static boost::shared_ptr<Option6IA> callback_ia_na_;

    /// Pointer to a subnet received by callout
    static Subnet6Ptr callback_subnet6_;

    /// A list of all available subnets (received by callout)
    static const Subnet6Collection* callback_subnet6collection_;

    /// A list of all received arguments
    static vector<string> callback_argument_names_;

    /// Flag indicating if copying retrieved options was enabled for
    /// a query during callout execution.
    static bool callback_qry_options_copy_;

    /// Flag indicating if copying retrieved options was enabled for
    /// a response during callout execution.
    static bool callback_resp_options_copy_;
};

// The following parameters are used by callouts to override
// renewed lease parameters
const uint32_t HooksDhcpv6SrvTest::override_iaid_ = 1000;
const uint32_t HooksDhcpv6SrvTest::override_preferred_ = 1003;
const uint32_t HooksDhcpv6SrvTest::override_valid_ = 1004;

// The following fields are used in testing pkt6_receive_callout.
// See fields description in the class for details
IOServicePtr HooksDhcpv6SrvTest::io_service_;
string HooksDhcpv6SrvTest::callback_name_;
Pkt6Ptr HooksDhcpv6SrvTest::callback_qry_pkt6_;
Pkt6Ptr HooksDhcpv6SrvTest::callback_resp_pkt6_;
Subnet6Ptr HooksDhcpv6SrvTest::callback_subnet6_;
const Subnet6Collection* HooksDhcpv6SrvTest::callback_subnet6collection_;
vector<string> HooksDhcpv6SrvTest::callback_argument_names_;
Lease6Ptr HooksDhcpv6SrvTest::callback_lease6_;
Lease6CollectionPtr HooksDhcpv6SrvTest::callback_new_leases6_;
Lease6CollectionPtr HooksDhcpv6SrvTest::callback_deleted_leases6_;
boost::shared_ptr<Option6IA> HooksDhcpv6SrvTest::callback_ia_na_;
bool HooksDhcpv6SrvTest::callback_qry_options_copy_;
bool HooksDhcpv6SrvTest::callback_resp_options_copy_;

/// @brief Fixture class used to do basic library load/unload tests
class LoadUnloadDhcpv6SrvTest : public Dhcpv6SrvTest {
public:
    /// @brief Pointer to the tested server object
    boost::shared_ptr<NakedDhcpv6Srv> server_;

    LoadUnloadDhcpv6SrvTest()
        : Dhcpv6SrvTest() {
        reset();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor
    ~LoadUnloadDhcpv6SrvTest() {
        server_.reset();
        reset();
        MultiThreadingMgr::instance().setMode(false);
    };

    /// @brief Reset hooks data
    ///
    /// Resets the data for the hooks-related portion of the test by ensuring
    /// that no libraries are loaded and that any marker files are deleted.
    void reset() {
        // Unload any previously-loaded libraries.
        EXPECT_TRUE(HooksManager::unloadLibraries());

        // Get rid of any marker files.
        static_cast<void>(remove(LOAD_MARKER_FILE));
        static_cast<void>(remove(UNLOAD_MARKER_FILE));
        static_cast<void>(remove(SRV_CONFIG_MARKER_FILE));

        CfgMgr::instance().clear();
    }
};


// Checks if callouts installed on buffer6_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "buffer6_receive".
TEST_F(HooksDhcpv6SrvTest, simpleBuffer6Receive) {

    // Install buffer6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_callout));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer6_receive", callback_name_);

    // Check that pkt6 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt6_.get() == sol.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query6"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on buffer6_receive is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv6SrvTest, valueChangeBuffer6Receive) {

    // Install buffer6_receive_change_clientid
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_change_clientid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt6Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(D6O_CLIENTID);

    ASSERT_TRUE(clientid);

    // ... and check if it is the modified value
    EXPECT_EQ(0xff, clientid->getData()[0]);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on buffer6_receive is able to delete
// existing options and that change impacts server processing (mandatory
// client-id option is deleted, so the packet is expected to be dropped)
TEST_F(HooksDhcpv6SrvTest, deleteClientIdBuffer6Receive) {

    // Install buffer6_receive_delete_clientid
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_delete_clientid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not send a response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on buffer6_received is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, skipBuffer6Receive) {

    // Install buffer6_receive_skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_skip));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on buffer6_received is able to set drop flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, dropBuffer6Receive) {

    // Install buffer6_receive_drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_drop));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "pkt6_receive".
TEST_F(HooksDhcpv6SrvTest, simplePkt6Receive) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_receive", pkt6_receive_callout));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt6_receive", callback_name_);

    // Check that pkt6 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt6_.get() == sol.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query6"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_received is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv6SrvTest, valueChangePkt6Receive) {

    // Install pkt6_receive_change_clientid
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_receive", pkt6_receive_change_clientid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt6Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(D6O_CLIENTID);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(D6O_CLIENTID);
    EXPECT_TRUE(clientid->equals(expected));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_received is able to delete
// existing options and that change impacts server processing (mandatory
// client-id option is deleted, so the packet is expected to be dropped)
TEST_F(HooksDhcpv6SrvTest, deleteClientIdPkt6Receive) {

    // Install pkt6_receive_delete_clientid
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_receive", pkt6_receive_delete_clientid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not send a response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_received is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, skipPkt6Receive) {

    // Install pkt6_receive_skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_receive", pkt6_receive_skip));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_received is able to set drop flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, dropPkt6Receive) {

    // Install pkt6_receive_drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_receive", pkt6_receive_drop));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}


// Checks if callouts installed on pkt6_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv6SrvTest, simplePkt6Send) {

    // Install pkt6_send_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_callout));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt6_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt6Ptr adv = srv_->fake_sent_.front();

    // Check that pkt6 argument passing was successful and returned proper
    // values
    EXPECT_TRUE(callback_qry_pkt6_.get() == sol.get());
    EXPECT_TRUE(callback_resp_pkt6_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query6"));
    expected_argument_names.push_back(string("response6"));
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);
    EXPECT_TRUE(callback_resp_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_send is able to change
// the values and the packet sent contains those changes
TEST_F(HooksDhcpv6SrvTest, valueChangePkt6Send) {

    // Install pkt6_send_change_serverid
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_change_serverid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_send callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt6Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(D6O_SERVERID);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(D6O_SERVERID);
    EXPECT_TRUE(clientid->equals(expected));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_send is able to delete
// existing options and that server applies those changes. In particular,
// we are trying to send a packet without server-id. The packet should
// be sent
TEST_F(HooksDhcpv6SrvTest, deleteServerIdPkt6Send) {

    // Install pkt6_send_delete_serverid
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_delete_serverid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_send callback.
    srv_->run();

    // Check that the server indeed sent a malformed ADVERTISE
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Get that ADVERTISE
    Pkt6Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Make sure that it does not have server-id
    EXPECT_FALSE(adv->getOption(D6O_SERVERID));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_skip is able to set skip flag that
// will cause the server to send an empty response.
TEST_F(HooksDhcpv6SrvTest, skipPkt6Send) {

    // Install pkt6_send_skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_skip));

    // Let's create a simple REQUEST
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_send callback.
    srv_->run();

    // Check that the server send the packet
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // But the sent packet should have 0 length (we told the server to
    // skip pack(), but did not do packing outselves)
    Pkt6Ptr sent = srv_->fake_sent_.front();

    // The actual size of sent packet should be 0
    EXPECT_EQ(0, sent->getBuffer().getLength());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on pkt6_drop is able to set drop flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, dropPkt6Send) {

    // Install pkt6_send_drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_drop));

    // Let's create a simple REQUEST
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_send callback.
    srv_->run();

    // Check that the server does not send the packet
    EXPECT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on buffer6_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv6SrvTest, simpleBuffer6Send) {

    // Install buffer6_send_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_send", buffer6_send_callout));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer6_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt6Ptr adv = srv_->fake_sent_.front();

    // Check that pkt6 argument passing was successful and returned proper
    // values
    EXPECT_TRUE(callback_resp_pkt6_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("response6"));
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_resp_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on buffer6_send can set skip flag and that flag
// causes the packet to not be sent
TEST_F(HooksDhcpv6SrvTest, buffer6SendSkip) {

    // Install buffer6_send_skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_send", buffer6_send_skip));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer6_send", callback_name_);

    // Check that there is no packet sent
    EXPECT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callouts installed on buffer6_send can set drop flag and that flag
// causes the packet to not be sent
TEST_F(HooksDhcpv6SrvTest, buffer6SendDrop) {

    // Install buffer6_send_drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_send", buffer6_send_drop));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer6_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer6_send", callback_name_);

    // Check that there is no packet sent
    EXPECT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// This test checks if subnet6_select callout is triggered and reports
// valid parameters
TEST_F(HooksDhcpv6SrvTest, subnet6Select) {

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"" + valid_iface_ + "\" "
        " }, {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP6(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = isc::config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Install subnet6_select_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet6_select", subnet6_select_callout));

    // Prepare solicit packet. Server should select first subnet for it
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    sol->setIndex(valid_ifindex_);
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(sol, ctx);
    ASSERT_FALSE(drop);
    srv_->initContext(sol, ctx, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr adv = srv_->processSolicit(ctx);

    // Check if we get response at all
    ASSERT_TRUE(adv);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("subnet6_select", callback_name_);

    // Check that pkt6 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt6_.get() == sol.get());

    const Subnet6Collection* exp_subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();

    // The server is supposed to pick the first subnet, because of matching
    // interface. Check that the value is reported properly.
    ASSERT_TRUE(callback_subnet6_);
    EXPECT_EQ(callback_subnet6_.get(), exp_subnets->begin()->get());

    // Server is supposed to report two subnets
    ASSERT_EQ(exp_subnets->size(), callback_subnet6collection_->size());

    // Compare that the available subnets are reported as expected
    EXPECT_TRUE((*exp_subnets->begin())->get() == (*callback_subnet6collection_->begin())->get());
    EXPECT_TRUE((*std::next(exp_subnets->begin()))->get() == (*std::next(callback_subnet6collection_->begin()))->get());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// This test checks if callout installed on subnet6_select hook point can pick
// a different subnet.
TEST_F(HooksDhcpv6SrvTest, subnet6SelectChange) {

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"" + valid_iface_ + "\" "
        " }, {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP6(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = isc::config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Install subnet6_select_different_subnet
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet6_select", subnet6_select_different_subnet));

    // Prepare solicit packet. Server should select first subnet for it
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    sol->setIndex(valid_ifindex_);
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(sol, ctx);
    ASSERT_FALSE(drop);
    srv_->initContext(sol, ctx, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr adv = srv_->processSolicit(ctx);

    // Check if we get response at all
    ASSERT_TRUE(adv);

    // The response should have an address from second pool, so let's check it
    OptionPtr tmp = adv->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);
    boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(tmp);
    ASSERT_TRUE(ia);
    tmp = ia->getOption(D6O_IAADDR);
    ASSERT_TRUE(tmp);
    boost::shared_ptr<Option6IAAddr> addr_opt =
        boost::dynamic_pointer_cast<Option6IAAddr>(tmp);
    ASSERT_TRUE(addr_opt);

    // Get all subnets and use second subnet for verification
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Advertised address must belong to the second pool (in subnet's range,
    // in dynamic pool)
    auto subnet = subnets->begin();
    ++subnet;
    EXPECT_TRUE((*subnet)->inRange(addr_opt->getAddress()));
    EXPECT_TRUE((*subnet)->inPool(Lease::TYPE_NA, addr_opt->getAddress()));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks that subnet6_select is able to drop the packet.
TEST_F(HooksDhcpv6SrvTest, subnet6SelectDrop) {

    // Install subnet6_select_drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet6_select", subnet6_select_drop));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered subnet6_select callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// This test verifies that the leases6_committed hook point is not triggered
// for the SOLICIT.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedSolicit) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    // Install leases6_committed callout
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSolicit());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases6_committed hook point is not triggered
// for the CONFIRM.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedConfirm) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    // Get a lease for the client.
    ASSERT_NO_THROW(client.doSARR());

    // Install leases6_committed callout
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doConfirm());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases6_committed hook point is not triggered
// for the INFREQUEST.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedInfRequest) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.useRelay();

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doInfRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of SOLICIT message with Rapid Commit option,
// sent to allocate new lease.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRapidCommit) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"rapid-commit\": true, "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
    client.useRapidCommit(true);

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSolicit());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that it is possible to park a SOLICIT packet including
// Rapid Commit option as a result of the leases6_committed callouts. The
// prefix delegation is requested with the Solicit packet.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedParkRapidCommitPrefixes) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:1::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"rapid-commit\": true, "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // Create first client and perform SARR.
    Dhcp6Client client1;
    client1.setInterface("eth1");
    client1.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:28::"));
    client1.useRapidCommit(true);

    ASSERT_NO_THROW(configure(config, *client1.getServer()));

    // This callout uses provided IO service object to post a function
    // that unparks the packet. The packet is parked and can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_park_callout));

    ASSERT_NO_THROW(client1.doSolicit());

    // We should be offered an address but the REPLY should not arrive
    // at this point, because the packet is parked.
    ASSERT_FALSE(client1.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be passed to the callout.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client1.getContext().query_);

    // Reset all indicators because we'll be now creating a second client.
    resetCalloutBuffers();

    // Create the second client to test that it may communicate with the
    // server while the previous packet is parked.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    client2.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:29::"));
    client2.useRapidCommit(true);
    ASSERT_NO_THROW(client2.doSolicit());

    // The ADVERTISE should have been returned but not REPLAY, as this
    // packet got parked too.
    ASSERT_FALSE(client2.getContext().response_);

    // Check that the callback called is indeed the one we installed.
    EXPECT_EQ("leases6_committed", callback_name_);

    // There should be now two actions scheduled on our IO service
    // by the invoked callouts. They unpark both REPLY messages.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client1.receiveResponse());
    ASSERT_TRUE(client1.getContext().response_);
    Pkt6Ptr rsp = client1.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client1.hasLeaseForPrefix(IOAddress("2001:db8:1:28::"), 64));

    // Receive and check the second response.
    ASSERT_NO_THROW(client2.receiveResponse());
    ASSERT_TRUE(client2.getContext().response_);
    rsp = client2.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client2.hasLeaseForPrefix(IOAddress("2001:db8:1:29::"), 64));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client2.getContext().query_);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of REQUEST message sent to allocate new
// lease or renew an existing lease.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRequest) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Request the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Requested lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Let's try to request again but force the client to request a different
    // address with a different IAID.
    client.requestAddress(0x2233, IOAddress("2001:db8:1::29"));

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // New lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(2, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(1);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::29", lease->addr_.toText());

    // The old lease is kept.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // The requested address is just a hint.
    client.requestAddress(0x5577, IOAddress("4000::2"));

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(2);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::", lease->addr_.toText());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Request a prefix: this should lead to an error as no prefix pool
    // is configured.
    client.requestPrefix(0x1122, 64, IOAddress("2001:db8:1000::"));

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check the error.
    EXPECT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(0x1122));

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of REQUEST message sent to allocate new
// lease or renew an existing lease. Prefix variant.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRequestPrefix) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:1::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:28::"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Request the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Requested lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Let's try to request again but force the client to request a different
    // prefix with a different IAID.
    client.requestPrefix(0x2233, 64, IOAddress("2001:db8:1:29::"));

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // New lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(2, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(1);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:29::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // The old lease is kept.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // The requested prefix is just a hint.
    client.requestPrefix(0x5577, 64, IOAddress("4000::1"));

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(2);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Request an address: this should lead to an error as no address pool
    // is configured.
    client.requestAddress(0x1122, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check the error.
    EXPECT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(0x1122));

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of REQUEST message sent to reuse an
// existing lease.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedCache) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\", "
        "    \"cache-threshold\": .25 "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Request the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Requested lease should not be present, because it is reused.
    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_TRUE(callback_new_leases6_->empty());

    // Deleted lease must not be present, because it is renewed.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of REQUEST message sent to reuse an
// existing lease. Prefix variant.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedCachePrefix) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:1::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\", "
        "    \"cache-threshold\": .25 "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:28::"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Request the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Requested lease should not be present, because it is reused.
    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_TRUE(callback_new_leases6_->empty());

    // Deleted lease must not be present, because it is renewed.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that it is possible to park a packet as a result of
// the leases6_committed callouts.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedParkRequests) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // Create first client and perform SARR.
    Dhcp6Client client1;
    client1.setInterface("eth1");
    client1.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client1.getServer()));

    // This callout uses provided IO service object to post a function
    // that unparks the packet. The packet is parked and can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_park_callout));

    ASSERT_NO_THROW(client1.doSARR());

    // We should be offered an address but the REPLY should not arrive
    // at this point, because the packet is parked.
    ASSERT_FALSE(client1.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be passed to the callout.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client1.getContext().query_);

    // Reset all indicators because we'll be now creating a second client.
    resetCalloutBuffers();

    // Create the second client to test that it may communicate with the
    // server while the previous packet is parked.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    client2.requestAddress(0xabca, IOAddress("2001:db8:1::29"));
    ASSERT_NO_THROW(client2.doSARR());

    // The ADVERTISE should have been returned but not REPLAY, as this
    // packet got parked too.
    ASSERT_FALSE(client2.getContext().response_);

    // Check that the callback called is indeed the one we installed.
    EXPECT_EQ("leases6_committed", callback_name_);

    // There should be now two actions scheduled on our IO service
    // by the invoked callouts. They unpark both REPLY messages.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client1.receiveResponse());
    ASSERT_TRUE(client1.getContext().response_);
    Pkt6Ptr rsp = client1.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::28")));

    // Receive and check the second response.
    ASSERT_NO_THROW(client2.receiveResponse());
    ASSERT_TRUE(client2.getContext().response_);
    rsp = client2.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::29")));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client2.getContext().query_);
}

// This test verifies that it is possible to park a packet as a result of
// the leases6_committed callouts. Prefix variant.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedParkRequestsPrefixes) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:1::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // Create first client and perform SARR.
    Dhcp6Client client1;
    client1.setInterface("eth1");
    client1.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:28::"));

    ASSERT_NO_THROW(configure(config, *client1.getServer()));

    // This callout uses provided IO service object to post a function
    // that unparks the packet. The packet is parked and can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_park_callout));

    ASSERT_NO_THROW(client1.doSARR());

    // We should be offered an address but the REPLY should not arrive
    // at this point, because the packet is parked.
    ASSERT_FALSE(client1.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be passed to the callout.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client1.getContext().query_);

    // Reset all indicators because we'll be now creating a second client.
    resetCalloutBuffers();

    // Create the second client to test that it may communicate with the
    // server while the previous packet is parked.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    client2.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:29::"));
    ASSERT_NO_THROW(client2.doSARR());

    // The ADVERTISE should have been returned but not REPLAY, as this
    // packet got parked too.
    ASSERT_FALSE(client2.getContext().response_);

    // Check that the callback called is indeed the one we installed.
    EXPECT_EQ("leases6_committed", callback_name_);

    // There should be now two actions scheduled on our IO service
    // by the invoked callouts. They unpark both REPLY messages.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client1.receiveResponse());
    ASSERT_TRUE(client1.getContext().response_);
    Pkt6Ptr rsp = client1.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client1.hasLeaseForPrefix(IOAddress("2001:db8:1:28::"), 64));

    // Receive and check the second response.
    ASSERT_NO_THROW(client2.receiveResponse());
    ASSERT_TRUE(client2.getContext().response_);
    rsp = client2.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client2.hasLeaseForPrefix(IOAddress("2001:db8:1:29::"), 64));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client2.getContext().query_);
}

// This test verifies that incoming (positive) RENEW can be handled properly,
// and the lease6_renew callouts are triggered.
TEST_F(HooksDhcpv6SrvTest, basicLease6Renew) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_renew_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_renew", lease6_renew_callout));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr renewed_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(renewed_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);
    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);
    ASSERT_TRUE(reply);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease6_renew", callback_name_);

    // Check that appropriate parameters are passed to the callouts
    EXPECT_TRUE(callback_qry_pkt6_);
    EXPECT_TRUE(callback_lease6_);
    EXPECT_TRUE(callback_ia_na_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("lease6");
    expected_argument_names.push_back("ia_na");

    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());

    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr_opt;
    ASSERT_NO_FATAL_FAILURE(addr_opt = checkIA_NA(reply, 234, subnet_->getT1(),
                                                  subnet_->getT2()));

    ASSERT_TRUE(addr_opt);
    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);

    // Check that the lease has been returned
    ASSERT_TRUE(callback_lease6_);

    // Check that the returned lease6 in callout is the same as the one in the
    // database
    EXPECT_TRUE(*callback_lease6_ == *l);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that incoming (positive) RENEW can be handled properly,
// and the lease6_renew callouts are able to change the lease being updated.
TEST_F(HooksDhcpv6SrvTest, leaseUpdateLease6Renew) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_renew_update
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_renew", lease6_renew_update));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr renewed_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(renewed_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Turn on tee time calculation so we can see the effect of overriding
    // the lease life time.
    subnet_->setCalculateTeeTimes(true);
    Triplet<uint32_t> unspecified;
    subnet_->setT1(unspecified);
    subnet_->setT2(unspecified);
    subnet_->setT1Percent(0.60);
    subnet_->setT2Percent(0.80);

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);
    ASSERT_TRUE(reply);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr_opt;
    ASSERT_NO_FATAL_FAILURE(addr_opt = checkIA_NA(reply, 1000, 602, 802));

    ASSERT_TRUE(addr_opt);
    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);

    // Check that we chose the distinct override values
    ASSERT_NE(override_preferred_, subnet_->getPreferred());
    EXPECT_NE(override_valid_,     subnet_->getValid());

    // Check that preferred, valid were overridden the callout
    EXPECT_EQ(override_preferred_, l->preferred_lft_);
    EXPECT_EQ(override_valid_, l->valid_lft_);

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    Lease6Ptr deleted_lease =
        LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                              addr_opt->getAddress());
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(deleted_lease));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that incoming (positive) RENEW can be handled properly,
// and the lease6_renew callouts are able to set the skip flag that will
// reject the renewal
TEST_F(HooksDhcpv6SrvTest, skipLease6Renew) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_renew_skip_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_renew", lease6_renew_skip_callout));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt are really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr renewed_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(renewed_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RENEW
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRenew(req);
    ASSERT_TRUE(reply);

    // Check that our callback was called
    EXPECT_EQ("lease6_renew", callback_name_);

    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);

    // Check that the old values are still there and they were not
    // updated by the renewal
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of RENEW message sent to allocate new
// lease or renew an existing lease.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRenew) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Renew the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Renewed lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    resetCalloutBuffers();

    // Let's try to renew again but force the client to renew a different
    // address with a different IAID.
    client.requestAddress(0x2233, IOAddress("2001:db8:1::29"));

    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // New lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(2, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(1);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::29", lease->addr_.toText());

    // The old lease is kept.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // The renewed address is just a hint.
    client.requestAddress(0x5577, IOAddress("4000::2"));

    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(2);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::", lease->addr_.toText());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Renew a prefix: this should lead to an error as no prefix pool
    // is configured.
    client.requestPrefix(0x1122, 64, IOAddress("2001:db8:1000::"));

    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check the error.
    EXPECT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(0x1122));

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of RENEW message sent to allocate new
// lease or renew an existing lease. Prefix variant.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRenewPrefix) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:1::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:28::"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    resetCalloutBuffers();

    // Renew the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Renewed lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Let's try to renew again but force the client to renew a different
    // prefix with a different IAID.
    client.requestPrefix(0x2233, 64, IOAddress("2001:db8:1:29::"));

    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // New lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(2, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(1);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:29::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // The old lease is kept.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // The renewed prefix is just a hint.
    client.requestPrefix(0x5577, 64, IOAddress("4000::1"));

    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(2);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Renew an address: this should lead to an error as no address pool
    // is configured.
    client.requestAddress(0x1122, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(client.doRenew());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check the error.
    EXPECT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(0x1122));

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that incoming (positive) RELEASE can be handled properly,
// that a REPLY is generated, that the response has status code and that the
// lease is indeed removed from the database.
//
// expected:
// - returned REPLY message has copy of client-id
// - returned REPLY message has server-id
// - returned REPLY message has IA that does not include an IAADDR
// - lease is actually removed from LeaseMgr
TEST_F(HooksDhcpv6SrvTest, basicLease6Release) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_release_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_release", lease6_release_callout));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RELEASE, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr released_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(released_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RELEASE
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(req);

    ASSERT_TRUE(reply);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease6_release", callback_name_);

    // Check that appropriate parameters are passed to the callouts
    EXPECT_TRUE(callback_qry_pkt6_);
    EXPECT_TRUE(callback_lease6_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("lease6");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Check that the lease is really gone in the database
    // get lease by address
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_FALSE(l);

    // Get lease by subnetid/duid/iaid combination
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, *duid_, iaid,
                                              subnet_->getID());
    ASSERT_FALSE(l);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This is a variant of the previous test that tests that callouts are
// properly invoked for the prefix release case.
TEST_F(HooksDhcpv6SrvTest, basicLease6ReleasePD) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_release_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_release", lease6_release_callout));

    const IOAddress prefix("2001:db8:1:2:1::");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the prefix we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_PD, prefix));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, prefix, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 80));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD,
                                                        prefix);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RELEASE, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_PD, iaid, 1500, 3000);

    OptionPtr released_addr_opt(new Option6IAPrefix(D6O_IAPREFIX, prefix, 80,
                                                    300, 500));
    ia->addOption(released_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RELEASE
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(req);

    ASSERT_TRUE(reply);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease6_release", callback_name_);

    // Check that appropriate parameters are passed to the callouts
    EXPECT_TRUE(callback_qry_pkt6_);
    EXPECT_TRUE(callback_lease6_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("lease6");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Check that the lease is really gone in the database
    // get lease by address
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD, prefix);
    ASSERT_FALSE(l);

    // Get lease by subnetid/duid/iaid combination
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD, *duid_, iaid,
                                              subnet_->getID());
    ASSERT_FALSE(l);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that skip flag returned by a callout installed on the
// lease6_release hook point will keep the lease.
TEST_F(HooksDhcpv6SrvTest, skipLease6Release) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_release_skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_release", lease6_release_skip));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RELEASE, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr released_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(released_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RELEASE
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(req);

    ASSERT_TRUE(reply);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease6_release", callback_name_);

    // Check that the lease is still there
    // get lease by address
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                              addr);
    ASSERT_TRUE(l);

    // Get lease by subnetid/duid/iaid combination
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, *duid_, iaid,
                                              subnet_->getID());
    ASSERT_TRUE(l);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that drop flag returned by a callout installed on the
// lease6_release hook point will keep the lease.
TEST_F(HooksDhcpv6SrvTest, dropLease6Release) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_release_drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_release", lease6_release_drop));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RELEASE, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr released_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(released_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Server-id is mandatory in RELEASE
    req->addOption(srv.getServerID());

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRelease(req);

    ASSERT_TRUE(reply);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease6_release", callback_name_);

    // Check that the lease is still there
    // get lease by address
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                              addr);
    ASSERT_TRUE(l);

    // Get lease by subnetid/duid/iaid combination
    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, *duid_, iaid,
                                              subnet_->getID());
    ASSERT_TRUE(l);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that the leases6_committed callout is executed
// with deleted leases as argument when RELEASE is processed.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRelease) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(client.doSARR());
    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doRelease());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // No new allocations.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_TRUE(callback_new_leases6_->empty());

    // Released lease should be returned.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_EQ(1, callback_deleted_leases6_->size());
    Lease6Ptr lease = callback_deleted_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases6_committed callout is executed
// with deleted leases as argument when RELEASE is processed. Prefix variant.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedReleasePrefix) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:1::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:28::"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(client.doSARR());
    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doRelease());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // No new allocations.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_TRUE(callback_new_leases6_->empty());

    // Released lease should be returned.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_EQ(1, callback_deleted_leases6_->size());
    Lease6Ptr lease = callback_deleted_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases6_committed callout is executed
// with deleted leases as argument when RELEASE is processed.
// Variant with two addresses and two prefixes.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedReleaseMultiple) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:2::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8::/32\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    // In theory we can reuse the IAID but copyIAsFromLeases() copies
    // only one lease...
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
    client.requestPrefix(0xabcb, 64, IOAddress("2001:db8:2:28::"));
    client.requestAddress(0x2233, IOAddress("2001:db8:1::29"));
    client.requestPrefix(0x2234, 64, IOAddress("2001:db8:2:29::"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(client.doSARR());
    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doRelease());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // No new allocations.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_TRUE(callback_new_leases6_->empty());

    // Released lease should be returned.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_EQ(4, callback_deleted_leases6_->size());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that incoming (positive) REBIND can be handled properly,
// and the lease6_rebind callouts are triggered.
TEST_F(HooksDhcpv6SrvTest, basicLease6Rebind) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_rebind_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_rebind", lease6_rebind_callout));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during REBIND.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a REBIND
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REBIND, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr rebound_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(rebound_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRebind(req);
    ASSERT_TRUE(reply);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease6_rebind", callback_name_);

    // Check that appropriate parameters are passed to the callouts
    EXPECT_TRUE(callback_qry_pkt6_);
    EXPECT_TRUE(callback_lease6_);
    EXPECT_TRUE(callback_ia_na_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("lease6");
    expected_argument_names.push_back("ia_na");

    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());

    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr_opt;
    ASSERT_NO_FATAL_FAILURE(addr_opt = checkIA_NA(reply, 234, subnet_->getT1(),
                                                  subnet_->getT2()));

    ASSERT_TRUE(addr_opt);
    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);

    // Check that the lease has been returned
    ASSERT_TRUE(callback_lease6_);

    // Check that the returned lease6 in callout is the same as the one in the
    // database
    EXPECT_TRUE(*callback_lease6_ == *l);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that incoming (positive) REBIND can be handled properly,
// and the lease6_rebind callouts are able to change the lease being updated.
TEST_F(HooksDhcpv6SrvTest, leaseUpdateLease6Rebind) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_rebind_update
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_rebind", lease6_rebind_update));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during REBIND.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a REBIND
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REBIND, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr rebound_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(rebound_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Turn on tee time calculation so we can see the effect of overriding
    // the lease life time.
    subnet_->setCalculateTeeTimes(true);
    Triplet<uint32_t> unspecified;
    subnet_->setT1(unspecified);
    subnet_->setT2(unspecified);
    subnet_->setT1Percent(0.60);
    subnet_->setT2Percent(0.80);

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRebind(req);
    ASSERT_TRUE(reply);

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    // Note we also verify that T1 and T2 were calculated correctly.
    boost::shared_ptr<Option6IAAddr> addr_opt;
    ASSERT_NO_FATAL_FAILURE(addr_opt = checkIA_NA(reply, 1000, 602, 802));

    ASSERT_TRUE(addr_opt);
    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);

    // Check that we chose the distinct override values
    ASSERT_NE(override_preferred_, subnet_->getPreferred());
    EXPECT_NE(override_valid_,     subnet_->getValid());

    // Check that preferred and  valid were overridden in the callout
    EXPECT_EQ(override_preferred_, l->preferred_lft_);
    EXPECT_EQ(override_valid_, l->valid_lft_);

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    Lease6Ptr deleted_lease =
        LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                              addr_opt->getAddress());
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(deleted_lease));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that incoming (positive) REBIND can be handled properly,
// and the lease6_rebind callouts are able to set the skip flag that will
// reject the rebinding
TEST_F(HooksDhcpv6SrvTest, skipLease6Rebind) {
    NakedDhcpv6Srv srv(0);

    // Install lease6_rebind_skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_rebind", lease6_rebind_skip));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during REBIND.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a REBIND
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_REBIND, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    boost::shared_ptr<Option6IA> ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);

    OptionPtr rebound_addr_opt(new Option6IAAddr(D6O_IAADDR, addr, 300, 500));
    ia->addOption(rebound_addr_opt);
    req->addOption(ia);
    req->addOption(clientid);

    // Pass it to the server and hope for a REPLY
    Pkt6Ptr reply = srv.processRebind(req);
    ASSERT_TRUE(reply);

    // Check that our callback was called
    EXPECT_EQ("lease6_rebind", callback_name_);

    l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);

    // Check that the old values are still there and they were not
    // updated by the rebinding
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of REBIND message sent to allocate new
// lease or renew an existing lease.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRebind) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Rebind the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Rebound lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Let's try to rebind again but force the client to rebind a different
    // address with a different IAID.
    client.requestAddress(0x2233, IOAddress("2001:db8:1::29"));

    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // New lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(2, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(1);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::29", lease->addr_.toText());

    // The old lease is kept.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // The rebound address is just a hint.
    client.requestAddress(0x5577, IOAddress("4000::2"));

    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(2);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::", lease->addr_.toText());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Rebind a prefix: this should lead to an error as no prefix pool
    // is configured.
    client.requestPrefix(0x1122, 64, IOAddress("2001:db8:1000::"));

    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check the error.
    EXPECT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(0x1122));

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases6_committed hook
// point is executed as a result of REBIND message sent to allocate new
// lease or renew an existing lease. Prefix variant.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedRebindPrefix) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": [ {"
        "        \"prefix\": \"2001:db8:1::\", "
        "        \"prefix-len\": 56, "
        "        \"delegated-len\": 64 } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestPrefix(0xabca, 64, IOAddress("2001:db8:1:28::"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Rebind the lease and make sure that the callout has been executed.
    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Rebound lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:28::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // Deleted lease must not be present, because it is a new allocation.
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Let's try to rebind again but force the client to rebind a different
    // prefix with a different IAID.
    client.requestPrefix(0x2233, 64, IOAddress("2001:db8:1:29::"));

    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // New lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(2, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(1);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1:29::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);

    // The old lease is kept.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // The rebound prefix is just a hint.
    client.requestPrefix(0x5577, 64, IOAddress("4000::1"));

    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    lease = callback_new_leases6_->at(2);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::", lease->addr_.toText());
    EXPECT_EQ(64, lease->prefixlen_);
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Rebind an address: this should lead to an error as no address pool
    // is configured.
    client.requestAddress(0x1122, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(client.doRebind());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check the error.
    EXPECT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(0x1122));

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    ASSERT_TRUE(callback_new_leases6_);
    EXPECT_EQ(3, callback_new_leases6_->size());
    ASSERT_TRUE(callback_deleted_leases6_);
    EXPECT_TRUE(callback_deleted_leases6_->empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test checks that the basic decline hook (lease6_decline) is
// triggered properly.
TEST_F(HooksDhcpv6SrvTest, basicLease6Decline) {
    IfaceMgrTestConfig test_config(true);

    // Install lease6_decline callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_decline", lease6_decline_callout));

    HooksManager::setTestMode(true);

    // Get an address and decline it. DUIDs, IAID match and we send valid
    // address, so the decline procedure should be successful.
    Dhcp6Client client;
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1234, VALID_ADDR, SHOULD_PASS);

    // Check that the proper callback was called.
    EXPECT_EQ("lease6_decline", callback_name_);

    // And valid parameters were passed.
    ASSERT_TRUE(callback_qry_pkt6_);
    ASSERT_TRUE(callback_lease6_);

    // Test sanity check - it was a decline, right?
    EXPECT_EQ(DHCPV6_DECLINE, callback_qry_pkt6_->getType());

    // Get the address from this decline.
    OptionPtr ia = callback_qry_pkt6_->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia);
    boost::shared_ptr<Option6IAAddr> addr_opt =
        boost::dynamic_pointer_cast<Option6IAAddr>(ia->getOption(D6O_IAADDR));
    ASSERT_TRUE(addr_opt);
    IOAddress addr(addr_opt->getAddress());

    // Now get a lease from the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               addr);
    ASSERT_TRUE(from_mgr);
    // Now check that it's indeed declined.
    EXPECT_EQ(Lease::STATE_DECLINED, from_mgr->state_);

    // And that the parameters passed to callout are consistent with the database
    EXPECT_EQ(addr, from_mgr->addr_);
    EXPECT_EQ(addr, callback_lease6_->addr_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// Test that the lease6_decline hook point can handle SKIP status.
TEST_F(HooksDhcpv6SrvTest, lease6DeclineSkip) {
    IfaceMgrTestConfig test_config(true);

    // Install lease6_decline_skip callout. It will set the status to skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_decline", lease6_decline_skip));

    HooksManager::setTestMode(true);

    // Get an address and decline it. DUIDs, IAID match and we send valid
    // address, so the decline procedure should be successful.
    Dhcp6Client client;
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1234, VALID_ADDR, SHOULD_FAIL);

    // Check that the proper callback was called.
    EXPECT_EQ("lease6_decline", callback_name_);

    // And valid parameters were passed.
    ASSERT_TRUE(callback_qry_pkt6_);
    ASSERT_TRUE(callback_lease6_);

    // Test sanity check - it was a decline, right?
    EXPECT_EQ(DHCPV6_DECLINE, callback_qry_pkt6_->getType());

    // Get the address from this decline.
    OptionPtr ia = callback_qry_pkt6_->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia);
    boost::shared_ptr<Option6IAAddr> addr_opt =
        boost::dynamic_pointer_cast<Option6IAAddr>(ia->getOption(D6O_IAADDR));
    ASSERT_TRUE(addr_opt);
    IOAddress addr(addr_opt->getAddress());

    // Now get a lease from the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               addr);
    ASSERT_TRUE(from_mgr);
    // Now check that it's NOT declined.
    EXPECT_EQ(Lease::STATE_DEFAULT, from_mgr->state_);

    // And that the parameters passed to callout are consistent with the database
    EXPECT_EQ(addr, from_mgr->addr_);
    EXPECT_EQ(addr, callback_lease6_->addr_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// Test that the lease6_decline hook point can handle DROP status.
TEST_F(HooksDhcpv6SrvTest, lease6DeclineDrop) {
    IfaceMgrTestConfig test_config(true);

    // Install lease6_decline_drop callout. It will set the status to drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_decline", lease6_decline_drop));

    HooksManager::setTestMode(true);

    // Get an address and decline it. DUIDs, IAID match and we send valid
    // address, so it would work, but the callout sets status to DROP, so
    // the server should not update the lease and should not send back any
    // packets.
    Dhcp6Client client;
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1234, VALID_ADDR, SHOULD_FAIL);

    // Check that the proper callback was called.
    EXPECT_EQ("lease6_decline", callback_name_);

    // And valid parameters were passed.
    ASSERT_TRUE(callback_qry_pkt6_);
    ASSERT_TRUE(callback_lease6_);

    // Test sanity check - it was a decline, right?
    EXPECT_EQ(DHCPV6_DECLINE, callback_qry_pkt6_->getType());

    // Get the address from this decline.
    OptionPtr ia = callback_qry_pkt6_->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia);
    boost::shared_ptr<Option6IAAddr> addr_opt =
        boost::dynamic_pointer_cast<Option6IAAddr>(ia->getOption(D6O_IAADDR));
    ASSERT_TRUE(addr_opt);
    IOAddress addr(addr_opt->getAddress());

    // Now get a lease from the database.
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                               addr);
    ASSERT_TRUE(from_mgr);
    // Now check that it's NOT declined.
    EXPECT_EQ(Lease::STATE_DEFAULT, from_mgr->state_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases6_committed callout is executed
// when DECLINE is processed. The declined lease is expected to be passed
// in leases6 argument to the callout.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedDecline) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(client.doSARR());
    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doDecline());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // No deleted leases.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Declined lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(1, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases6_committed callout is executed
// when DECLINE is processed. Variant with 2 IA_NAs.
TEST_F(HooksDhcpv6SrvTest, leases6CommittedDeclineTwoNAs) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
    client.requestAddress(0x2233, IOAddress("2001:db8:1::29"));

    ASSERT_NO_THROW(configure(config, *client.getServer()));

    ASSERT_NO_THROW(client.doSARR());
    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_callout));

    ASSERT_NO_THROW(client.doDecline());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query6");
    expected_argument_names.push_back("deleted_leases6");
    expected_argument_names.push_back("leases6");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // No deleted leases.
    ASSERT_TRUE(callback_deleted_leases6_);
    ASSERT_TRUE(callback_deleted_leases6_->empty());

    // Declined lease should be returned.
    ASSERT_TRUE(callback_new_leases6_);
    ASSERT_EQ(2, callback_new_leases6_->size());
    Lease6Ptr lease = callback_new_leases6_->at(0);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::28", lease->addr_.toText());
    lease = callback_new_leases6_->at(1);
    ASSERT_TRUE(lease);
    EXPECT_EQ("2001:db8:1::29", lease->addr_.toText());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// Should test with one NA and two addresses but need an example first...

// Checks if callout installed on host6_identifier can generate an
// identifier and whether that identifier is actually used.
TEST_F(HooksDhcpv6SrvTest, host6Identifier) {

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces-config\": {\n"
        "  \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"preferred-lifetime\": 3000,\n"
        "\"rebind-timer\": 2000,\n"
        "\"renew-timer\": 1000,\n"
        "\"host-reservation-identifiers\": [ \"flex-id\" ],\n"
        "\"subnet6\": [ {\n"
        "    \"pools\": [ { \"pool\": \"2001:db8::/64\" } ],\n"
        "    \"subnet\": \"2001:db8::/48\", \n"
        "    \"interface\": \"" + valid_iface_ + "\",\n"
        "    \"reservations\": [\n"
        "        {\n"
        "            \"flex-id\": \"'foo'\",\n"
        "            \"ip-addresses\": [ \"2001:db8::f00\" ]\n"
        "        }\n"
        "    ]\n"
        " } ]\n,"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP6(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = isc::config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Install host6_identifier_foo_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "host6_identifier", host6_identifier_foo_callout));

    // Prepare solicit packet. Server should select first subnet for it
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    sol->setIndex(valid_ifindex_);
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(sol, ctx);
    ASSERT_FALSE(drop);
    srv_->initContext(sol, ctx, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr adv = srv_->processSolicit(ctx);

    // Check if we get response at all
    ASSERT_TRUE(adv);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("host6_identifier", callback_name_);

    // Check that pkt6 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt6_.get() == sol.get());

    // Now check if we got the reserved address
    OptionPtr tmp = adv->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr_opt;
    ASSERT_NO_FATAL_FAILURE(addr_opt = checkIA_NA(adv, 234, 1000, 2000));

    ASSERT_TRUE(addr_opt);
    ASSERT_EQ("2001:db8::f00", addr_opt->getAddress().toText());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}

// Checks if callout installed on host6_identifier can generate an identifier
// other type. This particular callout always returns hwaddr.
TEST_F(HooksDhcpv6SrvTest, host6Identifier_hwaddr) {

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces-config\": {\n"
        "  \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"preferred-lifetime\": 3000,\n"
        "\"rebind-timer\": 2000,\n"
        "\"renew-timer\": 1000,\n"
        "\"host-reservation-identifiers\": [ \"flex-id\" ],\n"
        "\"subnet6\": [ {\n"
        "    \"pools\": [ { \"pool\": \"2001:db8::/64\" } ],\n"
        "    \"subnet\": \"2001:db8::/48\", \n"
        "    \"interface\": \"" + valid_iface_ + "\",\n"
        "    \"reservations\": [\n"
        "        {\n"
        "            \"hw-address\": \"00:01:02:03:04:05\",\n"
        "            \"ip-addresses\": [ \"2001:db8::f00\" ]\n"
        "        }\n"
        "    ]\n"
        " } ]\n,"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP6(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = isc::config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Install host6_identifier_foo_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "host6_identifier", host6_identifier_hwaddr_callout));

    // Prepare solicit packet. Server should select first subnet for it
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    sol->setIndex(valid_ifindex_);
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(sol, ctx);
    ASSERT_FALSE(drop);
    srv_->initContext(sol, ctx, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr adv = srv_->processSolicit(ctx);

    // Check if we get response at all
    ASSERT_TRUE(adv);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("host6_identifier", callback_name_);

    // Check that pkt6 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt6_.get() == sol.get());

    // Now check if we got the reserved address
    OptionPtr tmp = adv->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr_opt;
    ASSERT_NO_FATAL_FAILURE(addr_opt = checkIA_NA(adv, 234, 1000, 2000));

    ASSERT_TRUE(addr_opt);
    ASSERT_EQ("2001:db8::f00", addr_opt->getAddress().toText());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(sol);
}


// Verifies that libraries are unloaded by server destruction
// The callout libraries write their library index number to a marker
// file upon load and unload, making it simple to test whether or not
// the load and unload callouts have been invoked.
TEST_F(LoadUnloadDhcpv6SrvTest, unloadLibraries) {

    ASSERT_NO_THROW(server_.reset(new NakedDhcpv6Srv(0)));

    // Ensure no marker files to start with.
    ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Load the test libraries
    HookLibsCollection libraries;
    libraries.push_back(make_pair(std::string(CALLOUT_LIBRARY_1),
                                  ConstElementPtr()));
    libraries.push_back(make_pair(std::string(CALLOUT_LIBRARY_2),
                                  ConstElementPtr()));

    ASSERT_TRUE(HooksManager::loadLibraries(libraries));

    // Verify that they load functions created the LOAD_MARKER_FILE
    // and that its contents are correct: "12" - the first library
    // appends "1" to the file, the second appends "2"). Also
    // check that the unload marker file does not yet exist.
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "12"));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Destroy the server, instance which should unload the libraries.
    server_.reset();

    // Check that the libraries were unloaded. The libraries are
    // unloaded in the reverse order to which they are loaded, and
    // this should be reflected in the unload file.
    EXPECT_TRUE(checkMarkerFile(UNLOAD_MARKER_FILE, "21"));
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "12"));
}

// Verifies that libraries incompatible with multi threading are not loaded by
// the server.
// The callout libraries write their library index number to a marker
// file upon load and unload, making it simple to test whether or not
// the load and unload callouts have been invoked.
TEST_F(LoadUnloadDhcpv6SrvTest, failLoadIncompatibleLibraries) {

    ASSERT_NO_THROW(server_.reset(new NakedDhcpv6Srv(0)));

    MultiThreadingMgr::instance().setMode(true);

    // Ensure no marker files to start with.
    ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Load the test libraries
    HookLibsCollection libraries;
    libraries.push_back(make_pair(std::string(CALLOUT_LIBRARY_2),
                                  ConstElementPtr()));

    ASSERT_FALSE(HooksManager::loadLibraries(libraries));

    // The library is missing multi_threading_compatible function so loading
    // should fail
    EXPECT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    libraries.clear();
    libraries.push_back(make_pair(std::string(CALLOUT_LIBRARY_3),
                                  ConstElementPtr()));

    ASSERT_FALSE(HooksManager::loadLibraries(libraries));

    // The library is not multi threading compatible so loading should fail
    EXPECT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Destroy the server, instance which should unload the libraries.
    server_.reset();

    // Check that the libraries were unloaded. The libraries are
    // unloaded in the reverse order to which they are loaded, and
    // this should be reflected in the unload file.
    EXPECT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));
}

// Checks if callouts installed on the dhcp6_srv_configured ared indeed called
// and all the necessary parameters are passed.
TEST_F(LoadUnloadDhcpv6SrvTest, Dhcpv6SrvConfigured) {
    for (string parameters : {
        "",
        R"(, "parameters": { "mode": "fail-without-error" } )",
        R"(, "parameters": { "mode": "fail-with-error" } )"}) {

        reset();

        boost::shared_ptr<ControlledDhcpv6Srv> srv(new ControlledDhcpv6Srv(0));

        // Ensure no marker files to start with.
        ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
        ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));
        ASSERT_FALSE(checkMarkerFileExists(SRV_CONFIG_MARKER_FILE));

        // Minimal valid configuration for the server. It includes the
        // section which loads the callout library #3, which implements
        // dhcp6_srv_configured callout.
        string config_str =
            "{"
            "    \"interfaces-config\": {"
            "        \"interfaces\": [ ]"
            "    },"
            "    \"preferred-lifetime\": 3000,"
            "    \"rebind-timer\": 2000,"
            "    \"renew-timer\": 1000,"
            "    \"subnet6\": [ ],"
            "    \"valid-lifetime\": 4000,"
            "    \"lease-database\": {"
            "         \"type\": \"memfile\","
            "         \"persist\": false"
            "    },"
            "    \"hooks-libraries\": ["
            "        {"
            "            \"library\": \"" + std::string(CALLOUT_LIBRARY_3) + "\""
            + parameters +
            "        }"
            "    ]"
            "}";

        ConstElementPtr config = Element::fromJSON(config_str);

        // Configure the server.
        ConstElementPtr answer;
        ASSERT_NO_THROW(answer = srv->processConfig(config));

        // Make sure there were no errors.
        int status_code;
        parseAnswer(status_code, answer);
        if (parameters.empty()) {
            EXPECT_EQ(0, status_code);
            EXPECT_EQ(answer->str(), R"({ "result": 0, "text": "Configuration successful." })");
        } else {
            EXPECT_EQ(1, status_code);
            if (parameters.find("fail-without-error") != string::npos) {
                EXPECT_EQ(answer->str(), R"({ "result": 1, "text": "unknown error" })");
            } else if (parameters.find("fail-with-error") != string::npos) {
                EXPECT_EQ(answer->str(),
                          R"({ "result": 1, "text": "user explicitly configured me to fail" })");
            } else {
                GTEST_FAIL() << "unchecked test case";
            }
        }

        // The hook library should have been loaded.
        EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "3"));
        EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));
        // The dhcp6_srv_configured should have been invoked and the provided
        // parameters should be recorded.
        EXPECT_TRUE(checkMarkerFile(SRV_CONFIG_MARKER_FILE,
                                    "3io_contextjson_confignetwork_stateserver_config"));

        // Destroy the server, instance which should unload the libraries.
        srv.reset();

        // The server was destroyed, so the unload() function should now
        // include the library number in its marker file.
        EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "3"));
        EXPECT_TRUE(checkMarkerFile(UNLOAD_MARKER_FILE, "3"));
        EXPECT_TRUE(checkMarkerFile(SRV_CONFIG_MARKER_FILE,
                                    "3io_contextjson_confignetwork_stateserver_config"));
    }
}

// This test verifies that parked-packet-limit is enforced.
TEST_F(HooksDhcpv6SrvTest, leases6ParkedPacketLimit) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"parked-packet-limit\": 1,"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config, *srv_));

    // Verify we have no packets parked.
    const auto& parking_lot = ServerHooks::getServerHooks()
                              .getParkingLotPtr("leases6_committed");
    ASSERT_TRUE(parking_lot);
    ASSERT_EQ(0, parking_lot->size());

    // Statistic should not show any drops.
    EXPECT_EQ(0, getStatistic("pkt6-receive-drop"));

    // This callout uses provided IO service object to post a function
    // that unparks the packet. The packet is parked and can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases6_committed", leases6_committed_park_callout));

    // Create first client and perform SARR.
    Dhcp6Client client1(srv_);
    client1.setInterface("eth1");
    client1.requestAddress(0xabca, IOAddress("2001:db8:1::28"));

    ASSERT_NO_THROW(client1.doSARR());

    // We should be offered an address but the REPLY should not arrive
    // at this point, because the packet is parked.
    ASSERT_FALSE(client1.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases6_committed", callback_name_);

    // Verify we have one parked packet and no drops.
    ASSERT_EQ(1, parking_lot->size());
    EXPECT_EQ(0, getStatistic("pkt6-receive-drop"));

    // Reset all indicators because we'll be now creating a second client.
    resetCalloutBuffers();

    // Create the second client to test that it may communicate with the
    // server while the previous packet is parked.
    Dhcp6Client client2(srv_);
    client2.setInterface("eth1");
    client2.requestAddress(0xabca, IOAddress("2001:db8:1::29"));
    ASSERT_NO_THROW(client2.doSARR());

    // The ADVERTISE should have been returned but not REPLY, this
    // packet should have been dropped.
    ASSERT_FALSE(client2.getContext().response_);

    // Check that no callback was called.
    EXPECT_EQ("", callback_name_);

    // Verify we have one parked packet and one drop.
    ASSERT_EQ(1, parking_lot->size());
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));

    // There should now be one action scheduled on our IO service
    // by the invoked callout. It should unpark the REPLY message
    // for client1.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client1.receiveResponse());
    ASSERT_TRUE(client1.getContext().response_);
    Pkt6Ptr rsp = client1.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::28")));

    // Verify we have no parked packets and one drop.
    ASSERT_EQ(0, parking_lot->size());
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));

    // Should not anything to receive for client2.
    ASSERT_NO_THROW(client2.receiveResponse());
    ASSERT_FALSE(client2.getContext().response_);

    // Reset all indicators because we'll be now creating a second client.
    resetCalloutBuffers();

    // Retry the second client and verify that it is allowed to park
    // and be responded to.
    client2.requestAddress(0xabcb, IOAddress("2001:db8:1::29"));
    ASSERT_NO_THROW(client2.doSARR());

    // The ADVERTISE should have been returned but not REPLY, that
    // packet should have been parked.
    ASSERT_FALSE(client2.getContext().response_);

    // Check that the callback was called.
    EXPECT_EQ("leases6_committed", callback_name_);

    // Verify we again have one parked packet and one drop.
    ASSERT_EQ(1, parking_lot->size());
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));

    // There should now be one action scheduled on our IO service
    // by the invoked callout. It should unpark the REPLY message
    // for client2.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client2.receiveResponse());
    ASSERT_TRUE(client2.getContext().response_);
    rsp = client2.getContext().response_;
    EXPECT_EQ(DHCPV6_REPLY, rsp->getType());
    EXPECT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::29")));

    // Verify we no parked packets and one drop.
    ASSERT_EQ(0, parking_lot->size());
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}


}  // namespace
