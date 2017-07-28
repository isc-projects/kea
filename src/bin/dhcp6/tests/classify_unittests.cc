// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
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
        "    \"test\": \"option[host-name].text == 'foo'\" } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create packets with enough to select the subnet
    OptionPtr clientid = generateClientId();
    Pkt6Ptr query1(new Pkt6(DHCPV6_SOLICIT, 1234));
    query1->setRemoteAddr(IOAddress("fe80::abcd"));
    query1->addOption(clientid);
    query1->setIface("eth1");
    query1->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));
    Pkt6Ptr query2(new Pkt6(DHCPV6_SOLICIT, 1234));
    query2->setRemoteAddr(IOAddress("fe80::abcd"));
    query2->addOption(clientid);
    query2->setIface("eth1");
    query2->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    Pkt6Ptr query3(new Pkt6(DHCPV6_SOLICIT, 1234));
    query3->setRemoteAddr(IOAddress("fe80::abcd"));
    query3->addOption(clientid);
    query3->setIface("eth1");
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

    // Packets with the exception of the second should be in the router class
    EXPECT_TRUE(query1->inClass("router"));
    EXPECT_FALSE(query2->inClass("router"));
    EXPECT_TRUE(query3->inClass("router"));

    // Process queries
    Pkt6Ptr response1 = srv.processSolicit(query1);
    Pkt6Ptr response2 = srv.processSolicit(query2);
    Pkt6Ptr response3 = srv.processSolicit(query3);

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
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    query->setRemoteAddr(IOAddress("fe80::abcd"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));

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
    Pkt6Ptr response = srv.processSolicit(query);

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
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    query->setRemoteAddr(IOAddress("fe80::abcd"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));

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
    Pkt6Ptr response = srv.processSolicit(query);

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
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    query->setRemoteAddr(IOAddress("fe80::abcd"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));

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
    Pkt6Ptr response = srv.processSolicit(query);

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
        "         \"always-send\": true } ], "
        "\"subnet6\": [ "
        "{   \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"interface\": \"eth1\", "
        "    \"option-data\": ["
        "        {    \"name\": \"ipv6-forwarding\", "
        "             \"data\": \"false\", "
        "             \"always-send\": false } ] } ] }";
    ASSERT_NO_THROW(configure(config));

    // Create a packet with enough to select the subnet and go through
    // the SOLICIT processing
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    query->setRemoteAddr(IOAddress("fe80::abcd"));
    OptionPtr clientid = generateClientId();
    query->addOption(clientid);
    query->setIface("eth1");
    query->addOption(generateIA(D6O_IA_NA, 123, 1500, 3000));

    // Do not add an ORO.
    OptionPtr oro = query->getOption(D6O_ORO);
    EXPECT_FALSE(oro);

    // Create and add a host-name option to the query
    OptionStringPtr hostname(new OptionString(Option::V6, 1234, "foo"));
    ASSERT_TRUE(hostname);
    query->addOption(hostname);

    // Process the query
    Pkt6Ptr response = srv.processSolicit(query);

    // Processing should add an ip-forwarding option
    OptionPtr opt = response->getOption(2345);
    ASSERT_TRUE(opt);
    ASSERT_GT(opt->len(), opt->getHeaderLen());
    // Global sets the value to true/1, subnet to false/0
    // Here subnet has the priority
    EXPECT_EQ(0, opt->getUint8());
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

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("2001:db8:1::3"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // This discover does not belong to foo class, so it will not
    // be serviced
    EXPECT_FALSE(srv_.selectSubnet(sol));

    // Let's add the packet to bar class and try again.
    sol->addClass("bar");

    // Still not supported, because it belongs to wrong class.
    EXPECT_FALSE(srv_.selectSubnet(sol));

    // Let's add it to matching class.
    sol->addClass("foo");

    // This time it should work
    EXPECT_TRUE(srv_.selectSubnet(sol));
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
    Subnet6Ptr subnet1 = (*subnets)[0];
    Subnet6Ptr subnet2 = (*subnets)[1];
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    Pkt6Ptr sol = Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->setRemoteAddr(IOAddress("2001:db8:1::3"));
    sol->addOption(generateIA(D6O_IA_NA, 234, 1500, 3000));
    OptionPtr clientid = generateClientId();
    sol->addOption(clientid);

    // Now pretend the packet came via one relay.
    Pkt6::RelayInfo relay;
    relay.linkaddr_ = IOAddress("2001:db8:3::1");
    relay.peeraddr_ = IOAddress("fe80::1");

    sol->relay_info_.push_back(relay);

    // This packet does not belong to class foo, so it should be rejected in
    // subnet[0], even though the relay-ip matches. It should be accepted in
    // subnet[1], because the subnet matches and there are no class
    // requirements.
    EXPECT_TRUE(subnet2 == srv_.selectSubnet(sol));

    // Now let's add this packet to class foo and recheck. This time it should
    // be accepted in the first subnet, because both class and relay-ip match.
    sol->addClass("foo");
    EXPECT_TRUE(subnet1 == srv_.selectSubnet(sol));
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


} // end of anonymous namespace
