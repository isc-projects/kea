// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IFACES_CONFIG_PARSER_H
#define IFACES_CONFIG_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfg_iface.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>

namespace isc {
namespace dhcp {

/// @brief Parser for the configuration of interfaces.
///
/// This parser parses the "interfaces-config" parameter which holds the
/// full configuration of the DHCP server with respect to the use of
/// interfaces, DHCP traffic sockets and alike.
///
/// This parser is used in both DHCPv4 and DHCPv6. Derived parsers
/// are not needed.
class IfacesConfigParser : public isc::data::SimpleParser {
public:

    /// @brief Constructor
    ///
    /// In test mode only the configuration is checked. In particular
    /// sockets are not opened or closed.
    ///
    /// @param protocol AF_INET for DHCPv4 and AF_INET6 for DHCPv6.
    /// @param test_mode True if in test mode, False if not.
    IfacesConfigParser(const uint16_t protocol, bool test_mode);

    /// @brief Parses content of the "interfaces-config".
    ///
    /// @param config parsed structures will be stored here
    /// @param values pointer to the content of parsed values
    ///
    /// @throw DhcpConfigError if the interface names and/or addresses
    /// are invalid.
    void parse(const CfgIfacePtr& config, const isc::data::ConstElementPtr& values);

private:
    /// @brief parses interfaces-list structure
    ///
    /// This method goes through all the interfaces-specified in
    /// 'interfaces-list' and enabled them in the specified configuration
    /// structure
    ///
    /// @param cfg_iface parsed interfaces will be specified here
    /// @param ifaces_list interfaces-list to be parsed
    /// @throw DhcpConfigError if the interface names are invalid.
    void parseInterfacesList(const CfgIfacePtr& cfg_iface,
                             isc::data::ConstElementPtr ifaces_list);

    /// @brief AF_INET for DHCPv4 and AF_INET6 for DHCPv6.
    int protocol_;

    /// @brief Test mode.
    bool test_mode_;
};

}
} // end of namespace isc

#endif // IFACES_CONFIG_PARSER_H
