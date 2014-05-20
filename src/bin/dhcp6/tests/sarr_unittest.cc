// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Set of JSON configurations used by the SARR unit tests.
///
/// - Configuration 0:
///   - one subnet used on eth0 interface
///   - prefixes of length 64, delegated from the pool: 2001:db8:3::/48
const char* CONFIGS[] = {
    // Configuration 0
    "{ \"interfaces\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:3::\", "
        "          \"prefix-len\": 48, "
        "          \"delegated-len\": 64"
        "        } ],"
        "    \"subnet\": \"2001:db8::/32\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000 }"
};

/// @brief Test fixture class for testing 4-way exchange: Solicit-Advertise,
/// Request-Reply.
class SARRTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    SARRTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

/// Check that server processes correctly a prefix hint sent by the client.
/// This test checks that the server doesn't allocate colliding prefixes
/// as a result of receiving hints from two clients which set the
/// non-significant bytes of the prefix in their hints. The server should zero
/// the non-significant bytes of the hint and allocate the prefix of the
/// correct (configured) length.
TEST_F(SARRTest, directClientPrefixHint) {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.usePD();
    configure(CONFIGS[0], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getSubnets6();
    ASSERT_EQ(1, subnets->size());
    // Append IAPREFIX option to the client's message.
    ASSERT_NO_THROW(client.useHint(100, 200, 56, "2001:db8:3:33::33"));
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    // The server should correctly deal with the least significant bytes
    // of the hint being set. It should set them to zero and use the
    // valid portion of the hint.
    EXPECT_EQ("2001:db8:3:33::", lease_client.addr_.toText());
    // Server ignores other parts of the IAPREFIX option.
    EXPECT_EQ(64, lease_client.prefixlen_);
    EXPECT_EQ(3000, lease_client.preferred_lft_);
    EXPECT_EQ(4000, lease_client.valid_lft_);
    Lease6Ptr lease_server = checkLease(lease_client);
    // Check that the server recorded the lease.
    ASSERT_TRUE(lease_server);

    // Remove existing lease and modify the DUID of the client to simulate
    // the case that different client is trying to get the prefix.
    client.clearConfig();
    client.modifyDUID();

    // Use the hint with some least significant bytes set.
    ASSERT_NO_THROW(client.useHint(100, 200, 56, "2001:db8:3:33::34"));
    ASSERT_NO_THROW(client.doSARR());
    // Server should assign a lease.
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    // The hint collides with the existing lease, so the server should not
    // assign for the second client.
    EXPECT_NE("2001:db8:3:33::", lease_client.addr_.toText());
    EXPECT_NE("2001:db8:3:33::34", lease_client.addr_.toText());
    // Check that the assigned prefix belongs to the pool.
    (*subnets)[0]->inPool(Lease::TYPE_PD, lease_client.addr_);
    EXPECT_EQ(64, lease_client.prefixlen_);
    EXPECT_EQ(3000, lease_client.preferred_lft_);
    EXPECT_EQ(4000, lease_client.valid_lft_);
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
}

} // end of anonymous namespace
