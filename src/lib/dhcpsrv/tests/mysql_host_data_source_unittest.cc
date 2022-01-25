// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/mysql_host_data_source.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <mysql/mysql_connection.h>
#include <mysql/testutils/mysql_schema.h>
#include <testutils/multi_threading_utils.h>
#include <util/multi_threading_mgr.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::data;
using namespace isc::test;
using namespace isc::util;
using namespace std;

namespace {

class MySqlHostDataSourceTest : public GenericHostDataSourceTest {
public:
    /// @brief Clears the database and opens connection to it.
    void initializeTest() {
        // Ensure we have the proper schema with no transient data.
        createMySQLSchema();

        // Connect to the database
        try {
            HostMgr::create();
            HostMgr::addBackend(validMySQLConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        hdsptr_ = HostMgr::instance().getHostDataSource();
        hdsptr_->setIPReservationsUnique(true);

        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destroys the HDS and the schema.
    void destroyTest() {
        try {
            hdsptr_->rollback();
        } catch (...) {
            // Rollback may fail if backend is in read only mode. That's ok.
        }
        HostMgr::delAllBackends();
        hdsptr_.reset();
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroyMySQLSchema();
    }

    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    MySqlHostDataSourceTest() {
        initializeTest();
    }

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of hdsptr_ will close
    /// the database.  Then reopen it and delete everything created by the test.
    virtual ~MySqlHostDataSourceTest() {
        destroyTest();
    }

    /// @brief Reopen the database
    ///
    /// Closes the database and re-open it.  Anything committed should be
    /// visible.
    ///
    /// Parameter is ignored for MySQL backend as the v4 and v6 hosts share
    /// the same database.
    void reopen(Universe) {
        HostMgr::create();
        HostMgr::addBackend(validMySQLConnectionString());
        hdsptr_ = HostMgr::instance().getHostDataSource();
    }

    /// @brief returns number of rows in a table
    ///
    /// Note: This method uses its own connection. It will not work if your test
    /// uses transactions.
    ///
    /// @param name of the table
    /// @return number of rows currently present in the table
    int countRowsInTable(const std::string& table) {
        string query = "SELECT * FROM " + table;

        DatabaseConnection::ParameterMap params;
        params["name"] = "keatest";
        params["user"] = "keatest";
        params["password"] = "keatest";

        MySqlConnection conn(params);
        conn.openDatabase();

        int status = MysqlQuery(conn.mysql_, query.c_str());
        if (status != 0) {
            isc_throw(DbOperationError, "Query failed: " << mysql_error(conn.mysql_));
        }

        MYSQL_RES * res = mysql_store_result(conn.mysql_);
        int numrows = static_cast<int>(mysql_num_rows(res));
        mysql_free_result(res);

        return (numrows);
    }

    /// @brief Returns number of IPv4 options currently stored in DB.
    virtual int countDBOptions4() {
        return (countRowsInTable("dhcp4_options"));
    }

    /// @brief Returns number of IPv6 options currently stored in DB.
    virtual int countDBOptions6() {
        return (countRowsInTable("dhcp6_options"));
    }

    /// @brief Returns number of IPv6 reservations currently stored in DB.
    virtual int countDBReservations6() {
        return (countRowsInTable("ipv6_reservations"));
    }

};

/// @brief Check that database can be opened
///
/// This test checks if the MySqlHostDataSource can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// MySqlHostMgr test fixture set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.
TEST(MySqlHostDataSource, OpenDatabase) {
    // Schema needs to be created for the test to work.
    destroyMySQLSchema();
    createMySQLSchema();

    // Check that host manager opens the database correctly and tidy up.  If it
    // fails, print the error message.
    try {
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(validMySQLConnectionString()));
        HostMgr::delBackend("mysql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
    }

    // Check that host manager opens the database correctly with a longer
    // timeout.  If it fails, print the error message.
    try {
        string connection_string = validMySQLConnectionString() + string(" ") +
                                   string(VALID_TIMEOUT);
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(connection_string));
        HostMgr::delBackend("mysql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
    }

    // Check that attempting to get an instance of the host data source when
    // none is set returns empty pointer.
    EXPECT_FALSE(HostMgr::instance().getHostDataSource());

    // Check that wrong specification of backend throws an exception.
    // (This is really a check on HostDataSourceFactory, but is convenient to
    // perform here.)
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        NULL, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        InvalidParameter);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        INVALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        InvalidType);

    // Check that invalid login data causes an exception.
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_1)),
        DbInvalidTimeout);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_2)),
        DbInvalidTimeout);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD,
        VALID_TIMEOUT, INVALID_READONLY_DB)), DbInvalidReadOnly);

    // Check for missing parameters
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        NoDatabaseName);

    // Tidy up after the test
    destroyMySQLSchema();
}

/// @brief Check that database can be opened with Multi-Threading
///
/// This test checks if the MySqlHostDataSource can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// MySqlHostMgr test fixture set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.
TEST(MySqlHostDataSource, OpenDatabaseMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);

    // Schema needs to be created for the test to work.
    destroyMySQLSchema();
    createMySQLSchema();

    // Check that host manager opens the database correctly and tidy up.  If it
    // fails, print the error message.
    try {
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(validMySQLConnectionString()));
        HostMgr::delBackend("mysql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
    }

    // Check that host manager opens the database correctly with a longer
    // timeout.  If it fails, print the error message.
    try {
        string connection_string = validMySQLConnectionString() + string(" ") +
                                   string(VALID_TIMEOUT);
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(connection_string));
        HostMgr::delBackend("mysql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the MySQL tests will run correctly.\n";
    }

    // Check that attempting to get an instance of the host data source when
    // none is set returns empty pointer.
    EXPECT_FALSE(HostMgr::instance().getHostDataSource());

    // Check that wrong specification of backend throws an exception.
    // (This is really a check on HostDataSourceFactory, but is convenient to
    // perform here.)
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        NULL, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        InvalidParameter);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        INVALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        InvalidType);

    // Check that invalid login data causes an exception.
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_1)),
        DbInvalidTimeout);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_2)),
        DbInvalidTimeout);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD,
        VALID_TIMEOUT, INVALID_READONLY_DB)), DbInvalidReadOnly);

    // Check for missing parameters
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        NoDatabaseName);

    // Tidy up after the test
    destroyMySQLSchema();
}

/// @brief Flag used to detect calls to db_lost_callback function
bool callback_called = false;

/// @brief Callback function used in open database testing
bool db_lost_callback(ReconnectCtlPtr /* db_conn_retry */) {
    return (callback_called = true);
}

/// @brief Make sure open failures do NOT invoke db lost callback
/// The db lost callback should only be invoked after successfully
/// opening the DB and then subsequently losing it. Failing to
/// open should be handled directly by the application layer.
/// There is simply no good way to break the connection in a
/// unit test environment.  So testing the callback invocation
/// in a unit test is next to impossible. That has to be done
/// as a system test.
TEST(MySqlHostDataSource, NoCallbackOnOpenFail) {
    // Schema needs to be created for the test to work.
    destroyMySQLSchema();
    createMySQLSchema();

    callback_called = false;
    DatabaseConnection::db_lost_callback_ = db_lost_callback;
    HostMgr::create();
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
                 DbOpenError);

    EXPECT_FALSE(callback_called);
    destroyMySQLSchema();
}

/// @brief Make sure open failures do NOT invoke db lost callback
/// The db lost callback should only be invoked after successfully
/// opening the DB and then subsequently losing it. Failing to
/// open should be handled directly by the application layer.
/// There is simply no good way to break the connection in a
/// unit test environment.  So testing the callback invocation
/// in a unit test is next to impossible. That has to be done
/// as a system test.
TEST(MySqlHostDataSource, NoCallbackOnOpenFailMultiThreading) {
    // Enable Multi-Threading.
    MultiThreadingTest mt(true);

    // Schema needs to be created for the test to work.
    destroyMySQLSchema();
    createMySQLSchema();

    callback_called = false;
    DatabaseConnection::db_lost_callback_ = db_lost_callback;
    HostMgr::create();
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        MYSQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
                 DbOpenError);

    EXPECT_FALSE(callback_called);
    destroyMySQLSchema();
}

/// @brief Check conversion functions
///
/// The server works using cltt and valid_filetime.  In the database, the
/// information is stored as expire_time and valid-lifetime, which are
/// related by
///
/// expire_time = cltt + valid_lifetime
///
/// This test checks that the conversion is correct.  It does not check that the
/// data is entered into the database correctly, only that the MYSQL_TIME
/// structure used for the entry is correctly set up.
TEST(MySqlConnection, checkTimeConversion) {
    const time_t cltt = time(NULL);
    const uint32_t valid_lft = 86400;       // 1 day
    struct tm tm_expire;
    MYSQL_TIME mysql_expire;

    // Work out what the broken-down time will be for one day
    // after the current time.
    time_t expire_time = cltt + valid_lft;
    (void) localtime_r(&expire_time, &tm_expire);

    // Convert to the database time
    MySqlConnection::convertToDatabaseTime(cltt, valid_lft, mysql_expire);

    // Are the times the same?
    EXPECT_EQ(tm_expire.tm_year + 1900, mysql_expire.year);
    EXPECT_EQ(tm_expire.tm_mon + 1,  mysql_expire.month);
    EXPECT_EQ(tm_expire.tm_mday, mysql_expire.day);
    EXPECT_EQ(tm_expire.tm_hour, mysql_expire.hour);
    EXPECT_EQ(tm_expire.tm_min, mysql_expire.minute);
    EXPECT_EQ(tm_expire.tm_sec, mysql_expire.second);
    EXPECT_EQ(0, mysql_expire.second_part);
    EXPECT_EQ(0, mysql_expire.neg);

    // Convert back
    time_t converted_cltt = 0;
    MySqlConnection::convertFromDatabaseTime(mysql_expire, valid_lft, converted_cltt);
    EXPECT_EQ(cltt, converted_cltt);
}

/// @brief This test verifies that database backend can operate in Read-Only mode.
TEST_F(MySqlHostDataSourceTest, testReadOnlyDatabase) {
    testReadOnlyDatabase(MYSQL_VALID_TYPE);
}

/// @brief This test verifies that database backend can operate in Read-Only mode.
TEST_F(MySqlHostDataSourceTest, testReadOnlyDatabaseMultiThreading) {
    MultiThreadingTest mt(true);
    testReadOnlyDatabase(MYSQL_VALID_TYPE);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by IPv4
/// address. Host uses hw address as identifier.
TEST_F(MySqlHostDataSourceTest, basic4HWAddr) {
    testBasic4(Host::IDENT_HWADDR);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by IPv4
/// address. Host uses hw address as identifier.
TEST_F(MySqlHostDataSourceTest, basic4HWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testBasic4(Host::IDENT_HWADDR);
}

/// @brief Verifies that IPv4 host reservation with options can have the global
/// subnet id value
TEST_F(MySqlHostDataSourceTest, globalSubnetId4) {
    testGlobalSubnetId4();
}

/// @brief Verifies that IPv4 host reservation with options can have the global
/// subnet id value
TEST_F(MySqlHostDataSourceTest, globalSubnetId4MultiThreading) {
    MultiThreadingTest mt(true);
    testGlobalSubnetId4();
}

/// @brief Verifies that IPv6 host reservation with options can have the global
/// subnet id value
TEST_F(MySqlHostDataSourceTest, globalSubnetId6) {
    testGlobalSubnetId6();
}

/// @brief Verifies that IPv6 host reservation with options can have the global
/// subnet id value
TEST_F(MySqlHostDataSourceTest, globalSubnetId6MultiThreading) {
    MultiThreadingTest mt(true);
    testGlobalSubnetId6();
}

/// @brief Verifies that IPv4 host reservation with options can have a max value
/// for  dhcp4_subnet id
TEST_F(MySqlHostDataSourceTest, maxSubnetId4) {
    testMaxSubnetId4();
}

/// @brief Verifies that IPv4 host reservation with options can have a max value
/// for  dhcp4_subnet id
TEST_F(MySqlHostDataSourceTest, maxSubnetId4MultiThreading) {
    MultiThreadingTest mt(true);
    testMaxSubnetId4();
}

/// @brief Verifies that IPv6 host reservation with options can have a max value
/// for  dhcp6_subnet id
TEST_F(MySqlHostDataSourceTest, maxSubnetId6) {
    testMaxSubnetId6();
}

/// @brief Verifies that IPv6 host reservation with options can have a max value
/// for  dhcp6_subnet id
TEST_F(MySqlHostDataSourceTest, maxSubnetId6MultiThreading) {
    MultiThreadingTest mt(true);
    testMaxSubnetId6();
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAll4BySubnet) {
    testGetAll4();
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAll4BySubnetMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAll4();
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAll6BySubnet) {
    testGetAll6();
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAll6BySubnetMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAll6();
}

/// @brief Verifies that host reservations with the same hostname can be retrieved
TEST_F(MySqlHostDataSourceTest, getAllbyHostname) {
    testGetAllbyHostname();
}

/// @brief Verifies that host reservations with the same hostname can be retrieved
TEST_F(MySqlHostDataSourceTest, getAllbyHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testGetAllbyHostname();
}

/// @brief Verifies that IPv4 host reservations with the same hostname and in
/// the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAllbyHostnameSubnet4) {
    testGetAllbyHostnameSubnet4();
}

/// @brief Verifies that IPv4 host reservations with the same hostname and in
/// the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAllbyHostnameSubnet4MultiThreading) {
    MultiThreadingTest mt(true);
    testGetAllbyHostnameSubnet4();
}

/// @brief Verifies that IPv6 host reservations with the same hostname and in
/// the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAllbyHostnameSubnet6) {
    testGetAllbyHostnameSubnet6();
}

/// @brief Verifies that IPv6 host reservations with the same hostname and in
/// the same subnet can be retrieved
TEST_F(MySqlHostDataSourceTest, getAllbyHostnameSubnet6MultiThreading) {
    MultiThreadingTest mt(true);
    testGetAllbyHostnameSubnet6();
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
/// by pages.
TEST_F(MySqlHostDataSourceTest, getPage4) {
    testGetPage4();
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
/// by pages.
TEST_F(MySqlHostDataSourceTest, getPage4MultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage4();
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
/// by pages.
TEST_F(MySqlHostDataSourceTest, getPage6) {
    testGetPage6();
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
/// by pages.
TEST_F(MySqlHostDataSourceTest, getPage6MultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage6();
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
/// by pages without truncation from the limit.
TEST_F(MySqlHostDataSourceTest, getPageLimit4) {
    testGetPageLimit4(Host::IDENT_DUID);
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
/// by pages without truncation from the limit.
TEST_F(MySqlHostDataSourceTest, getPageLimit4MultiThreading) {
    MultiThreadingTest mt(true);
    testGetPageLimit4(Host::IDENT_DUID);
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
/// by pages without truncation from the limit.
TEST_F(MySqlHostDataSourceTest, getPageLimit6) {
    testGetPageLimit6(Host::IDENT_HWADDR);
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
/// by pages without truncation from the limit.
TEST_F(MySqlHostDataSourceTest, getPageLimit6MultiThreading) {
    MultiThreadingTest mt(true);
    testGetPageLimit6(Host::IDENT_HWADDR);
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
/// by pages even with multiple subnets.
TEST_F(MySqlHostDataSourceTest, getPage4Subnets) {
    testGetPage4Subnets();
}

/// @brief Verifies that IPv4 host reservations in the same subnet can be retrieved
/// by pages even with multiple subnets.
TEST_F(MySqlHostDataSourceTest, getPage4SubnetsMultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage4Subnets();
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
/// by pages even with multiple subnets.
TEST_F(MySqlHostDataSourceTest, getPage6Subnets) {
    testGetPage6Subnets();
}

/// @brief Verifies that IPv6 host reservations in the same subnet can be retrieved
/// by pages even with multiple subnets.
TEST_F(MySqlHostDataSourceTest, getPage6SubnetsMultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage6Subnets();
}

// Verifies that all IPv4 host reservations can be retrieved by pages.
TEST_F(MySqlHostDataSourceTest, getPage4All) {
    testGetPage4All();
}

// Verifies that all IPv4 host reservations can be retrieved by pages.
TEST_F(MySqlHostDataSourceTest, getPage4AllMultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage4All();
}

// Verifies that all IPv6 host reservations can be retrieved by pages.
TEST_F(MySqlHostDataSourceTest, getPage6All) {
    testGetPage6All();
}

// Verifies that all IPv6 host reservations can be retrieved by pages.
TEST_F(MySqlHostDataSourceTest, getPage6AllMultiThreading) {
    MultiThreadingTest mt(true);
    testGetPage6All();
}

/// @brief Test verifies if a host reservation can be added and later retrieved by IPv4
/// address. Host uses client-id (DUID) as identifier.
TEST_F(MySqlHostDataSourceTest, basic4ClientId) {
    testBasic4(Host::IDENT_DUID);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by IPv4
/// address. Host uses client-id (DUID) as identifier.
TEST_F(MySqlHostDataSourceTest, basic4ClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testBasic4(Host::IDENT_DUID);
}

/// @brief Test verifies that multiple hosts can be added and later retrieved by their
/// reserved IPv4 address. This test uses HW addresses as identifiers.
TEST_F(MySqlHostDataSourceTest, getByIPv4HWaddr) {
    testGetByIPv4(Host::IDENT_HWADDR);
}

/// @brief Test verifies that multiple hosts can be added and later retrieved by their
/// reserved IPv4 address. This test uses HW addresses as identifiers.
TEST_F(MySqlHostDataSourceTest, getByIPv4HWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv4(Host::IDENT_HWADDR);
}

/// @brief Test verifies that multiple hosts can be added and later retrieved by their
/// reserved IPv4 address. This test uses client-id (DUID) as identifiers.
TEST_F(MySqlHostDataSourceTest, getByIPv4ClientId) {
    testGetByIPv4(Host::IDENT_DUID);
}

/// @brief Test verifies that multiple hosts can be added and later retrieved by their
/// reserved IPv4 address. This test uses client-id (DUID) as identifiers.
TEST_F(MySqlHostDataSourceTest, getByIPv4ClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv4(Host::IDENT_DUID);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// hardware address.
TEST_F(MySqlHostDataSourceTest, get4ByHWaddr) {
    testGet4ByIdentifier(Host::IDENT_HWADDR);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// hardware address.
TEST_F(MySqlHostDataSourceTest, get4ByHWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_HWADDR);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// DUID.
TEST_F(MySqlHostDataSourceTest, get4ByDUID) {
    testGet4ByIdentifier(Host::IDENT_DUID);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// DUID.
TEST_F(MySqlHostDataSourceTest, get4ByDUIDMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_DUID);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// circuit id.
TEST_F(MySqlHostDataSourceTest, get4ByCircuitId) {
    testGet4ByIdentifier(Host::IDENT_CIRCUIT_ID);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// circuit id.
TEST_F(MySqlHostDataSourceTest, get4ByCircuitIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_CIRCUIT_ID);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// client-id.
TEST_F(MySqlHostDataSourceTest, get4ByClientId) {
    testGet4ByIdentifier(Host::IDENT_CLIENT_ID);
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// client-id.
TEST_F(MySqlHostDataSourceTest, get4ByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_CLIENT_ID);
}

/// @brief Test verifies if hardware address and client identifier are not confused.
TEST_F(MySqlHostDataSourceTest, hwaddrNotClientId1) {
    testHWAddrNotClientId();
}

/// @brief Test verifies if hardware address and client identifier are not confused.
TEST_F(MySqlHostDataSourceTest, hwaddrNotClientId1MultiThreading) {
    MultiThreadingTest mt(true);
    testHWAddrNotClientId();
}

/// @brief Test verifies if hardware address and client identifier are not confused.
TEST_F(MySqlHostDataSourceTest, hwaddrNotClientId2) {
    testClientIdNotHWAddr();
}

/// @brief Test verifies if hardware address and client identifier are not confused.
TEST_F(MySqlHostDataSourceTest, hwaddrNotClientId2MultiThreading) {
    MultiThreadingTest mt(true);
    testClientIdNotHWAddr();
}

/// @brief Test verifies if a host with FQDN hostname can be stored and later retrieved.
TEST_F(MySqlHostDataSourceTest, hostnameFQDN) {
    testHostname("foo.example.org", 1);
}

/// @brief Test verifies if a host with FQDN hostname can be stored and later retrieved.
TEST_F(MySqlHostDataSourceTest, hostnameFQDNMultiThreading) {
    MultiThreadingTest mt(true);
    testHostname("foo.example.org", 1);
}

/// @brief Test verifies if 100 hosts with unique FQDN hostnames can be stored and later
/// retrieved.
TEST_F(MySqlHostDataSourceTest, hostnameFQDN100) {
    testHostname("foo.example.org", 100);
}

/// @brief Test verifies if 100 hosts with unique FQDN hostnames can be stored and later
/// retrieved.
TEST_F(MySqlHostDataSourceTest, hostnameFQDN100MultiThreading) {
    MultiThreadingTest mt(true);
    testHostname("foo.example.org", 100);
}

/// @brief Test verifies if a host without any hostname specified can be stored and later
/// retrieved.
TEST_F(MySqlHostDataSourceTest, noHostname) {
    testHostname("", 1);
}

/// @brief Test verifies if a host without any hostname specified can be stored and later
/// retrieved.
TEST_F(MySqlHostDataSourceTest, noHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testHostname("", 1);
}

/// @brief Test verifies if a host with user context can be stored and later retrieved.
TEST_F(MySqlHostDataSourceTest, usercontext) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testUserContext(Element::fromJSON(comment));
}

/// @brief Test verifies if a host with user context can be stored and later retrieved.
TEST_F(MySqlHostDataSourceTest, usercontextMultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testUserContext(Element::fromJSON(comment));
}

/// @brief Test verifies if the hardware or client-id query can match hardware address.
TEST_F(MySqlHostDataSourceTest, DISABLED_hwaddrOrClientId1) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with hardware address X, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

/// @brief Test verifies if the hardware or client-id query can match hardware address.
TEST_F(MySqlHostDataSourceTest, DISABLED_hwaddrOrClientId1MultiThreading) {
    MultiThreadingTest mt(true);
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with hardware address X, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

/// @brief Test verifies if the hardware or client-id query can match client-id.
TEST_F(MySqlHostDataSourceTest, DISABLED_hwaddrOrClientId2) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with client identifier Y, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

/// @brief Test verifies if the hardware or client-id query can match client-id.
TEST_F(MySqlHostDataSourceTest, DISABLED_hwaddrOrClientId2MultiThreading) {
    MultiThreadingTest mt(true);
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with client identifier Y, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

/// @brief Test verifies that host with IPv6 address and DUID can be added and
/// later retrieved by IPv6 address.
TEST_F(MySqlHostDataSourceTest, get6AddrWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, false);
}

/// @brief Test verifies that host with IPv6 address and DUID can be added and
/// later retrieved by IPv6 address.
TEST_F(MySqlHostDataSourceTest, get6AddrWithDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_DUID, false);
}

/// @brief Test verifies that host with IPv6 address and HWAddr can be added and
/// later retrieved by IPv6 address.
TEST_F(MySqlHostDataSourceTest, get6AddrWithHWAddr) {
    testGetByIPv6(Host::IDENT_HWADDR, false);
}

/// @brief Test verifies that host with IPv6 address and HWAddr can be added and
/// later retrieved by IPv6 address.
TEST_F(MySqlHostDataSourceTest, get6AddrWithHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_HWADDR, false);
}

/// @brief Test verifies that host with IPv6 prefix and DUID can be added and
/// later retrieved by IPv6 prefix.
TEST_F(MySqlHostDataSourceTest, get6PrefixWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, true);
}

/// @brief Test verifies that host with IPv6 prefix and DUID can be added and
/// later retrieved by IPv6 prefix.
TEST_F(MySqlHostDataSourceTest, get6PrefixWithDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_DUID, true);
}

/// @brief Test verifies that host with IPv6 prefix and HWAddr can be added and
/// later retrieved by IPv6 prefix.
TEST_F(MySqlHostDataSourceTest, get6PrefixWithHWaddr) {
    testGetByIPv6(Host::IDENT_HWADDR, true);
}

/// @brief Test verifies that host with IPv6 prefix and HWAddr can be added and
/// later retrieved by IPv6 prefix.
TEST_F(MySqlHostDataSourceTest, get6PrefixWithHWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_HWADDR, true);
}

/// @brief Test verifies that host with IPv6 prefix reservation can be retrieved
/// by subnet id and prefix value.
TEST_F(MySqlHostDataSourceTest, get6SubnetPrefix) {
    testGetBySubnetIPv6();
}

/// @brief Test verifies that host with IPv6 prefix reservation can be retrieved
/// by subnet id and prefix value.
TEST_F(MySqlHostDataSourceTest, get6SubnetPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testGetBySubnetIPv6();
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// hardware address.
TEST_F(MySqlHostDataSourceTest, get6ByHWaddr) {
    testGet6ByHWAddr();
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// hardware address.
TEST_F(MySqlHostDataSourceTest, get6ByHWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGet6ByHWAddr();
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// client identifier.
TEST_F(MySqlHostDataSourceTest, get6ByClientId) {
    testGet6ByClientId();
}

/// @brief Test verifies if a host reservation can be added and later retrieved by
/// client identifier.
TEST_F(MySqlHostDataSourceTest, get6ByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGet6ByClientId();
}

/// @brief Test verifies if a host reservation can be stored with both IPv6 address and
/// prefix.
TEST_F(MySqlHostDataSourceTest, addr6AndPrefix) {
    testAddr6AndPrefix();
}

/// @brief Test verifies if a host reservation can be stored with both IPv6 address and
/// prefix.
TEST_F(MySqlHostDataSourceTest, addr6AndPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testAddr6AndPrefix();
}

/// @brief Tests if host with multiple IPv6 reservations can be added and then
/// retrieved correctly. Test checks reservations comparing.
TEST_F(MySqlHostDataSourceTest, multipleReservations) {
    testMultipleReservations();
}

/// @brief Tests if host with multiple IPv6 reservations can be added and then
/// retrieved correctly. Test checks reservations comparing.
TEST_F(MySqlHostDataSourceTest, multipleReservationsMultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleReservations();
}

/// @brief Tests if compareIPv6Reservations() method treats same pool of reservations
/// but added in different order as equal.
TEST_F(MySqlHostDataSourceTest, multipleReservationsDifferentOrder) {
    testMultipleReservationsDifferentOrder();
}

/// @brief Tests if compareIPv6Reservations() method treats same pool of reservations
/// but added in different order as equal.
TEST_F(MySqlHostDataSourceTest, multipleReservationsDifferentOrderMultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleReservationsDifferentOrder();
}

/// @brief Test that multiple client classes for IPv4 can be inserted and
/// retrieved for a given host reservation.
TEST_F(MySqlHostDataSourceTest, multipleClientClasses4) {
    testMultipleClientClasses4();
}

/// @brief Test that multiple client classes for IPv4 can be inserted and
/// retrieved for a given host reservation.
TEST_F(MySqlHostDataSourceTest, multipleClientClasses4MultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleClientClasses4();
}

/// @brief Test that multiple client classes for IPv6 can be inserted and
/// retrieved for a given host reservation.
TEST_F(MySqlHostDataSourceTest, multipleClientClasses6) {
    testMultipleClientClasses6();
}

/// @brief Test that multiple client classes for IPv6 can be inserted and
/// retrieved for a given host reservation.
TEST_F(MySqlHostDataSourceTest, multipleClientClasses6MultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleClientClasses6();
}

/// @brief Test that multiple client classes for both IPv4 and IPv6 can
/// be inserted and retrieved for a given host reservation.
TEST_F(MySqlHostDataSourceTest, multipleClientClassesBoth) {
    testMultipleClientClassesBoth();
}

/// @brief Test that multiple client classes for both IPv4 and IPv6 can
/// be inserted and retrieved for a given host reservation.
TEST_F(MySqlHostDataSourceTest, multipleClientClassesBothMultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleClientClassesBoth();
}

/// @brief Test if the same host can have reservations in different subnets (with the
/// same hardware address). The test logic is as follows:
/// Insert 10 host reservations for a given physical host (the same
/// hardware address), but for different subnets (different subnet-ids).
/// Make sure that getAll() returns them all correctly.
TEST_F(MySqlHostDataSourceTest, multipleSubnetsHWAddr) {
    testMultipleSubnets(10, Host::IDENT_HWADDR);
}

/// @brief Test if the same host can have reservations in different subnets (with the
/// same hardware address). The test logic is as follows:
/// Insert 10 host reservations for a given physical host (the same
/// hardware address), but for different subnets (different subnet-ids).
/// Make sure that getAll() returns them all correctly.
TEST_F(MySqlHostDataSourceTest, multipleSubnetsHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleSubnets(10, Host::IDENT_HWADDR);
}

/// @brief Test if the same host can have reservations in different subnets (with the
/// same client identifier). The test logic is as follows:
///
/// Insert 10 host reservations for a given physical host (the same
/// client-identifier), but for different subnets (different subnet-ids).
/// Make sure that getAll() returns them correctly.
TEST_F(MySqlHostDataSourceTest, multipleSubnetsClientId) {
    testMultipleSubnets(10, Host::IDENT_DUID);
}

/// @brief Test if the same host can have reservations in different subnets (with the
/// same client identifier). The test logic is as follows:
///
/// Insert 10 host reservations for a given physical host (the same
/// client-identifier), but for different subnets (different subnet-ids).
/// Make sure that getAll() returns them correctly.
TEST_F(MySqlHostDataSourceTest, multipleSubnetsClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleSubnets(10, Host::IDENT_DUID);
}

/// @brief Test if host reservations made for different IPv6 subnets are handled correctly.
/// The test logic is as follows:
///
/// Insert 10 host reservations for different subnets. Make sure that
/// get6(subnet-id, ...) calls return correct reservation.
TEST_F(MySqlHostDataSourceTest, subnetId6) {
    testSubnetId6(10, Host::IDENT_HWADDR);
}

/// @brief Test if host reservations made for different IPv6 subnets are handled correctly.
/// The test logic is as follows:
///
/// Insert 10 host reservations for different subnets. Make sure that
/// get6(subnet-id, ...) calls return correct reservation.
TEST_F(MySqlHostDataSourceTest, subnetId6MultiThreading) {
    MultiThreadingTest mt(true);
    testSubnetId6(10, Host::IDENT_HWADDR);
}

/// @brief Test if the duplicate host instances can't be inserted. The test logic is as
/// follows: try to add multiple instances of the same host reservation and
/// verify that the second and following attempts will throw exceptions.
/// Hosts with same DUID.
TEST_F(MySqlHostDataSourceTest, addDuplicate6WithDUID) {
    testAddDuplicate6WithSameDUID();
}

/// @brief Test if the duplicate host instances can't be inserted. The test logic is as
/// follows: try to add multiple instances of the same host reservation and
/// verify that the second and following attempts will throw exceptions.
/// Hosts with same DUID.
TEST_F(MySqlHostDataSourceTest, addDuplicate6WithDUIDMultiThreading) {
    MultiThreadingTest mt(true);
    testAddDuplicate6WithSameDUID();
}

/// @brief Test if the duplicate host instances can't be inserted. The test logic is as
/// follows: try to add multiple instances of the same host reservation and
/// verify that the second and following attempts will throw exceptions.
/// Hosts with same HWAddr.
TEST_F(MySqlHostDataSourceTest, addDuplicate6WithHWAddr) {
    testAddDuplicate6WithSameHWAddr();
}

/// @brief Test if the duplicate host instances can't be inserted. The test logic is as
/// follows: try to add multiple instances of the same host reservation and
/// verify that the second and following attempts will throw exceptions.
/// Hosts with same HWAddr.
TEST_F(MySqlHostDataSourceTest, addDuplicate6WithHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testAddDuplicate6WithSameHWAddr();
}

/// @brief Test if the same IPv6 reservation can't be inserted multiple times.
TEST_F(MySqlHostDataSourceTest, addDuplicateIPv6) {
    testAddDuplicateIPv6();
}

/// @brief Test if the same IPv6 reservation can't be inserted multiple times.
TEST_F(MySqlHostDataSourceTest, addDuplicateIPv6MultiThreading) {
    MultiThreadingTest mt(true);
    testAddDuplicateIPv6();
}

/// @brief Test if the host reservation for the same IPv6 address can be inserted
/// multiple times when allowed by the configuration and when the host identifier
/// is different.
TEST_F(MySqlHostDataSourceTest, allowDuplicateIPv6) {
    testAllowDuplicateIPv6();
}

/// @brief Test if the host reservation for the same IPv6 address can be inserted
/// multiple times when allowed by the configuration and when the host identifier
/// is different.
TEST_F(MySqlHostDataSourceTest, allowDuplicateIPv6MultiThreading) {
    MultiThreadingTest mt(true);
    testAllowDuplicateIPv6();
}

/// @brief Test if the duplicate IPv4 host instances can't be inserted. The test logic is as
/// follows: try to add multiple instances of the same host reservation and
/// verify that the second and following attempts will throw exceptions.
TEST_F(MySqlHostDataSourceTest, addDuplicateIPv4) {
    testAddDuplicateIPv4();
}

/// @brief Test if the duplicate IPv4 host instances can't be inserted. The test logic is as
/// follows: try to add multiple instances of the same host reservation and
/// verify that the second and following attempts will throw exceptions.
TEST_F(MySqlHostDataSourceTest, addDuplicateIPv4MultiThreading) {
    MultiThreadingTest mt(true);
    testAddDuplicateIPv4();
}

/// @brief Test if the host reservation for the same IPv4 address can be inserted
/// multiple times when allowed by the configuration and when the host identifier
/// is different.
TEST_F(MySqlHostDataSourceTest, allowDuplicateIPv4) {
    testAllowDuplicateIPv4();
}

/// @brief Test if the host reservation for the same IPv4 address can be inserted
/// multiple times when allowed by the configuration and when the host identifier
/// is different.
TEST_F(MySqlHostDataSourceTest, allowDuplicateIPv4MultiThreading) {
    MultiThreadingTest mt(true);
    testAllowDuplicateIPv4();
}

/// @brief This test verifies that DHCPv4 options can be inserted in a binary format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, optionsReservations4) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(false, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv4 options can be inserted in a binary format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, optionsReservations4MultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(false, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv6 options can be inserted in a binary format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, optionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(false, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv6 options can be inserted in a binary format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, optionsReservations6MultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(false, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
/// binary format and retrieved with a single query to the database.
TEST_F(MySqlHostDataSourceTest, optionsReservations46) {
    testOptionsReservations46(false);
}

/// @brief This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
/// binary format and retrieved with a single query to the database.
TEST_F(MySqlHostDataSourceTest, optionsReservations46MultiThreading) {
    MultiThreadingTest mt(true);
    testOptionsReservations46(false);
}

/// @brief This test verifies that DHCPv4 options can be inserted in a textual format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, formattedOptionsReservations4) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(true, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv4 options can be inserted in a textual format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, formattedOptionsReservations4MultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(true, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv6 options can be inserted in a textual format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, formattedOptionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(true, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv6 options can be inserted in a textual format
/// and retrieved from the MySQL host database.
TEST_F(MySqlHostDataSourceTest, formattedOptionsReservations6MultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(true, Element::fromJSON(comment));
}

/// @brief This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
/// textual format and retrieved with a single query to the database.
TEST_F(MySqlHostDataSourceTest, formattedOptionsReservations46) {
    testOptionsReservations46(true);
}

/// @brief This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
/// textual format and retrieved with a single query to the database.
TEST_F(MySqlHostDataSourceTest, formattedOptionsReservations46MultiThreading) {
    MultiThreadingTest mt(true);
    testOptionsReservations46(true);
}

/// @brief This test checks transactional insertion of the host information
/// into the database. The failure to insert host information at
/// any stage should cause the whole transaction to be rolled back.
TEST_F(MySqlHostDataSourceTest, testAddRollback) {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // To test the transaction rollback mechanism we need to cause the
    // insertion of host information to fail at some stage. The 'hosts'
    // table should be updated correctly but the failure should occur
    // when inserting reservations or options. The simplest way to
    // achieve that is to simply drop one of the tables. To do so, we
    // connect to the database and issue a DROP query.
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";
    MySqlConnection conn(params);
    ASSERT_NO_THROW(conn.openDatabase());

    int status = MysqlQuery(conn.mysql_,
                            "DROP TABLE IF EXISTS ipv6_reservations");
    ASSERT_EQ(0, status) << mysql_error(conn.mysql_);

    // Create a host with a reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::1",
                                        Host::IDENT_HWADDR, false);
    // Let's assign some DHCPv4 subnet to the host, because we will use the
    // DHCPv4 subnet to try to retrieve the host after failed insertion.
    host->setIPv4SubnetID(SubnetID(4));

    // There is no ipv6_reservations table, so the insertion should fail.
    ASSERT_THROW(hdsptr_->add(host), DbOperationError);

    // Even though we have created a DHCPv6 host, we can't use get6()
    // method to retrieve the host from the database, because the
    // query would expect that the ipv6_reservations table is present.
    // Therefore, the query would fail. Instead, we use the get4 method
    // which uses the same client identifier, but doesn't attempt to
    // retrieve the data from ipv6_reservations table. The query should
    // pass but return no host because the (insert) transaction is expected
    // to be rolled back.
    ConstHostPtr from_hds = hdsptr_->get4(host->getIPv4SubnetID(),
                                          host->getIdentifierType(),
                                          &host->getIdentifier()[0],
                                          host->getIdentifier().size());
    EXPECT_FALSE(from_hds);
}

/// @brief This test checks transactional insertion of the host information
/// into the database. The failure to insert host information at
/// any stage should cause the whole transaction to be rolled back.
TEST_F(MySqlHostDataSourceTest, testAddRollbackMultiThreading) {
    MultiThreadingTest mt(true);
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // To test the transaction rollback mechanism we need to cause the
    // insertion of host information to fail at some stage. The 'hosts'
    // table should be updated correctly but the failure should occur
    // when inserting reservations or options. The simplest way to
    // achieve that is to simply drop one of the tables. To do so, we
    // connect to the database and issue a DROP query.
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";
    MySqlConnection conn(params);
    ASSERT_NO_THROW(conn.openDatabase());

    int status = MysqlQuery(conn.mysql_,
                            "DROP TABLE IF EXISTS ipv6_reservations");
    ASSERT_EQ(0, status) << mysql_error(conn.mysql_);

    // Create a host with a reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::1",
                                        Host::IDENT_HWADDR, false);
    // Let's assign some DHCPv4 subnet to the host, because we will use the
    // DHCPv4 subnet to try to retrieve the host after failed insertion.
    host->setIPv4SubnetID(SubnetID(4));

    // There is no ipv6_reservations table, so the insertion should fail.
    ASSERT_THROW(hdsptr_->add(host), DbOperationError);

    // Even though we have created a DHCPv6 host, we can't use get6()
    // method to retrieve the host from the database, because the
    // query would expect that the ipv6_reservations table is present.
    // Therefore, the query would fail. Instead, we use the get4 method
    // which uses the same client identifier, but doesn't attempt to
    // retrieve the data from ipv6_reservations table. The query should
    // pass but return no host because the (insert) transaction is expected
    // to be rolled back.
    ConstHostPtr from_hds = hdsptr_->get4(host->getIPv4SubnetID(),
                                          host->getIdentifierType(),
                                          &host->getIdentifier()[0],
                                          host->getIdentifier().size());
    EXPECT_FALSE(from_hds);
}

/// @brief This test checks that siaddr, sname, file fields can be retrieved
/// from a database for a host.
TEST_F(MySqlHostDataSourceTest, messageFields) {
    testMessageFields4();
}

/// @brief This test checks that siaddr, sname, file fields can be retrieved
/// from a database for a host.
TEST_F(MySqlHostDataSourceTest, messageFieldsMultiThreading) {
    MultiThreadingTest mt(true);
    testMessageFields4();
}

/// @brief Check that delete(subnet-id, addr4) works.
TEST_F(MySqlHostDataSourceTest, deleteByAddr4) {
    testDeleteByAddr4();
}

/// @brief Check that delete(subnet-id, addr4) works.
TEST_F(MySqlHostDataSourceTest, deleteByAddr4MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteByAddr4();
}

/// @brief Check that delete(subnet4-id, identifier-type, identifier) works.
TEST_F(MySqlHostDataSourceTest, deleteById4) {
    testDeleteById4();
}

/// @brief Check that delete(subnet4-id, identifier-type, identifier) works.
TEST_F(MySqlHostDataSourceTest, deleteById4MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteById4();
}

/// @brief Check that delete(subnet4-id, identifier-type, identifier) works,
/// even when options are present.
TEST_F(MySqlHostDataSourceTest, deleteById4Options) {
    testDeleteById4Options();
}

/// @brief Check that delete(subnet4-id, identifier-type, identifier) works,
/// even when options are present.
TEST_F(MySqlHostDataSourceTest, deleteById4OptionsMultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteById4Options();
}

/// @brief Check that delete(subnet6-id, identifier-type, identifier) works.
TEST_F(MySqlHostDataSourceTest, deleteById6) {
    testDeleteById6();
}

/// @brief Check that delete(subnet6-id, identifier-type, identifier) works.
TEST_F(MySqlHostDataSourceTest, deleteById6MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteById6();
}

/// @brief Check that delete(subnet6-id, identifier-type, identifier) works,
/// even when options are present.
TEST_F(MySqlHostDataSourceTest, deleteById6Options) {
    testDeleteById6Options();
}

/// @brief Check that delete(subnet6-id, identifier-type, identifier) works,
/// even when options are present.
TEST_F(MySqlHostDataSourceTest, deleteById6OptionsMultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteById6Options();
}

/// @brief Tests that multiple reservations without IPv4 addresses can be
/// specified within a subnet.
TEST_F(MySqlHostDataSourceTest, testMultipleHostsNoAddress4) {
    testMultipleHostsNoAddress4();
}

/// @brief Tests that multiple reservations without IPv4 addresses can be
/// specified within a subnet.
TEST_F(MySqlHostDataSourceTest, testMultipleHostsNoAddress4MultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleHostsNoAddress4();
}

/// @brief Tests that multiple hosts can be specified within an IPv6 subnet.
TEST_F(MySqlHostDataSourceTest, testMultipleHosts6) {
    testMultipleHosts6();
}

/// @brief Tests that multiple hosts can be specified within an IPv6 subnet.
TEST_F(MySqlHostDataSourceTest, testMultipleHosts6MultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleHosts6();
}

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

    // Ensure we have the proper schema with no transient data.
    db::test::createMySQLSchema();

    // Connect to the database
    try {
        HostMgr::addBackend(db::test::validMySQLConnectionString());
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
    try {
        HostMgr::instance().getHostDataSource()->rollback();
    } catch(...) {
        // we don't care if we aren't in a transaction.
    }

    HostMgr::delBackend("mysql");
    // If data wipe enabled, delete transient data otherwise destroy the schema
    db::test::destroyMySQLSchema();
}

/// @brief Test fixture class for validating @c HostMgr using
/// MySQL as alternate host data source and MySQL connectivity loss.
class MySQLHostMgrDbLostCallbackTest : public HostMgrDbLostCallbackTest {
public:
    virtual void destroySchema() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
        db::test::destroyMySQLSchema();
    }

    virtual void createSchema() {
        // Ensure we have the proper schema with no transient data.
        db::test::createMySQLSchema();
    }

    virtual std::string validConnectString() {
        return (db::test::validMySQLConnectionString());
    }

    virtual std::string invalidConnectString() {
        return (connectionString(MYSQL_VALID_TYPE, INVALID_NAME, VALID_HOST,
                                 VALID_USER, VALID_PASSWORD));
    }
};

// This test verifies that reservations for a particular client can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll4BySubnet) {
    testGetAll4BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAll6BySubnet) {
    testGetAll6BySubnet(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that HostMgr returns all reservations for the specified
// IPv4 subnet and reserved address.
TEST_F(MySQLHostMgrTest, getAll4BySubnetIP) {
    testGetAll4BySubnetIP(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the specified
// IPv6 subnet and reserved address.
TEST_F(MySQLHostMgrTest, getAll6BySubnetIP) {
    testGetAll6BySubnetIP(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that reservations for a particular hostname can be
// retrieved from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getAllbyHostname) {
    testGetAllbyHostname(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular hostname and
// DHCPv4 subnet can be retrieved from the configuration file and a
// database simultaneously.
TEST_F(MySQLHostMgrTest, getAllbyHostnameSubnet4) {
    testGetAllbyHostnameSubnet4(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular hostname and
// DHCPv6 subnet can be retrieved from the configuration file and a
// database simultaneously.
TEST_F(MySQLHostMgrTest, getAllbyHostnameSubnet6) {
    testGetAllbyHostnameSubnet6(*getCfgHosts(), HostMgr::instance());
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
TEST_F(MySQLHostMgrTest, getPage4) {
    testGetPage4(true);
}

// This test verifies that all v4 reservations be retrieved by pages
// from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getPage4All) {
    testGetPage4All(true);
}

// This test verifies that reservations for a particular subnet can
// be retrieved by pages from the configuration file and a database
// simultaneously.
TEST_F(MySQLHostMgrTest, getPage6) {
    testGetPage6(true);
}

// This test verifies that all v6 reservations be retrieved by pages
// from the configuration file and a database simultaneously.
TEST_F(MySQLHostMgrTest, getPage6All) {
    testGetPage6All(true);
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

// This test verifies that it is possible to control whether the reserved
// IP addresses are unique or non unique via the HostMgr.
TEST_F(MySQLHostMgrTest, setIPReservationsUnique) {
    EXPECT_TRUE(HostMgr::instance().setIPReservationsUnique(true));
    EXPECT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(MySQLHostMgrDbLostCallbackTest, testNoCallbackOnOpenFailure) {
    MultiThreadingTest mt(false);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that db lost callback is not invoked on an open failure
TEST_F(MySQLHostMgrDbLostCallbackTest, testNoCallbackOnOpenFailureMultiThreading) {
    MultiThreadingTest mt(true);
    testNoCallbackOnOpenFailure();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndRecoveredCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndRecoveredCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndFailedCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndFailedCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndRecoveredAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndRecoveredAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallback) {
    MultiThreadingTest mt(false);
    testDbLostAndFailedAfterTimeoutCallback();
}

/// @brief Verifies that loss of connectivity to MySQL is handled correctly.
TEST_F(MySQLHostMgrDbLostCallbackTest, testDbLostAndFailedAfterTimeoutCallbackMultiThreading) {
    MultiThreadingTest mt(true);
    testDbLostAndFailedAfterTimeoutCallback();
}

}  // namespace
