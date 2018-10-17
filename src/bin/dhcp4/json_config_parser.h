// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
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
/// Test-only mode added. If check_only flag is set to true, the configuration
/// is parsed, but the actual change is not applied. The goal is to have
/// the ability to test configuration.
///
/// This method does not throw. It catches all exceptions and returns them as
/// reconfiguration statuses. It may return the following response codes:
/// 0 - configuration successful
/// 1 - malformed configuration (parsing failed)
/// 2 - commit failed (parsing was successful, but failed to store the
/// values in to server's configuration)
///
/// @param config_set a new configuration (JSON) for DHCPv4 server
/// @param check_only whether this configuration is for testing only
/// @return answer that contains result of reconfiguration
isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv&,
                     isc::data::ConstElementPtr config_set,
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
/// @param mutable_cfg parsed configuration from the configuration file plus default values
void
databaseConfigFetch(const SrvConfigPtr& srv_cfg, isc::data::ElementPtr /* mutable_cfg */);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_CONFIG_PARSER_H
