// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MULTI_THREADING_CONFIG_PARSER_H
#define MULTI_THREADING_CONFIG_PARSER_H

#include <cc/simple_parser.h>
#include <dhcpsrv/srv_config.h>

namespace isc {
namespace dhcp  {

/// @brief Simple parser for multi-threading structure
class MultiThreadingConfigParser : public isc::data::SimpleParser {
public:

    /// @brief parses JSON structure.
    ///
    /// This function stores the 'multi-threading' settings in the server
    /// configuration and updates the MT mode so that is can be checked when
    /// parsing 'hooks-libraries'.
    ///
    /// @param srv_cfg parsed value will be stored here.
    /// @param value a JSON map that contains multi-threading parameters.
    void parse(SrvConfig& srv_cfg, const isc::data::ConstElementPtr& value);
};

}  // namespace dhcp
}  // namespace isc

#endif /* MULTI_THREADING_CONFIG_PARSER_H */
