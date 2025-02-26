// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>
#include <dhcpsrv/utils.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace std;

namespace {

/// @brief Test fixture class for testing address registration..
class AddrRegTest : public Dhcpv6MessageTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    AddrRegTest() : Dhcpv6MessageTest() {
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
        "} ]\n"
        "}\n";
};

// Test that client-id is mandatory and server-id forbidden for
// Addr-reg-inform messages
TEST_F(AddrRegTest, sanityCheck) {
    // A message with no client-id should fail
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    EXPECT_FALSE(srv_.sanityCheck(addr_reg_inf));

    // A message with a single client-id should succeed
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    EXPECT_TRUE(srv_.sanityCheck(addr_reg_inf));

    // A message with server-id present should fail
    addr_reg_inf->addOption(srv_.getServerID());
    EXPECT_FALSE(srv_.sanityCheck(addr_reg_inf));
}

// Test that subnet selection must return a subnet for processAddrRegInform.
TEST_F(AddrRegTest, noSubnet) {
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_FALSE(ctx.subnet_);

    // No server: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    // The query is silently rejected so no log to check.
}

// Test that an IA_NA option is required.
TEST_F(AddrRegTest, noIA_NA) {
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
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // No IA_NA: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client fe80::abcd: ";
    expected += "Exactly 1 IA_NA option expected, but 0 received";
    EXPECT_EQ(1, countFile(expected));
}

// Test that exactly one IA_NA option is required.
TEST_F(AddrRegTest, twoIA_NAs) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    addr_reg_inf->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    addr_reg_inf->addOption(generateIA(D6O_IA_NA, 345, 1500, 3000));

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // 2 IA_NA options: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client fe80::abcd: ";
    expected += "Exactly 1 IA_NA option expected, but 2 received";
    EXPECT_EQ(1, countFile(expected));
}

// Test that an IA_NA sub-option is required.
TEST_F(AddrRegTest, noIA_NAsub) {
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
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // No IA_NA sub-options: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client fe80::abcd: ";
    expected += "Exactly 1 IA_NA sub-option expected, but 0 received";
    EXPECT_EQ(1, countFile(expected));
}

// Test that an exactly one IA_NA sub-option is required.
TEST_F(AddrRegTest, twoIA_NAsub) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(IOAddress("fe80::abcd"));
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));
    ia->addOption(generateIAAddr("2001:db8:1::2", 3000, 4000));
    addr_reg_inf->addOption(ia);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Two IA_NA sub-options: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client fe80::abcd: ";
    expected += "Exactly 1 IA_NA sub-option expected, but 2 received";
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
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));
    addr_reg_inf->addOption(ia);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Address mismatch: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client fe80::abcd: ";
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
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));
    addr_reg_inf->addOption(ia);

    // Add a relay.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("fe80::ef01");
    relay.peeraddr_ = IOAddress("fe80::1");
    addr_reg_inf->relay_info_.push_back(relay);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Address mismatch: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client fe80::ef01: ";
    expected += "Address mismatch: client at fe80::ef01 ";
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
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr("2001:db8:1::1", 3000, 4000));
    addr_reg_inf->addOption(ia);

    // Add a relay: it will be the outer one.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("fe80::ef01");
    relay.peeraddr_ = IOAddress("fe80::1");
    addr_reg_inf->relay_info_.push_back(relay);

    // Add a second relay: it will be the inner one.
    Pkt6::RelayInfo relay2;
    relay2.linkaddr_ = IOAddress("fe80::2345");
    relay2.peeraddr_ = IOAddress("fe80::1");
    addr_reg_inf->relay_info_.push_back(relay2);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Address mismatch: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client fe80::2345: ";
    expected += "Address mismatch: client at fe80::2345 ";
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
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr("2001:db8::1", 3000, 4000));
    addr_reg_inf->addOption(ia);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Not in subnet: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client 2001:db8::1: ";
    expected += "Address 2001:db8::1 is not in subnet ";
    expected += "2001:db8:1::/64 (id 1)";
    EXPECT_EQ(1, countFile(expected));
}

} // end of anonymous namespace
