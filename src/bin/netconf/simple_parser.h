// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_SIMPLE_PARSER_H
#define NETCONF_SIMPLE_PARSER_H

#include <cc/simple_parser.h>
#include <netconf/netconf_cfg_mgr.h>

namespace isc {
namespace netconf {

/// @brief SimpleParser specialized for Netconf
///
/// This class is a @ref isc::data::SimpleParser dedicated to Netconf.
/// In particular, it contains all the default values for the whole
/// netconf defaults.
///
/// For the actual values, see @file netconf/simple_parser.cc
class NetconfSimpleParser : public isc::data::SimpleParser {
public:
    /// @brief Sets all defaults for Netconf configuration
    ///
    /// This method sets global, option data and option definitions defaults.
    ///
    /// @param global scope to be filled in with defaults.
    /// @return number of default values added
    static size_t setAllDefaults(const isc::data::ElementPtr& global);

    /// @brief Derives (inherits) all parameters from global to more specific scopes.
    ///
    /// This method currently does the following:
    /// - derives global parameters to managed servers (flags for now)
    /// @param global scope to be modified if needed
    /// @return number of default values derived
    static size_t deriveParameters(isc::data::ElementPtr global);

    /// @brief Adds default values to a Managed server entry.
    ///
    /// Adds server specific defaults, e.g. the default model.
    ///
    /// @param name server name / entry key
    /// @param server server element / entry value
    /// @return returns the number of default values added
    static size_t setServerDefaults(const std::string name,
                                    isc::data::ElementPtr server);

    /// @brief Parses the netconf configuration
    ///
    /// @param ctx - parsed information will be stored here
    /// @param config - Element tree structure that holds configuration
    /// @param check_only - if true the configuration is verified only, not applied
    ///
    /// @throw ConfigError if any issues are encountered.
    void parse(const NetconfConfigPtr& ctx,
               const isc::data::ElementPtr& config,
               bool check_only);

    // see simple_parser.cc for comments for those parameters
    static const isc::data::SimpleDefaults NETCONF_DEFAULTS;
    static const isc::data::SimpleDefaults CTRL_SOCK_DEFAULTS;
    static const isc::data::SimpleDefaults DHCP4_DEFAULTS;
    static const isc::data::SimpleDefaults DHCP6_DEFAULTS;
    static const isc::data::SimpleDefaults D2_DEFAULTS;
    static const isc::data::SimpleDefaults CA_DEFAULTS;
    static const isc::data::ParamsList INHERIT_TO_SERVERS;
};  // NetconfSimpleParser

}  // namespace netconf
}  // namespace isc
#endif
