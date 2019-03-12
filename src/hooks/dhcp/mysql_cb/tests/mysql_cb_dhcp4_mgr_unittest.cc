// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/stamped_value.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <mysql_cb_dhcp4.h>
#include <mysql/testutils/mysql_schema.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::db;
using namespace isc::db::test;

namespace {

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv4Mgr.
class MySqlConfigBackendDHCPv4MgrTest : public GenericBackendTest {
public:
    /// @brief Constructor.
    MySqlConfigBackendDHCPv4MgrTest() {
        // Recreate a fresh mgr.
        ConfigBackendDHCPv4Mgr::create();

        // Ensure we have the proper schema with no transient data.
        createMySQLSchema();
    }

    /// @brief Destructor.
    virtual ~MySqlConfigBackendDHCPv4MgrTest() {
        // Destroy the mgr.
        ConfigBackendDHCPv4Mgr::destroy();

        // If data wipe enabled, delete transient data otherwise destroy the schema.
        destroyMySQLSchema();
    }
};

// This test verifies that MySQL backend can be registered with and
// unregistered from the Config Backend Manager.
TEST_F(MySqlConfigBackendDHCPv4MgrTest, factoryRegistration) {

    // Get the mgr singleton.
    ConfigBackendDHCPv4Mgr& mgr = ConfigBackendDHCPv4Mgr::instance();

    // With no factory registered, attempting to add a MySQL db should fail.
    ASSERT_THROW(mgr.addBackend(validMySQLConnectionString()), InvalidType);

    // Now we'll register the MySQL factory.
    ASSERT_NO_THROW(MySqlConfigBackendDHCPv4::registerBackendType());

    // With the factory registered, attempting to add a MySQL db should succeed.
    ASSERT_NO_THROW(mgr.addBackend(validMySQLConnectionString()));

    // Create a MySQL backend selector for convenience.
    BackendSelector mysql(BackendSelector::Type::MYSQL);

    // Should be able to create a global parameter.
    StampedValuePtr server_tag = StampedValue::create("server-tag", "whale");
    ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter4(mysql, ServerSelector::ALL(),
                                                                server_tag));
    // Verify parameter can be fetched.
    server_tag.reset();
    ASSERT_NO_THROW(server_tag = mgr.getPool()->getGlobalParameter4(mysql, ServerSelector::ALL(),
                                                                    "server-tag"));
    ASSERT_TRUE(server_tag);
    EXPECT_EQ("server-tag", server_tag->getName());
    EXPECT_EQ("whale", server_tag->getValue());

    // Now we'll unregister MySQL.
    ASSERT_NO_THROW(MySqlConfigBackendDHCPv4::unregisterBackendType());

    // With no factory registered, attempting to add a MySQL db should fail.
    ASSERT_THROW(mgr.addBackend(validMySQLConnectionString()), InvalidType);

    // Attempting to read the global parameter should fail.
    ASSERT_THROW(mgr.getPool()->getGlobalParameter4(mysql, ServerSelector::ALL(), "server-tag"),
                 NoSuchDatabase);
}

}
