// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_SUBNET_PARSER_H
#define SHARED_SUBNET_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/shared_network.h>

namespace isc {
namespace dhcp {

/// @brief Common parser for IPv4 and IPv6 shared networks.
///
/// It contains common functions for parsing the shared networks.
/// DHCPv4 and DHCPv6 specific implementations derive from it.
class SharedNetworkParser : public isc::data::SimpleParser {
protected:

    /// @brief Parses common DHCP timers.
    ///
    /// The parsed parameters are:
    /// - renew-timer,
    /// - rebind-timer,
    /// - valid-lifetime
    ///
    /// @param shared_network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    void parseCommonTimers(const data::ConstElementPtr& shared_network_data,
                           NetworkPtr& network);

    /// @brief Parses parameters related to "percent" timers settngs.
    ///
    /// The parsed parameters are:
    /// - calculate-tee-times,
    /// - t1-percent,
    /// - t2-percent.
    ///
    /// @param shared_network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    ///
    /// @throw DhcpConfigError if configuration of these parameters is
    /// invalid.
    void parseTeePercents(const data::ConstElementPtr& shared_network_data,
                          NetworkPtr& network);
};

/// @brief Implements parser for IPv4 shared networks.
class SharedNetwork4Parser : public SharedNetworkParser {
public:

    /// @brief Parses shared configuration information for IPv4 shared network.
    ///
    /// @param shared_network_data Data element holding shared network
    /// configuration to be parsed.
    ///
    /// @return Pointer to an object representing shared network.
    /// @throw DhcpConfigError when shared network configuration is invalid.
    SharedNetwork4Ptr
    parse(const data::ConstElementPtr& shared_network_data);
};

/// @brief Implements parser for IPv6 shared networks.
class SharedNetwork6Parser : public SharedNetworkParser {
public:

    /// @brief Parses shared configuration information for IPv6 shared network.
    ///
    /// @param shared_network_data Data element holding shared network
    /// configuration to be parsed.
    ///
    /// @return Pointer to an object representing shared network.
    /// @throw DhcpConfigError when shared network configuration is invalid.
    SharedNetwork6Ptr
    parse(const data::ConstElementPtr& shared_network_data);
};

} // enf of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_SUBNET_PARSER_H
