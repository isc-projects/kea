// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Test fixture class for SharedNetwork4Parser class.
class SharedNetwork4ParserTest : public ::testing::Test {
public:

    /// @brief Creates valid shared network configuration.
    ///
    /// @return Valid shared network configuration.
    std::string getWorkingConfig() const {
            std::string config = "{"
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
                "            \"next-server\": \"\","
                "            \"client-class\": \"\","
                "            \"reservation-mode\": \"all\","
                "            \"4o6-interface\": \"\","
                "            \"4o6-interface-id\": \"\","
                "            \"4o6-subnet\": \"\","
                "            \"dhcp4o6-port\": 0,"
                "            \"decline-probation-period\": 86400,"
                "            \"reservation-mode\": \"all\""
                "        },"
                "        {"
                "            \"id\": 2,"
                "            \"subnet\": \"192.0.2.0/24\","
                "            \"interface\": \"\","
                "            \"renew-timer\": 10,"
                "            \"rebind-timer\": 20,"
                "            \"valid-lifetime\": 30,"
                "            \"match-client-id\": false,"
                "            \"next-server\": \"\","
                "            \"client-class\": \"\","
                "            \"reservation-mode\": \"all\","
                "            \"4o6-interface\": \"\","
                "            \"4o6-interface-id\": \"\","
                "            \"4o6-subnet\": \"\","
                "            \"dhcp4o6-port\": 0,"
                "            \"decline-probation-period\": 86400,"
                "            \"reservation-mode\": \"all\""
                "        }"
                "    ]"
                "}";

            return (config);
    }
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
    ASSERT_NO_THROW(network = parser.parse(config_element));
    ASSERT_TRUE(network);

    // Check basic parameters.
    EXPECT_EQ("bird", network->getName());
    EXPECT_EQ("eth1", network->getIface());

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

// This test verifies that it's possible to specify client-class
// and match-client-id on shared-network level.
TEST_F(SharedNetwork4ParserTest, clientClassMatchClientId) {
    std::string config = getWorkingConfig();
    ElementPtr config_element = Element::fromJSON(config);

    config_element->set("match-client-id", Element::create(false));
    config_element->set("client-class", Element::create("alpha"));

    // Parse configuration specified above.
    SharedNetwork4Parser parser;
    SharedNetwork4Ptr network;
    network = parser.parse(config_element);
    ASSERT_TRUE(network);

    const ClientClasses classes = network->getClientClasses();
    ASSERT_EQ(1, classes.size());
    EXPECT_TRUE(classes.contains("alpha"));

    EXPECT_FALSE(network->getMatchClientId());
}

/// @brief Test fixture class for SharedNetwork6Parser class.
class SharedNetwork6ParserTest : public ::testing::Test {
public:

    /// @brief Creates valid shared network configuration.
    ///
    /// @return Valid shared network configuration.
    std::string getWorkingConfig() const {
            std::string config = "{"
                "    \"name\": \"bird\","
                "    \"interface\": \"eth1\","
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
                "            \"reservation-mode\": \"all\","
                "            \"decline-probation-period\": 86400,"
                "            \"dhcp4o6-port\": 0,"
                "            \"rapid-commit\": false"
                "        }"
                "    ]"
                "}";

            return (config);
    }
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

    const ClientClasses classes = network->getClientClasses();
    ASSERT_EQ(1, classes.size());
    EXPECT_TRUE(classes.contains("alpha"));
}

} // end of anonymous namespace
