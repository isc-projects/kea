// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/host_reservations_list_parser.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c HostReservationsListParser.
class HostReservationsListParserTest : public ::testing::Test {
protected:

    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr. It alse initializes
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

// This test verifies that the parser for the list of the host reservations
// parses IPv4 reservations correctly.
TEST_F(HostReservationsListParserTest, ipv4Reservations) {
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

    HostReservationsListParser<HostReservationParser4> parser(SubnetID(1));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;

    // Get the first reservation for the host identified by the HW address.
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(hwaddr_));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(0, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.134", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("foo.example.com", hosts[0]->getHostname());

    // Get the second reservation for the host identified by the DUID.
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(HWAddrPtr(), duid_));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(0, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.110", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("bar.example.com", hosts[0]->getHostname());
}

// This test verifies that the parser for the list of the host reservations
// parses IPv6 reservations correctly.
TEST_F(HostReservationsListParserTest, ipv6Reservations) {
    std::string config = 
        "[ "
        "  { \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "    \"ip-addresses\": [ ],"
        "    \"prefixes\": [ \"2001:db8:1:2::/80\" ],"
        "    \"hostname\": \"foo.example.com\" "
        "  }, "
        "  { \"hw-address\": \"01:02:03:04:05:06\","
        "    \"ip-addresses\": [ \"2001:db8:1::123\" ],"
        "    \"prefixes\": [ ],"
        "    \"hostname\": \"bar.example.com\" "
        "  } "
        "]";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration.
    HostReservationsListParser<HostReservationParser6> parser(SubnetID(2));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;

    // Get the reservation for the host identified by the HW address.
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(hwaddr_));
    ASSERT_EQ(1, hosts.size());

    // Make sure it belongs to a valid subnet.
    EXPECT_EQ(0, hosts[0]->getIPv4SubnetID());
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
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(HWAddrPtr(), duid_));
    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(0, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(2, hosts[0]->getIPv6SubnetID());

    // This reservation was for a prefix, instead of an IPv6 address.
    prefixes = hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(1, std::distance(prefixes.first, prefixes.second));

    EXPECT_EQ(IPv6Resrv::TYPE_PD, prefixes.first->second.getType());
    EXPECT_EQ("2001:db8:1:2::", prefixes.first->second.getPrefix().toText());
    EXPECT_EQ(80, prefixes.first->second.getPrefixLen());
}

} // end of anonymous namespace
