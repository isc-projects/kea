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

    /// @brief Check the response.
    ///
    /// @param resp the response.
    /// @param expected the expected lifetime.
    /// @param near use near comparision (when true) or equality (when false).
    void checkResponse(Pkt4Ptr resp, uint32_t expected, bool near = false) {
        ASSERT_TRUE(resp);

        // Make sure that the server has responded with DHCPACK.
        ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

        // Make sure that the client has got the requested address.
        EXPECT_EQ("10.0.0.14", resp->getYiaddr().toText());

        // Verify the valid liftime.
        OptionUint32Ptr opt = boost::dynamic_pointer_cast<
            OptionUint32>(resp->getOption(DHO_DHCP_LEASE_TIME));
        ASSERT_TRUE(opt);
        if (near) {
            EXPECT_NEAR(expected, opt->getValue(), 2);
        } else {
            EXPECT_EQ(expected, opt->getValue());
        }
    }

    /// @brief Allocate all pool leases leaving the last one free.
    void fill() {
        auto& lease_mgr = LeaseMgrFactory::instance();
        auto lease1 = createLease4(IOAddress("10.0.0.11"), 1);
        EXPECT_TRUE(lease_mgr.addLease(lease1));
        auto lease2 = createLease4(IOAddress("10.0.0.12"), 2);
        EXPECT_TRUE(lease_mgr.addLease(lease2));
        auto lease3 = createLease4(IOAddress("10.0.0.13"), 3);
        EXPECT_TRUE(lease_mgr.addLease(lease3));
    }

    /// @brief Age and commit a lease.
    ///
    /// @param lease the lease.
    /// @param delay the amount of time backward.
    /// @param update when false add the lease, when true update the lease.
    /// @param reclaim when true change the state.
    void ageLease(Lease4Ptr lease, uint32_t delay, bool update,
                  bool reclaim = false) {
        ASSERT_TRUE(lease);
        lease->cltt_ -= delay;
        lease->current_cltt_ -= delay;
        if (reclaim) {
            lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
        }
        auto& lease_mgr = LeaseMgrFactory::instance();
        if (update) {
            EXPECT_NO_THROW(lease_mgr.updateLease4(lease));
        } else {
            EXPECT_TRUE(lease_mgr.addLease(lease));
        }
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

    // Valid lifetime should be the valid-lifetime parameter value (200).
    Pkt4Ptr resp = client.getContext().response_;
    checkResponse(resp, 200);
}

// Test allocation with almost full pool.
TEST_F(FLQTest, last) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first addresses.
    fill();

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    Pkt4Ptr resp = client.getContext().response_;
    checkResponse(resp, 100);
}

// Test allocation with an expired lease.
TEST_F(FLQTest, expired) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first addresses.
    fill();

    // Create and expire last lease.
    auto lease = createLease4(IOAddress("10.0.0.14"), 4);
    ageLease(lease, 1000, false);
    ASSERT_TRUE(lease->expired());

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    Pkt4Ptr resp = client.getContext().response_;
    checkResponse(resp, 100);
}

// Test allocation with a reclaimed lease.
TEST_F(FLQTest, reclaimed) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Create leases for the first addresses.
    fill();

    // Create and reclaim last lease.
    auto lease = createLease4(IOAddress("10.0.0.14"), 4);
    ageLease(lease, 1000, false, true);

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    Pkt4Ptr resp = client.getContext().response_;
    checkResponse(resp, 100);
}

// Test renewal with almost empty pool.
TEST_F(FLQTest, renew) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Valid lifetime should be the valid-lifetime parameter value (200).
    Pkt4Ptr resp = client.getContext().response_;
    checkResponse(resp, 200);

    // Age the lease.
    auto& lease_mgr = LeaseMgrFactory::instance();
    Lease4Ptr lease = lease_mgr.getLease4(*hint);
    ageLease(lease, 150, true);
    ASSERT_FALSE(lease->expired());

    // Let's transition the client to Renewing state.
    client.setState(Dhcp4Client::RENEWING);

    // Set the unicast destination address to indicate that it is a renewal.
    client.setDestAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(client.doRequest());

    // Valid lifetime should be the valid-lifetime parameter value (200).
    resp = client.getContext().response_;
    checkResponse(resp, 200);
}

// Test renewal with full pool.
TEST_F(FLQTest, renewFull) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Valid lifetime should be the valid-lifetime parameter value (200).
    Pkt4Ptr resp = client.getContext().response_;
    checkResponse(resp, 200);

    // Create leases for the first addresses.
    fill();

    // Age the lease.
    auto& lease_mgr = LeaseMgrFactory::instance();
    Lease4Ptr lease = lease_mgr.getLease4(*hint);
    ageLease(lease, 150, true);
    ASSERT_FALSE(lease->expired());

    // Let's transition the client to Renewing state.
    client.setState(Dhcp4Client::RENEWING);

    // Set the unicast destination address to indicate that it is a renewal.
    client.setDestAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(client.doRequest());

    // Valid lifetime should be the min-valid-lifetime parameter value (100).
    resp = client.getContext().response_;
    checkResponse(resp, 100);
}

// Test renewal with full pool but remaining lifetime greater than minimal.
TEST_F(FLQTest, renewRemaining) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(FLQ_CONFIG, *client.getServer());

    // Obtain a lease from the server using the 4-way exchange.
    boost::shared_ptr<IOAddress> hint(new IOAddress("10.0.0.14"));
    ASSERT_NO_THROW(client.doDORA(hint));

    // Valid lifetime should be the valid-lifetime parameter value (200).
    Pkt4Ptr resp = client.getContext().response_;
    checkResponse(resp, 200);

    // Create leases for the first addresses.
    fill();

    // Age the lease but only by 50 seconds.
    auto& lease_mgr = LeaseMgrFactory::instance();
    Lease4Ptr lease = lease_mgr.getLease4(*hint);
    ageLease(lease, 50, true);
    ASSERT_FALSE(lease->expired());

    // Let's transition the client to Renewing state.
    client.setState(Dhcp4Client::RENEWING);

    // Set the unicast destination address to indicate that it is a renewal.
    client.setDestAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(client.doRequest());

    // Valid lifetime should be the remaining lifetime so ~150 seconds.
    resp = client.getContext().response_;
    checkResponse(resp, 150, true);
}

}
