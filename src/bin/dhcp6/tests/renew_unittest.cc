// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option6_pdexclude.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>
#include <boost/pointer_cast.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used throughout the Renew tests.
///
/// - Configuration 0:
///   - only addresses (no prefixes)
///   - 1 subnet with 2001:db8:1::/64 pool
///
/// - Configuration 1:
///   - only prefixes (no addresses)
///   - prefix pool: 3000::/72
///
/// - Configuration 2:
///   - addresses and prefixes
///   - 1 subnet with one address pool and one prefix pool
///   - address pool: 2001:db8:1::/64
///   - prefix pool: 3000::/72
///
/// - Configuration 3:
///   - only addresses (no prefixes)
///   - 1 subnet with 2001:db8:1::/64 pool
///   - DOCSIS vendor config file sub-option
///
/// - Configuration 4:
///   - single subnet 3000::/32,
///   - two options specified in the subnet scope,
///   - one option specified at the global scope,
///   - two address pools: 3000::10-3000::20, 3000::40-3000::50,
///   - two prefix pools: 2001:db8:3::/64 and 2001:db8:4::/64,
///   - an option with unique value specified for each pool, so as it is
///     possible to test that pool specific options can be assigned.
///
/// - Configuration 5:
///   - addresses and prefixes
///   - 1 subnet with one address pool and one prefix pool
///   - address pool: 2001:db8:1::/64
///   - prefix pool: 3000::/72
///   - excluded prefix 3000::1000/120 in a prefix pool.
///
const char* RENEW_CONFIGS[] = {
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
        "\"valid-lifetime\": 4000 }",

// Configuration 1
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": ["
        "        { \"prefix\": \"3000::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 2
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"pd-pools\": ["
        "        { \"prefix\": \"3000::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 3
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"config-file\","
        "    \"space\": \"vendor-4491\","
        "    \"data\": \"normal_erouter_v6.cm\""
        "}],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

// Configuration 4
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"dns-servers\","
        "    \"data\": \"3000:1::234\""
        "},"
        "{"
        "    \"name\": \"sntp-servers\","
        "    \"data\": \"3000:2::1\""
        "} ],"
        "\"subnet6\": [ { "
        "    \"option-data\": [ {"
        "        \"name\": \"dns-servers\","
        "        \"data\": \"3000:1::567\""
        "    },"
        "    {"
        "        \"name\": \"sntp-servers\","
        "        \"data\": \"3000:2::1\""
        "    } ],"
        "    \"pools\": [ { "
        "        \"pool\": \"3000::10 - 3000::20\","
        "        \"option-data\": [ {"
        "            \"name\": \"sntp-servers\","
        "            \"data\": \"3000:2::2\""
        "        } ]"
        "    },"
        "    {"
        "        \"pool\": \"3000::40 - 3000::50\","
        "        \"option-data\": [ {"
        "            \"name\": \"nisp-servers\","
        "            \"data\": \"3000:2::3\""
        "        } ]"
        "    } ],"
        "    \"pd-pools\": [ { "
        "        \"prefix\": \"2001:db8:3::\","
        "        \"prefix-len\": 64,"
        "        \"delegated-len\": 64,"
        "        \"option-data\": [ {"
        "            \"name\": \"dns-servers\","
        "            \"data\": \"3000:1::678\""
        "        } ]"
        "    },"
        "    {"
        "        \"prefix\": \"2001:db8:4::\","
        "        \"prefix-len\": 64,"
        "        \"delegated-len\": 64,"
        "        \"option-data\": [ {"
        "            \"name\": \"nis-servers\","
        "            \"data\": \"3000:1::789\""
        "        } ]"
        "    } ],"
        "    \"subnet\": \"3000::/32\", "
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000"
    "}",

// Configuration 5
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"pd-pools\": ["
        "        { \"prefix\": \"3000::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80,"
        "          \"excluded-prefix\": \"3000::1000\","
        "          \"excluded-prefix-len\": 120"
        "        } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }"
};

/// @brief Test fixture class for testing Renew.
class RenewTest : public Dhcpv6MessageTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    RenewTest()
        : Dhcpv6MessageTest(), na_iaid_(1234), pd_iaid_(5678) {
    }

    /// @brief IAID used for IA_NA.
    uint32_t na_iaid_;

    /// @brief IAID used for IA_PD.
    uint32_t pd_iaid_;

};

// This test verifies that the client can request the prefix delegation
// while it is renewing an address lease.
TEST_F(RenewTest, requestPrefixInRenew) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.requestAddress(na_iaid_);
    client.requestPrefix(pd_iaid_);

    // Configure the server with NA pools only.
    ASSERT_NO_THROW(configure(RENEW_CONFIGS[0], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // The client should not acquire a PD lease.
    std::vector<Lease6> leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_TRUE(leases_client_pd.empty());
    ASSERT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(pd_iaid_));

    // Send Renew message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRenew());
    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_TRUE(leases_client_pd.empty());
    ASSERT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(pd_iaid_));

    std::vector<Lease6> leases_client_na_renewed =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // Reconfigure the server to use both NA and PD pools.
    configure(RENEW_CONFIGS[2], *client.getServer());

    // Send Renew message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that the client has acquired NA lease.
    leases_client_na_renewed = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // The lease should have been renewed. Allow some time skew.
#ifdef STRICT_TEST_TIMING
    EXPECT_EQ(1000,
              leases_client_na_renewed[0].cltt_ - leases_client_na[0].cltt_);
#else
    EXPECT_LE(995,
              leases_client_na_renewed[0].cltt_ - leases_client_na[0].cltt_);
    EXPECT_GE(1005,
              leases_client_na_renewed[0].cltt_ - leases_client_na[0].cltt_);
#endif

    // The client should now also acquire a PD lease.
    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));
}

// Test that it is possible to renew a prefix lease with a Prefix Exclude
// option being included during renew.
TEST_F(RenewTest, renewWithExcludedPrefix) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.requestAddress(na_iaid_);
    client.requestPrefix(pd_iaid_);

    // Request Prefix Exclude option.
    client.requestOption(D6O_PD_EXCLUDE);

    // Configure the server with NA pools only.
    ASSERT_NO_THROW(configure(RENEW_CONFIGS[2], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // The client should also acquire a PD lease.
    std::vector<Lease6> leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
    ASSERT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));

    // Send Renew message to the server, including IA_NA and IA_PD.
    ASSERT_NO_THROW(client.doRenew());

    std::vector<Lease6> leases_client_na_renewed =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    std::vector<Lease6> leases_client_pd_renewed =
        client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));

    // Make sure that Prefix Exclude option hasn't been included.
    OptionPtr option = client.getContext().response_->getOption(D6O_IA_PD);
    ASSERT_TRUE(option);
    option = option->getOption(D6O_IAPREFIX);
    ASSERT_TRUE(option);
    option = option->getOption(D6O_PD_EXCLUDE);
    ASSERT_FALSE(option);

    // Reconfigure the server to use the prefix pool with excluded prefix.
    configure(RENEW_CONFIGS[5], *client.getServer());

    // Send Renew message to the server, including IA_NA and IA_PD.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that the client has acquired NA lease.
    leases_client_na_renewed = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // Make sure that the client has acquired PD lease.
    leases_client_pd_renewed = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));

    // The leases should have been renewed.
    EXPECT_GE(leases_client_na_renewed[0].cltt_ - leases_client_na[0].cltt_, 1000);
    EXPECT_GE(leases_client_pd_renewed[0].cltt_ - leases_client_pd[0].cltt_, 1000);

    // This time, the Prefix Exclude option should be included.
    option = client.getContext().response_->getOption(D6O_IA_PD);
    ASSERT_TRUE(option);
    option = option->getOption(D6O_IAPREFIX);
    ASSERT_TRUE(option);
    option = option->getOption(D6O_PD_EXCLUDE);
    ASSERT_TRUE(option);
    Option6PDExcludePtr pd_exclude = boost::dynamic_pointer_cast<Option6PDExclude>(option);
    ASSERT_TRUE(pd_exclude);
    EXPECT_EQ("3000::1000", pd_exclude->getExcludedPrefix(IOAddress("3000::"),
                                                          80).toText());
    EXPECT_EQ(120, static_cast<unsigned>(pd_exclude->getExcludedPrefixLength()));
}

// This test verifies that the client can request a prefix delegation
// with a hint, while it is renewing an address lease.
TEST_F(RenewTest, requestPrefixInRenewUseHint) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.requestAddress(na_iaid_);
    client.requestPrefix(pd_iaid_);

    // Configure the server with NA pools only.
    ASSERT_NO_THROW(configure(RENEW_CONFIGS[0], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());

    // The client should not acquire a PD lease.
    std::vector<Lease6> leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_TRUE(leases_client_pd.empty());
    ASSERT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(pd_iaid_));

    // Send Renew message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRenew());
    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_TRUE(leases_client_pd.empty());
    ASSERT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(pd_iaid_));

    std::vector<Lease6> leases_client_na_renewed =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // Specify the hint used for IA_PD.
    client.requestPrefix(pd_iaid_, 64, IOAddress::IPV6_ZERO_ADDRESS());

    // Send Renew message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that the client has acquired NA lease.
    leases_client_na_renewed = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_TRUE(leases_client_pd.empty());
    ASSERT_EQ(STATUS_NoPrefixAvail, client.getStatusCode(pd_iaid_));

    // Reconfigure the server to use both NA and PD pools.
    configure(RENEW_CONFIGS[2], *client.getServer());

    // Send Renew message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that the client has acquired NA lease.
    leases_client_na_renewed = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // The lease should have been renewed.
    EXPECT_GE(leases_client_na_renewed[0].cltt_ - leases_client_na[0].cltt_, 1000);

    // The client should now also acquire a PD lease.
    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));
}

// This test verifies that the client can request the prefix delegation
// while it is renewing an address lease.
TEST_F(RenewTest, requestAddressInRenew) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.requestAddress(na_iaid_);
    client.requestPrefix(pd_iaid_);

    // Configure the server with PD pools only.
    ASSERT_NO_THROW(configure(RENEW_CONFIGS[1], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired PD lease.
    std::vector<Lease6> leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));

    // The client should not acquire a NA lease.
    std::vector<Lease6> leases_client_na =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(0, leases_client_na.size());
    ASSERT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(na_iaid_));

    // Send Renew message to the server, including IA_PD and requesting IA_NA.
    // The server should return NoAddrsAvail status code in this case.
    ASSERT_NO_THROW(client.doRenew());
    leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(0, leases_client_na.size());
    ASSERT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(na_iaid_));

    std::vector<Lease6> leases_client_pd_renewed =
        client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));
    EXPECT_GE(leases_client_pd_renewed[0].cltt_ - leases_client_pd[0].cltt_, 1000);

    // Reconfigure the server to use both NA and PD pools.
    configure(RENEW_CONFIGS[2], *client.getServer());

    // Send Renew message to the server, including IA_PD and requesting IA_NA.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that the client has renewed PD lease.
    leases_client_pd_renewed =  client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));
    EXPECT_GE(leases_client_pd_renewed[0].cltt_ - leases_client_pd[0].cltt_, 1000);

    // The client should now also acquire a NA lease.
    leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));
}

// This test verifies that the client can request address assignment
// while it is renewing an address lease, with a hint.
TEST_F(RenewTest, requestAddressInRenewHint) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.requestAddress(na_iaid_);
    client.requestPrefix(pd_iaid_);

    // Configure the server with PD pools only.
    ASSERT_NO_THROW(configure(RENEW_CONFIGS[1], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired PD lease.
    std::vector<Lease6> leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));

    // The client should not acquire a NA lease.
    std::vector<Lease6> leases_client_na =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(0, leases_client_na.size());
    ASSERT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(na_iaid_));

    client.requestAddress(na_iaid_, IOAddress("2001:db8:1::100"));

    // Send Renew message to the server, including IA_PD and requesting IA_NA.
    // The server should return NoAddrsAvail status code in this case.
    ASSERT_NO_THROW(client.doRenew());
    leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    // The server should return the hint with the zero lifetimes.
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(0, leases_client_na[0].preferred_lft_);
    EXPECT_EQ(0, leases_client_na[0].valid_lft_);
    ASSERT_EQ(STATUS_NoAddrsAvail, client.getStatusCode(na_iaid_));

    std::vector<Lease6> leases_client_pd_renewed =
        client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));
    EXPECT_GE(leases_client_pd_renewed[0].cltt_ - leases_client_pd[0].cltt_, 1000);

    // Reconfigure the server to use both NA and PD pools.
    configure(RENEW_CONFIGS[2], *client.getServer());

    // Send Renew message to the server, including IA_PD and requesting IA_NA.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that the client has renewed PD lease.
    leases_client_pd_renewed = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(pd_iaid_));
    EXPECT_GE(leases_client_pd_renewed[0].cltt_ - leases_client_pd[0].cltt_, 1000);

    // The client should now also acquire a NA lease.
    leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));
}

// This test verifies that the client can request the DOCSIS sub-options.
TEST_F(RenewTest, docsisORO) {
    Dhcp6Client client;

    // Configure client to request IA_NA.
    client.requestAddress(na_iaid_);

    // Configure the DOCSIS vendor ORO for 32, 33, 34, 37 and 38.
    client.requestDocsisOption(DOCSIS3_V6_TFTP_SERVERS);
    client.requestDocsisOption(DOCSIS3_V6_CONFIG_FILE);
    client.requestDocsisOption(DOCSIS3_V6_SYSLOG_SERVERS);
    client.requestDocsisOption(DOCSIS3_V6_TIME_SERVERS);
    client.requestDocsisOption(DOCSIS3_V6_TIME_OFFSET);
    // Don't add it for now.
    client.useDocsisORO(false);

    // Configure the server with NA pools and DOCSIS config file.
    ASSERT_NO_THROW(configure(RENEW_CONFIGS[3], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // Send Renew message to the server.
    ASSERT_NO_THROW(client.doRenew());

    std::vector<Lease6> leases_client_na_renewed =
        client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // No vendor option was included in the renew so there should be none
    // in the received configuration.
    OptionPtr opt = client.config_.findOption(D6O_VENDOR_OPTS);
    ASSERT_FALSE(opt);

    // Add a DOCSIS ORO.
    client.useDocsisORO(true);

    // Send Renew message to the server.
    ASSERT_NO_THROW(client.doRenew());

    leases_client_na_renewed = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());
    EXPECT_EQ(STATUS_Success, client.getStatusCode(na_iaid_));

    // Verify whether there is a vendor option.
    opt = client.config_.findOption(D6O_VENDOR_OPTS);
    ASSERT_TRUE(opt);

    // The vendor option must be a OptionVendor object.
    boost::shared_ptr<OptionVendor> vendor =
        boost::dynamic_pointer_cast<OptionVendor>(opt);
    ASSERT_TRUE(vendor);

    // The vendor-id should be DOCSIS.
    EXPECT_EQ(VENDOR_ID_CABLE_LABS, vendor->getVendorId());

    // There must be a config file sub-option.
    opt = vendor->getOption(DOCSIS3_V6_CONFIG_FILE);

    // With the expected content.
    OptionStringPtr config_file =
        boost::dynamic_pointer_cast<OptionString>(opt);
    ASSERT_TRUE(opt);
    EXPECT_EQ("normal_erouter_v6.cm", config_file->getValue());
}

// This test verifies that the same options can be specified on the global
// level, subnet level and pool level. The options associated with pools
// are used when the lease is handed out from these pools.
TEST_F(RenewTest, optionsInheritance) {
    Dhcp6Client client;
    // Request a single address and single prefix.
    ASSERT_NO_THROW(client.requestPrefix(0xabac, 64, IOAddress("2001:db8:4::")));
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("3000::45")));
    // Request two options configured for the pools from which the client may get
    // a lease.
    client.requestOption(D6O_NAME_SERVERS);
    client.requestOption(D6O_NIS_SERVERS);
    client.requestOption(D6O_NISP_SERVERS);
    client.requestOption(D6O_SNTP_SERVERS);
    ASSERT_NO_FATAL_FAILURE(configure(RENEW_CONFIGS[4], *client.getServer()));
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Simulate aging of leases.
    client.fastFwdTime(1000);

    // Send Renew message to the server.
    ASSERT_NO_THROW(client.doRenew());

    // We have provided hints so we should get leases appropriate
    // for the hints we provided.
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("2001:db8:4::"), 64));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("3000::45")));
    // We shouldn't have leases for the prefix and address which we didn't
    // request.
    ASSERT_FALSE(client.hasLeaseForPrefix(IOAddress("2001:db8:3::"), 64));
    ASSERT_FALSE(client.hasLeaseForAddress(IOAddress("3000::11")));

    // We should have received options associated with a prefix pool and
    // address pool from which we have requested the leases. We should not
    // have received options associated with the remaining pools. Instead,
    // we should have received options associated with a subnet.
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "3000:1::567"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NIS_SERVERS, "3000:1::789"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NISP_SERVERS, "3000:2::3"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_SNTP_SERVERS, "3000:2::1"));

    // Let's now also request a prefix and an address from the remaining pools.
    ASSERT_NO_THROW(client.requestPrefix(0x6806, 64, IOAddress("2001:db8:3::")));
    ASSERT_NO_THROW(client.requestAddress(0x6860, IOAddress("3000::11")));

    client.fastFwdTime(1000);

    // Send another Renew.
    ASSERT_NO_THROW(client.doRenew());

    // We should now have two prefixes from two distinct pools.
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("2001:db8:3::"), 64));
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("2001:db8:4::"), 64));
    //  We should also have two addresses from two distinct pools.
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("3000::45")));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("3000::11")));

    // This time, options from all pools should have been assigned.
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "3000:1::678"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NIS_SERVERS, "3000:1::789"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NISP_SERVERS, "3000:2::3"));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_SNTP_SERVERS, "3000:2::2"));
}

} // end of anonymous namespace
