// Copyright (C) 2014-2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/option_int.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_hosts_util.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <testutils/test_to_element.h>
#include <boost/pointer_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::test;

namespace {

/// @brief Holds a type of the last identifier in @c IdentifierType enum.
///
/// This value must be updated when new identifiers are added to the enum.
// const Host::IdentifierType LAST_IDENTIFIER_TYPE = Host::IDENT_CIRCUIT_ID;

/// @brief Test fixture class for @c HostReservationParser.
class HostReservationParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    HostReservationParserTest() = default;

    /// @brief Destructor
    virtual ~HostReservationParserTest() = default;

protected:
    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();

    /// @brief Checks if the reservation is in the range of reservations.
    ///
    /// @param resrv Reservation to be searched for.
    /// @param range Range of reservations returned by the @c Host object
    /// in which the reservation will be searched.
    bool
    reservationExists(const IPv6Resrv& resrv, const IPv6ResrvRange& range) {
        for (IPv6ResrvIterator it = range.first; it != range.second;
             ++it) {
            if (resrv == it->second) {
                return (true);
            }
        }
        return (false);
    }

    /// @brief Retrieves DHCP option from a host.
    ///
    /// @param host Reference to a host object for which an option should be
    /// retrieved.
    /// @param option_space Option space name.
    /// @param option_code Code of an option to be retrieved.
    ///
    /// @return Pointer to the option retrieved or NULL pointer if option
    /// hasn't been found.
    OptionPtr
    retrieveOption(const Host& host, const std::string& option_space,
                   const uint16_t option_code) const {
        if ((option_space != DHCP6_OPTION_SPACE) && (option_space != DHCP4_OPTION_SPACE)) {
            return (OptionPtr());
        }

        // Retrieve a pointer to the appropriate container depending if we're
        // interested in DHCPv4 or DHCPv6 options.
        ConstCfgOptionPtr cfg_option = (option_space == DHCP4_OPTION_SPACE ?
                                        host.getCfgOption4() : host.getCfgOption6());

        // Retrieve options.
        OptionContainerPtr options = cfg_option->getAll(option_space);
        if (options) {
            const OptionContainerTypeIndex& idx = options->get<1>();
            OptionContainerTypeIndex::const_iterator it = idx.find(option_code);
            if (it != idx.end()) {
                return (it->option_);
            }
        }

        return (OptionPtr());
    }

    /// @brief This test verifies that it is possible to specify an empty list
    /// of options for a host.
    ///
    /// @tparam ParserType Type of the parser to be tested.
    template<typename ParserType>
    void testEmptyOptionList() const {
        // Create configuration with empty option list. Note that we have to
        // add reservation for at least one resource because host declarations
        // without any reservations are rejected. Thus, we have added hostname.
        std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
            "\"hostname\": \"foo.isc.org\","
            "\"option-data\": [ ]"
            "}";

        ElementPtr config_element = Element::fromJSON(config);

        HostPtr host;
        ParserType parser;
        ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));

        ASSERT_TRUE(host);

        // There should be no options assigned to a host.
        EXPECT_TRUE(host->getCfgOption4()->empty());
        EXPECT_TRUE(host->getCfgOption6()->empty());
    }

    /// @brief This test verifies that the parser can parse a DHCPv4
    /// reservation configuration including a specific identifier.
    ///
    /// @param identifier_name Identifier name.
    /// @param identifier_type Identifier type.
    void testIdentifier4(const std::string& identifier_name,
                         const std::string& identifier_value,
                         const Host::IdentifierType& /*expected_identifier_type*/,
                         const std::vector<uint8_t>& /*expected_identifier*/) const {
        std::ostringstream config;
        config << "{ \"" << identifier_name << "\": \"" << identifier_value
               << "\","
               << "\"ip-address\": \"192.0.2.112\","
               << "\"hostname\": \"\" }";

        ElementPtr config_element = Element::fromJSON(config.str());

        HostPtr host;
        HostReservationParser4 parser;
        ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
        ASSERT_TRUE(host);

        EXPECT_EQ(10, host->getIPv4SubnetID());
        EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
        EXPECT_EQ("192.0.2.112", host->getIPv4Reservation().toText());
        EXPECT_TRUE(host->getHostname().empty());
    }

    /// @brief This test verifies that the parser returns an error when
    /// configuration is invalid.
    ///
    /// @param config JSON configuration to be tested.
    /// @tparam ParserType Type of the parser class to use.
    template<typename ParserType>
    void testInvalidConfig(const std::string& config) const {
        ElementPtr config_element = Element::fromJSON(config);
        HostPtr host;
        ParserType parser;
        EXPECT_THROW({
            host = parser.parse(SubnetID(10), config_element);
            CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host);
        }, isc::Exception);
    }

    /// @brief HW Address object used by tests.
    HWAddrPtr hwaddr_;

    /// @brief DUID object used by tests.
    DuidPtr duid_;

    /// @brief Vector holding circuit id used by tests.
    std::vector<uint8_t> circuit_id_;

    /// @brief Vector holding client id used by tests.
    std::vector<uint8_t> client_id_;
};

void
HostReservationParserTest::SetUp() {
    CfgMgr::instance().clear();
    // Initialize HW address used by tests.
    const uint8_t hwaddr_data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    hwaddr_ = HWAddrPtr(new HWAddr(hwaddr_data, sizeof(hwaddr_data),
                                   HTYPE_ETHER));

    // Initialize DUID used by tests.
    const uint8_t duid_data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                  0x08, 0x09, 0x0A };
    duid_ = DuidPtr(new DUID(duid_data, sizeof(duid_data)));

    const std::string circuit_id_str = "howdy";
    circuit_id_.assign(circuit_id_str.begin(), circuit_id_str.end());

    client_id_.push_back(0x01); // Client identifier type.
    // Often client id comprises HW address.
    client_id_.insert(client_id_.end(), hwaddr_->hwaddr_.begin(),
                      hwaddr_->hwaddr_.end());
}

void
HostReservationParserTest::TearDown() {
    CfgMgr::instance().clear();
}

/// @brief class of subnet_id reservations
class CfgHostsSubnet : public CfgToElement {
public:
    /// @brief constructor
    CfgHostsSubnet(ConstCfgHostsPtr hosts, SubnetID id)
        : hosts_(hosts), id_(id) { }

    /// @brief unparse method
    ElementPtr toElement() const;

private:
    /// @brief the host reservation configuration
    ConstCfgHostsPtr hosts_;

    /// @brief the subnet ID
    SubnetID id_;
};

ElementPtr
CfgHostsSubnet::toElement() const {
    CfgHostsList list;
    try {
        list.internalize(hosts_->toElement());
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "CfgHostsSubnet::toElement: " << ex.what();
    }
    ElementPtr result = boost::const_pointer_cast<Element>(list.get(id_));

    // Strip
    for (size_t i = 0; i < result->size(); ++i) {
        ElementPtr resv = result->getNonConst(i);
        ConstElementPtr ip_address = resv->get("ip-address");
        if (ip_address && (ip_address->stringValue() == "0.0.0.0")) {
            resv->remove("ip-address");
        }
        ConstElementPtr ip_addresses = resv->get("ip-addresses");
        if (ip_addresses && ip_addresses->empty()) {
            resv->remove("ip-addresses");
        }
        ConstElementPtr prefixes = resv->get("prefixes");
        if (prefixes && prefixes->empty()) {
            resv->remove("prefixes");
        }
        ConstElementPtr hostname = resv->get("hostname");
        if (hostname && hostname->stringValue().empty()) {
            resv->remove("hostname");
        }
        ConstElementPtr next_server = resv->get("next-server");
        if (next_server && (next_server->stringValue() == "0.0.0.0")) {
            resv->remove("next-server");
        }
        ConstElementPtr server_hostname = resv->get("server-hostname");
        if (server_hostname && server_hostname->stringValue().empty()) {
            resv->remove("server-hostname");
        }
        ConstElementPtr boot_file_name = resv->get("boot-file-name");
        if (boot_file_name && boot_file_name->stringValue().empty()) {
            resv->remove("boot-file-name");
        }
        ConstElementPtr client_classes = resv->get("client-classes");
        if (client_classes && client_classes->empty()) {
            resv->remove("client-classes");
        }
        ConstElementPtr option_data = resv->get("option-data");
        if (option_data && option_data->empty()) {
            resv->remove("option-data");
        }
    }
    return (result);
}

// This test verifies that the parser can parse the reservation entry for
// which hw-address is a host identifier.
TEST_F(HostReservationParserTest, dhcp4HWaddr) {
    testIdentifier4("hw-address", "1:2:3:4:5:6", Host::IDENT_HWADDR,
                    hwaddr_->hwaddr_);
}

// This test verifies that the parser can parse the reservation entry for
// which DUID is a host identifier.
TEST_F(HostReservationParserTest, dhcp4DUID) {
    testIdentifier4("duid", "01:02:03:04:05:06:07:08:09:0A",
                    Host::IDENT_DUID, duid_->getDuid());
}

// This test verifies that the parser can parse the reservation entry for
// which DUID specified as a string of hexadecimal digits with '0x' prefix
// is a host identifier
TEST_F(HostReservationParserTest, dhcp4DUIDWithPrefix) {
    testIdentifier4("duid", "0x0102030405060708090A",
                    Host::IDENT_DUID, duid_->getDuid());
}

// This test verifies that the parser can parse a reservation entry for
// which circuit-id is an identifier. The circuit-id is specified as
// a string in quotes.
TEST_F(HostReservationParserTest, dhcp4CircuitIdStringInQuotes) {
    testIdentifier4("circuit-id", "'howdy'", Host::IDENT_CIRCUIT_ID,
                    circuit_id_);
}

// This test verifies that the parser can parse a reservation entry for
// which circuit-id is an identifier. The circuit-id is specified in
// hexadecimal format.
TEST_F(HostReservationParserTest, dhcp4CircuitIdHex) {
    testIdentifier4("circuit-id", "686F776479", Host::IDENT_CIRCUIT_ID,
                    circuit_id_);
}

// This test verifies that the parser can parse a reservation entry for
// which circuit-id is an identifier. The circuit-id is specified in
// hexadecimal format with a '0x' prefix.
TEST_F(HostReservationParserTest, dhcp4CircuitIdHexWithPrefix) {
    testIdentifier4("circuit-id", "0x686F776479", Host::IDENT_CIRCUIT_ID,
                    circuit_id_);
}

// This test verifies that the parser can parse a reservation entry for
// which client-id is an identifier. The client-id is specified in
// hexadecimal format.
TEST_F(HostReservationParserTest, dhcp4ClientIdHex) {
    testIdentifier4("client-id", "01010203040506", Host::IDENT_CLIENT_ID,
                    client_id_);
}

// This test verifies that the parser can parse a reservation entry for
// which client-id is an identifier. The client-id is specified in
// hexadecimal format with a '0x' prefix.
TEST_F(HostReservationParserTest, dhcp4ClientIdHexWithPrefix) {
    testIdentifier4("client-id", "0x01010203040506", Host::IDENT_CLIENT_ID,
                    client_id_);
}

// This test verifies that the parser can parse the reservation entry
// when IPv4 address is specified, but hostname is not.
TEST_F(HostReservationParserTest, dhcp4NoHostname) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0a\","
        "\"ip-address\": \"192.0.2.10\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser4 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(10, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.10", hosts[0]->getIPv4Reservation().toText());
    EXPECT_TRUE(hosts[0]->getHostname().empty());

    // lower duid value
    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[" + config + "]", cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet6(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet6);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that it is possible to specify DHCPv4 client classes
// within the host reservation.
TEST_F(HostReservationParserTest, dhcp4ClientClasses) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"client-classes\": [ \"foo\", \"bar\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser4 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_HWADDR,
                                              &hwaddr_->hwaddr_[0],
                                              hwaddr_->hwaddr_.size()));
    ASSERT_EQ(1, hosts.size());

    const ClientClasses& classes = hosts[0]->getClientClasses4();
    ASSERT_EQ(2, classes.size());
    EXPECT_TRUE(classes.contains("foo"));
    EXPECT_TRUE(classes.contains("bar"));

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[" + config + "]", cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet6(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet6);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that the parser can parse reservation entry
// containing next-server, server-hostname and boot-file-name values for
// DHCPv4 message fields.
TEST_F(HostReservationParserTest, dhcp4MessageFields) {
    std::string config = "{ \"hw-address\": \"1:2:3:4:5:6\","
        "\"next-server\": \"192.0.2.11\","
        "\"server-hostname\": \"some-name.example.org\","
        "\"boot-file-name\": \"/tmp/some-file.efi\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser4 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_HWADDR,
                                              &hwaddr_->hwaddr_[0],
                                              hwaddr_->hwaddr_.size()));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(10, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.11", hosts[0]->getNextServer().toText());
    EXPECT_EQ("some-name.example.org", hosts[0]->getServerHostname());
    EXPECT_EQ("/tmp/some-file.efi", hosts[0]->getBootFileName());

    // canonize hw-address
    config_element->set("hw-address",
                        Element::create(std::string("01:02:03:04:05:06")));
    ElementPtr expected = Element::createList();
    expected->add(config_element);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>(expected, cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet6(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet6);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that the invalid value of the next server is rejected.
TEST_F(HostReservationParserTest, invalidNextServer) {
    // Invalid IPv4 address.
    std::string config = "{ \"hw-address\": \"1:2:3:4:5:6\","
        "\"next-server\": \"192.0.2.foo\" }";
    testInvalidConfig<HostReservationParser4>(config);

    // Broadcast address.
    config = "{ \"hw-address\": \"1:2:3:4:5:6\","
        "\"next-server\": \"255.255.255.255\" }";
    testInvalidConfig<HostReservationParser4>(config);

    // IPv6 address.
    config = "{ \"hw-address\": \"1:2:3:4:5:6\","
        "\"next-server\": \"2001:db8:1::1\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the invalid server hostname is rejected.
TEST_F(HostReservationParserTest, invalidServerHostname) {
    std::ostringstream config;
    config << "{ \"hw-address\": \"1:2:3:4:5:6\","
        "\"server-hostname\": \"";
    config << std::string(64, 'a');
    config << "\" }";
    testInvalidConfig<HostReservationParser4>(config.str());
}

// This test verifies that the invalid boot file name is rejected.
TEST_F(HostReservationParserTest, invalidBootFileName) {
    std::ostringstream config;
    config << "{ \"hw-address\": \"1:2:3:4:5:6\","
        "\"boot-file-name\": \"";
    config << std::string(128, 'a');
    config << "\" }";
    testInvalidConfig<HostReservationParser4>(config.str());
}

// This test verifies that the configuration parser for host reservations
// throws an exception when IPv6 address is specified for IPv4 address
// reservation.
TEST_F(HostReservationParserTest, dhcp4IPv6Address) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"2001:db8:1::1\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when no HW address nor DUID is specified.
TEST_F(HostReservationParserTest, noIdentifier) {
    std::string config = "{ \"ip-address\": \"192.0.2.112\","
        "\"hostname\": \"\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies  that the configuration parser for host reservations
// throws an exception when neither ip address nor hostname is specified.
TEST_F(HostReservationParserTest, noResource) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the parser can parse the reservation entry
// when IP address is not specified, but hostname is specified.
TEST_F(HostReservationParserTest, noIPAddress) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"hostname\": \"foo.example.com\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser4 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(10, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("0.0.0.0", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("foo.example.com", hosts[0]->getHostname());

    // lower duid value
    boost::algorithm::to_lower(config);
    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[" + config + "]", cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet6(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet6);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies  that the configuration parser for host reservations
// throws an exception when hostname is empty, and IP address is not
// specified.
TEST_F(HostReservationParserTest, emptyHostname) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"hostname\": \"\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when invalid IP address is specified.
TEST_F(HostReservationParserTest, malformedAddress) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"192.0.2.bogus\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when zero IP address is specified.
TEST_F(HostReservationParserTest, zeroAddress) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"0.0.0.0\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when broadcast IP address is specified.
TEST_F(HostReservationParserTest, bcastAddress) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"255.255.255.255\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when invalid next server address is specified.
TEST_F(HostReservationParserTest, malformedNextServer) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"next-server\": \"192.0.2.bogus\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when zero next server address is specified.
TEST_F(HostReservationParserTest, zeroNextServer) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"next-server\": \"0.0.0.0\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when broadcast next server address is specified.
TEST_F(HostReservationParserTest, bcastNextServer) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"next-server\": \"255.255.255.255\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when unsupported parameter is specified.
TEST_F(HostReservationParserTest, invalidParameterName) {
    // The "ip-addresses" parameter name is incorrect for the DHCPv4
    // case - it is only valid for DHCPv6 case. Trying to set this
    // parameter should result in error.
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"hostname\": \"foo.bar.isc.org\","
        "\"ip-addresses\": \"2001:db8:1::1\" }";
    testInvalidConfig<HostReservationParser4>(config);
}

// This test verifies that the parser can parse the IPv6 reservation entry for
// which hw-address is a host identifier.
TEST_F(HostReservationParserTest, dhcp6HWaddr) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ],"
        "\"prefixes\": [ \"2001:db8:2000:0101::/64\", "
        "\"2001:db8:2000:0102::/64\" ],"
        "\"hostname\": \"foo.example.com\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser6 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_HWADDR,
                                              &hwaddr_->hwaddr_[0],
                                              hwaddr_->hwaddr_.size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(10, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("foo.example.com", hosts[0]->getHostname());

    IPv6ResrvRange addresses = hosts[0]->
        getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(2, std::distance(addresses.first, addresses.second));

    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::1")),
                                  addresses));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::2")),
                                  addresses));

    IPv6ResrvRange prefixes = hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(2, std::distance(prefixes.first, prefixes.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                            IOAddress("2001:db8:2000:0101::"),
                                            64),
                                  prefixes));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                            IOAddress("2001:db8:2000:0102::"),
                                            64),
                                  prefixes));

    // canonize prefixes
    config_element->set("prefixes",
                        Element::fromJSON("[ \"2001:db8:2000:101::/64\", "
                                          "\"2001:db8:2000:102::/64\" ]"));
    ElementPtr expected = Element::createList();
    expected->add(config_element);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>(expected, cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet4(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet4);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that the parser can parse the IPv6 reservation entry for
// which DUID is a host identifier.
TEST_F(HostReservationParserTest, dhcp6DUID) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"2001:db8:1::100\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ],"
        "\"hostname\": \"foo.example.com\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser6 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(12), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(12, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("foo.example.com", hosts[0]->getHostname());

    IPv6ResrvRange addresses = hosts[0]->
        getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(2, std::distance(addresses.first, addresses.second));

    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::100")),
                                  addresses));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::200")),
                                  addresses));

    IPv6ResrvRange prefixes = hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(0, std::distance(prefixes.first, prefixes.second));

    // remove prefixes and lower duid value
    config_element->remove("prefixes");
    config = prettyPrint(config_element);
    boost::algorithm::to_lower(config);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(12));
    runToElementTest<CfgHostsSubnet>("[" + config + "]", cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet4(cfg_hosts, SubnetID(12));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet4);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that host reservation parser for DHCPv6 rejects
// "circuit-id" as a host identifier.
TEST_F(HostReservationParserTest, dhcp6CircuitId) {
    // Use DHCPv4 specific identifier 'circuit-id' with DHCPv6 parser.
    std::string config = "{ \"circuit-id\": \"'howdy'\","
        "\"ip-addresses\": [ \"2001:db8:1::100\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ],"
        "\"hostname\": \"foo.example.com\" }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that host reservation parser for DHCPv6 rejects
// "client-id" as a host identifier.
TEST_F(HostReservationParserTest, dhcp6ClientId) {
    // Use DHCPv4 specific identifier 'client-id' with DHCPv6 parser.
    std::string config = "{ \"client-id\": \"01010203040506\","
        "\"ip-addresses\": [ \"2001:db8:1::100\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ],"
        "\"hostname\": \"foo.example.com\" }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the parser can parse the IPv6 reservation entry
// which lacks hostname parameter.
TEST_F(HostReservationParserTest, dhcp6NoHostname) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"2001:db8:1::100\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser6 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(12), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(12, hosts[0]->getIPv6SubnetID());
    EXPECT_TRUE(hosts[0]->getHostname().empty());

    IPv6ResrvRange addresses = hosts[0]->
        getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(2, std::distance(addresses.first, addresses.second));

    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::100")),
                                  addresses));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::200")),
                                  addresses));

    IPv6ResrvRange prefixes = hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(0, std::distance(prefixes.first, prefixes.second));

    // remove prefixes and lower duid value
    config_element->remove("prefixes");
    config = prettyPrint(config_element);
    boost::algorithm::to_lower(config);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(12));
    runToElementTest<CfgHostsSubnet>("[" + config + "]", cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet4(cfg_hosts, SubnetID(12));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet4);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that it is possible to specify DHCPv4 client classes
// within the host reservation.
TEST_F(HostReservationParserTest, dhcp6ClientClasses) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"client-classes\": [ \"foo\", \"bar\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser6 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    const ClientClasses& classes = hosts[0]->getClientClasses6();
    ASSERT_EQ(2, classes.size());
    EXPECT_TRUE(classes.contains("foo"));
    EXPECT_TRUE(classes.contains("bar"));

    // lower duid value
    boost::algorithm::to_lower(config);
    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[" + config + "]", cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet4(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet4);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that the configuration parser throws an exception
// when IPv4 address is specified for IPv6 reservation.
TEST_F(HostReservationParserTest, dhcp6IPv4Address) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"192.0.2.3\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when empty address has been specified.
TEST_F(HostReservationParserTest, dhcp6NullAddress) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"\" ],"
        "\"prefixes\": [ ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when invalid prefix length is specified.
TEST_F(HostReservationParserTest, dhcp6InvalidPrefixLength) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"2001:db8:1::/abc\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when empty prefix is specified.
TEST_F(HostReservationParserTest, dhcp6NullPrefix) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"/64\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when only slash is specified for the prefix..
TEST_F(HostReservationParserTest, dhcp6NullPrefix2) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"/\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when slash is missing for the prefix..
TEST_F(HostReservationParserTest, dhcp6NullPrefix3) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"2001:db8:2000:0101::\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when slash is followed by nothing for the prefix..
TEST_F(HostReservationParserTest, dhcp6NullPrefix4) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"2001:db8:2000:0101::/\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when slash is not followed by a number for the prefix..
TEST_F(HostReservationParserTest, dhcp6NullPrefix5) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"2001:db8:2000:0101::/foo\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when the same address is reserved twice.
TEST_F(HostReservationParserTest, dhcp6DuplicatedAddress) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::1\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser throws an exception
// when the same prefix is reserved twice.
TEST_F(HostReservationParserTest, dhcp6DuplicatedPrefix) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"2001:db8:0101::/64\", \"2001:db8:0101::/64\" ] }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when unsupported parameter is specified.
TEST_F(HostReservationParserTest, dhcp6invalidParameterName) {
    // The "ip-address" parameter name is incorrect for the DHCPv6
    // case - it is only valid for DHCPv4 case. Trying to set this
    // parameter should result in error.
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"hostname\": \"foo.bar.isc.org\","
        "\"ip-address\": \"192.0.2.3\" }";
    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that it is possible to specify DHCPv4 options for
// a host.
TEST_F(HostReservationParserTest, options4) {
    // Create configuration with three options for a host.
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"option-data\": ["
        "{"
           "\"name\": \"name-servers\","
           "\"data\": \"172.16.15.10, 172.16.15.20\""
        "},"
        "{"
           "\"name\": \"log-servers\","
           "\"code\": 7,"
           "\"csv-format\": true,"
           "\"space\": \"dhcp4\","
           "\"data\": \"172.16.15.23\","
           "\"always-send\": false"
        "},"
        "{"
           "\"name\": \"default-ip-ttl\","
           "\"data\": \"64\""
        "} ]"
        "}";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser4 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
    ASSERT_TRUE(host);

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_HWADDR,
                                              &hwaddr_->hwaddr_[0],
                                              hwaddr_->hwaddr_.size()));
    ASSERT_EQ(1, hosts.size());

    // Retrieve and sanity check name servers.
    Option4AddrLstPtr opt_dns = boost::dynamic_pointer_cast<
        Option4AddrLst>(retrieveOption(*hosts[0], DHCP4_OPTION_SPACE, DHO_NAME_SERVERS));
    ASSERT_TRUE(opt_dns);
    Option4AddrLst::AddressContainer dns_addrs = opt_dns->getAddresses();
    ASSERT_EQ(2, dns_addrs.size());
    EXPECT_EQ("172.16.15.10", dns_addrs[0].toText());
    EXPECT_EQ("172.16.15.20", dns_addrs[1].toText());

    // Retrieve and sanity check log servers.
    Option4AddrLstPtr opt_log = boost::dynamic_pointer_cast<
        Option4AddrLst>(retrieveOption(*hosts[0], DHCP4_OPTION_SPACE, DHO_LOG_SERVERS));
    ASSERT_TRUE(opt_log);
    Option4AddrLst::AddressContainer log_addrs = opt_log->getAddresses();
    ASSERT_EQ(1, log_addrs.size());
    EXPECT_EQ("172.16.15.23", log_addrs[0].toText());

    // Retrieve and sanity check default IP TTL.
    OptionUint8Ptr opt_ttl = boost::dynamic_pointer_cast<
        OptionUint8>(retrieveOption(*hosts[0], DHCP4_OPTION_SPACE, DHO_DEFAULT_IP_TTL));
    ASSERT_TRUE(opt_ttl);
    EXPECT_EQ(64, opt_ttl->getValue());

    // Canonize the config
    ElementPtr option = config_element->get("option-data")->getNonConst(0);
    option->set("code", Element::create(DHO_NAME_SERVERS));
    option->set("space", Element::create(std::string(DHCP4_OPTION_SPACE)));
    option->set("csv-format", Element::create(true));
    option->set("always-send", Element::create(false));
    option = config_element->get("option-data")->getNonConst(1);
    option = config_element->get("option-data")->getNonConst(2);
    option->set("code", Element::create(DHO_DEFAULT_IP_TTL));
    option->set("space", Element::create(std::string(DHCP4_OPTION_SPACE)));
    option->set("csv-format", Element::create(true));
    option->set("always-send", Element::create(false));
    ElementPtr expected = Element::createList();
    expected->add(config_element);

    // Try to unparse it.
    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>(expected, cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet6(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet6);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that it is possible to specify DHCPv6 options for
// a host.
TEST_F(HostReservationParserTest, options6) {
    // Create configuration with three options for a host.
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"option-data\": ["
        "{"
           "\"name\": \"dns-servers\","
           "\"data\": \"2001:db8:1::1, 2001:db8:1::2\""
        "},"
        "{"
           "\"name\": \"nis-servers\","
           "\"code\": 27,"
           "\"csv-format\": true,"
           "\"space\": \"dhcp6\","
           "\"data\": \"2001:db8:1::1204\","
           "\"always-send\": true"
        "},"
        "{"
           "\"name\": \"preference\","
           "\"data\": \"11\""
        "} ]"
        "}";

    ElementPtr config_element = Element::fromJSON(config);

    HostPtr host;
    HostReservationParser6 parser;
    ASSERT_NO_THROW(host = parser.parse(SubnetID(10), config_element));
    ASSERT_TRUE(host);

    // One host should have been added to the configuration.
    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_NO_THROW(cfg_hosts->add(host));

    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    // Retrieve and sanity check DNS servers option.
    Option6AddrLstPtr opt_dns = boost::dynamic_pointer_cast<
        Option6AddrLst>(retrieveOption(*hosts[0], DHCP6_OPTION_SPACE, D6O_NAME_SERVERS));
    ASSERT_TRUE(opt_dns);
    Option6AddrLst::AddressContainer dns_addrs = opt_dns->getAddresses();
    ASSERT_EQ(2, dns_addrs.size());
    EXPECT_EQ("2001:db8:1::1", dns_addrs[0].toText());
    EXPECT_EQ("2001:db8:1::2", dns_addrs[1].toText());

    // Retrieve and sanity check NIS servers option.
    Option6AddrLstPtr opt_nis = boost::dynamic_pointer_cast<
        Option6AddrLst>(retrieveOption(*hosts[0], DHCP6_OPTION_SPACE, D6O_NIS_SERVERS));
    ASSERT_TRUE(opt_nis);
    Option6AddrLst::AddressContainer nis_addrs = opt_nis->getAddresses();
    ASSERT_EQ(1, nis_addrs.size());
    EXPECT_EQ("2001:db8:1::1204", nis_addrs[0].toText());

    // Retrieve and sanity check preference option.
    OptionUint8Ptr opt_prf = boost::dynamic_pointer_cast<
        OptionUint8>(retrieveOption(*hosts[0], DHCP6_OPTION_SPACE, D6O_PREFERENCE));
    ASSERT_TRUE(opt_prf);
    EXPECT_EQ(11, opt_prf->getValue());

    // Canonize the config
    ElementPtr option = config_element->get("option-data")->getNonConst(0);
    option->set("code", Element::create(D6O_NAME_SERVERS));
    option->set("space", Element::create(std::string(DHCP6_OPTION_SPACE)));
    option->set("csv-format", Element::create(true));
    option->set("always-send", Element::create(false));
    option = config_element->get("option-data")->getNonConst(1);
    option = config_element->get("option-data")->getNonConst(2);
    option->set("code", Element::create(D6O_PREFERENCE));
    option->set("space", Element::create(std::string(DHCP6_OPTION_SPACE)));
    option->set("csv-format", Element::create(true));
    option->set("always-send", Element::create(false));
    config = prettyPrint(config_element);
    boost::algorithm::to_lower(config);

    // Try to unparse it.
    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[" + config + "]", cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet4(cfg_hosts, SubnetID(10));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet4);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that it is possible to specify an empty list of
// DHCPv4 options for a host declaration.
TEST_F(HostReservationParserTest, options4Empty) {
    testEmptyOptionList<HostReservationParser4>();
}

// This test verifies that it is possible to specify an empty list of
// DHCPv6 options for a host declaration.
TEST_F(HostReservationParserTest, options6Empty) {
    testEmptyOptionList<HostReservationParser6>();
}

// This test checks that specifying DHCPv6 options for the DHCPv4 host
// reservation parser is not allowed.
TEST_F(HostReservationParserTest, options4InvalidOptionSpace) {
    // Create configuration specifying DHCPv6 option for a DHCPv4 host
    // reservation parser.
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"option-data\": ["
        "{"
           "\"name\": \"dns-servers\","
           "\"space\": \"dhcp6\","
           "\"data\": \"2001:db8:1::1, 2001:db8:1::2\""
        "} ]"
        "}";

    testInvalidConfig<HostReservationParser4>(config);
}

// This test checks that specifying DHCPv4 options for the DHCPv6 host
// reservation parser is not allowed.
TEST_F(HostReservationParserTest, options6InvalidOptionSpace) {
    // Create configuration specifying DHCPv4 option for a DHCPv6 host
    // reservation parser.
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"option-data\": ["
        "{"
           "\"name\": \"name-servers\","
           "\"space\": \"dhcp4\","
           "\"data\": \"172.16.15.10, 172.16.15.20\""
        "} ]"
        "}";

    testInvalidConfig<HostReservationParser6>(config);
}

// This test verifies that host identifiers for DHCPv4 are mutually exclusive.
TEST_F(HostReservationParserTest, mutuallyExclusiveIdentifiers4) {
    std::vector<std::string> identifiers;
    identifiers.push_back("hw-address");
    identifiers.push_back("duid");
    identifiers.push_back("circuit-id");

    for (unsigned int i = 0; i < identifiers.size(); ++i) {
        // j points to an index of the next identifier. If it
        // overflows, we set it to 0.
        unsigned int j = (i + 1) % (identifiers.size());
        Host::IdentifierType first = static_cast<Host::IdentifierType>(i);
        Host::IdentifierType second = static_cast<Host::IdentifierType>(j);

        SCOPED_TRACE("Using identifiers " + Host::getIdentifierName(first)
                     + " and " + Host::getIdentifierName(second));

        // Create configuration with two different identifiers.
        std::ostringstream config;
        config << "{ \"" << Host::getIdentifierName(first) << "\": \"121314151617\","
            "\"" << Host::getIdentifierName(second) << "\": \"0A0B0C0D0E0F\","
            "\"ip-address\": \"192.0.2.3\" }";
        testInvalidConfig<HostReservationParser4>(config.str());
    }
}

// This test verifies that host identifiers for DHCPv6 are mutually exclusive.
TEST_F(HostReservationParserTest, mutuallyExclusiveIdentifiers6) {
    std::vector<std::string> identifiers;
    identifiers.push_back("hw-address");
    identifiers.push_back("duid");

    for (unsigned int i = 0; i < identifiers.size(); ++i) {
        // j points to an index of the next identifier. If it
        // overflows, we set it to 0.
        unsigned int j = (i + 1) % (identifiers.size());

        SCOPED_TRACE("Using identifiers " + identifiers[i] + " and "
                     + identifiers[j]);

        // Create configuration with two different identifiers.
        std::ostringstream config;
        config << "{ \"" << identifiers[i] << "\": \"121314151617\","
            "\"" << identifiers[j] << "\": \"0A0B0C0D0E0F\","
            "\"ip-addresses\": \"2001:db8:1::1\" }";
        testInvalidConfig<HostReservationParser6>(config.str());
    }
}

/// @brief Test fixture class for @ref HostReservationIdsParser.
class HostReservationIdsParserTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Clears current configuration.
    HostReservationIdsParserTest() {
        CfgMgr::instance().clear();
    }

    /// @brief Destructor.
    ///
    /// Clears current configuration.
    virtual ~HostReservationIdsParserTest() {
        CfgMgr::instance().clear();
    }

    /// @brief Test verifies that invalid configuration causes an error.
    ///
    /// @param config Configuration string.
    /// @tparam ParserType @ref HostReservationIdsParser4 or
    /// @ref HostReservationIdsParser6
    template<typename ParserType>
    void testInvalidConfig(const std::string& config) const {
        ElementPtr config_element = Element::fromJSON(config);
        ParserType parser;
        EXPECT_THROW(parser.parse(config_element), DhcpConfigError);
    }

};

// Test that list of supported DHCPv4 identifiers list is correctly
// parsed.
TEST_F(HostReservationIdsParserTest, dhcp4Identifiers) {
    std::string config =
        "[ \"circuit-id\", \"duid\", \"hw-address\", \"client-id\" ]";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationIdsParser4 parser;
    ASSERT_NO_THROW(parser.parse(config_element));

    ConstCfgHostOperationsPtr cfg = CfgMgr::instance().getStagingCfg()->
        getCfgHostOperations4();
    const CfgHostOperations::IdentifierTypes& ids = cfg->getIdentifierTypes();
    ASSERT_EQ(4, ids.size());

    CfgHostOperations::IdentifierTypes::const_iterator id = ids.begin();
    EXPECT_EQ(*id++, Host::IDENT_CIRCUIT_ID);
    EXPECT_EQ(*id++, Host::IDENT_DUID);
    EXPECT_EQ(*id++, Host::IDENT_HWADDR);
    EXPECT_EQ(*id++, Host::IDENT_CLIENT_ID);

    runToElementTest<CfgHostOperations>(config, *cfg);
}

// Test that list of supported DHCPv6 identifiers list is correctly
// parsed.
TEST_F(HostReservationIdsParserTest, dhcp6Identifiers) {
    std::string config = "[ \"duid\", \"hw-address\" ]";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationIdsParser6 parser;
    ASSERT_NO_THROW(parser.parse(config_element));

    ConstCfgHostOperationsPtr cfg = CfgMgr::instance().getStagingCfg()->
        getCfgHostOperations6();
    const CfgHostOperations::IdentifierTypes& ids = cfg->getIdentifierTypes();
    ASSERT_EQ(2, ids.size());

    CfgHostOperations::IdentifierTypes::const_iterator id = ids.begin();
    EXPECT_EQ(*id++, Host::IDENT_DUID);
    EXPECT_EQ(*id++, Host::IDENT_HWADDR);

    runToElementTest<CfgHostOperations>(config, *cfg);
}

// Test that invalid DHCPv4 identifier causes error.
TEST_F(HostReservationIdsParserTest, dhcp4InvalidIdentifier) {
    // Create configuration including unsupported identifier.
    std::string config = "[ \"unsupported-id\" ]";
    testInvalidConfig<HostReservationIdsParser4>(config);
}

// Test that invalid DHCPv6 identifier causes error.
TEST_F(HostReservationIdsParserTest, dhcp6InvalidIdentifier) {
    // Create configuration including unsupported identifier for DHCPv6.
    // The circuit-id is only supported in DHCPv4.
    std::string config = "[ \"circuit-id\" ]";
    testInvalidConfig<HostReservationIdsParser6>(config);
}

// Check that all supported identifiers are used when 'auto' keyword
// is specified for DHCPv4 case.
TEST_F(HostReservationIdsParserTest, dhcp4AutoIdentifiers) {
    std::string config = "[ \"auto\" ]";
    ElementPtr config_element = Element::fromJSON(config);

    HostReservationIdsParser4 parser;
    ASSERT_NO_THROW(parser.parse(config_element));

    ConstCfgHostOperationsPtr cfg = CfgMgr::instance().getStagingCfg()->
        getCfgHostOperations4();
    const CfgHostOperations::IdentifierTypes& ids = cfg->getIdentifierTypes();
    ASSERT_EQ(5, ids.size());

    CfgHostOperations::IdentifierTypes::const_iterator id = ids.begin();
    EXPECT_EQ(*id++, Host::IDENT_HWADDR);
    EXPECT_EQ(*id++, Host::IDENT_DUID);
    EXPECT_EQ(*id++, Host::IDENT_CIRCUIT_ID);
    EXPECT_EQ(*id++, Host::IDENT_CLIENT_ID);
    EXPECT_EQ(*id++, Host::IDENT_FLEX);
}

// This test verifies that use of "auto" together with an explicit
// identifier causes an error. "auto" is placed before the explicit
// identifier.
TEST_F(HostReservationIdsParserTest, dhcp4AutoBeforeIdentifier) {
    std::string config = "[ \"auto\", \"duid\" ]";
    testInvalidConfig<HostReservationIdsParser4>(config);
}

// This test verifies that use of "auto" together with an explicit
// identifier causes an error. "auto" is placed after the explicit
// identifier.
TEST_F(HostReservationIdsParserTest, dhcp4AutoAfterIdentifier) {
    std::string config = "[ \"duid\", \"auto\" ]";
    testInvalidConfig<HostReservationIdsParser4>(config);
}

// Test that empty list of identifier types is not allowed.
TEST_F(HostReservationIdsParserTest, dhcp4EmptyList) {
    std::string config = "[ ]";
    testInvalidConfig<HostReservationIdsParser4>(config);
}

// Check that all supported identifiers are used when 'auto' keyword
// is specified for DHCPv6 case.
TEST_F(HostReservationIdsParserTest, dhcp6AutoIdentifiers) {
    std::string config = "[ \"auto\" ]";
    ElementPtr config_element = Element::fromJSON(config);

    HostReservationIdsParser6 parser;
    ASSERT_NO_THROW(parser.parse(config_element));

    ConstCfgHostOperationsPtr cfg = CfgMgr::instance().getStagingCfg()->
        getCfgHostOperations6();
    const CfgHostOperations::IdentifierTypes& ids = cfg->getIdentifierTypes();
    ASSERT_EQ(3, ids.size());

    CfgHostOperations::IdentifierTypes::const_iterator id = ids.begin();
    EXPECT_EQ(*id++, Host::IDENT_HWADDR);
    EXPECT_EQ(*id++, Host::IDENT_DUID);
    EXPECT_EQ(*id++, Host::IDENT_FLEX);
}

// This test verifies that use of "auto" together with an explicit
// identifier causes an error. "auto" is placed before the explicit
// identifier.
TEST_F(HostReservationIdsParserTest, dhcp6AutoBeforeIdentifier) {
    std::string config = "[ \"auto\", \"duid\" ]";
    testInvalidConfig<HostReservationIdsParser6>(config);
}

// This test verifies that use of "auto" together with an explicit
// identifier causes an error. "auto" is placed after the explicit
// identifier.
TEST_F(HostReservationIdsParserTest, dhcp6AutoAfterIdentifier) {
    std::string config = "[ \"duid\", \"auto\" ]";
    testInvalidConfig<HostReservationIdsParser6>(config);
}

// Test that empty list of identifier types is not allowed.
TEST_F(HostReservationIdsParserTest, dhcp6EmptyList) {
    std::string config = "[ ]";
    testInvalidConfig<HostReservationIdsParser6>(config);
}

} // end of anonymous namespace
