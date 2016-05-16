// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_HOST_DATA_SOURCE_UNITTEST_H
#define GENERIC_HOST_DATA_SOURCE_UNITTEST_H

#include <asiolink/io_address.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/host.h>
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
    /// @param id Identifier type.
    ///
    /// @return generated Host object
    HostPtr initializeHost4(const std::string& address,
                            const Host::IdentifierType& id);

    /// @brief Creates a host reservation for specified IPv6 address.
    ///
    /// @param address IPv6 address to be reserved
    /// @param id type of identifier (IDENT_DUID or IDENT_HWADDR are supported)
    /// @param prefix reservation type (true = prefix, false = address)
    /// @param new_identifier Boolean value indicating if new host
    /// identifier should be generated or the same as previously.
    ///
    /// @return generated Host object
    HostPtr initializeHost6(std::string address, Host::IdentifierType id,
                            bool prefix, bool new_identifier = true);

    /// @brief Generates a hardware address in text version.
    ///
    /// @param increase A boolean value indicating if new address (increased)
    /// must be generated or the same address as previously.
    /// @return HW address in textual form acceptable by Host constructor
    std::vector<uint8_t> generateHWAddr(const bool new_identifier = true);

    /// @brief Generates a host identifier in a textual form..
    ///
    /// @param increase A boolean value indicating if new identifier (increased)
    /// must be generated or the same identifier as previously.
    /// @return Identifier in textual form acceptable by Host constructor
    std::vector<uint8_t> generateIdentifier(const bool new_identifier = true);

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
    void compareReservations6(IPv6ResrvRange resv1, IPv6ResrvRange resv2);

    /// @brief Compares two client classes
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param classes1 first list of client classes
    /// @param classes2 second list of client classes
    void compareClientClasses(const ClientClasses& classes1,
                              const ClientClasses& classes2);                           

    /// @brief Compares options within two configurations.
    ///
    /// @param cfg1 First configuration.
    /// @param cfg2 Second configuration.
    void compareOptions(const ConstCfgOptionPtr& cfg1,
                        const ConstCfgOptionPtr& cfg2) const;

    OptionDescriptor createEmptyOption(const Option::Universe& universe,
                                       const uint16_t option_type,
                                       const bool persist) const;

    /// @brief Creates an instance of the option for which it is possible to
    /// specify universe, option type and value in the constructor.
    ///
    /// Examples of options that can be created using this function are:
    /// - @ref OptionString
    /// - different variants of @ref OptionInt.
    ///
    /// @param encapsulated_space 
    /// @return Instance of the option created.
    template<typename OptionType, typename DataType>
    OptionDescriptor createOption(const Option::Universe& universe,
                                  const uint16_t option_type,
                                  const bool persist,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(new OptionType(universe, option_type,
                                                            value));
        std::ostringstream s;
        if (formatted) {
            s << value;
        }
        OptionDescriptor desc(option, persist, s.str());
        return (desc);
    }

    template<typename OptionType, typename DataType>
    OptionDescriptor createOption(const uint16_t option_type,
                                  const bool persist,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(new OptionType(option_type, value));

        std::ostringstream s;
        if (formatted) {
            s << value;
        }

        OptionDescriptor desc(option, persist, s.str());
        return (desc);
    }

    template<typename OptionType>
    OptionDescriptor
    createAddressOption(const uint16_t option_type,
                        const bool persist,
                        const bool formatted,
                        const std::string& address1 = "",
                        const std::string& address2 = "",
                        const std::string& address3 = "") const {
        std::ostringstream s;
        typename OptionType::AddressContainer addresses;
        if (!address1.empty()) {
            addresses.push_back(asiolink::IOAddress(address1));
            if (formatted) {
                s << address1;
            }
        }
        if (!address2.empty()) {
            addresses.push_back(asiolink::IOAddress(address2));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address2;
            }
        }
        if (!address3.empty()) {
            addresses.push_back(asiolink::IOAddress(address3));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address3;
            }
        }

        boost::shared_ptr<OptionType> option(new OptionType(option_type, addresses));
        OptionDescriptor desc(option, persist, s.str());
        return (desc);
    }

    OptionDescriptor createVendorOption(const Option::Universe& universe,
                                        const bool persist,
                                        const bool formatted,
                                        const uint32_t vendor_id) const;

    void addTestOptions(const HostPtr& host, const bool formatted) const;

    /// @brief Pointer to the host data source
    HostDataSourcePtr hdsptr_;

    /// @brief Test that checks that simple host with IPv4 reservation
    ///        can be inserted and later retrieved.
    ///
    /// Uses gtest macros to report failures.
    /// @param id Identifier type.
    void testBasic4(const Host::IdentifierType& id);

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

    void testAddRollback();

    /// @brief Test that DHCPv4 options can be inserted and retrieved from
    /// the database.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param formatted Boolean value indicating if the option values
    /// should be stored in the textual format in the database.
    void testOptionsReservations4(const bool formatted);

    /// @brief Test that DHCPv6 options can be inserted and retrieved from
    /// the database.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param formatted Boolean value indicating if the option values
    /// should be stored in the textual format in the database.
    void testOptionsReservations6(const bool formatted);

    /// @brief Test that DHCPv4 and DHCPv6 options can be inserted and retrieved
    /// with a single query to the database.
    ///
    /// Uses gtest macros to report failures.
    ///
    /// @param formatted Boolean value indicating if the option values
    /// should be stored in the textual format in the database.
    void testOptionsReservations46(const bool formatted);

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
