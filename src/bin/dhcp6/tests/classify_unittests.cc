// Copyright (C) 2016-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor_class.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/tests/pkt_captures.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <asiolink/io_address.h>
#include <stats/stats_mgr.h>
#include <boost/pointer_cast.hpp>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used by the classification unit tests.
///
/// - Configuration 0:
///   - Specifies 3 classes: 'router', 'reserved-class1' and 'reserved-class2'.
///   - 'router' class is assigned when the client sends option 1234 (string)
///      equal to 'foo'.
///   - The other two classes are reserved for the client having
///     DUID '01:02:03:04'
///   - Class 'router' includes option 'ipv6-forwarding'.
///   - Class 'reserved-class1' includes option DNS servers.
///   - Class 'reserved-class2' includes option NIS servers.
///   - All three options are sent when client has reservations for the
///     'reserved-class1', 'reserved-class2' and sends option 1234 with
///     the 'foo' value.
///   - There is one subnet specified 2001:db8:1::/48 with pool of
///     IPv6 addresses.
///
/// - Configuration 1:
///   - Used for complex membership (example taken from HA)
///   - 1 subnet: 2001:db8:1::/48
///   - 4 pools: 2001:db8:1:1::/64, 2001:db8:1:2::/64,
///              2001:db8:1:3::/64 and 2001:db8:1:4::/64
///   - 4 classes to compose:
///      server1 and server2 for each HA server
///      option 1234 'foo' aka telephones
///      option 1234 'bar' aka computers
///
/// - Configuration 2:
///   - Used for complex membership (example taken from HA) and pd-pools
///   - 1 subnet: 2001:db8::/32
///   - 4 pd-pools: 2001:db8:1::/48, 2001:db8:2::/48,
///                 2001:db8:3::/48 and 2001:db8:4::/48
///   - 4 classes to compose:
///      server1 and server2 for each HA server
///      option 1234 'foo' aka telephones
///      option 1234 'bar' aka computers
///
/// - Configuration 3:
///   - Used for the DROP class
///   - 1 subnet: 2001:db8:1::/48
///   - 2 pool: 2001:db8:1:1::/64
///   - the following class defined: option 1234 'foo', DROP
///
/// - Configuration 4:
///   - Used for the DROP class and reservation existence
///   - 1 subnet: 2001:db8:1::/48
///   - 2 pool: 2001:db8:1:1::/64
///   - the following class defined: not member('KNOWN'), DROP
/// @note the reservation includes a hostname because raw reservations are
/// not yet allowed
///
/// - Configuration 5:
///   - Used for the DROP class and reservation class
///   - 1 subnet: 2001:db8:1::/48
///   - 1 pool: 2001:db8:1:1::/64
///   - the following class defined:
///     - allowed
///     - member('KNOWN') or member('UNKNOWN'), t
///     - not member('allowed') and member('t'), DROP
///     The function of the always true 't' class is to move the DROP
///     evaluation to the classification point after the host reservation
///     lookup, i.e. indirect KNOWN / UNKNOWN dependency
///
/// - Configuration 6:
///   - Used for the early global reservations lookup / select subnet.
///   - 2 subnets: 2001:db8:1::/48 (guarded) and 2001:db8:2::/48
///   - 2 pools: 2001:db8:1:1::/64 and 2001:db8:2:1::/64
///   - 1 global reservation setting the first class
///   - the following class defined: first
///
/// - Configuration 7:
///   - Used for the early global reservations lookup / drop.
///   - 1 subnet: 2001:db8:1::/48
///   - 1 pool: 2001:db8:1:1::/64
///   - 1 global reservation setting the DROP class
///
const char* CONFIGS[] = {
    // Configuration 0
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-def\": [ "
        "{"
        "    \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\""
        "},"
        "{"
        "    \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\""
        "} ],"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"router\","
        "   \"test\": \"option[host-name].text == 'foo'\","
        "    \"option-data\": ["
        "    {"
        "        \"name\": \"ipv6-forwarding\", "
        "        \"data\": \"true\""
        "    } ]"
        "},"
        "{"
        "   \"name\": \"reserved-class1\","
        "   \"option-data\": ["
        "   {"
        "       \"name\": \"dns-servers\","
        "       \"data\": \"2001:db8:1::50\""
        "   }"
        "   ]"
        "},"
        "{"
        "   \"name\": \"reserved-class2\","
        "   \"option-data\": ["
        "   {"
        "       \"name\": \"nis-servers\","
        "       \"data\": \"2001:db8:1::100\""
        "   }"
        "   ]"
        "}"
        "],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:04\","
        "        \"client-classes\": [ \"reserved-class1\", \"reserved-class2\" ]"
        "    } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 1
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-def\": [ "
        "{"
        "    \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\""
        "} ],"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"server1\""
        "},"
        "{"
        "   \"name\": \"server2\""
        "},"
        "{"
        "   \"name\": \"telephones\","
        "   \"test\": \"option[host-name].text == 'foo'\""
        "},"
        "{"
        "   \"name\": \"computers\","
        "   \"test\": \"option[host-name].text == 'bar'\""
        "},"
        "{"
        "   \"name\": \"server1_and_telephones\","
        "   \"test\": \"member('server1') and member('telephones')\""
        "},"
        "{"
        "   \"name\": \"server1_and_computers\","
        "   \"test\": \"member('server1') and member('computers')\""
        "},"
        "{"
        "   \"name\": \"server2_and_telephones\","
        "   \"test\": \"member('server2') and member('telephones')\""
        "},"
        "{"
        "   \"name\": \"server2_and_computers\","
        "   \"test\": \"member('server2') and member('computers')\""
        "}"
        "],"
        "\"subnet6\": [ "
        "{   \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\","
        "    \"pools\": [ "
        "        { \"pool\": \"2001:db8:1:1::/64\","
        "          \"client-class\": \"server1_and_telephones\" },"
        "        { \"pool\": \"2001:db8:1:2::/64\","
        "          \"client-class\": \"server1_and_computers\" },"
        "        { \"pool\": \"2001:db8:1:3::/64\","
        "          \"client-class\": \"server2_and_telephones\" },"
        "        { \"pool\": \"2001:db8:1:4::/64\","
        "          \"client-class\": \"server2_and_computers\" } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 2
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-def\": [ "
        "{"
        "    \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\""
        "} ],"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"server1\""
        "},"
        "{"
        "   \"name\": \"server2\""
        "},"
        "{"
        "   \"name\": \"telephones\","
        "   \"test\": \"option[host-name].text == 'foo'\""
        "},"
        "{"
        "   \"name\": \"computers\","
        "   \"test\": \"option[host-name].text == 'bar'\""
        "},"
        "{"
        "   \"name\": \"server1_and_telephones\","
        "   \"test\": \"member('server1') and member('telephones')\""
        "},"
        "{"
        "   \"name\": \"server1_and_computers\","
        "   \"test\": \"member('server1') and member('computers')\""
        "},"
        "{"
        "   \"name\": \"server2_and_telephones\","
        "   \"test\": \"member('server2') and member('telephones')\""
        "},"
        "{"
        "   \"name\": \"server2_and_computers\","
        "   \"test\": \"member('server2') and member('computers')\""
        "}"
        "],"
        "\"subnet6\": [ "
        "{   \"subnet\": \"2001:db8::/32\", "
        "    \"interface\": \"eth1\","
        "    \"pd-pools\": [ "
        "        { \"prefix\": \"2001:db8:1::\","
        "          \"prefix-len\": 48, \"delegated-len\": 64,"
        "          \"client-class\": \"server1_and_telephones\" },"
        "        { \"prefix\": \"2001:db8:2::\","
        "          \"prefix-len\": 48, \"delegated-len\": 64,"
        "          \"client-class\": \"server1_and_computers\" },"
        "        { \"prefix\": \"2001:db8:3::\","
        "          \"prefix-len\": 48, \"delegated-len\": 64,"
        "          \"client-class\": \"server2_and_telephones\" },"
        "        { \"prefix\": \"2001:db8:4::\","
        "          \"prefix-len\": 48, \"delegated-len\": 64,"
        "          \"client-class\": \"server2_and_computers\" } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 3
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-def\": [ "
        "{"
        "    \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\""
        "},"
        "{"
        "    \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\""
        "} ],"
        "\"client-classes\": ["
        "{"
        "   \"name\": \"DROP\","
        "   \"test\": \"option[host-name].text == 'foo'\""
        "}"
        "],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\""
        " } ],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 4
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"client-classes\": ["
        "{"
        "   \"name\": \"DROP\","
        "   \"test\": \"not member('KNOWN')\""
        "}"
        "],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:04\","
        "        \"hostname\": \"allowed\""
        "    } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 5
    "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"client-classes\": ["
        "{"
        "   \"name\": \"allowed\""
        "},"
        "{"
        "   \"name\": \"t\","
        "   \"test\": \"member('KNOWN') or member('UNKNOWN')\""
        "},"
        "{"
        "   \"name\": \"DROP\","
        "   \"test\": \"not member('allowed') and member('t')\""
        "}"
        "],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:04\","
        "        \"client-classes\": [ \"allowed\" ]"
        "    } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }",

    // Configuration 6
    "{ \"interfaces-config\": {"
    "  \"interfaces\": [ \"*\" ]"
    "},"
    "\"early-global-reservations-lookup\": true, "
    "\"preferred-lifetime\": 3000, "
    "\"rebind-timer\": 2000, "
    "\"renew-timer\": 1000, "
    "\"client-classes\": ["
    "{"
    "   \"name\": \"first\""
    "}"
    "],"
    "\"subnet6\": [ "
    "{"
    "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
    "    \"subnet\": \"2001:db8:1::/48\", "
    "    \"interface\": \"eth1\","
    "    \"id\": 1,"
    "    \"client-class\": \"first\""
    "},"
    "{"
    "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ], "
    "    \"subnet\": \"2001:db8:2::/48\", "
    "    \"interface\": \"eth1\","
    "    \"id\": 2"
    "}"
    "],"
    "\"reservations\": ["
    "{"
    "    \"duid\": \"01:02:03:04\","
    "    \"client-classes\": [ \"first\" ]"
    "}"
    "],"
    "\"valid-lifetime\": 4000 }",

    // Configuration 7
    "{ \"interfaces-config\": {"
    "  \"interfaces\": [ \"*\" ]"
    "},"
    "\"early-global-reservations-lookup\": true, "
    "\"preferred-lifetime\": 3000, "
    "\"rebind-timer\": 2000, "
    "\"renew-timer\": 1000, "
    "\"subnet6\": [ "
    "{"
    "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
    "    \"subnet\": \"2001:db8:1::/48\", "
    "    \"interface\": \"eth1\","
    "    \"id\": 1"
    "}"
    "],"
    "\"reservations\": ["
    "{"
    "    \"duid\": \"01:02:03:04\","
    "    \"client-classes\": [ \"DROP\" ]"
    "}"
    "],"
    "\"valid-lifetime\": 4000 }"
};

/// @brief Test fixture class for testing client classification by the
/// DHCPv6 server.
///
/// @todo There are numerous tests not using Dhcp6Client class. They should be
/// migrated to use it one day.
class ClassifyTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    ClassifyTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
    }

    /// @brief Verify values of options returned by the server when the server
    /// uses configuration with index 0.
    ///
    /// @param config Reference to DHCP client's configuration received.
    /// @param ip_forwarding Expected value of IP forwarding option. This option
    /// is expected to always be present.
    /// @param dns_servers String holding an address carried within DNS
    /// servers option. If this value is empty, the option is expected to not
    /// be included in the response.
    /// @param nis_servers String holding an address carried within NIS
    /// servers option. If this value is empty, the option is expected to not
    /// be included in the response.
    void verifyConfig0Options(const Dhcp6Client::Configuration& config,
                              const uint8_t ip_forwarding = 1,
                              const std::string& dns_servers = "",
                              const std::string& nis_servers = "") {
        // IP forwarding option should always exist.
        OptionPtr ip_forwarding_opt = config.findOption(2345);
        ASSERT_TRUE(ip_forwarding_opt);
        // The option comprises 2 bytes of option code, 2 bytes of option length,
        // and a single 1 byte value. This makes it 5 bytes of a total length.
        ASSERT_EQ(5, ip_forwarding_opt->len());
        ASSERT_EQ(static_cast<int>(ip_forwarding),
                  static_cast<int>(ip_forwarding_opt->getUint8()));

        // DNS servers.
        Option6AddrLstPtr dns_servers_opt = boost::dynamic_pointer_cast<
            Option6AddrLst>(config.findOption(D6O_NAME_SERVERS));
        if (!dns_servers.empty()) {
            ASSERT_TRUE(dns_servers_opt);
            Option6AddrLst::AddressContainer addresses = dns_servers_opt->getAddresses();
            // For simplicity, we expect only a single address.
            ASSERT_EQ(1, addresses.size());
            EXPECT_EQ(dns_servers, addresses[0].toText());

        } else {
            EXPECT_FALSE(dns_servers_opt);
        }

        // NIS servers.
        Option6AddrLstPtr nis_servers_opt = boost::dynamic_pointer_cast<
            Option6AddrLst>(config.findOption(D6O_NIS_SERVERS));
        if (!nis_servers.empty()) {
            ASSERT_TRUE(nis_servers_opt);
            Option6AddrLst::AddressContainer addresses = nis_servers_opt->getAddresses();
            // For simplicity, we expect only a single address.
            ASSERT_EQ(1, addresses.size());
            EXPECT_EQ(nis_servers, addresses[0].toText());

        } else {
            EXPECT_FALSE(nis_servers_opt);
        }
    }

    /// @brief Create a solicit
    Pkt6Ptr createSolicit(std::string remote_addr = "fe80::abcd") {
            OptionPtr clientid = generateClientId();
            Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
            query->setRemoteAddr(IOAddress(remote_addr));
            query->addOption(clientid);
            query->setIface("eth1");
            query->setIndex(ETH1_INDEX);
            query->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));
            return (query);
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Checks if DOCSIS client packets are classified properly
TEST_F(ClassifyTest, docsisClientClassification) {

    NakedDhcpv6Srv srv(0);

    // Let's create a relayed SOLICIT. This particular relayed SOLICIT has
    // vendor-class set to docsis3.0
    Pkt6Ptr sol1;
    ASSERT_NO_THROW(sol1 = PktCaptures::captureDocsisRelayedSolicit());
    ASSERT_NO_THROW(sol1->unpack());

    srv.classifyPacket(sol1);

    // It should belong to docsis3.0 class. It should not belong to eRouter1.0
    EXPECT_TRUE(sol1->inClass("VENDOR_CLASS_docsis3.0"));
    EXPECT_FALSE(sol1->inClass("eRouter1.0"));

    // Let's get a relayed SOLICIT. This particular relayed SOLICIT has
    // vendor-class set to eRouter1.0
    Pkt6Ptr sol2;
    ASSERT_NO_THROW(sol2 = PktCaptures::captureeRouterRelayedSolicit());
    ASSERT_NO_THROW(sol2->unpack());

    srv.classifyPacket(sol2);

    EXPECT_TRUE(sol2->inClass(srv.VENDOR_CLASS_PREFIX + "eRouter1.0"));
    EXPECT_FALSE(sol2->inClass(srv.VENDOR_CLASS_PREFIX + "docsis3.0"));
}

// Checks if client packets are classified properly using match expressions.
// Note option names and definitions are used.
TEST_F(ClassifyTest, matchClassification) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[host-name].text == 'foo'\" },"
        "{   \"name\": \"template-client-id\","
        "    \"template-test\": \"substring(option[1].hex,0,3)\" },"
        "{   \"name\": \"SPAWN_template-hostname_foo\" },"
        "{   \"name\": \"template-hostname\","
        "    \"template-test\": \"option[host-name].text\"} ] }";

    ASSERT_NO_THROW(configure(config));

    // Create packets with enough to select the subnet
    Pkt6Ptr query1 = createSolicit();
    Pkt6Ptr query2 = createSolicit();
    Pkt6Ptr query3 = createSolicit();

    // Create and add an ORO option to the first 2 queries
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    ASSERT_TRUE(oro);
    oro->addValue(2345);
    query1->addOption(oro);
    query2->addOption(oro);

    // Create and add a host-name option to the first and last queries
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query1->addOption(hostname);
    query3->addOption(hostname);

    // Classify packets
    srv.classifyPacket(query1);
    srv.classifyPacket(query2);
    srv.classifyPacket(query3);

    EXPECT_EQ(query1->classes_.size(), 6);
    EXPECT_EQ(query2->classes_.size(), 3);
    EXPECT_EQ(query3->classes_.size(), 6);

    EXPECT_TRUE(query1->inClass("ALL"));
    EXPECT_TRUE(query2->inClass("ALL"));
    EXPECT_TRUE(query3->inClass("ALL"));

    // Packets with the exception of the second should be in the router class
    EXPECT_TRUE(query1->inClass("router"));
    EXPECT_FALSE(query2->inClass("router"));
    EXPECT_TRUE(query3->inClass("router"));

    EXPECT_TRUE(query1->inClass("template-hostname"));
    EXPECT_FALSE(query2->inClass("template-hostname"));
    EXPECT_TRUE(query3->inClass("template-hostname"));

    EXPECT_TRUE(query1->inClass("SPAWN_template-hostname_foo"));
    EXPECT_FALSE(query2->inClass("SPAWN_template-hostname_foo"));
    EXPECT_TRUE(query3->inClass("SPAWN_template-hostname_foo"));

    EXPECT_TRUE(query1->inClass("template-client-id"));
    EXPECT_TRUE(query2->inClass("template-client-id"));
    EXPECT_TRUE(query3->inClass("template-client-id"));

    EXPECT_TRUE(query1->inClass("SPAWN_template-client-id_def"));
    EXPECT_TRUE(query2->inClass("SPAWN_template-client-id_def"));
    EXPECT_TRUE(query3->inClass("SPAWN_template-client-id_def"));

    // Process queries
    AllocEngine::ClientContext6 ctx1;
    bool drop = !srv.earlyGHRLookup(query1, ctx1);
    ASSERT_FALSE(drop);
    srv.initContext(query1, ctx1, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response1 = srv.processSolicit(ctx1);
    AllocEngine::ClientContext6 ctx2;
    drop = !srv.earlyGHRLookup(query2, ctx2);
    ASSERT_FALSE(drop);
    srv.initContext(query2, ctx2, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response2 = srv.processSolicit(ctx2);
    AllocEngine::ClientContext6 ctx3;
    drop = !srv.earlyGHRLookup(query3, ctx3);
    ASSERT_FALSE(drop);
    srv.initContext(query3, ctx3, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response3 = srv.processSolicit(ctx3);

    // Classification processing should add an ip-forwarding option
    OptionPtr opt1 = response1->getOption(2345);
    EXPECT_TRUE(opt1);

    // But only for the first query: second was not classified
    OptionPtr opt2 = response2->getOption(2345);
    EXPECT_FALSE(opt2);

    // But only for the first query: third has no ORO
    OptionPtr opt3 = response3->getOption(2345);
    EXPECT_FALSE(opt3);
}

// Check that only-if-required classes are not evaluated by classifyPacket
TEST_F(ClassifyTest, required) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"only-if-required\": true, "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[host-name].text == 'foo'\" } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create packets with enough to select the subnet
    OptionPtr clientid = generateClientId();
    Pkt6Ptr query1(new Pkt6(DHCPV6_SOLICIT, 1234));
    query1->setRemoteAddr(IOAddress("fe80::abcd"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);
    query1->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));
    Pkt6Ptr query2(new Pkt6(DHCPV6_SOLICIT, 1234));
    query2->setRemoteAddr(IOAddress("fe80::abcd"));
    query2->addOption(clientid);
    query2->setIface("eth1");
    query2->setIndex(ETH1_INDEX);
    query2->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    Pkt6Ptr query3(new Pkt6(DHCPV6_SOLICIT, 1234));
    query3->setRemoteAddr(IOAddress("fe80::abcd"));
    query3->addOption(clientid);
    query3->setIface("eth1");
    query3->setIndex(ETH1_INDEX);
    query3->addOption(generateIA(D6O_IA_NA, 345, 1500, 3000));

    // Create and add an ORO option to the first 2 queries
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    ASSERT_TRUE(oro);
    oro->addValue(2345);
    query1->addOption(oro);
    query2->addOption(oro);

    // Create and add a host-name option to the first and last queries
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query1->addOption(hostname);
    query3->addOption(hostname);

    // Classify packets
    srv.classifyPacket(query1);
    srv.classifyPacket(query2);
    srv.classifyPacket(query3);

    // No packet is in the router class
    EXPECT_FALSE(query1->inClass("router"));
    EXPECT_FALSE(query2->inClass("router"));
    EXPECT_FALSE(query3->inClass("router"));

    // Process queries
    AllocEngine::ClientContext6 ctx1;
    bool drop = !srv.earlyGHRLookup(query1, ctx1);
    ASSERT_FALSE(drop);
    srv.initContext(query1, ctx1, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response1 = srv.processSolicit(ctx1);
    AllocEngine::ClientContext6 ctx2;
    drop = !srv.earlyGHRLookup(query2, ctx2);
    ASSERT_FALSE(drop);
    srv.initContext(query2, ctx2, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response2 = srv.processSolicit(ctx2);
    AllocEngine::ClientContext6 ctx3;
    drop = !srv.earlyGHRLookup(query3, ctx3);
    ASSERT_FALSE(drop);
    srv.initContext(query3, ctx3, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response3 = srv.processSolicit(ctx3);

    // Classification processing should do nothing
    OptionPtr opt1 = response1->getOption(2345);
    EXPECT_FALSE(opt1);
    OptionPtr opt2 = response2->getOption(2345);
    EXPECT_FALSE(opt2);
    OptionPtr opt3 = response3->getOption(2345);
    EXPECT_FALSE(opt3);
}

// Checks that when only-if-required classes are still evaluated
TEST_F(ClassifyTest, requiredClassification) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"require-client-classes\": [ \"router\" ], "
        "    \"interface\": \"eth1\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"router\", "
        "    \"only-if-required\": true, "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[host-name].text == 'foo'\" } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create packets with enough to select the subnet
    OptionPtr clientid = generateClientId();
    Pkt6Ptr query1(new Pkt6(DHCPV6_SOLICIT, 1234));
    query1->setRemoteAddr(IOAddress("fe80::abcd"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);
    query1->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));
    Pkt6Ptr query2(new Pkt6(DHCPV6_SOLICIT, 1234));
    query2->setRemoteAddr(IOAddress("fe80::abcd"));
    query2->addOption(clientid);
    query2->setIface("eth1");
    query2->setIndex(ETH1_INDEX);
    query2->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    Pkt6Ptr query3(new Pkt6(DHCPV6_SOLICIT, 1234));
    query3->setRemoteAddr(IOAddress("fe80::abcd"));
    query3->addOption(clientid);
    query3->setIface("eth1");
    query3->setIndex(ETH1_INDEX);
    query3->addOption(generateIA(D6O_IA_NA, 345, 1500, 3000));

    // Create and add an ORO option to the first 2 queries
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    ASSERT_TRUE(oro);
    oro->addValue(2345);
    query1->addOption(oro);
    query2->addOption(oro);

    // Create and add a host-name option to the first and last queries
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query1->addOption(hostname);
    query3->addOption(hostname);

    // Classify packets
    srv.classifyPacket(query1);
    srv.classifyPacket(query2);
    srv.classifyPacket(query3);

    // No packet is in the router class yet
    EXPECT_FALSE(query1->inClass("router"));
    EXPECT_FALSE(query2->inClass("router"));
    EXPECT_FALSE(query3->inClass("router"));

    // Process queries
    AllocEngine::ClientContext6 ctx1;
    bool drop = !srv.earlyGHRLookup(query1, ctx1);
    ASSERT_FALSE(drop);
    srv.initContext(query1, ctx1, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response1 = srv.processSolicit(ctx1);
    AllocEngine::ClientContext6 ctx2;
    drop = !srv.earlyGHRLookup(query2, ctx2);
    ASSERT_FALSE(drop);
    srv.initContext(query2, ctx2, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response2 = srv.processSolicit(ctx2);
    AllocEngine::ClientContext6 ctx3;
    drop = !srv.earlyGHRLookup(query3, ctx3);
    ASSERT_FALSE(drop);
    srv.initContext(query3, ctx3, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response3 = srv.processSolicit(ctx3);

    // Classification processing should add an ip-forwarding option
    OptionPtr opt1 = response1->getOption(2345);
    EXPECT_TRUE(opt1);

    // But only for the first query: second was not classified
    OptionPtr opt2 = response2->getOption(2345);
    EXPECT_FALSE(opt2);

    // But only for the first query: third has no ORO
    OptionPtr opt3 = response3->getOption(2345);
    EXPECT_FALSE(opt3);
}

// Checks subnet options have the priority over class options
TEST_F(ClassifyTest, subnetClassPriority) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // Subnet sets an ipv6-forwarding option in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"false\" } ] } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\","
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[1234].text == 'foo'\" } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create a packet with enough to select the subnet and go through
    // the SOLICIT processing
    Pkt6Ptr query = createSolicit();

    // Create and add an ORO option to the query
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    ASSERT_TRUE(oro);
    oro->addValue(2345);
    query->addOption(oro);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Classify the packet
    srv.classifyPacket(query);

    // The packet should be in the router class
    EXPECT_TRUE(query->inClass("router"));

    // Process the query
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv.earlyGHRLookup(query, ctx);
    ASSERT_FALSE(drop);
    srv.initContext(query, ctx,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response = srv.processSolicit(ctx);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(2345);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Classification sets the value to true/1, subnet to false/0
    // Here subnet has the priority
    EXPECT_EQ(0, opt->getUint8());
}

// Checks subnet options have the priority over global options
TEST_F(ClassifyTest, subnetGlobalPriority) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // Subnet sets an ipv6-forwarding option in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"option-data\": ["
        "    {    \"name\": \"ipv6-forwarding\", "
        "         \"data\": \"false\" } ], "
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"false\" } ] } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create a packet with enough to select the subnet and go through
    // the SOLICIT processing
    Pkt6Ptr query = createSolicit();

    // Create and add an ORO option to the query
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    ASSERT_TRUE(oro);
    oro->addValue(2345);
    query->addOption(oro);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Process the query
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv.earlyGHRLookup(query, ctx);
    ASSERT_FALSE(drop);
    srv.initContext(query, ctx,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response = srv.processSolicit(ctx);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(2345);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Global sets the value to true/1, subnet to false/0
    // Here subnet has the priority
    EXPECT_EQ(0, opt->getUint8());
}

// Checks class options have the priority over global options
TEST_F(ClassifyTest, classGlobalPriority) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // A global ipv6-forwarding option is set in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" } ],"
        "\"option-data\": ["
        "    {    \"name\": \"ipv6-forwarding\", "
        "         \"data\": \"false\" } ], "
        "\"client-classes\": [ "
        "{   \"name\": \"router\","
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"option[1234].text == 'foo'\" } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create a packet with enough to select the subnet and go through
    // the SOLICIT processing
    Pkt6Ptr query = createSolicit();

    // Create and add an ORO option to the query
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    ASSERT_TRUE(oro);
    oro->addValue(2345);
    query->addOption(oro);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Classify the packet
    srv.classifyPacket(query);

    // The packet should be in the router class
    EXPECT_TRUE(query->inClass("router"));

    // Process the query
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv.earlyGHRLookup(query, ctx);
    ASSERT_FALSE(drop);
    srv.initContext(query, ctx,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response = srv.processSolicit(ctx);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(2345);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Classification sets the value to true/1, global to false/0
    // Here class has the priority
    EXPECT_NE(0, opt->getUint8());
}

// Checks class options have the priority over global persistent options
TEST_F(ClassifyTest, classGlobalPersistency) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // Subnet sets an ipv6-forwarding option in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    // Note the persistency flag follows a "OR" semantic so to set
    // it to false (or to leave the default) has no effect.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"option-data\": ["
        "    {    \"name\": \"ipv6-forwarding\", "
        "         \"data\": \"false\", "
        "         \"always-send\": true, "
        "         \"never-send\": false } ], "
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"false\", "
        "             \"always-send\": false, "
        "             \"never-send\": false } ] } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create a packet with enough to select the subnet and go through
    // the SOLICIT processing
    Pkt6Ptr query = createSolicit();

    // Do not add an ORO.
    OptionPtr oro = query->getOption(D6O_ORO);
    EXPECT_FALSE(oro);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Process the query
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv.earlyGHRLookup(query, ctx);
    ASSERT_FALSE(drop);
    srv.initContext(query, ctx,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response = srv.processSolicit(ctx);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(2345);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Global sets the value to true/1, subnet to false/0
    // Here subnet has the priority
    EXPECT_EQ(0, opt->getUint8());
}

// Checks class never-send options have the priority over everything else.
TEST_F(ClassifyTest, classNeverSend) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // Subnet sets an ipv6-forwarding option in the response.
    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    // Note the cancellation flag follows a "OR" semantic so to set
    // it to false (or to leave the default) has no effect.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"option-data\": ["
        "    {    \"name\": \"ipv6-forwarding\", "
        "         \"data\": \"false\", "
        "         \"always-send\": true, "
        "         \"never-send\": false } ], "
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"always-send\": false, "
        "             \"never-send\": true } ] } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create a packet with enough to select the subnet and go through
    // the SOLICIT processing
    Pkt6Ptr query = createSolicit();

    // Do not add an ORO.
    OptionPtr oro = query->getOption(D6O_ORO);
    EXPECT_FALSE(oro);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Process the query
    AllocEngine::ClientContext6 ctx;
    bool drop = !srv.earlyGHRLookup(query, ctx);
    ASSERT_FALSE(drop);
    srv.initContext(query, ctx,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response = srv.processSolicit(ctx);

    // Processing should not add an ip-forwarding option
    EXPECT_FALSE(response->getOption(2345));
}

// Checks if the client-class field is indeed used for subnet selection.
// Note that packet classification is already checked in ClassifyTest
// .*Classification above.
TEST_F(ClassifyTest, clientClassifySubnet) {

    // This test configures 2 subnets. We actually only need the
    // first one, but since there's still this ugly hack that picks
    // the pool if there is only one, we must use more than one
    // subnet. That ugly hack will be removed in #3242, currently
    // under review.

    // The second subnet does not play any role here. The client's
    // IP address belongs to the first subnet, so only that first
    // subnet is being tested.
    std::string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " {  \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"client-class\": \"foo\" "
        " }, "
        " {  \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"client-class\": \"xyzzy\" "
        " } "
        "],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    Pkt6Ptr sol = createSolicit("2001:db8:1::3");

    // This discover does not belong to foo class, so it will not
    // be serviced
    bool drop = false;
    EXPECT_FALSE(srv_.selectSubnet(sol, drop));
    EXPECT_FALSE(drop);

    // Let's add the packet to bar class and try again.
    sol->addClass("bar");

    // Still not supported, because it belongs to wrong class.
    EXPECT_FALSE(srv_.selectSubnet(sol, drop));
    EXPECT_FALSE(drop);

    // Let's add it to matching class.
    sol->addClass("foo");

    // This time it should work
    EXPECT_TRUE(srv_.selectSubnet(sol, drop));
    EXPECT_FALSE(drop);
}

// Checks if the client-class field is indeed used for pool selection.
TEST_F(ClassifyTest, clientClassifyPool) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // This test configures 2 pools.
    // The second pool does not play any role here. The client's
    // IP address belongs to the first pool, so only that first
    // pool is being tested.
    std::string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"client-classes\": [ "
        " { "
        "    \"name\": \"foo\" "
        " }, "
        " { "
        "    \"name\": \"bar\" "
        " } "
        "], "
        "\"subnet6\": [ "
        " {  \"pools\": [ "
        "    { "
        "       \"pool\": \"2001:db8:1::/64\", "
        "       \"client-class\": \"foo\" "
        "    }, "
        "    { "
        "       \"pool\": \"2001:db8:2::/64\", "
        "       \"client-class\": \"xyzzy\" "
        "    } "
        "   ], "
        "   \"subnet\": \"2001:db8::/40\" "
        " } "
        "], "
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    Pkt6Ptr query1 = createSolicit("2001:db8:1::3");
    Pkt6Ptr query2 = createSolicit("2001:db8:1::3");
    Pkt6Ptr query3 = createSolicit("2001:db8:1::3");

    // This discover does not belong to foo class, so it will not
    // be serviced
    srv.classifyPacket(query1);
    AllocEngine::ClientContext6 ctx1;
    bool drop = !srv.earlyGHRLookup(query1, ctx1);
    ASSERT_FALSE(drop);
    srv.initContext(query1, ctx1,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response1 = srv.processSolicit(ctx1);
    ASSERT_TRUE(response1);
    OptionPtr ia_na1 = response1->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia_na1);
    EXPECT_TRUE(ia_na1->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(ia_na1->getOption(D6O_IAADDR));

    // Let's add the packet to bar class and try again.
    query2->addClass("bar");
    // Still not supported, because it belongs to wrong class.
    srv.classifyPacket(query2);
    AllocEngine::ClientContext6 ctx2;
    drop = !srv.earlyGHRLookup(query2, ctx2);
    ASSERT_FALSE(drop);
    srv.initContext(query2, ctx2,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response2 = srv.processSolicit(ctx2);
    ASSERT_TRUE(response2);
    OptionPtr ia_na2 = response2->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia_na2);
    EXPECT_TRUE(ia_na2->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(ia_na2->getOption(D6O_IAADDR));

    // Let's add it to matching class.
    query3->addClass("foo");
    // This time it should work
    srv.classifyPacket(query3);
    AllocEngine::ClientContext6 ctx3;
    drop = !srv.earlyGHRLookup(query3, ctx3);
    ASSERT_FALSE(drop);
    srv.initContext(query3, ctx3,  drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response3 = srv.processSolicit(ctx3);
    ASSERT_TRUE(response3);
    OptionPtr ia_na3 = response3->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia_na3);
    EXPECT_FALSE(ia_na3->getOption(D6O_STATUS_CODE));
    EXPECT_TRUE(ia_na3->getOption(D6O_IAADDR));
}

// Checks if the [UN]KNOWN built-in classes is indeed used for pool selection.
TEST_F(ClassifyTest, clientClassifyPoolKnown) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // This test configures 2 pools.
    // The first one requires reservation, the second does the opposite.
    std::string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " {  \"pools\": [ "
        "    { "
        "       \"pool\": \"2001:db8:1::/64\", "
        "       \"client-class\": \"KNOWN\" "
        "    }, "
        "    { "
        "       \"pool\": \"2001:db8:2::/64\", "
        "       \"client-class\": \"UNKNOWN\" "
        "    } "
        "   ], "
        "   \"subnet\": \"2001:db8::/40\", "
        "   \"reservations\": [ "
        "      { \"duid\": \"01:02:03:04\", \"hostname\": \"foo\" } ] "
        " } "
        "], "
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(configure(config));

    OptionPtr clientid1 = generateClientId();
    Pkt6Ptr query1 = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    query1->setRemoteAddr(IOAddress("2001:db8:1::3"));
    query1->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    query1->addOption(clientid1);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);

    // First pool requires reservation so the second will be used
    srv.classifyPacket(query1);
    AllocEngine::ClientContext6 ctx1;
    bool drop = !srv.earlyGHRLookup(query1, ctx1);
    ASSERT_FALSE(drop);
    srv.initContext(query1, ctx1, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response1 = srv.processSolicit(ctx1);
    ASSERT_TRUE(response1);
    OptionPtr ia_na1 = response1->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia_na1);
    EXPECT_FALSE(ia_na1->getOption(D6O_STATUS_CODE));
    OptionPtr iaaddr1 = ia_na1->getOption(D6O_IAADDR);
    ASSERT_TRUE(iaaddr1);
    boost::shared_ptr<Option6IAAddr> addr1 =
        boost::dynamic_pointer_cast<Option6IAAddr>(iaaddr1);
    ASSERT_TRUE(addr1);
    EXPECT_EQ("2001:db8:2::", addr1->getAddress().toText());

    // Try with DUID 01:02:03:04
    uint8_t duid[] = { 0x01, 0x02, 0x03, 0x04 };
    OptionBuffer buf(duid, duid + sizeof(duid));
    OptionPtr clientid2(new Option(Option::V6, D6O_CLIENTID, buf));
    Pkt6Ptr query2 = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 2345));
    query2->setRemoteAddr(IOAddress("2001:db8:1::3"));
    query2->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    query2->addOption(clientid2);
    query2->setIface("eth1");
    query2->setIndex(ETH1_INDEX);

    // Now the first pool will be used
    srv.classifyPacket(query2);
    AllocEngine::ClientContext6 ctx2;
    drop = !srv.earlyGHRLookup(query2, ctx2);
    ASSERT_FALSE(drop);
    srv.initContext(query2, ctx2, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response2 = srv.processSolicit(ctx2);
    ASSERT_TRUE(response2);
    OptionPtr ia_na2 = response2->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia_na2);
    EXPECT_FALSE(ia_na2->getOption(D6O_STATUS_CODE));
    OptionPtr iaaddr2 = ia_na2->getOption(D6O_IAADDR);
    ASSERT_TRUE(iaaddr2);
    boost::shared_ptr<Option6IAAddr> addr2 =
        boost::dynamic_pointer_cast<Option6IAAddr>(iaaddr2);
    ASSERT_TRUE(addr2);
    EXPECT_EQ("2001:db8:1::", addr2->getAddress().toText());
}

// Tests whether a packet with custom vendor-class (not erouter or docsis)
// is classified properly.
TEST_F(ClassifyTest, vendorClientClassification2) {
    NakedDhcpv6Srv srv(0);

    // Let's create a SOLICIT.
    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("2001:db8:1::3"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Now let's add a vendor-class with id=1234 and content "foo"
    OptionVendorClassPtr vendor_class(new OptionVendorClass(Option::V6, 1234));
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "foo";
    vendor_class->addTuple(tuple);
    sol->addOption(vendor_class);

    // Now the server classifies the packet.
    srv.classifyPacket(sol);

    // The packet should now belong to VENDOR_CLASS_foo.
    EXPECT_TRUE(sol->inClass(srv.VENDOR_CLASS_PREFIX + "foo"));

    // It should not belong to "foo"
    EXPECT_FALSE(sol->inClass("foo"));
}

// Checks if relay IP address specified in the relay-info structure can be
// used together with client-classification.
TEST_F(ClassifyTest, relayOverrideAndClientClass) {

    // This test configures 2 subnets. They both are on the same link, so they
    // have the same relay-ip address. Furthermore, the first subnet is
    // reserved for clients that belong to class "foo".
    std::string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " {  \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"client-class\": \"foo\", "
        "    \"relay\": { "
        "        \"ip-address\": \"2001:db8:3::1\""
        "    }"
        " }, "
        " {  \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"relay\": { "
        "        \"ip-address\": \"2001:db8:3::1\""
        "    }"
        " } "
        "],"
        "\"valid-lifetime\": 4000 }";

    // Use this config to set up the server
    ASSERT_NO_THROW(configure(config));

    // Let's get the subnet configuration objects
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());

    // Let's get them for easy reference
    Subnet6Ptr subnet1 = *subnets->begin();
    Subnet6Ptr subnet2 = *std::next(subnets->begin());
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    Pkt6Ptr sol = createSolicit("2001:db8:1::3");

    // Now pretend the packet came via one relay.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("2001:db8:3::1");
    relay.peeraddr_ = IOAddress("fe80::1");

    sol->relay_info_.push_back(relay);

    // This packet does not belong to class foo, so it should be rejected in
    // subnet[0], even though the relay-ip matches. It should be accepted in
    // subnet[1], because the subnet matches and there are no class
    // requirements.
    bool drop = false;
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(sol, drop));
    EXPECT_FALSE(drop);

    // Now let's add this packet to class foo and recheck. This time it should
    // be accepted in the first subnet, because both class and relay-ip match.
    sol->addClass("foo");
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(sol, drop));
    EXPECT_FALSE(drop);
}

// This test checks that it is possible to specify static reservations for
// client classes.
TEST_F(ClassifyTest, clientClassesInHostReservations) {
    Dhcp6Client client;
    // Initially use a DUID for which there are no reservations. As a result,
    // the client should be assigned a single class "router".
    client.setDUID("01:02:03:05");
    client.setInterface("eth1");
    client.requestAddress();
    // Request all options we may potentially get. Otherwise, the server will
    // not return them, even when the client is assigned to the classes for
    // which these options should be sent.
    client.requestOption(2345);
    client.requestOption(D6O_NAME_SERVERS);
    client.requestOption(D6O_NIS_SERVERS);

    ASSERT_NO_THROW(configure(CONFIGS[0], *client.getServer()));

    // Adding this option to the client's message will cause the client to
    // belong to the 'router' class.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    client.addExtraOption(hostname);

    // Send a message to the server.
    ASSERT_NO_THROW(client.doSolicit(true));

    // IP forwarding should be present, but DNS and NIS servers should not.
    ASSERT_NO_FATAL_FAILURE(verifyConfig0Options(client.config_));

    // Modify the DUID of our client to the one for which class reservations
    // have been made.
    client.setDUID("01:02:03:04");
    ASSERT_NO_THROW(client.doSolicit(true));

    // This time, the client should obtain options from all three classes.
    ASSERT_NO_FATAL_FAILURE(verifyConfig0Options(client.config_, 1,
                                                 "2001:db8:1::50",
                                                 "2001:db8:1::100"));

    // This should also work for Request case.
    ASSERT_NO_THROW(client.doSARR());
    ASSERT_NO_FATAL_FAILURE(verifyConfig0Options(client.config_, 1,
                                                 "2001:db8:1::50",
                                                 "2001:db8:1::100"));

    // Renew case.
    ASSERT_NO_THROW(client.doRenew());
    ASSERT_NO_FATAL_FAILURE(verifyConfig0Options(client.config_, 1,
                                                 "2001:db8:1::50",
                                                 "2001:db8:1::100"));

    // Rebind case.
    ASSERT_NO_THROW(client.doRebind());
    ASSERT_NO_FATAL_FAILURE(verifyConfig0Options(client.config_, 1,
                                                 "2001:db8:1::50",
                                                 "2001:db8:1::100"));

    // Confirm case. This must be before Information-request because the
    // client must have an address to confirm from one of the transactions
    // involving address assignment, i.e. Request, Renew or Rebind.
    ASSERT_NO_THROW(client.doConfirm());
    ASSERT_NO_FATAL_FAILURE(verifyConfig0Options(client.config_, 1,
                                                 "2001:db8:1::50",
                                                 "2001:db8:1::100"));

    // Information-request case.
    ASSERT_NO_THROW(client.doInfRequest());
    ASSERT_NO_FATAL_FAILURE(verifyConfig0Options(client.config_, 1,
                                                 "2001:db8:1::50",
                                                 "2001:db8:1::100"));
}

// Check classification using membership expressions.
TEST_F(ClassifyTest, member) {
    IfaceMgrTestConfig test_config(true);

    NakedDhcpv6Srv srv(0);

    // The router class matches incoming packets with foo in a host-name
    // option (code 1234) and sets an ipv6-forwarding option in the response.
    std::string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ] }, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000, "
        "\"option-def\": [ "
        "{   \"name\": \"host-name\","
        "    \"code\": 1234,"
        "    \"type\": \"string\" },"
        "{   \"name\": \"ipv6-forwarding\","
        "    \"code\": 2345,"
        "    \"type\": \"boolean\" }],"
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\" } ],"
        "\"client-classes\": [ "
        "{   \"name\": \"not-foo\", "
        "    \"test\": \"not (option[host-name].text == 'foo')\""
        "},"
        "{   \"name\": \"foo\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"true\" } ], "
        "    \"test\": \"not member('not-foo')\""
        "},"
        "{   \"name\": \"bar\", "
        "    \"test\": \"option[host-name].text == 'bar'\""
        "},"
        "{   \"name\": \"baz\", "
        "    \"test\": \"option[host-name].text == 'baz'\""
        "},"
        "{   \"name\": \"barz\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"false\" } ], "
        "    \"test\": \"member('bar') or member('baz')\" } ] }";

    ASSERT_NO_THROW(configure(config));

    // Create packets with enough to select the subnet
    OptionPtr clientid = generateClientId();
    Pkt6Ptr query1(new Pkt6(DHCPV6_SOLICIT, 1234));
    query1->setRemoteAddr(IOAddress("fe80::abcd"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->setIndex(ETH1_INDEX);
    query1->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));
    Pkt6Ptr query2(new Pkt6(DHCPV6_SOLICIT, 1234));
    query2->setRemoteAddr(IOAddress("fe80::abcd"));
    query2->addOption(clientid);
    query2->setIface("eth1");
    query2->setIndex(ETH1_INDEX);
    query2->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    Pkt6Ptr query3(new Pkt6(DHCPV6_SOLICIT, 1234));
    query3->setRemoteAddr(IOAddress("fe80::abcd"));
    query3->addOption(clientid);
    query3->setIface("eth1");
    query3->setIndex(ETH1_INDEX);
    query3->addOption(generateIA(D6O_IA_NA, 345, 1500, 3000));

    // Create and add an ORO option to queries
    OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6, D6O_ORO));
    ASSERT_TRUE(oro);
    oro->addValue(2345);
    query1->addOption(oro);
    query2->addOption(oro);
    query3->addOption(oro);

    // Create and add a host-name option to the first and last queries
    OptionStringPtr hostname1(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname1);
    query1->addOption(hostname1);
    OptionStringPtr hostname3(new OptionString(Option::V6, 1234, "baz"));
    ASSERT_TRUE(hostname3);
    query3->addOption(hostname3);

    // Classify packets
    srv.classifyPacket(query1);
    srv.classifyPacket(query2);
    srv.classifyPacket(query3);

    // Check classes
    EXPECT_FALSE(query1->inClass("not-foo"));
    EXPECT_TRUE(query1->inClass("foo"));
    EXPECT_FALSE(query1->inClass("bar"));
    EXPECT_FALSE(query1->inClass("baz"));
    EXPECT_FALSE(query1->inClass("barz"));

    EXPECT_TRUE(query2->inClass("not-foo"));
    EXPECT_FALSE(query2->inClass("foo"));
    EXPECT_FALSE(query2->inClass("bar"));
    EXPECT_FALSE(query2->inClass("baz"));
    EXPECT_FALSE(query2->inClass("barz"));

    EXPECT_TRUE(query3->inClass("not-foo"));
    EXPECT_FALSE(query3->inClass("foo"));
    EXPECT_FALSE(query3->inClass("bar"));
    EXPECT_TRUE(query3->inClass("baz"));
    EXPECT_TRUE(query3->inClass("barz"));

    // Process queries
    AllocEngine::ClientContext6 ctx1;
    bool drop = !srv.earlyGHRLookup(query1, ctx1);
    ASSERT_FALSE(drop);
    srv.initContext(query1, ctx1, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response1 = srv.processSolicit(ctx1);
    AllocEngine::ClientContext6 ctx2;
    drop = !srv.earlyGHRLookup(query2, ctx2);
    ASSERT_FALSE(drop);
    srv.initContext(query2, ctx2, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response2 = srv.processSolicit(ctx2);
    AllocEngine::ClientContext6 ctx3;
    drop = !srv.earlyGHRLookup(query3, ctx3);
    ASSERT_FALSE(drop);
    srv.initContext(query3, ctx3, drop);
    ASSERT_FALSE(drop);
    Pkt6Ptr response3 = srv.processSolicit(ctx3);

    // Classification processing should add an ip-forwarding option
    OptionPtr opt1 = response1->getOption(2345);
    EXPECT_TRUE(opt1);
    OptionCustomPtr ipf1 =
        boost::dynamic_pointer_cast<OptionCustom>(opt1);
    ASSERT_TRUE(ipf1);
    EXPECT_TRUE(ipf1->readBoolean());

    // But not the second query which was not classified
    OptionPtr opt2 = response2->getOption(2345);
    EXPECT_FALSE(opt2);

    // The third has the option but with another value
    OptionPtr opt3 = response3->getOption(2345);
    EXPECT_TRUE(opt3);
    OptionCustomPtr ipf3 =
        boost::dynamic_pointer_cast<OptionCustom>(opt3);
    ASSERT_TRUE(ipf3);
    EXPECT_FALSE(ipf3->readBoolean());
}

// This test checks the precedence order in required evaluation.
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedenceNone) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"interface\": \"eth1\","
        "    \"subnet6\": [ { "
        "        \"subnet\": \"2001:db8:1::/64\","
        "        \"id\": 1,"
        "        \"pools\": [ { "
        "            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\""
        "        } ]"
        "    } ]"
        "} ],"
        "\"valid-lifetime\": 600"
        "}";

    // Create a client requesting dns-servers option
    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
    client.requestOption(D6O_NAME_SERVERS);

    // Load the config and perform a SARR
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    EXPECT_EQ(1, client.getLeaseNum());
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Check dns-servers option
    OptionPtr opt = resp->getOption(D6O_NAME_SERVERS);
    EXPECT_FALSE(opt);
}

// This test checks the precedence order in required evaluation.
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedencePool) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"interface\": \"eth1\","
        "    \"subnet6\": [ { "
        "        \"subnet\": \"2001:db8:1::/64\","
        "        \"id\": 1,"
        "        \"pools\": [ { "
        "            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\","
        "            \"require-client-classes\": [ \"for-pool\" ]"
        "        } ]"
        "    } ]"
        "} ],"
        "\"valid-lifetime\": 600"
        "}";

    // Create a client requesting dns-servers option
    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
    client.requestOption(D6O_NAME_SERVERS);

    // Load the config and perform a SARR
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    EXPECT_EQ(1, client.getLeaseNum());
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Check dns-servers option
    OptionPtr opt = resp->getOption(D6O_NAME_SERVERS);
    ASSERT_TRUE(opt);
    Option6AddrLstPtr servers =
        boost::dynamic_pointer_cast<Option6AddrLst>(opt);
    ASSERT_TRUE(servers);
    auto addrs = servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("2001:db8:1::1", addrs[0].toText());
}

// This test checks the precedence order in required evaluation.
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedenceSubnet) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"interface\": \"eth1\","
        "    \"subnet6\": [ { "
        "        \"subnet\": \"2001:db8:1::/64\","
        "        \"id\": 1,"
        "        \"require-client-classes\": [ \"for-subnet\" ],"
        "        \"pools\": [ { "
        "            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\","
        "            \"require-client-classes\": [ \"for-pool\" ]"
        "        } ]"
        "    } ]"
        "} ],"
        "\"valid-lifetime\": 600"
        "}";

    // Create a client requesting dns-servers option
    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
    client.requestOption(D6O_NAME_SERVERS);

    // Load the config and perform a SARR
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    EXPECT_EQ(1, client.getLeaseNum());
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Check dns-servers option
    OptionPtr opt = resp->getOption(D6O_NAME_SERVERS);
    ASSERT_TRUE(opt);
    Option6AddrLstPtr servers =
        boost::dynamic_pointer_cast<Option6AddrLst>(opt);
    ASSERT_TRUE(servers);
    auto addrs = servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("2001:db8:1::2", addrs[0].toText());
}

// This test checks the precedence order in required evaluation.
// This order is: shared-network > subnet > pools
TEST_F(ClassifyTest, precedenceNetwork) {
    std::string config =
        "{"
        "\"interfaces-config\": {"
        "   \"interfaces\": [ \"*\" ]"
        "},"
        "\"client-classes\": ["
        "    {"
        "       \"name\": \"all\","
        "       \"test\": \"'' == ''\""
        "    },"
        "    {"
        "       \"name\": \"for-pool\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-subnet\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::2\""
        "       } ]"
        "    },"
        "    {"
        "       \"name\": \"for-network\","
        "       \"test\": \"member('all')\","
        "       \"only-if-required\": true,"
        "       \"option-data\": [ {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::3\""
        "       } ]"
        "    }"
        "],"
        "\"shared-networks\": [ {"
        "    \"name\": \"frog\","
        "    \"interface\": \"eth1\","
        "    \"require-client-classes\": [ \"for-network\" ],"
        "    \"subnet6\": [ { "
        "        \"subnet\": \"2001:db8:1::/64\","
        "        \"id\": 1,"
        "        \"require-client-classes\": [ \"for-subnet\" ],"
        "        \"pools\": [ { "
        "            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\","
        "            \"require-client-classes\": [ \"for-pool\" ]"
        "        } ]"
        "    } ]"
        "} ],"
        "\"valid-lifetime\": 600"
        "}";

    // Create a client requesting dns-servers option
    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
    client.requestOption(D6O_NAME_SERVERS);

    // Load the config and perform a SARR
    configure(config, *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    EXPECT_EQ(1, client.getLeaseNum());
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // Check dns-servers option
    OptionPtr opt = resp->getOption(D6O_NAME_SERVERS);
    ASSERT_TRUE(opt);
    Option6AddrLstPtr servers =
        boost::dynamic_pointer_cast<Option6AddrLst>(opt);
    ASSERT_TRUE(servers);
    auto addrs = servers->getAddresses();
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("2001:db8:1::3", addrs[0].toText());
}

// This test checks the complex membership from HA with server1 telephone.
TEST_F(ClassifyTest, server1Telephone) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestAddress(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    client.addExtraOption(hostname);

    // Add server1
    client.addClass("server1");

    // Load the config and perform a SARR
    configure(CONFIGS[1], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the first pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::", lease_client.addr_.toText());
}

// This test checks the complex membership from HA with server1 computer.
TEST_F(ClassifyTest, server1Computer) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestAddress(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "bar"));
    client.addExtraOption(hostname);

    // Add server1
    client.addClass("server1");

    // Load the config and perform a SARR
    configure(CONFIGS[1], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the second pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:2::", lease_client.addr_.toText());
}

// This test checks the complex membership from HA with server2 telephone.
TEST_F(ClassifyTest, server2Telephone) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestAddress(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    client.addExtraOption(hostname);

    // Add server2
    client.addClass("server2");

    // Load the config and perform a SARR
    configure(CONFIGS[1], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the third pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:3::", lease_client.addr_.toText());
}

// This test checks the complex membership from HA with server2 computer.
TEST_F(ClassifyTest, server2Computer) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestAddress(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "bar"));
    client.addExtraOption(hostname);

    // Add server2
    client.addClass("server2");

    // Load the config and perform a SARR
    configure(CONFIGS[1], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The address is from the forth pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:4::", lease_client.addr_.toText());
}

// This test checks the complex membership from HA with server1 telephone
// with prefixes.
TEST_F(ClassifyTest, pDserver1Telephone) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestPrefix(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    client.addExtraOption(hostname);

    // Add server1
    client.addClass("server1");

    // Load the config and perform a SARR
    configure(CONFIGS[2], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The prefix is from the first pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1::", lease_client.addr_.toText());
}

// This test checks the complex membership from HA with server1 computer
// with prefix.
TEST_F(ClassifyTest, pDserver1Computer) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestPrefix(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "bar"));
    client.addExtraOption(hostname);

    // Add server1
    client.addClass("server1");

    // Load the config and perform a SARR
    configure(CONFIGS[2], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The prefix is from the second pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:2::", lease_client.addr_.toText());
}

// This test checks the complex membership from HA with server2 telephone
// with prefixes.
TEST_F(ClassifyTest, pDserver2Telephone) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestPrefix(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    client.addExtraOption(hostname);

    // Add server2
    client.addClass("server2");

    // Load the config and perform a SARR
    configure(CONFIGS[2], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The prefix is from the third pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:3::", lease_client.addr_.toText());
}

// This test checks the complex membership from HA with server2 computer
// with prefix.
TEST_F(ClassifyTest, pDserver2Computer) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");
    ASSERT_NO_THROW(client.requestPrefix(0xabca0));

    // Add option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "bar"));
    client.addExtraOption(hostname);

    // Add server2
    client.addClass("server2");

    // Load the config and perform a SARR
    configure(CONFIGS[2], *client.getServer());
    ASSERT_NO_THROW(client.doSARR());

    // Check response
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // The prefix is from the forth pool.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:4::", lease_client.addr_.toText());
}

// This test checks the handling for the DROP special class.
TEST_F(ClassifyTest, dropClass) {
    Dhcp6Client client;
    client.setDUID("01:02:03:05");
    client.setInterface("eth1");
    client.requestAddress();

    // Configure DHCP server.
    ASSERT_NO_THROW(configure(CONFIGS[3], *client.getServer()));

    // Send a message to the server.
    ASSERT_NO_THROW(client.doSolicit(true));

    // No option: no drop.
    EXPECT_TRUE(client.getContext().response_);

    // Retry with an option matching the DROP class.
    Dhcp6Client client2;

    // Add the host-name option.
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    client2.addExtraOption(hostname);

    // Send a message to the server.
    ASSERT_NO_THROW(client2.doSolicit(true));

    // Option, dropped.
    EXPECT_FALSE(client2.getContext().response_);

    // There should also be pkt6-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt6-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

// This test checks the handling for the DROP special class at the host
// reservation classification point with KNOWN / UNKNOWN.
TEST_F(ClassifyTest, dropClassUnknown) {
    Dhcp6Client client;
    client.setDUID("01:02:03:04");
    client.setInterface("eth1");
    client.requestAddress();

    // Configure DHCP server.
    ASSERT_NO_THROW(configure(CONFIGS[4], *client.getServer()));

    // Send a message to the server.
    ASSERT_NO_THROW(client.doSolicit(true));

    // Reservation match: no drop.
    EXPECT_TRUE(client.getContext().response_);

    // Retry with an option matching the DROP class.
    Dhcp6Client client2;

    // Retry with another DUID.
    client2.setDUID("01:02:03:05");

    // Send a message to the server.
    ASSERT_NO_THROW(client2.doSolicit(true));

    // No reservation, dropped.
    EXPECT_FALSE(client2.getContext().response_);

    // There should also be pkt6-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt6-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

// This test checks the handling for the DROP special class at the host
// reservation classification point with a reserved class.
TEST_F(ClassifyTest, dropClassReservedClass) {
    Dhcp6Client client;
    client.setDUID("01:02:03:04");
    client.setInterface("eth1");
    client.requestAddress();

    // Configure DHCP server.
    ASSERT_NO_THROW(configure(CONFIGS[5], *client.getServer()));

    // Send a message to the server.
    ASSERT_NO_THROW(client.doSolicit(true));

    // Reservation match: no drop.
    EXPECT_TRUE(client.getContext().response_);

    // Retry with an option matching the DROP class.
    Dhcp6Client client2;

    // Retry with another DUID.
    client2.setDUID("01:02:03:05");

    // Send a message to the server.
    ASSERT_NO_THROW(client2.doSolicit(true));

    // No reservation, dropped.
    EXPECT_FALSE(client2.getContext().response_);

    // There should also be pkt6-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt6-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);
}

// This test checks the early global reservations lookup for selecting
// a guarded subnet.
TEST_F(ClassifyTest, earlySubnet) {
    Dhcp6Client client;
    client.setDUID("01:02:03:04");
    client.setInterface("eth1");
    client.requestAddress();

    // Configure DHCP server.
    ASSERT_NO_THROW(configure(CONFIGS[6], *client.getServer()));

    // Send a message to the server.
    ASSERT_NO_THROW(client.doSolicit(true));

    // Check response.
    Pkt6Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    OptionPtr ia_na = resp->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia_na);
    EXPECT_FALSE(ia_na->getOption(D6O_STATUS_CODE));
    OptionPtr iaaddr = ia_na->getOption(D6O_IAADDR);
    ASSERT_TRUE(iaaddr);
    boost::shared_ptr<Option6IAAddr> addr =
        boost::dynamic_pointer_cast<Option6IAAddr>(iaaddr);
    ASSERT_TRUE(addr);
    EXPECT_EQ("2001:db8:1::", addr->getAddress().toText());

    // Retry with another DUID.
    Dhcp6Client client2;
    client2.setDUID("01:02:03:05");
    client2.setInterface("eth1");
    client2.requestAddress();

    ASSERT_NO_THROW(client2.doSolicit(true));

    // Check response.
    resp = client2.getContext().response_;
    ASSERT_TRUE(resp);
    ia_na = resp->getOption(D6O_IA_NA);
    ASSERT_TRUE(ia_na);
    EXPECT_FALSE(ia_na->getOption(D6O_STATUS_CODE));
    iaaddr = ia_na->getOption(D6O_IAADDR);
    ASSERT_TRUE(iaaddr);
    addr = boost::dynamic_pointer_cast<Option6IAAddr>(iaaddr);
    ASSERT_TRUE(addr);
    EXPECT_EQ("2001:db8:2::", addr->getAddress().toText());
}

// This test checks the early global reservations lookup for dropping.
TEST_F(ClassifyTest, earlyDrop) {
    Dhcp6Client client;
    client.setDUID("01:02:03:04");
    client.setInterface("eth1");
    client.requestAddress();

    // Configure DHCP server.
    ASSERT_NO_THROW(configure(CONFIGS[7], *client.getServer()));

    // Send a message to the server.
    ASSERT_NO_THROW(client.doSolicit(true));

    // Match the reservation so dropped.
    EXPECT_FALSE(client.getContext().response_);

    // There should also be pkt6-receive-drop stat bumped up.
    stats::StatsMgr& mgr = stats::StatsMgr::instance();
    stats::ObservationPtr drop_stat = mgr.getObservation("pkt6-receive-drop");

    // This statistic must be present and must be set to 1.
    ASSERT_TRUE(drop_stat);
    EXPECT_EQ(1, drop_stat->getInteger().first);

    // Retry with another DUID.
    Dhcp6Client client2;
    client2.setDUID("01:02:03:05");
    client2.setInterface("eth1");
    client2.requestAddress();

    ASSERT_NO_THROW(client2.doSolicit(true));

    // Not matching so not dropped.
    EXPECT_TRUE(client2.getContext().response_);
}

} // end of anonymous namespace
