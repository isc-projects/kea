// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_RESERVATIONS_LIST_PARSER_H
#define HOST_RESERVATIONS_LIST_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <boost/foreach.hpp>

namespace isc {
namespace dhcp {

/// @brief Parser for a list of host reservations for a subnet.
///
/// @tparam HostReservationParserType Host reservation parser to be used to
/// parse individual reservations: @c HostReservationParser4 or
/// @c HostReservationParser6.
template<typename HostReservationParserType>
class HostReservationsListParser : public DhcpConfigParser {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Identifier of the subnet to which the reservations
    /// belong.
    HostReservationsListParser(const SubnetID& subnet_id)
        : subnet_id_(subnet_id) {
    }

    /// @brief Parses a list of host reservation entries for a subnet.
    ///
    /// @param hr_list Data element holding a list of host reservations.
    /// Each host reservation is described by a map object.
    ///
    /// @throw DhcpConfigError If the configuration if any of the reservations
    /// is invalid.
    virtual void build(isc::data::ConstElementPtr hr_list) {
        BOOST_FOREACH(data::ConstElementPtr reservation, hr_list->listValue()) {
            ParserPtr parser(new HostReservationParserType(subnet_id_));
            parser->build(reservation);
        }
    }

    /// @brief Commit, unused.
    virtual void commit() { }

private:

    /// @brief Identifier of the subnet to whic the reservations belong.
    SubnetID subnet_id_;

};

}
}

#endif // HOST_RESERVATIONS_LIST_PARSER_H
