// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <exceptions/exceptions.h>

#include <stdint.h>
#include <string>

#ifndef DHCP4_CONFIG_PARSER_H
#define DHCP4_CONFIG_PARSER_H

/// @todo: This header file and its .cc counterpart are very similar between
/// DHCPv4 and DHCPv6. They should be merged. A ticket #2355.

namespace isc {
namespace dhcp {

class Dhcpv4Srv;

/// @brief Configure DHCPv4 server (@c Dhcpv4Srv) with a set of configuration
/// values.
///
/// This function parses configuration information stored in @c config_set
/// and configures the @c server by applying the configuration to it.
/// It provides the strong exception guarantee as long as the underlying
/// derived class implementations of @c DhcpConfigParser meet the assumption,
/// that is, it ensures that either configuration is fully applied or the
/// state of the server is intact.
///
/// If a syntax or semantics level error happens during the configuration
/// (such as malformed configuration or invalid configuration parameter),
/// this function returns appropriate error code.
///
/// This function is called every time a new configuration is received. The
/// extra parameter is a reference to DHCPv4 server component. It is currently
/// not used and CfgMgr::instance() is accessed instead.
///
/// This method does not throw. It catches all exceptions and returns them as
/// reconfiguration statuses. It may return the following response codes:
/// 0 - configuration successful
/// 1 - malformed configuration (parsing failed)
/// 2 - commit failed (parsing was successful, but failed to store the
/// values in to server's configuration)
///
/// @param config_set a new configuration (JSON) for DHCPv4 server
/// @return answer that contains result of reconfiguration
isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv&,
                     isc::data::ConstElementPtr config_set);

/// @brief Returns the global context
///
/// @return a reference to the global context
ParserContextPtr& globalContext();

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_CONFIG_PARSER_H
