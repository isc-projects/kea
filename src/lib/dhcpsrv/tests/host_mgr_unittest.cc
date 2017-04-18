// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
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

#if defined HAVE_MYSQL
#include <dhcpsrv/testutils/mysql_schema.h>
#endif

#if defined HAVE_PGSQL
#include <dhcpsrv/testutils/pgsql_schema.h>
#endif

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

    /// @brief This test verifies that it is possible to retrieve an IPv6
    /// reservation for the particular host using HostMgr.
    ///
    /// @param data_source Host data source to which reservation is inserted and
    /// from which it will be retrieved.
    void testGet6(BaseHostDataSource& data_source);

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
                                     "hw-address", subnet_id, SubnetID(0),
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
    ConstHostCollection hosts = HostMgr::instance().getAll(hwaddrs_[0]);
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
    ConstHostPtr host = HostMgr::instance().get4(SubnetID(1), hwaddrs_[0]);
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
HostMgrTest::testGet6(BaseHostDataSource& data_source) {
    // Initially, no host should be present.
    ConstHostPtr host = HostMgr::instance().get6(SubnetID(2), duids_[0]);
    ASSERT_FALSE(host);

    // Add new host to the database.
    addHost6(data_source, duids_[0], SubnetID(2), IOAddress("2001:db8:1::1"));

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));
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

/// This test verifies that HostMgr returns all reservations for the
/// specified HW address. The reservations are defined in the server's
/// configuration.
TEST_F(HostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), *getCfgHosts());
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

// This test verifies that it is possible to retrieve IPv6 reservations for
// the particular host using HostMgr. The reservation is specified in the
// server's configuration.
TEST_F(HostMgrTest, get6) {
    testGet6(*getCfgHosts());
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
                          SubnetID(1), SubnetID(0), IOAddress("192.0.2.5")));
    EXPECT_THROW(HostMgr::instance().add(host), NoHostDataSourceManager);
}

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

    // Ensure schema is the correct one.
    test::destroyMySQLSchema();
    test::createMySQLSchema();

    // Connect to the database
    try {
        HostMgr::create(test::validMySQLConnectionString());
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
    HostDataSourceFactory::getHostDataSourcePtr()->rollback();
    HostDataSourceFactory::destroy();
    test::destroyMySQLSchema();
}

// This test verifies that reservations for a particular client can
// be retrieved from the confguration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), HostMgr::instance());
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

    // Ensure schema is the correct one.
    test::destroyPgSQLSchema();
    test::createPgSQLSchema();

    // Connect to the database
    try {
        HostMgr::create(test::validPgSQLConnectionString());
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
    HostDataSourceFactory::getHostDataSourcePtr()->rollback();
    HostDataSourceFactory::destroy();
    test::destroyPgSQLSchema();
}

// This test verifies that reservations for a particular client can
// be retrieved from the confguration file and a database simultaneously.
TEST_F(PostgreSQLHostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), HostMgr::instance());
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

#endif

} // end of anonymous namespace
