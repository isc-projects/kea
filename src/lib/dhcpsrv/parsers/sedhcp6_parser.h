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

#ifndef SEDHCP6_PARSER_H
#define SEDHCP6_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/cfg_sedhcp6.h>
#include <exceptions/exceptions.h>

#include <string>

namespace isc {
namespace dhcp {

/// @brief Secure DHCPv6 Parameters
///
/// This class is the parser for the secure DHCPv6 configuration.  This is a
/// map under the top-level "secure" element, and comprises a map of
/// strings.
class SeDhcp6Parser: public DhcpConfigParser {
public:
    /// @brief Keyword and associated value
    typedef std::pair<std::string, std::string> StringPair;

    /// @brief Keyword/value collection of secure DHCPv6 parameters
    typedef std::map<std::string, std::string> StringPairMap;

    /// @brief Constructor
    ///
    /// @param param_name Name of the parameter under which the secure
    ///        DHCPv6 details are held.
    /// @param universe Parser universe.
    SeDhcp6Parser(const std::string& param_name, Option::Universe universe);

    /// The destructor.
    virtual ~SeDhcp6Parser()
    {}

    /// @brief Prepare configuration value.
    ///
    /// Parses the set of strings forming the secure DHCPv6 specification and
    /// checks that all are OK.  In particular it checks:
    ///
    /// - public and private keys and certificate
    /// - algorithms and validation policy
    ///
    /// Once all has been validated, update the configuration values
    ///
    /// @param config_value The configuration value for the "secure""
    ///        identifier.
    ///
    /// @throw isc::data::TypeError
    /// @throw DhcpConfigError
    virtual void build(isc::data::ConstElementPtr config_value);

    /// @brief Apply the prepared configuration values to the server.
    ///
    /// This method is expected to be called after \c build(), and only once.
    virtual void commit();

    /// @brief Deletes all of the entries from the store.
    void clear();

private:
    /// @brief Create a new secure DHCPv6 state with new parameters
    CfgSeDhcp6 create() const;

    std::map<std::string, std::string> values_; ///< Stored parameter values

    Option::Universe universe_; ///< Parser universe
};

};  // namespace dhcp
};  // namespace isc


#endif // SEDHCP6_PARSER_H
