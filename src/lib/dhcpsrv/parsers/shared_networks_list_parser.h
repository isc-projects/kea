// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_NETWORKS_LIST_PARSER_H
#define SHARED_NETWORKS_LIST_PARSER_H

#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <cc/simple_parser.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Parser for a list of shared networks.
///
/// This is a generic parser for a list of IPv4 or IPv6 shared networks.
///
/// @tparam SharedNetworkParserType Type of the parser to be used for
/// parsing shared network, i.e. @ref SharedNetwork4Parser or
/// @ref SharedNetwork6Parser.
template<typename SharedNetworkParserType>
class SharedNetworksListParser : public data::SimpleParser {
public:

    /// @brief Constructor.
    ///
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    SharedNetworksListParser(bool check_iface = true)
        : check_iface_(check_iface) {
    }

    /// @brief Parses a list of shared networks.
    ///
    /// @tparam CfgSharedNetworksTypePtr Type of the configuration structure
    /// into which the result will be stored, i.e. @ref CfgSharedNetworks4
    /// or @ref CfgSharedNetworks6.
    /// @param [out] cfg Shared networks configuration structure into which
    /// the data should be parsed.
    /// @param shared_networks_list_data List element holding a list of
    /// shared networks.
    ///
    /// @throw DhcpConfigError when error has occurred, e.g. when networks
    /// with duplicated names have been specified.
    template<typename CfgSharedNetworksTypePtr>
    void parse(CfgSharedNetworksTypePtr& cfg,
               const data::ConstElementPtr& shared_networks_list_data) {
        try {
            // Get the C++ vector holding networks.
            const std::vector<data::ElementPtr>& networks_list =
                shared_networks_list_data->listValue();
            // Iterate over all networks and do the parsing.
            for (auto network_element = networks_list.cbegin();
                 network_element != networks_list.cend(); ++network_element) {
                SharedNetworkParserType parser(check_iface_);
                auto network = parser.parse(*network_element);
                cfg->add(network);
            }
        } catch (const DhcpConfigError&) {
            // Such exceptions are emitted by the lower level parsers and
            // errors should already include element's positions. So, we
            // simply rethrow.
            throw;

        } catch (const std::exception& ex) {
            // Other exceptions don't include positions of the elements, so
            // we should append one.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << shared_networks_list_data->getPosition() << ")");
        }
    }

protected:
    /// Check if the specified interface exists in the system.
    bool check_iface_;
};

/// @brief Type of the shared networks list parser for IPv4.
typedef SharedNetworksListParser<SharedNetwork4Parser> SharedNetworks4ListParser;

/// @brief Type of the shared networks list parser for IPv6.
typedef SharedNetworksListParser<SharedNetwork6Parser> SharedNetworks6ListParser;


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_NETWORKS_LIST_PARSER_H
