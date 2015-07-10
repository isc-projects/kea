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

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;

namespace {

/// @brief Set of JSON configurations used throughout the Renew tests.
///
/// - Configuration 0:
///   - only addresses (no prefixes)
///   - 2 subnets with 2001:db8:1::/64 and 2001:db8:2::64
///   - 1 subnet for eth0 and 1 subnet for eth1
///
/// - Configuration 1:
///   - similar to Configuration 0 but different subnets
///   - pools configured: 2001:db8:3::/64 and 2001:db8:4::/64
///
/// - Configuration 2:
///   - similar to Configuration 0 and Configuration 1
///   - pools configured: 3000:1::/64 and 3000:2::/64
///   - this specific configuration is used by tests using relays
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
        "\"valid-lifetime\": 4000 }"
};

/// @brief Test fixture class for testing Renew.
class RenewTest : public Dhcpv6MessageTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    RenewTest()
        : Dhcpv6MessageTest() {
    }
};

// This test verifies that the client can request the prefix delegation
// while it is renewing an address lease.
TEST_F(RenewTest, requestPrefixInRenew) {
    Dhcp6Client client;

    // Configure client to request IA_NA and IA_PD.
    client.useNA();
    client.usePD();

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

    // Reconfigure the server to use both NA and PD pools.
    configure(RENEW_CONFIGS[1], *client.getServer());

    // Send Renew message to the server, including IA_NA and requesting IA_PD.
    ASSERT_NO_THROW(client.doRenew());

    // Make sure that the client has acquired NA lease.
    std::vector<Lease6> leases_client_na_renewed = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases_client_na_renewed.size());

    // The lease should have been renewed.
    EXPECT_EQ(1000, leases_client_na_renewed[0].cltt_ - leases_client_na[0].cltt_);

    // The client should now also acquire a PD lease.
    leases_client_pd = client.getLeasesByType(Lease::TYPE_PD);
    ASSERT_EQ(1, leases_client_pd.size());
}


} // end of anonymous namespace
