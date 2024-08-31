// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
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

/// @todo: This header file and its .cc counterpart are very similar between
/// DHCPv4 and DHCPv6. They should be merged.

namespace isc {
namespace dhcp {

class Dhcpv6Srv;

/// @brief Configure DHCPv6 server (@c Dhcpv6Srv) with a set of configuration
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
/// extra parameter is a reference to DHCPv6 server component. It is currently
/// not used and CfgMgr::instance() is accessed instead.
///
/// Test-only mode is supported. If check_only flag is set to true, the
/// configuration is parsed, but the actual change is not applied. The goal is
/// to have the ability to test configuration.
///
/// This method does not throw. It catches all exceptions and returns them as
/// reconfiguration statuses. It may return the following response codes:
/// 0 - configuration successful
/// 1 - malformed configuration (parsing failed)
/// 2 - commit failed (parsing was successful, but failed to store the
/// values in to server's configuration)
///
/// @param server DHCPv6 server object.
/// @param config_set a new configuration (JSON) for DHCPv6 server.
/// @param check_only whether this configuration is for testing only.
/// @param extra_checks load hooks and perform extra checks if this flag is true
///        and check_only is also true, otherwise perform simple check if
///        check_only is true.
/// @return answer that contains result of the reconfiguration.
isc::data::ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& server, isc::data::ConstElementPtr config_set,
                     bool check_only = false, bool extra_checks = false);

}  // namespace dhcp
}  // namespace isc

#endif // DHCP6_CONFIG_PARSER_H
