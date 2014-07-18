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
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
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
/// - Configuration 5:
///   - only prefixes (no addresses)
///   - 2 subnets: 2001:db8:1::/40 and 2001:db8:2::/40
///   - 2 prefix pools: 2001:db8:1::/72 and 2001:db8:2::/72
///   - 1 subnet for eth0 and 1 subnet for eth1
///   - this specific configuration is used by tests which don't use relays
///
/// - Configuration 6:
///   - similar to Configuration 5 but with different subnets
///   - 2 subnets: 2001:db8:3::/40 and 2001:db8:4::/40
///   - 2 prefix pools: 2001:db8:3::/72 and 2001:db8:4::/72
///   - delegated length /80
///   - this specific configuration is used by tests which don't use relays
const char* CONFIRM_CONFIGS[] = {
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

// Configuration 5
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
class ConfirmTest : public Dhcpv6SrvTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    ConfirmTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
    }

    /// @brief Increases last byte of the address.
    ///
    /// This function is helpful to find a different address that is within
    /// the same subnet as the input address. It is achieved by increasing
    /// the last byte of the input address by one.
    ///
    /// @param input_addr An input address.
    ///
    /// @return New address.
    IOAddress bumpAddress(const IOAddress& input_addr);

    /// @brief Increases specific byte in the address by one.
    ///
    /// This function is called by @c bumpAddress and @c bumpSubnet.
    ///
    /// @param input_addr An input address.
    ///
    /// @return New address.
    IOAddress bumpByteInAddress(const IOAddress& input_addr,
                                const size_t byte_num);

    /// @brief Increases the first byte of the address.
    ///
    /// This function is helpful to find an address which belongs to the
    /// different subnet than the input address. It is achived by increasing
    /// the first byte of the input address.
    ///
    /// @param input_addr An input addres.
    ///
    /// @return New address.
    IOAddress bumpSubnet(const IOAddress& input_addr);

    /// @brief Make 4-way exchange to obtain a lease.
    ///
    /// @param config_index Index of the configuration held in @c CONFIRM_CONFIGS
    /// to use to configure the server.
    /// @param subnets_num Number of subnets being created with the specified
    /// configuration.
    /// @param client Object representing a test DHCPv6 client to use.
    void requestLease(const int config_index, const int subnets_num,
                      Dhcp6Client& client);

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

void
ConfirmTest::requestLease(const int config_index, const int subnets_num,
                         Dhcp6Client& client) {
    // Check that the index is in the configuration table.
    ASSERT_LT(config_index, sizeof(CONFIRM_CONFIGS)/sizeof(CONFIRM_CONFIGS[0]));
    // Configure the server.
    configure(CONFIRM_CONFIGS[config_index], *client.getServer());
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

IOAddress
ConfirmTest::bumpAddress(const IOAddress& input_addr) {
    return (bumpByteInAddress(input_addr, V6ADDRESS_LEN - 1));
}

IOAddress
ConfirmTest::bumpByteInAddress(const IOAddress& input_addr,
                               const size_t byte_num) {
    std::vector<uint8_t> input_addr_buffer = input_addr.toBytes();
    if (input_addr_buffer.size() > byte_num) {
        ++input_addr_buffer[byte_num];
        return (IOAddress::fromBytes(AF_INET6, &input_addr_buffer[0]));
    }
    return (input_addr);
}


IOAddress
ConfirmTest::bumpSubnet(const IOAddress& input_addr) {
    return (bumpByteInAddress(input_addr, 0));
}

// Test that directly connected client's Confirm message is processed and Reply
// message is sent back. In this test case, the client sends Confirm for two
// addresses that belong to the same IAID and are sent within the same IA_NA
// option.
TEST_F(ConfirmTest, directClientSameIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
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
// IA_NA options.
TEST_F(ConfirmTest, directClientDifferentIAID) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
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
    // Make sure that the server id has been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));


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


// Test that relayed client's Confirm message is processed and Reply message
// is sent back.
TEST_F(ConfirmTest, relayedClient) {
    Dhcp6Client client;
    // Client to send relayed message.
    client.useRelay();
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(2, 2, client));
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
    // Make sure that the server id has been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));
}

// Test that the Confirm message without any addresses is discarded.
TEST_F(ConfirmTest, relayedClientNoAddress) {
    Dhcp6Client client;
    // Configure the server.
    configure(CONFIRM_CONFIGS[2], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getSubnets6();
    ASSERT_EQ(2, subnets->size());
    // Client to send relayed message.
    client.useRelay();
    // Send Confirm message to the server. This message will contain no
    // addresses because client has no leases.
    ASSERT_NO_THROW(client.doConfirm());
    EXPECT_FALSE(client.getContext().response_);
}

// This test checks that the relayed Confirm messsage is processed by the server
// when sent to unicast address.
TEST_F(ConfirmTest, relayedUnicast) {
    Dhcp6Client client;
    // Client to send relayed message.
    client.useRelay();
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(2, 2, client));
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
    // Make sure that the server id has been included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_SERVERID));
}

// This test checks that the Confirm message is discarded by the server if it
// has been sent to unicast address (RFC3315, section 15).
TEST_F(ConfirmTest, unicast) {
    Dhcp6Client client;
    // Configure client to request IA_NA.
    client.useNA();
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(requestLease(0, 2, client));
    // Make sure the client has got the lease.
    ASSERT_GT(client.getLeaseNum(), 0);
    // Send Confirm message to the server to the unicast address.
    client.setDestAddress(IOAddress("2001:db8:1::1"));
    ASSERT_NO_THROW(client.doConfirm());
    // Mak sure that the server discarded client's Confirm message.
    EXPECT_FALSE(client.getContext().response_);
}

} // end of anonymous namespace
