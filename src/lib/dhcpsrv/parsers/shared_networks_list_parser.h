// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
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

namespace isc {
namespace dhcp {

template<typename SharedNetworkParserType>
class SharedNetworksListParser : public data::SimpleParser {
protected:

    template<typename CfgSharedNetworksTypePtr>
    void parse(const data::ConstElementPtr& shared_networks_list_data,
               CfgSharedNetworksTypePtr& cfg) {
        if (shared_networks_list_data->getType() != Element::list) {
            isc_throw(data::DhcpConfigError, "shared-networks value must be a list");
        }
    }
               
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_NETWORKS_LIST_PARSER_H
