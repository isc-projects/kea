// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef EXPIRATION_CONFIG_PARSER_H
#define EXPIRATION_CONFIG_PARSER_H

#include <dhcpsrv/parsers/dhcp_config_parser.h>

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
/// the allowed ranges and throws exception if they are. Each parameter
/// has a corresponding maximum value defined in the @c CfgExpiration class.
/// None of them may be negative.
class ExpirationConfigParser : public DhcpConfigParser {
public:

    /// @brief Constructor
    ExpirationConfigParser();

    /// @brief Parses parameters in the JSON map, pertaining to the processing
    /// of the expired leases.
    ///
    /// @param value pointer to the content of parsed values
    ///
    /// @throw DhcpConfigError if unknown parameter specified or the
    /// parameter contains invalid value..
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Does nothing.
    virtual void commit();

};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // EXPIRATION_CONFIG_PARSER_H
