// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_DATA_SOURCE_UTILS_H
#define HOST_DATA_SOURCE_UTILS_H

#include <config.h>
#include <dhcpsrv/host.h>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

/// @brief A helper class for manipulating hosts
///
/// Intended to be used in tests and benchmarks.
class HostDataSourceUtils {
public:
    /// @brief Creates a host reservation for specified IPv4 address.
    ///
    /// @param address IPv4 address to be set
    /// @param id Identifier type.
    /// @param new_identifier Boolean value indicating if new host
    /// identifier should be generated or the same as previously.
    ///
    /// @return generated Host object
    static isc::dhcp::HostPtr initializeHost4(const std::string& address,
                                              const Host::IdentifierType& id,
                                              const bool new_identifier = true);

    /// @brief Creates a host reservation for specified IPv6 address.
    ///
    /// @param address IPv6 address to be reserved
    /// @param id type of identifier (IDENT_DUID or IDENT_HWADDR are supported)
    /// @param prefix reservation type (true = prefix, false = address)
    /// @param new_identifier Boolean value indicating if new host
    /// identifier should be generated or the same as previously.
    ///
    /// @return generated Host object
    static HostPtr initializeHost6(std::string address, Host::IdentifierType id,
                                   bool prefix, bool new_identifier = true,
                                   const std::string key = "");

    /// @brief Generates a hardware address in text version.
    ///
    /// @param increase A boolean value indicating if new address (increased)
    /// must be generated or the same address as previously.
    /// @return HW address in textual form acceptable by Host constructor
    static std::vector<uint8_t> generateHWAddr(const bool new_identifier = true);

    /// @brief Generates a host identifier in a textual form..
    ///
    /// @param increase A boolean value indicating if new identifier (increased)
    /// must be generated or the same identifier as previously.
    /// @return Identifier in textual form acceptable by Host constructor
    static std::vector<uint8_t> generateIdentifier(const bool new_identifier = true);

    /// @brief Checks if the reservation is in the range of reservations.
    ///
    /// @param resrv Reservation to be searched for.
    /// @param range Range of reservations returned by the @c Host object
    /// in which the reservation will be searched
    static bool reservationExists(const IPv6Resrv& resrv, const IPv6ResrvRange& range);

    /// @brief Compares hardware addresses of the two hosts.
    ///
    /// This method compares two hardware address and uses gtest
    /// macros to signal unexpected (mismatch if expect_match is true;
    /// match if expect_match is false) values.
    ///
    /// @param host1 first host to be compared
    /// @param host2 second host to be compared
    /// @param expect_match true = HW addresses expected to be the same,
    ///                     false = HW addresses expected to be different
    static void compareHwaddrs(const ConstHostPtr& host1, const ConstHostPtr& host2,
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
    static void compareDuids(const ConstHostPtr& host1, const ConstHostPtr& host2,
                             bool expect_match);

    /// @brief Compares two hosts
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param host1 first host to compare
    /// @param host2 second host to compare
    static void compareHosts(const isc::dhcp::ConstHostPtr& host1, const ConstHostPtr& host2);

    /// @brief Compares two IPv6 reservation lists.
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param resv1 first IPv6 reservations list
    /// @param resv2 second IPv6 reservations list
    static void compareReservations6(IPv6ResrvRange resv1, IPv6ResrvRange resv2);

    /// @brief Compares two client classes
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param classes1 first list of client classes
    /// @param classes2 second list of client classes
    static void compareClientClasses(const ClientClasses& classes1,
                                     const ClientClasses& classes2);

    /// @brief Compares options within two configurations.
    ///
    /// This method uses gtest macros to signal errors.
    ///
    /// @param cfg1 First configuration.
    /// @param cfg2 Second configuration.
    static void compareOptions(const ConstCfgOptionPtr& cfg1,
                               const ConstCfgOptionPtr& cfg2);
};

}
}
}

#endif
