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

#ifndef IFACES_CONFIG_PARSER_H
#define IFACES_CONFIG_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>

namespace isc {
namespace dhcp {

/// @brief Parser for interface list definition.
///
/// This parser handles Dhcp4/interfaces-config/interfaces and
/// Dhcp6/interfaces-config/interfaces entries.
/// It contains a list of network interfaces that the server listens on.
/// In particular, it can contain an "*" that designates all interfaces.
class InterfaceListConfigParser : public DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param protocol AF_INET for DHCPv4 and AF_INET6 for DHCPv6.
    explicit InterfaceListConfigParser(const uint16_t protocol);

    /// @brief Parses a list of interface names.
    ///
    /// This method parses a list of interface/address tuples in a text
    /// format. The tuples specify the IP addresses and corresponding
    /// interface names on which the server should listen to the DHCP
    /// messages. The address is optional in each tuple and, if not
    /// specified, the interface name (without slash character) should
    /// be present.
    ///
    /// @param value pointer to the content of parsed values
    ///
    /// @throw DhcpConfigError if the interface names and/or addresses
    /// are invalid.
    virtual void build(isc::data::ConstElementPtr value);

    /// @brief Does nothing.
    virtual void commit();

private:

    /// @brief AF_INET for DHCPv4 and AF_INET6 for DHCPv6.
    uint16_t protocol_;

};


/// @brief Parser for the configuration of interfaces.
///
/// This parser parses the "interfaces-config" parameter which holds the
/// full configuration of the DHCP server with respect to the use of
/// interfaces, sockets and alike.
///
/// This parser uses the @c InterfaceListConfigParser to parse the
/// list of interfaces on which the server should listen. It handles
/// remaining parameters internally.
///
/// This parser is used as a base for the DHCPv4 and DHCPv6 specific
/// parsers and should not be used directly.
class IfacesConfigParser : public DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param protocol AF_INET for DHCPv4 and AF_INET6 for DHCPv6.
    explicit IfacesConfigParser(const uint16_t protocol);

    /// @brief Parses generic parameters in "interfaces-config".
    ///
    /// The generic parameters in the "interfaces-config" map are
    /// the ones that are common for DHCPv4 and DHCPv6.
    ///
    /// @param ifaces_config A data element holding configuration of
    /// interfaces.
    virtual void build(isc::data::ConstElementPtr ifaces_config);

    /// @brief Commit, unused.
    virtual void commit() { }

    /// @brief Checks if the specified parameter is a common parameter
    /// for DHCPv4 and DHCPv6 interface configuration.
    ///
    /// This method is invoked by the derived classes to check if the
    /// particular parameter is supported.
    ///
    /// @param parameter A name of the parameter.
    ///
    /// @return true if the specified parameter is a common parameter
    /// for DHCPv4 and DHCPv6 server.
    bool isGenericParameter(const std::string& parameter) const;

private:

    /// @brief AF_INET for DHCPv4 and AF_INET6 for DHCPv6.
    int protocol_;

};


/// @brief Parser for the "interfaces-config" parameter of the DHCPv4 server.
class IfacesConfigParser4 : public IfacesConfigParser {
public:

    /// @brief Constructor.
    ///
    /// Sets the protocol to AF_INET.
    IfacesConfigParser4();

    /// @brief Parses DHCPv4 specific parameters.
    ///
    /// Internally it invokes the @c InterfaceConfigParser::build to parse
    /// generic parameters. In addition, it parses the following parameters:
    /// - dhcp-socket-type
    ///
    /// @param ifaces_config A data element holding configuration of
    /// interfaces.
    ///
    /// @throw DhcpConfigError if unsupported parameters is specified.
    virtual void build(isc::data::ConstElementPtr ifaces_config);

};

/// @brief Parser for the "interfaces-config" parameter of the DHCPv4 server.
class IfacesConfigParser6 : public IfacesConfigParser {
public:

    /// @brief Constructor.
    ///
    /// Sets the protocol to AF_INET6.
    IfacesConfigParser6();

    /// @brief Parses DHCPv6 specific parameters.
    ///
    /// Internally it invokes the @c InterfaceConfigParser::build to parse
    /// generic parameters. Currently it doesn't parse any other parameters.
    ///
    /// @param ifaces_config A data element holding configuration of
    /// interfaces.
    ///
    /// @throw DhcpConfigError if unsupported parameters is specified.
    virtual void build(isc::data::ConstElementPtr ifaces_config);

};

}
} // end of namespace isc

#endif // IFACES_CONFIG_PARSER_H
