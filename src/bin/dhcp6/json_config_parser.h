// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP6_CONFIG_PARSER_H
#define DHCP6_CONFIG_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <exceptions/exceptions.h>

#include <string>

namespace isc {
namespace dhcp {

class Dhcpv6Srv;

/// @brief Configures DHCPv6 server
///
/// This function is called every time a new configuration is received. The
/// extra parameter is a reference to DHCPv6 server component. It is currently
/// not used and CfgMgr::instance() is accessed instead.
///
/// This method does not throw. It catches all exceptions and returns them as
/// reconfiguration statuses. It may return the following response codes:
/// 0 - configuration successful
/// 1 - malformed configuration (parsing failed)
/// 2 - commit failed (parsing was successful, but the values could not be
/// stored in the configuration).
///
/// @param server DHCPv6 server object.
/// @param config_set a new configuration for DHCPv6 server.
/// @return answer that contains result of the reconfiguration.
/// @throw Dhcp6ConfigError if trying to create a parser for NULL config.
isc::data::ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& server, isc::data::ConstElementPtr config_set);

/// @brief Returns the global context
///
/// @returns a reference to the global context
ParserContextPtr& globalContext();

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP6_CONFIG_PARSER_H
