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

    /// @brief Specifies expected outcome
    enum ExpectedResult {
        SHOULD_PASS, // pass = accept decline, move lease to declined state.
        SHOULD_FAIL  // fail = reject the decline
    };

    /// @brief Specifies what address should the client include in its Decline
    enum AddressInclusion {
        VALID_ADDR, // Client will include its own, valid address
        BOGUS_ADDR, // Client will include an address it doesn't own
        NO_ADDR,    // Client will send empty IA_NA (without address)
        NO_IA       // Client will not send IA_NA at all
    };

    /// @brief Tests if the acquired lease is or is not declined.
    ///
    /// @param duid1 DUID used during lease acquisition
    /// @param iaid1 IAID used during lease acquisition
    /// @param duid2 DUID used during Decline exchange
    /// @param iaid2 IAID used during Decline exchange
    /// @param addr_type specify what sort of address the client should
    ///        include (its own, a bogus one or no address at all)
    /// @param expected_result SHOULD_PASS if the lease is expected to
    /// be successfully declined, or SHOULD_FAIL if the lease is expected
    /// to not be declined.
    void acquireAndDecline(const std::string& duid1,
                           const uint32_t iaid1,
                           const std::string& duid2,
                           const uint32_t iaid2,
                           AddressInclusion addr_type,
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
                               AddressInclusion addr_type,
                               ExpectedResult expected_result) {
    // Set this global statistic explicitly to zero.
    StatsMgr::instance().setValue("declined-addresses", static_cast<int64_t>(0));

    Dhcp6Client client;
    client.setDUID(duid1);
    client.useNA(iaid1);

    // Configure the server with a configuration.
    ASSERT_NO_THROW(configure(DECLINE_CONFIGS[0], *client.getServer()));

    // Let's get the subnet-id and generate statistics name out of it.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Let's generate the subnet specific statistic
    std::string name = StatsMgr::generateName("subnet", subnets->at(0)->getID(),
                                              "declined-addresses");

    // Set this statistic explicitly to zero.
    StatsMgr::instance().setValue(name, static_cast<int64_t>(0));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // Remember the acquired address.
    IOAddress acquired_address = leases_client_na[0].addr_;

    // Check the declined-addresses (subnet) before the Decline operation.
    ObservationPtr declined_cnt = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(declined_cnt);
    uint64_t before = declined_cnt->getInteger().first;

        // Check the global declined-addresses statistic before the Decline.
    ObservationPtr declined_global = StatsMgr::instance()
        .getObservation("declined-addresses");
    ASSERT_TRUE(declined_global);
    uint64_t before_global = declined_cnt->getInteger().first;

    // Let's tamper with the address if necessary.
    switch (addr_type) {
    case VALID_ADDR:
        // Nothing to do, client will do its job correctly by default
        break;
    case BOGUS_ADDR:
        // Simple increase by one.
        client.config_.leases_[0].addr_ =
            IOAddress::increase(client.config_.leases_[0].addr_);
        break;
    case NO_ADDR:
        // Tell the client to not include an address in its IA_NA
        client.includeAddress(false);
        break;
    case NO_IA:
        // Tell the client to not include IA_NA at all
        client.useNA(false);
    }

    // Use the second duid
    client.setDUID(duid2);

    // Use the second IAID
    client.config_.leases_[0].iaid_ = iaid2;

    // Ok, let's decline the lease.
    ASSERT_NO_THROW(client.doDecline());

    // Let's check if there's a lease
    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                            acquired_address);
    ASSERT_TRUE(lease);

    declined_cnt = StatsMgr::instance().getObservation(name);
    ASSERT_TRUE(declined_cnt);
    uint64_t after = declined_cnt->getInteger().first;

    declined_global = StatsMgr::instance().getObservation("declined-addresses");
    ASSERT_TRUE(declined_global);
    uint64_t after_global = declined_global->getInteger().first;

    // We check if the decline process was successful by checking if the
    // lease is in the database and what is its state.
    if (expected_result == SHOULD_PASS) {
        EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);

        // The decline succeded, so the declined-addresses statistic should
        // be increased by one
        EXPECT_EQ(after, before + 1);
        EXPECT_EQ(after_global, before_global + 1);
    } else {
        // the decline was supposed, to be rejected.
        EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);

        // The decline failed, so the declined-addresses should be the same
        // as before
        EXPECT_EQ(before, after);
        EXPECT_EQ(before_global, after_global);
    }
}

// This test checks that the client can acquire and decline the lease.
TEST_F(DeclineTest, basic) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      VALID_ADDR, SHOULD_PASS);
}

// This test verifies the decline is rejected in the following case:
// - Client acquires new lease using duid, iaid
// - Client sends the DECLINE with duid, iaid, but uses wrong address.
// - The server rejects Decline due to address mismatch
TEST_F(DeclineTest, addressMismatch) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      BOGUS_ADDR, SHOULD_FAIL);
}

// This test verifies the decline is rejected in the following case:
// - Client acquires new lease using duid, iaid1
// - Client sends the DECLINE with duid, iaid2
// - The server rejects Decline due to IAID mismatch
TEST_F(DeclineTest, iaidMismatch) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1235,
                      VALID_ADDR, SHOULD_FAIL);
}

// This test verifies the decline correctness in the following case:
// - Client acquires new lease using duid1, iaid
// - Client sends the DECLINE using duid2, iaid
// - The server rejects the Decline due to DUID mismatch
TEST_F(DeclineTest, duidMismatch) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:07", 1234,
                      VALID_ADDR, SHOULD_FAIL);
}

// This test verifies the decline correctness in the following case:
// - Client acquires new lease using duid1, iaid
// - Client sends the DECLINE using valid duid/iaid, but does not
//   include the address in it
// - The server rejects the Decline due to missing address
TEST_F(DeclineTest, noAddrsSent) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      NO_ADDR, SHOULD_FAIL);
}

// This test verifies the decline correctness in the following case:
// - Client acquires new lease using duid1, iaid
// - Client sends the DECLINE using valid duid, but does not
//   include IA_NA at all
// - The server rejects the Decline due to missing IA_NA
TEST_F(DeclineTest, noIAs) {
    acquireAndDecline("01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      NO_IA, SHOULD_FAIL);
}

} // end of anonymous namespace
