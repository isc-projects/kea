// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/tests/mysql_schema.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

// Test default values of the lease and host database access strings.
TEST(CfgDbAccessTest, defaults) {
    CfgDbAccess cfg;
    EXPECT_EQ("type=memfile", cfg.getLeaseDbAccessString());
    EXPECT_TRUE(cfg.getHostDbAccessString().empty());
}

// This test verifies that it is possible to set the lease database
// string.
TEST(CfgDbAccessTest, setLeaseDbAccessString) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString("type=mysql"));
    EXPECT_EQ("type=mysql", cfg.getLeaseDbAccessString());

    // Append additional parameter.
    ASSERT_NO_THROW(cfg.setAppendedParameters("universe=4"));
    EXPECT_EQ("type=mysql universe=4", cfg.getLeaseDbAccessString());

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

    // Append additional parameter.
    ASSERT_NO_THROW(cfg.setAppendedParameters("universe=4"));
    EXPECT_EQ("type=mysql universe=4", cfg.getHostDbAccessString());

    // If access string is empty, no parameters will be appended.
    ASSERT_NO_THROW(cfg.setHostDbAccessString(""));
    EXPECT_TRUE(cfg.getHostDbAccessString().empty());
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
        // Ensure schema is the correct one.
        destroyMySQLSchema();
        createMySQLSchema();
    }

    /// @brief Destructor.
    virtual ~CfgMySQLDbAccessTest() {
        destroyMySQLSchema();
    }
};


// Tests that MySQL lease manager and host data source can be created from a
// specified configuration.
TEST_F(CfgMySQLDbAccessTest, createManagers) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString(validMySQLConnectionString()));
    ASSERT_NO_THROW(cfg.setHostDbAccessString(validMySQLConnectionString()));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("mysql", lease_mgr.getType());
    });

    ASSERT_NO_THROW({
        HostDataSourcePtr& host_data_source =
            HostDataSourceFactory::getHostDataSourcePtr();
        EXPECT_EQ("mysql", host_data_source->getType());
    });
}

#endif

} // end of anonymous namespace
