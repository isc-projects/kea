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
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;
using namespace isc::stats;

namespace {

/// @brief Set of JSON configurations used throughout the Renew tests.
///
/// - Configuration 0:
///   - only addresses (no prefixes)
///   - 1 subnet with 2001:db8:1::/64 pool
const char* DECLINE_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }"
};

/// @brief Test fixture class for testing Renew.
class DeclineTest : public Dhcpv6MessageTest {
public:

    enum ExpectedResult {
        SHOULD_PASS, // pass = accept decline, move lease to declined state.
        SHOULD_FAIL  // fail = reject the decline
    };

    /// @brief Performs 4-way exchange to obtain new lease.
    ///
    /// This is used as a preparatory step for Decline operation.
    ///
    /// @param client Client to be used to obtain a lease.
    void acquireLease(Dhcp6Client& client);

    /// @brief Tests if the acquired lease is or is not declined.
    ///
    /// @param duid1 DUID used during lease acquisition
    /// @param iaid1 IAID used during lease acquisition
    /// @param duid2 DUID used during Decline exchange
    /// @param iaid2 IAID used during Decline exchange
    /// @param declient_correct_address specify if the valid address should
    ///        be used (true = use the address client actually received,
    ///        false = use a different address)
    /// @param expected_result SHOULD_PASS if the lease is expected to
    /// be successfully declined, or SHOULD_FAIL if the lease is expected
    /// to not be declined.
    void acquireAndDecline(const std::string& duid1,
                           const uint32_t iaid1,
                           const std::string& duid2,
                           const uint32_t iaid2,
                           bool decline_correct_address,
                           ExpectedResult expected_result);
    
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    DeclineTest()
        : Dhcpv6MessageTest(), na_iaid_(1234) {
    }

    /// @brief IAID used for IA_NA.
    uint32_t na_iaid_;

};

void
DeclineTest::acquireAndDecline(const std::string& duid1,
                               const uint32_t iaid1,
                               const std::string& duid2,
                               const uint32_t iaid2,
                               bool decline_correct_address,
                               ExpectedResult expected_result) {
    Dhcp6Client client;
    client.setDUID(duid1);
    client.useNA(iaid1);

    // Configure the server with a configuration.
    ASSERT_NO_THROW(configure(DECLINE_CONFIGS[0], *client.getServer()));

    // Let's get the subnet-id and generate statistics name out of it.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_EQ(1, subnets->size());
    std::stringstream name;
    name << "subnet[" << subnets->at(0)->getID() << "].declined-addresses";

    // Set this statistic explicitly to zero.
    isc::stats::StatsMgr::instance().setValue(name.str(), static_cast<int64_t>(0));
    
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // Remember the acquired address.
    IOAddress acquired_address = leases_client_na[0].addr_;

    // Check the delined-addresses statistic before the Decline operation.
    ObservationPtr declined_cnt = StatsMgr::instance().getObservation(name.str());
    ASSERT_TRUE(declined_cnt);
    uint64_t before = declined_cnt->getInteger().first;
    
    // Let's tamper with the address if necessary.
    if (!decline_correct_address) {

        // Simple increase by one.
        leases_client_na[0].addr_ = IOAddress::increase(leases_client_na[0].addr_);
    }
    
    // Ok, let's decline the lease.
    client.setDUID(duid2);
    client.useNA(iaid2);
    ASSERT_NO_THROW(client.doDecline());

    // Let's check if there's a lease
    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, acquired_address);
    ASSERT_TRUE(lease);
    
    declined_cnt = StatsMgr::instance().getObservation(name.str());
    ASSERT_TRUE(declined_cnt);
    uint64_t after = declined_cnt->getInteger().first;

    // We check if the deline process was successful by checking if the
    // lease is in the database and what is its state.
    if (expected_result == SHOULD_PASS) {
        EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);

        // The decline succeded, so the declined-addresses statistic should
        // be increased by one
        EXPECT_EQ(after, before + 1);
    } else {
        // the decline was supposed, to be rejected.
        EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);

        // The decline failed, so the declined-addresses should be the same
        // as before
        EXPECT_EQ(before, after);
    }
}

// This test checks that the client can acquire and decline the lease.
TEST_F(DeclineTest, declineBasic) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      true, SHOULD_PASS);
}

// This test verifies the decline is rejected in the following case:
// - Client acquires new lease using duid, iaid
// - Client sends the DHCPDECLINE with duid, iaid, but uses wrong address.
// - The server rejects Decline due to address mismatch
TEST_F(DeclineTest, declineAddressMismatch) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      false, SHOULD_FAIL);
}

// This test verifies the decline is rejected in the following case:
// - Client acquires new lease using duid, iaid1
// - Client sends the DHCPDECLINE with duid, iaid2
// - The server rejects Decline due to IAID mismatch
TEST_F(DeclineTest, declineIAIDMismatch) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1235,
                      true, SHOULD_FAIL);
}

// This test verifies the decline correctness in the following case:
// - Client acquires new lease using duid1, iaid
// - Client sends the DHCPDECLINE using duid2, iaid
// - The server rejects the Decline due to DUID mismatch
TEST_F(DeclineTest, declineDuidMismatch) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:07", 1234,
                      true, SHOULD_PASS);
}

} // end of anonymous namespace
