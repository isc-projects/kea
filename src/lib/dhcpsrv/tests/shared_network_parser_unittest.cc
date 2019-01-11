// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;

namespace {
class SharedNetworkParserTest : public ::testing::Test {
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
        IOAddressList addresses_;
    };

    /// @brief virtual destructor
    virtual ~SharedNetworkParserTest(){};

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
        for (auto exp_address = test.addresses_.begin(); exp_address != test.addresses_.end();
             ++exp_address) {
            EXPECT_TRUE(network.hasRelayAddress(*exp_address))
                        << " expected address: " << (*exp_address).toText() << " not found" ;
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
};


/// @brief Test fixture class for SharedNetwork4Parser class.
class SharedNetwork4ParserTest : public SharedNetworkParserTest {
public:

    /// @brief Creates valid shared network configuration.
    ///
    /// @return Valid shared network configuration.
    virtual std::string getWorkingConfig() const {
            std::string config = "{"
                "    \"user-context\": { \"comment\": \"example\" },"
                "    \"name\": \"bird\","
                "    \"interface\": \"eth1\","
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
                "            \"match-client-id\": false,"
                "            \"authoritative\": false,"
                "            \"next-server\": \"\","
                "            \"server-hostname\": \"\","
                "            \"boot-file-name\": \"\","
                "            \"client-class\": \"\","
                "            \"require-client-classes\": []\n,"
                "            \"reservation-mode\": \"all\","
                "            \"4o6-interface\": \"\","
                "            \"4o6-interface-id\": \"\","
                "            \"4o6-subnet\": \"\","
                "            \"dhcp4o6-port\": 0,"
                "            \"decline-probation-period\": 86400,"
                "            \"reservation-mode\": \"all\","
                "            \"calculate-tee-times\": true,"
                "            \"t1-percent\": .45,"
                "            \"t2-percent\": .65"
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
                "            \"require-client-classes\": []\n,"
                "            \"reservation-mode\": \"all\","
                "            \"4o6-interface\": \"\","
                "            \"4o6-interface-id\": \"\","
                "            \"4o6-subnet\": \"\","
                "            \"dhcp4o6-port\": 0,"
                "            \"decline-probation-period\": 86400,"
                "            \"reservation-mode\": \"all\","
                "            \"calculate-tee-times\": false,"
                "            \"t1-percent\": .40,"
                "            \"t2-percent\": .80"
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
    // Basic configuration for shared network. A bunch of parameters
    // have to be specified for subnets because subnet parsers expect
    // that default and global values are set.
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;

    try { 
        network = parser.parse(config_element);
    } catch (const std::exception& ex) {
        std::cout << "kabook: " << ex.what() << std::endl;
    }

    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    // Check basic parameters.
    EXPECT_EQ("bird", network->getName());
    EXPECT_EQ("eth1", network->getIface());

    // Check user context.
    ConstElementPtr context = network->getContext();
    ASSERT_TRUE(context);
    EXPECT_TRUE(context->get("comment"));

    // Subnet with id 1
    Subnet4Ptr subnet1 = network->getSubnet(SubnetID(1));
    ASSERT_TRUE(subnet1);
    EXPECT_EQ("10.1.2.0", subnet1->get().first.toText());

    // Subnet with id 2
    Subnet4Ptr subnet2 = network->getSubnet(SubnetID(2));
    ASSERT_TRUE(subnet2);
    EXPECT_EQ("192.0.2.0", subnet2->get().first.toText());

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

    EXPECT_EQ("alpha", network->getClientClass());

    EXPECT_FALSE(network->getMatchClientId());

    EXPECT_TRUE(network->getAuthoritative());
}

// This test verifies that parsing of the "relay" element.
// It checks both valid and invalid scenarios.
TEST_F(SharedNetwork4ParserTest, relayInfoTests) {

    // Create the vector of test scenarios.
    std::vector<RelayTest> tests = {
        {
            "valid ip-address #1",
            "{ \"ip-address\": \"192.168.2.1\" }",
            true,
            { asiolink::IOAddress("192.168.2.1") }
        },
        {
            "invalid ip-address #1",
            "{ \"ip-address\": \"not an address\" }",
            false,
            { }
        },
        {
            "invalid ip-address #2",
            "{ \"ip-address\": \"2001:db8::1\" }",
            false,
            { }
        },
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
            "invalid both ip-address and ip-addresses",
            "{"
            " \"ip-address\": \"192.168.2.1\", "
            " \"ip-addresses\": [ \"192.168.2.1\", \"192.168.2.2\" ]"
            " }",
            false,
            { }
        },
        {
            "invalid neither ip-address nor ip-addresses",
            "{}",
            false,
            { }
        }
    };

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
            SCOPED_TRACE((*test).description_);
            relayTest(*test);
        }
    }
}


/// @brief Test fixture class for SharedNetwork6Parser class.
class SharedNetwork6ParserTest : public SharedNetworkParserTest {
public:

    /// @brief Creates valid shared network configuration.
    ///
    /// @return Valid shared network configuration.
    virtual std::string getWorkingConfig() const {
            std::string config = "{"
                "    \"name\": \"bird\","
                "    \"interface\": \"eth1\","
                "    \"user-context\": { },"
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
                "            \"valid-lifetime\": 400,"
                "            \"client-class\": \"\","
                "            \"require-client-classes\": []\n,"
                "            \"reservation-mode\": \"all\","
                "            \"decline-probation-period\": 86400,"
                "            \"dhcp4o6-port\": 0,"
                "            \"rapid-commit\": false"
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
                "            \"require-client-classes\": []\n,"
                "            \"reservation-mode\": \"all\","
                "            \"decline-probation-period\": 86400,"
                "            \"dhcp4o6-port\": 0,"
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

private:
    SharedNetwork6Ptr network_;
};

// This test verifies that shared network parser for IPv4 works properly
// in a positive test scenario.
TEST_F(SharedNetwork6ParserTest, parse) {
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
    EXPECT_EQ("bird", network->getName());
    EXPECT_EQ("eth1", network->getIface());

    // Check user context.
    ConstElementPtr context = network->getContext();
    ASSERT_TRUE(context);
    EXPECT_EQ(0, context->size());

    // Subnet with id 1
    Subnet6Ptr subnet1 = network->getSubnet(SubnetID(1));
    ASSERT_TRUE(subnet1);
    EXPECT_EQ("3000::", subnet1->get().first.toText());

    // Subnet with id 2
    Subnet6Ptr subnet2 = network->getSubnet(SubnetID(2));
    ASSERT_TRUE(subnet2);
    EXPECT_EQ("2001:db8:1::", subnet2->get().first.toText());

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

// This test verifies that it's possible to specify client-class
// on shared-network level.
TEST_F(SharedNetwork6ParserTest, clientClass) {
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    config_element->set("client-class", Element::create("alpha"));

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;
    network = parser.parse(config_element);
    ASSERT_TRUE(network);

    EXPECT_EQ("alpha", network->getClientClass());
}

// This test verifies that it's possible to specify require-client-classes
// on shared-network level.
TEST_F(SharedNetwork6ParserTest, evalClientClasses) {
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    ElementPtr class_list = Element::createList();
    class_list->add(Element::create("alpha"));
    class_list->add(Element::create("beta"));
    config_element->set("require-client-classes", class_list);

    // Parse configuration specified above.
    SharedNetwork6Parser parser;
    SharedNetwork6Ptr network;
    network = parser.parse(config_element);
    ASSERT_TRUE(network);

    const ClientClasses& classes = network->getRequiredClasses();
    EXPECT_EQ(2, classes.size());
    EXPECT_EQ("alpha, beta", classes.toText());
}

// This test verifies that bad require-client-classes configs raise
// expected errors.
TEST_F(SharedNetwork6ParserTest, badEvalClientClasses) {
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    // Element of the list must be strings.
    ElementPtr class_list = Element::createList();
    class_list->add(Element::create("alpha"));
    class_list->add(Element::create(1234));
    config_element->set("require-client-classes", class_list);

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

    // Create the vector of test scenarios.
    std::vector<RelayTest> tests = {
        {
            "valid ip-address #1",
            "{ \"ip-address\": \"2001:db8::1\" }",
            true,
            { asiolink::IOAddress("2001:db8::1") }
        },
        {
            "invalid ip-address #1",
            "{ \"ip-address\": \"not an address\" }",
            false,
            { }
        },
        {
            "invalid ip-address #2",
            "{ \"ip-address\": \"192.168.2.1\" }",
            false,
            { }
        },
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
            "invalid both ip-address and ip-addresses",
            "{"
            " \"ip-address\": \"2001:db8::1\", "
            " \"ip-addresses\": [ \"2001:db8::1\", \"2001:db8::2\" ]"
            " }",
            false,
            { }
        },
        {
            "invalid neither ip-address nor ip-addresses",
            "{}",
            false,
            { }
        }
    };

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
            SCOPED_TRACE((*test).description_);
            relayTest(*test);
        }
    }
}

} // end of anonymous namespace
