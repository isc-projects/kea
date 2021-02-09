// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef AGENT_SIMPLE_PARSER_H
#define AGENT_SIMPLE_PARSER_H

#include <cc/simple_parser.h>
#include <agent/ca_cfg_mgr.h>

namespace isc {
namespace agent {

/// @brief SimpleParser specialized for Control Agent
///
/// This class is a @ref isc::data::SimpleParser dedicated to Control Agent.
/// In particular, it contains all the default values for the whole
/// agent and for the socket defaults.
///
/// For the actual values, see @file agent/simple_parser.cc
class AgentSimpleParser : public isc::data::SimpleParser {
public:
    /// @brief Sets all defaults for Control Agent configuration
    ///
    /// This method sets global, option data and option definitions defaults.
    ///
    /// @param global scope to be filled in with defaults.
    /// @return number of default values added
    static size_t setAllDefaults(const isc::data::ElementPtr& global);

    /// @brief Check TLS setup consistency i.e. all or none.
    ///
    /// @param config - Element tree structure that holds configuration.
    /// @throw ConfigError when the configuration is not consistent.
    void checkTlsSetup(const isc::data::ConstElementPtr& config);

    /// @brief Parses the control agent configuration
    ///
    /// @param ctx - parsed information will be stored here
    /// @param config - Element tree structure that holds configuration
    /// @param check_only - if true the configuration is verified only, not applied
    ///
    /// @throw ConfigError if any issues are encountered.
    void parse(const CtrlAgentCfgContextPtr& ctx,
               const isc::data::ConstElementPtr& config,
               bool check_only);

    // see simple_parser.cc for comments for those parameters
    static const isc::data::SimpleDefaults AGENT_DEFAULTS;
    static const isc::data::SimpleDefaults AUTH_DEFAULTS;
    static const isc::data::SimpleDefaults SOCKET_DEFAULTS;
};

}
}
#endif
