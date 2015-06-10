// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option6_client_fqdn.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/d2_client_mgr.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;

namespace {

/// @brief Set of JSON configurations used by the SARR unit tests.
///
/// - Configuration 0:
///   - one subnet 3000::/32 used on eth0 interface
///   - prefixes of length 64, delegated from the pool: 2001:db8:3::/48
///   - the delegated prefix was intentionally selected to not match the
///     subnet prefix, to test that the delegated prefix doesn't need to
///     match the subnet prefix
///
/// - Configuration 1:
///   - two subnets 2001:db8:1::/48 and 2001:db8:2::/48
///   - first subnet assigned to interface eth0, another one assigned to eth1
///   - one pool for subnet in a range of 2001:db8:X::1 - 2001:db8:X::10,
///     where X is 1 or 2
///   - enables Rapid Commit for the first subnet and disables for the second
///     one
///   - DNS updates enabled
///
const char* CONFIGS[] = {
    // Configuration 0
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:3::\", "
        "          \"prefix-len\": 48, "
        "          \"delegated-len\": 64"
        "        } ],"
        "    \"subnet\": \"3000::/32\", "
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
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::10\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth0\","
        "    \"rapid-commit\": True"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::1 - 2001:db8:2::10\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"interface\": \"eth1\","
        "    \"rapid-commit\": False"
        " } ],"
        "\"valid-lifetime\": 4000,"
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : True, "
        "     \"qualifying-suffix\" : \"example.com\" }"
    "}",

// Configuration 2
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::10\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth0\","
        "    \"rapid-commit\": False"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::1 - 2001:db8:2::10\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"interface\": \"eth1\","
        "    \"rapid-commit\": True"
        " } ],"
        "\"valid-lifetime\": 4000,"
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : True, "
        "     \"qualifying-suffix\" : \"example.com\" }"
    "}"
};

/// @brief Test fixture class for testing 4-way exchange: Solicit-Advertise,
/// Request-Reply and 2-way exchange: Solicit-Reply.
class SARRTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    SARRTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
    }

    /// @brief Destructor.
    ///
    /// Clear the DHCP-DDNS configuration.
    virtual ~SARRTest() {
        D2ClientConfigPtr cfg(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(cfg);
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
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());
    // Append IAPREFIX option to the client's message.
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:3:33::33"));
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
    ASSERT_NO_THROW(client.useHint(100, 200, 64, "2001:db8:3:33::34"));
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

// Check that when the client includes the Rapid Commit option in its
// Solicit, the server responds with Reply and commits the lease.
TEST_F(SARRTest, rapidCommitEnable) {
    Dhcp6Client client;
    // Configure client to request IA_NA
    client.useNA();
    configure(CONFIGS[1], *client.getServer());
    ASSERT_NO_THROW(client.getServer()->startD2());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());
    // Perform 2-way exchange.
    client.useRapidCommit(true);
    // Include FQDN to trigger generation of name change requests.
    ASSERT_NO_THROW(client.useFQDN(Option6ClientFqdn::FLAG_S,
                                   "client-name.example.org",
                                   Option6ClientFqdn::FULL));

    ASSERT_NO_THROW(client.doSolicit());
    // Server should have committed a lease.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    // Make sure that the address belongs to the subnet configured.
    ASSERT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->
                selectSubnet(lease_client.addr_, ClientClasses()));
    // Make sure that the server responded with Reply.
    ASSERT_TRUE(client.getContext().response_);
    EXPECT_EQ(DHCPV6_REPLY, client.getContext().response_->getType());
    // Rapid Commit option should be included.
    EXPECT_TRUE(client.getContext().response_->getOption(D6O_RAPID_COMMIT));
    // Check that the lease has been committed.
    Lease6Ptr lease_server = checkLease(lease_client);
    EXPECT_TRUE(lease_server);
    // There should be one name change request generated.
    EXPECT_EQ(1, CfgMgr::instance().getD2ClientMgr().getQueueSize());
}

// Check that the server responds with Advertise if the client hasn't
// included the Rapid Commit option in the Solicit.
TEST_F(SARRTest, rapidCommitNoOption) {
    Dhcp6Client client;
    // Configure client to request IA_NA
    client.useNA();
    configure(CONFIGS[1], *client.getServer());
    ASSERT_NO_THROW(client.getServer()->startD2());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());
    // Include FQDN to test that the server will not create name change
    // requests when it sends Advertise (Rapid Commit disabled).
    ASSERT_NO_THROW(client.useFQDN(Option6ClientFqdn::FLAG_S,
                                   "client-name.example.org",
                                   Option6ClientFqdn::FULL));
    ASSERT_NO_THROW(client.doSolicit());
    // There should be no lease because the server should have responded
    // with Advertise.
    ASSERT_EQ(0, client.getLeaseNum());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    EXPECT_EQ(DHCPV6_ADVERTISE, client.getContext().response_->getType());
    // Make sure that the Rapid Commit option is not included.
    EXPECT_FALSE(client.getContext().response_->getOption(D6O_RAPID_COMMIT));
    // There should be no name change request generated.
    EXPECT_EQ(0, CfgMgr::instance().getD2ClientMgr().getQueueSize());
}

// Check that when the Rapid Commit support is disabled for the subnet
// the server replies with an Advertise and ignores the Rapid Commit
// option sent by the client.
TEST_F(SARRTest, rapidCommitDisable) {
    Dhcp6Client client;
    // The subnet assigned to eth1 has Rapid Commit disabled.
    client.setInterface("eth1");
    // Configure client to request IA_NA
    client.useNA();
    configure(CONFIGS[1], *client.getServer());
    ASSERT_NO_THROW(client.getServer()->startD2());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());
    // Send Rapid Commit option to the server.
    client.useRapidCommit(true);
    // Include FQDN to test that the server will not create name change
    // requests when it sends Advertise (Rapid Commit disabled).
    ASSERT_NO_THROW(client.useFQDN(Option6ClientFqdn::FLAG_S,
                                   "client-name.example.org",
                                   Option6ClientFqdn::FULL));
    ASSERT_NO_THROW(client.doSolicit());
    // There should be no lease because the server should have responded
    // with Advertise.
    ASSERT_EQ(0, client.getLeaseNum());
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    EXPECT_EQ(DHCPV6_ADVERTISE, client.getContext().response_->getType());
    // Make sure that the Rapid Commit option is not included.
    EXPECT_FALSE(client.getContext().response_->getOption(D6O_RAPID_COMMIT));
    // There should be no name change request generated.
    EXPECT_EQ(0, CfgMgr::instance().getD2ClientMgr().getQueueSize());
}


} // end of anonymous namespace
