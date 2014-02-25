// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp6/config_parser.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;

namespace {

/// @brief Set of JSON configurations used throughout the Rebind tests.
const std::string REBIND_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/64\" ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pool\": [ \"2001:db8:2::/64\" ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 1
    "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:3::/64\" ],"
        "    \"subnet\": \"2001:db8:3::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " },"
        " {"
        "    \"pool\": [ \"2001:db8:4::/64\" ],"
        "    \"subnet\": \"2001:db8:4::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 2
    "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"3000:1::/64\" ],"
        "    \"subnet\": \"3000:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pool\": [ \"3000:2::/64\" ],"
        "    \"subnet\": \"3000:2::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 3
    "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"3000:3::/64\" ],"
        "    \"subnet\": \"3000:3::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " },"
        " {"
        "    \"pool\": [ \"3000:4::/64\" ],"
        "    \"subnet\": \"3000:4::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 4
    "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"3000:3::/64\" ],"
        "    \"subnet\": \"3000:3::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " },"
        " {"
        "    \"pool\": [ \"3000:4::/64\" ],"
        "    \"subnet\": \"3000:4::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 5
    "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:1:01::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:1::/40\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:2:01::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:2::/40\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 6
    "{ \"interfaces\": [ \"all\" ],"
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

};

/// @brief Test fixture class for testing Rebind.
class RebindTest : public Dhcpv6SrvTest {
public:
    /// @brief Configure the DHCPv6 server using the JSON string.
    ///
    /// @param config New configuration in JSON format.
    /// @param srv Server to be configured.
    void configure(const std::string& config, NakedDhcpv6Srv& srv);

    /// @brief Make 4-way exchange to obtain a lease.
    ///
    /// @param config_index Index of the configuration held in @c REBIND_CONFIGS
    /// to use to configure the server.
    /// @param subnets_num Number of subnets being created with the specified
    /// configuration.
    /// @param client Object representing a test DHCPv6 client to use.
    void requestLease(const int config_index, const int subnets_num,
                      Dhcp6Client& client);

};

void
RebindTest::configure(const std::string& config, NakedDhcpv6Srv& srv) {
    ElementPtr json = Element::fromJSON(config);
    ConstElementPtr status;

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp6Server(srv, json));
    ASSERT_TRUE(status);
    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    ASSERT_EQ(0, rcode);
}

void
RebindTest::requestLease(const int config_index, const int subnets_num,
                         Dhcp6Client& client) {
    // Configure the server.
    configure(REBIND_CONFIGS[config_index], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getSubnets6();
    ASSERT_EQ(subnets_num, subnets->size());
    // Do the actual 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Simulate aging of leases, by moving their cltt_ back by 1000s.
    client.fastFwdTime(1000);
    // Make sure that we have obtained a lease that belongs to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getSubnet6(lease_client.addr_,
                                              ClientClasses()));
    // Check that the client's lease matches the information on the server
    // side.
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    // And that status code was OK.
    EXPECT_EQ(STATUS_Success, client.getStatusCode(0));
}

TEST_F(RebindTest, directClient) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belong to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getSubnet6(lease_client2.addr_,
                                              ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

TEST_F(RebindTest, directClientChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
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
    EXPECT_TRUE(lease_client == lease_client2);
    // Make sure, that the lease that client has, is matching the lease
    // in the lease database.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    // Client should have received NoBinding status code.
    EXPECT_EQ(STATUS_NoBinding, client.getStatusCode(0));

}

TEST_F(RebindTest, directClientChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
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

TEST_F(RebindTest, directClientLostLease) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
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
    ASSERT_NO_FATAL_FAILURE(requestLease(2, 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belongs to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getSubnet6(lease_client2.addr_,
                                              ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

TEST_F(RebindTest, relayedClientChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(2, 2, client));
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

TEST_F(RebindTest, relayedClientChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(2, 2, client));
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

TEST_F(RebindTest, relayedClientLostLease) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Configure DHCPv6 client to simulate sending the message through a relay
    // agent. The default link-addr is 3001:1::1. This address should be used
    // by the server to pick the suitable subnet.
    client.useRelay();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(2, 2, client));
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

TEST_F(RebindTest, relayedClientChangingAddress) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(2, 2, client));
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
    // Get the client's lease.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    // The lifetimes should be set to 0, as an explicit notification to the
    // client to stop using invalid prefix.
    EXPECT_EQ(0, lease_client2.valid_lft_);
    EXPECT_EQ(0, lease_client2.preferred_lft_);
    // Check that server still has the same lease.
    Lease6Ptr lease_server = checkLease(lease_client);
    EXPECT_TRUE(lease_server);
    // Make sure that the lease in the data base hasn't been addected.
    EXPECT_NE(0, lease_server->valid_lft_);
    EXPECT_NE(0, lease_server->preferred_lft_);
}


TEST_F(RebindTest, directClientPD) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(5, 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());
    // The client should still have one lease which belong to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getSubnet6(lease_client2.addr_,
                                              ClientClasses()));
    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);
    // Make sure, that the client's lease matches the lease held by the
    // server.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
}

TEST_F(RebindTest, directClientPDChangingSubnet) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(5, 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Reconfigure the server so as the new subnet is served on the
    // client's interface. Note that there will also be a new subnet
    // id assigned to the subnet on this interface.
    configure(REBIND_CONFIGS[6], *client.getServer());
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

TEST_F(RebindTest, directClientPDChangingIAID) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(5, 2, client));
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

TEST_F(RebindTest, directClientPDChangingPrefix) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(5, 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Modify the Prefix of the lease record that client stores. The server
    // should check that the prefix is invalid (hasn't been allocated for
    // the particular IAID).
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
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    // The lifetimes should be set to 0, as an explicit notification to the
    // client to stop using invalid prefix.
    EXPECT_EQ(0, lease_client2.valid_lft_);
    EXPECT_EQ(0, lease_client2.preferred_lft_);
    // Check that server still has the same lease.
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    // Make sure that the lease in the data base hasn't been addected.
    EXPECT_NE(0, lease_server->valid_lft_);
    EXPECT_NE(0, lease_server->preferred_lft_);
}

/// @todo Extend PD tests for relayed messages.

// This test checks that the Rebind message is discarded by the server if it
// has been sent to unicast address (RFC3315, section 15).
TEST_F(RebindTest, unicast) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client = client.getLease(0);
    // Set the unicast destionation address for the Rebind message.
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


} // end of anonymous namespace
