// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP_QUEUE_CONTROL_PARSER_H
#define DHCP_QUEUE_CONTROL_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>

namespace isc {
namespace dhcp {

/// @brief Parser for the configuration of DHCP packet queue controls
///
/// This parser parses the "dhcp-queue-control" parameter which holds the
/// the configurable parameters that tailor DHCP packet queue behavior.
/// In order to provide wide latitude to packet queue implementators,
/// 'dhcp-queue-control' is mostly treated as a map of arbitrary values.
/// There is only mandatory value, 'enable-queue', which enables/disables
/// DHCP packet queueing.  If this value is true, then the content must
/// also include a value for 'queue-type'.  Beyond these values, the
/// map may contain any combination of valid JSON elements.
///
/// Unlike most other parsers, this parser primarily serves to validate
/// the aforementioned rules, and rather than instantiate an object as
/// a result, it simply returns a copy original map of elements.
///
/// This parser is used in both DHCPv4 and DHCPv6. Derived parsers
/// are not needed.
class DHCPQueueControlParser : public isc::data::SimpleParser {
public:

    /// @brief Constructor.
    DHCPQueueControlParser(){};

    /// @brief Parses content of the "dhcp-queue-control".
    ///
    /// @param control_elem  MapElement containing the queue control values to
    /// parse.
    /// @param multi_threading_enabled The flag which indicates if MT is enabled.
    ///
    /// @return A copy of the of the input MapElement.
    ///
    /// @throw DhcpConfigError if any of the values are invalid.
    data::ElementPtr parse(const isc::data::ConstElementPtr& control_elem,
                           bool multi_threading_enabled);

private:
};

}
} // end of namespace isc

#endif // DHCP_QUEUE_CONTROL_PARSER_H
