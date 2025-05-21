// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/marker_file.h>
#include <dhcp4/tests/test_libraries.h>
#include <hooks/server_hooks.h>
#include <hooks/hooks_manager.h>
#include <hooks/hooks_parser.h>
#include <hooks/callout_manager.h>
#include <stats/stats_mgr.h>
#include <util/multi_threading_mgr.h>

#include <vector>


using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::stats;
using namespace isc::util;

using namespace std;

namespace {

// Checks if hooks are implemented properly.
TEST_F(Dhcpv4SrvTest, Hooks) {
    NakedDhcpv4Srv srv(0);

    // check if appropriate hooks are registered
    int hook_index_dhcp4_srv_configured = -1;
    int hook_index_buffer4_receive = -1;
    int hook_index_buffer4_send = -1;
    int hook_index_lease4_renew = -1;
    int hook_index_lease4_release = -1;
    int hook_index_lease4_decline = -1;
    int hook_index_pkt4_receive = -1;
    int hook_index_pkt4_send = -1;
    int hook_index_select_subnet = -1;
    int hook_index_leases4_committed = -1;
    int hook_index_host4_identifier = -1;
    int hook_index_lease4_offer = -1;
    int hook_index_lease4_server_decline = -1;
    int hook_index_ddns4_update = -1;

    // check if appropriate indexes are set
    EXPECT_NO_THROW(hook_index_dhcp4_srv_configured = ServerHooks::getServerHooks()
                    .getIndex("dhcp4_srv_configured"));
    EXPECT_NO_THROW(hook_index_buffer4_receive = ServerHooks::getServerHooks()
                    .getIndex("buffer4_receive"));
    EXPECT_NO_THROW(hook_index_buffer4_send = ServerHooks::getServerHooks()
                    .getIndex("buffer4_send"));
    EXPECT_NO_THROW(hook_index_lease4_renew = ServerHooks::getServerHooks()
                    .getIndex("lease4_renew"));
    EXPECT_NO_THROW(hook_index_lease4_release = ServerHooks::getServerHooks()
                    .getIndex("lease4_release"));
    EXPECT_NO_THROW(hook_index_lease4_decline = ServerHooks::getServerHooks()
                    .getIndex("lease4_decline"));
    EXPECT_NO_THROW(hook_index_pkt4_receive = ServerHooks::getServerHooks()
                    .getIndex("pkt4_receive"));
    EXPECT_NO_THROW(hook_index_pkt4_send = ServerHooks::getServerHooks()
                    .getIndex("pkt4_send"));
    EXPECT_NO_THROW(hook_index_select_subnet = ServerHooks::getServerHooks()
                    .getIndex("subnet4_select"));
    EXPECT_NO_THROW(hook_index_leases4_committed = ServerHooks::getServerHooks()
                    .getIndex("leases4_committed"));
    EXPECT_NO_THROW(hook_index_host4_identifier = ServerHooks::getServerHooks()
                    .getIndex("host4_identifier"));
    EXPECT_NO_THROW(hook_index_lease4_offer = ServerHooks::getServerHooks()
                    .getIndex("lease4_offer"));
    EXPECT_NO_THROW(hook_index_lease4_server_decline = ServerHooks::getServerHooks()
                    .getIndex("lease4_server_decline"));
    EXPECT_NO_THROW(hook_index_ddns4_update = ServerHooks::getServerHooks()
                    .getIndex("ddns4_update"));

    EXPECT_TRUE(hook_index_dhcp4_srv_configured > 0);
    EXPECT_TRUE(hook_index_buffer4_receive > 0);
    EXPECT_TRUE(hook_index_buffer4_send > 0);
    EXPECT_TRUE(hook_index_lease4_renew > 0);
    EXPECT_TRUE(hook_index_lease4_release > 0);
    EXPECT_TRUE(hook_index_lease4_decline > 0);
    EXPECT_TRUE(hook_index_pkt4_receive > 0);
    EXPECT_TRUE(hook_index_pkt4_send > 0);
    EXPECT_TRUE(hook_index_select_subnet > 0);
    EXPECT_TRUE(hook_index_leases4_committed > 0);
    EXPECT_TRUE(hook_index_host4_identifier > 0);
    EXPECT_TRUE(hook_index_lease4_offer > 0);
    EXPECT_TRUE(hook_index_lease4_server_decline > 0);
    EXPECT_TRUE(hook_index_ddns4_update > 0);
}

// A dummy MAC address, padded with 0s
const uint8_t dummyChaddr[16] = {0, 1, 2, 3, 4, 5, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0 };

// Let's use some creative test content here (128 chars + \0)
const uint8_t dummyFile[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit. Proin mollis placerat metus, at "
    "lacinia orci ornare vitae. Mauris amet.";

// Yet another type of test content (64 chars + \0)
const uint8_t dummySname[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit posuere.";

/// @brief a class dedicated to Hooks testing in DHCPv4 server
///
/// This class has a number of static members, because each non-static
/// method has implicit 'this' parameter, so it does not match callout
/// signature and couldn't be registered. Furthermore, static methods
/// can't modify non-static members (for obvious reasons), so many
/// fields are declared static. It is still better to keep them as
/// one class rather than unrelated collection of global objects.
class HooksDhcpv4SrvTest : public Dhcpv4SrvTest {

public:

    /// @brief creates Dhcpv4Srv and prepares buffers for callouts
    HooksDhcpv4SrvTest() {
        HooksManager::setTestMode(false);
        bool status = HooksManager::unloadLibraries();
        if (!status) {
            cerr << "(fixture ctor) unloadLibraries failed" << endl;
        }

        // Allocate new DHCPv4 Server
        srv_.reset(new NakedDhcpv4Srv(0));

        // Clear static buffers
        resetCalloutBuffers();

        io_service_ = boost::make_shared<IOService>();

        // Reset the hook system in its original state
        HooksManager::unloadLibraries();

        // Clear statistics.
        StatsMgr::instance().removeAll();
    }

    /// @brief destructor (deletes Dhcpv4Srv)
    virtual ~HooksDhcpv4SrvTest() {
        // Clear static buffers
        resetCalloutBuffers();

        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("dhcp4_srv_configured");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("buffer4_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("buffer4_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("pkt4_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("pkt4_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("subnet4_select");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("leases4_committed");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease4_renew");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease4_release");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease4_decline");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("host4_identifier");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease4_offer");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("lease4_server_decline");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("ddns4_update");

        HooksManager::setTestMode(false);
        bool status = HooksManager::unloadLibraries();
        if (!status) {
            cerr << "(fixture dtor) unloadLibraries failed" << endl;
        }

        // Clear statistics.
        StatsMgr::instance().removeAll();
    }

    /// @brief creates an option with specified option code.
    ///
    /// This method is static, because it is used from callouts
    /// that do not have a pointer to HooksDhcpv4SrvTest object
    ///
    /// @param option_code code of option to be created
    ///
    /// @return pointer to create option object
    static OptionPtr createOption(uint16_t option_code) {

        uint8_t payload[] = {
            0xa, 0xb, 0xc, 0xe, 0xf, 0x10, 0x11, 0x12, 0x13, 0x14
        };

        OptionBuffer tmp(payload, payload + sizeof(payload));
        return OptionPtr(new Option(Option::V4, option_code, tmp));
    }

    /// @brief Generates test packet.
    ///
    /// Allocates and generates on-wire buffer that represents test packet, with all
    /// fixed fields set to non-zero values.  Content is not always reasonable.
    ///
    /// See generateTestPacket1() function that returns exactly the same packet as
    /// Pkt4 object.
    ///
    /// @return pointer to allocated Pkt4 object
    /// Returns a vector containing a DHCPv4 packet header.
    Pkt4Ptr
    generateSimpleDiscover() {

        // That is only part of the header. It contains all "short" fields,
        // larger fields are constructed separately.
        uint8_t hdr[] = {
            1, 6, 6, 13,            // op, htype, hlen, hops,
            0x12, 0x34, 0x56, 0x78, // transaction-id
            0, 42, 0x80, 0x00,      // 42 secs, BROADCAST flags
            192, 0, 2, 1,           // ciaddr
            1, 2, 3, 4,             // yiaddr
            192, 0, 2, 255,         // siaddr
            192, 0, 2, 50,          // giaddr
        };

        // Initialize the vector with the header fields defined above.
        vector<uint8_t> buf(hdr, hdr + sizeof(hdr));

        // Append the large header fields.
        copy(dummyChaddr, dummyChaddr + Pkt4::MAX_CHADDR_LEN, back_inserter(buf));
        copy(dummySname, dummySname + Pkt4::MAX_SNAME_LEN, back_inserter(buf));
        copy(dummyFile, dummyFile + Pkt4::MAX_FILE_LEN, back_inserter(buf));

        // Should now have all the header, so check.  The "static_cast" is used
        // to get round an odd bug whereby the linker appears not to find the
        // definition of DHCPV4_PKT_HDR_LEN if it appears within an EXPECT_EQ().
        EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), buf.size());

        // Add magic cookie
        buf.push_back(0x63);
        buf.push_back(0x82);
        buf.push_back(0x53);
        buf.push_back(0x63);

        // Add message type DISCOVER
        buf.push_back(static_cast<uint8_t>(DHO_DHCP_MESSAGE_TYPE));
        buf.push_back(1); // length (just one byte)
        buf.push_back(static_cast<uint8_t>(DHCPDISCOVER));

        Pkt4Ptr dis(new Pkt4(&buf[0], buf.size()));
        // Interface must be selected for a Discover. Server will use the interface
        // name to select a subnet for a client. This test is using fake interfaces
        // and the fake eth0 interface has IPv4 address matching the subnet
        // currently configured for this test.
        dis->setIface("eth1");
        dis->setIndex(ETH1_INDEX);
        return (dis);
    }

    /// @brief Checks if the state of the callout handle associated with a query
    /// was reset after the callout invocation.
    ///
    /// The check includes verification if the status was set to 'continue' and
    /// that all arguments were deleted.
    ///
    /// @param query pointer to the query which callout handle is associated
    /// with.
    void checkCalloutHandleReset(const Pkt4Ptr& query) {
        CalloutHandlePtr callout_handle = query->getCalloutHandle();
        ASSERT_TRUE(callout_handle);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
        EXPECT_TRUE(callout_handle->getArgumentNames().empty());
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("buffer4_receive");

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that changes hwaddr value.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_change_hwaddr_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // If there is at least one option with data
        if (pkt->data_.size() >= Pkt4::DHCPV4_PKT_HDR_LEN) {
            // Offset of the first byte of the CHADDR field. Let's the first
            // byte to some new value that we could later check
            pkt->data_[28] = 0xff;
        }

        // Carry on as usual
        return buffer4_receive_callout(callout_handle);
    }

    /// @brief Test callback that sets skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_skip_callout(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // Carry on as usual
        return buffer4_receive_callout(callout_handle);
    }

    /// @brief Test callback that sets drop flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_receive_drop_callout(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // Carry on as usual
        return buffer4_receive_callout(callout_handle);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt4_receive");

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that changes client-id value.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_change_clientid_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // Get rid of the old client-id
        pkt->delOption(DHO_DHCP_CLIENT_IDENTIFIER);

        // Add a new option
        pkt->addOption(createOption(DHO_DHCP_CLIENT_IDENTIFIER));

        // Carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// @brief Test callback that deletes client-id.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_delete_clientid_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        // Get rid of the old client-id (and no HWADDR)
        vector<uint8_t> mac;
        pkt->delOption(DHO_DHCP_CLIENT_IDENTIFIER);
        pkt->setHWAddr(1, 0, mac); // HWtype 1, hardware len = 0

        // Carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// @brief Test callback that sets skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_skip_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // Carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// @brief Test callback that sets drop flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_receive_drop_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("query4", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // Carry on as usual
        return pkt4_receive_callout(callout_handle);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt4_send");

        callout_handle.getArgument("response4", callback_resp_pkt4_);

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        callout_handle.getArgument("subnet4", callback_subnet4_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        if (callback_resp_pkt4_) {
            callback_resp_options_copy_ = callback_resp_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that changes server-id.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_change_serverid_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // Get rid of the old server-id
        pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER);

        // Add a new option
        pkt->addOption(createOption(DHO_DHCP_SERVER_IDENTIFIER));

        // Carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// @brief Test callback that deletes server-id.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_delete_serverid_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // Get rid of the old client-id
        pkt->delOption(DHO_DHCP_SERVER_IDENTIFIER);

        // Carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// @brief Test callback that sets skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_skip_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// @brief Test callback that sets drop flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt4_send_drop_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // carry on as usual
        return pkt4_send_callout(callout_handle);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework.
    /// @return always 0
    static int
    buffer4_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("buffer4_send");

        callout_handle.getArgument("response4", callback_resp_pkt4_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_resp_pkt4_) {
            callback_resp_options_copy_ = callback_resp_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback changes the output buffer to a hardcoded value.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_send_change_callout(CalloutHandle& callout_handle) {

        Pkt4Ptr pkt;
        callout_handle.getArgument("response4", pkt);

        // modify buffer to set a different payload
        pkt->getBuffer().clear();
        pkt->getBuffer().writeData(dummyFile, sizeof(dummyFile));

        return (0);
    }

    /// @brief Test callback that sets skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_send_skip_callout(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // Carry on as usual
        return buffer4_send_callout(callout_handle);
    }

    /// @brief Test callback that sets drop flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer4_send_drop_callout(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // carry on as usual
        return buffer4_send_callout(callout_handle);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("subnet4_select");

        callout_handle.getArgument("query4", callback_qry_pkt4_);
        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("subnet4collection", callback_subnet4collection_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that picks the other subnet if possible.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_different_subnet_callout(CalloutHandle& callout_handle) {

        // Call the basic callout to record all passed values
        subnet4_select_callout(callout_handle);

        const Subnet4Collection* subnets;
        Subnet4Ptr subnet;
        callout_handle.getArgument("subnet4", subnet);
        callout_handle.getArgument("subnet4collection", subnets);

        // Let's change to a different subnet
        if (subnets->size() > 1) {
            subnet = *std::next(subnets->begin()); // Let's pick the other subnet
            callout_handle.setArgument("subnet4", subnet);
        }

        return (0);
    }

    /// @brief Test callback that sets skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_skip_callout(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        // Carry on as usual
        return subnet4_select_callout(callout_handle);
    }

    /// @brief Test callback that sets drop flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet4_select_drop_callout(CalloutHandle& callout_handle) {

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        // Carry on as usual
        return subnet4_select_callout(callout_handle);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_renew_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_renew");

        callout_handle.getArgument("query4", callback_qry_pkt4_);
        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("lease4", callback_lease4_);
        callout_handle.getArgument("hwaddr", callback_hwaddr_);
        callout_handle.getArgument("clientid", callback_clientid_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that sets the skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_renew_skip_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_renew");

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        return (0);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_release_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_release");

        callout_handle.getArgument("query4", callback_qry_pkt4_);
        callout_handle.getArgument("lease4", callback_lease4_);

        callback_argument_names_ = callout_handle.getArgumentNames();

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that sets the skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_release_skip_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_release");

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        return (0);
    }

    /// @brief Test callback that sets the drop flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_release_drop_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_release");

        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        return (0);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_decline_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_decline");
        callout_handle.getArgument("query4", callback_qry_pkt4_);
        callout_handle.getArgument("lease4", callback_lease4_);

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that sets the skip flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_decline_skip_callout(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

        return (lease4_decline_callout(callout_handle));
    }

    /// @brief Test callback that sets the drop flag.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_decline_drop_callout(CalloutHandle& callout_handle) {
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        return (lease4_decline_callout(callout_handle));
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_offer_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_offer");

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        Lease4CollectionPtr leases4;
        callout_handle.getArgument("leases4", leases4);
        if (leases4->size() > 0) {
            callback_lease4_ = leases4->at(0);
        }

        callout_handle.getArgument("offer_lifetime", callback_offer_lft_);
        callout_handle.getArgument("old_lease", callback_old_lease_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback which asks the server to park the packet.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_offer_park_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_offer");

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        io_service_->post(std::bind(&HooksDhcpv4SrvTest::pkt4_unpark_callout,
                                    callout_handle.getParkingLotHandlePtr(),
                                    callback_qry_pkt4_));

        callout_handle.getParkingLotHandlePtr()->reference(callback_qry_pkt4_);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_PARK);

        Lease4CollectionPtr leases4;
        callout_handle.getArgument("leases4", leases4);
        if (leases4->size() > 0) {
            callback_lease4_ = leases4->at(0);
        }

        callout_handle.getArgument("offer_lifetime", callback_offer_lft_);
        callout_handle.getArgument("old_lease", callback_old_lease_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that marks address in use and asks the server to
    /// park the packet.
    ///
    /// The server's unpark lambda uses the callout argument, "offer_adddress_in_use",
    /// to deteremine if it should decline the lease or send the offer to the
    /// client.  This function sets it to true.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_offer_park_in_use_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_offer");

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        callout_handle.setArgument("offer_address_in_use", true);
        io_service_->post(std::bind(&HooksDhcpv4SrvTest::pkt4_unpark_callout,
                                    callout_handle.getParkingLotHandlePtr(),
                                    callback_qry_pkt4_));

        callout_handle.getParkingLotHandlePtr()->reference(callback_qry_pkt4_);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_PARK);

        Lease4CollectionPtr leases4;
        callout_handle.getArgument("leases4", leases4);
        if (leases4->size() > 0) {
            callback_lease4_ = leases4->at(0);
        }

        callout_handle.getArgument("offer_lifetime", callback_offer_lft_);
        callout_handle.getArgument("old_lease", callback_old_lease_);
        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    leases4_committed_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("leases4_committed");

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        Lease4CollectionPtr leases4;
        callout_handle.getArgument("leases4", leases4);
        if (leases4->size() > 0) {
            callback_lease4_ = leases4->at(0);
        }

        Lease4CollectionPtr deleted_leases4;
        callout_handle.getArgument("deleted_leases4", deleted_leases4);
        if (deleted_leases4->size() > 0) {
            callback_deleted_lease4_ = deleted_leases4->at(0);
        }

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease4_server_decline_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease4_server_decline");
        callout_handle.getArgument("query4", callback_qry_pkt4_);

        Lease4Ptr lease4;
        callout_handle.getArgument("lease4", lease4);
        callback_lease4_ = lease4;

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test callback which asks the server to unpark the packet.
    ///
    /// This can be used with hook points: leases4_committed, lease4_offer.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static void
    pkt4_unpark_callout(ParkingLotHandlePtr parking_lot, Pkt4Ptr query) {
        parking_lot->unpark(query);
    }

    /// @brief Test callback which asks the server to park the packet.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    leases4_committed_park_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("leases4_committed");

        callout_handle.getArgument("query4", callback_qry_pkt4_);

        io_service_->post(std::bind(&HooksDhcpv4SrvTest::pkt4_unpark_callout,
                                    callout_handle.getParkingLotHandlePtr(),
                                    callback_qry_pkt4_));

        callout_handle.getParkingLotHandlePtr()->reference(callback_qry_pkt4_);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_PARK);

        Lease4CollectionPtr leases4;
        callout_handle.getArgument("leases4", leases4);
        if (leases4->size() > 0) {
            callback_lease4_ = leases4->at(0);
        }

        Lease4CollectionPtr deleted_leases4;
        callout_handle.getArgument("deleted_leases4", deleted_leases4);
        if (deleted_leases4->size() > 0) {
            callback_deleted_lease4_ = deleted_leases4->at(0);
        }

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        if (callback_qry_pkt4_) {
            callback_qry_options_copy_ = callback_qry_pkt4_->isCopyRetrievedOptions();
        }

        return (0);
    }

    /// @brief Test host4_identifier callback by setting identifier to "foo".
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    host4_identifier_foo_callout(CalloutHandle& handle) {
        callback_name_ = string("host4_identifier");

        // Make sure the query4 parameter is passed.
        handle.getArgument("query4", callback_qry_pkt4_);

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

    /// @brief Test host4_identifier callout by setting identifier to hwaddr.
    ///
    /// This callout always returns fixed HWADDR: 00:01:02:03:04:05
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    host4_identifier_hwaddr_callout(CalloutHandle& handle) {
        callback_name_ = string("host4_identifier");

        // Make sure the query4 parameter is passed.
        handle.getArgument("query4", callback_qry_pkt4_);

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

    /// @brief Test callback that stores callout name and passed parameters.
    ///
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    ddns4_update_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("ddns4_update");

        callout_handle.getArgument("query4", callback_qry_pkt4_);
        callout_handle.getArgument("response4", callback_resp_pkt4_);
        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("hostname", callback_hostname_);
        callout_handle.getArgument("fwd-update", callback_fwd_update_);
        callout_handle.getArgument("rev-update", callback_rev_update_);
        callout_handle.getArgument("ddns-params", callback_ddns_params_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        sort(callback_argument_names_.begin(), callback_argument_names_.end());

        return (0);
    }


    /// Resets buffers used to store data received by callouts
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_qry_pkt4_.reset();
        callback_resp_pkt4_.reset();
        callback_subnet4_.reset();
        callback_lease4_.reset();
        callback_deleted_lease4_.reset();
        callback_hwaddr_.reset();
        callback_clientid_.reset();
        callback_subnet4collection_ = NULL;
        callback_argument_names_.clear();
        callback_qry_options_copy_ = false;
        callback_resp_options_copy_ = false;
        callback_offer_lft_ = 0;
        callback_old_lease_.reset();
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

    /// Pointer to Dhcpv4Srv that is used in tests
    boost::shared_ptr<NakedDhcpv4Srv> srv_;

    /// Pointer to the IO service used in the tests.
    static IOServicePtr io_service_;

    /// The following fields are used in testing pkt4_receive_callout

    /// String name of the received callout
    static string callback_name_;

    /// Client's query Pkt4 structure returned in the callout
    static Pkt4Ptr callback_qry_pkt4_;

    /// Server's response Pkt4 structure returned in the callout
    static Pkt4Ptr callback_resp_pkt4_;

    /// Pointer to lease4 structure returned in the leases4_committed callout
    static Lease4Ptr callback_lease4_;

    /// Pointer to lease4 structure returned in the leases4_committed callout
    static Lease4Ptr callback_deleted_lease4_;

    /// Hardware address returned in the callout
    static HWAddrPtr callback_hwaddr_;

    /// Client-id returned in the callout
    static ClientIdPtr callback_clientid_;

    /// Pointer to a subnet received by callout
    static Subnet4Ptr callback_subnet4_;

    /// A list of all available subnets (received by callout)
    static const Subnet4Collection* callback_subnet4collection_;

    /// A list of all received arguments
    static vector<string> callback_argument_names_;

    /// Flag indicating if copying retrieved options was enabled for
    /// a query during callout execution.
    static bool callback_qry_options_copy_;

    /// Flag indicating if copying retrieved options was enabled for
    /// a response during callout execution.
    static bool callback_resp_options_copy_;

    /// Offer lifetime returned in the lease4_offer callout
    static uint32_t callback_offer_lft_;

    /// Old lease returned in the lease4_offer callout
    static Lease4Ptr callback_old_lease_;

    /// Hostname argument returned in ddns4_update callout.
    static std::string callback_hostname_;

    /// Forward update flag returned in ddns4_update callout.
    static bool callback_fwd_update_;

    /// Reverse update flag returned in ddns4_update callout.
    static bool callback_rev_update_;

    /// DDNS behavioral parameters returned in ddns4_update callout.
    static DdnsParamsPtr callback_ddns_params_;
};

// The following fields are used in testing pkt4_receive_callout.
// See fields description in the class for details
IOServicePtr HooksDhcpv4SrvTest::io_service_;
string HooksDhcpv4SrvTest::callback_name_;
Pkt4Ptr HooksDhcpv4SrvTest::callback_qry_pkt4_;
Pkt4Ptr HooksDhcpv4SrvTest::callback_resp_pkt4_;
Subnet4Ptr HooksDhcpv4SrvTest::callback_subnet4_;
const Subnet4Collection* HooksDhcpv4SrvTest::callback_subnet4collection_;
HWAddrPtr HooksDhcpv4SrvTest::callback_hwaddr_;
ClientIdPtr HooksDhcpv4SrvTest::callback_clientid_;
Lease4Ptr HooksDhcpv4SrvTest::callback_lease4_;
Lease4Ptr HooksDhcpv4SrvTest::callback_deleted_lease4_;
vector<string> HooksDhcpv4SrvTest::callback_argument_names_;
bool HooksDhcpv4SrvTest::callback_qry_options_copy_;
bool HooksDhcpv4SrvTest::callback_resp_options_copy_;
uint32_t HooksDhcpv4SrvTest::callback_offer_lft_;
Lease4Ptr HooksDhcpv4SrvTest::callback_old_lease_;
std::string HooksDhcpv4SrvTest::callback_hostname_;
bool HooksDhcpv4SrvTest::callback_fwd_update_;
bool HooksDhcpv4SrvTest::callback_rev_update_;
DdnsParamsPtr HooksDhcpv4SrvTest::callback_ddns_params_;

/// @brief Fixture class used to do basic library load/unload tests
class LoadUnloadDhcpv4SrvTest : public ::testing::Test {
public:
    /// @brief Pointer to the tested server object
    boost::shared_ptr<NakedDhcpv4Srv> server_;

    LoadUnloadDhcpv4SrvTest() {
        reset();
        MultiThreadingMgr::instance().setMode(false);
        resetHooksPath();
    }

    /// @brief Destructor
    ~LoadUnloadDhcpv4SrvTest() {
        server_.reset();
        reset();
        MultiThreadingMgr::instance().setMode(false);
        resetHooksPath();
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

    /// @brief Sets the Hooks path from which hooks can be loaded.
    /// @param explicit_path path to use as the hooks path.
    void setHooksTestPath(const std::string explicit_path = "") {
        HooksLibrariesParser::getHooksPath(true,
                                           (!explicit_path.empty() ?
                                            explicit_path : DHCP4_HOOKS_TEST_PATH));
    }

    /// @brief Resets the hooks path to DEFAULT_HOOKS_PATH.
    void resetHooksPath() {
        HooksLibrariesParser::getHooksPath(true);
    }
};

// Checks if callouts installed on buffer4_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "buffer4_receive".
TEST_F(HooksDhcpv4SrvTest, buffer4ReceiveSimple) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_receive", buffer4_receive_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer4_receive", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt4_.get() == discover.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query4"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on buffer4_receive is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv4SrvTest, buffer4ReceiveValueChange) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_receive_change_hwaddr_callout that modifies MAC addr of incoming packet
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_receive", buffer4_receive_change_hwaddr_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr offer = srv_->fake_sent_.front();
    ASSERT_TRUE(offer);

    // Get client-id...
    HWAddrPtr hwaddr = offer->getHWAddr();

    ASSERT_TRUE(hwaddr); // basic sanity check. HWAddr is always present

    // ... and check if it is the modified value
    ASSERT_FALSE(hwaddr->hwaddr_.empty()); // there must be a MAC address
    EXPECT_EQ(0xff, hwaddr->hwaddr_[0]); // check that its first byte was modified

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on buffer4_receive is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, buffer4ReceiveSkip) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_receive_skip_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_receive", buffer4_receive_skip_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on buffer4_receive is able to set drop flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, buffer4ReceiveDrop) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_receive_drop_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_receive", buffer4_receive_drop_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);

    // Drop statistics should be maintained by the callouts, not by the server.
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// Checks if callouts installed on pkt4_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "pkt4_receive".
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveSimple) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt4_receive", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt4_.get() == discover.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query4"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_received is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveValueChange) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_change_clientid_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(DHO_DHCP_CLIENT_IDENTIFIER);
    EXPECT_TRUE(clientid->equals(expected));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_received is able to delete
// existing options and that change impacts server processing (mandatory
// client-id option is deleted, so the packet is expected to be dropped)
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveDeleteClientId) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_receive_delete_clientid_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_delete_clientid_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not send a response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_received is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveSkip) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_receive_skip_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_skip_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_received is able to set drop flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, pkt4ReceiveDrop) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_receive_drop_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_receive", pkt4_receive_drop_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);

    // Drop statistics should be maintained by the callouts, not by the server.
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// Checks if callouts installed on pkt4_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv4SrvTest, pkt4SendSimple) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_send_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("pkt4_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt4Ptr adv = srv_->fake_sent_.front();

    // Check that pkt4 argument passing was successful and returned proper
    // values
    ASSERT_TRUE(callback_qry_pkt4_);
    EXPECT_TRUE(callback_qry_pkt4_.get() == discover.get());
    ASSERT_TRUE(callback_resp_pkt4_);
    EXPECT_TRUE(callback_resp_pkt4_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query4"));
    expected_argument_names.push_back(string("response4"));
    expected_argument_names.push_back(string("subnet4"));
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);
    EXPECT_TRUE(callback_resp_options_copy_);

    // Verify that packet sent to callout had the expected packet events.
    std::list<std::string> expected_events;
    expected_events.push_back(PktEvent::SOCKET_RECEIVED);
    expected_events.push_back(PktEvent::BUFFER_READ);
    expected_events.push_back("process_started");
    expected_events.push_back("process_completed");
    checkPktEvents(callback_qry_pkt4_, expected_events);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_send is able to change
// the values and the packet sent contains those changes
TEST_F(HooksDhcpv4SrvTest, pkt4SendValueChange) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_send_change_serverid_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_change_serverid_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_send callback.
    srv_->run();

    // Check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(DHO_DHCP_SERVER_IDENTIFIER);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(DHO_DHCP_SERVER_IDENTIFIER);
    EXPECT_TRUE(clientid->equals(expected));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_send is able to delete
// existing options and that server applies those changes. In particular,
// we are trying to send a packet without server-id. The packet should
// be sent
TEST_F(HooksDhcpv4SrvTest, pkt4SendDeleteServerId) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_send_delete_serverid_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_delete_serverid_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_send callback.
    srv_->run();

    // Check that the server indeed sent a malformed ADVERTISE
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Get that ADVERTISE
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Make sure that it does not have server-id
    EXPECT_FALSE(adv->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_skip is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, pkt4SendSkip) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_send_skip_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_skip_callout));

    // Let's create a simple REQUEST
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_send callback.
    srv_->run();

    // Check that the server sent the packet
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Get the first packet and check that it has zero length (i.e. the server
    // did not do packing on its own)
    Pkt4Ptr sent = srv_->fake_sent_.front();

    // The actual size of sent packet should be 0
    EXPECT_EQ(0, sent->getBuffer().getLength());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on pkt4_drop is able to set drop flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv4SrvTest, pkt4SendDrop) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install pkt4_send_drop_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt4_send", pkt4_send_drop_callout));

    // Let's create a simple REQUEST
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_send callback.
    srv_->run();

    // Check that the server does not send the packet
    EXPECT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on buffer4_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv4SrvTest, buffer4SendSimple) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_send_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_send", buffer4_send_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer4_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt4Ptr adv = srv_->fake_sent_.front();

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_resp_pkt4_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("response4"));
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_resp_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on buffer4_send are indeed called and that
// the output buffer can be changed.
TEST_F(HooksDhcpv4SrvTest, buffer4SendChange) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_send_change_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_send", buffer4_send_change_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_send callback.
    srv_->run();

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt4Ptr adv = srv_->fake_sent_.front();

    // The callout is supposed to fill the output buffer with dummyFile content
    ASSERT_EQ(sizeof(dummyFile), adv->getBuffer().getLength());
    EXPECT_EQ(0, memcmp(adv->getBuffer().getData(), dummyFile, sizeof(dummyFile)));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on buffer4_send can set skip flag and that flag
// causes the packet to not be sent
TEST_F(HooksDhcpv4SrvTest, buffer4SendSkip) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_send_skip_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_send", buffer4_send_skip_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer4_send", callback_name_);

    // Check that there is no packet sent.
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callouts installed on buffer4_send can set drop flag and that flag
// causes the packet to not be sent
TEST_F(HooksDhcpv4SrvTest, buffer4SendDrop) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install buffer4_send_drop_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer4_send", buffer4_send_drop_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered buffer4_send callback.
    srv_->run();

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("buffer4_send", callback_name_);

    // Check that there is no packet sent
    EXPECT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// This test checks if subnet4_select callout is triggered and reports
// valid parameters
TEST_F(HooksDhcpv4SrvTest, subnet4SelectSimple) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"id\": 1, "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"eth0\" "
        " }, {"
        "    \"id\": 2, "
        "    \"pools\": [ { \"pool\": \"192.0.3.0/25\" } ],"
        "    \"subnet\": \"192.0.3.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Commit the config
    CfgMgr::instance().commit();

    // Install subnet4_select_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet4_select", subnet4_select_callout));

    // Prepare discover packet. Server should select first subnet for it
    Pkt4Ptr discover = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    discover->setRemoteAddr(IOAddress("192.0.2.1"));
    discover->setIface("eth1");
    discover->setIndex(ETH1_INDEX);
    OptionPtr clientid = generateClientId();
    discover->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt4Ptr adv = srv_->processDiscover(discover);

    // Check if we get response at all
    ASSERT_TRUE(adv);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("subnet4_select", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt4_.get() == discover.get());

    const Subnet4Collection* exp_subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();

    // The server is supposed to pick the first subnet, because of matching
    // interface. Check that the value is reported properly.
    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(callback_subnet4_.get(), exp_subnets->begin()->get());

    // Server is supposed to report two subnets
    ASSERT_EQ(exp_subnets->size(), callback_subnet4collection_->size());
    ASSERT_GE(exp_subnets->size(), 2);

    // Compare that the available subnets are reported as expected
    EXPECT_TRUE((*exp_subnets->begin())->get() == (*callback_subnet4collection_->begin())->get());
    EXPECT_TRUE((*std::next(exp_subnets->begin()))->get() == (*std::next(callback_subnet4collection_->begin()))->get());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// This test checks if callout installed on subnet4_select hook point can pick
// a different subnet.
TEST_F(HooksDhcpv4SrvTest, subnet4SelectChange) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Configure 2 subnets, both directly reachable over local interface
    // (let's not complicate the matter with relays)
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"id\": 1, "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"interface\": \"eth0\" "
        " }, {"
        "    \"id\": 2, "
        "    \"pools\": [ { \"pool\": \"192.0.3.0/25\" } ],"
        "    \"subnet\": \"192.0.3.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Install subnet4_select_different_subnet_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet4_select", subnet4_select_different_subnet_callout));

    // Prepare discover packet. Server should select first subnet for it
    Pkt4Ptr discover = Pkt4Ptr(new Pkt4(DHCPDISCOVER, 1234));
    discover->setRemoteAddr(IOAddress("192.0.2.1"));
    discover->setIface("eth0");
    discover->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    discover->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt4Ptr adv = srv_->processDiscover(discover);

    // Check if we get response at all
    ASSERT_TRUE(adv);

    // The response should have an address from second pool, so let's check it
    IOAddress addr = adv->getYiaddr();
    EXPECT_NE("0.0.0.0", addr.toText());

    // Get all subnets and use second subnet for verification
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Advertised address must belong to the second pool (in subnet's range,
    // in dynamic pool)
    auto subnet = subnets->begin();
    ++subnet;
    EXPECT_TRUE((*subnet)->inRange(addr));
    EXPECT_TRUE((*subnet)->inPool(Lease::TYPE_V4, addr));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks that subnet4_select is able to drop the packet.
TEST_F(HooksDhcpv4SrvTest, subnet4SelectDrop) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install subnet4_select_drop_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet4_select", subnet4_select_drop_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered subnet4_select callback.
    srv_->run();

    // Check that the server dropped the packet and did not produce any response
    ASSERT_EQ(0, srv_->fake_sent_.size());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);

    // Drop statistics should be maintained by the callouts, not by the server.
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// This test verifies that the leases4_committed hook point is not triggered
// for the DHCPDISCOVER.
TEST_F(HooksDhcpv4SrvTest, leases4CommittedDiscover) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install leases4_committed_callout
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDiscover());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases4_committed hook point is not triggered
// for the DHCPINFORM.
TEST_F(HooksDhcpv4SrvTest, leases4CommittedInform) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.useRelay();
    ASSERT_NO_THROW(client.doInform());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases4_committed hook
// point is executed as a result of DHCPREQUEST message sent to allocate new
// lease or renew an existing lease.
TEST_F(HooksDhcpv4SrvTest, leases4CommittedRequest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("deleted_leases4");
    expected_argument_names.push_back("leases4");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.100", callback_lease4_->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    EXPECT_FALSE(callback_deleted_lease4_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Renew the lease and make sure that the callout has been executed.
    client.setState(Dhcp4Client::RENEWING);
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // Renewed lease should be returned.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.100", callback_lease4_->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    EXPECT_FALSE(callback_deleted_lease4_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Let's try to renew again but force the client to request a different
    // address.
    client.ciaddr_ = IOAddress("192.0.2.101");

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // New lease should be returned.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.101", callback_lease4_->addr_.toText());

    // The old lease should have been deleted.
    ASSERT_TRUE(callback_deleted_lease4_);
    EXPECT_EQ("192.0.2.100", callback_deleted_lease4_->addr_.toText());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Now request an address that can't be allocated.
    client.ciaddr_ = IOAddress("10.0.0.1");

    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we did not receive a response. Since we're
    // not authoritative, there should not be a DHCPNAK.
    ASSERT_FALSE(client.getContext().response_);

    // Check that no callback was not called.
    EXPECT_EQ("", callback_name_);
    EXPECT_FALSE(callback_lease4_);
    EXPECT_FALSE(callback_deleted_lease4_);
}

// This test verifies that the leases4_committed callout is executed
// with declined leases as argument when DHCPDECLINE is processed.
TEST_F(HooksDhcpv4SrvTest, leases4CommittedDecline) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.useRelay();
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    resetCalloutBuffers();

    ASSERT_NO_THROW(client.doDecline());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("deleted_leases4");
    expected_argument_names.push_back("leases4");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // No new allocations.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.100", callback_lease4_->addr_.toText());
    EXPECT_EQ(Lease::STATE_DECLINED, callback_lease4_->state_);

    // Released lease should be returned.
    EXPECT_FALSE(callback_deleted_lease4_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the leases4_committed callout is executed
// with deleted leases as argument when DHCPRELEASE is processed.
TEST_F(HooksDhcpv4SrvTest, leases4CommittedRelease) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    resetCalloutBuffers();

    ASSERT_NO_THROW(client.doRelease());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("deleted_leases4");
    expected_argument_names.push_back("leases4");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // No new allocations.
    EXPECT_FALSE(callback_lease4_);

    // Released lease should be returned.
    ASSERT_TRUE(callback_deleted_lease4_);
    EXPECT_EQ("192.0.2.100", callback_deleted_lease4_->addr_.toText());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the callout installed on the leases4_committed hook
// point is executed as a result of DHCPREQUEST message sent to reuse an
// existing lease.
TEST_F(HooksDhcpv4SrvTest, leases4CommittedCache) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_callout));

    // Modify the subnet to reuse leases.
    subnet_->setCacheThreshold(.25);

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("deleted_leases4");
    expected_argument_names.push_back("leases4");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.100", callback_lease4_->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    EXPECT_FALSE(callback_deleted_lease4_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();

    // Renew the lease and make sure that the callout has been executed.
    client.setState(Dhcp4Client::RENEWING);
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // Renewed lease should not be present because it was reused.
    EXPECT_FALSE(callback_lease4_);

    // Deleted lease must not be present, because it renews the same address.
    EXPECT_FALSE(callback_deleted_lease4_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that it is possible to park a packet as a result of
// the leases4_committed callouts.
TEST_F(HooksDhcpv4SrvTest, leases4CommittedParkRequests) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // This callout uses provided IO service object to post a function
    // that unparks the packet. The packet is parked and can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_park_callout));

    // Create first client and perform DORA.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client1.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // We should be offered an address but the DHCPACK should not arrive
    // at this point, because the packet is parked.
    ASSERT_FALSE(client1.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("leases4_committed", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("deleted_leases4");
    expected_argument_names.push_back("leases4");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be passed to the callout.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.100", callback_lease4_->addr_.toText());

    // Deleted lease must not be present, because it is a new allocation.
    EXPECT_FALSE(callback_deleted_lease4_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client1.getContext().query_);

    // Reset all indicators because we'll be now creating a second client.
    resetCalloutBuffers();

    // Create the second client to test that it may communicate with the
    // server while the previous packet is parked.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client2.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.101"))));

    // The DHCPOFFER should have been returned but not DHCPACK, as this
    // packet got parked too.
    ASSERT_FALSE(client2.getContext().response_);

    // Check that the callback called is indeed the one we installed.
    EXPECT_EQ("leases4_committed", callback_name_);

    // There should be now two actions scheduled on our IO service
    // by the invoked callouts. They unpark both DHCPACK messages.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client1.receiveResponse());
    Pkt4Ptr rsp = client1.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPACK, rsp->getType());
    EXPECT_EQ("192.0.2.100", rsp->getYiaddr().toText());

    // Receive and check the second response.
    ASSERT_NO_THROW(client2.receiveResponse());
    rsp = client2.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPACK, rsp->getType());
    EXPECT_EQ("192.0.2.101", rsp->getYiaddr().toText());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client2.getContext().query_);
}

// This test verifies that incoming (positive) REQUEST/Renewing can be handled
// properly and that callout installed on lease4_renew is triggered with
// expected parameters.
TEST_F(HooksDhcpv4SrvTest, lease4RenewSimple) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install lease4_renew_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_renew", lease4_renew_callout));

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2,
                              &client_id_->getClientId()[0], client_id_->getClientId().size(),
                              temp_valid, temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RENEW
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress(addr));
    req->setYiaddr(addr);
    req->setCiaddr(addr); // client's address
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    req->setHWAddr(hwaddr2);

    req->addOption(clientid);
    req->addOption(srv_->getServerID());

    // Pass it to the server and hope for a response
    Pkt4Ptr ack = srv_->processRequest(req);

    // Check if we get response at all
    checkResponse(ack, DHCPACK, 1234);

    // Check that the lease is really in the database
    l = checkLease(ack, clientid, req->getHWAddr(), addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt were really updated
    EXPECT_EQ(l->valid_lft_, subnet_->getValid());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_renew", callback_name_);

    // Check that query4 argument passing was successful and
    // returned proper value
    EXPECT_TRUE(callback_qry_pkt4_.get() == req.get());

    // Check that hwaddr parameter is passed properly
    ASSERT_TRUE(callback_hwaddr_);
    EXPECT_TRUE(*callback_hwaddr_ == *req->getHWAddr());

    // Check that the subnet is passed properly
    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(callback_subnet4_->toText(), subnet_->toText());

    ASSERT_TRUE(callback_clientid_);
    ASSERT_TRUE(client_id_);
    EXPECT_TRUE(*client_id_ == *callback_clientid_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("subnet4");
    expected_argument_names.push_back("clientid");
    expected_argument_names.push_back("hwaddr");
    expected_argument_names.push_back("lease4");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());

    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that a callout installed on lease4_renew can trigger
// the server to not renew a lease.
TEST_F(HooksDhcpv4SrvTest, lease4RenewSkip) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install lease4_renew_skip_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_renew", lease4_renew_skip_callout));

    // Generate client-id also sets client_id_ member
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // let's create a lease and put it in the LeaseMgr
    uint8_t hwaddr2_data[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hwaddr2(new HWAddr(hwaddr2_data, sizeof(hwaddr2_data), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(IOAddress("192.0.2.106"), hwaddr2,
                              &client_id_->getClientId()[0], client_id_->getClientId().size(),
                              temp_valid, temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Check that preferred, valid and cltt really set.
    // Constructed lease looks as if it was assigned 10 seconds ago
    EXPECT_EQ(l->valid_lft_, temp_valid);
    EXPECT_EQ(l->cltt_, temp_timestamp);

    // Let's create a RENEW
    Pkt4Ptr req = Pkt4Ptr(new Pkt4(DHCPREQUEST, 1234));
    req->setRemoteAddr(IOAddress(addr));
    req->setYiaddr(addr);
    req->setCiaddr(addr); // client's address
    req->setIface("eth0");
    req->setIndex(ETH0_INDEX);
    req->setHWAddr(hwaddr2);

    req->addOption(clientid);
    req->addOption(srv_->getServerID());

    // Pass it to the server and hope for a response
    Pkt4Ptr ack = srv_->processRequest(req);
    ASSERT_TRUE(ack);

    // Check that the lease is really in the database
    l = checkLease(ack, clientid, req->getHWAddr(), addr);
    ASSERT_TRUE(l);

    // Check that valid and cltt were NOT updated
    EXPECT_EQ(temp_valid, l->valid_lft_);
    EXPECT_EQ(temp_timestamp, l->cltt_);

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(lease));

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(req);
}

// This test verifies that valid RELEASE triggers lease4_release callouts
TEST_F(HooksDhcpv4SrvTest, lease4ReleaseSimple) {
    IfaceMgrTestConfig test_config(true);
    CfgMgr::instance().getCurrentCfg()->getCfgExpiration()->setFlushReclaimedTimerWaitTime(0);
    CfgMgr::instance().getCurrentCfg()->getCfgExpiration()->setHoldReclaimedTime(0);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install lease4_release_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_release", lease4_release_callout));

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, hw, &client_id_->getClientId()[0],
                              client_id_->getClientId().size(), temp_valid,
                              temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setCiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv_->getServerID());
    rel->setHWAddr(hw);

    // Note: there is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv_->processRelease(rel));

    // The lease should be gone from LeaseMgr
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_FALSE(l);

    // Try to get the lease by hardware address
    Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*hw);
    EXPECT_EQ(leases.size(), 0);

    // Try to get it by hw/subnet_id combination
    l = LeaseMgrFactory::instance().getLease4(*hw, subnet_->getID());
    EXPECT_FALSE(l);

    // Try by client-id
    leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    EXPECT_EQ(leases.size(), 0);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_FALSE(l);

    // Ok, the lease is *really* not there.

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_release", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt4_.get() == rel.get());

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("lease4");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(rel);
}

// This test verifies that valid RELEASE triggers lease4_release callouts
// This test is using infinite lease with lease affinity enabled.
TEST_F(HooksDhcpv4SrvTest, lease4ReleaseSimpleInfiniteLease) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = Lease::INFINITY_LFT;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install lease4_release_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_release", lease4_release_callout));

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, hw, &client_id_->getClientId()[0],
                              client_id_->getClientId().size(), temp_valid,
                              temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setCiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv_->getServerID());
    rel->setHWAddr(hw);

    // Note: there is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv_->processRelease(rel));

    // The lease should be gone from LeaseMgr
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_FALSE(l);

    // Try to get the lease by hardware address
    Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*hw);
    EXPECT_EQ(leases.size(), 0);

    // Try to get it by hw/subnet_id combination
    l = LeaseMgrFactory::instance().getLease4(*hw, subnet_->getID());
    EXPECT_FALSE(l);

    // Try by client-id
    leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    EXPECT_EQ(leases.size(), 0);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_FALSE(l);

    // Ok, the lease is *really* not there.

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_release", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt4_.get() == rel.get());

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("lease4");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(rel);
}

// This test verifies that valid RELEASE triggers lease4_release callouts
TEST_F(HooksDhcpv4SrvTest, lease4ReleaseSimpleNoDelete) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install lease4_release_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_release", lease4_release_callout));

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, hw, &client_id_->getClientId()[0],
                              client_id_->getClientId().size(), temp_valid,
                              temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setCiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv_->getServerID());
    rel->setHWAddr(hw);

    // Note: there is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv_->processRelease(rel));

    // The lease should not be gone from LeaseMgr
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_TRUE(l);

    // Try to get the lease by hardware address
    Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*hw);
    EXPECT_EQ(leases.size(), 1);

    // Try to get it by hw/subnet_id combination
    l = LeaseMgrFactory::instance().getLease4(*hw, subnet_->getID());
    EXPECT_TRUE(l);

    // Try by client-id
    leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    EXPECT_EQ(leases.size(), 1);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_TRUE(l);

    // Ok, the lease is *really* there.

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_release", callback_name_);

    // Check that pkt4 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_qry_pkt4_.get() == rel.get());

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("lease4");
    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(rel);
}

// This test verifies that skip flag returned by a callout installed on the
// lease4_release hook point will keep the lease.
TEST_F(HooksDhcpv4SrvTest, lease4ReleaseSkip) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install lease4_release_skip_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_release", lease4_release_skip_callout));

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, hw, &client_id_->getClientId()[0],
                              client_id_->getClientId().size(), temp_valid,
                              temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv_->getServerID());
    rel->setHWAddr(hw);

    // Note: there is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv_->processRelease(rel));

    // The lease should be still there
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_TRUE(l);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_TRUE(l);

    // Try to get the lease by hardware address, should succeed
    Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*hw);
    EXPECT_EQ(leases.size(), 1);

    // Try by client-id, should be successful as well.
    leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    EXPECT_EQ(leases.size(), 1);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(rel);
}

// This test verifies that drop flag returned by a callout installed on the
// lease4_release hook point will keep the lease.
TEST_F(HooksDhcpv4SrvTest, lease4ReleaseDrop) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    const IOAddress addr("192.0.2.106");
    const uint32_t temp_valid = 100;
    const time_t temp_timestamp = time(NULL) - 10;

    // Install lease4_release_drop_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_release", lease4_release_drop_callout));

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_V4, addr));

    // Let's create a lease and put it in the LeaseMgr
    uint8_t mac_addr[] = { 0, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe };
    HWAddrPtr hw(new HWAddr(mac_addr, sizeof(mac_addr), HTYPE_ETHER));
    Lease4Ptr used(new Lease4(addr, hw, &client_id_->getClientId()[0],
                              client_id_->getClientId().size(), temp_valid,
                              temp_timestamp, subnet_->getID()));
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(used));

    // Check that the lease is really in the database
    Lease4Ptr l = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(l);

    // Let's create a RELEASE
    // Generate client-id also duid_
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setRemoteAddr(addr);
    rel->setYiaddr(addr);
    rel->addOption(clientid);
    rel->addOption(srv_->getServerID());
    rel->setHWAddr(hw);

    // Note: there is no response to RELEASE in DHCPv4
    EXPECT_NO_THROW(srv_->processRelease(rel));

    // The lease should be still there
    l = LeaseMgrFactory::instance().getLease4(addr);
    EXPECT_TRUE(l);

    // Try by client-id/subnet-id
    l = LeaseMgrFactory::instance().getLease4(*client_id_, subnet_->getID());
    EXPECT_TRUE(l);

    // Try to get the lease by hardware address, should succeed
    Lease4Collection leases = LeaseMgrFactory::instance().getLease4(*hw);
    EXPECT_EQ(leases.size(), 1);

    // Try by client-id, should be successful as well.
    leases = LeaseMgrFactory::instance().getLease4(*client_id_);
    EXPECT_EQ(leases.size(), 1);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(rel);
}

// This test checks that the basic decline hook (lease4_decline) is
// triggered properly.
TEST_F(HooksDhcpv4SrvTest, lease4DeclineSimple) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install lease4_decline_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_decline", lease4_decline_callout));

    HooksManager::setTestMode(true);

    // Conduct the actual DORA + Decline.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    acquireAndDecline(client, "01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_PASS);

    EXPECT_EQ("lease4_decline", callback_name_);

    // Verifying DHCPDECLINE is a bit tricky, as it is created somewhere in
    // acquireAndDecline. We'll just verify that it's really a DECLINE
    // and that its address is equal to what we have in LeaseMgr.
    ASSERT_TRUE(callback_qry_pkt4_);
    ASSERT_TRUE(callback_lease4_);

    // Check that it's the proper packet that was reported.
    EXPECT_EQ(DHCPDECLINE, callback_qry_pkt4_->getType());

    // Extract the address being declined.
    OptionCustomPtr opt_declined_addr = boost::dynamic_pointer_cast<
        OptionCustom>(callback_qry_pkt4_->getOption(DHO_DHCP_REQUESTED_ADDRESS));
    ASSERT_TRUE(opt_declined_addr);
    IOAddress addr(opt_declined_addr->readAddress());

    // And try to get a matching lease from the lease manager.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);
    EXPECT_EQ(Lease::STATE_DECLINED, from_mgr->state_);

    // Let's now check that those 3 things (packet, lease returned and lease from
    // the lease manager) all match.
    EXPECT_EQ(addr, from_mgr->addr_);
    EXPECT_EQ(addr, callback_lease4_->addr_);

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// Test that the lease4_decline hook point can handle SKIP status.
TEST_F(HooksDhcpv4SrvTest, lease4DeclineSkip) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install lease4_decline_skip_callout. It will set the status to skip
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_decline", lease4_decline_skip_callout));

    HooksManager::setTestMode(true);

    // Conduct the actual DORA + Decline. The DECLINE should fail, as the
    // hook will set the status to SKIP.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    acquireAndDecline(client, "01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_FAIL);

    EXPECT_EQ("lease4_decline", callback_name_);

    // Verifying DHCPDECLINE is a bit tricky, as it is created somewhere in
    // acquireAndDecline. We'll just verify that it's really a DECLINE
    // and that its address is equal to what we have in LeaseMgr.
    ASSERT_TRUE(callback_qry_pkt4_);
    ASSERT_TRUE(callback_lease4_);

    // Check that it's the proper packet that was reported.
    EXPECT_EQ(DHCPDECLINE, callback_qry_pkt4_->getType());

    // Extract the address being declined.
    OptionCustomPtr opt_declined_addr = boost::dynamic_pointer_cast<
        OptionCustom>(callback_qry_pkt4_->getOption(DHO_DHCP_REQUESTED_ADDRESS));
    ASSERT_TRUE(opt_declined_addr);
    IOAddress addr(opt_declined_addr->readAddress());

    // And try to get a matching lease from the lease manager. The lease should
    // still be there in default state, not in declined state.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);
    EXPECT_EQ(Lease::STATE_DEFAULT, from_mgr->state_);

    // As a final sanity check, let's now check that those 3 things (packet,
    // lease returned and lease from the lease manager) all match.
    EXPECT_EQ(addr, from_mgr->addr_);
    EXPECT_EQ(addr, callback_lease4_->addr_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// Test that the lease4_decline hook point can handle DROP status.
TEST_F(HooksDhcpv4SrvTest, lease4DeclineDrop) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install lease4_decline_drop_callout. It will set the status to drop
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_decline", lease4_decline_drop_callout));

    HooksManager::setTestMode(true);

    // Conduct the actual DORA + Decline. The DECLINE should fail, as the
    // hook will set the status to DROP.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    acquireAndDecline(client, "01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_FAIL);

    EXPECT_EQ("lease4_decline", callback_name_);

    // Verifying DHCPDECLINE is a bit tricky, as it is created somewhere in
    // acquireAndDecline. We'll just verify that it's really a DECLINE
    // and that its address is equal to what we have in LeaseMgr.
    ASSERT_TRUE(callback_qry_pkt4_);
    ASSERT_TRUE(callback_lease4_);

    // Check that it's the proper packet that was reported.
    EXPECT_EQ(DHCPDECLINE, callback_qry_pkt4_->getType());

    // Extract the address being declined.
    OptionCustomPtr opt_declined_addr = boost::dynamic_pointer_cast<
        OptionCustom>(callback_qry_pkt4_->getOption(DHO_DHCP_REQUESTED_ADDRESS));
    ASSERT_TRUE(opt_declined_addr);
    IOAddress addr(opt_declined_addr->readAddress());

    // And try to get a matching lease from the lease manager. The lease should
    // still be there in default state, not in declined state.
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(addr);
    ASSERT_TRUE(from_mgr);
    EXPECT_EQ(Lease::STATE_DEFAULT, from_mgr->state_);

    // As a final sanity check, let's now check that those 3 things (packet,
    // lease returned and lease from the lease manager) all match.
    EXPECT_EQ(addr, from_mgr->addr_);
    EXPECT_EQ(addr, callback_lease4_->addr_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// Checks if callout installed on host4_identifier can generate an
// identifier and whether that identifier is actually used.
TEST_F(HooksDhcpv4SrvTest, host4Identifier) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Configure a subnet with host reservation. The reservation is based on
    // flexible identifier value of 'foo'. That's exactly what the
    // host4_identifier_foo_callout sets.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"host-reservation-identifiers\": [ \"flex-id\" ], "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1, "
        "    \"interface\": \"eth0\", "
        "    \"reservations\": ["
        "        {"
        "            \"flex-id\": \"'foo'\","
        "            \"ip-address\": \"192.0.2.201\""
        "        }"
        "    ]"
        "} ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    ASSERT_TRUE(json);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Install host4_identifier_foo_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "host4_identifier", host4_identifier_foo_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Make sure the address offered is the one that was reserved.
    EXPECT_EQ("192.0.2.201", adv->getYiaddr().toText());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Checks if callout installed on host4_identifier can generate an identifier of
// other type. This particular callout always returns hwaddr.
TEST_F(HooksDhcpv4SrvTest, host4IdentifierHWAddr) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Configure a subnet with host reservation. The reservation is based on
    // flexible identifier value of 'foo'. That's exactly what the
    // host4_identifier_foo_callout sets.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"host-reservation-identifiers\": [ \"flex-id\" ], "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/25\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1, "
        "    \"interface\": \"eth0\", "
        "    \"reservations\": ["
        "        {"
        "            \"hw-address\": \"00:01:02:03:04:05\","
        "            \"ip-address\": \"192.0.2.201\""
        "        }"
        "    ]"
        "} ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    ASSERT_TRUE(json);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Install host4_identifier_hwaddr_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "host4_identifier", host4_identifier_hwaddr_callout));

    // Let's create a simple DISCOVER
    Pkt4Ptr discover = generateSimpleDiscover();

    // Simulate that we have received that traffic
    srv_->fakeReceive(discover);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive4(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt4_receive callback.
    srv_->run();

    // check that the server did send a response
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt4Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Make sure the address offered is the one that was reserved.
    EXPECT_EQ("192.0.2.201", adv->getYiaddr().toText());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(discover);
}

// Verifies that libraries are unloaded by server destruction
// The callout libraries write their library index number to a marker
// file upon load and unload, making it simple to test whether or not
// the load and unload callouts have been invoked.
TEST_F(LoadUnloadDhcpv4SrvTest, unloadLibraries) {

    ASSERT_NO_THROW(server_.reset(new NakedDhcpv4Srv()));

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
TEST_F(LoadUnloadDhcpv4SrvTest, failLoadIncompatibleLibraries) {

    ASSERT_NO_THROW(server_.reset(new NakedDhcpv4Srv()));

    // Ensure no marker files to start with.
    ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Load the test libraries
    HookLibsCollection libraries;
    libraries.push_back(make_pair(std::string(CALLOUT_LIBRARY_2),
                                  ConstElementPtr()));

    ASSERT_FALSE(HooksManager::loadLibraries(libraries, true));

    // The library is missing multi_threading_compatible function so loading
    // should fail
    EXPECT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    libraries.clear();
    libraries.push_back(make_pair(std::string(CALLOUT_LIBRARY_3),
                                  ConstElementPtr()));

    ASSERT_FALSE(HooksManager::loadLibraries(libraries, true));

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

// Checks if callouts installed on the dhcp4_srv_configured ared indeed called
// and all the necessary parameters are passed.
TEST_F(LoadUnloadDhcpv4SrvTest, Dhcpv4SrvConfigured) {
    setHooksTestPath();
    for (auto const& parameters : vector<string>{
        "",
        R"(, "parameters": { "mode": "fail-without-error" } )",
        R"(, "parameters": { "mode": "fail-with-error" } )"}) {

        reset();

        boost::shared_ptr<ControlledDhcpv4Srv> srv(new ControlledDhcpv4Srv(0));

        // Ensure no marker files to start with.
        ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
        ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));
        ASSERT_FALSE(checkMarkerFileExists(SRV_CONFIG_MARKER_FILE));

        // Minimal valid configuration for the server. It includes the
        // section which loads the callout library #3, which implements
        // dhcp4_srv_configured callout. MT needs to be disabled
        // since the library is single-threaded.
        string config_str =
            "{"
            "    \"interfaces-config\": {"
            "        \"interfaces\": [ ]"
            "    },"
            "    \"rebind-timer\": 2000,"
            "    \"renew-timer\": 1000,"
            "    \"subnet4\": [ ],"
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
          R"(    ],
                 "multi-threading": {
                    "enable-multi-threading": false
                }
            })";

        ConstElementPtr config = Element::fromJSON(config_str);

        // Configure the server.
        ConstElementPtr answer;
        ASSERT_NO_THROW(answer = srv->processConfig(config));

        // Make sure there were no errors.
        int status_code;
        parseAnswer(status_code, answer);
        if (parameters.empty()) {
            EXPECT_EQ(0, status_code);
            string expected = "{ \"arguments\": { \"hash\": \"";
            ConstElementPtr config =
                CfgMgr::instance().getStagingCfg()->toElement();
            expected += BaseCommandMgr::getHash(config);
            expected += "\" }, \"result\": 0, \"text\": ";
            expected += "\"Configuration successful.\" }";
            EXPECT_EQ(answer->str(), expected);
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
        // The dhcp4_srv_configured should have been invoked and the provided
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

// This test verifies that parked-packet-limit is properly enforced.
TEST_F(HooksDhcpv4SrvTest, leases4ParkedPacketLimit) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"parked-packet-limit\": 1,"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1, "
        "    \"interface\": \"eth1\" "
        " } ],"
        "\"valid-lifetime\": 4000"
        "}";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Commit the config
    CfgMgr::instance().commit();
    IfaceMgr::instance().openSockets4();

    // This callout uses the provided IO service object to post a function
    // that unparks the packet. Once the packet is parked, it can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "leases4_committed", leases4_committed_park_callout));

    // Statistic should not show any drops.
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));

    // Create a client and initiate a DORA cycle for it.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Check that the callback called is indeed the one we installed
    ASSERT_EQ("leases4_committed", callback_name_);

    // Make sure that we have not received a response.
    ASSERT_FALSE(client.getContext().response_);

    // Verify we have a packet parked.
    auto const& parking_lot = ServerHooks::getServerHooks().getParkingLotPtr("leases4_committed");
    ASSERT_TRUE(parking_lot);
    ASSERT_EQ(1, parking_lot->size());

    // Clear callout buffers.
    resetCalloutBuffers();

    // Create a second client and initiate a DORA for it.
    // Since the parking lot limit has been reached, the packet
    // should be dropped with no response.
    Dhcp4Client client2(Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client2.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.101"))));

    // Check that no callback was called.
    ASSERT_EQ("", callback_name_);

    // Make sure that we have not received a response.
    ASSERT_FALSE(client2.getContext().response_);

    // Verify we have not parked another packet.
    ASSERT_EQ(1, parking_lot->size());

    // Statistic should show one drop.
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));

    // Invoking poll should run the scheduled action only for
    // the first client.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client.receiveResponse());
    Pkt4Ptr rsp = client.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPACK, rsp->getType());
    EXPECT_EQ("192.0.2.100", rsp->getYiaddr().toText());

    // Verify we have no parked packets.
    ASSERT_EQ(0, parking_lot->size());

    resetCalloutBuffers();

    // Try client2 again.
    ASSERT_NO_THROW(client2.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.101"))));

    // Check that the callback called is indeed the one we installed
    ASSERT_EQ("leases4_committed", callback_name_);

    // Make sure that we have not received a response.
    ASSERT_FALSE(client2.getContext().response_);

    // Verify we parked the packet.
    ASSERT_EQ(1, parking_lot->size());

    // Invoking poll should run the scheduled action.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client2.receiveResponse());
    rsp = client2.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPACK, rsp->getType());
    EXPECT_EQ("192.0.2.101", rsp->getYiaddr().toText());

    // Verify we have no parked packets.
    ASSERT_EQ(0, parking_lot->size());

    // Statistic should still show one drop.
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// This test verifies that the lease4_offer hook point is triggered
// for the DHCPDISCOVER.
TEST_F(HooksDhcpv4SrvTest, lease4OfferDiscover) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install lease4_offer_callout
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDiscover());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_offer", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("leases4");
    expected_argument_names.push_back("offer_lifetime");
    expected_argument_names.push_back("old_lease");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be returned.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.100", callback_lease4_->addr_.toText());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the lease4_offer hook point is not triggered
// for the DHCPINFORM.
TEST_F(HooksDhcpv4SrvTest, lease4OfferInform) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.useRelay();
    ASSERT_NO_THROW(client.doInform());

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the lease4_offer hook point is not triggered
// for the DHCPDECLINE.
TEST_F(HooksDhcpv4SrvTest, lease4OfferDecline) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.useRelay();
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    resetCalloutBuffers();

    ASSERT_NO_THROW(client.doDecline());

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the lease4_offer hook point is not triggered
// for the DHCPREQUEST.
TEST_F(HooksDhcpv4SrvTest, lease4OfferRequest) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    resetCalloutBuffers();

    client.setState(Dhcp4Client::RENEWING);
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that the callout wasn't called on DHCPREQUEST.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that the lease4_offer hook point is not triggered
// for the DHCPRELEASE.
TEST_F(HooksDhcpv4SrvTest, lease4OfferRelease) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_callout));

    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    resetCalloutBuffers();

    ASSERT_NO_THROW(client.doRelease());

    // Make sure that the callout wasn't called.
    EXPECT_TRUE(callback_name_.empty());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);
}

// This test verifies that it is possible to park a packet as a result of
// the lease4_offer callout.
TEST_F(HooksDhcpv4SrvTest, lease4OfferParkRequests) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // This callout uses provided IO service object to post a function
    // that unparks the packet. The packet is parked and can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_park_callout));

    // Create first client and perform DORA.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client1.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // We should not be offered an address yet
    // at this point, because the packet is parked.
    ASSERT_FALSE(client1.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_offer", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("leases4");
    expected_argument_names.push_back("offer_lifetime");
    expected_argument_names.push_back("old_lease");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Newly allocated lease should be passed to the callout.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ("192.0.2.100", callback_lease4_->addr_.toText());

    // Pkt passed to a callout must be configured to copy retrieved options.
    EXPECT_TRUE(callback_qry_options_copy_);

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client1.getContext().query_);

    // Reset all indicators because we'll be now creating a second client.
    resetCalloutBuffers();

    // Create the second client to test that it may communicate with the
    // server while the previous packet is parked.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client2.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.101"))));

    // We should not be offered an address yet
    // at this point, because the packet is parked.
    ASSERT_FALSE(client2.getContext().response_);

    // Check that the callback called is indeed the one we installed.
    EXPECT_EQ("lease4_offer", callback_name_);

    // There should be now two actions scheduled on our IO service
    // by the invoked callouts. They unpark both DHCPOFFER messages.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client1.receiveResponse());
    Pkt4Ptr rsp = client1.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPOFFER, rsp->getType());
    EXPECT_EQ("192.0.2.100", rsp->getYiaddr().toText());

    // Receive and check the second response.
    ASSERT_NO_THROW(client2.receiveResponse());
    rsp = client2.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPOFFER, rsp->getType());
    EXPECT_EQ("192.0.2.101", rsp->getYiaddr().toText());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client2.getContext().query_);
}

// This test verifies that parked-packet-limit is properly enforced with lease4_offer callout.
TEST_F(HooksDhcpv4SrvTest, lease4OfferParkedPacketLimit) {
    IfaceMgrTestConfig test_config(true);

    string config = "{ \"interfaces-config\": {"
                    "    \"interfaces\": [ \"*\" ]"
                    "},"
                    "\"rebind-timer\": 2000, "
                    "\"renew-timer\": 1000, "
                    "\"parked-packet-limit\": 1,"
                    "\"subnet4\": [ { "
                    "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
                    "    \"subnet\": \"192.0.2.0/24\", "
                    "    \"id\": 1, "
                    "    \"interface\": \"eth1\" "
                    " } ],"
                    "\"valid-lifetime\": 4000"
                    "}";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Commit the config
    CfgMgr::instance().commit();
    IfaceMgr::instance().openSockets4();

    // This callout uses the provided IO service object to post a function
    // that unparks the packet. Once the packet is parked, it can be unparked
    // by simply calling IOService::poll.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_park_callout));

    // Statistic should not show any drops.
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));

    // Create a client and initiate a DORA cycle for it.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Check that the callback called is indeed the one we installed
    ASSERT_EQ("lease4_offer", callback_name_);

    // Make sure that we have not received a response.
    ASSERT_FALSE(client.getContext().response_);

    // Verify we have a packet parked.
    auto const& parking_lot = ServerHooks::getServerHooks().getParkingLotPtr("lease4_offer");
    ASSERT_TRUE(parking_lot);
    ASSERT_EQ(1, parking_lot->size());

    // Clear callout buffers.
    resetCalloutBuffers();

    // Create a second client and initiate a DORA for it.
    // Since the parking lot limit has been reached, the packet
    // should be dropped with no response.
    Dhcp4Client client2(Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client2.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.101"))));

    // Check that no callback was called.
    ASSERT_EQ("", callback_name_);

    // Make sure that we have not received a response.
    ASSERT_FALSE(client2.getContext().response_);

    // Verify we have not parked another packet.
    ASSERT_EQ(1, parking_lot->size());

    // Statistic should show one drop.
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));

    // Invoking poll should run the scheduled action only for
    // the first client.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client.receiveResponse());
    Pkt4Ptr rsp = client.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPOFFER, rsp->getType());
    EXPECT_EQ("192.0.2.100", rsp->getYiaddr().toText());

    // Verify we have no parked packets.
    ASSERT_EQ(0, parking_lot->size());

    resetCalloutBuffers();

    // Try client2 again.
    ASSERT_NO_THROW(client2.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.101"))));

    // Check that the callback called is indeed the one we installed
    ASSERT_EQ("lease4_offer", callback_name_);

    // Make sure that we have not received a response.
    ASSERT_FALSE(client2.getContext().response_);

    // Verify we parked the packet.
    ASSERT_EQ(1, parking_lot->size());

    // Invoking poll should run the scheduled action.
    ASSERT_NO_THROW(io_service_->poll());

    // Receive and check the first response.
    ASSERT_NO_THROW(client2.receiveResponse());
    rsp = client2.getContext().response_;
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPOFFER, rsp->getType());
    EXPECT_EQ("192.0.2.101", rsp->getYiaddr().toText());

    // Verify we have no parked packets.
    ASSERT_EQ(0, parking_lot->size());

    // Statistic should still show one drop.
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// This test verifies that a lease4_offer callout that marks a
// lease as in-use and unparks the query, causes the offer to be
// discarded, and Dhcpv4Srv::serverDecline() to be invoked. This should,
// in turn, cause the lease to be declined in the lease store and the
// callout for lease4_server_decline to be called.
TEST_F(HooksDhcpv4SrvTest, lease4OfferDiscoverDecline) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Install lease4_offer callout that will mark lease as in-use and unpark
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_offer", lease4_offer_park_in_use_callout));

    // Install lease4_server_decline callout
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "lease4_server_decline", lease4_server_decline_callout));

    // Make sure there's no existing lease.
    IOAddress expected_address("192.0.2.100");
    ASSERT_FALSE(LeaseMgrFactory::instance().getLease4(expected_address));

    // Generate a DISCOVER.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    ASSERT_NO_THROW(client.doDiscover());

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("lease4_offer", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("leases4");
    expected_argument_names.push_back("offer_lifetime");
    expected_argument_names.push_back("old_lease");
    expected_argument_names.push_back("offer_address_in_use");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Declined lease should be returned.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ(expected_address, callback_lease4_->addr_);

    // Since the callout set offer_address_in_use flag to true the offer should
    // have been discarded. Make sure that we did not receive a response.
    ASSERT_FALSE(client.getContext().response_);

    // Clear static buffers
    resetCalloutBuffers();

    // Polling the IOService should unpark the packet invoking the unpark lambda
    // which should invoke Dhcp4Srv::serverDecline().  This should decline the
    // lease in the db and then invoke lease4_server_decline callback.
    ASSERT_NO_THROW(io_service_->poll());

    // The lease should be in the lease store and in the DECLINED state.
    Lease4Ptr declined_lease = LeaseMgrFactory::instance().getLease4(callback_lease4_->addr_);
    ASSERT_TRUE(declined_lease);
    EXPECT_EQ(declined_lease->state_, Lease::STATE_DECLINED);

    // Check that we called lease4_server_decline callback.
    EXPECT_EQ("lease4_server_decline", callback_name_);

    // Check if all expected parameters were really received
    expected_argument_names.clear();
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("lease4");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Declined lease should be returned.
    ASSERT_TRUE(callback_lease4_);
    EXPECT_EQ(expected_address, callback_lease4_->addr_);
}

// Checks that postponed hook start service can fail.
TEST_F(LoadUnloadDhcpv4SrvTest, startServiceFail) {
    setHooksTestPath();

    boost::shared_ptr<ControlledDhcpv4Srv> srv(new ControlledDhcpv4Srv(0));

    // Ensure no marker files to start with.
    ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));
    ASSERT_FALSE(checkMarkerFileExists(SRV_CONFIG_MARKER_FILE));

    // Minimal valid configuration for the server. It includes the
    // section which loads the callout library #4, which implements
    // dhcp4_srv_configured callout and a failing start service.
    string config_str =
        "{ \"Dhcp4\": {"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ ]"
        "    },"
        "    \"rebind-timer\": 2000,"
        "    \"renew-timer\": 1000,"
        "    \"subnet4\": [ ],"
        "    \"valid-lifetime\": 4000,"
        "    \"lease-database\": {"
        "         \"type\": \"memfile\","
        "         \"persist\": false"
        "    },"
        "    \"hooks-libraries\": ["
        "        {"
        "            \"library\": \"" + std::string(CALLOUT_LIBRARY_4) + "\""
        "        }"
        "    ]"
        "} }";

    ConstElementPtr config = Element::fromJSON(config_str);

    // Configure the server.
    ConstElementPtr answer;
    ASSERT_NO_THROW(answer = CommandMgr::instance().processCommand(createCommand("config-set", config)));

    // Make sure there was an error with expected message.
    int status_code;
    parseAnswer(status_code, answer);
    EXPECT_EQ(1, status_code);
    EXPECT_EQ(answer->str(),
              R"({ "result": 1, "text": "Error initializing hooks: start service failed" })");

    // The hook library should have been loaded.
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "4"));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));
    // The dhcp4_srv_configured should have been invoked and the provided
    // parameters should be recorded.
    EXPECT_TRUE(checkMarkerFile(SRV_CONFIG_MARKER_FILE,
                                "4io_contextjson_confignetwork_stateserver_config"));

    // Destroy the server, instance which should unload the libraries.
    srv.reset();

    // The server was destroyed, so the unload() function should now
    // include the library number in its marker file.
    EXPECT_TRUE(checkMarkerFile(UNLOAD_MARKER_FILE, "4"));
}

// This test verifies that the callout installed on the ddns4_update hook
// point is executed as a result of DHCPREQUEST message sent to allocate
// a lease.
TEST_F(HooksDhcpv4SrvTest, ddns4Update) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"parked-packet-limit\": 1,"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1, "
        "    \"interface\": \"eth1\" "
        " } ],"
        " \"dhcp-ddns\" : {"
        "       \"enable-updates\": true"
        "},"
        " \"ddns-send-updates\": true,"
        " \"ddns-qualifying-suffix\": \"example.com\","
        "\"valid-lifetime\": 4000"
        "}";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = Dhcpv4SrvTest::configure(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    // Commit the config
    CfgMgr::instance().commit();
    IfaceMgr::instance().openSockets4();

    // Start D2 client so NCR send will succeed.
    srv_->startD2();

    // Register ddns4_update callout.
    ASSERT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                    "ddns4_update", ddns4_update_callout));

    // Carry out a DORA.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    client.includeFQDN(Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E,
                                       "client-name", Option4ClientFqdn::PARTIAL);
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<IOAddress>(new IOAddress("192.0.2.100"))));

    // Make sure that we received a response
    ASSERT_TRUE(client.getContext().response_);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("ddns4_update", callback_name_);

    // Check if all expected parameters were really received
    vector<string> expected_argument_names;
    expected_argument_names.push_back("query4");
    expected_argument_names.push_back("response4");
    expected_argument_names.push_back("subnet4");
    expected_argument_names.push_back("hostname");
    expected_argument_names.push_back("fwd-update");
    expected_argument_names.push_back("rev-update");
    expected_argument_names.push_back("ddns-params");

    sort(expected_argument_names.begin(), expected_argument_names.end());
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);

    // Verify query in the callout is as expected.
    ASSERT_TRUE(callback_qry_pkt4_);
    ASSERT_TRUE(client.getContext().query_);
    EXPECT_EQ(client.getContext().query_->getType(), callback_qry_pkt4_->getType());
    EXPECT_EQ(client.getContext().query_->getLabel(), callback_qry_pkt4_->getLabel());

    // Verify response in the callout is as expected.
    ASSERT_TRUE(callback_resp_pkt4_);
    ASSERT_TRUE(client.getContext().response_);
    EXPECT_EQ(client.getContext().response_->getType(), callback_resp_pkt4_->getType());
    EXPECT_EQ(client.getContext().response_->getLabel(), callback_resp_pkt4_->getLabel());

    // Verify the subnet.
    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(1, callback_subnet4_->getID());

    // Verify the hostname.
    EXPECT_EQ("client-name.example.com.", callback_hostname_);

    // Verify the update direction flags.
    EXPECT_TRUE(callback_fwd_update_);
    EXPECT_TRUE(callback_rev_update_);

    // Verify behavioral parameter set.
    ASSERT_TRUE(callback_ddns_params_);
    EXPECT_EQ("example.com", callback_ddns_params_->getQualifyingSuffix());

    // Check if the callout handle state was reset after the callout.
    checkCalloutHandleReset(client.getContext().query_);

    resetCalloutBuffers();
}

}  // namespace
