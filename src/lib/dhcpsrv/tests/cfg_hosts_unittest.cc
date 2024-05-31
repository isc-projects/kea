// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfg_hosts_util.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/cfgmgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

#include <sstream>
#include <set>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::util;

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

    /// @brief Destructor.
    ///
    /// This destructor resets global state after tests are run.
    ~CfgHostsTest();

    /// @brief Increases last byte of an address.
    ///
    /// @param address Address to be increased.
    IOAddress increase(const IOAddress& address, const uint8_t num) const;

    /// @brief test methods.
    void testGetAllNonRepeatingHosts();
    void testGetAllRepeatingHosts();
    void testGetAll4BySubnet();
    void testGetAll6BySubnet();
    void testGetAll6ByAddress();
    void testGetPage4();
    void testGetPage6();
    void testGetPage4All();
    void testGetPage6All();
    void testGetAll4ByAddress();
    void testDeleteForIPv4();
    void testDeleteForIPv6();
    void testDelete2ForIPv6();
    void testDel4();
    void testDel6();
    void testDeleteAll4();
    void testGet4();
    void testUnparsed4();
    void testGet6();
    void testDeleteAll6();
    void testUnparse6();
    void testGet6ByAddr();
    void testGet6MultipleAddrs();
    void testAdd4AlreadyReserved();
    void testAllow4AlreadyReserved();
    void testAdd6Invalid2Hosts();
    void testAllowAddress6AlreadyReserved();
    void testAllowPrefix6AlreadyReserved();
    void testDuplicatesSubnet4HWAddr();
    void testDuplicatesSubnet4DUID();
    void testDuplicatesSubnet6HWAddr();
    void testDuplicatesSubnet6DUID();
    void testUpdate();

    /// @brief Collection of HW address objects allocated for unit tests.
    std::vector<HWAddrPtr> hwaddrs_;
    /// @brief Collection of DUIDs allocated for unit tests.
    std::vector<DuidPtr> duids_;
    /// @brief Collection of IPv4 address objects allocated for unit tests.
    std::vector<IOAddress> addressesa_;
    std::vector<IOAddress> addressesb_;
};

CfgHostsTest::CfgHostsTest() {
    const uint8_t mac_template[] = {
        0x01, 0x02, 0x0A, 0xBB, 0x03, 0x00
    };
    for (unsigned i = 0; i < 50; ++i) {
        std::vector<uint8_t> vec(mac_template,
                                 mac_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        HWAddrPtr hwaddr(new HWAddr(vec, HTYPE_ETHER));
        hwaddrs_.push_back(hwaddr);
    }

    const uint8_t duid_template[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x00
    };
    for (unsigned i = 0; i < 50; ++i) {
        std::vector<uint8_t> vec(duid_template,
                                 duid_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        DuidPtr duid(new DUID(vec));
        duids_.push_back(duid);
    }

    const uint32_t addra_template = 0xc0000205; // 192.0.2.5
    const uint32_t addrb_template = 0xc00a020a; // 192.10.2.10
    for (unsigned i = 0; i < 50; ++i) {
        IOAddress addra(addra_template + i);
        addressesa_.push_back(addra);
        IOAddress addrb(addrb_template + i);
        addressesb_.push_back(addrb);
    }
    MultiThreadingMgr::instance().setMode(false);
}

CfgHostsTest::~CfgHostsTest() {
    CfgMgr::instance().setFamily(AF_INET);
    MultiThreadingMgr::instance().setMode(false);
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
void
CfgHostsTest::testGetAllNonRepeatingHosts() {
    CfgHosts cfg;
    // Add 25 hosts identified by HW address and 25 hosts identified by
    // DUID. They are added to different subnets.
    for (unsigned i = 0; i < 25; ++i) {
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(i % 10 + 1), SubnetID(i % 5 + 1),
                                 addressesa_[i])));

        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(i % 5 + 1), SubnetID(i % 10 + 1),
                                 addressesb_[i])));

    }

    // Try to retrieve each added reservation using HW address and DUID. Do it
    // in the reverse order to make sure that the order doesn't matter.
    for (int i = 24; i >= 0; --i) {
        // Get host identified by HW address.
        HostCollection hosts = cfg.getAll(Host::IDENT_HWADDR,
                                          &hwaddrs_[i]->hwaddr_[0],
                                          hwaddrs_[i]->hwaddr_.size());
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(i % 10 + 1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ(addressesa_[i].toText(),
                  hosts[0]->getIPv4Reservation().toText());

        // Get host identified by DUID.
        hosts = cfg.getAll(Host::IDENT_DUID,
                           &duids_[i]->getDuid()[0],
                           duids_[i]->getDuid().size());
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(i % 5 + 1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ(addressesb_[i].toText(),
                  hosts[0]->getIPv4Reservation().toText());
    }

    // Make sure that the reservations do not exist for the hardware addresses
    // and DUIDs from the range of 25 to 49.
    for (int i = 49; i >= 25; --i) {
        EXPECT_TRUE(cfg.getAll(Host::IDENT_HWADDR, &hwaddrs_[i]->hwaddr_[0],
                               hwaddrs_[i]->hwaddr_.size()).empty());
        EXPECT_TRUE(cfg.getAll(Host::IDENT_DUID, &duids_[i]->getDuid()[0],
                               duids_[i]->getDuid().size()).empty());
    }
}

TEST_F(CfgHostsTest, getAllNonRepeatingHosts) {
    testGetAllNonRepeatingHosts();
}

TEST_F(CfgHostsTest, getAllNonRepeatingHostsMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAllNonRepeatingHosts();
}

// This test verifies that the host can be added to multiple subnets and
// that the getAll message retrieves all instances of the host.
void
CfgHostsTest::testGetAllRepeatingHosts() {
    CfgHosts cfg;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
        // Add two hosts, using the same HW address to two distinct subnets.
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(1), SubnetID(2),
                                 addressesa_[i])));
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(2), SubnetID(3),
                                 addressesb_[i])));

        // Add two hosts, using the same DUID to two distinct subnets.
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(1), SubnetID(2),
                                 addressesb_[i])));
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(2), SubnetID(3),
                                 addressesa_[i])));
    }

    // Verify that hosts can be retrieved.
    for (unsigned i = 0; i < 25; ++i) {
        // Get host by HW address.
        HostCollection hosts = cfg.getAll(Host::IDENT_HWADDR,
                                          &hwaddrs_[i]->hwaddr_[0],
                                          hwaddrs_[i]->hwaddr_.size());
        ASSERT_EQ(2, hosts.size());
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ(addressesa_[i], hosts[0]->getIPv4Reservation().toText());
        EXPECT_EQ(2, hosts[1]->getIPv4SubnetID());
        EXPECT_EQ(addressesb_[i], hosts[1]->getIPv4Reservation().toText());

        // The HW address is non-null but there are no reservations
        // for the HW addresses from the range of 25 to 49.
        hosts = cfg.getAll(Host::IDENT_HWADDR,
                           &hwaddrs_[i + 25]->hwaddr_[0],
                           hwaddrs_[i + 25]->hwaddr_.size());
        EXPECT_TRUE(hosts.empty());

        // Get host by DUID.
        hosts = cfg.getAll(Host::IDENT_DUID,
                           &duids_[i]->getDuid()[0],
                           duids_[i]->getDuid().size());

        // The DUID is non-null but there are no reservations
        // for the DUIDs from the range of 25 to 49.
        hosts = cfg.getAll(Host::IDENT_DUID,
                           &duids_[i + 25]->getDuid()[0],
                           duids_[i + 25]->getDuid().size());
        EXPECT_TRUE(hosts.empty());
    }
}

TEST_F(CfgHostsTest, getAllRepeatingHosts) {
    testGetAllRepeatingHosts();
}

TEST_F(CfgHostsTest, getAllRepeatingHostsMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAllRepeatingHosts();
}

// This test checks that hosts in the same subnet can be retrieved from
// the host configuration.
void
CfgHostsTest::testGetAll4BySubnet() {
    CfgHosts cfg;
    // Add 25 hosts identified by HW address in the same subnet.
    for (unsigned i = 0; i < 25; ++i) {
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(1), SubnetID(1),
                                 addressesa_[i])));
    }

    // Check that other subnets are empty.
    HostCollection hosts = cfg.getAll4(SubnetID(100));
    EXPECT_EQ(0, hosts.size());

    // Try to retrieve all added reservations.
    hosts = cfg.getAll4(SubnetID(1));
    ASSERT_EQ(25, hosts.size());
    for (unsigned i = 0; i < 25; ++i) {
        EXPECT_EQ(1, hosts[i]->getIPv4SubnetID());
        EXPECT_EQ(addressesa_[i].toText(),
                  hosts[i]->getIPv4Reservation().toText());
    }
}

TEST_F(CfgHostsTest, getAll4BySubnet) {
    testGetAll4BySubnet();
}

TEST_F(CfgHostsTest, getAll4BySubnetMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAll4BySubnet();
}

// This test checks that hosts in the same subnet can be retrieved from
// the host configuration.
void
CfgHostsTest::testGetAll6BySubnet() {
    CfgHosts cfg;
    // Add 25 hosts identified by DUID in the same subnet.
    for (unsigned i = 0; i < 25; ++i) {
        HostPtr host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                        SubnetID(1), SubnetID(1),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:1::1"),
                                                i)));
        cfg.add(host);
    }

    // Check that other subnets are empty.
    HostCollection hosts = cfg.getAll6(SubnetID(100));
    EXPECT_EQ(0, hosts.size());

    // Try to retrieve all added reservations.
    hosts = cfg.getAll6(SubnetID(1));
    ASSERT_EQ(25, hosts.size());
    for (unsigned i = 0; i < 25; ++i) {
        EXPECT_EQ(1, hosts[i]->getIPv6SubnetID());
        IPv6ResrvRange reservations =
            hosts[i]->getIPv6Reservations(IPv6Resrv::TYPE_NA);
        ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
        EXPECT_EQ(increase(IOAddress("2001:db8:1::1"), i),
                  reservations.first->second.getPrefix());
    }
}

TEST_F(CfgHostsTest, getAll6BySubnet) {
    testGetAll6BySubnet();
}

TEST_F(CfgHostsTest, getAll6BySubnetMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAll6BySubnet();
}

// This test checks that hosts with the same reserved address can be retrieved
// from the host configuration.
void
CfgHostsTest::testGetAll6ByAddress() {
    CfgHosts cfg;
    // Add 25 hosts identified by DUID in the same subnet.
    for (unsigned i = 0; i < 25; ++i) {
        HostPtr host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                        SUBNET_ID_UNUSED, SubnetID(i+1),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:1::1"),
                                                i % 5)));
        cfg.add(host);
    }

    // Try to retrieve all added reservations with IP equals 2001:db8:1::1.
    auto hosts = cfg.getAll6(IOAddress("2001:db8:1::1"));
    EXPECT_EQ(5, hosts.size());
    for (unsigned i = 0; i < 5; ++i) {
        EXPECT_EQ(1 + 5 * i, hosts[i]->getIPv6SubnetID());
        IPv6ResrvRange reservations =
            hosts[i]->getIPv6Reservations(IPv6Resrv::TYPE_NA);
        ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
        EXPECT_EQ(IOAddress("2001:db8:1::1"),
                  reservations.first->second.getPrefix());
    }
}

TEST_F(CfgHostsTest, getAll6ByAddress) {
    testGetAll6ByAddress();
}

TEST_F(CfgHostsTest, getAll6ByAddressMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAll6ByAddress();
}

// This test checks that hosts in the same subnet can be retrieved from
// the host configuration by pages.
void
CfgHostsTest::testGetPage4() {
    CfgHosts cfg;
    // Add 25 hosts identified by DUID in the same subnet.
    for (unsigned i = 0; i < 25; ++i) {
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(1), SubnetID(1),
                                 addressesa_[i])));
    }
    size_t idx(0);
    uint64_t host_id(0);
    HostPageSize page_size(10);

    // Check that other subnets are empty.
    HostCollection page = cfg.getPage4(SubnetID(100), idx, host_id, page_size);
    EXPECT_EQ(0, page.size());

    // Try to retrieve all added reservations.
    // Get first page.
    page = cfg.getPage4(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();

    // Get second and last pages.
    page = cfg.getPage4(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    page = cfg.getPage4(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(5, page.size());
    host_id = page[4]->getHostId();

    // Verify we have everything.
    page = cfg.getPage4(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(0, page.size());
}

TEST_F(CfgHostsTest, getPage4) {
    testGetPage4();
}

TEST_F(CfgHostsTest, getPage4MultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage4();
}

// This test checks that hosts in the same subnet can be retrieved from
// the host configuration by pages.
void
CfgHostsTest::testGetPage6() {
    CfgHosts cfg;
    // Add 25 hosts identified by HW address in the same subnet.
    for (unsigned i = 0; i < 25; ++i) {
        HostPtr host = HostPtr(new Host(hwaddrs_[i]->toText(false),
                                        "hw-address",
                                        SubnetID(1), SubnetID(1),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:1::1"),
                                                i)));
        cfg.add(host);
    }
    size_t idx(0);
    uint64_t host_id(0);
    HostPageSize page_size(10);

    // Check that other subnets are empty.
    HostCollection page = cfg.getPage6(SubnetID(100), idx, host_id, page_size);
    EXPECT_EQ(0, page.size());

    // Try to retrieve all added reservations.
    // Get first page.
    page = cfg.getPage6(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();

    // Get second and last pages.
    page = cfg.getPage6(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    page = cfg.getPage6(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(5, page.size());
    host_id = page[4]->getHostId();

    // Verify we have everything.
    page = cfg.getPage6(SubnetID(1), idx, host_id, page_size);
    EXPECT_EQ(0, page.size());
}

TEST_F(CfgHostsTest, getPage6) {
    testGetPage6();
}

TEST_F(CfgHostsTest, getPage6MultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage6();
}

// This test checks that all hosts can be retrieved from the host
// configuration by pages.
void
CfgHostsTest::testGetPage4All() {
    CfgHosts cfg;
    // Add 25 hosts identified by DUID.
    for (unsigned i = 0; i < 25; ++i) {
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(i), SubnetID(i),
                                 addressesa_[i])));
    }
    size_t idx(0);
    uint64_t host_id(0);
    HostPageSize page_size(10);

    // Try to retrieve all added reservations.
    // Get first page.
    HostCollection page = cfg.getPage4(idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();

    // Get second and last pages.
    page = cfg.getPage4(idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    page = cfg.getPage4(idx, host_id, page_size);
    EXPECT_EQ(5, page.size());
    host_id = page[4]->getHostId();

    // Verify we have everything.
    page = cfg.getPage4(idx, host_id, page_size);
    EXPECT_EQ(0, page.size());
}

TEST_F(CfgHostsTest, getPage4All) {
    testGetPage4All();
}

TEST_F(CfgHostsTest, getPage4AllMultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage4All();
}

// This test checks that all hosts can be retrieved from the host
// configuration by pages.
void
CfgHostsTest::testGetPage6All() {
    CfgHosts cfg;
    // Add 25 hosts identified by HW address.
    for (unsigned i = 0; i < 25; ++i) {
        HostPtr host = HostPtr(new Host(hwaddrs_[i]->toText(false),
                                        "hw-address",
                                        SubnetID(i), SubnetID(i),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:1::1"),
                                                i)));
        cfg.add(host);
    }
    size_t idx(0);
    uint64_t host_id(0);
    HostPageSize page_size(10);

    // Try to retrieve all added reservations.
    // Get first page.
    HostCollection page = cfg.getPage6(idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();

    // Get second and last pages.
    page = cfg.getPage6(idx, host_id, page_size);
    EXPECT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    page = cfg.getPage6(idx, host_id, page_size);
    EXPECT_EQ(5, page.size());
    host_id = page[4]->getHostId();

    // Verify we have everything.
    page = cfg.getPage6(idx, host_id, page_size);
    EXPECT_EQ(0, page.size());
}

TEST_F(CfgHostsTest, getPage6All) {
    testGetPage6All();
}

TEST_F(CfgHostsTest, getPage6AllMultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage6All();
}

// This test checks that all reservations for the specified IPv4 address can
// be retrieved.
void
CfgHostsTest::testGetAll4ByAddress() {
    CfgHosts cfg;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
        // Add host identified by the HW address.
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(1 + i), SUBNET_ID_UNUSED,
                                 IOAddress("192.0.2.5"))));
        // Add host identified by the DUID.
        cfg.add(HostPtr(new Host(duids_[i]->toText(),
                                 "duid",
                                 SubnetID(1 + i), SUBNET_ID_UNUSED,
                                 IOAddress("192.0.2.10"))));
    }

    HostCollection hosts = cfg.getAll4(IOAddress("192.0.2.10"));
    std::set<uint32_t> subnet_ids;
    for (auto const& host : hosts) {
        subnet_ids.insert(host->getIPv4SubnetID());
    }
    ASSERT_EQ(25, subnet_ids.size());
    EXPECT_EQ(1, *subnet_ids.begin());
    EXPECT_EQ(25, *subnet_ids.rbegin());
}

TEST_F(CfgHostsTest, getAll4ByAddress) {
    testGetAll4ByAddress();
}

TEST_F(CfgHostsTest, getAll4ByAddressMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAll4ByAddress();
}

// This test checks that the IPv4 reservation for the specified IPv4 address can
// be deleted.
void
CfgHostsTest::testDeleteForIPv4() {
    CfgHosts cfg;
    // Add hosts.
    IOAddress address("10.0.0.42");
    SubnetID subnet_id(42);
    size_t host_count = 10;

    for (size_t i = 0; i < host_count; i++)
    {
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                "hw-address",
                                subnet_id, SUBNET_ID_UNUSED,
                                increase(address, i))));
    }

    // Get all inserted hosts.
    HostCollection hosts_by_subnet = cfg.getAll4(subnet_id);
    HostCollection hosts_by_address = cfg.getAll4(address);
    // Make sure the hosts and IP reservations were added.
    ASSERT_EQ(host_count, hosts_by_subnet.size());
    ASSERT_EQ(1, hosts_by_address.size());

    // Delete one host.
    EXPECT_TRUE(cfg.del(subnet_id, address));

    // Check if the host is actually deleted.
    hosts_by_subnet = cfg.getAll4(subnet_id);
    hosts_by_address = cfg.getAll4(address);
    EXPECT_EQ(host_count-1, hosts_by_subnet.size());
    EXPECT_EQ(0, hosts_by_address.size());
}

TEST_F(CfgHostsTest, deleteForIPv4) {
    testDeleteForIPv4();
}

TEST_F(CfgHostsTest, deleteForIPv4MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteForIPv4();
}

// This test checks that the IPv6 reservation for the specified subnet ID and
// IPv6 address can be deleted.
void
CfgHostsTest::testDeleteForIPv6() {
    CfgHosts cfg;
    // Add hosts.
    IOAddress address("2001:db8:1::1");
    size_t host_count = 10;
    SubnetID subnet_id(42);

    for (size_t i = 0; i < host_count; i++)
    {
        HostPtr host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                        SUBNET_ID_UNUSED, subnet_id,
                                        IOAddress::IPV4_ZERO_ADDRESS()));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress(address), i)));
        cfg.add(host);
    }


    // Get all inserted hosts.
    auto hosts_by_subnet_and_address = cfg.getAll6(subnet_id, address);
    auto hosts_by_subnet = cfg.getAll6(subnet_id);
    // Make sure the hosts and IP reservations were added.
    ASSERT_EQ(1, hosts_by_subnet_and_address.size());
    ASSERT_EQ(host_count, hosts_by_subnet.size());

    // Delete one host.
    EXPECT_TRUE(cfg.del(subnet_id, address));

    // Check if the host is actually deleted.
    hosts_by_subnet_and_address = cfg.getAll6(subnet_id, address);
    hosts_by_subnet = cfg.getAll6(subnet_id);
    EXPECT_EQ(0, hosts_by_subnet_and_address.size());
    EXPECT_EQ(host_count-1, hosts_by_subnet.size());
}

TEST_F(CfgHostsTest, deleteForIPv6) {
    testDeleteForIPv6();
}

TEST_F(CfgHostsTest, deleteForIPv6MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteForIPv6();
}

// This test checks that two IPv6 reservations for the specified subnet ID and
// IPv6 address can be deleted.
void
CfgHostsTest::testDelete2ForIPv6() {
    CfgHosts cfg;
    // Add host with two addresses.
    IOAddress address1("2001:db8:1::1");
    IOAddress address2("2001:db8:2::2");
    size_t host_count = 10;
    SubnetID subnet_id(42);

    HostPtr host = HostPtr(new Host(duids_[0]->toText(), "duid",
                                    SUBNET_ID_UNUSED, subnet_id,
                                    IOAddress::IPV4_ZERO_ADDRESS()));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, address1));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, address2));
    cfg.add(host);

    // Delete one host using first address.
    EXPECT_TRUE(cfg.del(subnet_id, address1));

    // Check if all addresses were removed.
    EXPECT_FALSE(cfg.get6(subnet_id, address2));
    EXPECT_FALSE(cfg.del(subnet_id, address2));
}

TEST_F(CfgHostsTest, delete2ForIPv6) {
    testDelete2ForIPv6();
}

TEST_F(CfgHostsTest, delete2ForIPv6MultiThreading) {
    MultiThreadingTest mt(true);
    testDelete2ForIPv6();
}

// This test checks that false is returned for deleting the IPv4 reservation
// that doesn't exist.
TEST_F(CfgHostsTest, deleteForMissingIPv4) {
    CfgHosts cfg;

    // Delete non-existent host.
    EXPECT_FALSE(cfg.del(SubnetID(42), IOAddress(("10.0.0.42"))));

    MultiThreadingTest mt(true);
    EXPECT_FALSE(cfg.del(SubnetID(42), IOAddress(("10.0.0.42"))));
}

// This test checks that false is returned for deleting the IPv6 reservation
// that doesn't exist.
TEST_F(CfgHostsTest, deleteForMissingIPv6) {
    CfgHosts cfg;

    // Delete non-existent host.
    EXPECT_FALSE(cfg.del(SubnetID(42), IOAddress(("2001:db8:1::1"))));

    MultiThreadingTest mt(true);
    EXPECT_FALSE(cfg.del(SubnetID(42), IOAddress(("2001:db8:1::1"))));
}

// This test checks that the reservation for the specified IPv4 subnet and
// identifier can be deleted.
void
CfgHostsTest::testDel4() {
    CfgHosts cfg;

    // Add hosts.
    size_t host_count = 20;
    size_t host_id = 5;
    SubnetID subnet_id(42);
    IOAddress address("10.0.0.1");

    // Add half of the hosts with the same subnet ID but differ with DUID and
    // address.
    for (size_t i = 0; i < host_count / 2; i++) {
        HostPtr host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                        subnet_id, SUBNET_ID_UNUSED,
                                        increase(address, i)));
        cfg.add(host);
    }
    // Add half of the hosts with the same subnet DUID and address but
    // differ with address.
    for (size_t i = 0; i < host_count / 2; i++) {
        HostPtr host = HostPtr(new Host(duids_[host_id]->toText(), "duid",
                                        SubnetID(subnet_id + i + 1), SUBNET_ID_UNUSED,
                                        increase(address, host_id)));
        cfg.add(host);
    }


    // Get all inserted hosts.
    HostCollection hosts_by_subnet = cfg.getAll4(subnet_id);
    HostCollection hosts_by_address = cfg.getAll4(increase(address, host_id));
    HostPtr host = cfg.get4(subnet_id, Host::IdentifierType::IDENT_DUID,
                                             &duids_[host_id]->getDuid()[0],
                                             duids_[host_id]->getDuid().size());
    // Make sure the hosts and IP reservations were added.
    ASSERT_EQ(host_count / 2, hosts_by_subnet.size());
    ASSERT_EQ(host_count / 2 + 1, hosts_by_address.size());
    ASSERT_TRUE(host);

    // Delete one host.
    EXPECT_TRUE(cfg.del4(subnet_id, Host::IdentifierType::IDENT_DUID,
                         &duids_[host_id]->getDuid()[0], duids_[host_id]->getDuid().size()));

    // Check if the host is actually deleted.
    hosts_by_subnet = cfg.getAll4(subnet_id);
    hosts_by_address = cfg.getAll4(increase(address, host_id));
    host = cfg.get4(subnet_id, Host::IdentifierType::IDENT_DUID,
                                             &duids_[host_id]->getDuid()[0],
                                             duids_[host_id]->getDuid().size());
    EXPECT_EQ((host_count / 2)-1, hosts_by_subnet.size());
    EXPECT_EQ(host_count / 2, hosts_by_address.size());
    EXPECT_FALSE(host);
}

TEST_F(CfgHostsTest, del4) {
    testDel4();
}

TEST_F(CfgHostsTest, del4MultiThreading) {
    MultiThreadingTest mt(true);
    testDel4();
}

// This test checks that the host and its reservations for the specified IPv6
// subnet and identifier can be deleted.
void
CfgHostsTest::testDel6() {
    CfgHosts cfg;

    // Add hosts.
    size_t host_count = 20;
    size_t host_id = 5;
    SubnetID subnet_id(42);
    IOAddress address("2001:db8:1::1");

    // Add half of the hosts with the same subnet ID but differ with DUID and
    // address.
    for (size_t i = 0; i < host_count / 2; i++) {
        HostPtr host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                        SUBNET_ID_UNUSED, subnet_id,
                                        IOAddress::IPV4_ZERO_ADDRESS()));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress(address), i)));
        cfg.add(host);
    }
    // Add half of the hosts with the same subnet DUID and address but
    // differ with address.
    for (size_t i = 0; i < host_count / 2; i++) {
        HostPtr host = HostPtr(new Host(duids_[host_id]->toText(), "duid",
                                        SUBNET_ID_UNUSED, SubnetID(subnet_id + i + 1),
                                        IOAddress::IPV4_ZERO_ADDRESS()));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(address, host_id)));
        cfg.add(host);
    }


    // Get all inserted hosts.
    HostCollection hosts_by_subnet = cfg.getAll6(subnet_id);
    HostCollection hosts_by_address = cfg.getAll6(increase(address, host_id));
    HostPtr host = cfg.get6(subnet_id, Host::IdentifierType::IDENT_DUID,
                                             &duids_[host_id]->getDuid()[0],
                                             duids_[host_id]->getDuid().size());
    // Make sure the hosts and IP reservations were added.
    ASSERT_EQ(host_count / 2, hosts_by_subnet.size());
    ASSERT_EQ(host_count / 2 + 1, hosts_by_address.size());
    ASSERT_TRUE(host);

    // Delete one host.
    EXPECT_TRUE(cfg.del6(subnet_id, Host::IdentifierType::IDENT_DUID,
                         &duids_[host_id]->getDuid()[0], duids_[host_id]->getDuid().size()));

    // Check if the host is actually deleted.
    hosts_by_subnet = cfg.getAll6(subnet_id);
    hosts_by_address = cfg.getAll6(increase(address, host_id));
    host = cfg.get6(subnet_id, Host::IdentifierType::IDENT_DUID,
                                             &duids_[host_id]->getDuid()[0],
                                             duids_[host_id]->getDuid().size());
    EXPECT_EQ((host_count / 2)-1, hosts_by_subnet.size());
    EXPECT_EQ(host_count / 2, hosts_by_address.size());
    EXPECT_FALSE(host);
}

TEST_F(CfgHostsTest, del6) {
    testDel6();
}

TEST_F(CfgHostsTest, del6MultiThreading) {
    MultiThreadingTest mt(true);
    testDel6();
}

// This test checks that false is returned for deleting the IPv4 host that
// doesn't exist.
TEST_F(CfgHostsTest, del4MissingHost) {
    CfgHosts cfg;
    EXPECT_FALSE(cfg.del4(SubnetID(42), Host::IdentifierType::IDENT_DUID,
                         &duids_[0]->getDuid()[0], duids_[0]->getDuid().size()));
    MultiThreadingTest mt(true);
    EXPECT_FALSE(cfg.del4(SubnetID(42), Host::IdentifierType::IDENT_DUID,
                         &duids_[0]->getDuid()[0], duids_[0]->getDuid().size()));
}

// This test checks that false is returned for deleting the IPv6 host that
// doesn't exist.
TEST_F(CfgHostsTest, del6MissingHost) {
    CfgHosts cfg;
    EXPECT_FALSE(cfg.del6(SubnetID(42), Host::IdentifierType::IDENT_DUID,
                         &duids_[0]->getDuid()[0], duids_[0]->getDuid().size()));
    MultiThreadingTest mt(true);
    EXPECT_FALSE(cfg.del6(SubnetID(42), Host::IdentifierType::IDENT_DUID,
                         &duids_[0]->getDuid()[0], duids_[0]->getDuid().size()));
}

// This test checks that all reservations for the specified IPv4 subnet can
// be deleted.
void
CfgHostsTest::testDeleteAll4() {
    CfgHosts cfg;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
        // Hosts will differ by hostname. It is easier than differentiating by
        // IPv4 address because if they all have zero IPv4 address it is
        // easier to retrieve all of them to check the host counts.
        std::ostringstream s;
        s << "hostname" << i;

        // Add host identified by the HW address.
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(1 + i % 2), SUBNET_ID_UNUSED,
                                 IOAddress::IPV4_ZERO_ADDRESS(),
                                 s.str())));
    }

    // Get all inserted hosts.
    HostCollection hosts = cfg.getAll4(IOAddress::IPV4_ZERO_ADDRESS());
    std::set<uint32_t> subnet_ids;
    for (auto const& host : hosts) {
        subnet_ids.insert(host->getIPv4SubnetID());
    }
    // Make sure there are two unique subnets: 1 and 2.
    ASSERT_EQ(2, subnet_ids.size());
    EXPECT_EQ(1, *subnet_ids.begin());
    EXPECT_EQ(2, *subnet_ids.rbegin());

    // Delete all hosts for subnet id 2. There should be 12 of them.
    EXPECT_EQ(12, cfg.delAll4(SubnetID(2)));

    // Gather the host counts again.
    subnet_ids.clear();
    hosts = cfg.getAll4(IOAddress::IPV4_ZERO_ADDRESS());
    for (auto const& host : hosts) {
        subnet_ids.insert(host->getIPv4SubnetID());
    }
    // We should only have hosts for one subnet and it should be the subnet
    // with ID of 1.
    ASSERT_EQ(1, subnet_ids.size());
    EXPECT_EQ(1, *subnet_ids.begin());
}

TEST_F(CfgHostsTest, deleteAll4) {
    testDeleteAll4();
}

TEST_F(CfgHostsTest, deleteAll4MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteAll4();
}

// This test checks that the reservations can be retrieved for the particular
// host connected to the specific IPv4 subnet (by subnet id).
void
CfgHostsTest::testGet4() {
    CfgHosts cfg;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
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

    for (unsigned i = 0; i < 25; ++i) {
        // Retrieve host by HW address.
        HostPtr host = cfg.get4(SubnetID(1 + i % 2), Host::IDENT_HWADDR,
                                &hwaddrs_[i]->hwaddr_[0],
                                hwaddrs_[i]->hwaddr_.size());
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv4SubnetID());
        EXPECT_EQ(increase(IOAddress("192.0.2.5"), i),
                  host->getIPv4Reservation());

        // Retrieve host by DUID.
        host = cfg.get4(SubnetID(1 + i % 2), Host::IDENT_DUID,
                        &duids_[i]->getDuid()[0], duids_[i]->getDuid().size());
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv4SubnetID());
        EXPECT_EQ(increase(IOAddress("192.0.2.100"), i),
                  host->getIPv4Reservation());

    }
}

TEST_F(CfgHostsTest, get4) {
    testGet4();
}

TEST_F(CfgHostsTest, get4MultiThreading) {
    MultiThreadingTest mt(true);
    testGet4();
}

// This test checks that the DHCPv4 reservations can be unparsed
void
CfgHostsTest::testUnparsed4() {
    CfgMgr::instance().setFamily(AF_INET);
    CfgHosts cfg;
    CfgHostsList list;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
        // Add host identified by HW address.
        cfg.add(HostPtr(new Host(hwaddrs_[i]->toText(false),
                                 "hw-address",
                                 SubnetID(1 + i), SubnetID(13),
                                 increase(IOAddress("192.0.2.5"), i))));

        // Add host identified by DUID.
        cfg.add(HostPtr(new Host(duids_[i]->toText(), "duid",
                                 SubnetID(1 + i), SubnetID(13),
                                 increase(IOAddress("192.0.2.100"), i))));
    }

    using namespace isc::data;
    ConstElementPtr cfg_unparsed;
    ASSERT_NO_THROW(cfg_unparsed = cfg.toElement());
    ASSERT_NO_THROW(list.internalize(cfg_unparsed));
    for (unsigned i = 0; i < 25; ++i) {
        ConstElementPtr unparsed = list.get(SubnetID(1 + i));
        ASSERT_TRUE(unparsed);
        ASSERT_EQ(Element::list, unparsed->getType());
        EXPECT_EQ(2, unparsed->size());
        ASSERT_NE(0, unparsed->size());

        // Check by HW address entries
        bool checked_hw = false;
        for (unsigned j = 0; j < unparsed->size(); ++j) {
            ConstElementPtr host = unparsed->get(j);
            ASSERT_TRUE(host);
            ASSERT_EQ(Element::map, host->getType());
            if (!host->contains("hw-address")) {
                continue;
            }
            checked_hw = true;
            // Not both hw-address and duid
            EXPECT_FALSE(host->contains("duid"));
            // Check the HW address
            ConstElementPtr hw = host->get("hw-address");
            ASSERT_TRUE(hw);
            ASSERT_EQ(Element::string, hw->getType());
            EXPECT_EQ(hwaddrs_[i]->toText(false), hw->stringValue());
            // Check the reservation
            ConstElementPtr resv = host->get("ip-address");
            ASSERT_TRUE(resv);
            ASSERT_EQ(Element::string, resv->getType());
            EXPECT_EQ(increase(IOAddress("192.0.2.5"), i),
                          IOAddress(resv->stringValue()));
        }
        ASSERT_TRUE(checked_hw);

        // Check by DUID entries
        bool checked_duid = false;
        for (unsigned j = 0; j < unparsed->size(); ++j) {
            ConstElementPtr host = unparsed->get(j);
            ASSERT_TRUE(host);
            ASSERT_EQ(Element::map, host->getType());
            if (!host->contains("duid")) {
                continue;
            }
            checked_duid = true;
            // Not both hw-address and duid
            EXPECT_FALSE(host->contains("hw-address"));
            // Check the DUID
            ConstElementPtr duid = host->get("duid");
            ASSERT_TRUE(duid);
            ASSERT_EQ(Element::string, duid->getType());
            EXPECT_EQ(duids_[i]->toText(), duid->stringValue());
            // Check the reservation
            ConstElementPtr resv = host->get("ip-address");
            ASSERT_TRUE(resv);
            ASSERT_EQ(Element::string, resv->getType());
            EXPECT_EQ(increase(IOAddress("192.0.2.100"), i),
                      IOAddress(resv->stringValue()));
        }
        ASSERT_TRUE(checked_duid);
    }
}

TEST_F(CfgHostsTest, unparsed4) {
    testUnparsed4();
}

TEST_F(CfgHostsTest, unparsed4MultiThreading) {
    MultiThreadingTest mt(true);
    testUnparsed4();
}

// This test checks that the reservations can be retrieved for the particular
// host connected to the specific IPv6 subnet (by subnet id).
void
CfgHostsTest::testGet6() {
    CfgHosts cfg;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
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

    for (unsigned i = 0; i < 25; ++i) {
        // Retrieve host by HW address.
        HostPtr host = cfg.get6(SubnetID(1 + i % 2), Host::IDENT_HWADDR,
                                &hwaddrs_[i]->hwaddr_[0],
                                hwaddrs_[i]->hwaddr_.size());
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv6SubnetID());
        IPv6ResrvRange reservations =
            host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
        ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
        EXPECT_EQ(increase(IOAddress("2001:db8:1::1"), i),
                  reservations.first->second.getPrefix());

        // Retrieve host by DUID.
        host = cfg.get6(SubnetID(1 + i % 2), Host::IDENT_DUID,
                        &duids_[i]->getDuid()[0], duids_[i]->getDuid().size());
        ASSERT_TRUE(host);
        EXPECT_EQ(1 + i % 2, host->getIPv6SubnetID());
        reservations = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
        ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
        EXPECT_EQ(increase(IOAddress("2001:db8:2::1"), i),
                  reservations.first->second.getPrefix());
    }
}

TEST_F(CfgHostsTest, get6) {
    testGet6();
}

TEST_F(CfgHostsTest, get6MultiThreading) {
    MultiThreadingTest mt(true);
    testGet6();
}

// This test checks that all reservations for the specified IPv6 subnet can
// be deleted.
void
CfgHostsTest::testDeleteAll6() {
    CfgHosts cfg;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
        // Add host identified by HW address. The subnet for which we're
        // adding the host has id of 1 for even values of i and 2 for
        // odd values of i.
        HostPtr host = HostPtr(new Host(hwaddrs_[i]->toText(false),
                                        "hw-address",
                                        SubnetID(10), SubnetID(1 + i % 2),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:1::1"),
                                                i)));
        cfg.add(host);
    }

    // Delete all hosts for subnet id. There should be 13 of them.
    EXPECT_EQ(13, cfg.delAll6(SubnetID(1)));

    for (unsigned i = 0; i < 25; ++i) {
        // Calculate subnet id for the given i.
        SubnetID subnet_id = 1 + i % 2;

        // Try to retrieve host by HW address.
        HostPtr host = cfg.get6(subnet_id, Host::IDENT_HWADDR,
                                &hwaddrs_[i]->hwaddr_[0],
                                hwaddrs_[i]->hwaddr_.size());
        // The host should exist for subnet id of 2.
        if (subnet_id == 2) {
            ASSERT_TRUE(host);
            EXPECT_EQ(subnet_id, host->getIPv6SubnetID());
            IPv6ResrvRange reservations =
                host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
            ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
            EXPECT_EQ(increase(IOAddress("2001:db8:1::1"), i),
                      reservations.first->second.getPrefix());

        } else {
            // All hosts for subnet id 1 should be gone.
            EXPECT_FALSE(host);
        }
    }
}

TEST_F(CfgHostsTest, deleteAll6) {
    testDeleteAll6();
}

TEST_F(CfgHostsTest, deleteAll6MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteAll6();
}

// This test checks that the DHCPv6 reservations can be unparsed
void
CfgHostsTest::testUnparse6() {
    CfgMgr::instance().setFamily(AF_INET6);
    CfgHosts cfg;
    CfgHostsList list;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {
        // Add host identified by HW address.
        HostPtr host = HostPtr(new Host(hwaddrs_[i]->toText(false),
                                        "hw-address",
                                        SubnetID(10), SubnetID(1 + i),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:1::1"),
                                                i)));
        cfg.add(host);

        // Add host identified by DUID.
        host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                SubnetID(10), SubnetID(1 + i),
                                IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:2::1"),
                                                i)));
        cfg.add(host);
    }

    using namespace isc::data;
    ConstElementPtr cfg_unparsed;
    ASSERT_NO_THROW(cfg_unparsed = cfg.toElement());
    ASSERT_NO_THROW(list.internalize(cfg_unparsed));
    for (unsigned i = 0; i < 25; ++i) {
        ConstElementPtr unparsed = list.get(SubnetID(1 + i));
        ASSERT_TRUE(unparsed);
        ASSERT_EQ(Element::list, unparsed->getType());
        EXPECT_EQ(2, unparsed->size());
        ASSERT_NE(0, unparsed->size());

        // Check by HW address entries
        bool checked_hw = false;
        for (unsigned j = 0; j < unparsed->size(); ++j) {
            ConstElementPtr host = unparsed->get(j);
            ASSERT_TRUE(host);
            ASSERT_EQ(Element::map, host->getType());
            if (!host->contains("hw-address")) {
                continue;
            }
            checked_hw = true;
            // Not both hw-address and duid
            EXPECT_FALSE(host->contains("duid"));
            // Check the HW address
            ConstElementPtr hw = host->get("hw-address");
            ASSERT_TRUE(hw);
            ASSERT_EQ(Element::string, hw->getType());
            EXPECT_EQ(hwaddrs_[i]->toText(false), hw->stringValue());
            // Check the reservation
            ConstElementPtr resvs = host->get("ip-addresses");
            ASSERT_TRUE(resvs);
            ASSERT_EQ(Element::list, resvs->getType());
            EXPECT_EQ(1, resvs->size());
            ASSERT_GE(1, resvs->size());
            ConstElementPtr resv = resvs->get(0);
            ASSERT_TRUE(resv);
            ASSERT_EQ(Element::string, resv->getType());
            EXPECT_EQ(increase(IOAddress("2001:db8:1::1"), i),
                          IOAddress(resv->stringValue()));
        }
        ASSERT_TRUE(checked_hw);

        // Check by DUID entries
        bool checked_duid = false;
        for (unsigned j = 0; j < unparsed->size(); ++j) {
            ConstElementPtr host = unparsed->get(j);
            ASSERT_TRUE(host);
            ASSERT_EQ(Element::map, host->getType());
            if (!host->contains("duid")) {
                continue;
            }
            checked_duid = true;
            // Not both hw-address and duid
            EXPECT_FALSE(host->contains("hw-address"));
            // Check the DUID
            ConstElementPtr duid = host->get("duid");
            ASSERT_TRUE(duid);
            ASSERT_EQ(Element::string, duid->getType());
            EXPECT_EQ(duids_[i]->toText(), duid->stringValue());
            // Check the reservation
            ConstElementPtr resvs = host->get("ip-addresses");
            ASSERT_TRUE(resvs);
            ASSERT_EQ(Element::list, resvs->getType());
            EXPECT_EQ(1, resvs->size());
            ASSERT_GE(1, resvs->size());
            ConstElementPtr resv = resvs->get(0);
            ASSERT_TRUE(resv);
            ASSERT_EQ(Element::string, resv->getType());
            EXPECT_EQ(increase(IOAddress("2001:db8:2::1"), i),
                      IOAddress(resv->stringValue()));
        }
        ASSERT_TRUE(checked_duid);
    }
}

TEST_F(CfgHostsTest, unparse6) {
    testUnparse6();
}

TEST_F(CfgHostsTest, unparse6MultiThreading) {
    MultiThreadingTest mt(true);
    testUnparse6();
}

// This test checks that the IPv6 reservations can be retrieved for a particular
// (subnet-id, address) tuple.
void
CfgHostsTest::testGet6ByAddr() {
    CfgHosts cfg;
    // Add hosts.
    for (unsigned i = 0; i < 25; ++i) {

        // Add host identified by DUID.
        HostPtr host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                        SUBNET_ID_UNUSED, SubnetID(1 + i % 2),
                                        IOAddress("0.0.0.0")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       increase(IOAddress("2001:db8:2::1"),
                                                i)));
        cfg.add(host);
    }

    for (unsigned i = 0; i < 25; ++i) {
        // Retrieve host by (subnet-id,address).
        HostPtr host = cfg.get6(SubnetID(1 + i % 2),
                                increase(IOAddress("2001:db8:2::1"), i));
        ASSERT_TRUE(host);

        EXPECT_EQ(1 + i % 2, host->getIPv6SubnetID());
        IPv6ResrvRange reservations =
            host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
        ASSERT_EQ(1, std::distance(reservations.first, reservations.second));
        EXPECT_EQ(increase(IOAddress("2001:db8:2::1"), i),
                  reservations.first->second.getPrefix());
    }
}

TEST_F(CfgHostsTest, get6ByAddr) {
    testGet6ByAddr();
}

TEST_F(CfgHostsTest, get6ByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGet6ByAddr();
}

// This test checks that the IPv6 reservations can be retrieved for a particular
// (subnet-id, address) tuple.
void
CfgHostsTest::testGet6MultipleAddrs() {
    CfgHosts cfg;

    // Add 25 hosts. Each host has reservations for 5 addresses.
    for (unsigned i = 0; i < 25; ++i) {

        // Add host identified by DUID.
        HostPtr host = HostPtr(new Host(duids_[i]->toText(), "duid",
                                        SUBNET_ID_UNUSED, SubnetID(1 + i % 2),
                                        IOAddress("0.0.0.0")));

        // Generate 5 unique addresses for this host.
        for (unsigned j = 0; j < 5; ++j) {
            std::stringstream address_stream;
            address_stream << "2001:db8:" << i << "::" << j;
            host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                           address_stream.str()));
        }
        cfg.add(host);
    }

    // Now check if we can retrieve each of those 25 hosts by using each
    // of their addresses.
    for (unsigned i = 0; i < 25; ++i) {

        // Check that the host is there.
        HostPtr by_duid = cfg.get6(SubnetID(1 + i % 2), Host::IDENT_DUID,
                                   &duids_[i]->getDuid()[0],
                                   duids_[i]->getDuid().size());
        ASSERT_TRUE(by_duid);

        for (unsigned j = 0; j < 5; ++j) {
            std::stringstream address_stream;
            address_stream << "2001:db8:" << i << "::" << j;

            // Retrieve host by (subnet-id,address).
            HostPtr by_addr = cfg.get6(SubnetID(1 + i % 2),
                                       address_stream.str());
            ASSERT_TRUE(by_addr);

            // The pointers should match. Maybe we should compare contents
            // rather than just pointers? I think there's no reason why
            // the code would make any copies of the Host object, so
            // the pointers should always point to the same object.
            EXPECT_EQ(by_duid, by_addr);
        }
    }
}

TEST_F(CfgHostsTest, get6MultipleAddrs) {
    testGet6MultipleAddrs();
}

TEST_F(CfgHostsTest, get6MultipleAddrsMultiThreading) {
    MultiThreadingTest mt(true);
    testGet6MultipleAddrs();
}

// Checks that it's not possible for a second host to reserve an address
// which is already reserved.
void
CfgHostsTest::testAdd4AlreadyReserved() {
    CfgHosts cfg;

    // First host has a reservation for address 192.0.2.1
    HostPtr host1 = HostPtr(new Host(hwaddrs_[0]->toText(false),
                                     "hw-address",
                                     SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                                     IOAddress("192.0.2.1")));
    // Adding this should work.
    EXPECT_NO_THROW(cfg.add(host1));

    // The second host has a reservation for the same address.
    HostPtr host2 = HostPtr(new Host(hwaddrs_[1]->toText(false),
                                     "hw-address",
                                     SubnetID(1), SUBNET_ID_UNUSED,
                                     IOAddress("192.0.2.1")));

    // This second host has a reservation for an address that is already
    // reserved for the first host, so it should be rejected.
    EXPECT_THROW(cfg.add(host2), isc::dhcp::ReservedAddress);
}

TEST_F(CfgHostsTest, add4AlreadyReserved) {
    testAdd4AlreadyReserved();
}

TEST_F(CfgHostsTest, add4AlreadyReservedMultiThreading) {
    MultiThreadingTest mt(true);
    testAdd4AlreadyReserved();
}

// Test that it is possible to allow inserting multiple reservations for
// the same IP address.
void
CfgHostsTest::testAllow4AlreadyReserved() {
    CfgHosts cfg;
    // Allow creating multiple reservations for the same IP address.
    ASSERT_TRUE(cfg.setIPReservationsUnique(false));

    // First host has a reservation for address 192.0.2.1
    HostPtr host1 = HostPtr(new Host(hwaddrs_[0]->toText(false),
                                     "hw-address",
                                     SubnetID(1), SubnetID(SUBNET_ID_UNUSED),
                                     IOAddress("192.0.2.1")));
    ASSERT_NO_THROW(cfg.add(host1));

    // The second host has a reservation for the same address.
    HostPtr host2 = HostPtr(new Host(hwaddrs_[1]->toText(false),
                                     "hw-address",
                                     SubnetID(1), SUBNET_ID_UNUSED,
                                     IOAddress("192.0.2.1")));
    // Adding this should work because the HW address is different.
    ASSERT_NO_THROW(cfg.add(host2));

    // Get both hosts.
    ConstHostCollection returned;
    ASSERT_NO_THROW(returned = cfg.getAll4(host1->getIPv4SubnetID(), IOAddress("192.0.2.1")));
    EXPECT_EQ(2, returned.size());

    // Make sure the address is the same but the identifiers are different.
    EXPECT_NE(returned[0]->getIdentifierAsText(), returned[1]->getIdentifierAsText());
    EXPECT_EQ(returned[0]->getIPv4Reservation().toText(),
              returned[1]->getIPv4Reservation().toText());
}

TEST_F(CfgHostsTest, allow4AlreadyReserved) {
    testAllow4AlreadyReserved();
}

TEST_F(CfgHostsTest, allow4AlreadyReservedMultiThreading) {
    MultiThreadingTest mt(true);
    testAllow4AlreadyReserved();
}

// Checks that it's not possible for two hosts to have the same address
// reserved at the same time.
void
CfgHostsTest::testAdd6Invalid2Hosts() {
    CfgHosts cfg;

    // First host has a reservation for address 2001:db8::1
    HostPtr host1 = HostPtr(new Host(duids_[0]->toText(), "duid",
                                     SUBNET_ID_UNUSED, SubnetID(1),
                                     IOAddress("0.0.0.0")));
    host1->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8::1")));
    // Adding this should work.
    EXPECT_NO_THROW(cfg.add(host1));

    // The second host has a reservation for the same address.
    HostPtr host2 = HostPtr(new Host(duids_[1]->toText(), "duid",
                                     SUBNET_ID_UNUSED, SubnetID(1),
                                     IOAddress("0.0.0.0")));
    host2->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8::1")));

    // This second host has a reservation for an address that is already
    // reserved for the first host, so it should be rejected.
    EXPECT_THROW(cfg.add(host2), isc::dhcp::DuplicateHost);
}

TEST_F(CfgHostsTest, add6Invalid2Hosts) {
    testAdd6Invalid2Hosts();
}

TEST_F(CfgHostsTest, add6Invalid2HostsMultiThreading) {
    MultiThreadingTest mt(true);
    testAdd6Invalid2Hosts();
}

// Test that it is possible to allow inserting multiple reservations for
// the same IPv6 address.
void
CfgHostsTest::testAllowAddress6AlreadyReserved() {
    CfgHosts cfg;
    // Allow creating multiple reservations for the same IP address.
    ASSERT_TRUE(cfg.setIPReservationsUnique(false));

    // First host has a reservation for address 2001:db8::1
    HostPtr host1 = HostPtr(new Host(duids_[0]->toText(), "duid",
                                     SUBNET_ID_UNUSED, SubnetID(1),
                                     IOAddress("0.0.0.0")));
    host1->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8::1")));
    // Adding this should work.
    EXPECT_NO_THROW(cfg.add(host1));

    // The second host has a reservation for the same address.
    HostPtr host2 = HostPtr(new Host(duids_[1]->toText(), "duid",
                                     SUBNET_ID_UNUSED, SubnetID(1),
                                     IOAddress("0.0.0.0")));
    host2->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8::1")));

    // Adding this should work because the DUID is different.
    ASSERT_NO_THROW(cfg.add(host2));

    ConstHostCollection returned;
    ASSERT_NO_THROW(returned = cfg.getAll6(host1->getIPv6SubnetID(), IOAddress("2001:db8::1")));
    EXPECT_EQ(2, returned.size());

    // Make sure the address is the same but the identifiers are different.
    EXPECT_NE(returned[0]->getIdentifierAsText(), returned[1]->getIdentifierAsText());

    auto range0 = returned[0]->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    EXPECT_EQ(1, std::distance(range0.first, range0.second));
    auto range1 = returned[1]->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    EXPECT_EQ(1, std::distance(range1.first, range1.second));
    EXPECT_EQ(range0.first->second.getPrefix().toText(),
              range1.first->second.getPrefix().toText());
}

TEST_F(CfgHostsTest, allowAddress6AlreadyReserved) {
    testAllowAddress6AlreadyReserved();
}

TEST_F(CfgHostsTest, allowAddress6AlreadyReservedMultiThreading) {
    MultiThreadingTest mt(true);
    testAllowAddress6AlreadyReserved();
}

// Test that it is possible to allow inserting multiple reservations for
// the same IPv6 delegated prefix.
void
CfgHostsTest::testAllowPrefix6AlreadyReserved() {
    CfgHosts cfg;
    // Allow creating multiple reservations for the same delegated prefix.
    ASSERT_TRUE(cfg.setIPReservationsUnique(false));

    // First host has a reservation for prefix 3000::/64.
    HostPtr host1 = HostPtr(new Host(duids_[0]->toText(), "duid",
                                     SUBNET_ID_UNUSED, SubnetID(1),
                                     IOAddress("0.0.0.0")));
    host1->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                    IOAddress("3000::"), 64));
    // Adding this should work.
    EXPECT_NO_THROW(cfg.add(host1));

    // The second host has a reservation for the same prefix.
    HostPtr host2 = HostPtr(new Host(duids_[1]->toText(), "duid",
                                     SUBNET_ID_UNUSED, SubnetID(1),
                                     IOAddress("0.0.0.0")));
    host2->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                    IOAddress("3000::"), 64));

    // Adding this should work because the DUID is different.
    ASSERT_NO_THROW(cfg.add(host2));

    ConstHostCollection returned;
    ASSERT_NO_THROW(returned = cfg.getAll6(host1->getIPv6SubnetID(), IOAddress("3000::")));
    EXPECT_EQ(2, returned.size());

    // Make sure the prefix is the same but the identifiers are different.
    EXPECT_NE(returned[0]->getIdentifierAsText(), returned[1]->getIdentifierAsText());

    auto range0 = returned[0]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    EXPECT_EQ(1, std::distance(range0.first, range0.second));
    auto range1 = returned[1]->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    EXPECT_EQ(1, std::distance(range1.first, range1.second));
    EXPECT_EQ(range0.first->second.getPrefix().toText(),
              range1.first->second.getPrefix().toText());
}

TEST_F(CfgHostsTest, allowPrefix6AlreadyReserved) {
    testAllowPrefix6AlreadyReserved();
}

TEST_F(CfgHostsTest, allowPrefix6AlreadyReservedMultiThreading) {
    MultiThreadingTest mt(true);
    testAllowPrefix6AlreadyReserved();
}

// Check that no error is reported when adding a host with subnet
// ids equal to global.
TEST_F(CfgHostsTest, globalSubnetIDs) {
    CfgHosts cfg;
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SUBNET_ID_GLOBAL, SUBNET_ID_GLOBAL,
                                             IOAddress("10.0.0.1")))));
}


// Check that error is reported when trying to add a host with subnet
// ids equal to unused.
TEST_F(CfgHostsTest, unusedSubnetIDs) {
    CfgHosts cfg;
    ASSERT_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                          "hw-address",
                                          SUBNET_ID_UNUSED, SUBNET_ID_UNUSED,
                                          IOAddress("10.0.0.1")))),
                 isc::BadValue);
}

// This test verifies that it is not possible to add the same Host to the
// same IPv4 subnet twice.
void
CfgHostsTest::testDuplicatesSubnet4HWAddr() {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SubnetID(10), SUBNET_ID_UNUSED,
                                             IOAddress("10.0.0.1")))));

    // Try to add the host with the same HW address to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                          "hw-address",
                                          SubnetID(10), SUBNET_ID_UNUSED,
                                          IOAddress("10.0.0.10")))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SubnetID(11), SUBNET_ID_UNUSED,
                                             IOAddress("10.0.0.10")))));
}

TEST_F(CfgHostsTest, duplicatesSubnet4HWAddr) {
    testDuplicatesSubnet4HWAddr();
}

TEST_F(CfgHostsTest, duplicatesSubnet4HWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testDuplicatesSubnet4HWAddr();
}

// This test verifies that it is not possible to add the same Host to the
// same IPv4 subnet twice.
void
CfgHostsTest::testDuplicatesSubnet4DUID() {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SubnetID(10), SUBNET_ID_UNUSED,
                                             IOAddress("10.0.0.1")))));

    // Try to add the host with the same DUID to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                          "duid",
                                          SubnetID(10), SUBNET_ID_UNUSED,
                                          IOAddress("10.0.0.10")))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SubnetID(11), SUBNET_ID_UNUSED,
                                             IOAddress("10.0.0.10")))));
}

TEST_F(CfgHostsTest, duplicatesSubnet4DUID) {
    testDuplicatesSubnet4DUID();
}

TEST_F(CfgHostsTest, duplicatesSubnet4DUIDMultiThreading) {
    MultiThreadingTest mt(true);
    testDuplicatesSubnet4DUID();
}

// This test verifies that it is not possible to add the same Host to the
// same IPv6 subnet twice.
void
CfgHostsTest::testDuplicatesSubnet6HWAddr() {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SUBNET_ID_UNUSED, SubnetID(1),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));

    // Try to add the host with the same HW address to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                          "hw-address",
                                          SUBNET_ID_UNUSED, SubnetID(1),
                                          IOAddress("0.0.0.0"),
                                          "foo.example.com"))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(hwaddrs_[0]->toText(false),
                                             "hw-address",
                                             SUBNET_ID_UNUSED, SubnetID(2),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));
}

TEST_F(CfgHostsTest, duplicatesSubnet6HWAddr) {
    testDuplicatesSubnet6HWAddr();
}

TEST_F(CfgHostsTest, duplicatesSubnet6HWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testDuplicatesSubnet6HWAddr();
}

// This test verifies that it is not possible to add the same Host to the
// same IPv6 subnet twice.
void
CfgHostsTest::testDuplicatesSubnet6DUID() {
    CfgHosts cfg;
    // Add a host.
    ASSERT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SUBNET_ID_UNUSED, SubnetID(1),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));

    // Try to add the host with the same DUID to the same subnet. The fact
    // that the IP address is different here shouldn't really matter.
    EXPECT_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                          "duid",
                                          SUBNET_ID_UNUSED, SubnetID(1),
                                          IOAddress("0.0.0.0"),
                                          "foo.example.com"))),
                 isc::dhcp::DuplicateHost);

    // Now try to add it to a different subnet. It should go through.
    EXPECT_NO_THROW(cfg.add(HostPtr(new Host(duids_[0]->toText(),
                                             "duid",
                                             SUBNET_ID_UNUSED, SubnetID(2),
                                             IOAddress("0.0.0.0"),
                                             "foo.example.com"))));
}

TEST_F(CfgHostsTest, duplicatesSubnet6DUID) {
    testDuplicatesSubnet6DUID();
}

TEST_F(CfgHostsTest, duplicatesSubnet6DUIDMultiThreading) {
    MultiThreadingTest mt(true);
    testDuplicatesSubnet6DUID();
}

// Checks that updates work correctly.
void
CfgHostsTest::testUpdate() {
    CfgHosts cfg;

    HostPtr const host(boost::make_shared<Host>(duids_[0]->toText(), "duid", SUBNET_ID_UNUSED,
                                                SubnetID(1), IOAddress("0.0.0.0"),
                                                "foo.example.com"));

    // Updating a host that doesn't exist should throw.
    EXPECT_THROW_MSG(cfg.update(host), HostNotFound, "Host not updated (not found).");

    // There should be no hosts.
    HostCollection hosts(cfg.getAll6(SubnetID(1)));
    EXPECT_EQ(0, hosts.size());

    // Add a host.
    EXPECT_NO_THROW(cfg.add(host));

    // The host should be in the config.
    hosts = cfg.getAll6(SubnetID(1));
    ASSERT_EQ(1, hosts.size());
    EXPECT_EQ("duid=010203040500 ipv6_subnet_id=1 hostname=foo.example.com "
              "ipv4_reservation=(no) siaddr=(no) sname=(empty) file=(empty) "
              "key=(empty) ipv6_reservations=(none)", hosts[0]->toText());

    // Update the host. Change nothing.
    EXPECT_NO_THROW(cfg.update(host));

    // The same host should be in the config.
    hosts = cfg.getAll6(SubnetID(1));
    ASSERT_EQ(1, hosts.size());
    EXPECT_EQ("duid=010203040500 ipv6_subnet_id=1 hostname=foo.example.com "
              "ipv4_reservation=(no) siaddr=(no) sname=(empty) file=(empty) "
              "key=(empty) ipv6_reservations=(none)", hosts[0]->toText());

    // Update the host with new hostname.
    host->setHostname("bar.example.com");
    EXPECT_NO_THROW(cfg.update(host));

    // The change should be reflected in the config.
    hosts = cfg.getAll6(SubnetID(1));
    ASSERT_EQ(1, hosts.size());
    EXPECT_EQ("duid=010203040500 ipv6_subnet_id=1 hostname=bar.example.com "
              "ipv4_reservation=(no) siaddr=(no) sname=(empty) file=(empty) "
              "key=(empty) ipv6_reservations=(none)", hosts[0]->toText());

    // Remove hostname from host.
    host->setHostname("");
    EXPECT_NO_THROW(cfg.update(host));

    // The change should be reflected in the config.
    hosts = cfg.getAll6(SubnetID(1));
    ASSERT_EQ(1, hosts.size());
    EXPECT_EQ("duid=010203040500 ipv6_subnet_id=1 hostname=(empty) "
              "ipv4_reservation=(no) siaddr=(no) sname=(empty) file=(empty) "
              "key=(empty) ipv6_reservations=(none)", hosts[0]->toText());
}

TEST_F(CfgHostsTest, update) {
    testUpdate();
}

TEST_F(CfgHostsTest, updateMultiThreading) {
    MultiThreadingTest mt(true);
    testUpdate();
}

}  // namespace
