// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
    explicit HostReservationsListParser(const SubnetID& subnet_id)
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
