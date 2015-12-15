// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
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
        SHOULD_PASS,
        SHOULD_FAIL
    };

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    ReleaseTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();
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
    /// @param expected_result SHOULD_PASS if the lease is expected to
    /// be successfully released, or SHOULD_FAIL if the lease is expected
    /// to not be released.
    void acquireAndRelease(const std::string& hw_address_1,
                           const std::string& client_id_1,
                           const std::string& hw_address_2,
                           const std::string& client_id_2,
                           ExpectedResult expected_result);

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
                               ExpectedResult expected_result) {
    CfgMgr::instance().clear();
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer());
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
    name << "subnet[" << subnets->at(0)->getID() << "].assigned-addresses";

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
    // lease is in the database. It is expected that it is not present,
    // i.e. has been deleted with the release.
    if (expected_result == SHOULD_PASS) {
        EXPECT_FALSE(lease);

        // The removal succeded, so the assigned-addresses statistic should
        // be decreased by one
        EXPECT_EQ(before, after + 1);
    } else {
        EXPECT_TRUE(lease);

        // The removal failed, so the assigned-address should be the same
        // as before
        EXPECT_EQ(before, after);
    }
}

// This test checks that the client can acquire and release the lease.
TEST_F(ReleaseTest, releaseNoIdentifierChange) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:14",
                      SHOULD_PASS);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using HW address only
// - Client sends the DHCPRELEASE with valid HW address and without
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseHWAddressOnly) {
    acquireAndRelease("01:02:03:04:05:06", "",
                      "01:02:03:04:05:06", "",
                      SHOULD_PASS);
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using the client identifier and HW address
// - Client sends the DHCPRELEASE with valid HW address but with no
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseNoClientId) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "",
                      SHOULD_PASS);
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
                      SHOULD_PASS);
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease using the client identifier and HW address
// - Client sends the DHCPRELEASE with the valid HW address but with invalid
//   client identifier.
// - The server should not remove the lease.
TEST_F(ReleaseTest, releaseNonMatchingClientId) {
    acquireAndRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:15:16",
                      SHOULD_FAIL);
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
                      SHOULD_PASS);
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease.
// - Client sends DHCPRELEASE with the ciaddr set to a different
//   address than it has acquired from the server.
// - Server determines that the client is trying to release a
//   wrong address and will refuse to release.
TEST_F(ReleaseTest, releaseNonMatchingIPAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer());
    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Modify the client's address to force it to release a different address
    // than it has obtained from the server.
    client.config_.lease_.addr_ = IOAddress(static_cast<uint32_t>(leased_address) + 1);

    // Send DHCPRELEASE and make sure it was unsuccessful, i.e. the lease
    // remains in the database.
    ASSERT_NO_THROW(client.doRelease());
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);
}

// This test verifies that an incoming RELEASE for an address within
// a subnet that has been removed can still be released.
TEST_F(ReleaseTest, releaseNoSubnet) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
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

} // end of anonymous namespace
