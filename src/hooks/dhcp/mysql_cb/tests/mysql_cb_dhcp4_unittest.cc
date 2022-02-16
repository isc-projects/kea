// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <database/db_exceptions.h>
#include <database/server.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/testutils/generic_cb_dhcp4_unittest.h>
#include <dhcpsrv/testutils/generic_cb_recovery_unittest.h>
#include <dhcpsrv/testutils/mysql_generic_backend_unittest.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <mysql_cb_dhcp4.h>
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
using namespace isc::util;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace isc::test;
namespace ph = std::placeholders;

namespace {

/// @brief Test implementation of the MySQL configuration backend.
///
/// It exposes protected members of the @c MySqlConfigBackendDHCPv4.
class TestMySqlConfigBackendDHCPv4 : public MySqlConfigBackendDHCPv4 {
public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit TestMySqlConfigBackendDHCPv4(const DatabaseConnection::ParameterMap& parameters)
        : MySqlConfigBackendDHCPv4(parameters) {
    }

    using MySqlConfigBackendDHCPv4::base_impl_;
};

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv4.
class MySqlConfigBackendDHCPv4Test : public GenericConfigBackendDHCPv4Test {
public:
    /// @brief Constructor.
    MySqlConfigBackendDHCPv4Test() {}

    /// @brief Destructor.
    virtual ~MySqlConfigBackendDHCPv4Test() {}

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

    /// @brief Instantiates an instance of a MySQL DHCPv4 configuration
    /// back end.
    ///
    /// @params Connection parameters describing the back end to create.
    ///
    /// @return Pointer to the newly created back end instance.
    ConfigBackendDHCPv4Ptr backendFactory(db::DatabaseConnection::ParameterMap&
                                          params) {

        return (ConfigBackendDHCPv4Ptr(new TestMySqlConfigBackendDHCPv4(params)));
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
        auto p = boost::dynamic_pointer_cast<TestMySqlConfigBackendDHCPv4>(cbptr_);
        if (!p) {
            ADD_FAILURE() << "cbptr_ does not cast to TestMySqlConfigBackendDHCPv4";
            return (0);
        }

        // Reuse the existing connection of the backend.
        auto impl = boost::dynamic_pointer_cast<MySqlConfigBackendImpl>(p->base_impl_);
        auto& conn = impl->conn_;

        return (MySqlGenericBackendTest::countRows(conn, table));
    }
};

TEST_F(MySqlConfigBackendDHCPv4Test, getType) {
    getTypeTest("mysql");
}

TEST_F(MySqlConfigBackendDHCPv4Test, getHost) {
    getHostTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getPort) {
    getPortTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteServerTest) {
    createUpdateDeleteServerTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAndDeleteAllServersTest) {
    getAndDeleteAllServersTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteGlobalParameter4Test) {
    createUpdateDeleteGlobalParameter4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, globalParameters4WithServerTagsTest) {
    globalParameters4WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllGlobalParameters4Test) {
    getAllGlobalParameters4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedGlobalParameters4Test) {
    getModifiedGlobalParameters4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, nullKeyErrorTest) {
    nullKeyErrorTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateSubnet4SelectorsTest) {
    createUpdateSubnet4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4Test) {
    getSubnet4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4byIdSelectorsTest) {
    getSubnet4byIdSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4WithOptionalUnspecifiedTest) {
    getSubnet4WithOptionalUnspecifiedTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4SharedNetworkTest) {
    getSubnet4SharedNetworkTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4ByPrefixTest) {
    getSubnet4ByPrefixTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4byPrefixSelectorsTest) {
    getSubnet4byPrefixSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllSubnets4Test) {
    getAllSubnets4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllSubnets4SelectorsTest) {
    getAllSubnets4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllSubnets4WithServerTagsTest) {
    getAllSubnets4WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedSubnets4SelectorsTest) {
    getModifiedSubnets4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteSubnet4Test) {
    deleteSubnet4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteSubnet4ByIdSelectorsTest) {
    deleteSubnet4ByIdSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteSubnet4ByPrefixSelectorsTest) {
    deleteSubnet4ByPrefixSelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteAllSubnets4SelectorsTest) {
    deleteAllSubnets4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, unassignedSubnet4Test) {
    unassignedSubnet4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedSubnets4Test) {
    getModifiedSubnets4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, subnetLifetimeTest) {
    subnetLifetimeTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetworkSubnets4Test) {
    getSharedNetworkSubnets4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, subnetUpdatePoolsTest) {
    subnetUpdatePoolsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, subnetOptionsTest) {
    subnetOptionsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetwork4Test) {
    getSharedNetwork4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetwork4SelectorsTest) {
    getSharedNetwork4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateSharedNetwork4Test) {
    createUpdateSharedNetwork4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateSharedNetwork4SelectorsTest) {
    createUpdateSharedNetwork4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetwork4WithOptionalUnspecifiedTest) {
    getSharedNetwork4WithOptionalUnspecifiedTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteSharedNetworkSubnets4Test) {
    deleteSharedNetworkSubnets4Test();
}

/// @todo This test is disabled pending resolution of #2299.
TEST_F(MySqlConfigBackendDHCPv4Test, DISABLED_getAllSharedNetworks4Test) {
    getAllSharedNetworks4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllSharedNetworks4SelectorsTest) {
    getAllSharedNetworks4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllSharedNetworks4WithServerTagsTest) {
    getAllSharedNetworks4WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedSharedNetworks4Test) {
    getModifiedSharedNetworks4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedSharedNetworks4SelectorsTest) {
    getModifiedSharedNetworks4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteSharedNetwork4Test) {
    deleteSharedNetwork4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteSharedNetwork4SelectorsTest) {
    deleteSharedNetwork4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteAllSharedNetworks4SelectorsTest) {
    deleteAllSharedNetworks4SelectorsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, unassignedSharedNetworkTest) {
    unassignedSharedNetworkTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, sharedNetworkLifetimeTest) {
    sharedNetworkLifetimeTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, sharedNetworkOptionsTest) {
    sharedNetworkOptionsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getOptionDef4Test) {
    getOptionDef4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, optionDefs4WithServerTagsTest) {
    optionDefs4WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllOptionDefs4Test) {
    getAllOptionDefs4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedOptionDefs4Test) {
    getModifiedOptionDefs4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteOption4Test) {
    createUpdateDeleteOption4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, globalOptions4WithServerTagsTest) {
    globalOptions4WithServerTagsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getAllOptions4Test) {
    getAllOptions4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedOptions4Test) {
    getModifiedOptions4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteSubnetOption4Test) {
    createUpdateDeleteSubnetOption4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeletePoolOption4Test) {
    createUpdateDeletePoolOption4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteSharedNetworkOption4Test) {
    createUpdateDeleteSharedNetworkOption4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, subnetOptionIdOrderTest) {
    subnetOptionIdOrderTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, sharedNetworkOptionIdOrderTest) {
    sharedNetworkOptionIdOrderTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, setAndGetAllClientClasses4Test) {
    setAndGetAllClientClasses4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getClientClass4Test) {
    getClientClass4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateClientClass4OptionsTest) {
    createUpdateClientClass4OptionsTest();
}

TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedClientClasses4Test) {
    getModifiedClientClasses4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteClientClass4Test) {
    deleteClientClass4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, deleteAllClientClasses4Test) {
    deleteAllClientClasses4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, clientClassDependencies4Test) {
    clientClassDependencies4Test();
}

TEST_F(MySqlConfigBackendDHCPv4Test, multipleAuditEntriesTest) {
    multipleAuditEntriesTest();
}

/// @brief Test fixture for verifying database connection loss-recovery
/// behavior.
class MySqlConfigBackendDHCPv4DbLostCallbackTest : public GenericConfigBackendDbLostCallbackTest {
public:
    /// @brief Constructor
    MySqlConfigBackendDHCPv4DbLostCallbackTest() {};

    /// @brief Destructor
    virtual ~MySqlConfigBackendDHCPv4DbLostCallbackTest() {};

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
        isc::dhcp::MySqlConfigBackendDHCPv4::registerBackendType();
    }

    /// @brief Unregisters MySQL as a CB backend type.
    virtual void unregisterBackendType() {
        isc::dhcp::MySqlConfigBackendDHCPv4::unregisterBackendType();
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
    /// connetion parameters.
    virtual void addBackend(const std::string& access) {
        ConfigBackendDHCPv4Mgr::instance().addBackend(access);
    }

    /// @brief Fetches a collection of all the servers currently in
    /// the CB database.  This function is used to check the operability
    /// of the CB backend.
    ServerCollection getAllServers() {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->getAllServers4(BackendSelector()));
    }
};

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testNoCallbackOnOpenFailure) {
    MultiThreadingTest mt(false);
    testNoCallbackOnOpenFailure();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testNoCallbackOnOpenFailureMultiThreading) {
    MultiThreadingTest mt(true);
    testNoCallbackOnOpenFailure();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredCallback();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredCallback();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedCallback();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedCallback();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedAfterTimeoutCallback();
}

TEST_F(MySqlConfigBackendDHCPv4DbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedAfterTimeoutCallback();
}

}
