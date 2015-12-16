// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_RESERVATION_PARSER_H
#define HOST_RESERVATION_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>

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

    /// @brief Checks if the specified parameter is supported by the parser.
    ///
    /// @param param_name Parameter name.
    ///
    /// @return true if the parameter is supported, false otherwise.
    virtual bool isSupportedParameter(const std::string& param_name) const = 0;

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

protected:

    /// @brief Checks if the specified parameter is supported by the parser.
    ///
    /// @param param_name Parameter name.
    ///
    /// @return true if the parameter is supported, false otherwise.
    virtual bool isSupportedParameter(const std::string& param_name) const;
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

protected:

    /// @brief Checks if the specified parameter is supported by the parser.
    ///
    /// @param param_name Parameter name.
    ///
    /// @return true if the parameter is supported, false otherwise.
    virtual bool isSupportedParameter(const std::string& param_name) const;
};


}
} // end of namespace isc

#endif // HOST_RESERVATION_PARSER_H
