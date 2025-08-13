// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief JSON configuration
std::string FLQ_CONFIG =
    "{ \"interfaces-config\": {"
    "      \"interfaces\": [ \"*\" ]"
    "},"
    "\"min-preferred-lifetime\": 100,"
    "\"preferred-lifetime\": 200,"
    "\"max-preferred-lifetime\": 300,"
    "\"min-valid-lifetime\": 400,"
    "\"valid-lifetime\": 500,"
    "\"max-valid-lifetime\": 600,"
    "\"rebind-timer\": 250,"
    "\"renew-timer\": 250,"
    "\"adaptive-lease-time-threshold\": .5,"
    "\"cache-threshold\": 0.,"
    "\"subnet6\": [ { "
    "    \"subnet\": \"3000::/32\", "
    "    \"id\": 1,"
    "    \"interface\": \"eth0\","
    "    \"pd-pools\": [ {"
    "        \"prefix\": \"2001:db8:1::\","
    "        \"prefix-len\": 48,"
    "        \"delegated-len\": 51"
    "    } ],"
    "    \"pd-allocator\": \"flq\""
    " } ]"
    "}";

/// @brief Test fixture class for testing FLQ / adaptive-lease-time-threshold.
class FLQTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    FLQTest() : Dhcpv6SrvTest(), iface_mgr_test_config_(true) {
    }

    /// @brief Creates a DHCPv6 lease for an address and MAC address.
    ///
    /// @param address Lease address.
    /// @param duid_seed a seed from which the DUID is generated.
    /// @return Created lease pointer.
    Lease6Ptr
    createLease6(const IOAddress& address, uint64_t duid_seed) const {
        vector<uint8_t> duid_vec(sizeof(duid_seed));
        for (unsigned i = 0; i < sizeof(duid_seed); ++i) {
            duid_vec[i] = (duid_seed >> i) & 0xFF;
        }
        DuidPtr duid(new DUID(duid_vec));
        Lease6Ptr lease(new Lease6(Lease::TYPE_PD, address, duid, 1,
                                   800, 1200, 1, HWAddrPtr(), 51));
        return (lease);
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Test allocation with empty pool.
TEST_F(FLQTest, empty) {
    Dhcp6Client client(srv_);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Perform 4-way exchange with the server requesting the last prefix.
    client.requestPrefix(1, 51, IOAddress("2001:db8:1:e000::"));
    ASSERT_NO_THROW(client.doSARR());

    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6Ptr lease = checkLease(client.getLease(0));
    ASSERT_TRUE(lease);

    // Make sure that the client has got the requested prefix.
    EXPECT_EQ("2001:db8:1:e000::", lease->addr_.toText());
    EXPECT_EQ(51, lease->prefixlen_);

    // Preferred lifetime should be the config preferred-lifetime (200).
    EXPECT_EQ(200, lease->preferred_lft_);

    // Valid lifetime should be the config valid-lifetime (500).
    EXPECT_EQ(500, lease->valid_lft_);
}

// Test allocation with almost full pool.
TEST_F(FLQTest, last) {
    Dhcp6Client client(srv_);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first prefixes.
    auto& lease_mgr = LeaseMgrFactory::instance();
    auto lease0 = createLease6(IOAddress("2001:db8:1::"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease0));
    auto lease1 = createLease6(IOAddress("2001:db8:1:2000::"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease6(IOAddress("2001:db8:1:4000::"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease6(IOAddress("2001:db8:1:6000::"), 4);
    EXPECT_TRUE(lease_mgr.addLease(lease3));
    auto lease4 = createLease6(IOAddress("2001:db8:1:8000::"), 5);
    EXPECT_TRUE(lease_mgr.addLease(lease4));
    auto lease5 = createLease6(IOAddress("2001:db8:1:a000::"), 6);
    EXPECT_TRUE(lease_mgr.addLease(lease5));
    auto lease6 = createLease6(IOAddress("2001:db8:1:c000::"), 7);
    EXPECT_TRUE(lease_mgr.addLease(lease6));

    // Perform 4-way exchange with the server.
    client.requestPrefix();
    ASSERT_NO_THROW(client.doSARR());

    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6Ptr lease = checkLease(client.getLease(0));
    ASSERT_TRUE(lease);

    // Make sure that the client has got the requested prefix.
    EXPECT_EQ("2001:db8:1:e000::", lease->addr_.toText());
    EXPECT_EQ(51, lease->prefixlen_);

    // Preferred lifetime should be the config min-preferred-lifetime (100).
    EXPECT_EQ(100, lease->preferred_lft_);

    // Valid lifetime should be the config min-valid-lifetime (400).
    EXPECT_EQ(400, lease->valid_lft_);
}

// Test allocation with an expired lease.
TEST_F(FLQTest, expired) {
    Dhcp6Client client(srv_);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first prefixes.
    auto& lease_mgr = LeaseMgrFactory::instance();
    auto lease0 = createLease6(IOAddress("2001:db8:1::"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease0));
    auto lease1 = createLease6(IOAddress("2001:db8:1:2000::"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease6(IOAddress("2001:db8:1:4000::"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease6(IOAddress("2001:db8:1:6000::"), 4);
    EXPECT_TRUE(lease_mgr.addLease(lease3));
    auto lease4 = createLease6(IOAddress("2001:db8:1:8000::"), 5);
    EXPECT_TRUE(lease_mgr.addLease(lease4));
    auto lease5 = createLease6(IOAddress("2001:db8:1:a000::"), 6);
    EXPECT_TRUE(lease_mgr.addLease(lease5));
    auto lease6 = createLease6(IOAddress("2001:db8:1:c000::"), 7);
    EXPECT_TRUE(lease_mgr.addLease(lease6));
    auto lease7 = createLease6(IOAddress("2001:db8:1:e000::"), 8);
    // Expired lease.
    lease7->cltt_ -= 10000;
    lease7->current_cltt_ -= 10000;
    ASSERT_TRUE(lease7->expired());
    EXPECT_TRUE(lease_mgr.addLease(lease7));

    // Perform 4-way exchange with the server.
    client.requestPrefix();
    ASSERT_NO_THROW(client.doSARR());

    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6Ptr lease = checkLease(client.getLease(0));
    ASSERT_TRUE(lease);

    // Make sure that the client has got the requested prefix.
    EXPECT_EQ("2001:db8:1:e000::", lease->addr_.toText());
    EXPECT_EQ(51, lease->prefixlen_);

    // Preferred lifetime should be the config min-preferred-lifetime (100).
    EXPECT_EQ(100, lease->preferred_lft_);

    // Valid lifetime should be the config min-valid-lifetime (400).
    EXPECT_EQ(400, lease->valid_lft_);
}

// Test allocation with a reclaimed lease.
TEST_F(FLQTest, reclaimed) {
    Dhcp6Client client(srv_);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first prefixes.
    auto& lease_mgr = LeaseMgrFactory::instance();
    auto lease0 = createLease6(IOAddress("2001:db8:1::"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease0));
    auto lease1 = createLease6(IOAddress("2001:db8:1:2000::"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease6(IOAddress("2001:db8:1:4000::"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease6(IOAddress("2001:db8:1:6000::"), 4);
    EXPECT_TRUE(lease_mgr.addLease(lease3));
    auto lease4 = createLease6(IOAddress("2001:db8:1:8000::"), 5);
    EXPECT_TRUE(lease_mgr.addLease(lease4));
    auto lease5 = createLease6(IOAddress("2001:db8:1:a000::"), 6);
    EXPECT_TRUE(lease_mgr.addLease(lease5));
    auto lease6 = createLease6(IOAddress("2001:db8:1:c000::"), 7);
    EXPECT_TRUE(lease_mgr.addLease(lease6));
    auto lease7 = createLease6(IOAddress("2001:db8:1:e000::"), 8);
    // Reclaimed lease.
    lease7->cltt_ -= 10000;
    lease7->current_cltt_ -= 10000;
    ASSERT_TRUE(lease7->expired());
    lease7->state_ = Lease::STATE_EXPIRED_RECLAIMED;
    EXPECT_TRUE(lease_mgr.addLease(lease7));

    // Perform 4-way exchange with the server.
    client.requestPrefix();
    ASSERT_NO_THROW(client.doSARR());

    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6Ptr lease = checkLease(client.getLease(0));
    ASSERT_TRUE(lease);

    // Make sure that the client has got the requested prefix.
    EXPECT_EQ("2001:db8:1:e000::", lease->addr_.toText());
    EXPECT_EQ(51, lease->prefixlen_);

    // Preferred lifetime should be the config min-preferred-lifetime (100).
    EXPECT_EQ(100, lease->preferred_lft_);

    // Valid lifetime should be the config min-valid-lifetime (400).
    EXPECT_EQ(400, lease->valid_lft_);
}
#if 0
// Test renewal with almost empty pool.
TEST_F(FLQTest, renew) {
    Dhcp6Client client(srv_, Dhcp6Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Make sure that the server responded.
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client has got the requested address.
    EXPECT_EQ(*hint, resp->getYiaddr());

    // Valid lifetime should be the valid-lifetime parameter value (200).
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(200, opt->getValue());

    // Age the lease.
    auto& lease_mgr = LeaseMgrFactory::instance();
    Lease6Ptr lease = lease_mgr.getLease6(*hint);
    ASSERT_TRUE(lease);
    lease->cltt_ -= 150;
    lease->current_cltt_ -= 150;
    EXPECT_NO_THROW(lease_mgr.updateLease6(lease));

    // Let's transition the client to Renewing state.
    client.setState(Dhcp6Client::RENEWING);

    // Set the unicast destination address to indicate that it is a renewal.
    client.setDestAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that renewal was ACKed.
    resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client renewed the requested address.
    EXPECT_EQ(*hint, resp->getYiaddr());

    // Valid lifetime should be the valid-lifetime parameter value (200).
    opt = boost::dynamic_pointer_cast<OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(200, opt->getValue());
}

// Test renewal with full pool.
TEST_F(FLQTest, renewFull) {
    Dhcp6Client client(srv_, Dhcp6Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Make sure that the server responded.
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client has got the requested address.
    EXPECT_EQ(*hint, resp->getYiaddr());

    // Valid lifetime should be the valid-lifetime parameter value (200).
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(200, opt->getValue());

    // Age the lease.
    auto& lease_mgr = LeaseMgrFactory::instance();
    Lease6Ptr lease = lease_mgr.getLease6(*hint);
    ASSERT_TRUE(lease);
    lease->cltt_ -= 150;
    lease->current_cltt_ -= 150;
    EXPECT_NO_THROW(lease_mgr.updateLease6(lease));

    // Create leases for the first addresses.
    auto lease1 = createLease6(IOAddress("10.0.0.11"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease6(IOAddress("10.0.0.12"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease6(IOAddress("10.0.0.13"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease3));

    // Let's transition the client to Renewing state.
    client.setState(Dhcp6Client::RENEWING);

    // Set the unicast destination address to indicate that it is a renewal.
    client.setDestAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that renewal was ACKed.
    resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client renewed the requested address.
    EXPECT_EQ(*hint, resp->getYiaddr());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    opt = boost::dynamic_pointer_cast<OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(100, opt->getValue());
}

// Test renewal with full pool but remaining lifetime greater than minimal.
TEST_F(FLQTest, renewRemaining) {
    Dhcp6Client client(srv_, Dhcp6Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Make sure that the server responded.
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client has got the requested address.
    EXPECT_EQ(*hint, resp->getYiaddr());

    // Valid lifetime should be the valid-lifetime parameter value (200).
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(200, opt->getValue());

    // Age the lease but only by 50 seconds.
    auto& lease_mgr = LeaseMgrFactory::instance();
    Lease6Ptr lease = lease_mgr.getLease6(*hint);
    ASSERT_TRUE(lease);
    lease->cltt_ -= 50;
    lease->current_cltt_ -= 50;
    EXPECT_NO_THROW(lease_mgr.updateLease6(lease));

    // Create leases for the first addresses.
    auto lease1 = createLease6(IOAddress("10.0.0.11"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease6(IOAddress("10.0.0.12"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease6(IOAddress("10.0.0.13"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease3));

    // Let's transition the client to Renewing state.
    client.setState(Dhcp6Client::RENEWING);

    // Set the unicast destination address to indicate that it is a renewal.
    client.setDestAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(client.doRequest());

    // Make sure that renewal was ACKed.
    resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client renewed the requested address.
    EXPECT_EQ(*hint, resp->getYiaddr());

    // Valid lifetime should be the remaining lifetime so ~150 seconds.
    opt = boost::dynamic_pointer_cast<OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_NEAR(150, opt->getValue(), 2);
}
#endif

}
