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
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;

namespace {

/// @brief Set of JSON configurations used by the Host reservation unit tests.
///
/// - Configuration 0: 
///   Single subnet with two reservations, one with a hostname, one without
const char* CONFIGS[] = {
    // Configuration 0: 
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1:1::/64\" } ],"
        "    \"interface\" : \"eth0\" , "
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:04\","
        "        \"ip-addresses\": [ \"2001:db8:1:1::babe\" ],"
        "        \"hostname\": \"alice\""
        "    },"
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1:1::babf\" ]"
        "    } ]"
        " } ]"
    "}"
};

/// @brief Test fixture class for testing host reservations
class HostTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    HostTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

TEST_F(HostTest, basicSARRs) {
    Dhcp6Client client;
    configure(CONFIGS[0], *client.getServer());

    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client we got the reserved address 
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and lease has reserved hostname 
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("alice", lease_server->hostname_);

    // Now redo the client, adding one to the DUID
    client.clearConfig();
    client.modifyDUID();
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client we got the reserved address 
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babf", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and that the server lease has NO hostname 
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("", lease_server->hostname_);

    // Now redo the client with yet another DUID and verify that
    // we get a dynamic address. 
    client.clearConfig();
    client.modifyDUID();
    client.useNA();
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client got a dynamic address
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and that the server lease has NO hostname 
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("", lease_server->hostname_);
}

} // end of anonymous namespace
