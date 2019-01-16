// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>
#include <dhcpsrv/utils.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used throughout the Rebind tests.
///
/// - Configuration 0:
///   - only addresses (no prefixes)
///   - 2 subnets with 2001:db8:1::/64 and 2001:db8:2::/64
///   - 1 subnet for eth0 and 1 subnet for eth1
///
/// - Configuration 1:
///   - similar to Configuration 0 but different subnets
///   - pools configured: 2001:db8:3::/64 and 2001:db8:4::/64
///
/// - Configuration 2:
///   - similar to Configuration 0 and Configuration 1
///   - pools configured: 3000:1::/64 and 3000:2::/64
///   - this specific configuration is used by tests using relays
///
/// - Configuration 3:
///   - similar to Configuration 2 but with different subnets
///   - pools configured: 3000:3::/64 and 3000:4::/64
///   - this specific configuration is used by tests using relays
///
/// - Configuration 4:
///   - only prefixes (no addresses)
///   - 2 subnets: 2001:db8:1::/40 and 2001:db8:2::/40
///   - 2 prefix pools: 3000::/72 and 2001:db8:2::/72
///   - 1 subnet for eth0 and 1 subnet for eth1
///   - this specific configuration is used by tests which don't use relays
///
/// - Configuration 5:
///   - similar to Configuration 4 but with different subnets
///   - 2 subnets: 2001:db8:3::/40 and 2001:db8:4::/40
///   - 2 prefix pools: 2001:db8:3::/72 and 2001:db8:4::/72
///   - delegated length /80
///   - this specific configuration is used by tests which don't use relays
///
/// - Configuration 6:
///   - addresses and prefixes
///   - address pool: 2001:db8:1::/64
///   - prefix pool: 3000::/72
///
/// - Configuration 7:
///   - only addresses (no prefixes)
///   - 2 subnets with 2001:db8:1::/64 and 2001:db8:2::/64
///   - 1 subnet for eth0 and 1 subnet for eth1
///   - DOCSIS vendor config file sub-option
///
/// - Configuration 8:
///   - single subnet 3000::/32,
///   - two options specified in the subnet scope,
///   - one option specified at the global scope,
///   - two address pools: 3000::10-3000::20, 3000::40-3000::50,
///   - two prefix pools: 2001:db8:3::/64 and 2001:db8:4::/64,
///   - an option with unique value specified for each pool, so as it is
///     possible to test that pool specific options can be assigned.
///
const char* REBIND_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 1
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/64\" } ],"
        "    \"subnet\": \"2001:db8:3::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/64\" } ],"
        "    \"subnet\": \"2001:db8:4::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 2
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"3000:1::/64\" } ],"
        "    \"subnet\": \"3000:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"3000:2::/64\" } ],"
        "    \"subnet\": \"3000:2::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 3
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"3000:3::/64\" } ],"
        "    \"subnet\": \"3000:3::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"3000:4::/64\" } ],"
        "    \"subnet\": \"3000:4::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 4
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": ["
        "        { \"prefix\": \"3000::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:1::/40\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:2::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:2::/40\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 5
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:3:01::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:3::/40\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " },"
        " {"
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:4:01::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:4::/40\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 6
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"pd-pools\": ["
        "        { \"prefix\": \"3000::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 7
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"config-file\","
        "    \"space\": \"vendor-4491\","
        "    \"data\": \"normal_erouter_v6.cm\""
        "}],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 8
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"dns-servers\","
        "    \"data\": \"3000:1::234\""
        "},"
        "{"
        "    \"name\": \"sntp-servers\","
        "    \"data\": \"3000:2::1\""
        "} ],"
        "\"subnet6\": [ { "
        "    \"option-data\": [ {"
        "        \"name\": \"dns-servers\","
        "        \"data\": \"3000:1::567\""
        "    },"
        "    {"
        "        \"name\": \"sntp-servers\","
        "        \"data\": \"3000:2::1\""
        "    } ],"
        "    \"pools\": [ { "
        "        \"pool\": \"3000::10 - 3000::20\","
        "        \"option-data\": [ {"
        "            \"name\": \"sntp-servers\","
        "            \"data\": \"3000:2::2\""
        "        } ]"
        "    },"
        "    {"
        "        \"pool\": \"3000::40 - 3000::50\","
        "        \"option-data\": [ {"
        "            \"name\": \"nisp-servers\","
        "            \"data\": \"3000:2::3\""
        "        } ]"
        "    } ],"
        "    \"pd-pools\": [ { "
        "        \"prefix\": \"2001:db8:3::\","
        "        \"prefix-len\": 64,"
        "        \"delegated-len\": 64,"
        "        \"option-data\": [ {"
        "            \"name\": \"dns-servers\","
        "            \"data\": \"3000:1::678\""
        "        } ]"
        "    },"
        "    {"
        "        \"prefix\": \"2001:db8:4::\","
        "        \"prefix-len\": 64,"
        "        \"delegated-len\": 64,"
        "        \"option-data\": [ {"
        "            \"name\": \"nis-servers\","
        "            \"data\": \"3000:1::789\""
        "        } ]"
        "    } ],"
        "    \"subnet\": \"3000::/32\", "
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000"
    "}"
};

/// @brief Test fixture class for testing Rebind.
class RebindTest : public Dhcpv6MessageTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    RebindTest()
        : Dhcpv6MessageTest() {
    }
};

// Test that client-id is mandatory and server-id forbidden for Rebind messages
TEST_F(RebindTest, sanityCheck) {
    NakedDhcpv6Srv srv(0);

    // A message with no client-id should fail
    Pkt6Ptr rebind = Pkt6Ptr(new Pkt6(DHCPV6_REBIND, 1234));
    EXPECT_FALSE(srv.sanityCheck(rebind));

    // A message with a single client-id should succeed
    OptionPtr clientid = generateClientId();
    rebind->addOption(clientid);
    EXPECT_TRUE(srv.sanityCheck(rebind));

    // A message with server-id present should fail
    rebind->addOption(srv.getServerID());
    EXPECT_FALSE(srv.sanityCheck(rebind));
}

// Test that directly connected client's Rebind message is processed and Reply
// message is sent back.
TEST_F(RebindTest, directClient) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belong to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->
                selectSubnet(lease_client2.addr_, ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

// Test that server allocates a lease from a new subnet when the server
// is reconfigured such that the previous subnet is replaced with a
// new subnet. The client should get the new lease and an old lease
// with zero lifetimes in the Reply.
TEST_F(RebindTest, directClientChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Reconfigure the server so as the new subnet is served on the
    // client's interface. Note that there will also be a new subnet
    // id assigned to the subnet on this interface.
    configure(REBIND_CONFIGS[1], *client.getServer());
    // Try to rebind, using the address that the client had acquired using
    // previous server configuration.

    ASSERT_NO_THROW(client.doRebind());

    // We are expecting that the server has allocated a lease from the new
    // subnet and sent zero lifetimes for a previous lease.

    std::vector<Lease6> old_leases = client.getLeasesWithZeroLifetime();
    ASSERT_EQ(1, old_leases.size());
    EXPECT_EQ(lease_client.addr_, old_leases[0].addr_);

    std::vector<Lease6> new_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, new_leases.size());

    // Make sure, that the lease that client has, is matching the lease
    // in the lease database.
    Lease6Ptr lease_server2 = checkLease(new_leases[0]);
    EXPECT_TRUE(lease_server2);
    // Client should have received Success status code.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(1234));
}

// Check that the server allocates a new lease when the client sends IA_NA
// with a new IAID.
TEST_F(RebindTest, directClientChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the IAID of the lease record that client stores. By adding
    // one to IAID we guarantee that the IAID will change.
    client.clearRequestedIAs();
    client.config_.leases_[0].iaid_ = 1235;
    client.requestAddress(1235);

    // Try to Rebind. The server should allocate new lease for this IAID.
    ASSERT_NO_THROW(client.doRebind());

    // The old lease should be returned with 0 lifetimes.
    std::vector<Lease6> old_leases = client.getLeasesWithZeroLifetime();
    ASSERT_EQ(1, old_leases.size());
    EXPECT_EQ(lease_client.addr_, old_leases[0].addr_);

    // The new lease should be allocated.
    std::vector<Lease6> new_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, new_leases.size());

    Lease6Ptr lease_server2 = checkLease(new_leases[0]);
    EXPECT_TRUE(lease_server2);
    // The Status code returned to the client, should be Success.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(1235));
}

// Check that the server allocates a requested lease for the client when
// this lease has been lost from the database.
TEST_F(RebindTest, directClientLostLease) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // The lease has been acquired. Now, let's explicitly remove it from the
    // lease database.
    Lease6Ptr lease(new Lease6());
    lease->addr_ = lease_client.addr_;
    LeaseMgrFactory::instance().deleteLease(lease);

    // Send Rebind.
    ASSERT_NO_THROW(client.doRebind());

    // The server should re-allocate this lease to the client.
    std::vector<Lease6> new_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, new_leases.size());
    EXPECT_EQ(lease_client.addr_, new_leases[0].addr_);
    // Status code should be Success.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(1234));
}

/// @todo Extend tests for direct client changing address.

// Check that the client can Rebind existing lease through a relay.
TEST_F(RebindTest, relayedClient) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease. Pick the configuration #2 as it
    // specifies the subnet for the relay agent's link address.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[2], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belongs to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->
                selectSubnet(lease_client2.addr_, ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

// Check that the lease is not extended for the relayed client when the
// configuration has changed such that the subnet that client is using
// doesn't exist anymore.
TEST_F(RebindTest, relayedClientChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[2], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Reconfigure the server so as the new subnet is served on the
    // client's interface. Note that there will also be a new subnet
    // id assigned to the subnet on this interface.
    configure(REBIND_CONFIGS[3], *client.getServer());
    // Update relay link address to match the new subnet.
    client.relay_link_addr_ = IOAddress("3001:4::1");
    // Try to rebind, using the address that the client had acquired using
    // previous server configuration.
    ASSERT_NO_THROW(client.doRebind());
    // We are expecting that the server didn't extend the lease because
    // the address that client is using doesn't match the new subnet.
    ASSERT_EQ(0, client.getLeaseNum());
    // Client should have received NoBinding status code.
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(1234));

}

// Check that the lease is not extended for the relayed client when the IAID in
// the Rebind message doesn't match the one recorded for the client.
TEST_F(RebindTest, relayedClientChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[2], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);

    // Modify the IAID of the lease record that client stores. By adding
    // one to IAID we guarantee that the IAID will change.
    client.clearRequestedIAs();
    client.config_.leases_[0].iaid_ = 1235;
    client.requestAddress(1235);

    // Try to Rebind. The server should allocate new lease for this IAID.
    ASSERT_NO_THROW(client.doRebind());

    // The old lease should be returned with 0 lifetimes.
    std::vector<Lease6> old_leases = client.getLeasesWithZeroLifetime();
    ASSERT_EQ(1, old_leases.size());
    EXPECT_EQ(lease_client.addr_, old_leases[0].addr_);

    // The new lease should be allocated.
    std::vector<Lease6> new_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, new_leases.size());

    Lease6Ptr lease_server2 = checkLease(new_leases[0]);
    EXPECT_TRUE(lease_server2);
    // The Status code returned to the client, should be Success.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(1235));
}

// Check that the server allocates a requested lease for the client when
// this lease has been lost from the database.
TEST_F(RebindTest, relayedClientLostLease) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[2], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // The lease has been acquired. Now, let's explicitly remove it from the
    // lease database.
    Lease6Ptr lease(new Lease6());
    lease->addr_ = lease_client.addr_;
    LeaseMgrFactory::instance().deleteLease(lease);

    // Send Rebind.
    ASSERT_NO_THROW(client.doRebind());

    // The server should re-allocate this lease to the client.
    std::vector<Lease6> new_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, new_leases.size());
    EXPECT_EQ(lease_client.addr_, new_leases[0].addr_);
    // Status code should be Success.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(1234));
}

// Check that relayed client receives the IA with lifetimes of 0, when
// client is trying to Rebind using an address it doesn't have.
TEST_F(RebindTest, relayedClientChangingAddress) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[2], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the address of the lease record that client stores. The server
    // should check that the address is invalid (hasn't been allocated for
    // the particular IAID).
    client.config_.leases_[0].addr_ = IOAddress("3000::100");
    // Try to Rebind. The client will use correct IAID but will specify a
    // wrong address. The server will discover that the client has a binding
    // but the address will not match.
    ASSERT_NO_THROW(client.doRebind());
    // Make sure that the server has discarded client's message. In such case,
    // the message sent back to the client should be NULL.
    EXPECT_TRUE(client.getContext().response_)
        << "The server discarded the Rebind message, while it should have"
        " sent a response indicating that the client should stop using the"
        " lease, by setting lifetime values to 0.";
    // Get the client's leases. He should get two addresses:
    // the first one for the bogus 3000::100 address with 0 lifetimes.
    // the second one with the actual lease with non-zero lifetimes.
    ASSERT_EQ(2, client.getLeaseNum());

    // Let's check the first one
    Lease6 lease_client1 = client.getLease(0);
    Lease6 lease_client2 = client.getLease(1);

    if (lease_client1.addr_.toText() != "3000::100") {
        lease_client1 = client.getLease(1);
        lease_client2 = client.getLease(0);
    }

    // The lifetimes should be set to 0, as an explicit notification to the
    // client to stop using invalid prefix.
    EXPECT_EQ(0, lease_client1.valid_lft_);
    EXPECT_EQ(0, lease_client1.preferred_lft_);

    // Let's check the second lease
    // The lifetimes should be set to 0, as an explicit notification to the
    // client to stop using invalid prefix.
    EXPECT_NE(0, lease_client2.valid_lft_);
    EXPECT_NE(0, lease_client2.preferred_lft_);

    // Check that server still has the same lease.
    Lease6Ptr lease_server = checkLease(lease_client);
    EXPECT_TRUE(lease_server);
    // Make sure that the lease in the data base hasn't been added.
    EXPECT_NE(0, lease_server->valid_lft_);
    EXPECT_NE(0, lease_server->preferred_lft_);
}

// Check that the server extends the lease for the client having a prefix.
TEST_F(RebindTest, directClientPD) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.requestPrefix();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[4], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belong to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

// Test that server allocates a lease from a new subnet when the server
// is reconfigured such that the previous subnet is replaced with a
// new subnet. The client should get the new lease and an old lease
// with zero lifetimes in the Reply.
TEST_F(RebindTest, directClientPDChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.requestPrefix();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[4], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Reconfigure the server so as the new subnet is served on the
    // client's interface. Note that there will also be a new subnet
    // id assigned to the subnet on this interface.
    configure(REBIND_CONFIGS[5], *client.getServer());

    // Try to rebind, using the prefix that the client had acquired using
    // previous server configuration.
    client.doRebind();

    // We are expecting that the server has allocated a lease from the new
    // subnet and sent zero lifetimes for a previous lease.

    std::vector<Lease6> old_leases = client.getLeasesWithZeroLifetime();
    ASSERT_EQ(1, old_leases.size());
    EXPECT_EQ(lease_client.addr_, old_leases[0].addr_);

    std::vector<Lease6> new_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, new_leases.size());

    // Make sure, that the lease that client has, is matching the lease
    // in the lease database.
    Lease6Ptr lease_server2 = checkLease(new_leases[0]);
    EXPECT_TRUE(lease_server2);
    // Client should have received Success status code.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(5678));
}

// Check that the server allocates a new lease when the client sends IA_PD
// with a new IAID.
TEST_F(RebindTest, directClientPDChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.requestPrefix();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[4], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);

    // Modify the IAID of the lease record that client stores. By adding
    // one to IAID we guarantee that the IAID will change.
    client.clearRequestedIAs();
    client.config_.leases_[0].iaid_ = 5679;
    client.requestPrefix(5679);

    // Try to Rebind. The server should allocate new lease for this IAID.
    ASSERT_NO_THROW(client.doRebind());

    // The old lease should be returned with 0 lifetimes.
    std::vector<Lease6> old_leases = client.getLeasesWithZeroLifetime();
    ASSERT_EQ(1, old_leases.size());
    EXPECT_EQ(lease_client.addr_, old_leases[0].addr_);

    // The new lease should be allocated.
    std::vector<Lease6> new_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, new_leases.size());

    Lease6Ptr lease_server2 = checkLease(new_leases[0]);
    EXPECT_TRUE(lease_server2);
    // The Status code returned to the client, should be Success.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(5679));
}

// Check that the prefix lifetime is not extended for the client when the
// prefix used in Rebind message doesn't match the one that client has.
TEST_F(RebindTest, directClientPDChangingPrefix) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.requestPrefix();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[4], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the Prefix of the lease record that client stores. The server
    // should check that the prefix is invalid (hasn't been allocated for
    // the particular IAID).
    ASSERT_NE(client.config_.leases_[0].addr_,
              IOAddress("2001:db8:1:10::"));
    client.config_.leases_[0].addr_ = IOAddress("2001:db8:1:10::");
    // Try to Rebind. The client will use correct IAID but will specify a
    // wrong prefix. The server will discover that the client has a binding
    // but the prefix will not match. According to the RFC 8415, section 18.3.5
    // the server may return delegated prefix with lifetime of 0 when it
    // finds that the lease entry for the particular IAID but the prefix
    // is not appropriate. This constitues explicit notification to the
    // client to not use this prefix.
    ASSERT_NO_THROW(client.doRebind());
    // Make sure that the server has discarded client's message. In such case,
    // the message sent back to the client should be NULL.
    EXPECT_TRUE(client.getContext().response_)
        << "The server discarded the Rebind message, while it should have"
        " sent a response indicating that the client should stop using the"
        " lease, by setting lifetime values to 0.";
    // Get the client's lease.
    ASSERT_EQ(2, client.getLeaseNum());

    // Client should get two entries. One with the invalid address he requested
    // with zeroed lifetimes and a second one with the actual prefix he has
    // with non-zero lifetimes.

    // Get the lease with 0 lifetimes.
    std::vector<Lease6> invalid_leases = client.getLeasesWithZeroLifetime();
    ASSERT_EQ(1, invalid_leases.size());
    EXPECT_EQ(0, invalid_leases[0].valid_lft_);
    EXPECT_EQ(0, invalid_leases[0].preferred_lft_);

    // Get the valid lease with non-zero lifetime.
    std::vector<Lease6> valid_leases = client.getLeasesWithNonZeroLifetime();
    ASSERT_EQ(1, valid_leases.size());

    // Check that server still has the same lease.
    Lease6Ptr lease_server = checkLease(valid_leases[0]);
    ASSERT_TRUE(lease_server);
    // Make sure that the lease in the data base hasn't been added.
    EXPECT_NE(0, lease_server->valid_lft_);
    EXPECT_NE(0, lease_server->preferred_lft_);
}

/// @todo Extend PD tests for relayed messages.
/// @todo Extend PD tests to cover same prefix by different length.

// This test checks that the Rebind message is discarded by the server if it
// has been sent to unicast address (RFC 8415, section 18.4).
TEST_F(RebindTest, unicast) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Set the unicast destination address for the Rebind message.
    // The Rebind should be discarded when sent to unicast address,
    // according to section 18.4 of RFC 8415.
    client.setDestAddress(IOAddress("2001:db8:1::1"));
    // Send the Rebind message to a unicast address.
    ASSERT_NO_THROW(client.doRebind());
    // The client's lease should remain with no change (shouldn't be extended)
    // because server is supposed to drop the message sent to a unicast address.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(lease_client2 == lease_client);
    // Check that server still has the lease.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    // Make sure that the server has discarded client's message. In such case,
    // the message sent back to the client should be NULL.
    EXPECT_FALSE(client.getContext().response_);
}

// This test checks that the relayed Rebind message is processed by the server
// when sent to unicast address.
TEST_F(RebindTest, relayedUnicast) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease. Pick the configuration #2 as it
    // specifies the subnet for the relay agent's link address.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[2], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Set the unicast destination address.
    client.setDestAddress(IOAddress("2001:db8:1::1"));
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belongs to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->
                selectSubnet(lease_client2.addr_, ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

// This test verifies that the client can request the prefix delegation
// while it is rebinding an address lease.
TEST_F(RebindTest, requestPrefixInRebind) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.requestAddress();
    client.requestPrefix();

    // Configure the server with NA pools only.
    ASSERT_NO_THROW(configure(REBIND_CONFIGS[0], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());

    // The client should not acquire a PD lease.
    std::vector<Lease6> leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_TRUE(leases_client_pd.empty());
    ASSERT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(5678));

    // Send Rebind message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRebind());
    ASSERT_TRUE(client.getContext().response_);
    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_TRUE(leases_client_pd.empty());
    ASSERT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(5678));

    // Reconfigure the server to use both NA and PD pools.
    configure(REBIND_CONFIGS[6], *client.getServer());

    // Send Rebind message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRebind());

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na_rebound =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_rebound.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(1234));

    // The lease should have been rebound.
    EXPECT_EQ(1000, leases_client_na_rebound[0].cltt_ - leases_client_na[0].cltt_);

    // The client should now also acquire a PD lease.
    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(5678));
}

// This test verifies that the client can request the prefix delegation
// while it is rebinding an address lease.
TEST_F(RebindTest, requestAddressInRebind) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.requestAddress();
    client.requestPrefix();

    // Configure the server with PD pools only.
    ASSERT_NO_THROW(configure(REBIND_CONFIGS[4], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired PD lease.
    std::vector<Lease6> leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(5678));

    // The client should not acquire a NA lease.
    std::vector<Lease6> leases_client_na =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(0, leases_client_na.size());
    ASSERT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(1234));

    // Send Rebind message to the server, including IA_PD and requesting IA_NA.
    // The server should return NoAddrsAvail status code in this case.
    ASSERT_NO_THROW(client.doRebind());
    leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(0, leases_client_na.size());
    ASSERT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(1234));

    // Reconfigure the server to use both NA and PD pools.
    configure(REBIND_CONFIGS[6], *client.getServer());

    // Send Rebind message to the server, including IA_PD and requesting IA_NA.
    ASSERT_NO_THROW(client.doRebind());

    // Make sure that the client has renewed PD lease.
    std::vector<Lease6> leases_client_pd_renewed =
        client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(5678));
    EXPECT_GE(leases_client_pd_renewed[0].cltt_ - leases_client_pd[0].cltt_, 1000);

    // The client should now also acquire a NA lease.
    leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(1234));
}

// This test verifies that the client can request the DOCSIS sub-options.
TEST_F(RebindTest, docsisORO) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Configure the DOCSIS vendor ORO for 32, 33, 34, 37 and 38.
    client.requestDocsisOption(DOCSIS3_V6_TFTP_SERVERS);
    client.requestDocsisOption(DOCSIS3_V6_CONFIG_FILE);
    client.requestDocsisOption(DOCSIS3_V6_SYSLOG_SERVERS);
    client.requestDocsisOption(DOCSIS3_V6_TIME_SERVERS);
    client.requestDocsisOption(DOCSIS3_V6_TIME_OFFSET);
    // Don't add it for now.
    client.useDocsisORO(false);
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[7], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);

    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belong to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->
                selectSubnet(lease_client2.addr_, ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    // No vendor option was included in the renew so there should be none
    // in the received configuration.
    OptionPtr opt = client.config_.findOption(D6O_VENDOR_OPTS);
    ASSERT_FALSE(opt);

    // Add a DOCSIS ORO.
    client.useDocsisORO(true);
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belong to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->
                selectSubnet(lease_client2.addr_, ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);

    // Verify whether there is a vendor option.
    opt = client.config_.findOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);
    // The vendor option must be a OptionVendor object.
    boost::shared_ptr<OptionVendor> vendor =
        boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);
    // The vendor-id should be DOCSIS.
    EXPECT_EQ(VENDOR_ID_CABLE_LABS, vendor->getVendorId());
    // There must be a config file sub-option.
    opt = vendor->getOption(DOCSIS3_V6_CONFIG_FILE);
    // With the expected content.
    OptionStringPtr config_file =
        boost::dynamic_pointer_cast<OptionString>(opt);
    ASSERT_TRUE(opt);
    EXPECT_EQ("normal_erouter_v6.cm", config_file->getValue());
}

// This test verifies that the same options can be specified on the global
// level, subnet level and pool level. The options associated with pools
// are used when the lease is handed out from these pools.
TEST_F(RebindTest, optionsInheritance) {
    Dhcp6Client client;
    // Request a single address and single prefix.
    ASSERT_NO_THROW(client.requestPrefix(0xabac, 64, IOAddress("2001:db8:4::")));
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("3000::45")));
    // Request two options configured for the pools from which the client may get
    // a lease.
    client.requestOption(D6O_NAME_SERVERS);
    client.requestOption(D6O_NIS_SERVERS);
    client.requestOption(D6O_NISP_SERVERS);
    client.requestOption(D6O_SNTP_SERVERS);
    ASSERT_NO_FATAL_FAILURE(configure(REBIND_CONFIGS[8], *client.getServer()));
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());

    // We have provided hints so we should get leases appropriate
    // for the hints we provided.
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("2001:db8:4::"), 64));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("3000::45")));
    // We shouldn't have leases for the prefix and address which we didn't
    // request.
    ASSERT_FALSE(client.hasLeaseForPrefix(IOAddress("2001:db8:3::"), 64));
    ASSERT_FALSE(client.hasLeaseForAddress(IOAddress("3000::11")));

    // We should have received options associated with a prefix pool and
    // address pool from which we have requested the leases. We should not
    // have received options associated with the remaining pools. Instead,
    // we should have received options associated with a subnet.
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "3000:1::567"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NIS_SERVERS, "3000:1::789"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NISP_SERVERS, "3000:2::3"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_SNTP_SERVERS, "3000:2::1"));

    // Let's now also request a prefix and an address from the remaining pools.
    ASSERT_NO_THROW(client.requestPrefix(0x6806, 64, IOAddress("2001:db8:3::")));
    ASSERT_NO_THROW(client.requestAddress(0x6860, IOAddress("3000::11")));

    client.fastFwdTime(1000);

    // Send another Rebind.
    ASSERT_NO_THROW(client.doRebind());

    // We should now have two prefixes from two distinct pools.
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("2001:db8:3::"), 64));
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("2001:db8:4::"), 64));
    //  We should also have two addresses from two distinct pools.
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("3000::45")));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("3000::11")));

    // This time, options from all pools should have been assigned.
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "3000:1::678"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NIS_SERVERS, "3000:1::789"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NISP_SERVERS, "3000:2::3"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_SNTP_SERVERS, "3000:2::2"));
}

}  // namespace
