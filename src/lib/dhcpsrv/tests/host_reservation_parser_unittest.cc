// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <gtest/gtest.h>
#include <iterator>
#include <string>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c HostReservationParser.
class HostReservationParserTest : public ::testing::Test {
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

    void
    expectFailure(const HostReservationParser& parser,
                  const std::string& config) const;

    /// @brief HW Address object used by tests.
    HWAddrPtr hwaddr_;

    /// @brief DUID object used by tests.
    DuidPtr duid_;

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
}

void
HostReservationParserTest::TearDown() {
    CfgMgr::instance().clear();
}

// This test verfies that the parser can parse the reservation entry for
// which hw-address is a host identifier.
TEST_F(HostReservationParserTest, dhcp4HWaddr) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"192.0.2.134\","
        "\"hostname\": \"foo.example.com\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(1));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(hwaddr_, DuidPtr()));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(0, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.134", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("foo.example.com", hosts[0]->getHostname());
}

// This test verfies that the parser can parse the reservation entry for
// which DUID is a host identifier.
TEST_F(HostReservationParserTest, dhcp4DUID) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-address\": \"192.0.2.112\","
        "\"hostname\": \"\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(HWAddrPtr(), duid_));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(10, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(0, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.112", hosts[0]->getIPv4Reservation().toText());
    EXPECT_TRUE(hosts[0]->getHostname().empty());
}

// This test verifies that the parser can parse the reservation entry
// when IPv4 address is specified, but hostname is not.
TEST_F(HostReservationParserTest, dhcp4NoHostname) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-address\": \"192.0.2.10\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(HWAddrPtr(), duid_));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(10, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(0, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.10", hosts[0]->getIPv4Reservation().toText());
    EXPECT_TRUE(hosts[0]->getHostname().empty());
}


// This test verifies that the configuration parser for host reservations
// throws an exception when IPv6 address is specified for IPv4 address
// reservation.
TEST_F(HostReservationParserTest, dhcp4IPv6Address) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"2001:db8:1::1\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when no HW address nor DUID is specified.
TEST_F(HostReservationParserTest, noIdentifier) {
    std::string config = "{ \"ip-address\": \"192.0.2.112\","
        "\"hostname\": \"\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies  that the configuration parser for host reservations
// throws an exception when neither ip address nor hostname is specified.
TEST_F(HostReservationParserTest, noResource) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the parser can parse the reservation entry
// when IP address is not specified, but hostname is specified.
TEST_F(HostReservationParserTest, noIPAddress) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"hostname\": \"foo.example.com\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(HWAddrPtr(), duid_));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(10, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(0, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ("0.0.0.0", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("foo.example.com", hosts[0]->getHostname());
}

// This test verifies  that the configuration parser for host reservations
// throws an exception when hostname is empty, and IP address is not
// specified.
TEST_F(HostReservationParserTest, emptyHostname) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"hostname\": \"\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when invalid IP address is specified.
TEST_F(HostReservationParserTest, malformedAddress) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"192.0.2.bogus\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when zero IP address is specified.
TEST_F(HostReservationParserTest, zeroAddress) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"0.0.0.0\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser for host reservations
// throws an exception when broadcast IP address is specified.
TEST_F(HostReservationParserTest, bcastAddress) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"255.255.255.255\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
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

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser4 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verfies that the parser can parse the IPv6 reservation entry for
// which hw-address is a host identifier.
TEST_F(HostReservationParserTest, dhcp6HWaddr) {
    std::string config = "{ \"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ],"
        "\"prefixes\": [ \"2001:db8:2000:0101::/64\", "
        "\"2001:db8:2000:0102::/64\" ],"
        "\"hostname\": \"foo.example.com\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(10));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(hwaddr_, DuidPtr()));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(0, hosts[0]->getIPv4SubnetID());
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

}

// This test verfies that the parser can parse the IPv6 reservation entry for
// which DUID is a host identifier.
TEST_F(HostReservationParserTest, dhcp6DUID) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"2001:db8:1::100\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ],"
        "\"hostname\": \"foo.example.com\" }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(HWAddrPtr(), duid_));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(0, hosts[0]->getIPv4SubnetID());
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
}

// This test verfies that the parser can parse the IPv6 reservation entry
// which lacks hostname parameter.
TEST_F(HostReservationParserTest, dhcp6NoHostname) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"2001:db8:1::100\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    ASSERT_NO_THROW(parser.build(config_element));

    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    HostCollection hosts;
    ASSERT_NO_THROW(hosts = cfg_hosts->getAll(HWAddrPtr(), duid_));

    ASSERT_EQ(1, hosts.size());

    EXPECT_EQ(0, hosts[0]->getIPv4SubnetID());
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
}


// This test verifies that the configuration parser throws an exception
// when IPv4 address is specified for IPv6 reservation.
TEST_F(HostReservationParserTest, dhcp6IPv4Address) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"192.0.2.3\", \"2001:db8:1::200\" ],"
        "\"prefixes\": [ ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser throws an exception
// when empty address has been specified.
TEST_F(HostReservationParserTest, dhcp6NullAddress) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"\" ],"
        "\"prefixes\": [ ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser throws an exception
// when invalid prefix length is specified.
TEST_F(HostReservationParserTest, dhcp6InvalidPrefixLength) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"2001:db8:1::/abc\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser throws an exception
// when empty prefix is specified.
TEST_F(HostReservationParserTest, dhcp6NullPrefix) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"/64\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser throws an exception
// when only slash is specified for the prefix..
TEST_F(HostReservationParserTest, dhcp6NullPrefix2) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"/\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser throws an exception
// when the same address is reserved twice.
TEST_F(HostReservationParserTest, dhcp6DuplicatedAddress) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::1\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test verifies that the configuration parser throws an exception
// when the same prefix is reserved twice.
TEST_F(HostReservationParserTest, dhcp6DuplicatedPrefix) {
    std::string config = "{ \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "\"prefixes\": [ \"2001:db8:0101::/64\", \"2001:db8:0101::/64\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(12));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
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

    ElementPtr config_element = Element::fromJSON(config);

    HostReservationParser6 parser(SubnetID(10));
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

} // end of anonymous namespace
