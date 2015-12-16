// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_HOST_DATA_SOURCE_UNITTEST_H
#define GENERIC_HOST_DATA_SOURCE_UNITTEST_H

#include <dhcpsrv/base_host_data_source.h>
#include <dhcp/classify.h>
#include <gtest/gtest.h>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test Fixture class with utility functions for HostDataSource backends
///
/// It contains utility functions for test purposes.
/// All concrete HostDataSource test classes should be derived from it.
class GenericHostDataSourceTest : public ::testing::Test {
public:

    /// @brief Universe (V4 or V6).
    enum Universe {
        V4,
        V6
    };

    /// @brief Default constructor.
    GenericHostDataSourceTest();

    /// @brief Virtual destructor.
    virtual ~GenericHostDataSourceTest();

    /// @brief Creates a host reservation for specified IPv4 address.
    ///
    /// @param address IPv4 address to be set
    /// @param hwaddr type of identifier (true = hwaddr, false = client-id)
    ///
    /// @return generated Host object
    HostPtr initializeHost4(std::string address, bool hwaddr);

    /// @brief Creates a host reservation for specified IPv6 address.
    ///
    /// @param address IPv6 address to be reserved
    /// @param id type of identifier (ID_DUID or ID_HWADDR are supported)
    /// @param prefix reservation type (true = prefix, false = address)
    ///
    /// @return generated Host object
    HostPtr initializeHost6(std::string address, BaseHostDataSource::IdType id,
                            bool prefix);

    /// @brief Generates a hardware address in text version.
    ///
    /// @return HW address in textual form acceptable by Host constructor
    std::string generateHWAddr();

    /// @brief Generates a hardware address in text version.
    /// @return DUID in textual form acceptable by Host constructor
    std::string generateDuid();

    /// @brief Compares hardware addresses of the two hosts.
    ///
    /// This method compares two hwardware address and uses gtest
    /// macros to signal unexpected (mismatch if expect_match is true;
    /// match if expect_match is false) values.
    ///
    /// @param host1 first host to be compared
    /// @param host2 second host to be compared
    /// @param expect_match true = HW addresses expected to be the same,
    ///                     false = HW addresses expected to be different
    void
    compareHwaddrs(const ConstHostPtr& host1, const ConstHostPtr& host2,
                   bool expect_match);

    /// @brief Compares DUIDs of the two hosts.
    ///
    /// This method compares two DUIDs (client-ids) and uses gtest
    /// macros to signal unexpected (mismatch if expect_match is true;
    /// match if expect_match is false) values.
    ///
    /// @param host1 first host to be compared
    /// @param host2 second host to be compared
    /// @param expect_match true = DUIDs expected to be the same,
    ///                     false = DUIDs expected to be different
    void
    compareDuids(const ConstHostPtr& host1, const ConstHostPtr& host2,
                 bool expect_match);

    /// @brief Compares two hosts
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param host1 first host to compare
    /// @param host2 second host to compare
    void compareHosts(const ConstHostPtr& host1, const ConstHostPtr& host2);

    /// @brief Compares two IPv6 reservation lists.
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param resv1 first IPv6 reservations list
    /// @param resv2 second IPv6 reservations list
    void compareReservations6(IPv6ResrvRange resv1, IPv6ResrvRange resv2,
                              bool expect_match);

    /// @brief Compares two client classes
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param classes1 first list of client classes
    /// @param classes2 second list of client classes
    void compareClientClasses(const ClientClasses& classes1,
                              const ClientClasses& classes2);

    /// @brief Pointer to the host data source
    HostDataSourcePtr hdsptr_;

    /// @brief Test that checks that simple host with IPv4 reservation
    ///        can be inserted and later retrieved.
    ///
    /// Uses gtest macros to report failures.
    /// @param hwaddr true = use HW address as identifier, false = use client-id(DUID)
    void testBasic4(bool hwaddr);

    /// @brief Test inserts several hosts with unique IPv4 address and
    ///        checks that they can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    /// @param hwaddr true = use HW address as identifier, false = use client-id(DUID)
    void testGetByIPv4(bool hwaddr);

    /// @brief Test that hosts can be retrieved by hardware address.
    ///
    /// Uses gtest macros to report failures.
    void testGet4ByHWAddr();

    /// @brief Test that hosts can be retrieved by client-id
    ///
    /// Uses gtest macros to report failures.
    void testGet4ByClientId();

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

    /// @brief Test inserts multiple reservations for the same host for different
    /// subnets and check that they can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param subnets number of subnets to test
    /// @param hwaddr true = use HW address, false = use client-id
    void testMultipleSubnets(int subnets, bool hwaddr);

    /// @brief Test inserts several hosts with unique IPv6 addresses and
    ///        checks that they can be retrieved properly.
    ///
    /// Uses gtest macros to report failures.
    /// @param id type of the identifier to be used (HWAddr or DUID)
    /// @param prefix true - reserve IPv6 prefix, false - reserve IPv6 address
    void testGetByIPv6(BaseHostDataSource::IdType id, bool prefix);

    /// @brief Test that hosts can be retrieved by hardware address.
    ///
    /// Uses gtest macros to report failures.
    void testGet6ByHWAddr();

    /// @brief Test that hosts can be retrieved by client-id
    ///
    /// Uses gtest macros to report failures.
    void testGet6ByClientId();

    /// @brief Test if host reservations made for different IPv6 subnets
    ///        are handled correctly.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param subnets number of subnets to test
    /// @param id identifier type (ID_HWADDR or ID_DUID)
    void testSubnetId6(int subnets, BaseHostDataSource::IdType id);

    /// @brief Test if the duplicate host instances can't be inserted.
    ///
    /// Uses gtest macros to report failures.
    void testAddDuplicate();

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

}; // namespace test
}; // namespace dhcp
}; // namespace isc

#endif
