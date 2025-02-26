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
#include <sstream>

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

    /// @brief Check that when a not registered lease exits for the
    /// registering address the address is considered as already in use
    /// and the registration is rejected.
    ///
    /// @param state The state of the lease.
    void testAddressInUse(const uint32_t state);

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
        "\"dhcp-ddns\": { \"enable-updates\": true },\n"
        "\"ddns-qualifying-suffix\": \"example.com\"\n"
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

void
AddrRegTest::testAddressInUse(const uint32_t state) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Create and add a lease.
    IOAddress addr("2001:db8:1::1");
    DuidPtr duid(new DUID(vector<uint8_t>(8, 0x44)));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 1234, 200, 300, 1));
    lease->state_ = state;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr(addr, 3000, 4000));
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

    // Address in use: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client 2001:db8:1::1: ";
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
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr("2001:db8:1::10", 3000, 4000));
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

    // Reserved address: no response.
    EXPECT_FALSE(srv_.processAddrRegInform(ctx));

    string expected = "DHCP6_ADDR_REG_INFORM_FAIL ";
    expected += "error on addr-reg-inform from client 2001:db8:1::10: ";
    expected += "Address 2001:db8:1::10 is reserved";
    EXPECT_EQ(1, countFile(expected));
}

// Test the basic positive scenario.
TEST_F(AddrRegTest, basic) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr(addr, 3000, 4000));
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

    // Verify the response.
    Pkt6Ptr response = srv_.processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = checkIA_NA(response, 234, 1500, 3000);
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
    EXPECT_EQ(ia->getIAID(), l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test the relayed positive scenario.
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
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr(addr, 3000, 4000));
    addr_reg_inf->addOption(ia);

    // Add a relay: it will be the outer one.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("fe80::ef01");
    relay.peeraddr_ = IOAddress("fe80::1");
    addr_reg_inf->relay_info_.push_back(relay);

    // Add a second relay: it will be the inner one.
    Pkt6::RelayInfo relay2;
    relay2.linkaddr_ = addr;
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

    // Verify the response.
    Pkt6Ptr response = srv_.processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = checkIA_NA(response, 234, 1500, 3000);
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
    EXPECT_EQ(ia->getIAID(), l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_ADD_ADDR6 ";
    expected += "adding IPv6 lease with address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
}

// Test that the registration can be renewed.
TEST_F(AddrRegTest, renew) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Create and add a lease.
    IOAddress addr("2001:db8:1::1");
    OptionPtr clientid = generateClientId();
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid_, 2345, 200, 300, 1));
    lease->state_ = Lease::STATE_REGISTERED;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    addr_reg_inf->addOption(clientid);
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr(addr, 3000, 4000));
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

    // Verify the response.
    Pkt6Ptr response = srv_.processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // Verify the updated lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(ia->getIAID(), l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCP6_ADDR_REG_INFORM_CLIENT_CHANGE";
    EXPECT_EQ(0, countFile(expected));
}

// Test that the registered lease is updated even it belongs to another client.
TEST_F(AddrRegTest, another) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));

    // Create and add a lease for another client.
    IOAddress addr("2001:db8:1::1");
    DuidPtr duid(new DUID(vector<uint8_t>(8, 0x44)));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 2345, 200, 300, 1));
    lease->state_ = Lease::STATE_REGISTERED;
    lease->cltt_ = 1234;
    ASSERT_TRUE(LeaseMgrFactory::instance().addLease(lease));

    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr(addr, 3000, 4000));
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

    // Verify the response.
    Pkt6Ptr response = srv_.processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    // Verify the updated lease.
    Lease6Ptr l = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::STATE_REGISTERED, l->state_);
    EXPECT_EQ(addr, l->addr_);
    ASSERT_TRUE(l->duid_);
    EXPECT_TRUE(*l->duid_ == *duid_);
    EXPECT_EQ(ia->getIAID(), l->iaid_);
    EXPECT_EQ(1, l->subnet_id_);
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);

    string expected = "DHCPSRV_MEMFILE_UPDATE_ADDR6 ";
    expected += "updating IPv6 lease for address 2001:db8:1::1";
    EXPECT_EQ(1, countFile(expected));
    expected = "DHCP6_ADDR_REG_INFORM_CLIENT_CHANGE ";
    expected += "received an addr-reg-inform for 2001:db8:1::1 from client '";
    expected += duid_->toText();
    expected += "' but the address was registered by another client ";
    expected += "'44:44:44:44:44:44:44:44'";
    EXPECT_EQ(1, countFile(expected));
}

// Test that the FQDN option is handled.
TEST_F(AddrRegTest, fqdn) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_NO_THROW(configure(config_));
    ASSERT_NO_THROW(srv_.startD2());

    IOAddress addr("2001:db8:1::1");
    Pkt6Ptr addr_reg_inf = Pkt6Ptr(new Pkt6(DHCPV6_ADDR_REG_INFORM, 1234));
    addr_reg_inf->setRemoteAddr(addr);
    addr_reg_inf->setIface("eth0");
    addr_reg_inf->setIndex(ETH0_INDEX);
    OptionPtr clientid = generateClientId();
    addr_reg_inf->addOption(clientid);
    auto ia = generateIA(D6O_IA_NA, 234, 1500, 3000);
    ia->addOption(generateIAAddr(addr, 3000, 4000));
    addr_reg_inf->addOption(ia);

    // Add an FQDN option.
    Option6ClientFqdnPtr fqdn(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                                    "client.example.com",
                                                    Option6ClientFqdn::FULL));
    addr_reg_inf->addOption(fqdn);

    // Pass it to the server.
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv_.earlyGHRLookup(addr_reg_inf, ctx);
    ASSERT_FALSE(drop);
    ctx.subnet_ = srv_.selectSubnet(addr_reg_inf, drop);
    ASSERT_FALSE(drop);
    srv_.initContext(ctx, drop);
    ASSERT_FALSE(drop);
    ASSERT_TRUE(ctx.subnet_);

    // Verify the response.
    Pkt6Ptr response = srv_.processAddrRegInform(ctx);
    ASSERT_TRUE(response);

    EXPECT_EQ(DHCPV6_ADDR_REG_REPLY, response->getType());
    EXPECT_EQ(addr_reg_inf->getTransid(), response->getTransid());
    Option6IAAddrPtr iaaddr = checkIA_NA(response, 234, 1500, 3000);
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
    EXPECT_EQ(ia->getIAID(), l->iaid_);
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

} // end of anonymous namespace
