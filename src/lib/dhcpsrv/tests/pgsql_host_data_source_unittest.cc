// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/tests/test_utils.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/pgsql_host_data_source.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <pgsql/pgsql_connection.h>
#include <pgsql/testutils/pgsql_schema.h>

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
using namespace std;

namespace {

class PgSqlHostDataSourceTest : public GenericHostDataSourceTest {
public:
    /// @brief Clears the database and opens connection to it.
    void initializeTest() {
        // Ensure we have the proper schema with no transient data.
        createPgSQLSchema();

        // Connect to the database
        try {
            HostMgr::create();
            HostMgr::addBackend(validPgSQLConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the PostgreSQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        hdsptr_ = HostMgr::instance().getHostDataSource();
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
        destroyPgSQLSchema();
    }

    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    PgSqlHostDataSourceTest() {
        initializeTest();
    }

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of hdsptr_ will close
    /// the database.  Then reopen it and delete everything created by the test.
    virtual ~PgSqlHostDataSourceTest() {
        destroyTest();
    }

    /// @brief Reopen the database
    ///
    /// Closes the database and re-open it.  Anything committed should be
    /// visible.
    ///
    /// Parameter is ignored for PostgreSQL backend as the v4 and v6 hosts share
    /// the same database.
    void reopen(Universe) {
        HostMgr::create();
        HostMgr::addBackend(validPgSQLConnectionString());
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

        PgSqlConnection::ParameterMap params;
        params["name"] = "keatest";
        params["user"] = "keatest";
        params["password"] = "keatest";

        PgSqlConnection conn(params);
        conn.openDatabase();

        PgSqlResult r(PQexec(conn, query.c_str()));
        if (PQresultStatus(r) != PGRES_TUPLES_OK) {
            isc_throw(DbOperationError, "Query failed:" << PQerrorMessage(conn));
        }

        int numrows = PQntuples(r);

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
/// This test checks if the PgSqlHostDataSource can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// PgSqlHostMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(PgSqlHostDataSource, OpenDatabase) {

    // Schema needs to be created for the test to work.
    destroyPgSQLSchema();
    createPgSQLSchema();

    // Check that host manager open the database opens correctly and tidy up.
    //  If it fails, print the error message.
    try {
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(validPgSQLConnectionString()));
        HostMgr::delBackend("postgresql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the PostgreSQL tests will run correctly.\n";
    }

    // Check that host manager open the database opens correctly with a longer
    // timeout.  If it fails, print the error message.
    try {
        string connection_string = validPgSQLConnectionString() + string(" ") +
                                   string(VALID_TIMEOUT);
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(connection_string));
        HostMgr::delBackend("postgresql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the PostgreSQL tests will run correctly.\n";
    }

    // Check that attempting to get an instance of the host data source when
    // none is set throws an exception.
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
        PGSQL_VALID_TYPE, INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        PGSQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        PGSQL_VALID_TYPE, VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        PGSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)),
        DbOpenError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        PGSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_1)),
        DbInvalidTimeout);
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        PGSQL_VALID_TYPE, VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_2)),
        DbInvalidTimeout);

    // Check for missing parameters
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        PGSQL_VALID_TYPE, NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)),
        NoDatabaseName);

    // Tidy up after the test
    destroyPgSQLSchema();
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
TEST(PgSqlHostDataSource, NoCallbackOnOpenFail) {
    // Schema needs to be created for the test to work.
    destroyPgSQLSchema();
    createPgSQLSchema();

    callback_called = false;
    DatabaseConnection::db_lost_callback = db_lost_callback;
    HostMgr::create();
    EXPECT_THROW(HostMgr::addBackend(connectionString(
        PGSQL_VALID_TYPE, VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)),
                 DbOpenError);

    EXPECT_FALSE(callback_called);
    destroyPgSQLSchema();
}

// This test verifies that database backend can operate in Read-Only mode.
TEST_F(PgSqlHostDataSourceTest, testReadOnlyDatabase) {
    testReadOnlyDatabase(PGSQL_VALID_TYPE);
}

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses hw address as identifier.
TEST_F(PgSqlHostDataSourceTest, basic4HWAddr) {
    testBasic4(Host::IDENT_HWADDR);
}

// Verifies that IPv4 host reservation with options can have a the global
// subnet id value
TEST_F(PgSqlHostDataSourceTest, globalSubnetId4) {
    testGlobalSubnetId4();
}

// Verifies that IPv6 host reservation with options can have a the global
// subnet id value
TEST_F(PgSqlHostDataSourceTest, globalSubnetId6) {
    testGlobalSubnetId6();
}

// Verifies that IPv4 host reservation with options can have a max value
// for  dhcp4_subnet id
TEST_F(PgSqlHostDataSourceTest, maxSubnetId4) {
    testMaxSubnetId4();
}

// Verifies that IPv6 host reservation with options can have a max value
// for  dhcp6_subnet id
TEST_F(PgSqlHostDataSourceTest, maxSubnetId6) {
    testMaxSubnetId6();
}

// Verifies that IPv4 host reservations in the same subnet can be retrieved
TEST_F(PgSqlHostDataSourceTest, getAll4BySubnet) {
    testGetAll4();
}

// Verifies that IPv6 host reservations in the same subnet can be retrieved
TEST_F(PgSqlHostDataSourceTest, getAll6BySubnet) {
    testGetAll6();
}

// Verifies that IPv4 host reservations in the same subnet can be retrieved
// by pages.
TEST_F(PgSqlHostDataSourceTest, getPage4) {
    testGetPage4();
}

// Verifies that IPv6 host reservations in the same subnet can be retrieved
// by pages.
TEST_F(PgSqlHostDataSourceTest, getPage6) {
    testGetPage6();
}

// Verifies that IPv4 host reservations in the same subnet can be retrieved
// by pages without truncation from the limit.
TEST_F(PgSqlHostDataSourceTest, getPageLimit4) {
    testGetPageLimit4(Host::IDENT_DUID);
}

// Verifies that IPv6 host reservations in the same subnet can be retrieved
// by pages without truncation from the limit.
TEST_F(PgSqlHostDataSourceTest, getPageLimit6) {
    testGetPageLimit6(Host::IDENT_HWADDR);
}

// Verifies that IPv4 host reservations in the same subnet can be retrieved
// by pages even with multiple subnets.
TEST_F(PgSqlHostDataSourceTest, getPage4Subnets) {
    testGetPage4Subnets();
}

// Verifies that IPv6 host reservations in the same subnet can be retrieved
// by pages even with multiple subnets.
TEST_F(PgSqlHostDataSourceTest, getPage6Subnets) {
    testGetPage6Subnets();
}

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses client-id (DUID) as identifier.
TEST_F(PgSqlHostDataSourceTest, basic4ClientId) {
    testBasic4(Host::IDENT_DUID);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses HW addresses as identifiers.
TEST_F(PgSqlHostDataSourceTest, getByIPv4HWaddr) {
    testGetByIPv4(Host::IDENT_HWADDR);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses client-id (DUID) as identifiers.
TEST_F(PgSqlHostDataSourceTest, getByIPv4ClientId) {
    testGetByIPv4(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(PgSqlHostDataSourceTest, get4ByHWaddr) {
    testGet4ByIdentifier(Host::IDENT_HWADDR);
}

// Test verifies if a host reservation can be added and later retrieved by
// DUID.
TEST_F(PgSqlHostDataSourceTest, get4ByDUID) {
    testGet4ByIdentifier(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// circuit id.
TEST_F(PgSqlHostDataSourceTest, get4ByCircuitId) {
    testGet4ByIdentifier(Host::IDENT_CIRCUIT_ID);
}

// Test verifies if a host reservation can be added and later retrieved by
// client-id.
TEST_F(PgSqlHostDataSourceTest, get4ByClientId) {
    testGet4ByIdentifier(Host::IDENT_CLIENT_ID);
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(PgSqlHostDataSourceTest, hwaddrNotClientId1) {
    testHWAddrNotClientId();
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(PgSqlHostDataSourceTest, hwaddrNotClientId2) {
    testClientIdNotHWAddr();
}

// Test verifies if a host with FQDN hostname can be stored and later retrieved.
TEST_F(PgSqlHostDataSourceTest, hostnameFQDN) {
    testHostname("foo.example.org", 1);
}

// Test verifies if 100 hosts with unique FQDN hostnames can be stored and later
// retrieved.
TEST_F(PgSqlHostDataSourceTest, hostnameFQDN100) {
    testHostname("foo.example.org", 100);
}

// Test verifies if a host without any hostname specified can be stored and later
// retrieved.
TEST_F(PgSqlHostDataSourceTest, noHostname) {
    testHostname("", 1);
}

// Test verifies if a host with user context can be stored and later retrieved.
TEST_F(PgSqlHostDataSourceTest, usercontext) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testUserContext(Element::fromJSON(comment));
}

// Test verifies if the hardware or client-id query can match hardware address.
TEST_F(PgSqlHostDataSourceTest, DISABLED_hwaddrOrClientId1) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with hardware address X, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

// Test verifies if the hardware or client-id query can match client-id.
TEST_F(PgSqlHostDataSourceTest, DISABLED_hwaddrOrClientId2) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with client identifier Y, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

// Test verifies that host with IPv6 address and DUID can be added and
// later retrieved by IPv6 address.
TEST_F(PgSqlHostDataSourceTest, get6AddrWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, false);
}

// Test verifies that host with IPv6 address and HWAddr can be added and
// later retrieved by IPv6 address.
TEST_F(PgSqlHostDataSourceTest, get6AddrWithHWAddr) {
    testGetByIPv6(Host::IDENT_HWADDR, false);
}

// Test verifies that host with IPv6 prefix and DUID can be added and
// later retrieved by IPv6 prefix.
TEST_F(PgSqlHostDataSourceTest, get6PrefixWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, true);
}

// Test verifies that host with IPv6 prefix and HWAddr can be added and
// later retrieved by IPv6 prefix.
TEST_F(PgSqlHostDataSourceTest, get6PrefixWithHWaddr) {
    testGetByIPv6(Host::IDENT_HWADDR, true);
}

// Test verifies that host with IPv6 prefix reservation can be retrieved
// by subnet id and prefix value.
TEST_F(PgSqlHostDataSourceTest, get6SubnetPrefix) {
    testGetBySubnetIPv6();
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(PgSqlHostDataSourceTest, get6ByHWaddr) {
    testGet6ByHWAddr();
}

// Test verifies if a host reservation can be added and later retrieved by
// client identifier.
TEST_F(PgSqlHostDataSourceTest, get6ByClientId) {
    testGet6ByClientId();
}

// Test verifies if a host reservation can be stored with both IPv6 address and
// prefix.
TEST_F(PgSqlHostDataSourceTest, addr6AndPrefix) {
    testAddr6AndPrefix();
}

// Tests if host with multiple IPv6 reservations can be added and then
// retrieved correctly. Test checks reservations comparing.
TEST_F(PgSqlHostDataSourceTest, multipleReservations){
    testMultipleReservations();
}

// Tests if compareIPv6Reservations() method treats same pool of reservations
// but added in different order as equal.
TEST_F(PgSqlHostDataSourceTest, multipleReservationsDifferentOrder){
    testMultipleReservationsDifferentOrder();
}

// Test that multiple client classes for IPv4 can be inserted and
// retrieved for a given host reservation.
TEST_F(PgSqlHostDataSourceTest, multipleClientClasses4) {
    testMultipleClientClasses4();
}

// Test that multiple client classes for IPv6 can be inserted and
// retrieved for a given host reservation.
TEST_F(PgSqlHostDataSourceTest, multipleClientClasses6) {
    testMultipleClientClasses6();
}

// Test that multiple client classes for both IPv4 and IPv6 can
// be inserted and retrieved for a given host reservation.
TEST_F(PgSqlHostDataSourceTest, multipleClientClassesBoth) {
    testMultipleClientClassesBoth();
}

// Test if the same host can have reservations in different subnets (with the
// same hardware address). The test logic is as follows:
// Insert 10 host reservations for a given physical host (the same
// hardware address), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them all correctly.
TEST_F(PgSqlHostDataSourceTest, multipleSubnetsHWAddr) {
    testMultipleSubnets(10, Host::IDENT_HWADDR);
}

// Test if the same host can have reservations in different subnets (with the
// same client identifier). The test logic is as follows:
//
// Insert 10 host reservations for a given physical host (the same
// client-identifier), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them correctly.
TEST_F(PgSqlHostDataSourceTest, multipleSubnetsClientId) {
    testMultipleSubnets(10, Host::IDENT_DUID);
}

// Test if host reservations made for different IPv6 subnets are handled correctly.
// The test logic is as follows:
//
// Insert 10 host reservations for different subnets. Make sure that
// get6(subnet-id, ...) calls return correct reservation.
TEST_F(PgSqlHostDataSourceTest, subnetId6) {
    testSubnetId6(10, Host::IDENT_HWADDR);
}

// Test if the duplicate host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
// Hosts with same DUID.
TEST_F(PgSqlHostDataSourceTest, addDuplicate6WithDUID) {
    testAddDuplicate6WithSameDUID();
}

// Test if the duplicate host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
// Hosts with same HWAddr.
TEST_F(PgSqlHostDataSourceTest, addDuplicate6WithHWAddr) {
    testAddDuplicate6WithSameHWAddr();
}

// Test if the duplicate IPv4 host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
TEST_F(PgSqlHostDataSourceTest, addDuplicate4) {
    testAddDuplicate4();
}

// This test verifies that DHCPv4 options can be inserted in a binary format
/// and retrieved from the PostgreSQL host database.
TEST_F(PgSqlHostDataSourceTest, optionsReservations4) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(false, Element::fromJSON(comment));
}

// This test verifies that DHCPv6 options can be inserted in a binary format
/// and retrieved from the PostgreSQL host database.
TEST_F(PgSqlHostDataSourceTest, optionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(false, Element::fromJSON(comment));
}

// This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
/// binary format and retrieved with a single query to the database.
TEST_F(PgSqlHostDataSourceTest, optionsReservations46) {
    testOptionsReservations46(false);
}

// This test verifies that DHCPv4 options can be inserted in a textual format
/// and retrieved from the PostgreSQL host database.
TEST_F(PgSqlHostDataSourceTest, formattedOptionsReservations4) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(true, Element::fromJSON(comment));
}

// This test verifies that DHCPv6 options can be inserted in a textual format
/// and retrieved from the PostgreSQL host database.
TEST_F(PgSqlHostDataSourceTest, formattedOptionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(true, Element::fromJSON(comment));
}

// This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
// textual format and retrieved with a single query to the database.
TEST_F(PgSqlHostDataSourceTest, formattedOptionsReservations46) {
    testOptionsReservations46(true);
}

// This test checks transactional insertion of the host information
// into the database. The failure to insert host information at
// any stage should cause the whole transaction to be rolled back.
TEST_F(PgSqlHostDataSourceTest, testAddRollback) {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // To test the transaction rollback mechanism we need to cause the
    // insertion of host information to fail at some stage. The 'hosts'
    // table should be updated correctly but the failure should occur
    // when inserting reservations or options. The simplest way to
    // achieve that is to simply drop one of the tables. To do so, we
    // connect to the database and issue a DROP query.
    PgSqlConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";
    PgSqlConnection conn(params);
    ASSERT_NO_THROW(conn.openDatabase());

    PgSqlResult r(PQexec(conn, "DROP TABLE IF EXISTS ipv6_reservations"));
    ASSERT_TRUE (PQresultStatus(r) == PGRES_COMMAND_OK)
                 << " drop command failed :" << PQerrorMessage(conn);

    // Create a host with a reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::1",
                                        Host::IDENT_HWADDR, false, "randomKey");
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

// This test checks that siaddr, sname, file fields can be retrieved
/// from a database for a host.
TEST_F(PgSqlHostDataSourceTest, messageFields) {
    testMessageFields4();
}

// Check that delete(subnet-id, addr4) works.
TEST_F(PgSqlHostDataSourceTest, deleteByAddr4) {
    testDeleteByAddr4();
}

// Check that delete(subnet4-id, identifier-type, identifier) works.
TEST_F(PgSqlHostDataSourceTest, deleteById4) {
    testDeleteById4();
}

// Check that delete(subnet4-id, identifier-type, identifier) works,
// even when options are present.
TEST_F(PgSqlHostDataSourceTest, deleteById4Options) {
    testDeleteById4Options();
}

// Check that delete(subnet6-id, identifier-type, identifier) works.
TEST_F(PgSqlHostDataSourceTest, deleteById6) {
    testDeleteById6();
}

// Check that delete(subnet6-id, identifier-type, identifier) works,
// even when options are present.
TEST_F(PgSqlHostDataSourceTest, deleteById6Options) {
    testDeleteById6Options();
}

// Tests that multiple reservations without IPv4 addresses can be
// specified within a subnet.
TEST_F(PgSqlHostDataSourceTest, testMultipleHostsNoAddress4) {
    testMultipleHostsNoAddress4();
}

// Tests that multiple hosts can be specified within an IPv6 subnet.
TEST_F(PgSqlHostDataSourceTest, testMultipleHosts6) {
    testMultipleHosts6();
}

}  // namespace
