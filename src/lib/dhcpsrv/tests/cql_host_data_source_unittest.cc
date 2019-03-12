// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2016-2017 Deutsche Telekom AG.
//
// Author: Andrei Pavel <andrei.pavel@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <cql/cql_connection.h>
#include <cql/testutils/cql_schema.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/cql_lease_mgr.h>
#include <dhcpsrv/cql_host_data_source.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/tests/test_utils.h>

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

class CqlHostDataSourceTest : public GenericHostDataSourceTest {
public:
    /// @brief Clears the database and opens connection to it.
    void initializeTest() {
        // Ensure we have the proper schema with no transient data.
        createCqlSchema();

        // Connect to the database
        try {
            HostMgr::create();
            HostMgr::addBackend(validCqlConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the CQL tests will run correctly.\n"
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
            // Rollback should never fail, as Cassandra doesn't support transactions
            // (commit and rollback are both no-op).
        }
        HostMgr::delAllBackends();
        hdsptr_.reset();
        // If data wipe enabled, delete transient data otherwise destroy the schema
        destroyCqlSchema();
    }

    /// @brief Constructor
    ///
    /// Deletes everything from the database and opens it.
    CqlHostDataSourceTest() {
        initializeTest();
    }

    /// @brief Destructor
    ///
    /// Rolls back all pending transactions.  The deletion of hdsptr_ will close
    /// the database.  Then reopen it and delete everything created by the test.
    virtual ~CqlHostDataSourceTest() {
        destroyTest();
    }

    /// @brief Reopen the database
    ///
    /// Closes the database and re-open it.  Anything committed should be
    /// visible.
    ///
    /// Parameter is ignored for CQL backend as the v4 and v6 hosts share
    /// the same database.
    void reopen(Universe) {
        HostMgr::create();
        HostMgr::addBackend(validCqlConnectionString());
        hdsptr_ = HostMgr::instance().getHostDataSource();
    }

    /// @brief Returns number of IPv4 options currently stored in DB.
    virtual int countDBOptions4() {
        int result = 0;

        const CqlHostDataSource* cql_host_mgr = dynamic_cast<const CqlHostDataSource*>(&(*hdsptr_));
        ConstHostCollection all = cql_host_mgr->getAllHosts();

        for (ConstHostCollection::const_iterator it = all.begin();
             it != all.end(); ++it) {
            ConstCfgOptionPtr cfg_option4 = (*it)->getCfgOption4();
            std::list<std::string> option_spaces4 = cfg_option4->getOptionSpaceNames();
            std::list<std::string> vendor_spaces4 = cfg_option4->getVendorIdsSpaceNames();
            option_spaces4.insert(option_spaces4.end(), vendor_spaces4.begin(),
                                  vendor_spaces4.end());
            for (const std::string& space : option_spaces4) {
                OptionContainerPtr options = cfg_option4->getAll(space);
                result += options->size();
            }
        }

        return (result);
    }

    /// @brief Returns number of IPv6 options currently stored in DB.
    virtual int countDBOptions6() {
        int result = 0;

        const CqlHostDataSource* cql_host_mgr = dynamic_cast<const CqlHostDataSource*>(&(*hdsptr_));
        ConstHostCollection all = cql_host_mgr->getAllHosts();

        for (ConstHostCollection::const_iterator it = all.begin();
             it != all.end(); ++it) {
            ConstCfgOptionPtr cfg_option6 = (*it)->getCfgOption6();
            std::list<std::string> option_spaces6 = cfg_option6->getOptionSpaceNames();
            std::list<std::string> vendor_spaces6 = cfg_option6->getVendorIdsSpaceNames();
            option_spaces6.insert(option_spaces6.end(), vendor_spaces6.begin(),
                                  vendor_spaces6.end());
            for (const std::string& space : option_spaces6) {
                OptionContainerPtr options = cfg_option6->getAll(space);
                result += options->size();
            }
        }

        return (result);
    }

    /// @brief Returns number of IPv6 reservations currently stored in DB.
    virtual int countDBReservations6() {
        int result = 0;

        const CqlHostDataSource* cql_host_mgr = dynamic_cast<const CqlHostDataSource*>(&(*hdsptr_));
        ConstHostCollection all = cql_host_mgr->getAllHosts();

        for (ConstHostCollection::const_iterator it = all.begin();
             it != all.end(); ++it) {
            IPv6ResrvRange reservations = (*it)->getIPv6Reservations();
                result += std::distance(reservations.first, reservations.second);
        }

        return (result);
    }

};

/// @brief Check that database can be opened
///
/// This test checks if the CqlHostDataSource can be instantiated.  This happens
/// only if the database can be opened.  Note that this is not part of the
/// CqlHostMgr test fixure set.  This test checks that the database can be
/// opened: the fixtures assume that and check basic operations.

TEST(CqlHostDataSource, OpenDatabase) {

    // Ensure we have the proper schema with no transient data.
    createCqlSchema();

    // Check that host manager open the database opens correctly and tidy up.
    //  If it fails, print the error message.
    try {
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(validCqlConnectionString()));
        HostMgr::delBackend("cql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the CQL tests will run correctly.\n";
    }

    // Check that host manager open the database opens correctly with a longer
    // timeout.  If it fails, print the error message.
    try {
        // CQL specifies the timeout values in ms, not seconds. Therefore
        // we need to add extra 000 to the "connect-timeout=10" string.
        string connection_string = validCqlConnectionString() + string(" ") +
            string(VALID_TIMEOUT) + string("000");
        HostMgr::create();
        EXPECT_NO_THROW(HostMgr::addBackend(connection_string));
        HostMgr::delBackend("cql");
    } catch (const isc::Exception& ex) {
        FAIL() << "*** ERROR: unable to open database, reason:\n"
               << "    " << ex.what() << "\n"
               << "*** The test environment is broken and must be fixed\n"
               << "*** before the CQL tests will run correctly.\n";
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

    // Check that invalid login data does not cause an exception, CQL should use
    // default values.
    EXPECT_NO_THROW(HostMgr::addBackend(connectionString(CQL_VALID_TYPE,
                    INVALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD)));
    EXPECT_NO_THROW(HostMgr::addBackend(connectionString(CQL_VALID_TYPE,
                    VALID_NAME, INVALID_HOST, VALID_USER, VALID_PASSWORD)));
    EXPECT_NO_THROW(HostMgr::addBackend(connectionString(CQL_VALID_TYPE,
                    VALID_NAME, VALID_HOST, INVALID_USER, VALID_PASSWORD)));
    EXPECT_NO_THROW(HostMgr::addBackend(connectionString(CQL_VALID_TYPE,
                    VALID_NAME, VALID_HOST, VALID_USER, INVALID_PASSWORD)));

    // Check that invalid timeouts throw DbOperationError.
    EXPECT_THROW(HostMgr::addBackend(connectionString(CQL_VALID_TYPE,
                 VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_1)),
                 DbOperationError);
    EXPECT_THROW(HostMgr::addBackend(connectionString(CQL_VALID_TYPE,
                 VALID_NAME, VALID_HOST, VALID_USER, VALID_PASSWORD, INVALID_TIMEOUT_2)),
                 DbOperationError);

    // Check that CQL allows the hostname to not be specified.
    EXPECT_NO_THROW(HostMgr::addBackend(connectionString(CQL_VALID_TYPE,
                    NULL, VALID_HOST, INVALID_USER, VALID_PASSWORD)));

    // Tidy up after the test
    destroyCqlSchema();
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
/// data is entered into the database correctly, only that the CQL_TIME
/// structure used for the entry is correctly set up.
TEST(CqlConnection, checkTimeConversion) {
    const time_t cltt = time(NULL);
    const uint32_t valid_lft = 86400;  // 1 day
    cass_int64_t cql_expire;

    // Convert to the database time
    CqlExchange::convertToDatabaseTime(cltt, valid_lft, cql_expire);

    // Convert back
    time_t converted_cltt = 0;
    CqlExchange::convertFromDatabaseTime(cql_expire, valid_lft, converted_cltt);
    EXPECT_EQ(cltt, converted_cltt);
}

// This test verifies that database backend can operate in Read-Only mode.
// We currently don't test Cassandra in read-only mode.
TEST_F(CqlHostDataSourceTest, DISABLED_testReadOnlyDatabase) {
    testReadOnlyDatabase(CQL_VALID_TYPE);
}

// Verifies that IPv4 host reservations in the same subnet can be retrieved
TEST_F(CqlHostDataSourceTest, getAll4BySubnet) {
    testGetAll4();
}

// Verifies that IPv6 host reservations in the same subnet can be retrieved
TEST_F(CqlHostDataSourceTest, getAll6BySubnet) {
    testGetAll6();
}

// Verifies that IPv4 host reservations in the same subnet can be retrieved
// by pages.
// Does not work because TOKEN(id) order is not the same than id...
TEST_F(CqlHostDataSourceTest, DISABLED_getPage4) {
    testGetPage4();
}

// Verifies that IPv6 host reservations in the same subnet can be retrieved
// by pages.
TEST_F(CqlHostDataSourceTest, DISABLED_getPage6) {
    testGetPage6();
}

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses hw address as identifier.
TEST_F(CqlHostDataSourceTest, basic4HWAddr) {
    testBasic4(Host::IDENT_HWADDR);
}

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses client-id (DUID) as identifier.
TEST_F(CqlHostDataSourceTest, basic4ClientId) {
    testBasic4(Host::IDENT_DUID);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses HW addresses as identifiers.
TEST_F(CqlHostDataSourceTest, getByIPv4HWaddr) {
    testGetByIPv4(Host::IDENT_HWADDR);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses client-id (DUID) as identifiers.
TEST_F(CqlHostDataSourceTest, getByIPv4ClientId) {
    testGetByIPv4(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(CqlHostDataSourceTest, get4ByHWaddr) {
    testGet4ByIdentifier(Host::IDENT_HWADDR);
}

// Test verifies if a host reservation can be added and later retrieved by
// DUID.
TEST_F(CqlHostDataSourceTest, get4ByDUID) {
    testGet4ByIdentifier(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// circuit id.
TEST_F(CqlHostDataSourceTest, get4ByCircuitId) {
    testGet4ByIdentifier(Host::IDENT_CIRCUIT_ID);
}

// Test verifies if a host reservation can be added and later retrieved by
// client-id.
TEST_F(CqlHostDataSourceTest, get4ByClientId) {
    testGet4ByIdentifier(Host::IDENT_CLIENT_ID);
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(CqlHostDataSourceTest, hwaddrNotClientId1) {
    testHWAddrNotClientId();
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(CqlHostDataSourceTest, hwaddrNotClientId2) {
    testClientIdNotHWAddr();
}

// Test verifies if a host with FQDN hostname can be stored and later retrieved.
TEST_F(CqlHostDataSourceTest, hostnameFQDN) {
    testHostname("foo.example.org", 1);
}

// Test verifies if 100 hosts with unique FQDN hostnames can be stored and later
// retrieved.
TEST_F(CqlHostDataSourceTest, hostnameFQDN100) {
    testHostname("foo.example.org", 100);
}

// Test verifies if a host without any hostname specified can be stored and later
// retrieved.
TEST_F(CqlHostDataSourceTest, noHostname) {
    testHostname("", 1);
}

// Test verifies if a host with user context can be stored and later retrieved.
TEST_F(CqlHostDataSourceTest, usercontext) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testUserContext(Element::fromJSON(comment));
}

// Test verifies if the hardware or client-id query can match hardware address.
TEST_F(CqlHostDataSourceTest, DISABLED_hwaddrOrClientId1) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with hardware address X, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

// Test verifies if the hardware or client-id query can match client-id.
TEST_F(CqlHostDataSourceTest, DISABLED_hwaddrOrClientId2) {
    /// @todo: The logic behind ::get4(subnet_id, hwaddr, duid) call needs to
    /// be discussed.
    ///
    /// @todo: Add host reservation with client identifier Y, try to retrieve
    /// host for hardware address X or client identifier Y, verify that the
    /// reservation is returned.
}

// Test verifies that host with IPv6 address and DUID can be added and
// later retrieved by IPv6 address.
TEST_F(CqlHostDataSourceTest, get6AddrWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, false);
}

// Test verifies that host with IPv6 address and HWAddr can be added and
// later retrieved by IPv6 address.
TEST_F(CqlHostDataSourceTest, get6AddrWithHWAddr) {
    testGetByIPv6(Host::IDENT_HWADDR, false);
}

// Test verifies that host with IPv6 prefix and DUID can be added and
// later retrieved by IPv6 prefix.
TEST_F(CqlHostDataSourceTest, get6PrefixWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, true);
}

// Test verifies that host with IPv6 prefix and HWAddr can be added and
// later retrieved by IPv6 prefix.
TEST_F(CqlHostDataSourceTest, get6PrefixWithHWaddr) {
    testGetByIPv6(Host::IDENT_HWADDR, true);
}

// Test verifies that host with IPv6 prefix reservation can be retrieved
// by subnet id and prefix value.
TEST_F(CqlHostDataSourceTest, get6SubnetPrefix) {
    testGetBySubnetIPv6();
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(CqlHostDataSourceTest, get6ByHWaddr) {
    testGet6ByHWAddr();
}

// Test verifies if a host reservation can be added and later retrieved by
// client identifier.
TEST_F(CqlHostDataSourceTest, get6ByClientId) {
    testGet6ByClientId();
}

// Test verifies if a host reservation can be stored with both IPv6 address and
// prefix.
TEST_F(CqlHostDataSourceTest, addr6AndPrefix) {
    testAddr6AndPrefix();
}

// Tests if host with multiple IPv6 reservations can be added and then
// retrieved correctly. Test checks reservations comparing.
TEST_F(CqlHostDataSourceTest, multipleReservations) {
    testMultipleReservations();
}

// Tests if compareIPv6Reservations() method treats same pool of reservations
// but added in different order as equal.
TEST_F(CqlHostDataSourceTest, multipleReservationsDifferentOrder) {
    testMultipleReservationsDifferentOrder();
}

// Test that multiple client classes for IPv4 can be inserted and
// retrieved for a given host reservation.
TEST_F(CqlHostDataSourceTest, multipleClientClasses4) {
    testMultipleClientClasses4();
}

// Test that multiple client classes for IPv6 can be inserted and
// retrieved for a given host reservation.
TEST_F(CqlHostDataSourceTest, multipleClientClasses6) {
    testMultipleClientClasses6();
}

// Test that multiple client classes for both IPv4 and IPv6 can
// be inserted and retrieved for a given host reservation.
TEST_F(CqlHostDataSourceTest, multipleClientClassesBoth) {
    testMultipleClientClassesBoth();
}

// Test if the same host can have reservations in different subnets (with the
// same hardware address). The test logic is as follows:
// Insert 10 host reservations for a given physical host (the same
// hardware address), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them all correctly.
TEST_F(CqlHostDataSourceTest, multipleSubnetsHWAddr) {
    testMultipleSubnets(10, Host::IDENT_HWADDR);
}

// Test if the same host can have reservations in different subnets (with the
// same client identifier). The test logic is as follows:
//
// Insert 10 host reservations for a given physical host (the same
// client-identifier), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them correctly.
TEST_F(CqlHostDataSourceTest, multipleSubnetsClientId) {
    testMultipleSubnets(10, Host::IDENT_DUID);
}

// Test if host reservations made for different IPv6 subnets are handled correctly.
// The test logic is as follows:
//
// Insert 10 host reservations for different subnets. Make sure that
// get6(subnet-id, ...) calls return correct reservation.
TEST_F(CqlHostDataSourceTest, subnetId6) {
    testSubnetId6(10, Host::IDENT_HWADDR);
}

// Test if the duplicate host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
// Hosts with same DUID.
TEST_F(CqlHostDataSourceTest, addDuplicate6WithDUID) {
    testAddDuplicate6WithSameDUID();
}

// Test if the duplicate host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
// Hosts with same HWAddr.
TEST_F(CqlHostDataSourceTest, addDuplicate6WithHWAddr) {
    testAddDuplicate6WithSameHWAddr();
}

// Test if the duplicate IPv4 host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
TEST_F(CqlHostDataSourceTest, addDuplicate4) {
    testAddDuplicate4();
}

// This test verifies that DHCPv4 options can be inserted in a binary format
/// and retrieved from the CQL host database.
TEST_F(CqlHostDataSourceTest, optionsReservations4) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(false, Element::fromJSON(comment));
}

// This test verifies that DHCPv6 options can be inserted in a binary format
/// and retrieved from the CQL host database.
TEST_F(CqlHostDataSourceTest, optionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(false, Element::fromJSON(comment));
}

// This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
/// binary format and retrieved with a single query to the database.
TEST_F(CqlHostDataSourceTest, optionsReservations46) {
    testOptionsReservations46(false);
}

// This test verifies that DHCPv4 options can be inserted in a textual format
/// and retrieved from the CQL host database.
TEST_F(CqlHostDataSourceTest, formattedOptionsReservations4) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations4(true, Element::fromJSON(comment));
}

// This test verifies that DHCPv6 options can be inserted in a textual format
/// and retrieved from the CQL host database.
TEST_F(CqlHostDataSourceTest, formattedOptionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(true, Element::fromJSON(comment));
}

// This test verifies that DHCPv4 and DHCPv6 options can be inserted in a
// textual format and retrieved with a single query to the database.
TEST_F(CqlHostDataSourceTest, formattedOptionsReservations46) {
    testOptionsReservations46(true);
}

// This test checks transactional insertion of the host information
// into the database. The failure to insert host information at
// any stage should cause the whole transaction to be rolled back.
TEST_F(CqlHostDataSourceTest, testAddRollback) {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // To test the transaction rollback mechanism we need to cause the
    // insertion of host information to fail at some stage. The 'hosts'
    // table should be updated correctly but the failure should occur
    // when inserting reservations or options. The simplest way to
    // achieve that is to simply drop one of the tables. To do so, we
    // connect to the database and issue a DROP query.
    CqlConnection::ParameterMap params;
    params["name"] = "keatest";
    params["user"] = "keatest";
    params["password"] = "keatest";
    CqlConnection connection(params);
    ASSERT_NO_THROW(connection.openDatabase());

    // Drop every table so we make sure host_reservations doesn't exist anymore.
    destroyCqlSchema(false, true);

    // Create a host with a reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::1",
                                        Host::IDENT_HWADDR, false, "key##1");
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
    ASSERT_THROW(hdsptr_->get4(host->getIPv4SubnetID(),
                               host->getIdentifierType(),
                               &host->getIdentifier()[0],
                               host->getIdentifier().size()),
                               DbOperationError);
}

TEST_F(CqlHostDataSourceTest, DISABLED_stressTest) {
    // Run with 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4092, 8192,
    // 16384 & 32768 hosts.
    for (unsigned int i = 0X0001U; i < 0xfffdU; i <<= 1) {
        initializeTest();
        stressTest(i);
        destroyTest();
    }
}

// This test checks that siaddr, sname, file fields can be retrieved
/// from a database for a host.
TEST_F(CqlHostDataSourceTest, messageFields) {
    testMessageFields4();
}

// Check that delete(subnet-id, addr4) works.
TEST_F(CqlHostDataSourceTest, deleteByAddr4) {
    testDeleteByAddr4();
}

// Check that delete(subnet4-id, identifier-type, identifier) works.
TEST_F(CqlHostDataSourceTest, deleteById4) {
    testDeleteById4();
}

// Check that delete(subnet4-id, identifier-type, identifier) works,
// even when options are present.
TEST_F(CqlHostDataSourceTest, deleteById4Options) {
    testDeleteById4Options();
}

// Check that delete(subnet6-id, identifier-type, identifier) works.
TEST_F(CqlHostDataSourceTest, deleteById6) {
    testDeleteById6();
}

// Check that delete(subnet6-id, identifier-type, identifier) works,
// even when options are present.
TEST_F(CqlHostDataSourceTest, deleteById6Options) {
    testDeleteById6Options();
}

// Tests that multiple reservations without IPv4 addresses can be
// specified within a subnet.
TEST_F(CqlHostDataSourceTest, testMultipleHostsNoAddress4) {
    testMultipleHostsNoAddress4();
}

// Tests that multiple hosts can be specified within an IPv6 subnet.
TEST_F(CqlHostDataSourceTest, testMultipleHosts6) {
    testMultipleHosts6();
}

// Verifies that IPv4 host reservation with options can have a the global
// subnet id value
TEST_F(CqlHostDataSourceTest, globalSubnetId4) {
    testGlobalSubnetId4();
}

// Verifies that IPv6 host reservation with options can have a the global
// subnet id value
TEST_F(CqlHostDataSourceTest, globalSubnetId6) {
    testGlobalSubnetId6();
}

// Verifies that IPv4 host reservation with options can have a max value
// for  dhcp4_subnet id
TEST_F(CqlHostDataSourceTest, maxSubnetId4) {
    testMaxSubnetId4();
}

// Verifies that IPv6 host reservation with options can have a max value
// for  dhcp6_subnet id
TEST_F(CqlHostDataSourceTest, maxSubnetId6) {
    testMaxSubnetId6();
}



}  // namespace
