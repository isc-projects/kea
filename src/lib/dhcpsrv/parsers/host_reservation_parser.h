// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_RESERVATION_PARSER_H
#define HOST_RESERVATION_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/host.h>

namespace isc {
namespace dhcp {

/// @brief Parser for a single host reservation entry.
class HostReservationParser : public isc::data::SimpleParser {
public:

    /// @brief Destructor.
    virtual ~HostReservationParser() { }

    /// @brief Parses a single entry for host reservation.
    ///
    /// @param subnet_id Identifier of the subnet that the host is
    /// connected to.
    /// @param reservation_data Data element holding map with a host
    /// reservation configuration.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    ///
    /// @return Pointer to the object representing parsed host.
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual HostPtr
    parse(const SubnetID& subnet_id,
          isc::data::ConstElementPtr reservation_data,
          bool encapsulate_options = true) final;

protected:

    /// @brief Parses a single entry for host reservation.
    ///
    /// This method is called by @ref parse and it can be overridden in the
    /// derived classes to provide class specific parsing logic.
    ///
    /// @param subnet_id Identifier of the subnet that the host is
    /// connected to.
    /// @param reservation_data Data element holding map with a host
    /// reservation configuration.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    ///
    /// @return Pointer to the object representing parsed host.
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual HostPtr parseInternal(const SubnetID& subnet_id,
                                  isc::data::ConstElementPtr reservation_data,
                                  bool encapsulate_options);

    /// @brief Checks if the specified parameter is a host identifier.
    ///
    /// @param param_name Parameter name.
    ///
    /// @return true if the parameter specifies host identifier, false
    /// otherwise.
    virtual bool isIdentifierParameter(const std::string& param_name) const;

    /// @brief Checks if the specified parameter is supported by the parser.
    ///
    /// @param param_name Parameter name.
    ///
    /// @return true if the parameter is supported, false otherwise.
    virtual bool isSupportedParameter(const std::string& param_name) const;

    /// @brief Returns set of the supported parameters.
    ///
    /// @param identifiers_only Indicates if the function should only
    /// return supported host identifiers (if true) or all supported
    /// parameters (if false).
    ///
    /// @return Set of supported parameter names.
    virtual const std::set<std::string>&
    getSupportedParameters(const bool identifiers_only) const = 0;
};

/// @brief Parser for a single host reservation for DHCPv4.
class HostReservationParser4 : public HostReservationParser {
protected:

    /// @brief Parses a single host reservation for DHCPv4.
    ///
    /// @param subnet_id Identifier of the subnet that the host is
    /// connected to.
    /// @param reservation_data Data element holding map with a host
    /// reservation configuration.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    ///
    /// @return Pointer to the object representing parsed host.
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual HostPtr parseInternal(const SubnetID& subnet_id,
                                  isc::data::ConstElementPtr reservation_data,
                                  bool encapsulate_options);

    /// @brief Returns set of the supported parameters for DHCPv4.
    ///
    /// @param identifiers_only Indicates if the function should only
    /// return supported host identifiers (if true) or all supported
    /// parameters (if false).
    ///
    /// @return Set of supported parameter names.
    virtual const std::set<std::string>&
    getSupportedParameters(const bool identifiers_only) const;
};

/// @brief Parser for a single host reservation for DHCPv6.
class HostReservationParser6 : public HostReservationParser {
protected:

    /// @brief Parses a single host reservation for DHCPv6.
    ///
    /// @param subnet_id Identifier of the subnet that the host is
    /// connected to.
    /// @param reservation_data Data element holding map with a host
    /// reservation configuration.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    ///
    /// @return Pointer to the object representing parsed host.
    /// @throw DhcpConfigError If the configuration is invalid.
    virtual HostPtr parseInternal(const SubnetID& subnet_id,
                                  isc::data::ConstElementPtr reservation_data,
                                  bool encapsulate_options);

    /// @brief Returns set of the supported parameters for DHCPv6.
    ///
    /// @param identifiers_only Indicates if the function should only
    /// return supported host identifiers (if true) or all supported
    /// parameters (if false).
    ///
    /// @return Set of supported parameter names.
    virtual const std::set<std::string>&
    getSupportedParameters(const bool identifiers_only) const;

};

/// @brief Parser for a list of host identifiers.
///
/// This is a parent parser class for parsing "host-reservation-identifiers"
/// global configuration parameter. The DHCPv4 and DHCPv6 specific parsers
/// derive from this class.
class HostReservationIdsParser : public isc::data::SimpleParser {
public:

    /// @brief Constructor.
    HostReservationIdsParser();

    /// @brief Destructor.
    virtual ~HostReservationIdsParser() { }

    /// @brief Parses a list of host identifiers.
    ///
    /// @param ids_list Data element pointing to an ordered list of host
    /// identifier names.
    ///
    /// @throw DhcpConfigError If specified configuration is invalid.
    void parse(isc::data::ConstElementPtr ids_list);

protected:

    /// @brief Parses a list of host identifiers.
    ///
    /// This method is called by @ref parse and it can be overridden in the
    /// derived classes to provide class specific parsing logic.
    ///
    /// @param ids_list Data element pointing to an ordered list of host
    /// identifier names.
    ///
    /// @throw DhcpConfigError If specified configuration is invalid.
    virtual void parseInternal(isc::data::ConstElementPtr ids_list);

    /// @brief Checks if specified identifier name is supported in the
    /// context of the parser.
    ///
    /// This is abstract method which must be implemented in the derived
    /// parser classes for DHCPv4 and DHCPv6.
    ///
    /// @param id_name Identifier name.
    /// @return true if the specified identifier is supported, false
    /// otherwise.
    virtual bool isSupportedIdentifier(const std::string& id_name) const = 0;

    /// @brief Pointer to the object holding configuration.
    CfgHostOperationsPtr staging_cfg_;

};

/// @brief Parser for a list of host identifiers for DHCPv4.
class HostReservationIdsParser4 : public HostReservationIdsParser {
public:

    /// @brief Constructor.
    ///
    /// Initializes staging configuration pointer to the one used for DHCPv4
    /// configuration.
    HostReservationIdsParser4();

protected:

    /// @brief Checks if specified identifier name is supported for DHCPv4.
    ///
    /// @param id_name Identifier name.
    /// @return true if the specified identifier is supported, false
    /// otherwise.
    virtual bool isSupportedIdentifier(const std::string& id_name) const;

};

/// @brief Parser for a list of host identifiers for DHCPv6.
class HostReservationIdsParser6 : public HostReservationIdsParser {
public:

    /// @brief Constructor.
    ///
    /// Initializes staging configuration pointer to the one used for DHCPv6
    /// configuration.
    HostReservationIdsParser6();

protected:

    /// @brief Checks if specified identifier name is supported for DHCPv6.
    ///
    /// @param id_name Identifier name.
    /// @return true if the specified identifier is supported, false
    /// otherwise.
    virtual bool isSupportedIdentifier(const std::string& id_name) const;
};


}
} // end of namespace isc

#endif // HOST_RESERVATION_PARSER_H
