// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <database/dbaccess_parser.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

#if defined HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#endif

#if defined HAVE_PGSQL
#include <pgsql/testutils/pgsql_schema.h>
#endif

using namespace isc;
using namespace isc::dhcp;
using namespace isc::test;

namespace {

// Test default values of the lease and host database access strings.
TEST(CfgDbAccessTest, defaults) {
    CfgDbAccess cfg;
    EXPECT_EQ("type=memfile", cfg.getLeaseDbAccessString());
    std::string expected = "{ \"type\": \"memfile\" }";
    runToElementTest<CfgLeaseDbAccess>(expected, CfgLeaseDbAccess(cfg));

    EXPECT_TRUE(cfg.getHostDbAccessString().empty());
    runToElementTest<CfgHostDbAccess>("[ ]", CfgHostDbAccess(cfg));
}

// This test verifies that it is possible to set the lease database
// string.
TEST(CfgDbAccessTest, setLeaseDbAccessString) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString("type=mysql"));
    EXPECT_EQ("type=mysql", cfg.getLeaseDbAccessString());

    // Check unparse
    std::string expected = "{ \"type\": \"mysql\" }";
    runToElementTest<CfgLeaseDbAccess>(expected, CfgLeaseDbAccess(cfg));

    // Append additional parameter.
    ASSERT_NO_THROW(cfg.setAppendedParameters("universe=4"));
    EXPECT_EQ("type=mysql universe=4", cfg.getLeaseDbAccessString());

    // Additional parameters are not in lease_db_access_
    runToElementTest<CfgLeaseDbAccess>(expected, CfgLeaseDbAccess(cfg));

    // If access string is empty, no parameters will be appended.
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString(""));
    EXPECT_TRUE(cfg.getLeaseDbAccessString().empty());
}


// This test verifies that it is possible to set the host database
// string.
TEST(CfgDbAccessTest, setHostDbAccessString) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setHostDbAccessString("type=mysql"));
    EXPECT_EQ("type=mysql", cfg.getHostDbAccessString());

    // Check unparse
    std::string expected = "[ { \"type\": \"mysql\" } ]";
    runToElementTest<CfgHostDbAccess>(expected, CfgHostDbAccess(cfg));

    // Append additional parameter.
    ASSERT_NO_THROW(cfg.setAppendedParameters("universe=4"));
    EXPECT_EQ("type=mysql universe=4", cfg.getHostDbAccessString());

    // Additional parameters are not in host_db_access_
    runToElementTest<CfgHostDbAccess>(expected, CfgHostDbAccess(cfg));

    // If access string is empty, no parameters will be appended.
    CfgDbAccess cfg1;
    ASSERT_NO_THROW(cfg1.setHostDbAccessString(""));
    EXPECT_TRUE(cfg1.getHostDbAccessString().empty());
}

// This test verifies that it is possible to set multiple host
// database string.
TEST(CfgDbAccessTest, pushHostDbAccessString) {
    // Push a string.
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setHostDbAccessString("type=foo"));

    // Push another in front.
    ASSERT_NO_THROW(cfg.setHostDbAccessString("type=mysql", true));
    EXPECT_EQ("type=mysql", cfg.getHostDbAccessString());

    // Push a third string.
    ASSERT_NO_THROW(cfg.setHostDbAccessString("type=bar"));

    // Check unparse
    std::string expected = "[ { \"type\": \"mysql\" }, ";
    expected += "{ \"type\": \"foo\" }, { \"type\": \"bar\" } ]";
    runToElementTest<CfgHostDbAccess>(expected, CfgHostDbAccess(cfg));

    // Check access strings
    std::list<std::string> hal = cfg.getHostDbAccessStringList();
    ASSERT_EQ(3, hal.size());
    std::list<std::string>::const_iterator it = hal.cbegin();
    ASSERT_NE(hal.cend(), it);
    EXPECT_EQ("type=mysql", *it);
    ASSERT_NE(hal.cend(), ++it);
    EXPECT_EQ("type=foo", *it);
    ASSERT_NE(hal.cend(), ++it);
    EXPECT_EQ("type=bar", *it);

    // Build a similar list with the first string empty so it will be ignored.
    CfgDbAccess cfg1;
    ASSERT_NO_THROW(cfg1.setHostDbAccessString(""));
    ASSERT_NO_THROW(cfg1.setHostDbAccessString("type=foo"));
    ASSERT_NO_THROW(cfg1.setHostDbAccessString("type=bar"));
    expected = "[ { \"type\": \"foo\" }, { \"type\": \"bar\" } ]";
    runToElementTest<CfgHostDbAccess>(expected, CfgHostDbAccess(cfg1));
    hal = cfg1.getHostDbAccessStringList();
    ASSERT_EQ(2, hal.size());
    EXPECT_EQ("type=foo", hal.front());
    EXPECT_EQ("type=bar", hal.back());
}

// Tests that lease manager can be created from a specified configuration.
TEST(CfgDbAccessTest, createLeaseMgr) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString("type=memfile persist=false universe=4"));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("memfile",lease_mgr.getType());
    });
}

// The following tests require MySQL enabled.
#if defined HAVE_MYSQL

/// @brief Test fixture class for testing @ref CfgDbAccessTest using MySQL
/// backend.
class CfgMySQLDbAccessTest : public ::testing::Test {
public:

    /// @brief Constructor.
    CfgMySQLDbAccessTest() {
        // Ensure we have the proper schema with no transient data.
        db::test::createMySQLSchema();
    }

    /// @brief Destructor.
    virtual ~CfgMySQLDbAccessTest() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        db::test::destroyMySQLSchema();
        LeaseMgrFactory::destroy();
    }
};


// Tests that MySQL lease manager and host data source can be created from a
// specified configuration.
TEST_F(CfgMySQLDbAccessTest, createManagers) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString(db::test::validMySQLConnectionString()));
    ASSERT_NO_THROW(cfg.setHostDbAccessString(db::test::validMySQLConnectionString()));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("mysql", lease_mgr.getType());
    });

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("mysql", host_data_source->getType());
    });

    // Because of the lazy initialization of the HostMgr instance, it is
    // possible that the first call to the instance() function tosses
    // existing connection to the database created by the call to
    // createManagers(). Let's make sure that this doesn't happen.
    ASSERT_NO_THROW(HostMgr::instance());

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("mysql", host_data_source->getType());
    });

    EXPECT_TRUE(HostMgr::instance().getIPReservationsUnique());
}

// Tests that the createManagers function utilizes the setting in the
// CfgDbAccess class which controls whether the IP reservations must
// be unique or can be non-unique.
TEST_F(CfgMySQLDbAccessTest, createManagersIPResrvUnique) {
    CfgDbAccess cfg;

    cfg.setIPReservationsUnique(false);

    ASSERT_NO_THROW(cfg.setLeaseDbAccessString(db::test::validMySQLConnectionString()));
    ASSERT_NO_THROW(cfg.setHostDbAccessString(db::test::validMySQLConnectionString()));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("mysql", host_data_source->getType());
    });

    // Because of the lazy initialization of the HostMgr instance, it is
    // possible that the first call to the instance() function tosses
    // existing connection to the database created by the call to
    // createManagers(). Let's make sure that this doesn't happen.
    ASSERT_NO_THROW(HostMgr::instance());

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("mysql", host_data_source->getType());
    });

    EXPECT_FALSE(HostMgr::instance().getIPReservationsUnique());
}

#endif

// The following tests require PgSQL enabled.
#if defined HAVE_PGSQL

/// @brief Test fixture class for testing @ref CfgDbAccessTest using PgSQL
/// backend.
class CfgPgSQLDbAccessTest : public ::testing::Test {
public:

    /// @brief Constructor.
    CfgPgSQLDbAccessTest() {
        // Ensure we have the proper schema with no transient data.
        db::test::createPgSQLSchema();
    }

    /// @brief Destructor.
    virtual ~CfgPgSQLDbAccessTest() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        db::test::destroyPgSQLSchema();
        LeaseMgrFactory::destroy();
    }
};


// Tests that PgSQL lease manager and host data source can be created from a
// specified configuration.
TEST_F(CfgPgSQLDbAccessTest, createManagers) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString(db::test::validPgSQLConnectionString()));
    ASSERT_NO_THROW(cfg.setHostDbAccessString(db::test::validPgSQLConnectionString()));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("postgresql", lease_mgr.getType());
    });

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("postgresql", host_data_source->getType());
    });

    // Because of the lazy initialization of the HostMgr instance, it is
    // possible that the first call to the instance() function tosses
    // existing connection to the database created by the call to
    // createManagers(). Let's make sure that this doesn't happen.
    ASSERT_NO_THROW(HostMgr::instance());

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("postgresql", host_data_source->getType());
    });

    EXPECT_TRUE(HostMgr::instance().getIPReservationsUnique());
}

// Tests that the createManagers function utilizes the setting in the
// CfgDbAccess class which controls whether the IP reservations must
// be unique or can be non-unique.
TEST_F(CfgPgSQLDbAccessTest, createManagersIPResrvUnique) {
    CfgDbAccess cfg;

    cfg.setIPReservationsUnique(false);

    ASSERT_NO_THROW(cfg.setLeaseDbAccessString(db::test::validPgSQLConnectionString()));
    ASSERT_NO_THROW(cfg.setHostDbAccessString(db::test::validPgSQLConnectionString()));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("postgresql", host_data_source->getType());
    });

    // Because of the lazy initialization of the HostMgr instance, it is
    // possible that the first call to the instance() function tosses
    // existing connection to the database created by the call to
    // createManagers(). Let's make sure that this doesn't happen.
    ASSERT_NO_THROW(HostMgr::instance());

    ASSERT_NO_THROW({
        const HostDataSourcePtr& host_data_source =
            HostMgr::instance().getHostDataSource();
        ASSERT_TRUE(host_data_source);
        EXPECT_EQ("postgresql", host_data_source->getType());
    });

    EXPECT_FALSE(HostMgr::instance().getIPReservationsUnique());
}

#endif

} // end of anonymous namespace
