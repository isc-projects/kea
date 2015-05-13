// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <boost/shared_ptr.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

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
        "        \"code\": 3,"
        "        \"data\": \"10.0.0.200,10.0.0.201\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
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

    /// @brief Test successful release for different identifiers.
    ///
    /// @param hw_address_1 HW Address to be used to acquire the lease.
    /// @param client_id_1 Client id to be used to acquire the lease.
    /// @param hw_address_2 HW Address to be used to release the lease.
    /// @param client_id_2 Client id to be used to release the lease.
    void successfulRelease(const std::string& hw_address_1,
                           const std::string& client_id_1,
                           const std::string& hw_address_2,
                           const std::string& client_id_2);

    /// @brief Test unsuccessful release for different identifiers.
    ///
    /// @param hw_address_1 HW Address to be used to acquire the lease.
    /// @param client_id_1 Client id to be used to acquire the lease.
    /// @param hw_address_2 HW Address to be used to release the lease.
    /// @param client_id_2 Client id to be used to release the lease.
    void unsuccessfulRelease(const std::string& hw_address_1,
                             const std::string& client_id_1,
                             const std::string& hw_address_2,
                             const std::string& client_id_2);

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
ReleaseTest::successfulRelease(const std::string& hw_address_1,
                               const std::string& client_id_1,
                               const std::string& hw_address_2,
                               const std::string& client_id_2) {
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
    ASSERT_FALSE(lease);
}

void
ReleaseTest::unsuccessfulRelease(const std::string& hw_address_1,
                                 const std::string& client_id_1,
                                 const std::string& hw_address_2,
                                 const std::string& client_id_2) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(RELEASE_CONFIGS[0], *client.getServer());
    // Explicitly set the client id.
    client.includeClientId(client_id_1);
    // Explicitly set the HW address.
    client.setHWAddress(hw_address_1);
    // Perform 4-way exchange to obtain a new lease.
    acquireLease(client);

    // Remember the acquired address.
    IOAddress leased_address = client.config_.lease_.addr_;

    // Explicitly set the client id for DHCPRELEASE.
    client.includeClientId(client_id_2);
    // Explicitly set the HW address for DHCPRELEASE.
    client.setHWAddress(hw_address_2);

    // Send DHCPRELEASE and make sure it was unsuccessful, i.e. the lease
    // remains in the database.
    ASSERT_NO_THROW(client.doRelease());
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);
}


// This test checks that the client can acquire and release the lease.
TEST_F(ReleaseTest, releaseNoIdentifierChange) {
    successfulRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "12:14");
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using HW address only
// - Client sends the DHCPRELEASE with valid HW address and without
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseHWAddressOnly) {
    successfulRelease("01:02:03:04:05:06", "",
                      "01:02:03:04:05:06", "");
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using the client identifier and HW address
// - Client sends the DHCPRELEASE with valid HW address but with no
//   client identifier.
// - The server successfully releases the lease.
TEST_F(ReleaseTest, releaseNoClientId) {
    successfulRelease("01:02:03:04:05:06", "12:14",
                      "01:02:03:04:05:06", "");
}

// This test verifies the release correctness in the following case:
// - Client acquires new lease using HW address
// - Client sends the DHCPRELEASE with valid HW address and some
//   client identifier.
// - The server identifies the lease using HW address and releases
//   this lease.
TEST_F(ReleaseTest, releaseNoClientId2) {
    successfulRelease("01:02:03:04:05:06", "",
                      "01:02:03:04:05:06", "12:14");
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease using the client identifier and HW address
// - Client sends the DHCPRELEASE with the valid HW address but with invalid
//   client identifier.
// - The server should not remove the lease.
TEST_F(ReleaseTest, releaseNonMatchingClientId) {
    unsuccessfulRelease("01:02:03:04:05:06", "12:14",
                        "01:02:03:04:05:06", "12:15:16");
}

// This test checks the server's behavior in the following case:
// - Client acquires new lease using client identifier and HW address
// - Client sends the DHCPRELEASE with the same client identifier but
//   different HW address.
// - The server uses client identifier to find the client's lease and
//   releases it.
TEST_F(ReleaseTest, releaseNonMatchingHWAddress) {
    successfulRelease("01:02:03:04:05:06", "12:14",
                      "06:06:06:06:06:06", "12:14");
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

} // end of anonymous namespace
