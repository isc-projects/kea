// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option_int.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
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
    "\"min-valid-lifetime\": 100,"
    "\"valid-lifetime\": 200,"
    "\"max-valid-lifetime\": 300,"
    "\"adaptive-lease-time-threshold\": .5,"
    "\"cache-threshold\": 0.,"
    "\"subnet4\": [ { "
    "    \"subnet\": \"10.0.0.0/24\", "
    "    \"id\": 1,"
    "    \"pools\": [ { \"pool\": \"10.0.0.11-10.0.0.14\" } ],"
    "    \"allocator\": \"flq\""
    " } ]"
    "}";

/// @brief Test fixture class for testing FLQ / adaptive-lease-time-threshold.
class FLQTest : public Dhcpv4SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    FLQTest() : Dhcpv4SrvTest(), iface_mgr_test_config_(true) {
    }

    /// @brief Creates a DHCPv4 lease for an address and MAC address.
    ///
    /// @param address Lease address.
    /// @param hw_address_seed a seed from which the hardware address is generated.
    /// @return Created lease pointer.
    Lease4Ptr
    createLease4(const IOAddress& address, uint64_t hw_address_seed) const {
        vector<uint8_t> hw_address_vec(sizeof(hw_address_seed));
        for (unsigned i = 0; i < sizeof(hw_address_seed); ++i) {
            hw_address_vec[i] = (hw_address_seed >> i) & 0xFF;
        }
        HWAddrPtr hw_address(new HWAddr(hw_address_vec, HTYPE_ETHER));
        Lease4Ptr lease(new Lease4(address, hw_address, ClientIdPtr(),
                                   600, time(0), 1));
        return (lease);
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Test allocation with empty pool.
TEST_F(FLQTest, empty) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Perform 4-way exchange with the server requesting the last address.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Make sure that the server responded.
    Pkt4Ptr resp = client.getContext().response_;
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
}

// Test allocation with almost full pool.
TEST_F(FLQTest, last) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first addresses.
    auto& lease_mgr = LeaseMgrFactory::instance();
    auto lease1 = createLease4(IOAddress("10.0.0.11"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease4(IOAddress("10.0.0.12"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease4(IOAddress("10.0.0.13"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease3));

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client has got the last address.
    EXPECT_EQ("10.0.0.14", resp->getYiaddr().toText());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(100, opt->getValue());
}

// Test allocation with an expired lease.
TEST_F(FLQTest, expired) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first addresses.
    auto& lease_mgr = LeaseMgrFactory::instance();
    auto lease1 = createLease4(IOAddress("10.0.0.11"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease4(IOAddress("10.0.0.12"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease4(IOAddress("10.0.0.13"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease3));
    auto lease4 = createLease4(IOAddress("10.0.0.14"), 4);
    // Expired lease.
    lease4->cltt_ -= 1000;
    lease4->current_cltt_ -= 1000;
    ASSERT_TRUE(lease4->expired());
    EXPECT_TRUE(lease_mgr.addLease(lease4));

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client has got the last address.
    EXPECT_EQ("10.0.0.14", resp->getYiaddr().toText());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(100, opt->getValue());
}

// Test allocation with a reclaimed lease.
TEST_F(FLQTest, reclaimed) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first addresses.
    auto& lease_mgr = LeaseMgrFactory::instance();
    auto lease1 = createLease4(IOAddress("10.0.0.11"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease4(IOAddress("10.0.0.12"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease4(IOAddress("10.0.0.13"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease3));
    auto lease4 = createLease4(IOAddress("10.0.0.14"), 4);
    // Reclaimed lease.
    lease4->cltt_ -= 1000;
    lease4->current_cltt_ -= 1000;
    lease4->state_ = Lease::STATE_EXPIRED_RECLAIMED;
    EXPECT_TRUE(lease_mgr.addLease(lease4));

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Make sure that the client has got the last address.
    EXPECT_EQ("10.0.0.14", resp->getYiaddr().toText());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
    ASSERT_TRUE(opt);
    EXPECT_EQ(100, opt->getValue());
}

// Test renewal with almost empty pool.
TEST_F(FLQTest, renew) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Make sure that the server responded.
    Pkt4Ptr resp = client.getContext().response_;
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
    Lease4Ptr lease = lease_mgr.getLease4(*hint);
    ASSERT_TRUE(lease);
    lease->cltt_ -= 150;
    lease->current_cltt_ -= 150;
    EXPECT_NO_THROW(lease_mgr.updateLease4(lease));

    // Let's transition the client to Renewing state.
    client.setState(Dhcp4Client::RENEWING);

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
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Make sure that the server responded.
    Pkt4Ptr resp = client.getContext().response_;
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
    Lease4Ptr lease = lease_mgr.getLease4(*hint);
    ASSERT_TRUE(lease);
    lease->cltt_ -= 150;
    lease->current_cltt_ -= 150;
    EXPECT_NO_THROW(lease_mgr.updateLease4(lease));

    // Create leases for the first addresses.
    auto lease1 = createLease4(IOAddress("10.0.0.11"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease4(IOAddress("10.0.0.12"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease4(IOAddress("10.0.0.13"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease3));

    // Let's transition the client to Renewing state.
    client.setState(Dhcp4Client::RENEWING);

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
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Make sure that the server responded.
    Pkt4Ptr resp = client.getContext().response_;
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
    Lease4Ptr lease = lease_mgr.getLease4(*hint);
    ASSERT_TRUE(lease);
    lease->cltt_ -= 50;
    lease->current_cltt_ -= 50;
    EXPECT_NO_THROW(lease_mgr.updateLease4(lease));

    // Create leases for the first addresses.
    auto lease1 = createLease4(IOAddress("10.0.0.11"), 1);
    EXPECT_TRUE(lease_mgr.addLease(lease1));
    auto lease2 = createLease4(IOAddress("10.0.0.12"), 2);
    EXPECT_TRUE(lease_mgr.addLease(lease2));
    auto lease3 = createLease4(IOAddress("10.0.0.13"), 3);
    EXPECT_TRUE(lease_mgr.addLease(lease3));

    // Let's transition the client to Renewing state.
    client.setState(Dhcp4Client::RENEWING);

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

}
