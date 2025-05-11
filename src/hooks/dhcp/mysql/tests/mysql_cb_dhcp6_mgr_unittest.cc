// Copyright (C) 2019-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/stamped_value.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <mysql_cb_dhcp6.h>
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

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv6Mgr.
class MySqlConfigBackendDHCPv6MgrTest : public GenericBackendTest {
public:
    /// @brief Constructor.
    MySqlConfigBackendDHCPv6MgrTest() {
        // Recreate a fresh mgr.
        ConfigBackendDHCPv6Mgr::create();

        // Ensure we have the proper schema with no transient data.
        createMySQLSchema();
    }

    /// @brief Destructor.
    virtual ~MySqlConfigBackendDHCPv6MgrTest() {
        // Destroy the mgr.
        ConfigBackendDHCPv6Mgr::destroy();

        // If data wipe enabled, delete transient data otherwise destroy the schema.
        destroyMySQLSchema();
    }
};

// This test verifies that MySQL backend can be registered with and
// unregistered from the Config Backend Manager.
TEST_F(MySqlConfigBackendDHCPv6MgrTest, factoryRegistration) {

    // Get the mgr singleton.
    ConfigBackendDHCPv6Mgr& mgr = ConfigBackendDHCPv6Mgr::instance();

    // With no factory registered, attempting to add a MySQL db should fail.
    ASSERT_THROW(mgr.addBackend(validMySQLConnectionString()), InvalidType);

    // Now we'll register the MySQL factory.
    ASSERT_NO_THROW(MySqlConfigBackendDHCPv6::registerBackendType());

    // With the factory registered, attempting to add a MySQL db should succeed.
    ASSERT_NO_THROW(mgr.addBackend(validMySQLConnectionString()));

    // Create a MySQL backend selector for convenience.
    BackendSelector mysql(BackendSelector::Type::MYSQL);

    // Should be able to create a global parameter.
    StampedValuePtr server_tag = StampedValue::create("server-tag", "whale");
    ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter6(mysql, ServerSelector::ALL(),
                                                                server_tag));
    // Verify parameter can be fetched.
    server_tag.reset();
    ASSERT_NO_THROW(server_tag = mgr.getPool()->getGlobalParameter6(mysql, ServerSelector::ALL(),
                                                                    "server-tag"));
    ASSERT_TRUE(server_tag);
    EXPECT_EQ("server-tag", server_tag->getName());
    EXPECT_EQ("whale", server_tag->getValue());

    // Now we'll unregister MySQL.
    ASSERT_NO_THROW(MySqlConfigBackendDHCPv6::unregisterBackendType());

    // With no factory registered, attempting to add a MySQL db should fail.
    ASSERT_THROW(mgr.addBackend(validMySQLConnectionString()), InvalidType);

    // Attempting to read the global parameter should fail.
    ASSERT_THROW(mgr.getPool()->getGlobalParameter6(mysql, ServerSelector::ALL(), "server-tag"),
                 NoSuchDatabase);
}

}
