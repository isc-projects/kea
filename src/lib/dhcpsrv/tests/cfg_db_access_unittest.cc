// Copyright (C) 2016-2026 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/memfile_lease_mgr.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::util;

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
    ASSERT_EQ(3U, hal.size());
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
    ASSERT_EQ(2U, hal.size());
    EXPECT_EQ("type=foo", hal.front());
    EXPECT_EQ("type=bar", hal.back());
}

// Tests that lease manager can be created from a specified configuration.
TEST(CfgDbAccessTest, createLeaseMgrV4) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString("type=memfile persist=false universe=4"));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("memfile", lease_mgr.getType());
        Memfile_LeaseMgr& mgr = dynamic_cast<Memfile_LeaseMgr&>(lease_mgr);
        EXPECT_FALSE(mgr.persistLeases(Memfile_LeaseMgr::V4));
    });
}

// Tests that lease manager can be created from a specified configuration.
TEST(CfgDbAccessTest, createLeaseMgrV6) {
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString("type=memfile persist=false universe=6"));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("memfile", lease_mgr.getType());
        Memfile_LeaseMgr& mgr = dynamic_cast<Memfile_LeaseMgr&>(lease_mgr);
        EXPECT_FALSE(mgr.persistLeases(Memfile_LeaseMgr::V6));
    });
}

// Tests that lease manager can be created from a specified configuration using test mode.
TEST(CfgDbAccessTest, createLeaseMgrV4TestMode) {
    MtTestMode mt;
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString("type=memfile persist=true universe=4"));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("memfile", lease_mgr.getType());
        Memfile_LeaseMgr& mgr = dynamic_cast<Memfile_LeaseMgr&>(lease_mgr);
        EXPECT_FALSE(mgr.persistLeases(Memfile_LeaseMgr::V4));
    });

}

// Tests that lease manager can be created from a specified configuration using test mode.
TEST(CfgDbAccessTest, createLeaseMgrV6TestMode) {
    MtTestMode mt;
    CfgDbAccess cfg;
    ASSERT_NO_THROW(cfg.setLeaseDbAccessString("type=memfile persist=true universe=6"));
    ASSERT_NO_THROW(cfg.createManagers());

    ASSERT_NO_THROW({
        LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
        EXPECT_EQ("memfile", lease_mgr.getType());
        Memfile_LeaseMgr& mgr = dynamic_cast<Memfile_LeaseMgr&>(lease_mgr);
        EXPECT_FALSE(mgr.persistLeases(Memfile_LeaseMgr::V6));
    });
}

} // end of anonymous namespace
