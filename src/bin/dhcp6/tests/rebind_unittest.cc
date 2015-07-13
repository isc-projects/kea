// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <cc/data.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;

namespace {

/// @brief Set of JSON configurations used throughout the Rebind tests.
///
/// - Configuration 0:
///   - only addresses (no prefixes)
///   - 2 subnets with 2001:db8:1::/64 and 2001:db8:2::64
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
///   - similar to Configuration 5 but with different subnets
///   - 2 subnets: 2001:db8:3::/40 and 2001:db8:4::/40
///   - 2 prefix pools: 2001:db8:3::/72 and 2001:db8:4::/72
///   - delegated length /80
///   - this specific configuration is used by tests which don't use relays
const char* REBIND_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"new-leases-on-renew\": False,"
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
        "\"new-leases-on-renew\": False,"
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
        "\"new-leases-on-renew\": False,"
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
        "\"new-leases-on-renew\": False,"
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
        "\"new-leases-on-renew\": False,"
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
        "\"new-leases-on-renew\": False,"
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

// Test that directly connected client's Rebind message is processed and Reply
// message is sent back.
TEST_F(RebindTest, directClient) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
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

// Test that server doesn't extend the lease when the configuration has changed
// such that the existing subnet is replaced with a different subnet.
TEST_F(RebindTest, directClientChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
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

    // We are expecting that the server didn't extend the lease because
    // the address that client is using doesn't match the new subnet.
    // But, the client still has an old lease.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);

    // The current lease should be exactly the same as old lease,
    // because server shouldn't have extended.
    EXPECT_TRUE(lease_client.addr_ == lease_client2.addr_);
    EXPECT_EQ(0, lease_client2.preferred_lft_);
    EXPECT_EQ(0, lease_client2.valid_lft_);

    // Make sure, that the lease that client has, is matching the lease
    // in the lease database.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    // Client should have received NoBinding status code.
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(0));

}

// Check that the server doesn't extend the lease for the client when the
// client sends IAID which doesn't belong to the lease that client has.
TEST_F(RebindTest, directClientChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the IAID of the lease record that client stores. By adding
    // one to IAID we guarantee that the IAID will change.
    ++client.config_.leases_[0].lease_.iaid_;
    // Try to Rebind. Note that client will use a different IAID (which
    // is not matching IAID that server retains for the client). Server
    // should not find the lease that client is trying to extend and
    // should return NoBinding.
    ASSERT_NO_THROW(client.doRebind());
    // The lease obtained in 4-way exchange should not change after the Rebind
    // attempt.
    Lease6Ptr lease_server2 = checkLease(lease_client);
    EXPECT_TRUE(lease_server2);
    // The Status code returned to the client, should be NoBinding.
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(0));

}

// Check that server sends NoBinding when the lease has been lost from
// the database and client is trying to Rebind it.
TEST_F(RebindTest, directClientLostLease) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // The lease has been acquired. Now, let's explicitly remove it from the
    // lease database.
    LeaseMgrFactory::instance().deleteLease(lease_client.addr_);
    // An attempt to Rebind should fail. The lease should not be found by
    // the server and the server should return NoBinding status code.
    ASSERT_NO_THROW(client.doRebind());
    ASSERT_EQ(1, client.getLeaseNum());
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(0));
}

/// @todo Extend tests for direct client changing address.

// Check that the client can Rebind existing lease through a relay.
TEST_F(RebindTest, relayedClient) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
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
    client.useNA();
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
    // But, the client still has an old lease.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    // The current lease should be exactly the same as old lease,
    // because server shouldn't have extended.
    EXPECT_TRUE(lease_client == lease_client2);
    // Make sure, that the lease that client has, is matching the lease
    // in the lease database.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    // Client should have received NoBinding status code.
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(0));

}

// Check that the lease is not extended for the relayed client when the IAID in
// the Rebind message doesn't match the one recorded for the client.
TEST_F(RebindTest, relayedClientChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
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
    ++client.config_.leases_[0].lease_.iaid_;
    // Try to Rebind. Note that client will use a different IAID (which
    // is not matching IAID that server retains for the client). Server
    // should not find the lease that client is trying to extend and
    // should return NoBinding.
    ASSERT_NO_THROW(client.doRebind());
    // The lease obtained in 4-way exchange should not change after the Rebind
    // attempt.
    Lease6Ptr lease_server2 = checkLease(lease_client);
    EXPECT_TRUE(lease_server2);
    // The Status code returned to the client, should be NoBinding.
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(0));

}

// Check that the relayed client receives NoBinding when the lease that he
// is Rebinding has been lost from the database.
TEST_F(RebindTest, relayedClientLostLease) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
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
    LeaseMgrFactory::instance().deleteLease(lease_client.addr_);
    // An attempt to Rebind should fail. The lease should not be found by
    // the server and the server should return NoBinding status code.
    ASSERT_NO_THROW(client.doRebind());
    ASSERT_EQ(1, client.getLeaseNum());
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(0));
}

// Check that relayed client receives the IA with lifetimes of 0, when
// client is trying to Rebind using an address it doesn't have.
TEST_F(RebindTest, relayedClientChangingAddress) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[2], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the address of the lease record that client stores. The server
    // should check that the address is invalid (hasn't been allocated for
    // the particular IAID).
    client.config_.leases_[0].lease_.addr_ = IOAddress("3000::100");
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
    client.usePD();
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

// Check that the prefix lifetime is not extended for the client in case
// the configuration has been changed such, that the subnet he is using
// doesn't exist anymore.
TEST_F(RebindTest, directClientPDChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[4], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Reconfigure the server so as the new subnet is served on the
    // client's interface. Note that there will also be a new subnet
    // id assigned to the subnet on this interface.
    configure(REBIND_CONFIGS[5], *client.getServer());
    // Try to rebind, using the address that the client had acquired using
    // previous server configuration.
    ASSERT_NO_THROW(client.doRebind());
    // Make sure that the server has discarded client's message. In such case,
    // the message sent back to the client should be NULL.
    EXPECT_FALSE(client.getContext().response_)
        << "The server responded to the Rebind message, while it should have"
        " discarded it because there is no binding for the client.";
    // We are expecting that the server didn't extend the lease because
    // the address that client is using doesn't match the new subnet.
    // But, the client still has an old lease.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    // The current lease should be exactly the same as old lease,
    // because server shouldn't have extended.
    EXPECT_TRUE(lease_client == lease_client2);
    // Make sure, that the lease that client has, is matching the lease
    // in the lease database.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

// Check that the prefix lifetime is not extended for the client when the
// IAID used in the Rebind is not matching the one recorded by the server
// for the particular client.
TEST_F(RebindTest, directClientPDChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[4], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the IAID of the lease record that client stores. By adding
    // one to IAID we guarantee that the IAID will change.
    ++client.config_.leases_[0].lease_.iaid_;
    // Try to Rebind. Note that client will use a different IAID (which
    // is not matching IAID that server retains for the client). This is
    // a condition described in RFC3633, section 12.2 as the server finds
    // no binding for the client. It is an indication that some other
    // server has probably allocated the lease for the client. Hence, our
    // server should discard the message.
    ASSERT_NO_THROW(client.doRebind());
    // Make sure that the server has discarded client's message. In such case,
    // the message sent back to the client should be NULL.
    EXPECT_FALSE(client.getContext().response_)
        << "The server responded to the Rebind message, while it should have"
        " discarded it because there is no binding for the client.";
    // Check that server still has the same lease.
    Lease6Ptr lease_server = checkLease(lease_client);
    EXPECT_TRUE(lease_server);
}

// Check that the prefix lifetime is not extended for the client when the
// prefix used in Rebind message doesn't match the one that client has.
TEST_F(RebindTest, directClientPDChangingPrefix) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[4], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the Prefix of the lease record that client stores. The server
    // should check that the prefix is invalid (hasn't been allocated for
    // the particular IAID).
    ASSERT_NE(client.config_.leases_[0].lease_.addr_,
              IOAddress("2001:db8:1:10::"));
    client.config_.leases_[0].lease_.addr_ = IOAddress("2001:db8:1:10::");
    // Try to Rebind. The client will use correct IAID but will specify a
    // wrong prefix. The server will discover that the client has a binding
    // but the prefix will not match. According to the RFC3633, section 12.2.
    // the server has to return the lease with lifetimes set to 0, when there
    // is a binding for the client but the prefix doesn't match.
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
    Lease6 lease_client1 = client.getLease(0);
    Lease6 lease_client2 = client.getLease(1);

    // The lifetimes should be set to 0, as an explicit notification to the
    // client to stop using invalid prefix.
    EXPECT_EQ(0, lease_client1.valid_lft_);
    EXPECT_EQ(0, lease_client1.preferred_lft_);

    // The lifetimes should be set to 0, as an explicit notification to the
    // client to stop using invalid prefix.
    EXPECT_NE(0, lease_client2.valid_lft_);
    EXPECT_NE(0, lease_client2.preferred_lft_);

    // Check that server still has the same lease.
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    // Make sure that the lease in the data base hasn't been added.
    EXPECT_NE(0, lease_server->valid_lft_);
    EXPECT_NE(0, lease_server->preferred_lft_);
}

/// @todo Extend PD tests for relayed messages.
/// @todo Extend PD tests to cover same prefix by different length.

// This test checks that the Rebind message is discarded by the server if it
// has been sent to unicast address (RFC3315, section 15).
TEST_F(RebindTest, unicast) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(REBIND_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Set the unicast destination address for the Rebind message.
    // The Rebind should be discarded when sent to unicast address,
    // according to section 15 of RFC3315.
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
    client.useNA();
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

} // end of anonymous namespace
