// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <testutils/gtest_utils.h>
#include <testutils/log_utils.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {
class SharedNetworkParserTest : public LogContentTest {
public:

    /// @brief Structure for describing a single relay test scenario
    struct RelayTest {
        /// @brief Description of the test scenario, used for logging
        std::string description_;
        /// @brief JSON configuration body of the "relay" element
        std::string json_content_;
        /// @brief indicates if parsing should pass or fail
        bool should_parse_;
        /// @brief list of addresses expected after parsing
        std::vector<IOAddress> addresses_;
    };

    /// @brief virtual destructor
    virtual ~SharedNetworkParserTest() = default;

    /// @brief Fetch valid shared network configuration JSON text
    virtual std::string getWorkingConfig() const = 0;
    ElementPtr makeTestConfig(const std::string& name, const std::string& json_content) {
        // Create working config element tree
        ElementPtr config = Element::fromJSON(getWorkingConfig());

        // Create test element contents
        ElementPtr content = Element::fromJSON(json_content);

        // Add the test element to working config
        config->set(name, content);
        return (config);
    }

    /// @brief Executes a single "relay" parsing scenario
    ///
    /// Each test pass consists of the following steps:
    /// -# Attempt to parse the given JSON text
    /// -# If parsing is expected to fail and it does return otherwise fatal fail
    /// -# If parsing is expected to succeed, fatal fail if it does not
    /// -# Verify the network's relay address list matches the expected list
    /// in size and content.
    ///
    /// @param test RelayTest which describes the test to conduct
    void relayTest(const RelayTest& test) {
        ElementPtr test_config;
        ASSERT_NO_THROW(test_config =
                        makeTestConfig("relay", test.json_content_));

        // Init our ref to a place holder
        Network4 dummy;
        Network& network = dummy;

        // If parsing should fail, call parse expecting a throw.
        if (!test.should_parse_) {
            ASSERT_THROW(network = parseIntoNetwork(test_config), DhcpConfigError);
            // No throw so test outcome is correct, nothing else to do.
           return;
        }

        // Should parse without error, let's see if it does.
        ASSERT_NO_THROW(network = parseIntoNetwork(test_config));

        // It parsed, are the number of entries correct?
        ASSERT_EQ(test.addresses_.size(), network.getRelayAddresses().size());

        // Are the expected addresses in the list?
        for (auto const& exp_address : test.addresses_) {
            EXPECT_TRUE(network.hasRelayAddress(exp_address))
                        << " expected address: " << exp_address.toText() << " not found" ;
        }
    }

    /// @brief Attempts to parse the given configuration into a shared network
    ///
    /// Virtual function used by relayTest() to parse a test configuration.
    /// Implementation should not catch parsing exceptions.
    ///
    /// @param test_config JSON configuration text to parse
    /// @return A reference to the Network created if parsing is successful
    virtual Network& parseIntoNetwork(ConstElementPtr test_config) = 0;

    // Verifies valid permutations of ddns-ttl-percent, ddns-ttl,
    // ddns-ttl-min, and ddns-ttl-max values for SharedNetwork4.
    template<typename NetworkTypePtr, typename ParserType>
    void validDdnsTtlParmatersTest() {
        struct Scenario {
            size_t line_no_;
            std::string json_;
            double ddns_ttl_percent_;
            uint32_t ddns_ttl_;
            uint32_t ddns_ttl_min_;
            uint32_t ddns_ttl_max_;
        };

        std::list<Scenario> scenarios = {
        {
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl": 100
            })^",
            0.0, 100, 0, 0
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl-percent": 5.0
            })^",
            5.0, 0, 0, 0
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl-min": 25
            })^",
            0.0, 0, 25, 0
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl-max": 150
            })^",
            0.0, 0, 0, 150
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl-min": 25,
                "ddns-ttl-max": 150
            })^",
            0.0, 0, 25, 150
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl-percent": 5.0,
                "ddns-ttl-min": 25,
                "ddns-ttl-max": 150
            })^",
            5.0, 0, 25, 150
        }};

        for (const auto& scenario : scenarios) {
            std::stringstream oss;
            oss << "scenario at " << scenario.line_no_;
            SCOPED_TRACE(oss.str());

            // Parse configuration specified above.
            ElementPtr config_element;
            ASSERT_NO_THROW_LOG(config_element = Element::fromJSON(scenario.json_));

            ParserType parser;
            NetworkTypePtr network;

            ASSERT_NO_THROW_LOG(network = parser.parse(config_element));
            ASSERT_TRUE(network);

            EXPECT_EQ(network->getDdnsTtlPercent().unspecified(), (scenario.ddns_ttl_percent_ == 0.0));
            EXPECT_EQ(network->getDdnsTtlPercent(), scenario.ddns_ttl_percent_);

            EXPECT_EQ(network->getDdnsTtl().unspecified(), (scenario.ddns_ttl_ == 0));
            EXPECT_EQ(network->getDdnsTtl(), scenario.ddns_ttl_);

            EXPECT_EQ(network->getDdnsTtlMin().unspecified(), (scenario.ddns_ttl_min_ == 0));
            EXPECT_EQ(network->getDdnsTtlMin(), scenario.ddns_ttl_min_);

            EXPECT_EQ(network->getDdnsTtlMax().unspecified(), (scenario.ddns_ttl_max_ == 0));
            EXPECT_EQ(network->getDdnsTtlMax(), scenario.ddns_ttl_max_);
        }
    }

    // Verifies invalid permutations of ddns-ttl-percent, ddns-ttl,
    // ddns-ttl-min, and ddns-ttl-max values for SharedNetwork.
    template<typename ParserType>
    void invalidDdnsTtlParmatersTest() {
        struct Scenario {
            size_t line_no_;
            std::string json_;
            std::string exp_message_;
            };

        std::list<Scenario> scenarios = {
        {
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl-percent": 5.0,
                "ddns-ttl": 100
            })^",
            "cannot specify both ddns-ttl-percent and ddns-ttl (<string>:1:2)"
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl": 100,
                "ddns-ttl-min": 25
            })^",
            "cannot specify both ddns-ttl-min and ddns-ttl (<string>:1:2)"
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl": 100,
                "ddns-ttl-max": 150
            })^",
            "cannot specify both ddns-ttl-max and ddns-ttl (<string>:1:2)"
        },{
            __LINE__,
            R"^({
                "name": "one",
                "ddns-ttl-min": 150,
                "ddns-ttl-max": 25
            })^",
            "ddns-ttl-max: 25 must be greater than ddns-ttl-min: 150 (<string>:1:2)"
        }};

        for (const auto& scenario : scenarios) {
            std::stringstream oss;
            oss << "scenario at " << scenario.line_no_;
            SCOPED_TRACE(oss.str());

            // Parse configuration specified above.
            ElementPtr config_element;
            ASSERT_NO_THROW_LOG(config_element = Element::fromJSON(scenario.json_));
            ParserType parser;
            ASSERT_THROW_MSG(parser.parse(config_element), DhcpConfigError, scenario.exp_message_);
        }
    }
};

/// @brief Test fixture class for SharedNetwork4Parser class.
class SharedNetwork4ParserTest : public SharedNetworkParserTest {
public:

    /// @brief Creates valid shared network configuration.
    ///
    /// @return Valid shared network configuration.
    virtual std::string getWorkingConfig() const {
            std::string config = "{"
                "    \"allocator\": \"iterative\","
                "    \"authoritative\": true,"
                "    \"boot-file-name\": \"/dev/null\","
                "    \"client-class\": \"srv1\","
                "    \"interface\": \"eth1961\","
                "    \"match-client-id\": true,"
                "    \"name\": \"bird\","
                "    \"next-server\": \"10.0.0.1\","
                "    \"rebind-timer\": 199,"
                "    \"relay\": { \"ip-addresses\": [ \"10.1.1.1\" ] },"
                "    \"renew-timer\": 99,"
                "    \"reservations-global\": false,"
                "    \"reservations-in-subnet\": true,"
                "    \"reservations-out-of-pool\": true,"
                "    \"server-hostname\": \"example.org\","
                "    \"evaluate-additional-classes\": [ \"runner\" ],"
                "    \"user-context\": { \"comment\": \"example\" },"
                "    \"valid-lifetime\": 399,"
                "    \"min-valid-lifetime\": 299,"
                "    \"max-valid-lifetime\": 499,"
                "    \"calculate-tee-times\": true,"
                "    \"t1-percent\": 0.345,"
                "    \"t2-percent\": 0.721,"
                "    \"ddns-send-updates\": true,"
                "    \"ddns-override-no-update\": true,"
                "    \"ddns-override-client-update\": true,"
                "    \"ddns-replace-client-name\": \"always\","
                "    \"ddns-generated-prefix\": \"prefix\","
                "    \"ddns-qualifying-suffix\": \"example.com.\","
                "    \"hostname-char-set\": \"[^A-Z]\","
                "    \"hostname-char-replacement\": \"x\","
                "    \"store-extended-info\": true,"
                "    \"cache-threshold\": 0.123,"
                "    \"cache-max-age\": 123,"
                "    \"offer-lifetime\": 777,"
                "    \"ddns-update-on-renew\": true,"
                "    \"option-data\": ["
                "        {"
                "            \"name\": \"domain-name-servers\","
                "            \"data\": \"192.0.2.3\""
                "        }"
                "    ],"
                "    \"subnet4\": ["
                "        {"
                "            \"id\": 1,"
                "            \"subnet\": \"10.1.2.0/24\","
                "            \"interface\": \"\","
                "            \"renew-timer\": 100,"
                "            \"rebind-timer\": 200,"
                "            \"valid-lifetime\": 300,"
                "            \"min-valid-lifetime\": 200,"
                "            \"max-valid-lifetime\": 400,"
                "            \"match-client-id\": false,"
                "            \"authoritative\": false,"
                "            \"next-server\": \"\","
                "            \"server-hostname\": \"\","
                "            \"boot-file-name\": \"\","
                "            \"client-class\": \"\","
                "            \"evaluate-additional-classes\": []\n,"
                "            \"reservations-global\": false,"
                "            \"reservations-in-subnet\": true,"
                "            \"reservations-out-of-pool\": false,"
                "            \"4o6-interface\": \"\","
                "            \"4o6-interface-id\": \"\","
                "            \"4o6-subnet\": \"\","
                "            \"calculate-tee-times\": true,"
                "            \"t1-percent\": .45,"
                "            \"t2-percent\": .65,"
                "            \"hostname-char-set\": \"\","
                "            \"cache-threshold\": .20,"
                "            \"cache-max-age\": 50,"
                "            \"allocator\": \"random\""
                "        },"
                "        {"
                "            \"id\": 2,"
                "            \"subnet\": \"192.0.2.0/24\","
                "            \"interface\": \"\","
                "            \"renew-timer\": 10,"
                "            \"rebind-timer\": 20,"
                "            \"valid-lifetime\": 30,"
                "            \"match-client-id\": false,"
                "            \"authoritative\": false,"
                "            \"next-server\": \"\","
                "            \"server-hostname\": \"\","
                "            \"boot-file-name\": \"\","
                "            \"client-class\": \"\","
                "            \"evaluate-additional-classes\": []\n,"
                "            \"reservations-global\": false,"
                "            \"reservations-in-subnet\": true,"
                "            \"reservations-out-of-pool\": false,"
                "            \"4o6-interface\": \"\","
                "            \"4o6-interface-id\": \"\","
                "            \"4o6-subnet\": \"\","
                "            \"calculate-tee-times\": false,"
                "            \"t1-percent\": .40,"
                "            \"t2-percent\": .80,"
                "            \"cache-threshold\": .15,"
                "            \"cache-max-age\": 5"
                "        }"
                "    ]"
                "}";

            return (config);
    }

    virtual Network& parseIntoNetwork(ConstElementPtr test_config) {
        // Parse configuration.
        SharedNetwork4Parser parser;
        network_ = parser.parse(test_config);
        return (*network_);
    }

private:
    SharedNetwork4Ptr network_;
};

// This test verifies that shared network parser for IPv4 works properly
// in a positive test scenario.
TEST_F(SharedNetwork4ParserTest, parse) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network. A bunch of parameters
    // have to be specified for subnets because subnet parsers expect
    // that default and global values are set.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;

    ASSERT_NO_THROW_LOG(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    // Check basic parameters.
    EXPECT_TRUE(network->getAuthoritative());
    EXPECT_TRUE(network->getClientClasses().contains("srv1"));
    EXPECT_EQ("bird", network->getName());
    EXPECT_EQ("eth1961", network->getIface().get());
    EXPECT_EQ(99, network->getT1().get());
    EXPECT_EQ(199, network->getT2().get());
    EXPECT_EQ(399, network->getValid().get());
    EXPECT_EQ(299, network->getValid().getMin());
    EXPECT_EQ(499, network->getValid().getMax());
    EXPECT_TRUE(network->getCalculateTeeTimes());
    EXPECT_EQ(0.345, network->getT1Percent());
    EXPECT_EQ(0.721, network->getT2Percent());
    EXPECT_EQ("/dev/null", network->getFilename().get());
    EXPECT_EQ("10.0.0.1", network->getSiaddr().get().toText());
    EXPECT_EQ("example.org", network->getSname().get());
    EXPECT_FALSE(network->getReservationsGlobal());
    EXPECT_TRUE(network->getReservationsInSubnet());
    EXPECT_TRUE(network->getReservationsOutOfPool());
    EXPECT_TRUE(network->getDdnsSendUpdates().get());
    EXPECT_TRUE(network->getDdnsOverrideNoUpdate().get());
    EXPECT_TRUE(network->getDdnsOverrideClientUpdate().get());
    EXPECT_EQ(D2ClientConfig::RCM_ALWAYS, network->getDdnsReplaceClientNameMode().get());
    EXPECT_EQ("prefix", network->getDdnsGeneratedPrefix().get());
    EXPECT_EQ("example.com.", network->getDdnsQualifyingSuffix().get());
    EXPECT_EQ("[^A-Z]", network->getHostnameCharSet().get());
    EXPECT_EQ("x", network->getHostnameCharReplacement().get());
    EXPECT_TRUE(network->getStoreExtendedInfo().get());
    EXPECT_EQ(0.123, network->getCacheThreshold());
    EXPECT_EQ(123, network->getCacheMaxAge().get());
    EXPECT_EQ(777, network->getOfferLft().get());
    EXPECT_TRUE(network->getDdnsUpdateOnRenew().get());
    EXPECT_EQ("iterative", network->getAllocatorType().get());

    // Relay information.
    auto relay_info = network->getRelayInfo();
    EXPECT_EQ(1, relay_info.getAddresses().size());
    EXPECT_TRUE(relay_info.containsAddress(IOAddress("10.1.1.1")));

    // Additional client classes.
    auto additional = network->getAdditionalClasses();
    ASSERT_EQ(1, additional.size());
    EXPECT_EQ("runner", *additional.cbegin());

    // Check user context.
    ConstElementPtr context = network->getContext();
    ASSERT_TRUE(context);
    EXPECT_TRUE(context->get("comment"));

    // Subnet with id 1
    Subnet4Ptr subnet = network->getSubnet(SubnetID(1));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("10.1.2.0", subnet->get().first.toText());
    EXPECT_EQ(300, subnet->getValid().get());
    EXPECT_EQ(200, subnet->getValid().getMin());
    EXPECT_EQ(400, subnet->getValid().getMax());
    EXPECT_FALSE(subnet->getHostnameCharSet().unspecified());
    EXPECT_EQ("", subnet->getHostnameCharSet().get());
    EXPECT_EQ("random", subnet->getAllocatorType().get());

    // Subnet with id 2
    subnet = network->getSubnet(SubnetID(2));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("192.0.2.0", subnet->get().first.toText());
    EXPECT_EQ(30, subnet->getValid().get());
    EXPECT_EQ(30, subnet->getValid().getMin());
    EXPECT_EQ(30, subnet->getValid().getMax());
    EXPECT_EQ("[^A-Z]", subnet->getHostnameCharSet().get());
    EXPECT_EQ("x", subnet->getHostnameCharReplacement().get());
    EXPECT_EQ("iterative", subnet->getAllocatorType().get());

    // DHCP options
    ConstCfgOptionPtr cfg_option = network->getCfgOption();
    ASSERT_TRUE(cfg_option);
    OptionDescriptor opt_dns_servers = cfg_option->get("dhcp4",
                                                       DHO_DOMAIN_NAME_SERVERS);
    ASSERT_TRUE(opt_dns_servers.option_);
    Option4AddrLstPtr dns_servers = boost::dynamic_pointer_cast<
        Option4AddrLst>(opt_dns_servers.option_);
    ASSERT_TRUE(dns_servers);
    Option4AddrLst::AddressContainer addresses = dns_servers->getAddresses();
    ASSERT_EQ(1, addresses.size());
    EXPECT_EQ("192.0.2.3", addresses[0].toText());
}

// This test verifies that parser throws an exception when mandatory parameter
// "name" is not specified.
TEST_F(SharedNetwork4ParserTest, missingName) {
    // Remove a name parameter from the valid configuration.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(config_element->remove("name"));

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;
    ASSERT_THROW(network = parser.parse(config_element), DhcpConfigError);
}

// This test verifies that it's possible to specify client-class,
// match-client-id, and authoritative on shared-network level.
TEST_F(SharedNetwork4ParserTest, clientClassMatchClientIdAuthoritative) {
    IfaceMgrTestConfig ifmgr(true);

    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    config_element->set("authoritative", Element::create(true));
    config_element->set("match-client-id", Element::create(false));
    config_element->set("client-class", Element::create("alpha"));

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;
    network = parser.parse(config_element);
    ASSERT_TRUE(network);

    EXPECT_TRUE(network->getClientClasses().contains("alpha"));

    EXPECT_FALSE(network->getMatchClientId());

    EXPECT_TRUE(network->getAuthoritative());
}

// This test verifies that parsing of the "relay" element.
// It checks both valid and invalid scenarios.
TEST_F(SharedNetwork4ParserTest, relayInfoTests) {
    IfaceMgrTestConfig ifmgr(true);

    // Create the vector of test scenarios.
    std::vector<RelayTest> tests = {
        {
            "valid ip-addresses #1",
            "{ \"ip-addresses\": [ ] }",
            true,
            {}
        },
        {
            "valid ip-addresses #2",
            "{ \"ip-addresses\": [ \"192.168.2.1\" ] }",
            true,
            { asiolink::IOAddress("192.168.2.1") }
        },
        {
            "valid ip-addresses #3",
            "{ \"ip-addresses\": [ \"192.168.2.1\", \"192.168.2.2\" ] }",
            true,
            { asiolink::IOAddress("192.168.2.1"), asiolink::IOAddress("192.168.2.2") }
        },
        {
            "invalid ip-addresses #1",
            "{ \"ip-addresses\": [ \"not an address\" ] }",
            false,
            { }
        },
        {
            "invalid ip-addresses #2",
            "{ \"ip-addresses\": [ \"2001:db8::1\" ] }",
            false,
            { }
        },
        {
            "invalid no ip-addresses",
            "{}",
            false,
            { }
        }
    };

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto const& test : tests) {
        SCOPED_TRACE(test.description_);
        relayTest(test);
    }
}

// This test verifies that the optional interface check works as expected.
TEST_F(SharedNetwork4ParserTest, iface) {
    // Basic configuration for shared network.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.

    // The interface check can be disabled.
    SharedNetwork4Parser parser_no_check(false);
    SharedNetwork4Ptr network;
    EXPECT_NO_THROW(network = parser_no_check.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_FALSE(network->getIface().unspecified());
    EXPECT_EQ("eth1961", network->getIface().get());

    // Retry with the interface check enabled.
    SharedNetwork4Parser parser;
    EXPECT_THROW(parser.parse(config_element), DhcpConfigError);

    // Configure default test interfaces.
    IfaceMgrTestConfig ifmgr(true);

    EXPECT_NO_THROW(network = parser_no_check.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_FALSE(network->getIface().unspecified());
    EXPECT_EQ("eth1961", network->getIface().get());

    EXPECT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_FALSE(network->getIface().unspecified());
    EXPECT_EQ("eth1961", network->getIface().get());
}

// This test verifies that shared network parser for IPv4 works properly
// when using invalid renew and rebind timers.
TEST_F(SharedNetwork4ParserTest, parseWithInvalidRenewRebind) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network but with a renew-timer value
    // larger than rebind-timer.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);
    ConstElementPtr valid_element = config_element->get("rebind-timer");
    int64_t value = valid_element->intValue();
    valid_element = config_element->get("renew-timer");
    ElementPtr mutable_element = boost::const_pointer_cast<Element>(valid_element);
    mutable_element->setValue(value + 1);

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;

    // Parser should not throw.
    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    // Veriy we emitted the proper log message.
    addString("DHCPSRV_CFGMGR_RENEW_GTR_REBIND in shared-network bird,"
              " the value of renew-timer 200 is greater than the value"
              " of rebind-timer 199, ignoring renew-timer");
    EXPECT_TRUE(checkFile());
}

// This test verifies that shared network parser for IPv4 works properly
// when renew and rebind timers are equal.
TEST_F(SharedNetwork4ParserTest, parseValidWithEqualRenewRebind) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);
    ConstElementPtr valid_element = config_element->get("rebind-timer");
    int64_t value = valid_element->intValue();
    valid_element = config_element->get("renew-timer");
    ElementPtr mutable_element = boost::const_pointer_cast<Element>(valid_element);
    mutable_element->setValue(value);

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);
}

// Test that FLQ allocator can be used for a shared network.
TEST_F(SharedNetwork4ParserTest, parseFLQAllocator) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network.
    std::string config = "{ \"name\": \"lion\", \"allocator\": \"flq\" }";
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_EQ("flq", network->getAllocatorType().get());
}


/// @brief Test fixture class for SharedNetwork6Parser class.
class SharedNetwork6ParserTest : public SharedNetworkParserTest {
public:

    /// @brief Constructor.
    SharedNetwork6ParserTest()
        : SharedNetworkParserTest(), network_(), use_iface_id_(false) {
    }

    /// @brief Creates valid shared network configuration.
    ///
    /// @return Valid shared network configuration.
    virtual std::string getWorkingConfig() const {
            std::string config = "{"
                "    \"client-class\": \"srv1\","
                + std::string(use_iface_id_ ? "\"interface-id\": " : "\"interface\": ") +
                "\"eth1961\","
                "    \"name\": \"bird\","
                "    \"preferred-lifetime\": 211,"
                "    \"min-preferred-lifetime\": 111,"
                "    \"max-preferred-lifetime\": 311,"
                "    \"rapid-commit\": true,"
                "    \"rebind-timer\": 199,"
                "    \"relay\": { \"ip-addresses\": [ \"2001:db8:1::1\" ] },"
                "    \"renew-timer\": 99,"
                "    \"evaluate-additional-classes\": [ \"runner\" ],"
                "    \"reservations-global\": false,"
                "    \"reservations-in-subnet\": true,"
                "    \"reservations-out-of-pool\": true,"
                "    \"user-context\": { },"
                "    \"valid-lifetime\": 399,"
                "    \"min-valid-lifetime\": 299,"
                "    \"max-valid-lifetime\": 499,"
                "    \"calculate-tee-times\": true,"
                "    \"t1-percent\": 0.345,"
                "    \"t2-percent\": 0.721,"
                "    \"ddns-send-updates\": true,"
                "    \"ddns-override-no-update\": true,"
                "    \"ddns-override-client-update\": true,"
                "    \"ddns-replace-client-name\": \"always\","
                "    \"ddns-generated-prefix\": \"prefix\","
                "    \"ddns-qualifying-suffix\": \"example.com.\","
                "    \"hostname-char-set\": \"[^A-Z]\","
                "    \"hostname-char-replacement\": \"x\","
                "    \"store-extended-info\": true,"
                "    \"cache-threshold\": 0.123,"
                "    \"cache-max-age\": 123,"
                "    \"ddns-update-on-renew\": true,"
                "    \"allocator\": \"random\","
                "    \"pd-allocator\": \"iterative\","
                "    \"option-data\": ["
                "        {"
                "            \"name\": \"dns-servers\","
                "            \"data\": \"2001:db8:1::cafe\""
                "        }"
                "    ],"
                "    \"subnet6\": ["
                "        {"
                "            \"id\": 1,"
                "            \"subnet\": \"3000::/16\","
                "            \"interface\": \"\","
                "            \"interface-id\": \"\","
                "            \"renew-timer\": 100,"
                "            \"rebind-timer\": 200,"
                "            \"preferred-lifetime\": 300,"
                "            \"min-preferred-lifetime\": 200,"
                "            \"max-preferred-lifetime\": 400,"
                "            \"valid-lifetime\": 400,"
                "            \"min-valid-lifetime\": 300,"
                "            \"max-valid-lifetime\": 500,"
                "            \"client-class\": \"\","
                "            \"evaluate-additional-classes\": []\n,"
                "            \"reservations-global\": false,"
                "            \"reservations-in-subnet\": true,"
                "            \"reservations-out-of-pool\": false,"
                "            \"rapid-commit\": false,"
                "            \"hostname-char-set\": \"\","
                "            \"allocator\": \"iterative\","
                "            \"pd-allocator\": \"random\""
                "        },"
                "        {"
                "            \"id\": 2,"
                "            \"subnet\": \"2001:db8:1::/64\","
                "            \"interface\": \"\","
                "            \"interface-id\": \"\","
                "            \"renew-timer\": 10,"
                "            \"rebind-timer\": 20,"
                "            \"preferred-lifetime\": 30,"
                "            \"valid-lifetime\": 40,"
                "            \"client-class\": \"\","
                "            \"evaluate-additional-classes\": []\n,"
                "            \"reservations-global\": false,"
                "            \"reservations-in-subnet\": true,"
                "            \"reservations-out-of-pool\": false,"
                "            \"rapid-commit\": false"
                "        }"
                "    ]"
                "}";

            return (config);
    }

    virtual Network& parseIntoNetwork(ConstElementPtr test_config) {
        // Parse configuration.
        SharedNetwork6Parser parser;
        network_ = parser.parse(test_config);
        return (*network_);
    }

public:

    SharedNetwork6Ptr network_;

    /// Boolean flag indicating if the interface-id should be used instead
    /// of interface.
    bool use_iface_id_;
};

// This test verifies that shared network parser for IPv6 works properly
// in a positive test scenario.
TEST_F(SharedNetwork6ParserTest, parse) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network. A bunch of parameters
    // have to be specified for subnets because subnet parsers expect
    // that default and global values are set.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;
    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    // Check basic parameters.
    EXPECT_TRUE(network->getClientClasses().contains("srv1"));
    EXPECT_EQ("bird", network->getName());
    EXPECT_EQ("eth1961", network->getIface().get());
    EXPECT_EQ(211, network->getPreferred().get());
    EXPECT_EQ(111, network->getPreferred().getMin());
    EXPECT_EQ(311, network->getPreferred().getMax());
    EXPECT_TRUE(network->getRapidCommit());
    EXPECT_EQ(99, network->getT1().get());
    EXPECT_EQ(199, network->getT2().get());
    EXPECT_EQ(399, network->getValid().get());
    EXPECT_EQ(299, network->getValid().getMin());
    EXPECT_EQ(499, network->getValid().getMax());
    EXPECT_TRUE(network->getCalculateTeeTimes());
    EXPECT_EQ(0.345, network->getT1Percent());
    EXPECT_EQ(0.721, network->getT2Percent());
    EXPECT_TRUE(network->getDdnsSendUpdates().get());
    EXPECT_TRUE(network->getDdnsOverrideNoUpdate().get());
    EXPECT_TRUE(network->getDdnsOverrideClientUpdate().get());
    EXPECT_EQ(D2ClientConfig::RCM_ALWAYS, network->getDdnsReplaceClientNameMode().get());
    EXPECT_EQ("prefix", network->getDdnsGeneratedPrefix().get());
    EXPECT_EQ("example.com.", network->getDdnsQualifyingSuffix().get());
    EXPECT_EQ("[^A-Z]", network->getHostnameCharSet().get());
    EXPECT_EQ("x", network->getHostnameCharReplacement().get());
    EXPECT_TRUE(network->getStoreExtendedInfo().get());
    EXPECT_EQ(0.123, network->getCacheThreshold());
    EXPECT_EQ(123, network->getCacheMaxAge().get());
    EXPECT_TRUE(network->getDdnsUpdateOnRenew().get());
    EXPECT_EQ("random", network->getAllocatorType().get());
    EXPECT_EQ("iterative", network->getPdAllocatorType().get());

    // Relay information.
    auto relay_info = network->getRelayInfo();
    EXPECT_EQ(1, relay_info.getAddresses().size());
    EXPECT_TRUE(relay_info.containsAddress(IOAddress("2001:db8:1::1")));

    // Additional client classes.
    auto additional = network->getAdditionalClasses();
    ASSERT_EQ(1, additional.size());
    EXPECT_EQ("runner", *additional.cbegin());

    // Check user context.
    ConstElementPtr context = network->getContext();
    ASSERT_TRUE(context);
    EXPECT_EQ(0, context->size());

    // Subnet with id 1
    Subnet6Ptr subnet = network->getSubnet(SubnetID(1));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("3000::", subnet->get().first.toText());
    EXPECT_EQ(300, subnet->getPreferred().get());
    EXPECT_EQ(200, subnet->getPreferred().getMin());
    EXPECT_EQ(400, subnet->getPreferred().getMax());
    EXPECT_EQ(400, subnet->getValid().get());
    EXPECT_EQ(300, subnet->getValid().getMin());
    EXPECT_EQ(500, subnet->getValid().getMax());
    EXPECT_FALSE(subnet->getHostnameCharSet().unspecified());
    EXPECT_EQ("", subnet->getHostnameCharSet().get());
    EXPECT_EQ("iterative", subnet->getAllocatorType().get());
    EXPECT_EQ("random", subnet->getPdAllocatorType().get());

    // Subnet with id 2
    subnet = network->getSubnet(SubnetID(2));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("2001:db8:1::", subnet->get().first.toText());
    EXPECT_EQ(30, subnet->getPreferred().get());
    EXPECT_EQ(30, subnet->getPreferred().getMin());
    EXPECT_EQ(30, subnet->getPreferred().getMax());
    EXPECT_EQ(40, subnet->getValid().get());
    EXPECT_EQ(40, subnet->getValid().getMin());
    EXPECT_EQ(40, subnet->getValid().getMax());
    EXPECT_EQ("[^A-Z]", subnet->getHostnameCharSet().get());
    EXPECT_EQ("x", subnet->getHostnameCharReplacement().get());
    EXPECT_EQ("random", subnet->getAllocatorType().get());
    EXPECT_EQ("iterative", subnet->getPdAllocatorType().get());

    // DHCP options
    ConstCfgOptionPtr cfg_option = network->getCfgOption();
    ASSERT_TRUE(cfg_option);
    OptionDescriptor opt_dns_servers = cfg_option->get("dhcp6",
                                                       D6O_NAME_SERVERS);
    ASSERT_TRUE(opt_dns_servers.option_);
    Option6AddrLstPtr dns_servers = boost::dynamic_pointer_cast<
        Option6AddrLst>(opt_dns_servers.option_);
    ASSERT_TRUE(dns_servers);
    Option6AddrLst::AddressContainer addresses = dns_servers->getAddresses();
    ASSERT_EQ(1, addresses.size());
    EXPECT_EQ("2001:db8:1::cafe", addresses[0].toText());
}

// This test verifies that shared network parser for IPv6 works properly
// in a positive test scenario.
TEST_F(SharedNetwork6ParserTest, parseWithInterfaceId) {
    IfaceMgrTestConfig ifmgr(true);

    // Use the configuration with interface-id instead of interface parameter.
    use_iface_id_ = true;
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;
    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    // Check that interface-id has been parsed.
    auto opt_iface_id = network->getInterfaceId();
    ASSERT_TRUE(opt_iface_id);
}

// This test verifies that shared network parser for IPv6 works properly
// when using invalid renew and rebind timers.
TEST_F(SharedNetwork6ParserTest, parseWithInvalidRenewRebind) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network but with a renew-timer value
    // larger than rebind-timer.
    use_iface_id_ = true;
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);
    ConstElementPtr valid_element = config_element->get("rebind-timer");
    int64_t value = valid_element->intValue();
    valid_element = config_element->get("renew-timer");
    ElementPtr mutable_element = boost::const_pointer_cast<Element>(valid_element);
    mutable_element->setValue(value + 1);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;

    // Parser should not throw.
    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    // Veriy we emitted the proper log message.
    addString("DHCPSRV_CFGMGR_RENEW_GTR_REBIND in shared-network bird,"
              " the value of renew-timer 200 is greater than the value"
              " of rebind-timer 199, ignoring renew-timer");
    EXPECT_TRUE(checkFile());
}

// This test verifies that shared network parser for IPv6 works properly
// when renew and rebind timers are equal.
TEST_F(SharedNetwork6ParserTest, parseValidWithEqualRenewRebind) {
    IfaceMgrTestConfig ifmgr(true);

    // Use the configuration with interface-id instead of interface parameter.
    use_iface_id_ = true;
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);
    ConstElementPtr valid_element = config_element->get("rebind-timer");
    int64_t value = valid_element->intValue();
    valid_element = config_element->get("renew-timer");
    ElementPtr mutable_element = boost::const_pointer_cast<Element>(valid_element);
    mutable_element->setValue(value);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);
}

// This test verifies that error is returned when trying to configure a
// shared network with both interface and interface id.
TEST_F(SharedNetwork6ParserTest, mutuallyExclusiveInterfaceId) {
    IfaceMgrTestConfig ifmgr(true);

    // Use the configuration with interface-id instead of interface parameter.
    use_iface_id_ = true;
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Add interface which is mutually exclusive with interface-id
    config_element->set("interface", Element::create("eth1"));

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    EXPECT_THROW(parser.parse(config_element), DhcpConfigError);
}

// This test verifies that it's possible to specify client-class
// on shared-network level.
TEST_F(SharedNetwork6ParserTest, clientClass) {
    IfaceMgrTestConfig ifmgr(true);

    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    config_element->set("client-class", Element::create("alpha"));

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;
    network = parser.parse(config_element);
    ASSERT_TRUE(network);

    EXPECT_TRUE(network->getClientClasses().contains("alpha"));
}

// This test verifies that it's possible to specify evaluate-additional-classes
// on shared-network level.
TEST_F(SharedNetwork6ParserTest, evalClientClasses) {
    IfaceMgrTestConfig ifmgr(true);

    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    ElementPtr class_list = Element::createList();
    class_list->add(Element::create("alpha"));
    class_list->add(Element::create("beta"));
    config_element->set("evaluate-additional-classes", class_list);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;
    network = parser.parse(config_element);
    ASSERT_TRUE(network);

    const ClientClasses& classes = network->getAdditionalClasses();
    EXPECT_EQ(2, classes.size());
    EXPECT_EQ("alpha, beta", classes.toText());
}

// This test verifies that bad evaluate-additional-classes configs raise
// expected errors.
TEST_F(SharedNetwork6ParserTest, badEvalClientClasses) {
    IfaceMgrTestConfig ifmgr(true);

    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Element of the list must be strings.
    ElementPtr class_list = Element::createList();
    class_list->add(Element::create("alpha"));
    class_list->add(Element::create(1234));
    config_element->set("evaluate-additional-classes", class_list);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;
    EXPECT_THROW(network = parser.parse(config_element), DhcpConfigError);

    // Empty class name is forbidden.
    class_list = Element::createList();
    class_list->add(Element::create("alpha"));
    class_list->add(Element::create(""));
    EXPECT_THROW(network = parser.parse(config_element), DhcpConfigError);

    // And of course the list must be a list even the parser can only
    // trigger the previous error case...
    class_list = Element::createMap();
    EXPECT_THROW(network = parser.parse(config_element), DhcpConfigError);
}

// This test verifies that v6 parsing of the "relay" element.
// It checks both valid and invalid scenarios.
TEST_F(SharedNetwork6ParserTest, relayInfoTests) {
    IfaceMgrTestConfig ifmgr(true);


    // Create the vector of test scenarios.
    std::vector<RelayTest> tests = {
        {
            "valid ip-addresses #1",
            "{ \"ip-addresses\": [ ] }",
            true,
            {}
        },
        {
            "valid ip-addresses #2",
            "{ \"ip-addresses\": [ \"2001:db8::1\" ] }",
            true,
            { asiolink::IOAddress("2001:db8::1") }
        },
        {
            "valid ip-addresses #3",
            "{ \"ip-addresses\": [ \"2001:db8::1\", \"2001:db8::2\" ] }",
            true,
            { asiolink::IOAddress("2001:db8::1"), asiolink::IOAddress("2001:db8::2") }
        },
        {
            "invalid ip-addresses #1",
            "{ \"ip-addresses\": [ \"not an address\" ] }",
            false,
            { }
        },
        {
            "invalid ip-addresses #2",
            "{ \"ip-addresses\": [ \"192.168.1.1\" ] }",
            false,
            { }
        },
        {
            "invalid no ip-addresses",
            "{}",
            false,
            { }
        }
    };

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto const& test : tests) {
        SCOPED_TRACE(test.description_);
        relayTest(test);
    }
}

// This test verifies that the optional interface check works as expected.
TEST_F(SharedNetwork6ParserTest, iface) {
    // Basic configuration for shared network.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.

    // The interface check can be disabled.
    SharedNetwork6Parser parser_no_check(false);
    SharedNetwork6Ptr network;
    EXPECT_NO_THROW(network = parser_no_check.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_FALSE(network->getIface().unspecified());
    EXPECT_EQ("eth1961", network->getIface().get());

    // Retry with the interface check enabled.
    SharedNetwork6Parser parser;
    EXPECT_THROW(parser.parse(config_element), DhcpConfigError);

    // Configure default test interfaces.
    IfaceMgrTestConfig ifmgr(true);

    EXPECT_NO_THROW(network = parser_no_check.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_FALSE(network->getIface().unspecified());
    EXPECT_EQ("eth1961", network->getIface().get());

    EXPECT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_FALSE(network->getIface().unspecified());
    EXPECT_EQ("eth1961", network->getIface().get());
}

// Test that the FLQ allocator can't be used for DHCPv6 address assignment.
TEST_F(SharedNetwork6ParserTest, parseFLQAllocatorNA) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network.
    std::string config = "{ \"name\": \"lion\", \"allocator\": \"flq\" }";
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    EXPECT_THROW(parser.parse(config_element), DhcpConfigError);
}

// Test that FLQ allocator can be used for prefix delegation.
TEST_F(SharedNetwork6ParserTest, parseFLQAllocatorPD) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration for shared network.
    std::string config = "{ \"name\": \"lion\", \"pd-allocator\": \"flq\" }";
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);
    EXPECT_EQ("flq", network->getPdAllocatorType().get());
}

// Verify that deprecated require-client-classes is handled properly
// by v4 parser.
TEST_F(SharedNetwork4ParserTest, deprecatedRequireClientClasses) {
    // Valid entry.
    std::string config =
       R"^({
            "name": "foo",
            "require-client-classes": [ "one", "two" ]
        })^";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    const auto cclasses = network->getAdditionalClasses();
    EXPECT_EQ(cclasses.size(), 2);
    auto cclass = cclasses.begin();
    EXPECT_EQ(*cclass, "one");
    ++cclass;
    EXPECT_EQ(*cclass, "two");

    // Invalid entry specifies both parameters.
    config =
       R"^({
            "name": "foo",
            "require-client-classes": [ "one", "two" ],
            "evaluate-additional-classes": [ "one", "two" ]
        })^";

    config_element = Element::fromJSON(config);

    // Should throw a complaint.
    ASSERT_THROW_MSG(parser.parse(config_element),
                     DhcpConfigError,
                     "cannot specify both 'require-client-classes' and"
                     " 'evaluate-additional-classes'. Use only the latter."
                     " (<string>:1:2)");
}

// Verify that deprecated require-client-classes is handled properly
// by v6 parser.
TEST_F(SharedNetwork6ParserTest, deprecatedRequireClientClasses) {
    // Valid entry.
    std::string config =
       R"^({
            "name": "foo",
            "require-client-classes": [ "one", "two" ]
       })^";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    const auto cclasses = network->getAdditionalClasses();
    EXPECT_EQ(cclasses.size(), 2);
    auto cclass = cclasses.begin();
    EXPECT_EQ(*cclass, "one");
    ++cclass;
    EXPECT_EQ(*cclass, "two");

    // Invalid entry specifies both parameters.
    config =
       R"^({
            "name": "foo",
            "require-client-classes": [ "one", "two" ],
            "evaluate-additional-classes": [ "one", "two" ]
        })^";

    config_element = Element::fromJSON(config);

    // Should throw a complaint.
    ASSERT_THROW_MSG(parser.parse(config_element),
                     DhcpConfigError,
                     "cannot specify both 'require-client-classes' and"
                     " 'evaluate-additional-classes'. Use only the latter."
                     " (<string>:1:2)");
}

// Verify that deprecated client-class is handled properly
// by v4 parser.
TEST_F(SharedNetwork4ParserTest, deprecatedClientClass) {
    // Valid entry.
    std::string config =
       R"^({
            "name": "foo",
            "client-class": "one"
        })^";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    const auto cclasses = network->getClientClasses();
    EXPECT_EQ(cclasses.size(), 1);
    auto cclass = cclasses.begin();
    EXPECT_EQ(*cclass, "one");

    // Invalid entry specifies both parameters.
    config =
       R"^({
            "name": "foo",
            "client-class": "one",
            "client-classes": [ "one", "two" ]
        })^";

    config_element = Element::fromJSON(config);

    // Should throw a complaint.
    ASSERT_THROW_MSG(parser.parse(config_element),
                     DhcpConfigError,
                     "cannot specify both 'client-class' and"
                     " 'client-classes'. Use only the latter."
                     " (<string>:1:2)");
}

// Verify that deprecated client-class is handled properly
// by v6 parser.
TEST_F(SharedNetwork6ParserTest, deprecatedClientClass) {
    // Valid entry.
    std::string config =
       R"^({
            "name": "foo",
            "client-class": "one"
        })^";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    const auto cclasses = network->getClientClasses();
    EXPECT_EQ(cclasses.size(), 1);
    auto cclass = cclasses.begin();
    EXPECT_EQ(*cclass, "one");

    // Invalid entry specifies both parameters.
    config =
       R"^({
            "name": "foo",
            "client-class": "one",
            "client-classes": [ "one", "two" ]
        })^";

    config_element = Element::fromJSON(config);

    // Should throw a complaint.
    ASSERT_THROW_MSG(parser.parse(config_element),
                     DhcpConfigError,
                     "cannot specify both 'client-class' and"
                     " 'client-classes'. Use only the latter."
                     " (<string>:1:2)");
}

// Verifies valid permutations of ddns-ttl-percent, ddns-ttl,
// ddns-ttl-min, and ddns-ttl-max values for SharedNetwork4.
TEST_F(SharedNetwork4ParserTest, validDdnsTtlParmaters4) {
    validDdnsTtlParmatersTest<SharedNetwork4Ptr, SharedNetwork4Parser>();
}

// Verifies valid permutations of ddns-ttl-percent, ddns-ttl,
// ddns-ttl-min, and ddns-ttl-max values for SharedNetwork6.
TEST_F(SharedNetwork6ParserTest, validDdnsTtlParmaters6) {
    validDdnsTtlParmatersTest<SharedNetwork6Ptr, SharedNetwork6Parser>();
}

// Verifies invalid permutations of ddns-ttl-percent, ddns-ttl,
// ddns-ttl-min, and ddns-ttl-max values for Subnet4.
TEST_F(SharedNetwork4ParserTest, invalidDdnsTtlParmaters4) {
    invalidDdnsTtlParmatersTest<SharedNetwork4Parser>();
}

// Verifies invalid permutations of ddns-ttl-percent, ddns-ttl,
// ddns-ttl-min, and ddns-ttl-max values for Subnet6.
TEST_F(SharedNetwork6ParserTest, invalidDdnsTtlParmaters6) {
    invalidDdnsTtlParmatersTest<SharedNetwork6Parser>();
}

} // end of anonymous namespace
