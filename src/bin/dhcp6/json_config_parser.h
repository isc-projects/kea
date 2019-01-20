// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
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
/// Test-only mode is supported. If check_only flag is set to true, the
/// configuration is parsed, but the actual change is not applied. The goal is
/// to have the ability to test configuration.
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
/// @param check_only whether this configuration is for testing only
/// @return answer that contains result of the reconfiguration.
/// @throw Dhcp6ConfigError if trying to create a parser for NULL config.
isc::data::ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& server, isc::data::ConstElementPtr config_set,
                     bool check_only = false);

/// @brief Attempts to connect to configured CB databases
///
/// First, this function will close all existing CB backends. It
/// will then attempt to connect to all of the CB backends defined
/// in the given SrvConfig (if any).
///
/// It will return true if there are configured CB databases,
/// and false otherwise.  Any errors encountered along the way
/// should generate throws.
///
/// @param srv_cfg Server configuration from which to get
/// the config-control information to use.
///
/// @return True if there are configured CB databases, false if not.
bool
databaseConfigConnect(const SrvConfigPtr& srv_cfg);

/// @brief Fetch configuration from CB databases and merge it into the given configuration
///
/// It will call @c databaseConfigConnect, passing in the given server configuration. If
/// that call results in open CB databases, the function will then proceed to fetch
/// configuration components from said databases and merge them into the given server
/// configuration.
///
/// @param srv_cfg Server configuration into which database configuration should be merged
/// @param mutable_cfg parsed configuration from the configuration file plus default values (ignored)
void
databaseConfigFetch(const SrvConfigPtr& srv_cfg, isc::data::ElementPtr mutable_cfg);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP6_CONFIG_PARSER_H
