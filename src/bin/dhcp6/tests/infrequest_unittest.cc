// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_client_fqdn.h>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used by the Information-Request unit tests.
///
/// - Configuration 0:
///   - one subnet used on eth0 interface
///     - with address and prefix pools
///     - dns-servers option
/// - Configuation 1:
///   - one subnet used on eth0 interface
///     - no addresses or prefixes
///     - domain-search option
/// - Configuration 2:
///   - one subnet used on eth0 interface
///     - dns-servers option for subnet
///   - sip-servers defined in global scope
/// - Configuration 3:
///   - nis-server, nis-domain specified in global scope
///   - no subnets defined
const char* CONFIGS[] = {
    // Configuration 0
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:3::\", "
        "          \"prefix-len\": 48, "
        "          \"delegated-len\": 64"
        "        } ],"
        "    \"option-data\": [ {"
        "        \"name\": \"dns-servers\","
        "        \"data\": \"2001:db8::1, 2001:db8::2\""
        "    } ],"
        "    \"subnet\": \"2001:db8::/32\", "
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
        "    \"option-data\": [ {"
        "    \"name\": \"sip-server-addr\","
        "    \"data\": \"2001:db8::abcd\""
        "    } ],"
        "    \"subnet\": \"2001:db8::/32\", "
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
        "    \"option-data\": [ {"
        "        \"name\": \"sip-server-addr\","
        "        \"data\": \"2001:db8::1\""
        "    } ],"
        "\"subnet6\": [ { "
        "    \"subnet\": \"2001:db8::/32\", "
        "    \"interface\": \"eth0\","
        "    \"option-data\": [ {"
        "        \"name\": \"dns-servers\","
        "        \"data\": \"2001:db8::2\""
        "    } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 3
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"option-data\": [ {"
        "    \"name\": \"nis-servers\","
        "    \"data\": \"2001:db8::1, 2001:db8::2\""
        " } ]"
        "}"
};

/// @brief Test fixture class for testing 4-way exchange: Solicit-Advertise,
/// Request-Reply.
class InfRequestTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    InfRequestTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {

        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Destructor.
    ///
    /// Removes any statistics that may have been set.
    ~InfRequestTest() {
        // Let's wipe all existing statistics.
        isc::stats::StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

/// Check that server processes correctly an incoming inf-request in a
/// typical subnet that has also address and prefix pools.
TEST_F(InfRequestTest, infRequestBasic) {
    Dhcp6Client client;

    // Configure client to request IA_PD.
    configure(CONFIGS[0], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Perform 2-way exchange (Inf-request/reply)
    client.requestOption(D6O_NAME_SERVERS);
    ASSERT_NO_THROW(client.doInfRequest());

    // Confirm that there's a response
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);

    // Check that it contains our client-id
    OptionPtr client_id = response->getOption(D6O_CLIENTID);
    ASSERT_TRUE(client_id);
    EXPECT_TRUE(compareOptions(client_id, client.getClientId()));

    // Check that it contains proper server-id
    OptionPtr server_id = response->getOption(D6O_SERVERID);
    ASSERT_TRUE(server_id);
    EXPECT_TRUE(compareOptions(server_id, client.getServer()->getServerID()));

    // Check that we received requested DNS servers option
    Option6AddrLstPtr dns = boost::dynamic_pointer_cast<Option6AddrLst>
                            (response->getOption(D6O_NAME_SERVERS));
    ASSERT_TRUE(dns);
    Option6AddrLst::AddressContainer addrs = dns->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("2001:db8::1", addrs[0].toText());
    EXPECT_EQ("2001:db8::2", addrs[1].toText());
}

/// Check that server processes correctly an incoming inf-request
/// that does not hold client-id. It's so called anonymous inf-request.
/// Uncommon, but certainly valid behavior.
TEST_F(InfRequestTest, infRequestAnonymous) {
    Dhcp6Client client;

    // Configure client to request IA_PD.
    configure(CONFIGS[0], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Perform 2-way exchange (Inf-request/reply)
    client.requestOption(D6O_NAME_SERVERS);
    client.useClientId(false);
    ASSERT_NO_THROW(client.doInfRequest());

    // Confirm that there's a response
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);

    // Check that we received the requested DNS servers option
    Option6AddrLstPtr dns = boost::dynamic_pointer_cast<Option6AddrLst>
                            (response->getOption(D6O_NAME_SERVERS));
    ASSERT_TRUE(dns);
    Option6AddrLst::AddressContainer addrs = dns->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("2001:db8::1", addrs[0].toText());
    EXPECT_EQ("2001:db8::2", addrs[1].toText());
}

/// Check that server processes correctly an incoming inf-request
/// if there is a subnet without any addresses or prefixes configured.
TEST_F(InfRequestTest, infRequestStateless) {
    Dhcp6Client client;

    // Configure client to request IA_PD.
    configure(CONFIGS[1], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Perform 2-way exchange (Inf-request/reply)
    client.requestOption(D6O_SIP_SERVERS_ADDR);
    ASSERT_NO_THROW(client.doInfRequest());

    // Confirm that there's a response
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);

    // Check that we received the requested SIP servers option
    Option6AddrLstPtr sip = boost::dynamic_pointer_cast<Option6AddrLst>
                            (response->getOption(D6O_SIP_SERVERS_ADDR));
    ASSERT_TRUE(sip);
    Option6AddrLst::AddressContainer addrs = sip->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("2001:db8::abcd", addrs[0].toText());
}

/// Check that server processes correctly an incoming inf-request
/// if there are options defined at both global and subnet scope.
TEST_F(InfRequestTest, infRequestSubnetAndGlobal) {
    Dhcp6Client client;

    // Configure client to request IA_PD.
    configure(CONFIGS[2], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Perform 2-way exchange (Inf-request/reply)
    client.requestOption(D6O_SIP_SERVERS_ADDR);
    client.requestOption(D6O_NAME_SERVERS);
    ASSERT_NO_THROW(client.doInfRequest());

    // Confirm that there's a response
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);

    // Check that we received the requested sip servers option
    Option6AddrLstPtr sip = boost::dynamic_pointer_cast<Option6AddrLst>
                            (response->getOption(D6O_SIP_SERVERS_ADDR));
    ASSERT_TRUE(sip);
    Option6AddrLst::AddressContainer addrs = sip->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("2001:db8::1", addrs[0].toText());

    // Check that we received the requested dns servers option
    Option6AddrLstPtr dns = boost::dynamic_pointer_cast<Option6AddrLst>
                            (response->getOption(D6O_NAME_SERVERS));
    ASSERT_TRUE(dns);
    addrs = dns->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("2001:db8::2", addrs[0].toText());
}

/// Check that server processes correctly an incoming inf-request
/// if there are options defined at global scope only (no subnets).
TEST_F(InfRequestTest, infRequestNoSubnets) {
    Dhcp6Client client;

    // Configure client to request IA_PD.
    configure(CONFIGS[3], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(0, subnets->size());

    // Perform 2-way exchange (Inf-request/reply)
    client.requestOption(D6O_NIS_SERVERS);
    ASSERT_NO_THROW(client.doInfRequest());

    // Confirm that there's a response
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);

    // Check that we received the requested sip servers option
    Option6AddrLstPtr nis = boost::dynamic_pointer_cast<Option6AddrLst>
                            (response->getOption(D6O_NIS_SERVERS));
    ASSERT_TRUE(nis);
    Option6AddrLst::AddressContainer addrs = nis->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("2001:db8::1", addrs[0].toText());
    EXPECT_EQ("2001:db8::2", addrs[1].toText());
}

/// Check that server processes correctly an incoming inf-request in a
/// typical subnet that has also address and prefix pools.
TEST_F(InfRequestTest, infRequestStats) {
    Dhcp6Client client;

    // Configure client to request IA_PD.
    configure(CONFIGS[0], *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Ok, let's check the statistics. None should be present.
    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr pkt6_rcvd = mgr.getObservation("pkt6-received");
    ObservationPtr pkt6_infreq_rcvd = mgr.getObservation("pkt6-infrequest-received");
    ObservationPtr pkt6_reply_sent = mgr.getObservation("pkt6-reply-sent");
    ObservationPtr pkt6_sent = mgr.getObservation("pkt6-sent");
    EXPECT_FALSE(pkt6_rcvd);
    EXPECT_FALSE(pkt6_infreq_rcvd);
    EXPECT_FALSE(pkt6_reply_sent);
    EXPECT_FALSE(pkt6_sent);

    // Perform 2-way exchange (Inf-request/reply)
    client.requestOption(D6O_NAME_SERVERS);
    ASSERT_NO_THROW(client.doInfRequest());

    // Confirm that there's a response
    Pkt6Ptr response = client.getContext().response_;
    ASSERT_TRUE(response);

    pkt6_rcvd = mgr.getObservation("pkt6-received");
    pkt6_infreq_rcvd = mgr.getObservation("pkt6-infrequest-received");
    pkt6_reply_sent = mgr.getObservation("pkt6-reply-sent");
    pkt6_sent = mgr.getObservation("pkt6-sent");

    ASSERT_TRUE(pkt6_rcvd);
    ASSERT_TRUE(pkt6_infreq_rcvd);
    ASSERT_TRUE(pkt6_reply_sent);
    ASSERT_TRUE(pkt6_sent);

    // They also must have expected values.
    EXPECT_EQ(1, pkt6_rcvd->getInteger().first);
    EXPECT_EQ(1, pkt6_infreq_rcvd->getInteger().first);
    EXPECT_EQ(1, pkt6_reply_sent->getInteger().first);
    EXPECT_EQ(1, pkt6_sent->getInteger().first);
}

} // end of anonymous namespace
