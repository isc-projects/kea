// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/stamped_value.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <pgsql_cb_dhcp6.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::db;
using namespace isc::db::test;

namespace {

/// @brief Test fixture class for @c PgSqlConfigBackendDHCPv6Mgr.
class PgSqlConfigBackendDHCPv6MgrTest : public GenericBackendTest {
public:
    /// @brief Constructor.
    PgSqlConfigBackendDHCPv6MgrTest() {
        // Recreate a fresh mgr.
        ConfigBackendDHCPv6Mgr::create();

        // Ensure we have the proper schema with no transient data.
        createPgSQLSchema();
    }

    /// @brief Destructor.
    virtual ~PgSqlConfigBackendDHCPv6MgrTest() {
        // Destroy the mgr.
        ConfigBackendDHCPv6Mgr::destroy();

        // If data wipe enabled, delete transient data otherwise destroy the schema.
        destroyPgSQLSchema();
    }
};

// This test verifies that PgSQL backend can be registered with and
// unregistered from the Config Backend Manager.
TEST_F(PgSqlConfigBackendDHCPv6MgrTest, factoryRegistration) {

    // Get the mgr singleton.
    ConfigBackendDHCPv6Mgr& mgr = ConfigBackendDHCPv6Mgr::instance();

    // With no factory registered, attempting to add a PgSQL db should fail.
    ASSERT_THROW(mgr.addBackend(validPgSQLConnectionString()), InvalidType);

    // Now we'll register the PgSQL factory.
    ASSERT_NO_THROW(PgSqlConfigBackendDHCPv6::registerBackendType());

    // With the factory registered, attempting to add a PgSQL db should succeed.
    ASSERT_NO_THROW(mgr.addBackend(validPgSQLConnectionString()));

    // Create a PgSQL backend selector for convenience.
    BackendSelector pgsql(BackendSelector::Type::POSTGRESQL);

    // Should be able to create a global parameter.
    StampedValuePtr server_tag = StampedValue::create("server-tag", "whale");
    ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter6(pgsql, ServerSelector::ALL(),
                                                                server_tag));
    // Verify parameter can be fetched.
    server_tag.reset();
    ASSERT_NO_THROW(server_tag = mgr.getPool()->getGlobalParameter6(pgsql, ServerSelector::ALL(),
                                                                    "server-tag"));
    ASSERT_TRUE(server_tag);
    EXPECT_EQ("server-tag", server_tag->getName());
    EXPECT_EQ("whale", server_tag->getValue());

    // Now we'll unregister PgSQL.
    ASSERT_NO_THROW(PgSqlConfigBackendDHCPv6::unregisterBackendType());

    // With no factory registered, attempting to add a PgSQL db should fail.
    ASSERT_THROW(mgr.addBackend(validPgSQLConnectionString()), InvalidType);

    // Attempting to read the global parameter should fail.
    ASSERT_THROW(mgr.getPool()->getGlobalParameter6(pgsql, ServerSelector::ALL(), "server-tag"),
                 NoSuchDatabase);
}

}
