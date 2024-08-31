// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SANITY_CHECKS_PARSER_H
#define SANITY_CHECKS_PARSER_H

#include <cc/simple_parser.h>
#include <dhcpsrv/srv_config.h>

namespace isc {
namespace dhcp  {

/// @brief Simple parser for sanity-checks structure
///
/// Currently parses only one parameter:
/// - lease-checks. Allowed values: none, warn, fix, fix-del, del
class SanityChecksParser : public isc::data::SimpleParser {
 public:
    /// @brief parses JSON structure
    ///
    /// @param srv_cfg parsed value will be stored here
    /// @param value a JSON map that contains lease-checks parameter.
    void parse(SrvConfig& srv_cfg, const isc::data::ConstElementPtr& value);
};

}
}

#endif /* SANITY_CHECKS_PARSER_H */
