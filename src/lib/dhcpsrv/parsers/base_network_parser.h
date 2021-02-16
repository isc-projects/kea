// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_NETWORK_PARSER_H
#define BASE_NETWORK_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/network.h>

namespace isc {
namespace dhcp {

/// @brief Common configuration parser for shared networks
/// and subnets.
class BaseNetworkParser : public data::SimpleParser {
public:

    /// @brief Moves deprecated reservation-mode parameter to
    /// new reservations flags.
    ///
    /// @param config [in/out] configuration to alter.
    /// @throw DhcpConfigError on error e.g. when both reservation-mode
    /// and a flag are specified.
    static void moveReservationMode(isc::data::ElementPtr config);

protected:

    /// @brief Parses common parameters
    ///
    /// The parsed parameters are:
    /// - renew-timer,
    /// - rebind-timer,
    /// - valid-lifetime,
    /// - store-extended-info
    /// - reservations-global
    /// - reservations-in-subnet
    /// - reservations-out-of-pool
    ///
    /// @param network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    void parseCommon(const data::ConstElementPtr& network_data,
                     NetworkPtr& network);

    /// @brief Parses parameters related to "percent" timers settings.
    ///
    /// The parsed parameters are:
    /// - calculate-tee-times,
    /// - t1-percent,
    /// - t2-percent.
    ///
    /// @param network_data Data element holding network configuration
    /// to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    ///
    /// @throw DhcpConfigError if configuration of these parameters is
    /// invalid.
    void parseTeePercents(const data::ConstElementPtr& network_data,
                          NetworkPtr& network);

    /// @brief Parses parameters related to lease cache settings.
    ///
    /// The parsed parameters are:
    /// - cache-threshold,
    /// - cache-max-age.
    ///
    /// @param network_data Data element holding network configuration
    /// to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    ///
    /// @throw DhcpConfigError if configuration of these parameters is
    /// invalid.
    void parseCacheParams(const data::ConstElementPtr& network_data,
                     NetworkPtr& network);

    /// @brief Parses parameters pertaining to DDNS behavior.
    ///
    /// The parsed parameters are:
    /// - ddns-send-updates
    /// - ddns-override-no-update
    /// - ddns-override-client-update
    /// - ddns-replace-client-name
    /// - ddns-generated-prefix
    /// - ddns-qualifying-suffix
    ///
    /// @param network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param [out] network Pointer to a network in which parsed data is
    /// to be stored.
    void parseDdnsParams(const data::ConstElementPtr& network_data,
                         NetworkPtr& network);
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
