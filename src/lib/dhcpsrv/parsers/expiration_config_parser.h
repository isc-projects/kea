// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EXPIRATION_CONFIG_PARSER_H
#define EXPIRATION_CONFIG_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>

namespace isc {
namespace dhcp {


/// @brief Parser for the configuration parameters pertaining to the
/// processing of expired leases.
///
/// This parser iterates over parameters stored in the map and tries to
/// set the appropriate values in the @c CfgExpiration object of the
/// Configuration Manager.
///
/// Currently supported parameters are:
/// - reclaim-timer-wait-time,
/// - flush-reclaimed-timer-wait-time,
/// - hold-reclaimed-time,
/// - max-reclaim-leases,
/// - max-reclaim-time,
/// - unwarned-reclaim-cycles.
///
/// These parameters are optional and the default values are used for
/// those that aren't specified.
///
/// The parser checks if the values of the specified parameters are within
/// the allowed ranges and throws exception if they aren't. Each parameter
/// has a corresponding maximum value defined in the @c CfgExpiration class.
/// None of them may be negative.
class ExpirationConfigParser : public isc::data::SimpleParser {
public:

    /// @brief Destructor.
    virtual ~ExpirationConfigParser() { }

    /// @brief Parses parameters in the JSON map, pertaining to the processing
    /// of the expired leases.
    ///
    /// @param expiration_config pointer to the content of parsed values
    ///
    /// @throw DhcpConfigError if unknown parameter specified or the
    /// parameter contains invalid value..
    void parse(isc::data::ConstElementPtr expiration_config);

};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // EXPIRATION_CONFIG_PARSER_H
