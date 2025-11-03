// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/option_int.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>
#include <dhcpsrv/utils.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::stats;
using namespace std;

namespace {

/// @brief Test fixture class for testing address registration..
class AddrRegTest : public Dhcpv6MessageTest {
public:

    /// @brief Constructor.
    AddrRegTest() : Dhcpv6MessageTest() {
        reset();
    }

    /// @brief Destructor.
    virtual ~AddrRegTest() {
        reset();
    }

    /// @brief Reset hooks data.
    virtual void reset() {
        // Reset the query.
        addr_reg_inf_.reset();

        // Deregister the callouts.
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("addr6_register");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("leases6_committed");

        // Unload any previously-loaded libraries.
        HooksManager::setTestMode(false);
        EXPECT_TRUE(HooksManager::unloadLibraries());

        // Clear callout error message.
        callout_errmsg_.clear();

        // Reset callout status and old lease state.
        callout_status_ = CalloutHandle::NEXT_STEP_CONTINUE;
        callout_has_old_lease_ = false;
    }

    /// @brief Generate IAADDR option with specified parameters.
    ///
    /// @param addr The address.
    /// @param preferred_lft The preferred lifetime.
    /// @param valid_lft The valid lifetime.
    Option6IAAddrPtr generateIAAddr(const IOAddress& addr,
                                    uint32_t preferred_lft,
                                    uint32_t valid_lft) {
        Option6IAAddrPtr iaaddr(new Option6IAAddr(D6O_IAADDR, addr,
                                                  preferred_lft, valid_lft));
        return (iaaddr);
    }

    /// @brief Generate IAADDR option with specified parameters.
    ///
    /// @param addr The address in textual form.
    /// @param preferred_lft The preferred lifetime.
    /// @param valid_lft The valid lifetime.
    Option6IAAddrPtr generateIAAddr(const string& addr,
                                    uint32_t preferred_lft,
                                    uint32_t valid_lft) {
        return (generateIAAddr(IOAddress(addr), preferred_lft, valid_lft));
    }

    /// @brief Get IAADDR option from response.
    ///
    /// @param rsp The response.
    /// @return The Option6IAAddrPtr to the unique IAADDR option or null.
    Option6IAAddrPtr getIAAddr(const Pkt6Ptr& rsp) {
        auto opts = rsp->getOptions(D6O_IAADDR);
        if (opts.size() == 0) {
            ADD_FAILURE() << "IAADDR option not present in response";
            return (Option6IAAddrPtr());
        }
        if (opts.size() > 1) {
            ADD_FAILURE() << "multiple IAADDR options present in response";
            return (Option6IAAddrPtr());
        }
        return (boost::dynamic_pointer_cast<Option6IAAddr>(opts.begin()->second));
    }

    /// @brief Checks if the state of the callout handle associated
    /// with a query was reset after the callout invocation.
    ///
    /// The check includes verification if the status was set to
    /// 'continue' and that all arguments were deleted.
    void checkCalloutHandleReset() {
        CalloutHandlePtr callout_handle = addr_reg_inf_->getCalloutHandle();
        ASSERT_TRUE(callout_handle);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
        EXPECT_TRUE(callout_handle->getArgumentNames().empty());
    }

    /// @brief Test callback for the addr6_register callout.
    ///
    /// @param callout_handle The handle passed by the hooks framework.
    /// @return Always 0
    static int addr6_register_callout(CalloutHandle& callout_handle) {
        if (callout_handle.getStatus() != CalloutHandle::NEXT_STEP_CONTINUE) {
            callout_errmsg_ = "bad status";
            return (0);
        }
        Pkt6Ptr query6;
        callout_handle.getArgument("query6", query6);
        if (!query6) {
            callout_errmsg_ = "no query6";
            return (0);
        }
        if (query6->getType() != DHCPV6_ADDR_REG_INFORM) {
            callout_errmsg_ = "bad query6";
            return (0);
        }
        Pkt6Ptr response6;
        callout_handle.getArgument("response6", response6);
        if (!response6) {
            callout_errmsg_ = "no response6";
            return (0);
        }
        if (response6->getType() != DHCPV6_ADDR_REG_REPLY) {
            callout_errmsg_ = "bad response6";
            return (0);
        }
        IOAddress address6 = IOAddress::IPV6_ZERO_ADDRESS();
        callout_handle.getArgument("address6", address6);
        if (address6.isV6Zero()) {
            callout_errmsg_ = "address6 == ::";
            return (0);
        }
        Lease6Ptr old_lease6;
        callout_handle.getArgument("old_lease6", old_lease6);
        if (old_lease6) {
            callout_has_old_lease_ = true;
            if (old_lease6->state_ != Lease::STATE_REGISTERED) {
                callout_errmsg_ = "bad old_lease6 state";
                return (0);
            }
            if (old_lease6->addr_ != address6) {
                callout_errmsg_ = "bad old_lease6 address";
                return (0);
            }
        }
        Lease6Ptr new_lease6;
        callout_handle.getArgument("new_lease6", new_lease6);
        if (!new_lease6) {
            callout_errmsg_ = "no new_lease6";
            return (0);
        }
        if (new_lease6->state_ != Lease::STATE_REGISTERED) {
            callout_errmsg_ = "bad new_lease6 state";
            return (0);
        }
        if (new_lease6->addr_ != address6) {
            callout_errmsg_ = "bad new_lease6 address";
            return (0);
        }
        callout_handle.setStatus(callout_status_);
        return (0);
    }

    /// @brief Test callback for the leases6_committed callout.
    ///
    /// @param callout_handle The handle passed by the hooks framework.
    /// @return Always 0
    static int leases6_committed_callout(CalloutHandle& callout_handle) {
        if (callout_handle.getStatus() != CalloutHandle::NEXT_STEP_CONTINUE) {
            callout_errmsg_ = "bad status";
            return (0);
        }
        Pkt6Ptr query6;
        callout_handle.getArgument("query6", query6);
        if (!query6) {
            callout_errmsg_ = "no query6";
            return (0);
        }
        if (query6->getType() != DHCPV6_ADDR_REG_INFORM) {
            callout_errmsg_ = "bad query6";
            return (0);
        }
        Pkt6Ptr response6;
        callout_handle.getArgument("response6", response6);
        if (!response6) {
            callout_errmsg_ = "no response6";
            return (0);
        }
        if (response6->getType() != DHCPV6_ADDR_REG_REPLY) {
            callout_errmsg_ = "bad response6";
            return (0);
        }
        Lease6CollectionPtr leases6;
        callout_handle.getArgument("leases6", leases6);
        if (!leases6) {
            callout_errmsg_ = "no leases6";
            return (0);
        }
        if (leases6->size() != 1) {
            callout_errmsg_ = "expected one lease in leases6";
            return (0);
        }
        Lease6Ptr new_lease6 = (*leases6)[0];
        if (!new_lease6) {
            callout_errmsg_ = "no new_lease6";
            return (0);
        }
        if (new_lease6->state_ != Lease::STATE_REGISTERED) {
            callout_errmsg_ = "bad new_lease6 state";
            return (0);
        }
        Lease6CollectionPtr deleted_leases6;
        callout_handle.getArgument("deleted_leases6", deleted_leases6);
        if (deleted_leases6 && !deleted_leases6->empty()) {
            callout_has_old_lease_ = true;
        }
        callout_handle.setStatus(callout_status_);
        return (0);
    }

    /// @brief Check that when a not registered lease exits for the
    /// registering address the address is considered as already in use
    /// and the registration is rejected.
    ///
    /// @param state The state of the lease.
    void testAddressInUse(const uint32_t state);

    /// @brief Test the basic positive scenario.
    void testBasic();

    /// @brief Test that the registration can be renewed.
    void testRenew();

    /// @brief Test that the registered lease is updated even it
    /// belongs to another client.
    void testAnotherClient();

    /// @brief Test that the registered lease is updated even it
    /// belongs to another subnet.
    void testAnotherSubnet();

    /// @brief Basic configuration.
    string config_ = "{\n"
        "\"interfaces-config\": { \"interfaces\": [ \"*\" ] },\n"
        "\"valid-lifetime\": 4000,\n"
        "\"preferred-lifetime\": 3000,\n"
        "\"rebind-timer\": 2000,\n"
        "\"renew-timer\": 1000,\n"
        "\"subnet6\": [ {\n"
        "    \"id\": 1,\n"
        "    \"subnet\": \"2001:db8:1::/64\",\n"
        "    \"interface\": \"eth0\"\n"
        "} ],\n"
        "\"reservations\": [ {\n"
        "    \"duid\": \"01:02:03:04:05:0A:0B:0C:0D:0E\",\n"
        "    \"ip-addresses\": [ \"2001:db8:1::10\" ]\n"
        "} ],\n"
        "\"option-data\": [ {\n"
        "    \"name\": \"dns-servers\",\n"
        "    \"data\": \"2001:db8:1::45, 2001:db8:1::100\"\n"
        "} ],\n"
        "\"dhcp-ddns\": { \"enable-updates\": true },\n"
        "\"ddns-qualifying-suffix\": \"example.com\",\n"
        "\"ddns-update-on-renew\": false\n"
        "}\n";

    /// @brief The addr-reg-inform packet.
    Pkt6Ptr addr_reg_inf_;

    /// @brief Callout error message.
    static string callout_errmsg_;

    /// @brief Callout next step.
    static CalloutHandle::CalloutNextStep callout_status_;

    /// @brief Callout old lease argument is not null / empty.
    static bool callout_has_old_lease_;

    /// @brief The registered-nas statistic name.
    static string registered_nas_name_;

    /// @brief The cumulative-registered-nas statistic name.
    static string cumulative_registered_nas_name_;
};

// Callout error message.
string AddrRegTest::callout_errmsg_;

// Callout next step.
CalloutHandle::CalloutNextStep AddrRegTest::callout_status_;

// Callout old lease argument is not null / empty.
bool AddrRegTest::callout_has_old_lease_;

string AddrRegTest::registered_nas_name_ =
    StatsMgr::generateName("subnet", 1, "registered-nas");

string AddrRegTest::cumulative_registered_nas_name_ =
    StatsMgr::generateName("subnet", 1, "cumulative-registered-nas");

// Test that client-id is mandatory and server-id forbidden for
// Addr-reg-inform messages
TEST_F(AddrRegTest, sanityCheck) {
    // A message with no client-id should fail
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    EXPECT_FALSE(srv_->sanityCheck(addr_reg_inf));

    // A message with a single client-id should succeed
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    EXPECT_TRUE(srv_->sanityCheck(addr_reg_inf));

    // A message with server-id present should fail
    addr_reg_inf->addOption(srv_->getServerID());
    EXPECT_FALSE(srv_->sanityCheck(addr_reg_inf));
}

// Test that more than one client-id are forbidden for Addr-reg-inform messages
TEST_F(AddrRegTest, sanityCheck2) {
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));

    // A message with more than one client-id options should fail.
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(clientid);
    EXPECT_FALSE(srv_->sanityCheck(addr_reg_inf));
}

// Test that subnet selection must return a subnet for processAddrRegInform.
TEST_F(AddrRegTest, noSubnet) {
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_FALSE(ctx.subnet_);

    // No server: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    // The query is silently rejected so no log to check.
}

// Test that an IA_NA option is forbidden.
TEST_F(AddrRegTest, unexpectedIA_NA) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Unexpected IA_NA: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::abcd, ";
    expected += "unexpected IA_NA option";
    EXPECT_EQ(1, countFile(expected));
}

// Test that an IA_TA option is forbidden.
TEST_F(AddrRegTest, unexpectedIA_TA) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    OptionPtr ia(new OptionInt<uint32_t>(Option::V6, D6O_IA_TA, 234));
    addr_reg_inf->addOption(ia);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Unexpected IA_TA: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::abcd, ";
    expected += "unexpected IA_TA option";
    EXPECT_EQ(1, countFile(expected));
}

// Test that an IA_PD option is forbidden.
TEST_F(AddrRegTest, unexpectedIA_PD) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIA(D6O_IA_PD, 234, 1500, 3000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Unexpected IA_PD: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::abcd, ";
    expected += "unexpected IA_PD option";
    EXPECT_EQ(1, countFile(expected));
}

// Test that an IAADDR option is required.
TEST_F(AddrRegTest, noIAADDR) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // No IAADDR options: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::abcd, ";
    expected += "Exactly 1 IAADDR option expected, but 0 received";
    EXPECT_EQ(1, countFile(expected));
}

// Test that an exactly one IAADDR option is required.
TEST_F(AddrRegTest, twoIAADDR) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));
    addr_reg_inf->addOption(generateIAAddr("2001:db8:1::2", 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Two IAADDR options: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::abcd, ";
    expected += "Exactly 1 IAADDR option expected, but 2 received";
    EXPECT_EQ(1, countFile(expected));
}

// Test that a well formed IAADDR option is required.
TEST_F(AddrRegTest, badIAADDR) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    OptionCustomPtr iaaddr(new OptionCustom(LibDHCP::D6O_IAADDR_DEF(),
                                            Option::V6));
    iaaddr->writeAddress(IOAddress("2001:db8:1::1"), 0);
    iaaddr->writeInteger<uint32_t>(3000, 1);
    iaaddr->writeInteger<uint32_t>(4000, 2);
    addr_reg_inf->addOption(iaaddr);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Two IAADDR options: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::abcd, ";
    expected += "can't convert the IAADDR option";
    EXPECT_EQ(1, countFile(expected));
}

// Test that addresses must match.
TEST_F(AddrRegTest, noAddrMatch) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Address mismatch: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::abcd, ";
    expected += "Address mismatch: client at fe80::abcd ";
    expected += "wants to register 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that addresses must match with a relay.
TEST_F(AddrRegTest, noAddrMatchRelay) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));

    // Add a relay.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("fe80::ef01");
    relay.peeraddr_ = IOAddress("fe80::1");
    addr_reg_inf->relay_info_.push_back(relay);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Address mismatch: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::1, ";
    expected += "Address mismatch: client at fe80::1 ";
    expected += "wants to register 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that addresses must match with relays.
TEST_F(AddrRegTest, noAddrMatch2Relays) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));

    // Add a relay: it will be the outer one.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("fe80::ef01");
    relay.peeraddr_ = IOAddress("fe80::2345");
    addr_reg_inf->relay_info_.push_back(relay);

    // Add a second relay: it will be the inner one.
    Pkt6::RelayInfo relay2;
    relay2.linkaddr_ = IOAddress("fe80::2345");
    relay2.peeraddr_ = IOAddress("fe80::1");
    addr_reg_inf->relay_info_.push_back(relay2);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Address mismatch: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client fe80::1, ";
    expected += "Address mismatch: client at fe80::1 ";
    expected += "wants to register 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that the registering address must be in the subnet.
TEST_F(AddrRegTest, noInSubnet) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("2001:db8::1"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr("2001:db8::1", 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Not in subnet: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client 2001:db8::1, ";
    expected += "Address 2001:db8::1 is not in subnet ";
    expected += "2001:db8:1::/64 (id 1)";
    EXPECT_EQ(1, countFile(expected));
}

// Test that the registering address must be not reserved.
TEST_F(AddrRegTest, reserved) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("2001:db8:1::10"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr("2001:db8:1::10", 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Reserved address: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client 2001:db8:1::10, ";
    expected += "Address 2001:db8:1::10 is reserved";
    EXPECT_EQ(1, countFile(expected));
}

void
AddrRegTest::testAddressInUse(const uint32_t state) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Create and add a lease.
    IOAddress addr("2001:db8:1::1");
    DuidPtr duid(new DUID(vector<uint8_t>(8, 0x44)));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 234, 200, 300, 1));
    lease->state_ = state;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Address in use: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on ADDR-REG-INFORM from client 2001:db8:1::1, ";
    expected +=  "Address 2001:db8:1::1 already in use Type:";
    EXPECT_EQ(1, countFile(expected));
}

// Check that a lease in the defaul state (0) makes the registering address
// being considered as in use and the registration rejected.
TEST_F(AddrRegTest, addressInUseAssigned) {
    testAddressInUse(0);

}

// Check that a declined lease (1) makes the registering address being
// considered as in use and the registration rejected.
TEST_F(AddrRegTest, addressInUseDeclined) {
    testAddressInUse(1);
}

// Check that a relaimed lease (2) makes the registering address being
// considered as in use and the registration rejected.
TEST_F(AddrRegTest, addressInUseReclaimed) {
    testAddressInUse(2);
}

// Check that a released lease (3) makes the registering address being
// considered as in use and the registration rejected.
TEST_F(AddrRegTest, addressInUseReleased) {
    testAddressInUse(3);
}

// Check that a lease with a random state makes the registering address
// being considered as in use and the registration rejected.
TEST_F(AddrRegTest, addressInUseLease123) {
    testAddressInUse(123);
}

// Test the basic positive scenario.
void
AddrRegTest::testBasic() {
    IOAddress addr("2001:db8:1::1");
    addr_reg_inf_ = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf_->setRemoteAddr(addr);
    addr_reg_inf_->setIface("eth0");
    addr_reg_inf_->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf_->addOption(clientid);
    addr_reg_inf_->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf_, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf_, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf_->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = getIAAddr(response);
    ASSERT_TRUE(iaaddr);
    EXPECT_EQ(addr, iaaddr->getAddress());
    EXPECT_EQ(3000, iaaddr->getPreferred());
    EXPECT_EQ(4000, iaaddr->getValid());

    // Verify the added lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test the basic positive scenario.
TEST_F(AddrRegTest, basic) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    testBasic();
}

// Test the relayed scenario.
TEST_F(AddrRegTest, relayed) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr(addr, 3000, 4000));

    // Add a relay: it will be the outer one.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("fe80::ef01");
    relay.peeraddr_ = IOAddress("fe80::1");
    addr_reg_inf->relay_info_.push_back(relay);

    // Add a second relay: it will be the inner one.
    Pkt6::RelayInfo relay2;
    relay2.linkaddr_ = IOAddress("fe80::1");
    relay2.peeraddr_ = addr;
    addr_reg_inf->relay_info_.push_back(relay2);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = getIAAddr(response);
    ASSERT_TRUE(iaaddr);
    EXPECT_EQ(addr, iaaddr->getAddress());
    EXPECT_EQ(3000, iaaddr->getPreferred());
    EXPECT_EQ(4000, iaaddr->getValid());

    // Verify relays.
    auto relay_info = response->relay_info_;
    ASSERT_EQ(2, relay_info.size());
    EXPECT_EQ(relay.linkaddr_, relay_info[0].linkaddr_);
    EXPECT_EQ(relay.peeraddr_, relay_info[0].peeraddr_);
    EXPECT_EQ(relay2.linkaddr_, relay_info[1].linkaddr_);
    EXPECT_EQ(relay2.peeraddr_, relay_info[1].peeraddr_);

    // Verify the added lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that the registration can be renewed.
void
AddrRegTest::testRenew() {
    // Create and add a lease.
    IOAddress addr("2001:db8:1::1");
    OptionPtr clientid = generateClientId();
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, 0, 200, 300, 1));
    lease->state_ = Lease::STATE_REGISTERED;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    addr_reg_inf_ = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf_->setRemoteAddr(addr);
    addr_reg_inf_->setIface("eth0");
    addr_reg_inf_->setIndex(ETH0_INDEX);
    addr_reg_inf_->addOption(clientid);
    addr_reg_inf_->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf_, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf_, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // Verify the updated lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCP6_ADDR_REG_INFORM_CLIENT_CHANGE";
    EXPECT_EQ(0, countFile(expected));
}

// Test that the registration can be renewed.
TEST_F(AddrRegTest, renew) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    testRenew();
}

// Test that the registered lease is updated even it belongs to another client.
void
AddrRegTest::testAnotherClient() {
    // Create and add a lease for another client.
    IOAddress addr("2001:db8:1::1");
    DuidPtr duid(new DUID(vector<uint8_t>(8, 0x44)));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0, 200, 300, 1));
    lease->state_ = Lease::STATE_REGISTERED;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    addr_reg_inf_ = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf_->setRemoteAddr(addr);
    addr_reg_inf_->setIface("eth0");
    addr_reg_inf_->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf_->addOption(clientid);
    addr_reg_inf_->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf_, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf_, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // Verify the updated lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCP6_ADDR_REG_INFORM_CLIENT_CHANGE ";
    expected += "received an ADDR-REG-INFORM for 2001:db8:1::1 from client '";
    expected += duid_->toText();
    expected += "' but the address was registered by another client ";
    expected += "'44:44:44:44:44:44:44:44'";
    EXPECT_EQ(1, countFile(expected));
}

// Test that the registered lease is updated even it belongs to another client.
TEST_F(AddrRegTest, anotherClient) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    testAnotherClient();
}

// Test that the registratered lease is updated even it belongs to
// another subnet.
void
AddrRegTest::testAnotherSubnet() {
    // Create and add a lease.
    IOAddress addr("2001:db8:1::1");
    OptionPtr clientid = generateClientId();
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, 0, 200, 300, 2));
    lease->state_ = Lease::STATE_REGISTERED;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    addr_reg_inf_ = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf_->setRemoteAddr(addr);
    addr_reg_inf_->setIface("eth0");
    addr_reg_inf_->setIndex(ETH0_INDEX);
    addr_reg_inf_->addOption(clientid);
    addr_reg_inf_->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf_, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf_, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // Verify the updated lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCP6_ADDR_REG_INFORM_CLIENT_CHANGE";
    EXPECT_EQ(0, countFile(expected));
}

// Test that the registered lease is updated even it belongs to another subnet.
TEST_F(AddrRegTest, anotherSubnet) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    testAnotherSubnet();
}

// Test that the FQDN option is handled.
TEST_F(AddrRegTest, fqdn) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));
    ASSERT_NO_THROW(srv_->startD2());

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr(addr, 3000, 4000));

    // Add an FQDN option.
    Option6ClientFqdnPtr fqdn(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                                    "client.example.com",
                                                    Option6ClientFqdn::FULL));
    addr_reg_inf->addOption(fqdn);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = getIAAddr(response);
    ASSERT_TRUE(iaaddr);
    EXPECT_EQ(addr, iaaddr->getAddress());
    EXPECT_EQ(3000, iaaddr->getPreferred());
    EXPECT_EQ(4000, iaaddr->getValid());
    EXPECT_TRUE(response->getOption(D6O_CLIENT_FQDN));

    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_EQ("client.example.com.", l->hostname_);
    EXPECT_TRUE(l->fqdn_fwd_);
    EXPECT_TRUE(l->fqdn_rev_);

    // There should be one name change request generated.
    EXPECT_EQ(1, CfgMgr::instance().getD2ClientMgr().getQueueSize());

    string expected = "DHCP6_DDNS_CREATE_ADD_NAME_CHANGE_REQUEST duid=[";
    expected += duid_->toText();
    expected += "], [no hwaddr info], tid=0x4d2: ";
    expected += "created name change request: Type: 0 (CHG_ADD)";
    EXPECT_EQ(1, countFile(expected));
}

// Test that DDNS is skipped on renew.
TEST_F(AddrRegTest, renewDdns) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));
    ASSERT_NO_THROW(srv_->startD2());

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr(addr, 3000, 4000));

    // Add an FQDN option.
    Option6ClientFqdnPtr fqdn(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                                    "client.example.com",
                                                    Option6ClientFqdn::FULL));
    addr_reg_inf->addOption(fqdn);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // There should be one name change request generated.
    auto& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    EXPECT_EQ(1, d2_mgr.getQueueSize());

    // Clear the queue.
    ASSERT_NO_THROW(d2_mgr.runReadyIO());
    EXPECT_EQ(0, d2_mgr.getQueueSize());

    // Process it a second time.
    AllocEngine::ClientContext6 ctx2;
    drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx2);
    ASSERT_FALSE(drop);
    ctx2.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx2, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx2.subnet_);

    response = srv_->processAddrRegInform(ctx2);
    ASSERT_TRUE(response);

    // DDNS is skipped when ddns-update-on-renew is false (default).
    EXPECT_FALSE(ctx2.getDdnsParams()->getUpdateOnRenew());
    EXPECT_EQ(0, d2_mgr.getQueueSize());

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that DDNS is not skipped on renew when ddns-update-on-renew is true.
TEST_F(AddrRegTest, renewDdnsUpdateOnRenew) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));
    Subnet6Ptr subnet =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getSubnet(1);
    ASSERT_TRUE(subnet);
    ASSERT_NO_THROW(subnet->setDdnsUpdateOnRenew(true));
    ASSERT_NO_THROW(srv_->startD2());

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr(addr, 3000, 4000));

    // Add an FQDN option.
    Option6ClientFqdnPtr fqdn(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                                    "client.example.com",
                                                    Option6ClientFqdn::FULL));
    addr_reg_inf->addOption(fqdn);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // There should be one name change request generated.
    auto& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    EXPECT_EQ(1, d2_mgr.getQueueSize());

    // Clear the queue.
    ASSERT_NO_THROW(d2_mgr.runReadyIO());
    EXPECT_EQ(0, d2_mgr.getQueueSize());

    // Process it a second time.
    AllocEngine::ClientContext6 ctx2;
    drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx2);
    ASSERT_FALSE(drop);
    ctx2.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx2, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx2.subnet_);

    response = srv_->processAddrRegInform(ctx2);
    ASSERT_TRUE(response);

    // DDNS is not skipped when ddns-update-on-renew is true.
    EXPECT_TRUE(ctx2.getDdnsParams()->getUpdateOnRenew());
    // One CHG_REMOVE and one CHG_ADD (no CHG_UPDATE).
    EXPECT_EQ(2, d2_mgr.getQueueSize());

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that DDNS is not skipped when the hostname changes.
TEST_F(AddrRegTest, renewDdnsHostname) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));
    ASSERT_NO_THROW(srv_->startD2());

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr(addr, 3000, 4000));

    // Add an FQDN option.
    Option6ClientFqdnPtr fqdn(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                                    "client.example.com",
                                                    Option6ClientFqdn::FULL));
    addr_reg_inf->addOption(fqdn);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // There should be one name change request generated.
    auto& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    EXPECT_EQ(1, d2_mgr.getQueueSize());

    // Clear the queue.
    ASSERT_NO_THROW(d2_mgr.runReadyIO());
    EXPECT_EQ(0, d2_mgr.getQueueSize());

    // Change the hostname.
    ASSERT_TRUE(addr_reg_inf->delOption(D6O_CLIENT_FQDN));
    Option6ClientFqdnPtr fqdn2(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                                     "client2.example.com",
                                                     Option6ClientFqdn::FULL));
    addr_reg_inf->addOption(fqdn2);

    // Process it a second time.
    AllocEngine::ClientContext6 ctx2;
    drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx2);
    ASSERT_FALSE(drop);
    ctx2.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx2, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx2.subnet_);

    response = srv_->processAddrRegInform(ctx2);
    ASSERT_TRUE(response);

    // DDNS is not skipped when the hostname changed.
    EXPECT_FALSE(ctx2.getDdnsParams()->getUpdateOnRenew());
    // One CHG_REMOVE and one CHG_ADD (no CHG_UPDATE).
    EXPECT_EQ(2, d2_mgr.getQueueSize());

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that the ORO option is handled.
TEST_F(AddrRegTest, oro) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIAAddr(addr, 3000, 4000));

    // Add an ORO option for the dns-servers option.
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    oro->addValue(D6O_NAME_SERVERS);
    addr_reg_inf->addOption(oro);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = getIAAddr(response);
    ASSERT_TRUE(iaaddr);
    EXPECT_EQ(addr, iaaddr->getAddress());
    EXPECT_EQ(3000, iaaddr->getPreferred());
    EXPECT_EQ(4000, iaaddr->getValid());

    // Check the name-servers option.
    OptionPtr opt = response->getOption(D6O_NAME_SERVERS);
    Option6AddrLstPtr ns = boost::dynamic_pointer_cast<Option6AddrLst>(opt);
    ASSERT_TRUE(ns);
    Option6AddrLst::AddressContainer ns_addrs = ns->getAddresses();
    ASSERT_EQ(2, ns_addrs.size());
    EXPECT_EQ("2001:db8:1::45", ns_addrs[0].toText());
    EXPECT_EQ("2001:db8:1::100", ns_addrs[1].toText());

    // Option processing is silent: nothing to check.
}

// Test the callout in the basic scenario.
TEST_F(AddrRegTest, callout) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Install addr6_register_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "addr6_register", addr6_register_callout));
    testBasic();
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    EXPECT_FALSE(callout_has_old_lease_);
    checkCalloutHandleReset();

    string expected = "HOOKS_CALLOUTS_BEGIN ";
    expected += "begin all callouts for hook addr6_register";
    EXPECT_EQ(1, countFile(expected));
}

// Test the callout in the renew scenario.
TEST_F(AddrRegTest, calloutRenew) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Install addr6_register_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "addr6_register", addr6_register_callout));
    testRenew();
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    EXPECT_TRUE(callout_has_old_lease_);
    checkCalloutHandleReset();

    string expected = "HOOKS_CALLOUTS_BEGIN ";
    expected += "begin all callouts for hook addr6_register";
    EXPECT_EQ(1, countFile(expected));
}

// Test the callout in the another client scenario.
TEST_F(AddrRegTest, calloutAnotherClient) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Install addr6_register_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "addr6_register", addr6_register_callout));
    testAnotherClient();
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    EXPECT_TRUE(callout_has_old_lease_);
    checkCalloutHandleReset();

    string expected = "HOOKS_CALLOUTS_BEGIN ";
    expected += "begin all callouts for hook addr6_register";
    EXPECT_EQ(1, countFile(expected));
}

// Test the callout in the another subnet scenario.
TEST_F(AddrRegTest, calloutAnotherSubnet) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Install addr6_register_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "addr6_register", addr6_register_callout));
    testAnotherSubnet();
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    EXPECT_TRUE(callout_has_old_lease_);
    checkCalloutHandleReset();

    string expected = "HOOKS_CALLOUTS_BEGIN ";
    expected += "begin all callouts for hook addr6_register";
    EXPECT_EQ(1, countFile(expected));
}

// Test that when the callout sets the status skip the lease operation
// is not performed.
TEST_F(AddrRegTest, calloutSkip) {
    callout_status_ = CalloutHandle::NEXT_STEP_SKIP;

    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Install addr6_register_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "addr6_register", addr6_register_callout));

    IOAddress addr("2001:db8:1::1");
    addr_reg_inf_ = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf_->setRemoteAddr(addr);
    addr_reg_inf_->setIface("eth0");
    addr_reg_inf_->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf_->addOption(clientid);
    addr_reg_inf_->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf_, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf_, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_->processAddrRegInform(ctx);
    ASSERT_TRUE(response);
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    checkCalloutHandleReset();

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf_->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = getIAAddr(response);
    ASSERT_TRUE(iaaddr);
    EXPECT_EQ(addr, iaaddr->getAddress());
    EXPECT_EQ(3000, iaaddr->getPreferred());
    EXPECT_EQ(4000, iaaddr->getValid());

    // No lease was added.
    EXPECT_FALSE(LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr));

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6";
    EXPECT_EQ(0, countFile(expected));
    EXPECT_EQ(1, countFile("DHCP6_HOOK_ADDR6_REGISTER_SKIP"));
}

// Test that when the callout sets the status drop the query is dropped.
TEST_F(AddrRegTest, calloutDrop) {
    callout_status_ = CalloutHandle::NEXT_STEP_DROP;

    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Install addr6_register_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "addr6_register", addr6_register_callout));

    IOAddress addr("2001:db8:1::1");
    addr_reg_inf_ = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf_->setRemoteAddr(addr);
    addr_reg_inf_->setIface("eth0");
    addr_reg_inf_->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf_->addOption(clientid);
    addr_reg_inf_->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf_, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf_, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Callout set the status to drop: no response.
    EXPECT_FALSE(srv_->processAddrRegInform(ctx));
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    checkCalloutHandleReset();

    string expected = "HOOKS_CALLOUTS_BEGIN ";
    expected += "begin all callouts for hook addr6_register";
    EXPECT_EQ(1, countFile(expected));
    EXPECT_EQ(1, countFile("DHCP6_HOOK_ADDR6_REGISTER_DROP"));
}

// Check the statistics for the basic scenario.
TEST_F(AddrRegTest, stats) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    StatsMgr::instance().setValue(registered_nas_name_,
                                  static_cast<int64_t>(5));
    StatsMgr::instance().setValue(cumulative_registered_nas_name_,
                                  static_cast<int64_t>(10));
    StatsMgr::instance().setValue("cumulative-registered-nas",
                                  static_cast<int64_t>(20));

    testBasic();

    // Statistics should have been bumped by one.
    ObservationPtr stat;
    stat = StatsMgr::instance().getObservation(registered_nas_name_);
    ASSERT_TRUE(stat);
    EXPECT_EQ(6, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation(cumulative_registered_nas_name_);
    ASSERT_TRUE(stat);
    EXPECT_EQ(11, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation("cumulative-registered-nas");
    EXPECT_EQ(21, stat->getInteger().first);
}

// Check the statistics for the renew scenario.
TEST_F(AddrRegTest, statsRenew) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    StatsMgr::instance().setValue(registered_nas_name_,
                                  static_cast<int64_t>(5));
    StatsMgr::instance().setValue(cumulative_registered_nas_name_,
                                  static_cast<int64_t>(10));
    StatsMgr::instance().setValue("cumulative-registered-nas",
                                  static_cast<int64_t>(20));

    testRenew();

    // Statistics should have been not touched.
    ObservationPtr stat;
    stat = StatsMgr::instance().getObservation(registered_nas_name_);
    ASSERT_TRUE(stat);
    EXPECT_EQ(5, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation(cumulative_registered_nas_name_);
    ASSERT_TRUE(stat);
    EXPECT_EQ(10, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation("cumulative-registered-nas");
    EXPECT_EQ(20, stat->getInteger().first);
}

// Check the statistics for the another subnet scenario.
TEST_F(AddrRegTest, statsAnotherSubnet) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    string registered_nas_name2 =
        StatsMgr::generateName("subnet", 2, "registered-nas");
    StatsMgr::instance().setValue(registered_nas_name2,
                                  static_cast<int64_t>(3));
    StatsMgr::instance().setValue(registered_nas_name_,
                                  static_cast<int64_t>(5));
    string cumulative_registered_nas_name2 =
        StatsMgr::generateName("subnet", 2, "cumulative-registered-nas");
    StatsMgr::instance().setValue(cumulative_registered_nas_name2,
                                  static_cast<int64_t>(8));
    StatsMgr::instance().setValue(cumulative_registered_nas_name_,
                                  static_cast<int64_t>(10));
    StatsMgr::instance().setValue("cumulative-registered-nas",
                                  static_cast<int64_t>(20));

    testAnotherSubnet();

    // Statistics should have been not touched.
    ObservationPtr stat;
    stat = StatsMgr::instance().getObservation(registered_nas_name2);
    ASSERT_TRUE(stat);
    EXPECT_EQ(2, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation(registered_nas_name_);
    ASSERT_TRUE(stat);
    EXPECT_EQ(6, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation(cumulative_registered_nas_name2);
    ASSERT_TRUE(stat);
    EXPECT_EQ(8, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation(cumulative_registered_nas_name_);
    ASSERT_TRUE(stat);
    EXPECT_EQ(11, stat->getInteger().first);
    stat = StatsMgr::instance().getObservation("cumulative-registered-nas");
    EXPECT_EQ(20, stat->getInteger().first);
}

// Check the basic scenario with the client test tool.
TEST_F(AddrRegTest, client) {
    Dhcp6Client client(srv_);
    DuidPtr duid = client.getDuid();
    ASSERT_TRUE(duid);

    ASSERT_NO_THROW(configure(config_, *client.getServer()));

    // Install leases6_committed_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "leases6_committed", leases6_committed_callout));

    // Do the address registration.
    IOAddress addr("2001:db8:1::1");
    client.setLinkLocal(addr);
    client.addExtraOption(generateIAAddr(addr, 3000, 4000));
    ASSERT_NO_THROW(client.doAddrRegInform());

    // Check the response.
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);
    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    EXPECT_FALSE(callout_has_old_lease_);
    addr_reg_inf_ = client.getContext().query_;
    checkCalloutHandleReset();

    // Verify the added lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_EQ(3000, l->preferred_lft_);
    EXPECT_EQ(4000, l->valid_lft_);

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "HOOKS_CALLOUTS_BEGIN ";
    expected += "begin all callouts for hook leases6_committed";
    EXPECT_EQ(1, countFile(expected));
}

// Check the renew scenario with the client test tool.
TEST_F(AddrRegTest, clientRenew) {
    Dhcp6Client client(srv_);
    DuidPtr duid = client.getDuid();
    ASSERT_TRUE(duid);

    ASSERT_NO_THROW(configure(config_, *client.getServer()));

    // Install leases6_committed_callout.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "leases6_committed", leases6_committed_callout));

    // Create and add a lease.
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0, 200, 300, 1));
    lease->state_ = Lease::STATE_REGISTERED;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    // Do the address registration.
    client.setLinkLocal(addr);
    client.addExtraOption(generateIAAddr(addr, 3000, 4000));
    ASSERT_NO_THROW(client.doAddrRegInform());

    // Check the response.
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);
    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_TRUE(callout_errmsg_.empty()) << callout_errmsg_;
    EXPECT_FALSE(callout_has_old_lease_);
    addr_reg_inf_ = client.getContext().query_;
    checkCalloutHandleReset();

    // Verify the updated lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid);
    EXPECT_EQ(0, l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_EQ(3000, l->preferred_lft_);
    EXPECT_EQ(4000, l->valid_lft_);

    string expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "HOOKS_CALLOUTS_BEGIN ";
    expected += "begin all callouts for hook leases6_committed";
    EXPECT_EQ(1, countFile(expected));
}

// Test the global allow-address-registration = false;
TEST_F(AddrRegTest, allowAddressRegistrationFalse) {
    IfaceMgrTestConfig test_config(true);

    /// @brief Basic configuration.
    string config = "{\n"
        "\"interfaces-config\": { \"interfaces\": [ \"*\" ] },\n"
        "\"valid-lifetime\": 4000,\n"
        "\"preferred-lifetime\": 3000,\n"
        "\"rebind-timer\": 2000,\n"
        "\"renew-timer\": 1000,\n"
        "\"subnet6\": [ {\n"
        "    \"id\": 1,\n"
        "    \"subnet\": \"2001:db8:1::/64\",\n"
        "    \"interface\": \"eth0\"\n"
        "} ],\n"
        "\"reservations\": [ {\n"
        "    \"duid\": \"01:02:03:04:05:0A:0B:0C:0D:0E\",\n"
        "    \"ip-addresses\": [ \"2001:db8:1::10\" ]\n"
        "} ],\n"
        "\"option-data\": [ {\n"
        "    \"name\": \"dns-servers\",\n"
        "    \"data\": \"2001:db8:1::45, 2001:db8:1::100\"\n"
        "} ],\n"
        "\"dhcp-ddns\": { \"enable-updates\": true },\n"
        "\"ddns-qualifying-suffix\": \"example.com\",\n"
        "\"ddns-update-on-renew\": false\n,"
        "\"allow-address-registration\" : false\n"
        "}\n";

    ASSERT_NO_THROW(configure(config));

    IOAddress addr("2001:db8:1::1");
    addr_reg_inf_ = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf_->setRemoteAddr(addr);
    addr_reg_inf_->setIface("eth0");
    addr_reg_inf_->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf_->addOption(clientid);
    addr_reg_inf_->addOption(generateIAAddr(addr, 3000, 4000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_->earlyGHRLookup(addr_reg_inf_, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_->selectSubnet(addr_reg_inf_, drop);
    ASSERT_FALSE(drop);
    srv_->initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify no response.
    ASSERT_FALSE(srv_->processAddrRegInform(ctx));

    // Drop stat should have been bumped by one and the log emitted.
    ObservationPtr stat;
    stat = StatsMgr::instance().getObservation("pkt6-receive-drop");
    ASSERT_TRUE(stat);
    EXPECT_EQ(1, stat->getInteger().first);
    EXPECT_EQ(1, countFile("DHCP6_ADDR6_REGISTER_DISABLED_DROP ADDR-REG-INFORM"));
}

// Test the global allow-address-registration = true;
TEST_F(AddrRegTest, allowAddressRegistrationTrue) {
    IfaceMgrTestConfig test_config(true);

    /// @brief Basic configuration.
    string config = "{\n"
        "\"interfaces-config\": { \"interfaces\": [ \"*\" ] },\n"
        "\"valid-lifetime\": 4000,\n"
        "\"preferred-lifetime\": 3000,\n"
        "\"rebind-timer\": 2000,\n"
        "\"renew-timer\": 1000,\n"
        "\"subnet6\": [ {\n"
        "    \"id\": 1,\n"
        "    \"subnet\": \"2001:db8:1::/64\",\n"
        "    \"interface\": \"eth0\"\n"
        "} ],\n"
        "\"reservations\": [ {\n"
        "    \"duid\": \"01:02:03:04:05:0A:0B:0C:0D:0E\",\n"
        "    \"ip-addresses\": [ \"2001:db8:1::10\" ]\n"
        "} ],\n"
        "\"option-data\": [ {\n"
        "    \"name\": \"dns-servers\",\n"
        "    \"data\": \"2001:db8:1::45, 2001:db8:1::100\"\n"
        "} ],\n"
        "\"dhcp-ddns\": { \"enable-updates\": true },\n"
        "\"ddns-qualifying-suffix\": \"example.com\",\n"
        "\"ddns-update-on-renew\": false\n,"
        "\"allow-address-registration\" : true\n"
        "}\n";

    ASSERT_NO_THROW(configure(config));
    testBasic();
}

} // end of anonymous namespace
