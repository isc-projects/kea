// Copyright (C) 2014-2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfg_hosts_util.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/host_reservations_list_parser.h>
#include <testutils/test_to_element.h>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::test;

namespace {

/// @brief Test fixture class for @c HostReservationsListParser.
class HostReservationsListParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    HostReservationsListParserTest() = default;

    /// @brief Destructor
    virtual ~HostReservationsListParserTest() = default;

protected:
    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr. It also initializes
    /// hwaddr_ and duid_ class members.
    virtual void SetUp();

    /// @brief Clean up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();

    /// @brief HW Address object used by tests.
    HWAddrPtr hwaddr_;

    /// @brief DUID object used by tests.
    DuidPtr duid_;
};

void
HostReservationsListParserTest::SetUp() {
    CfgMgr::instance().clear();
    // Initialize HW address used by tests.
    const uint8_t hwaddr_data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    hwaddr_ = HWAddrPtr(new HWAddr(hwaddr_data, sizeof(hwaddr_data),
                                   HTYPE_ETHER));

    // Initialize DUID used by tests.
    const uint8_t duid_data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                  0x08, 0x09, 0x0A };
    duid_ = DuidPtr(new DUID(duid_data, sizeof(duid_data)));
}

void
HostReservationsListParserTest::TearDown() {
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

// This test verifies that the parser for the list of the host reservations
// parses IPv4 reservations correctly.
TEST_F(HostReservationsListParserTest, ipv4Reservations) {
    CfgMgr::instance().setFamily(AF_INET);
    // hexadecimal in lower case for toElement()
    std::string config =
        "[ "
        "  { "
        "   \"hw-address\": \"01:02:03:04:05:06\","
        "   \"ip-address\": \"192.0.2.134\","
        "   \"hostname\": \"foo.example.com\""
        "  }, "
        "  { "
        "   \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "   \"ip-address\": \"192.0.2.110\","
        "   \"hostname\": \"bar.example.com\""
        "  } "
        "]";

    ElementPtr config_element = Element::fromJSON(config);

    HostCollection hosts;
    HostReservationsListParser<HostReservationParser4> parser;
    ASSERT_NO_THROW(parser.parse(SubnetID(1), config_element, hosts));

    for (auto h = hosts.begin(); h != hosts.end(); ++h) {
        CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(*h);
    }

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();

    // Get the first reservation for the host identified by the HW address.
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_HWADDR,
                                              &hwaddr_->hwaddr_[0],
                                              hwaddr_->hwaddr_.size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.134", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("foo.example.com", hosts[0]->getHostname());

    // Get the second reservation for the host identified by the DUID.
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.110", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("bar.example.com", hosts[0]->getHostname());

    // Get back the config from cfg_hosts
    boost::algorithm::to_lower(config);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>(config, cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet6(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet6);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SUBNET_ID_UNUSED);
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that an attempt to add two reservations with the
// same identifier value will return an error.
TEST_F(HostReservationsListParserTest, duplicatedIdentifierValue4) {
    std::vector<std::string> identifiers;
    identifiers.push_back("hw-address");
    identifiers.push_back("duid");
    identifiers.push_back("circuit-id");
    identifiers.push_back("flex-id");

    for (unsigned int i = 0; i < identifiers.size(); ++i) {
        SCOPED_TRACE("Using identifier " + identifiers[i]);

        std::ostringstream config;
        config <<
            "[ "
            "  { "
            "   \"" << identifiers[i] << "\": \"010203040506\","
            "   \"ip-address\": \"192.0.2.134\","
            "   \"hostname\": \"foo.example.com\""
            "  }, "
            "  { "
            "   \"" << identifiers[i] << "\": \"010203040506\","
            "   \"ip-address\": \"192.0.2.110\","
            "   \"hostname\": \"bar.example.com\""
            "  } "
            "]";

        ElementPtr config_element = Element::fromJSON(config.str());

        HostCollection hosts;
        HostReservationsListParser<HostReservationParser4> parser;
        EXPECT_THROW({
                parser.parse(SubnetID(1), config_element, hosts);
                for (auto h = hosts.begin(); h != hosts.end(); ++h) {
                    CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(*h);
                }
            }, DuplicateHost);
        // The code threw exception, because the second insertion failed.
        // Nevertheless, the first host insertion succeeded, so the next
        // time we try to insert them, we will get ReservedAddress exception,
        // rather than DuplicateHost. Therefore we need to remove the
        // first host that's still there.
        CfgMgr::instance().clear();
    }
}

// This test verifies that the parser for the list of the host reservations
// parses IPv6 reservations correctly.
TEST_F(HostReservationsListParserTest, ipv6Reservations) {
    // hexadecimal in lower case for toElement()
    std::string config =
        "[ "
        "  { \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "    \"ip-addresses\": [ ],"
        "    \"prefixes\": [ \"2001:db8:1:2::/80\" ],"
        "    \"hostname\": \"foo.example.com\" "
        "  }, "
        "  { \"hw-address\": \"01:02:03:04:05:06\","
        "    \"ip-addresses\": [ \"2001:db8:1::123\" ],"
        "    \"hostname\": \"bar.example.com\" "
        "  } "
        "]";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration.
    HostCollection hosts;
    HostReservationsListParser<HostReservationParser6> parser;
    ASSERT_NO_THROW(parser.parse(SubnetID(2), config_element, hosts));

    for (auto h = hosts.begin(); h != hosts.end(); ++h) {
        CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(*h);
    }

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();

    // Get the reservation for the host identified by the HW address.
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_HWADDR,
                                              &hwaddr_->hwaddr_[0],
                                              hwaddr_->hwaddr_.size()));
    ASSERT_EQ(1, hosts.size());

    // Make sure it belongs to a valid subnet.
    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(2, hosts[0]->getIPv6SubnetID());

    // Get the reserved addresses for the host. There should be exactly one
    // address reserved for this host.
    IPv6ResrvRange prefixes =
        hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(1, std::distance(prefixes.first, prefixes.second));

    EXPECT_EQ(IPv6Resrv::TYPE_NA, prefixes.first->second.getType());
    EXPECT_EQ("2001:db8:1::123", prefixes.first->second.getPrefix().toText());
    EXPECT_EQ(128, prefixes.first->second.getPrefixLen());

    // Validate the second reservation.
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(Host::IDENT_DUID,
                                              &duid_->getDuid()[0],
                                              duid_->getDuid().size()));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(SUBNET_ID_UNUSED, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(2, hosts[0]->getIPv6SubnetID());

    // This reservation was for a prefix, instead of an IPv6 address.
    prefixes = hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(1, std::distance(prefixes.first, prefixes.second));

    EXPECT_EQ(IPv6Resrv::TYPE_PD, prefixes.first->second.getType());
    EXPECT_EQ("2001:db8:1:2::", prefixes.first->second.getPrefix().toText());
    EXPECT_EQ(80, prefixes.first->second.getPrefixLen());

    // Get back the config from cfg_hosts
    ElementPtr resv = config_element->getNonConst(0);
    resv->remove("ip-addresses");
    config = prettyPrint(config_element);
    boost::algorithm::to_lower(config);
    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet(cfg_hosts, SubnetID(2));
    runToElementTest<CfgHostsSubnet>(config, cfg_subnet);

    CfgMgr::instance().setFamily(AF_INET);
    CfgHostsSubnet cfg_subnet4(cfg_hosts, SubnetID(2));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet4);

    CfgMgr::instance().setFamily(AF_INET6);
    CfgHostsSubnet cfg_subnet1(cfg_hosts, SubnetID(1));
    runToElementTest<CfgHostsSubnet>("[ ]", cfg_subnet1);
}

// This test verifies that an attempt to add two reservations with the
// same identifier value will return an error.
TEST_F(HostReservationsListParserTest, duplicatedIdentifierValue6) {
    std::vector<std::string> identifiers;
    identifiers.push_back("hw-address");
    identifiers.push_back("duid");
    identifiers.push_back("flex-id");

    for (unsigned int i = 0; i < identifiers.size(); ++i) {
        SCOPED_TRACE("Using identifier " + identifiers[i]);

        std::ostringstream config;
        config <<
            "[ "
            "  { "
            "   \"" << identifiers[i] << "\": \"010203040506\","
            "   \"ip-addresses\": [ \"2001:db8:1::123\" ],"
            "   \"hostname\": \"foo.example.com\""
            "  }, "
            "  { "
            "   \"" << identifiers[i] << "\": \"010203040506\","
            "   \"ip-addresses\": [ \"2001:db8:1::123\" ],"
            "   \"hostname\": \"bar.example.com\""
            "  } "
            "]";

        ElementPtr config_element = Element::fromJSON(config.str());

        HostCollection hosts;
        HostReservationsListParser<HostReservationParser6> parser;
        EXPECT_THROW({
            parser.parse(SubnetID(1), config_element, hosts);
            for (auto h = hosts.begin(); h != hosts.end(); ++h) {
                CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(*h);
            }
        }, DuplicateHost);
    }
}

} // end of anonymous namespace
