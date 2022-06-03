// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <database/db_exceptions.h>
#include <database/server.h>
#include <database/testutils/schema.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/testutils/generic_cb_dhcp6_unittest.h>
#include <dhcpsrv/testutils/generic_cb_recovery_unittest.h>
#include <dhcpsrv/testutils/mysql_generic_backend_unittest.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <mysql_cb_dhcp6.h>
#include <mysql/testutils/mysql_schema.h>
#include <testutils/multi_threading_utils.h>
#include <testutils/gtest_utils.h>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <mysql.h>
#include <map>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace isc::test;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief Test implementation of the MySQL configuration backend.
///
/// It exposes protected members of the @c MySqlConfigBackendDHCPv6.
class TestMySqlConfigBackendDHCPv6 : public MySqlConfigBackendDHCPv6 {
public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit TestMySqlConfigBackendDHCPv6(const DatabaseConnection::ParameterMap& parameters)
        : MySqlConfigBackendDHCPv6(parameters) {
    }

    using MySqlConfigBackendDHCPv6::base_impl_;
};

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv6.
class MySqlConfigBackendDHCPv6Test : public GenericConfigBackendDHCPv6Test {
public:
    /// @brief Constructor.
    MySqlConfigBackendDHCPv6Test() {}

    /// @brief Destructor.
    virtual ~MySqlConfigBackendDHCPv6Test() {}

    /// @brief Creates the MySQL back end schema
    virtual void createSchema() {
        createMySQLSchema();
    }

    /// @brief Destroys the MySQL back end schema
    virtual void destroySchema() {
        destroyMySQLSchema();
    }

    /// @brief Returns a valid MySQL back end specific connection
    /// string
    std::string validConnectionString() {
        return (validMySQLConnectionString());
    }

    /// @brief Instantiates an instance of a MySQL DHCPv6 configuration
    /// back end.
    ///
    /// @params Connection parameters describing the back end to create.
    ///
    /// @return Pointer to the newly created back end instance.
    ConfigBackendDHCPv6Ptr backendFactory(db::DatabaseConnection::ParameterMap&
                                          params) {

        return (ConfigBackendDHCPv6Ptr(new TestMySqlConfigBackendDHCPv6(params)));
    }

    /// @brief Counts rows in a selected table in MySQL database.
    ///
    /// This method can be used to verify that some configuration elements were
    /// deleted from a selected table as a result of cascade delete or a trigger.
    /// For example, deleting a subnet should trigger deletion of its address
    /// pools and options. By counting the rows on each table we can determine
    /// whether the deletion took place on all tables for which it was expected.
    ///
    /// @param table Table name.
    /// @return Number of rows in the specified table.
    size_t countRows(const std::string& table) const {
        auto p = boost::dynamic_pointer_cast<TestMySqlConfigBackendDHCPv6>(cbptr_);
        if (!p) {
            ADD_FAILURE() << "cbptr_ does not cast to TestMySqlConfigBackendDHCPv6";
            return (0);
        }

        // Reuse the existing connection of the backend.
        auto impl = boost::dynamic_pointer_cast<MySqlConfigBackendImpl>(p->base_impl_);
        auto& conn = impl->conn_;

        return (MySqlGenericBackendTest::countRows(conn, table));
    }
};

TEST_F(MySqlConfigBackendDHCPv6Test, getType) {
    getTypeTest("mysql");
}

TEST_F(MySqlConfigBackendDHCPv6Test, getHost) {
    getHostTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getPort) {
    getPortTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteServerTest) {
    createUpdateDeleteServerTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAndDeleteAllServersTest) {
    getAndDeleteAllServersTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteGlobalParameter6Test) {
    createUpdateDeleteGlobalParameter6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, globalParameters6WithServerTagsTest) {
    globalParameters6WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllGlobalParameters6Test) {
    getAllGlobalParameters6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedGlobalParameters6Test) {
    getModifiedGlobalParameters6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, nullKeyErrorTest) {
    nullKeyErrorTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateSubnet6SelectorsTest) {
    createUpdateSubnet6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6Test) {
    getSubnet6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6byIdSelectorsTest) {
    getSubnet6byIdSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6WithOptionalUnspecifiedTest) {
    getSubnet6WithOptionalUnspecifiedTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6SharedNetworkTest) {
    getSubnet6SharedNetworkTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6ByPrefixTest) {
    getSubnet6ByPrefixTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6byPrefixSelectorsTest) {
    getSubnet6byPrefixSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllSubnets6Test) {
    getAllSubnets6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllSubnets6SelectorsTest) {
    getAllSubnets6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllSubnets6WithServerTagsTest) {
    getAllSubnets6WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedSubnets6SelectorsTest) {
    getModifiedSubnets6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteSubnet6Test) {
    deleteSubnet6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteSubnet6ByIdSelectorsTest) {
    deleteSubnet6ByIdSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteSubnet6ByPrefixSelectorsTest) {
    deleteSubnet6ByPrefixSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteAllSubnets6SelectorsTest) {
    deleteAllSubnets6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, unassignedSubnet6Test) {
    unassignedSubnet6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedSubnets6Test) {
    getModifiedSubnets6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, subnetLifetimeTest) {
    subnetLifetimeTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSharedNetworkSubnets6Test) {
    getSharedNetworkSubnets6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, subnetUpdatePoolsTest) {
    subnetUpdatePoolsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, subnetOptionsTest) {
    subnetOptionsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSharedNetwork6Test) {
    getSharedNetwork6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSharedNetwork6SelectorsTest) {
    getSharedNetwork6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateSharedNetwork6Test) {
    createUpdateSharedNetwork6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateSharedNetwork6SelectorsTest) {
    createUpdateSharedNetwork6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getSharedNetwork6WithOptionalUnspecifiedTest) {
    getSharedNetwork6WithOptionalUnspecifiedTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteSharedNetworkSubnets6Test) {
    deleteSharedNetworkSubnets6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllSharedNetworks6Test) {
    getAllSharedNetworks6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllSharedNetworks6SelectorsTest) {
    getAllSharedNetworks6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllSharedNetworks6WithServerTagsTest) {
    getAllSharedNetworks6WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedSharedNetworks6Test) {
    getModifiedSharedNetworks6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedSharedNetworks6SelectorsTest) {
    getModifiedSharedNetworks6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteSharedNetwork6Test) {
    deleteSharedNetwork6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteSharedNetwork6SelectorsTest) {
    deleteSharedNetwork6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteAllSharedNetworks6SelectorsTest) {
    deleteAllSharedNetworks6SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, unassignedSharedNetworkTest) {
    unassignedSharedNetworkTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, sharedNetworkLifetimeTest) {
    sharedNetworkLifetimeTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, sharedNetworkOptionsTest) {
    sharedNetworkOptionsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getOptionDef6Test) {
    getOptionDef6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, optionDefs6WithServerTagsTest) {
    optionDefs6WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllOptionDefs6Test) {
    getAllOptionDefs6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedOptionDefs6Test) {
    getModifiedOptionDefs6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteOption6Test) {
    createUpdateDeleteOption6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, globalOptions6WithServerTagsTest) {
    globalOptions6WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getAllOptions6Test) {
    getAllOptions6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedOptions6Test) {
    getModifiedOptions6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteSubnetOption6Test) {
    createUpdateDeleteSubnetOption6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeletePoolOption6Test) {
    createUpdateDeletePoolOption6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeletePdPoolOption6Test) {
    createUpdateDeletePdPoolOption6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteSharedNetworkOption6Test) {
    createUpdateDeleteSharedNetworkOption6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, subnetOptionIdOrderTest) {
    subnetOptionIdOrderTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, sharedNetworkOptionIdOrderTest) {
    sharedNetworkOptionIdOrderTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, setAndGetAllClientClasses6Test) {
    setAndGetAllClientClasses6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getClientClass6Test) {
    getClientClass6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateClientClass6OptionsTest) {
    createUpdateClientClass6OptionsTest();
}

TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedClientClasses6Test) {
    getModifiedClientClasses6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteClientClass6Test) {
    deleteClientClass6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, deleteAllClientClasses6Test) {
    deleteAllClientClasses6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, clientClassDependencies6Test) {
    clientClassDependencies6Test();
}

TEST_F(MySqlConfigBackendDHCPv6Test, multipleAuditEntriesTest) {
    multipleAuditEntriesTest();
}

/// @brief Test fixture for verifying database connection loss-recovery
/// behavior.
class MySqlConfigBackendDHCPv6DbLostCallbackTest : public GenericConfigBackendDbLostCallbackTest {
public:
    /// @brief Constructor
    MySqlConfigBackendDHCPv6DbLostCallbackTest() {};

    /// @brief Destructor
    virtual ~MySqlConfigBackendDHCPv6DbLostCallbackTest() {};

    /// @brief Creates the MySQL CB schema.
    virtual void createSchema() {
        createMySQLSchema();
    }

    /// @brief Destroys the MySQL CB schema.
    virtual void destroySchema() {
        destroyMySQLSchema();
    }

    /// @brief Method which returns a valid back end specific connection
    /// string
    virtual std::string validConnectionString() {
        return (validMySQLConnectionString());
    }

    /// @brief Method which returns an invalid back end specific connection
    /// string.
    virtual std::string invalidConnectionString() {
        return (connectionString(MYSQL_VALID_TYPE, INVALID_NAME, VALID_HOST,
                                 VALID_USER, VALID_PASSWORD));
    }

    /// @brief Registers MySQL as a CB backend type.
    virtual void registerBackendType() {
        isc::dhcp::MySqlConfigBackendDHCPv6::registerBackendType();
    }

    /// @brief Unregisters MySQL as a CB backend type.
    virtual void unregisterBackendType() {
        isc::dhcp::MySqlConfigBackendDHCPv6::unregisterBackendType();
    }

    /// @brief Sets the IOService instance in the CB implementation object.
    ///
    /// @param io_service pointer to the IOService instance to use. It may be
    /// an empty pointer.
    virtual void setConfigBackendImplIOService(isc::asiolink::IOServicePtr io_service) {
        isc::dhcp::MySqlConfigBackendImpl::setIOService(io_service);
    }

    /// @brief  Attempts to add a backend instance to the CB manager.
    ///
    /// @param access Connection access string containing the database
    /// connection parameters.
    virtual void addBackend(const std::string& access) {
        ConfigBackendDHCPv6Mgr::instance().addBackend(access);
    }

    /// @brief Fetches a collection of all the servers currently in
    /// the CB database.  This function is used to check the operability
    /// of the CB backend.
    ServerCollection getAllServers() {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->getAllServers6(BackendSelector()));
    }
};

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testNoCallbackOnOpenFailure) {
    MultiThreadingTest mt(false);
    testNoCallbackOnOpenFailure();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testNoCallbackOnOpenFailureMultiThreading) {
    MultiThreadingTest mt(true);
    testNoCallbackOnOpenFailure();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredCallback();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredCallback();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedCallback();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedCallback();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedAfterTimeoutCallback();
}

TEST_F(MySqlConfigBackendDHCPv6DbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedAfterTimeoutCallback();
}

}
