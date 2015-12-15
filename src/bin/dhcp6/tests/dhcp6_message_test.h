// Copyright (C) 2014-2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP6_MESSAGE_TEST_H
#define DHCP6_MESSAGE_TEST_H

#include <asiolink/io_address.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcp6/tests/dhcp6_test_utils.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Base class for test fixure classes used to validate the DHCPv6
/// message processing by the server.
class Dhcpv6MessageTest : public Dhcpv6SrvTest {
public:
    /// @brief Constructor.
    ///
    /// Sets up interfaces.
    Dhcpv6MessageTest();

    /// @brief Increases last byte of the address.
    ///
    /// This function is helpful to find a different address that is within
    /// the same subnet as the input address. It is achieved by increasing
    /// the last byte of the input address by one.
    ///
    /// @param input_addr An input address.
    ///
    /// @return New address.
    asiolink::IOAddress bumpAddress(const asiolink::IOAddress& input_addr);

    /// @brief Increases specific byte in the address by one.
    ///
    /// This function is called by @c bumpAddress and @c bumpSubnet.
    ///
    /// @warning This function is no-op if the byte index is out of range.
    ///
    /// @param input_addr An input address
    /// @param byte_num An index of the byte which value should be increased..
    ///
    /// @return New address.
    asiolink::IOAddress bumpByteInAddress(const asiolink::IOAddress& input_addr,
                                          const size_t byte_num);

    /// @brief Increases the first byte of the address.
    ///
    /// This function is helpful to find an address which belongs to the
    /// different subnet than the input address. It is achieved by increasing
    /// the first byte of the input address.
    ///
    /// @param input_addr An input addres.
    ///
    /// @return New address.
    asiolink::IOAddress bumpSubnet(const asiolink::IOAddress& input_addr);

    /// @brief Make 4-way exchange to obtain a lease.
    ///
    /// @param config Configuration in the JSON format to be applied before the
    /// lease is requested..
    /// @param subnets_num Number of subnets being created with the specified
    /// configuration.
    /// @param client Object representing a test DHCPv6 client to use.
    void requestLease(const std::string& config, const int subnets_num,
                      Dhcp6Client& client);


protected:

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

} // isc::dhcp::test
} // isc::dhcp
} // isc

#endif // DHCP6_MESSAGE_TEST_H
