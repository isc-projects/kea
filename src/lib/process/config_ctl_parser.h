// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PROCESS_CONFIG_CONTROL_PARSER_H
#define PROCESS_CONFIG_CONTROL_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <process/config_ctl_info.h>

namespace isc {
namespace process {

/// @brief Implements parser for config control information, "config-control"
class ConfigControlParser : isc::data::SimpleParser {
public:

    /// @brief Parses a configuration control Element
    ///
    /// @param config_control Element holding the config control content
    /// to be parsed.
    ///
    /// @return Pointer to newly created ConfigControlInfo instance
    /// @throw DhcpConfigError when config control content is invalid.
    ConfigControlInfoPtr
    parse(const data::ConstElementPtr& config_control);
};

} // enf of namespace isc::process
} // end of namespace isc

#endif // PROCESS_CONFIG_CONTROL_PARSER_H
