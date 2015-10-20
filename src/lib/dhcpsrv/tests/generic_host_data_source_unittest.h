// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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

    /// @brief Creates a host reservation for specified IPv4 address.
    ///
    /// @param address IPv6 address to be reserved
    /// @param hwaddr type of identifier (true = hwaddr, false = client-id)
    /// @param prefix reservation type (true = prefix, false = address)
    ///
    /// @return generated Host object
    HostPtr initializeHost6(std::string address, bool hwaddr, bool prefix);

    /// @brief Generates a hardware address in text version.
    ///
    /// @return HW address in textual form acceptable by Host constructor
    std::string generateHWAddr();

    /// @brief Generates a hardware address in text version.
    /// @return DUID in textual form acceptable by Host constructor
    std::string generateDuid();

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

    /// @brief Pointer to the host data source
    BaseHostDataSource* hdsptr_;

    /// @brief Test that checks that simple host with IPv4 reservation
    ///        can be inserted and later retrieved.
    ///
    /// Uses gtest macros to report failures.
    void testBasic4();
};

}; // namespace test
}; // namespace dhcp
}; // namespace isc

#endif
