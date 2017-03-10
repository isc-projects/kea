// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DUID_CONFIG_PARSER_H
#define DUID_CONFIG_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <stdint.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Parser for server DUID configuration.
///
/// This parser currently supports the following DUID types:
/// - DUID-LLT,
/// - DUID-EN
/// - DUID-LL
///
/// @todo Add support for DUID-UUID in the parser.
class DUIDConfigParser : public isc::data::SimpleParser {
public:
    /// @brief Parses DUID configuration.
    ///
    /// @param cfg parsed DUID configuration will be stored here
    /// @param duid_configuration Data element holding a map representing
    /// DUID configuration.
    ///
    /// @throw DhcpConfigError If the configuration is invalid.
    void parse(const CfgDUIDPtr& cfg, isc::data::ConstElementPtr duid_configuration);
};

}
} // end of namespace isc

#endif // DUID_CONFIG_PARSER_H
