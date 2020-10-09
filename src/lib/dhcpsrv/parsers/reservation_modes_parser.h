// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RESERVATION_MODES_PARSER_H
#define RESERVATION_MODES_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>

namespace isc {
namespace dhcp {

/// @brief Parser for the configuration of DHCP packet queue controls
///
/// This parser parses the "reservation-modes" parameter which holds the
/// the configurable parameters that tailor host reservation modes.
///
/// This parser is used in both DHCPv4 and DHCPv6, and also inside subnet and
/// shared networks.
class HostReservationModesParser : public isc::data::SimpleParser {
public:

    /// @brief Constructor
    ///
    HostReservationModesParser(){};

    /// @brief Parses content of the "reservation-modes".
    ///
    /// @param control_elem MapElement containing the host reservation modes
    /// values to parse
    ///
    /// @return Host reservation modes flags.
    ///
    /// @throw DhcpConfigError if any of the values are invalid.
    Network::HRMode parse(const isc::data::ConstElementPtr& control_elem);
};

}
} // end of namespace isc

#endif // RESERVATION_MODES_PARSER_H
