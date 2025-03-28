// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>
#include <dhcpsrv/lease.h>

#ifdef HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#include <hooks/dhcp/mysql/mysql_lease_mgr.h>
#endif

#ifdef HAVE_PGSQL
#include <pgsql/testutils/pgsql_schema.h>
#include <hooks/dhcp/pgsql/pgsql_lease_mgr.h>
#endif

#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
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
        "    \"id\": 1, "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",
// Configuration 1 - only use when mysql is enabled
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"lease-database\": {"
            "\"type\": \"mysql\","
            "\"name\": \"keatest\","
            "\"user\": \"keatest\","
            "\"password\": \"keatest\""
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"id\": 1, "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",
// Configuration 2 - only use when pgsql is enabled
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"lease-database\": {"
            "\"type\": \"postgresql\","
            "\"name\": \"keatest\","
            "\"user\": \"keatest\","
            "\"password\": \"keatest\""
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"id\": 1, "
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

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    DeclineTest()
        : Dhcpv6MessageTest(), na_iaid_(1234) {
    }

    /// @brief IAID used for IA_NA.
    uint32_t na_iaid_;
};

}

namespace isc {
namespace dhcp {
namespace test {

void
Dhcpv6SrvTest::acquireAndDecline(Dhcp6Client& client,
                                 const std::string& duid1,
                                 const uint32_t iaid1,
                                 const std::string& duid2,
                                 const uint32_t iaid2,
                                 AddressInclusion addr_type,
                                 ExpectedResult expected_result,
                                 uint8_t config_index) {
    // Set this global statistic explicitly to zero.
    StatsMgr::instance().setValue("declined-addresses", static_cast<int64_t>(0));

    client.setDUID(duid1);
    client.requestAddress(iaid1);

    // Configure the server with a configuration.
    ASSERT_NO_THROW(configure(DECLINE_CONFIGS[config_index], *client.getServer()));

    // Let's get the subnet-id and generate statistics name out of it.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Let's generate the subnet specific statistic
    std::string name = StatsMgr::generateName("subnet",
                                              (*subnets->begin())->getID(),
                                              "declined-addresses");

    // Set this statistic explicitly to zero.
    StatsMgr::instance().setValue(name, static_cast<int64_t>(0));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(iaid1));

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

    /// Determines if the client will include address in the messages it sends.
    bool include_address_ = true;

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
        include_address_ = false;
        break;
    case NO_IA:
        // Tell the client to not include IA_NA at all
        client.config_.clear();
        client.clearRequestedIAs();
    }

    // Use the second duid
    client.setDUID(duid2);

    // Use the second IAID (but not in NO_IA which has cleared leases)
    if (addr_type != NO_IA) {
        ASSERT_NE(0, client.config_.leases_.size());
        client.config_.leases_[0].iaid_ = iaid2;
    }

    // Ok, let's decline the lease.
    ASSERT_NO_THROW(client.doDecline(include_address_));

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
        ASSERT_EQ(Lease::STATE_DECLINED, lease->state_);

        ASSERT_FALSE(lease->hwaddr_);
        ASSERT_TRUE(lease->duid_);
        ASSERT_EQ(*lease->duid_, DUID::EMPTY());
        ASSERT_EQ(lease->preferred_lft_, 0);
        ASSERT_TRUE(lease->hostname_.empty());
        ASSERT_FALSE(lease->fqdn_fwd_);
        ASSERT_FALSE(lease->fqdn_rev_);

        // The decline succeeded, so the declined-addresses statistic should
        // be increased by one
        ASSERT_EQ(after, before + 1);
        ASSERT_EQ(after_global, before_global + 1);
    } else {
        // the decline was supposed, to be rejected.
        ASSERT_EQ(Lease::STATE_DEFAULT, lease->state_);

        ASSERT_TRUE(lease->hwaddr_);
        ASSERT_TRUE(lease->duid_);
        ASSERT_NE(*lease->duid_, DUID::EMPTY());
        ASSERT_NE(lease->preferred_lft_, 0);
        ASSERT_FALSE(lease->fqdn_fwd_);
        ASSERT_FALSE(lease->fqdn_rev_);

        // The decline failed, so the declined-addresses should be the same
        // as before
        ASSERT_EQ(before, after);
        ASSERT_EQ(before_global, after_global);
    }
}

// This test checks that the client can acquire and decline the lease.
TEST_F(DeclineTest, basicMemfile) {
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1234, VALID_ADDR, SHOULD_PASS);
}

#ifdef HAVE_MYSQL
// This test checks that the client can acquire and decline the lease.
TEST_F(DeclineTest, basicMySQL) {
    MySqlLeaseMgrInit init;
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1234, VALID_ADDR, SHOULD_PASS, 1);
}
#endif

#ifdef HAVE_PGSQL
TEST_F(DeclineTest, basicPgSQL) {
    PgSqlLeaseMgrInit init;
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1234, VALID_ADDR, SHOULD_PASS, 2);
}
#endif

}
}
}

namespace {

// This test verifies the decline is rejected in the following case:
// - Client acquires new lease using duid, iaid
// - Client sends the DECLINE with duid, iaid, but uses wrong address.
// - The server rejects Decline due to address mismatch
TEST_F(DeclineTest, addressMismatch) {
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1234, BOGUS_ADDR, SHOULD_FAIL);
}

// This test verifies the decline is rejected in the following case:
// - Client acquires new lease using duid, iaid1
// - Client sends the DECLINE with duid, iaid2
// - The server rejects Decline due to IAID mismatch
TEST_F(DeclineTest, iaidMismatch) {
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234, "01:02:03:04:05:06",
                      1235, VALID_ADDR, SHOULD_FAIL);
}

// This test verifies the decline correctness in the following case:
// - Client acquires new lease using duid1, iaid
// - Client sends the DECLINE using duid2, iaid
// - The server rejects the Decline due to DUID mismatch
TEST_F(DeclineTest, duidMismatch) {
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:07", 1234,
                      VALID_ADDR, SHOULD_FAIL);
}

// This test verifies the decline correctness in the following case:
// - Client acquires new lease using duid1, iaid
// - Client sends the DECLINE using valid duid/iaid, but does not
//   include the address in it
// - The server rejects the Decline due to missing address
TEST_F(DeclineTest, noAddrsSent) {
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      NO_ADDR, SHOULD_FAIL);
}

// This test verifies the decline correctness in the following case:
// - Client acquires new lease using duid1, iaid
// - Client sends the DECLINE using valid duid, but does not
//   include IA_NA at all
// - The server rejects the Decline due to missing IA_NA
TEST_F(DeclineTest, noIAs) {
    Dhcp6Client client(srv_);
    acquireAndDecline(client, "01:02:03:04:05:06", 1234,
                      "01:02:03:04:05:06", 1234,
                      NO_IA, SHOULD_FAIL);
}

// Test that the released lease cannot be declined.
TEST_F(DeclineTest, declineAfterRelease) {
    Dhcp6Client client(srv_);
    uint32_t iaid = 1;
    client.requestAddress(iaid);

    // Configure DHCP server.
    configure(DECLINE_CONFIGS[0], *client.getServer());
    // Perform 4-way exchange to obtain a new lease.
    client.doSARR();
    auto leases = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(iaid));

    // Release the acquired lease.
    auto lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, leases[0].addr_);
    lease->state_ = Lease::STATE_RELEASED;
    LeaseMgrFactory::instance().updateLease6(lease);

    // Try to decline the released address.
    ASSERT_NO_THROW(client.doDecline());

    // The address should not be declined. It should still be in the
    // released state.
    lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, lease->addr_);
    ASSERT_TRUE(lease);
    EXPECT_EQ(Lease::STATE_RELEASED, lease->state_);
}

// Test that the released lease cannot be declined.
TEST_F(DeclineTest, declineAfterExpire) {
    Dhcp6Client client(srv_);
    uint32_t iaid = 1;
    client.requestAddress(iaid);

    // Configure DHCP server.
    configure(DECLINE_CONFIGS[0], *client.getServer());
    // Perform 4-way exchange to obtain a new lease.
    client.doSARR();
    auto leases = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(iaid));

    // Release the acquired lease.
    auto lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, leases[0].addr_);
    lease->cltt_ -= 7200;
    LeaseMgrFactory::instance().updateLease6(lease);

    // Try to decline the expired lease.
    ASSERT_NO_THROW(client.doDecline());

    // The address should not be declined. It should still be in the
    // default state.
    lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, lease->addr_);
    ASSERT_TRUE(lease);
    EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);
}

// Test that expired-reclaimed lease cannot be declined.
TEST_F(DeclineTest, declineAfterReclamation) {
    Dhcp6Client client(srv_);
    uint32_t iaid = 1;
    client.requestAddress(iaid);

    // Configure DHCP server.
    configure(DECLINE_CONFIGS[0], *client.getServer());
    // Perform 4-way exchange to obtain a new lease.
    client.doSARR();
    auto leases = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(iaid));

    // Release the acquired lease.
    auto lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, leases[0].addr_);
    lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
    LeaseMgrFactory::instance().updateLease6(lease);

    // Try to decline the reclaimed lease.
    ASSERT_NO_THROW(client.doDecline());

    // The address should not be declined. It should still be in the
    // reclaimed state.
    lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, lease->addr_);
    ASSERT_TRUE(lease);
    EXPECT_EQ(Lease::STATE_EXPIRED_RECLAIMED, lease->state_);
}


} // end of anonymous namespace
