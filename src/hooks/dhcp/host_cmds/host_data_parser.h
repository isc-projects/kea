// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_DATA_PARSER_H
#define HOST_DATA_PARSER_H

#include <dhcpsrv/cfg_host_operations.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace host_cmds {

/// @brief A class for parsing extended host reservation data
///
/// This template class provides a convenient interface for parsing extended
/// host reservation data. Extended means that it is the typical host reservation
/// as used in configuration file, with the addition of subnet-id parameter.
/// It is not needed in the configuration file, because it's always obvious
/// from the context (HR is defined in a subnet that has subnet-id). However,
/// in reservation-add, reservation-del, reservation-update commands,
/// the subnet-id parameter has to be specified explicitly.
///
/// @tparam ParserBase base class to be extended
template<typename ParserBase>
class HostDataParser : public ParserBase {
public:

    /// @brief Parser specified parameter as host reservation data
    ///
    /// This method expects the input to be a ConstElementPtr tree structure
    /// that represents host reservation information. If parsing is successful,
    /// it returns HostPtr to the Host object that was created.
    ///
    /// This method calls parse method from the ParserBase class. This method
    /// may throw additional exception types.
    ///
    /// @param host_data Element tree to be parsed
    /// @param required True (default) if the subnet-id entry is required,
    /// false otherwise.
    /// @return parsed host information
    /// @throw BadValue if subnet-id is required but missing, or has invalid
    /// format.
    isc::dhcp::HostPtr parseWithSubnet(isc::data::ConstElementPtr host_data,
                                       bool required = true) {
        uint32_t subnet_id = dhcp::SUBNET_ID_UNUSED;
        boost::shared_ptr<isc::data::MapElement> new_map = boost::dynamic_pointer_cast<
            isc::data::MapElement>(isc::data::Element::createMap());

        for (auto const& el : host_data->mapValue()) {
            if (el.first == "subnet-id") {
                if (el.second->getType() != isc::data::Element::integer) {
                    isc_throw(isc::BadValue,
                              "'subnet-id' parameter is not integer.");
                }

                if (el.second->intValue() < 0 ||
                    el.second->intValue() > dhcp::SUBNET_ID_MAX) {
                    isc_throw(isc::BadValue,
                              "subnet-id: " << el.second->intValue()
                              << " is invalid," << " must be between 0 and "
                              << dhcp::SUBNET_ID_MAX << " (inclusive).");
                }

                subnet_id = static_cast<uint32_t>(el.second->intValue());
            } else {
                new_map->set(el.first, el.second);
            }
        }

        if (required && (subnet_id == dhcp::SUBNET_ID_UNUSED)) {
            isc_throw(isc::BadValue,
                      "Mandatory 'subnet-id' parameter missing."
                      << " Use `reservation-get-by-id' or"
                      << " 'reservation-get-by-address' to get the list of"
                      << " reservations with given identifier or address.");
        }

        // Parse host reservations without encapsulating options with suboptions.
        return (ParserBase::parse(subnet_id,
                                  boost::dynamic_pointer_cast<const isc::data::Element>(new_map),
                                  false));
    }
};

/// @brief Parser for DHCPv4 host reservation
typedef HostDataParser<isc::dhcp::HostReservationParser4> HostDataParser4;

/// @brief Parser for DHCPv4 host reservation
typedef HostDataParser<isc::dhcp::HostReservationParser6> HostDataParser6;

}  // namespace host_cmds
}  // namespace isc

#endif
