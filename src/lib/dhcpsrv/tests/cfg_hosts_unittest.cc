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
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/host.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

/// @brief Test fixture class for testing @c CfgHost object holding
/// host reservations specified in the configuration file.
class CfgHostsTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// This constructor allocates a collection of @c HWAddr and @c DuidPtr
    /// objects used by the unit tests.
    ///
    /// The allocated HW addresses use the following pattern: 01:02:0A:BB:03:XX
    /// where XX is a number between 0 and 0x32. All of them are of the
    /// HTYPE_ETHER type.
    ///
    /// The allocated DUID LLTs use the following pattern:
    /// 01:02:03:04:05:06:07:08:09:0A:XX where the XX is a number between
    /// 0 and 0x32.
    CfgHostsTest();

    /// @brief Increases last byte of an address.
    ///
    /// @param address Address to be increased.
    IOAddress increase(const IOAddress& address, const uint8_t num) const;

    /// @brief Collection of HW address objects allocated for unit tests.
    std::vector<HWAddrPtr> hwaddrs_;
    /// @brief Collection of DUIDs allocated for unit tests.
    std::vector<DuidPtr> duids_;
};

CfgHostsTest::CfgHostsTest() {
    const uint8_t mac_template[] = {
        0x01, 0x02, 0x0A, 0xBB, 0x03, 0x00
    };
    for (int i = 0; i < 50; ++i) {
        std::vector<uint8_t> vec(mac_template,
                                 mac_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        HWAddrPtr hwaddr(new HWAddr(vec, HTYPE_ETHER));
        hwaddrs_.push_back(hwaddr);
    }

    const uint8_t duid_template[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x00
    };
    for (int i = 0; i < 50; ++i) {
        std::vector<uint8_t> vec(duid_template,
                                 duid_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        DuidPtr duid(new DUID(vec));
        duids_.push_back(duid);
    }
}

IOAddress
CfgHostsTest::increase(const IOAddress& address, const uint8_t num) const {
    std::vector<uint8_t> vec = address.toBytes();
    if (!vec.empty()) {
        vec[vec.size() - 1] += num;
        return (IOAddress::fromBytes(address.getFamily(), &vec[0]));
    }
    return (address);
}

// This test checks that hosts with unique HW addresses and DUIDs can be
// retrieved from the host configuration.
TEST_F(CfgHostsTest, getAllNonRepeatingHosts) {
    CfgHosts cfg;
    // Add 25 hosts identified by HW address and 25 hosts identified by
    // DUID. They are added to different subnets.
    for (int i = 0; i < 25; ++i) {
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(i % 10), SubnetID(i % 5),
                                 IOAddress("192.0.2.5"))));

        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(i % 5), SubnetID(i % 10),
                                 IOAddress("192.0.2.10"))));

    }

    // Try to retrieve each added reservation using HW address and DUID. Do it
    // in the reverse order to make sure that the order doesn't matter.
    for (int i = 24; i >= 0; --i) {
        // Get host identified by HW address. The DUID is non-zero but it
        // points to a host for which the reservation hasn't been added.
        HostCollection hosts = cfg.getAll(hwaddrs_[i], duids_[i + 25]);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(i % 10, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());

        // Get host identified by DUID. The HW address is non-null but it
        // points to a host for which the reservation hasn't been added.
        hosts = cfg.getAll(hwaddrs_[i + 25], duids_[i]);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(i % 5, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.10", hosts[0]->getIPv4Reservation().toText());
    }

    // Make sure that the reservations do not exist for the hardware addresses
    // and DUIDs from the range of 25 to 49.
    for (int i = 49; i >= 25; --i) {
        EXPECT_TRUE(cfg.getAll(hwaddrs_[i]).empty());
        EXPECT_TRUE(cfg.getAll(HWAddrPtr(), duids_[i]).empty());
    }
}

// This test verifies that the host can be added to multiple subnets and
// that the getAll message retrieves all instances of the host.
TEST_F(CfgHostsTest, getAllRepeatingHosts) {
    CfgHosts cfg;
    // Add hosts.
    for (int i = 0; i < 25; ++i) {
        // Add two hosts, using the same HW address to two distnict subnets.
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(1), SubnetID(2),
                                 IOAddress("192.0.2.5"))));
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(2), SubnetID(3),
                                 IOAddress("10.0.0.5"))));

        // Add two hosts, using the same DUID to two distnict subnets.
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(1), SubnetID(2),
                                 IOAddress("192.0.2.10"))));
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(2), SubnetID(3),
                                 IOAddress("10.0.2.10"))));
    }

    // Verify that hosts can be retrieved.
    for (int i = 0; i < 25; ++i) {
        // Get host by HW address. The DUID is non-null but the reservation
        // should be returned for the HW address because there are no
        // reservations for the DUIDs from the range of 25 to 49.
        HostCollection hosts = cfg.getAll(hwaddrs_[i], duids_[i + 25]);
        ASSERT_EQ(2, hosts.size());
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
        EXPECT_EQ(2, hosts[1]->getIPv4SubnetID());
        EXPECT_EQ("10.0.0.5", hosts[1]->getIPv4Reservation().toText());

        // Get host by DUID. The HW address is non-null but the reservation
        // should be returned for the DUID because there are no
        // reservations for the HW addresses from the range of 25 to 49.
        hosts = cfg.getAll(hwaddrs_[i + 25], duids_[i]);
        ASSERT_EQ(2, hosts.size());
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ(2, hosts[1]->getIPv4SubnetID());
    }

    // The getAll function should return empty containers for the HW addresses
    //  and DUIDs for which the reservations haven't been added.
    for (int i = 25; i < 50; ++i) {
        EXPECT_TRUE(cfg.getAll(hwaddrs_[i]).empty());
        EXPECT_TRUE(cfg.getAll(HWAddrPtr(), duids_[i]).empty());
    }
}

// This test checks that the reservations can be retrieved for the particular
// host connected to the specific IPv4 subnet (by subnet id).
TEST_F(CfgHostsTest, get4) {
    CfgHosts cfg;
    // Add hosts.
    for (int i = 0; i < 25; ++i) {
        // Add host identified by HW address.
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(1 + i % 2), SubnetID(13),
                                 increase(IOAddress("192.0.2.5"), i))));

        // Add host identified by DUID.
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(1 + i % 2), SubnetID(13),
                                 increase(IOAddress("192.0.2.100"), i))));
    }

    for (int i = 0; i < 25; ++i) {
        // Retrieve host by HW address. The DUID is non-null but there is no
        // reservation made for the DUID so the reservation is returned for
        // HW address.
        HostPtr host = cfg.get4(SubnetID(1 + i % 2), hwaddrs_[i],
                                duids_[i + 25]);
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv4SubnetID());
        EXPECT_EQ(increase(IOAddress("192.0.2.5"), i),
                  host->getIPv4Reservation());

        // Retrieve host by DUID. The HW address is non-null but there is no
        // reservation made for the HW address so the reservation is returned
        // for the DUID.
        host = cfg.get4(SubnetID(1 + i % 2), hwaddrs_[i + 25], duids_[i]);
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv4SubnetID());
        EXPECT_EQ(increase(IOAddress("192.0.2.100"), i),
                  host->getIPv4Reservation());

    }

    // Also check that when the get4 finds multiple Host objects that fulfil
    // search criteria, it will throw an exception. Note that the reservation
    // exist both for hwaddrs_[0] and duids_[0].
    EXPECT_THROW(cfg.get4(SubnetID(1), hwaddrs_[0], duids_[0]), DuplicateHost);
}

// This test checks that the reservations can be retrieved for the particular
// host connected to the specific IPv6 subnet (by subnet id).
TEST_F(CfgHostsTest, get6) {
    CfgHosts cfg;
    // Add hosts.
    for (int i = 0; i < 25; ++i) {
        // Add host identified by HW address.
        HostPtr host = HostPtr(new Host(hwaddrs_[i]->toText(false),
                                        "hw-address",
                                        SubnetID(10), SubnetID(1 + i % 2),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:1::1"),
                                                i)));
        cfg.add(host);

        // Add host identified by DUID.
        host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                SubnetID(10), SubnetID(1 + i % 2),
                                IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:2::1"),
                                                i)));
        cfg.add(host);
    }

    for (int i = 0; i < 25; ++i) {
        // Retrieve host by HW address. The DUID is non-null but there is no
        // reservation made for the DUID so the reservation is returned for
        // HW address.
        HostPtr host = cfg.get6(SubnetID(1 + i % 2), duids_[i + 25],
                                hwaddrs_[i]);
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv6SubnetID());
        IPv6ResrvRange reservations =
            host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
        ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
        EXPECT_EQ(increase(IOAddress("2001:db8:1::1"), i),
                  reservations.first->second.getPrefix());

        // Retrieve host by DUID. The HW address is non-null but there is no
        // reservation made for the HW address so the reservation is returned
        // for the DUID.
        host = cfg.get6(SubnetID(1 + i % 2), duids_[i], hwaddrs_[i + 25]);
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv6SubnetID());
        reservations = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
        ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
        EXPECT_EQ(increase(IOAddress("2001:db8:2::1"), i),
                  reservations.first->second.getPrefix());
    }

    // Also check that when the get6 finds multiple Host objects that fulfil
    // search criteria, it will throw an exception. Note that the reservation
    // exist both for hwaddrs_[0] and duids_[0].
    EXPECT_THROW(cfg.get6(SubnetID(1), duids_[0], hwaddrs_[0]), DuplicateHost);
}

// This test verifies that it is not possible to add the same Host to the
// same IPv4 subnet twice.
TEST_F(CfgHostsTest, duplicatesSubnet4HWAddr) {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SubnetID(10), SubnetID(1),
                                             IOAddress("10.0.0.1")))));

    // Try to add the host with the same HW address to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                          "hw-address",
                                          SubnetID(10), SubnetID(12),
                                          IOAddress("10.0.0.10")))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SubnetID(11), SubnetID(12),
                                             IOAddress("10.0.0.10")))));
}

// This test verifies that it is not possible to add the same Host to the
// same IPv4 subnet twice.
TEST_F(CfgHostsTest, duplicatesSubnet4DUID) {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SubnetID(10), SubnetID(1),
                                             IOAddress("10.0.0.1")))));

    // Try to add the host with the same DUID to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                          "duid",
                                          SubnetID(10), SubnetID(12),
                                          IOAddress("10.0.0.10")))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SubnetID(11), SubnetID(12),
                                             IOAddress("10.0.0.10")))));
}

// This test verifies that it is not possible to add the same Host to the
// same IPv6 subnet twice.
TEST_F(CfgHostsTest, duplicatesSubnet6HWAddr) {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SubnetID(10), SubnetID(1),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));

    // Try to add the host with the same HW address to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                          "hw-address",
                                          SubnetID(11), SubnetID(1),
                                          IOAddress("0.0.0.0"),
                                          "foo.example.com"))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SubnetID(11), SubnetID(2),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));
}

// This test verifies that it is not possible to add the same Host to the
// same IPv6 subnet twice.
TEST_F(CfgHostsTest, duplicatesSubnet6DUID) {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SubnetID(10), SubnetID(1),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));

    // Try to add the host with the same DUID to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                          "duid",
                                          SubnetID(11), SubnetID(1),
                                          IOAddress("0.0.0.0"),
                                          "foo.example.com"))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SubnetID(11), SubnetID(2),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));
}


} // end of anonymous namespace
