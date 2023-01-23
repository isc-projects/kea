// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_pdexclude.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <asiolink/io_address.h>
#include <stats/stats_mgr.h>
#include <set>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

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
/// - Configuration 2:
///   - single subnet 3000::/32,
///   - two options specified in the subnet scope,
///   - one option specified at the global scope,
///   - two address pools: 3000::10-3000::20, 3000::40-3000::50,
///   - two prefix pools: 2001:db8:3::/64 and 2001:db8:4::/64,
///   - an option with unique value specified for each pool, so as it is
///     possible to test that pool specific options can be assigned.
///
/// - Configuration 3:
///   - one subnet 3000::/32 used on eth0 interface
///   - prefixes of length 64, delegated from the pool: 2001:db8:3::/48
///   - Excluded Prefix specified (RFC 6603).
///
/// - Configuration 4:
///   - Simple configuration with a single subnet
///   - Two host reservations, one out of the pool, another one in pool
///   - The reservations-in-subnet and reservations-out-of-pool flags are set to
///     true to test that only out of pool reservations are honored.
///
/// - Configuration 5:
///   - Selects random allocator for addresses.
///   - One subnet with three distinct pools.
///   - Random allocator enabled globally for addresses.
///   - Iterative allocator for prefix delegation.
///
/// - Configuration 6:
///   - Selects random allocator for delegated prefixes.
///   - One subnet with three distinct pools.
///   - Random allocator enabled globally for delegated prefixes.
///   - Iterative allocator for address allocation.
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
        "    \"rapid-commit\": true"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::1 - 2001:db8:2::10\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"interface\": \"eth1\","
        "    \"rapid-commit\": false"
        " } ],"
        "\"valid-lifetime\": 4000,"
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : true, "
        "     \"qualifying-suffix\" : \"example.com\" }"
    "}",

    // Configuration 2
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

    // Configuration 3
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
        "          \"delegated-len\": 64,"
        "          \"excluded-prefix\": \"2001:db8:3::1000\","
        "          \"excluded-prefix-len\": 120"
        "        } ],"
        "    \"subnet\": \"3000::/32\", "
        "    \"interface-id\": \"\","
        "    \"interface\": \"eth0\""
        " } ],"
        "\"valid-lifetime\": 4000"
    "}",

    // Configuration 4
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::10\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth0\", "
        "    \"reservations-global\": false,"
        "    \"reservations-in-subnet\": true,"
        "    \"reservations-out-of-pool\": true,"
        "    \"reservations\": [ "
        "       {"
        "         \"duid\": \"aa:bb:cc:dd:ee:ff\","
        "         \"ip-addresses\": [\"2001:db8:1::20\"]"
        "       },"
        "       {"
        "         \"duid\": \"11:22:33:44:55:66\","
        "         \"ip-addresses\": [\"2001:db8:1::5\"]"
        "       }"
        "    ]"
        "} ]"
    "}",

    // Configuration 5
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"allocator\": \"random\","
        "\"pd-allocator\": \"iterative\","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": ["
        "    {"
        "        \"pools\": ["
        "            {"
        "                \"pool\": \"3000::20 - 3000::60\""
        "            }"
        "        ],"
        "        \"pd-pools\": ["
        "            {"
        "                \"prefix\": \"2001:db8:3::\", "
        "                \"prefix-len\": 48, "
        "                \"delegated-len\": 64"
        "            }"
        "        ],"
        "        \"subnet\": \"3000::/32\", "
        "        \"interface\": \"eth0\""
        "    }"
        "],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 6
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"allocator\": \"iterative\","
        "\"pd-allocator\": \"random\","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": ["
        "    {"
        "        \"pools\": ["
        "            {"
        "                \"pool\": \"3000::20 - 3000::60\""
        "            }"
        "        ],"
        "        \"pd-pools\": ["
        "            {"
        "                \"prefix\": \"2001:db8:3::\", "
        "                \"prefix-len\": 48, "
        "                \"delegated-len\": 64"
        "            }"
        "        ],"
        "        \"subnet\": \"3000::/32\", "
        "        \"interface\": \"eth0\""
        "    }"
        "],"
        "\"valid-lifetime\": 4000 }",
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
        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Destructor.
    ///
    /// Clear the DHCP-DDNS configuration.
    virtual ~SARRTest() {
        D2ClientConfigPtr cfg(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(cfg);

        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Check that server processes correctly a prefix hint sent by the
    /// client. This test checks that the server doesn't allocate colliding
    /// prefixes as a result of receiving hints from two clients which set the
    /// non-significant bytes of the prefix in their hints. The server should
    /// zero the non-significant bytes of the hint and allocate the prefix of
    /// the correct (configured) length.
    void directClientPrefixHint();

    /// @brief Check that the server assigns a delegated prefix that is later
    /// returned to the client for various prefix hints.
    ///
    /// When the client renews the lease, it sends a prefix hint with the same
    /// prefix but with a different prefix length. In another case, the client
    /// asks for the same prefix length but different prefix. In both cases,
    /// the server should return an existing lease.
    void directClientPrefixLengthHintRenewal();

    /// @brief This test verifies that the same options can be specified on the
    /// global level, subnet level and pool level. The options associated with
    /// pools are used when the lease is handed out from these pools.
    void optionsInheritance();

    /// @brief This test verifies that it is possible to specify an excluded
    /// prefix (RFC 6603) and send it back to the client requesting prefix
    /// delegation.
    void directClientExcludedPrefix();

    /// @brief Check that when the client includes the Rapid Commit option in
    /// its Solicit, the server responds with Reply and commits the lease.
    void rapidCommitEnable();

    /// @brief Check that the server responds with Advertise if the client
    /// hasn't included the Rapid Commit option in the Solicit.
    void rapidCommitNoOption();

    /// @brief Check that when the Rapid Commit support is disabled for the
    /// subnet the server replies with an Advertise and ignores the Rapid Commit
    /// option sent by the client.
    void rapidCommitDisable();

    /// @brief This test verifies that regular Solicit/Adv/Request/Reply
    /// exchange will result in appropriately set statistics.
    void sarrStats();

    /// @brief This test verifies that pkt6-receive-drop is increased properly
    /// when the client's packet is rejected due to mismatched server-id value.
    void pkt6ReceiveDropStat1();

    /// @brief This test verifies that pkt6-receive-drop is increased properly
    /// when the client's packet is rejected due to being unicast communication.
    void pkt6ReceiveDropStat2();

    /// @brief This test verifies that pkt6-receive-drop is increased properly
    /// when the client's packet is rejected due to having too many client-id
    /// options (exactly one is expected).
    void pkt6ReceiveDropStat3();

    /// @brief This test verifies that in pool reservations are ignored when the
    /// reservations-out-of-pool flag is set to true.
    void reservationModeOutOfPool();

    /// @brief This test verifies that the in-pool reservation can be assigned
    /// to a client not owning this reservation when the
    /// reservations-out-of-pool flag is set to true.
    void reservationIgnoredInOutOfPoolMode();

    /// @brief This test verifies that random allocator is used according
    /// to the configuration and it allocates random addresses.
    void randomAddressAllocation();

    /// @brief This test verifies that random allocator is used according
    /// to the configuration and it allocates random prefixes.
    void randomPrefixAllocation();

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

void
SARRTest::directClientPrefixHint() {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.requestPrefix();
    configure(CONFIGS[0], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());
    // Append IAPREFIX option to the client's message.
    ASSERT_NO_THROW(client.requestPrefix(5678, 64, asiolink::IOAddress("2001:db8:3:33::33")));
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
    client.clearRequestedIAs();
    ASSERT_NO_THROW(client.requestPrefix(5678, 64, IOAddress("2001:db8:3:33::34")));
    ASSERT_NO_THROW(client.doSARR());
    // Server should assign a lease.
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    // The hint collides with the existing lease, so the server should not
    // assign for the second client.
    EXPECT_NE("2001:db8:3:33::", lease_client.addr_.toText());
    EXPECT_NE("2001:db8:3:33::34", lease_client.addr_.toText());
    // Check that the assigned prefix belongs to the pool.
    ASSERT_TRUE(!subnets->empty());
    (*subnets->begin())->inPool(Lease::TYPE_PD, lease_client.addr_);
    EXPECT_EQ(64, lease_client.prefixlen_);
    EXPECT_EQ(3000, lease_client.preferred_lft_);
    EXPECT_EQ(4000, lease_client.valid_lft_);
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
}

TEST_F(SARRTest, directClientPrefixHint) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    directClientPrefixHint();
}

TEST_F(SARRTest, directClientPrefixHintMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    directClientPrefixHint();
}

void
SARRTest::directClientPrefixLengthHintRenewal() {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.requestPrefix();
    configure(CONFIGS[0], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());
    // Append IAPREFIX option to the client's message.
    ASSERT_NO_THROW(client.requestPrefix(5678, 64, asiolink::IOAddress("2001:db8:3:36::")));
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    // The server should respect the prefix hint.
    EXPECT_EQ("2001:db8:3:36::", lease_client.addr_.toText());
    // Server ignores other parts of the IAPREFIX option.
    EXPECT_EQ(64, lease_client.prefixlen_);
    EXPECT_EQ(3000, lease_client.preferred_lft_);
    EXPECT_EQ(4000, lease_client.valid_lft_);
    Lease6Ptr lease_server = checkLease(lease_client);
    // Check that the server recorded the lease.
    ASSERT_TRUE(lease_server);

    // Request the same prefix with a different length. The server should
    // return an existing lease.
    client.clearRequestedIAs();
    ASSERT_NO_THROW(client.requestPrefix(5678, 80, IOAddress("2001:db8:3:36::")));
    ASSERT_NO_THROW(client.doSARR());
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:3:36::", lease_client.addr_.toText());
    EXPECT_EQ(64, lease_client.prefixlen_);

    // Try to request another prefix. The client should still get the existing
    // lease.
    client.clearRequestedIAs();
    ASSERT_NO_THROW(client.requestPrefix(5678, 64, IOAddress("2001:db8:3:37::")));
    ASSERT_NO_THROW(client.doSARR());
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:3:36::", lease_client.addr_.toText());
    EXPECT_EQ(64, lease_client.prefixlen_);
}

TEST_F(SARRTest, directClientPrefixLengthHintRenewal) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    directClientPrefixLengthHintRenewal();
}

TEST_F(SARRTest, directClientPrefixLengthHintRenewalMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    directClientPrefixLengthHintRenewal();
}

void
SARRTest::optionsInheritance() {
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
    ASSERT_NO_FATAL_FAILURE(configure(CONFIGS[2], *client.getServer()));
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

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

    // Perform 4-way exchange again.
    ASSERT_NO_THROW(client.doSARR());

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

TEST_F(SARRTest, optionsInheritance) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    optionsInheritance();
}

TEST_F(SARRTest, optionsInheritanceMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    optionsInheritance();
}

void
SARRTest::directClientExcludedPrefix() {
    Dhcp6Client client;
    // Configure client to request IA_PD.
    client.requestPrefix();
    client.requestOption(D6O_PD_EXCLUDE);
    configure(CONFIGS[3], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ(64, lease_client.prefixlen_);
    EXPECT_EQ(3000, lease_client.preferred_lft_);
    EXPECT_EQ(4000, lease_client.valid_lft_);
    Lease6Ptr lease_server = checkLease(lease_client);
    // Check that the server recorded the lease.
    ASSERT_TRUE(lease_server);

    OptionPtr option = client.getContext().response_->getOption(D6O_IA_PD);
    ASSERT_TRUE(option);
    Option6IAPtr ia = boost::dynamic_pointer_cast<Option6IA>(option);
    ASSERT_TRUE(ia);
    option = ia->getOption(D6O_IAPREFIX);
    ASSERT_TRUE(option);
    Option6IAPrefixPtr pd_option = boost::dynamic_pointer_cast<Option6IAPrefix>(option);
    ASSERT_TRUE(pd_option);
    option = pd_option->getOption(D6O_PD_EXCLUDE);
    ASSERT_TRUE(option);
    Option6PDExcludePtr pd_exclude = boost::dynamic_pointer_cast<Option6PDExclude>(option);
    ASSERT_TRUE(pd_exclude);
    EXPECT_EQ("2001:db8:3::1000", pd_exclude->getExcludedPrefix(IOAddress("2001:db8:3::"),
                                                                64).toText());
    EXPECT_EQ(120, static_cast<unsigned>(pd_exclude->getExcludedPrefixLength()));
}

TEST_F(SARRTest, directClientExcludedPrefix) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    directClientExcludedPrefix();
}

TEST_F(SARRTest, directClientExcludedPrefixMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    directClientExcludedPrefix();
}

void
SARRTest::rapidCommitEnable() {
    Dhcp6Client client;
    // Configure client to request IA_NA
    client.requestAddress();
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

TEST_F(SARRTest, rapidCommitEnable) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    rapidCommitEnable();
}

TEST_F(SARRTest, rapidCommitEnableMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    rapidCommitEnable();
}

void
SARRTest::rapidCommitNoOption() {
    Dhcp6Client client;
    // Configure client to request IA_NA
    client.requestAddress();
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

TEST_F(SARRTest, rapidCommitNoOption) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    rapidCommitNoOption();
}

TEST_F(SARRTest, rapidCommitNoOptionMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    rapidCommitNoOption();
}

void
SARRTest::rapidCommitDisable() {
    Dhcp6Client client;
    // The subnet assigned to eth1 has Rapid Commit disabled.
    client.setInterface("eth1");
    // Configure client to request IA_NA
    client.requestAddress();
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

TEST_F(SARRTest, rapidCommitDisable) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    rapidCommitDisable();
}

TEST_F(SARRTest, rapidCommitDisableMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    rapidCommitDisable();
}

void
SARRTest::sarrStats() {

    // Let's use one of the existing configurations and tell the client to
    // ask for an address.
    Dhcp6Client client;
    configure(CONFIGS[1], *client.getServer());
    client.setInterface("eth1");
    client.requestAddress();

    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Check that the tested statistics is initially set to 0
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr pkt6_rcvd = mgr.getObservation("pkt6-received");
    ObservationPtr pkt6_solicit_rcvd = mgr.getObservation("pkt6-solicit-received");
    ObservationPtr pkt6_adv_sent = mgr.getObservation("pkt6-advertise-sent");
    ObservationPtr pkt6_request_rcvd = mgr.getObservation("pkt6-request-received");
    ObservationPtr pkt6_reply_sent = mgr.getObservation("pkt6-reply-sent");
    ObservationPtr pkt6_sent = mgr.getObservation("pkt6-sent");
    ASSERT_TRUE(pkt6_rcvd);
    ASSERT_TRUE(pkt6_solicit_rcvd);
    ASSERT_TRUE(pkt6_adv_sent);
    ASSERT_TRUE(pkt6_request_rcvd);
    ASSERT_TRUE(pkt6_reply_sent);
    ASSERT_TRUE(pkt6_sent);
    EXPECT_EQ(0, pkt6_rcvd->getInteger().first);
    EXPECT_EQ(0, pkt6_solicit_rcvd->getInteger().first);
    EXPECT_EQ(0, pkt6_adv_sent->getInteger().first);
    EXPECT_EQ(0, pkt6_request_rcvd->getInteger().first);
    EXPECT_EQ(0, pkt6_reply_sent->getInteger().first);
    EXPECT_EQ(0, pkt6_sent->getInteger().first);

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());

    // All expected statistics must be present now.
    pkt6_rcvd = mgr.getObservation("pkt6-received");
    pkt6_solicit_rcvd = mgr.getObservation("pkt6-solicit-received");
    pkt6_adv_sent = mgr.getObservation("pkt6-advertise-sent");
    pkt6_request_rcvd = mgr.getObservation("pkt6-request-received");
    pkt6_reply_sent = mgr.getObservation("pkt6-reply-sent");
    pkt6_sent = mgr.getObservation("pkt6-sent");
    ASSERT_TRUE(pkt6_rcvd);
    ASSERT_TRUE(pkt6_solicit_rcvd);
    ASSERT_TRUE(pkt6_adv_sent);
    ASSERT_TRUE(pkt6_request_rcvd);
    ASSERT_TRUE(pkt6_reply_sent);
    ASSERT_TRUE(pkt6_sent);

    // They also must have expected values.
    EXPECT_EQ(2, pkt6_rcvd->getInteger().first);
    EXPECT_EQ(1, pkt6_solicit_rcvd->getInteger().first);
    EXPECT_EQ(1, pkt6_adv_sent->getInteger().first);
    EXPECT_EQ(1, pkt6_request_rcvd->getInteger().first);
    EXPECT_EQ(1, pkt6_reply_sent->getInteger().first);
    EXPECT_EQ(2, pkt6_sent->getInteger().first);
}

TEST_F(SARRTest, sarrStats) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    sarrStats();
}

TEST_F(SARRTest, sarrStatsMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    sarrStats();
}

void
SARRTest::pkt6ReceiveDropStat1() {

    // Dummy server-id (0xff repeated 10 times)
    std::vector<uint8_t> data(10, 0xff);
    OptionPtr bogus_srv_id(new Option(Option::V6, D6O_SERVERID, data));

    // Let's use one of the existing configurations and tell the client to
    // ask for an address.
    Dhcp6Client client;
    configure(CONFIGS[1], *client.getServer());
    client.setInterface("eth1");
    client.requestAddress();

    client.doSolicit();
    client.useServerId(bogus_srv_id);
    client.doRequest();

    // Ok, let's check the statistic. pkt6-receive-drop should be set to 1.
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();

    ObservationPtr pkt6_recv_drop = mgr.getObservation("pkt6-receive-drop");
    ASSERT_TRUE(pkt6_recv_drop);

    EXPECT_EQ(1, pkt6_recv_drop->getInteger().first);
}

TEST_F(SARRTest, pkt6ReceiveDropStat1) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    pkt6ReceiveDropStat1();
}

TEST_F(SARRTest, pkt6ReceiveDropStat1MultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    pkt6ReceiveDropStat1();
}

void
SARRTest::pkt6ReceiveDropStat2() {

    // Let's use one of the existing configurations and tell the client to
    // ask for an address.
    Dhcp6Client client;
    configure(CONFIGS[1], *client.getServer());
    client.setInterface("eth1");
    client.requestAddress();

    client.setDestAddress(asiolink::IOAddress("2001:db8::1")); // Pretend it's unicast
    client.doSolicit();

    // Ok, let's check the statistic. pkt6-receive-drop should be set to 1.
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();

    ObservationPtr pkt6_recv_drop = mgr.getObservation("pkt6-receive-drop");
    ASSERT_TRUE(pkt6_recv_drop);

    EXPECT_EQ(1, pkt6_recv_drop->getInteger().first);
}

TEST_F(SARRTest, pkt6ReceiveDropStat2) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    pkt6ReceiveDropStat2();
}

TEST_F(SARRTest, pkt6ReceiveDropStat2MultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    pkt6ReceiveDropStat2();
}

void
SARRTest::pkt6ReceiveDropStat3() {

    // Let's use one of the existing configurations and tell the client to
    // ask for an address.
    Dhcp6Client client;
    configure(CONFIGS[1], *client.getServer());
    client.setInterface("eth1");
    client.requestAddress();

    // Let's send our client-id as server-id. That will result in the
    // packet containing the client-id twice. That should cause RFCViolation
    // exception.
    client.useServerId(client.getClientId());
    client.doSolicit();

    // Ok, let's check the statistic. pkt6-receive-drop should be set to 1.
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();

    ObservationPtr pkt6_recv_drop = mgr.getObservation("pkt6-receive-drop");
    ASSERT_TRUE(pkt6_recv_drop);

    EXPECT_EQ(1, pkt6_recv_drop->getInteger().first);
}

TEST_F(SARRTest, pkt6ReceiveDropStat3) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    pkt6ReceiveDropStat3();
}

TEST_F(SARRTest, pkt6ReceiveDropStat3MultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    pkt6ReceiveDropStat3();
}

void
SARRTest::reservationModeOutOfPool() {
    // Create the first client for which we have a reservation out of the
    // dynamic pool.
    Dhcp6Client client;
    configure(CONFIGS[4], *client.getServer());
    client.setDUID("aa:bb:cc:dd:ee:ff");
    client.setInterface("eth0");
    client.requestAddress(1234, IOAddress("2001:db8:1::3"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());

    Lease6 lease = client.getLease(0);
    // Check that the server allocated the reserved address.
    ASSERT_EQ("2001:db8:1::20", lease.addr_.toText());

    client.clearConfig();
    // Create another client which has a reservation within the pool.
    // The server should ignore this reservation in the current mode.
    client.setDUID("11:22:33:44:55:66");
    // This client is requesting a different address than reserved. The
    // server should allocate this address to the client.
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());

    lease = client.getLease(0);
    // Check that the requested address was assigned.
    ASSERT_EQ("2001:db8:1::3", lease.addr_.toText());
}

TEST_F(SARRTest, reservationModeOutOfPool) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    reservationModeOutOfPool();
}

TEST_F(SARRTest, reservationModeOutOfPoolMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    reservationModeOutOfPool();
}

void
SARRTest::reservationIgnoredInOutOfPoolMode() {
    // Create the first client for which we have a reservation out of the
    // dynamic pool.
    Dhcp6Client client;
    configure(CONFIGS[4], *client.getServer());
    client.setDUID("12:34:56:78:9A:BC");
    client.setInterface("eth0");
    client.requestAddress(1234, IOAddress("2001:db8:1::5"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Server should have assigned a prefix.
    ASSERT_EQ(1, client.getLeaseNum());

    Lease6 lease = client.getLease(0);
    // Check that the server allocated the reserved address.
    ASSERT_EQ("2001:db8:1::5", lease.addr_.toText());
}

TEST_F(SARRTest, reservationIgnoredInOutOfPoolMode) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    reservationIgnoredInOutOfPoolMode();
}

TEST_F(SARRTest, reservationIgnoredInOutOfPoolModeMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    reservationIgnoredInOutOfPoolMode();
}

void
SARRTest::randomAddressAllocation() {
    // Create the base client and server configuration.
    Dhcp6Client client;
    configure(CONFIGS[5], *client.getServer());

    // Record what addresses have been allocated and in what order.
    std::set<std::string> allocated_na_set;
    std::vector<IOAddress> allocated_na_vector;
    std::set<std::string> allocated_pd_set;
    std::vector<IOAddress> allocated_pd_vector;
    // Simulate allocations from different clients.
    for (auto i = 0; i < 30; ++i) {
        // Create a client from the base client.
        Dhcp6Client next_client(client.getServer());
        next_client.requestAddress();
        next_client.requestPrefix();
        // Run 4-way exchange.
        ASSERT_NO_THROW(next_client.doSARR());
        // We should have one IA_NA and one IA_PD.
        auto leases_na = next_client.getLeasesByType(Lease::TYPE_NA);
        ASSERT_EQ(1, leases_na.size());
        auto leases_pd = next_client.getLeasesByType(Lease::TYPE_PD);
        ASSERT_EQ(1, leases_pd.size());
        // Remember allocated address and delegated prefix uniqueness
        // and order.
        allocated_na_set.insert(leases_na[0].toText());
        allocated_na_vector.push_back(leases_na[0].addr_);
        allocated_pd_set.insert(leases_pd[0].toText());
        allocated_pd_vector.push_back(leases_pd[0].addr_);
    }
    // Make sure that we have 30 distinct allocations for each lease type.
    ASSERT_EQ(30, allocated_na_set.size());
    ASSERT_EQ(30, allocated_na_vector.size());
    ASSERT_EQ(30, allocated_pd_set.size());
    ASSERT_EQ(30, allocated_pd_vector.size());

    // Make sure that the addresses are not allocated iteratively.
    int consecutives = 0;
    for (auto i = 1; i < allocated_na_vector.size(); ++i) {
        // Record the cases when the previously allocated address is
        // lower by 1 (iterative allocation). Some cases like this are
        // possible even with the random allocation but they should be
        // very rare.
        if (IOAddress::increase(allocated_na_vector[i-1]) == allocated_na_vector[i]) {
            ++consecutives;
        }
    }
    EXPECT_LT(consecutives, 10);

    // Make sure that delegated prefixes have been allocated iteratively.
    consecutives = 0;
    for (auto i = 1; i < allocated_pd_vector.size(); ++i) {
        if (IOAddress::subtract(allocated_pd_vector[i], allocated_pd_vector[i-1]) == IOAddress("0:0:0:1::")) {
            ++consecutives;
        }
    }
    EXPECT_EQ(29, consecutives);
}

TEST_F(SARRTest, randomAddressAllocation) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    randomAddressAllocation();
}

TEST_F(SARRTest, randomAddressAllocationMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    randomAddressAllocation();
}

void
SARRTest::randomPrefixAllocation() {
    // Create the base client and server configuration.
    Dhcp6Client client;
    configure(CONFIGS[6], *client.getServer());

    // Record what addresses have been allocated and in what order.
    std::set<std::string> allocated_na_set;
    std::vector<IOAddress> allocated_na_vector;
    std::set<std::string> allocated_pd_set;
    std::vector<IOAddress> allocated_pd_vector;
    // Simulate allocations from different clients.
    for (auto i = 0; i < 30; ++i) {
        // Create a client from the base client.
        Dhcp6Client next_client(client.getServer());
        next_client.requestAddress();
        next_client.requestPrefix();
        // Run 4-way exchange.
        ASSERT_NO_THROW(next_client.doSARR());
        // We should have one IA_NA and one IA_PD.
        auto leases_na = next_client.getLeasesByType(Lease::TYPE_NA);
        ASSERT_EQ(1, leases_na.size());
        auto leases_pd = next_client.getLeasesByType(Lease::TYPE_PD);
        ASSERT_EQ(1, leases_pd.size());
        // Remember allocated address and delegated prefix uniqueness
        // and order.
        allocated_na_set.insert(leases_na[0].toText());
        allocated_na_vector.push_back(leases_na[0].addr_);
        allocated_pd_set.insert(leases_pd[0].toText());
        allocated_pd_vector.push_back(leases_pd[0].addr_);
    }
    // Make sure that we have 30 distinct allocations for each lease type.
    ASSERT_EQ(30, allocated_na_set.size());
    ASSERT_EQ(30, allocated_na_vector.size());
    ASSERT_EQ(30, allocated_pd_set.size());
    ASSERT_EQ(30, allocated_pd_vector.size());

    // Make sure that the addresses have been allocated iteratively.
    int consecutives = 0;
    for (auto i = 1; i < allocated_na_vector.size(); ++i) {
        // Record the cases when the previously allocated address is
        // lower by 1 (iterative allocation).
        if (IOAddress::increase(allocated_na_vector[i-1]) == allocated_na_vector[i]) {
            ++consecutives;
        }
    }

    // Make sure that addresses have been allocated iteratively.
    EXPECT_EQ(29, consecutives);

    // Make sure that delegated prefixes have been allocated randomly.
    consecutives = 0;
    for (auto i = 1; i < allocated_pd_vector.size(); ++i) {
        if (IOAddress::subtract(allocated_pd_vector[i], allocated_pd_vector[i-1]) == IOAddress("0:0:0:1::")) {
            ++consecutives;
        }
    }
    EXPECT_LT(consecutives, 10);
}

TEST_F(SARRTest, randomPrefixAllocation) {
    Dhcpv6SrvMTTestGuard guard(*this, false);
    randomPrefixAllocation();
}

TEST_F(SARRTest, randomPrefixAllocationMultiThreading) {
    Dhcpv6SrvMTTestGuard guard(*this, true);
    randomPrefixAllocation();
}


} // end of anonymous namespace
