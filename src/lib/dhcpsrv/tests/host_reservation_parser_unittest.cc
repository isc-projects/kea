// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_reservation_parser.h>
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

    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1::1")),
                                  addresses));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1::2")),
                                  addresses));

    IPv6ResrvRange prefixes = hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(2, std::distance(prefixes.first, prefixes.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:2000:0101::"),
                                            64),
                                  prefixes));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:2000:0102::"),
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

    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1::100")),
                                  addresses));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1::200")),
                                  addresses));

    IPv6ResrvRange prefixes = hosts[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(0, std::distance(prefixes.first, prefixes.second));
}


} // end of anonymous namespace
