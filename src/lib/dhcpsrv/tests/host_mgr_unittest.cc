// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_mgr.h>
#include <gtest/gtest.h>
#include <vector>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

/// @brief Test fixture class for @c HostMgr class.
class HostMgrTest : public ::testing::Test {
protected:

    /// @brief Prepares the class for a test.
    ///
    /// This method crates a handful of unique HW address and DUID objects
    /// for use in unit tests. These objects are held in the @c hwaddrs_ and
    /// @c duids_ members respectively.
    ///
    /// This method also resets the @c CfgMgr configuration and re-creates
    /// the @c HostMgr object.
    virtual void SetUp();

    /// @brief Convenience method returning a pointer to the @c CfgHosts object
    /// in the @c CfgMgr.
    CfgHostsPtr getCfgHosts() const;

    /// @brief HW addresses to be used by the tests.
    std::vector<HWAddrPtr> hwaddrs_;
    /// @brief DUIDs to be used by the tests.
    std::vector<DuidPtr> duids_;
};

void
// cppcheck-suppress unusedFunction
HostMgrTest::SetUp() {
    // Remove all configuration which may be dangling from the previous test.
    CfgMgr::instance().clear();
    // Recreate HostMgr instance. It drops any previous state.
    HostMgr::create();
    // Create HW addresses from the template.
    const uint8_t mac_template[] = {
        0x01, 0x02, 0x0A, 0xBB, 0x03, 0x00
    };
    for (uint8_t i = 0; i < 10; ++i) {
        std::vector<uint8_t> vec(mac_template,
                                 mac_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        HWAddrPtr hwaddr(new HWAddr(vec, HTYPE_ETHER));
        hwaddrs_.push_back(hwaddr);
    }
    // Create DUIDs from the template.
    const uint8_t duid_template[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x00
    };
    for (uint8_t i = 0; i < 10; ++i) {
        std::vector<uint8_t> vec(duid_template,
                                 duid_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        DuidPtr duid(new DUID(vec));
        duids_.push_back(duid);
    }
}

CfgHostsPtr
HostMgrTest::getCfgHosts() const {
    return (CfgMgr::instance().getStagingCfg()->getCfgHosts());
}

/// This test verifies that HostMgr returns all reservations for the
/// specified HW address. The reservations are defined in the server's
/// configuration.
TEST_F(HostMgrTest, getAll) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll(hwaddrs_[0]);
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same HW address. They differ by the IP
    // address reserved and the IPv4 subnet.
    getCfgHosts()->add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                        "hw-address", SubnetID(1), SubnetID(0),
                                        IOAddress("192.0.2.5"))));
    getCfgHosts()->add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                        "hw-address", SubnetID(10), SubnetID(0),
                                        IOAddress("192.0.3.10"))));
    CfgMgr::instance().commit();

    // If there non-matching HW address is specified, nothing should be
    // returned.
    ASSERT_TRUE(HostMgr::instance().getAll(hwaddrs_[1]).empty());
    // For the correct HW address, there should be two reservations.
    hosts = HostMgr::instance().getAll(hwaddrs_[0]);
    ASSERT_EQ(2, hosts.size());

    // We don't know the order in which the reservations are returned so
    // we have to match with any of the two reservations returned.

    // Look for the first reservation.
    bool found = false;
    for (int i = 0; i < 2; ++i) {
        if (hosts[0]->getIPv4Reservation() == IOAddress("192.0.2.5")) {
            ASSERT_EQ(1, hosts[0]->getIPv4SubnetID());
            found = true;
        }
    }
    if (!found) {
        ADD_FAILURE() << "Reservation for the IPv4 address 192.0.2.5"
            " not found using getAll method";
    }

    // Look for the second reservation.
    found = false;
    for (int i = 0; i < 2; ++i) {
        if (hosts[1]->getIPv4Reservation() == IOAddress("192.0.3.10")) {
            ASSERT_EQ(10, hosts[1]->getIPv4SubnetID());
            found = true;
        }
    }
    if (!found) {
        ADD_FAILURE() << "Reservation for the IPv4 address 192.0.3.10"
            " not found using getAll method";
    }

}

// This test verifies that it is possible to gather all reservations for the
// specified IPv4 address from the HostMgr. The reservations are specified in
// the server's configuration. Note: this test is currently disabled because the
// getAll4 method is not implemented in the CfgHosts object.
TEST_F(HostMgrTest, DISABLED_getAll4) {
    ConstHostCollection hosts =
        HostMgr::instance().getAll4(IOAddress("192.0.2.5"));
    ASSERT_TRUE(hosts.empty());

    getCfgHosts()->add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                        "hw-address", SubnetID(1), SubnetID(0),
                                        IOAddress("192.0.2.5"))));

    getCfgHosts()->add(HostPtr(new Host(hwaddrs_[1]->toText(false),
                                        "hw-address", SubnetID(10), SubnetID(0),
                                        IOAddress("192.0.2.5"))));
    CfgMgr::instance().commit();

    hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5"));
    ASSERT_EQ(2, hosts.size());

    /// @todo Extend this test to sanity check the hosts, once the test
    /// is enabled.
}

// This test verifies that it is possible to retrieve a reservation for the
// particular host using HostMgr. The reservation is specified in the server's
// configuration.
TEST_F(HostMgrTest, get4) {
    ConstHostPtr host = HostMgr::instance().get4(SubnetID(1), hwaddrs_[0]);
    ASSERT_FALSE(host);

    getCfgHosts()->add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                        "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.5"))));
    CfgMgr::instance().commit();

    host = HostMgr::instance().get4(SubnetID(1), hwaddrs_[0]);
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());
}

// This test verifies that it is possible to retrieve IPv6 reservations for
// the particular host using HostMgr. The reservation is specified in the
// server's configuration.
TEST_F(HostMgrTest, get6) {
    ConstHostPtr host = HostMgr::instance().get6(SubnetID(2), duids_[0]);
    ASSERT_FALSE(host);

    HostPtr new_host(new Host(duids_[0]->toText(), "duid", SubnetID(1),
                              SubnetID(2), IOAddress("0.0.0.0")));
    new_host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8:1::1")));
    getCfgHosts()->add(new_host);
    CfgMgr::instance().commit();

    host = HostMgr::instance().get6(SubnetID(2), duids_[0]);
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));
}

// This test verifies that it is possible to retrieve the reservation of the
// particular IPv6 prefix using HostMgr. Note: this test is currently disabled
// because the get6(prefix, prefix_len) method is not implemented in the
// CfgHosts class.
TEST_F(HostMgrTest, DISABLED_get6ByPrefix) {
    ConstHostPtr host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64);
    ASSERT_FALSE(host);

    HostPtr new_host(new Host(duids_[0]->toText(), "duid", SubnetID(1),
                              SubnetID(2), IOAddress("0.0.0.0")));
    new_host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                       IOAddress("2001:db8:1::"), 64));
    getCfgHosts()->add(new_host);
    CfgMgr::instance().commit();

    host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64);
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
    IOAddress("2001:db8:1::"), 64)));
}

} // end of anonymous namespace
