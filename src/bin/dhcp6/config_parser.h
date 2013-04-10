// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCP6_CONFIG_PARSER_H
#define DHCP6_CONFIG_PARSER_H

/// @todo: This header file and its .cc counterpart are very similar between
/// DHCPv4 and DHCPv6. They should be merged. See ticket #2355.

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/dhcp_parsers.h>

#include <string>

namespace isc {
namespace dhcp {

class Dhcpv6Srv;

/// @brief Configures DHCPv6 server
///
/// This function is called every time a new configuration is received. The extra
/// parameter is a reference to DHCPv6 server component. It is currently not used
/// and CfgMgr::instance() is accessed instead.
///
/// This method does not throw. It catches all exceptions and returns them as
/// reconfiguration statuses. It may return the following response codes:
/// 0 - configuration successful
/// 1 - malformed configuration (parsing failed)
/// 2 - commit failed (parsing was successful, but the values could not be
/// stored in the configuration).
///
/// @param server DHCPv6 server object.
/// @param config_set a new configuration for DHCPv6 server.
/// @return answer that contains result of the reconfiguration.
/// @throw Dhcp6ConfigError if trying to create a parser for NULL config.
isc::data::ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& server, isc::data::ConstElementPtr config_set);

/// @brief Parser for DHCP6 option data value.
///
/// This parser parses configuration entries that specify value of
/// a single option specific to DHCP6.  It provides the DHCP6-specific
/// implementation of the abstract class OptionDataParser.
class Dhcp6OptionDataParser : public OptionDataParser {
public:
    /// @brief Constructor.
    ///
    /// Class constructor.
    Dhcp6OptionDataParser(const std::string&, OptionStorage *options,
        OptionDefStorage *option_defs);

    /// @brief static factory method for instantiating Dhcp4OptionDataParsers
    ///
    /// @param param_name name fo the parameter to be parsed.
    /// @param options storage where the parameter value is to be stored.
    /// @param global_option_defs global option definitions storage 
    static OptionDataParser* factory(const std::string& param_name, OptionStorage *options,
        OptionDefStorage *global_option_defs);

protected:
    /// @brief Finds an option definition within the server's option space
    /// 
    /// Given an option space and an option code, find the correpsonding 
    /// option defintion within the server's option defintion storage.
    ///
    /// @param option_space name of the parameter option space 
    /// @param option_code numeric value of the parameter to find 
    /// @return OptionDefintionPtr of the option defintion or an 
    /// empty OptionDefinitionPtr if not found.
    /// @throw DhcpConfigError if the option space requested is not valid 
    /// for this server. 
    virtual OptionDefinitionPtr findServerSpaceOptionDefinition (
        std::string& option_space, uint32_t option_code);

private:
    // Private default Constructor declared for safety.
    Dhcp6OptionDataParser() :OptionDataParser("",NULL,NULL,Option::V6) {}
};


}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP6_CONFIG_PARSER_H
