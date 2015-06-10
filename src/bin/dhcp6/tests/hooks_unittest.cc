// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/utils.h>
#include <util/buffer.h>
#include <util/range_utilities.h>
#include <hooks/server_hooks.h>

#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp/tests/pkt_captures.h>
#include <cc/command_interpreter.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace isc;
using namespace isc::data;
using namespace isc::test;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::hooks;
using namespace std;

// namespace has to be named, because friends are defined in Dhcpv6Srv class
// Maybe it should be isc::test?
namespace {

// Checks if hooks are implemented properly.
TEST_F(Dhcpv6SrvTest, Hooks) {
    NakedDhcpv6Srv srv(0);

    // check if appropriate hooks are registered
    int hook_index_buffer6_receive = -1;
    int hook_index_buffer6_send    = -1;
    int hook_index_lease6_renew    = -1;
    int hook_index_lease6_release  = -1;
    int hook_index_pkt6_received   = -1;
    int hook_index_select_subnet   = -1;
    int hook_index_pkt6_send       = -1;

    // check if appropriate indexes are set
    EXPECT_NO_THROW(hook_index_buffer6_receive = ServerHooks::getServerHooks()
                    .getIndex("buffer6_receive"));
    EXPECT_NO_THROW(hook_index_buffer6_send = ServerHooks::getServerHooks()
                    .getIndex("buffer6_send"));
    EXPECT_NO_THROW(hook_index_lease6_renew = ServerHooks::getServerHooks()
                    .getIndex("lease6_renew"));
    EXPECT_NO_THROW(hook_index_lease6_release = ServerHooks::getServerHooks()
                    .getIndex("lease6_release"));
    EXPECT_NO_THROW(hook_index_pkt6_received = ServerHooks::getServerHooks()
                    .getIndex("pkt6_receive"));
    EXPECT_NO_THROW(hook_index_select_subnet = ServerHooks::getServerHooks()
                    .getIndex("subnet6_select"));
    EXPECT_NO_THROW(hook_index_pkt6_send     = ServerHooks::getServerHooks()
                    .getIndex("pkt6_send"));

    EXPECT_TRUE(hook_index_pkt6_received   > 0);
    EXPECT_TRUE(hook_index_select_subnet   > 0);
    EXPECT_TRUE(hook_index_pkt6_send       > 0);
    EXPECT_TRUE(hook_index_buffer6_receive > 0);
    EXPECT_TRUE(hook_index_buffer6_send    > 0);
    EXPECT_TRUE(hook_index_lease6_renew    > 0);
    EXPECT_TRUE(hook_index_lease6_release  > 0);
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
    HooksDhcpv6SrvTest() {

        // Allocate new DHCPv6 Server
        srv_.reset(new NakedDhcpv6Srv(0));

        // Clear static buffers
        resetCalloutBuffers();
    }

    /// @brief destructor (deletes Dhcpv6Srv)
    ~HooksDhcpv6SrvTest() {
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

    /// test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt6_receive");

        callout_handle.getArgument("query6", callback_pkt6_);

        callback_argument_names_ = callout_handle.getArgumentNames();
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

        callout_handle.setSkip(true);

        // Carry on as usual
        return pkt6_receive_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    buffer6_receive_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("buffer6_receive");

        callout_handle.getArgument("query6", callback_pkt6_);

        callback_argument_names_ = callout_handle.getArgumentNames();
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
        callout_handle.setSkip(true);

        // Carry on as usual
        return buffer6_receive_callout(callout_handle);
    }

    /// Test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    pkt6_send_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("pkt6_send");

        callout_handle.getArgument("response6", callback_pkt6_);

        callback_argument_names_ = callout_handle.getArgumentNames();
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

        callout_handle.setSkip(true);

        // carry on as usual
        return pkt6_send_callout(callout_handle);
    }

    /// Test callback that stores received callout name and subnet6 values
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet6_select_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("subnet6_select");

        callout_handle.getArgument("query6", callback_pkt6_);
        callout_handle.getArgument("subnet6", callback_subnet6_);
        callout_handle.getArgument("subnet6collection", callback_subnet6collection_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that picks the other subnet if possible.
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    subnet6_select_different_subnet_callout(CalloutHandle& callout_handle) {

        // Call the basic calllout to record all passed values
        subnet6_select_callout(callout_handle);

        const Subnet6Collection* subnets;
        Subnet6Ptr subnet;
        callout_handle.getArgument("subnet6", subnet);
        callout_handle.getArgument("subnet6collection", subnets);

        // Let's change to a different subnet
        if (subnets->size() > 1) {
            subnet = (*subnets)[1]; // Let's pick the other subnet
            callout_handle.setArgument("subnet6", subnet);
        }

        return (0);
    }

    /// Test callback that stores received callout name and pkt6 value
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_renew_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_renew");

        callout_handle.getArgument("query6", callback_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);
        callout_handle.getArgument("ia_na", callback_ia_na_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// The following values are used by the callout to override
    /// renewed lease parameters
    static const uint32_t override_iaid_;
    static const uint32_t override_t1_;
    static const uint32_t override_t2_;
    static const uint32_t override_preferred_;
    static const uint32_t override_valid_;

    /// Test callback that overrides received lease. It updates
    /// T1, T2, preferred and valid lifetimes
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_renew_update_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_renew");

        callout_handle.getArgument("query6", callback_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);
        callout_handle.getArgument("ia_na", callback_ia_na_);

        // Let's override some values in the lease
        callback_lease6_->iaid_          = override_iaid_;
        callback_lease6_->t1_            = override_t1_;
        callback_lease6_->t2_            = override_t2_;
        callback_lease6_->preferred_lft_ = override_preferred_;
        callback_lease6_->valid_lft_     = override_valid_;

        // Override the values to be sent to the client as well
        callback_ia_na_->setIAID(override_iaid_);
        callback_ia_na_->setT1(override_t1_);
        callback_ia_na_->setT2(override_t2_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that sets the skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_renew_skip_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_renew");

        callout_handle.setSkip(true);

        return (0);
    }

    /// Test callback that stores received callout name passed parameters
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_release_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_release");

        callout_handle.getArgument("query6", callback_pkt6_);
        callout_handle.getArgument("lease6", callback_lease6_);

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// Test callback that sets the skip flag
    /// @param callout_handle handle passed by the hooks framework
    /// @return always 0
    static int
    lease6_release_skip_callout(CalloutHandle& callout_handle) {
        callback_name_ = string("lease6_release");

        callout_handle.setSkip(true);

        return (0);
    }

    /// Resets buffers used to store data received by callouts
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_pkt6_.reset();
        callback_subnet6_.reset();
        callback_lease6_.reset();
        callback_ia_na_.reset();
        callback_subnet6collection_ = NULL;
        callback_argument_names_.clear();
    }

    /// Pointer to Dhcpv6Srv that is used in tests
    boost::scoped_ptr<NakedDhcpv6Srv> srv_;

    // The following fields are used in testing pkt6_receive_callout

    /// String name of the received callout
    static string callback_name_;

    /// Pkt6 structure returned in the callout
    static Pkt6Ptr callback_pkt6_;

    /// Pointer to lease6
    static Lease6Ptr callback_lease6_;

    /// Pointer to IA_NA option being renewed
    static boost::shared_ptr<Option6IA> callback_ia_na_;

    /// Pointer to a subnet received by callout
    static Subnet6Ptr callback_subnet6_;

    /// A list of all available subnets (received by callout)
    static const Subnet6Collection* callback_subnet6collection_;

    /// A list of all received arguments
    static vector<string> callback_argument_names_;
};

// The following parameters are used by callouts to override
// renewed lease parameters
const uint32_t HooksDhcpv6SrvTest::override_iaid_ = 1000;
const uint32_t HooksDhcpv6SrvTest::override_t1_ = 1001;
const uint32_t HooksDhcpv6SrvTest::override_t2_ = 1002;
const uint32_t HooksDhcpv6SrvTest::override_preferred_ = 1003;
const uint32_t HooksDhcpv6SrvTest::override_valid_ = 1004;

// The following fields are used in testing pkt6_receive_callout.
// See fields description in the class for details
string HooksDhcpv6SrvTest::callback_name_;
Pkt6Ptr HooksDhcpv6SrvTest::callback_pkt6_;
Subnet6Ptr HooksDhcpv6SrvTest::callback_subnet6_;
const Subnet6Collection* HooksDhcpv6SrvTest::callback_subnet6collection_;
vector<string> HooksDhcpv6SrvTest::callback_argument_names_;
Lease6Ptr HooksDhcpv6SrvTest::callback_lease6_;
boost::shared_ptr<Option6IA> HooksDhcpv6SrvTest::callback_ia_na_;

// Checks if callouts installed on pkt6_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "buffer6_receive".
TEST_F(HooksDhcpv6SrvTest, simple_buffer6_receive) {

    // Install pkt6_receive_callout
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
    EXPECT_TRUE(callback_pkt6_.get() == sol.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query6"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on buffer6_receive is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv6SrvTest, valueChange_buffer6_receive) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_change_clientid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the server did send a reposonce
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt6Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(D6O_CLIENTID);

    ASSERT_TRUE(clientid);

    // ... and check if it is the modified value
    EXPECT_EQ(0xff, clientid->getData()[0]);
}

// Checks if callouts installed on buffer6_receive is able to delete
// existing options and that change impacts server processing (mandatory
// client-id option is deleted, so the packet is expected to be dropped)
TEST_F(HooksDhcpv6SrvTest, deleteClientId_buffer6_receive) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_delete_clientid));

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
}

// Checks if callouts installed on buffer6_received is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, skip_buffer6_receive) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "buffer6_receive", buffer6_receive_skip));

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
}

// Checks if callouts installed on pkt6_receive are indeed called and the
// all necessary parameters are passed.
//
// Note that the test name does not follow test naming convention,
// but the proper hook name is "pkt6_receive".
TEST_F(HooksDhcpv6SrvTest, simple_pkt6_receive) {

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
    EXPECT_TRUE(callback_pkt6_.get() == sol.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("query6"));

    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on pkt6_received is able to change
// the values and the parameters are indeed used by the server.
TEST_F(HooksDhcpv6SrvTest, valueChange_pkt6_receive) {

    // Install pkt6_receive_callout
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

    // Check that the server did send a reposonce
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Make sure that we received a response
    Pkt6Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Get client-id...
    OptionPtr clientid = adv->getOption(D6O_CLIENTID);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(D6O_CLIENTID);
    EXPECT_TRUE(clientid->equals(expected));
}

// Checks if callouts installed on pkt6_received is able to delete
// existing options and that change impacts server processing (mandatory
// client-id option is deleted, so the packet is expected to be dropped)
TEST_F(HooksDhcpv6SrvTest, deleteClientId_pkt6_receive) {

    // Install pkt6_receive_callout
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
}

// Checks if callouts installed on pkt6_received is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, skip_pkt6_receive) {

    // Install pkt6_receive_callout
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
}


// Checks if callouts installed on pkt6_send are indeed called and the
// all necessary parameters are passed.
TEST_F(HooksDhcpv6SrvTest, simple_pkt6_send) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_callout));

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
    EXPECT_EQ("pkt6_send", callback_name_);

    // Check that there is one packet sent
    ASSERT_EQ(1, srv_->fake_sent_.size());
    Pkt6Ptr adv = srv_->fake_sent_.front();

    // Check that pkt6 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt6_.get() == adv.get());

    // Check that all expected parameters are there
    vector<string> expected_argument_names;
    expected_argument_names.push_back(string("response6"));
    EXPECT_TRUE(expected_argument_names == callback_argument_names_);
}

// Checks if callouts installed on pkt6_send is able to change
// the values and the packet sent contains those changes
TEST_F(HooksDhcpv6SrvTest, valueChange_pkt6_send) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_change_serverid));

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
    OptionPtr clientid = adv->getOption(D6O_SERVERID);

    // ... and check if it is the modified value
    OptionPtr expected = createOption(D6O_SERVERID);
    EXPECT_TRUE(clientid->equals(expected));
}

// Checks if callouts installed on pkt6_send is able to delete
// existing options and that server applies those changes. In particular,
// we are trying to send a packet without server-id. The packet should
// be sent
TEST_F(HooksDhcpv6SrvTest, deleteServerId_pkt6_send) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_delete_serverid));

    // Let's create a simple SOLICIT
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the server indeed sent a malformed ADVERTISE
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // Get that ADVERTISE
    Pkt6Ptr adv = srv_->fake_sent_.front();
    ASSERT_TRUE(adv);

    // Make sure that it does not have server-id
    EXPECT_FALSE(adv->getOption(D6O_SERVERID));
}

// Checks if callouts installed on pkt6_skip is able to set skip flag that
// will cause the server to not process the packet (drop), even though it is valid.
TEST_F(HooksDhcpv6SrvTest, skip_pkt6_send) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "pkt6_send", pkt6_send_skip));

    // Let's create a simple REQUEST
    Pkt6Ptr sol = Pkt6Ptr(PktCaptures::captureSimpleSolicit());

    // Simulate that we have received that traffic
    srv_->fakeReceive(sol);

    // Server will now process to run its normal loop, but instead of calling
    // IfaceMgr::receive6(), it will read all packets from the list set by
    // fakeReceive()
    // In particular, it should call registered pkt6_receive callback.
    srv_->run();

    // Check that the server send the packet
    ASSERT_EQ(1, srv_->fake_sent_.size());

    // But the sent packet should have 0 length (we told the server to
    // skip pack(), but did not do packing outselves)
    Pkt6Ptr sent = srv_->fake_sent_.front();

    // The actual size of sent packet should be 0
    EXPECT_EQ(0, sent->getBuffer().getLength());
}

// This test checks if subnet6_select callout is triggered and reports
// valid parameters
TEST_F(HooksDhcpv6SrvTest, subnet6_select) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet6_select", subnet6_select_callout));

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

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = isc::config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Prepare solicit packet. Server should select first subnet for it
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr adv = srv_->processSolicit(sol);

    // Check if we get response at all
    ASSERT_TRUE(adv);

    // Check that the callback called is indeed the one we installed
    EXPECT_EQ("subnet6_select", callback_name_);

    // Check that pkt6 argument passing was successful and returned proper value
    EXPECT_TRUE(callback_pkt6_.get() == sol.get());

    const Subnet6Collection* exp_subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();

    // The server is supposed to pick the first subnet, because of matching
    // interface. Check that the value is reported properly.
    ASSERT_TRUE(callback_subnet6_);
    EXPECT_EQ(callback_subnet6_.get(), exp_subnets->front().get());

    // Server is supposed to report two subnets
    ASSERT_EQ(exp_subnets->size(), callback_subnet6collection_->size());

    // Compare that the available subnets are reported as expected
    EXPECT_TRUE((*exp_subnets)[0].get() == (*callback_subnet6collection_)[0].get());
    EXPECT_TRUE((*exp_subnets)[1].get() == (*callback_subnet6collection_)[1].get());
}

// This test checks if callout installed on subnet6_select hook point can pick
// a different subnet.
TEST_F(HooksDhcpv6SrvTest, subnet_select_change) {

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "subnet6_select", subnet6_select_different_subnet_callout));

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

    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(status);
    comment_ = isc::config::parseAnswer(rcode_, status);
    ASSERT_EQ(0, rcode_);

    CfgMgr::instance().commit();

    // Prepare solicit packet. Server should select first subnet for it
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("fe80::abcd"));
    sol->setIface(valid_iface_);
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Pass it to the server and get an advertise
    Pkt6Ptr adv = srv_->processSolicit(sol);

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
    EXPECT_TRUE((*subnets)[1]->inRange(addr_opt->getAddress()));
    EXPECT_TRUE((*subnets)[1]->inPool(Lease::TYPE_NA, addr_opt->getAddress()));
}

// This test verifies that incoming (positive) RENEW can be handled properly,
// and the lease6_renew callouts are triggered.
TEST_F(HooksDhcpv6SrvTest, basic_lease6_renew) {
    NakedDhcpv6Srv srv(0);

    // Install pkt6_receive_callout
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
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->t1_, subnet_->getT1());
    EXPECT_NE(l->t2_, subnet_->getT2());
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
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
    EXPECT_TRUE(callback_pkt6_);
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
    boost::shared_ptr<Option6IAAddr> addr_opt = checkIA_NA(reply, 234, subnet_->getT1(),
                                                           subnet_->getT2());

    ASSERT_TRUE(addr_opt);
    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);

    // Check that the lease has been returned
    ASSERT_TRUE(callback_lease6_);

    // Check that the returned lease6 in callout is the same as the one in the
    // database
    EXPECT_TRUE(*callback_lease6_ == *l);
}

// This test verifies that incoming (positive) RENEW can be handled properly,
// and the lease6_renew callouts are able to change the lease being updated.
TEST_F(HooksDhcpv6SrvTest, leaseUpdate_lease6_renew) {
    NakedDhcpv6Srv srv(0);

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_renew", lease6_renew_update_callout));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->t1_, subnet_->getT1());
    EXPECT_NE(l->t2_, subnet_->getT2());
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
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

    // Check if we get response at all
    checkResponse(reply, DHCPV6_REPLY, 1234);

    OptionPtr tmp = reply->getOption(D6O_IA_NA);
    ASSERT_TRUE(tmp);

    // Check that IA_NA was returned and that there's an address included
    boost::shared_ptr<Option6IAAddr> addr_opt = checkIA_NA(reply, 1000, 1001, 1002);

    ASSERT_TRUE(addr_opt);
    // Check that the lease is really in the database
    l = checkLease(duid_, reply->getOption(D6O_IA_NA), addr_opt);
    ASSERT_TRUE(l);

    // Check that we chose the distinct override values
    ASSERT_NE(override_t1_,        subnet_->getT1());
    ASSERT_NE(override_t2_,        subnet_->getT2());
    ASSERT_NE(override_preferred_, subnet_->getPreferred());
    EXPECT_NE(override_valid_,     subnet_->getValid());

    // Check that T1, T2, preferred, valid were overridden the the callout
    EXPECT_EQ(override_t1_, l->t1_);
    EXPECT_EQ(override_t2_, l->t2_);
    EXPECT_EQ(override_preferred_, l->preferred_lft_);
    EXPECT_EQ(override_valid_, l->valid_lft_);

    // Checking for CLTT is a bit tricky if we want to avoid off by 1 errors
    int32_t cltt = static_cast<int32_t>(l->cltt_);
    int32_t expected = static_cast<int32_t>(time(NULL));
    // Equality or difference by 1 between cltt and expected is ok.
    EXPECT_GE(1, abs(cltt - expected));

    EXPECT_TRUE(LeaseMgrFactory::instance().deleteLease(addr_opt->getAddress()));
}

// This test verifies that incoming (positive) RENEW can be handled properly,
// and the lease6_renew callouts are able to set the skip flag that will
// reject the renewal
TEST_F(HooksDhcpv6SrvTest, skip_lease6_renew) {
    NakedDhcpv6Srv srv(0);

    // Install pkt6_receive_callout
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
                               501, 502, 503, 504, subnet_->getID(),
                               HWAddrPtr(), 0));
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Check that the lease is really in the database
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                        addr);
    ASSERT_TRUE(l);

    // Check that T1, T2, preferred, valid and cltt really set and not using
    // previous (500, 501, etc.) values
    EXPECT_NE(l->t1_, subnet_->getT1());
    EXPECT_NE(l->t2_, subnet_->getT2());
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));

    // Let's create a RENEW
    Pkt6Ptr req = Pkt6Ptr(new Pkt6(DHCPV6_RENEW, 1234));
    req->setRemoteAddr(IOAddress("fe80::abcd"));
    req->setIface("eth0");
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
    EXPECT_NE(l->t1_, subnet_->getT1());
    EXPECT_NE(l->t2_, subnet_->getT2());
    EXPECT_NE(l->preferred_lft_, subnet_->getPreferred());
    EXPECT_NE(l->valid_lft_, subnet_->getValid());
    EXPECT_NE(l->cltt_, time(NULL));
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
TEST_F(HooksDhcpv6SrvTest, basic_lease6_release) {
    NakedDhcpv6Srv srv(0);

    // Install pkt6_receive_callout
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
                               501, 502, 503, 504, subnet_->getID(),
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
    EXPECT_TRUE(callback_pkt6_);
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
TEST_F(HooksDhcpv6SrvTest, skip_lease6_release) {
    NakedDhcpv6Srv srv(0);

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_release", lease6_release_skip_callout));

    const IOAddress addr("2001:db8:1:1::cafe:babe");
    const uint32_t iaid = 234;

    // Generate client-id also duid_
    OptionPtr clientid = generateClientId();

    // Check that the address we are about to use is indeed in pool
    ASSERT_TRUE(subnet_->inPool(Lease::TYPE_NA, addr));

    // Note that preferred, valid, T1 and T2 timers and CLTT are set to invalid
    // value on purpose. They should be updated during RENEW.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, iaid,
                               501, 502, 503, 504, subnet_->getID(),
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
}

}   // end of anonymous namespace
