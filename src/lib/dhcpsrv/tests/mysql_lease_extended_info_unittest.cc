// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/testutils/generic_lease_extended_info_unittest.h>
#include <mysql/testutils/mysql_schema.h>
#include <dhcpsrv/mysql_lease_mgr.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::util;
using namespace std;

namespace {

/// @brief A derivation of the lease manager exposing protected methods.
class NakedMySqlLeaseMgr : public MySqlLeaseMgr {
public:
    /// @brief Constructor.
    ///
    /// Creates an instance of the lease manager.
    ///
    /// @param parameters Parameter map.
    NakedMySqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
        : MySqlLeaseMgr(parameters) {
    }

    /// @brief Destructor.
    virtual ~NakedMySqlLeaseMgr() {
    }

    /// @brief Exposes protected methods.
    using MySqlLeaseMgr::deleteExtendedInfo6;
    using MySqlLeaseMgr::addRelayId6;
    using MySqlLeaseMgr::addRemoteId6;

    /// @brief Return valid connection string.
    static string validConnectionString() {
        return (validMySQLConnectionString());
    }

    /// @brief Create the database schema.
    static void createSchema() {
        createMySQLSchema();
    }

    /// @brief Destroy the database schema.
    static void destroySchema() {
        destroyMySQLSchema();
    }
};

/// @brief Test fixture class for extended info tests.
class MySqlExtendedInfoTest :
    public isc::dhcp::test::GenericExtendedInfoTest<NakedMySqlLeaseMgr> { };

/// @brief Verifies that the lease manager can start.
TEST_F(MySqlExtendedInfoTest, startWithoutExtendedTables) {
    start(false);
}

/// @brief Verifies that the lease manager can start with MT.
TEST_F(MySqlExtendedInfoTest, startWithoutExtendedTablesMultiThreading) {
    MultiThreadingTest mt(true);
    start(false);
}

/// @brief Verifies that the lease manager can start with tables.
TEST_F(MySqlExtendedInfoTest, startWithExtendedTables) {
    start(true);
}

/// @brief Verifies that the lease manager can start with tables and MT.
TEST_F(MySqlExtendedInfoTest, startWithExtendedTablesMultiThreading) {
    MultiThreadingTest mt(true);
    start(true);
}

TEST_F(MySqlExtendedInfoTest, initLease4) {
    testInitLease4();
}

TEST_F(MySqlExtendedInfoTest, initLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testInitLease4();
}

TEST_F(MySqlExtendedInfoTest, getLeases4ByRelayId) {
    testGetLeases4ByRelayId();
}

TEST_F(MySqlExtendedInfoTest, getLeases4ByRelayIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRelayId();
}

TEST_F(MySqlExtendedInfoTest, getLeases4ByRemoteId) {
    testGetLeases4ByRemoteId();
}

TEST_F(MySqlExtendedInfoTest, getLeases4ByRemoteIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRemoteId();
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4None) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_NONE,
                             LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4Fix) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                             LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4Strict) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
                             LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4Pedantic) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
                             LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4_10) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                             LeasePageSize(10));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4_5) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                             LeasePageSize(5));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4_2) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                             LeasePageSize(2));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo4_1) {
    testUpgradeExtendedInfo4(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                             LeasePageSize(1));
}

TEST_F(MySqlExtendedInfoTest, initLease6) {
    testInitLease6();
}

TEST_F(MySqlExtendedInfoTest, initLease6MultiThreading) {
    MultiThreadingTest mt(true);
    testInitLease6();
}

TEST_F(MySqlExtendedInfoTest, enableTables) {
    testEnableTables();
}

TEST_F(MySqlExtendedInfoTest, enableTablesMultiThreading) {
    MultiThreadingTest mt(true);
    testEnableTables();
}

TEST_F(MySqlExtendedInfoTest, deleteCascade) {
    testDeleteCascade();
}

TEST_F(MySqlExtendedInfoTest, deleteCascadeMultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteCascade();
}

TEST_F(MySqlExtendedInfoTest, getLeases6ByRelayId) {
    testGetLeases6ByRelayId();
}

TEST_F(MySqlExtendedInfoTest, getLeases6ByRelayIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6ByRelayId();
}

TEST_F(MySqlExtendedInfoTest, getLeases6ByRemoteId) {
    testGetLeases6ByRemoteId();
}

TEST_F(MySqlExtendedInfoTest, getLeases6ByRemoteIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6ByRemoteId();
}

TEST_F(MySqlExtendedInfoTest, getLeases6ByLink) {
    testGetLeases6ByLink();
}

TEST_F(MySqlExtendedInfoTest, getLeases6ByLinkMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6ByLink();
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo6NoCheckDisabled) {
    testUpgradeExtendedInfo6(CfgConsistency::EXTENDED_INFO_CHECK_NONE,
                             false,
                             LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo6NoCheckEnabled) {
    testUpgradeExtendedInfo6(CfgConsistency::EXTENDED_INFO_CHECK_NONE,
                             true,
                             LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo6FixkDisabled) {
    testUpgradeExtendedInfo6(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                             false,
                             LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo6FixEnabled) {
    testUpgradeExtendedInfo6(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                             true,
                             LeasePageSize(100));
}

}  // namespace
