// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <stats/stats_mgr.h>
#include <boost/shared_ptr.hpp>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;

namespace {

/// @brief Set of JSON configurations used throughout the Release tests.
///
/// - Configuration 0:
///   - Used for testing Release message processing
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - Router option present: 10.0.0.200 and 10.0.0.201
const char* RELEASE_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"id\": 1,"
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"option-data\": [ {"
        "        \"name\": \"routers\","
        "        \"data\": \"10.0.0.200,10.0.0.201\""
        "    } ]"
        " } ]"
    "}"
};

/// @brief Test fixture class for testing 4-way (DORA) exchanges.
///
/// @todo Currently there is a limit number of test cases covered here.
/// In the future it is planned that the tests from the
/// dhcp4_srv_unittest.cc will be migrated here and will use the
/// @c Dhcp4Client class.
class ReleaseTest : public Dhcpv4SrvTest {
public:

    enum ExpectedResult {
        SHOULD_PASS_EXPIRED,
        SHOULD_PASS_DELETED,
        SHOULD_FAIL
    };

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    ReleaseTest()
        : Dhcpv4SrvTest(), iface_mgr_test_config_(true) {
    }

    /// @brief Performs 4-way exchange to obtain new lease.
    ///
    /// @param client Client to be used to obtain a lease.
    void acquireLease(Dhcp4Client& client);

    /// @brief Tests if the acquired lease is or is not released.
    ///
    /// @param hw_address_1 HW Address to be used to acquire the lease.
    /// @param client_id_1 Client id to be used to acquire the lease.
    /// @param hw_address_2 HW Address to be used to release the lease.
    /// @param client_id_2 Client id to be used to release the lease.
    /// @param expected_result SHOULD_PASS_EXPIRED if the lease is expected to
    /// be successfully released and expired, SHOULD_PASS_DELETED if the lease
    /// is expected to be successfully released and deleted, or SHOULD_FAIL if
    /// the lease is expected to not be released.
    /// @param lease_affinity A flag which indicates if lease affinity should
    /// be enabled or disabled.
    void acquireAndRelease(const std::string& hw_address_1,
                           const std::string& client_id_1,
                           const std::string& hw_address_2,
                           const std::string& client_id_2,
                           ExpectedResult expected_result,
                           const LeaseAffinity lease_affinity);

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

void
ReleaseTest::acquireLease(Dhcp4Client& client) {
    // Perform 4-way exchange with the server but to not request any
    // specific address in the DHCPDISCOVER message.
    ASSERT_NO_THROW(client.doDORA());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease with the requested address.
    ASSERT_NE(client.config_.lease_.addr_.toText(), "0.0.0.0");
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(client.config_.lease_.addr_);
    ASSERT_TRUE(lease);
}

void
ReleaseTest::acquireAndRelease(const std::string& hw_address_1,
                               const std::string& client_id_1,
                               const std::string& hw_address_2,
                               const std::string& client_id_2,
                               ExpectedResult expected_result,
                               const LeaseAffinity lease_affinity) {
    CfgMgr::instance().clear();
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer(), true, true, true, false, lease_affinity);
    // Explicitly set the client id.
    client.includeClientId(client_id_1);
    // Explicitly set the HW address.
    client.setHWAddress(hw_address_1);
    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    std::stringstream name;

    // Let's get the subnet-id and generate statistics name out of it
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(1, subnets->size());
    name << "subnet[" << (*subnets->begin())->getID() << "].assigned-addresses";

    ObservationPtr assigned_cnt = StatsMgr::instance().getObservation(name.str());
    ASSERT_TRUE(assigned_cnt);
    uint64_t before = assigned_cnt->getInteger().first;

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Explicitly set the client id for DHCPRELEASE.
    client.includeClientId(client_id_2);
    // Explicitly set the HW address for DHCPRELEASE.
    client.setHWAddress(hw_address_2);

    // Send the release and make sure that the lease is removed from the
    // server.
    ASSERT_NO_THROW(client.doRelease());
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);

    assigned_cnt = StatsMgr::instance().getObservation(name.str());
    ASSERT_TRUE(assigned_cnt);
    uint64_t after = assigned_cnt->getInteger().first;

    // We check if the release process was successful by checking if the
    // lease is in the database.
    if (expected_result == SHOULD_PASS_EXPIRED) {
        ASSERT_TRUE(lease);

        // The update succeeded, so the assigned-address should be expired
        EXPECT_EQ(lease->valid_lft_, 0);
        EXPECT_EQ(Lease4::STATE_RELEASED, lease->state_);

        // The release succeeded, so the assigned-addresses statistic should
        // be decreased by one
        EXPECT_EQ(before, after + 1);

    } else if (expected_result == SHOULD_PASS_DELETED) {
        EXPECT_FALSE(lease);

        // The removal succeeded, so the assigned-addresses statistic should
        // be decreased by one
        EXPECT_EQ(before, after + 1);
    } else {
        EXPECT_TRUE(lease);
        EXPECT_EQ(Lease4::STATE_DEFAULT, lease->state_);

        // The removal failed, so the assigned-address should be the same
        // as before
        EXPECT_EQ(before, after);
    }
}

// This test checks that the client can acquire and release the lease.
TEST_F(ReleaseTest, releaseNoIdentifierChange) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_PASS_DELETED, LEASE_AFFINITY_DISABLED);
}

// This test checks that the client can acquire and release the lease.
TEST_F(ReleaseTest, releaseNoDeleteNoIdentifierChange) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_PASS_EXPIRED, LEASE_AFFINITY_ENABLED);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using HW address only
// - Client sends the DHCPRELEASE with valid HW address and without
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseHWAddressOnly) {
    acquireAndRelease("01:02:03:04:05:06", "",
                      "01:02:03:04:05:06", "",
                      SHOULD_PASS_DELETED, LEASE_AFFINITY_DISABLED);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using HW address only
// - Client sends the DHCPRELEASE with valid HW address and without
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseNoDeleteHWAddressOnly) {
    acquireAndRelease("01:02:03:04:05:06", "",
                      "01:02:03:04:05:06", "",
                      SHOULD_PASS_EXPIRED, LEASE_AFFINITY_ENABLED);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using the client identifier and HW address
// - Client sends the DHCPRELEASE with valid HW address but with no
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseNoClientId) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "",
                      SHOULD_PASS_DELETED, LEASE_AFFINITY_DISABLED);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using the client identifier and HW address
// - Client sends the DHCPRELEASE with valid HW address but with no
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseNoDeleteNoClientId) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "",
                      SHOULD_PASS_EXPIRED, LEASE_AFFINITY_ENABLED);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using HW address
// - Client sends the DHCPRELEASE with valid HW address and some
//   client identifier.
// - The server identifies the lease using HW address and releases
//   this lease.
TEST_F(ReleaseTest, releaseNoClientId2) {
    acquireAndRelease("01:02:03:04:05:06", "",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_PASS_DELETED, LEASE_AFFINITY_DISABLED);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using HW address
// - Client sends the DHCPRELEASE with valid HW address and some
//   client identifier.
// - The server identifies the lease using HW address and releases
//   this lease.
TEST_F(ReleaseTest, releaseNoDeleteNoClientId2) {
    acquireAndRelease("01:02:03:04:05:06", "",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_PASS_EXPIRED, LEASE_AFFINITY_ENABLED);
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease using the client identifier and HW address
// - Client sends the DHCPRELEASE with the valid HW address but with invalid
//   client identifier.
// - The server should not remove the lease.
TEST_F(ReleaseTest, releaseNonMatchingClientId) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:15:16",
                      SHOULD_FAIL, LEASE_AFFINITY_DISABLED);
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease using client identifier and HW address
// - Client sends the DHCPRELEASE with the same client identifier but
//   different HW address.
// - The server uses client identifier to find the client's lease and
//   releases it.
TEST_F(ReleaseTest, releaseNonMatchingHWAddress) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "06:06:06:06:06:06", "12:14",
                      SHOULD_PASS_DELETED, LEASE_AFFINITY_DISABLED);
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease using client identifier and HW address
// - Client sends the DHCPRELEASE with the same client identifier but
//   different HW address.
// - The server uses client identifier to find the client's lease and
//   releases it.
TEST_F(ReleaseTest, releaseNoDeleteNonMatchingHWAddress) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "06:06:06:06:06:06", "12:14",
                      SHOULD_PASS_EXPIRED, LEASE_AFFINITY_ENABLED);
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease.
// - Client sends DHCPRELEASE with the ciaddr set to a different
//   address than it has acquired from the server.
// - Server determines that the client is trying to release a
//   wrong address and will refuse to release.
TEST_F(ReleaseTest, releaseNonMatchingIPAddress) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer());
    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Modify the client's address to force it to release a different address
    // than it has obtained from the server.
    client.config_.lease_.addr_ = IOAddress(leased_address.toUint32() + 1);

    // Send DHCPRELEASE and make sure it was unsuccessful, i.e. the lease
    // remains in the database.
    ASSERT_NO_THROW(client.doRelease());
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease.
// - Client sends DHCPRELEASE with the ciaddr set to a different
//   address than it has acquired from the server.
// - Server determines that the client is trying to release a
//   wrong address and will refuse to release.
TEST_F(ReleaseTest, releaseNoDeleteNonMatchingIPAddress) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer(), true, true, true, false, LEASE_AFFINITY_ENABLED);
    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Modify the client's address to force it to release a different address
    // than it has obtained from the server.
    client.config_.lease_.addr_ = IOAddress(leased_address.toUint32() + 1);

    // Send DHCPRELEASE and make sure it was unsuccessful, i.e. the lease
    // remains in the database.
    ASSERT_NO_THROW(client.doRelease());
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);
}

// This test verifies that an incoming RELEASE for an address within
// a subnet that has been removed can still be released.
TEST_F(ReleaseTest, releaseNoSubnet) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer());
    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Release is as it was relayed
    client.useRelay(true);

    // Send the release
    ASSERT_NO_THROW(client.doRelease());

    // Check that the lease was removed
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    EXPECT_FALSE(lease);
}

// This test verifies that an incoming RELEASE for an address within
// a subnet that has been removed can still be released.
TEST_F(ReleaseTest, releaseNoDeleteNoSubnet) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer(), true, true, true, false, LEASE_AFFINITY_ENABLED);
    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Release is as it was relayed
    client.useRelay(true);

    // Send the release
    ASSERT_NO_THROW(client.doRelease());

    // Check that the lease was not removed
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);

    // Check That the lease has been expired
    EXPECT_EQ(lease->valid_lft_, 0);
}

// This test verifies that an incoming RELEASE for an address within
// a subnet can be reclaimed and does not cause counters to decrease below 0.
TEST_F(ReleaseTest, releaseAndReclaim) {
    Dhcp4Client client(srv_, Dhcp4Client::SELECTING);
    // Configure DHCP server.
    const char* RELEASE_CONFIG = {
    // Configuration 0
        "{ \"interfaces-config\": {"
            "      \"interfaces\": [ \"*\" ]"
            "},"
            "\"valid-lifetime\": 1,"
            "\"subnet4\": [ { "
            "    \"subnet\": \"10.0.0.0/24\", "
            "    \"id\": 1,"
            "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
            "    \"option-data\": [ {"
            "        \"name\": \"routers\","
            "        \"data\": \"10.0.0.200,10.0.0.201\""
            "    } ]"
            " } ],"
            " \"expired-leases-processing\": {"
            "    \"flush-reclaimed-timer-wait-time\": 3,"
            "    \"hold-reclaimed-time\": 1,"
            "    \"max-reclaim-leases\": 100,"
            "    \"max-reclaim-time\": 250,"
            "    \"reclaim-timer-wait-time\": 1,"
            "    \"unwarned-reclaim-cycles\": 5"
            "},"
            "\"multi-threading\": { \"enable-multi-threading\": false }"
        "}"
    };

    setenv("KEA_LFC_EXECUTABLE", KEA_LFC_EXECUTABLE, 1);
    ConstElementPtr json;
    try {
        json = parseJSON(RELEASE_CONFIG);
    } catch (const std::exception& ex) {
        // Fatal failure on parsing error
        FAIL() << "parsing failure:"
               << "config:" << RELEASE_CONFIG << std::endl
               << "error: " << ex.what();
    }

    disableIfacesReDetect(json);

    client.getServer()->processConfig(json);

    CfgMgr::instance().commit();

    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    std::stringstream name;

    // Let's get the subnet-id and generate statistics name out of it
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(1, subnets->size());
    name << "subnet[" << (*subnets->begin())->getID() << "].assigned-addresses";

    ObservationPtr assigned_cnt = StatsMgr::instance().getObservation(name.str());
    ASSERT_TRUE(assigned_cnt);
    uint64_t before = assigned_cnt->getInteger().first;

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Release is as it was relayed
    client.useRelay(true);

    // Send the release
    ASSERT_NO_THROW(client.doRelease());

    // Check that the lease was not removed
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);

    // Check That the lease has been expired
    EXPECT_EQ(lease->valid_lft_, 0);

    assigned_cnt = StatsMgr::instance().getObservation(name.str());
    ASSERT_TRUE(assigned_cnt);
    uint64_t after = assigned_cnt->getInteger().first;
    ASSERT_EQ(after, before - 1);
    sleep(1);
    client.getServer()->getIOService()->poll();
    assigned_cnt = StatsMgr::instance().getObservation(name.str());
    ASSERT_TRUE(assigned_cnt);
    uint64_t count = assigned_cnt->getInteger().first;
    ASSERT_EQ(count, after);
}

} // end of anonymous namespace
