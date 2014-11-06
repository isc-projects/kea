// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef HOST_RESERVATION_PARSER_H
#define HOST_RESERVATION_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <dhcpsrv/host.h>

namespace isc {
namespace dhcp {

/// @brief Parser for a single host reservation entry.
class HostReservationParser : public DhcpConfigParser {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Identifier of the subnet that the host is
    /// connected to.
    HostReservationParser(const SubnetID& subnet_id);

    /// @brief Parses a single entry for host reservation.
    ///
    /// @param reservation_data Data element holding map with a host
    /// reservation configuration.
    ///
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual void build(isc::data::ConstElementPtr reservation_data);

    /// @brief Commit, unused.
    virtual void commit() { }

protected:

    /// @brief Inserts @c host_ object to the staging configuration.
    ///
    /// This method should be called by derived classes to insert the fully
    /// parsed host reservation configuration to the @c CfgMgr.
    ///
    /// @param reservation_data Data element holding host reservation. It
    /// used by this method to append the line number to the error string.
    ///
    /// @throw DhcpConfigError When operation to add a configured host fails.
    void addHost(isc::data::ConstElementPtr reservation_data);

    /// @brief Identifier of the subnet that the host is connected to.
    SubnetID subnet_id_;

    /// @brief Holds a pointer to @c Host object representing a parsed
    /// host reservation configuration.
    HostPtr host_;

};

/// @brief Parser for a single host reservation for DHCPv4.
class HostReservationParser4 : public HostReservationParser {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Identifier of the subnet that the host is
    /// connected to.
    HostReservationParser4(const SubnetID& subnet_id);

    /// @brief Parses a single host reservation for DHCPv4.
    ///
    /// @param reservation_data Data element holding map with a host
    /// reservation configuration.
    ///
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual void build(isc::data::ConstElementPtr reservation_data);
};

/// @brief Parser for a single host reservation for DHCPv6.
class HostReservationParser6 : public HostReservationParser {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Identifier of the subnet that the host is
    /// connected to.
    HostReservationParser6(const SubnetID& subnet_id);

    /// @brief Parses a single host reservation for DHCPv6.
    ///
    /// @param reservation_data Data element holding map with a host
    /// reservation configuration.
    ///
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual void build(isc::data::ConstElementPtr reservation_data);
};


}
} // end of namespace isc

#endif // HOST_RESERVATION_PARSER_H
