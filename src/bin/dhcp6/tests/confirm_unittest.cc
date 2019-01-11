// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
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

/// @brief Set of JSON configurations used throughout the Confirm tests.
///
/// - Configuration 0:
///   - only addresses (no prefixes)
///   - 2 subnets with 2001:db8:1::/64 and 2001:db8:2::/64
///   - 1 subnet for eth0 and 1 subnet for eth1
///
/// - Configuration 1:
///   - similar to Configuration 0
///   - pools configured: 3000:1::/64 and 3000:2::/64
///   - this specific configuration is used by tests using relays
///
const char* CONFIRM_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [  { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pools\": [  { \"pool\": \"2001:db8:2::/64\" } ],"
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
        "    \"pools\": [  { \"pool\": \"3000:1::/64\" } ],"
        "    \"subnet\": \"3000:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " },"
        " {"
        "    \"pools\": [  { \"pool\": \"3000:2::/64\" } ],"
        "    \"subnet\": \"3000:2::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }"
};

/// @brief Test fixture class for testing Confirm..
class ConfirmTest : public isc::dhcp::test::Dhcpv6MessageTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    ConfirmTest()
        : Dhcpv6MessageTest() {
    }

};


// Test that client-id is mandatory and server-id forbidden for Confirm messages
TEST_F(ConfirmTest, sanityCheck) {
    NakedDhcpv6Srv srv(0);

    // A message with no client-id should fail
    Pkt6Ptr confirm = Pkt6Ptr(new Pkt6(DHCPV6_CONFIRM, 1234));
    EXPECT_FALSE(srv.sanityCheck(confirm));

    // A message with a single client-id should succeed
    OptionPtr clientid = generateClientId();
    confirm->addOption(clientid);
    EXPECT_TRUE(srv.sanityCheck(confirm));

    // A message with server-id present should fail
    confirm->addOption(srv.getServerID());
    EXPECT_FALSE(srv.sanityCheck(confirm));
}

// Test that directly connected client's Confirm message is processed and Reply
// message is sent back. In this test case, the client sends Confirm for two
// addresses that belong to the same IAID and are sent within the same IA_NA
// option (RFC 8415, section 18.3.3).
TEST_F(ConfirmTest, directClientSameIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(CONFIRM_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client1 = client.getLease(0);
    // Clone the lease and modify its address so as it is still in the range
    // of the subnet to which the first lease belongs. When the client sends
    // the Confirm it should include both addresses and the server should
    // send Success because both of these addresses are on-link, regardless
    // what the server has in the lease database.
    Lease6 lease_client2 = lease_client1;
    lease_client2.addr_ = bumpAddress(lease_client2.addr_);
    client.createLease(lease_client2);
    ASSERT_EQ(2, client.getLeaseNum());
    // Send Confirm message to the server.
    ASSERT_NO_THROW(client.doConfirm());
    // Client should have received a status code option and this option should
    // indicate the success.
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_Success, client.getStatusCode());

    ASSERT_EQ(2, client.getLeaseNum());
    lease_client2 = client.getLease(1);
    lease_client2.addr_ = bumpSubnet(lease_client2.addr_);
    client.createLease(lease_client2);
    // Send confirm to the server. This time, one of the leases contains the
    // address which doesn't belong to the configured subnet and the server
    // should respond with STATUS_NotOnLink.
    ASSERT_NO_THROW(client.doConfirm());
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_NotOnLink, client.getStatusCode());
    // Make sure that the server id has been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));
}

// Test that directly connected client's Confirm message is processed and Reply
// message is sent back. In this test case, the client sends Confirm for two
// addresses that belong to different IAIDs and are sent within the different
// IA_NA options (RFC 8415, section 18.3.3).
TEST_F(ConfirmTest, directClientDifferentIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(CONFIRM_CONFIGS[0], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client1 = client.getLease(0);
    // Clone the lease and modify its address so as it is still in the range
    // of the subnet to which the first lease belongs. When the client sends
    // the Confirm it should include both addresses and the server should
    // send Success because both of these addresses are on-link, regardless
    // what the server has in the lease database.
    Lease6 lease_client2 = lease_client1;
    ++lease_client2.iaid_;
    lease_client2.addr_ = bumpAddress(lease_client2.addr_);
    client.createLease(lease_client2);
    ASSERT_EQ(2, client.getLeaseNum());
    // Send Confirm message to the server.
    ASSERT_NO_THROW(client.doConfirm());
    // Client should have received a status code option and this option should
    // indicate the success.
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_Success, client.getStatusCode());
    // Make sure that the server id and client id have been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_CLIENTID));

    ASSERT_EQ(2, client.getLeaseNum());
    lease_client2 = client.getLease(1);
    lease_client2.addr_ = bumpSubnet(lease_client2.addr_);
    client.createLease(lease_client2);
    // Send confirm to the server. This time, one of the leases contains the
    // address which doesn't belong to the configured subnet and the server
    // should respond with STATUS_NotOnLink.
    ASSERT_NO_THROW(client.doConfirm());
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_NotOnLink, client.getStatusCode());
    // Make sure that the server id have been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_CLIENTID));
}


// Test that relayed client's Confirm message is processed and Reply message
// is sent back (RFC 8415, section 18.3.3).
TEST_F(ConfirmTest, relayedClient) {
    Dhcp6Client client;
    // Client to send relayed message.
    client.useRelay();
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(CONFIRM_CONFIGS[1], 2, client));
    // Keep the client's lease for future reference.
    Lease6 lease_client1 = client.getLease(0);
    // Clone the lease and modify its address so as it is still in the range
    // of the subnet to which the first lease belongs. When the client sends
    // the Confirm it should include both addresses and the server should
    // send Success because both of these addresses are on-link, regardless
    // what the server has in the lease database.
    Lease6 lease_client2 = lease_client1;
    lease_client2.addr_ = bumpAddress(lease_client2.addr_);
    ++lease_client2.iaid_;
    client.createLease(lease_client2);
    // Send Confirm message to the server.
    ASSERT_NO_THROW(client.doConfirm());
    // Client should have received a status code option and this option should
    // indicate the success.
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_Success, client.getStatusCode());

    lease_client2 = client.getLease(1);
    lease_client2.addr_ = bumpSubnet(lease_client2.addr_);
    client.createLease(lease_client2);
    // Send confirm to the server. This time, one of the leases contains the
    // address which doesn't belong to the configured subnet and the server
    // should respond with STATUS_NotOnLink.
    ASSERT_NO_THROW(client.doConfirm());
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_NotOnLink, client.getStatusCode());
    // Make sure that the server id and client id have been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_CLIENTID));
}

// Test that the Confirm message without any addresses is discarded
// (RFC 8415, section 18.3.3).
TEST_F(ConfirmTest, relayedClientNoAddress) {
    Dhcp6Client client;
    // Configure the server.
    configure(CONFIRM_CONFIGS[1], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());
    // Client to send relayed message.
    client.useRelay();
    // Send Confirm message to the server. This message will contain no
    // addresses because client has no leases.
    ASSERT_NO_THROW(client.doConfirm());
    EXPECT_FALSE(client.getContext().response_);
}

// This test checks that the server processes Confirm message correctly if
// the subnet can't be selected for the client (RFC 8415, section 18.3.3).
TEST_F(ConfirmTest, relayedClientNoSubnet) {
    Dhcp6Client client;
    // Client to send relayed message.
    client.useRelay();
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(CONFIRM_CONFIGS[1], 2, client));
    // Now that the client has a lease, let's remove any subnets to check
    // how the server would respond to the Confirm.
    ASSERT_NO_THROW(CfgMgr::instance().clear());
    // Send Confirm message to the server.
    ASSERT_NO_THROW(client.doConfirm());
    // Client should have received a status code option and this option should
    // indicate that the client is NotOnLink because subnet could not be
    // selected.
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_NotOnLink, client.getStatusCode());

    // Let's test another case that the client sends no addresses in the Confirm
    // message. The subnet can't be selected for that client as in the previous
    // case but this time the server must discard the client's message because
    // it contains no addresses (is invalid).

    // Set lifetimes to 0 so as the Confirm will ignore the specific address
    // and send an empty IA_NA.
    client.config_.leases_[0].preferred_lft_ = 0;
    client.config_.leases_[0].valid_lft_ = 0;
    ASSERT_NO_THROW(client.doConfirm());
    EXPECT_FALSE(client.getContext().response_);

    // Do similar test but this time remove the lease so as no IA_NA option
    // is sent.
    client.config_.clear();
    ASSERT_NO_THROW(client.doConfirm());
    EXPECT_FALSE(client.getContext().response_);
}

// This test checks that the relayed Confirm message is processed by the server
// when sent to unicast address.
TEST_F(ConfirmTest, relayedUnicast) {
    Dhcp6Client client;
    // Client to send relayed message.
    client.useRelay();
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(CONFIRM_CONFIGS[1], 2, client));
    // Make sure we have got the lease.
    ASSERT_GT(client.getLeaseNum(), 0);
    client.setDestAddress(IOAddress("2001:db8:1::1"));
    // Send Confirm message to the server.
    ASSERT_NO_THROW(client.doConfirm());
    // Client should have received a response.
    ASSERT_TRUE(client.getContext().response_);
    // Client should have received a status code option and this option should
    // indicate the success.
    ASSERT_TRUE(client.receivedStatusCode());
    ASSERT_EQ(STATUS_Success, client.getStatusCode());
    // Make sure that the server id and client id have been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_CLIENTID));
}

// This test checks that the Confirm message is discarded by the server if it
// has been sent to unicast address (RFC 8415, section 18.3.3).
TEST_F(ConfirmTest, unicast) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.requestAddress();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(CONFIRM_CONFIGS[0], 2, client));
    // Make sure the client has got the lease.
    ASSERT_GT(client.getLeaseNum(), 0);
    // Send Confirm message to the server to the unicast address.
    client.setDestAddress(IOAddress("2001:db8:1::1"));
    ASSERT_NO_THROW(client.doConfirm());
    // Mak sure that the server discarded client's Confirm message.
    EXPECT_FALSE(client.getContext().response_);
}

} // end of anonymous namespace
