// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/tests/test_utils.h>

#if defined HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#endif

#if defined HAVE_PGSQL
#include <pgsql/testutils/pgsql_schema.h>
#endif

#if defined HAVE_CQL
#include <cql/testutils/cql_schema.h>
#endif

#include <gtest/gtest.h>
#include <vector>

using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
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

    /// @brief Inserts IPv4 reservation into the host data source.
    ///
    /// @param data_source Reference to the data source to which the reservation
    /// should be inserted.
    /// @param hwaddr Pointer to the hardware address to be associated with the
    /// reservation.
    /// @param subnet_id IPv4 subnet id.
    /// @param address IPv4 address to be reserved.
    void addHost4(BaseHostDataSource& data_source,
                  const HWAddrPtr& hwaddr,
                  const SubnetID& subnet_id,
                  const IOAddress& address);

    /// @brief Inserts IPv6 reservation into the host data source.
    ///
    /// @param data_source Reference to the data source to which the reservation
    /// should be inserted.
    /// @param duid Pointer to the DUID to be associated with the reservation.
    /// @param subnet_id IPv6 subnet id.
    /// @param address IPv6 address/prefix to be reserved.
    /// @param prefix_len Prefix length. The default value is 128 which
    /// indicates that the reservation is for an IPv6 address rather than a
    /// prefix.
    void addHost6(BaseHostDataSource& data_source,
                  const DuidPtr& duid,
                  const SubnetID& subnet_id,
                  const IOAddress& address,
                  const uint8_t prefix_len = 128);

    /// @brief This test verifies that HostMgr returns all reservations for the
    /// specified HW address.
    ///
    /// If reservations are added to different host data sources, it is expected
    /// that the @c HostMgr will retrieve reservations from both of them.
    ///
    /// @param data_source1 Host data source to which first reservation is
    /// inserted.
    /// @param data_source2 Host data source to which second reservation is
    /// inserted.
    void testGetAll(BaseHostDataSource& data_source1,
                    BaseHostDataSource& data_source2);

    /// @brief This test verifies that HostMgr returns all reservations for the
    /// specified DHCPv4 subnet.
    ///
    /// If reservations are added to different host data sources, it is expected
    /// that the @c HostMgr will retrieve reservations from both of them.
    ///
    /// @param data_source1 Host data source to which first reservation is
    /// inserted.
    /// @param data_source2 Host data source to which second reservation is
    /// inserted.
    void testGetAll4BySubnet(BaseHostDataSource& data_source1,
                             BaseHostDataSource& data_source2);

    /// @brief This test verifies that HostMgr returns all reservations for the
    /// specified DHCPv6 subnet.
    ///
    /// If reservations are added to different host data sources, it is expected
    /// that the @c HostMgr will retrieve reservations from both of them.
    ///
    /// @param data_source1 Host data source to which first reservation is
    /// inserted.
    /// @param data_source2 Host data source to which second reservation is
    /// inserted.
    void testGetAll6BySubnet(BaseHostDataSource& data_source1,
                             BaseHostDataSource& data_source2);

    /// @brief This test verifies that HostMgr returns all reservations for the
    /// specified DHCPv4 subnet by pages.
    ///
    /// If reservations are added to different host data sources, it is expected
    /// that the @c HostMgr will retrieve reservations from both of them.
    ///
    /// @param use_database True when the second reservation is inserted
    /// in a database.
    void testGetPage4(bool use_database);

    /// @brief This test verifies that HostMgr returns all reservations for the
    /// specified DHCPv6 subnet by pages.
    ///
    /// If reservations are added to different host data sources, it is expected
    /// that the @c HostMgr will retrieve reservations from both of them.
    ///
    /// @param use_database True when the second reservation is inserted
    /// in a database.
    void testGetPage6(bool use_database);

    /// @brief This test verifies that it is possible to retrieve IPv4
    /// reservation for the particular host using HostMgr.
    ///
    /// If reservations are added to different host data sources, it is expected
    /// that the @c HostMgr will retrieve reservations from both of them.
    ///
    /// @param data_source1 Host data source to which first reservation is
    /// inserted.
    /// @param data_source2 Host data source to which second reservation is
    /// inserted.
    void testGetAll4(BaseHostDataSource& data_source1,
                     BaseHostDataSource& data_source2);

    /// @brief This test verifies that it is possible to retrieve an IPv4
    /// reservation for the particular host using HostMgr.
    ///
    /// @param data_source Host data source to which reservation is inserted and
    /// from which it will be retrieved.
    void testGet4(BaseHostDataSource& data_source);

    /// @brief This test verifies that it is possible to retrieve negative
    /// cached reservation with and only with get4Any.
    void testGet4Any();

    /// @brief This test verifies that it is possible to retrieve an IPv6
    /// reservation for the particular host using HostMgr.
    ///
    /// @param data_source Host data source to which reservation is inserted and
    /// from which it will be retrieved.
    void testGet6(BaseHostDataSource& data_source);

    /// @brief This test verifies that it is possible to retrieve negative
    /// cached reservation with and only with get6Any.
    void testGet6Any();

    /// @brief This test verifies that it is possible to retrieve an IPv6
    /// prefix reservation for the particular host using HostMgr.
    ///
    /// @param data_source1 Host data source to which first reservation is
    /// inserted.
    /// @param data_source2 Host data source to which second reservation is
    /// inserted.
    void testGet6ByPrefix(BaseHostDataSource& data_source1,
                          BaseHostDataSource& data_source2);

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

void
HostMgrTest::addHost4(BaseHostDataSource& data_source,
                      const HWAddrPtr& hwaddr,
                      const SubnetID& subnet_id,
                      const IOAddress& address) {
    data_source.add(HostPtr(new Host(hwaddr->toText(false),
                                     "hw-address", subnet_id, SUBNET_ID_UNUSED,
                                     address)));
}

void
HostMgrTest::addHost6(BaseHostDataSource& data_source,
                      const DuidPtr& duid,
                      const SubnetID& subnet_id,
                      const IOAddress& address,
                      const uint8_t prefix_len) {
    HostPtr new_host(new Host(duid->toText(), "duid", SubnetID(1),
                              subnet_id, IOAddress::IPV4_ZERO_ADDRESS()));
    new_host->addReservation(IPv6Resrv(prefix_len == 128 ? IPv6Resrv::TYPE_NA :
                                       IPv6Resrv::TYPE_PD,
                                       address, prefix_len));
    data_source.add(new_host);
}


void
HostMgrTest::testGetAll(BaseHostDataSource& data_source1,
                        BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts =
        HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                   &hwaddrs_[1]->hwaddr_[0],
                                   hwaddrs_[1]->hwaddr_.size());
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same HW address. They differ by the IP
    // address reserved and the IPv4 subnet.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[0], SubnetID(10), IOAddress("192.0.3.10"));

    CfgMgr::instance().commit();

    // If there non-matching HW address is specified, nothing should be
    // returned.
    hosts = HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                       &hwaddrs_[1]->hwaddr_[0],
                                       hwaddrs_[1]->hwaddr_.size());
    ASSERT_TRUE(hosts.empty());

    // For the correct HW address, there should be two reservations.
    hosts = HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size());
    ASSERT_EQ(2, hosts.size());

    // We don't know the order in which the reservations are returned so
    // we have to match with any of the two reservations returned.

    // Look for the first reservation.
    bool found = false;
    for (unsigned i = 0; i < 2; ++i) {
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
    for (unsigned i = 0; i < 2; ++i) {
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

void
HostMgrTest::testGetAll4BySubnet(BaseHostDataSource& data_source1,
                                 BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll4(SubnetID(1));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same subnet.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[1], SubnetID(1), IOAddress("192.0.2.6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll4(SubnetID(100));
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    hosts = HostMgr::instance().getAll4(SubnetID(1));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv4SubnetID());

    // Make sure that two different hosts were returned.
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("192.0.2.6", hosts[1]->getIPv4Reservation().toText());
}

void
HostMgrTest::testGetAll6BySubnet(BaseHostDataSource& data_source1,
                                 BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll6(SubnetID(1));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same subnet.
    addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[1], SubnetID(1), IOAddress("2001:db8:1::6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll6(SubnetID(100));
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    hosts = HostMgr::instance().getAll6(SubnetID(1));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());

    // Make sure that two different hosts were returned.
    EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    EXPECT_TRUE(hosts[1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));
}

void
HostMgrTest::testGetPage4(bool use_database) {
    BaseHostDataSource& data_source1 = *getCfgHosts();
    BaseHostDataSource& data_source2 = HostMgr::instance();

    // Initially, no reservations should be present.
    size_t idx(0);
    HostPageSize page_size(10);
    ConstHostCollection hosts =
        HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());
    if (use_database) {
        EXPECT_EQ(2, idx);
    } else {
        EXPECT_EQ(1, idx);
    }

    // Add two reservations for the same subnet.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(use_database ? data_source2 : data_source1,
             hwaddrs_[1], SubnetID(1), IOAddress("192.0.2.6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    idx = 0;
    hosts = HostMgr::instance().getPage4(SubnetID(100), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    idx = 0;
    hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
    if (use_database) {
        ASSERT_EQ(1, hosts.size());
    } else {
        ASSERT_EQ(2, hosts.size());
    }

    // Make sure that returned values are correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    if (!use_database) {
        EXPECT_EQ(1, hosts[1]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[1]->getIPv4Reservation().toText());

        // Check it was the last page.
        uint64_t hid = hosts[1]->getHostId();
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 1;
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }

    if (use_database) {
        uint64_t hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        ASSERT_EQ(0, idx);
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(1, hosts.size());
        ASSERT_NE(0, idx);
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[0]->getIPv4Reservation().toText());

        // Alternate way to use the database.
        idx = 1;
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[0]->getIPv4Reservation().toText());

        // Check it was the last page.
        hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 2;
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }
}

void
HostMgrTest::testGetPage6(bool use_database) {
    BaseHostDataSource& data_source1 = *getCfgHosts();
    BaseHostDataSource& data_source2 = HostMgr::instance();

    // Initially, no reservations should be present.
    size_t idx(0);
    HostPageSize page_size(10);
    ConstHostCollection hosts =
        HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());
    if (use_database) {
        EXPECT_EQ(2, idx);
    } else {
        EXPECT_EQ(1, idx);
    }

    // Add two reservations for the same subnet.
    addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(use_database ? data_source2 : data_source1,
             duids_[1], SubnetID(1), IOAddress("2001:db8:1::6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    idx = 0;
    hosts = HostMgr::instance().getPage6(SubnetID(100), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    idx = 0;
    hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
    if (use_database) {
        ASSERT_EQ(1, hosts.size());
    } else {
        ASSERT_EQ(2, hosts.size());
    }

    // Make sure that returned values are correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    if (!use_database) {
        EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[1]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Check it was the last page.
        uint64_t hid = hosts[1]->getHostId();
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 1;
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }

    if (use_database) {
        uint64_t hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        ASSERT_EQ(0, idx);
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(1, hosts.size());
        ASSERT_NE(0, idx);
        EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[0]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Alternate way to use the database.
        idx = 1;
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[0]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Check it was the last page.
        hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 2;
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }
}

void
HostMgrTest::testGetAll4(BaseHostDataSource& data_source1,
                         BaseHostDataSource& data_source2) {
    // Initially, no hosts should be present.
    ConstHostCollection hosts =
        HostMgr::instance().getAll4(IOAddress("192.0.2.5"));
    ASSERT_TRUE(hosts.empty());

    // Add two hosts to different data sources.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[1], SubnetID(10), IOAddress("192.0.2.5"));

    CfgMgr::instance().commit();

    // Retrieve all hosts, This should return hosts from both sources
    // in a single container.
    hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5"));
    ASSERT_EQ(2, hosts.size());

    // Make sure that IPv4 address is correct.
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("192.0.2.5", hosts[1]->getIPv4Reservation().toText());

    // Make sure that two different hosts were returned.
    EXPECT_NE(hosts[0]->getIPv4SubnetID(), hosts[1]->getIPv4SubnetID());
}

void
HostMgrTest::testGet4(BaseHostDataSource& data_source) {
    // Initially, no host should be present.
    ConstHostPtr host =
        HostMgr::instance().get4(SubnetID(1), Host::IDENT_HWADDR,
                                 &hwaddrs_[0]->hwaddr_[0],
                                 hwaddrs_[0]->hwaddr_.size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    addHost4(data_source, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());
}

void
HostMgrTest::testGet4Any() {
    // Initially, no host should be present.
    ConstHostPtr host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                                 &duids_[0]->getDuid()[0],
                                                 duids_[0]->getDuid().size());
    ASSERT_FALSE(host);
    HostMgr::instance().get4Any(SubnetID(1), Host::IDENT_DUID,
                                &duids_[0]->getDuid()[0],
                                duids_[0]->getDuid().size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    HostPtr new_host(new Host(duids_[0]->toText(), "duid", SubnetID(1),
                              SUBNET_ID_UNUSED, IOAddress("192.0.2.5")));
    // Abuse of the server's configuration.
    getCfgHosts()->add(new_host);

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());

    // Set the negative cache flag on the host.
    new_host->setNegative(true);

    // get4 is not supposed to get it.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    EXPECT_FALSE(host);

    // But get4Any should.
    host = HostMgr::instance().get4Any(SubnetID(1), Host::IDENT_DUID,
                                       &duids_[0]->getDuid()[0],
                                       duids_[0]->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());
    EXPECT_TRUE(host->getNegative());

    // To be sure. Note we use the CfgHosts source so only this
    // get4 overload works.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    EXPECT_FALSE(host);
}

void
HostMgrTest::testGet6(BaseHostDataSource& data_source) {
    // Initially, no host should be present.
    ConstHostPtr host =
        HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                 &duids_[0]->getDuid()[0],
                                 duids_[0]->getDuid().size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    addHost6(data_source, duids_[0], SubnetID(2), IOAddress("2001:db8:1::1"));

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));
}

void
HostMgrTest::testGet6Any() {
    // Initially, no host should be present.
    ConstHostPtr host = HostMgr::instance().get6(SubnetID(2),
                                                 Host::IDENT_HWADDR,
                                                 &hwaddrs_[0]->hwaddr_[0],
                                                 hwaddrs_[0]->hwaddr_.size());
    ASSERT_FALSE(host);
    host = HostMgr::instance().get6Any(SubnetID(2), Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    HostPtr new_host(new Host(hwaddrs_[0]->toText(false), "hw-address",
                              SubnetID(1), SubnetID(2),
                              IOAddress::IPV4_ZERO_ADDRESS()));
    new_host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8:1::1"), 128));
    // Abuse of the server's configuration.
    getCfgHosts()->add(new_host);

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));

    // Set the negative cache flag on the host.
    new_host->setNegative(true);

    // get6 is not supposed to get it.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    EXPECT_FALSE(host);

    // But get6Any should.
    host = HostMgr::instance().get6Any(SubnetID(2), Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size());
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));
    EXPECT_TRUE(host->getNegative());

    // To be sure. Note we use the CfgHosts source so only this
    // get6 overload works.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    EXPECT_FALSE(host);
}

void
HostMgrTest::testGet6ByPrefix(BaseHostDataSource& data_source1,
                              BaseHostDataSource& data_source2) {
    ConstHostPtr host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64);
    ASSERT_FALSE(host);

    // Add a host with a reservation for a prefix 2001:db8:1::/64.
    addHost6(data_source1, duids_[0], SubnetID(2), IOAddress("2001:db8:1::"), 64);

    // Add another host having a reservation for prefix 2001:db8:1:0:6::/72.
    addHost6(data_source2, duids_[1], SubnetID(3), IOAddress("2001:db8:1:0:6::"), 72);

    CfgMgr::instance().commit();

    // Retrieve first reservation.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64);
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1::"), 64)));

    // Make sure the first reservation is not retrieved when the prefix
    // length is incorrect.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 72);
    EXPECT_FALSE(host);

    // Retrieve second reservation.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1:0:6::"), 72);
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1:0:6::"), 72)));

    // Make sure the second reservation is not retrieved when the prefix
    // length is incorrect.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1:0:6::"), 64);
    EXPECT_FALSE(host);
}

// This test verifies that HostMgr returns all reservations for the
// specified HW address. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv4 subnet. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAll4BySubnet) {
    testGetAll4BySubnet(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv6 subnet. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAll6BySubnet) {
    testGetAll6BySubnet(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv4 subnet by pages. The reservations are defined in
// the server's configuration.
TEST_F(HostMgrTest, getPage4) {
    testGetPage4(false);
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv6 subnet by pages. The reservations are defined in
// the server's configuration.
TEST_F(HostMgrTest, getPage6) {
    testGetPage6(false);
}

// This test verifies that it is possible to gather all reservations for the
// specified IPv4 address from the HostMgr. The reservations are specified in
// the server's configuration.
TEST_F(HostMgrTest, getAll4) {
    testGetAll4(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that it is possible to retrieve a reservation for the
// particular host using HostMgr. The reservation is specified in the server's
// configuration.
TEST_F(HostMgrTest, get4) {
    testGet4(*getCfgHosts());
}

// This test verifies handling of negative caching by get4/get4Any.
TEST_F(HostMgrTest, get4Any) {
    testGet4Any();
}

// This test verifies that it is possible to retrieve IPv6 reservations for
// the particular host using HostMgr. The reservation is specified in the
// server's configuration.
TEST_F(HostMgrTest, get6) {
    testGet6(*getCfgHosts());
}

// This test verifies handling of negative caching by get4/get4Any.
TEST_F(HostMgrTest, get6Any) {
    testGet6Any();
}

// This test verifies that it is possible to retrieve the reservation of the
// particular IPv6 prefix using HostMgr.
TEST_F(HostMgrTest, get6ByPrefix) {
    testGet6ByPrefix(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that without a host data source an exception is thrown.
TEST_F(HostMgrTest, addNoDataSource) {
    // Remove all configuration.
    CfgMgr::instance().clear();
    // Recreate HostMgr instance.
    HostMgr::create();

    HostPtr host(new Host(hwaddrs_[0]->toText(false), "hw-address",
                          SubnetID(1), SUBNET_ID_UNUSED, IOAddress("192.0.2.5")));
    EXPECT_THROW(HostMgr::instance().add(host), NoHostDataSourceManager);
}

class HostMgrDbLostCallbackTest : public ::testing::Test {
public:
    HostMgrDbLostCallbackTest() : callback_called_(false) {};

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and create a basic host manager to
    /// wipe out any prior instance
    virtual void SetUp() {
        DatabaseConnection::db_lost_callback = 0;
        // Ensure we have the proper schema with no transient data.
        createSchema();
        // Wipe out any pre-existing mgr
        HostMgr::create();
    }

    /// @brief Pre-text exit clean up
    ///
    /// Invoked by gtest upon test exit, we destroy the schema
    /// we created.
    virtual void TearDown() {
        DatabaseConnection::db_lost_callback = 0;
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroySchema();
    }

    /// @brief Abstract method for destroying the back end specific shcema
    virtual void destroySchema() = 0;

    /// @brief Abstract method for creating the back end specific shcema
    virtual void createSchema() = 0;

    /// @brief Abstract method which returns the back end specific connection
    /// string
    virtual std::string validConnectString() = 0;

#if defined(HAVE_MYSQL) || defined(HAVE_PGSQL)
    /// @brief Verifies the host manager's behavior if DB connection is lost
    ///
    /// This function creates a host manager with an alternate data source
    /// that supports connectivity lost callback (currently only MySQL and
    /// PostgreSQL currently).  It verifies connectivity by issuing a known
    /// valid query.  Next it simulates connectivity lost by identifying and
    /// closing the socket connection to the host backend.  It then reissues
    /// the query and verifies that:
    /// -# The Query throws  DbOperationError (rather than exiting)
    /// -# The registered DbLostCallback was invoked
    void testDbLostCallback();
#endif

    /// @brief Callback function registered with the host manager
    bool db_lost_callback(ReconnectCtlPtr /* not_used */) {
        return (callback_called_ = true);
    }

    /// @brief Flag used to detect calls to db_lost_callback function
    bool callback_called_;
};

#if defined(HAVE_MYSQL) || defined(HAVE_PGSQL)
void
HostMgrDbLostCallbackTest::testDbLostCallback() {
    // Create the HostMgr.
    HostMgr::create();

    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback =
        boost::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, _1);

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Connect to the host backend.
    ASSERT_NO_THROW(HostMgr::addBackend(validConnectString()));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Clear the callback invocation marker.
    callback_called_ = false;

    // Verify we can execute a query.  We don't care about the answer.
    ConstHostCollection hosts;
    ASSERT_NO_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")));

    // Now close the sql socket out from under backend client
    ASSERT_FALSE(close(sql_socket)) << "failed to close socket";

    // A query should fail with DbOperationError.
    ASSERT_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")),
                 DbOperationError);

    // Our lost connectivity callback should have been invoked.
    EXPECT_TRUE(callback_called_);
}
#endif

// The following tests require MySQL enabled.
#if defined HAVE_MYSQL

/// @brief Test fixture class for validating @c HostMgr using
/// MySQL as alternate host data source.
class MySQLHostMgrTest : public HostMgrTest {
protected:

    /// @brief Build MySQL schema for a test.
    virtual void SetUp();

    /// @brief Rollback and drop MySQL schema after the test.
    virtual void TearDown();
};

void
MySQLHostMgrTest::SetUp() {
    HostMgrTest::SetUp();

    // Ensure we have the proper schema with no transient data.
    db::test::createMySQLSchema();

    // Connect to the database
    try {
        HostMgr::addBackend(db::test::validMySQLConnectionString());
    } catch (...) {
        std::cerr << "*** ERROR: unable to open database. The test\n"
            "*** environment is broken and must be fixed before\n"
            "*** the MySQL tests will run correctly.\n"
            "*** The reason for the problem is described in the\n"
            "*** accompanying exception output.\n";
        throw;
    }
}

void
MySQLHostMgrTest::TearDown() {
    HostMgr::instance().getHostDataSource()->rollback();
    HostMgr::delBackend("mysql");

    // If data wipe enabled, delete transient data otherwise destroy the schema
    db::test::destroyMySQLSchema();
}

/// @brief Test fixture class for validating @c HostMgr using
/// MySQL as alternate host data source and MySQL connectivity loss.
class MySQLHostMgrDbLostCallbackTest : public HostMgrDbLostCallbackTest {
public:
    virtual void destroySchema() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        db::test::destroyMySQLSchema();
    }

    virtual void createSchema() {
        // Ensure we have the proper schema with no transient data.
        db::test::createMySQLSchema();
    }

    virtual std::string validConnectString() {
        return (db::test::validMySQLConnectionString());
    }
};

// This test verifies that reservations for a particular client can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll4BySubnet) {
    testGetAll4BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll6BySubnet) {
    testGetAll6BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
TEST_F(MySQLHostMgrTest, getPage4) {
    testGetPage4(true);
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
TEST_F(MySQLHostMgrTest, getPage6) {
    testGetPage6(true);
}

// This test verifies that IPv4 reservations for a particular client can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll4) {
    testGetAll4(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that the IPv4 reservation can be retrieved from a
// database.
TEST_F(MySQLHostMgrTest, get4) {
    testGet4(HostMgr::instance());
}

// This test verifies that the IPv6 reservation can be retrieved from a
// database.
TEST_F(MySQLHostMgrTest, get6) {
    testGet6(HostMgr::instance());
}

// This test verifies that the IPv6 prefix reservation can be retrieved
// from a configuration file and a database.
TEST_F(MySQLHostMgrTest, get6ByPrefix) {
    testGet6ByPrefix(*getCfgHosts(), HostMgr::instance());
}

// Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostCallback) {
    testDbLostCallback();
}
#endif


// The following tests require PostgreSQL enabled.
#if defined HAVE_PGSQL

/// @brief Test fixture class for validating @c HostMgr using
/// PostgreSQL as alternate host data source.
class PostgreSQLHostMgrTest : public HostMgrTest {
protected:

    /// @brief Build PostgreSQL schema for a test.
    virtual void SetUp();

    /// @brief Rollback and drop PostgreSQL schema after the test.
    virtual void TearDown();
};

void
PostgreSQLHostMgrTest::SetUp() {
    HostMgrTest::SetUp();

    // Ensure we have the proper schema with no transient data.
    db::test::createPgSQLSchema();

    // Connect to the database
    try {
        HostMgr::addBackend(db::test::validPgSQLConnectionString());
    } catch (...) {
        std::cerr << "*** ERROR: unable to open database. The test\n"
            "*** environment is broken and must be fixed before\n"
            "*** the PostgreSQL tests will run correctly.\n"
            "*** The reason for the problem is described in the\n"
            "*** accompanying exception output.\n";
        throw;
    }
}

void
PostgreSQLHostMgrTest::TearDown() {
    HostMgr::instance().getHostDataSource()->rollback();
    HostMgr::delBackend("postgresql");
    // If data wipe enabled, delete transient data otherwise destroy the schema
    db::test::destroyPgSQLSchema();
}

/// @brief Test fixture class for validating @c HostMgr using
/// PostgreSQL as alternate host data source and PostgreSQL connectivity loss.
class PostgreSQLHostMgrDbLostCallbackTest : public HostMgrDbLostCallbackTest {
public:
    virtual void destroySchema() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        db::test::destroyPgSQLSchema();
    }

    virtual void createSchema() {
        // Ensure we have the proper schema with no transient data.
        db::test::createPgSQLSchema();
    }

    virtual std::string validConnectString() {
        return (db::test::validPgSQLConnectionString());
    }
};

// This test verifies that reservations for a particular client can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(PostgreSQLHostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(PostgreSQLHostMgrTest, getAll4BySubnet) {
    testGetAll4BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(PostgreSQLHostMgrTest, getAll6BySubnet) {
    testGetAll6BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
TEST_F(PostgreSQLHostMgrTest, getPage4) {
    testGetPage4(true);
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
TEST_F(PostgreSQLHostMgrTest, getPage6) {
    testGetPage6(true);
}

// This test verifies that IPv4 reservations for a particular client can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(PostgreSQLHostMgrTest, getAll4) {
    testGetAll4(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that the IPv4 reservation can be retrieved from a
// database.
TEST_F(PostgreSQLHostMgrTest, get4) {
    testGet4(HostMgr::instance());
}

// This test verifies that the IPv6 reservation can be retrieved from a
// database.
TEST_F(PostgreSQLHostMgrTest, get6) {
    testGet6(HostMgr::instance());
}

// This test verifies that the IPv6 prefix reservation can be retrieved
// from a configuration file and a database.
TEST_F(PostgreSQLHostMgrTest, get6ByPrefix) {
    testGet6ByPrefix(*getCfgHosts(), HostMgr::instance());
}

// Verifies that loss of connectivity to PostgreSQL is handled correctly.
TEST_F(PostgreSQLHostMgrDbLostCallbackTest, testDbLostCallback) {
    testDbLostCallback();
}
#endif

// The following tests require Cassandra enabled.
#if defined HAVE_CQL

/// @brief Test fixture class for validating @c HostMgr using
/// CQL as alternate host data source.
class CQLHostMgrTest : public HostMgrTest {
protected:

    /// @brief Build CQL schema for a test.
    virtual void SetUp();

    /// @brief Rollback and drop CQL schema after the test.
    virtual void TearDown();
};

void
CQLHostMgrTest::SetUp() {
    HostMgrTest::SetUp();

    // Ensure we have the proper schema with no transient data.
    db::test::createCqlSchema();

    // Connect to the database
    try {
        HostMgr::addBackend(db::test::validCqlConnectionString());
    } catch (...) {
        std::cerr << "*** ERROR: unable to open database. The test\n"
            "*** environment is broken and must be fixed before\n"
            "*** the CQL tests will run correctly.\n"
            "*** The reason for the problem is described in the\n"
            "*** accompanying exception output.\n";
        throw;
    }
}

void
CQLHostMgrTest::TearDown() {
    HostMgr::instance().getHostDataSource()->rollback();
    HostMgr::delBackend("cql");

    // If data wipe enabled, delete transient data otherwise destroy the schema
    db::test::destroyCqlSchema();
}

// This test verifies that reservations for a particular client can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(CQLHostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(CQLHostMgrTest, getAll4BySubnet) {
    testGetAll4BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(CQLHostMgrTest, getAll6BySubnet) {
    testGetAll6BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
//// Paging is not supported by Cassandra.
TEST_F(CQLHostMgrTest, DISABLED_getPage4) {
    testGetPage4(true);
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
//// Paging is not supported by Cassandra.
TEST_F(CQLHostMgrTest, DISABLED_getPage6) {
    testGetPage6(true);
}

// This test verifies that IPv4 reservations for a particular client can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(CQLHostMgrTest, getAll4) {
    testGetAll4(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that the IPv4 reservation can be retrieved from a
// database.
TEST_F(CQLHostMgrTest, get4) {
    testGet4(HostMgr::instance());
}

// This test verifies that the IPv6 reservation can be retrieved from a
// database.
TEST_F(CQLHostMgrTest, get6) {
    testGet6(HostMgr::instance());
}

// This test verifies that the IPv6 prefix reservation can be retrieved
// from a configuration file and a database.
TEST_F(CQLHostMgrTest, get6ByPrefix) {
    testGet6ByPrefix(*getCfgHosts(), HostMgr::instance());
}

#endif

}  // namespace
