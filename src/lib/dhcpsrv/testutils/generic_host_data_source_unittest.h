// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_HOST_DATA_SOURCE_UNITTEST_H
#define GENERIC_HOST_DATA_SOURCE_UNITTEST_H

#include <asiolink/io_address.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <dhcp/classify.h>
#include <dhcp/option.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test Fixture class with utility functions for HostDataSource backends
///
/// It contains utility functions for test purposes.
/// All concrete HostDataSource test classes should be derived from it.
class GenericHostDataSourceTest : public GenericBackendTest {
public:

    /// @brief Universe (V4 or V6).
    enum Universe {
        V4,
        V6
    };

    /// @brief Options to be inserted into a host.
    ///
    /// Parameter of this type is passed to the @ref addTestOptions to
    /// control which option types should be inserted into a host.
    enum AddedOptions {
        DHCP4_ONLY,
        DHCP6_ONLY,
        DHCP4_AND_DHCP6
    };

    /// @brief Default constructor.
    GenericHostDataSourceTest();

    /// @brief Virtual destructor.
    virtual ~GenericHostDataSourceTest();

    /// @brief Used to sort a host collection by IPv4 subnet id.
    /// @param host1 first host to be compared
    /// @param host2 second host to be compared
    /// @result return true if host1's subnet id is smaller than host2's
    /// subnet id
    static bool compareHostsForSort4(const ConstHostPtr& host1,
                                     const ConstHostPtr& host2);

    /// @brief Used to sort a host collection by IPv6 subnet id.
    /// @param host1 first host to be compared
    /// @param host2 second host to be compared
    /// @result return true if host1's subnet id is smaller than host2's
    /// subnet id
    static bool compareHostsForSort6(const ConstHostPtr& host1,
                                     const ConstHostPtr& host2);

    /// @brief Used to sort a host collection by host identifier.
    /// @param host1 first host to be compared
    /// @param host2 second host to be compared
    /// @result return true if host1's identifier is smaller than host2's
    /// identifier
    static bool compareHostsIdentifier(const ConstHostPtr& host1,
                                       const ConstHostPtr& host2);

    /// @brief Returns number of entries in the v4 options table.
    ///
    /// This utility method is expected to be implemented by specific backends.
    /// The code here is just a boilerplate for backends that do not store
    /// host options in a table.
    ///
    /// @param number of existing entries in options table
    virtual int countDBOptions4() {
        return (-1);
    }

    /// @brief Returns number of entries in the v6 options table.
    ///
    /// This utility method is expected to be implemented by specific backends.
    /// The code here is just a boilerplate for backends that do not store
    /// host options in a table.
    ///
    /// @param number of existing entries in options table
    virtual int countDBOptions6() {
        return (-1);
    }

    /// @brief Returns number of entries in the v6 reservations table.
    ///
    /// This utility method is expected to be implemented by specific backends.
    /// The code here is just a boilerplate for backends that do not store
    /// v6 reservations in a table.
    ///
    /// @param number of existing entries in v6_reservations table
    virtual int countDBReservations6() {
        return (-1);
    }

    /// @brief Adds multiple options into the host.
    ///
    /// This method creates the following options into the host object:
    /// - DHCPv4 boot file name option,
    /// - DHCPv4 default ip ttl option,
    /// - DHCPv4 option 1 within vendor-encapsulated-options space,
    /// - DHCPv4 option 254 with a single IPv4 address,
    /// - DHCPv4 option 1 within isc option space,
    /// - DHCPv6 boot file url option,
    /// - DHCPv6 information refresh time option,
    /// - DHCPv6 vendor option with vendor id 2495,
    /// - DHCPv6 option 1024, with a single IPv6 address,
    /// - DHCPv6 empty option 1, within isc2 option space,
    /// - DHCPv6 option 2, within isc2 option space with 3 IPv6 addresses,
    ///
    /// This method also creates option definitions for the non-standard
    /// options and registers them in the LibDHCP as runtime option
    /// definitions.
    ///
    /// @param host Host object into which options should be added.
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param added_options Controls which options should be inserted into
    /// a host: DHCPv4, DHCPv6 options or both.
    /// @param user_context Optional user context
    void addTestOptions(const HostPtr& host, const bool formatted,
                        const AddedOptions& added_options,
                        isc::data::ConstElementPtr user_context =
                        isc::data::ConstElementPtr()) const;

    /// @brief Pointer to the host data source
    HostDataSourcePtr hdsptr_;

    /// @brief Test that backend can be started in read-only mode.
    ///
    /// Some backends can operate when the database is read only, e.g.
    /// host reservation tables are read only, or the database user has
    /// read only privileges on the entire database. In such cases, the
    /// Kea server administrator can specify in the backend configuration
    /// that the database should be opened in read only mode, i.e.
    /// INSERT, UPDATE, DELETE statements can't be issued. If any of the
    /// functions updating the database is called for the backend, the
    /// error is reported. The database running in read only mode can
    /// be merely used to retrieve existing host reservations from the
    /// database. This test verifies that this is the case.
    ///
    /// @param valid_db_type Parameter specifying type of backend to
    /// be used, e.g. type=mysql.
    void testReadOnlyDatabase(const char* valid_db_type);

    /// @brief Test that checks that simple host with IPv4 reservation
    ///        can be inserted and later retrieved.
    ///
    /// Uses gtest macros to report failures.
    /// @param id Identifier type.
    void testBasic4(const Host::IdentifierType& id);

    /// @brief Test that verifies that an IPv4 host reservation with
    /// options can have the global subnet id value.
    ///
    /// Uses gtest macros to report failures.
    void testGlobalSubnetId4();

    /// @brief Test that verifies that an IPv6 host reservation with
    /// options can have the global subnet id value.
    ///
    /// Uses gtest macros to report failures.
    void testGlobalSubnetId6();

    /// @brief Test that verifies that an IPv4 host reservation with
    /// options can have a max value for dhcp4_subnet id
    ///
    /// Uses gtest macros to report failures.
    void testMaxSubnetId4();

    /// @brief Test that Verifies that an IPv6 host reservation with
    /// options can have a max value for dhcp6_subnet id
    ///
    /// Uses gtest macros to report failures.
    void testMaxSubnetId6();

    /// @brief Test that Verifies that IPv4 host reservations in the
    /// same subnet can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    void testGetAll4();

    /// @brief Test that Verifies that IPv6 host reservations in the
    /// same subnet can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    void testGetAll6();

    /// @brief Test that Verifies that host reservations with the same
    /// hostname can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    void testGetAllbyHostname();

    /// @brief Test that Verifies that IPv4 host reservations with the same
    /// hostname and in the same subnet can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    void testGetAllbyHostnameSubnet4();

    /// @brief Test that Verifies that IPv6 host reservations with the same
    /// hostname and in the same subnet can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    void testGetAllbyHostnameSubnet6();

    /// @brief Test that Verifies that pages of host reservations in the
    /// same subnet can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    void testGetPage4();

    /// @brief Test that Verifies that pages of host reservations in the
    /// same subnet can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    void testGetPage6();

    /// @brief Test that Verifies that pages of complex host reservations
    /// are not truncated, i.e. the limit applies on the number of hosts
    /// and not on the number of rows.
    ///
    /// Uses gtest macros to report failures.
    /// @param id Identifier type (hwaddr or duid).
    void testGetPageLimit4(const Host::IdentifierType& id);

    /// @brief Test that Verifies that pages of complex host reservations
    /// are not truncated, i.e. the limit applies on the number of hosts
    /// and not on the number of rows.
    ///
    /// Uses gtest macros to report failures.
    /// @param id Identifier type (hwaddr or duid).
    void testGetPageLimit6(const Host::IdentifierType& id);

    /// @brief Test that Verifies that pages of host reservations in the
    /// same subnet can be retrieved properly even with multiple subnets.
    ///
    /// Uses gtest macros to report failures.
    void testGetPage4Subnets();

    /// @brief Test that Verifies that pages of host reservations in the
    /// same subnet can be retrieved properly even with multiple subnets.
    ///
    /// Uses gtest macros to report failures.
    void testGetPage6Subnets();

    /// @brief Test inserts several hosts with unique IPv4 address and
    ///        checks that they can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    /// @param id Identifier type.
    void testGetByIPv4(const Host::IdentifierType& id);

    /// @brief Test that hosts can be retrieved by host identifier.
    ///
    /// Uses gtest macros to report failures.
    void testGet4ByIdentifier(const Host::IdentifierType& identifier_type);

    /// @brief Test that clients with stored HW address can't be retrieved
    ///        by DUID with the same value.
    ///
    /// Test procedure: add host reservation with hardware address X, try to retrieve
    /// host by client-identifier X, verify that the reservation is not returned.
    ///
    /// Uses gtest macros to report failures.
    void testHWAddrNotClientId();

    /// @brief Test that clients with stored DUID can't be retrieved
    ///        by HW address of the same value.
    ///
    /// Test procedure: add host reservation with client identifier X, try to
    /// retrieve host by hardware address X, verify that the reservation is not
    /// returned.
    ///
    /// Uses gtest macros to report failures.
    void testClientIdNotHWAddr();

    /// @brief Test adds specified number of hosts with unique hostnames, then
    /// retrives them and checks that the hostnames are set properly.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param name hostname to be used (if n>1, numbers will be appended)
    /// @param num number of hostnames to be added.
    void testHostname(std::string name, int num);

    /// @brief Test insert and retrieve a host with user context.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param user_context The user context.
    void testUserContext(isc::data::ConstElementPtr user_context);

    /// @brief Test inserts multiple reservations for the same host for different
    /// subnets and check that they can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param subnets number of subnets to test
    /// @param id Host identifier type.
    void testMultipleSubnets(int subnets, const Host::IdentifierType& id);

    /// @brief Test inserts several hosts with unique IPv6 addresses and
    ///        checks that they can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    /// @param id type of the identifier to be used (IDENT_HWADDR or IDENT_DUID)
    /// @param prefix true - reserve IPv6 prefix, false - reserve IPv6 address
    void testGetByIPv6(Host::IdentifierType id, bool prefix);

    /// @brief Test inserts several hosts with unique prefixes and checks
    ///        that the can be retrieved by subnet id and prefix value.
    void testGetBySubnetIPv6();

    /// @brief Test that hosts can be retrieved by hardware address.
    ///
    /// Uses gtest macros to report failures.
    void testGet6ByHWAddr();

    /// @brief Test that hosts can be retrieved by client-id
    ///
    /// Uses gtest macros to report failures.
    void testGet6ByClientId();

    /// @brief Test verifies if a host reservation can be stored with both
    ///         IPv6 address and prefix.
    /// Uses gtest macros to report failures.
    void testAddr6AndPrefix();

    /// @brief Tests if host with multiple IPv6 reservations can be added and then
    ///        retrieved correctly.
    void testMultipleReservations();

    /// @brief Tests if compareIPv6Reservations() method treats same pool of
    ///        reservations but added in different order as equal.
    void testMultipleReservationsDifferentOrder();

    /// @brief Test if host reservations made for different IPv6 subnets
    ///        are handled correctly.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param subnets number of subnets to test
    /// @param id identifier type (IDENT_HWADDR or IDENT_DUID)
    void testSubnetId6(int subnets, Host::IdentifierType id);

    /// @brief Test if the duplicate host with same DUID can't be inserted.
    ///
    /// Uses gtest macros to report failures.
    void testAddDuplicate6WithSameDUID();

    /// @brief Test if the duplicate host with same HWAddr can't be inserted.
    ///
    /// Uses gtest macros to report failures.
    void testAddDuplicate6WithSameHWAddr();

    /// @brief Test if the duplicate IPv4 host with can't be inserted.
    ///
    /// Uses gtest macros to report failures.
    void testAddDuplicate4();

    /// @brief Test that DHCPv4 options can be inserted and retrieved from
    /// the database.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param formatted Boolean value indicating if the option values
    /// should be stored in the textual format in the database.
    /// @param user_context Optional user context.
    void testOptionsReservations4(const bool formatted,
                                  isc::data::ConstElementPtr user_context =
                                  isc::data::ConstElementPtr());

    /// @brief Test that DHCPv6 options can be inserted and retrieved from
    /// the database.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param formatted Boolean value indicating if the option values
    /// should be stored in the textual format in the database.
    /// @param user_context Optional user context.
    void testOptionsReservations6(const bool formatted,
                                  isc::data::ConstElementPtr user_context =
                                  isc::data::ConstElementPtr());

    /// @brief Test that DHCPv4 and DHCPv6 options can be inserted and retrieved
    /// with a single query to the database.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param formatted Boolean value indicating if the option values
    /// should be stored in the textual format in the database.
    void testOptionsReservations46(const bool formatted);

    /// @brief Test that multiple client classes for IPv4 can be inserted and
    /// retrieved for a given host reservation.
    ///
    /// Uses gtest macros to report failures.
    ///
    void testMultipleClientClasses4();

    /// @brief Test that multiple client classes for IPv6 can be inserted and
    /// retrieved for a given host reservation.
    ///
    /// Uses gtest macros to report failures.
    ///
    void testMultipleClientClasses6();

    /// @brief Test that multiple client classes for both IPv4 and IPv6 can
    /// be inserted and retrieved for a given host reservation.
    ///
    /// Uses gtest macros to report failures.
    ///
    void testMultipleClientClassesBoth();

    /// @brief Test that siaddr, sname, file fields can be retrieved
    /// from a database for a host.
    ///
    /// Uses gtest macros to report failures.
    void testMessageFields4();

    /// @brief Stress test on adding and retrieving hosts
    ///
    /// Rather than checking for correctness, this test gives interpretable
    /// performance results.
    ///
    /// @param n_of_hosts number of hosts to insert into and retrieve from the
    ///     database
    void stressTest(uint32_t n_of_hosts);
    /// @brief Tests that delete(subnet-id, addr4) call works.
    ///
    /// Uses gtest macros to report failures.
    void testDeleteByAddr4();

    /// @brief Tests that delete(subnet4-id, identifier-type, identifier) works.
    ///
    /// Uses gtest macros to report failures.
    void testDeleteById4();

    /// @brief Tests that delete(subnet4-id, id-type, id) also deletes options.
    void testDeleteById4Options();

    /// @brief Tests that delete(subnet6-id, identifier-type, identifier) works.
    ///
    /// Uses gtest macros to report failures.
    void testDeleteById6();

    /// @brief Tests that delete(subnet6-id, id-type, id) also deletes options.
    ///
    /// Uses gtest macros to report failures.
    void testDeleteById6Options();

    /// @brief Tests that multiple reservations without IPv4 addresses can be
    /// specified within a subnet.
    ///
    /// Uses gtest macros to report failures.
    void testMultipleHostsNoAddress4();

    /// @brief Tests that multiple hosts can be specified within an IPv6 subnet.
    ///
    /// Uses gtest macros to report failures.
    void testMultipleHosts6();

    /// @brief Returns DUID with identical content as specified HW address
    ///
    /// This method does not have any sense in real life and is only useful
    /// in testing corner cases in the database backends (e.g. whether the DB
    /// is able to tell the difference between hwaddr and duid)
    ///
    /// @param hwaddr hardware address to be copied
    /// @return duid with the same value as specified HW address
    DuidPtr HWAddrToDuid(const HWAddrPtr& hwaddr);

    /// @brief Returns HW address with identical content as specified DUID
    ///
    /// This method does not have any sense in real life and is only useful
    /// in testing corner cases in the database backends (e.g. whether the DB
    /// is able to tell the difference between hwaddr and duid)
    ///
    /// @param duid DUID to be copied
    /// @return HW address with the same value as specified DUID
    HWAddrPtr DuidToHWAddr(const DuidPtr& duid);

};

}  // namespace test
}  // namespace dhcp
}  // namespace isc

#endif
